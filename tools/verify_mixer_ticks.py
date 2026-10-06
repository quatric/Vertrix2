"""Compare scheduler phase and callback count with original 0x40c5c0."""
import argparse
import ctypes
import json
import random
import struct
import subprocess
from pathlib import Path

from original import Original, BOARD


class Batch(ctypes.Structure):
    _fields_ = [("values", ctypes.c_uint32), ("phase", ctypes.c_uint32), ("tick", ctypes.c_int)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / "source"
    library = build / "ticks.dylib"
    subprocess.run(
        [
            "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
            str(source / "mixer.c"), "-o", str(library)
        ],
        check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_tick_batch.argtypes = [
        ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint32, ctypes.POINTER(Batch)
    ]
    original = Original(args.executable)
    original.cpu.mem_write(0x700200, bytes.fromhex("ff0500188000c3"))
    original.cpu.mem_write(0x52FC30, struct.pack("<I", 0x700200))
    original.cpu.mem_write(0x52FC18, bytes(4))
    rng = random.Random(0x40c5c0)
    cases = 5000
    total_batches = total_ticks = 0
    for index in range(cases):
        period = rng.randrange(64, 4097)
        phase = rng.randrange(period)
        remaining = rng.randrange(1, 8193)
        original.cpu.mem_write(0x52FC24, struct.pack("<II", period, phase))
        original.cpu.mem_write(0x801800, bytes(4))
        original.call(0x40C5C0, eax=BOARD, edx=remaining)
        expected_phase = struct.unpack("<I", original.cpu.mem_read(0x52FC28, 4))[0]
        expected_ticks = struct.unpack("<I", original.cpu.mem_read(0x801800, 4))[0]
        ticks = 0
        while remaining:
            batch = Batch()
            assert native.vertrix_mixer_tick_batch(period, phase, remaining, ctypes.byref(batch))
            assert 0 < batch.values <= remaining
            phase = batch.phase
            remaining -= batch.values
            ticks += batch.tick
            total_batches += 1
        assert (phase, ticks) == (expected_phase, expected_ticks), (
            index, phase, ticks, expected_phase, expected_ticks)
        total_ticks += ticks
    batch = Batch(17, 19, 23)
    assert not native.vertrix_mixer_tick_batch(0, 0, 128, ctypes.byref(batch))
    assert (batch.values, batch.phase, batch.tick) == (17, 19, 23)
    assert not native.vertrix_mixer_tick_batch(128, 0, 0, ctypes.byref(batch))
    assert not native.vertrix_mixer_tick_batch(128, 0, 128, None)
    report = {
        "status": "passed",
        "buffer_cases": cases,
        "native_batches": total_batches,
        "tick_callbacks": total_ticks,
        "scope": "Complete original 0x40c5c0 with zero channels and counting callback, random "
                 "periods 64..4096, phases below period, buffer lengths 1..8192 values. Final "
                 "phase and callback count match repeated native scheduling. Excludes channel "
                 "mixing during callbacks, callback effect logic and hardware timing."
    }
    (build / "mixer-ticks-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()