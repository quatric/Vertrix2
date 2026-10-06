"""Compare complete main retrigger, volume transform and sample selection."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK, BLOCKS
from verify_mixer_sample_selection import Pitch, State as Selection
from verify_mixer_timed_trigger import Instrument

class State(ctypes.Structure):
    _fields_ = [(name,ctypes.c_uint32) for name in ('base','output','pan')] + [
        (name,ctypes.c_uint8) for name in ('transform','interval','counter')]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable',type=Path);
parser.add_argument('--build-dir', type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      'source';
library = build / 'retrigger.dylib' subprocess.run(
                      [
                          'cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC',
                          str(source / 'mixer.c'), '-o', str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
function = native.vertrix_mixer_retrigger function.argtypes = [
    ctypes.c_uint8, ctypes.c_int32, ctypes.POINTER(Instrument), ctypes.c_int,
    ctypes.POINTER(Selection), ctypes.POINTER(State)
] original = Original(args.executable);
rng = random.Random(0x40da20); cases = 40000
    assert bytes(original.cpu.mem_read(0x4f7324,16)) == bytes((0,255,254,252,248,240,0,0,0,1,2,4,8,16,0,0))
    assert bytes(original.cpu.mem_read(0x4f7334,16)) == bytes((16,16,16,16,16,16,11,8,16,16,16,16,16,16,24,32))
    for index in range(cases):
        data = bytearray(rng.randbytes(192));
descriptor = bytearray(rng.randbytes(252)); samples = rng.randbytes(16 * 60)
        mapping = (ctypes.c_uint8 * 96)(*[rng.randrange(21) for _ in range(96)])
        pitches = (Pitch * 16)(*[Pitch(*struct.unpack_from('<bb',samples,i * 60 + 34)) for i in range(16)])
        descriptor[32:128] = bytes(mapping);
struct.pack_into('<H', descriptor, 128, 16);
struct.pack_into('<I', descriptor, 248, BLOCKS) present = index % 2; linear = (index // 256) % 2; parameter = index % 256
        data[3] = 27; data[4] = parameter; data[7] = rng.randrange(256)
        data[110] = (index // 3) % 16; data[111] = rng.randrange(256)
        data[112] = (0,255,data[111],rng.randrange(256))[index % 4]
        if index % 3 == 0: struct.pack_into('<II',data,16,rng.randrange(65),rng.randrange(65))
        struct.pack_into('<I',data,52,MASK if present else 0)
        old = rng.randrange(16); struct.pack_into('<I',data,56,BLOCKS + old * 60)
        tick = (0,1,-1,rng.randrange(-2147483648,2147483648))[(index // 512) % 4]
        selected = Selection(old,struct.unpack_from('<i',data,12)[0],struct.unpack_from('<i',data,8)[0],*struct.unpack_from('<II',data,36),data[7],data[0],data[6],data[3],data[2],data[1])
        state = State(*struct.unpack_from('<II',data,16),struct.unpack_from('<I',data,28)[0],data[110],data[111],data[112])
        instrument = Instrument(mapping,pitches,16,0,0,0,0,0)
        original.cpu.mem_write(BOARD,bytes(data)); original.cpu.mem_write(MASK,bytes(descriptor)); original.cpu.mem_write(BLOCKS,samples)
        original.cpu.mem_write(0x531b46,bytes([linear])); original.cpu.mem_write(0x531b4c,struct.pack('<i',tick)); original.call(0x40dc50,eax=BOARD)
        assert function(parameter,tick,ctypes.byref(instrument) if present else None,linear,ctypes.byref(selected),ctypes.byref(state))
        actual = bytearray(data); actual[0] = selected.active; actual[1] = selected.flags; actual[6] = selected.mapping
        struct.pack_into('<ii',actual,8,selected.finetune,selected.relative); struct.pack_into('<II',actual,36,selected.base,selected.output)
        struct.pack_into('<I',actual,56,0 if selected.selected == 0xffffffff else BLOCKS + selected.selected * 60)
        struct.pack_into('<II',actual,16,state.base,state.output); struct.pack_into('<I',actual,28,state.pan)
        actual[110:113] = bytes((state.transform,state.interval,state.counter))
        assert bytes(actual) == bytes(original.cpu.mem_read(BOARD,192)),index
    state.transform = 16; state.interval = 0; before = bytes(state),bytes(selected)
    assert not function(0,1,None,0,ctypes.byref(selected),ctypes.byref(state)) and (bytes(state),bytes(selected)) == before
    report = {'status':'passed','retrigger_cases':cases,
        'scope':'Complete original main dispatcher effect 27 with real sample selection, whole channel comparisons, exact executable volume tables, nibble memories, byte counter wrapping, volume-column overrides, signed arithmetic/clamps and envelope preservation. Excludes scheduling and remaining dispatch integration.'}
    (build / 'mixer-retrigger-verification.json').write_text(json.dumps(report,indent=2) + '\n'); print(json.dumps(report,indent=2))
if __name__ == '__main__': main()
