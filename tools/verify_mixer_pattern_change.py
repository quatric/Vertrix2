""
    "Compare original order jump and row break state transitions."
    "" import argparse,
    ctypes, json, random, struct, subprocess from pathlib import Path from original import Original,
    BOARD,
    MASK class State(ctypes.Structure)
    : _fields_ =
          [ ("order", ctypes.c_uint32), ("row", ctypes.c_uint32), ("flags", ctypes.c_uint8) ] def
      main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument("executable",
                                                                                  type = Path);
parser.add_argument("--build-dir", type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "pattern-change.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "mixer.c"), "-o", str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
native.vertrix_mixer_pattern_change.argtypes = [
    ctypes.c_uint8, ctypes.c_int32, ctypes.c_int, ctypes.c_uint16, ctypes.POINTER(State)
] original = Original(args.executable);
rng = random.Random(0x40d450);cases=30000
    original.cpu.mem_write(0x53043C,struct.pack("<I",MASK))
    for row_break,address in ((0,0x40D450),(1,0x40D4C0)):
        for index in range(cases):
            parameter=index%256;tick=0 if index%2==0 else rng.randrange(-2147483648,2147483648)
            length=(0,1,128,255,256,65535)[index%6] if index<10000 else rng.randrange(65536)
            order,row=[rng.randrange(2**32) for _ in range(2)];
flags = rng.randrange(256) original.cpu.mem_write(BOARD + 4, bytes([parameter]));
original.cpu.mem_write(MASK + 34,
                       struct.pack("<H", length)) original.cpu.mem_write(0x531B4C,
                                                                         struct.pack("<i", tick));
original.cpu.mem_write(0x531B70, struct.pack("<II", order, row));
original.cpu.mem_write(0x531B44, bytes([flags])) original.call(address, eax = BOARD)
    expected = (*struct.unpack("<II", original.cpu.mem_read(0x531B70, 8)),
                original.cpu.mem_read(0x531B44, 1)[0])state =
    State(order, row, flags) assert native.vertrix_mixer_pattern_change(parameter, tick, row_break,
                                                                        length, ctypes.byref(state))
        assert(state.order, state.row, state.flags) == expected,
    (row_break, index)assert not native.vertrix_mixer_pattern_change(1, 0, 0, 128, None) report =
        {
            "status" : "passed",
            "effect_cases" :
                    cases * 2,
            "scope" :
                "Complete original 0x40d450/0x40d4c0: all parameter bytes, song-length limits, "
                "zero/nonzero signed ticks, prior order/row/flags. Includes decimal-invalid "
                "nibbles in row breaks. Excludes consumption of pending changes by sequencer."
        }(build / "mixer-pattern-change-verification.json")
            .write_text(json.dumps(report, indent = 2) + "\n");
print(json.dumps(report, indent = 2)) if __name__ == "__main__" : main()
