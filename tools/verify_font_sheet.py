"""Verify VF font-sheet composition against original transparency and crop pixels."""
import argparse
import ctypes as c
import json
import struct
import subprocess
from pathlib import Path
from original import Original
from verify_image import NativeImage


class Sheet(c.Structure):
    _fields_ = [('count', c.c_uint32), ('glyphs', c.POINTER(NativeImage))]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('archive', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / 'sheet.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', * [str(root / 'source' / name) for name in ('font_sheet.c', 'font_cell.c', 'image_crop.c', 'image_key.c', 'image.c', 'vf.c')], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_vf_open.argtypes = [c.c_char_p]
    native.vertrix_vf_open.restype = c.c_void_p
    native.vertrix_vf_close.argtypes = [c.c_void_p]
    native.vertrix_image_bmp.argtypes = [c.c_void_p, c.c_char_p, c.POINTER(NativeImage)]
    native.vertrix_image_free.argtypes = [c.POINTER(NativeImage)]
    native.vertrix_font_sheet_load.argtypes = [c.c_void_p, c.c_char_p, c.c_char_p, c.c_uint32, c.c_uint32, c.POINTER(Sheet)]
    native.vertrix_font_sheet_free.argtypes = [c.POINTER(Sheet)]
    original = Original(args.executable)
    original.cpu.mem_map(0x900000, 0x200000)
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    operations = json.loads((root / 'docs/font-load-plan.json').read_text())['operations']
    owned = []
    count = pixels = 0
    try:
        for operation in operations:
            if operation['address'] != '0x43f200':
                continue
            name = operation['vf_image'].encode()
            width, height = operation['ebx'], operation['ecx']
            sheet, image = Sheet(), NativeImage()
            assert native.vertrix_font_sheet_load(archive, name, b'image/systeme/.pcx', width, height, c.byref(sheet)), name
            assert sheet.count == operation['stack_argument'], name
            assert native.vertrix_image_bmp(archive, name, c.byref(image))
            try:
                raw = c.string_at(image.rgba, image.width * image.height * 4)
                original.cpu.mem_write(0x804000, struct.pack('<3I', 0x900000, image.width, image.height))
                original.cpu.mem_write(0x900000, raw)
                original.call(0x4799f0, eax=0x804000, edx=struct.unpack_from('<I', raw)[0])
                expected = []
                for i in range(sheet.count):
                    columns = image.width // (width + 1)
                    x, y = 1 + (i % columns) * (width + 1), 1 + (i // columns) * (height + 1)
                    original.cpu.mem_write(0x805000, struct.pack('<3I4BI', 0xa00000, width, height, 4, 32, 0, 0, 0))
                    original.cpu.mem_write(0x805040, struct.pack('<3I4BI', 0x900000, image.width, image.height, 4, 32, 0, 0, 0))
                    original.call(0x47ce10, eax=0x805000, edx=0x805040, ebx=0, ecx=0, args=(x, y, width, height))
                    reference = bytes(original.cpu.mem_read(0xa00000, width * height * 4))
                    glyph = sheet.glyphs[i]
                    assert (glyph.width, glyph.height) == (width, height)
                    assert c.string_at(glyph.rgba, len(reference)) == reference, (name, i)
                    expected.append(reference)
                    count += 1
                    pixels += width * height
                saved = bytes(sheet)
                assert not native.vertrix_font_sheet_load(archive, name, b'image/systeme/.pcx', width, height, c.byref(sheet))
                assert bytes(sheet) == saved
                owned.append((sheet, expected))
            finally:
                native.vertrix_image_free(c.byref(image))
        empty = Sheet()
        assert not native.vertrix_font_sheet_load(archive, b'missing.bmp', b'.pcx', 1, 1, c.byref(empty))
        assert bytes(empty) == bytes(Sheet())
    finally:
        native.vertrix_vf_close(archive)
    for sheet, expected in owned:
        for index, reference in enumerate(expected):
            assert c.string_at(sheet.glyphs[index].rgba, len(reference)) == reference
        native.vertrix_font_sheet_free(c.byref(sheet))
        assert bytes(sheet) == bytes(Sheet())
    assert len(owned) == 29 and count == 466
    report = {'status': 'passed', 'vf_sheets': len(owned), 'glyphs': count, 'pixels': pixels, 'scope': 'Direct original VF composition of29 BMP sheets into466 base glyphs; ' 'actual4799f0 and47ce10 execute without hooks. Pixel bytes, dimensions, ' 'ordering, owned lifetime after archive close, occupied-output rejection ' 'and missing-artwork failure verified. Mask-present branch, final ' 'color ordering,82 derived glyphs and text rendering remain separate.'}
    (args.build_dir / 'font-sheet-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
