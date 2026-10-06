"""Compare complete complete rotating block handler."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK
from verify_animation import Animation
from verify_timer import Timer
from verify_rotation import Trace
from verify_rotation_tables import Tables


fields=[('x',c.c_int16,14,'h'),('y',c.c_int16,22,'h'),('angle',c.c_int16,36,'h'),('rotation_step',c.c_int16,40,'h'),('radius',c.c_int16,42,'h'),('center_x',c.c_int16,44,'h'),('center_y',c.c_int16,46,'h'),('rotation_target',c.c_int16,48,'h'),('rotation_change',c.c_int16,50,'h'),('mode',c.c_uint8,68,'B'),('amount',c.c_uint8,78,'B'),('amount_target',c.c_uint8,79,'B'),('amount_step',c.c_int16,80,'h'),('field_93',c.c_uint8,147,'B'),('handler',c.c_uint32,340,'I')]
class Orbit(c.Structure):
    _fields_=[('timer',Timer),('rotation_timer',Timer)]+[(name,typ) for name,typ,offset,fmt in fields]
class Context(c.Structure):
    _fields_=[('tables',c.POINTER(Tables)),('width',c.c_uint16),('height',c.c_uint16),('screen_override',c.c_uint8),('screen_unscaled',c.c_uint8),('screen_mode',c.c_uint8)]

def main():
    p=argparse.ArgumentParser(description=__doc__);
p.add_argument('executable', type = Path);
p.add_argument('--build-dir', type = Path, required = True);
a = p.parse_args();
a.build_dir.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                            'source';
lib = a.build_dir.resolve() / 'block.dylib';subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror','-shared','-fPIC',*[str(source/name) for name in ('block_spin.c','block_update.c','animation.c','timer.c','rotation.c','rotation_tables.c','vf.c','byte_transition.c','word_transition.c','dword_transition.c','render_geometry.c','surface.c','render_dispatch.c')],'-o',str(lib)],check=True)
    n=c.CDLL(str(lib));
n.vertrix_block_spin_update.argtypes = [
    c.POINTER(Animation), c.POINTER(c.c_uint32), c.c_size_t, c.c_uint32, c.POINTER(c.c_uint32),
    c.POINTER(Orbit), c.POINTER(Trace), c.POINTER(Context)
] o = Original(a.executable);
rng = random.Random(0x44de20);
linked = 0 o.call(0x4b9050) assets = Path(a.executable).resolve().parent.parent /
                                     'assets/table' sine = (assets / 'sin.tab').read_bytes();
cosine = (assets / 'cos.tab').read_bytes() tables =
    Tables((c.c_int32 * 360)(*struct.unpack('<360i', sine)),
           (c.c_int32 * 360)(*struct.unpack('<360i', cosine)), 1) o.cpu.mem_write(0x598dfc, sine);o.cpu.mem_write(0x59939c,cosine)
    def node(address,count,kind,frames=0,children=0,indices=0):o.cpu.mem_write(address,struct.pack('<6I',frames,count,0,children,indices,kind))
    for case in range(4096):
count = rng.randrange(1, 65);ids=[rng.getrandbits(32) for _ in range(64)];mapping=[rng.randrange(64) for _ in range(count)];second=[rng.randrange(64) for _ in range(64)];
depth = case % 3 o.cpu.mem_write(0x803000, struct.pack('<64I', *ids));
    node(0x802000, 64, 0, frames = 0x803000) if depth:
o.cpu.mem_write(0x803400,
                struct.pack('<' + 'I' * count, *([0x802100 if depth == 2 else 0x802000] * count)));
o.cpu.mem_write(0x803800, struct.pack('<' + 'I' * count, *mapping));
node(MASK, count, 1, children = 0x803400, indices = 0x803800) if depth == 2
    : o.cpu.mem_write(0x803a00, struct.pack('<64I', *([0x802000] * 64)));
o.cpu.mem_write(0x803c00, struct.pack('<64I', *second));node(0x802100,64,1,children=0x803a00,indices=0x803c00)
            resolved=[ids[second[index] if depth==2 else index] for index in mapping];
linked += 1 else : node(MASK, count, rng.choice([ 0, 2, 16, 0xffffffff ]), frames = 0x803000);
resolved = ids[:count] period = rng.randrange(65);
counter = rng.randrange(129) * (period or 1);
elapsed = rng.randrange(129) * (period or 1);
frame = rng.randrange(count);
animation = Animation(Timer(counter, period), frame, count);
frames = (c.c_uint32 * count)(*resolved);
descriptor = c.c_uint32(rng.getrandbits(32));
raw = bytearray(rng.randbytes(
    0x160)) struct.pack_into('<2I', raw, 0xbc, rng.randrange(65),
                             rng.randrange(17)) struct.pack_into('<h', raw, 0x24,
                                                                 rng.randrange(360));
struct.pack_into('<2h', raw, 0x28, rng.choice([ 0, -15, 1, 15 ]), rng.randrange(101));
struct.pack_into('<2h', raw, 0x30, rng.randrange(101), rng.randrange(9));
struct.pack_into('<2I', raw, 0xdc, rng.randrange(65),
                 rng.randrange(17)) raw[0x44] = rng.randrange(17);
raw[0x91] = rng.randrange(2) struct.pack_into('<I', raw, 0x154,
                                              0x44ece0 if case % 2 == 0 else 0x44ee20) if case < 64:
            elapsed=0
            struct.pack_into('<2I',raw,0xbc,0,1)
            struct.pack_into('<2I',raw,0xdc,0,1)
            struct.pack_into('<h',raw,0x2a,10)
            struct.pack_into('<h',raw,0x30,10)
            raw[0x4e]=100 if case%2 else 0
        context=Context(c.pointer(tables),rng.randrange(65536),rng.randrange(65536),raw[0x91],rng.randrange(2),rng.randrange(17))
        o.cpu.mem_write(0x805000,struct.pack('<3I',0,context.width,context.height)+bytes(28))
        descriptor.value=0x805000
        o.cpu.mem_write(0x544070,struct.pack('<I',0x809000));o.cpu.mem_write(0x809220,bytes([context.screen_unscaled,context.screen_mode]))
        state=Orbit(Timer(*struct.unpack_from('<2I',raw,0xbc)),Timer(*struct.unpack_from('<2I',raw,0xdc)),*[struct.unpack_from('<'+fmt,raw,offset)[0] for name,typ,offset,fmt in fields])
        trace=Trace(rng.getrandbits(32),rng.getrandbits(32))
        o.cpu.mem_write(0x5bb5f8,struct.pack('<I',trace.iterations));o.cpu.mem_write(0x5bb5f4,struct.pack('<I',trace.unwrapped))
        struct.pack_into('<3I',raw,0xb0,MASK,descriptor.value,frame);struct.pack_into('<2I',raw,0xcc,counter,period);o.cpu.mem_write(BOARD,bytes(raw));o.cpu.mem_write(0x5bd834,struct.pack('<I',elapsed));o.call(state.handler,eax=BOARD)
        assert n.vertrix_block_spin_update(c.byref(animation),frames,count,elapsed,c.byref(descriptor),c.byref(state),c.byref(trace),c.byref(context))
        if case<64:
            assert state.handler == 0x44c860 and state.field_93 == (0 if case % 2 else 1) expected =
                bytearray(raw);
            struct.pack_into('<I', expected, 0xbc, state.timer.counter);
            struct.pack_into('<I', expected, 0xdc, state.rotation_timer.counter);
        for
            name, typ, offset,
                fmt in fields
                : struct.pack_into('<' + fmt, expected, offset,
                                   getattr(state, name)) struct.pack_into('<I', expected, 0xb4,
                                                                          descriptor.value);
        struct.pack_into('<I', expected, 0xb8, animation.frame);struct.pack_into('<I',expected,0xcc,animation.timer.counter)
        assert bytes(expected)==bytes(o.cpu.mem_read(BOARD,len(raw))),(case,[(hex(i),a,b) for i,(a,b) in enumerate(zip(expected,o.cpu.mem_read(BOARD,len(raw)))) if a!=b])
        assert (trace.iterations,trace.unwrapped)==(struct.unpack('<I',o.cpu.mem_read(0x5bb5f8,4))[0],struct.unpack('<I',o.cpu.mem_read(0x5bb5f4,4))[0])
    prior=bytes(animation),descriptor.value
    assert not n.vertrix_block_spin_update(c.byref(animation),frames,count-1,16,c.byref(descriptor),c.byref(state),c.byref(trace),c.byref(context)) and (bytes(animation),descriptor.value)==prior
    assert not n.vertrix_block_spin_update(None,frames,count,16,c.byref(descriptor),c.byref(state),c.byref(trace),c.byref(context))
    report={'status':'passed','cases':4096,'zero_cycle_completions':64,'linked_resources':linked,'scope':'Actual complete original 0x44ece0/0x44ee20 including independent timers, radius transition, angle, original table coordinates, fade, scale, measurement and frame binding, with no routine hooks. Whole block state matches direct and one/two-level linked resource tables. Native receives independently resolved descriptor order; does not implement resource graph construction, actual VF actor binding or complete object runtime/game.'}
    (a.build_dir/'block-spin-verification.json').write_text(json.dumps(report,indent=2)+'\n');
        print(json.dumps(report, indent = 2)) if __name__ == '__main__' : main()
