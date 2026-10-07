"""Compare the cleaned object accessors with the complete original routines."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import build

OBJECT, SIZE = 0x801000, 0x1000
ELAPSED = 0x5bd834
U = c.c_uint32


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    if args.cases < 1:
        parser.error('--cases must be positive')
    n = build(args.build_dir, 'object-accessors', ['object_accessors.c', 'actor_storage.c'])
    n.vertrix_actor_add_elapsed.argtypes = [c.c_void_p, c.c_size_t, U, U]
    n.vertrix_actor_counter_pair_reached.argtypes = [c.c_void_p, c.c_size_t, U, U, c.POINTER(U)]
    n.vertrix_actor_set_times_twelve.argtypes = [c.c_void_p, c.c_size_t, U, U]
    n.vertrix_player_fill_bytes.argtypes = [c.c_void_p, c.c_size_t, U, U, U]
    n.vertrix_object_clear_slots.argtypes = [c.c_void_p, c.c_size_t]
    n.vertrix_compare_u32.argtypes = [U, U]
    n.vertrix_compare_u32.restype = c.c_int32
    n.vertrix_object_set_18.argtypes = [c.c_void_p, c.c_size_t, U]
    n.vertrix_player_set_bytes_168.argtypes = [c.c_void_p, c.c_size_t, U, U, U]
    for name in ('actor_clock_reached', 'player_flag_4e8', 'player_bonus_meter_full',
                 'player_flag_a60', 'player_byte_4c4_is_one'):
        getattr(n, 'vertrix_' + name).argtypes = [c.c_void_p, c.c_size_t, c.POINTER(U)]
    for name in ('actor_clock_to_period', 'actor_select_ec', 'actor_select_f0'):
        getattr(n, 'vertrix_' + name).argtypes = [c.c_void_p, c.c_size_t]
    full_args = {
        'actor_advance_elapsed': [U, U, U], 'actor_sync_clock_period': [U],
        'actor_choose_handler': [U, U], 'player_write_bytes_168': [U, U, U, U],
        'player_test_4e8': [], 'player_test_a60': [], 'player_test_4c4': [],
        'object_write_18': [U, U], 'actor_test_counter_pair': [U, U],
        'actor_store_times_twelve': [U, U], 'player_fill_byte_range': [U, U, U, U],
        'object_reset_slots': [U],
    }
    for name, extra in full_args.items():
        function = getattr(n, 'vertrix_' + name)
        function.argtypes = [c.c_void_p, c.c_size_t] + extra
        function.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_map(0xfffff000, 0x1000)

    def write_object(token, data):
        top = min(len(data), 0x100000000 - token)
        cpu.mem_write(token, bytes(data[:top]))
        if top < len(data):
            cpu.mem_write(0, bytes(data[top:]))

    def read_object(token):
        top = min(SIZE, 0x100000000 - token)
        return bytes(cpu.mem_read(token, top)) + (bytes(cpu.mem_read(0, SIZE - top)) if top < SIZE else b'')
    rng = random.Random(0x4ac500)
    totals, full_totals = {}, {}

    def interesting():
        return rng.choice([0, 1, 2, 3, 0xffffffff, 0x80000000, rng.getrandbits(32),
                           rng.randrange(0, 20)])

    for case in range(args.cases):
        object_token = (OBJECT, OBJECT + 0x1000, OBJECT + 0x4000, 0xfffffffc)[case % 4]
        raw = bytearray(rng.randbytes(SIZE))
        for offset in (0xbc, 0xc0, 0x4e8, 0x18c, 0xa60, 0x4c4):
            struct.pack_into('<I', raw, offset, interesting())
        if rng.random() < 0.4:
            struct.pack_into('<I', raw, 0xbc, struct.unpack_from('<I', raw, 0xc0)[0])
        cpu.mem_write(ELAPSED, struct.pack('<I', interesting()))
        elapsed = struct.unpack('<I', bytes(cpu.mem_read(ELAPSED, 4)))[0]

        def run(address, **registers):
            write_object(object_token, raw)
            result = original.call(address, eax=object_token, **registers) & 0xffffffff
            return result, read_object(object_token)

        def fresh():
            return c.create_string_buffer(bytes(raw), SIZE)

        def full(address, name, expected, after, *parameters):
            buffer = fresh()
            got = getattr(n, 'vertrix_' + name)(buffer, SIZE, *parameters)
            assert got == expected, (hex(address), case, name, hex(got), hex(expected))
            assert buffer.raw == after, (hex(address), case, name, 'whole_object')
            key = hex(address)
            full_totals[key] = full_totals.get(key, 0) + 1

        def count(name):
            totals[name] = totals.get(name, 0) + 1

        for address, offset in ((0x4ac500, 0xbc), (0x4ac370, 0xcc), (0x4ac600, 0xdc)):
            result, after = run(address)
            full(address, 'actor_advance_elapsed', result, after, object_token, offset, elapsed)
            buffer = fresh()
            assert n.vertrix_actor_add_elapsed(buffer, SIZE, offset, elapsed)
            assert buffer.raw == after, (hex(address), case)
            count('add_elapsed_%x' % offset)
        for address, name in ((0x418830, 'actor_clock_to_period'), (0x4ac920, 'actor_select_ec'),
                              (0x4ac940, 'actor_select_f0')):
            result, after = run(address)
            if address == 0x418830:
                full(address, 'actor_sync_clock_period', result, after, object_token)
            else:
                full(address, 'actor_choose_handler', result, after, object_token,
                     0xec if address == 0x4ac920 else 0xf0)
            buffer = fresh()
            assert getattr(n, 'vertrix_' + name)(buffer, SIZE)
            assert buffer.raw == after, (name, case)
            count(name)
        for address, name in ((0x4ac520, 'actor_clock_reached'), (0x43b970, 'player_flag_4e8'),
                              (0x43ba70, 'player_bonus_meter_full'),
                              (0x4320c0, 'player_flag_a60'), (0x43bd40, 'player_byte_4c4_is_one')):
            result, after = run(address)
            if address == 0x4ac520:
                full(address, 'actor_test_counter_pair', result, after, 0xbc, 0xc0)
            elif address != 0x43ba70:
                full(address, {0x43b970: 'player_test_4e8', 0x4320c0: 'player_test_a60',
                               0x43bd40: 'player_test_4c4'}[address], result, after)
            out = U()
            assert getattr(n, 'vertrix_' + name)(fresh(), SIZE, c.byref(out))
            assert out.value == result & 0xff and after == bytes(raw), (name, case)
            count(name)
        first, second, third = interesting(), interesting(), interesting()
        result, after = run(0x43a4f0, edx=first, ebx=second, ecx=third)
        full(0x43a4f0, 'player_write_bytes_168', result, after, object_token, first, second, third)
        buffer = fresh()
        assert n.vertrix_player_set_bytes_168(buffer, SIZE, first, second, third)
        assert buffer.raw == after, case
        count('player_set_bytes_168')
        value = interesting()
        result, after = run(0x47f8e0, edx=value)
        full(0x47f8e0, 'object_write_18', result, after, object_token, value)
        buffer = fresh()
        assert n.vertrix_object_set_18(buffer, SIZE, value)
        assert buffer.raw == after, case
        count('object_set_18')
        for address, c_off, l_off in ((0x4ac390, 0xcc, 0xd0), (0x4ac620, 0xdc, 0xe0),
                                      (0x4ac520, 0xbc, 0xc0)):
            result, after = run(address)
            full(address, 'actor_test_counter_pair', result, after, c_off, l_off)
            out = U()
            assert n.vertrix_actor_counter_pair_reached(fresh(), SIZE, c_off, l_off, c.byref(out))
            assert out.value == result & 0xff, (hex(address), case)
            count('counter_reached_%x' % c_off)
        for address, offset in ((0x4ac470, 0xd0), (0x4ac7b0, 0xc0), (0x4ac840, 0xe0)):
            value = interesting()
            result, after = run(address, edx=value)
            full(address, 'actor_store_times_twelve', result, after, offset, value)
            buffer = fresh()
            assert n.vertrix_actor_set_times_twelve(buffer, SIZE, offset, value)
            assert buffer.raw == after, (hex(address), case)
            count('set_times_twelve_%x' % offset)
        for address, start, length in ((0x42ef60, 0x99c, 5), (0x42ef80, 0x9a1, 5),
                                       (0x42f7d0, 0x9a6, 13), (0x42f7f0, 0x9b3, 13),
                                       (0x42f810, 0x9c0, 13), (0x42f830, 0x9cd, 13)):
            value = interesting()
            result, after = run(address, edx=value)
            full(address, 'player_fill_byte_range', result, after, object_token, start, length, value)
            buffer = fresh()
            assert n.vertrix_player_fill_bytes(buffer, SIZE, start, length, value)
            assert buffer.raw == after, (hex(address), case)
            count('fill_bytes_%x' % start)
        result, after = run(0x425de0)
        full(0x425de0, 'object_reset_slots', result, after, object_token)
        buffer = fresh()
        assert n.vertrix_object_clear_slots(buffer, SIZE)
        assert buffer.raw == after, case
        count('object_clear_slots')
        first, second = interesting(), interesting()
        result = original.call(0x418150, eax=first, edx=second) & 0xffffffff
        assert n.vertrix_compare_u32(first, second) & 0xffffffff == result, case
        count('compare_u32')
        key = '0x418150'
        full_totals[key] = full_totals.get(key, 0) + 1
    expected = [0x4ac500, 0x4ac370, 0x4ac600, 0x418830, 0x4ac920, 0x4ac940,
                0x4ac520, 0x43b970, 0x4320c0, 0x43bd40, 0x43a4f0, 0x47f8e0,
                0x4ac390, 0x4ac620, 0x4ac470, 0x4ac7b0, 0x4ac840, 0x42ef60,
                0x42ef80, 0x42f7d0, 0x42f7f0, 0x42f810, 0x42f830, 0x425de0, 0x418150]
    assert full_totals == {hex(address): args.cases * (2 if address == 0x4ac520 else 1)
                           for address in expected}, full_totals
    # Every public full API rejects missing/short storage before changing any byte.
    guards = {
        'actor_advance_elapsed': (0xc0, (OBJECT, 0xbc, 1)),
        'actor_sync_clock_period': (0xc4, (OBJECT,)),
        'actor_choose_handler': (0x158, (OBJECT, 0xec)),
        'player_write_bytes_168': (0x16b, (OBJECT, 1, 2, 3)),
        'player_test_4e8': (0x4ec, ()), 'player_test_a60': (0xa64, ()),
        'player_test_4c4': (0x4c5, ()), 'object_write_18': (0x1c, (OBJECT, 1)),
        'actor_test_counter_pair': (0xc4, (0xbc, 0xc0)),
        'actor_store_times_twelve': (0xc4, (0xc0, 0xffffffff)),
        'player_fill_byte_range': (0x9a1, (OBJECT, 0x99c, 5, 1)),
        'object_reset_slots': (0x1c, (OBJECT,)),
    }
    guard_count = 0
    for name, (end, parameters) in guards.items():
        function = getattr(n, 'vertrix_' + name)
        buffer = fresh()
        before = buffer.raw
        assert function(buffer, end - 1, *parameters) == 0
        assert buffer.raw == before, name
        assert function(None, SIZE, *parameters) == 0
        guard_count += 2
    function = n.vertrix_player_fill_byte_range
    for start, length in ((0xffffffff, 13), (0x99c, 0), (0x99c, 0xffffffff)):
        buffer = fresh()
        before = buffer.raw
        assert function(buffer, SIZE, OBJECT, start, length, 1) == 0
        assert buffer.raw == before
        guard_count += 1
    report = {'status': 'passed' , 'executions': totals, 'exact_eax_comparisons': full_totals,
              'native_invalid_storage_guard_cases': guard_count,
              'scope': 'Complete original routines run unchanged. New full APIs compare exact 32-bit '
                       'EAX and every byte of 0x1000 object storage; elapsed/copy/byte setters return '
                       'object tokens, times twelve stores/returns the product, fills return object+count, '
                       'slot clearing returns object+0x1c and predicates return 0/1. Mapped object '
                       'identities include 0xfffffffc with split wrapping guest storage, proving '
                       'end-token wrap. Legacy APIs compare state/out-parameters only. 43ba70 legacy '
                       'bonus flag remains a projected output here; its existing exact-return '
                       'bonus_ready API is separately verified in player_slots. Invalid native '
                       'storage/ranges return zero without writes.'}
    (args.build_dir / 'object-accessors-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
