"""Compare the original buffer reader 0x4db8c0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original, STACK
from oracle_kit import Stubs, build

U = c.c_uint32


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


CALLEES = {0x4db950: 3, 0x4ca370: 0, 0x4ca670: 0, 0x4ca6c0: 0}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'read-into', ['rtl_glue.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_rtl_read_into.argtypes = [c.POINTER(Calls), U, U, U, U, U]
    n.vertrix_rtl_read_into.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4db8c0)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4db950:
            returns.append(rng.choice([0, rng.randrange(0, 0x100), rng.randrange(0xfd, 0x104),
                                       rng.randrange(0, 0x1800)]))
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
                          (s.stack, s.stack_next, s.stack_third)[:CALLEES[s.target]])
        return replay.pop(0)

    calls = Calls(call, None)
    count = 0
    for case in range(args.cases):
        eax, edx, ebx, ecx = (rng.getrandbits(32) for _ in range(4))
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x4db8c0, eax=eax, edx=edx, ebx=ebx, ecx=ecx) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_rtl_read_into(c.byref(calls), STACK, eax, edx, ebx, ecx)
        assert got == result, (hex(got), hex(result))
        assert native_log == stubs.log, (native_log, stubs.log)
        assert not replay
        count += 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4db8c0': count},
              'scope': 'The routine executes completely in the original with its callees stubbed '
                       'and logged (0x4db950 with its three stack arguments); every callee call and '
                       'the returned eax compare.'}
    (args.build_dir / 'read-into-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
