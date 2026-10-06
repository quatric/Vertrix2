"""Compare the original bit field fill 0x4074a0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x200
TABLES = 0x4f5e78
TABLES_SIZE = 0x20


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(14)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'bits-fill', ['bits_fill.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_bits_fill.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, c.POINTER(U)]
    n.vertrix_bits_fill.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4074a0)
    pool = Pool(cpu, 3, SIZE)
    tables = c.create_string_buffer(bytes(cpu.mem_read(TABLES, TABLES_SIZE)), TABLES_SIZE)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == TABLES:
            storage[0] = c.addressof(tables)
            size[0] = TABLES_SIZE
            return 1
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    stubs.add(0x404680, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        out, obj, _ = pool.handles
        data = bytearray(rng.randbytes(SIZE))
        flags = rng.choice([rng.getrandbits(32), rng.getrandbits(31), rng.randrange(0, 16)])
        mode = rng.choice([2, 2, rng.randrange(0, 4)])
        struct.pack_into('<I', data, 0, flags)
        struct.pack_into('<I', data, 0xc, rng.randrange(0, 16))
        struct.pack_into('<II', data, 0x10, mode, rng.choice([0, 1]))
        cpu.mem_write(obj, bytes(data))
        c.memmove(pool.buffers[obj], bytes(data), SIZE)
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        want = original.call(0x4074a0, eax=out, edx=obj) & 0xffffffff
        replay[:] = list(returns)
        total = U()
        assert n.vertrix_bits_fill(c.byref(calls), c.byref(services), out, obj, c.byref(total)), case
        assert total.value == want, (case, total.value, want)
        assert native_log == stubs.log, (case, len(native_log), len(stubs.log), native_log[:3], stubs.log[:3])
        assert not replay and pool.same(), (case, pool.diff())
        key = 'mode2' if mode == 2 else ('wide' if flags >> 31 else 'flags')
        totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4074a0': totals},
              'scope': 'The routine executes completely in the original with 0x404680 stubbed '
                       'and logged; every bit read (width and the loop registers), the returned '
                       'bit total and the output array compare.'}
    (args.build_dir / 'bits-fill-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
