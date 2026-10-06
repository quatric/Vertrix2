""
    "Verify complete original combined pitch/volume slide effects."
    "" import argparse,
    ctypes, json, random, struct, subprocess from pathlib import Path from original import Original,
    BOARD from verify_mixer_portamento import State as Portamento from verify_mixer_vibrato import
        State as Vibrato from verify_mixer_volume_slide import State as Volume

            def
            main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument("executable",
                                                                                  type = Path);
parser.add_argument("--build-dir", type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "combined.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "mixer.c"), "-o", str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
original = Original(args.executable);rng=random.Random(0x40d2d0)
    cases=20000
    for kind,address,klass in (("portamento",0x40D2D0,Portamento),("vibrato",0x40D300,Vibrato)):
        function=getattr(native,"vertrix_mixer_"+kind+"_volume");function.argtypes=[ctypes.c_uint8,ctypes.c_int32,ctypes.POINTER(klass),ctypes.POINTER(Volume)]
        for index in range(cases):
            data=bytearray(rng.randbytes(128));
parameter = index % 256;
data[4] = parameter;
tick = 0 if index % 3 == 0 else rng.randrange(-2147483648, 2147483648) word =
           lambda offset : struct.unpack_from("<I", data, offset)[0] if kind == "portamento"
    : pitch = klass(word(36), word(40), word(96), word(100), data[1]) else
    : pitch = klass(word(36), word(40), word(64), word(68), word(72), data[60], data[1]) volume =
          Volume(word(16), word(20), data[104], data[1]) original.cpu.mem_write(BOARD, bytes(data));
original.cpu.mem_write(0x531B4C, struct.pack("<i", tick));
original.call(address, eax = BOARD) expected = bytes(original.cpu.mem_read(BOARD, 128)) assert
    function(parameter, tick, ctypes.byref(pitch), ctypes.byref(volume)) actual = bytearray(data);
actual[1] = pitch.flags;
actual[104] = volume.memory assert volume.flags ==
              pitch.flags struct.pack_into("<II", actual, 16, volume.base, volume.output);
struct.pack_into("<II", actual, 36, pitch.base, pitch.output) if kind == "portamento"
    : struct.pack_into("<II", actual, 96, pitch.speed, pitch.target) else
    : struct.pack_into("<III", actual, 64, pitch.phase, pitch.depth, pitch.speed);
actual[60] = pitch.wave assert bytes(actual) == expected,
    (kind, index)assert not function(1, 0, None, ctypes.byref(volume)) assert
    not function(1, 0, ctypes.byref(pitch),
                 None) report = {
        "status" : "passed",
        "effect_cases" : cases * 2,
        "scope" : "Complete original 0x40d2d0/0x40d300 combined effects. Whole 128-byte channel "
                  "comparison checks pitch/volume state, first-tick memory and flags, later "
                  "application order, and preservation of unrelated fields. All parameter bytes "
                  "and random full-width states. Excludes sequencer dispatch."
    }(build / "mixer-combined-verification.json")
                                    .write_text(json.dumps(report, indent = 2) + "\n");
print(json.dumps(report, indent = 2)) if __name__ == "__main__" : main()
