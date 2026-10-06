"""Compare complete original actor timer, frame counter and setter routines with the native
recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import build

ACTOR, SIZE = 0x801000, 0x200
U = c.c_uint32


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'actor-counters', ['actor_fields.c', 'actor_storage.c'])
    P, SZ, UP = c.c_void_p, c.c_size_t, c.POINTER(U)
    f = lambda name: getattr(n, 'vertrix_actor_' + name)
    for name in ('reset_frame_counter', 'next_frame_counter', 'previous_frame_counter',
                 'handler_from_ec', 'handler_from_f0'):
        f(name).argtypes = [P, SZ]
    for name in ('cc_reached', 'counter_reached', 'counter_quotient', 'progress_quotient',
                 'frame_counter_is_zero', 'get_b4'):
        f(name).argtypes = [P, SZ, UP]
    for name in ('add_cc', 'set_e0_steps', 'set_e0', 'set_ec', 'set_f0', 'set_b4', 'set_11c'):
        f(name).argtypes = [P, SZ, U]
    f('set_114').argtypes = [P, SZ, U, U]
    f('set_words_2a').argtypes = [P, SZ] + [c.c_uint16] * 3
    f('set_words_3a').argtypes = [P, SZ] + [c.c_uint16] * 3
    f('set_box').argtypes = [P, SZ] + [c.c_uint16] * 4
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4ac370)
    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    def raw():
        data = bytearray(rng.randbytes(SIZE))
        for offset in (0xbc, 0xc0, 0xcc, 0xd0, 0xdc, 0xe0):
            struct.pack_into('<I', data, offset, rng.choice([0, 1, rng.getrandbits(32),
                                                            rng.randrange(0, 100)]))
        struct.pack_into('<I', data, 0xb8, rng.choice([0, 1, 0xffffffff, rng.getrandbits(32)]))
        return bytes(data)

    def mutate(address, name, native, **registers):
        data = raw()
        cpu.mem_write(ACTOR, data)
        original.call(address, eax=ACTOR, **registers)
        actor = c.create_string_buffer(data, SIZE)
        assert native(actor), (name, 'rejected')
        assert actor.raw == bytes(cpu.mem_read(ACTOR, SIZE)), (name, 'storage differs')
        count(name)

    def query(address, name, native, mask=0xffffffff):
        data = raw()
        cpu.mem_write(ACTOR, data)
        expect = original.call(address, eax=ACTOR) & mask
        actor = c.create_string_buffer(data, SIZE)
        out = U()
        assert native(actor, c.byref(out)), name
        assert out.value == expect, (name, out.value, expect)
        count(name)

    for case in range(args.cases):
        v, w = rng.getrandbits(32), rng.getrandbits(32)
        words = [rng.getrandbits(16) for _ in range(4)]
        cpu.mem_write(0x5bd834, struct.pack('<I', v))
        mutate(0x4ac370, 'add_cc', lambda a: f('add_cc')(a, SIZE, v))
        query(0x4ac390, 'cc_reached', lambda a, o: f('cc_reached')(a, SIZE, o), 0xff)
        query(0x4ac520, 'counter_reached', lambda a, o: f('counter_reached')(a, SIZE, o), 0xff)
        query(0x4ac540, 'counter_quotient', lambda a, o: f('counter_quotient')(a, SIZE, o))
        query(0x4ac640, 'progress_quotient', lambda a, o: f('progress_quotient')(a, SIZE, o))
        mutate(0x4ac700, 'reset_frame_counter', lambda a: f('reset_frame_counter')(a, SIZE))
        mutate(0x4ac740, 'next_frame_counter', lambda a: f('next_frame_counter')(a, SIZE))
        mutate(0x4ac750, 'previous_frame_counter', lambda a: f('previous_frame_counter')(a, SIZE))
        query(0x4ac7a0, 'frame_counter_is_zero',
              lambda a, o: f('frame_counter_is_zero')(a, SIZE, o), 0xff)
        mutate(0x4ac840, 'set_e0_steps', lambda a: f('set_e0_steps')(a, SIZE, v), edx=v)
        mutate(0x4ac860, 'set_e0', lambda a: f('set_e0')(a, SIZE, v), edx=v)
        mutate(0x4ac910, 'set_ec', lambda a: f('set_ec')(a, SIZE, v), edx=v)
        mutate(0x4ac920, 'handler_from_ec', lambda a: f('handler_from_ec')(a, SIZE))
        mutate(0x4ac930, 'set_f0', lambda a: f('set_f0')(a, SIZE, v), edx=v)
        mutate(0x4ac940, 'handler_from_f0', lambda a: f('handler_from_f0')(a, SIZE))
        mutate(0x4ac950, 'set_b4', lambda a: f('set_b4')(a, SIZE, v), edx=v)
        query(0x4ac960, 'get_b4', lambda a, o: f('get_b4')(a, SIZE, o))
        mutate(0x4ac4e0, 'set_114', lambda a: f('set_114')(a, SIZE, w, v), ebx=w, edx=v)
        mutate(0x4ac4f0, 'set_11c', lambda a: f('set_11c')(a, SIZE, v), edx=v)
        mutate(0x4ad510, 'set_words_2a', lambda a: f('set_words_2a')(a, SIZE, *words[:3]),
               edx=words[0], ebx=words[1], ecx=words[2])
        mutate(0x4ad520, 'set_words_3a', lambda a: f('set_words_3a')(a, SIZE, *words[:3]),
               edx=words[0], ebx=words[1], ecx=words[2])
        mutate(0x4b54d0, 'set_box', lambda a: f('set_box')(a, SIZE, *words), edx=words[0],
               ebx=words[1], ecx=words[2], args=(words[3],))
    actor = c.create_string_buffer(SIZE)
    assert not f('set_box')(actor, 0xf7, 1, 2, 3, 4)
    assert not f('set_words_3a')(actor, 0x3f, 1, 2, 3)
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 4ac370, 4ac390, 4ac4e0, 4ac4f0, 4ac520, 4ac540, 4ac640, 4ac700, '
                       '4ac740, 4ac750, 4ac7a0, 4ac840, 4ac860, 4ac910, 4ac920, 4ac930, 4ac940, '
                       '4ac950, 4ac960, 4ad510, 4ad520 and 4b54d0 execute in the original; whole '
                       'actor storage and returned values compare.'}
    (args.build_dir / 'actor-counters-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
