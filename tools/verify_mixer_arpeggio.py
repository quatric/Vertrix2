"""Compare complete original music arpeggio effect and update flags."""
import argparse, ctypes, json, random, struct, subprocess
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
    library = build / "arpeggio.dylib"
    subprocess.run(["cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC", str(source / "mixer.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_arpeggio.argtypes = [ctypes.c_uint8, ctypes.c_int32, ctypes.c_uint8, ctypes.c_int32, ctypes.c_int32, ctypes.c_int, ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_uint8)]
    original = Original(args.executable)
    rng = random.Random(0x40cef0)
    cases = 30000
    compared_cases = 0
    for index in range(cases):
        parameter = index % 256
        tick = rng.randrange(- 2147483648, 2147483648)
        note = rng.randrange(256)
        relative = rng.randrange(- 96, 97)
        tune = rng.randrange(- 128, 128)
        linear = index % 2
        initial_period = rng.randrange(2 ** 32)
        initial_flags = rng.randrange(256)
        channel = bytearray(64)
        channel[1] = initial_flags
        channel[4] = parameter
        channel[7] = note
        struct.pack_into("<ii", channel, 8, tune, relative)
        struct.pack_into("<I", channel, 40, initial_period)
        original.cpu.mem_write(BOARD, bytes(channel))
        original.cpu.mem_write(0x531B4C, struct.pack("<i", tick))
        original.cpu.mem_write(0x531B46, bytes([linear]))
        original.call(0x40CEF0, eax=BOARD)
        expected_period = struct.unpack("<I", original.cpu.mem_read(BOARD + 40, 4))[0]
        expected_flags = original.cpu.mem_read(BOARD + 1, 1)[0]
        period = ctypes.c_uint32(initial_period)
        flags = ctypes.c_uint8(initial_flags)
        assert native.vertrix_mixer_arpeggio(parameter, tick, note, relative, tune, linear, ctypes.byref(period), ctypes.byref(flags))
        assert (period.value, flags.value) == (expected_period, expected_flags), index
        compared_cases += 1
    assert compared_cases == cases, (compared_cases, cases)
    assert not native.vertrix_mixer_arpeggio(1, 0, 48, 0, 0, 1, None, ctypes.byref(flags))
    assert not native.vertrix_mixer_arpeggio(1, 0, 48, 0, 0, 1, ctypes.byref(period), None)
    report = {"status": "passed", "effect_cases": cases, "compared_cases": compared_cases, "scope": "Complete original 0x40cef0 effect, all 256 parameters, signed full-width ticks, " "both tuning modes, random base notes/relative notes/finetunes and prior output " "state. Period and dirty bit match including zero-parameter preservation. " "Excludes complete sequencer dispatch and other effects."}
    (build / "mixer-arpeggio-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
if __name__ == "__main__":
    main()
