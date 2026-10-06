"""Compare complete original board piece move routines with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, build

U = c.c_uint32
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
Allocate = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_void_p)
Range = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_uint32), c.POINTER(c.c_uint32), c.c_void_p)
Read = c.CFUNCTYPE(c.c_int, U, c.c_uint, c.POINTER(U), c.c_void_p)
SIZE = 0xd00
GRID, COMPANION, MARKERS = 0x220, 0x87c, 0xb94


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', Allocate), ('draw', Draw), ('range', Range),
                ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'board-piece-moves',
              ['board_piece_moves.c', 'board_piece.c', 'piece_children.c', 'board_markers.c', 'board.c', 'board_cells.c',
               'actor_storage.c', 'actor_fields.c', 'random.c'])
    S = c.POINTER(Services)
    P, SZ, UP = c.c_void_p, c.c_size_t, c.POINTER(U)
    class Piece(c.Structure):
        _fields_ = [('resolve', Resolve), ('read', Read), ('context', c.c_void_p)]
    PS = c.POINTER(Piece)
    n.vertrix_board_piece_shape_fits.argtypes = [P, SZ, U, U, PS, UP]
    n.vertrix_board_piece_touches_side.argtypes = [P, SZ, U, U, c.c_int, PS, UP]
    n.vertrix_board_piece_store_negated.argtypes = [P, SZ, U, U, PS]
    n.vertrix_board_piece_store_negated_always.argtypes = [P, SZ, PS]
    n.vertrix_board_piece_store_touch.argtypes = [P, SZ, U, U, c.c_int, PS]
    n.vertrix_board_piece_shift.argtypes = [P, SZ, U, U, c.c_int, PS]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x42f280)
    pool = Pool(cpu, 10, SIZE)
    board = pool.handles[0]
    targets = pool.handles[1:]

    @Read
    def read(address, width, value, context):
        value[0] = int.from_bytes(bytes(cpu.mem_read(address, width)), 'little')
        return 1

    services = Piece(pool.resolve, read, None)
    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    def fresh(missing=0.0):
        piece = rng.choice(targets)
        bx, by = rng.randrange(0, 200), rng.randrange(0, 200)
        px = (bx + 24 * rng.randrange(-1, 6) + rng.randrange(0, 24)) & 0xffff
        py = (by + rng.randrange(-30, 300)) & 0xffff

        def patch(handle, data):
            if handle == board:
                struct.pack_into('<I', data, 0xc, bx << 16)
                struct.pack_into('<I', data, 0x14, by << 16)
                struct.pack_into('<I', data, 0xa60, piece if rng.random() >= missing else 0)
                data[0x58] = rng.getrandbits(8)
                for i in range(65):
                    struct.pack_into('<I', data, 0x220 + 4 * i,
                                     rng.choice(targets) if rng.random() < 0.5 else 0)
            elif handle == piece:
                struct.pack_into('<I', data, 0xc, px << 16)
                struct.pack_into('<I', data, 0x14, py << 16)
        pool.fill(rng, patch)
        return piece

    for case in range(args.cases):
        fresh()
        shape, rotation = rng.randrange(0, 8), rng.randrange(0, 4)
        b = pool.buffers[board]
        for side, addr in ((0, 0x42efa0), (-1, 0x42f030), (1, 0x42f120)):
            expect = original.call(addr, eax=board, edx=shape, ebx=rotation) & 0xffffffff
            out = U()
            if side == 0:
                ok = n.vertrix_board_piece_shape_fits(b, SIZE, shape, rotation, c.byref(services),
                                                      c.byref(out))
            else:
                ok = n.vertrix_board_piece_touches_side(b, SIZE, shape, rotation, side,
                                                        c.byref(services), c.byref(out))
            assert ok and out.value == expect, (case, hex(addr), out.value, expect)
            count(hex(addr))
        for addr, native, name in (
                (0x42f280, lambda: n.vertrix_board_piece_store_negated(
                    b, SIZE, shape, rotation, c.byref(services)), '0x42f280'),
                (0x42f2b0, lambda: n.vertrix_board_piece_store_negated_always(
                    b, SIZE, c.byref(services)), '0x42f2b0'),
                (0x42f520, lambda: n.vertrix_board_piece_store_touch(
                    b, SIZE, shape, rotation, -1, c.byref(services)), '0x42f520'),
                (0x42f550, lambda: n.vertrix_board_piece_store_touch(
                    b, SIZE, shape, rotation, 1, c.byref(services)), '0x42f550'),
                (0x42f6e0, lambda: n.vertrix_board_piece_shift(
                    b, SIZE, shape, rotation, -1, c.byref(services)), '0x42f6e0'),
                (0x42f720, lambda: n.vertrix_board_piece_shift(
                    b, SIZE, shape, rotation, 1, c.byref(services)), '0x42f720')):
            fresh(0.1)
            b = pool.buffers[board]
            before = [bytes(pool.buffers[h].raw) for h in pool.handles]
            if addr == 0x42f2b0:
                original.call(addr, eax=board, edx=0xdeadbeef)
            else:
                original.call(addr, eax=board, edx=shape, ebx=rotation)
            assert native(), (case, name)
            assert pool.same(), (case, name, pool.diff())
            if before != [bytes(pool.buffers[h].raw) for h in pool.handles]:
                count(name + '_changed')
            count(name)
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 42efa0, 42f030, 42f120, 42f280, 42f2b0, 42f520, 42f550, 42f6e0 '
                       'and 42f720 execute in the original with shape tables read from original '
                       'memory; return values, whole boards and pieces compare.'}
    (args.build_dir / 'board-piece-moves-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
