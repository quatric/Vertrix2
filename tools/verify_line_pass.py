"""Compare the original line pass 0x4346b0 with the native vertrix_line_pass."""
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
    parser.add_argument('--cases', type=int, default=8000)
    args = parser.parse_args()
    n = build(args.build_dir, 'line-pass', ['match.c'])
    cells = c.c_uint8 * CELLS
    n.vertrix_line_pass.argtypes = [cells, cells, c.c_int, c.POINTER(c.c_int)]
    n.vertrix_line_pass.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4346b0)
    found_cases = 0
    for case in range(args.cases):
        palette = rng.choice([[0, 1, 2, 3, 255, 255], [0, 0, 1, 255], [0, 255], [0, 1, 5, 6, 255],
                                [0, 1, 7, 255]])
        board = [rng.choice(palette) for _ in range(CELLS)]
        if case % 2:
            for x in range(5):
                column = [v for v in board[x * 13:x * 13 + 13] if v != 255]
                board[x * 13:x * 13 + 13] = [255] * (13 - len(column)) + column
        threshold = rng.choice([0, 1, 2, 2, 3, 255])
        start_mask = [rng.choice([0, 0, 1]) for _ in range(CELLS)]
        base = rng.choice([0, 0, 0, 75, rng.getrandbits(16)])
        cpu.mem_write(BOARD, bytes(board))
        cpu.mem_write(MASK, struct.pack('<65I', *start_mask))
        cpu.mem_write(COUNTER, struct.pack('<I', base))
        eax = original.call(0x4346b0, eax=BOARD, edx=MASK, ebx=threshold, ecx=COUNTER, args=()) & 0xff
        mask = list(struct.unpack('<65I', cpu.mem_read(MASK, 260)))
        reward = struct.unpack('<I', cpu.mem_read(COUNTER, 4))[0]
        native_mask = cells(*start_mask)
        native_reward = c.c_int(base)
        found = n.vertrix_line_pass(cells(*board), native_mask, threshold, c.byref(native_reward))
        assert found == eax, (case, found, eax)
        assert list(native_mask) == mask, (case, board, threshold)
        assert native_reward.value == reward, (case, native_reward.value, reward)
        if found:
            found_cases += 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4346b0': args.cases},
              'cases_with_runs': found_cases,
              'scope': 'The complete line pass runs in the original over random boards '
                       '(including kind 7), thresholds (including 0 and 255), nonzero reward '
                       'bases and pre-marked masks; the answer, the mask and the reward '
                       'compare with vertrix_line_pass.'}
    (args.build_dir / 'line-pass-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
