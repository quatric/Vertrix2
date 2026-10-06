"""Compare complete original board/active-piece routines with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, build

U = c.c_uint32
SIZE = 0xd00


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'board-piece',
              ['board_piece.c', 'piece_children.c', 'actor_storage.c', 'actor_fields.c'])
    P, SZ, UP = c.c_void_p, c.c_size_t, c.POINTER(U)
    K = c.c_uint8 * 3
    n.vertrix_board_has_piece.argtypes = [P, SZ, UP]
    n.vertrix_board_fill_cells.argtypes = [P, SZ]
    n.vertrix_board_piece_child_kinds.argtypes = [P, SZ, Resolve, P, K]
    n.vertrix_board_flash_children.argtypes = [P, SZ, Resolve, P]
    n.vertrix_board_piece_past_edge.argtypes = [P, SZ, Resolve, P, c.c_int, UP]
    I = c.c_int32
    n.vertrix_board_piece_column.argtypes = [P, SZ, Resolve, P, c.POINTER(I)]
    n.vertrix_board_piece_span.argtypes = [P, SZ, Resolve, P, c.POINTER(I), c.POINTER(I),
                                           c.POINTER(I)]
    n.vertrix_board_piece_child_kind.argtypes = [P, SZ, Resolve, P, U, c.POINTER(I)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x431fb0)
    pool = Pool(cpu, 6, SIZE)
    board, piece, kids = pool.handles[0], pool.handles[1], pool.handles[2:5]
    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    for case in range(args.cases):
        def patch(handle, data):
            if handle == board:
                struct.pack_into('<I', data, 0xa60, rng.choice([piece, piece, 0]))
                x = rng.choice([rng.getrandbits(16), rng.randrange(0, 400)])
                struct.pack_into('<H', data, 0xe, x)
                struct.pack_into('<H', data, 0x16, rng.getrandbits(16))
            elif handle == piece:
                for slot, kid in zip((0x15c, 0x160, 0x164), kids):
                    struct.pack_into('<I', data, slot, rng.choice([kid, kid, piece]))
                struct.pack_into('<H', data, 0xe, rng.choice([rng.getrandbits(16),
                                                              rng.randrange(0, 400)]))

        pool.fill(rng, patch)
        has = U()
        expect = original.call(0x4320c0, eax=board) & 0xff
        assert n.vertrix_board_has_piece(pool.buffers[board], SIZE, c.byref(has))
        assert has.value == expect, case
        count('0x4320c0')
        original.call(0x42f2e0, eax=board)
        assert n.vertrix_board_fill_cells(pool.buffers[board], SIZE)
        assert pool.same(), (case, pool.diff())
        count('0x42f2e0')
        pool.fill(rng, patch)
        if struct.unpack_from('<I', pool.buffers[board].raw, 0xa60)[0]:
        out = K(0xaa, 0xaa, 0xaa) cpu.mem_write(0x80c000, bytes([0xaa] * 3)) original
                  .call(0x431fa0, eax = board, edx = 0x80c000, ebx = 0x80c001, ecx = 0x80c002)
                      assert n.vertrix_board_piece_child_kinds(pool.buffers[board], SIZE,
                                                               pool.resolve, None, out) assert
              bytes(out) == bytes(cpu.mem_read(0x80c000, 3)),
        case count('0x431fa0') original.call(0x431fb0, eax = board) assert n
            .vertrix_board_flash_children(pool.buffers[board], SIZE, pool.resolve,
                                          None) assert pool.same(),
        (case, pool.diff())count('0x431fb0') pool.fill(rng, patch) if not struct.unpack_from(
            '<I', pool.buffers[board].raw, 0xa60)[0]:
                continue
            for right, address in ((1, 0x432040), (0, 0x432080)):
                expect = original.call(address, eax=board) & 0xff
                past = U()
                assert n.vertrix_board_piece_past_edge(pool.buffers[board], SIZE, pool.resolve,
                                                       None, right, c.byref(past))
                assert past.value == expect, (case, hex(address))
                count(hex(address))
            expect = original.call(0x431340, eax=board)
            column = I()
            assert n.vertrix_board_piece_column(pool.buffers[board], SIZE, pool.resolve, None,
                                                c.byref(column))
            assert column.value == c.c_int32(expect).value, case
            count('0x431340')
            cpu.mem_write(0x80c100, bytes(12))
            assert original.call(0x431b20, eax=board, edx=0x80c100, ebx=0x80c104,
                                 ecx=0x80c108) == 1
            native = [I(), I(), I()]
            assert n.vertrix_board_piece_span(pool.buffers[board], SIZE, pool.resolve, None,
                                              *[c.byref(v) for v in native])
            expect = struct.unpack('<iii', bytes(cpu.mem_read(0x80c100, 12)))
            assert (native[0].value, native[1].value, native[2].value) == (
                expect[0], expect[1], expect[2]), case
            count('0x431b20')
            index = rng.randrange(0, 3)
            expect = original.call(0x431c10, eax=board, edx=index)
            kind = I()
            assert n.vertrix_board_piece_child_kind(pool.buffers[board], SIZE, pool.resolve, None,
                                                    index, c.byref(kind))
            assert kind.value == c.c_int32(expect).value, case
            count('0x431c10')
    assert not n.vertrix_board_has_piece(pool.buffers[board], 0xa63, c.byref(has))
    assert not n.vertrix_board_fill_cells(pool.buffers[board], 0x1dd)
    report = {'status':
                'passed', 'complete_original_executions' : totals,
                                                           'scope'
                    : 'Complete 4320c0, 42f2e0, 431fa0, 431fb0, 432040, 432080, 431340, 431b20 and 431c10 execute in the ' 'original; return values and every pool object compare.'
                }
                (args.build_dir / 'board-piece-verification.json')
                        .write_text(json.dumps(report, indent = 2) + '\n')
                            print(json.dumps(report, indent = 2))

                                if __name__ == '__main__' : main()
