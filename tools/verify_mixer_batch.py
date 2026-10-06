"""Compare mixer batch sizing and temporary reverse step with original x86."""
import argparse
import ctypes
import json
import random
import struct
import subprocess
from pathlib import Path
from unicorn.x86_const import UC_X86_REG_EDI, UC_X86_REG_ESI
from original import Original, BOARD

class Cursor(ctypes.Structure):
    _fields_ = [("position", ctypes.c_uint32), ("start", ctypes.c_uint32), ("end", ctypes.c_uint32), ("flags", ctypes.c_uint8)]

class Batch(ctypes.Structure):
    _fields_ = [("frames", ctypes.c_uint32), ("step", ctypes.c_uint32)]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / "source"
    library = build / "mixer-batch.dylib"
    subprocess.run(["cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC", str(source / "mixer.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_batch.argtypes = [ctypes.POINTER(Cursor), ctypes.c_uint32, ctypes.c_uint32, ctypes.POINTER(Batch)]
    original = Original(args.executable)
    rng = random.Random(0x40c518)
    cases = 30000
    for index in range(cases):
        position, start, end, remaining = [rng.randrange(2**32) for _ in range(4)]
        step = rng.randrange(1, 0x80000000)
        flags = rng.randrange(256)
        if index < 10000:
            step = rng.randrange(1, 20000)
            remaining = rng.randrange(1, 1000)
            start = 4096
            end = 4096000
            position = rng.randrange(start, end + 1)
        if index % 11 == 0:
            position = start if flags & 16 else end
        channel = bytearray(24)
        struct.pack_into("<IIII", channel, 4, position, step, start, end)
        channel[22] = flags
        original.cpu.mem_write(BOARD, bytes(channel))
        original.cpu.reg_write(UC_X86_REG_EDI, remaining)
        original.call(0x40C518, ebx=BOARD, stop=0x40C547)
        expected_frames = original.cpu.reg_read(UC_X86_REG_ESI)
        expected_step = struct.unpack("<I", original.cpu.mem_read(BOARD + 8, 4))[0]
        cursor = Cursor(position, start, end, flags)
        batch = Batch()
        assert native.vertrix_mixer_batch(ctypes.byref(cursor), step, remaining, ctypes.byref(batch))
        assert (batch.frames, batch.step) == (expected_frames, expected_step), index
    batch = Batch(17, 19)
    for step in (0, 0x80000000, 0xffffffff):
        assert not native.vertrix_mixer_batch(ctypes.byref(cursor), step, 32, ctypes.byref(batch))
        assert (batch.frames, batch.step) == (17, 19)
    assert not native.vertrix_mixer_batch(None, 4096, 32, ctypes.byref(batch))
    assert not native.vertrix_mixer_batch(ctypes.byref(cursor), 4096, 32, None)
    report = {"status": "passed", "batch_cases": cases, "scope": "Actual original 0x40c518..0x40c547: batch length, unsigned wrapped product comparison, signed wrapped numerator division, temporary reverse-step negation. 10000 realistic-range and 20000 full-width fixtures, including equality. Excludes kernel dispatch, repeated traversal and music scheduling."}
    (build / "mixer-batch-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))

if __name__ == "__main__":
    main()
