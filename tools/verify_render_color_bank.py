"""Compare complete original474e00 color-bank construction."""
import argparse
import ctypes as c
import itertools
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original


class Bank(c.Structure):
    _fields_ = [('lookup', c.c_uint32 * 13), ('colors', c.c_uint32 * 13), ('format_colors', c.c_uint32 * 12)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'color-bank.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', * [str(source / name) for name in ('render_color_bank.c', 'image.c', 'vf.c')], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_render_color_bank_build.argtypes = [c.POINTER(c.c_uint32), c.c_void_p, c.c_size_t, c.POINTER(Bank)]
    original = Original(args.executable)
    original.cpu.mem_map(0x900000, 0x1000)
    original.cpu.mem_write(0x54cdc8, struct.pack('<I', 0x900000))
    original.cpu.mem_write(0x900000 + 100 * 4, struct.pack('<I', 0x900800))
    rng = random.Random(0x474e00)
    permutations = list(itertools.permutations((0xff0000, 0xff00, 0xff)))
    permutations += list(itertools.permutations((0xf800, 0x7e0, 0x1f)))
    completed = 0
    for case in range(256):
        masks = (c.c_uint32 * 3)(* permutations[case % len(permutations)])
        row_bytes = rng.randbytes(101)
        row = c.create_string_buffer(row_bytes, 101)
        original.cpu.mem_write(0x900800, row_bytes)
        original.cpu.mem_write(0x804000, bytes(40))
        original.call(0x481bc0, eax=0x804000, edx=masks[0], ebx=masks[1], ecx=masks[2], args=(0xff000000,))
        original.call(0x474e00, eax=0x804000)
        output = Bank()
        assert native.vertrix_render_color_bank_build(masks, row, 101, c.byref(output)) == 1
        assert tuple(output.lookup) == struct.unpack('<13I', original.cpu.mem_read(0x54b808, 52)), case
        assert tuple(output.colors) == struct.unpack('<13I', original.cpu.mem_read(0x54b83c, 52)), case
        assert tuple(output.format_colors) == struct.unpack('<12I', original.cpu.mem_read(0x54d5f4, 48)), case
        before = bytes(output)
        assert native.vertrix_render_color_bank_build(masks, row, 100, c.byref(output)) == 0
        assert bytes(output) == before
        completed += 1
    assert completed == 256, completed
    report = {'status': 'passed', 'cases': completed, 'complete_original_executions': {'0x474e00': completed}, 'scope': 'Complete original474e00 executes without hooks, including original ' 'format setup/conversion. Native13 lookup/colors and12 format colors ' 'match across RGB32/RGB565 mask permutations and selected channel rows. ' 'Complete render preparation and playable application remain unfinished.'}
    (args.build_dir / 'render-color-bank-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
