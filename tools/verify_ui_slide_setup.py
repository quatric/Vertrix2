"""Compare complete original UI slide setup routines with the native recovery."""
import ctypes as c, random, struct
from original import Original
import verify_support as vs

OBJ, DESC, SCREEN = vs.SCRATCH, vs.SCRATCH + 0x400, vs.SCRATCH + 0x800
SIZE = 0x100


class Dimensions(c.Structure):
    _fields_ = [('width', c.c_uint16), ('height', c.c_uint16)]


def main():
    args = vs.parse(__doc__)
    n = vs.build(args, 'ui-slide-setup', ['ui_slide_setup.c', 'render_geometry.c', 'surface.c', 'render_dispatch.c'])
    U8P, U = c.POINTER(c.c_uint8), c.c_uint32
    n.vertrix_ui_slide_from_below.argtypes = [U8P, c.c_size_t]
    n.vertrix_ui_slide_from_above.argtypes = [U8P, c.c_size_t]
    n.vertrix_ui_slide_sideways.argtypes = [U8P, c.c_size_t, U, c.c_int32, c.c_int32, c.c_uint16]
    n.vertrix_ui_center_on_anchor.argtypes = [U8P, c.c_size_t, c.POINTER(Dimensions), c.c_uint8,
                                              c.c_uint8]
    original = Original(args.executable)
    cpu = original.cpu
    original.call(0x4b9050)
    rng = random.Random(0x4717f0)
    totals = {}
    for case in range(args.cases):
        data = bytearray(rng.randbytes(SIZE))
        cpu.mem_write(OBJ, bytes(data))

        def native(call):
            buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
            result = call(buffer)
            return bytes(buffer), result

        descriptor = None

        def check(name, expected_call):
            got, result = native(expected_call)
            assert result == 1, (case, name)
            want = bytes(cpu.mem_read(OBJ, SIZE))
            assert got == want, (case, name, [(hex(i), got[i], want[i]) for i in range(SIZE) if got[i] != want[i]], bytes(data[0x44:0x45]), data[0x91], descriptor)
            totals[name] = totals.get(name, 0) + 1

        original.call(0x4717f0, eax=OBJ)
        check('0x4717f0', lambda b: n.vertrix_ui_slide_from_below(b, SIZE))
        cpu.mem_write(OBJ, bytes(data))
        original.call(0x4719a0, eax=OBJ)
        check('0x4719a0', lambda b: n.vertrix_ui_slide_from_above(b, SIZE))
        cpu.mem_write(OBJ, bytes(data))
        mode = rng.choice([0, 1, 1, 2, rng.getrandbits(32)])
        distance = rng.getrandbits(32)
        offset = rng.getrandbits(32)
        width = rng.getrandbits(16)
        cpu.mem_write(0x5b9c8e, struct.pack('<H', width))
        original.call(0x471820, eax=OBJ, edx=mode, ebx=distance, args=(offset, rng.getrandbits(32)))
        check('0x471820', lambda b: n.vertrix_ui_slide_sideways(
            b, SIZE, mode, struct.unpack('<i', struct.pack('<I', distance))[0],
            struct.unpack('<i', struct.pack('<I', offset))[0], width))
        cpu.mem_write(OBJ, bytes(data))
# 0x457890 : resource measurement with and without a descriptor.
        with_descriptor = rng.random() < 0.5
        mode_byte = rng.randrange(17)
        data[0x44] = mode_byte
        data[0x91] = rng.choice([0, 1])
        for offset_ in (0xf4, 0xf8):
            struct.pack_into('<H', data, offset_, rng.choice([0, 1, 7, 16, 24, rng.getrandbits(16) & 0x1ff]))
        descriptor = None
        if with_descriptor:
            dims = (rng.choice([0, 3, 24, rng.getrandbits(16) & 0x1ff]),
                    rng.choice([0, 5, 24, rng.getrandbits(16) & 0x1ff]))
            struct.pack_into('<I', data, 0xb4, DESC)
            cpu.mem_write(DESC, bytes(rng.randbytes(0x40)))
            cpu.mem_write(DESC + 4, struct.pack('<H', dims[0]))
            cpu.mem_write(DESC + 8, struct.pack('<H', dims[1]))
            descriptor = Dimensions(*dims)
        else:
            struct.pack_into('<I', data, 0xb4, 0)
        unscaled, screen_mode = rng.choice([0, 1]), rng.randrange(17)
        cpu.mem_write(SCREEN, bytes(0x300))
        cpu.mem_write(SCREEN + 0x220, bytes([unscaled, screen_mode]))
        cpu.mem_write(0x544070, struct.pack('<I', SCREEN))
        cpu.mem_write(OBJ, bytes(data))
        original.call(0x457890, eax=OBJ)
        check('0x457890', lambda b: n.vertrix_ui_center_on_anchor(
            b, SIZE, c.byref(descriptor) if descriptor else None, unscaled, screen_mode))
    vs.write_report(args, 'ui-slide-setup', {
        'status': 'passed', 'complete_original_executions': totals,
        'scope': 'Complete 4717f0, 4719a0, 471820 and 457890 (including the real 4b14c0 '
                 'measurement with and without a descriptor) execute in the original; the whole '
                 '256-byte actor storage compares after every call.'})


if __name__ == '__main__':
    main()
