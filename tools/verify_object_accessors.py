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
    n = build(args.build_dir, 'object-accessors', ['object_accessors.c', 'actor_storage.c'])
    n.vertrix_actor_add_elapsed.argtypes = [c.c_void_p, c.c_size_t, U, U]
    n.vertrix_actor_counter_reached.argtypes = [c.c_void_p, c.c_size_t, U, U, c.POINTER(U)]
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
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4ac500)
    totals = {}

    def interesting():
        return rng.choice([0, 1, 2, 3, 0xffffffff, 0x80000000, rng.getrandbits(32),
                           rng.randrange(0, 20)])

    for case in range(args.cases):
        raw = bytearray(rng.randbytes(SIZE))
        for offset in (0xbc, 0xc0, 0x4e8, 0x18c, 0xa60, 0x4c4):
            struct.pack_into('<I', raw, offset, interesting())
        if rng.random() < 0.4:
            struct.pack_into('<I', raw, 0xbc, struct.unpack_from('<I', raw, 0xc0)[0])
        cpu.mem_write(ELAPSED, struct.pack('<I', interesting()))
        elapsed = struct.unpack('<I', bytes(cpu.mem_read(ELAPSED, 4)))[0]

        def run(address, **registers):
            cpu.mem_write(OBJECT, bytes(raw))
            result = original.call(address, eax=OBJECT, **registers) & 0xffffffff
            return result, bytes(cpu.mem_read(OBJECT, SIZE))

        def fresh():
            return c.create_string_buffer(bytes(raw), SIZE)

        def count(name):
            totals[name] = totals.get(name, 0) + 1

        for address, offset in ((0x4ac500, 0xbc), (0x4ac370, 0xcc), (0x4ac600, 0xdc)):
            _, after = run(address)
            buffer = fresh()
            assert n.vertrix_actor_add_elapsed(buffer, SIZE, offset, elapsed)
            assert buffer.raw == after, (hex(address), case)
            count('add_elapsed_%x' % offset)
        for address, name in ((0x418830, 'actor_clock_to_period'), (0x4ac920, 'actor_select_ec'),
                              (0x4ac940, 'actor_select_f0')):
            _, after = run(address)
            buffer = fresh()
            assert getattr(n, 'vertrix_' + name)(buffer, SIZE)
            assert buffer.raw == after, (name, case)
            count(name)
        for address, name in ((0x4ac520, 'actor_clock_reached'), (0x43b970, 'player_flag_4e8'),
                              (0x43ba70, 'player_bonus_meter_full'),
                              (0x4320c0, 'player_flag_a60'), (0x43bd40, 'player_byte_4c4_is_one')):
            result, after = run(address)
            out = U()
            assert getattr(n, 'vertrix_' + name)(fresh(), SIZE, c.byref(out))
            assert out.value == result & 0xff and after == bytes(raw), (name, case)
            count(name)
        first, second, third = interesting(), interesting(), interesting()
        _, after = run(0x43a4f0, edx=first, ebx=second, ecx=third)
        buffer = fresh()
        assert n.vertrix_player_set_bytes_168(buffer, SIZE, first, second, third)
        assert buffer.raw == after, case
        count('player_set_bytes_168')
        value = interesting()
        _, after = run(0x47f8e0, edx=value)
        buffer = fresh()
        assert n.vertrix_object_set_18(buffer, SIZE, value)
        assert buffer.raw == after, case
        count('object_set_18')
        for address, c_off, l_off in ((0x4ac390, 0xcc, 0xd0), (0x4ac620, 0xdc, 0xe0),
                                      (0x4ac520, 0xbc, 0xc0)):
            result, _ = run(address)
            out = U()
            assert n.vertrix_actor_counter_reached(fresh(), SIZE, c_off, l_off, c.byref(out))
            assert out.value == result & 0xff, (hex(address), case)
            count('counter_reached_%x' % c_off)
        for address, offset in ((0x4ac470, 0xd0), (0x4ac7b0, 0xc0), (0x4ac840, 0xe0)):
            value = interesting()
            _, after = run(address, edx=value)
            buffer = fresh()
            assert n.vertrix_actor_set_times_twelve(buffer, SIZE, offset, value)
            assert buffer.raw == after, (hex(address), case)
            count('set_times_twelve_%x' % offset)
        for address, start, length in ((0x42ef60, 0x99c, 5), (0x42ef80, 0x9a1, 5),
                                       (0x42f7d0, 0x9a6, 13), (0x42f7f0, 0x9b3, 13),
                                       (0x42f810, 0x9c0, 13), (0x42f830, 0x9cd, 13)):
            value = interesting()
            _, after = run(address, edx=value)
            buffer = fresh()
            assert n.vertrix_player_fill_bytes(buffer, SIZE, start, length, value)
            assert buffer.raw == after, (hex(address), case)
            count('fill_bytes_%x' % start)
        _, after = run(0x425de0)
        buffer = fresh()
        assert n.vertrix_object_clear_slots(buffer, SIZE)
        assert buffer.raw == after, case
        count('object_clear_slots')
        first, second = interesting(), interesting()
        result = original.call(0x418150, eax=first, edx=second) & 0xffffffff
        assert n.vertrix_compare_u32(first, second) & 0xffffffff == result, case
        count('compare_u32')
    report = {'status': 'passed', 'executions': totals,
              'scope': 'Cleaned small actor and player accessors against the complete original '
                       'routines: every returned value and the whole object compare.'}
    (args.build_dir / 'object-accessors-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
