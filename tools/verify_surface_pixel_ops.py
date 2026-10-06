"""Compare complete original software surface operations with the native recovery."""
import ctypes as c, random, struct
from original import Original
import verify_support as vs

TARGET, SOURCE = vs.SCRATCH, vs.SCRATCH + 0x100
TARGET_DATA, SOURCE_DATA, OUT = vs.SCRATCH + 0x1000, vs.SCRATCH + 0x3000, vs.SCRATCH + 0x5000
DATA = 0x1800


class Surface(c.Structure):
    _fields_ = [('data', c.c_void_p), ('size', c.c_size_t), ('width', c.c_uint32),
                ('height', c.c_uint32), ('stride', c.c_uint32), ('bytes_per_pixel', c.c_uint8)]


def main():
    args = vs.parse(__doc__)
    n = vs.build(args, 'surface-pixel-ops', ['surface_pixel_ops.c', 'surface.c', 'render_dispatch.c'])
    S, U = c.POINTER(Surface), c.c_uint32
    n.vertrix_surface_or_rectangle.argtypes = [S, U, U, U, U, c.c_uint8]
    n.vertrix_surface_copy_pixel.argtypes = [S, S, c.c_int32, c.c_int32]
    n.vertrix_surface_flip_vertical.argtypes = [S]
    n.vertrix_surface_blit_keyed.argtypes = [S, U, U, S, U, U, U, U, U, U]
    n.vertrix_surface_decimate.argtypes = [S, U, c.POINTER(U), c.c_size_t]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x479450)
    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    def make(address, data_address, width, height, bpp, stride, flag=0):
        obj = bytearray(rng.randbytes(0x40))
        struct.pack_into('<IIIB', obj, 0, data_address, width, height, bpp)
        obj[0xc] = bpp
        struct.pack_into('<I', obj, 0x10, flag)
        struct.pack_into('<I', obj, 0x14, stride)
        cpu.mem_write(address, bytes(obj))
        content = bytes(rng.getrandbits(8) if rng.random() < 0.9 else 0 for _ in range(DATA))
        cpu.mem_write(data_address, content)
        buf = (c.c_uint8 * DATA).from_buffer_copy(content)
        return buf, Surface(c.cast(buf, c.c_void_p), DATA, width, height, stride, bpp)

    def guest(address):
        return bytes(cpu.mem_read(address, DATA))

    def run(name, native, oracle, buffers, extra=None):
        """Run native first on copies; a rejected case must preserve storage, accepted ones compare."""
        saved = [bytes(b) for b in buffers]
        if not native():
            assert [bytes(b) for b in buffers] == saved, name
            count(name + '_rejected')
            return
        oracle()
        for buf, address in zip(buffers, (TARGET_DATA, SOURCE_DATA)):
            assert bytes(buf) == guest(address), (name, [i for i in range(DATA) if buf[i] != guest(address)[i]][:8])
        if extra:
            extra()
        count(name)

    for case in range(args.cases):
        width = rng.choice([1, 2, 5, 16, 32, 40, 70])
        height = rng.choice([1, 2, 3, 8, 17, 30])
        bpp = rng.choice([1, 2, 3, 4, 4, 4])
        stride = width * bpp + rng.choice([0, 0, 3, 8])
# 0x479450 : OR rectangle
        t, ts = make(TARGET, TARGET_DATA, rng.choice([8, 40, 64, 100]), 30, 1, 0)
        x, y, w, rows = rng.randrange(0, 20), rng.randrange(0, 20), rng.randrange(0, 20), rng.randrange(0, 12)
        value = rng.getrandbits(8)
        run('0x479450', lambda: n.vertrix_surface_or_rectangle(c.byref(ts), x, y, w, rows, value),
            lambda: original.call(0x479450, eax=TARGET, edx=x, ebx=y, ecx=w, args=(rows, value | rng.getrandbits(24) << 8)), [t])
# 0x479d70 : copy one pixel
        tb, tsurf = make(TARGET, TARGET_DATA, width, height, bpp, stride)
        sw, sh = rng.choice([width, 5, 70]), rng.choice([height, 5])
        sbpp = rng.choice([bpp, bpp, 1, 2, 4])
        sb, ssurf = make(SOURCE, SOURCE_DATA, sw, sh, sbpp, sw * sbpp + rng.choice([0, 4]))
        px, py = rng.randrange(-2, width + 2), rng.randrange(-2, height + 2)
        run('0x479d70', lambda: n.vertrix_surface_copy_pixel(c.byref(ssurf), c.byref(tsurf), px, py),
            lambda: original.call(0x479d70, eax=TARGET, edx=SOURCE, ebx=px & 0xffffffff, ecx=py & 0xffffffff), [tb, sb])
# 0x479b50 : vertical flip(non - negative heights)
        fw, fh, fb = rng.randrange(1, 40), rng.randrange(0, 20), rng.choice([1, 2, 3, 4, 4, 0, 5])
        if rng.random() < 0.2:
            fw |= rng.getrandbits(16) << 16
            fh |= rng.getrandbits(16) << 16
        fbuf, fs = make(TARGET, TARGET_DATA, fw, fh, fb, 0)
        run('0x479b50', lambda: n.vertrix_surface_flip_vertical(c.byref(fs)),
            lambda: original.call(0x479b50, eax=TARGET), [fbuf])
# 0x47e200 : keyed blit(4 - byte pixels, flags zero)
        flags = rng.choice([0, 0, 0, 1])
        aw, ah = rng.choice([8, 16, 20]), rng.choice([8, 16])
        bw, bh = rng.choice([8, 16, 20]), rng.choice([8, 16])
        abuf, asurf = make(TARGET, TARGET_DATA, aw, ah, rng.choice([4, 4, 4, 2]), aw * 4, flags)
        bbuf, bsurf = make(SOURCE, SOURCE_DATA, bw, bh, 4, bw * 4, rng.choice([0, 0, 1]))
        xa, ya, xb, yb = (rng.randrange(0, 8) for _ in range(4))
        bw_count, rows_count = rng.randrange(0, 12), rng.randrange(0, 10)
        tflag = struct.unpack('<I', bytes(cpu.mem_read(TARGET + 0x10, 4)))[0]
        sflag = struct.unpack('<I', bytes(cpu.mem_read(SOURCE + 0x10, 4)))[0]
        run('0x47e200', lambda: n.vertrix_surface_blit_keyed(c.byref(asurf), xa, ya, c.byref(bsurf), xb, yb,
                                                              bw_count, rows_count, tflag, sflag),
            lambda: original.call(0x47e200, eax=TARGET, edx=SOURCE, ebx=xa, ecx=ya, args=(xb, yb, bw_count, rows_count)),
            [abuf, bbuf])
# 0x47cd60 : decimate into OUT
        dw, dh, dbpp = rng.choice([4, 8, 12, 16, 20, 7, 9]), rng.choice([4, 8, 12, 16, 9]), rng.choice([4, 4, 4, 2])
        n_div = rng.choice([1, 2, 3, 4, 5])
        dbuf, dsurf = make(TARGET, TARGET_DATA, dw, dh, dbpp, dw * 4)
        cpu.mem_write(OUT, bytes(0x1000))
        out = (U * 1024)()
        run('0x47cd60', lambda: n.vertrix_surface_decimate(c.byref(dsurf), n_div, out, 1024),
            lambda: original.call(0x47cd60, eax=TARGET, edx=OUT, ebx=n_div), [dbuf],
            extra=lambda: (_ for _ in ()).throw(AssertionError(case)) if bytes(cpu.mem_read(OUT, 4096)) != struct.pack('<1024I', *out) else None)
    vs.write_report(args, 'surface-pixel-ops', {
        'status': 'passed', 'complete_original_executions': totals,
        'scope': 'Complete 479450, 479d70, 479b50, 47e200 and 47cd60 execute in the original over '
                 'guest surface storage; every pixel byte of both surfaces and the decimation output '
                 'compare. Cases where the original would touch bytes outside the supplied storage '
                 'are not executed and must leave the native storage unchanged (counted as '
                 'rejected). Scratch globals 0x5589xx..0x558cxx are not modeled.'})


if __name__ == '__main__':
    main()
