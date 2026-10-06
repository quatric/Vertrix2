"""Compare complete original choice grid routines with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Stubs, build

BOARD = 0x800000
SIZE = 0x300
CELLS, VALUES, FIRST, SECOND = 0x15c, 0x1cc, 0x23c, 0x258
U = c.c_uint32
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)


class Grid(c.Structure):
    _fields_ = [('cells', U * 28), ('values', U * 28), ('first', c.c_uint8 * 28),
                ('second', c.c_uint8 * 28)]


def grid_from(memory):
    return Grid.from_buffer_copy(memory[CELLS:CELLS + 0x70] + memory[VALUES:VALUES + 0x70]
                                 + memory[FIRST:FIRST + 28] + memory[SECOND:SECOND + 28])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'choice-grid', ['choice_grid.c', 'actor_storage.c', 'actor_fields.c'])
    G = c.POINTER(Grid)
    n.vertrix_choice_grid_apply.argtypes = [G, __import__('oracle_kit').Resolve, c.c_void_p]
    n.vertrix_choice_grid_load_values.argtypes = [G, c.POINTER(U), n.vertrix_choice_grid_apply.argtypes[1],
                                                  c.c_void_p]
    n.vertrix_choice_grid_store_values.argtypes = [G, c.POINTER(U), U]
    n.vertrix_choice_grid_pick_rows.argtypes = [G, c.c_uint8, c.POINTER(U), Draw, c.c_void_p]
    n.vertrix_choice_grid_pick_cell.argtypes = [G, c.POINTER(c.c_uint8), c.POINTER(c.c_uint8), Draw, c.c_void_p]
    n.vertrix_choice_grid_pick_column.argtypes = [G, c.c_uint8, c.POINTER(c.c_uint8), Draw, c.c_void_p]
    for name in ('mark', 'available'):
        getattr(n, 'vertrix_choice_grid_' + name).argtypes = [G, U, U, n.vertrix_choice_grid_apply.argtypes[1],
                                                              c.c_void_p]
    n.vertrix_choice_grid_any_marked.argtypes = [G, n.vertrix_choice_grid_apply.argtypes[1], c.c_void_p]
    n.vertrix_choice_grid_cell_bytes.argtypes = [G, U, U, c.POINTER(c.c_uint8), c.POINTER(c.c_uint8)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x429d50)
    pool = Pool(cpu, 40)
    draws = []

    def handler(address, eax, edx, ebx, ecx, stack):
        value = rng.randrange(edx & 0xffff)
        draws.append(value)
        return value

    stubs = Stubs(cpu, handler)
    stubs.add(0x4826c0)
    replay = iter([])

    @Draw
    def draw(divisor, context):
        return next(replay)

    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    for case in range(args.cases):
        memory = bytearray(rng.randbytes(SIZE))
        density = rng.choice([0.2, 0.7, 1.0])
        for i in range(28):
            struct.pack_into('<I', memory, CELLS + 4 * i,
                             rng.choice(pool.handles) if rng.random() < density else 0)
            struct.pack_into('<I', memory, VALUES + 4 * i, rng.choice([0, 1, 1, 2, 0xffffffff]))
        row_mode = rng.random()
        if row_mode < 0.3:
            for i in range(28):
                if i // 4 in rng.sample(range(7), rng.randrange(8)):
                    struct.pack_into('<I', memory, VALUES + 4 * i, 0)

        def patch(handle, data):
            data[0x15c] = rng.choice([0, 0, 1, 2])
            data[0x15d] = rng.choice([0, 1, 1, 2])

        def fresh():
            cpu.mem_write(BOARD, bytes(memory))
            pool.fill(rng, patch)
            return grid_from(memory)

        def check(grid, name):
            assert bytes(grid) == bytes(grid_from(bytes(cpu.mem_read(BOARD, SIZE)))), (case, name)
            assert pool.same(), (case, name, pool.diff())
            count(name)

        grid = fresh()
        original.call(0x429d50, eax=BOARD)
        assert n.vertrix_choice_grid_apply(c.byref(grid), pool.resolve, None)
        check(grid, 'apply')
        grid = fresh()
        source = (U * 28)(*[rng.choice([0, 1, 1, 2, 0xffffffff]) for _ in range(28)])
        cpu.mem_write(BOARD + 0x400, bytes(source))
        original.call(0x429df0, eax=BOARD, edx=BOARD + 0x400)
        assert n.vertrix_choice_grid_load_values(c.byref(grid), source, pool.resolve, None)
        check(grid, 'load_values')
        grid = fresh()
        start = rng.randrange(0, 5)
        cpu.mem_write(BOARD + 0x400, bytes(0x200))
        original.call(0x429e80, eax=BOARD, edx=BOARD + 0x400, ecx=start)
        out = (U * 128)()
        n.vertrix_choice_grid_store_values(c.byref(grid), out, start)
        assert bytes(out)[:0x200] == bytes(cpu.mem_read(BOARD + 0x400, 0x200)), case
        check(grid, 'store_values')
        grid = fresh()
        limit = rng.choice([0, 1, 2, 3, 7, 9, 255])
        cpu.mem_write(BOARD + 0x400, bytes(range(32)))
        draws.clear()
        result = original.call(0x429ee0, eax=BOARD, edx=BOARD + 0x400, ebx=limit)
        replay = iter(list(draws))
        rows = (U * 8)(*[0xdead] * 8)
        found = n.vertrix_choice_grid_pick_rows(c.byref(grid), limit, rows, draw, None)
        assert found == result & 0xffffffff, case
        assert bytes(rows)[:28] == bytes(cpu.mem_read(BOARD + 0x400, 28)), case
        assert next(replay, None) is None, case
        check(grid, 'pick_rows')
        grid = fresh()
        row = rng.randrange(7)
        cpu.mem_write(BOARD + 0x400, bytes([0xaa] * 8))
        draws.clear()
        result = original.call(0x42a080, eax=BOARD, edx=row, ebx=BOARD + 0x400)
        replay = iter(list(draws))
        column = c.c_uint8(0xaa)
        found = n.vertrix_choice_grid_pick_column(c.byref(grid), row, c.byref(column), draw, None)
        assert found == result & 0xffffffff, case
        assert column.value == cpu.mem_read(BOARD + 0x400, 1)[0], case
        assert next(replay, None) is None, case
        check(grid, 'pick_column')
        grid = fresh()
        cpu.mem_write(BOARD + 0x400, bytes([0xaa] * 8))
        draws.clear()
        result = original.call(0x429fe0, eax=BOARD, edx=BOARD + 0x400, ebx=BOARD + 0x401)
        replay = iter(list(draws))
        row_out, column = c.c_uint8(0xaa), c.c_uint8(0xaa)
        found = n.vertrix_choice_grid_pick_cell(c.byref(grid), c.byref(row_out), c.byref(column),
                                                draw, None)
        assert found == result & 0xffffffff, case
        assert bytes([row_out.value, column.value]) == bytes(cpu.mem_read(BOARD + 0x400, 2)), case
        assert next(replay, None) is None, case
        check(grid, 'pick_cell')
        grid = fresh()
        row, col = rng.randrange(7), rng.randrange(4)
        result = original.call(0x42a140, eax=BOARD, edx=row, ebx=col)
        assert n.vertrix_choice_grid_mark(c.byref(grid), row, col, pool.resolve, None) == result & 0xffffffff
        check(grid, 'mark')
        grid = fresh()
        result = original.call(0x42a190, eax=BOARD, edx=row, ebx=col)
        assert n.vertrix_choice_grid_available(c.byref(grid), row, col, pool.resolve, None) == \
            result & 0xffffffff
        check(grid, 'available')
        grid = fresh()
        result = original.call(0x42a1b0, eax=BOARD)
        assert n.vertrix_choice_grid_any_marked(c.byref(grid), pool.resolve, None) == result & 0xffffffff
        check(grid, 'any_marked')
        grid = fresh()
        cpu.mem_write(BOARD + 0x400, bytes([0xaa, 0xbb]))
        original.call(0x42a170, eax=BOARD, edx=row, ebx=col, ecx=BOARD + 0x400, args=(BOARD + 0x401,))
        first, second = c.c_uint8(0xaa), c.c_uint8(0xbb)
        n.vertrix_choice_grid_cell_bytes(c.byref(grid), row, col, c.byref(first), c.byref(second))
        assert bytes([first.value, second.value]) == bytes(cpu.mem_read(BOARD + 0x400, 2)), case
        check(grid, 'cell_bytes')
    report = {'status':
        'passed', 'complete_original_executions' : totals,
                                                   'scope'
            : 'Complete 429d50, 429fe0, 429df0, 429e80, 429ee0, 42a080, 42a140, 42a170, 42a190 and ' '42a1b0 execute in the original (4826c0 draws are stubbed and replayed); the ' 'grid, every pool object, outputs, results and draw counts compare.'
        }
        (args.build_dir / 'choice-grid-verification.json')
                .write_text(json.dumps(report, indent = 2) + '\n')
                    print(json.dumps(report, indent = 2))

                        if __name__ == '__main__' : main()
