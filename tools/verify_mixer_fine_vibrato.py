""
    "Compare complete original fine vibrato waveform/state arithmetic."
    "" import argparse,
    ctypes, json, random, struct, subprocess from pathlib import Path from original import Original,
    BOARD class State(ctypes.Structure)
    : _fields_ =
          [
              ("base", ctypes.c_uint32), ("output", ctypes.c_uint32), ("phase", ctypes.c_uint32),
              ("depth", ctypes.c_uint32), ("speed", ctypes.c_uint32), ("wave", ctypes.c_uint8),
              ("flags", ctypes.c_uint8)
          ] def main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument("executable",
                                                                                  type = Path);
parser.add_argument("--build-dir", type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "vibrato.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "mixer.c"), "-o", str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
native.vertrix_mixer_fine_vibrato.argtypes =
    [ ctypes.c_uint8, ctypes.c_int32, ctypes.POINTER(State) ] original = Original(args.executable);
rng = random.Random(0x40d170);cases=40000
    for index in range(cases):
        parameter=index%256;tick=0 if index%3==0 else rng.randrange(-2147483648,2147483648)
        base,output,phase,depth,speed=[rng.randrange(2**32) for _ in range(5)];
wave = index % 256;
flags = rng.randrange(256) if index < 10000 : base = rng.randrange(1, 32000);
phase = index % 256;
depth = rng.randrange(16);
speed = rng.randrange(16) * 4 channel = bytearray(128);
channel[1] = flags;
channel[4] = parameter;
channel[60] = wave struct.pack_into("<II", channel, 36, base, output);
struct.pack_into("<III", channel, 64, phase, depth, speed) original.cpu.mem_write(BOARD,
                                                                                  bytes(channel));
original.cpu.mem_write(0x531B4C, struct.pack("<i", tick));
original.call(0x40D170, eax = BOARD)
    expected = (*struct.unpack("<II", original.cpu.mem_read(BOARD + 36, 8)),
                *struct.unpack("<III", original.cpu.mem_read(BOARD + 64, 12)),
                original.cpu.mem_read(BOARD + 60, 1)[0],
                original.cpu.mem_read(BOARD + 1, 1)[0]) state =
    State(base, output, phase, depth, speed, wave,
          flags) assert native.vertrix_mixer_fine_vibrato(parameter, tick, ctypes.byref(state))
        assert(state.base, state.output, state.phase, state.depth, state.speed, state.wave,
               state.flags) == expected,
    index assert not native.vertrix_mixer_fine_vibrato(1, 0, None) report =
        {
            "status" : "passed",
            "effect_cases" : cases,
            "scope" :
                "Complete original 0x40d170: all waveform selectors/phase bytes, tick-zero nibble "
                "memory, signed clamps and wrapped multiply/phase arithmetic, realistic and "
                "full-width states. Excludes other vibrato variants and full effect dispatch."
        }(build / "mixer-fine-vibrato-verification.json")
            .write_text(json.dumps(report, indent = 2) + "\n");
print(json.dumps(report, indent = 2)) if __name__ == "__main__" : main()
