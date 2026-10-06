"""Verify signed palette map bindings and pixels through original pointer tables."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from verify_palette_tables import Tables


class Map(c.Structure):
    _fields_ = [('data', c.c_void_p), ('size', c.c_size_t)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'palette-map.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
        str(source / 'palette_map.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_palette_map.argtypes = [c.POINTER(Tables), c.c_int16,
        c.c_int16, c.POINTER(Map)]
    native.vertrix_palette_map_pixel.argtypes = [c.POINTER(Tables), c.c_int16,
        c.c_uint32, c.c_int, c.POINTER(c.c_uint16), c.POINTER(c.c_uint32)]
    rng = random.Random(0x475400)
    tables = Tables()
    lookup = (c.c_uint32 * 262144)()
    hue = c.c_uint8()
    tables.lookup, tables.hue = lookup, c.pointer(hue)
    channel_bytes = rng.randbytes(20301)
    c.memmove(tables.channels, channel_bytes, 20301)
    original = Original(args.executable)
    original.cpu.mem_map(0x900000, 0x100000)
    original.cpu.mem_write(0x5468b0, channel_bytes)
    original.call(0x475400, stop=0x475443)
    original.cpu.mem_write(0x54b800, struct.pack('<I', 0x900000))
    original.cpu.mem_write(0x5bb764, struct.pack('<I', 0x804000))
    original.cpu.mem_write(0x5bb768, struct.pack('<I', 0x804004))
    for shift in range(-200, 401):
        result = Map()
        assert native.vertrix_palette_map(c.byref(tables), shift, 0, c.byref(result)) == 1
        pointer = struct.unpack('<I', original.cpu.mem_read(0x54bb90 + shift * 4, 4))[0]
        assert c.string_at(result.data, 101) == bytes(original.cpu.mem_read(pointer, 101)), shift
        indexed = Map()
        assert native.vertrix_palette_map(c.byref(tables), 0, shift, c.byref(indexed)) == 1
        assert bytes(indexed) == bytes(result)
    before = bytes(result)
    for shift in (-32768, -201, 401, 32767):
        assert native.vertrix_palette_map(c.byref(tables), shift, 0, c.byref(result)) == 0
        assert bytes(result) == before
    for case in range(4096):
        pixel = rng.getrandbits(32)
        index = ((pixel & 0xfc0000) >> 6) | ((pixel & 0xfc00) >> 4) | ((pixel & 0xfc) >> 2)
        entry = (rng.randrange(101) | (rng.randrange(101) << 8) |
                 (rng.randrange(101) << 16) | (rng.randrange(101) << 24))
        lookup[index] = entry
        original.cpu.mem_write(0x900000 + index * 4, struct.pack('<I', entry))
        shift = rng.randrange(-200, 301)
        original.cpu.mem_write(0x54cdc8, struct.pack('<I', 0x54bb90 + shift * 4))
        channels = (c.c_uint16 * 3)(*[rng.randrange(101) for _ in range(3)])
        original.cpu.mem_write(0x54d5dc, bytes(channels))
        original.cpu.mem_write(0x804000, struct.pack('<2I', pixel, 0xdeadbeef))
        original.call(0x48d7f0 if case % 2 else 0x48d740)
        expected = struct.unpack('<I', original.cpu.mem_read(0x804004, 4))[0]
        output = c.c_uint32()
        assert native.vertrix_palette_map_pixel(c.byref(tables), shift, pixel,
            case % 2, channels, c.byref(output)) == 1
        assert output.value == expected, (case, shift, output.value, expected)
    report = {'status': 'passed', 'relative_slots': 601, 'pixel_cases': 4096,
        'scope': 'Original475400..475441 builds pointer tables unchanged. Every '
                 'backed relative slot and4096 complete48d740/48d7f0 pixels match '
                 'native signed map resolution, including repeated row0 and row200. '
                 'Unbacked slots reject; full drawing/application integration remains unfinished.'}
    (args.build_dir / 'palette-map-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
