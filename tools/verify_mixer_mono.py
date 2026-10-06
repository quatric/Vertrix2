"""Compare PCM8 mono accumulation and read state with full original kernel."""
import argparse
import ctypes
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original, BOARD, BLOCKS

class State(ctypes.Structure):
    _fields_ = [("position", ctypes.c_uint32), ("last_sample", ctypes.c_uint8)]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / "source"
    library = build / "mixer-mono.dylib"
    subprocess.run(["cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC", str(source / "mixer.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_pcm8_mono.argtypes = [ctypes.POINTER(ctypes.c_uint8), ctypes.c_size_t, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint32, ctypes.POINTER(State), ctypes.POINTER(ctypes.c_int32), ctypes.c_size_t, ctypes.c_size_t]
    original = Original(args.executable)
    original.cpu.mem_map(0x900000, 0x20000)
    original.cpu.mem_map(0x920000, 0x10000)
    for address, value in ((0x52FC2C, 1), (0x52F910, 0x900000), (0x52F914, 0x920000)):
        original.cpu.mem_write(address, struct.pack("<I", value))
    original.cpu.mem_write(0x52FC1D, bytes([0]))
    rng = random.Random(0x40109c)
    cases = total_frames = 0
    for master in (0, 1, 2, 15, 16, 127, 128, 255, 256):
        assert original.call(0x40C7D0, eax=1, edx=master) == 0
        for index in range(2500):
            frames = 1 + index % 65
            position = rng.randrange(512 << 12, 2048 << 12)
            step = rng.randrange(-16384, 16385)
            volume = rng.randrange(33)
            data = rng.randbytes(4096)
            existing = [rng.randrange(-2147483648, 2147483648) for _ in range(frames)]
            original.cpu.mem_write(BLOCKS, data)
            channel = bytearray(24)
            struct.pack_into("<III", channel, 0, BLOCKS, position, step & 0xffffffff)
            channel[20] = volume
            original.cpu.mem_write(BOARD, bytes(channel))
            original.cpu.mem_write(BOARD + 1024, struct.pack("<" + "i" * frames, *existing))
            original.call(0x40109C, args=(BOARD + 1024, frames, BOARD))
            expected = bytes(original.cpu.mem_read(BOARD + 1024, frames * 4))
            expected_position = struct.unpack("<I", original.cpu.mem_read(BOARD + 4, 4))[0]
            expected_last = original.cpu.mem_read(BOARD + 23, 1)[0]
            samples = (ctypes.c_uint8 * len(data)).from_buffer_copy(data)
            output = (ctypes.c_int32 * frames)(*existing)
            state = State(position, 0)
            assert native.vertrix_mixer_pcm8_mono(samples, len(data), step & 0xffffffff, volume, master, ctypes.byref(state), output, frames, frames)
            assert bytes(output) == expected, (master, index)
            assert (state.position, state.last_sample) == (expected_position, expected_last)
            cases += 1
            total_frames += frames
    samples = (ctypes.c_uint8 * 1)(127)
    output = (ctypes.c_int32 * 1)(123)
    state = State(0, 19)
    assert not native.vertrix_mixer_pcm8_mono(samples, 1, 4096, 32, 256, ctypes.byref(state), output, 1, 1)
    assert (state.position, state.last_sample, output[0]) == (0, 19, 123)
    assert not native.vertrix_mixer_pcm8_mono(samples, 1, 0, 32, 256, ctypes.byref(state), output, 1, 0)
    assert native.vertrix_mixer_pcm8_mono(None, 0, 0, 32, 256, ctypes.byref(state), None, 0, 0)
    report = {"status": "passed", "kernel_batches": cases, "accumulated_frames": total_frames, "scope": "Complete original noninterpolated PCM8 mono kernel 0x40109c: random signed accumulator contents, raw samples, fractional forward/reverse/zero steps, all batch lengths 1..65, volumes 0..32, nine master gains. Output bytes, final position and prefetched last sample match. Native transactional prefetch/capacity rejection and zero-count guard. Excludes loop traversal, stereo and interpolation."}
    (build / "mixer-mono-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))

if __name__ == "__main__":
    main()
