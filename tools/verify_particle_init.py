"""Compare the original particle initialisers 0x43e740 and 0x43e840 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Resolve, Stubs, build

U = c.c_uint32
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
Allocate = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_void_p)
Range = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_uint32), c.POINTER(c.c_uint32), c.c_void_p)
Bind = c.CFUNCTYPE(None, c.c_uint32, c.c_void_p)
Append = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)
ACTOR, SIZE = 0x80a000, 0x200
WIDTH, HEIGHT = 0x5b9c8e, 0x5b9c90
SCRATCH = {0x43e740: (0x541014, 4), 0x43e840: (0x54101c, 2)}


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', Allocate), ('draw', Draw), ('range', Range),
                ('context', c.c_void_p)]


class Hooks(c.Structure):
    _fields_ = [('bind_frame', Bind), ('append', Append), ('context', c.c_void_p)]


class Screen(c.Structure):
    _fields_ = [('width', c.c_uint16), ('height', c.c_uint16)]


class Scratch(c.Structure):
    _fields_ = [('scratch', c.c_uint16 * 4)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'particle-init',
              ['particle_init.c', 'board_burst.c', 'block_factory.c', 'board_cells.c',
               'board_markers.c', 'actor_storage.c', 'actor_fields.c', 'board.c', 'fixed_point.c',
               'board_actions.c', 'surface.c', 'render_pixel.c', 'render_weights.c',
               'palette_map.c', 'palette_color.c', 'palette_tables.c', 'render_dispatch.c',
               'render_palette.c', 'random.c'])
    for name in ('drift', 'fall'):
        getattr(n, 'vertrix_particle_init_' + name).argtypes = [
            c.c_void_p, c.c_size_t, U, c.POINTER(Screen), c.POINTER(Services), c.POINTER(Hooks),
            c.POINTER(Scratch)]
    n.vertrix_board_particles_reset.argtypes = [c.c_void_p, c.c_size_t]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43e740)
    draws, events, native_events = [], [], []
    replay = {'draws': []}

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4826c0:
            draws.append(rng.randrange(edx & 0xffff))
            return draws[-1]
        events.append(eax)
        return None

    stubs = Stubs(cpu, handler)
    stubs.add(0x4826c0)
    stubs.add(0x4ac8a0)

    @Draw
    def draw(divisor, context):
        value = replay['draws'].pop(0)
        assert value < divisor
        return value

    @Bind
    def bind(actor, context):
        native_events.append(actor)

    services = Services(Resolve(lambda *a: 0), Allocate(lambda s, x: 0), draw,
                        Range(lambda *a: 0), None)
    hooks = Hooks(bind, Append(lambda *a: None), None)
    totals = {}
    for case in range(args.cases):
        address, name = ((0x43e740, 'drift'), (0x43e840, 'fall'))[case % 2]
        width, height = rng.randrange(1, 1200), rng.randrange(1, 900)
        raw = rng.randbytes(SIZE)
        cpu.mem_write(WIDTH, struct.pack('<H', width))
        cpu.mem_write(HEIGHT, struct.pack('<H', height))
        cpu.mem_write(ACTOR, raw)
        draws.clear()
        events.clear()
        native_events.clear()
        original.call(address, eax=0, edx=ACTOR)
        replay['draws'] = list(draws)
        native = c.create_string_buffer(raw, SIZE)
        scratch = Scratch()
        assert getattr(n, 'vertrix_particle_init_' + name)(
            native, SIZE, ACTOR, c.byref(Screen(width, height)), c.byref(services),
            c.byref(hooks), c.byref(scratch)), case
        assert events == native_events, case
        assert native.raw == bytes(cpu.mem_read(ACTOR, SIZE)), (case, name)
        base, count = SCRATCH[address]
        assert list(struct.unpack('<%dH' % count, bytes(cpu.mem_read(base, 2 * count)))) == \
            list(scratch.scratch)[:count], (case, name)
        assert not replay['draws'], case
        totals[name] = totals.get(name, 0) + 1
    board_rng = random.Random(0x43e100)
    for _ in range(args.cases):
        raw = board_rng.randbytes(0xd00)
        cpu.mem_write(ACTOR, raw)
        original.call(0x43e100, eax=ACTOR)
        expected = bytes(cpu.mem_read(ACTOR, 0xd00))
        host = c.create_string_buffer(raw, 0xd00)
        assert n.vertrix_board_particles_reset(host, 0xd00) == 1
        assert host.raw == expected
        totals['reset'] = totals.get('reset', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 43e740, 43e840 and 43e100 execute in the original (the draw 4826c0 '
                       'replayed, the frame binding 4ac8a0 logged); the actor storage, the '
                       'scratch globals, the binding calls and the draws compare.'}
    (args.build_dir / 'particle-init-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
