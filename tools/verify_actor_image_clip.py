"""Compare original clipping with actor-byte integration."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from verify_actor_image_bounds import Bounds
from verify_render_geometry import Clip, SpriteClip


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'actor-clip.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
        *[str(source / name) for name in ['actor_image_clip.c', 'actor_storage.c',
            'render_geometry.c', 'surface.c', 'render_dispatch.c']], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_actor_image_clip.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(Bounds),
        c.c_uint16, c.c_uint16, Clip, c.POINTER(SpriteClip)]
    native.vertrix_actor_image_clip_offset.argtypes = [c.POINTER(Bounds),
        c.POINTER(SpriteClip), c.c_uint16, c.c_uint8, c.POINTER(c.c_uint32)]
    original = Original(args.executable)
    rng = random.Random(0x4b1a99)
    visible = 0
    for case in range(4096):
x, y = rng.randrange(-128, 769), rng.randrange(-128, 609) width, height = rng.randrange(1, 129),
   rng.randrange(1, 129) mode = rng.choice([ 0, 1, 2, 3, 4, 255 ]) target = (rng.randrange(1, 1025),
                                                                             rng.randrange(1, 1025))
       object_clip = (rng.randrange(-64, 129), rng.randrange(256, 769), rng.randrange(-64, 129),
                      rng.randrange(256, 609))cached = (-16, 655, -16, 495)expected =
           original.sprite_clip(x, y, width, height, cached, mode = mode, target = target,
                                object_clip = object_clip) raw = bytearray(rng.randbytes(0x160))
               raw[0x8e] = mode struct.pack_into('<4h', raw, 0xa8, *object_clip) storage =
                   c.create_string_buffer(bytes(raw), len(raw)) bounds = Bounds(
                       x, y, width, height) result = SpriteClip() before = bytes(result) status =
                       native.vertrix_actor_image_clip(storage, len(raw), c.byref(bounds), *target,
                                                       Clip(*cached), c.byref(result)) assert status
                       == (expected is not None),
   case if expected is None:
assert bytes(result) == before else
    : actual = (result.bounds.left, result.bounds.right, result.bounds.top, result.bounds.bottom,
                result.width, result.height, result.source_offset, result.clipped)assert actual
               == expected,
      (case, actual, expected)scale =
          case % 16 +
          1 source_width = rng.randrange(1, 513) offset = c.c_uint32(0xdeadbeef) columns =
              (result.bounds.left - x) & 65535 rows = (result.bounds.top -
                                                       y) & 65535 expected_offset =
                  (result.source_offset if scale ==
                   16 else original.scale_clip_offset(scale, source_width, columns, rows, 0)) assert
                  native.vertrix_actor_image_clip_offset(c.byref(bounds), c.byref(result),
                                                         source_width, scale, c.byref(offset)) ==
                  1 assert offset.value == expected_offset,
      (case, offset.value, expected_offset)visible +=
      1 assert storage.raw ==
      bytes(raw) before = bytes(result) assert native.vertrix_actor_image_clip(storage, 0x15b,
                                                                               c.byref(bounds),
                                                                               *target,
                                                                               Clip(*cached),
                                                                               c.byref(result)) ==
                          -1 assert bytes(result) == before report = {'status':
'passed', 'cases' : 4096, 'visible' : visible,
                                      'scope'
    : 'Original4b1a99 clipping executes with actor/custom/cached/target modes. ' 'Native actor-storage adapter matches visible rectangles, dimensions, ' 'source offsets and clipped flags; actor bytes remain unchanged and ' 'clipped/invalid output is preserved. Visible source offsets also match ' 'original4ae99f..4aea50 scale advances. Effects ' 'and complete draw/application integration remain unfinished.'
}
(args.build_dir / 'actor-image-clip-verification.json')
        .write_text(json.dumps(report, indent = 2) + '\n') print(json.dumps(report, indent = 2))

            if __name__ == '__main__' : main()
