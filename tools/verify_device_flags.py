"""Compare complete original device flag routines with the native recovery."""
import ctypes as c, random, struct
from original import Original
import verify_common_a as common
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX
LockItem = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)
U = c.c_uint32
BASE = 0x531b44
FIELDS = ((0x531b48, 'count'), (0x531b50, 'value50'), (0x531b5c, 'value5c'), (0x531b68, 'limit'), (0x531b70, 'first'), (0x531b74, 'second'))


class Device(c.Structure):
    _fields_ = [('flags', c.c_uint8), ('count', c.c_int32), ('value50', U), ('value5c', U), ('limit', U), ('first', U), ('second', U)]


def load(cpu):
    d = Device()
    d.flags = cpu.mem_read(BASE, 1)[0]
    for address, name in FIELDS:
        setattr(d, name, struct.unpack('<i' if name == 'count' else '<I', cpu.mem_read(address, 4))[0])
    return d


def main():
    args = common.parse(__doc__)
    n = common.build(args, 'device-flags', 'device_flags.c')
    P, PU = c.POINTER(Device), c.POINTER(U)
    for name, types in (('mark_dirty', [P]), ('set_limit', [P, U]), ('set_pair', [P, U, U]), ('get_values', [P, PU, PU]), ('get_locked', [P, PU])):
        f = getattr(n, 'vertrix_device_' + name)
        f.argtypes, f.restype = types, U
    n.vertrix_device_lock.argtypes = [P, PU, LockItem, c.c_void_p]
    n.vertrix_device_lock.restype = U
    original = Original(args.executable)
    events, native = [], []
    common.stub(original.cpu, 0x40ae00, lambda uc: events.append((uc.reg_read(UC_X86_REG_EAX), uc.reg_read(UC_X86_REG_EDX))))
    @ LockItem
    def lock_item(item, argument, context):
        native.append((item, argument))
    cpu = original.cpu
    rng = random.Random(0x40ee30)
    totals = {}
    OUT = common.DATA + 0x100
    def count(name):
        totals[name] = totals.get(name, 0) + 1
    for case in range(args.cases):
        cpu.mem_write(0x531b00, rng.randbytes(0x100))
        cpu.mem_write(BASE, bytes([rng.getrandbits(8) if rng.random() < 0.5 else rng.choice([0x80, 0xa0, 0x90, 0xff, 0x00, 0x7f])]))
        snapshot = bytes(cpu.mem_read(0x531b00, 0x100))
        device = load(cpu)
        assert original.call(0x40ee30) == n.vertrix_device_mark_dirty(c.byref(device)), case
        assert bytes(device) == bytes(load(cpu)), case
        count('mark_dirty')
        cpu.mem_write(0x531b00, snapshot)
        device = load(cpu)
        limit = rng.choice([rng.randrange(0x50), rng.getrandbits(32)])
        assert original.call(0x40ee60, eax=limit) == n.vertrix_device_set_limit(c.byref(device), limit), case
        assert bytes(device) == bytes(load(cpu)), case
        count('set_limit')
        cpu.mem_write(0x531b00, snapshot)
        device = load(cpu)
        a, b = rng.getrandbits(32), rng.getrandbits(32)
        assert original.call(0x40eea0, eax=a, edx=b) == n.vertrix_device_set_pair(c.byref(device), a, b), case
        assert bytes(device) == bytes(load(cpu)), case
        count('set_pair')
        cpu.mem_write(0x531b00, snapshot)
        device = load(cpu)
        pa, pb = rng.choice([0, OUT]), rng.choice([0, OUT + 4])
        cpu.mem_write(OUT, struct.pack('<2I', 0xdead, 0xbeef))
        oa, ob = U(0xdead), U(0xbeef)
        want = original.call(0x40ef00, eax=pa, edx=pb)
        got = n.vertrix_device_get_values(c.byref(device), c.byref(oa) if pa else None, c.byref(ob) if pb else None)
        assert want == got, case
        assert struct.unpack('<2I', cpu.mem_read(OUT, 8)) == (oa.value, ob.value), case
        count('get_values')
        cpu.mem_write(OUT, struct.pack('<I', 0xdead))
        ol = U(0xdead)
        pa = rng.choice([0, OUT])
        want = original.call(0x40ef40, eax=pa)
        got = n.vertrix_device_get_locked(c.byref(device), c.byref(ol) if pa else None)
        assert want == got and struct.unpack('<I', cpu.mem_read(OUT, 4))[0] == ol.value, case
        count('get_locked')
    for case in range(args.cases):
        cpu.mem_write(0x531ac4, rng.randbytes(0x80))
        cpu.mem_write(0x531b44, bytes([rng.choice([0x80, 0xa0, 0x00, 0x7f, 0xff])]))
        cpu.mem_write(0x531b48, struct.pack('<i', rng.choice([rng.randrange(- 3, 33), 0])))
        snapshot = bytes(cpu.mem_read(0x531b00, 0x100))
        device = load(cpu)
        items = (U * 32).from_buffer_copy(bytes(cpu.mem_read(0x531ac4, 0x80)))
        events.clear()
        native.clear()
        want = original.call(0x40ede0)
        assert want == n.vertrix_device_lock(c.byref(device), items, lock_item, None), case
        assert events == native and bytes(device) == bytes(load(cpu)), case
        count('lock')
        common.report(args, 'device-flags', totals, 'Complete 40ede0 (lock callback 40ae00 stubbed), 40ee30, 40ee60, 40eea0, 40ef00 and 40ef40 run unmodified in the original over ' 'random flag bytes and parameters; status, flags, fields and outputs compare.')
if __name__ == '__main__':
    main()
