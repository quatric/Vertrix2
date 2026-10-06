"""Execute original mixer boundary branches, preserving signed comparisons."""
import argparse
import ctypes
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original, BOARD

class Cursor(ctypes.Structure):
    _fields_ = [("position", ctypes.c_uint32), ("start", ctypes.c_uint32), ("end", ctypes.c_uint32), ("flags", ctypes.c_uint8)]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / "source"
    library = build / "mixer-boundary.dylib"
    subprocess.run(["cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC", str(source / "mixer.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_boundary.argtypes = [ctypes.POINTER(Cursor)]
    original = Original(args.executable)
    rng = random.Random(0x40c483)
    cases = 50000
    outcomes = [0, 0, 0]
    for index in range(cases):
        position, start, end = [rng.randrange(2**32) for _ in range(3)]
        flags = rng.randrange(256) & 254
        reverse = bool(flags & 16)
        boundary = start if reverse else end
        if index % 5 == 0:
            position = boundary
        outside = (position ^ 0x80000000) < (boundary ^ 0x80000000) if reverse else (position ^ 0x80000000) > (boundary ^ 0x80000000)
        outcome = 1 if not outside else (2 if flags & 12 else 0)
        stop = 0x40c518 if outcome == 1 else (0x40c477 if outcome == 2 else (0x40c4ce if reverse else 0x40c510))
        channel = bytearray(24)
        struct.pack_into("<I", channel, 4, position)
        struct.pack_into("<II", channel, 12, start, end)
        channel[22] = flags
        original.cpu.mem_write(BOARD, bytes(channel))
        original.call(0x40C483 if reverse else 0x40C4D6, ebx=BOARD, edx=flags, stop=stop)
        expected_position = struct.unpack("<I", original.cpu.mem_read(BOARD + 4, 4))[0]
        expected_flags = original.cpu.mem_read(BOARD + 22, 1)[0]
        cursor = Cursor(position, start, end, flags)
        actual_outcome = native.vertrix_mixer_boundary(ctypes.byref(cursor))
        assert actual_outcome == outcome
        assert (cursor.position, cursor.flags) == (expected_position, expected_flags), (index, position, start, end, flags)
        outcomes[outcome] += 1
    cursor = Cursor(123, 45, 67, 17)
    assert native.vertrix_mixer_boundary(ctypes.byref(cursor)) == 0
    assert (cursor.position, cursor.flags) == (123, 17)
    assert native.vertrix_mixer_boundary(None) == -1
    report = {"status": "passed", "boundary_cases": cases, "outcomes_stopped_ready_adjusted": outcomes, "scope": "Original 0x40c483/0x40c4d6 single boundary decisions: signed comparisons, exact-boundary equality, wrapping/reflection arithmetic, direction toggles and stop bits. Random full-width positions and flags. Excludes repeated traversal, batch sizing and kernel dispatch."}
    (build / "mixer-boundary-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))

if __name__ == "__main__":
    main()
