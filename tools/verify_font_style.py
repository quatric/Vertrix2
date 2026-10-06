"""Compare actual styled-font parent field transfer with native semantic fields."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from unicorn.x86_const import UC_X86_REG_ESI, UC_X86_REG_EDI
from original import Original


class Style(c.Structure):
    _fields_ = [('clip_mode', c.c_uint8), ('binary', c.c_uint8), ('amount', c.c_uint8),
                ('effect', c.c_int16), ('stage', c.c_uint8), ('flag94', c.c_uint8),
                ('flag95', c.c_uint8), ('flag93', c.c_uint8), ('mode', c.c_uint8),
                ('screen_override', c.c_uint8), ('cycle', c.c_uint32), ('cycle_flag', c.c_uint8),
                ('clip_left', c.c_int16), ('clip_right', c.c_int16),
                ('clip_top', c.c_int16), ('clip_bottom', c.c_int16)]


FIELDS = {'clip_mode': (0x8e, 'B'), 'binary': (0x8f, 'B'), 'amount': (0x4e, 'B'),
          'effect': (0x48, 'h'), 'stage': (0x52, 'B'), 'flag94': (0x94, 'B'),
          'flag95': (0x95, 'B'), 'flag93': (0x93, 'B'), 'mode': (0x44, 'B'),
          'screen_override': (0x91, 'B'), 'cycle': (0x80, 'I'), 'cycle_flag': (0x8c, 'B'),
          'clip_left': (0xa8, 'h'), 'clip_right': (0xaa, 'h'),
          'clip_top': (0xac, 'h'), 'clip_bottom': (0xae, 'h')}


def unpack(raw):
    output = Style()
    for name, (offset, format) in FIELDS.items():
        setattr(output, name, struct.unpack_from('<' + format, raw, offset)[0])
    return output


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / 'style.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    str(root / 'source/font_style.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library)).vertrix_font_glyph_style
    native.argtypes = [c.POINTER(Style), c.POINTER(Style)]
    original = Original(args.executable)
    rng = random.Random(0x440b93)
    for case in range(2048):
        parent_raw, child_raw = rng.randbytes(0x15c), rng.randbytes(0x15c)
        parent, child = unpack(parent_raw), unpack(child_raw)
        original.cpu.mem_write(0x804000, parent_raw)
        original.cpu.mem_write(0x805000, child_raw)
        original.cpu.reg_write(UC_X86_REG_EDI, 0x804000)
        original.cpu.reg_write(UC_X86_REG_ESI, 0x805000)
        original.call(0x440b93, stop=0x440c46)
        expected = bytes(original.cpu.mem_read(0x805000, 0x15c))
        assert native(c.byref(parent), c.byref(child))
        matched = bytearray(child_raw)
        for name, (offset, format) in FIELDS.items():
            actual = getattr(child, name)
            assert actual == getattr(unpack(expected), name), (case, name)
            struct.pack_into('<' + format, matched, offset, actual)
        assert bytes(matched) == expected
        assert bytes(original.cpu.mem_read(0x804000, 0x15c)) == parent_raw
        assert native(c.byref(parent), c.byref(parent))
        assert parent.binary == 1
    before = bytes(child)
    assert not native(None, c.byref(child))
    assert bytes(child) == before
    report = {'status': 'passed', 'cases': 2048, 'fields': len(FIELDS),
              'scope': 'Actual440b93..440c46 without hooks, all16 transferred drawing '
                       'fields, forced binary flag and untouched child bytes compared. '
                       'Parent unchanged and native in-place/null behavior checked. '
                       'Renderer interpretation of effects/cycle/clipping and complete '
                       'styled text drawing remain separate.'}
    (args.build_dir / 'font-style-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
