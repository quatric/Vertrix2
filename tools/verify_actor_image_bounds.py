"""Compare original descriptor geometry with portable actor/image integration."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original, BOARD, MASK, COUNTER
from verify_sprite_clone import Image


class Bounds(c.Structure):
    _fields_ = [(name, c.c_int32) for name in ['x', 'y', 'width', 'height']]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'actor-bounds.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
        *[str(source / name) for name in ['actor_image_bounds.c', 'actor_storage.c',
            'render_geometry.c', 'surface.c', 'render_dispatch.c']], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_actor_image_bounds.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(Image),
        c.c_uint32, c.c_uint32, c.c_uint8, c.c_uint8, c.POINTER(Bounds)]
    original = Original(args.executable)
    rng = random.Random(0x4b15e0)
    for case in range(4096):
        width, height = rng.randrange(1, 1025), rng.randrange(1, 1025)
        origin_x, origin_y = rng.getrandbits(32), rng.getrandbits(32)
        x, y = rng.randrange(-32768, 32768), rng.randrange(-32768, 32768)
        mode, override, unscaled, screen_mode = rng.randrange(17), rng.randrange(2), rng.randrange(2), rng.randrange(17)
        original.resource_measure(width, height, mode, screen_override=override,
                                  screen_unscaled=unscaled, screen_mode=screen_mode)
        original.cpu.mem_write(MASK + 12, struct.pack('<2I', origin_x, origin_y))
        original.cpu.mem_write(BOARD + 0xe, struct.pack('<h', x))
        original.cpu.mem_write(BOARD + 0x16, struct.pack('<h', y))
        original.call(0x4b15e0, edx=COUNTER, ebx=COUNTER + 4, ecx=COUNTER + 8, args=(COUNTER + 12,))
        expected = tuple(struct.unpack('<4i', original.cpu.mem_read(COUNTER, 16)))
        storage = c.create_string_buffer(bytes(original.cpu.mem_read(BOARD, 0x160)), 0x160)
        image = Image(width, height, None)
        bounds = Bounds()
        assert native.vertrix_actor_image_bounds(storage, len(storage), c.byref(image),
            origin_x, origin_y, unscaled, screen_mode, c.byref(bounds))
        assert tuple(getattr(bounds, name) for name in ['x', 'y', 'width', 'height']) == expected, case
    before = bytes(bounds)
    assert not native.vertrix_actor_image_bounds(storage, 0x15b, c.byref(image), 0, 0, 0, 16, c.byref(bounds))
    assert bytes(bounds) == before
    report = {'status':
        'passed', 'cases' : 4096,
            'scope'
            : 'Complete original4b15e0 descriptor bounds execute unchanged. Native actor ' 'storage/image integration matches modes0..16, screen overrides, wrapped ' 'positions and low-word descriptor origins. Invalid short storage preserves ' 'output. Clipping/effects/drawing and full application remain unfinished.'
        }
        (args.build_dir / 'actor-image-bounds-verification.json')
                .write_text(json.dumps(report, indent = 2) + '\n')
                    print(json.dumps(report, indent = 2))

                        if __name__ == '__main__' : main()
