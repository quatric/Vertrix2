"""Compare original three-block generation and RNG consumption to native C."""

import argparse
import ctypes
import json
import random
import subprocess
from pathlib import Path

from original import Original
from verify_random import NativeRandom


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", required=True, type=Path)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / "recovered-piece.dylib"
    subprocess.run([
        "cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror",
        str(root / "source/random.c"), str(root / "source/piece.c"), "-o", str(library),
    ], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_random_seed.argtypes = [ctypes.POINTER(NativeRandom), ctypes.c_uint32]
    native.vertrix_piece.argtypes = [ctypes.POINTER(NativeRandom), ctypes.c_uint32,
                                     ctypes.POINTER(ctypes.c_uint8)]
    native.vertrix_piece_cycle.argtypes = [ctypes.POINTER(ctypes.c_uint8)]
    native.vertrix_piece_bottom_color.argtypes = [ctypes.POINTER(NativeRandom), ctypes.POINTER(ctypes.c_uint8)]
    oracle = Original(args.executable)
    chooser = random.Random(0x43D180)
    comparisons = 0
    seeds = [0, 1, 0x12345678, 0xFFFFFFFF]
    for seed in seeds:
        state = NativeRandom()
        native.vertrix_random_seed(ctypes.byref(state), seed)
        oracle.piece_seed(seed)
#Continuous sequences include mode transitions and buffer wrap.
        modes = list(range(93)) + [0xFFFFFFFF]
        modes += [chooser.choice([0, 0x22, 0x28, 0x29, 0x2A, 0x2D, 0x2E])
                  for _ in range(10000)]
        for index, mode in enumerate(modes):
            blocks = (ctypes.c_uint8 * 3)()
            native.vertrix_piece(ctypes.byref(state), mode, blocks)
            expected, position = oracle.piece(mode)
            if (list(blocks), state.position) != (expected, position):
                raise AssertionError(f"Piece difference: seed={seed:#x}, mode={mode:#x}, "
                                     f"index={index}, actual={list(blocks)}, expected={expected}")
            comparisons += 1
    operations = 0
    state = NativeRandom()
    native.vertrix_random_seed(ctypes.byref(state), 0x12345678)
    oracle.piece_seed(0x12345678)
    for i in range(20000):
        values = [chooser.randrange(7) for _ in range(3)]
        blocks = (ctypes.c_uint8 * 3)(*values)
        cycle = i % 2 == 0
        if cycle:
            native.vertrix_piece_cycle(blocks)
        else:
            native.vertrix_piece_bottom_color(ctypes.byref(state), blocks)
        expected, position = oracle.piece_operation(values, cycle)
        if (list(blocks), state.position) != (expected, position):
            raise AssertionError(f"Piece operation differs: {i}, {values}, cycle={cycle}")
        operations += 1
    report = {
        "status": "passed", "piece_and_rng_position_comparisons": comparisons,
        "seeds": seeds, "original_addresses": ["0x0043d130", "0x0043d180"],
        "piece_operation_and_rng_comparisons": operations,
        "scope": "Block types and RNG consumption; spawn/render/collision still unrecovered",
    }
    (args.build_dir / "piece-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
