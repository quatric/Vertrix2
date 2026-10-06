"""Compare the original double remainder 0x4db250 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import build

U = c.c_uint32
QUOTIENT, RESULT = 0x80f000, 0x80f010


def double_bits(rng):
    kind = rng.random()
    exponent = rng.choice([0x3ff, 0x400, 0x3fe, 0x405, 0x3f0, 0x410, rng.randrange(0x3c0, 0x440)])
    sign = rng.getrandbits(1)
    mantissa = rng.getrandbits(52) if kind < 0.8 else rng.choice([0, 1, (1 << 52) - 1])
    return sign << 63 | exponent << 52 | mantissa


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=20000)
    args = parser.parse_args()
    n = build(args.build_dir, 'float-remainder', ['rtl_glue.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_float_remainder.argtypes = [U, U, U, U] + [c.POINTER(U)] * 3
    n.vertrix_float_remainder.restype = None
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4db250)
    zero = 0
    for case in range(args.cases):
        a, b = double_bits(rng), double_bits(rng)
        if rng.random() < 0.05:
            b = rng.choice([0, 1 << 63, a, a ^ 1 << 63])
        al, ah, bl, bh = a & 0xffffffff, a >> 32, b & 0xffffffff, b >> 32
        cpu.mem_write(QUOTIENT, bytes(4))
        cpu.mem_write(RESULT, bytes(8))
        original.call(0x4db250, args=(al, ah, bl, bh, QUOTIENT, RESULT))
        q, lo, hi = U(), U(), U()
        n.vertrix_float_remainder(al, ah, bl, bh, c.byref(q), c.byref(lo), c.byref(hi))
        want = (struct.unpack('<I', bytes(cpu.mem_read(QUOTIENT, 4)))[0],
                *struct.unpack('<II', bytes(cpu.mem_read(RESULT, 8))))
        assert (q.value, lo.value, hi.value) == want, (case, hex(a), hex(b), (q.value, lo.value, hi.value), want)
        zero += bh == 0
    report = {'status': 'passed', 'complete_original_executions': {'0x4db250': args.cases},
              'scope': 'The routine executes completely in the original over random doubles of '
                       'nearby exponents and special mantissas; the quotient bits and both result '
                       'dwords compare.'}
    (args.build_dir / 'float-remainder-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
