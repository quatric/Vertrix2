"""Compare complete original extended note-cut timing and state."""
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
    library = build / "note-cut.dylib"
    subprocess.run(["cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC", str(source / "mixer.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_note_cut.argtypes = [ctypes.c_uint8, ctypes.c_int32, ctypes.POINTER(State)]
    original = Original(args.executable)
    rng = random.Random(0x40d7ec)
    cases = 30000
    for index in range(cases):
        parameter = 0xc0 | (index % 16)
        tick = index % 16 if index % 3 == 0 else (rng.randrange(- 16, 32) if index < 10000 else rng.randrange(- 2147483648, 2147483648))
        data = bytearray(rng.randbytes(128))
        data[4] = parameter
        state = State(* struct.unpack_from("<II", data, 16), data[104], data[1])
        original.cpu.mem_write(BOARD, bytes(data))
        original.cpu.mem_write(0x531B4C, struct.pack("<i", tick))
        original.call(0x40D540, eax=BOARD)
        expected = bytes(original.cpu.mem_read(BOARD, 128))
        assert native.vertrix_mixer_note_cut(parameter, tick, ctypes.byref(state))
        actual = bytearray(data)
        struct.pack_into("<II", actual, 16, state.base, state.output)
        actual[104] = state.memory
        actual[1] = state.flags
        assert bytes(actual) == expected, index
        before = bytes(state)
        assert not native.vertrix_mixer_note_cut(0xb0, 0, ctypes.byref(state)) and bytes(state) == before
        assert not native.vertrix_mixer_note_cut(0xc0, 0, None)
    report = {"status": "passed", "effect_cases": cases, "scope": "Full original extended dispatcher selecting note-cut case 12. All tick nibbles, " "exact matches, near and full-width signed ticks, arbitrary channel state. Whole " "channel comparison includes memory and unrelated field preservation. Excludes " "note delay/retrigger and full sequencing."}
    (build / "mixer-note-cut-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
if __name__ == "__main__":
    main()
