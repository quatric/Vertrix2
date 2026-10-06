"""Compare complete original object value helpers with the native recovery."""
import ctypes as c, random, struct
from original import Original
from unicorn.x86_const import UC_X86_REG_EAX
import verify_support as vs

OBJ, DEST = vs.SCRATCH, vs.SCRATCH + 0x2000
SIZE = 0x300


def main():
    args = vs.parse(__doc__, 8192)
    n = vs.build(args, 'object-value-helpers', ['object_value_helpers.c'])
    U8P, U = c.POINTER(c.c_uint8), c.c_uint32
    n.vertrix_format_decimal.argtypes = [c.c_int32, c.c_uint8, c.c_char_p]
    n.vertrix_format_decimal.restype = c.c_size_t
    n.vertrix_object_fill_ramp.argtypes = [U8P, c.c_size_t]
    n.vertrix_object_remaining.argtypes = [U8P, c.c_size_t]
    n.vertrix_object_clamp_position.argtypes = [U8P, c.c_size_t, c.c_int32, c.c_int32]
    n.vertrix_pixel_pack.argtypes = [c.c_uint8, U, U8P]
    n.vertrix_pixel_pack.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4776a0)
    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    def object_case(name, address, setup, native, **registers):
        data = bytearray(rng.randbytes(SIZE))
        setup(data)
        cpu.mem_write(OBJ, bytes(data))
        original.call(address, eax=OBJ, **registers)
        result = cpu.reg_read(UC_X86_REG_EAX)
        buf = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
        got = native(buf)
        assert bytes(buf) == bytes(cpu.mem_read(OBJ, SIZE)), (name, data[:0x50].hex())
        if got is not None:
            assert got == result, (name, got, result)
        count(name)

    for case in range(args.cases):
        value = rng.choice([0, 1, -1, rng.getrandbits(32) - (1 << 31), rng.randrange(-100000, 100000),
                            -(1 << 31), (1 << 31) - 1, rng.randrange(0, 1000)])
        width = rng.choice([0, 1, 2, 3, 5, 8, 10, 11, 12, rng.getrandbits(8)])
        cpu.mem_write(DEST, b'\xaa' * 32)
        original.call(0x4776a0, eax=value & 0xffffffff, edx=DEST, ebx=width | rng.getrandbits(24) << 8)
        out = c.create_string_buffer(b'\xaa' * 32, 32)
        length = n.vertrix_format_decimal(value, width, c.cast(out, c.c_char_p))
        assert out.raw == bytes(cpu.mem_read(DEST, 32)), (value, width)
        assert length == cpu.reg_read(UC_X86_REG_EAX), (value, width)
        count('0x4776a0')

        def ramp_setup(data):
            struct.pack_into('<H', data, 0x26, rng.choice([0, 1, 2, 3, 7, 24, 100, rng.randrange(0x1d0)]))
        object_case('0x478b70', 0x478b70, ramp_setup, lambda b: (n.vertrix_object_fill_ramp(b, SIZE), None)[1])

        def remaining_setup(data):
            struct.pack_into('<I', data, 0x14, rng.choice([0, 5, 100, rng.getrandbits(32)]))
            struct.pack_into('<I', data, 4, rng.choice([0, 1, 5, 20, rng.getrandbits(32)]))
            data[0xc] = rng.choice([0, 1, 5, rng.getrandbits(8)])
            if rng.random() < 0.4:
                struct.pack_into('<I', data, 0x14, (struct.unpack_from('<I', data, 4)[0] * data[0xc]) & 0xffffffff)
        object_case('0x478da0', 0x478da0, remaining_setup, lambda b: n.vertrix_object_remaining(b, SIZE))
        x = rng.choice([rng.randrange(-100, 700), rng.getrandbits(32) - (1 << 31)])
        y = rng.choice([rng.randrange(-100, 700), rng.getrandbits(32) - (1 << 31)])

        def clamp_setup(data):
            for offset in (0x3c, 0x3e, 0x40, 0x42):
                struct.pack_into('<H', data, offset, rng.choice([0, 10, 100, 300, rng.getrandbits(16) & 0x3ff]))
        object_case('0x478480', 0x478480, clamp_setup,
                    lambda b: (n.vertrix_object_clamp_position(b, SIZE, x, y), None)[1],
                    edx=x & 0xffffffff, ebx=y & 0xffffffff)
        fmt = rng.choice([0, 1, 2, 3, rng.getrandbits(8)])
        rgb = rng.getrandbits(32)
        cpu.mem_write(OBJ + 0xd, bytes([fmt]))
        cpu.mem_write(0x558a50, b'\x55')
        original.call(0x479a40, eax=OBJ, edx=rgb)
        stored = c.c_uint8(0x55)
        got = n.vertrix_pixel_pack(fmt, rgb, c.byref(stored))
        assert got == cpu.reg_read(UC_X86_REG_EAX) and stored.value == bytes(cpu.mem_read(0x558a50, 1))[0], (fmt, rgb)
        count('0x479a40')
    vs.write_report(args, 'object-value-helpers', {
        'status': 'passed', 'complete_original_executions': totals,
        'scope': 'Complete 4776a0, 478b70, 478da0, 478480 and 479a40 execute in the original; '
                 'text buffer and length, whole 768-byte objects, results and the pixel format '
                 'global compare. Decimal cases include INT_MIN, zero, negative values and every '
                 'width class.'})


if __name__ == '__main__':
    main()
