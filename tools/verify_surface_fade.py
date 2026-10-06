"""Compare the original surface softening routine 0x47a040 with the native recovery."""
import argparse, ctypes as c, json, random, struct
from pathlib import Path
from original import Original
from oracle_kit import build, Stubs

SURFACE = 0x801000
DATA = 0x808000
DATA_SIZE = 0x2000
TEMP, TEMP_DATA = 0x801200, 0x80a000
TABLES = 0x558cf0
TABLE_BYTES = 101 * 256


class Base(c.Structure):
    _fields_ = [('data', c.c_void_p), ('size', c.c_size_t), ('width', c.c_uint32),
                ('height', c.c_uint32), ('stride', c.c_uint32), ('bytes_per_pixel', c.c_uint8)]


class Surface(c.Structure):
    _fields_ = [('surface', Base), ('sub_format', c.c_uint8), ('pitched', c.c_uint8)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=3000)
    args = parser.parse_args()
    n = build(args.build_dir, 'surface-fade', ['surface_blit.c'])
    n.vertrix_surface_fade.argtypes = [c.POINTER(Surface)] + [c.c_uint32] * 5 + [c.c_char_p, c.c_char_p]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x47a040)

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x478d10:
            header = bytearray(0x20)
            struct.pack_into('<IIIB', header, 0, TEMP_DATA, eax, edx, ebx & 0xff)
            struct.pack_into('<I', header, 0x14, eax * (ebx & 0xff))
            cpu.mem_write(TEMP, bytes(header))
            return TEMP
        return None

    stubs = Stubs(cpu, handler)
    stubs.add(0x478d10)
    stubs.add(0x478d80)
    totals = {}
    for case in range(args.cases):
        bpp = rng.choice([1, 2, 2, 4, 4, 3])
        sub = rng.choice([1, 2])
        sw, sh = rng.randrange(2, 16), rng.randrange(2, 12)
        w, h = rng.randrange(1, sw + 1), rng.randrange(1, sh + 1)
        if w * h == 1:
            w = 2
            sw = max(sw, 2)
        x, y = rng.randrange(0, sw - w + 1), rng.randrange(0, sh - h + 1)
        percent = rng.randrange(0, 101)
        tables = rng.randbytes(TABLE_BYTES)
        raw = rng.randbytes(DATA_SIZE)
        cpu.mem_write(TABLES, tables)
        cpu.mem_write(DATA, raw)
        header = bytearray(0x20)
        struct.pack_into('<IIIBB', header, 0, DATA, sw, sh, bpp, sub)
        struct.pack_into('<I', header, 0x14, sw * bpp)
        cpu.mem_write(SURFACE, bytes(header))
        original.call(0x47a040, eax=SURFACE, edx=x, ebx=y, ecx=w, args=(h, percent))
        native = c.create_string_buffer(raw, DATA_SIZE)
        scratch = c.create_string_buffer(w * h * bpp + 16)
        surface = Surface(Base(c.addressof(native), sw * sh * bpp + 16, sw, sh, sw * bpp, bpp), sub, 0)
        n.vertrix_surface_fade(c.byref(surface), x, y, w, h, percent, tables, scratch)
        assert native.raw == bytes(cpu.mem_read(DATA, DATA_SIZE)), (case, bpp, sub, w, h)
        key = '%d%s' % (bpp, '/565' if bpp == 2 and sub == 2 else '/555' if bpp == 2 else '')
        totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 47a040 runs in the original (allocation included) over random '
                       'rectangles, percentages and tables; the pixel memory compares.'}
    (args.build_dir / 'surface-fade-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
