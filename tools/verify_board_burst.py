"""Compare the original spark routines 0x430660 and 0x430440 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
Allocate = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_void_p)
Range = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_uint32), c.POINTER(c.c_uint32), c.c_void_p)
Bind = c.CFUNCTYPE(None, c.c_uint32, c.c_void_p)
Append = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)
SIZE = 0x200


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', Allocate), ('draw', Draw), ('range', Range),
                ('context', c.c_void_p)]


class Hooks(c.Structure):
    _fields_ = [('bind_frame', Bind), ('append', Append), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'board-burst',
              ['board_burst.c', 'block_factory.c', 'board_cells.c', 'board_markers.c',
               'actor_storage.c', 'actor_fields.c', 'board.c', 'fixed_point.c',
               'board_actions.c', 'random.c'])
    for name in ('burst', 'rings'):
        getattr(n, 'vertrix_board_' + name).argtypes = [
            c.c_void_p, c.c_size_t, U, c.c_int32, c.c_int32, c.POINTER(Services),
            c.POINTER(Hooks)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x430660)
    pool = Pool(cpu, 60, 0x200)
    # the rings build 54 actors; the pool objects are the actor storage only
    board = pool.handles[0]
    targets = pool.handles[1:]
    draws, allocations, events, native_events = [], [], [], []
    replay = {'draws': [], 'allocs': []}

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            handle = targets[len(allocations) % len(targets)]
            allocations.append(handle)
            return handle
        if address == 0x4826c0:
            draws.append(rng.randrange(edx & 0xffff))
            return draws[-1]
        events.append((address, eax, edx))
        return None

    stubs = Stubs(cpu, handler)
    for address in (0x4ca000, 0x4826c0, 0x4ac8a0, 0x4b5e70):
        stubs.add(address)

    @Draw
    def draw(divisor, context):
        value = replay['draws'].pop(0)
        assert value < divisor
        return value

    @Allocate
    def allocate(size, context):
        assert size == 0x15c
        return replay['allocs'].pop(0)

    @Range
    def table_range(index, lo, hi, context):
        return 0

    @Bind
    def bind(actor, context):
        native_events.append((0x4ac8a0, actor, None))

    @Append
    def append(list_address, item, context):
        native_events.append((0x4b5e70, list_address, item))

    services = Services(pool.resolve, allocate, draw, table_range, None)
    hooks = Hooks(bind, append, None)
    totals = {}
    for case in range(args.cases):
        address, name = ((0x430660, 'burst'), (0x430440, 'rings'))[case % 2]
        pool.fill(rng)
        draws.clear()
        allocations.clear()
        events.clear()
        native_events.clear()
        x, y = rng.randrange(-2, 8), rng.randrange(-2, 15)
        original.call(address, eax=board, edx=x & 0xffffffff, ebx=y & 0xffffffff)
        replay['draws'] = list(draws)
        replay['allocs'] = list(allocations)
        assert getattr(n, 'vertrix_board_' + name)(pool.buffers[board], SIZE, board, x, y, c.byref(services),
                                     c.byref(hooks)), case
        # the original reports the bind with the actor in eax and the append with item in edx
        original_events = [(a, e, d if a == 0x4b5e70 else None) for a, e, d in events]
        assert original_events == native_events, (case, original_events[:4], native_events[:4])
        assert pool.same(), (case, pool.diff())
        assert not replay['draws'] and not replay['allocs'], case
        totals[hex(address)] = totals.get(hex(address), 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 430660 and 430440 execute in the original (operator new 4ca000 and the draw '
                       '4826c0 stubbed and replayed; the frame binding 4ac8a0 and the list append '
                       '4b5e70 logged); the call log, the board and every object compare.'}
    (args.build_dir / 'board-burst-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
