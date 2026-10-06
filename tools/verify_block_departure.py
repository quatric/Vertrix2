"""Compare complete block departure handler and clipping."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK
from verify_animation import Animation
from verify_timer import Timer


class Departure(c.Structure):
    _fields_ = [('timer', Timer), ('age', c.c_uint32), ('threshold', c.c_int32), ('x', c.c_int16), ('y', c.c_int16), ('step_x', c.c_int16), ('step_y', c.c_int16), ('mode', c.c_uint8), ('mode_target', c.c_uint8), ('mode_step', c.c_int16), ('effect', c.c_int16), ('effect_target', c.c_int16), ('effect_step', c.c_int16), ('field_95', c.c_uint8), ('handler', c.c_uint32), ('left', c.c_int16), ('right', c.c_int16), ('top', c.c_int16), ('bottom', c.c_int16)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    lib = a.build_dir.resolve() / 'block.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', * [str(source / name) for name in ('block_departure.c', 'block_update.c', 'animation.c', 'timer.c')], '-o', str(lib)], check=True)
    n = c.CDLL(str(lib))
    n.vertrix_block_departure_update.argtypes = [c.POINTER(Animation), c.POINTER(c.c_uint32), c.c_size_t, c.c_uint32, c.POINTER(c.c_uint32), c.POINTER(Departure)]
    o = Original(a.executable)
    rng = random.Random(0x44dcf0)
    linked = 0
    def node(address, count, kind, frames=0, children=0, indices=0):
        o.cpu.mem_write(address, struct.pack('<6I', frames, count, 0, children, indices, kind))
    for case in range(1024):
        count = rng.randrange(1, 65)
        ids = [rng.getrandbits(32) for _ in range(64)]
        mapping = [rng.randrange(64) for _ in range(count)]
        second = [rng.randrange(64) for _ in range(64)]
        depth = case % 3
        o.cpu.mem_write(0x803000, struct.pack('<64I', * ids))
        node(0x802000, 64, 0, frames=0x803000)
        if depth:
            o.cpu.mem_write(0x803400, struct.pack('<' + 'I' * count, * ([0x802100 if depth == 2 else 0x802000] * count)))
            o.cpu.mem_write(0x803800, struct.pack('<' + 'I' * count, * mapping))
            node(MASK, count, 1, children=0x803400, indices=0x803800)
            if depth == 2:
                o.cpu.mem_write(0x803a00, struct.pack('<64I', * ([0x802000] * 64)))
                o.cpu.mem_write(0x803c00, struct.pack('<64I', * second))
                node(0x802100, 64, 1, children=0x803a00, indices=0x803c00)
            resolved = [ids[second[index] if depth == 2 else index] for index in mapping]
            linked += 1
        else:
            node(MASK, count, rng.choice([0, 2, 16, 0xffffffff]), frames=0x803000)
            resolved = ids[: count]
        period = rng.randrange(65)
        counter = rng.randrange(129) * (period or 1)
        elapsed = rng.randrange(129) * (period or 1)
        frame = rng.randrange(count)
        animation = Animation(Timer(counter, period), frame, count)
        frames = (c.c_uint32 * count)(* resolved)
        descriptor = c.c_uint32(rng.getrandbits(32))
        raw = bytearray(rng.randbytes(0x160))
        struct.pack_into('<2I', raw, 0xbc, rng.getrandbits(32), rng.choice([0, 1, 100, 0xffffffff]))
        struct.pack_into('<I', raw, 0x154, 0x44dcf0)
        if case < 64:
            elapsed = 0
            struct.pack_into('<2I', raw, 0xbc, 1, 1)
            struct.pack_into('<I', raw, 0x58, 0)
            struct.pack_into('<i', raw, 0x64, case % 2)
            struct.pack_into('<h', raw, 0xe, [200, 201, - 23, - 24][(case // 2) % 4])
            struct.pack_into('<h', raw, 0x16, [0, 200, 201, - 24][(case // 8) % 4])
            struct.pack_into('<h', raw, 0x12, 0)
            struct.pack_into('<h', raw, 0x1a, - 1)
            raw[0x44] = 16
            struct.pack_into('<4h', raw, 0xa8, 0, 200, 0, 200)
        state = Departure(Timer(* struct.unpack_from('<2I', raw, 0xbc)), struct.unpack_from('<I', raw, 0x58)[0], struct.unpack_from('<i', raw, 0x64)[0], struct.unpack_from('<h', raw, 0xe)[0], struct.unpack_from('<h', raw, 0x16)[0], struct.unpack_from('<h', raw, 0x12)[0], struct.unpack_from('<h', raw, 0x1a)[0], * struct.unpack_from('<BBh', raw, 0x44), * struct.unpack_from('<3h', raw, 0x48), raw[0x95], 0x44dcf0, * struct.unpack_from('<4h', raw, 0xa8))
        struct.pack_into('<3I', raw, 0xb0, MASK, descriptor.value, frame)
        struct.pack_into('<2I', raw, 0xcc, counter, period)
        o.cpu.mem_write(BOARD, bytes(raw))
        o.cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        o.call(0x44dcf0, eax=BOARD)
        assert n.vertrix_block_departure_update(c.byref(animation), frames, count, elapsed, c.byref(descriptor), c.byref(state))
        expected = bytearray(raw)
        struct.pack_into('<I', expected, 0xbc, state.timer.counter)
        struct.pack_into('<I', expected, 0x58, state.age)
        struct.pack_into('<h', expected, 0xe, state.x)
        struct.pack_into('<h', expected, 0x16, state.y)
        struct.pack_into('<h', expected, 0x1a, state.step_y)
        struct.pack_into('<BBh', expected, 0x44, state.mode, state.mode_target, state.mode_step)
        struct.pack_into('<3h', expected, 0x48, state.effect, state.effect_target, state.effect_step)
        expected[0x95] = state.field_95
        struct.pack_into('<I', expected, 0x154, state.handler)
        struct.pack_into('<I', expected, 0xb4, descriptor.value)
        struct.pack_into('<I', expected, 0xb8, animation.frame)
        struct.pack_into('<I', expected, 0xcc, animation.timer.counter)
        assert bytes(expected) == bytes(o.cpu.mem_read(BOARD, len(raw))), (case, 'whole normal block')
    prior = bytes(animation), descriptor.value, bytes(state)
    assert not n.vertrix_block_departure_update(c.byref(animation), frames, count - 1, 16, c.byref(descriptor), c.byref(state)) and (bytes(animation), descriptor.value, bytes(state)) == prior
    assert not n.vertrix_block_departure_update(None, frames, count, 16, c.byref(descriptor), c.byref(state))
    report = {'status': 'passed', 'cases': 1024, 'linked_resources': linked, 'scope': 'Actual complete original 0x44dcf0 including animation, primary timer, signed threshold gating, paired transitions, word motion, clipping and frame binding, with no routine hooks. Whole block state matches direct and one/two-level linked resource tables. Native receives independently resolved descriptor order; does not implement resource graph construction, actual VF actor binding or complete object runtime/game.'}
    (a.build_dir / 'block-departure-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
