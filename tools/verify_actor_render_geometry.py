"""Compare direct actor geometry with complete original 0x4ae3e0 preparation."""
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
from verify_sprite_clone import Frame


class Geometry(c.Structure):
    _fields_ = [('bounds', Bounds), ('clip', SpriteClip), ('offset', c.c_uint32), ('scale', c.c_uint8)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'actor-render-geometry.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
        *[str(source / name) for name in ('actor_render_geometry.c', 'actor_image_bounds.c',
        'actor_image_clip.c', 'actor_storage.c', 'render_geometry.c', 'surface.c',
        'render_dispatch.c')], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_actor_render_geometry.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(Frame),
        c.c_uint16, c.c_uint16, Clip, c.POINTER(Geometry)]
    original = Original(args.executable)
    original.call(0x4b9050)
    rng = random.Random(0x4ae3e0)
    visible = 0
    for case in range(4096):
actor = bytearray(0x15c) width,
    height = rng.randrange(1, 33),
    rng.randrange(1, 33) x, y, displacement = rng.randrange(-20, 71), rng.randrange(-20, 71),
    rng.randrange(-5, 6) mode =
        rng.randrange(1, 17) struct.pack_into('<H', actor, 0xe, x & 65535) struct
            .pack_into('<H', actor, 0x16,
                       y & 65535) struct.pack_into('<H', actor, 0x1e,
                                                   displacement & 65535) actor[0x44],
    actor[0x4e], actor[0x8e], actor[0x91] = mode, 100, 1,
    rng.randrange(2) struct.pack_into(
                               '<I', actor, 0xb4,
                               0x801000) struct.pack_into('<I', actor, 0x134,
                                                          0x804000) struct.pack_into('<I', actor,
                                                                                     0x13c, 1)
        frame = Frame() frame.image.width,
    frame.image.height = width,
    height frame.metadata [0:5] =
        [
            0x804000, width, height, rng.randrange(-5, 6) & 65535, rng.randrange(-5, 6) & 65535
        ] frame.metadata[9] = 4 << 24 original.cpu.mem_write(0x800000, bytes(actor)) original.cpu
                                       .mem_write(0x801000, bytes(frame.metadata)) target =
                                  bytearray(0x28) struct.pack_into('<3I', target, 0, 0x808000, 64,
                                                                   64) target[0xc],
    target[0xd] = 4,
    4 struct.pack_into('<I', target, 0x14,
                       256) original.cpu.mem_write(0x802000, bytes(target)) original.cpu
        .mem_write(0x5bc010, struct.pack('<I', 0x802000)) expected_visible =
        original.call(0x4ae3e0, eax = 0x800000, edx = 1) storage = c.create_string_buffer(
            bytes(actor), len(actor)) result = Geometry() before = bytes(result) status =
            native.vertrix_actor_render_geometry(storage, len(actor), c.byref(frame), 64, 64,
                                                 Clip(0, 63, 0, 63), c.byref(result))
                assert(status == 1) == (expected_visible == 1),
    (case, status, expected_visible) if status == 1
    : expected_size = struct.unpack('<2H', original.cpu.mem_read(0x5bb750, 4)) expected_offset =
        struct.unpack('<I', original.cpu.mem_read(0x5bb790,
                                                  4))[0] assert(result.clip.width,
                                                                result.clip.height) == expected_size
    ,
    (case, expected_size)assert result.offset == expected_offset,
    (case, result.offset, expected_offset)target_pointer =
        struct.unpack('<I', original.cpu.mem_read(0x5bb768, 4))[0] assert target_pointer ==
        (0x808000 + result.clip.bounds.top * 256 + result.clip.bounds.left * 4),
    (case, hex(target_pointer))visible +=
    1 else : assert bytes(result) == before before =
        bytes(result) assert native.vertrix_actor_render_geometry(storage, len(actor) - 1,
                                                                  c.byref(frame), 64, 64,
                                                                  Clip(0, 63, 0, 63),
                                                                  c.byref(result)) ==
        -1 assert bytes(result) == before report = {
            'status' : 'passed',
            'original_direct_geometry_cases' : 4096,
            'visible_cases' : visible,
            'invalid_storage_preservation_cases' : 4096,
            'scope' :
                'Complete original 0x4ae3e0 direct-coordinate preparation compares visibility, ' 'visible dimensions and source offsets. Target clipping mode1, scale1..16, ' 'descriptor anchors, displacement and ignored screen override are covered. ' 'Drawing, other clip modes and full application remain unfinished.'
        }(args.build_dir / 'actor-render-geometry-verification.json')
                                                       .write_text(json.dumps(report, indent = 2) +
                                                                   '\n')
                                                           print(json.dumps(report, indent = 2))

                                                               if __name__
                                                   == '__main__' : main()
