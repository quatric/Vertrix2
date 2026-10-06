"""Verify original 8/16-bit mixer output conversion, including overflow flags."""
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
    library = build / "mixer-output.dylib"
    subprocess.run(["cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC", str(source / "mixer.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_output.argtypes = [ctypes.POINTER(ctypes.c_int32), ctypes.c_size_t, ctypes.c_int, ctypes.POINTER(ctypes.c_uint8), ctypes.c_size_t]
    original = Original(args.executable)
    rng = random.Random(0x401010)
    values = list(range(-65536, 65537)) + list(range(2147450870, 2147483648)) + [-2147483648]
    values += [rng.randrange(-2147483648, 2147483648) for _ in range(20000)]
    for sixteen, routine in ((0, 0x401010), (1, 0x401054)):
        stride = sixteen + 1
        for offset in range(0, len(values), 1024):
            batch = values[offset:offset + 1024]
            count = len(batch)
            source_values = (ctypes.c_int32 * count)(*batch)
            output = (ctypes.c_uint8 * (count * stride))()
            original.cpu.mem_write(BLOCKS, struct.pack("<" + "i" * count, *batch))
            original.cpu.mem_write(BOARD, bytes(count * stride))
            original.call(routine, args=(BOARD, BLOCKS, count))
            expected = bytes(original.cpu.mem_read(BOARD, count * stride))
            assert native.vertrix_mixer_output(source_values, count, sixteen, output, len(output))
            assert bytes(output) == expected, (sixteen, offset)
    source_values = (ctypes.c_int32 * 2)(-32768, 32767)
    output = (ctypes.c_uint8 * 4)(17, 19, 23, 29)
    assert not native.vertrix_mixer_output(source_values, 2, 1, output, 3)
    assert bytes(output) == bytes([17, 19, 23, 29])
    assert not native.vertrix_mixer_output(None, 2, 1, output, 4)
    assert not native.vertrix_mixer_output(source_values, 2, 1, None, 4)
    assert native.vertrix_mixer_output(None, 0, 1, None, 0)
    report = {"status": "passed", "converted_samples": len(values) * 2, "scope": "Complete original 0x401010 and 0x401054 output routines. Exhaustive -65536..65536, all positive signed overflow inputs for the PCM8 bias addition, 20000 random signed 32-bit values, plus INT_MIN. Native capacity/null/zero-count guards. Excludes accumulation and complete playback."}
    (build / "mixer-output-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))

if __name__ == "__main__":
    main()
