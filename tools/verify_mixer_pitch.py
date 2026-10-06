"""Compare original music pitch conversion and its embedded lookup table."""
import argparse
import ctypes
import json
import random
import struct
import subprocess
from pathlib import Path

from original import Original


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / "source"
    library = build / "pitch.dylib"
    subprocess.run(
        [
            "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
            str(source / "mixer.c"), "-o", str(library)
        ],
        check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_pitch.argtypes = [ctypes.c_int32, ctypes.c_int]
    native.vertrix_mixer_pitch.restype = ctypes.c_uint32
    original = Original(args.executable)
    rng = random.Random(0x40ce20)
    periods=list(range(-32,24577))+[-2147483648,2147483647]
    periods += [rng.randrange(-2147483648,2147483648) for _ in range(20000)]
    for linear in (0,1):
        original.cpu.mem_write(0x531B46,bytes([linear]))
        for period in periods:
            expected=original.call(0x40CE20,eax=period & 0xffffffff)
            assert native.vertrix_mixer_pitch(period,linear)==expected,(period,linear)
    report = {
        "status": "passed",
        "pitch_cases": len(periods) * 2,
        "scope": "Complete original 0x40ce20 in reciprocal and linear modes, exhaustive periods -32..24576 covering all 768 table entries and shift-count wrap at octave 32, signed extrema and 20000 random full-width periods per mode. Excludes note-to-period generation, sequencer effects and output playback."
    }
    (build / "mixer-pitch-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
