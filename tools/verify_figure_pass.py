"""Compare the original figure pass 0x434ee0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, BOARD, MASK, COUNTER
from oracle_kit import build

CELLS = 65


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'figure-pass', ['match.c', 'board.c'])
    cells_type = c.c_uint8 * CELLS
    n.vertrix_figure_pass.argtypes = [cells_type, cells_type, c.POINTER(c.c_int), c.c_int]
    n.vertrix_figure_pass.restype = c.c_int
    original = Original(args.executable)
    rng = random.Random(0x434ee0)
    found_cases = 0
    for case in range(args.cases):
        palette = rng.choice([[0, 1, 2, 3, 4, 5, 6, 255], [0, 0, 0, 1, 255], [0, 1, 255, 255, 255],
                                [0, 1, 7, 255]])
        board = [rng.choice(palette) for _ in range(CELLS)]
        if case % 3 == 0:
            for x in range(5):
                column = [v for v in board[x * 13:x * 13 + 13] if v != 255]
                board[x * 13:x * 13 + 13] = [255] * (13 - len(column)) + column
        for ebx, ecx in ((0, 1), (rng.randrange(256), 0)):
            original.cpu.mem_write(BOARD, bytes(board))
            original.cpu.mem_write(MASK, bytes(260))
            original.cpu.mem_write(COUNTER, bytes(4))
            eax = original.call(0x434EE0, ebx=ebx, ecx=ecx, args=(COUNTER,)) & 0xffffffff
            word = struct.unpack('<H', original.cpu.mem_read(COUNTER, 2))[0]
            cells, mask, reward = cells_type(*board), cells_type(), c.c_int()
            found = n.vertrix_figure_pass(cells, mask, c.byref(reward), ecx)
            assert eax == found, (case, eax, found, board)
            assert word == reward.value & 0xffff, (case, word, reward.value, board)
            assert list(original.cpu.mem_read(BOARD, CELLS)) == list(cells), (case, board)
            if ecx == 1 or not found:
                assert original.read_mask() == [int(v) for v in mask], (case, board)
            if ecx == 1:
                found_cases += found
    report = {'status': 'passed', 'complete_original_executions': {'0x434ee0': args.cases * 2},
              'boards_with_figures': found_cases,
              'scope': 'The complete figure pass runs in the original on random boards (with ecx 1 '
                       'and with ecx 0 and a random ebx, including kind 7); eax, the reward word, '
                       'the mask (written when ecx is 1) and the branded board compare with the '
                       'native pass.'}
    (args.build_dir / 'figure-pass-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
