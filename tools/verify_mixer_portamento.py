""
    "Compare full original target-note slide, including first-tick flags."
    "" import argparse,
    ctypes, json, random, struct, subprocess from pathlib import Path from original import Original,
    BOARD class State(ctypes.Structure)
    : _fields_ =
          [
              ("base", ctypes.c_uint32), ("output", ctypes.c_uint32), ("speed", ctypes.c_uint32),
              ("target", ctypes.c_uint32), ("flags", ctypes.c_uint8)
          ] def main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument("executable",
                                                                                  type = Path);
parser.add_argument("--build-dir", type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "portamento.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "mixer.c"), "-o", str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
native.vertrix_mixer_portamento.argtypes = [
    ctypes.c_uint8, ctypes.c_int32, ctypes.c_uint8, ctypes.c_int32, ctypes.c_int32, ctypes.c_int,
    ctypes.POINTER(State)
] original = Original(args.executable);
rng = random.Random(0x40cff0);cases=40000
    for index in range(cases):
        parameter=index%256;
tick = 0 if index % 3 == 0 else rng.randrange(-2147483648, 2147483648) note = rng.randrange(256);
relative = rng.randrange(-96, 97);
tune = rng.randrange(-128, 128);linear=index%2
        base,output,speed,target=[rng.randrange(2**32) for _ in range(4)];
flags = rng.randrange(256) if index < 10000 : base = rng.randrange(1, 32000);
target = rng.randrange(1, 32000);
speed = rng.randrange(1021) if index % 7 == 0 : target = base channel = bytearray(128);
channel[1] = flags;
channel[4] = parameter;
channel[7] = note struct.pack_into("<ii", channel, 8, tune, relative);
struct.pack_into("<II", channel, 36, base, output);
struct.pack_into("<II", channel, 96, speed, target) original.cpu.mem_write(BOARD, bytes(channel));
original.cpu.mem_write(0x531B4C, struct.pack("<i", tick));
original.cpu.mem_write(0x531B46, bytes([linear]));
original.call(0x40CFF0, eax = BOARD)
    expected = (*struct.unpack("<II", original.cpu.mem_read(BOARD + 36, 8)),
                *struct.unpack("<II", original.cpu.mem_read(BOARD + 96, 8)),
                original.cpu.mem_read(BOARD + 1, 1)[0]) state =
    State(base, output, speed, target,
          flags) assert native.vertrix_mixer_portamento(parameter, tick, note, relative, tune,
                                                        linear, ctypes.byref(state))
        assert(state.base, state.output, state.speed, state.target, state.flags) == expected,
    index assert not native.vertrix_mixer_portamento(1, 0, 48, 0, 0, 1, None) report =
        {
            "status" : "passed",
            "effect_cases" : cases,
            "scope" : "Complete original 0x40cff0: first-tick speed memory and target generation, "
                      "cleared flags, later signed comparisons and wrapping movement, target "
                      "clamps, output and flags. Both tuning modes, realistic/full-width states "
                      "and exact-target cases. Excludes sequencer dispatch."
        }(build / "mixer-portamento-verification.json")
            .write_text(json.dumps(report, indent = 2) + "\n");
print(json.dumps(report, indent = 2)) if __name__ == "__main__" : main()
