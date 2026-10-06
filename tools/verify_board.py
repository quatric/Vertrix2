"""Differential tests against the supplied game's actual x86 instructions."""

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
    parser.add_argument("--build-dir", required=True, type=Path)
    parser.add_argument("--cases", type=int, default=1000)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    args.build_dir.mkdir(parents=True, exist_ok=True)
    library = args.build_dir.resolve() / "recovered-board.dylib"
    subprocess.run(
        [
            "rtk", "proxy", "cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror",
            str(root / "source/match.c"), str(root / "source/board.c"), "-o", str(library),
        ],
        check=True,
    )
    native = ctypes.CDLL(str(library))
    byte_board = ctypes.c_uint8 * 65
    oracle = Original(args.executable)
    rng = random.Random(1203)
    counts = {"alignment": 0, "falling": 0, "collapse": 0, "bomb_estimate": 0, "live_blast": 0}

    def check(kind, actual, expected, context):
        if actual != expected:
            raise AssertionError(f"{kind}: {context}\nNative: {actual}\nOriginal: {expected}")
        counts[kind] += 1

    for case in range(args.cases):
#Dense, sparse, and gravity - settled boards exercise different overlaps.
        colors = [0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 255, 255]
        board = [rng.choice(colors) for _ in range(65)]
        if case % 3 == 0:
            for x in range(5):
                column = [color for color in board[x * 13 : x * 13 + 13] if color != 255]
                board[x * 13 : x * 13 + 13] = [255] * (13 - len(column)) + column
        for threshold in (2, 3):
            for figures in (0, 1):
                cells, mask = byte_board(*board), byte_board()
                reward = native.match_board(cells, mask, threshold, figures)
                check("alignment", (reward, list(mask)), oracle.matches(board, threshold, figures),
                      (case, threshold, figures, board))
        cells, mask = byte_board(*board), byte_board()
        moving = native.board_falling_mask(cells, mask)
        check("falling", (moving, list(mask)), oracle.falling(board), (case, board))
        native.board_collapse(cells)
        check("collapse", bytes(cells), oracle.collapse(board), (case, board))
        for pattern in range(1, 5):
            cells = byte_board(*board)
            stones, total = ctypes.c_int(), ctypes.c_int()
            native.board_bomb_estimate(cells, pattern, ctypes.byref(stones), ctypes.byref(total))
            check("bomb_estimate", (stones.value, total.value), oracle.estimate(board, pattern),
                  (case, pattern, board))
            for radius in (0, 1, 2, 3, 5, 13, 255):
                native.board_blast_mask(cells, mask, pattern, radius)
                check("live_blast", list(mask), oracle.blast(board, pattern, radius),
                      (case, pattern, radius, board))

    powers = json.loads((root / "docs/character-powers.json").read_text())
    for character in range(19):
        for slot in range(28):
            if powers[character][slot] != oracle.power(character, slot):
                raise AssertionError(f"Character power table differs at {character}, {slot}")
    report = {
        "status": "passed",
        "seed": 1203,
        "boards": args.cases,
        "comparisons": counts,
        "character_power_entries": 19 * 28,
        "original_speeds": oracle.speeds(),
        "scope": "Recovered board routines and tables only; not full-game fidelity",
    }
    destination = args.build_dir / "verification.json"
    destination.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
