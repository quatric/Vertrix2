"""Compare original fixed-color preparation with native state."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original


class Color(c.Structure):
    _fields_ = [('lookup_entry', c.c_uint32), ('color', c.c_uint32), ('half_color', c.c_uint32), ('indices', c.c_uint16 * 3), ('channels', c.c_uint8 * 3), ('hue', c.c_uint8)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'render-color.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', str(source / 'render_color.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_render_color_prepare.argtypes = [c.c_uint8, c.POINTER(c.c_uint32), c.POINTER(c.c_uint32), c.c_size_t, c.c_void_p, c.c_size_t, c.POINTER(Color)]
    original = Original(args.executable)
    original.cpu.mem_map(0x900000, 0x40000)
    rng = random.Random(0x4ae2ff)
    hue_bytes = rng.randbytes(262144)
    hues = c.create_string_buffer(hue_bytes, len(hue_bytes))
    original.cpu.mem_write(0x900000, hue_bytes)
    original.cpu.mem_write(0x54b804, struct.pack('<I', 0x900000))
    for case in range(4096):
        colors = (c.c_uint32 * 13)(* [rng.getrandbits(32) for _ in range(13)])
        entries = (c.c_uint32 * 13)(* [rng.getrandbits(32) for _ in range(13)])
        index = case % 13
        original.cpu.mem_write(0x54b808, struct.pack('<13I', * entries))
        original.cpu.mem_write(0x54b83c, struct.pack('<13I', * colors))
        original.cpu.mem_write(0x5bc000, bytes([index]))
        original.call(0x4ae2ff, stop=0x4ae3b4)
        output = Color()
        assert native.vertrix_render_color_prepare(index, entries, colors, 13, hues, len(hue_bytes), c.byref(output)) == 1
        assert output.lookup_entry == struct.unpack('<I', original.cpu.mem_read(0x54d5d4, 4))[0]
        assert output.color == struct.unpack('<I', original.cpu.mem_read(0x5bc008, 4))[0]
        assert output.half_color == struct.unpack('<I', original.cpu.mem_read(0x54d5ec, 4))[0]
        assert tuple(output.indices) == struct.unpack('<3H', original.cpu.mem_read(0x54d5dc, 6))
        assert bytes(output.channels) == bytes(original.cpu.mem_read(0x54d5e8, 3))
        assert output.hue == original.cpu.mem_read(0x54d5f0, 1)[0]
    before = bytes(output)
    assert native.vertrix_render_color_prepare(13, entries, colors, 13, hues, len(hue_bytes), c.byref(output)) == 0
    assert bytes(output) == before
    assert native.vertrix_render_color_prepare(0, entries, colors, 13, hues, 0, c.byref(output)) == 0
    assert bytes(output) == before
    report = {'status': 'passed', 'cases': 4096, 'scope': 'Original4ae2ff..4ae3b3 executes unchanged with explicit palette ' 'banks and hue table. All fixed-color globals match native fields. ' 'Palette color-bank creation and complete draw preparation remain unfinished.'}
    (args.build_dir / 'render-color-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
