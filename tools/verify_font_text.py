"""Verify complete original VF text rendering composition and export a font preview."""
import argparse
import ctypes as c
import json
import random
import subprocess
from pathlib import Path
from PIL import Image, ImageDraw
from verify_font_bank import Bank
from verify_font_map import FontMap
from verify_font_draw import Surface


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('archive', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    names = ['font_draw.c', 'font_run.c', 'font_binding.c', 'font_map.c', 'font_measure.c',
             'font_bank.c', 'font_stencils.c', 'sprite_files.c', 'font_sheet.c', 'font_cell.c', 'font_image.c',
             'font_outline.c', 'font_stencil.c', 'image_crop.c', 'image_key.c', 'image.c',
             'vf.c', 'render_geometry.c', 'surface.c', 'render_dispatch.c']
    library = args.build_dir.resolve() / 'text.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    *[str(root / 'source' / name) for name in names], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_vf_open.argtypes = [c.c_char_p]
    native.vertrix_vf_open.restype = c.c_void_p
    native.vertrix_vf_close.argtypes = [c.c_void_p]
    native.vertrix_font_bank_load.argtypes = [c.c_void_p, c.POINTER(c.c_uint32), c.POINTER(Bank)]
    native.vertrix_font_bank_free.argtypes = [c.POINTER(Bank)]
    native.vertrix_font_map_construct.argtypes = [c.POINTER(FontMap)]
    native.vertrix_font_maps_initialize.argtypes = [c.POINTER(FontMap), c.c_size_t] + [c.c_uint32] * 4
    native.vertrix_font_draw_text.argtypes = [c.POINTER(Bank), c.POINTER(FontMap), c.c_void_p,
        c.c_size_t, c.c_uint32, c.c_int16, c.POINTER(Surface), c.POINTER(c.c_size_t), c.POINTER(c.c_uint32)]
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    bank = Bank()
    masks = (c.c_uint32 * 3)(0xff0000, 0xff00, 0xff)
    assert native.vertrix_font_bank_load(archive, masks, c.byref(bank))
    native.vertrix_vf_close(archive)
    maps = (FontMap * 19)()
    for mapping in maps:
        assert native.vertrix_font_map_construct(c.byref(mapping))
    assert native.vertrix_font_maps_initialize(maps, 19, 15, 15, 21, 21)
    glyphs = [c.string_at(image.rgba, image.width * image.height * 4) for image in bank.glyphs]
    rng = random.Random(0x4404904ae6fa)
    cases = 0
    for font in range(19):
        for sample in range(16):
            text = (b'GO VS ABC 0123?@' if sample == 0 else bytes(
                    rng.choice(b'GO VS ABCXYZ0123456789!?@\xff\xfe') for _ in range(rng.randrange(25)))) + b'\0'
            x = (rng.getrandbits(16) << 16) | (rng.randrange(-60, 120) & 65535)
            y = rng.randrange(-30, 70)
            stride = 320 * 4 + 16
            initial = rng.randbytes(stride * 80)
            expected = bytearray(initial)
            position, expected_drawn = x, 0
            for glyph in text[:-1]:
                if glyph == 32:
                    position = (position + maps[font].space_width + 1) & 0xffffffff
                    continue
                index = maps[font].glyphs[glyph]
                if index == -1:
                    continue
                image = bank.glyphs[index]
                dx = ((position - bank.origin_x[index] + 32768) & 65535) - 32768
                dy = ((y - bank.origin_y[index] + 32768) & 65535) - 32768
                visible = dx < 320 and dy < 80 and dx + image.width > 0 and dy + image.height > 0
                expected_drawn += visible
                for sy in range(max(0, -dy), min(image.height, 80 - dy)):
                    for sx in range(max(0, -dx), min(image.width, 320 - dx)):
                        source = (sy * image.width + sx) * 4
                        if glyphs[index][source + 3]:
                            destination = (dy + sy) * stride + (dx + sx) * 4
                            expected[destination:destination + 4] = glyphs[index][source:source + 4]
                position = (((position & 0xffff0000) | ((position + image.width) & 65535)) + 1) & 0xffffffff
            storage = c.create_string_buffer(initial)
            target = Surface(c.addressof(storage), len(initial), 320, 80, stride, 4)
            drawn, final = c.c_size_t(123), c.c_uint32(456)
            assert native.vertrix_font_draw_text(c.byref(bank), c.byref(maps[font]), text, len(text),
                x, y, c.byref(target), c.byref(drawn), c.byref(final)), (font, sample)
            assert storage.raw[:len(initial)] == expected, (font, sample)
            assert (drawn.value, final.value) == (expected_drawn, position)
            saved = storage.raw, drawn.value, final.value
            assert not native.vertrix_font_draw_text(c.byref(bank), c.byref(maps[font]), b'A', 1,
                x, y, c.byref(target), c.byref(drawn), c.byref(final))
            assert (storage.raw, drawn.value, final.value) == saved
            invalid = FontMap.from_buffer_copy(bytes(maps[font]))
            invalid.glyphs[65] = -2
            assert not native.vertrix_font_draw_text(c.byref(bank), c.byref(invalid), b'GO A\0', 5,
                x, y, c.byref(target), c.byref(drawn), c.byref(final))
            assert (storage.raw, drawn.value, final.value) == saved
            cases += 1
    gallery = Image.new('RGBA', (760, 19 * 64), (24, 28, 36, 255))
    labels = ImageDraw.Draw(gallery)
    text = b'GO VS 0123\0'
    for font in range(19):
        raw = bytes((24, 28, 36, 255)) * (640 * 64)
        storage = c.create_string_buffer(raw)
        target = Surface(c.addressof(storage), len(raw), 640, 64, 640 * 4, 4)
        drawn, final = c.c_size_t(), c.c_uint32()
        assert native.vertrix_font_draw_text(c.byref(bank), c.byref(maps[font]), text, len(text),
            14, 20, c.byref(target), c.byref(drawn), c.byref(final))
        gallery.paste(Image.frombytes('RGBA', (640, 64), storage.raw[:len(raw)]), (100, font * 64))
        labels.text((12, font * 64 + 25), f'Font {font}', fill=(220, 225, 235, 255))
    gallery.save(args.build_dir / 'original-vf-fonts.png')
    native.vertrix_font_bank_free(c.byref(bank))
    report = {'status': 'passed', 'fonts': 19, 'text_draws': cases,
              'scope': 'Complete VF text composition independently checks pixels, trailing '
                       'spacing, full/low-word position arithmetic, descriptor origins, '
                       'missing glyphs, row padding, clipping and invalid-input preservation. '
                       'Delegates separately oracle-verified traversal, origin and binary '
                       'renderer components. Whole original virtual sprite preparation, '
                       'scaled text, viewport offsets and application remain separate.'}
    (args.build_dir / 'font-text-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
