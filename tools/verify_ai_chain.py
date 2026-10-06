"""Compare the original computer-player chain search 0x4269e0 with the native recovery."""
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
    parser.add_argument('--cases', type=int, default=3000)
    args = parser.parse_args()
    n = build(args.build_dir, 'ai-chain', ['ai_player.c', 'ai_features.c', 'match.c', 'board.c'])
    cells_type = c.c_uint8 * CELLS
    n.vertrix_ai_chain_search.argtypes = [cells_type, U, U, U, U, U, U, U, c.POINTER(U),
                                          c.POINTER(U)]
    n.vertrix_ai_chain_search.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4269e0)
    totals = {'found': 0, 'none': 0, 'levels': {}}
    for case in range(args.cases):
        palette = rng.choice([[0, 1, 2, 255, 255, 255], [0, 0, 1, 255, 255], [0, 1, 255, 255, 255],
                              [0, 1, 2, 3, 4, 255]])
        board = [rng.choice(palette) for _ in range(CELLS)]
        for x in range(5):
            column = [v for v in board[x * 13:x * 13 + 13] if v != 255]
            if case % 3:
                column = column[-rng.randrange(0, 11):] if rng.random() < 0.7 else column
            board[x * 13:x * 13 + 13] = [255] * (13 - len(column)) + column
        a, b, cc = [rng.randrange(3) for _ in range(3)]
        threshold = rng.choice([2, 2, 2, 3, 1])
        start = rng.randrange(0, 6)
        row = rng.randrange(0, 13)
        level = rng.choice([0, 1, 2, 3, 3, 4, 4, 5])
        cpu.mem_write(BOARD, bytes(OBJECT_SIZE))
        cpu.mem_write(BOARD + BOARD_OFFSET, bytes(board))
        cpu.mem_write(KIND_OUT, struct.pack('<II', 0xdead, 0xbeef))
        eax = original.call(0x4269e0, eax=BOARD, edx=b, ebx=cc, ecx=a,
                            args=(KIND_OUT, COLUMN_OUT, threshold, start, row, level)) & 0xff
        kind_out, column_out = struct.unpack('<II', cpu.mem_read(KIND_OUT, 8))
        column, rotation = U(0xbeef), U(0xdead)
        result = n.vertrix_ai_chain_search(cells_type(*board), b, cc, a, threshold, start, row,
                                           level, c.byref(column), c.byref(rotation))
        assert result == eax, (case, result, eax, board, a, b, cc, threshold, start, row, level)
        assert (kind_out, column_out) == (rotation.value, column.value), (
            case, (kind_out, column_out), (rotation.value, column.value), board, a, b, cc,
            threshold, start, row, level)
        totals['found' if result else 'none'] += 1
        totals['levels'][level] = totals['levels'].get(level, 0) + result
    assert totals['found'] > 300, totals
    report = {'status': 'passed', 'complete_original_executions': {'0x4269e0': args.cases},
              'cases': totals,
              'scope': 'The complete chain search runs in the original with its line pass, '
                       'collapse and row reach executing for real over random boards, pieces, '
                       'thresholds, starts, rows and levels; the answer and both output words '
                       'compare with the native search.'}
    (args.build_dir / 'ai-chain-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
