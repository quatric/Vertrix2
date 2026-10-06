"""Compare original extended fine volume-slide state and timing."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD
from verify_mixer_volume_slide import State


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / "source"
    library = build / "fine-volume.dylib"
    subprocess.run(["cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC", str(source / "mixer.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_fine_volume.argtypes = [ctypes.c_uint8, ctypes.c_int32, ctypes.POINTER(State)]
    original = Original(args.executable)
    rng = random.Random(0x40d76d)
    cases = 0
    for selector in (10, 11):
        fixtures = [(low, tick, base) for low in range(16) for tick in (0, 1, - 1) for base in range(65)]
        fixtures += [(rng.randrange(16), 0 if index % 2 == 0 else rng.randrange(- 2147483648, 2147483648), rng.randrange(2 ** 32)) for index in range(20000)]
        for low, tick, base in fixtures:
            parameter = (selector << 4) | low
            data = bytearray(rng.randbytes(128))
            data[4] = parameter
            struct.pack_into("<I", data, 16, base)
            state = State(* struct.unpack_from("<II", data, 16), data[104], data[1])
            original.cpu.mem_write(BOARD, bytes(data))
            original.cpu.mem_write(0x531B4C, struct.pack("<i", tick))
            original.call(0x40D540, eax=BOARD)
            expected = bytes(original.cpu.mem_read(BOARD, 128))
            assert native.vertrix_mixer_fine_volume(parameter, tick, ctypes.byref(state))
            actual = bytearray(data)
            struct.pack_into("<II", actual, 16, state.base, state.output)
            actual[104] = state.memory
            actual[1] = state.flags
            assert bytes(actual) == expected, (selector, low, tick, base)
            cases += 1
            before = bytes(state)
            assert not native.vertrix_mixer_fine_volume(0xc0, 0, ctypes.byref(state)) and bytes(state) == before
            assert not native.vertrix_mixer_fine_volume(0xa0, 0, None)
    report = {"status": "passed", "effect_cases": cases, "scope": "Full original extended dispatcher selecting fine-volume cases 10/11. " "Exhaustive low nibbles/valid volumes at ticks 0/1/-1 plus 20000 " "full-width states per selector. Whole channel comparison checks output, " "flags, memory and unrelated preservation. Excludes full sequencing."}
    (build / "mixer-fine-volume-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
if __name__ == "__main__":
    main()
