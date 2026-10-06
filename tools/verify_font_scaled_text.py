"""Check complete scaled VF text using original bounds and sampling tables."""
import argparse
import ctypes as c
import json
import random
import subprocess
from pathlib import Path
from original import Original
from verify_font_bank import Bank
from verify_font_map import FontMap
from verify_font_draw import Surface


def word(value):
    return ((value + 32768) & 65535) - 32768


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('archive', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    files = sorted(source.glob('font_*.c')) + sorted(source.glob('image*.c'))
    files += [source / name for name in ('vf.c', 'sprite_files.c', 'render_geometry.c', 'surface.c', 'render_dispatch.c')]
    library = args.build_dir.resolve() / 'scaled-text.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    *map(str, files), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_vf_open.argtypes = [c.c_char_p]
    native.vertrix_vf_open.restype = c.c_void_p
    native.vertrix_vf_close.argtypes = [c.c_void_p]
    native.vertrix_font_bank_load.argtypes = [c.c_void_p, c.POINTER(c.c_uint32), c.POINTER(Bank)]
    native.vertrix_font_bank_free.argtypes = [c.POINTER(Bank)]
    native.vertrix_font_map_construct.argtypes = [c.POINTER(FontMap)]
    native.vertrix_font_maps_initialize.argtypes = [c.POINTER(FontMap), c.c_size_t] + [c.c_uint32] * 4
    native.vertrix_font_draw_text_scaled.argtypes = [c.POINTER(Bank), c.POINTER(FontMap),
        c.c_void_p, c.c_size_t, c.c_int16, c.c_int16, c.c_uint8, c.c_uint8, c.c_uint8,
        c.c_uint8, c.POINTER(Surface), c.POINTER(c.c_size_t), c.POINTER(c.c_int16)]
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    bank, maps = Bank(), (FontMap * 19)()
    masks = (c.c_uint32 * 3)(0xff0000, 0xff00, 0xff)
    assert native.vertrix_font_bank_load(archive, masks, c.byref(bank))
    native.vertrix_vf_close(archive)
    for mapping in maps:
        assert native.vertrix_font_map_construct(c.byref(mapping))
    assert native.vertrix_font_maps_initialize(maps, 19, 15, 15, 21, 21)
    glyphs = [c.string_at(image.rgba, image.width * image.height * 4) for image in bank.glyphs]
    original = Original(args.executable)
    original.call(0x4b9050)
    rng = random.Random(0x440a204aed56)
    cases = 0
    text = b'GO VS 0123!\xff\0'
    for font in range(19):
        for mode in range(17):
            for override in range(3):
                unscaled, screen_mode = rng.randrange(2), rng.randrange(17)
                effective = (16 if unscaled else screen_mode) if override else mode
                x, y = rng.randrange(-20, 80), rng.randrange(-20, 55)
                position = x
                stride = 256 * 4 + 16
                initial = rng.randbytes(stride * 64)
                expected = bytearray(initial)
                expected_drawn = 0
                advances = (bytes(original.cpu.mem_read(0x5c1c00 + effective * 1024, 1024))
                            if 0 < effective < 16 else bytes([1]) * 1024)
                for glyph in text[:-1]:
                    if glyph == 32:
                        mw, mh = original.resource_measure(maps[font].space_width, maps[font].space_height, effective)
                    else:
                        index = maps[font].glyphs[glyph]
                        if index == -1:
                            continue
                        image = bank.glyphs[index]
                        dx, dy, mw, mh = original.resource_bounds(image.width, image.height,
                            bank.origin_x[index], bank.origin_y[index], effective, position, y)
                        dx, dy = word(dx), word(dy)
                        expected_drawn += bool(mw and mh and dx < 256 and dy < 64 and dx + mw > 0 and dy + mh > 0)
                        sy = 0
                        for row in range(mh):
                            sx = 0
                            for column in range(mw):
                                tx, ty = dx + column, dy + row
                                offset = (sy * image.width + sx) * 4
                                if 0 <= tx < 256 and 0 <= ty < 64 and glyphs[index][offset + 3]:
                                    destination = ty * stride + tx * 4
                                    expected[destination:destination + 4] = glyphs[index][offset:offset + 4]
                                sx += advances[column]
                            sy += advances[row]
                    position = word(position + mw + 1)
                storage = c.create_string_buffer(initial)
                target = Surface(c.addressof(storage), len(initial), 256, 64, stride, 4)
                drawn, final = c.c_size_t(123), c.c_int16(456)
                assert native.vertrix_font_draw_text_scaled(c.byref(bank), c.byref(maps[font]),
                    text, len(text), x, y, mode, override, unscaled, screen_mode,
                    c.byref(target), c.byref(drawn), c.byref(final))
                assert storage.raw[:len(initial)] == expected, (font, mode, override)
                assert (drawn.value, final.value) == (expected_drawn, position)
                saved = storage.raw, drawn.value, final.value
                assert not native.vertrix_font_draw_text_scaled(c.byref(bank), c.byref(maps[font]),
                    b'A', 1, x, y, mode, override, unscaled, screen_mode,
                    c.byref(target), c.byref(drawn), c.byref(final))
                assert (storage.raw, drawn.value, final.value) == saved
                cases += 1
    native.vertrix_font_bank_free(c.byref(bank))
    report = {'status': 'passed', 'fonts': 19, 'scale_modes': 17, 'text_draws': cases,
              'scope': 'Complete basic scaled text over real owned VF glyphs independently '
                       'matches pixels, spacing, origins, clipping, row padding, screen overrides '
                       'and output positions against actual original measurement/bounds and '
                       'sampling tables. Components have separate original traversal proofs. '
                       'Parent effects/custom clipping/viewport offsets and playable application '
                       'remain unfinished.'}
    (args.build_dir / 'font-scaled-text-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
