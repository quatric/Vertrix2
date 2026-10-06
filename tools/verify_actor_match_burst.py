"""Compare the complete original match burst 0x4302a0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x200
SEED = 0x598d30


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


Allocate = c.CFUNCTYPE(U, U, c.c_void_p)
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
Bind = c.CFUNCTYPE(None, U, c.c_uint16, c.c_void_p)
Append = c.CFUNCTYPE(None, U, U, c.c_void_p)


class Hooks(c.Structure):
    _fields_ = [('allocate', Allocate), ('draw', Draw), ('bind_frame', Bind), ('append', Append),
                ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=512)
    args = parser.parse_args()
    n = build(args.build_dir, 'actor-match-burst',
              ['actor_spawn.c', 'call_glue.c', 'actor_storage.c', 'actor_fields.c',
               'block_factory.c', 'board_cells.c'])
    n.vertrix_actor_spawn_match_burst.argtypes = [c.POINTER(Services), c.c_void_p, c.c_size_t, U,
                                                 U, U, c.POINTER(Hooks)]
    n.vertrix_actor_spawn_match_burst.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4302a0)
    pool = Pool(cpu, 10, SIZE)
    handles, sizes, divisors, binds, appends = [], [], [], [], []
    script = []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            assert eax == 0x15c, hex(eax)
            handle = rng.choice(others)
            handles.append(handle)
            sizes.append(eax)
            return handle
        if address == 0x4826c0:
            assert eax == SEED, hex(eax)
            divisors.append(edx)
            return script.pop(0)
        if address == 0x4ac8a0:
            binds.append((eax, edx))
            return None
        if address == 0x4b5e70:
            appends.append((eax, edx))
            return 0
        raise AssertionError(hex(address))

    stubs = Stubs(cpu, handler)
    stubs.add(0x4ca000)
    stubs.add(0x4826c0)
    stubs.add(0x4ac8a0)
    stubs.add(0x4b5e70)

    @Allocate
    def allocate(size, context):
        sizes.append(size)
        return handles.pop(0)

    @Draw
    def draw(divisor, context):
        divisors.append(divisor)
        return script.pop(0)

    @Bind
    def bind(actor, descriptor, context):
        binds.append((actor, descriptor))

    @Append
    def append(list_handle, item, context):
        appends.append((list_handle, item))

    hooks = Hooks(allocate, draw, bind, append, None)
    services = Services(pool.resolve, None, None, None, None)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        source = rng.choice(pool.handles)
        others = [handle for handle in pool.handles if handle != source]
        edx, ebx, ecx = (rng.getrandbits(32) for _ in range(3))
        values = [rng.getrandbits(16) for _ in range(2 + 8)]
        for log in (handles, sizes, divisors, binds, appends):
            log.clear()
        script[:] = list(values)
        expect = original.call(0x4302a0, eax=source, edx=edx, ebx=ebx, ecx=ecx) & 0xffffffff
        assert [size for size in sizes] == [0x15c] * 8, (case, sizes)
        assert divisors == [0x168, 2] + [0x20] * 8, (case, divisors)
        orig_binds, orig_appends = list(binds), list(appends)
        for log in (sizes, divisors, binds, appends):
            log.clear()
        script[:] = list(values)
        result = n.vertrix_actor_spawn_match_burst(c.byref(services), pool.buffers[source], SIZE,
                                                   source, edx, ebx, c.byref(hooks))
        assert result == expect == 0, (case, hex(result), hex(expect))
        assert sizes == [0x15c] * 8, (case, sizes)
        assert divisors == [0x168, 2] + [0x20] * 8, (case, divisors)
        assert binds == orig_binds, (case, binds, orig_binds)
        assert appends == orig_appends, (case, appends, orig_appends)
        assert pool.same(), (case, pool.diff())
        totals['0x4302a0'] = totals.get('0x4302a0', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete original 0x4302a0 executions with the allocator 0x4ca000, the '
                       'draw 0x4826c0, the frame bind 0x4ac8a0 and the list append 0x4b5e70 '
                       'stubbed and logged (0x4abd70, 0x4adf20, 0x4ac470, 0x4ac7b0, 0x4ac840, '
                       '0x4ac8d0, 0x4ac710, 0x4ad510 and 0x4ac8f0 execute for real on both '
                       'sides); the zero return, the draw divisor order, the bind '
                       '(actor, descriptor) pairs, the append (list, item) pairs and every pool '
                       'object compare.'}
    (args.build_dir / 'actor-match-burst-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
