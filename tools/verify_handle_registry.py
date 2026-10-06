"""Compare complete original registry and guarded-call routines with the native recovery."""
import ctypes as c, random, struct
from original import Original
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX
import verify_common_a as common

U, PU = c.c_uint32, c.POINTER(c.c_uint32)
Start = c.CFUNCTYPE(U, U, c.c_void_p)
Close = c.CFUNCTYPE(U, c.c_void_p)
Release = c.CFUNCTYPE(None, U, c.c_void_p)
Assign = c.CFUNCTYPE(None, U, U, c.c_void_p)


class Guard(c.Structure):
    _fields_ = [('disabled_id', U), ('depth', U)]


def main():
    args = common.parse(__doc__)
    n = common.build(args, 'handle-registry', 'handle_registry.c')
    n.vertrix_registry_add.argtypes, n.vertrix_registry_add.restype = [PU, U], U
    n.vertrix_handles_release.argtypes, n.vertrix_handles_release.restype = [PU, U, U], U
    n.vertrix_handles_init.argtypes, n.vertrix_handles_init.restype = [PU, PU, U, Start, c.c_void_p], U
    n.vertrix_guarded_call.argtypes = [c.POINTER(Guard), U, Start, c.c_void_p]
    n.vertrix_guarded_call.restype = U
    n.vertrix_close_cell.argtypes = [PU, Close, Release, c.c_void_p]
    n.vertrix_close_cell.restype = U
    n.vertrix_handles_shutdown.argtypes, n.vertrix_handles_shutdown.restype = [PU, PU, Close, c.c_void_p], U
    n.vertrix_text_for_code.argtypes = [U, U, PU, Assign, c.c_void_p]
    n.vertrix_text_for_code.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x40a860)
    events, native = [], []
    returns = {}

    def put(slot, value):
        cpu.mem_write(common.DATA + 4 * slot, struct.pack('<I', value))

#Library entries are reached through function pointers held in original memory.
    for slot, pointer in ((1, 0x52f020), (2, 0x52f03c), (3, 0x52f058), (6, 0x52f040)):
        entry = 0x80f400 + 0x10 * slot
        common.stub(cpu, entry, lambda uc, s=slot: events.append((s, uc.reg_read(UC_X86_REG_EAX) if s not in (3, 6) else 0)), slot)
        cpu.mem_write(pointer, struct.pack('<I', entry))
    common.stub(cpu, 0x4ea190, lambda uc: events.append(('free', uc.reg_read(UC_X86_REG_EAX))), 4)
    common.stub(cpu, 0x4eb860, lambda uc: events.append(
        ('assign', uc.reg_read(UC_X86_REG_EAX), uc.reg_read(UC_X86_REG_EDX))), 5)

    @Start
    def start(count, context):
        native.append((2, count))
        return returns['start']

    @Start
    def guarded(argument, context):
        native.append((1, argument))
        return returns['guarded']

    @Close
    def close(context):
        native.append((3, 0))
        return returns['close']

    @Release
    def release(obj, context):
        native.append(('free', obj))

    @Close
    def stop(context):
        native.append((6, 0))
        return returns['stop']

    @Assign
    def assign(dest, source, context):
        native.append(('assign', dest, source))

    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    for case in range(args.cases):
# 40a890
        pool = [rng.choice([0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) for _ in range(8)]
        if rng.random() < 0.5:
            pool = sorted(pool, key=lambda v: v == 0)
        cpu.mem_write(0x52f090, struct.pack('<8I', *pool))
        value = rng.randrange(0, 11)
        slots = (U * 8)(*pool)
        assert original.call(0x40a890, eax=value) == n.vertrix_registry_add(slots, value), case
        assert bytes(slots) == bytes(cpu.mem_read(0x52f090, 32)), case
        count('registry_add')
# 40ad50
        table = [rng.getrandbits(32) for _ in range(32)]
        cpu.mem_write(0x52f0b0, struct.pack('<32I', *table))
        limit = rng.randrange(0, 33)
        cpu.mem_write(0x52f130, struct.pack('<I', limit))
        handle = rng.choice([0, rng.randrange(0, 36), 0xffffffff])
        cells = (U * 32)(*table)
        assert original.call(0x40ad50, eax=handle) == n.vertrix_handles_release(cells, limit, handle), case
        assert bytes(cells) == bytes(cpu.mem_read(0x52f0b0, 128)), case
        count('handles_release')
# 40ab60
        cpu.mem_write(0x52f0b0, struct.pack('<32I', *table))
        cpu.mem_write(0x52f130, struct.pack('<I', 0x1234))
        returns['start'] = rng.choice([0, 0, 5, 0xffffffff])
        put(2, returns['start'])
        arg = rng.randrange(0, 40)
        events.clear(); native.clear()
        cells, stored = (U * 32)(*table), U(0x1234)
        assert original.call(0x40ab60, eax=arg) == n.vertrix_handles_init(cells, c.byref(stored), arg,
                                                                           start, None), case
        assert bytes(cells) == bytes(cpu.mem_read(0x52f0b0, 128)), case
        assert stored.value == struct.unpack('<I', cpu.mem_read(0x52f130, 4))[0], case
        assert events == native, case
        count('handles_init')
# 40ab20
        disabled = rng.choice([0xffff, 0, 0xffff, 7])
        depth = rng.choice([0, 0, 1, 2, 5])
        cpu.mem_write(0x4f6418, struct.pack('<I', disabled))
        cpu.mem_write(0x4f644c, struct.pack('<I', depth))
        returns['guarded'] = rng.getrandbits(32)
        put(1, returns['guarded'])
        arg = rng.getrandbits(32)
        events.clear(); native.clear()
        guard = Guard(disabled, depth)
        assert original.call(0x40ab20, eax=arg) == n.vertrix_guarded_call(c.byref(guard), arg, guarded, None), case
        assert guard.depth == struct.unpack('<I', cpu.mem_read(0x4f644c, 4))[0], case
        assert events == native, case
        count('guarded_call')
# 40aca0
        returns['close'] = rng.getrandbits(32)
        put(3, returns['close'])
        obj = rng.choice([0, rng.getrandbits(32)])
        cpu.mem_write(0x806000, struct.pack('<I', obj))
        pointer = rng.choice([0, 0x806000])
        events.clear(); native.clear()
        cell = U(obj)
        want = original.call(0x40aca0, eax=pointer)
        got = n.vertrix_close_cell(c.byref(cell) if pointer else None, close, release, None)
        assert want == got and events == native, case
        count('close_cell')
# 40aba0
        mix = rng.choice([0.0, 0.0, 0.1, 0.5])
        table = [rng.getrandbits(32) if rng.random() < mix else 0 for _ in range(32)]
        cpu.mem_write(0x52f0b0, struct.pack('<32I', *table))
        limit = rng.randrange(0, 33)
        cpu.mem_write(0x52f130, struct.pack('<I', limit))
        returns['stop'] = rng.getrandbits(32)
        put(6, returns['stop'])
        events.clear(); native.clear()
        cells, stored = (U * 32)(*table), U(limit)
        assert original.call(0x40aba0) == n.vertrix_handles_shutdown(cells, c.byref(stored), stop, None), case
        assert bytes(cells) == bytes(cpu.mem_read(0x52f0b0, 128)), case
        assert stored.value == struct.unpack('<I', cpu.mem_read(0x52f130, 4))[0], case
        assert events == native, case
        count('handles_shutdown')
# 40a860
        texts = [rng.getrandbits(32) for _ in range(12)]
        cpu.mem_write(0x4f641c, struct.pack('<12I', *texts))
        code = rng.choice([rng.randrange(0, 14), rng.getrandbits(32)])
        dest = rng.choice([0, rng.getrandbits(32) | 1])
        events.clear(); native.clear()
        want = original.call(0x40a860, eax=code, edx=dest)
        got = n.vertrix_text_for_code(code, dest, (U * 12)(*texts), assign, None)
        assert want == got and events == native, case
        count('text_for_code')
    common.report(args, 'handle-registry', totals,
                  'Complete 40a890, 40ad50, 40aba0 (entry 52f040 stubbed), 40ab60 (with the real 4eb5c0), 40ab20, 40aca0 and 40a860 run '
                  'in the original over random registry memory. The library entries 52f020, 52f03c, '
                  '52f058 and the runtime calls 4ea190 and 4eb860 are data-driven stubs whose call '
                  'sequences and arguments compare with the native callbacks.')


if __name__ == '__main__':
        main()
