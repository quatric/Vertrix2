"""Execute original stereo kernels and compare every valid volume/pan pair."""
import argparse
import ctypes
import json
import struct
import subprocess
from pathlib import Path
from original import Original, BOARD, BLOCKS

class Gains(ctypes.Structure):
    _fields_ = [("left", ctypes.c_uint8), ("right", ctypes.c_uint8)]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / "source"
    library = build / "mixer-gains.dylib"
    subprocess.run(["cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC", str(source / "mixer.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_stereo_gains.argtypes = [ctypes.c_uint32, ctypes.c_uint8, ctypes.POINTER(Gains)]
    original = Original(args.executable)
    original.cpu.mem_map(0x900000, 0x20000)
    original.cpu.mem_map(0x920000, 0x10000)
    for address, value in ((0x52FC2C, 1), (0x52F910, 0x900000), (0x52F914, 0x920000)):
        original.cpu.mem_write(address, struct.pack("<I", value))
    original.cpu.mem_write(0x52FC1D, bytes([1]))
    original.call(0x40C7D0, eax=1, edx=256)
    cases = 0
    for kernel, sample in ((0x401328, bytes([127]) * 8), (0x402C18, bytes([0, 127]) * 8)):
        original.cpu.mem_write(BLOCKS, sample)
        for volume in range(33):
            for pan in range(256):
                channel = bytearray(24)
                struct.pack_into("<III", channel, 0, BLOCKS, 0, 4096)
                channel[20], channel[21] = volume, pan
                original.cpu.mem_write(BOARD, bytes(channel))
                original.cpu.mem_write(BLOCKS + 8192, bytes(8))
                original.call(kernel, args=(BLOCKS + 8192, 1, BOARD))
                actual = struct.unpack("<ii", original.cpu.mem_read(BLOCKS + 8192, 8))
                result = Gains()
                assert native.vertrix_mixer_stereo_gains(volume, pan, ctypes.byref(result))
                expected = (result.left * 2032, result.right * 2032)
                assert actual == expected, (hex(kernel), volume, pan, actual, expected)
                cases += 1
    result = Gains(17, 19)
    assert not native.vertrix_mixer_stereo_gains(33, 128, ctypes.byref(result))
    assert (result.left, result.right) == (17, 19)
    assert not native.vertrix_mixer_stereo_gains(32, 128, None)
    report = {"status": "passed", "kernel_cases": cases, "scope": "Full original noninterpolated 8-bit and 16-bit stereo kernels, one positive sample per case, all 33 valid stored volumes and all 256 pan values. Original gain table initialized by 0x40c7d0 with master gain 256. Does not verify interpolation, arbitrary PCM, looping or complete music playback."}
    (build / "mixer-gains-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))

if __name__ == "__main__":
    main()
