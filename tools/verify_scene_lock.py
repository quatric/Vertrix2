""
    "Compare original locking with real block handles and object fields."
    "" import argparse,
    ctypes as c, json, random, struct,
    subprocess from pathlib import Path from original import Original,
    BOARD from verify_scene import Scene from verify_scene_frame import Object as FrameObject
        from verify_scene_layout import Resolver from verify_object_list import Visit from unicorn
            import UC_HOOK_CODE from unicorn.x86_const import UC_X86_REG_EAX,
    UC_X86_REG_EDX class Object(c.Structure)
    : _fields_ = FrameObject._fields_ +
                 [ ('field_93', c.c_uint8), ('field_4e', c.c_uint8),
                   ('effect', c.c_uint16) ] class Piece(c.Structure)
    : _fields_ =
                     [
                         ('handle', c.c_uint32), ('children', c.c_uint32 * 3), ('x', c.c_int16),
                         ('y', c.c_int16)
                     ]

      def main()
    : p = argparse.ArgumentParser(description = __doc__);
p.add_argument('executable', type = Path);
p.add_argument('--build-dir', type = Path, required = True);
a = p.parse_args();
a.build_dir.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                            'source';
lib = a.build_dir.resolve() / 'lock.dylib';
subprocess.run(
    [
        'cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC',
        str(source / 'scene_lock.c'), str(source / 'board.c'), '-o', str(lib)
    ],
    check = True) n = c.CDLL(str(lib));
n.vertrix_scene_lock.argtypes = [
    c.POINTER(Scene), c.POINTER(Piece), c.c_int16, c.c_int16, Resolver, Visit, c.c_void_p,
    c.POINTER(c.c_int)
] o = Original(a.executable);
o.cpu.mem_map(0x900000, 0x10000);
o.cpu.mem_write(0x700100, b '\xc3');
o.cpu.mem_write(0x709000, struct.pack('<I', 0x700100));
piece_handle = 0x900000;
children = [ 0x900200, 0x900400, 0x900600 ];objects={h:Object() for h in children};
piece = None;
original_events = [];
native_events = [] @Resolver def resolve(handle, context)
    : return c
          .addressof(objects[handle]) if handle in objects else None
      @Visit def visit(handle, destroy, context)
    : native_events
          .append((handle, destroy, tuple(piece.children)))
              def original_visit(cpu, address, size, context)
    : original_events
          .append((cpu.reg_read(UC_X86_REG_EAX), cpu.reg_read(UC_X86_REG_EDX),
                   struct.unpack('<3I', cpu.mem_read(piece_handle + 0x15c, 12))))
              o.cpu.hook_add(UC_HOOK_CODE, original_visit, begin = 0x700100, end = 0x700100)
                  rng = random.Random(0x431c60);destructions=transfers=failed=0
    for case in range(4096):
scene = Scene();
scene.active = piece_handle;
ox = rng.randrange(-30000, 30001);
oy = rng.randrange(-30000, 30001);
col = rng.randrange(5);
top = rng.randrange(-8, 17);
x = ox + col * 24 + rng.randrange(24);
y = oy + top * 24 + rng.randrange(24) piece =
        Piece(piece_handle, (c.c_uint32 * 3)(*children), x, y);
raw = bytearray(0xd00);
struct.pack_into('<h', raw, 14, ox);
struct.pack_into('<h', raw, 22, oy);struct.pack_into('<I',raw,0xa60,piece_handle)
        for i in range(65):scene.slots[i]=rng.choice([0,0x900800]);struct.pack_into('<I',raw,0x220+i*4,scene.slots[i])
        initial=[]
        for handle,obj in objects.items():
            data=bytearray(rng.randbytes(512));
obj.field_93 = data[0x93];
obj.field_4e = data[0x4e];
obj.effect = struct.unpack_from('<H', data, 0x48)[0];
struct.pack_into('<I', data, 0x158, 0x709000);
initial.append(bytes(data));
o.cpu.mem_write(handle, bytes(data)) record = bytearray(512);
struct.pack_into('<h', record, 14, x);
struct.pack_into('<h', record, 22, y);
struct.pack_into('<I', record, 0x158, 0x709000);
struct.pack_into('<3I', record, 0x15c, *children);
o.cpu.mem_write(piece_handle, bytes(record));
o.cpu.mem_write(BOARD, bytes(raw));
original_events.clear();
native_events.clear();
expected = o.call(0x431c60, eax = BOARD);locked=c.c_int(-1)
        assert n.vertrix_scene_lock(c.byref(scene),c.byref(piece),ox,oy,resolve,visit,None,c.byref(locked))
        assert locked.value==expected and scene.active==0,(case,'result')
        assert native_events==original_events,(case,'destruction/ownership')
        assert tuple(piece.children)==struct.unpack('<3I',o.cpu.mem_read(piece_handle+0x15c,12))
        assert list(scene.slots[:65])==list(struct.unpack('<65I',o.cpu.mem_read(BOARD+0x220,260)))
        for index,(handle,obj) in enumerate(objects.items()):
            data=bytearray(initial[index]);
data[0x93] = obj.field_93;
data[0x4e] = obj.field_4e;
struct.pack_into('<H', data, 0x48, obj.effect);
assert bytes(data) == bytes(o.cpu.mem_read(handle, 512)),
    (case, hex(handle), 'block metadata')destructions += len(native_events);transfers+=sum(h in scene.slots[:65] for h in children);
failed += not locked.value assert not n.vertrix_scene_lock(None, c.byref(piece), 0, 0, resolve,
                                                           visit, None, c.byref(locked))
                  report = {
    'status' : 'passed',
    'cases' : 4096,
    'transferred_blocks' : transfers,
    'destructor_calls' : destructions,
    'failed_lock_results' : failed,
    'scope' :
        'Complete original 0x431c60 including original coordinate conversion and block metadata writes; only virtual destructors captured. Cell handles, ownership observed at each destructor, child clearing, active clearing, lock result and whole block records match. Actual object destructors, surrounding descent/scene composition and complete game remain unfinished.'
}(a.build_dir / 'scene-lock-verification.json')
                               .write_text(json.dumps(report, indent = 2) + '\n');
print(json.dumps(report, indent = 2)) if __name__ == '__main__' : main()
