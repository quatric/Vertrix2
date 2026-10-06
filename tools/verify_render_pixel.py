"""Verify flag-selected recovered32-bit kernels through prepared palette views."""
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
from verify_render_weights import Weights
from verify_render_dispatch import FlagState
from verify_render_color_bank import Bank
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EBP, UC_X86_REG_ESI, UC_X86_REG_ESP, UC_X86_REG_EIP

class ImageRequest(c.Structure):
    _fields_ = [('flags', c.c_uint32), ('source_stride', c.c_uint32),
        ('destination_stride', c.c_uint32), ('width', c.c_uint16), ('height', c.c_uint16),
        ('scale', c.c_uint8), ('binary', c.c_uint8), ('transform', c.c_uint8), ('alpha', c.c_uint32)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'render-pixel.dylib'
    names = ('render_pixel.c', 'palette_map.c', 'palette_tables.c', 'palette_color.c',
             'render_palette.c', 'render_dispatch.c', 'surface.c', 'render_weights.c', 'render_row.c',
             'render_preparation.c', 'render_color.c')
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-ffp-contract=off', '-Wall',
        '-Wextra', '-Werror', *[str(source / name) for name in names], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_render_pixel32.argtypes = [c.c_uint32, c.c_uint32, c.c_uint32,
        c.POINTER(Preparation), c.POINTER(Tables), c.POINTER(c.c_uint32)]
    native.vertrix_render_binary_row32.argtypes = [c.c_void_p, c.c_size_t, c.c_size_t,
        c.c_size_t, c.c_uint16, c.c_uint32, c.POINTER(Preparation), c.POINTER(Tables)]
    native.vertrix_render_row32.argtypes = native.vertrix_render_binary_row32.argtypes
    native.vertrix_render_sample_binary_row32.argtypes = (
        native.vertrix_render_binary_row32.argtypes + [c.POINTER(c.c_uint8), c.c_size_t])
    native.vertrix_render_sample_row32.argtypes = native.vertrix_render_sample_binary_row32.argtypes
    native.vertrix_render_sample32.argtypes = [c.c_void_p, c.c_size_t, c.c_size_t,
        c.c_size_t, c.c_uint32, c.c_uint32, c.c_uint16, c.c_uint16, c.c_uint32,
        c.POINTER(Preparation), c.POINTER(Tables), c.POINTER(c.c_uint8), c.c_size_t,
        c.POINTER(c.c_uint8), c.c_size_t, c.c_int]
    native.vertrix_render_image32.argtypes = native.vertrix_render_sample32.argtypes[:11] + [c.c_int]
    native.vertrix_render_alpha_image32.argtypes = native.vertrix_render_sample32.argtypes[:8]
    native.vertrix_render_bound32.argtypes = [c.c_void_p, c.c_size_t, c.c_size_t, c.c_size_t,
        c.POINTER(ImageRequest), c.POINTER(Preparation), c.POINTER(Tables),
        c.POINTER(c.c_uint8), c.c_size_t, c.POINTER(c.c_uint8), c.c_size_t]
    native.vertrix_render_prepared32.argtypes = [c.c_void_p, c.c_size_t, c.c_size_t, c.c_size_t,
        c.POINTER(ImageRequest), c.c_uint32, FlagState, c.c_uint8, c.POINTER(Weights),
        c.POINTER(Bank), c.POINTER(Tables), c.POINTER(Preparation), c.POINTER(c.c_uint8),
        c.c_size_t, c.POINTER(c.c_uint8), c.c_size_t]
    native.vertrix_render_kernel_address.argtypes = [c.c_uint32, c.c_uint8]
    native.vertrix_render_kernel_address.restype = c.c_uint32
    native.vertrix_palette_tables_build.argtypes = [c.POINTER(Tables)]
    native.vertrix_palette_tables_free.argtypes = [c.POINTER(Tables)]
    native.vertrix_render_weights_build.argtypes = [c.POINTER(Weights)]
    tables, weights = Tables(), Weights()
    assert native.vertrix_palette_tables_build(c.byref(tables)) == 1
    assert native.vertrix_render_weights_build(c.byref(weights)) == 1
    original = Original(args.executable)
    original.cpu.mem_map(0x900000, 0x100000)
    original.cpu.mem_write(0x900000, struct.pack('<262144I', *tables.lookup[:262144]))
    original.cpu.mem_write(0x5468b0, bytes(tables.channels))
    original.cpu.mem_write(0x558cf0, bytes(weights.bytes))
    original.cpu.mem_write(0x55f1f8, b''.join(struct.pack('<512H', *row) for row in weights.words))
    original.cpu.mem_write(0x588600, bytes(weights.inverse_alpha))
    def supplied_preparation(cpu, address, size, data):
        stack = cpu.reg_read(UC_X86_REG_ESP)
        target = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
        cpu.reg_write(UC_X86_REG_ESP, stack + 4)
        cpu.reg_write(UC_X86_REG_EIP, target)
    preparation_hook = original.cpu.hook_add(UC_HOOK_CODE, supplied_preparation,
        begin=0x4ae250, end=0x4ae250)
    original.call(0x475400, stop=0x475443)
    original.cpu.mem_write(0x54b800, struct.pack('<I', 0x900000))
    original.cpu.mem_map(0xa00000, 0x40000)
    original.cpu.mem_write(0xa00000, bytes(tables.hue[:262144]))
    original.cpu.mem_write(0x54b804, struct.pack('<I', 0xa00000))
    original.cpu.mem_write(0x54c1d4, bytes(765 * 4))
    original.cpu.mem_write(0x54c1d4, struct.pack('<255I', *tables.auxiliary))
    original.cpu.mem_write(0x54c9cc, struct.pack('<255I', *([100] * 255)))
    original.cpu.mem_write(0x54d1d0, struct.pack('<256I', 0x54c9cc,
        *[0x54c1d4 + i * 4 for i in range(255)]))
    original.cpu.mem_write(0x5bb764, struct.pack('<I', 0x804000))
    original.cpu.mem_write(0x5bb768, struct.pack('<I', 0x804004))
    supported = {0x48d720, 0x48d740, 0x48d7f0, 0x48d890, 0x48d9a0, 0x48da80,
                 0x48dba0, 0x48dcd0, 0x48dd00, 0x48dd50, 0x48dda0, 0x48ddf0,
                 0x48de10, 0x490340, 0x4904c0, 0x48db70, 0x4902a0, 0x490560, 0x48de30,
                 0x48df10, 0x48dff0, 0x48e0c0, 0x48e190, 0x48e280, 0x48e370,
                 0x48e460, 0x48e520, 0x48e5f0, 0x48e6c0, 0x48e700, 0x48e850,
                 0x48e900, 0x48e9d0, 0x48ea30, 0x48eb40,
                 0x48ec10, 0x48ec70, 0x48ed80, 0x48ee50, 0x48eeb0, 0x48efc0, 0x48f070,
                 0x48f0a0, 0x48f190, 0x48f230, 0x48f260, 0x48f360, 0x48f430, 0x48f520,
                 0x48f620, 0x48f6f0, 0x48f800, 0x48f910, 0x48f9f0, 0x48faf0, 0x48fbe0,
                 0x48fcd0, 0x48fdb0, 0x48fe90, 0x490010, 0x4901a0, 0x4906a0, 0x4907d0,
                 0x4908c0, 0x490980, 0x490b30, 0x490c60, 0x490dc0, 0x490e90, 0x490f60,
                 0x491050, 0x4911d0, 0x4912e0, 0x4913e0, 0x491530, 0x491620,
                 0x491720, 0x491820, 0x491920, 0x491a00, 0x491af0, 0x491be0, 0x491ce0,
                 0x491e10, 0x491f70, 0x492120, 0x48d8c0}
    rules = list(struct.iter_unpack('<II', original.cpu.mem_read(0x4fed44, 92 * 8)))
    rng = random.Random(0x4ff024)
    counts = {}
    rejected = 0
    for required, allowed in rules:
        for case in range(256):
            flags = required | (allowed & rng.getrandbits(32))
            rule = original.call(0x4af2a0, edx=flags)
            original.call(0x4b1fde, eax=rule, ecx=0, stop=0x4b2006)
            kernel = struct.unpack('<I', original.cpu.mem_read(0x5bb72c, 4))[0]
            if kernel == 0x4901a0:
                weighted_flags = flags
            if kernel == 0x491ce0:
                cycling_weighted_flags = flags
            assert native.vertrix_render_kernel_address(flags, 4) == kernel
            prepared = Preparation()
            prepared.map_shift = rng.randrange(-100, 301)
            prepared.cycle = case
            prepared.color.half_color = rng.getrandbits(32) & 0x7f7f7f
            prepared.color.indices[:] = [rng.randrange(101) for _ in range(3)]
            prepared.color.channels[:] = [rng.randrange(256) for _ in range(3)]
            prepared.color.hue = rng.randrange(256)
            amount = rng.randrange(101)
            prepared.source_weights = c.addressof(weights.bytes[amount])
            prepared.destination_weights = c.addressof(weights.bytes[100 - amount])
            prepared.source_words = c.addressof(weights.words[amount])
            prepared.destination_words = c.addressof(weights.words[100 - amount])
            source_pixel, destination_pixel = rng.getrandbits(32), rng.getrandbits(32)
            output = c.c_uint32(0xdeadbeef)
            status = native.vertrix_render_pixel32(flags, source_pixel, destination_pixel,
                c.byref(prepared), c.byref(tables), c.byref(output))
            if kernel not in supported:
                assert status == 0 and output.value == 0xdeadbeef
                rejected += 1
                continue
            original.cpu.mem_write(0x54cdc8, struct.pack('<I', 0x54bb90 + prepared.map_shift * 4))
            if kernel in (0x490dc0, 0x490e90, 0x490f60, 0x491050, 0x4911d0, 0x4912e0,
                          0x4913e0, 0x491530, 0x491620, 0x491720, 0x491820, 0x491920, 0x491a00,
                          0x491af0, 0x491be0, 0x491ce0, 0x491e10, 0x491f70, 0x492120):
                original.call(0x4754e0, eax=prepared.cycle)
            original.cpu.mem_write(0x54d5dc, struct.pack('<3H', *prepared.color.indices))
            original.cpu.mem_write(0x54d5ec, struct.pack('<I', prepared.color.half_color))
            original.cpu.mem_write(0x54d5e8, bytes(prepared.color.channels))
            original.cpu.mem_write(0x54d5f0, bytes([prepared.color.hue]))
            original.cpu.mem_write(0x55f1f0, struct.pack('<2I',
                0x558cf0 + amount * 256, 0x558cf0 + (100 - amount) * 256))
            original.cpu.mem_write(0x5785f8, struct.pack('<2I',
                0x55f1f8 + amount * 1024, 0x55f1f8 + (100 - amount) * 1024))
            original.cpu.mem_write(0x804000, struct.pack('<2I', source_pixel, destination_pixel))
            original.call(kernel)
            expected = struct.unpack('<I', original.cpu.mem_read(0x804004, 4))[0]
            assert status == 1 and output.value == expected, (hex(kernel), case, output.value, expected)
            counts[hex(kernel)] = counts.get(hex(kernel), 0) + 1
            pixel_rng = rng
            rng = random.Random(kernel * 256 + case)
            prepared.map_shift = min(prepared.map_shift, 98)
            original.cpu.mem_write(0x54cdc8, struct.pack('<I', 0x54bb90 + prepared.map_shift * 4))
            if kernel in (0x490dc0, 0x490e90, 0x490f60, 0x491050, 0x4911d0, 0x4912e0,
                          0x4913e0, 0x491530, 0x491620, 0x491720, 0x491820, 0x491920,
                          0x491a00, 0x491af0, 0x491be0, 0x491ce0, 0x491e10, 0x491f70, 0x492120):
                original.call(0x4754e0, eax=prepared.cycle)
            row_data = bytearray(rng.randbytes(128))
            width = rng.randrange(17)
            source_offset, destination_offset = rng.randrange(65), rng.randrange(65)
            for column in range(width):
                if rng.randrange(2):
                    row_data[source_offset + column * 4 + 3] = 0
            backing = c.create_string_buffer(bytes(row_data), 128)
            original.cpu.mem_write(0x804000, bytes(row_data))
            original.cpu.mem_write(0x5bb764, struct.pack('<2I', 0x804000 + source_offset,
                0x804000 + destination_offset))
            original.cpu.mem_write(0x5bc016, struct.pack('<H', width))
            original.call(0x492280)
            assert native.vertrix_render_binary_row32(backing, 128, source_offset,
                destination_offset, width, flags, c.byref(prepared), c.byref(tables)) == 1, ('row backing', hex(kernel), case)
            assert backing.raw == bytes(original.cpu.mem_read(0x804000, 128)), ('row', hex(kernel), case)
            assert struct.unpack('<2I', original.cpu.mem_read(0x5bb764, 8)) == (
                0x804000 + source_offset + width * 4, 0x804000 + destination_offset + width * 4)
            assert original.cpu.mem_read(0x5bc016, 2) == bytes(2)
            before = backing.raw
            assert native.vertrix_render_binary_row32(backing, 128, 129,
                destination_offset, width, flags, c.byref(prepared), c.byref(tables)) == 0
            assert backing.raw == before
            c.memmove(backing, bytes(row_data), 128)
            original.cpu.mem_write(0x804000, bytes(row_data))
            original.cpu.mem_write(0x5bb764, struct.pack('<2I', 0x804000 + source_offset,
                0x804000 + destination_offset))
            original.cpu.mem_write(0x5bc016, struct.pack('<H', width))
            original.call(0x492400)
            assert native.vertrix_render_row32(backing, 128, source_offset, destination_offset,
                width, flags, c.byref(prepared), c.byref(tables)) == 1
            assert backing.raw == bytes(original.cpu.mem_read(0x804000, 128)), ('opaque row', hex(kernel), case)
            assert struct.unpack('<2I', original.cpu.mem_read(0x5bb764, 8)) == (
                0x804000 + source_offset + width * 4, 0x804000 + destination_offset + width * 4)
            assert original.cpu.mem_read(0x5bc016, 2) == bytes(2)
            sample_width = rng.randrange(1, 17)
            steps = [rng.randrange(3) for _ in range(sample_width)]
            steps[-1] = rng.randrange(256)
            advances = (c.c_uint8 * sample_width)(*steps)
            sample_data = bytearray(rng.randbytes(256))
            source_offset, destination_offset = rng.randrange(65), rng.randrange(65)
            cursor = source_offset
            for step in steps:
                if rng.randrange(2):
                    sample_data[cursor + 3] = 0
                cursor += step * 4
            sampled = c.create_string_buffer(bytes(sample_data), 256)
            original.cpu.mem_write(0x804000, bytes(sample_data))
            original.cpu.mem_write(0x5bb764, struct.pack('<2I', 0x804000 + source_offset,
                0x804000 + destination_offset))
            original.cpu.mem_write(0x5bc016, struct.pack('<H', sample_width))
            original.cpu.mem_write(0x808000, bytes(advances))
            original.cpu.mem_write(0x5bb7dc, struct.pack('<I', 0x808000))
            original.call(0x492550)
            assert native.vertrix_render_sample_binary_row32(sampled, 256, source_offset,
                destination_offset, sample_width, flags, c.byref(prepared), c.byref(tables),
                advances, sample_width) == 1
            assert sampled.raw == bytes(original.cpu.mem_read(0x804000, 256)), ('sampled', hex(kernel), case)
            assert struct.unpack('<2I', original.cpu.mem_read(0x5bb764, 8)) == (
                0x804000 + cursor, 0x804000 + destination_offset + sample_width * 4)
            assert struct.unpack('<I', original.cpu.mem_read(0x5bb7dc, 4))[0] == 0x808000 + sample_width
            assert original.cpu.mem_read(0x5bc016, 2) == bytes(2)
            before = sampled.raw
            assert native.vertrix_render_sample_binary_row32(sampled, 256, source_offset,
                destination_offset, sample_width, flags, c.byref(prepared), c.byref(tables),
                advances, sample_width - 1) == 0
            assert sampled.raw == before
            c.memmove(sampled, bytes(sample_data), 256)
            original.cpu.mem_write(0x804000, bytes(sample_data))
            original.cpu.mem_write(0x5bb764, struct.pack('<2I', 0x804000 + source_offset,
                0x804000 + destination_offset))
            original.cpu.mem_write(0x5bc016, struct.pack('<H', sample_width))
            original.cpu.mem_write(0x5bb7dc, struct.pack('<I', 0x808000))
            original.call(0x492710)
            assert native.vertrix_render_sample_row32(sampled, 256, source_offset,
                destination_offset, sample_width, flags, c.byref(prepared), c.byref(tables),
                advances, sample_width) == 1
            assert sampled.raw == bytes(original.cpu.mem_read(0x804000, 256)), ('opaque sampled', hex(kernel), case)
            assert struct.unpack('<2I', original.cpu.mem_read(0x5bb764, 8)) == (
                0x804000 + cursor, 0x804000 + destination_offset + sample_width * 4)
            assert struct.unpack('<I', original.cpu.mem_read(0x5bb7dc, 4))[0] == 0x808000 + sample_width
            assert original.cpu.mem_read(0x5bc016, 2) == bytes(2)
            rectangle_width, rectangle_height = rng.randrange(1, 5), rng.randrange(1, 5)
            hs = (c.c_uint8 * rectangle_width)(*[rng.randrange(2) for _ in range(rectangle_width)])
            vs = (c.c_uint8 * rectangle_height)(*[rng.randrange(2) for _ in range(rectangle_height)])
            vs[-1] = rng.randrange(256)
            image_data = bytearray(rng.randbytes(512))
            for byte in range(3, 512, 8):
                image_data[byte] = 0
            source_offset, destination_offset = rng.randrange(65), rng.randrange(65)
            image = c.create_string_buffer(bytes(image_data), 512)
            original.cpu.mem_write(0x804000, bytes(image_data))
            original.cpu.mem_write(0x808000, bytes(hs))
            original.cpu.mem_write(0x808100, bytes(vs))
            for address, value in ((0x5bb764, 0x804000 + source_offset),
                (0x5bb76c, 0x804000 + source_offset), (0x5bb768, 0x804000 + destination_offset),
                (0x5bb770, 0x804000 + destination_offset), (0x5bb7d8, 0x808000),
                (0x5bb7d4, 0x808100), (0x5bb7c0, 6), (0x5bb7c4, 16)):
                original.cpu.mem_write(address, struct.pack('<I', value))
            original.cpu.mem_write(0x5bb750, struct.pack('<2H', rectangle_width, rectangle_height))
            binary = case & 1
            original.call(0x4928f0, eax=0x492550 if binary else 0x492710)
            assert native.vertrix_render_sample32(image, 512, source_offset, destination_offset,
                24, 16, rectangle_width, rectangle_height, flags, c.byref(prepared),
                c.byref(tables), hs, rectangle_width, vs, rectangle_height, binary) == 1
            assert image.raw == bytes(original.cpu.mem_read(0x804000, 512)), ('image', hex(kernel), case)
            assert struct.unpack('<2I', original.cpu.mem_read(0x5bb764, 8)) == (
                0x804000 + source_offset + sum(vs) * 24,
                0x804000 + destination_offset + rectangle_height * 16)
            assert original.cpu.mem_read(0x5bb752, 2) == bytes(2)
            assert struct.unpack('<I', original.cpu.mem_read(0x5bb7d4, 4))[0] == 0x808100 + rectangle_height
            before = image.raw
            assert native.vertrix_render_sample32(image, 512, source_offset, destination_offset,
                24, 16, rectangle_width, rectangle_height, flags, c.byref(prepared),
                c.byref(tables), hs, rectangle_width, vs, rectangle_height - 1, binary) == 0
            assert image.raw == before
            request = ImageRequest(flags, 24, 16, rectangle_width, rectangle_height,
                1 if case & 2 else 16, binary, 0, 1 if case & 4 else 0)
            group = 2 if request.scale != 16 else 0
            index = group + binary
            selected_rule = original.call(0x4af2a0, edx=flags)
            c.memmove(image, bytes(image_data), 512)
            original.cpu.mem_write(0x804000, bytes(image_data))
            for address, value in ((0x5bb764, 0x804000 + source_offset),
                (0x5bb76c, 0x804000 + source_offset), (0x5bb768, 0x804000 + destination_offset),
                (0x5bb770, 0x804000 + destination_offset), (0x5bb7d8, 0x808000),
                (0x5bb7d4, 0x808100)):
                original.cpu.mem_write(address, struct.pack('<I', value))
            original.cpu.mem_write(0x5bb750, struct.pack('<2H', rectangle_width, rectangle_height))
            original.cpu.mem_write(0x800150, struct.pack('<I', request.alpha))
            original.cpu.mem_write(0x5bb79c, struct.pack('<I', 6 - rectangle_width))
            original.cpu.mem_write(0x5bb7c8, struct.pack('<I', 16 - rectangle_width * 4))
            original.cpu.reg_write(UC_X86_REG_ESI, 0x800000)
            original.cpu.reg_write(UC_X86_REG_EBP, 0x708800)
            for offset, value in ((0x20, selected_rule), (0x18, index), (0x24, index * 4), (0x1c, 1)):
                original.cpu.mem_write(0x708800 - offset, struct.pack('<I', value))
            row_address = struct.unpack('<I', original.cpu.mem_read(0x4ff6c4 + index * 4, 4))[0]
            image_address = struct.unpack('<I', original.cpu.mem_read(0x4ff684 + group * 4, 4))[0]
            original.call(0x4af786, eax=group, ecx=0, ebx=row_address,
                edx=image_address, stop=0x4af7b9)
            assert native.vertrix_render_bound32(image, 512, source_offset, destination_offset,
                c.byref(request), c.byref(prepared), c.byref(tables), hs, rectangle_width,
                vs, rectangle_height) == 1
            assert image.raw == bytes(original.cpu.mem_read(0x804000, 512)), ('bound image', hex(kernel), case)
            before = image.raw
            request.transform = 1
            assert native.vertrix_render_bound32(image, 512, source_offset, destination_offset,
                c.byref(request), c.byref(prepared), c.byref(tables), hs, rectangle_width,
                vs, rectangle_height) == 0
            assert image.raw == before
            c.memmove(image, bytes(image_data), 512)
            original.cpu.mem_write(0x804000, bytes(image_data))
            original.cpu.mem_write(0x5bb764, struct.pack('<2I', 0x804000 + source_offset,
                0x804000 + destination_offset))
            original.cpu.mem_write(0x5bb750, struct.pack('<2H', rectangle_width, rectangle_height))
            original.cpu.mem_write(0x5bb79c, struct.pack('<I', 6 - rectangle_width))
            original.cpu.mem_write(0x5bb7c8, struct.pack('<I', 16 - rectangle_width * 4))
            original.call(0x492880, eax=0x492280 if binary else 0x492400)
            assert native.vertrix_render_image32(image, 512, source_offset, destination_offset,
                24, 16, rectangle_width, rectangle_height, flags, c.byref(prepared),
                c.byref(tables), binary) == 1
            assert image.raw == bytes(original.cpu.mem_read(0x804000, 512)), ('native image', hex(kernel), case)
            assert struct.unpack('<2I', original.cpu.mem_read(0x5bb764, 8)) == (
                0x804000 + source_offset + rectangle_height * 24,
                0x804000 + destination_offset + rectangle_height * 16)
            assert original.cpu.mem_read(0x5bb752, 2) == bytes(2)
            before = image.raw
            assert native.vertrix_render_image32(image, 512, 513, destination_offset,
                24, 16, rectangle_width, rectangle_height, flags, c.byref(prepared),
                c.byref(tables), binary) == 0
            assert image.raw == before
            original.cpu.mem_write(0x5bb764, struct.pack('<2I', 0x804000, 0x804004))
            rng = pixel_rng
    assert set(int(address, 16) for address in counts) == supported
    original.cpu.mem_write(0x588600, bytes(weights.inverse_alpha))
    alpha_rng = random.Random(0x4ab380)
    for case in range(4096):
        width, height = alpha_rng.randrange(9), alpha_rng.randrange(9)
        source_stride, destination_stride = alpha_rng.randrange(9) * 4, alpha_rng.randrange(41)
        source_offset, destination_offset = alpha_rng.randrange(33), alpha_rng.randrange(33)
        data = bytearray(alpha_rng.randbytes(512))
        for byte in range(3, 512, 4):
            data[byte] = alpha_rng.choice((0, 255, alpha_rng.randrange(256)))
        backing = c.create_string_buffer(bytes(data), 512)
        original.cpu.mem_write(0x804000, bytes(data))
        original.cpu.mem_write(0x5bb764, struct.pack('<2I', 0x804000 + source_offset,
            0x804000 + destination_offset))
        original.cpu.mem_write(0x5bb750, struct.pack('<2H', width, height))
        original.cpu.mem_write(0x5bb79c, struct.pack('<I', (source_stride // 4 - width) & 0xffffffff))
        original.cpu.mem_write(0x5bb7c8, struct.pack('<I', (destination_stride - width * 4) & 0xffffffff))
        original.call(0x4ab380)
        assert native.vertrix_render_alpha_image32(backing, 512, source_offset,
            destination_offset, source_stride, destination_stride, width, height) == 1
        assert backing.raw == bytes(original.cpu.mem_read(0x804000, 512)), ('alpha image', case)
        if width and height:
            before = backing.raw
            assert native.vertrix_render_alpha_image32(backing, 512, 513,
                destination_offset, source_stride, destination_stride, width, height) == 0
            assert backing.raw == before
    original.cpu.mem_write(0x5bb764, struct.pack('<2I', 0x804000, 0x804004))
    original.cpu.hook_del(preparation_hook)
    prepared_rng = random.Random(0x4af560)
    complete_prepared_cases = 0
    invalid_prepared_cases = 0
    while complete_prepared_cases < 2048:
        state = FlagState(prepared_rng.randrange(2), prepared_rng.randrange(2),
            prepared_rng.choice((0, 1, 3, 4, 5, 6, 7, 8)), prepared_rng.choice((0, 50, 100)),
            prepared_rng.choice((13, prepared_rng.randrange(13))), 13,
            prepared_rng.randrange(2), prepared_rng.randrange(-20, 51) & 65535)
        for address, value in zip((0x5bb73a, 0x5bb739, 0x5bc00d, 0x5bc00e,
                                  0x5bc000, 0x5bb730, 0x5bc00c), tuple(getattr(state, name)
                                  for name, _ in FlagState._fields_[:-1])):
            original.cpu.mem_write(address, bytes([value]))
        original.cpu.mem_write(0x5bc002, struct.pack('<H', state.word_002))
        original_flags = original.call(0x4af370)
        if native.vertrix_render_kernel_address(original_flags, 4) not in supported:
            continue
        bank = Bank()
        for i in range(13):
            bank.lookup[i] = sum(prepared_rng.randrange(101) << shift for shift in (0, 8, 16, 24))
            bank.colors[i] = prepared_rng.getrandbits(32)
        original.cpu.mem_write(0x54b808, bytes(bank.lookup))
        original.cpu.mem_write(0x54b83c, bytes(bank.colors))
        prepared = Preparation()
        prepared.source_weights = c.addressof(weights.bytes[50])
        prepared.destination_weights = c.addressof(weights.bytes[50])
        prepared.source_words = c.addressof(weights.words[50])
        prepared.destination_words = c.addressof(weights.words[50])
        for address, payload in ((0x54d5d4, bytes(4)), (0x5bc008, bytes(4)),
            (0x54d5ec, bytes(4)), (0x54d5dc, bytes(6)), (0x54d5e8, bytes(3)),
            (0x54d5f0, bytes(1)), (0x54cdc8, struct.pack('<I', 0x54bb90)),
            (0x55f1f0, struct.pack('<2I', 0x558cf0 + 50 * 256, 0x558cf0 + 50 * 256)),
            (0x5785f8, struct.pack('<2I', 0x55f1f8 + 50 * 1024, 0x55f1f8 + 50 * 1024))):
            original.cpu.mem_write(address, payload)
        original.call(0x4754e0, eax=0)
        request = ImageRequest(0, 24, 16, prepared_rng.randrange(1, 5),
            prepared_rng.randrange(1, 5), prepared_rng.choice((1, 16)), prepared_rng.randrange(2),
            0, prepared_rng.randrange(2))
        cycle = prepared_rng.randrange(256)
        resource = prepared_rng.choice((0, 1, 1, 1))
        original.cpu.mem_write(0x800000, bytes(0x160))
        original.cpu.mem_write(0x800134, struct.pack('<I', resource))
        original.cpu.mem_write(0x800150, struct.pack('<I', request.alpha))
        for address, value in ((0x5bb738, request.scale), (0x5bbfff, request.binary),
            (0x5bbff0, 0), (0x5bb733, 4), (0x5bb7b8, cycle)):
            original.cpu.mem_write(address, bytes([value]))
        source_offset, destination_offset = prepared_rng.randrange(65), prepared_rng.randrange(65)
        data = prepared_rng.randbytes(512)
        backing = c.create_string_buffer(data, 512)
        original.cpu.mem_write(0x804000, data)
        hs = (c.c_uint8 * request.width)(*[prepared_rng.randrange(2) for _ in range(request.width)])
        vs = (c.c_uint8 * request.height)(*[prepared_rng.randrange(2) for _ in range(request.height)])
        original.cpu.mem_write(0x808000, bytes(hs))
        original.cpu.mem_write(0x808100, bytes(vs))
        for address, value in ((0x5bb764, 0x804000 + source_offset),
            (0x5bb76c, 0x804000 + source_offset), (0x5bb768, 0x804000 + destination_offset),
            (0x5bb770, 0x804000 + destination_offset), (0x5bb7d8, 0x808000),
            (0x5bb7d4, 0x808100), (0x5bb7c0, 6), (0x5bb7c4, 16),
            (0x5bb79c, 6 - request.width), (0x5bb7c8, 16 - request.width * 4)):
            original.cpu.mem_write(address, struct.pack('<I', value))
        original.cpu.mem_write(0x5bb750, struct.pack('<2H', request.width, request.height))
        original.call(0x4af560)
        assert native.vertrix_render_prepared32(backing, 512, source_offset, destination_offset,
            c.byref(request), resource, state, cycle, c.byref(weights), c.byref(bank),
            c.byref(tables), c.byref(prepared), hs, request.width, vs, request.height) == 1
        assert backing.raw == bytes(original.cpu.mem_read(0x804000, 512)), ('complete prepared', complete_prepared_cases)
        if resource and not (state.amount_00e == 0 and state.flag_739 == 1 and
                             state.word_002 == 0 and state.format_000 == state.format_730):
            before, previous_preparation = backing.raw, bytes(prepared)
            assert native.vertrix_render_prepared32(backing, 512, 513, destination_offset,
                c.byref(request), resource, state, cycle, c.byref(weights), c.byref(bank),
                c.byref(tables), c.byref(prepared), hs, request.width, vs, request.height) == 0
            assert backing.raw == before and bytes(prepared) == previous_preparation
            invalid_prepared_cases += 1
        complete_prepared_cases += 1
    original.cpu.mem_write(0x5bb764, struct.pack('<2I', 0x804000, 0x804004))
    channel_fixture = rng.randbytes(20301)
    c.memmove(tables.channels, channel_fixture, 20301)
    original.cpu.mem_write(0x5468b0, channel_fixture)
    for slot in range(-200, 401):
        prepared = Preparation()
        prepared.map_shift = rng.randrange(-100, 101)
        selected = slot - prepared.map_shift
        first = rng.randrange(65536)
        second = (selected - first) & 65535
        source_words = (c.c_uint16 * 256)(*([first] * 256))
        destination_words = (c.c_uint16 * 256)(*([second] * 256))
        prepared.source_words = c.addressof(source_words)
        prepared.destination_words = c.addressof(destination_words)
        original.cpu.mem_write(0x806000, struct.pack('<256H', *source_words))
        original.cpu.mem_write(0x807000, struct.pack('<256H', *destination_words))
        original.cpu.mem_write(0x5785f8, struct.pack('<2I', 0x806000, 0x807000))
        original.cpu.mem_write(0x54cdc8, struct.pack('<I', 0x54bb90 + prepared.map_shift * 4))
        source_pixel, destination_pixel = rng.getrandbits(32), rng.getrandbits(32)
        original.cpu.mem_write(0x804000, struct.pack('<2I', source_pixel, destination_pixel))
        original.call(0x4901a0)
        expected = struct.unpack('<I', original.cpu.mem_read(0x804004, 4))[0]
        output = c.c_uint32(0xdeadbeef)
        assert native.vertrix_render_pixel32(weighted_flags, source_pixel, destination_pixel,
            c.byref(prepared), c.byref(tables), c.byref(output)) == 1
        assert output.value == expected, (slot, selected, output.value, expected)
        prepared.cycle = rng.randrange(256)
        original.call(0x4754e0, eax=prepared.cycle)
        original.cpu.mem_write(0x804000, struct.pack('<2I', source_pixel, destination_pixel))
        original.call(0x491ce0)
        expected = struct.unpack('<I', original.cpu.mem_read(0x804004, 4))[0]
        output = c.c_uint32(0xdeadbeef)
        assert native.vertrix_render_pixel32(cycling_weighted_flags, source_pixel,
            destination_pixel, c.byref(prepared), c.byref(tables), c.byref(output)) == 1
        assert output.value == expected, ('cycling', slot, selected, output.value, expected)
    native.vertrix_palette_tables_free(c.byref(tables))
    report = {'status': 'passed', 'kernel_cases': counts, 'signed_weighted_row_cases': 601,
        'premultiplied_alpha_image_cases': 4096,
        'binary_row_cases': sum(counts.values()),
        'opaque_row_cases': sum(counts.values()),
        'sampled_binary_row_cases': sum(counts.values()),
        'sampled_opaque_row_cases': sum(counts.values()),
        'sampled_image_cases': sum(counts.values()),
        'native_image_cases': sum(counts.values()),
        'bound_image_cases': sum(counts.values()),
        'complete_prepared_dispatch_cases': complete_prepared_cases,
        'invalid_prepared_dispatch_preservation_cases': invalid_prepared_cases,
        'unsupported_transform_preservation_cases': sum(counts.values()),
        'invalid_native_image_cases': sum(counts.values()),
        'invalid_sampled_image_cases': sum(counts.values()),
        'invalid_sampled_binary_row_cases': sum(counts.values()),
        'invalid_binary_row_preservation_cases': sum(counts.values()),
        'signed_cycling_weighted_row_cases': 601,
        'unsupported_preservation_cases': rejected,
        'scope': 'Original flag rule and kernel selection execute unchanged, followed '
                 'by complete supported kernel bodies. Eighty-seven 32-bit kernels match through '
                 'native prepared palette/weight views and signed map shifts. Other selected '
                 'kernels reject explicitly. Full pixel traversal/actor drawing and playable '
                 'application remain unfinished.'}
    (args.build_dir / 'render-pixel-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
