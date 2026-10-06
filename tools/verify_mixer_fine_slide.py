"""Compare original extended dispatcher fine pitch slide cases."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD
from verify_mixer_slides import Slide


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / "source"
    library = build / "fine-slide.dylib"
    subprocess.run(["cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC", str(source / "mixer.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_fine_slide.argtypes = [ctypes.c_uint8, ctypes.c_int32, ctypes.c_int, ctypes.POINTER(Slide)]
    original = Original(args.executable)
    rng = random.Random(0x40d55f)
    cases = 30000
    for increasing, selector, memory in ((0, 1, 106), (1, 2, 107)):
        for index in range(cases):
            parameter = (selector << 4) | (index % 16)
            tick = 0 if index % 2 == 0 else rng.randrange(- 2147483648, 2147483648)
            base, output = [rng.randrange(2 ** 32) for _ in range(2)]
            amount = rng.randrange(256)
            flags = rng.randrange(256)
            data = bytearray(rng.randbytes(128))
            data[1] = flags
            data[4] = parameter
            data[memory] = amount
            struct.pack_into("<II", data, 36, base, output)
            original.cpu.mem_write(BOARD, bytes(data))
            original.cpu.mem_write(0x531B4C, struct.pack("<i", tick))
            original.call(0x40D540, eax=BOARD)
            expected = bytes(original.cpu.mem_read(BOARD, 128))
            state = Slide(base, output, amount, flags)
            assert native.vertrix_mixer_fine_slide(parameter, tick, increasing, ctypes.byref(state))
            actual = bytearray(data)
            actual[1] = state.flags
            actual[memory] = state.amount
            struct.pack_into("<II", actual, 36, state.base, state.output)
            assert bytes(actual) == expected, (increasing, index)
            state.amount = 256
            before = bytes(state)
            assert not native.vertrix_mixer_fine_slide(1, 0, 0, ctypes.byref(state)) and bytes(state) == before
            assert not native.vertrix_mixer_fine_slide(1, 0, 0, None)
    report = {"status": "passed", "effect_cases": cases * 2, "scope": "Full original extended dispatcher 0x40d540 selecting fine pitch slides 1/2, all low " "nibbles, byte memory, zero/nonzero signed ticks, whole channel preservation, signed " "clamps and wrapping. Excludes other extended selectors and full sequencing."}
    (build / "mixer-fine-slide-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
if __name__ == "__main__":
    main()
