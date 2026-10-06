"""Compare original extended glissando nibble controls exhaustively."""
import argparse, ctypes, json, struct, subprocess
from pathlib import Path
from original import Original, BOARD


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / "source"
    library = build / "glissando-control.dylib"
    subprocess.run(["cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC", str(source / "mixer.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_glissando_control.argtypes = [ctypes.c_uint8, ctypes.c_int32, ctypes.POINTER(ctypes.c_uint8)]
    original = Original(args.executable)
    cases = 0
    for selector in (3,):
        for low in range(16):
            parameter = (selector << 4) | low
            for initial in range(256):
                for tick in (0, 1, - 1):
                    data = bytearray([0xa5] * 128)
                    data[4] = parameter
                    data[61] = initial
                    original.cpu.mem_write(BOARD, bytes(data))
                    original.cpu.mem_write(0x531B4C, struct.pack("<i", tick))
                    original.call(0x40D540, eax=BOARD)
                    expected = bytes(original.cpu.mem_read(BOARD, 128))
                    result = ctypes.c_uint8(initial)
                    assert native.vertrix_mixer_glissando_control(parameter, tick, ctypes.byref(result))
                    actual = bytearray(data)
                    actual[61] = result.value
                    assert bytes(actual) == expected
                    cases += 1
                    result = ctypes.c_uint8(123)
                    assert not native.vertrix_mixer_glissando_control(0x40, 0, ctypes.byref(result)) and result.value == 123
                    assert not native.vertrix_mixer_glissando_control(0x30, 0, None)
    report = {"status": "passed", "effect_cases": cases, "scope": "Complete original 0x40d540 selecting glissando control 3, exhaustive " "low nibbles and prior glissando bytes at ticks 0/1/-1. Full channel " "comparison verifies mode replacement and all unrelated state " "preservation. Excludes later pitch quantization use."}
    (build / "mixer-glissando-control-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
if __name__ == "__main__":
    main()
