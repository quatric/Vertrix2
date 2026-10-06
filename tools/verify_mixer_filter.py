"""Verify smoothing recurrence against complete original interpolation kernel."""
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
    library = build / "mixer-filter.dylib"
    subprocess.run(["cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC", str(source / "mixer.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_filter.argtypes = [ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint8)]
    original = Original(args.executable)
    original.cpu.mem_map(0x900000, 0x20000)
    original.cpu.mem_map(0x920000, 0x10000)
    for address, value in ((0x52FC2C, 1), (0x52F910, 0x900000), (0x52F914, 0x920000)):
        original.cpu.mem_write(address, struct.pack("<I", value))
    original.cpu.mem_write(0x52FC1D, bytes([0]))
    assert original.call(0x40C7D0, eax=1, edx=256) == 0
    rng = random.Random(0x401cd0)
    fixtures = [(previous, rng.randrange(256), weight * 128) for weight in range(32) for previous in range(256)]
    fixtures += [(rng.randrange(256), rng.randrange(256), rng.randrange(-4095, 4096)) for _ in range(20000)]
    for previous, sample, step in fixtures:
        channel = bytearray(24)
        struct.pack_into("<III", channel, 0, BLOCKS, 4096, step & 0xffffffff)
        channel[20], channel[23] = 32, previous
        original.cpu.mem_write(BOARD, bytes(channel))
        original.cpu.mem_write(BLOCKS, bytes([sample]) * 8)
        original.cpu.mem_write(BOARD + 1024, bytes(4))
        original.call(0x401CD0, args=(BOARD + 1024, 1, BOARD))
        actual = struct.unpack("<i", original.cpu.mem_read(BOARD + 1024, 4))[0]
        cached = original.cpu.mem_read(BOARD + 23, 1)[0]
        result = ctypes.c_uint8()
        assert native.vertrix_mixer_filter(previous, sample, abs(step) >> 7, ctypes.byref(result))
        signed = result.value if result.value < 128 else result.value - 256
        assert actual == signed * 256 and cached == result.value, (previous, sample, step, actual, cached, result.value)
    result = ctypes.c_uint8(123)
    assert not native.vertrix_mixer_filter(128, 127, 32, ctypes.byref(result)) and result.value == 123
    assert not native.vertrix_mixer_filter(128, 127, 31, None)
    report = {"status": "passed", "original_kernel_cases": len(fixtures), "scope": "Complete original PCM8 mono interpolated kernel 0x401cd0, one output frame per fixture, previous filtered byte varied, all 32 quantized weights, forward/reverse/zero sub-sample steps. Output contribution and persisted filtered byte match. Excludes long batches, large-step fallback, other kernels and loop traversal."}
    (build / "mixer-filter-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))

if __name__ == "__main__":
    main()
