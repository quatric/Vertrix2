"""Compare original48dba0 palette index half blending."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from verify_palette_tables import Tables
from verify_render_weights import Weights


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'palette-half.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-ffp-contract=off', '-Wall',
        '-Wextra', '-Werror', *[str(source / name) for name in ('palette_tables.c',
        'palette_color.c', 'render_palette.c', 'render_weights.c')], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_render_palette_half_pixel.argtypes = [c.c_uint32, c.c_uint32,
        c.POINTER(c.c_uint32), c.c_size_t, c.c_void_p, c.c_size_t,
        c.c_size_t, c.c_size_t, c.POINTER(c.c_uint32)]
    native.vertrix_render_palette_weighted_pixel.argtypes = [c.c_uint32, c.c_uint32,
        c.POINTER(c.c_uint32), c.c_size_t, c.c_void_p, c.c_size_t,
        c.c_size_t, c.c_size_t, c.c_void_p, c.c_void_p, c.POINTER(c.c_uint32)]
    native.vertrix_palette_tables_build.argtypes = [c.POINTER(Tables)]
    native.vertrix_palette_tables_free.argtypes = [c.POINTER(Tables)]
    tables = Tables()
    assert native.vertrix_palette_tables_build(c.byref(tables)) == 1
    weights = Weights()
    native.vertrix_render_weights_build.argtypes = [c.POINTER(Weights)]
    assert native.vertrix_render_weights_build(c.byref(weights)) == 1
    original = Original(args.executable)
    original.cpu.mem_map(0x900000, 0x140000)
    original.cpu.mem_write(0x54b800, struct.pack('<I', 0x900000))
    original.cpu.mem_write(0x54cdc8, struct.pack('<I', 0xa20000))
    original.cpu.mem_write(0x5bb764, struct.pack('<I', 0x804000))
    original.cpu.mem_write(0x5bb768, struct.pack('<I', 0x804004))
    original.cpu.mem_write(0x55f1f0, struct.pack('<I', 0xa30000))
    original.cpu.mem_write(0x55f1f4, struct.pack('<I', 0xa30100))
    rng = random.Random(0x48dba0)
    for phase in range(2):
        if phase == 0:
            lookup = tables.lookup
            maps_bytes = bytes(tables.channels)
            stride, count = 101, 201
        else:
            lookup = (c.c_uint32 * 262144).from_buffer_copy(rng.randbytes(1048576))
            maps_bytes = rng.randbytes(131072)
            stride, count = 256, 256
        maps = c.create_string_buffer(maps_bytes, len(maps_bytes))
        original.cpu.mem_write(0x900000, struct.pack('<262144I', *lookup[:262144]))
        original.cpu.mem_write(0xa00000, maps_bytes)
        original.cpu.mem_write(0xa20000,
            struct.pack('<%dI' % count, *[0xa00000 + i * stride for i in range(count)]))
        for case in range(4096):
source_pixel,
    destination_pixel = rng.getrandbits(32),
    rng.getrandbits(32) original.cpu
        .mem_write(0x804000, struct.pack('<2I', source_pixel, destination_pixel)) original.call(
            0x48dba0) expected = struct.unpack('<I', original.cpu.mem_read(0x804004, 4))[0] output =
        c.c_uint32(0xdeadbeef) assert native.vertrix_render_palette_half_pixel(
            source_pixel, destination_pixel, lookup, 262144, maps, len(maps_bytes), stride, count,
            c.byref(output)) == 1 assert output.value
        == expected,
    (phase, case, output.value, expected)amount =
        case % 101 source_bytes = (bytes(weights.bytes[amount]) if phase ==
                                   0 else rng.randbytes(256)) destination_bytes =
            (bytes(weights.bytes[100 - amount]) if phase ==
             0 else rng.randbytes(256)) source_weight = c.create_string_buffer(source_bytes, 256)
                                                            destination_weight =
                c.create_string_buffer(destination_bytes,
                                       256) original.cpu.mem_write(0xa30000, source_bytes) original
                    .cpu.mem_write(0xa30100, destination_bytes) original.cpu
                    .mem_write(0x804000,
                               struct.pack('<2I', source_pixel,
                                           destination_pixel)) original.call(0x490340) expected =
                    struct.unpack('<I', original.cpu.mem_read(0x804004, 4))[0] assert native
                        .vertrix_render_palette_weighted_pixel(source_pixel, destination_pixel,
                                                               lookup, 262144, maps,
                                                               len(maps_bytes), stride, count,
                                                               source_weight, destination_weight,
                                                               c.byref(output)) ==
                    1 assert output.value == expected,
    ('weighted', phase, case, output.value, expected)before =
        output.value assert native.vertrix_render_palette_half_pixel(source_pixel,
                                                                     destination_pixel, lookup, 0,
                                                                     maps, len(maps_bytes), stride,
                                                                     count, c.byref(output)) ==
        0 assert output.value ==
        before assert native.vertrix_render_palette_half_pixel(source_pixel, destination_pixel,
                                                               lookup, 262144, maps, 0, stride,
                                                               count, c.byref(output)) ==
        0 assert output.value ==
        before native.vertrix_palette_tables_free(c.byref(tables)) assert native
            .vertrix_render_palette_weighted_pixel(source_pixel, destination_pixel, lookup, 262144,
                                                   maps, len(maps_bytes), stride, count, None,
                                                   destination_weight, c.byref(output)) ==
        0 assert output.value == before report = {'status':
'passed', 'cases' : 8192, 'recovered_table_cases' : 4096, 'weighted_cases' : 8192,
    'scope'
    : 'Complete original48dba0 executes without hooks. Native palette ' 'index averaging matches original for recovered tables and arbitrary ' 'lookup/channel fixtures. Additional8192 complete original490340 weighted ' 'kernel comparisons match using recovered percentage tables and arbitrary byte ' 'weight tables, including cross-row index sums. Scene selection ' 'and full draw integration remain unfinished.'
}
(args.build_dir / 'palette-half-verification.json')
        .write_text(json.dumps(report, indent = 2) + '\n') print(json.dumps(report, indent = 2))

            if __name__ == '__main__' : main()
