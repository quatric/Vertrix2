"""Compare complete original board layout with resolved sprite dimensions."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD
from verify_scene import Scene, OFFSETS
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ESP, UC_X86_REG_EIP


class Object(c.Structure):
    _fields_ = [('x', c.c_int16), ('y', c.c_int16), ('mode', c.c_uint8), ('width', c.c_int32), ('height', c.c_int32)]

Resolver = c.CFUNCTYPE(c.c_void_p, c.c_uint32, c.c_void_p)


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    lib = a.build_dir.resolve() / 'layout.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', str(source / 'scene.c'), '-o', str(lib)], check=True)
    n = c.CDLL(str(lib))
    n.vertrix_scene_layout.argtypes = [c.POINTER(Scene), c.c_int16, c.c_int16, Resolver, c.c_void_p]
    o = Original(a.executable)
    o.cpu.mem_map(0x900000, 0x10000)
    objects = {0x900000 + i * 512: Object() for i in range(64)}
    @ Resolver
    def resolve(handle, context):
        return c.addressof(objects[handle]) if handle in objects else None
    def measure(cpu, address, size, context):
        obj = objects[cpu.reg_read(UC_X86_REG_EAX)]
        cpu.mem_write(cpu.reg_read(UC_X86_REG_EDX), struct.pack('<i', obj.width))
        cpu.mem_write(cpu.reg_read(UC_X86_REG_EBX), struct.pack('<i', obj.height))
        stack = cpu.reg_read(UC_X86_REG_ESP)
        target = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
        cpu.reg_write(UC_X86_REG_ESP, stack + 4)
        cpu.reg_write(UC_X86_REG_EIP, target)
    o.cpu.hook_add(UC_HOOK_CODE, measure, begin=0x4b14c0, end=0x4b14c0)
    rng = random.Random(0x430930)
    comparisons = 0
    for case in range(512):
        scene = Scene()
        raw = bytearray(0xd00)
        ox = rng.randrange(- 32768, 32768)
        oy = rng.randrange(- 32768, 32768)
        struct.pack_into('<h', raw, 14, ox)
        struct.pack_into('<h', raw, 22, oy)
        for field, offset, size in [('cell_a', 0x15c, 65), ('cell_b', 0x19d, 65), ('columns_a', 0x99c, 5), ('columns_b', 0x9a1, 5), ('rows', 0x9a6, 52)]:
            flags = bytes(rng.randrange(256) for _ in range(size))
            raw[offset: offset + size] = flags
            c.memmove(c.addressof(getattr(scene, field)), flags, size)
        for index, offset in enumerate(OFFSETS):
            handle = rng.choice([0] * 16 + list(objects))
            scene.slots[index] = handle
            struct.pack_into('<I', raw, offset, handle)
        for handle, obj in objects.items():
            obj.x = rng.randrange(- 32768, 32768)
            obj.y = rng.randrange(- 32768, 32768)
            obj.mode = rng.randrange(17)
            obj.width = rng.randrange(- 32768, 32768)
            obj.height = rng.randrange(- 32768, 32768)
            data = bytearray(512)
            struct.pack_into('<h', data, 14, obj.x)
            struct.pack_into('<h', data, 22, obj.y)
            data[0x44] = obj.mode
            o.cpu.mem_write(handle, bytes(data))
        o.cpu.mem_write(BOARD, bytes(raw))
        o.call(0x430930, eax=BOARD)
        assert n.vertrix_scene_layout(c.byref(scene), ox, oy, resolve, None)
        for handle, obj in objects.items():
            x = struct.unpack('<h', o.cpu.mem_read(handle + 14, 2))[0]
            y = struct.unpack('<h', o.cpu.mem_read(handle + 22, 2))[0]
            assert (obj.x, obj.y) == (x, y), (case, hex(handle), (obj.x, obj.y), (x, y))
            comparisons += 1
            assert not n.vertrix_scene_layout(None, 0, 0, resolve, None)
            assert not n.vertrix_scene_layout(c.byref(scene), 0, 0, Resolver(), None)
            scene = Scene()
            scene.slots[0] = 0xffffffff
            assert not n.vertrix_scene_layout(c.byref(scene), 0, 0, resolve, None)
    report = {'status': 'passed', 'cases': 512, 'object_comparisons': comparisons, 'scope': 'Complete original 0x430930 with only resource dimension helper intercepted. Both cell collections, incoming columns/rows, quadrant positions, null/aliased handles, signed-byte offsets, signed-word wrap, mode 16 bypass and unsigned centering arithmetic. Resource measurement separately verified; renderer integration and full game remain unfinished.'}
    (a.build_dir / 'scene-layout-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
