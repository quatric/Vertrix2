"""Compare original XM instrument metadata normalization and empty-header carry."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK, STACK
from unicorn.x86_const import UC_X86_REG_EBP
class Point(ctypes.Structure):
    _fields_ = [('tick',ctypes.c_uint16),('value',ctypes.c_uint16)]
class Envelope(ctypes.Structure):
    _fields_ = [('points',Point*12)] + [(n,ctypes.c_uint8) for n in ('count','sustain','start','end','flags')]
class Instrument(ctypes.Structure):
    _fields_ = [('name',ctypes.c_char*23),('mapping',ctypes.c_uint8*96),('samples',ctypes.c_uint16)] + [(n,ctypes.c_uint8) for n in ('waveform','sweep','depth','rate')] + [('fade',ctypes.c_uint16),('volume',Envelope),('pan',Envelope)]
def encode(instrument):
    data = bytearray(252);
data[:22] = bytes(instrument) [:22];
data [32:128] = bytes(instrument.mapping) struct.pack_into('<H', data, 128, instrument.samples);
data [130:134] = bytes((instrument.waveform, instrument.sweep, instrument.depth, instrument.rate)); struct.pack_into('<H',data,134,instrument.fade)
    for offset,meta,env in ((136,184,instrument.volume),(192,240,instrument.pan)):
        for point in range(env.count): struct.pack_into('<HH',data,offset+point*4,env.points[point].tick,env.points[point].value)
        data[meta:meta+5] = bytes((env.count,env.sustain,env.start,env.end,env.flags))
    return bytes(data)
def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable',type=Path);
parser.add_argument('--build-dir', type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      'source'; library = build / 'instrument-header.dylib'
    subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror','-shared','-fPIC',*[str(source/n) for n in ('xm.c','vf.c','audio.c')],'-o',str(library)],check=True)
    native = ctypes.CDLL(str(library));
native.vertrix_xm_instrument_header.argtypes = [
    ctypes.c_void_p, ctypes.c_size_t, ctypes.POINTER(Instrument), ctypes.POINTER(Instrument)
] original = Original(args.executable);
rng = random.Random(0x4117e0);
carry = Instrument();
scratch = bytearray(243);
cases = 20000; empty = 0
    frame = STACK+512
    for index in range(cases):
        count = index % 17;
length = 263 if count else 29;
header = bytearray(rng.randbytes(length));
struct.pack_into('<I', header, 0, length);
struct.pack_into('<H', header, 27, count) if count : scratch[:] = header[:243] else
    : scratch
      [:29] = header;
empty += 1 original.cpu.mem_write(0x5326d1, bytes(scratch));
original.cpu.mem_write(BOARD, bytes(252));
original.cpu.mem_write(frame - 16, struct.pack('<I', BOARD));
original.cpu.mem_write(frame - 24, struct.pack('<I', MASK)) original.cpu.reg_write(UC_X86_REG_EBP,
                                                                                   frame);
original.call(0x4117e0, stop = 0x411a00) raw = (ctypes.c_uint8 * length).from_buffer_copy(header);
loaded = Instrument() assert
             native.vertrix_xm_instrument_header(raw, length, ctypes.byref(carry),
                                                 ctypes.byref(loaded)) actual = encode(loaded); expected = bytes(original.cpu.mem_read(BOARD,252))
        assert actual == expected,(index,[(i,a,b) for i,(a,b) in enumerate(zip(actual,expected)) if a != b])
        scratch[:] = original.cpu.mem_read(0x5326d1,243);
carry = loaded invalid = (ctypes.c_uint8 * 29)();
before = bytes(carry) assert not native.vertrix_xm_instrument_header(invalid, 29, None,
                                                                     ctypes.byref(carry)) and
         bytes(carry) == before report = {
    'status' : 'passed',
    'instrument_headers' : cases,
    'empty_headers_with_carry' : empty,
    'scope' :
        'Original 0x4117e0..0x411a00 metadata conversion with the actual bounded name-copy routine, whole zero-initialized 252-byte instrument records. Counts 0..16, clamped envelope counts, bounded note maps, flag masks, LE points, vibrato/fade fields and loader-scratch carry on empty instruments. Invalid native header preserves output. Excludes VF traversal and sample allocation/loading.'
}(build / 'xm-instrument-header-verification.json')
                                             .write_text(json.dumps(report, indent = 2) + '\n');
print(json.dumps(report, indent = 2)) if __name__ == '__main__' : main()
