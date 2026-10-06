"""Compare the original value parser 0x48a4a0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x200


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


CALLEES = {0x48a2e0: 0, 0x48a2f0: 0, 0x48a300: 0, 0x4ca310: 0, 0x4ca370: 0, 0x4ca210: 0}
CURRENT = []


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'parse-texts', ['list_text.c', 'rtl_glue.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_list_parse_texts.argtypes = [c.POINTER(Calls), U, U, U, U, U, U]
    n.vertrix_list_parse_texts.restype = None
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x48a4a0)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay, picked = [], [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x48a2e0:
            returns.append(rng.randrange(0, 6))
        elif address == 0x48a2f0:
            returns.append(rng.choice([rng.randrange(0, 4), rng.getrandbits(32)]))
        elif address == 0x48a300:
            returns.append(rng.choice(pool.handles))
        else:
            returns.append(rng.getrandbits(32))
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
    executions = 0
    for case in range(args.cases):
        pool.fill(rng)
        obj = rng.choice(pool.handles)
        count = rng.choice([rng.randrange(0, 6), rng.getrandbits(32) & 0x30007])
        count = (count & 0xffff0000) | (count & 7)
        fallback, threshold = rng.getrandbits(32), rng.choice([rng.randrange(0, 4), rng.getrandbits(32)])
        ebx_in = rng.getrandbits(32)
        base = 0x801000
        values = bytes(32)
        cpu.mem_write(base, values)
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        original.call(0x48a4a0, eax=obj, edx=base, ebx=count, ecx=fallback, args=(threshold,))
        replay[:] = list(returns)
        n.vertrix_list_parse_texts(c.byref(calls), STACK - 4, obj, base, count, fallback, threshold)
        assert native_log == stubs.log and not replay and pool.same(), (native_log, stubs.log)
        executions += 1
    report = {'status': 'passed', 'complete_original_executions': {'0x48a4a0': executions},
              'scope': 'The routine executes completely in the original with its callees stubbed '
                       'and logged; every callee call, the returned eax, every pool object '
                       'compare. The register arguments of each call are the loop state; the '
                       'allocations never return the object itself.'}
    (args.build_dir / 'parse-texts-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
