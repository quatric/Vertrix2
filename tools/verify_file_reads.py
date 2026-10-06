"""Compare complete original exact-size file reads with the native recovery."""
import ctypes as c, random, struct
from original import Original
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EDX
import verify_common_a as common
U = c.c_uint32
Read = c.CFUNCTYPE(U, U, c.POINTER(c.c_uint8), U, U, c.c_void_p)
BUFFER = 0x806000


def main():
    args = common.parse(__doc__)
    n = common.build(args, 'file-reads', 'file_reads.c')
    B = c.POINTER(c.c_uint8)
    n.vertrix_file_read_exact.argtypes = [U, B, U, Read, c.c_void_p]
    n.vertrix_file_read_exact.restype = U
    for name in ('byte', 'word', 'dword'):
        f = getattr(n, 'vertrix_file_read_' + name)
        f.argtypes, f.restype = [U, B, Read, c.c_void_p], U
    n.vertrix_file_read_word_swapped.argtypes = [U, B, Read, c.c_void_p]
    n.vertrix_file_read_word_swapped.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x40c220)
    plan = {}
    calls, native = [], []
    def on_read(uc):
        buf, size, count, file = (uc.reg_read(r) for r in (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX))
        calls.append((buf, size, count, file))
        got = plan['read']
        cpu.mem_write(buf, plan['data'][: got * size])
        cpu.mem_write(common.DATA, struct.pack('<I', got))
    common.stub(cpu, 0x4ebec0, on_read)
    @ Read
    def read(file, buffer, size, count, context):
        native.append((BUFFER, size, count, file))
        for i in range(plan['read'] * size):
            buffer[i] = plan['data'][i]
        return plan['read']
    totals = {}
    for case in range(args.cases):
        file = rng.getrandbits(32)
        cpu.mem_write(0x52f90c, struct.pack('<I', file))
        for address, name, fixed in ((0x40c220, 'exact', None), (0x40c260, 'byte', 1), (0x40c2a0, 'word', 2), (0x40c2e0, 'dword', 4), (0x40c320, 'byte', 1), (0x40c360, 'word_swapped', 2)):
            count = rng.randrange(0, 17) if fixed is None else fixed
            plan['read'] = count if rng.random() < 0.5 else rng.randrange(0, count + 2)
            plan['data'] = rng.randbytes(32)
            fill = rng.randbytes(32)
            cpu.mem_write(BUFFER, fill)
            calls.clear()
        native.clear()
        buffer = (c.c_uint8 * 32).from_buffer_copy(fill)
        ptr = c.cast(buffer, B)
        if fixed is None:
            result = original.call(address, eax=BUFFER, edx=count)
            got = n.vertrix_file_read_exact(file, ptr, count, read, None)
        else:
            result = original.call(address, eax=BUFFER)
            got = getattr(n, 'vertrix_file_read_' + name)(file, ptr, read, None)
            assert result == got == 0, (case, address)
            assert calls == native, (case, address)
            assert bytes(buffer) == bytes(cpu.mem_read(BUFFER, 32)), (case, address)
            totals[hex(address)] = totals.get(hex(address), 0) + 1
            common.report(args, 'file-reads', totals, 'Complete 40c360 (byte-swapped word), 40c220, 40c260, 40c2a0, 40c2e0 and 40c320 run in the original with the real ' '4eb5c0 zero fill; the runtime read 4ebec0 is a data-driven stub (full and short ' 'reads). Read arguments and the whole buffer compare.')
if __name__ == '__main__':
    main()
