"""Compare the original byte-board collapse 0x432980 with the native board_collapse."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original, BOARD, MASK, COUNTER
from oracle_kit import build

CELLS = 65


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=8000)
    args = parser.parse_args()
    n = build(args.build_dir, 'board-collapse-bytes', ['board.c'])
    cells = c.c_uint8 * CELLS
    n.board_collapse.argtypes = [cells]
    n.board_collapse.restype = None
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x432980)
    changed = 0
    for case in range(args.cases):
        palette = rng.choice([[0, 1, 2, 3, 255, 255], [0, 1, 255, 255, 255, 255], [0, 1, 5, 6, 255]])
        board = [rng.choice(palette) for _ in range(CELLS)]
        cpu.mem_write(BOARD, bytes(board))
        original.call(0x432980, eax=BOARD, edx=MASK, ebx=0, ecx=COUNTER, args=())
        expected = list(cpu.mem_read(BOARD, CELLS))
        native = cells(*board)
        n.board_collapse(native)
        assert list(native) == expected, (case, board, expected, list(native))
        changed += expected != board
    report = {'status': 'passed', 'complete_original_executions': {'0x432980': args.cases},
              'cases_that_changed': changed,
              'scope': 'The complete byte-board collapse runs in the original over random '
                       'boards; the resulting board compares with board_collapse.'}
    (args.build_dir / 'board-collapse-bytes-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
