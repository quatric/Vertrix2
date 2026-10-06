"""Verify original note-period conversion with original tuning table."""
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
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / "source"
    library = build / "notes.dylib"
    subprocess.run(
        [
            "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
            str(source / "mixer.c"), "-o", str(library)
        ],
        check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_note_period.argtypes = [
        ctypes.c_int32, ctypes.c_int32, ctypes.c_int32, ctypes.c_int
    ]
    native.vertrix_mixer_note_period.restype = ctypes.c_uint32
    original = Original(args.executable)
    rng = random.Random(0x40ce80)
    fixtures=[(note,0,tune) for note in range(0,122) for tune in range(-128,128)]
    fixtures += [(rng.randrange(-2147483648,2147483648),rng.randrange(-2147483648,2147483648),rng.randrange(-2147483648,2147483648)) for _ in range(20000)]
    fixtures += [(rng.randrange(1,97),rng.randrange(-96,97),rng.randrange(-128,128)) for _ in range(20000)]
    for linear in (0,1):
        original.cpu.mem_write(0x531B46,bytes([linear]))
        for note,relative,tune in fixtures:
            expected=original.call(0x40CE80,eax=note & 0xffffffff,edx=relative & 0xffffffff,ebx=tune & 0xffffffff)
            assert native.vertrix_mixer_note_period(note,relative,tune,linear)==expected,(note,relative,tune,linear)
    report = {
        "status": "passed",
        "note_cases": len(fixtures) * 2,
        "scope": "Complete original 0x40ce80 in both modes, exhaustive notes 0..121 with all signed-byte finetunes at zero relative note, 20000 random realistic relative-note fixtures and 20000 full-width register fixtures per mode. Covers original table, bounds and wrapping. Excludes instrument mapping and sequencer effects."
    }
    (build / "mixer-notes-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
