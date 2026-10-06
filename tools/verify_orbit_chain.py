"""Compare consecutive rotating-effect phases with the original executable."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original, BOARD, MASK
from verify_block_orbit import Orbit, Context, fields
from verify_animation import Animation
from verify_timer import Timer
from verify_rotation import Trace
from verify_rotation_tables import Tables


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'orbit-chain.dylib'
    names = ['block_orbit.c', 'block_update.c', 'animation.c', 'timer.c',
             'rotation.c', 'rotation_tables.c', 'vf.c', 'byte_transition.c',
             'word_transition.c', 'dword_transition.c', 'render_geometry.c',
             'surface.c', 'render_dispatch.c', 'actor_storage.c']
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared',
                    '-fPIC', *[str(source / name) for name in names],
                    '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_block_orbit_update.argtypes = [c.POINTER(Animation),
        c.POINTER(c.c_uint32), c.c_size_t, c.c_uint32, c.POINTER(c.c_uint32),
        c.POINTER(Orbit), c.POINTER(Trace), c.POINTER(Context)]
    original = Original(args.executable)
    original.call(0x4b9050)
    assets = args.executable.resolve().parent.parent / 'assets/table'
    sine = (assets / 'sin.tab').read_bytes()
    cosine = (assets / 'cos.tab').read_bytes()
    tables = Tables((c.c_int32 * 360)(*struct.unpack('<360i', sine)),
                    (c.c_int32 * 360)(*struct.unpack('<360i', cosine)), 1)
    original.cpu.mem_write(0x598dfc, sine)
    original.cpu.mem_write(0x59939c, cosine)
    frames = (c.c_uint32 * 8)(*[0x805000 + 64 * i for i in range(8)])
    original.cpu.mem_write(MASK, struct.pack('<6I', 0x802000, 8, 0, 0, 0, 0))
    original.cpu.mem_write(0x802000, bytes(frames))
    for address in frames:
        original.cpu.mem_write(address, struct.pack('<3I', 0, 24, 24) + bytes(28))
    original.cpu.mem_write(0x544070, struct.pack('<I', 0x809000))
    original.cpu.mem_write(0x809220, bytes([1, 0]))
    context = Context(c.pointer(tables), 24, 24, 1, 1, 0)
    rng = random.Random(0x44dfb0)
    updates = 0
    for case in range(256):
        raw = bytearray(rng.randbytes(0x160))
        struct.pack_into('<I', raw, 0x154, 0x44de20)
        struct.pack_into('<3I', raw, 0xb0, MASK, frames[0], 0)
        struct.pack_into('<2I', raw, 0xbc, 0, rng.randrange(1, 5))
        struct.pack_into('<2I', raw, 0xcc, 0, rng.randrange(1, 5))
        struct.pack_into('<2h', raw, 8, 0, 12 + rng.randrange(96))
        struct.pack_into('<3h', raw, 14, 36, 36, 6)
        struct.pack_into('<3h', raw, 22, 0, 0, 6)
        struct.pack_into('<h', raw, 36, 0)
        struct.pack_into('<h', raw, 40, 0)
        raw[0x44] = 11
        struct.pack_into('<h', raw, 0x46, 1)
        struct.pack_into('<3h', raw, 0x48, 0, 0, 0)
        struct.pack_into('<3i', raw, 0x58, 0, 1, 0)
        struct.pack_into('<i', raw, 0x68, rng.randrange(49))
        raw[0x91] = 1
        original.cpu.mem_write(BOARD, bytes(raw))
        trace = Trace(0, 1)
        original.cpu.mem_write(0x5bb5f8, struct.pack('<I', trace.iterations))
        original.cpu.mem_write(0x5bb5f4, struct.pack('<I', trace.unwrapped))
        phases = []
        for tick in range(512):
            handler = struct.unpack_from('<I', raw, 0x154)[0]
            if handler == 0x44c860:
                break
            if not phases or phases[-1] != handler:
                phases.append(handler)
            elapsed = rng.randrange(1, 9)
            animation = Animation(Timer(*struct.unpack_from('<2I', raw, 0xcc)),
                                  struct.unpack_from('<I', raw, 0xb8)[0], 8)
            descriptor = c.c_uint32(struct.unpack_from('<I', raw, 0xb4)[0])
            state = Orbit(Timer(*struct.unpack_from('<2I', raw, 0xbc)),
                          *[struct.unpack_from('<' + fmt, raw, offset)[0]
                            for name, typ, offset, fmt in fields])
            original.cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
            original.call(handler, eax=BOARD)
            assert native.vertrix_block_orbit_update(c.byref(animation), frames,
                8, elapsed, c.byref(descriptor), c.byref(state), c.byref(trace),
                c.byref(context))
            struct.pack_into('<I', raw, 0xbc, state.timer.counter)
            for name, typ, offset, fmt in fields:
                struct.pack_into('<' + fmt, raw, offset, getattr(state, name))
            struct.pack_into('<I', raw, 0xb4, descriptor.value)
            struct.pack_into('<I', raw, 0xb8, animation.frame)
            struct.pack_into('<I', raw, 0xcc, animation.timer.counter)
            assert bytes(raw) == bytes(original.cpu.mem_read(BOARD, len(raw))), (case, tick)
            assert trace.iterations == struct.unpack('<I', original.cpu.mem_read(0x5bb5f8, 4))[0]
            assert trace.unwrapped == struct.unpack('<I', original.cpu.mem_read(0x5bb5f4, 4))[0]
            updates += 1
        else:
            raise AssertionError('sequence did not finish')
        assert phases == [0x44de20, 0x44dfb0], (case, phases)
    report = {'status': 'passed', 'sequences': 256, 'whole_object_updates': updates,
              'scope': 'Consecutive original 0x44de20 -> 0x44dfb0 -> 0x44c860, '
                       'including frame binding and shared rotation globals, without hooks. '
                       'Timer periods, dimensions and intervals are fixtures; full actor '
                       'runtime and playable game are not verified.'}
    (args.build_dir / 'orbit-chain-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
