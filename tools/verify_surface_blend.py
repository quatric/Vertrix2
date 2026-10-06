"""Compare the original blend routine 0x47c930 with the native recovery."""
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
SCRATCH_FIELDS = (('destination', 0x558b9c, 4), ('source', 0x558ba0, 4), ('counter', 0x558ba4, 4),
                  ('skip_target', 0x558ba8, 4), ('skip_source', 0x558bac, 4),
                  ('target_width', 0x558bb4, 4), ('source_width', 0x558bb8, 4),
                  ('target_depth', 0x558bbc, 1), ('source_depth', 0x558bbd, 1),
                  ('target_format', 0x558bbe, 1), ('source_format', 0x558bbf, 1),
                  ('table_first', 0x55f1f0, 4), ('table_second', 0x55f1f4, 4))


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
    n.vertrix_surface_blend.argtypes = [c.POINTER(Surface), c.POINTER(Surface), U, U, U * 5,
                                        c.c_char_p, c.POINTER(Scratch)]
    n.vertrix_surface_blend.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x47c930)
    totals = {'blended': 0, 'other_depth': 0}
    for case in range(args.cases):
        depths = rng.choice([(4, 4)] * 6 + [(4, 2), (2, 4), (3, 3), (1, 1)])
        tw, th = rng.randrange(1, 14), rng.randrange(1, 10)
        sw, sh = rng.randrange(1, 14), rng.randrange(1, 10)
        w, h = rng.randrange(0, min(tw, sw) + 1), rng.randrange(0, min(th, sh) + 1)
        column, row = rng.randrange(0, tw - w + 1), rng.randrange(0, th - h + 1)
        source_column, source_row = rng.randrange(0, sw - w + 1), rng.randrange(0, sh - h + 1)
        percent = rng.randrange(0, 101)
        tables = rng.randbytes(TABLE_BYTES)
        target_raw, source_raw = rng.randbytes(DATA_SIZE), rng.randbytes(DATA_SIZE)
        source_raw = bytes(b if i % 4 != 3 or rng.random() < 0.6 else 0
                           for i, b in enumerate(source_raw))
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
        cpu.mem_write(0x558b9c, bytes(0x28))
        cpu.mem_write(0x55f1f0, bytes(8))
        cpu.mem_write(0x558ba0, struct.pack('<I', initial))
        arguments = (source_column, source_row, w, h, percent)
        original.call(0x47c930, eax=TARGET, edx=SOURCE, ebx=column, ecx=row, args=arguments)
        target = Surface(c.cast(c.create_string_buffer(target_raw, DATA_SIZE), c.c_void_p),
                         DATA_SIZE, TARGET_DATA, tw, depths[0], 0)
        target_buffer = c.create_string_buffer(target_raw, DATA_SIZE)
        target.data = c.cast(target_buffer, c.c_void_p)
        source_buffer = c.create_string_buffer(source_raw, DATA_SIZE)
        source = Surface(c.cast(source_buffer, c.c_void_p), DATA_SIZE, SOURCE_DATA, sw, depths[1], 0)
        for surface, address in ((target, TARGET), (source, SOURCE)):
            surface.sub_format = bytes(cpu.mem_read(address + 0xd, 1))[0]
        scratch = Scratch()
        scratch.source = initial
        ok = n.vertrix_surface_blend(c.byref(target), c.byref(source), row, column, (U * 5)(*arguments),
                                     tables, c.byref(scratch))
        assert ok == 1, case
        assert target_buffer.raw == bytes(cpu.mem_read(TARGET_DATA, DATA_SIZE)), (case, 'target')
        assert source_buffer.raw == bytes(cpu.mem_read(SOURCE_DATA, DATA_SIZE)), (case, 'source')
        for name, address, width in SCRATCH_FIELDS:
            expected = int.from_bytes(bytes(cpu.mem_read(address, width)), 'little')
            assert getattr(scratch, name) == expected, (case, name, hex(getattr(scratch, name)),
                                                        hex(expected))
        totals['blended' if depths == (4, 4) else 'other_depth'] += 1
    report = {'status': 'passed', 'complete_original_executions': {'0x47c930': args.cases},
              'cases': totals,
              'scope': 'The original executes completely over random surfaces and random 101 x 256 '
                       'tables; both pixel buffers and every scratch global (0x558b9c..0x558bbf, '
                       '0x55f1f0, 0x55f1f4) compare, including the sums that carry into the '
                       'neighbouring channel fields and the early exits for other pixel depths.'}
    (args.build_dir / 'surface-blend-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
