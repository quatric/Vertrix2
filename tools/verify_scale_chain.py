"""Compare successive original scale-to-fade phases without routine hooks."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original, BOARD, MASK
from verify_animation import Animation
from verify_timer import Timer
from verify_block_scale import Motion as Scale
from verify_block_fade import Motion as Fade


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = a.build_dir.resolve() / 'chain.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    *[str(source / name) for name in ['block_scale.c','dword_transition.c', 'block_byte_pulse.c',
                    'block_update.c', 'animation.c', 'timer.c']], '-o', str(library)], check=True)
    n = c.CDLL(str(library))
    common = [c.POINTER(Animation), c.POINTER(c.c_uint32), c.c_size_t,
              c.c_uint32, c.POINTER(c.c_uint32)]
    n.vertrix_block_scale_update.argtypes = common + [c.POINTER(Scale)]
    n.vertrix_block_byte_pulse_update.argtypes = common + [c.POINTER(Fade)]
    o = Original(a.executable)
    rng = random.Random(0x44d330)
    frames = (c.c_uint32 * 8)(*[rng.getrandbits(32) for _ in range(8)])
    o.cpu.mem_write(MASK, struct.pack('<6I', 0x802000, 8, 0, 0, 0, 0))
    o.cpu.mem_write(0x802000, bytes(frames))
    updates = 0
    for case in range(256):
        raw = bytearray(rng.randbytes(0x160))
        struct.pack_into('<I', raw, 0x154, 0x44d330)
        struct.pack_into('<3I', raw, 0xb0, MASK, rng.getrandbits(32), rng.randrange(8))
        struct.pack_into('<2I', raw, 0xbc, 0, rng.randrange(5))
        struct.pack_into('<2I', raw, 0xcc, 0, rng.randrange(5))
        struct.pack_into('<i', raw, 0x58, rng.randrange(101))
        raw[0x4e] = rng.randrange(101)
        o.cpu.mem_write(BOARD, bytes(raw))
        phases = []
        for tick in range(512):
            handler = struct.unpack_from('<I', raw, 0x154)[0]
            if handler == 0x44c860:
                break
            if not phases or phases[-1] != handler:
                phases.append(handler)
            elapsed = rng.randrange(1, 9)
            o.cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
            o.call(handler, eax=BOARD)
            animation = Animation(Timer(*struct.unpack_from('<2I', raw, 0xcc)),
                                  struct.unpack_from('<I', raw, 0xb8)[0], 8)
            descriptor = c.c_uint32(struct.unpack_from('<I', raw, 0xb4)[0])
            timer = Timer(*struct.unpack_from('<2I', raw, 0xbc))
            if handler in (0x44d330, 0x44d3a0):
                state = Scale(timer, *struct.unpack_from('<3i', raw, 0x58),
                              *struct.unpack_from('<3h', raw, 0x48), raw[0x4e], raw[0x95], handler)
                assert n.vertrix_block_scale_update(c.byref(animation), frames, 8, elapsed,
                                                    c.byref(descriptor), c.byref(state))
                struct.pack_into('<3i', raw, 0x58, state.current, state.target, state.step)
                struct.pack_into('<3h', raw, 0x48, state.effect, state.effect_target, state.effect_step)
                raw[0x4e], raw[0x95] = state.amount, state.field_95
            else:
                assert handler == 0x44d410
                state = Fade(timer, *struct.unpack_from('<BBh', raw, 0x4e), raw[0x93], handler)
                assert n.vertrix_block_byte_pulse_update(c.byref(animation), frames, 8, elapsed,
                                                         c.byref(descriptor), c.byref(state))
                struct.pack_into('<BBh', raw, 0x4e, state.current, state.target, state.step)
                raw[0x93] = state.field_93
            struct.pack_into('<I', raw, 0xbc, state.timer.counter)
            struct.pack_into('<I', raw, 0x154, state.handler)
            struct.pack_into('<I', raw, 0xcc, animation.timer.counter)
            struct.pack_into('<I', raw, 0xb8, animation.frame)
            struct.pack_into('<I', raw, 0xb4, descriptor.value)
            assert bytes(raw) == bytes(o.cpu.mem_read(BOARD, len(raw))), (case, tick, hex(handler))
            updates += 1
        else:
            raise AssertionError('sequence did not finish')
        assert phases == [0x44d330, 0x44d3a0, 0x44d410]
        assert raw[0x4e] == 100 and struct.unpack_from('<i', raw, 0x58)[0] == 100
    report = {'status': 'passed', 'sequences': 256, 'whole_object_updates': updates,
              'scope': 'Successive original 0x44d330 -> 0x44d3a0 -> 0x44d410 -> 0x44c860 '
              'compared without hooks. Random timer periods and frame intervals are fixtures. '
              'No full actor runtime or playable-game execution is claimed.'}
    (a.build_dir / 'scale-chain-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
