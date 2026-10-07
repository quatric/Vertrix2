"""Compare the original counter wraps 0x4ac5b0 and 0x4ac6b0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from unicorn.x86_const import UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX
from oracle_kit import build

ACTOR, SIZE = 0x80a000, 0x200


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=8192)
    args = parser.parse_args()
    if args.cases < 2:
        parser.error('--cases must be at least 2 to cover both entrypoints')
    n = build(args.build_dir, 'actor-wrap', ['actor_fields.c', 'actor_storage.c'])
    for name in ('counter', 'progress'):
        getattr(n, 'vertrix_actor_%s_wrap' % name).argtypes = [c.c_void_p, c.c_size_t]
        function = getattr(n, 'vertrix_actor_%s_consume' % name)
        function.argtypes = [c.c_void_p, c.c_size_t]
        function.restype = c.c_uint32
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4ac5b0)
    totals, return_totals, fixtures = {}, {}, {}
    boundaries = {}
    for case in range(args.cases):
        address, name, first = ((0x4ac5b0, 'counter', 0xbc), (0x4ac6b0, 'progress', 0xdc))[case % 2]
        raw = bytearray(rng.randbytes(SIZE))
        fixture = ('zero_divisor', 'zero_counter', 'below_divisor', 'exact_multiple',
                   'remainder', 'random')[(case // 2) % 6]
        edges = [0, 1, 2, 3, 0x7fffffff, 0x80000000, 0xffffffff]
        counter, divisor = rng.choice(edges + [rng.getrandbits(32)]), rng.choice(edges + [rng.getrandbits(32)])
        if fixture == 'zero_divisor':
            divisor = 0
        elif fixture == 'zero_counter':
            counter = 0
        elif fixture == 'below_divisor':
            divisor = rng.randrange(1, 1 << 32)
            counter = rng.randrange(divisor)
        elif fixture == 'exact_multiple':
            divisor = rng.randrange(1, 1 << 32)
            counter = rng.randrange(0xffffffff // divisor + 1) * divisor
        elif fixture == 'remainder':
            divisor = rng.randrange(2, 1 << 32)
            remainder = rng.randrange(1, divisor)
            counter = rng.randrange((0xffffffff - remainder) // divisor + 1) * divisor + remainder
        struct.pack_into('<II', raw, first, counter, divisor)
        cpu.mem_write(ACTOR, bytes(raw))
        edx, ebx, ecx = [rng.getrandbits(32) for _ in range(3)]
        result = original.call(address, eax=ACTOR, edx=edx, ebx=ebx, ecx=ecx)
        assert [cpu.reg_read(register) for register in (UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX)] == [edx, ebx, ecx]
        want = bytes(cpu.mem_read(ACTOR, SIZE))
        native = c.create_string_buffer(bytes(raw), SIZE)
        assert getattr(n, 'vertrix_actor_%s_wrap' % name)(native, SIZE), case
        assert native.raw == want, (case, name, 'legacy_state')
        native = c.create_string_buffer(bytes(raw), SIZE)
        got = getattr(n, 'vertrix_actor_%s_consume' % name)(native, SIZE)
        assert got == result, (case, name, got, result)
        assert native.raw == want, (case, name, 'full_state')
        key = hex(address)
        return_totals[key] = return_totals.get(key, 0) + 1
        key = name + '_' + fixture
        fixtures[key] = fixtures.get(key, 0) + 1
        boundaries[name] = (native, first)
        totals[name] = totals.get(name, 0) + 1
    assert sum(return_totals.values()) == args.cases
    assert return_totals == {'0x4ac5b0': (args.cases + 1) // 2, '0x4ac6b0': args.cases // 2}
    guard_count = 0
    for name, (buffer, first) in boundaries.items():
        function = getattr(n, 'vertrix_actor_%s_consume' % name)
        before = buffer.raw
        for short_size in (first + 3, first + 7):
            assert function(buffer, short_size) == 0
            assert buffer.raw == before
            guard_count += 1
        assert function(None, SIZE) == 0
        guard_count += 1
    report = {'status': 'passed' , 'complete_original_executions': totals,
              'exact_eax_comparisons': return_totals, 'branch_fixtures': fixtures,
              'native_invalid_storage_guard_cases': guard_count,
              'scope': 'Complete unchanged 4ac5b0 and 4ac6b0 execute over unsigned edge/random counters '
                       'and divisors. New consume APIs compare original EAX (consumed whole-period '
                       'product) and entire 0x200 actor storage. Original EDX/EBX/ECX preservation '
                       'also checks. Zero divisors, zero/below/exact/remainder counters and high-bit '
                       'values are covered. Legacy wrap APIs compare state only; native invalid '
                       'storage guards preserve memory and return zero.'}
    (args.build_dir / 'actor-wrap-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
