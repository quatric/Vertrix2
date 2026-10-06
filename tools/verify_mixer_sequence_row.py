"""Compare original row/order/pattern decisions with zero channels."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, MASK, BLOCKS

NAMES = ('tick','row','rows','pattern','order','pending_order','pending_row')
OFFSETS = (8,12,16,20,24,44,48)
class State(ctypes.Structure):
    _fields_ = [(name,ctypes.c_uint32) for name in NAMES] + [('flags',ctypes.c_uint8)]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable',type=Path);
parser.add_argument('--build-dir', type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      'source';
library = build / 'sequence-row.dylib' subprocess.run(
                      [
                          'cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC',
                          str(source / 'mixer.c'), '-o', str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
function = native.vertrix_mixer_sequence_row function.argtypes = [
    ctypes.c_uint16, ctypes.c_uint16, ctypes.POINTER(ctypes.c_uint8), ctypes.c_size_t,
    ctypes.POINTER(ctypes.c_uint16), ctypes.c_uint16, ctypes.POINTER(State)
] original = Original(args.executable);
rng = random.Random(0x40e940); cases = 40000
    counts = [0,0,0,0]
    for index in range(cases):
        region = bytearray(rng.randbytes(64));
region[0] = index % 256;
struct.pack_into('<I', region, 4, 0) row = (rng.randrange(-20, 21) & 0xffffffff, 0xffffffff,
                                            0x7fffffff)[index % 3] rows = rng.randrange(0, 16);
order = rng.randrange(9); pending_order = rng.randrange(9)
        pending_row = rng.randrange(-20,21) & 0xffffffff
        for offset,value in ((12,row),(16,rows),(24,order),(44,pending_order),(48,pending_row)): struct.pack_into('<I',region,offset,value)
        song_length = rng.randrange(1,7); restart = rng.randrange(9)
        orders = (ctypes.c_uint8 * 9)(*[rng.randrange(5) for _ in range(9)])
        pattern_rows = (ctypes.c_uint16 * 2)(rng.randrange(16),rng.randrange(16))
        song = bytearray(344);
struct.pack_into('<HH', song, 34, song_length, restart);
struct.pack_into('<H', song, 40, 2) song [48:57] = bytes(orders); struct.pack_into('<I',song,336,BLOCKS)
        patterns = bytearray(24)
        for i in range(2):
            struct.pack_into('<H',patterns,i * 12 + 4,pattern_rows[i])
            struct.pack_into('<I',patterns,i * 12 + 8,0)
        state = State(*[struct.unpack_from('<I',region,o)[0] for o in OFFSETS],region[0])
        original.cpu.mem_write(0x531b44,bytes(region));
original.cpu.mem_write(MASK, bytes(song));
original.cpu.mem_write(BLOCKS, bytes(patterns)) original.cpu.mem_write(0x53043c,
                                                                       struct.pack('<I', MASK));
original.cpu.mem_write(0x530440, struct.pack('<I', 0x809000)) original.call(0x40e940) result =
    function(song_length, restart, orders, 9, pattern_rows, 2, ctypes.byref(state));
assert result >= 0, index counts[result] += 1 actual = bytearray(region); actual[0] = state.flags
        for name,offset in zip(NAMES,OFFSETS): struct.pack_into('<I',actual,offset,getattr(state,name))
        assert bytes(actual) == bytes(original.cpu.mem_read(0x531b44,64)),index
        assert struct.unpack('<I',original.cpu.mem_read(0x530440,4))[0] == (0 if result == 2 else 0x809000),index
    state.flags = 1;
state.pending_order = 0;
before = bytes(state) assert function(1, 0, None, 0, pattern_rows, 2, ctypes.byref(state)) == -1 and
         bytes(state) == before assert function(1, 0, orders, 9, pattern_rows, 2, None) ==
             -1 assert all(counts) report = {
    'status' : 'passed',
    'row_decision_cases' : cases,
    'result_counts' : counts,
    'scope' :
        'Complete original 0x40e940 with zero channels, whole sequencer state and packed-pointer changes. Covers delay, row boundary, jump/break precedence, restarts, invalid-pattern fallback and signed row values. Excludes nonzero-channel packed skipping/row initialization.'
}(build / 'mixer-sequence-row-verification.json')
                                                .write_text(json.dumps(report, indent = 2) + '\n');
print(json.dumps(report, indent = 2)) if __name__ == '__main__' : main()
