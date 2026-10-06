"""Compare bordered-sheet glyph crop bytes against actual original copy routine."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original


class Image(c.Structure):
    _fields_ = [('width', c.c_uint32), ('height', c.c_uint32), ('rgba', c.POINTER(c.c_ubyte))]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    library = args.build_dir.resolve() / 'crop.dylib'
    source = Path(__file__).resolve().parents[1] / 'source/image_crop.c'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', str(source), '-o', str(library)], check=True)
    native = c.CDLL(str(library)).vertrix_image_font_crop
    native.argtypes = [c.POINTER(Image)] + [c.c_uint32] * 4 + [c.POINTER(Image)]
    release = c.CDLL(None).free
    release.argtypes = [c.c_void_p]
    original = Original(args.executable)
    rng = random.Random(0x47ce10)
    pixels = 0
    for case in range(1024):
        sw, sh = rng.randrange(2, 33), rng.randrange(1, 33)
        width, height = rng.randrange(1, sw), rng.randrange(1, sh + 1)
        x, y = rng.randrange(sw - width + 1), rng.randrange(sh - height + 1)
        raw = rng.randbytes(sw * sh * 4)
        storage = (c.c_ubyte * len(raw)).from_buffer_copy(raw)
        image, output = Image(sw, sh, storage), Image()
        original.cpu.mem_write(0x806000, raw)
        original.cpu.mem_write(0x808000, bytes(width * height * 4))
        for address, pointer, w, h in ((0x805000, 0x808000, width, height), (0x805040, 0x806000, sw, sh)):
            original.cpu.mem_write(address, struct.pack('<3I4BI', pointer, w, h, 4, 32, 0, 0, 0))
        original.call(0x47ce10, eax=0x805000, edx=0x805040, ebx=0, ecx=0, args=(x, y, width, height))
        assert native(c.byref(image), x, y, width, height, c.byref(output))
        try:
            assert output.width == width and output.height == height
            assert c.string_at(output.rgba, width * height * 4) == bytes(original.cpu.mem_read(0x808000, width * height * 4)), case
            assert bytes(original.cpu.mem_read(0x806000, len(raw))) == raw
            pixels += width * height
        finally:
            release(output.rgba)
            sentinel = Image()
            assert not native(c.byref(image), sw, y, width, height, c.byref(sentinel))
            assert bytes(sentinel) == bytes(Image())
    report = {'status': 'passed', 'cases': 1024, 'pixels_compared': pixels, 'scope': 'Actual47ce10 four-byte regular row-copy branch, no hooks. ' 'Narrower bordered-sheet crops; all pixel bytes and unmodified ' 'source compared. Full-width fast path, original482f80 allocator ' 'and VF font integration are outside this proof.'}
    (args.build_dir / 'font-crop-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
