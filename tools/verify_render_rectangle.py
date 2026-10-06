"""Compare destination rectangle traversal against complete original 0x492dc0."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from verify_palette_tables import Tables
from verify_render_preparation import Preparation


class Surface(c.Structure):
    _fields_ = [('data', c.c_void_p), ('size', c.c_size_t), ('width', c.c_uint32), ('height', c.c_uint32), ('stride', c.c_uint32), ('bpp', c.c_uint8)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    library = args.build_dir.resolve() / 'rectangle.dylib'
    source = Path(__file__).resolve().parents[1] / 'source/render_rectangle.c'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror', str(source), str(source.parent / 'palette_map.c'), str(source.parent / 'render_dispatch.c'), str(source.parent / 'surface.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_render_rectangle_half32.argtypes = [c.POINTER(Surface), c.c_uint32, c.c_uint32, c.c_uint16, c.c_uint16, c.c_uint32]
    original = Original(args.executable)
    rng = random.Random(0x492dc0)
    lookup = (c.c_uint32 * 262144)(* [sum(rng.randrange(101) << shift for shift in (0, 8, 16, 24)) for _ in range(262144)])
    hue = (c.c_uint8 * 262144)()
    tables = Tables(lookup, hue)
    tables.channels[:
        ] = rng.randbytes(20301)
    original.cpu.mem_map(0x900000, 0x100000)
    original.cpu.mem_write(0x900000, bytes(lookup))
    original.cpu.mem_write(0x54b800, struct.pack('<I', 0x900000))
    original.cpu.mem_write(0x5468b0, bytes(tables.channels))
    original.call(0x475400, stop=0x475443)
    native.vertrix_render_rectangle_palette32.argtypes = [c.POINTER(Surface), c.c_uint32, c.c_uint32, c.c_uint16, c.c_uint16, c.POINTER(Tables), c.c_int16]
    native.vertrix_render_rectangle_fixed_palette32.argtypes = [c.POINTER(Surface), c.c_uint32, c.c_uint32, c.c_uint16, c.c_uint16, c.POINTER(Tables), c.c_int16, c.POINTER(c.c_uint16)]
    native.vertrix_render_rectangle_index_half32.argtypes = (native.vertrix_render_rectangle_fixed_palette32.argtypes)
    native.vertrix_render_rectangle_half_palette32.argtypes = [c.POINTER(Surface), c.c_uint32, c.c_uint32, c.c_uint16, c.c_uint16, c.POINTER(Tables), c.c_int16, c.c_uint32]
    native.vertrix_render_rectangle32.argtypes = [c.c_uint32, c.POINTER(Surface), c.c_uint32, c.c_uint32, c.c_uint16, c.c_uint16, c.POINTER(Preparation), c.POINTER(Tables)]
    selections = {}
    for required, allowed in struct.iter_unpack('<II', original.cpu.mem_read(0x4fed44, 92 * 8)):
        rule = original.call(0x4af2a0, edx=required)
        original.call(0x4b1fde, eax=rule, ecx=0, stop=0x4b2006)
        address = struct.unpack('<I', original.cpu.mem_read(0x5bb72c, 4))[0]
        if address in (0x492b90, 0x492cc0, 0x492dc0, 0x492e40, 0x492f90):
            selections[address] = required
    assert len(selections) == 5
    pixels = 0
    for case in range(4096):
        sw, sh = rng.randrange(1, 33), rng.randrange(1, 17)
        stride = rng.randrange(1, sw * 4 + 17)
        size = (sh - 1) * stride + sw * 4
        data = rng.randbytes(size)
        storage = c.create_string_buffer(data, size)
        target = Surface(c.addressof(storage), size, sw, sh, stride, 4)
        x, y = rng.randrange(sw + 1), rng.randrange(sh + 1)
        width, height = rng.randrange(sw - x + 1), rng.randrange(sh - y + 1)
        color = rng.getrandbits(32)
        count = rng.randrange(65536)
        offset = y * stride + x * 4
        original.cpu.mem_write(0x804000, data)
        original.cpu.mem_write(0x5bb768, struct.pack('<I', 0x804000 + offset))
        original.cpu.mem_write(0x54d5ec, struct.pack('<I', color))
        original.cpu.mem_write(0x5bb750, struct.pack('<2H', width, height))
        original.cpu.mem_write(0x5bc016, struct.pack('<H', count))
        original.cpu.mem_write(0x5bb7c8, struct.pack('<I', (stride - width * 4) & 0xffffffff))
        original.call(0x492dc0)
        assert native.vertrix_render_rectangle_half32(c.byref(target), x, y, width, height, color) == 1
        assert storage.raw == bytes(original.cpu.mem_read(0x804000, size)), case
        final_pointer = struct.unpack('<I', original.cpu.mem_read(0x5bb768, 4))[0]
        assert final_pointer == 0x804000 + offset + height * stride
        final_count = struct.unpack('<H', original.cpu.mem_read(0x5bc016, 2))[0]
        assert final_count == (0 if width and height else width if height else count)
        assert original.cpu.mem_read(0x5bb752, 2) == bytes(2)
        pixels += width * height
        before = storage.raw
        assert native.vertrix_render_rectangle_half32(c.byref(target), sw + 1, y, width, height, color) == 0
        assert storage.raw == before
        shift = rng.randrange(- 100, 301)
        c.memmove(storage, data, size)
        original.cpu.mem_write(0x804000, data)
        original.cpu.mem_write(0x5bb768, struct.pack('<I', 0x804000 + offset))
        original.cpu.mem_write(0x5bb750, struct.pack('<2H', width, height))
        original.cpu.mem_write(0x5bc016, struct.pack('<H', count))
        original.cpu.mem_write(0x54cdc8, struct.pack('<I', 0x54bb90 + shift * 4))
        original.call(0x492b90)
        assert native.vertrix_render_rectangle_palette32(c.byref(target), x, y, width, height, c.byref(tables), shift) == 1
        assert storage.raw == bytes(original.cpu.mem_read(0x804000, size)), ('palette', case)
        assert struct.unpack('<I', original.cpu.mem_read(0x5bb768, 4))[0] == (0x804000 + offset + height * stride)
        assert struct.unpack('<H', original.cpu.mem_read(0x5bc016, 2))[0] == (0 if width and height else width if height else count)
        before = storage.raw
        if width and height:
            assert native.vertrix_render_rectangle_palette32(c.byref(target), x, y, width, height, c.byref(tables), 32767) == 0
            assert storage.raw == before
        indices = (c.c_uint16 * 3)(* [rng.randrange(256 if shift <= 98 else 101) for _ in range(3)])
        c.memmove(storage, data, size)
        original.cpu.mem_write(0x804000, data)
        original.cpu.mem_write(0x5bb768, struct.pack('<I', 0x804000 + offset))
        original.cpu.mem_write(0x5bb750, struct.pack('<2H', width, height))
        original.cpu.mem_write(0x5bc016, struct.pack('<H', count))
        original.cpu.mem_write(0x54d5dc, bytes(indices))
        original.call(0x492cc0)
        assert native.vertrix_render_rectangle_fixed_palette32(c.byref(target), x, y, width, height, c.byref(tables), shift, indices) == 1
        assert storage.raw == bytes(original.cpu.mem_read(0x804000, size)), ('fixed', case)
        assert struct.unpack('<I', original.cpu.mem_read(0x5bb768, 4))[0] == (0x804000 + offset + height * stride)
        assert struct.unpack('<H', original.cpu.mem_read(0x5bc016, 2))[0] == (0 if width and height else width if height else count)
        if width and height:
            before = storage.raw
            assert native.vertrix_render_rectangle_fixed_palette32(c.byref(target), x, y, width, height, c.byref(tables), shift, None) == 0
            assert storage.raw == before
        for address, function, argument in ((0x492e40, native.vertrix_render_rectangle_index_half32, indices), (0x492f90, native.vertrix_render_rectangle_half_palette32, color)):
            c.memmove(storage, data, size)
            original.cpu.mem_write(0x804000, data)
            original.cpu.mem_write(0x5bb768, struct.pack('<I', 0x804000 + offset))
            original.cpu.mem_write(0x5bb750, struct.pack('<2H', width, height))
            original.cpu.mem_write(0x5bc016, struct.pack('<H', count))
            original.call(address)
            assert function(c.byref(target), x, y, width, height, c.byref(tables), shift, argument) == 1
            assert storage.raw == bytes(original.cpu.mem_read(0x804000, size)), (hex(address), case)
            assert struct.unpack('<I', original.cpu.mem_read(0x5bb768, 4))[0] == (0x804000 + offset + height * stride)
            assert struct.unpack('<H', original.cpu.mem_read(0x5bc016, 2))[0] == (0 if width and height else width if height else count)
            if width and height:
                before = storage.raw
                assert function(c.byref(target), x, y, width, height, c.byref(tables), 32767, argument) == 0
                assert storage.raw == before
        prepared = Preparation()
        prepared.map_shift = shift
        prepared.color.indices[:
            ] = indices
        prepared.color.half_color = color
        for address, flags in selections.items():
            c.memmove(storage, data, size)
            original.cpu.mem_write(0x804000, data)
            original.cpu.mem_write(0x5bb768, struct.pack('<I', 0x804000 + offset))
            original.cpu.mem_write(0x5bb750, struct.pack('<2H', width, height))
            original.cpu.mem_write(0x5bc016, struct.pack('<H', count))
            original.call(address)
            assert native.vertrix_render_rectangle32(flags, c.byref(target), x, y, width, height, c.byref(prepared), c.byref(tables)) == 1
            assert storage.raw == bytes(original.cpu.mem_read(0x804000, size)), ('dispatch', case, hex(address))
        before = storage.raw
        assert native.vertrix_render_rectangle32(0xffffffff, c.byref(target), x, y, width, height, c.byref(prepared), c.byref(tables)) == 0
        assert storage.raw == before
    report = {'status': 'passed', 'original_rectangle_cases': 4096, 'flag_selected_rectangle_cases': 20480, 'original_index_half_rectangle_cases': 4096, 'original_half_palette_rectangle_cases': 4096, 'original_fixed_palette_rectangle_cases': 4096, 'original_palette_rectangle_cases': 4096, 'pixels': pixels, 'invalid_preservation_cases': 4096, 'scope': 'All five original destination rectangle bodies compare whole backing, forward traversal, ' 'overlapping rows, zero dimensions, arbitrary packed colors and final ' 'original cursor/counters. Actor dispatch and playable application remain unfinished.'}
    (args.build_dir / 'render-rectangle-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
