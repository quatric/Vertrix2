"""Compare complete original sample attachment and preserved mixer fields."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, MASK, BLOCKS
from verify_mixer_channel import Channel, Cursor

Pointer = ctypes.POINTER(ctypes.c_uint8)
class Binding(ctypes.Structure):
    _fields_ = [('samples',Pointer)] + [(name,ctypes.c_uint32) for name in ('count','start','end')] + [('flags',ctypes.c_uint8)]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable',type=Path);
parser.add_argument('--build-dir', type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      'source';
library = build / 'attach.dylib' subprocess.run(
                      [
                          'cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC',
                          str(source / 'mixer.c'), '-o', str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
function = native.vertrix_mixer_attach function.argtypes =
    [ ctypes.POINTER(Binding), ctypes.POINTER(Channel), ctypes.POINTER(Pointer) ] original =
        Original(args.executable);
rng = random.Random(0x40c9d0);
cases = 30000 original.cpu.mem_write(0x52fc18, struct.pack('<I', 1)); storage = (ctypes.c_uint8 * 1)(0)
    for index in range(cases):
        data = bytearray(rng.randbytes(24));
descriptor = bytearray(rng.randbytes(24)) present = index % 3 != 0;
valid_source = index % 5 != 0 struct.pack_into('<I', descriptor, 4, BLOCKS if valid_source else 0);
descriptor[22] = index % 256 count, start,
    end = struct.unpack_from('<III', descriptor, 8) sample =
        Binding(ctypes.cast(storage, Pointer) if valid_source else None, count, start, end,
                descriptor[22]) old_pointer,
    position, step, old_start,
    old_end = struct.unpack_from('<5I', data) state =
        Channel(Cursor(position, old_start, old_end, data[22]), step, data[20], data[21], data[23])
            bound = Pointer();
original.cpu.mem_write(0x52f918, bytes(data));
original.cpu.mem_write(MASK, bytes(descriptor)) result =
    original.call(0x40c9d0, eax = 0, edx = MASK if present else 0) assert
    function(ctypes.byref(sample) if present else None, ctypes.byref(state),
             ctypes.byref(bound)) == result pointer = BLOCKS if present and valid_source
    else old_pointer actual = bytearray(data);
struct.pack_into('<5I', actual, 0, pointer, state.cursor.position, state.step, state.cursor.start,
                 state.cursor.end) actual
    [20:24] = bytes((state.volume, state.pan, state.cursor.flags, state.last)) assert
              bytes(actual) == bytes(original.cpu.mem_read(0x52f918, 24)),
    index assert(ctypes.cast(bound, ctypes.c_void_p).value == ctypes.addressof(storage)) if result
        ==
        0 else not bound before = bytes(state) assert function(ctypes.byref(sample),
                                                               ctypes.byref(state), None) == 1 and
                                  bytes(state) ==
                                      before assert
                                      function(ctypes.byref(sample), None, ctypes.byref(bound)) ==
                                      1 report = {
        'status' : 'passed',
        'attachment_cases' : cases,
        'scope' :
            'Complete original 0x40c9d0, null descriptor/source rejection and whole channel comparisons with all sample flag bytes and arbitrary counts/loop geometry; verifies source binding and preservation of step/volume/pan/cache. Excludes buffer lifetime, slot indexing and publication integration.'
    }(build / 'mixer-attach-verification.json')
                                                     .write_text(json.dumps(report, indent = 2) +
                                                                 '\n');
print(json.dumps(report, indent = 2)) if __name__ == '__main__' : main()
