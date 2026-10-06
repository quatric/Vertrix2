"""Compare original lookup builder's nearest-channel selection."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from unicorn.x86_const import UC_X86_REG_EBP


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'lookup-entry.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', str(source / 'palette_color.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_palette_lookup_entry.argtypes = [c.c_void_p, c.c_size_t, c.c_uint16, c.POINTER(c.c_uint8), c.POINTER(c.c_uint32)]
    native.vertrix_palette_channels.argtypes = [c.c_void_p, c.c_size_t]
    original = Original(args.executable)
    rng = random.Random(0x475183)
    maps = c.create_string_buffer(201 * 101)
    assert native.vertrix_palette_channels(maps, len(maps)) == 1
    frame = 0x709000
    for case in range(4096):
        if case == 2048:
            maps = c.create_string_buffer(rng.randbytes(201 * 101), 201 * 101)
        row = rng.randrange(201)
        channels = (c.c_uint8 * 3)(* [rng.randrange(256) for _ in range(3)])
        original.cpu.mem_write(0x5468b0, maps.raw)
        original.cpu.mem_write(frame - 0x100, bytes(0x100))
        original.cpu.mem_write(frame - 0x50, struct.pack('<I', row))
        original.cpu.mem_write(frame - 0x3c, struct.pack('<I', row))
        for offset, channel in zip((0x44, 0x48, 0x30), channels):
            original.cpu.mem_write(frame - offset, struct.pack('<H', channel))
        original.cpu.mem_write(0x54b800, struct.pack('<I', 0x804000))
        original.cpu.reg_write(UC_X86_REG_EBP, frame)
        original.call(0x475183, stop=0x47525e)
        expected = struct.unpack('<I', original.cpu.mem_read(0x804000, 4))[0]
        output = c.c_uint32(0xdeadbeef)
        assert native.vertrix_palette_lookup_entry(maps, len(maps), row, channels, c.byref(output)) == 1
        assert output.value == expected, (case, row, tuple(channels), output.value, expected)
    before = output.value
    assert native.vertrix_palette_lookup_entry(maps, len(maps), 201, channels, c.byref(output)) == 0
    assert output.value == before
    assert native.vertrix_palette_lookup_entry(maps, 0, 0, channels, c.byref(output)) == 0
    assert output.value == before
    report = {'status': 'passed', 'cases': 4096, 'scope': 'Unchanged original475183..47525c nearest-channel lookup assembly ' 'matches native using recovered and random channel tables, including ' 'first-entry ties. RGB-to-HSV and complete lookup generation remain unfinished.'}
    (args.build_dir / 'palette-lookup-entry-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
