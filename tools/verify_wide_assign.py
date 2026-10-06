"""Compare the original wide string assignment 0x4ca3a0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x100


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


CALLEES = (0x4d8580, 0x4ca1e0, 0x4ca730, 0x4ca6c0)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'wide-assign', ['rtl_glue.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_rtl_wide_assign.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U]
    n.vertrix_rtl_wide_assign.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4ca3a0)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        returns.append(rng.randrange(0, 0x40) if address == 0x4d8580 else rng.getrandbits(32))
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
    services = Services(pool.resolve, None, None, None, None)
    count = 0
    for case in range(args.cases):
        pool.fill(rng)
        variable = rng.choice(pool.handles)
        source = rng.choice([0, rng.getrandbits(32)])
        ebx = rng.getrandbits(32)
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x4ca3a0, eax=variable, edx=source, ebx=ebx) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_rtl_wide_assign(c.byref(calls), c.byref(services), variable, source, ebx)
        assert got == result, (hex(got), hex(result))
        assert native_log == stubs.log and not replay and pool.same(), (native_log, stubs.log)
        count += 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4ca3a0': count},
              'scope': 'The routine executes completely in the original with its callees stubbed '
                       'and logged; every callee call, the returned eax and every pool object '
                       'compare.'}
    (args.build_dir / 'wide-assign-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
