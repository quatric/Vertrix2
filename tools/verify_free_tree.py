"""Compare the original tree release 0x40ef90 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x800


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


CALLEES = {0x4ea190: 0, 0x40aca0: 0}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'free-tree', ['object_glue.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_object_free_tree.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U, U]
    n.vertrix_object_free_tree.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x40ef90)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay, picked = [], [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        returns.append(rng.choice([rng.randrange(0, 9), rng.getrandbits(32)])
                       if False else rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) +
                          (s.stack, s.stack_next, s.stack_third, s.rest0, s.rest1)[:CALLEES[s.target]])
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    count = 0
    for case in range(args.cases):
        def patch(handle, data):
            def pointer():
                return rng.choice(pool.handles + [0])

            struct.pack_into('<I', data, 0x150, pointer())
            struct.pack_into('<I', data, 0x154, pointer())
            struct.pack_into('<H', data, 0x28, rng.randrange(0, 6))
            struct.pack_into('<H', data, 0x2a, rng.randrange(0, 3))
            for index in range(6):
                struct.pack_into('<I', data, 0xc * index + 8, pointer())
            for index in range(3):
                struct.pack_into('<I', data, 0xfc * index + 0xf8, pointer())
                struct.pack_into('<H', data, 0xfc * index + 0x80, rng.randrange(0, 5))

        pool.fill(rng, patch)
        obj = rng.choice(pool.handles + [0, 0])
        edx, ebx, ecx = (rng.getrandbits(32) for _ in range(3))
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x40ef90, eax=obj, edx=edx, ebx=ebx, ecx=ecx) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_object_free_tree(c.byref(calls), c.byref(services), obj, edx, ebx, ecx)
        assert got == result, (hex(got), hex(result))
        assert native_log == stubs.log and not replay and pool.same(), (native_log, stubs.log)
        count += 1
    report = {'status': 'passed', 'complete_original_executions': {'0x40ef90': count},
              'scope': 'The routine executes completely in the original with its callees stubbed '
                       'and logged; every callee call, the returned eax, every pool object '
                       'compare. The register arguments of the release calls are the loop state.'}
    (args.build_dir / 'free-tree-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
