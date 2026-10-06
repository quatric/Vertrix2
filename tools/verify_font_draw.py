"""Verify original glyph origin positioning and binary sprite drawing integration."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original
from verify_font_bank import Bank
from verify_font_run import Placement


class Surface(c.Structure):
    _fields_ = [('data', c.c_void_p), ('size', c.c_size_t), ('width', c.c_uint32),
                ('height', c.c_uint32), ('stride', c.c_uint32), ('bytes_per_pixel', c.c_uint8)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / 'draw.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
        *[str(root / 'source' / name) for name in ('font_draw.c', 'font_run.c', 'font_binding.c', 'font_measure.c', 'render_geometry.c',
          'surface.c', 'render_dispatch.c')], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_font_glyph_position.argtypes = [c.POINTER(Bank), c.c_uint16,
        c.c_int16, c.c_int16, c.POINTER(c.c_int16), c.POINTER(c.c_int16)]
    native.vertrix_font_draw_glyph.argtypes = [c.POINTER(Bank), c.POINTER(Placement), c.POINTER(Surface)]
    original = Original(args.executable)
    bank = Bank()
    bank.ready = 1
    rng = random.Random(0x4ae6fa)
    for case in range(2048):
        index = rng.randrange(548)
        x, y = rng.randrange(-32768, 32768), rng.randrange(-32768, 32768)
        ox, oy = rng.getrandbits(32), rng.getrandbits(32)
        bank.origin_x[index], bank.origin_y[index] = ox, oy
        for address, value in ((0x5bb7a0, x), (0x5bb7a2, y), (0x5bb7b0, ox),
                               (0x5bb7b2, oy), (0x5bb7ae, 0), (0x5bb74c, 12)):
            original.cpu.mem_write(address, struct.pack('<H', value & 65535))
        original.call(0x4ae6fa, ebx=12, ecx=12, stop=0x4ae747)
        px, py = c.c_int16(), c.c_int16()
        assert native.vertrix_font_glyph_position(c.byref(bank), index, x, y, c.byref(px), c.byref(py))
        expected_x = struct.unpack('<h', original.cpu.mem_read(0x5bb7a0, 2))[0]
        expected_y = struct.unpack('<h', original.cpu.mem_read(0x5bb7a2, 2))[0]
        assert (px.value, py.value) == (expected_x, expected_y)
    for case in range(1024):
        index = rng.randrange(548)
        width, height = rng.randrange(1, 33), rng.randrange(1, 33)
        raw = bytearray(rng.randbytes(width * height * 4))
        raw[3::4] = bytes(rng.choice([0, 1, 128, 255]) for _ in range(width * height))
        source_storage = c.create_string_buffer(bytes(raw))
        bank.glyphs[index].width, bank.glyphs[index].height = width, height
        bank.glyphs[index].rgba = c.addressof(source_storage)
        ox, oy = rng.randrange(21), rng.randrange(21)
        bank.origin_x[index], bank.origin_y[index] = ox, oy
        x, y = rng.randrange(-30, 70), rng.randrange(-30, 70)
        placement = Placement(index, x, y, 65)
        target_raw = rng.randbytes(48 * 48 * 4)
        expected = bytearray(target_raw)
        for sy in range(height):
            for sx in range(width):
                tx, ty = x - ox + sx, y - oy + sy
                offset = (sy * width + sx) * 4
                if 0 <= tx < 48 and 0 <= ty < 48 and raw[offset + 3]:
                    destination = (ty * 48 + tx) * 4
                    expected[destination:destination + 4] = raw[offset:offset + 4]
        target_storage = c.create_string_buffer(target_raw)
        target = Surface(c.addressof(target_storage), len(target_raw), 48, 48, 192, 4)
        result = native.vertrix_font_draw_glyph(c.byref(bank), c.byref(placement), c.byref(target))
        assert result >= 0
        assert target_storage.raw[:len(target_raw)] == expected, case
        assert source_storage.raw[:len(raw)] == raw
    report = {'status': 'passed', 'original_origin_cases': 2048, 'draw_cases': 1024,
              'scope': 'Actual4ae6fa..4ae747 origin arithmetic matches without hooks. '
                       'Owned-image draw adapter composes separately oracle-verified clipping '
                       'and binary pixel renderer; integration pixels independently checked '
                       'with randomized alpha/background/edge clipping. Whole original '
                       'sprite preparation, nonzero viewport origins and application integration '
                       'remain separate.'}
    (args.build_dir / 'font-draw-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
