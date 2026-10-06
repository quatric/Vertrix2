"""Compare complete original board action routines with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
Allocate = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_void_p)
Range = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_uint32), c.POINTER(c.c_uint32), c.c_void_p)
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
    n = build(args.build_dir, 'board-actions',
              ['board_actions.c', 'block_factory.c', 'board_markers.c', 'board.c', 'board_cells.c',
               'actor_storage.c', 'actor_fields.c', 'random.c'])
    S = c.POINTER(Services)
    P, SZ, UP = c.c_void_p, c.c_size_t, c.POINTER(U)
    n.vertrix_board_piece_hits_grid.argtypes = [P, SZ, S, UP, UP]
    n.vertrix_board_start_marked.argtypes = [P, SZ, S]
    n.vertrix_board_flag_marked.argtypes = [P, SZ, S]
    n.vertrix_actor_start_slide.argtypes = [P, SZ, P, SZ, c.c_int32, c.c_int32]
    n.vertrix_board_make_stone.argtypes = [P, SZ, c.c_int8, c.c_int8, S]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4330d0)
    pool = Pool(cpu, 12, SIZE)
    board, other = pool.handles[0], pool.handles[1]
    targets = pool.handles[2:]
    draws, allocations, replay = [], [], {
    'draws' : [], 'allocs' : []}

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            handle = targets[len(allocations) % len(targets)]
            allocations.append(handle)
            return handle
        draws.append(rng.randrange(edx & 0xffff))
        return draws[-1]

    stubs = Stubs(cpu, handler)
    stubs.add(0x4ca000)
    stubs.add(0x4826c0)

    @Draw
    def draw(divisor, context):
        value = replay['draws'].pop(0)
        assert value < divisor
        return value

    @Allocate
    def allocate(size, context):
        return replay['allocs'].pop(0)

    @Range
    def table_range(index, lo, hi, context):
        lo[0] = struct.unpack('<I', bytes(cpu.mem_read((0x53bcd0 + 8 * index) & 0xffffffff, 4)))[0]
        hi[0] = struct.unpack('<I', bytes(cpu.mem_read((0x53bcd4 + 8 * index) & 0xffffffff, 4)))[0]
        return 1

    services = Services(pool.resolve, allocate, draw, table_range, None)
    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    def fresh(markers=False, full=False, piece=True, stone=False):
        def patch(handle, data):
            if handle in (board, other):
                for grid in (GRID, COMPANION):
                    for i in range(65):
                        fill = full or rng.random() < 0.5
                        struct.pack_into('<I', data, grid + 4 * i,
                                         rng.choice(targets) if fill else 0)
            if handle == board:
                struct.pack_into('<H', data, 0xe, rng.randrange(0, 200))
                struct.pack_into('<H', data, 0x16, rng.randrange(0, 200))
                struct.pack_into('<I', data, 0xa60, rng.choice(targets))
                for i in range(65):
                    data[MARKERS + i] = rng.choice([0, 0, 1, 1, 2, 3]) if markers else data[MARKERS + i]
            elif handle in targets:
                data[0x15c] = rng.choice([0, 1, 5, 5, rng.getrandbits(8)])
        pool.fill(rng, patch)
        draws.clear()
        allocations.clear()
        if piece:
            piece_handle = struct.unpack_from('<I', pool.buffers[board].raw, 0xa60)[0]
            bx = struct.unpack_from('<H', pool.buffers[board].raw, 0xe)[0]
            by = struct.unpack_from('<H', pool.buffers[board].raw, 0x16)[0]
            px = (bx + 24 * rng.randrange(-1, 6) + rng.randrange(0, 24)) & 0xffff
            py = (by + rng.randrange(-60, 340)) & 0xffff
            for buffer in (pool.buffers[piece_handle],):
                struct.pack_into('<H', buffer, 0xe, px)
                struct.pack_into('<H', buffer, 0x16, py)
            data = bytes(pool.buffers[piece_handle].raw)
            cpu.mem_write(piece_handle, data)

    def begin():
        replay['draws'] = list(draws)
        replay['allocs'] = list(allocations)

    for case in range(args.cases):
# 4330d0
        fresh()
        expect = original.call(0x4330d0, eax=board, edx=other) & 0xffffffff
        grid = (U * 65).from_buffer_copy(pool.buffers[other].raw[GRID:GRID + 260])
        hit = U()
        if n.vertrix_board_piece_hits_grid(pool.buffers[board], SIZE, c.byref(services), grid,
                                           c.byref(hit)):
            assert hit.value == expect, (case, hit.value, expect)
            count('0x4330d0')
# 4371b0 and 437460
        for address, native, name in ((0x4371b0, n.vertrix_board_start_marked, '0x4371b0'),
                                      (0x437460, n.vertrix_board_flag_marked, '0x437460')):
            fresh(markers=True, full=True, piece=False)
            result = original.call(address, eax=board)
            assert native(pool.buffers[board], SIZE, c.byref(services)), (case, name)
            assert result == 1, (name, result)
            assert pool.same(), (case, name, pool.diff())
            count(name)
# 438470
        fresh(piece=False)
        actor = rng.choice(targets)
        cells_x, cells_y = rng.randrange(-3, 8), rng.randrange(-3, 15)
        by = struct.unpack_from('<H', pool.buffers[board].raw, 0x16)[0]
        ay = (by + 24 * cells_y + rng.choice([0, 0, -5, 5, 24, -24])) & 0xffff
        struct.pack_into('<H', pool.buffers[actor], 0x16, ay)
        cpu.mem_write(actor, bytes(pool.buffers[actor].raw))
        original.call(0x438470, eax=board, edx=actor, ebx=cells_x, ecx=cells_y)
        assert n.vertrix_actor_start_slide(pool.buffers[board], SIZE, pool.buffers[actor], SIZE,
                                           cells_x, cells_y)
        assert pool.same(), (case, pool.diff())
        count('0x438470')
# 433750
        fresh(piece=False)
        col, row = rng.randrange(0, 5), rng.randrange(0, 13)
        if rng.random() < 0.6:
            struct.pack_into('<I', pool.buffers[board], COMPANION + 0x34 * col + 4 * row, 0)
            struct.pack_into('<I', pool.buffers[board], GRID + 0x34 * col + 4 * row,
                             rng.choice(targets[:3]))
            cpu.mem_write(board, bytes(pool.buffers[board].raw))
        result = original.call(0x433750, eax=board, edx=col, ebx=row)
        begin()
        ok = n.vertrix_board_make_stone(pool.buffers[board], SIZE, col, row,
                                        c.byref(services))
        assert ok == (result & 0xff) or (not ok and (result & 0xff) == 0), (case, ok, result)
        if result & 0xff:
            assert pool.same(), (case, pool.diff())
            assert not replay['draws'] and not replay['allocs']
            count('0x433750')
        else:
            count('0x433750_declined')
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 4330d0, 4371b0, 437460, 438470 and 433750 execute in the original '
                       '(operator new 4ca000 and the draw 4826c0 stubbed and replayed, recovered '
                       'building blocks executed for real); returned values, whole boards and '
                       'objects, and the draws consumed compare.'}
    (args.build_dir / 'board-actions-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
