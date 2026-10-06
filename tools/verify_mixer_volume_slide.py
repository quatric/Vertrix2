""
    "Compare complete original volume slide and parameter memory."
    "" import argparse,
    ctypes, json, random, struct, subprocess from pathlib import Path from original import Original,
    BOARD class State(ctypes.Structure)
    : _fields_ =
          [
              ("base", ctypes.c_uint32), ("output", ctypes.c_uint32), ("memory", ctypes.c_uint8),
              ("flags", ctypes.c_uint8)
          ] def main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument("executable",
                                                                                  type = Path);
parser.add_argument("--build-dir", type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "volume-slide.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "mixer.c"), "-o", str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
native.vertrix_mixer_volume_slide.argtypes =
    [ ctypes.c_uint8, ctypes.c_int32, ctypes.POINTER(State) ] original = Original(args.executable);rng=random.Random(0x40d250)
    fixtures=[(parameter,tick,base,parameter) for parameter in range(256) for tick in (0,1) for base in range(65)]
    fixtures += [(rng.randrange(256),rng.randrange(-2147483648,2147483648),rng.randrange(2**32),rng.randrange(256)) for _ in range(20000)]
    for index,(parameter,tick,base,memory) in enumerate(fixtures):
        output=rng.randrange(2**32);
flags = rng.randrange(256) channel = bytearray(128);
channel[1] = flags;
channel[4] = parameter;
channel[104] = memory;
struct.pack_into("<II", channel, 16, base, output) original.cpu.mem_write(BOARD, bytes(channel));
original.cpu.mem_write(0x531B4C, struct.pack("<i", tick));
original.call(0x40D250, eax = BOARD)
    expected = (*struct.unpack("<II", original.cpu.mem_read(BOARD + 16, 8)),
                original.cpu.mem_read(BOARD + 104, 1)[0],
                original.cpu.mem_read(BOARD + 1, 1)[0]) state =
    State(base, output, memory, flags) assert native.vertrix_mixer_volume_slide(parameter, tick,
                                                                                ctypes.byref(state))
        assert(state.base, state.output, state.memory, state.flags) == expected,
    index assert not native.vertrix_mixer_volume_slide(1, 0, None) report =
        {
            "status" : "passed",
            "effect_cases" : len(fixtures),
            "scope" : "Complete original 0x40d250: all volume 0..64/parameter pairs at tick zero "
                      "and one, plus 20000 random full-width states. Upper-nibble precedence, "
                      "signed clamping, parameter memory and dirty flags match. Excludes combined "
                      "effects and sequencer dispatch."
        }(build / "mixer-volume-slide-verification.json")
            .write_text(json.dumps(report, indent = 2) + "\n");
print(json.dumps(report, indent = 2)) if __name__ == "__main__" : main()
