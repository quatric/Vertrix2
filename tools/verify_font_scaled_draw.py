"""Verify original scaled glyph origins and integration with binary sampling."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from unicorn.x86_const import UC_X86_REG_EBP
from original import Original
from verify_font_bank import Bank
from verify_font_run import Placement
from verify_font_draw import Surface


class Bounds(c.Structure):
    _fields_ = [('x', c.c_int16), ('y', c.c_int16), ('width', c.c_uint16), ('height', c.c_uint16)]


def word(value):
    return ((value + 32768) & 65535) - 32768


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / 'scaled-draw.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
        *[str(root / 'source' / name) for name in ('font_draw.c', 'font_run.c', 'font_binding.c',
          'font_measure.c', 'render_geometry.c', 'surface.c', 'render_dispatch.c')],
        '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_font_glyph_bounds.argtypes = [c.POINTER(Bank), c.POINTER(Placement), c.c_uint8, c.POINTER(Bounds)]
    native.vertrix_font_draw_glyph_scaled.argtypes = [c.POINTER(Bank), c.POINTER(Placement), c.c_uint8, c.POINTER(Surface)]
    original = Original(args.executable)
    original.call(0x4b9050)
    bank = Bank()
    bank.ready = 1
    rng = random.Random(0x4aed56)
    for case in range(2048):
        index = rng.randrange(548)
        width, height = rng.randrange(1, 32768), rng.randrange(1, 32768)
        scale = rng.randrange(16)
        ox, oy = rng.getrandbits(32), rng.getrandbits(32)
        x, y = rng.randrange(-32768, 32768), rng.randrange(-32768, 32768)
        bank.glyphs[index].width, bank.glyphs[index].height, bank.glyphs[index].rgba = width, height, 1
        bank.origin_x[index], bank.origin_y[index] = ox, oy
        for address, value in ((0x5bb7b4, width), (0x5bb7b6, height), (0x5bb7b0, ox), (0x5bb7b2, oy)):
            original.cpu.mem_write(address, struct.pack('<H', value & 65535))
        original.cpu.mem_write(0x5bb738, bytes([scale]))
        original.cpu.reg_write(UC_X86_REG_EBP, 0x709000)
        original.call(0x4aed56, stop=0x4aee28)
        mw, mh = struct.unpack('<2H', original.cpu.mem_read(0x5bb74c, 4))
        ax, ay = struct.unpack('<2h', original.cpu.mem_read(0x5bb7b0, 4))
        placement = Placement(index, x, y, 65)
        bounds = Bounds()
        assert native.vertrix_font_glyph_bounds(c.byref(bank), c.byref(placement), scale, c.byref(bounds))
        assert (bounds.x, bounds.y, bounds.width, bounds.height) == (word(x - ax), word(y - ay), mw, mh)
    for case in range(512):
        index = rng.randrange(548)
        width, height = rng.randrange(1, 33), rng.randrange(1, 33)
        scale = case % 17
        ox, oy = rng.randrange(8), rng.randrange(8)
        x, y = rng.randrange(-15, 55), rng.randrange(-15, 55)
        raw = bytearray(rng.randbytes(width * height * 4))
        raw[3::4] = bytes(rng.choice([0, 1, 128, 255]) for _ in range(width * height))
        pixels = c.create_string_buffer(bytes(raw))
        bank.glyphs[index].width, bank.glyphs[index].height = width, height
        bank.glyphs[index].rgba = c.addressof(pixels)
        bank.origin_x[index], bank.origin_y[index] = ox, oy
        dx, dy, mw, mh = original.resource_bounds(width, height, ox, oy, scale, x, y)
        dx, dy = word(dx), word(dy)
        target_raw = rng.randbytes(48 * 48 * 4)
        expected = bytearray(target_raw)
        advances = bytes(original.cpu.mem_read(0x5c1c00 + scale * 1024, 1024)) if 0 < scale < 16 else bytes([1]) * 1024
        sy = 0
        for row in range(mh):
            sx = 0
            for column in range(mw):
                tx, ty = dx + column, dy + row
                source = (sy * width + sx) * 4
                if 0 <= tx < 48 and 0 <= ty < 48 and raw[source + 3]:
                    destination = (ty * 48 + tx) * 4
                    expected[destination:destination + 4] = raw[source:source + 4]
                sx += advances[column]
            sy += advances[row]
        storage = c.create_string_buffer(target_raw)
        target = Surface(c.addressof(storage), len(target_raw), 48, 48, 192, 4)
        placement = Placement(index, x, y, 65)
        result = native.vertrix_font_draw_glyph_scaled(c.byref(bank), c.byref(placement), scale, c.byref(target))
        assert result >= 0
        assert storage.raw[:len(target_raw)] == expected, (case, scale)
        assert pixels.raw[:len(raw)] == raw
    report = {'status': 'passed', 'original_anchor_cases': 2048, 'draw_cases': 512,
              'scope': 'Actual4aed56..4aee28 measured dimensions and scaled anchors '
                       'match without hooks. Basic scaled binary image integration checks '
                       'pixels against actual original4b15e0 bounds and4b9050 sample tables, '
                       'all scale0..16, clipping and nonzero alpha values. Original full '
                       'sprite preparation, parent effects/custom clips and complete styled '
                       'text/application integration remain separate.'}
    (args.build_dir / 'font-scaled-draw-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
