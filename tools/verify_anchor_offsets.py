"""Compare complete original anchor offset updates with the native recovery."""
import ctypes as c, random, struct
from original import Original
import verify_common_a as common

PI = c.POINTER(c.c_int32)
PU = c.POINTER(c.c_uint32)


class AnchorSet(c.Structure):
    _fields_ = [('groups', c.c_uint32), ('stride', c.c_uint32), ('counts', PU), ('anchor_x', PI),
                ('anchor_y', PI), ('item_x', PI), ('item_y', PI), ('offset_x', PI), ('offset_y', PI)]

#address of counts, anchors x / y, items x / y, offsets x / y, groups, stride, original entry
LAYOUTS = (
    (0x414a90, 19, 60, 0x53969c, 0x534888, 0x5348d4, 0x5396e8, 0x53a8b8, 0x5372fc, 0x5384cc),
    (0x414b10, 5, 5, 0x54021c, 0x540064, 0x540078, 0x540230, 0x540294, 0x540154, 0x5401b8),
)


def main():
    args = common.parse(__doc__)
    n = common.build(args, 'anchor-offsets', 'anchor_offsets.c')
    n.vertrix_anchor_offsets_update.argtypes = [c.POINTER(AnchorSet)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x414a90)
    totals = {}
    for case in range(args.cases):
        for entry, groups, stride, counts, ax, ay, ix, iy, ox, oy in LAYOUTS:
            def words(address, size, small=False):
                if small:
                    values = [rng.randrange(-20, 200) if rng.random() < 0.9 else rng.getrandbits(32) - (1 << 31)
                              for _ in range(size)]
                else:
                    values = [rng.randrange(0, stride + 1) for _ in range(size)]
                cpu.mem_write(address, struct.pack('<%di' % size, *values) if small else
                              struct.pack('<%dI' % size, *values))
                return values

            count_values = words(counts, groups)
            ax_v, ay_v = words(ax, groups, True), words(ay, groups, True)
            size = groups * stride
            ix_v, iy_v = words(ix, size, True), words(iy, size, True)
            ox_v, oy_v = words(ox, size, True), words(oy, size, True)
            arrays = [(c.c_int32 * len(v))(*v) for v in (ax_v, ay_v, ix_v, iy_v, ox_v, oy_v)]
            count_array = (c.c_uint32 * groups)(*count_values)
            native = AnchorSet(groups, stride, count_array, *[c.cast(a, PI) for a in arrays])
            original.call(entry)
            n.vertrix_anchor_offsets_update(c.byref(native))
            assert bytes(arrays[4]) == bytes(cpu.mem_read(ox, size * 4)), (case, hex(entry))
            assert bytes(arrays[5]) == bytes(cpu.mem_read(oy, size * 4)), (case, hex(entry))
            totals[hex(entry)] = totals.get(hex(entry), 0) + 1
    common.report(args, 'anchor-offsets', totals,
                  'Complete 414a90 and 414b10 run unmodified in the original over random anchors, item '
                  'positions (including signed extremes) and counts; both offset arrays compare whole.')


if __name__ == '__main__':
    main()
