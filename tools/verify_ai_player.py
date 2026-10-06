"""Compare the original computer-player figure search 0x4270a0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, BOARD, COUNTER
from oracle_kit import build

CELLS = 65
BOARD_OFFSET = 0x184
OBJECT_SIZE = 0x200
KIND_OUT = COUNTER
COLUMN_OUT = COUNTER + 4
U = c.c_uint32


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'ai-player', ['ai_player.c', 'ai_features.c', 'match.c', 'board.c'])
    cells_type = c.c_uint8 * CELLS
    n.vertrix_ai_search_native.argtypes = [cells_type, U, U, U, U, U, U, c.POINTER(U),
                                           c.POINTER(U)]
    n.vertrix_ai_search_native.restype = c.c_int
    original = Original(args.executable)
    rng = random.Random(0x4270a0)
    totals = {'found': 0, 'none': 0, 'level': 0}
    for case in range(args.cases):
        palette = rng.choice([[0, 1, 2, 3, 4, 255, 255], [0, 0, 1, 255, 255, 255, 255],
                              [0, 1, 2, 5, 6, 255, 255, 255], [0, 1, 255, 255, 255, 255, 255, 255]])
        board = [rng.choice(palette) for _ in range(CELLS)]
        if case % 2 == 0:
            for x in range(5):
                column = [v for v in board[x * 13:x * 13 + 13] if v != 255]
                board[x * 13:x * 13 + 13] = [255] * (13 - len(column)) + column
        colours = [rng.randrange(5) for _ in range(3)]
        if rng.random() < 0.4:
            colours = [colours[0]] * 3
        a, b, cc = colours
        start = rng.randrange(0, 6)
        row = rng.randrange(0, 13)
        level = rng.choice([0, 1, 2, 3, 3, 4, 5, 7, 9])
        pressure = rng.randrange(256)
        original.cpu.mem_write(BOARD, bytes(OBJECT_SIZE))
        original.cpu.mem_write(BOARD + BOARD_OFFSET, bytes(board))
        original.cpu.mem_write(KIND_OUT, struct.pack('<II', 0xdead, 0xbeef))
        eax = original.call(0x4270a0, eax=BOARD, edx=b, ebx=cc, ecx=a,
                            args=(KIND_OUT, COLUMN_OUT, pressure, start, row, level)) & 0xff
        kind_out, column_out = struct.unpack('<II', original.cpu.mem_read(KIND_OUT, 8))
        column, rotation = U(0xbeef), U(0xdead)
        result = n.vertrix_ai_search_native(cells_type(*board), a, b, cc, start, row, level,
                                            c.byref(column), c.byref(rotation))
        if level <= 2:
            totals['level'] += 1
        elif result:
            totals['found'] += 1
        else:
            totals['none'] += 1
        assert result == eax, (case, result, eax, board, a, b, cc, start, row, level)
        assert (kind_out, column_out) == (rotation.value, column.value), (
            case, (kind_out, column_out), (rotation.value, column.value))
    assert totals['found'] > 200, totals
    report = {'status': 'passed', 'complete_original_executions': {'0x4270a0': args.cases},
              'cases': totals,
              'scope': 'The complete search runs in the original with its figure pass, row reach '
                       'and every callee executing for real over random boards, pieces, starts, '
                       'rows and levels (start 0..5 and row 0..12, the inputs the game produces); the answer and both output words compare with the '
                       'native search.'}
    (args.build_dir / 'ai-player-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
