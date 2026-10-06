"""Compare original483ce0 four-byte horizontal mirror without hooks."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original, BOARD, MASK


class Image(c.Structure):
    _fields_ = [('width', c.c_uint32), ('height', c.c_uint32), ('rgba', c.POINTER(c.c_ubyte))]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'image-mirror.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', str(source / 'image_mirror.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_image_mirror_horizontal.argtypes = [c.POINTER(Image)]
    original = Original(args.executable)
    rng = random.Random(0x483ce0)
    pixels = 0
    for case in range(2048):
        width, height = rng.randrange(1, 65), rng.randrange(1, 65)
        raw = rng.randbytes(width * height * 4)
        descriptor = bytearray(rng.randbytes(40))
        struct.pack_into('<3I', descriptor, 0, MASK, width, height)
        descriptor[39] = 4
        original.cpu.mem_write(BOARD, bytes(descriptor))
        original.cpu.mem_write(MASK, raw)
        original.call(0x483ce0, eax=BOARD)
        storage = (c.c_ubyte * len(raw)).from_buffer_copy(raw)
        image = Image(width, height, storage)
        metadata = bytes(image)
        assert native.vertrix_image_mirror_horizontal(c.byref(image))
        assert bytes(storage) == bytes(original.cpu.mem_read(MASK, len(raw))), case
        assert bytes(descriptor) == bytes(original.cpu.mem_read(BOARD, 40)), case
        assert bytes(image) == metadata
        assert native.vertrix_image_mirror_horizontal(c.byref(image))
        assert bytes(storage) == raw
        pixels += width * height
        invalid = Image(0, 1, storage)
        before = bytes(storage)
        assert not native.vertrix_image_mirror_horizontal(c.byref(invalid))
        assert bytes(storage) == before
    report = {'status': 'passed', 'cases': 2048, 'pixels': pixels, 'scope': 'Actual complete483ce0 four-byte branch without hooks. Pixels and ' 'unchanged descriptor match; double mirror restores input. One-byte ' 'branch and complete configured sprite bank remain outside this proof.'}
    (args.build_dir / 'image-mirror-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
