"""Compare the original marker actor constructor 0x465a70 with the native recovery."""
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


CALLEES = {0x4ca000: 0, 0x4abd70: 0, 0x4adf20: 5, 0x4ac8d0: 0, 0x4ac710: 0, 0x4ac8a0: 0,
           0x4b5e70: 0}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'marker-actor', ['marker_actor.c', 'call_glue.c', 'actor_storage.c',
                                               'block_factory.c', 'actor_fields.c',
                                               'board_cells.c'])
    n.vertrix_marker_spawn.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U]
    n.vertrix_marker_spawn.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x465a70)
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
    for case in range(args.cases):
        pool.fill(rng)
        x, y, frame = (rng.getrandbits(32) for _ in range(3))
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x465a70, eax=x, edx=y, ebx=frame) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_marker_spawn(c.byref(calls), c.byref(services), x, y, frame)
        assert got == result, (case, hex(got), hex(result))
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert not replay and pool.same(), (case, pool.diff())
    report = {'status': 'passed', 'complete_original_executions': {'0x465a70': args.cases},
              'scope': 'The original executes completely with its callees stubbed and logged '
                       '(0x4adf20 with its five stack arguments); every call, the returned eax '
                       'and every pool object compare.'}
    (args.build_dir / 'marker-actor-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
