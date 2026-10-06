"""Compare the original format converting blit 0x47ce10 with the native recovery."""
import argparse, ctypes as c, json, random, struct
from pathlib import Path
from original import Original
from oracle_kit import build

DST, SRC = 0x801000, 0x801100
DST_DATA, SRC_DATA = 0x808000, 0x80c000
DATA_SIZE = 0x1000


class Base(c.Structure):
    _fields_ = [('data', c.c_void_p), ('size', c.c_size_t), ('width', c.c_uint32),
                ('height', c.c_uint32), ('stride', c.c_uint32), ('bytes_per_pixel', c.c_uint8)]


class Surface(c.Structure):
    _fields_ = [('surface', Base), ('sub_format', c.c_uint8), ('pitched', c.c_uint8)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=8192)
    args = parser.parse_args()
    n = build(args.build_dir, 'surface-blit', ['surface_blit.c'])
    n.vertrix_surface_blit_progress.argtypes = [c.POINTER(Surface), c.POINTER(Surface), c.c_uint32, c.c_uint32]
    n.vertrix_surface_blit_region.argtypes = [c.POINTER(Surface), c.POINTER(Surface), c.POINTER(c.c_uint16)]
    n.vertrix_surface_blit_whole.argtypes = [c.POINTER(Surface), c.POINTER(Surface)]
    n.vertrix_surface_blit.argtypes = [c.POINTER(Surface), c.POINTER(Surface)] + [c.c_uint32] * 6
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x47ce10)
    totals = {}
    for case in range(args.cases):
        dst_bpp, src_bpp = rng.choice([1, 2, 3, 4]), rng.choice([1, 2, 3, 4])
        if rng.random() < 0.5:
            src_bpp = dst_bpp
        dst_sub, src_sub = rng.choice([0, 1, 2, 2, 1, 3]), rng.choice([0, 1, 2, 2, 1, 3])
        pitched = rng.choice([0, 0, 1, 5])
        dst_pitched, src_pitched = (pitched, 0) if rng.random() < 0.5 else (0, pitched)
        dw, dh = rng.randrange(1, 24), rng.randrange(1, 12)
        sw, sh = rng.randrange(1, 24), rng.randrange(1, 12)
        dst_pitch = dw * dst_bpp + rng.choice([0, 0, 1, 4, 7])
        src_pitch = sw * src_bpp + rng.choice([0, 0, 1, 4, 7])
        w = rng.randrange(0, min(dw, sw) + 1)
        h = rng.randrange(0, min(dh, sh) + 1)
        dx, dy = rng.randrange(0, dw - w + 1), rng.randrange(0, dh - h + 1)
        sx, sy = rng.randrange(0, sw - w + 1), rng.randrange(0, sh - h + 1)
        any_pitched = bool(dst_pitched or src_pitched)
        dst_stride = dst_pitch if any_pitched else dw * dst_bpp
        src_stride = src_pitch if any_pitched else sw * src_bpp
        dst_size = max(dst_pitch, dw * dst_bpp) * dh + 16
        src_size = max(src_pitch, sw * src_bpp) * sh + 16
        dst_raw, src_raw = rng.randbytes(DATA_SIZE), rng.randbytes(DATA_SIZE)
        cpu.mem_write(DST_DATA, dst_raw)
        cpu.mem_write(SRC_DATA, src_raw)
        for address, data, width, height, bpp, sub, flag, pitch in (
                (DST, DST_DATA, dw, dh, dst_bpp, dst_sub, dst_pitched, dst_pitch),
                (SRC, SRC_DATA, sw, sh, src_bpp, src_sub, src_pitched, src_pitch)):
            header = bytearray(0x20)
            struct.pack_into('<IIIBBxxIII', header, 0, data, width, height, bpp, sub, flag, pitch, 0)
            struct.pack_into('<I', header, 0x10, flag)
            struct.pack_into('<I', header, 0x14, pitch)
            cpu.mem_write(address, bytes(header))
        original.call(0x47ce10, eax=DST, edx=SRC, ebx=dx, ecx=dy, args=(sx, sy, w, h))
        native_dst = c.create_string_buffer(dst_raw, DATA_SIZE)
        native_src = c.create_string_buffer(src_raw, DATA_SIZE)
        target = Surface(Base(c.addressof(native_dst), dst_size, dw, dh, dst_pitch, dst_bpp),
                         dst_sub, dst_pitched)
        source = Surface(Base(c.addressof(native_src), src_size, sw, sh, src_pitch, src_bpp),
                         src_sub, src_pitched)
        assert n.vertrix_surface_blit(c.byref(target), c.byref(source), dx, dy, sx, sy, w, h), case
        got = bytes(cpu.mem_read(DST_DATA, DATA_SIZE))
        assert native_dst.raw == got, (
            case, dst_bpp, src_bpp, dst_sub, src_sub, any_pitched, w, h)
        assert native_src.raw == src_raw
        key = '%d<-%d%s' % (dst_bpp, src_bpp, 'p' if any_pitched else '')
        totals[key] = totals.get(key, 0) + 1
    # the wrappers 41a2f0 (progress bar) and 41ab90 (region), with real pixel memory
    OBJECT, SRC_PTR_SLOT = 0x801400, 0x801800
    for case in range(args.cases // 4):
        for wrapper in ('progress', 'region'):
            dst_bpp = src_bpp = 4
            dw, dh = rng.randrange(4, 24), rng.randrange(1, 12)
            sw, sh = rng.randrange(4, 24), rng.randrange(1, 12)
            if wrapper == 'progress':
                dw, dh = 4, 470
                sw, sh = rng.randrange(1, 5), rng.randrange(1, 9)
            tall = DATA_SIZE if wrapper == 'region' else dw * dh * 4 + 16
            dst_raw, src_raw = rng.randbytes(tall), rng.randbytes(DATA_SIZE)
            cpu.mem_write(DST_DATA, dst_raw)
            cpu.mem_write(SRC_DATA, src_raw)
            for address, data, width, height in ((DST, DST_DATA, dw, dh), (SRC, SRC_DATA, sw, sh)):
                header = bytearray(0x20)
                struct.pack_into('<IIIBB', header, 0, data, width, height, 4, 0)
                struct.pack_into('<I', header, 0x14, width * 4)
                cpu.mem_write(address, bytes(header))
            native_dst = c.create_string_buffer(dst_raw, tall)
            native_src = c.create_string_buffer(src_raw, DATA_SIZE)
            target = Surface(Base(c.addressof(native_dst), dw * dh * 4 + 16, dw, dh, dw * 4, 4), 0, 0)
            source = Surface(Base(c.addressof(native_src), sw * sh * 4 + 16, sw, sh, sw * 4, 4), 0, 0)
            if wrapper == 'progress':
                denominator = rng.randrange(1, 12)
                numerator = rng.randrange(0, denominator + 1)
                cpu.mem_write(OBJECT, struct.pack('<I', SRC) * 0x40)
                cpu.mem_write(OBJECT + 0xd0, struct.pack('<I', SRC))
                original.call(0x41a2f0, eax=OBJECT, edx=DST, ebx=numerator, ecx=denominator)
                ok = n.vertrix_surface_blit_progress(c.byref(target), c.byref(source), numerator,
                                                     denominator)
            else:
                x, y = rng.randrange(0, sw), rng.randrange(0, sh)
                w, h = rng.randrange(0, min(sw - x, dw) + 1), rng.randrange(0, min(sh - y, dh) + 1)
                words = (c.c_uint16 * 4)(x, y, w, h)
                cpu.mem_write(0x544070, struct.pack('<I', OBJECT))
                cpu.mem_write(0x558c80, struct.pack('<I', DST))
                body = bytearray(0x300)
                struct.pack_into('<HHHH', body, 0x214, x, y, w, h)
                struct.pack_into('<I', body, 0x268, SRC)
                cpu.mem_write(OBJECT, bytes(body))
                original.call(0x41ab90)
                ok = n.vertrix_surface_blit_region(c.byref(target), c.byref(source), words)
            assert ok, (case, wrapper)
            assert native_dst.raw == bytes(cpu.mem_read(DST_DATA, tall)), (case, wrapper)
            totals['wrapper_' + wrapper] = totals.get('wrapper_' + wrapper, 0) + 1
    # 441b30: the whole target from the source, through an object holding both surfaces
    for case in range(args.cases // 4):
        dw, dh = rng.randrange(1, 12), rng.randrange(1, 10)
        sw, sh = rng.randrange(dw, 24), rng.randrange(dh, 12)
        dst_raw, src_raw = rng.randbytes(DATA_SIZE), rng.randbytes(DATA_SIZE)
        cpu.mem_write(DST_DATA, dst_raw)
        cpu.mem_write(SRC_DATA, src_raw)
        for address, data, width, height in ((DST, DST_DATA, dw, dh), (SRC, SRC_DATA, sw, sh)):
            header = bytearray(0x20)
            struct.pack_into('<IIIBB', header, 0, data, width, height, 4, 0)
            struct.pack_into('<I', header, 0x14, width * 4)
            cpu.mem_write(address, bytes(header))
        absent = rng.choice([None, None, None, 'target', 'source'])
        body = bytearray(0x300)
        struct.pack_into('<II', body, 0x274, 0 if absent == 'target' else DST,
                         0 if absent == 'source' else SRC)
        cpu.mem_write(0x801400, bytes(body))
        original.call(0x441b30, eax=0x801400)
        native_dst = c.create_string_buffer(dst_raw, DATA_SIZE)
        native_src = c.create_string_buffer(src_raw, DATA_SIZE)
        target = Surface(Base(c.addressof(native_dst), dw * dh * 4 + 16, dw, dh, dw * 4, 4), 0, 0)
        source = Surface(Base(c.addressof(native_src), sw * sh * 4 + 16, sw, sh, sw * 4, 4), 0, 0)
        assert n.vertrix_surface_blit_whole(None if absent == 'target' else c.byref(target),
                                            None if absent == 'source' else c.byref(source)), case
        assert native_dst.raw == bytes(cpu.mem_read(DST_DATA, DATA_SIZE)), ('whole', case)
        totals['wrapper_whole'] = totals.get('wrapper_whole', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 47ce10 executes in the original for every format pair, sub-format '
                       'and pitched flag combination over random rectangles; the target pixel '
                       'memory (including untouched bytes) compares and the source is unchanged.'}
    (args.build_dir / 'surface-blit-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
