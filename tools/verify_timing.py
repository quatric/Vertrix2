"""Compare recovered parameter draws with all three original player routines."""

import argparse
import ctypes
import json
import subprocess
from pathlib import Path

from original import Original
from verify_random import NativeRandom


class Delay(ctypes.Structure):
    _fields_ = [("minimum", ctypes.c_uint16), ("width", ctypes.c_uint16)]


class Motion(ctypes.Structure):
    _fields_ = [("period", ctypes.c_uint32), ("counter", ctypes.c_uint32),
                ("step", ctypes.c_uint16), ("state", ctypes.c_uint32)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", required=True, type=Path)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    args.build_dir.mkdir(parents=True, exist_ok=True)
    library = args.build_dir.resolve() / "recovered-timing.dylib"
    subprocess.run([
        "rtk", "proxy", "cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror",
        str(root / "source/random.c"), str(root / "source/timing.c"), "-o", str(library),
    ], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_delay.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_uint32, ctypes.c_int]
    native.vertrix_delay.restype = Delay
    native.vertrix_random_seed.argtypes = [ctypes.POINTER(NativeRandom), ctypes.c_uint32]
    native.vertrix_random_range.argtypes = [ctypes.POINTER(NativeRandom), ctypes.c_uint16,
                                          ctypes.c_uint16]
    native.vertrix_random_range.restype = ctypes.c_uint32
    oracle = Original(args.executable)
    native.vertrix_motion_level.argtypes = [ctypes.POINTER(Motion), ctypes.c_int, ctypes.c_int]
    native.vertrix_motion_fast.argtypes = [ctypes.POINTER(Motion), ctypes.c_int]
    cases = 0
    for seed in (0x12345678, 0xFFFFFFFF):
        state = NativeRandom()
        native.vertrix_random_seed(ctypes.byref(state), seed)
        oracle.timing_seed(seed)
        for cycle in range(3):
            for difficulty in range(3):
                for character in range(19):
                    for level in range(10):
                        for parameter in range(3):
                            delay = native.vertrix_delay(character, difficulty, level, parameter)
                            actual = native.vertrix_random_range(ctypes.byref(state), delay.minimum,
                                                                 delay.width)
                            expected, position = oracle.timing(character, difficulty, level, parameter)
                            if (actual, state.position) != (expected, position):
                                raise AssertionError(f"Timing differs: {seed:#x}, {cycle}, "
                                                     f"{difficulty}, {character}, {level}, {parameter}")
                            cases += 1
    for character in range(19):
        for slot in range(28):
            if native.vertrix_character_power(character, slot) != oracle.power(character, slot):
                raise AssertionError(f"Native character power differs: {character}, {slot}")
    motion_cases = 0
    for difficulty in range(3):
        for level in range(10):
            for state_value in (0, 1, 2, 0xFFFFFFFF):
                for initial in (0, 1, 0xFFFFFFFF):
                    motion = Motion(initial, initial, initial & 0xFFFF, state_value)
                    expected = oracle.motion_level(difficulty, level, motion.period,
                                                    motion.counter, motion.step, motion.state)
                    native.vertrix_motion_level(ctypes.byref(motion), difficulty, level)
                    if (motion.period, motion.counter, motion.step) != expected:
                        raise AssertionError(f"Motion update differs: {difficulty}, {level}, {state_value}")
                    motion_cases += 1
                    motion = Motion(initial, initial, initial & 0xFFFF, state_value)
                    expected = oracle.motion_level(difficulty, level, motion.period,
                                                    motion.counter, motion.step, motion.state, fast=True)
                    native.vertrix_motion_fast(ctypes.byref(motion), difficulty)
                    if (motion.period, motion.counter, motion.step, motion.state) != expected:
                        raise AssertionError(f"Fast descent differs: {difficulty}, {state_value}")
    report = {
        "status": "passed", "parameter_draw_and_position_comparisons": cases,
        "native_character_power_entries": 532,
        "active_piece_motion_updates": motion_cases,
        "fast_descent_updates": motion_cases,
        "scope": "Player +0x458/+0x45c/+0x460 draw routines; game-loop scheduling remains unverified",
    }
    (args.build_dir / "timing-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
