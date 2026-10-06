"""Compare native palette pixels against unchanged original kernels."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'render-palette.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', str(source / 'render_palette.c'), str(source / 'palette_color.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_render_palette_pixel.argtypes = [c.c_uint32, c.POINTER(c.c_uint32), c.c_size_t, c.c_void_p, c.c_size_t, c.c_int, c.POINTER(c.c_uint16), c.POINTER(c.c_uint32)]
    native.vertrix_render_palette_pixel_layout.argtypes = [c.c_uint32, c.POINTER(c.c_uint32), c.c_size_t, c.c_void_p, c.c_size_t, c.c_size_t, c.c_size_t, c.c_int, c.POINTER(c.c_uint16), c.POINTER(c.c_uint32)]
    native.vertrix_palette_channels.argtypes = [c.c_void_p, c.c_size_t]
    original = Original(args.executable)
    rng = random.Random(0x48d740)
    lookup_bytes = rng.randbytes(262144 * 4)
    maps_bytes = rng.randbytes(131072)
    lookup = (c.c_uint32 * 262144).from_buffer_copy(lookup_bytes)
    maps = c.create_string_buffer(maps_bytes, len(maps_bytes))
    original.cpu.mem_map(0x900000, 0x140000)
    original.cpu.mem_write(0x900000, lookup_bytes)
    original.cpu.mem_write(0xa00000, maps_bytes)
    original.cpu.mem_write(0x54b800, struct.pack('<I', 0x900000))
    original.cpu.mem_write(0x54cdc8, struct.pack('<I', 0xa20000))
    original.cpu.mem_write(0xa20000, struct.pack('<256I', * [0xa00000 + i * 256 for i in range(256)]))
    original.cpu.mem_write(0x5bb764, struct.pack('<I', 0x804000))
    original.cpu.mem_write(0x5bb768, struct.pack('<I', 0x804004))
    for case in range(8192):
        pixel = rng.getrandbits(32)
        fixed = case % 2
        channels = (c.c_uint16 * 3)(* [rng.randrange(65536) for _ in range(3)])
        original.cpu.mem_write(0x804000, struct.pack('<2I', pixel, 0xdeadbeef))
        original.cpu.mem_write(0x54d5dc, bytes(channels))
        original.call(0x48d7f0 if fixed else 0x48d740)
        expected = struct.unpack('<I', original.cpu.mem_read(0x804004, 4))[0]
        output = c.c_uint32(0xdeadbeef)
        assert native.vertrix_render_palette_pixel(pixel, lookup, len(lookup), maps, len(maps_bytes), fixed, channels, c.byref(output)) == 1
        assert output.value == expected, (case, output.value, expected)
    output = c.c_uint32(0xdeadbeef)
    assert native.vertrix_render_palette_pixel(0xffffff, lookup, 0, maps, len(maps_bytes), 0, None, c.byref(output)) == 0
    assert output.value == 0xdeadbeef
    assert native.vertrix_render_palette_pixel(0, lookup, len(lookup), maps, 0, 0, None, c.byref(output)) == 0
    assert output.value == 0xdeadbeef
    channel_maps = c.create_string_buffer(201 * 101)
    assert native.vertrix_palette_channels(channel_maps, len(channel_maps)) == 1
    original.cpu.mem_write(0xa00000, channel_maps.raw)
    original.cpu.mem_write(0xa20000, struct.pack('<201I', * [0xa00000 + i * 101 for i in range(201)]))
    for case in range(4096):
        pixel = rng.getrandbits(32)
        index = ((pixel & 0xfc0000) >> 6) | ((pixel & 0xfc00) >> 4) | ((pixel & 0xfc) >> 2)
        entry = (rng.randrange(201) | (rng.randrange(101) << 8) | (rng.randrange(101) << 16) | (rng.randrange(101) << 24))
        lookup[index] = entry
        original.cpu.mem_write(0x900000 + index * 4, struct.pack('<I', entry))
        channels = (c.c_uint16 * 3)(* [rng.randrange(101) for _ in range(3)])
        fixed = case % 2
        original.cpu.mem_write(0x804000, struct.pack('<2I', pixel, 0xdeadbeef))
        original.cpu.mem_write(0x54d5dc, bytes(channels))
        original.call(0x48d7f0 if fixed else 0x48d740)
        expected = struct.unpack('<I', original.cpu.mem_read(0x804004, 4))[0]
        assert native.vertrix_render_palette_pixel_layout(pixel, lookup, len(lookup), channel_maps, len(channel_maps), 101, 201, fixed, channels, c.byref(output)) == 1
        assert output.value == expected, (case, output.value, expected)
    before = output.value
    assert native.vertrix_render_palette_pixel_layout(pixel, lookup, len(lookup), channel_maps, len(channel_maps), 101, 0, fixed, channels, c.byref(output)) == 0
    assert output.value == before
    report = {'status': 'passed', 'cases': 8192, 'original_channel_layout_cases': 4096, 'scope': 'Unchanged original48d740/48d7f0 execute without hooks. ' 'Random lookup entries, channel maps, pixels and full-word fixed channel ' 'indices match native palette conversion. Original palette creation and ' 'complete actor draw dispatch remain unfinished. Additional4096 cases ' 'match using the recovered201-by101 channel table and original pointer stride.'}
    (args.build_dir / 'render-palette-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
