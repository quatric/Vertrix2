"""Compare the complete original surface bounding box scan with the native recovery."""
import ctypes as c, random, struct
from original import Original
from unicorn.x86_const import UC_X86_REG_EAX
import verify_support as vs

OBJ, DATA, OUT, DATA_SIZE = vs.SCRATCH, vs.SCRATCH + 0x1000, vs.SCRATCH + 0x800, 0x2000


class Surface(c.Structure):
    _fields_ = [('data', c.c_void_p), ('size', c.c_size_t), ('width', c.c_uint32),
                ('height', c.c_uint32), ('stride', c.c_uint32), ('bytes_per_pixel', c.c_uint8)]


class Bounds(c.Structure):
    _fields_ = [('x', c.c_int32), ('y', c.c_int32), ('width', c.c_int32), ('height', c.c_int32)]


def main():
    args = vs.parse(__doc__, 4096)
    n = vs.build(args, 'surface-bounds', ['surface_bounds.c', 'surface.c', 'render_dispatch.c'])
    n.vertrix_surface_bounds.argtypes = [c.POINTER(Surface), c.POINTER(Bounds), c.POINTER(c.c_uint32)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4792d0)
    totals = {}
    for case in range(args.cases):
        width, height = rng.choice([0, 1, 2, 5, 12, 20]), rng.choice([0, 1, 3, 7, 16])
        bpp = rng.choice([1, 2, 3, 4, 4, 0])
        stride = width * bpp + rng.choice([0, 0, 4])
        density = rng.choice([0.0, 0.02, 0.2, 1.0])
        mode = rng.choice(['random', 'last_column', 'first_column'])
        content = bytearray(DATA_SIZE)
        for y in range(height):
            for x in range(width):
                if mode == 'last_column' and x != width - 1 and x != 0 and rng.random() < 0.8:
                    continue
                if mode == 'first_column' and x != 0:
                    continue
                if rng.random() < density:
                    offset = y * stride + x * max(bpp, 1)
                    content[offset:offset + 4] = rng.randbytes(4)
        obj = bytearray(rng.randbytes(0x40))
        struct.pack_into('<III', obj, 0, DATA, width, height)
        obj[0xc] = bpp
        struct.pack_into('<I', obj, 0x14, stride)
        cpu.mem_write(OBJ, bytes(obj))
        cpu.mem_write(DATA, bytes(content))
        cpu.mem_write(OUT, rng.randbytes(16))
        original.call(0x4792d0, eax=OBJ, edx=OUT, ebx=OUT + 4, ecx=OUT + 8, args=(OUT + 12,))
        result = cpu.reg_read(UC_X86_REG_EAX)
        want = struct.unpack('<iiii', bytes(cpu.mem_read(OUT, 16)))
        buf = (c.c_uint8 * DATA_SIZE).from_buffer_copy(bytes(content))
        surface = Surface(c.cast(buf, c.c_void_p), DATA_SIZE, width, height, stride, bpp)
        bounds, differs = Bounds(), c.c_uint32(7)
        assert n.vertrix_surface_bounds(c.byref(surface), c.byref(bounds), c.byref(differs)), case
        assert (bounds.x, bounds.y, bounds.width, bounds.height) == want, (case, want, width, height, bpp, mode)
        assert differs.value == result, (case, result)
        key = 'last_column_images' if mode == 'last_column' else 'other_images'
        totals[key] = totals.get(key, 0) + 1
    vs.write_report(args, 'surface-bounds', {
        'status':
        'passed', 'complete_original_executions' : totals,
                                                   'scope'
            : 'Complete 4792d0 executes in the original over 1, 2, 3 and 4 byte (and zero) ' 'pixel surfaces of 0 to 20 columns and 0 to 16 rows with empty, sparse, dense, ' 'first-column and last-column images; all four output dwords and the result ' 'compare, including the empty/last-column whole-image quirk.'
        })


if __name__ == '__main__':
    main()
