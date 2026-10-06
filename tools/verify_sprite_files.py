"""Verify original VF filename slots and original45f540 path construction."""
import argparse
import ctypes as c
import json
from pathlib import Path
import struct
import subprocess
from original import Original
from verify_font_stencils import Stencils
from verify_wii_platform_check import resource


def write_vf(path, entries):
    offset = 8 + sum(12+len(name) for name, _ in entries)
    index = bytearray(struct.pack('<II', 10, len(entries)))
    payload = bytearray()
    for name, data in entries:
        index.extend(struct.pack('<III', len(data), offset, len(name))+name)
        payload.extend(data)
        offset += len(data)
    path.write_bytes(index+payload)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('archive', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = build / 'sprite-files.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
        *[str(root / 'source' / n) for n in ('sprite_files.c', 'font_stencils.c', 'image.c', 'vf.c')],
        '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_vf_open.argtypes = [c.c_char_p]
    native.vertrix_vf_open.restype = c.c_void_p
    native.vertrix_vf_close.argtypes = [c.c_void_p]
    native.vertrix_sprite_file.argtypes = [c.c_void_p, c.c_uint32, c.c_void_p, c.c_size_t]
    native.vertrix_font_stencils_load.argtypes = [c.c_void_p, c.POINTER(c.c_uint32), c.POINTER(Stencils)]
    native.vertrix_font_stencils_free.argtypes = [c.POINTER(Stencils)]
    data = args.archive.read_bytes()
    table = resource(data, b'texte/spritefilename.ini')
    names = [line.split(b'\\')[0] for line in table.splitlines()
             if line and not line.startswith(b'/')]
    assert len(names) == 20
    original = Original(args.executable)
    prefix = bytes(original.cpu.mem_read(0x4fc188, 16)).split(b'\0')[0]
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    invalid = 0
    for slot in range(23):
        filename = names[slot] if slot < len(names) else b''
        original.cpu.mem_write(0x801000, filename+b'\0')
        original.call(0x45f540, eax=0x800000, edx=0x4fc188, ebx=0x801000)
        expected = bytes(original.cpu.mem_read(0x800000, 256)).split(b'\0')[0]
        assert expected == prefix+filename
        output = c.create_string_buffer(256)
        assert native.vertrix_sprite_file(archive, slot, output, 256)
        assert output.value == expected
        for capacity in range(len(expected)+1):
            output.raw = bytes([0xa5])*256
            assert not native.vertrix_sprite_file(archive, slot, output, capacity)
            assert output.raw == bytes([0xa5])*256
            invalid += 1
    output = c.create_string_buffer(b'unchanged', 256)
    before = output.raw
    assert not native.vertrix_sprite_file(archive, 23, output, 256)
    assert output.raw == before
    native.vertrix_vf_close(archive)
#A renamed, table - selected Circle resource proves the loader reads the row.
    altered = table.replace(b'Circle.spr', b'CustomCircle.spr')
    fixture = build / 'renamed-circle.vf'
    write_vf(fixture, [(b'texte/SpriteFileName.ini', altered),
                      (b'sprite/CustomCircle.spr', resource(data, b'sprite/circle.spr'))])
    archive = native.vertrix_vf_open(str(fixture).encode())
    assert archive
    stencils = Stencils()
    masks = (c.c_uint32*3)(0xff, 0xff00, 0xff0000)
    assert native.vertrix_font_stencils_load(archive, masks, c.byref(stencils))
    assert stencils.frame6.image.rgba and stencils.frame9.image.rgba
    native.vertrix_font_stencils_free(c.byref(stencils))
    native.vertrix_vf_close(archive)
    malformed = [b'bad.spr', b'bad.spr\\ junk', b'\x01.spr\\', b'a/b.spr\\',
                 b'a:b.spr\\', b'\\', b'x.spr\\\n'*24]
    for i, text in enumerate(malformed):
        path = build / f'malformed-{i}.vf'
        write_vf(path, [(b'texte/SpriteFileName.ini', text)])
        archive = native.vertrix_vf_open(str(path).encode())
        assert archive
        output.raw = before
        assert not native.vertrix_sprite_file(archive, 0, output, 256)
        assert output.raw == before
        native.vertrix_vf_close(archive)
    report = {'status': 'passed', 'original_filename_slots': 23,
        'original_nonempty_rows': 20, 'capacity_preservation_cases': invalid,
        'renamed_table_selected_stencils': 2, 'malformed_table_cases': len(malformed),
        'scope': 'All original VF slots match complete original45f540 path construction. '
                 'Missing trailing23-slot entries retain empty names. Renamed VF row17 '
                 'drives font stencil loading. Bounded supported-table reader; not an '
                 'emulation of every original generic INI parser behavior or startup settings.'}
    (build / 'sprite-files-verification.json').write_text(json.dumps(report, indent=2)+'\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
