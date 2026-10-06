"""Verify original auxiliary palette pointer cycling through bounded native lookup."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from verify_palette_tables import Tables


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'palette-cycle.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
        *[str(source / name) for name in ('palette_tables.c', 'palette_color.c',
                                        'render_palette.c')], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_palette_tables_cycle.argtypes = [c.POINTER(Tables), c.c_uint32,
        c.c_uint8, c.c_uint32, c.POINTER(c.c_uint32)]
    original = Original(args.executable)
    rng = random.Random(0x4754e0)
    tables = Tables()
    dummy = c.c_uint32()
    dummy_hue = c.c_uint8()
    tables.lookup = c.pointer(dummy)
    tables.hue = c.pointer(dummy_hue)
    for i in range(255):
        tables.auxiliary[i] = rng.getrandbits(32)
    original.cpu.mem_write(0x54c1d4, bytes(765 * 4))
    original.cpu.mem_write(0x54c1d4, struct.pack('<255I', *tables.auxiliary))
    constant_tail = rng.getrandbits(32)
    original.cpu.mem_write(0x54c9cc, struct.pack('<256I', *([100] * 255), constant_tail))
    original.cpu.mem_write(0x54d1d0, struct.pack('<256I', 0x54c9cc,
        *[0x54c1d4 + i * 4 for i in range(255)]))
    for cycle in range(256):
        original.call(0x4754e0, eax=cycle)
        assert struct.unpack('<I', original.cpu.mem_read(0x54cdcc, 4))[0] == 0x54cdd0
        pointers = struct.unpack('<256I', original.cpu.mem_read(0x54cdd0, 1024))
        for index, pointer in enumerate(pointers):
            expected = struct.unpack('<I', original.cpu.mem_read(pointer, 4))[0]
            output = c.c_uint32(0xdeadbeef)
            assert native.vertrix_palette_tables_cycle(c.byref(tables), index,
                cycle, constant_tail, c.byref(output)) == 1
            assert output.value == expected, (cycle, index, output.value, expected)
    before = output.value
    assert native.vertrix_palette_tables_cycle(c.byref(tables), 256, 0, constant_tail, c.byref(output)) == 0
    assert output.value == before
    report = {'status': 'passed', 'cycles': 256, 'resolved_entries': 65536,
        'scope': 'Unchanged original4754e0 executes without hooks. Original default '
                 'pointer layout with arbitrary auxiliary entries and zero tail matches '
                 'including the index0/cycle255 adjacent-global boundary, '
                 'bounded native lookup for every byte cycle and index. Complete scene '
                 'render preparation and drawing remain unfinished.'}
    (args.build_dir / 'palette-cycle-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
