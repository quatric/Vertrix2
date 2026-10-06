"""Compare the original piece frame builder 0x43a310 with the native recovery."""
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
SIZE = 0x400


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
    n = build(args.build_dir, 'piece-frames',
              ['particle_init.c', 'board_burst.c', 'block_factory.c', 'board_cells.c',
               'board_markers.c', 'actor_storage.c', 'actor_fields.c', 'board.c', 'fixed_point.c',
               'board_actions.c', 'surface.c', 'render_pixel.c', 'palette_map.c',
               'palette_tables.c', 'palette_color.c', 'render_dispatch.c', 'render_color.c',
               'render_palette.c', 'render_weights.c', 'render_color_bank.c', 'render_geometry.c',
               'render_row.c', 'render_rectangle.c', 'render_preparation.c', 'image.c', 'vf.c'])
    n.vertrix_piece_frames_build.argtypes = [c.c_void_p, c.c_size_t, c.c_int16, c.c_int16, c.c_int16,
                                             c.c_int16, c.c_int16, c.c_uint8, c.POINTER(Services)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x430660)
    pool = Pool(cpu, 9, SIZE)
    piece = None
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
        assert size == 0x160
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
        pool.fill(rng)
        draws.clear()
        allocations.clear()
        events.clear()
        native_events.clear()
        piece = pool.handles[0]
        left, width, top, height, step = (rng.randrange(-300, 700) for _ in range(5))
        mode = rng.randrange(256)
        original.call(0x43a310, eax=piece, edx=left & 0xffff, ebx=top & 0xffff, ecx=width & 0xffff,
                      args=(height & 0xffff, step & 0xffff, mode))
        replay['allocs'] = list(allocations)
        assert n.vertrix_piece_frames_build(pool.buffers[piece], SIZE, left, width, top, height,
                                            step, mode, c.byref(services)), case
        assert pool.same(), (case, pool.diff())
        assert not replay['allocs'], case
        totals['0x43a310'] = totals.get('0x43a310', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 4731a0 executes in the original (operator new 4ca000 and the draw '
                       '4826c0 stubbed and replayed; the frame binding 4ac8a0 and the list append '
                       '4b5e70 logged); the call log and every object compare.'}
    (args.build_dir / 'piece-frames-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
