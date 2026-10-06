"""Verify difficulty-dependent score updates against original x86 instructions."""

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
    library = args.build_dir.resolve() / "score.dylib"
    subprocess.run(["cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra",
                    "-Werror", str(root / "source/score.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_score_add.argtypes = [ctypes.c_uint32] * 3
    native.vertrix_score_add.restype = ctypes.c_uint32
    oracle = Original(args.executable)
    chooser = random.Random(0x43BA90)
    edges = [0, 1, 99999998, 99999999, 100000000, 0x7FFFFFFF, 0xFFFFFFFF]
    cases = [(score, reward) for score in edges for reward in edges]
    cases += [(chooser.randrange(100000000), chooser.randrange(1000)) for _ in range(5000)]
    cases += [(chooser.randrange(2**32), chooser.randrange(2**32)) for _ in range(5000)]
    for score, reward in cases:
        for difficulty in range(3):
            actual = native.vertrix_score_add(score, reward, difficulty)
            expected = oracle.score_add(score, reward, difficulty)
            if actual != expected:
                raise AssertionError(f"Score difference: {(score, reward, difficulty)}")
    report = {"status": "passed", "score_comparisons": len(cases) * 3,
              "original_address": "0x0043ba90",
              "scope": "Score arithmetic and cap only; level/bonus/state transitions separate"}
    (args.build_dir / "score-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
