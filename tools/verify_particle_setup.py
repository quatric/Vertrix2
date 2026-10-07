"""Compare the original particle field setup 0x43e4d0 with the native recovery."""
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
SIZE = 0xd00
WIDTH, HEIGHT = 0x5b9c8e, 0x5b9c90
SURFACE, SURFACE_DATA = 0x80e000, 0x80f000
NAME = 0x1234


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', Allocate), ('draw', Draw), ('range', Range),
                ('context', c.c_void_p)]


class Hooks(c.Structure):
    _fields_ = [('bind_frame', Bind), ('append', Append), ('context', c.c_void_p)]


class Screen(c.Structure):
    _fields_ = [('width', c.c_uint16), ('height', c.c_uint16)]


class Scratch(c.Structure):
    _fields_ = [('scratch', c.c_uint16 * 4)]


class Surface(c.Structure):
    _fields_ = [('data', c.c_void_p), ('size', c.c_size_t), ('width', c.c_uint32),
                ('height', c.c_uint32), ('stride', c.c_uint32), ('bytes_per_pixel', c.c_uint8)]


Load = c.CFUNCTYPE(c.c_void_p, c.c_uint32, c.c_void_p)
Release = c.CFUNCTYPE(None, c.c_void_p, c.c_void_p)


class Loader(c.Structure):
    _fields_ = [('load', Load), ('release', Release), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=256)
    args = parser.parse_args()
    n = build(args.build_dir, 'particle-setup',
              ['particle_init.c', 'call_glue.c', 'board_burst.c', 'block_factory.c', 'board_cells.c',
               'board_markers.c', 'actor_storage.c', 'actor_fields.c', 'board.c', 'fixed_point.c',
               'board_actions.c', 'surface.c', 'render_pixel.c', 'palette_map.c',
               'palette_tables.c', 'palette_color.c', 'render_dispatch.c', 'render_color.c',
               'render_palette.c', 'render_weights.c', 'render_color_bank.c', 'render_geometry.c',
               'render_row.c', 'render_rectangle.c', 'render_preparation.c', 'image.c', 'vf.c', 'random.c'])
    n.vertrix_board_particles_setup.argtypes = [
        c.c_void_p, c.c_size_t, U, U, c.POINTER(Screen), c.POINTER(Services), c.POINTER(Hooks),
        c.POINTER(Loader), c.POINTER(Scratch), c.POINTER(Scratch)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43e4d0)
    pool = Pool(cpu, 9, SIZE)
    board = pool.handles[0]
    targets = pool.handles[1:]
    state = {'surface': None}
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
        if address == 0x4816f0:
            events.append(('load', eax))
            return SURFACE if state['surface'] else 0
        events.append((address, eax))
        return None

    stubs = Stubs(cpu, handler)
    for address in (0x4ca000, 0x4826c0, 0x4ac8a0, 0x4816f0, 0x478d80):
        stubs.add(address)

    @Draw
    def draw(divisor, context):
        value = replay['draws'].pop(0)
        assert value < divisor
        return value

    @Allocate
    def allocate(size, context):
        return replay['allocs'].pop(0)

    @Bind
    def bind(actor, context):
        native_events.append((0x4ac8a0, actor))

    native_surface = {}

    @Load
    def load(name, context):
        native_events.append(('load', name))
        return c.addressof(native_surface['value']) if state['surface'] else None

    @Release
    def release(surface, context):
        native_events.append((0x478d80, SURFACE))

    services = Services(pool.resolve, allocate, draw, Range(lambda *a: 0), None)
    hooks = Hooks(bind, Append(lambda *a: None), None)
    loader = Loader(load, release, None)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        width, height = rng.randrange(1, 1200), rng.randrange(1, 900)
        cpu.mem_write(WIDTH, struct.pack('<H', width))
        cpu.mem_write(HEIGHT, struct.pack('<H', height))
        if rng.random() < 0.75:
            sw, sh, bpp = rng.randrange(1, 9), rng.randrange(1, 9), rng.choice([1, 2, 4])
            density = rng.choice([0.05, 0.3, 0.9])
            pixels = bytes(rng.randrange(1, 256) if rng.random() < density else 0
                           for _ in range(sw * sh * bpp))
            header = bytearray(0x20)
            struct.pack_into('<IIIB', header, 0, SURFACE_DATA, sw, sh, bpp)
            struct.pack_into('<I', header, 0x14, sw * bpp)
            cpu.mem_write(SURFACE, bytes(header))
            cpu.mem_write(SURFACE_DATA, pixels)
            state['surface'] = (sw, sh, bpp)
            data = c.create_string_buffer(pixels, len(pixels) + 16)
            native_surface['value'] = Surface(c.addressof(data), len(pixels), sw, sh, sw * bpp, bpp)
            native_surface['data'] = data
        else:
            state['surface'] = None
        draws.clear()
        allocations.clear()
        events.clear()
        native_events.clear()
        original.call(0x43e4d0, eax=board, edx=NAME)
        replay['draws'] = list(draws)
        replay['allocs'] = list(allocations)
        drift, fall = Scratch(), Scratch()
        assert n.vertrix_board_particles_setup(
            pool.buffers[board], SIZE, board, NAME, c.byref(Screen(width, height)),
            c.byref(services), c.byref(hooks), c.byref(loader), c.byref(drift), c.byref(fall)), case
        assert events == native_events, (case, events[:5], native_events[:5])
        assert pool.same(), (case, pool.diff())
        assert list(struct.unpack('<4H', bytes(cpu.mem_read(0x541014, 8)))) == list(drift.scratch)
        assert list(struct.unpack('<2H', bytes(cpu.mem_read(0x54101c, 4)))) == \
            list(fall.scratch)[:2], case
        assert not replay['draws'] and not replay['allocs'], case
        key = 'picture' if state['surface'] else 'no_picture'
        totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 43e4d0 executes in the original (operator new, the draw, the '
                       'picture loader and release and the frame binding stubbed and replayed or '
                       'logged; the pixel reader 478f10 executed for real); the call log, the '
                       'board, every object and the scratch globals compare.'}
    (args.build_dir / 'particle-setup-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
