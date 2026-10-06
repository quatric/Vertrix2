"""Compare VF fixed-point rotation coordinates with original instructions."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path

from original import Original, BOARD


class Tables(c.Structure):
    _fields_ = [('sine', c.c_int32 * 360), ('cosine', c.c_int32 * 360), ('ready', c.c_uint)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('archive', type=Path)
    p.add_argument('references', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = a.build_dir.resolve() / 'tables.dylib'
    subprocess.run(
        [
            'cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
            str(source / 'rotation_tables.c'), str(source / 'vf.c'), '-o', str(library)
        ],
        check=True)
    n = c.CDLL(str(library))
    n.vertrix_vf_open.argtypes = [c.c_char_p]
    n.vertrix_vf_open.restype = c.c_void_p
    n.vertrix_vf_close.argtypes = [c.c_void_p]
    n.vertrix_rotation_tables_load.argtypes = [c.c_void_p, c.POINTER(Tables)]
    n.vertrix_rotation_coordinates.argtypes = [
        c.POINTER(Tables), c.c_int16, c.c_int32, c.c_int32, c.POINTER(c.c_int32),
        c.POINTER(c.c_int32)
    ]
    tables = Tables()
    archive = n.vertrix_vf_open(str(a.archive.resolve()).encode())
    assert archive
    try:
        assert n.vertrix_rotation_tables_load(archive, c.byref(tables))
        before = bytes(tables)
        assert not n.vertrix_rotation_tables_load(archive, c.byref(tables))
        assert bytes(tables) == before
    finally:
        n.vertrix_vf_close(archive)
    sine = (a.references / 'table/sin.tab').read_bytes()
    cosine = (a.references / 'table/cos.tab').read_bytes()
    assert list(tables.sine) == list(struct.unpack('<360i', sine))
    assert list(tables.cosine) == list(struct.unpack('<360i', cosine))
    o = Original(a.executable)
    o.cpu.mem_write(0x598dfc, sine)
    o.cpu.mem_write(0x59939c, cosine)
    rng = random.Random(0x4ad1c0)
    x, y = c.c_int32(), c.c_int32()
    for case in range(2048):
        angle = case % 360
        rx = rng.choice([0, 1, -1, 48, 32767, -32768, rng.randrange(-2147483648, 2147483648)])
        ry = rng.choice([0, 1, -1, 5, 32767, -32768, rng.randrange(-2147483648, 2147483648)])
        raw = bytearray(rng.randbytes(0x160))
        struct.pack_into('<h', raw, 0x24, angle)
        o.cpu.mem_write(BOARD, bytes(raw))
        o.call(0x4ad1c0, eax=BOARD, edx=rx & 0xffffffff, ebx=ry & 0xffffffff, ecx=0x803000,
               args=(0x803004,))
        assert n.vertrix_rotation_coordinates(c.byref(tables), angle, rx, ry, c.byref(x),
                                              c.byref(y))
        assert (x.value, y.value) == struct.unpack('<2i', o.cpu.mem_read(0x803000, 8)), case
        assert bytes(raw) == bytes(o.cpu.mem_read(BOARD, len(raw))), case
    before = x.value, y.value
    assert not n.vertrix_rotation_coordinates(c.byref(tables), -1, 48, 5, c.byref(x), c.byref(y))
    assert not n.vertrix_rotation_coordinates(c.byref(tables), 360, 48, 5, c.byref(x), c.byref(y))
    assert (x.value, y.value) == before
    report = {
        'status': 'passed',
        'coordinate_cases': 2048,
        'table_values': 720,
        'scope': 'Direct original VF sine/cosine values match extraction references. '
                 'Actual original 0x4ad1c0/0x4849e0 instructions run without hooks with original '
                 'tables populated in memory; signed radii and wrapped shifts match. File I/O '
                 'initializer and enclosing actor handler are not executed by this harness.'
    }
    (a.build_dir / 'rotation-tables-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
