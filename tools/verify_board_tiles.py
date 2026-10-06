"""Compare the original edge tile routine 0x433180 with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import build

OUTPUT, GRID, TABLES, SCRATCH = 0x803000, 0x807000, 0x4fb790, 0x5407f9
OUTPUT_SIZE = 0x1000


class Scratch(c.Structure):
    _fields_ = [('scratch', c.c_uint8 * 12)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'board-tiles', ['board_tiles.c', 'actor_storage.c'])
    n.vertrix_board_tile_cell.argtypes = [c.c_void_p, c.c_size_t, c.c_char_p, c.c_size_t,
                                          c.c_uint8, c.c_uint8, c.c_char_p, c.POINTER(Scratch)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x433180)
    totals = {}
    for case in range(args.cases):
        output = rng.randbytes(OUTPUT_SIZE)
        density = rng.choice([0.1, 0.5, 0.9])
        grid = bytes(rng.randrange(1, 8) if rng.random() < density else 0 for _ in range(65))
        # the tables of the original: eight bytes each; the lookups index them by 0..7
        tables = rng.randbytes(32)
        column, row = rng.randrange(0, 5), rng.randrange(0, 13)
        cpu.mem_write(OUTPUT, output)
        cpu.mem_write(GRID, grid)
        cpu.mem_write(TABLES, tables)
        cpu.mem_write(SCRATCH, rng.randbytes(12))
        original.call(0x433180, eax=OUTPUT, edx=column, ebx=row, ecx=GRID)
        native_output = c.create_string_buffer(output, OUTPUT_SIZE)
        scratch = Scratch()
        assert n.vertrix_board_tile_cell(native_output, OUTPUT_SIZE, grid, len(grid), column, row,
                                         tables, c.byref(scratch)), case
        assert native_output.raw == bytes(cpu.mem_read(OUTPUT, OUTPUT_SIZE)), (case, column, row)
        assert bytes(scratch.scratch) == bytes(cpu.mem_read(SCRATCH, 12)), (case, column, row)
        key = 'edge' if column in (0, 4) or row in (0, 12) else 'inner'
        totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 433180 executes in the original over random grids, tables and '
                       'cells; the output memory and the twelve scratch globals compare.'}
    (args.build_dir / 'board-tiles-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
