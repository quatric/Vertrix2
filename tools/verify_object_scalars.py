"""Compare complete original one-field accessors with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path
from original import Original
from oracle_kit import Pool, Resolve, build
U, I = c.c_uint32, c.c_int32
SIZE = 0x600
CELLS = 8


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    if args.cases < 1:
        parser.error('--cases must be positive')
    n = build(args.build_dir, 'object-scalars', ['object_scalars.c', 'actor_storage.c'])
    P, SZ, UP = c.c_void_p, c.c_size_t, c.POINTER(U)
    for name in ('toggle_flag',):
        getattr(n, 'vertrix_object_' + name).argtypes = [P, SZ, U]
    n.vertrix_object_flag.argtypes = [P, SZ, U, UP]
    for name in ('set_period', 'set_counter'):
        getattr(n, 'vertrix_object_' + name).argtypes = [P, SZ, U]
    for name in ('counter_to_period', 'clear_counter'):
        getattr(n, 'vertrix_object_' + name).argtypes = [P, SZ]
    for name in ('clear_offset_x', 'clear_offset_y'):
        getattr(n, 'vertrix_piece_' + name).argtypes = [P, SZ]
    n.vertrix_object_y_above_limit.argtypes = [P, SZ, UP]
    n.vertrix_player_set_e0.argtypes = [P, SZ, U]
    n.vertrix_player_e0.argtypes = [P, SZ, UP]
    n.vertrix_player_has_e8.argtypes = [P, SZ, UP]
    n.vertrix_player_set_cd.argtypes = [P, SZ, c.c_uint8]
    n.vertrix_player_set_cc.argtypes = [P, SZ, c.c_uint8]
    n.vertrix_player_c4_is_one.argtypes = [P, SZ, UP]
    n.vertrix_player_enter_state.argtypes = [P, SZ]
    n.vertrix_player_partner_not_cc_one.argtypes = [P, SZ, Resolve, P, UP]
    n.vertrix_global_set_cell.argtypes = [P, U, U]
    n.vertrix_global_cell.argtypes = [P, U, U, UP]
    n.vertrix_global_clear.argtypes = [P]
    n.vertrix_global_increment.argtypes = [P]
    n.vertrix_global_clear_tables.argtypes = [P, P]
    n.vertrix_global_next_index.argtypes = [P]
    n.vertrix_global_reset_pair.argtypes = [U, P, P]
    n.vertrix_compare_unsigned.argtypes = [U, U]
    n.vertrix_compare_unsigned.restype = I
    n.vertrix_table_used_count.argtypes = [P]
    n.vertrix_table_used_count.restype = U
    n.vertrix_player_partner_free.argtypes = [P, SZ, Resolve, P, UP]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4126d0)
    pool = Pool(cpu, 3, SIZE)
    obj, partner = pool.handles[0], pool.handles[1]
    totals = {}
    def count(name):
        totals[name] = totals.get(name, 0) + 1
    def buf():
        return pool.buffers[obj]
    def fill():
        def patch(handle, data):
            if handle == obj:
                struct.pack_into('<I', data, 0x3b0, rng.choice([partner, obj]))
                for offset in (0x5cc, 0x5d0, 0x4e8):
                    struct.pack_into('<I', data, offset, rng.choice([0, 1, 2, rng.getrandbits(32)]))
                for offset in (0x4cc, 0x4c4):
                    data[offset] = rng.choice([0, 1, 2, rng.getrandbits(8)])
            elif handle == partner:
                data[0x4cc] = rng.choice([0, 1, 2, rng.getrandbits(8)])
        pool.fill(rng, patch)
    def mutate(address, name, native, ** registers):
        original.call(address, eax=obj, ** registers)
        assert native(), (name, 'rejected')
        assert pool.same(), (name, pool.diff())
        count(name)
    for case in range(args.cases):
        fill()
        index = rng.randrange(0, 2)
        mutate(0x4126d0, '0x4126d0', lambda: n.vertrix_object_toggle_flag(buf(), SIZE, index), edx=index)
        fill()
        index = rng.randrange(0, 2)
        out = U()
        expect = original.call(0x4126f0, eax=obj, edx=index)
        assert n.vertrix_object_flag(buf(), SIZE, index, c.byref(out)) and out.value == expect
        count('0x4126f0')
        value = rng.getrandbits(32)
        fill()
        mutate(0x418820, '0x418820', lambda: n.vertrix_object_set_period(buf(), SIZE, value), edx=value)
        fill()
        mutate(0x418840, '0x418840', lambda: n.vertrix_object_set_counter(buf(), SIZE, value), edx=value)
        fill()
        mutate(0x418830, '0x418830', lambda: n.vertrix_object_counter_to_period(buf(), SIZE))
        fill()
        mutate(0x418870, '0x418870', lambda: n.vertrix_object_clear_counter(buf(), SIZE))
        fill()
        mutate(0x42a940, '0x42a940', lambda: n.vertrix_piece_clear_offset_x(buf(), SIZE))
        fill()
        mutate(0x42a950, '0x42a950', lambda: n.vertrix_piece_clear_offset_y(buf(), SIZE))
        fill()
        mutate(0x43b860, '0x43b860', lambda: n.vertrix_player_set_e0(buf(), SIZE, value), edx=value)
        fill()
        byte = rng.getrandbits(8)
        mutate(0x43bad0, '0x43bad0', lambda: n.vertrix_player_set_cd(buf(), SIZE, byte), edx=byte)
        fill()
        mutate(0x43bae0, '0x43bae0', lambda: n.vertrix_player_set_cc(buf(), SIZE, byte), edx=byte)
        fill()
        mutate(0x43cde0, '0x43cde0', lambda: n.vertrix_player_enter_state(buf(), SIZE))
        fill()
        for address, name, fn in ((0x42ba40, 'y_above_limit', n.vertrix_object_y_above_limit), (0x43b870, 'e0', n.vertrix_player_e0), (0x43b970, 'has_e8', n.vertrix_player_has_e8), (0x43bd40, 'c4_is_one', n.vertrix_player_c4_is_one)):
            out = U()
            expect = original.call(address, eax=obj)
            if name != 'e0':
                expect &= 0xff
            assert fn(buf(), SIZE, c.byref(out)) and out.value == expect, (case, name)
            count(hex(address))
        out = U()
        expect = original.call(0x43cc90, eax=obj) & 0xff
        assert n.vertrix_player_partner_not_cc_one(buf(), SIZE, pool.resolve, None, c.byref(out))
        assert out.value == expect, case
        count('0x43cc90')
#global cells
        for address, base in ((0x415b30, 0x5344a4), (0x415b40, 0x5344f0)):
            cells = [rng.getrandbits(32) for _ in range(CELLS)]
            cpu.mem_write(base, struct.pack('<%dI' % CELLS, * cells))
            index = rng.randrange(CELLS)
            original.call(address, eax=index)
            native = (U * CELLS)(* cells)
            assert n.vertrix_global_set_cell(native, CELLS, index)
            assert bytes(native) == bytes(cpu.mem_read(base, 4 * CELLS)), case
            count(hex(address))
        cells = [rng.getrandbits(32) for _ in range(CELLS)]
        cpu.mem_write(0x53bad8, struct.pack('<%dI' % CELLS, * cells))
        index = rng.randrange(7)
        cpu.mem_write(0x53bb10, struct.pack('<I', index))
        expect = original.call(0x415d60)
        out = U()
        native = (U * CELLS)(* cells)
        assert n.vertrix_global_cell(native, 7, index, c.byref(out)) and out.value == expect
        count('0x415d60')
        index = rng.randrange(4)
        cpu.mem_write(0x53bb10, struct.pack('<I', index))
        cells = [rng.getrandbits(32) for _ in range(4)]
        cpu.mem_write(0x53baf4, struct.pack('<4I', * cells))
        cpu.mem_write(0x53bb10, struct.pack('<I', index))
        native = (U * 4)(* cells)
        original.call(0x415d90)
        assert n.vertrix_global_set_cell(native, 4, index)
        assert bytes(native) == bytes(cpu.mem_read(0x53baf4, 16)), case
        count('0x415d90')
        for address, cell in ((0x417f40, 0x540014), (0x41a930, 0x54004c)):
            value = rng.getrandbits(32)
            cpu.mem_write(cell, struct.pack('<I', value))
            original.call(address)
            native = U(value)
            n.vertrix_global_clear(c.byref(native))
            assert native.value == struct.unpack('<I', bytes(cpu.mem_read(cell, 4)))[0]
            count(hex(address))
        value = rng.getrandbits(32)
        cpu.mem_write(0x5329f8, struct.pack('<I', value))
        original.call(0x41d660)
        native = U(value)
        n.vertrix_global_increment(c.byref(native))
        assert native.value == struct.unpack('<I', bytes(cpu.mem_read(0x5329f8, 4)))[0]
        count('0x41d660')
        out = U()
        expect = original.call(0x43bd60, eax=obj) & 0xff
        assert n.vertrix_player_partner_free(buf(), SIZE, pool.resolve, None, c.byref(out))
        assert out.value == expect, case
        count('0x43bd60')
        a = [rng.getrandbits(32) for _ in range(19)]
        b = [rng.getrandbits(32) for _ in range(19)]
        cpu.mem_write(0x5344a4, struct.pack('<19I', * a))
        cpu.mem_write(0x5344f0, struct.pack('<19I', * b))
        original.call(0x415b10)
        na, nb = (U * 19)(* a), (U * 19)(* b)
        n.vertrix_global_clear_tables(na, nb)
        assert bytes(na) == bytes(cpu.mem_read(0x5344a4, 76)) and bytes(nb) == bytes(cpu.mem_read(0x5344f0, 76)), case
        count('0x415b10')
        value = rng.choice([6, 5, 7, 0xffffffff, rng.getrandbits(32)])
        cpu.mem_write(0x53bb10, struct.pack('<I', value))
        expect = original.call(0x415d40) & 0xff
        native = U(value)
        assert n.vertrix_global_next_index(c.byref(native)) == expect
        assert native.value == struct.unpack('<I', bytes(cpu.mem_read(0x53bb10, 4)))[0]
        count('0x415d40')
        mode = rng.choice([0, 1, 2, rng.getrandbits(32)])
        pair = [rng.getrandbits(32) for _ in range(2)]
        cpu.mem_write(0x532b40, struct.pack('<I', mode))
        cpu.mem_write(0x532b44, struct.pack('<2I', * pair))
        original.call(0x415530)
        first, second = U(pair[0]), U(pair[1])
        n.vertrix_global_reset_pair(mode, c.byref(first), c.byref(second))
        assert [first.value, second.value] == list(struct.unpack('<2I', bytes(cpu.mem_read(0x532b44, 8)))), case
        count('0x415530')
        left = rng.choice([0, 1, 0xffffffff, rng.getrandbits(32)])
        right = rng.choice([left, rng.getrandbits(32), 0x80000000])
        expect = original.call(0x418150, eax=left, edx=right)
        assert n.vertrix_compare_unsigned(left, right) == c.c_int32(expect).value, case
        count('0x418150')
        table = [rng.choice([0xffffffff, rng.getrandbits(32), 0]) for _ in range(7)]
        cpu.mem_write(0x80c000, struct.pack('<7I', * table))
        expect = original.call(0x425e00, eax=0x80c000)
        assert n.vertrix_table_used_count((U * 7)(* table)) == expect, case
        count('0x425e00')
    assert not n.vertrix_object_toggle_flag(buf(), 0x5cf, 0)
    assert not n.vertrix_player_enter_state(buf(), 0x473)
    assert len(totals) == 30 and all(value == args.cases for value in totals.values())
    report = {
        'status': 'passed', 'complete_original_executions': totals,
        'scope': 'The 30 listed original entrypoints execute complete normal routines. Legacy '
                 'object and global mutators compare storage, while predicates/getters compare '
                 'projected out-parameters and existing direct scalar APIs compare their returns. '
                 'Success status from legacy mutators is not an original EAX comparison. New '
                 'complete object/piece/player EAX and live address-boundary proofs are reported '
                 'separately in object-scalar-returns-verification.json; full globals retain their '
                 'separate verifier. This report makes no full-ABI claim for projected helpers.'}
    (args.build_dir / 'object-scalars-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
