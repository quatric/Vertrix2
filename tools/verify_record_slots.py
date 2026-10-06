"""Compare complete original record slot copies with the native recovery."""
import ctypes as c, random
from original import Original
import verify_common_a as common

U = c.c_uint32
SIZE = 0x800


def main():
    args = common.parse(__doc__)
    n = common.build(args, 'record-slots', 'record_slots.c', 'actor_storage.c')
    B = c.POINTER(c.c_uint8)
    for name in ('load', 'store'):
        f = getattr(n, 'vertrix_record_%s_current' % name)
        f.argtypes, f.restype = [B, c.c_size_t, U], c.c_int
    n.vertrix_record_table_init.argtypes = [B, c.c_size_t, U]
    n.vertrix_record_table_init.restype = c.c_int
    n.vertrix_record_field.argtypes = [B, c.c_size_t, U, U, c.POINTER(c.c_int32)]
    n.vertrix_record_field.restype = c.c_int
    n.vertrix_record_step.argtypes = [B, c.c_size_t, U, U, c.c_int]
    n.vertrix_record_step.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x412650)
    totals = {}
    for case in range(args.cases):
        for address, name in ((0x412650, 'load'), (0x412690, 'store')):
            data = rng.randbytes(SIZE)
            cpu.mem_write(0x806000, data)
            buffer = (c.c_uint8 * SIZE).from_buffer_copy(data)
            index = rng.randrange(0, 0x80)
            original.call(address, eax=0x806000, edx=index)
            ok = getattr(n, 'vertrix_record_%s_current' % name)(c.cast(buffer, B), SIZE, index)
            assert ok and bytes(buffer) == bytes(cpu.mem_read(0x806000, SIZE)), (case, address)
            totals[name] = totals.get(name, 0) + 1
    for case in range(args.cases):
        data = rng.randbytes(SIZE)
        cpu.mem_write(0x806000, data)
        buffer = (c.c_uint8 * SIZE).from_buffer_copy(data)
        owner = rng.getrandbits(32)
        original.call(0x4120a0, eax=0x806000, edx=owner)
        assert n.vertrix_record_table_init(c.cast(buffer, B), SIZE, owner)
        assert bytes(buffer) == bytes(cpu.mem_read(0x806000, SIZE)), case
        totals['table_init'] = totals.get('table_init', 0) + 1
        data = bytes(buffer)
        data = bytes(b if rng.random() < 0.5 else rng.choice([0, 0x80, 0xff, 0x7f]) for b in data)
        cpu.mem_write(0x806000, data)
        buffer = (c.c_uint8 * SIZE).from_buffer_copy(data)
        for field in list(range(10)) + [rng.getrandbits(32)]:
            index = rng.randrange(0, 123)
            want = original.call(0x4125e0, eax=0x806000, edx=index, ebx=field)
            value = c.c_int32(0x7777)
            assert n.vertrix_record_field(c.cast(buffer, B), SIZE, index, field, c.byref(value))
            assert value.value == c.c_int32(want).value, (case, field, index)
            totals['field'] = totals.get('field', 0) + 1
    for case in range(args.cases):
        data = bytearray(rng.randbytes(SIZE))
        for i in range(0, SIZE - 12, 12):
            for offset, limit in ((0, 3), (1, 12), (2, 102), (4, 202), (6, 15), (7, 4), (8, 3), (10, 256)):
                if rng.random() < 0.7 and offset not in (4, 10):
                    data[i + offset] = (rng.randrange(-3, limit) if offset in (0, 1, 7, 8)
                                        else rng.randrange(0, limit)) & 0xff
        for address, increase in ((0x412430, 1), (0x412510, 0)):
            cpu.mem_write(0x806000, bytes(data))
            buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
            index = rng.randrange(0, 123)
            field = rng.choice([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, rng.getrandbits(32)])
            original.call(address, eax=0x806000, edx=index, ebx=field)
            assert n.vertrix_record_step(c.cast(buffer, B), SIZE, index, field, increase)
            assert bytes(buffer) == bytes(cpu.mem_read(0x806000, SIZE)), (case, address, field)
            totals['step_up' if increase else 'step_down'] = totals.get('step_up' if increase else 'step_down', 0) + 1
    common.report(args, 'record-slots', totals,
                  'Complete 412650, 412690, 4120a0, 4125e0, 412430 and 412510 run unmodified in the original over random storage; the '
                  'whole 2 KiB storage compares (12 bytes move, including overlapping records).')


if __name__ == '__main__':
    main()
