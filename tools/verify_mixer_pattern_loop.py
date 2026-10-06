""
    "Compare original extended pattern-loop counters and pending changes."
    "" import argparse,
    ctypes, json, random, struct, subprocess from pathlib import Path from original import Original,
    BOARD from verify_mixer_pattern_change import State as Change class Loop(ctypes.Structure)
    : _fields_ = [ ("start", ctypes.c_uint32), ("remaining", ctypes.c_uint32) ] def main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument("executable",
                                                                                  type = Path);
parser.add_argument("--build-dir", type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "pattern-loop.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "mixer.c"), "-o", str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
native.vertrix_mixer_pattern_loop.argtypes = [
    ctypes.c_uint8, ctypes.c_int32, ctypes.c_uint32, ctypes.c_uint32, ctypes.POINTER(Loop),
    ctypes.POINTER(Change)
] original = Original(args.executable);
rng = random.Random(0x40d66a);cases=30000
    for index in range(cases):
        parameter=0x60|(index%16);tick=0 if index%2==0 else rng.randrange(-2147483648,2147483648)
        start,remaining,order,row,pending_order,pending_row=[rng.randrange(2**32) for _ in range(6)]
        if index<10000:remaining=index%17
        flags=rng.randrange(256);
data = bytearray(rng.randbytes(192));
data[4] = parameter;
struct.pack_into("<II", data, 172, start, remaining) original.cpu.mem_write(BOARD, bytes(data));
original.cpu.mem_write(0x531B4C, struct.pack("<i", tick));
original.cpu.mem_write(0x531B50, struct.pack("<I", row));
original.cpu.mem_write(0x531B5C, struct.pack("<I", order));
original.cpu.mem_write(0x531B70, struct.pack("<II", pending_order, pending_row));
original.cpu.mem_write(0x531B44, bytes([flags]));
original.call(0x40D540, eax = BOARD) expected = bytes(original.cpu.mem_read(BOARD, 192));
expected_change = (*struct.unpack("<II", original.cpu.mem_read(0x531B70, 8)),
                   original.cpu.mem_read(0x531B44, 1)[0])loop = Loop(start, remaining);
change = Change(pending_order, pending_row, flags) assert
             native.vertrix_mixer_pattern_loop(parameter, tick, order, row, ctypes.byref(loop),
                                               ctypes.byref(change)) actual = bytearray(data);
struct.pack_into("<II", actual, 172, loop.start, loop.remaining) assert bytes(actual) == expected
    and (change.order, change.row, change.flags) == expected_change,
    index assert not native
        .vertrix_mixer_pattern_loop(0x50, 0, 0, 0, ctypes.byref(loop), ctypes.byref(change)) assert
    not native
        .vertrix_mixer_pattern_loop(0x60, 0, 0, 0, None, ctypes.byref(change)) assert
    not native.vertrix_mixer_pattern_loop(0x60, 0, 0, 0, ctypes.byref(loop), None)
        report = {
        "status" : "passed",
        "effect_cases" : cases,
        "scope" : "Full original extended dispatcher selecting pattern-loop case 6, all low "
                  "nibbles, zero/nonzero signed ticks, realistic/full-width counters, "
                  "saved/current row and order, pending change flags. Whole channel and pending "
                  "change comparison. Excludes sequencer consumption."
    }(build / "mixer-pattern-loop-verification.json")
                     .write_text(json.dumps(report, indent = 2) + "\n");
print(json.dumps(report, indent = 2)) if __name__ == "__main__" : main()
