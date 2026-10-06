"""Verify original font stencil identity and owned VF frame pixels."""
import argparse
import ctypes as c
import json
import struct
import subprocess
from pathlib import Path
from original import Original
from verify_sprite import SpriteFrame


class Stencils(c.Structure):
    _fields_ = [('frame6', SpriteFrame), ('frame9', SpriteFrame)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('archive', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / 'stencils.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    *[str(root / 'source' / name) for name in ('font_stencils.c', 'sprite_files.c', 'image.c', 'vf.c')],
                    '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_vf_open.argtypes = [c.c_char_p]
    native.vertrix_vf_open.restype = c.c_void_p
    native.vertrix_vf_close.argtypes = [c.c_void_p]
    native.vertrix_vf_find.argtypes = [c.c_void_p, c.c_char_p, c.POINTER(c.c_uint32)]
    native.vertrix_vf_size.argtypes = [c.c_void_p, c.c_uint32, c.POINTER(c.c_uint32)]
    native.vertrix_vf_read.argtypes = [c.c_void_p, c.c_uint32, c.c_uint32, c.c_void_p, c.c_size_t]
    native.vertrix_font_stencils_load.argtypes = [c.c_void_p, c.POINTER(c.c_uint32), c.POINTER(Stencils)]
    native.vertrix_font_stencils_free.argtypes = [c.POINTER(Stencils)]
    original = Original(args.executable)
    assert bytes(original.cpu.mem_read(0x513c5d, 1)) == b'\x11'
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive

    def read(name):
        index, size = c.c_uint32(), c.c_uint32()
        assert native.vertrix_vf_find(archive, name.encode(), c.byref(index))
        assert native.vertrix_vf_size(archive, index, c.byref(size))
        data = c.create_string_buffer(size.value)
        assert native.vertrix_vf_read(archive, index, 0, data, size.value)
        return data.raw

    config = read('texte/SpriteFileName.ini').decode('cp1252')
    names = [line.split('\\')[0].strip() for line in config.splitlines()
             if line.strip() and not line.startswith('/')]
    assert names[17] == 'Circle.spr'
    blob = read('sprite/Circle.spr')
    cursor = 2
    frames = {}
    for index in range(struct.unpack_from('<H', blob)[0]):
        header = blob[cursor:cursor + 48]
        width, height = struct.unpack_from('<2I', header, 12)
        cursor += 48
        payload = blob[cursor:cursor + width * height * 4]
        cursor += len(payload)
        frames[index] = (width, height, header, payload)
    owned = []
    evidence = []
    for reverse in (False, True):
        masks = (c.c_uint32 * 3)(*( [0xff, 0xff00, 0xff0000] if reverse
                                   else [0xff0000, 0xff00, 0xff]))
        stencils = Stencils()
        assert native.vertrix_font_stencils_load(archive, masks, c.byref(stencils))
        references = []
        for index, actual in ((6, stencils.frame6), (9, stencils.frame9)):
            width, height, header, payload = frames[index]
            expected = bytearray(payload)
            if not reverse:
                expected[0::4], expected[2::4] = payload[2::4], payload[0::4]
            expected[3::4] = bytes(255 if alpha == 0 else 0 for alpha in payload[3::4])
            assert (actual.image.width, actual.image.height, actual.frame_count) == (width, height, 10)
            assert tuple(actual.metadata) == struct.unpack_from('<10I', header, 8)
            assert c.string_at(actual.image.rgba, len(expected)) == expected
            references.append(bytes(expected))
            if not reverse:
                evidence.append({'frame': index, 'width': width, 'height': height})
        saved = bytes(stencils)
        assert not native.vertrix_font_stencils_load(archive, masks, c.byref(stencils))
        assert bytes(stencils) == saved
        owned.append((stencils, references))
    invalid = Stencils()
    masks = (c.c_uint32 * 3)(0, 0, 0)
    assert not native.vertrix_font_stencils_load(archive, masks, c.byref(invalid))
    assert bytes(invalid) == bytes(Stencils())
    native.vertrix_vf_close(archive)
    for stencils, references in owned:
        for frame, expected in zip((stencils.frame6, stencils.frame9), references):
            assert c.string_at(frame.image.rgba, len(expected)) == expected
        native.vertrix_font_stencils_free(c.byref(stencils))
        assert bytes(stencils) == bytes(Stencils())
    report = {'status': 'passed', 'frames': evidence, 'color_orders': 2,
              'scope': 'Original static sprite index513c5d=17 matches VF SpriteFileName.ini '
                       'Circle.spr. Frames6/9 independently parsed and owned pixels/metadata '
                       'match binary alpha and RGB ordering in both directions, including '
                       'lifetime after archive close and invalid masks. Original resource '
                       'graph construction and complete derived glyph bank remain separate.'}
    (args.build_dir / 'font-stencils-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
