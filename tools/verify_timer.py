"""Compare both original timer families with native accumulator arithmetic."""

import argparse
import ctypes
import json
import random
import subprocess
from pathlib import Path

from original import Original


class Timer(ctypes.Structure):
    _fields_ = [("counter", ctypes.c_uint32), ("period", ctypes.c_uint32)]


class FrameClock(ctypes.Structure):
    _fields_ = [("previous", ctypes.c_uint32), ("current", ctypes.c_uint32),
                ("elapsed", ctypes.c_uint32)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / "timer.dylib"
    subprocess.run(["rtk", "proxy", "cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra",
                    "-Werror", str(root / "source/timer.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_timer_advance.argtypes = [ctypes.POINTER(Timer), ctypes.c_uint32]
    native.vertrix_timer_scaled.argtypes = [ctypes.POINTER(Timer), ctypes.c_uint32]
    native.vertrix_timer_scaled.restype = ctypes.c_uint32
    for name in ("due", "cycles", "consume"):
        function = getattr(native, "vertrix_timer_" + name)
        function.argtypes = [ctypes.POINTER(Timer)]
        function.restype = None if name == "consume" else ctypes.c_uint32
    oracle = Original(args.executable)
    native.vertrix_frame_sample.argtypes = [ctypes.POINTER(FrameClock), ctypes.c_uint32]
    chooser = random.Random(0x4AC500)
    edges = [0, 1, 2, 24, 1000, 0x7FFFFFFF, 0xFFFFFFFF]
    cases = [(a, b, c, d) for a in edges for b in edges for c in edges for d in edges]
    cases += [tuple(chooser.randrange(2**32) for _ in range(4)) for _ in range(10000)]
    for counter, period, elapsed, scale in cases:
        timer = Timer(counter, period)
        native.vertrix_timer_advance(ctypes.byref(timer), elapsed)
        actual = [timer.counter, native.vertrix_timer_due(ctypes.byref(timer)),
                  native.vertrix_timer_cycles(ctypes.byref(timer)),
                  native.vertrix_timer_scaled(ctypes.byref(timer), scale)]
        native.vertrix_timer_consume(ctypes.byref(timer))
        actual.append(timer.counter)
        for second in (False, True):
            expected = oracle.timer(counter, period, elapsed, scale, second)
            if tuple(actual) != expected:
                raise AssertionError(f"Timer difference: {(counter, period, elapsed, scale, second)}")
    clock_cases = [(previous, now) for previous in edges + [65534, 65535, 65536]
                   for now in edges + [65534, 65535, 65536]]
    clock_cases += [(chooser.randrange(2**32), chooser.randrange(2**32)) for _ in range(10000)]
    for previous, now in clock_cases:
        clock = FrameClock(previous, 0, 12345)
        expected = oracle.frame_sample(previous, clock.elapsed, now)
        native.vertrix_frame_sample(ctypes.byref(clock), now)
        if (clock.previous, clock.current, clock.elapsed) != expected:
            raise AssertionError(f"Frame clock differs: {(previous, now)}")
    report = {"status": "passed", "timer_sequence_comparisons": len(cases) * 2,
              "frame_clock_comparisons": len(clock_cases),
              "scope": "Both integer timers and supplied-clock elapsed calculation; platform clock integration and frame scheduling remain separate"}
    (args.build_dir / "timer-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
