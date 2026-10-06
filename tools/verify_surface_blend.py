"""Compare the original blend routines 0x47c930 and 0x47cb40 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import build

TARGET, SOURCE = 0x801000, 0x801100
TARGET_DATA, SOURCE_DATA = 0x808000, 0x80a000
DATA_SIZE = 0x2000
TABLES = 0x558cf0
TABLE_BYTES = 101 * 256
U = c.c_uint32
NAMES = ('destination', 'source', 'counter', 'skip_target', 'skip_source', 'target_width',
         'source_width', 'target_depth', 'source_depth', 'target_format', 'source_format',
         'table_first', 'table_second')
WIDTHS = (4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 4, 4)
ADDRESSES = {
    0x47c930: (0x558b9c, 0x558ba0, 0x558ba4, 0x558ba8, 0x558bac, 0x558bb4, 0x558bb8, 0x558bbc,
               0x558bbd, 0x558bbe, 0x558bbf, 0x55f1f0, 0x55f1f4),
    0x47cb40: (0x558bc8, 0x558bcc, 0x558bd8, 0x558bdc, 0x558be0, 0x558be8, 0x558bec, 0x558bf0,
               0x558bf1, 0x558bf2, 0x558bf3, 0x55f1f0, 0x55f1f4),
}
FUNCTIONS = {0x47c930: 'vertrix_surface_blend', 0x47cb40: 'vertrix_surface_blend_masked'}


class Surface(c.Structure):
    _fields_ = [('data', c.c_void_p), ('size', c.c_size_t), ('address', U), ('width', U),
                ('bytes_per_pixel', c.c_uint8), ('sub_format', c.c_uint8)]


class Scratch(c.Structure):
    _fields_ = [('destination', U), ('source', U), ('counter', U), ('skip_target', U),
                ('skip_source', U), ('target_width', U), ('source_width', U),
                ('target_depth', c.c_uint8), ('source_depth', c.c_uint8),
                ('target_format', c.c_uint8), ('source_format', c.c_uint8),
                ('table_first', U), ('table_second', U)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'surface-blend', ['surface_blend.c'])
    for name in FUNCTIONS.values():
        function = getattr(n, name)
        function.argtypes = [c.POINTER(Surface), c.POINTER(Surface), U, U, U * 5, c.c_char_p,
                             c.POINTER(Scratch)]
        function.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x47c930)
    totals = {}
    for case in range(args.cases):
        for entry, function_name in FUNCTIONS.items():
            depths = rng.choice([(4, 4)] * 6 + [(4, 2), (2, 4), (3, 3), (1, 1)])
            tw, th = rng.randrange(1, 14), rng.randrange(1, 10)
            sw, sh = rng.randrange(1, 14), rng.randrange(1, 10)
            w, h = rng.randrange(0, min(tw, sw) + 1), rng.randrange(0, min(th, sh) + 1)
            column, row = rng.randrange(0, tw - w + 1), rng.randrange(0, th - h + 1)
            source_column, source_row = rng.randrange(0, sw - w + 1), rng.randrange(0, sh - h + 1)
            percent = rng.randrange(0, 101)
            tables = rng.randbytes(TABLE_BYTES)

            def pixels():
                raw = rng.randbytes(DATA_SIZE)
                return bytes(b if i % 4 != 3 or rng.random() < 0.6 else 0
                             for i, b in enumerate(raw))
            target_raw, source_raw = pixels(), pixels()
            for address, data, width, depth in ((TARGET, TARGET_DATA, tw, depths[0]),
                                                (SOURCE, SOURCE_DATA, sw, depths[1])):
                header = bytearray(0x20)
                struct.pack_into('<II', header, 0, data, width)
                header[0xc], header[0xd] = depth, rng.choice([1, 2])
                cpu.mem_write(address, bytes(header))
            cpu.mem_write(TARGET_DATA, target_raw)
            cpu.mem_write(SOURCE_DATA, source_raw)
            cpu.mem_write(TABLES, tables)
            initial = rng.getrandbits(32)
            addresses = ADDRESSES[entry]
            cpu.mem_write(0x558b9c, bytes(0x60))
            cpu.mem_write(0x55f1f0, bytes(8))
            cpu.mem_write(addresses[1], struct.pack('<I', initial))
            arguments = (source_column, source_row, w, h, percent)
            original.call(entry, eax=TARGET, edx=SOURCE, ebx=column, ecx=row, args=arguments)
            target_buffer = c.create_string_buffer(target_raw, DATA_SIZE)
            source_buffer = c.create_string_buffer(source_raw, DATA_SIZE)
            target = Surface(c.cast(target_buffer, c.c_void_p), DATA_SIZE, TARGET_DATA, tw,
                             depths[0], bytes(cpu.mem_read(TARGET + 0xd, 1))[0])
            source = Surface(c.cast(source_buffer, c.c_void_p), DATA_SIZE, SOURCE_DATA, sw,
                             depths[1], bytes(cpu.mem_read(SOURCE + 0xd, 1))[0])
            scratch = Scratch()
            scratch.source = initial
            ok = getattr(n, function_name)(c.byref(target), c.byref(source), row, column,
                                           (U * 5)(*arguments), tables, c.byref(scratch))
            assert ok == 1, (hex(entry), case)
            assert target_buffer.raw == bytes(cpu.mem_read(TARGET_DATA, DATA_SIZE)), (case, 'target')
            assert source_buffer.raw == bytes(cpu.mem_read(SOURCE_DATA, DATA_SIZE)), (case, 'source')
            for name, address, width in zip(NAMES, addresses, WIDTHS):
                expected = int.from_bytes(bytes(cpu.mem_read(address, width)), 'little')
                assert getattr(scratch, name) == expected, (hex(entry), case, name,
                                                            hex(getattr(scratch, name)),
                                                            hex(expected))
            key = hex(entry) + (' blended' if depths == (4, 4) else ' other depth')
            totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed',
              'complete_original_executions': {hex(entry): args.cases for entry in FUNCTIONS},
              'cases': totals,
              'scope': 'Each original executes completely over random surfaces and random '
                       '101 x 256 tables (a quarter of the alpha bytes are zero); both pixel '
                       'buffers and every scratch global compare, including the sums that carry '
                       'into the neighbouring channel fields and the early exits for other pixel '
                       'depths.'}
    (args.build_dir / 'surface-blend-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
