""
    "Compare original mixer start/stop/offset/frequency/volume/pan setters."
    "" import argparse,
    ctypes, json, random, struct,
    subprocess from pathlib import Path from original import Original from verify_mixer_channel
        import Channel,
    Cursor

        def
        main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument('executable',
                                                                                  type = Path);
parser.add_argument('--build-dir', type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      'source';
library = build / 'command.dylib' subprocess.run(
                      [
                          'cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC',
                          str(source / 'mixer.c'), '-o', str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
function = native.vertrix_mixer_command function.argtypes =
    [ ctypes.c_uint8, ctypes.c_uint32, ctypes.c_uint32, ctypes.POINTER(Channel) ] original =
        Original(args.executable);
rng = random.Random(0x40ca70); cases = 15000
    original.cpu.mem_write(0x52fc18, struct.pack('<I', 1))
    for kind, address in ((6,0x40ca70),(2,0x40caa0),(1,0x40cad0),(3,0x40cb10),(4,0x40cb70),(5,0x40cbb0)):
        for index in range(cases):
            data = bytearray(rng.randbytes(24));
pointer, position, step, start,
    end = struct.unpack_from('<5I', data) if kind == 1 and index % 3 == 0 : end =
              rng.randrange(1, 0x80000000) struct.pack_into('<I', data, 16, end) value =
                  rng.getrandbits(32) if index % 2
    : value = rng.randrange({1 : 0x100000, 3 : 524800, 4 : 70, 5 : 270}.get(kind, 256)) if kind ==
              1 and index % 5 == 0 : value =
                  end >> 12 rate = rng.randrange(1, 0x100000000) state =
                      Channel(Cursor(position, start, end, data[22]), step, data[20], data[21],
                              data[23]) original.cpu.mem_write(0x52f918, bytes(data));
original.cpu.mem_write(0x52fc20, struct.pack('<I', rate))
    expected_result = original.call(address, eax = 0, edx = value) assert
                      function(kind, value, rate, ctypes.byref(state)) == expected_result,
    (kind, index)actual = bytearray(data);
struct.pack_into('<5I', actual, 0, pointer, state.cursor.position, state.step, state.cursor.start,
                 state.cursor.end) actual
    [20:24] = bytes((state.volume, state.pan, state.cursor.flags, state.last)) assert
              bytes(actual) == bytes(original.cpu.mem_read(0x52f918, 24)),
    (kind, index)
        before =
            bytes(state) assert function(0, 0, 48000, ctypes.byref(state)) == 2 and
            bytes(state) == before assert function(3, 512, 0, ctypes.byref(state)) == 2 and
            bytes(state) == before assert function(6, 0, 48000, None) == 1 report =
                {
                    'status' : 'passed',
                    'setter_cases' : cases * 6,
                    'scope' :
                        'Complete original non-attachment setters 0x40ca70/0x40caa0/0x40cad0/0x40cb10/0x40cb70/0x40cbb0, exact return values and whole mixer channel comparisons. Covers valid/invalid values, wrapping, bounds and unrelated fields. Native zero-rate rejection avoids original divide fault. Excludes sample attachment and slot indexing.'
                }(build / 'mixer-command-verification.json')
                    .write_text(json.dumps(report, indent = 2) + '\n')
                        print(json.dumps(report, indent = 2)) if __name__
                == '__main__' : main()
