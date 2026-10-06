"""Compare the original object constructors with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
Allocate = c.CFUNCTYPE(U, U, c.c_void_p)
SIZE = 0xd00


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next')]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', Allocate), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


CALLEES = (0x4abd70, 0x4b5db0, 0x4b2290, 0x4ac7d0, 0x4ac8f0, 0x4ac910, 0x4b5e70, 0x42f850, 0x42f860, 0x42ef00, 0x42ef10, 0x42ef20,
           0x42ef30, 0x42ef40, 0x42ef50, 0x42f870, 0x42f880)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'object-construct',
              ['object_construct.c', 'call_glue.c', 'actor_storage.c', 'actor_fields.c', 'block_factory.c',
               'board_cells.c', 'board_markers.c', 'board.c', 'fixed_point.c', 'board_actions.c',
               'surface.c', 'render_pixel.c', 'palette_map.c', 'palette_tables.c', 'palette_color.c',
               'render_dispatch.c', 'render_color.c', 'render_palette.c', 'render_weights.c',
               'render_color_bank.c', 'render_geometry.c', 'render_row.c', 'render_rectangle.c',
               'render_preparation.c', 'image.c', 'vf.c', 'board_burst.c'])
    P = c.POINTER(Calls)
    for name in ('board_construct', 'slot_object_construct', 'chain_object_construct'):
        function = getattr(n, 'vertrix_' + name)
        function.argtypes = [P, c.POINTER(Services), U]
        function.restype = U
    n.vertrix_special_actor_spawn.argtypes = [P, c.POINTER(Services), U, U, U]
    n.vertrix_special_actor_spawn.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x42e870)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            return operator_new(address, eax, edx, ebx, ecx, stack)
        if address == 0x4abd70:
            returns.append(rng.choice(pool.handles))
        elif address == 0x4b5db0:
            returns.append(eax)
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address in CALLEES:
        stubs.add(address, 0)
    allocations, allocated = [], []

    def operator_new(address, eax, edx, ebx, ecx, stack):
        handle = pool.handles[len(allocations) % len(pool.handles)]
        allocations.append(handle)
        return handle

    stubs.add(0x4ca000, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    @Allocate
    def allocate(size, context):
        assert size == 0x15c
        return allocated.pop(0)

    services = Services(pool.resolve, allocate, None, None, None)
    totals = {}

    def run(name, address, native, **registers):
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        allocations.clear()
        result = original.call(address, **registers) & 0xffffffff
        replay[:] = list(returns)
        allocated[:] = list(allocations)
        got = native()
        assert got == result, (name, hex(got), hex(result))
        assert native_log == [e for e in stubs.log if e[0] != 0x4ca000], (name, native_log[:4],
                                                                          stubs.log[:4])
        assert not allocated, name
        assert not replay, name
        assert pool.same(), (name, pool.diff())
        totals[hex(address)] = totals.get(hex(address), 0) + 1

    for case in range(args.cases):
        pool.fill(rng)
        eax = rng.getrandbits(32)
        run('board', 0x42e870, lambda: n.vertrix_board_construct(c.byref(calls), c.byref(services),
                                                                  eax), eax=eax)
        eax = rng.getrandbits(32)
        run('slot', 0x43d6a0, lambda: n.vertrix_slot_object_construct(
            c.byref(calls), c.byref(services), eax), eax=eax)
        eax = rng.choice(pool.handles)
        allocations.clear()
        stubs.log.clear()
        run('chain', 0x4413b0, lambda: n.vertrix_chain_object_construct(
            c.byref(calls), c.byref(services), eax), eax=eax)
    for case in range(args.cases):
        pool.fill(rng)
        run('special', 0x472570, lambda: n.vertrix_special_actor_spawn(
            c.byref(calls), c.byref(services), 0, 0, 0), eax=0, edx=0, ebx=0, ecx=0)
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Each constructor executes completely in the original, exception frame '
                       'included, with its callees stubbed and logged; every callee call, the '
                       'returned object and every pool object compare.'}
    (args.build_dir / 'object-construct-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
