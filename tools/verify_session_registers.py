"""Compare complete original session register resets with the native recovery."""
import ctypes as c, random, struct
from original import Original
import verify_common_a as common

U = c.c_uint32


class Latch(c.Structure):
    _fields_ = [('state', U), ('first', U), ('second', U)]


class Registers(c.Structure):
    _fields_ = [('primary', U), ('secondary', U), ('tertiary', U), ('cleared', U * 4)]


LATCH = 0x532b40
SOURCE = 0x5332bc


def region(cpu):
    return bytes(cpu.mem_read(0x532a00, 0x200))


def registers_from(cpu):
    r = Registers()
    r.primary, r.secondary, r.tertiary = struct.unpack('<3I', cpu.mem_read(0x532a68, 12))
    r.cleared[:] = struct.unpack('<4I', cpu.mem_read(0x532aa4, 16))
    return r


def main():
    args = common.parse(__doc__)
    n = common.build(args, 'session-registers', 'session_registers.c')
    n.vertrix_session_latch_release.argtypes = [c.POINTER(Latch)]
    for name in ('reset', 'reset_open', 'reset_secondary'):
        f = getattr(n, 'vertrix_session_registers_' + name)
        f.argtypes = [c.POINTER(Registers), U]
        f.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x415550)
    totals = {}
    for case in range(args.cases):
        noise = rng.randbytes(0x200)
        cpu.mem_write(0x532a00, noise)
        state = rng.choice([0, 1, 1, 2, 0xffffffff])
        cpu.mem_write(LATCH, struct.pack('<3I', state, rng.getrandbits(32), rng.getrandbits(32)))
        source = rng.getrandbits(32)
        cpu.mem_write(SOURCE, struct.pack('<I', source))
        latch = Latch(*struct.unpack('<3I', cpu.mem_read(LATCH, 12)))
        before = region(cpu)
        original.call(0x415550)
        n.vertrix_session_latch_release(c.byref(latch))
        after = struct.unpack('<3I', cpu.mem_read(LATCH, 12))
        assert after == (latch.state, latch.first, latch.second), case
        totals['latch'] = totals.get('latch', 0) + 1
        for address, name in ((0x415b50, 'reset'), (0x415b90, 'reset_open'),
                              (0x415bd0, 'reset_secondary')):
        cpu.mem_write(0x532a00, noise)
            registers = registers_from(cpu) result = original.call(address) getattr(
            n, 'vertrix_session_registers_' +
                   name)(c.byref(registers), source) expected = registers_from(cpu) assert
                                                                bytes(registers) == bytes(expected),
            (case, name)assert result == source,
            (case, name)totals[name] =
                totals.get(name, 0) +
                    1 common.report(
                        args, 'session-registers',
                        totals,
                        'Complete 415550, 415b50, 415b90 and 415bd0 run unmodified in the original over ' 'random register memory; all fields compare, and the leftover eax equals the source ' 'dword.')

                        if __name__
                == '__main__' : main()
