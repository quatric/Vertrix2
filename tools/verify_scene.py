"""Verify original board update-tail ordering with captured leaf operations."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_ECX

class Scene(c.Structure):
    _fields_=[('slots',c.c_uint32*486),('active',c.c_uint32),('extra',c.c_uint32),('suppress_layout',c.c_uint32),('active_a',c.c_uint8),('active_b',c.c_uint8),('cell_a',c.c_uint8*65),('cell_b',c.c_uint8*65),('columns_a',c.c_uint8*5),('columns_b',c.c_uint8*5),('rows',(c.c_uint8*13)*4)]
Callback=c.CFUNCTYPE(None,c.c_uint32,c.c_uint32,c.c_uint32,c.c_void_p)
GROUPS=((0x220,65),(0x87c,65),(0x988,5),(0x9e8,13),(0xa2c,13),(0x324,260),(0xbdc,65))
OFFSETS=[base+i*4 for base,count in GROUPS for i in range(count)]

def main():
    p=argparse.ArgumentParser(description=__doc__);
p.add_argument('executable', type = Path);
p.add_argument('--build-dir', type = Path, required = True);
a = p.parse_args();
a.build_dir.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                            'source';
library =
    a.build_dir.resolve() / 'scene.dylib' subprocess.run(
                                [
                                    'cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared',
                                    '-fPIC', str(source / 'scene.c'), '-o', str(library)
                                ],
                                check = True) n = c.CDLL(str(library));
n.vertrix_scene_update.argtypes = [ c.POINTER(Scene), c.c_uint32, Callback, c.c_void_p ] o =
    Original(a.executable);
o.cpu.mem_map(0x900000, 0x10000);
o.cpu.mem_write(0x700100, b '\xc3');o.cpu.mem_write(0x708004,struct.pack('<I',0x700100))
    objects=[0x900000+i*512 for i in range(32)]
    for obj in objects:o.cpu.mem_write(obj+0x158,struct.pack('<I',0x708000))
    original_events=[];
native_events = [];
mutate = False;
original_mutated = False;
native_mutated = False;
scene = None def original_event(cpu, address, size, context)
    : nonlocal original_mutated obj = cpu.reg_read(UC_X86_REG_EAX);
operation =
    0 if address == 0x700100 else address value =
        cpu.reg_read(UC_X86_REG_EDX) if address in(
               0x42a960, 0x42a970) else 0 original_events.append((operation, obj,
                                                                  value)) if mutate and operation ==
        0 and not original_mutated : original_mutated =
            True cpu.mem_write(BOARD + OFFSETS[-1], struct.pack('<I', objects[-1]));
cpu.mem_write(BOARD + 0xb8c, bytes(4)) if address in(0x700100, 0x42a960, 0x42a970)
    : return stack = cpu.reg_read(UC_X86_REG_ESP);
target = struct.unpack('<I', cpu.mem_read(stack, 4))[0];
cpu.reg_write(UC_X86_REG_ESP, stack + 4);cpu.reg_write(UC_X86_REG_EIP,target)
    addresses=(0x700100,0x42a960,0x42a970,0x430930,0x4b6200,0x4b5f50)
    for addr in addresses:o.cpu.hook_add(UC_HOOK_CODE,original_event,begin=addr,end=addr)
    @Callback
    def native_event(operation,obj,value,context):
        nonlocal native_mutated
        native_events.append((operation,obj,value))
        if mutate and operation==0 and not native_mutated:
            native_mutated=True;
scene.slots[-1] = objects[-1];
scene.suppress_layout = 0 rng = random.Random(0x42fc56);events=0
    for case in range(512):
scene = Scene();raw=bytearray(0xd00)
        for index,offset in enumerate(OFFSETS):
            value=rng.choice([0]*5+objects);
scene.slots[index] = value;
struct.pack_into('<I', raw, offset, value) scene.active = rng.choice([0] + objects);
scene.extra = rng.choice([0] + objects);
scene.suppress_layout = rng.choice([ 0, 1, 2, 0xffffffff ]);
scene.active_a = rng.randrange(256);
scene.active_b = rng.randrange(256) struct.pack_into('<I', raw, 0xa60, scene.active);
raw[0xa64] = scene.active_a;
raw[0xa65] = scene.active_b;
struct.pack_into('<I', raw, 0xce0, scene.extra);struct.pack_into('<I',raw,0xb8c,scene.suppress_layout)
        for field,offset,size in [('cell_a',0x15c,65),('cell_b',0x19d,65),('columns_a',0x99c,5),('columns_b',0x9a1,5),('rows',0x9a6,52)]:
            flags=bytes(rng.randrange(256) for _ in range(size));
raw [offset:offset + size] = flags;
c.memmove(c.addressof(getattr(scene, field)), flags, size) o.cpu.mem_write(BOARD, bytes(raw));
original_events.clear();
native_events.clear();mutate=case%2==0;original_mutated=native_mutated=False
        o.cpu.reg_write(UC_X86_REG_ECX,BOARD);o.call(0x42fc56,ecx=BOARD,stop=0x42fd81)
        assert n.vertrix_scene_update(c.byref(scene),BOARD,native_event,None)
        assert original_events==native_events,(case,original_events[:10],native_events[:10])
        for field,offset,size in [('cell_a',0x15c,65),('cell_b',0x19d,65),('columns_a',0x99c,5),('columns_b',0x9a1,5),('rows',0x9a6,52)]:
            assert bytes(getattr(scene,field))==bytes(o.cpu.mem_read(BOARD+offset,size))==bytes(size),(case,field)
        assert scene.active_a==scene.active_b==0 and bytes(o.cpu.mem_read(BOARD+0xa64,2))==bytes(2)
        events+=len(original_events)
    assert not n.vertrix_scene_update(None,BOARD,native_event,None)
    assert not n.vertrix_scene_update(c.byref(scene),BOARD,Callback(),None)
    report={'status':'passed','cases':512,'compared_operations':events,'scope':'Original 0x42fc56..0x42fd81 board update-tail dispatch, including live collection mutations and layout gating. Original collection traversal and active-byte setters execute; all ten original reset methods execute normally and all 194 flag bytes are compared; virtual object updates and layout/list leaves are captured. Does not prove those leaf implementations, preceding descent/effects, or complete game scheduling.'}
    (a.build_dir/'scene-verification.json').write_text(json.dumps(report,indent=2)+'\n');
print(json.dumps(report, indent = 2)) if __name__ == '__main__' : main()
