""
    "Compare both original pitch-slide effects and retained effect memory."
    "" import argparse,
    ctypes, json, random, struct, subprocess from pathlib import Path from original import Original,
    BOARD class Slide(ctypes.Structure)
    : _fields_ =
          [
              ("base", ctypes.c_uint32), ("output", ctypes.c_uint32), ("amount", ctypes.c_uint32),
              ("flags", ctypes.c_uint8)
          ] def main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument("executable",
                                                                                  type = Path);
parser.add_argument("--build-dir", type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "slides.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "mixer.c"), "-o", str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
native.vertrix_mixer_pitch_slide.argtypes =
    [ ctypes.c_uint8, ctypes.c_int32, ctypes.c_int, ctypes.POINTER(Slide) ] original =
        Original(args.executable);
rng = random.Random(0x40cf50);cases=30000
    for increasing,address,memory in ((0,0x40CF50,88),(1,0x40CFA0,92)):
        for index in range(cases):
            parameter=index%256;tick=0 if index%3==0 else rng.randrange(-2147483648,2147483648)
            base,output,amount=[rng.randrange(2**32) for _ in range(3)];
flags = rng.randrange(256) if index < 10000 : base = rng.randrange(1, 32000);
amount = rng.randrange(1021) channel = bytearray(128);
channel[1] = flags;
channel[4] = parameter struct.pack_into("<II", channel, 36, base, output);
struct.pack_into("<I", channel, memory, amount) original.cpu.mem_write(BOARD, bytes(channel));
original.cpu.mem_write(0x531B4C, struct.pack("<i", tick));
original.call(address, eax = BOARD)
    expected = (*struct.unpack("<II", original.cpu.mem_read(BOARD + 36, 8)),
                struct.unpack("<I", original.cpu.mem_read(BOARD + memory, 4))[0],
                original.cpu.mem_read(BOARD + 1, 1)[0]) state =
    Slide(base, output, amount, flags) assert native.vertrix_mixer_pitch_slide(parameter, tick,
                                                                               increasing,
                                                                               ctypes.byref(state))
        assert(state.base, state.output, state.amount, state.flags) == expected,
    (increasing, index)assert not native.vertrix_mixer_pitch_slide(1, 0, 0, None) report =
        {
            "status" : "passed",
            "slide_cases" : cases * 2,
            "scope" : "Complete original 0x40cf50 and 0x40cfa0: tick-zero parameter "
                      "memory/preservation, subsequent application, signed clamps, wrapped "
                      "arithmetic, output period and dirty flags. Realistic and full-width random "
                      "states. Excludes sequencer effect dispatch and other slides."
        }(build / "mixer-slides-verification.json")
            .write_text(json.dumps(report, indent = 2) + "\n");
print(json.dumps(report, indent = 2)) if __name__ == "__main__" : main()
