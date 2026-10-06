"""Compare the original array list walkers 0x4874f0 and 0x4876c0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


CALLEES = ((0x4ec160, 0), (0x4830f0, 0), (0x4ea190, 0), (0x483790, 0), (0x483060, 8))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'array-list', ['array_list.c', 'call_glue.c', 'actor_storage.c'])
    for name in ('vertrix_array_list_release', 'vertrix_array_list_each'):
        function = getattr(n, name)
        function.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U]
        function.restype = U
    n.vertrix_array_list_make.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U, U,
                                          U * 10]
    n.vertrix_array_list_make.restype = U
    n.vertrix_array_list_build.argtypes = n.vertrix_array_list_make.argtypes
    n.vertrix_array_list_build.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4874f0)
    returns, native_log, replay = [], [], []

    current = [0]

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ec160:
            returns.append(rng.choice([h for h in pool.handles if h != current[0]]))
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES:
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) + (
            (s.stack, s.stack_next, s.stack_third, s.rest0, s.rest1, s.rest2, s.rest3, s.rest4)
            if s.target == 0x483060 else ()))
        return replay.pop(0)

    calls = Calls(call, None)
    pool = Pool(cpu, 4, 0x200)
    services = Services(pool.resolve)
    totals = {}

    def patch(handle, data):
        struct.pack_into('<I', data, 0, rng.choice(pool.handles + [0]))
        struct.pack_into('<I', data, 4, rng.randrange(0, 9))
        for offset in (8, 0xc, 0x10):
            struct.pack_into('<I', data, offset, rng.choice([0, rng.getrandbits(32)]))
        struct.pack_into('<I', data, 0x14, rng.choice([0, 0, 1]))
        for index in range(16):
            struct.pack_into('<I', data, 0x40 + 4 * index, rng.choice([0, rng.getrandbits(32)]))

    for case in range(args.cases):
        for address, name in ((0x4874f0, 'release'), (0x4876c0, 'each')):
            pool.fill(rng, patch)
            handle, edx = rng.choice(pool.handles), rng.getrandbits(32)
            if rng.random() < 0.7:
                data = bytearray(cpu.mem_read(handle, 0x200))
                struct.pack_into('<I', data, 0, rng.choice(pool.handles))
                cpu.mem_write(handle, bytes(data))
                pool.buffers[handle] = c.create_string_buffer(bytes(data), 0x200)
            stubs.log.clear()
            returns.clear()
            native_log.clear()
            result = original.call(address, eax=handle, edx=edx) & 0xffffffff
            replay[:] = list(returns)
            got = getattr(n, 'vertrix_array_list_' + name)(c.byref(calls), c.byref(services),
                                                           handle, edx)
            assert got == result, (case, name, hex(got), hex(result))
            assert native_log == stubs.log, (case, name, native_log, stubs.log)
            assert not replay and pool.same(), (case, name, pool.diff())
            totals[hex(address)] = totals.get(hex(address), 0) + 1
    for case in range(args.cases):
        pool.fill(rng, patch)
        handle, index = rng.choice(pool.handles), rng.randrange(0, 8)
        data = bytearray(cpu.mem_read(handle, 0x200))
        array = rng.choice([h for h in pool.handles if h != handle])
        struct.pack_into('<I', data, 0, array)
        cpu.mem_write(handle, bytes(data))
        pool.buffers[handle] = c.create_string_buffer(bytes(data), 0x200)
        arguments = [rng.getrandbits(32) for _ in range(10)]
        a, b = rng.getrandbits(32), rng.getrandbits(32)
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x487660, eax=handle, edx=index, ebx=a, ecx=b,
                               args=tuple(arguments)) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_array_list_make(c.byref(calls), c.byref(services), handle, index, a, b,
                                        (U * 10)(*arguments))
        assert got == result, (case, hex(got), hex(result))
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert not replay and pool.same(), (case, pool.diff())
        totals['0x487660'] = totals.get('0x487660', 0) + 1
    for case in range(args.cases):
        pool.fill(rng, patch)
        handle, count = rng.choice(pool.handles), rng.randrange(0, 5)
        current[0] = handle
        arguments = [rng.getrandbits(32) for _ in range(10)]
        a, b = rng.getrandbits(32), rng.getrandbits(32)
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x4875a0, eax=handle, edx=count, ebx=a, ecx=b,
                               args=tuple(arguments)) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_array_list_build(c.byref(calls), c.byref(services), handle, count, a, b,
                                         (U * 10)(*arguments))
        assert got == result, (case, hex(got), hex(result))
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert not replay and pool.same(), (case, pool.diff())
        totals['0x4875a0'] = totals.get('0x4875a0', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': '0x4874f0, 0x4876c0 and 0x487660 execute completely in the original with 0x4830f0, 0x4ea190 and '
                       '0x483790, 0x483060 stubbed and logged; the callee registers, eax and every object '
                       'compare.'}
    (args.build_dir / 'array-list-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
