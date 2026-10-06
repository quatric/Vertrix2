"""Compare the complete original match-effect actor factory 0x430190 with the native recovery."""
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
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next')]


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
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'actor-match-effect',
              ['actor_spawn.c', 'call_glue.c', 'actor_storage.c', 'actor_fields.c',
               'block_factory.c', 'board_cells.c'])
    n.vertrix_actor_spawn_match_effect.argtypes = [c.POINTER(Calls), c.POINTER(Services),
                                                   c.c_void_p, c.c_size_t, U, U, U]
    n.vertrix_actor_spawn_match_effect.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x430190)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        returns.append(rng.choice(pool.handles))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    stubs.add(0x4ca000)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        source = rng.choice(pool.handles)
        edx, ebx, ecx = (rng.getrandbits(32) for _ in range(3))
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x430190, eax=source, edx=edx, ebx=ebx, ecx=ecx) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_actor_spawn_match_effect(c.byref(calls), c.byref(services),
                                                 pool.buffers[source], SIZE, edx, ebx, ecx)
        assert got == result, (case, hex(got), hex(result))
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert not replay and pool.same(), (case, pool.diff())
        totals['0x430190'] = totals.get('0x430190', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete original 0x430190 executions with only the allocator 0x4ca000 '
                       'stubbed and logged (0x4abd70, 0x4adf20, 0x4ac470, 0x4ac7b0, 0x4ac8d0 and '
                       '0x4ac710 execute for real on both sides); the returned actor handle, the '
                       'single allocator call and every pool object compare.'}
    (args.build_dir / 'actor-match-effect-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
