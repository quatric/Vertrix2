"""Compare original byte-to-glyph resource lookup without service hooks."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original


class FontMap(c.Structure):
    _fields_ = [('space_width', c.c_uint32), ('space_height', c.c_uint32),
                ('glyphs', c.c_int16 * 256)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source/font_map.c'
    library = a.build_dir.resolve() / 'map.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    str(source), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_font_glyph.argtypes = [c.POINTER(FontMap), c.c_uint8,
        c.POINTER(c.c_uint32), c.c_size_t, c.POINTER(c.c_int16), c.POINTER(c.c_uint32)]
    original = Original(a.executable)
    rng = random.Random(0x43f420)
    lookups = missing = 0
    for case in range(32):
        resources = (c.c_uint32 * 128)(*[rng.getrandbits(32) for _ in range(128)])
        original.cpu.mem_write(0x5410f8, bytes(resources))
        maps = []
        for font in range(20):
            entries = [rng.choice([-1, rng.randrange(128)]) for _ in range(256)]
            mapping = FontMap(rng.getrandbits(32), rng.getrandbits(32), (c.c_int16 * 256)(*entries))
            maps.append(mapping)
            original.cpu.mem_write(0x541988 + font * 0x20c, bytes(mapping))
        for glyph in range(256):
            font = rng.randrange(20)
            index, resource = c.c_int16(42), c.c_uint32(123)
            expected = original.call(0x43f420, eax=font, edx=glyph)
            assert native.vertrix_font_glyph(c.byref(maps[font]), glyph, resources, 128,
                                             c.byref(index), c.byref(resource))
            assert resource.value == expected
            assert index.value == struct.unpack('<h', original.cpu.mem_read(0x5410f4, 2))[0]
            missing += index.value == -1
            lookups += 1
    mapping.glyphs[0] = -2
    before = index.value, resource.value
    assert not native.vertrix_font_glyph(c.byref(mapping), 0, resources, 128, c.byref(index), c.byref(resource))
    assert (index.value, resource.value) == before
    report = {'status': 'passed', 'lookups': lookups, 'missing': missing,
              'scope': 'Original 0x43f420 and 0x48ac00 without hooks across20 font slots, '
                       'all256 byte codes, shared selected index and resource handles. '
                       'Maps/resources are fixtures; original initialization and VF font loading remain unfinished.'}
    (a.build_dir / 'font-map-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
