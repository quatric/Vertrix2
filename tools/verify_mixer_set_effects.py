"""Compare original pan, sample-offset and volume music setters."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD


class State(ctypes.Structure):
    _fields_ = [("pan", ctypes.c_uint32), ("offset", ctypes.c_uint32), ("base", ctypes.c_uint32), ("output", ctypes.c_uint32), ("flags", ctypes.c_uint8)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / "source"
    library = build / "set-effects.dylib"
    subprocess.run(["cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC", str(source / "mixer.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_set_effect.argtypes = [ctypes.c_int, ctypes.c_uint8, ctypes.c_int32, ctypes.POINTER(State)]
    original = Original(args.executable)
    rng = random.Random(0x40d410)
    cases = 20000
    for effect, address in enumerate((0x40D410, 0x40D430, 0x40D490)):
        for index in range(cases):
            data = bytearray(rng.randbytes(128))
            parameter = index % 256
            data[4] = parameter
            tick = 0 if index % 2 == 0 else rng.randrange(- 2147483648, 2147483648)
            word = lambda offset: struct.unpack_from("<I", data, offset)[0]
            state = State(word(28), word(116), word(16), word(20), data[1])
            original.cpu.mem_write(BOARD, bytes(data))
            original.cpu.mem_write(0x531B4C, struct.pack("<i", tick))
            original.call(address, eax=BOARD)
            expected = bytes(original.cpu.mem_read(BOARD, 128))
            assert native.vertrix_mixer_set_effect(effect, parameter, tick, ctypes.byref(state))
            actual = bytearray(data)
            actual[1] = state.flags
            struct.pack_into("<I", actual, 28, state.pan)
            struct.pack_into("<I", actual, 116, state.offset)
            struct.pack_into("<II", actual, 16, state.base, state.output)
            assert bytes(actual) == expected, (effect, index)
            before = bytes(state)
            assert not native.vertrix_mixer_set_effect(3, 255, 0, ctypes.byref(state)) and bytes(state) == before
            assert not native.vertrix_mixer_set_effect(- 1, 255, 0, ctypes.byref(state)) and bytes(state) == before
            assert not native.vertrix_mixer_set_effect(0, 255, 0, None)
    report = {"status": "passed", "effect_cases": cases * 3, "scope": "Complete original 0x40d410/0x40d430/0x40d490, all parameter bytes and " "zero/nonzero signed ticks. Whole-channel comparison verifies changed " "fields/flags and preservation of unrelated state. Native invalid-effect/null " "checks. Excludes effect dispatch and sample-offset interpretation."}
    (build / "mixer-set-effects-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
if __name__ == "__main__":
    main()
