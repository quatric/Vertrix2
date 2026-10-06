""
    "Compare original pattern-delay gating and pending state."
    "" import argparse,
    ctypes, json, random, struct, subprocess from pathlib import Path from original import Original,
    BOARD

        def
        main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument("executable",
                                                                                  type = Path);
parser.add_argument("--build-dir", type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "pattern-delay.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "mixer.c"), "-o", str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
native.vertrix_mixer_pattern_delay.argtypes = [
    ctypes.c_uint8, ctypes.c_int32, ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_uint8)
] original = Original(args.executable);
rng = random.Random(0x40d842);cases=0
    for low in range(16):
        for prior_flags in range(256):
            for tick in (0,1,-1):
                parameter=0xe0|low;
prior_delay = rng.randrange(2 * *32);
data = rng.randbytes(192);
data = bytearray(data);
data[4] = parameter original.cpu.mem_write(BOARD, bytes(data));
original.cpu.mem_write(0x531B4C, struct.pack("<i", tick));
original.cpu.mem_write(0x531B78, struct.pack("<I", prior_delay));
original.cpu.mem_write(0x531B44, bytes([prior_flags]));
original.call(0x40D540, eax = BOARD) expected =
    (struct.unpack("<I", original.cpu.mem_read(0x531B78, 4))[0],
     original.cpu.mem_read(0x531B44, 1)[0])delay = ctypes.c_uint32(prior_delay);
flags = ctypes.c_uint8(prior_flags)
            assert native.vertrix_mixer_pattern_delay(parameter, tick, ctypes.byref(delay),
                                                      ctypes.byref(flags))
                assert(delay.value,
                       flags.value) == expected assert bytes(original.cpu.mem_read(BOARD, 192)) ==
        bytes(data) cases +=
    1 before =
        (delay.value, flags.value)assert
        not native.vertrix_mixer_pattern_delay(0xd0, 0, ctypes.byref(delay),
                                               ctypes.byref(flags)) and
        (delay.value,
         flags.value) == before assert not native
                             .vertrix_mixer_pattern_delay(0xe0, 0, None, ctypes.byref(flags)) assert
                         not native.vertrix_mixer_pattern_delay(0xe0, 0, ctypes.byref(delay),
                                                                None) report = {
            "status" : "passed",
            "effect_cases" : cases,
            "scope" :
                "Full original extended dispatcher selecting case 14. Exhaustive low nibbles/prior "
                "sequencer flags at ticks 0/1/-1, random pending delays, channel preservation. "
                "Excludes pending-delay consumption and full sequencing."
        }(build / "mixer-pattern-delay-verification.json")
                                                                                   .write_text(
                                                                                       json.dumps(
                                                                                           report,
                                                                                           indent =
                                                                                               2) +
                                                                                       "\n");
print(json.dumps(report, indent = 2)) if __name__ == "__main__" : main()
