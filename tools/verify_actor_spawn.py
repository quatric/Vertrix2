"""Compare the original actor spawn routines 0x472470, 0x4724f0 and 0x472570 with the native
recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x200


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


class Spec(c.Structure):
    _fields_ = [(name, U) for name in ('kind', 'delay', 'field58', 'field5c', 'field60', 'handler')]


CALLEES = {0x4ca000: 0, 0x4abd70: 0, 0x4adf20: 5, 0x4ac7d0: 0, 0x4ac8f0: 0, 0x4ac910: 0,
           0x4b5e70: 0}
SPECS = ((0x472470, Spec(8, 0xf, 0, 0x64, 1, 0x459760)),
         (0x4724f0, Spec(8, 0xa, 0, 0x64, 1, 0x459760)),
         (0x472570, Spec(9, 0xa, 0x1df, 0, 4, 0x4597a0)))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=512)
    args = parser.parse_args()
    n = build(args.build_dir, 'actor-spawn', ['actor_spawn.c', 'call_glue.c', 'actor_storage.c', 'block_factory.c', 'actor_fields.c', 'board_cells.c'])
    n.vertrix_actor_spawn.argtypes = [c.POINTER(Calls), c.POINTER(Services), c.POINTER(Spec), U, U,
                                      U]
    n.vertrix_actor_spawn.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x472470)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address in (0x4ca000, 0x4abd70):
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
        count = CALLEES[s.target]
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) +
                          (s.stack, s.stack_next, s.stack_third, s.rest0, s.rest1)[:count])
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    totals = {}
    for case in range(args.cases):
        for address, spec in SPECS:
            pool.fill(rng)
            edx, ebx, ecx = (rng.getrandbits(32) for _ in range(3))
            stubs.log.clear()
            returns.clear()
            native_log.clear()
            result = original.call(address, edx=edx, ebx=ebx, ecx=ecx) & 0xffffffff
            replay[:] = list(returns)
            got = n.vertrix_actor_spawn(c.byref(calls), c.byref(services), c.byref(spec), edx, ebx,
                                        ecx)
            assert got == result, (hex(address), hex(got), hex(result))
            assert native_log == stubs.log, (hex(address), native_log, stubs.log)
            assert not replay and pool.same(), (hex(address), pool.diff())
            totals[hex(address)] = totals.get(hex(address), 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Each routine executes completely in the original with its callees stubbed '
                       'and logged (0x4adf20 with its five stack arguments); every callee call, '
                       'the returned eax and every pool object compare.'}
    (args.build_dir / 'actor-spawn-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
