"""Compare original software-mixer sample guards with recovered native C."""
import argparse
import ctypes
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original, BOARD, BLOCKS


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / "source"
    library = build / "guard.dylib"
    subprocess.run(["cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC", str(source / "audio.c"), str(source / "vf.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_audio_sample_guard.argtypes = [ctypes.c_void_p, ctypes.c_size_t, * ([ctypes.c_uint32] * 3), ctypes.c_uint8, * ([ctypes.c_uint32] * 2)]
    original = Original(args.executable)
    rng = random.Random(0x40c990)
    cases = 20000
    for _ in range(cases):
        count = rng.randrange(257)
        start, end = rng.randrange(count + 1), rng.randrange(count + 1)
        flags = rng.randrange(256)
        offset, updated = rng.randrange(2 ** 32), rng.randrange(2 ** 32)
        data = rng.randbytes(count + 4) + bytes([165]) * 4
        original.cpu.mem_write(BOARD, bytes(32))
        original.cpu.mem_write(BOARD + 4, struct.pack("<4I", BLOCKS, count, start, end))
        original.cpu.mem_write(BOARD + 0x16, bytes([flags]))
        original.cpu.mem_write(BLOCKS, data)
        original.call(0x40C990, edx=offset, ebx=updated)
        expected = bytes(original.cpu.mem_read(BLOCKS, len(data)))
        samples = (ctypes.c_uint8 * len(data)).from_buffer_copy(data)
        assert native.vertrix_audio_sample_guard(samples, count + 4, count, start, end, flags, offset, updated)
        assert bytes(samples) == expected
        storage = (ctypes.c_uint8 * 8)(* ([165] * 8))
        saved = bytes(storage)
        assert not native.vertrix_audio_sample_guard(storage, 8, 8, 0, 8, 16, 0, 8)
        assert bytes(storage) == saved
        assert not native.vertrix_audio_sample_guard(storage, 8, 8, 0, 8, 0, 0, 8)
        assert bytes(storage) == saved
    report = {"status": "passed", "cases": cases, "scope": "Original complete 0x40c990 sample guard callback, forward loops, overlaps, end " "guards and wrapping update arithmetic. No mixer playback."}
    (build / "audio-guard-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
if __name__ == "__main__":
    main()
