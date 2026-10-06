"""Compare complete original volume-column effect dispatch."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD

NAMES = ('base_volume','output_volume','pan','base_period','output_period','portamento_speed',
         'portamento_target','vibrato_phase','vibrato_depth','vibrato_speed')
OFFSETS = (16,20,28,36,40,96,100,64,68,72)
class State(ctypes.Structure):
    _fields_ = [(name,ctypes.c_uint32) for name in NAMES] + [('waveform',ctypes.c_uint8),('flags',ctypes.c_uint8)]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable',type=Path);
parser.add_argument('--build-dir', type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      'source';
library = build / 'volume-column.dylib' subprocess.run(
                      [
                          'cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC',
                          str(source / 'mixer.c'), '-o', str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
function = native.vertrix_mixer_volume_column function.argtypes =
    [ ctypes.c_uint8, ctypes.c_uint8, ctypes.c_int32, ctypes.POINTER(State) ] original =
        Original(args.executable);
rng = random.Random(0x40dc80); cases = 60000
    for index in range(cases):
        data = bytearray(rng.randbytes(192));
command = index % 256; data[2] = command
        tick = (0,1,-1,rng.randrange(-2147483648,2147483648))[(index // 256) % 4]
        if index % 3 == 0:
            struct.pack_into('<II',data,16,rng.randrange(65),rng.randrange(65))
            struct.pack_into('<I',data,28,rng.randrange(256))
            struct.pack_into('<II',data,36,rng.randrange(1,0x7d00),rng.randrange(1,0x7d00))
        state = State(*[struct.unpack_from('<I',data,o)[0] for o in OFFSETS],data[60],data[1])
        original.cpu.mem_write(BOARD,bytes(data)); original.cpu.mem_write(0x531b4c,struct.pack('<i',tick))
        original.call(0x40dc80,eax=BOARD)
        assert function(command,data[4],tick,ctypes.byref(state))
        actual = bytearray(data)
        for name,offset in zip(NAMES,OFFSETS): struct.pack_into('<I',actual,offset,getattr(state,name))
        actual[60] = state.waveform; actual[1] = state.flags
        assert bytes(actual) == bytes(original.cpu.mem_read(BOARD,192)),(index,command,tick)
    assert not function(0,0,0,None)
    report = {'status':'passed','volume_column_cases':cases,
        'scope':'Complete original 0x40dc80, all 256 command bytes at zero/nonzero signed ticks, whole channel comparison including delegated vibrato and portamento. Realistic and full-width values cover clamps and wrapping. Excludes main effect dispatch and sequencing.'}
    (build / 'mixer-volume-column-verification.json').write_text(json.dumps(report,indent=2) + '\n'); print(json.dumps(report,indent=2))
if __name__ == '__main__': main()
