"""Compare the complete original bit reader with the native recovery."""
import ctypes as c, random, struct
from original import Original
import verify_common_a as common
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX
Copy = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_uint32, c.c_void_p)
U = c.c_uint32


class Reader(c.Structure):
    _fields_ = [('address', U), ('bit', U)]


def main():
    args = common.parse(__doc__)
    n = common.build(args, 'bit-reader', 'bit_reader.c')
    n.vertrix_bit_reader_next.argtypes = [c.POINTER(Reader), c.c_uint8]
    n.vertrix_bit_reader_next.restype = U
    B = c.POINTER(c.c_uint8)
    n.vertrix_bit_reader_bits24.argtypes = [c.POINTER(Reader), U, B]
    n.vertrix_bit_reader_bits24.restype = U
    n.vertrix_bit_reader_bits16.argtypes = n.vertrix_bit_reader_bits24.argtypes
    n.vertrix_bit_reader_bits16.restype = U
    n.vertrix_bit_reader_unread.argtypes = [c.POINTER(Reader), U, U, c.c_int32, U, Copy, c.c_void_p]
    n.vertrix_bit_reader_unread.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4046e0)
    copies, native_copies = [], []
    common.stub(cpu, 0x4eb5e0, lambda uc: copies.append(tuple(uc.reg_read(r) for r in (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX))))
    @ Copy
    def copy(destination, source, count, context):
        native_copies.append((destination, source, count))
    totals = {'next': 0, 'bits24': 0, 'bits16': 0, 'unread': 0}
    for case in range(args.cases):
#Positions 0..7 occur in use; wider values exercise the shift and carry arithmetic.
        bit = rng.choice([rng.randrange(8)] * 4 + [rng.randrange(40), rng.getrandbits(32), rng.getrandbits(8) | 0xff00])
        address = rng.choice([0x806000 + rng.randrange(0x100), 0x806080])
        cpu.mem_write(0x806000, rng.randbytes(0x200))
        cpu.mem_write(0x51f014, struct.pack('<2I', address, bit))
        byte = cpu.mem_read(address, 1)[0]
        reader = Reader(address, bit)
        want = original.call(0x4046e0)
        got = n.vertrix_bit_reader_next(c.byref(reader), byte)
        assert want & 0xffffffff == got, case
        assert struct.unpack('<2I', cpu.mem_read(0x51f014, 8)) == (reader.address, reader.bit), case
        totals['next'] += 1
        for name, address, width in (('bits24', 0x404610, 3), ('bits16', 0x404680, 2)):
            amount = rng.choice([rng.randrange(0, 25)] * 3 + [rng.randrange(0, 40), rng.getrandbits(32)])
            if width == 2 and amount > 16 and rng.random() < 0.7:
                amount %= 17
            bit = rng.choice([rng.randrange(8)] * 3 + [rng.randrange(40), rng.getrandbits(32)])
            address_in = 0x806000 + rng.randrange(0x100)
            cpu.mem_write(0x51f014, struct.pack('<2I', address_in, bit))
            data = bytes(cpu.mem_read(address_in, 3))
            reader = Reader(address_in, bit)
            want = original.call(address, eax=amount) & 0xffffffff
            got = getattr(n, 'vertrix_bit_reader_' + name)(c.byref(reader), amount, (c.c_uint8 * 3).from_buffer_copy(data))
            assert want == got, (case, name, amount, bit)
            assert struct.unpack('<2I', cpu.mem_read(0x51f014, 8)) == (reader.address, reader.bit), (case, name)
            totals[name] += 1
        stream = 0x808000
        filled = rng.choice([rng.randrange(- 4, 100), rng.getrandbits(32) - (1 << 31), 0, - 1])
        index = rng.choice([rng.randrange(0, 16), rng.getrandbits(32)])
        cpu.mem_write(stream + 0x10, struct.pack('<i', filled))
        cpu.mem_write(stream + 0x3668, struct.pack('<I', index))
        cpu.mem_write(0x51f01c, struct.pack('<I', stream))
        amount = rng.choice([0, rng.randrange(0, 40), rng.getrandbits(32), 0xffffffff])
        address_in, bit = rng.getrandbits(32), rng.choice([rng.randrange(8), rng.getrandbits(32)])
        cpu.mem_write(0x51f014, struct.pack('<2I', address_in, bit))
        copies.clear()
        native_copies.clear()
        reader = Reader(address_in, bit)
        want = original.call(0x4060e0, eax=amount) & 0xffffffff
        got = n.vertrix_bit_reader_unread(c.byref(reader), amount, stream, filled, index, copy, None)
        assert want == got and copies == native_copies, (case, amount, filled)
        assert struct.unpack('<2I', cpu.mem_read(0x51f014, 8)) == (reader.address, reader.bit), case
        totals['unread'] += 1
        common.report(args, 'bit-reader', totals, 'Complete 4046e0, 404610, 404680 and 4060e0 (copy 4eb5e0 stubbed and compared) run unmodified in the original over positions 0..7 and wide ' 'positions (shift counts, sign carry); result and both state dwords compare.')
if __name__ == '__main__':
    main()
