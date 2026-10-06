"""Verify original horizontal board transitions and evicted-block order."""

import argparse
import ctypes
import json
import random
import subprocess
from pathlib import Path

from original import Original


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / "shift.dylib"
    subprocess.run(["rtk", "proxy", "cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra",
                    "-Werror", str(root / "source/board.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.board_shift.argtypes = [ctypes.POINTER(ctypes.c_uint8)] * 3 + [ctypes.c_int]
    native.board_rise.argtypes = [ctypes.POINTER(ctypes.c_uint8)] * 3
    native.board_lock.argtypes = [ctypes.POINTER(ctypes.c_uint8), ctypes.c_int32,
                                  ctypes.c_int32, ctypes.POINTER(ctypes.c_uint8),
                                  ctypes.POINTER(ctypes.c_uint8)]
    oracle = Original(args.executable)
    chooser = random.Random(0x42F580)
    comparisons = 0
    for case in range(10000):
        board = [chooser.choice([255, 255, 0, 1, 2, 3, 4, 5, 6]) for _ in range(65)]
        incoming = [chooser.choice([255, 255, 0, 1, 5, 6]) for _ in range(13)]
        if case < 13:
            incoming = [5 if row == case else 255 for row in range(13)]
        elif case == 13:
            incoming = [255] * 13 elif case == 14:
            incoming = [6] * 13
        for right in (0, 1):
            actual = (ctypes.c_uint8 * 65)(*board)
            remaining = (ctypes.c_uint8 * 13)(*incoming)
            evicted = (ctypes.c_uint8 * 13)()
            native.board_shift(actual, remaining, evicted, right)
            expected, expected_remaining, destroyed = oracle.shift(board, incoming, right)
            if (list(actual), list(remaining), [value for value in evicted if value != 255]) != (
                    expected, expected_remaining, destroyed):
                raise AssertionError(f"Shift difference: case={case}, right={right}")
            comparisons += 1
        actual = (ctypes.c_uint8 * 65)(*board)
        rise_incoming = incoming[:5]
        if case < 5:
            rise_incoming = [6 if column == case else 255 for column in range(5)]
        remaining = (ctypes.c_uint8 * 5)(*rise_incoming)
        evicted = (ctypes.c_uint8 * 5)()
        native.board_rise(actual, remaining, evicted)
        expected, expected_remaining, destroyed = oracle.shift(board, rise_incoming, None)
        if (list(actual), list(remaining), [value for value in evicted if value != 255]) != (
                expected, expected_remaining, destroyed):
            raise AssertionError(f"Rising board difference: case={case}")
        column, top = case % 5, (case // 5) % 20 - 5
        blocks = [chooser.randrange(7) for _ in range(3)]
        actual = (ctypes.c_uint8 * 65)(*board)
        native_blocks = (ctypes.c_uint8 * 3)(*blocks)
        discarded = (ctypes.c_uint8 * 3)()
        result = native.board_lock(actual, column, top, native_blocks, discarded)
        expected_result, expected = oracle.lock(board, column, top, blocks)
        if (result, list(actual), list(discarded)) != (
                expected_result, expected, [int(not 0 <= top + i < 13) for i in range(3)]):
            raise AssertionError(f "Lock difference: case={case}")
                report = {
                    "status" : "passed",
                    "board_incoming_and_eviction_comparisons" : comparisons,
                    "lock_placement_comparisons" : 10000,
                    "rising_board_comparisons" : 10000,
                    "original_addresses" : [ "0x0042f580", "0x0042f620", "0x0042f310" ],
                    "scope" : "Board types, incoming consumption and destructor order; graphics "
                              "destructor effects remain separate"
                }(args.build_dir / "shift-verification.json")
                             .write_text(json.dumps(report, indent = 2) + "\n")
                                 print(json.dumps(report, indent = 2))

                                     if __name__
                         == "__main__" : main()
