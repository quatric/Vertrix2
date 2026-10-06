"""Compare the original stream token readers 0x48a3c0 and 0x48a420 with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x100
CALLEES = (0x4ca370, 0x48a910, 0x48aa80, 0x48aa90, 0x4ca630, 0x4ce030, 0x4cdfe0, 0x48a380)
BYTES = b' \n\r/x\\ y'


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


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'stream-token', ['object_glue.c', 'call_glue.c', 'actor_storage.c', 'table_queries.c'])
    for name in ('read_token', 'next_directive'):
        function = getattr(n, 'vertrix_stream_' + name)
        function.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U]
        function.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x48a3c0)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x48aa80:
            handle = rng.choice(pool.handles)
            returns.append(handle)
        elif address == 0x48a910:
            returns.append(1 if rng.random() < 0.25 else 0)
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address in CALLEES:
        stubs.add(address, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve)
    totals = {}
    for case in range(args.cases):
        for address, name in ((0x48a3c0, 'read_token'), (0x48a420, 'next_directive')):
            pool.fill(rng)
            for handle in pool.handles:
                first = bytes([rng.choice(BYTES)])
                cpu.mem_write(handle, first)
                c.memmove(pool.buffers[handle], first, 1)
            obj, stream, ebx = rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32)
            stubs.log.clear()
            returns.clear()
            native_log.clear()
            if name == 'read_token':
                result = original.call(address, eax=ebx ^ 1, edx=stream, ebx=obj) & 0xffffffff
            else:
                result = original.call(address, eax=obj, edx=stream, ebx=ebx) & 0xffffffff
            replay[:] = list(returns)
            order = (stream, obj) if name == 'read_token' else (obj, stream)
            got = getattr(n, 'vertrix_stream_' + name)(c.byref(calls), c.byref(services), *order)
            assert got == result, (case, name, hex(got), hex(result))
            assert native_log == stubs.log, (case, name, native_log, stubs.log)
            assert not replay and pool.same(), (case, name, pool.diff())
            totals[hex(address)] = totals.get(hex(address), 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Each routine executes completely in the original with its callees stubbed '
                       'and logged; every callee call (address and registers), the returned eax '
                       'and every pool object compare.'}
    (args.build_dir / 'stream-token-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
