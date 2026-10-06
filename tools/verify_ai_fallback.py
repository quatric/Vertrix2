"""Compare the original computer-player fallback 0x426240 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, BOARD, COUNTER
from oracle_kit import build, Stubs

CELLS = 65
BOARD_OFFSET = 0x184
OBJECT_SIZE = 0x200
KIND_OUT = COUNTER
COLUMN_OUT = COUNTER + 4
U = c.c_uint32


DRAW = c.CFUNCTYPE(c.c_uint16, c.c_void_p, c.c_uint16)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'ai-fallback', ['ai_player.c', 'ai_features.c', 'match.c', 'board.c'])
    cells_type = c.c_uint8 * CELLS
    n.vertrix_ai_fallback.argtypes = [cells_type, U, U, U, U, U, U, c.POINTER(U), DRAW,
                                      c.c_void_p, c.POINTER(U), c.POINTER(U)]
    n.vertrix_ai_fallback.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x426240)
    draws = []

    def handler(address, eax, edx, ebx, ecx, stack):
        draws.append((edx & 0xffff, rng.randrange(edx & 0xffff)))
        return draws[-1][1]

    stubs = Stubs(cpu, handler)
    stubs.add(0x4826c0)
    replay = []

    @DRAW
    def draw(context, divisor):
        expected, value = replay.pop(0)
        assert expected == divisor, (expected, divisor)
        return value

    totals = {'valid': 0, 'invalid': 0, 'draws': 0, 'kinds': [0, 0, 0]}
    for case in range(args.cases):
        palette = rng.choice([[0, 1, 2, 3, 4, 255, 255, 255], [0, 0, 1, 255, 255, 255, 255],
                              [0, 1, 255, 255, 255, 255, 255, 255, 255, 255]])
        board = [rng.choice(palette) for _ in range(CELLS)]
        if case % 2 == 0:
            for x in range(5):
                column = [v for v in board[x * 13:x * 13 + 13] if v != 255]
                board[x * 13:x * 13 + 13] = [255] * (13 - len(column)) + column
        colours = [rng.randrange(5) for _ in range(3)]
        if rng.random() < 0.3:
            colours[1] = colours[0]
        a, b, cc = colours
        start = rng.randrange(0, 6)
        row = rng.randrange(0, 13)
        level = rng.choice([0, 1, 2, 3, 3, 4, 4, 5, 7])
        previous = rng.choice([0, 1, 2, 3, 4, 0xffffffff, 7])
        cpu.mem_write(BOARD, bytes(OBJECT_SIZE))
        cpu.mem_write(BOARD + BOARD_OFFSET, bytes(board))
        cpu.mem_write(BOARD + 0x180, struct.pack('<I', previous))
        cpu.mem_write(KIND_OUT, struct.pack('<II', 0xdead, 0xbeef))
        del draws[:]
        original.call(0x426240, eax=BOARD, edx=b, ebx=cc, ecx=a,
                      args=(KIND_OUT, COLUMN_OUT, 0, start, row, level))
        kind_out, column_out = struct.unpack('<II', cpu.mem_read(KIND_OUT, 8))
        previous_out = struct.unpack('<I', cpu.mem_read(BOARD + 0x180, 4))[0]
        replay[:] = list(draws)
        column, rotation, prev = U(0xbeef), U(0xdead), U(previous)
        result = n.vertrix_ai_fallback(cells_type(*board), b, cc, a, start, row, level,
                                       c.byref(prev), draw, None, c.byref(column),
                                       c.byref(rotation))
        assert result == 1 and not replay, (case, result, replay)
        assert (kind_out, column_out, previous_out) == (rotation.value, column.value,
                                                       prev.value), (
            case, (kind_out, column_out, previous_out),
            (rotation.value, column.value, prev.value), board, a, b, cc, start, row, level,
            previous)
        totals['valid'] += 1
        totals['draws'] += len(draws)
        if rotation.value < 3:
            totals['kinds'][rotation.value] += 1
    report = {'status': 'passed', 'complete_original_executions': {'0x426240': args.cases},
              'cases': totals,
              'scope': 'The complete fallback runs in the original (only the 0x4826c0 draws are '
                       'stubbed and replayed in order, with their divisors checked) over random '
                       'boards, pieces, starts, rows, levels and remembered columns; both output '
                       'words and the remembered column compare with the native version.'}
    (args.build_dir / 'ai-fallback-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
