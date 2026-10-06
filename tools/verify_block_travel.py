"""Compare complete original fade-to-travel block handlers."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK
from verify_animation import Animation
from verify_timer import Timer
fields = [('origin_x', c.c_int16, 8, 'h'), ('origin_y', c.c_int16, 10, 'h'), ('x', c.c_int16, 14, 'h'), ('target_x', c.c_int16, 16, 'h'), ('step_x', c.c_int16, 18, 'h'), ('y', c.c_int16, 22, 'h'), ('target_y', c.c_int16, 24, 'h'), ('step_y', c.c_int16, 26, 'h'), ('current', c.c_int32, 88, 'i'), ('target', c.c_int32, 92, 'i'), ('step', c.c_int32, 96, 'i'), ('handler', c.c_uint32, 340, 'I')]


class Travel(c.Structure):
    _fields_ = [('timer', Timer)] + [(name, typ) for name, typ, offset, fmt in fields]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    lib = a.build_dir.resolve() / 'block.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', * [str(source / name) for name in ('block_travel.c', 'block_update.c', 'animation.c', 'timer.c', 'dword_transition.c', 'word_transition.c', 'actor_storage.c')], '-o', str(lib)], check=True)
    n = c.CDLL(str(lib))
    n.vertrix_block_travel_update.argtypes = [c.POINTER(Animation), c.POINTER(c.c_uint32), c.c_size_t, c.c_uint32, c.POINTER(c.c_uint32), c.POINTER(Travel)]
    o = Original(a.executable)
    rng = random.Random(0x44de20)
    linked = 0
    def node(address, count, kind, frames=0, children=0, indices=0):
        o.cpu.mem_write(address, struct.pack('<6I', frames, count, 0, children, indices, kind))
    for case in range(2048):
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
            struct.pack_into('<2I', raw, 0xbc, rng.randrange(65), rng.randrange(17))
            struct.pack_into('<h', raw, 0x24, rng.randrange(360))
            struct.pack_into('<h', raw, 0x28, rng.choice([0, - 15, 1, 15]))
            raw[0x44] = rng.randrange(17)
            raw[0x91] = rng.randrange(2)
        struct.pack_into('<I', raw, 0x154, 0x44ebe0 if case % 2 == 0 else 0x44ec40)
        state = Travel(Timer(* struct.unpack_from('<2I', raw, 0xbc)), * [struct.unpack_from('<' + fmt, raw, offset)[0] for name, typ, offset, fmt in fields])
        struct.pack_into('<3I', raw, 0xb0, MASK, descriptor.value, frame)
        struct.pack_into('<2I', raw, 0xcc, counter, period)
        o.cpu.mem_write(BOARD, bytes(raw))
        o.cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        o.call(state.handler, eax=BOARD)
        assert n.vertrix_block_travel_update(c.byref(animation), frames, count, elapsed, c.byref(descriptor), c.byref(state))
        expected = bytearray(raw)
        struct.pack_into('<I', expected, 0xbc, state.timer.counter)
        for name, typ, offset, fmt in fields:
            struct.pack_into('<' + fmt, expected, offset, getattr(state, name))
            struct.pack_into('<I', expected, 0xb4, descriptor.value)
        struct.pack_into('<I', expected, 0xb8, animation.frame)
        struct.pack_into('<I', expected, 0xcc, animation.timer.counter)
        assert bytes(expected) == bytes(o.cpu.mem_read(BOARD, len(raw))), (case, 'whole normal block')
        prior = bytes(animation), descriptor.value
        assert not n.vertrix_block_travel_update(c.byref(animation), frames, count - 1, 16, c.byref(descriptor), c.byref(state)) and (bytes(animation), descriptor.value) == prior
        assert not n.vertrix_block_travel_update(None, frames, count, 16, c.byref(descriptor), c.byref(state))
    report = {'status': 'passed', 'cases': 2048, 'linked_resources': linked, 'scope': 'Complete original 0x44ebe0 and 0x44ec40 whole-object comparison without hooks, including dword handoff, origin movement, both-axis completion and frame binding. Gameplay construction remains incomplete.'}
    (a.build_dir / 'block-travel-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
