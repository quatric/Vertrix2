"""Compare complete original 0x40c460 channel traversal and accumulation."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, BLOCKS


class Cursor(ctypes.Structure):
    _fields_ = [("position", ctypes.c_uint32), ("start", ctypes.c_uint32), ("end", ctypes.c_uint32), ("flags", ctypes.c_uint8)]


class Channel(ctypes.Structure):
    _fields_ = [("cursor", Cursor), ("step", ctypes.c_uint32), ("volume", ctypes.c_uint8), ("pan", ctypes.c_uint8), ("last", ctypes.c_uint8)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / "source"
    library = build / "channel.dylib"
    subprocess.run(["cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC", str(source / "mixer.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_channel.argtypes = [ctypes.POINTER(ctypes.c_uint8), ctypes.c_size_t, ctypes.c_uint32, ctypes.c_int, ctypes.c_int, ctypes.POINTER(Channel), ctypes.POINTER(ctypes.c_int32), ctypes.c_size_t, ctypes.c_size_t]
    original = Original(args.executable)
    original.cpu.mem_map(0x900000, 0x20000)
    original.cpu.mem_map(0x920000, 0x10000)
    for address, value in ((0x52FC2C, 1), (0x52F910, 0x900000), (0x52F914, 0x920000)):
        original.cpu.mem_write(address, struct.pack("<I", value))
    rng = random.Random(0x40c460)
    cases = total = 0
    for stereo in (0, 1):
        original.cpu.mem_write(0x52FC1D, bytes([stereo]))
        original.call(0x40C7D0, eax=1, edx=255)
        for interpolate in (0, 1):
            kernels = ((0x40109c, 0x402934), (0x401328, 0x402c18)) if not interpolate else ((0x401cd0, 0x4036c8), (0x401f9c, 0x4039e4))
            for address, value in ((0x52FC34, kernels[stereo][0]), (0x52FC38, kernels[stereo][1])):
                original.cpu.mem_write(address, struct.pack("<I", value))
            for index in range(2000):
                flags = (index % 2) * 2 + (0, 4, 12)[index % 3] + (16 if index % 5 == 0 else 0)
                position = rng.randrange(16 << 12, 65 << 12)
                step = rng.randrange(1, 12000)
                frames = rng.randrange(1, 257)
                volume = rng.randrange(33)
                pan = rng.randrange(256)
                last = rng.randrange(256)
                data = rng.randbytes(512)
                values = frames * (stereo + 1)
                existing = [rng.randrange(- 2147483648, 2147483648) for _ in range(values)]
                channel = bytearray(24)
                struct.pack_into("<IIIII", channel, 0, BLOCKS, position, step, 16 << 12, 64 << 12)
                channel[20: 24] = bytes([volume, pan, flags, last])
                original.cpu.mem_write(BOARD, bytes(channel))
                original.cpu.mem_write(BLOCKS, data)
                original.cpu.mem_write(BOARD + 1024, struct.pack("<" + "i" * values, * existing))
                original.call(0x40C460, eax=BOARD + 1024, edx=values, ebx=BOARD)
                expected = bytes(original.cpu.mem_read(BOARD + 1024, values * 4))
                final = bytes(original.cpu.mem_read(BOARD, 24))
                samples = (ctypes.c_uint8 * len(data)).from_buffer_copy(data)
                output = (ctypes.c_int32 * values)(* existing)
                state = Channel(Cursor(position, 16 << 12, 64 << 12, flags), step, volume, pan, last)
            assert native.vertrix_mixer_channel(samples, len(data), 255, stereo, interpolate, ctypes.byref(state), output, frames, values), (stereo, interpolate, index)
            assert bytes(output) == expected, (stereo, interpolate, index, "audio")
            assert (state.cursor.position, state.cursor.flags, state.step, state.last) == (struct.unpack_from("<I", final, 4)[0], final[22], struct.unpack_from("<I", final, 8)[0], final[23]), (stereo, interpolate, index, "state")
            cases += 1
            total += frames
    report = {"status": "passed", "channel_cases": cases, "frames": total, "scope": "Complete original 0x40c460 channel traversal, all eight kernel modes, forward/reverse, " "nonloop/forward-loop/ping-pong, repeated crossings and stopping. Output and final " "position/flags/step/cache match. Music scheduling and output delivery excluded."}
    (build / "mixer-channel-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
if __name__ == "__main__":
    main()
