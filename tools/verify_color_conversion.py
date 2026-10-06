"""Compare complete original palette and pixel conversion routines with the native recovery."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original

ENTRIES = 0x598630
SOURCE, DESTINATION, SCRATCH = 0x801000, 0x801100, 0x802000


class Format(c.Structure):
    _fields_ = [('mask', c.c_uint32 * 4), ('shift', c.c_uint8 * 4), ('scale', c.c_uint8 * 4)]


def native_format(raw):
    masks = struct.unpack_from('<4I', raw, 4)
    return Format((c.c_uint32 * 4)(*masks), (c.c_uint8 * 4)(*raw[0x19:0x1d]),
                  (c.c_uint8 * 4)(*raw[0x1d:0x21]))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'color-conversion.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    str(source / 'color_conversion.c'), '-o', str(library)], check=True)
    n = c.CDLL(str(library))
    n.vertrix_palette_expand_vga.argtypes = [c.c_void_p, c.c_void_p]
    n.vertrix_palette_cube.argtypes = [c.c_void_p]
    n.vertrix_pixel_convert.argtypes = [c.POINTER(Format), c.POINTER(Format), c.c_uint32]
    n.vertrix_pixel_convert.restype = c.c_uint32
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x480890)
    totals = {'palette_expand_vga': 0, 'palette_cube': 0, 'pixel_convert': 0}
    for case in range(args.cases):
        rgb = rng.randbytes(768)
        cpu.mem_write(SCRATCH, rgb)
        cpu.mem_write(ENTRIES, rng.randbytes(1024))
        original.call(0x480890, eax=SCRATCH)
        entries = (c.c_uint8 * 1024)()
        n.vertrix_palette_expand_vga(rgb, entries)
        assert bytes(entries) == bytes(cpu.mem_read(ENTRIES, 1024)), case
        totals['palette_expand_vga'] += 1
        junk = rng.randbytes(768)
        cpu.mem_write(SCRATCH, junk)
        original.call(0x480ca0, eax=SCRATCH)
        cube = (c.c_uint8 * 768).from_buffer_copy(junk)
        n.vertrix_palette_cube(cube)
        assert bytes(cube) == bytes(cpu.mem_read(SCRATCH, 768)), case
        totals['palette_cube'] += 1
        for _ in range(4):
            a, b = bytearray(rng.randbytes(0x40)), bytearray(rng.randbytes(0x40))
            if rng.random() < 0.7:
                for raw in (a, b):
                    for i in range(0x19, 0x21):
                        raw[i] = rng.randrange(0, 12)
                    for slot in range(4):
                        struct.pack_into('<I', raw, 4 + 4 * slot, rng.getrandbits(32) & rng.choice(
                            [0xffffffff, 0xff, 0xff00, 0xff0000, 0xff000000, 0xf800, 0x7e0, 0x1f]))
            pixel = rng.getrandbits(32)
            cpu.mem_write(SOURCE, bytes(a))
            cpu.mem_write(DESTINATION, bytes(b))
            expected = original.call(0x481d90, eax=SOURCE, edx=DESTINATION, ebx=pixel)
            actual = n.vertrix_pixel_convert(c.byref(native_format(a)), c.byref(native_format(b)), pixel)
            assert actual == expected, (case, hex(actual), hex(expected))
            totals['pixel_convert'] += 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 480890, 480ca0 and 481d90 execute in the original over random inputs; '
                       'palette tables and converted pixels compare exactly (random shift counts '
                       'included).'}
    (build / 'color-conversion-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
