""
    "Compare complete original extended panning command."
    "" import argparse,
    ctypes, json, random, struct, subprocess from pathlib import Path from original import Original,
    BOARD from verify_mixer_set_effects import State

        def
        main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument("executable",
                                                                                  type = Path);
parser.add_argument("--build-dir", type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "extended-pan.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "mixer.c"), "-o", str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
native.vertrix_mixer_extended_pan.argtypes =
    [ ctypes.c_uint8, ctypes.c_int32, ctypes.POINTER(State) ] original = Original(args.executable);
rng = random.Random(0x40d70a);cases=30000
    for index in range(cases):
        parameter=0x80|(index%16);
tick = 0 if index % 2 == 0 else rng.randrange(-2147483648, 2147483648) data =
           bytearray(rng.randbytes(128));
data[4] = parameter word = lambda offset : struct.unpack_from("<I", data, offset)[0] state =
    State(word(28), word(116), word(16), word(20), data[1])
        original.cpu.mem_write(BOARD, bytes(data));
original.cpu.mem_write(0x531B4C, struct.pack("<i", tick));
original.call(0x40D540, eax = BOARD) expected =
    bytes(original.cpu.mem_read(BOARD, 128)) assert native.vertrix_mixer_extended_pan(
        parameter, tick, ctypes.byref(state)) actual = bytearray(data);
actual[1] = state.flags;
struct.pack_into("<I", actual, 28, state.pan);
struct.pack_into("<I", actual, 116, state.offset);
struct.pack_into("<II", actual, 16, state.base, state.output) assert bytes(actual) == expected,
    index before = bytes(state) assert
                   not native.vertrix_mixer_extended_pan(0x70, 0, ctypes.byref(state)) and
                   bytes(state) == before assert
                                   not native.vertrix_mixer_extended_pan(0x80, 0, None) report =
                       {
                           "status" : "passed",
                           "effect_cases" : cases,
                           "scope" : "Full original extended dispatcher selecting case 8, all low "
                                     "nibbles, zero/nonzero signed ticks, random prior pan/flags "
                                     "and whole channel comparison. Excludes full sequencing."
                       }(build / "mixer-extended-pan-verification.json")
                           .write_text(json.dumps(report, indent = 2) + "\n");
print(json.dumps(report, indent = 2)) if __name__ == "__main__" : main()
