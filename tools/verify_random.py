"""Verify original seeded RNG generation, range behavior, and buffer wrap."""

import argparse
import ctypes
import json
import random
import subprocess
from pathlib import Path

from original import Original

Clock = ctypes.CFUNCTYPE(ctypes.c_uint32, ctypes.c_void_p)

class NativeRandom(ctypes.Structure):
    _fields_ = [
        ("samples", ctypes.c_uint16 * 4097),
        ("position", ctypes.c_uint16),
        ("seed", ctypes.c_uint32),
        ("clock", ctypes.c_void_p),
        ("clock_context", ctypes.c_void_p),
    ]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", required=True, type=Path)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    args.build_dir.mkdir(parents=True, exist_ok=True)
    library = args.build_dir.resolve() / "recovered-random.dylib"
    subprocess.run([
        "rtk", "proxy", "cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror",
        str(root / "source/random.c"), "-o", str(library),
    ], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_random_seed.argtypes = [ctypes.POINTER(NativeRandom), ctypes.c_uint32]
    native.vertrix_random_range.argtypes = [ctypes.POINTER(NativeRandom), ctypes.c_uint16,
                                          ctypes.c_uint16]
    native.vertrix_random_range.restype = ctypes.c_uint32
    native.vertrix_random_clock.argtypes = [ctypes.POINTER(NativeRandom), Clock,
                                          ctypes.c_void_p]
    oracle = Original(args.executable)
    chooser = random.Random(42097)
    seeds = [0, 1, 12345, 0x12345678, 0x80000000, 0xFFFFFFFF]
    draws = 0
    for seed in seeds:
        state = NativeRandom()
        native.vertrix_random_seed(ctypes.byref(state), seed)
        expected = oracle.random_seed(seed)
        if list(state.samples) != expected:
            raise AssertionError(f"Original sample buffer differs for seed {seed:#x}")
        for index in range(10000):
            minimum = chooser.choice([0, 1, 65535, chooser.randrange(65536)])
            width = chooser.choice([0, 1, 2, 3, 5, 4097, 65535, chooser.randrange(65536)])
            actual = native.vertrix_random_range(ctypes.byref(state), minimum, width)
            expected, position = oracle.random_range(minimum, width)
            if (actual, state.position) != (expected, position):
                raise AssertionError(f"RNG difference: seed={seed:#x}, draw={index}, "
                                     f"range=({minimum},{width})")
            draws += 1
    clock_draws = 0
    clock_samples = 0
    for step in (0, 1, 0x7FFFFFFF):
        counts = [0, 0]

        def clock_value(side):
            value = (0xFFFFFFF0 + counts[side] * step) & 0xFFFFFFFF
            counts[side] += 1
            return value

        callback = Clock(lambda context: clock_value(0))
        state = NativeRandom()
        native.vertrix_random_clock(ctypes.byref(state), callback, None)
        clock_oracle = Original(args.executable)
        expected = clock_oracle.random_clock(lambda: clock_value(1))
        if list(state.samples) != expected or counts != [9, 9]:
            raise AssertionError(f"Clock initialization differs: step={step}, calls={counts}")
        clock_samples += 4097
        for index in range(13000):
            width = 0 if index % 17 == 0 else chooser.randrange(1, 65536)
            actual = native.vertrix_random_range(ctypes.byref(state), 65535, width)
            expected, position = clock_oracle.random_range(65535, width)
            if (actual, state.position) != (expected, position) or counts[0] != counts[1]:
                raise AssertionError(f"Clock range/refill differs: step={step}, draw={index}")
            if width and position == 0:
                if list(state.samples) != clock_oracle.random_samples():
                    raise AssertionError("Clock refill buffer differs")
                clock_samples += 4097
            clock_draws += 1
    report = {
        "status": "passed", "seeds": seeds, "sample_words": 4097 * len(seeds),
        "range_and_position_comparisons": draws,
        "clock_range_and_position_comparisons": clock_draws,
        "clock_sample_words": clock_samples,
        "scope": "Seeded repeating and clock-reseeded modes, including wrap/refill",
        "oracle_platform_seam": "Single-thread CRT storage and supplied time(); original rand unchanged",
    }
    (args.build_dir / "random-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
