"""Verify owned image adapters against separately oracle-verified transform kernels."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from verify_image import NativeImage


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / 'font-image.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    *[str(root / 'source' / name) for name in ('font_image.c', 'font_outline.c',
                       'font_stencil.c', 'image.c', 'vf.c')], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_font_image_outline.argtypes = [c.POINTER(NativeImage), c.c_uint32,
                                                 c.c_uint32, c.POINTER(NativeImage)]
    native.vertrix_font_image_stencil.argtypes = [c.POINTER(NativeImage), c.POINTER(NativeImage),
                                                 c.c_uint32, c.POINTER(NativeImage)]
    native.vertrix_font_outline.argtypes = [c.POINTER(c.c_uint32), c.POINTER(c.c_uint32),
                                           c.c_size_t] + [c.c_uint32] * 4
    native.vertrix_font_stencil.argtypes = [c.POINTER(c.c_uint32), c.c_uint32, c.c_uint32,
                                           c.POINTER(c.c_uint32), c.c_uint32, c.c_uint32,
                                           c.c_uint32, c.POINTER(c.c_uint32), c.c_size_t]
    native.vertrix_image_free.argtypes = [c.POINTER(NativeImage)]
    rng = random.Random(0x4831b0483400)
    pixels = 0
    for case in range(1024):
        width, height = rng.randrange(1, 17), rng.randrange(1, 17)
        words = [rng.getrandbits(24) | (rng.choice([0, 1, 255]) << 24)
                 for _ in range(width * height)]
        raw = struct.pack('<' + 'I' * len(words), *words)
        storage = c.create_string_buffer(raw)
        image = NativeImage(width, height, c.addressof(storage))
        output = NativeImage()
        working = (c.c_uint32 * len(words))(*words)
        if case % 2:
            sw, sh = rng.randrange(1, 9), rng.randrange(1, 9)
            stamp = [rng.getrandbits(24) | (rng.choice([0, 128, 255]) << 24)
                     for _ in range(sw * sh)]
            stamp_words = (c.c_uint32 * len(stamp))(*stamp)
            stamp_raw = struct.pack('<' + 'I' * len(stamp), *stamp)
            stamp_storage = c.create_string_buffer(stamp_raw)
            stencil = NativeImage(sw, sh, c.addressof(stamp_storage))
            ow, oh = width + 2 * (sw // 2), height + 2 * (sh // 2)
            expected = (c.c_uint32 * (ow * oh))()
            solid = rng.randrange(3)
            assert native.vertrix_font_stencil(working, width, height, stamp_words,
                                               sw, sh, solid, expected, len(expected))
            assert native.vertrix_font_image_stencil(c.byref(image), c.byref(stencil),
                                                     solid, c.byref(output))
            assert storage.raw[:len(raw)] == raw and stamp_storage.raw[:len(stamp_raw)] == stamp_raw
        else:
            ow, oh = width, height
            expected = (c.c_uint32 * len(words))()
            passes, diagonal = rng.randrange(5), rng.randrange(3)
            assert native.vertrix_font_outline(working, expected, len(words), width, height,
                                               passes, diagonal)
            assert native.vertrix_font_image_outline(c.byref(image), passes, diagonal, c.byref(output))
            expected_source = struct.pack('<' + 'I' * len(words), *working)
            assert storage.raw[:len(raw)] == expected_source
        try:
            expected_bytes = struct.pack('<' + 'I' * len(expected), *expected)
            assert (output.width, output.height) == (ow, oh)
            assert c.string_at(output.rgba, len(expected_bytes)) == expected_bytes
            saved = bytes(output), storage.raw
            assert not native.vertrix_font_image_outline(c.byref(image), 1, 1, c.byref(output))
            assert (bytes(output), storage.raw) == saved
            pixels += len(expected)
        finally:
            native.vertrix_image_free(c.byref(output))
    empty, invalid = NativeImage(), NativeImage()
    assert not native.vertrix_font_image_outline(c.byref(invalid), 1, 1, c.byref(empty))
    assert bytes(empty) == bytes(NativeImage())
    report = {'status': 'passed', 'cases': 1024, 'pixels': pixels,
              'scope': 'Owned image adapters match separately oracle-verified kernels. '
                       'Explicit LE byte translation, source mutation/preservation, dimensions, '
                       'nonempty-output rejection and freeing checked. This integration proof '
                       'does not execute x86 or validate complete VF-derived glyph assembly.'}
    (args.build_dir / 'font-image-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
