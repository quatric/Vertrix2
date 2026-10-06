"""Verify original full-pixel color key and direct VF font-sheet transparency."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original
from verify_image import NativeImage


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('archive', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / 'key.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    *[str(root / 'source' / name) for name in ('image_key.c', 'image.c', 'vf.c')],
                    '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_image_color_key.argtypes = [c.POINTER(NativeImage), c.c_uint32]
    native.vertrix_vf_open.argtypes = [c.c_char_p]
    native.vertrix_vf_open.restype = c.c_void_p
    native.vertrix_vf_close.argtypes = [c.c_void_p]
    native.vertrix_vf_count.argtypes = [c.c_void_p]
    native.vertrix_vf_name.argtypes = [c.c_void_p, c.c_uint32]
    native.vertrix_vf_name.restype = c.c_char_p
    for name in ('vertrix_image_bmp', 'vertrix_image_bmp_keyed'):
        getattr(native, name).argtypes = [c.c_void_p, c.c_char_p, c.POINTER(NativeImage)]
    native.vertrix_image_free.argtypes = [c.POINTER(NativeImage)]
    original = Original(args.executable)
    original.cpu.mem_map(0x900000, 0x1000000)
    rng = random.Random(0x4799f0)

    def expected(raw, width, height, key):
        original.cpu.mem_write(0x804000, struct.pack('<3I', 0x900000, width, height))
        original.cpu.mem_write(0x900000, raw)
        original.call(0x4799f0, eax=0x804000, edx=key)
        return bytes(original.cpu.mem_read(0x900000, len(raw)))

    for case in range(1024):
        width, height = rng.randrange(1, 17), rng.randrange(1, 17)
        key = rng.getrandbits(32)
        words = [rng.choice([key, key ^ 0xff000000, rng.getrandbits(32)])
                 for _ in range(width * height)]
        raw = struct.pack('<' + 'I' * len(words), *words)
        storage = c.create_string_buffer(raw)
        image = NativeImage(width, height, c.addressof(storage))
        assert native.vertrix_image_color_key(c.byref(image), key)
        assert storage.raw[:len(raw)] == expected(raw, width, height, key)
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    owned = []
    pixels = 0
        try:
        for
            index in range(native.vertrix_vf_count(archive))
                : name = native.vertrix_vf_name(archive, index) if '/font' not in name.decode()
                             .lower()
                             .replace('\\', '/') or
                         not name.lower().endswith(b '.bmp')
                : continue before,
                  output = NativeImage(),
                  NativeImage() assert native.vertrix_image_bmp(archive, name, c.byref(before))
            try : raw = c.string_at(before.rgba, before.width * before.height * 4)
                reference = expected(raw, before.width, before.height, struct.unpack_from('<I', raw)[0])
                assert native.vertrix_image_bmp_keyed(archive, name, c.byref(output))
                assert c.string_at(output.rgba, len(raw)) == reference, name
                saved = bytes(output)
                assert not native.vertrix_image_bmp_keyed(archive, name, c.byref(output))
                assert bytes(output) == saved
                owned.append((output, reference))
                pixels += before.width * before.height
            finally:
                native.vertrix_image_free(c.byref(before))
    finally:
        native.vertrix_vf_close(archive)
    for output, reference in owned:
        assert c.string_at(output.rgba, len(reference)) == reference
        native.vertrix_image_free(c.byref(output))
    assert len(owned) == 29, len(owned)
    report = {'status': 'passed', 'kernel_cases': 1024, 'vf_font_sheets': len(owned),
              'vf_pixels': pixels, 'scope': 'Actual4799f0 without hooks; full32-bit key '
                       'comparison including alpha. Direct VF BMP/top-left-key composition '
                       'matches original kernel across all29 font sheets; owned pixels remain '
                       'valid after archive close. Mask-present selection, configuration parsing, '
                       'glyph resource construction and text rendering remain separate.'}
    (args.build_dir / 'image-key-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
