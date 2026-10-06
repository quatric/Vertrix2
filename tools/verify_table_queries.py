"""Compare complete original table query routines with the native recovery."""
import ctypes as c, random, struct
from original import Original
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX
import verify_common_a as common
U, B = c.c_uint32, c.POINTER(c.c_uint8)
Compare = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_uint32, c.c_void_p)


def fake_compare(item, key):
    return (item * 7 + key) % 3


def main():
    args = common.parse(__doc__)
    n = common.build(args, 'table-queries', 'table_queries.c')
    PU32, PU16 = c.POINTER(c.c_uint32), c.POINTER(c.c_uint16)
    n.vertrix_table_byte_pair.argtypes = [B, B, c.c_uint8, c.c_uint8, B, B]
    n.vertrix_table_grid_value.argtypes = [PU32, U, U]
    n.vertrix_table_grid_value.restype = U
    n.vertrix_table_row_used.argtypes = [B, U]
    n.vertrix_table_row_used.restype = U
    n.vertrix_table_bonus.argtypes = [U, U, U, PU32, U]
    n.vertrix_table_bonus.restype = U
    n.vertrix_table_column_count.argtypes = [PU32, PU32, U, U]
    n.vertrix_table_column_count.restype = U
    n.vertrix_table_column_nth.argtypes = [PU32, PU32, U, U, U]
    n.vertrix_table_column_nth.restype = U
    n.vertrix_table_last_change.argtypes = [PU32, U]
    n.vertrix_table_last_change.restype = c.c_uint8
    n.vertrix_table_level_for.argtypes = [PU16, U]
    n.vertrix_table_level_for.restype = U
    n.vertrix_table_all_filled.argtypes = [PU32]
    n.vertrix_table_all_filled.restype = U
    n.vertrix_table_find_matching.argtypes = [PU32, U, U, Compare, c.c_void_p]
    n.vertrix_table_find_matching.restype = c.c_int32
    n.vertrix_table_find_equal.argtypes = [PU32, U, U]
    n.vertrix_table_find_equal.restype = c.c_int32
    n.vertrix_table_value_matching.argtypes = [PU32, PU32, U, U, Compare, c.c_void_p]
    n.vertrix_table_value_matching.restype = U
    n.vertrix_table_value_equal.argtypes = [PU32, PU32, U, U]
    n.vertrix_table_value_equal.restype = U
    n.vertrix_table_pair_select.argtypes = [PU32, U, U, PU32, PU32]
    n.vertrix_table_pair_select.restype = c.c_int
    n.vertrix_table_pair_link.argtypes = [B, B, B, c.c_uint8, c.c_uint8]
    n.vertrix_table_pair_link.restype = U
    n.vertrix_table_groups_used.argtypes, n.vertrix_table_groups_used.restype = [B, U], U
    Draw = c.CFUNCTYPE(U, U, c.c_void_p)
    n.vertrix_table_random_empty.argtypes, n.vertrix_table_random_empty.restype = [PU32, Draw, c.c_void_p], U
    n.vertrix_table_column_open.argtypes, n.vertrix_table_column_open.restype = [PU32, PU32, U], U
    n.vertrix_table_column_open_nth.argtypes = [PU32, PU32, U, U]
    n.vertrix_table_column_open_nth.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x417930)
    compare_log = []
    def on_compare(uc):
        item, key = uc.reg_read(UC_X86_REG_EAX), uc.reg_read(UC_X86_REG_EDX)
        cpu.mem_write(common.DATA, struct.pack('<I', fake_compare(item, key)))
    common.stub(cpu, 0x4ccfe0, on_compare)
    draws = []
    def on_draw(uc):
        limit = uc.reg_read(UC_X86_REG_EDX) & 0xffff
        pick = rng.randrange(limit) | (rng.getrandbits(16) << 16 if rng.random() < 0.3 else 0)
        draws.append((limit, pick))
        cpu.mem_write(common.DATA + 4, struct.pack('<I', pick))
    common.stub(cpu, 0x4826c0, on_draw, 1)
    replay = []
    @ Draw
    def draw(limit, context):
        replay.append((limit, draws[len(replay)][1]))
        return draws[len(replay) - 1][1]
    @ Compare
    def compare(item, key, context):
        return fake_compare(item, key)
    totals = {}
    def count(name):
        totals[name] = totals.get(name, 0) + 1
    def fill(address, size, low=0, high=255):
        data = bytes(rng.randrange(low, high + 1) for _ in range(size))
        cpu.mem_write(address, data)
        return data
    def words(address, size, * pool):
        data = b''.join(struct.pack('<I', rng.choice(pool) if pool else rng.getrandbits(32)) for _ in range(size))
        cpu.mem_write(address, data)
        return (c.c_uint32 * size).from_buffer_copy(data)
    for case in range(args.cases):
        fill(0x4f9320, 8192)
        fill(0x4f9538, 8192)
        first, second = bytes(cpu.mem_read(0x4f9320, 8192)), bytes(cpu.mem_read(0x4f9538, 8192))
        pa, pb = (c.c_uint8 * 8192).from_buffer_copy(first), (c.c_uint8 * 8192).from_buffer_copy(second)
        row, column = rng.randrange(256), rng.randrange(256) if rng.random() < 0.5 else rng.randrange(28)
        out1, out2 = c.c_uint8(), c.c_uint8()
        cpu.mem_write(common.DATA + 0x100, bytes(2))
        original.call(0x417930, eax=row | 0xabcd00, edx=column | 0x1200, ebx=common.DATA + 0x100, ecx=common.DATA + 0x101)
        n.vertrix_table_byte_pair(c.cast(pa, B), c.cast(pb, B), row, column, c.byref(out1), c.byref(out2))
        assert bytes(cpu.mem_read(common.DATA + 0x100, 2)) == bytes([out1.value, out2.value]), (case, row, column, bytes(cpu.mem_read(common.DATA + 0x100, 2)), out1.value, out2.value)
        count('byte_pair')
        grid = words(0x533e1c, 2048)
        r, col = rng.randrange(25), rng.randrange(25)
        want = original.call(0x417cf0, eax=r, edx=col)
        assert n.vertrix_table_grid_value(grid, r, col) == want, case
        for address, base in ((0x417d10, 0x4f8ce0), (0x417d40, 0x4f8ce4), (0x417d70, 0x4f8ce8)):
            offset = rng.randrange(25)
            cpu.mem_write(base, struct.pack('<I', offset))
            assert n.vertrix_table_grid_value(grid, r, offset) == original.call(address, eax=r), (case, address)
        count('grid_value')
        flags = fill(0x4f9ad8, 400, 0, 1 if rng.random() < 0.8 else 255)
        flags = bytes(b if rng.random() < 0.15 else 0 for b in flags) if rng.random() < 0.5 else flags
        cpu.mem_write(0x4f9ad8, flags)
        pf = (c.c_uint8 * 400).from_buffer_copy(flags)
        r = rng.randrange(30)
        assert n.vertrix_table_row_used(c.cast(pf, B), r) == original.call(0x417df0, eax=r), case
        count('row_used')
        mult = words(0x4f80d8, 16, * ([rng.getrandbits(32)] if rng.random() < 0.3 else []))
        limit, level = rng.choice([rng.randrange(60), rng.getrandbits(32)]), rng.randrange(16)
        cpu.mem_write(0x532b34, struct.pack('<I', limit))
        cpu.mem_write(0x532bbc, struct.pack('<I', level))
        base = rng.choice([rng.randrange(1000), rng.getrandbits(32), 99999999])
        value = rng.choice([rng.randrange(80), rng.getrandbits(32)])
        want = original.call(0x417e20, eax=base, edx=value)
        assert n.vertrix_table_bonus(base, value, limit, mult, level) == want, case
        count('bonus')
        counts = words(0x534f10, 19, * range(11))
        pool = (1, 2, 3)
        cgrid = words(0x534c18, 190, * pool)
        column, value = rng.randrange(19), rng.choice(pool + (4,))
        assert n.vertrix_table_column_count(cgrid, counts, column, value) == original.call(0x417fc0, eax=column, edx=value), case
        count('column_count')
        nth = rng.randrange(0, 12)
        assert n.vertrix_table_column_nth(cgrid, counts, column, value, nth) == original.call(0x418000, eax=column, edx=value, ebx=nth), case
        count('column_nth')
        table = words(0x533290, 260, 0, 1, 2)
        limit = rng.randrange(255)
        want = original.call(0x417840, eax=limit) & 0xff
        assert n.vertrix_table_last_change(table, limit) == want, (case, limit)
        count('last_change')
        steps = fill(0x4f74d4, 192, 0, 255)
        if rng.random() < 0.5:
            steps = struct.pack('<96H', * sorted((rng.randrange(0, 2000) for _ in range(96)), reverse=True))
            cpu.mem_write(0x4f74d4, steps)
        ps = (c.c_uint16 * 96).from_buffer_copy(steps)
        value = rng.choice([0, rng.randrange(2500), rng.getrandbits(32)])
        assert n.vertrix_table_level_for(ps, value) == original.call(0x40f170, eax=value), case
        count('level_for')
        for address, base in ((0x415c00, 0x5344a4), (0x415c30, 0x5344f0)):
            slots = words(base, 19, * ([0, 1, 5, 9] if rng.random() < 0.1 else [1, 2, 3, 4, 5]))
            assert n.vertrix_table_all_filled(slots) == original.call(address), (case, address)
            count('all_filled')
            items = words(0x806000, 16, 1, 2, 3, 4, 5, 6)
            total = rng.randrange(17)
            key = rng.randrange(1, 8)
            want = original.call(0x415e40, eax=key, edx=0x806000, ebx=total) & 0xffffffff
            assert n.vertrix_table_find_matching(items, total, key, compare, None) & 0xffffffff == want, case
            want = original.call(0x415e80, eax=key, edx=0x806000, ebx=total) & 0xffffffff
            assert n.vertrix_table_find_equal(items, total, key) & 0xffffffff == want, case
            count('find')
            values = words(0x806400, 16)
            want = original.call(0x415eb0, eax=key, edx=0x806000, ebx=0x806400, ecx=total) & 0xffffffff
            assert n.vertrix_table_value_matching(items, values, total, key, compare, None) == want, case
            want = original.call(0x415ed0, eax=key, edx=0x806400, ebx=0x806000, ecx=total) & 0xffffffff
            assert n.vertrix_table_value_equal(items, values, total, key) == want, case
            count('value')
# 4153e0
            table = words(0x5336ac, 280)
            column, mode = rng.randrange(20), rng.choice([0, 1, 2, 3, 4, 5, 6, 7, 8, rng.getrandbits(32)])
            out = common.DATA + 0x200
            cpu.mem_write(out, struct.pack('<2I', 0xdead, 0xbeef))
            slot = rng.randrange(0, 8)
            cpu.mem_write(0x53bcd0, bytes(64))
            original.call(0x4153e0, eax=column, edx=mode, ebx=slot)
            first, second = U(0xdead), U(0xbeef)
            wrote = n.vertrix_table_pair_select(table, column, mode, c.byref(first), c.byref(second))
            got = struct.unpack('<2I', cpu.mem_read(0x53bcd0 + 8 * slot, 8))
            assert (first.value, second.value) == (got if wrote else (0xdead, 0xbeef)), (case, mode)
            assert wrote == (1 if mode <= 6 else 0), (case, mode)
            count('pair_select')
# 417970
            links = fill(0x4f90f7, 2400 + 300)
            fill(0x4f9320, 8192)
            fill(0x4f9538, 8192)
            zero_bias = rng.random() < 0.5
            if zero_bias:
                cpu.mem_write(0x4f9320, bytes(b if rng.random() < 0.7 else 0 for b in cpu.mem_read(0x4f9320, 8192)))
            cpu.mem_write(0x4f9538, bytes(b if rng.random() < 0.7 else 0 for b in cpu.mem_read(0x4f9538, 8192)))
        first = bytes(cpu.mem_read(0x4f9320, 8192))
        second = bytes(cpu.mem_read(0x4f9538, 8192))
        linkdata = bytes(cpu.mem_read(0x4f90f7, 2400))
        row, column = rng.randrange(256), rng.randrange(28)
        want = original.call(0x417970, eax=row, edx=column)
        got = n.vertrix_table_pair_link(c.cast((c.c_uint8 * 8192).from_buffer_copy(first), B), c.cast((c.c_uint8 * 8192).from_buffer_copy(second), B), c.cast((c.c_uint8 * 2400).from_buffer_copy(linkdata), B), row, column)
        assert want == got, (case, row, column)
        count('pair_link')
# 417da0
        data = fill(0x4f9800, 400, 0, 1 if rng.random() < 0.5 else 255)
        data = bytes(b if rng.random() < 0.15 else 0 for b in data) if rng.random() < 0.6 else data
        cpu.mem_write(0x4f9800, data)
        r = rng.randrange(0, 13)
        assert n.vertrix_table_groups_used(c.cast((c.c_uint8 * 400).from_buffer_copy(data), B), r) == original.call(0x417da0, eax=r), case
        count('groups_used')
# 417e60 / 417ed0
        for address, base in ((0x417e60, 0x5344a4), (0x417ed0, 0x5344f0)):
            slots = words(base, 19, * ([0, 1, 7] if rng.random() < 0.8 else [1]))
            draws.clear()
            replay.clear()
            want = original.call(address)
            got = n.vertrix_table_random_empty(slots, draw, None)
            assert want & 0xffffffff == got and draws == replay, (case, address)
            count('random_empty')
# 418050 / 4180a0
            counts = words(0x534f10, 19, * range(11))
            cgrid = words(0x534c18, 190, 0, 1, 2, 3, 4, 5, 6)
            column = rng.randrange(19)
            assert n.vertrix_table_column_open(cgrid, counts, column) == original.call(0x418050, eax=column), case
            nth = rng.randrange(0, 12)
            assert n.vertrix_table_column_open_nth(cgrid, counts, column, nth) == original.call(0x4180a0, eax=column, edx=nth), case
            count('column_open')
            common.report(args, 'table-queries', totals, 'Complete 4153e0, 417970, 417da0, 417e60, 417ed0 (draw 4826c0 stubbed and replayed), 418050, 4180a0, 417930, 417cf0, 417d10, 417d40, 417d70, 417df0, 417e20, 417fc0, 418000, ' '417840, 40f170, 415c00, 415c30, 415e40, 415e80, 415eb0 and 415ed0 run unmodified in the original over ' 'randomized table memory; only the comparison 4ccfe0 is replaced by a data-driven stub.')
if __name__ == '__main__':
    main()
