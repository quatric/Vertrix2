"""Verify original pixel-to-board conversion, including signed edge cases."""

import argparse
import ctypes
import itertools
import json
import random
import subprocess
from pathlib import Path

from original import Original


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", required=True, type=Path)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / "recovered-coordinates.dylib"
    subprocess.run([
        "rtk", "proxy", "cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror",
        str(root / "source/board.c"), str(root / "source/collision.c"), "-o", str(library),
    ], check=True)
    native = ctypes.CDLL(str(library))
    native.board_pixel_cell.argtypes = [ctypes.c_int16] * 4 + [ctypes.POINTER(ctypes.c_int32)] * 2
    native.vertrix_side_contact.argtypes = [ctypes.POINTER(ctypes.c_uint8)] * 2 + [ctypes.c_int16] * 4 + [ctypes.c_int]
    native.vertrix_side_shift_contact.argtypes = [ctypes.POINTER(ctypes.c_uint8), ctypes.c_uint32] + [ctypes.c_int16] * 4 + [ctypes.c_int]
    native.vertrix_down_clear.argtypes = [ctypes.POINTER(ctypes.c_uint8)] + [ctypes.c_int16] * 4
    oracle = Original(args.executable)
    shift_oracle = Original(args.executable)
    edges = [-32768, -25, -24, -23, -1, 0, 1, 23, 24, 25, 32767]
    cases = list(itertools.product(edges, repeat=4))
    chooser = random.Random(0x431AE0)
    cases += [tuple(chooser.randrange(-32768, 32768) for _ in range(4))
              for _ in range(10000)]
    for values in cases:
        column, row = ctypes.c_int32(), ctypes.c_int32()
        native.board_pixel_cell(*values, ctypes.byref(column), ctypes.byref(row))
        expected = oracle.pixel_cell(*values)
        if (column.value, row.value) != expected:
            raise AssertionError(f"Coordinate difference: {values}")
    contacts = 0
    shift_contacts = 0
    for i in range(10000):
        board = [chooser.choice([255, 255, 255, 0, 1, 5, 6]) for _ in range(65)]
        mask = [chooser.choice([0, 0, 1, 2, 7, 255]) for _ in range(13)]
        origin_x, origin_y = chooser.randrange(-1000, 1000), chooser.randrange(-1000, 1000)
#Cover aligned and sub - cell positions, all walls and above - board rows.
        piece_x = origin_x + chooser.randrange(5) * 24 + chooser.randrange(24)
        piece_y = origin_y + chooser.randrange(-5 * 24, 10 * 24)
        native_board = (ctypes.c_uint8 * 65)(*board)
        native_mask = (ctypes.c_uint8 * 13)(*mask)
        for right in (0, 1):
            actual = native.vertrix_side_contact(native_board, native_mask, origin_x, origin_y,
                                                  piece_x, piece_y, right)
            expected = oracle.side_contact(board, mask, origin_x, origin_y, piece_x, piece_y, right)
            if actual != expected:
                raise AssertionError(f"Side contact difference: case={i}, right={right}")
            contacts += 1
            for pattern in range(3):
                actual = native.vertrix_side_shift_contact(native_board, pattern, origin_x,
                                                           origin_y, piece_x, piece_y, right)
                expected = shift_oracle.side_contact(board, None, origin_x, origin_y,
                                                      piece_x, piece_y, right, pattern)
                if actual != expected:
                    raise AssertionError(f"Original mask difference: case={i}, pattern={pattern}")
                shift_contacts += 1
    down_comparisons = 0
    for case in range(20000):
        board = [chooser.choice([255, 255, 0, 1, 5, 6]) for _ in range(65)]
        origin_x = chooser.randrange(-1000, 1000)
        origin_y = chooser.randrange(100, 1000)
        piece_x = origin_x + chooser.randrange(5) * 24 + chooser.randrange(24)
        piece_y = origin_y + chooser.randrange(-120, 350)
        if case < 1000:
        piece_y =
            origin_y - 72 + (case % 25) - 12 native_board = (ctypes.c_uint8 * 65)(*board)actual =
                native.vertrix_down_clear(native_board, origin_x, origin_y, piece_x, piece_y)
                    expected =
                    oracle.down_clear(board, origin_x, origin_y, piece_x, piece_y) if actual !=
                    expected : raise AssertionError(f "Downward probe difference: case={case}")
                                   down_comparisons +=
            1 report = {
                "status" : "passed",
                "coordinate_comparisons" : len(cases),
                "downward_probe_comparisons" : down_comparisons,
                "side_contact_comparisons" : contacts,
                "original_shift_mask_comparisons" : shift_contacts,
                "original_address" : "0x00431ae0",
                "scope" : "Coordinate conversion, supplied-mask contacts and original first-step "
                          "shift patterns 0..2; full movement remains incomplete"
            }(args.build_dir / "coordinate-verification.json")
                           .write_text(json.dumps(report, indent = 2) + "\n")
                               print(json.dumps(report, indent = 2))

                                   if __name__ == "__main__" : main()
