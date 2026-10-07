"""Compare the original particle initialisers 0x43e740 and 0x43e840 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Resolve, Stubs, build
from verify_call_glue import Call, Calls

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
               'call_glue.c', 'palette_map.c', 'palette_color.c', 'palette_tables.c', 'render_dispatch.c',
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
    full, mutations, failures = verify_full(n, Original(args.executable), args.cases)
    report = {'full_return_and_storage_comparisons': full,
              'mutable_callback_cases': mutations, 'native_late_failure_cases': failures, 'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 43e740, 43e840 and 43e100 execute in the original (the draw 4826c0 '
                       'replayed, the frame binding 4ac8a0 logged); the actor storage, the '
                       'scratch globals, the binding calls and the draws compare. Full APIs additionally compare '
                       'exact EAX, call registers, independent live mutable storage and boundary failures.'}
    (args.build_dir / 'particle-init-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


Read = c.CFUNCTYPE(c.c_int, U, c.c_uint, c.POINTER(U), c.c_void_p)
Write = c.CFUNCTYPE(c.c_int, U, c.c_uint, U, c.c_void_p)


def verify_full(native, original, cases):
    # Separate oracle hooks and separate backing keep mutations independent.
    cpu = original.cpu
    rng = random.Random(0x43e840)
    regions = {}
    oracle_log, host_log, contexts = [], [], []
    mode = 0
    address = 0
    returned = []
    fail = None

    def locate(a, width):
        for base, data in regions.items():
            if base <= a and a + width <= base + len(data):
                return data, a - base
        return None, None

    def host_store(a, data):
        region, offset = locate(a, len(data))
        if region is None:
            raise RuntimeError(('unmapped callback mutation', a))
        region[offset:offset + len(data)] = data

    def effects(index, store):
        base = SCRATCH[address][0]
        if mode == 1 and index == 0:
            store(base, struct.pack('<2H', 311, 277))
            if address == 0x43e740:
                store(base + 4, struct.pack('<2H', 29, 41))
        if mode == 2 and index == 1:
            if address == 0x43e740:
                store(base + 2, struct.pack('<3H', 177, 83, 91))
            else:
                store(ACTOR + 0xa, struct.pack('<H', 177))
        if mode == 3 and index == 3:
            store(ACTOR + 0x64, struct.pack('<I', 0xfedc0000))
            store(ACTOR + 0x71, b'abc')
        if mode == 4 and index == 2 and address == 0x43e740:
            store(base + 6, struct.pack('<H', 0x8001))

    def handler(target, eax, edx, ebx, ecx, stack):
        index = len(oracle_log)
        oracle_log.append((target, eax, edx, ebx, ecx))
        effects(index, cpu.mem_write)
        # High bits intentionally nonzero; original uses AX at each draw site.
        value = rng.getrandbits(32) if target == 0x4ac8a0 else \
            (rng.getrandbits(16) << 16) | rng.randrange(max(1, edx & 0xffff))
        returned.append(value)
        return value

    stubs = Stubs(cpu, handler)
    stubs.add(0x4826c0)
    stubs.add(0x4ac8a0)

    @Read
    def read(a, width, value, context):
        contexts.append(context)
        data, offset = locate(a, width)
        if data is None or fail == ('read', a):
            return 0
        value[0] = int.from_bytes(data[offset:offset + width], 'little')
        return 1

    @Write
    def write(a, width, value, context):
        contexts.append(context)
        data, offset = locate(a, width)
        if data is None or fail == ('write', a):
            return 0
        data[offset:offset + width] = value.to_bytes(4, 'little')[:width]
        return 1

    @Call
    def call(pointer, context):
        site = pointer.contents
        contexts.append(context)
        index = len(host_log)
        host_log.append((site.target, site.eax, site.edx, site.ebx, site.ecx))
        effects(index, host_store)
        return returned[index] if index < len(returned) else 0

    calls = Calls(call, 0x1234)
    totals, mutations = {}, {}
    for name, address in (('drift', 0x43e740), ('fall', 0x43e840)):
        function = getattr(native, 'vertrix_particle_init_' + ('burst' if name == 'drift' else name) + '_full')
        function.argtypes = [U, U, Read, Write, c.c_void_p, c.POINTER(Calls), c.POINTER(U)]
        for case in range(cases + 4):
            mode = 0 if case < cases else case - cases + 1
            raw = rng.randbytes(SIZE)
            regions = {ACTOR: bytearray(raw), WIDTH: bytearray(struct.pack('<2H',
                rng.randrange(1, 1200), rng.randrange(1, 900))),
                0x541014: bytearray(rng.randbytes(12))}
            for base, data in regions.items():
                cpu.mem_write(base, bytes(data))
            oracle_log.clear(); host_log.clear(); contexts.clear(); returned.clear()
            ebx = rng.getrandbits(32)
            expected = original.call(address, eax=rng.getrandbits(32), edx=ACTOR,
                                     ebx=ebx, ecx=rng.getrandbits(32))
            output = U(0xdeadbeef)
            assert function(ACTOR, ebx, read, write, 0x1234, c.byref(calls), c.byref(output))
            assert output.value == expected, (name, case, output.value, expected)
            assert host_log == oracle_log and len(host_log) == 4, (name, case, host_log, oracle_log)
            assert contexts and all(x == 0x1234 for x in contexts), (name, case, contexts)
            assert all(bytes(data) == bytes(cpu.mem_read(base, len(data)))
                       for base, data in regions.items()), (name, case)
            totals[name] = totals.get(name, 0) + 1
            mutations[name] = mutations.get(name, 0) + bool(mode)
    failures = 0
    mode = 1
    for name, address in (('drift', 0x43e740), ('fall', 0x43e840)):
        function = getattr(native, 'vertrix_particle_init_' + ('burst' if name == 'drift' else name) + '_full')
        for failure in [('write', ACTOR + 0xc0), ('read', SCRATCH[address][0]),
                        ('write', ACTOR + 0x60)]:
            regions = {ACTOR: bytearray(b'\xaa' * SIZE), WIDTH: bytearray(struct.pack('<2H', 100, 80)),
                       0x541014: bytearray(12)}
            host_log.clear(); contexts.clear()
            returned[:] = [0x12345678, 0xdead0005, 0xabcd0007, 0xff000002]
            fail = failure
            output = U(0xdeadbeef)
            assert not function(ACTOR, 123, read, write, 0x1234, c.byref(calls), c.byref(output))
            assert output.value == 0xdeadbeef
            expected_calls = (4 if name == 'drift' else 3) if failure == ('write', ACTOR + 0x60) else 1
            assert len(host_log) == expected_calls, (name, failure, host_log)
            base, offset = locate(SCRATCH[address][0], 4)
            assert bytes(base[offset:offset + 4]) == struct.pack('<2H', 311, 277)
            assert all(x == 0x1234 for x in contexts)
            assert int.from_bytes(regions[ACTOR][0xb0:0xb4], 'little') == \
                (0x544c10 if name == 'drift' else 0x544c64)
            failures += 1
    fail = None
    assert totals == {'drift': cases + 4, 'fall': cases + 4}
    assert mutations == {'drift': 4, 'fall': 4} and failures == 6
    return totals, mutations, failures


if __name__ == '__main__':
    main()
