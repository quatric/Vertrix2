"""Compare the original natural logarithm 0x4db896 (fldln2, fyl2x) with the native recovery."""
import argparse
import ctypes as c
import json
import math
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import build


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'ln', ['rtl_glue.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_rtl_natural_log.argtypes = [c.c_uint64]
    n.vertrix_rtl_natural_log.restype = c.c_uint64
    original = Original(args.executable)
    rng = random.Random(0x4db896)
    exact = worst = 0
    values = [1.0, 2.0, math.e, 0.5, 1e-300, 1e300, float('inf')]
    for case in range(args.cases):
        value = rng.choice(values + [math.exp(rng.uniform(-30, 30)), rng.uniform(0, 100)])
        bits = struct.unpack('<Q', struct.pack('<d', value))[0]
        original.call(0x4db896, eax=bits & 0xffffffff, edx=bits >> 32)
        cpu = original.cpu
        from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX
        expected = cpu.reg_read(UC_X86_REG_EDX) << 32 | cpu.reg_read(UC_X86_REG_EAX)
        got = n.vertrix_rtl_natural_log(bits)
        if got == expected:
            exact += 1
            continue
        a, b = struct.unpack('<d', struct.pack('<Q', got))[0], struct.unpack(
            '<d', struct.pack('<Q', expected))[0]
        assert abs(a - b) <= 2 * math.ulp(b), (value, a, b)
        worst = max(worst, abs(a - b) / math.ulp(b))
    report = {'status': 'passed', 'complete_original_executions': {'0x4db896': args.cases},
              'bit_exact': exact, 'worst_error_ulp': worst,
              'scope': 'The routine executes completely in the original (x87 fyl2x). The native '
                       'result is compared bit for bit; where it differs it must be within two '
                       'units in the last place. Zero is not tested: the emulator returns 0.0 for '
                       'fyl2x of zero where the hardware gives minus infinity, which the C '
                       'library matches.'}
    (args.build_dir / 'ln-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
