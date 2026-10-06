"""Compare all four original sprite animation playback routines."""
import argparse
import ctypes
import json
import random
import subprocess
from pathlib import Path
from original import Original
from verify_timer import Timer

class Animation(ctypes.Structure):
    _fields_ = [("timer", Timer), ("frame", ctypes.c_uint32), ("frame_count", ctypes.c_uint32)]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / "animation.dylib"
    subprocess.run(["rtk", "proxy", "cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror",
                    str(root / "source/animation.c"), str(root / "source/timer.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_animation_tick.argtypes = [ctypes.POINTER(Animation), ctypes.c_uint32, ctypes.c_int]
    oracle = Original(args.executable)
    rng = random.Random(0x4AC1F0)
    comparisons = 0
    edges = [0, 1, 2, 24, 100, 65535, 0x7FFFFFFF, 0xFFFFFFFF]
    cases = [(counter, period, elapsed) for counter in edges for period in edges for elapsed in edges]
    cases += [(rng.randrange(10000), rng.randrange(1, 1000), rng.randrange(10000)) for _ in range(3000)]
    for counter, period, elapsed in cases:
        total = (counter + elapsed) & 0xFFFFFFFF
        steps = total // (period or 1) if total >= period else 0
        for count in [1, 2, 17, 0xFFFFFFFF]:
            for frame in [0, count - 1]:
                for mode in range(4):
                    distance = count - 1 - frame if mode == 1 else frame
                    if steps > 500 and (mode in [0, 3] or distance > 100):
                        continue
                    animation = Animation(Timer(counter, period), frame, count)
                    result = native.vertrix_animation_tick(ctypes.byref(animation), elapsed, mode)
                    expected = oracle.animation(counter, period, frame, count, elapsed, mode)
                    assert (animation.timer.counter, animation.frame, result) == expected, (counter, period, elapsed, count, frame, mode)
                    assert animation.timer.period == period and animation.frame_count == count
                    comparisons += 1
    sequential = 0
    for _ in range(500):
        animation = Animation(Timer(0, rng.randrange(1, 1000)), 0, rng.randrange(1, 50))
        for _ in range(40):
            elapsed, mode = rng.randrange(1000), rng.randrange(4)
            expected = oracle.animation(animation.timer.counter, animation.timer.period, animation.frame,
                                        animation.frame_count, elapsed, mode)
            result = native.vertrix_animation_tick(ctypes.byref(animation), elapsed, mode)
            assert (animation.timer.counter, animation.frame, result) == expected
            sequential += 1
    for animation, mode in [(Animation(Timer(7, 8), 0, 0), 0),
                            (Animation(Timer(7, 8), 1, 1), 0),
                            (Animation(Timer(7, 8), 0, 1), 4)]:
        saved = bytes(animation)
        assert native.vertrix_animation_tick(ctypes.byref(animation), 100, mode) == -1
        assert bytes(animation) == saved
    report = {"status": "passed", "animation_comparisons": comparisons,
              "sequential_animation_comparisons": sequential,
              "scope": "Original four playback routines and timer/frame helpers execute unchanged; resource decoding, drawing and full-game scheduling remain separate"}
    (args.build_dir / "animation-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))

if __name__ == "__main__":
    main()
