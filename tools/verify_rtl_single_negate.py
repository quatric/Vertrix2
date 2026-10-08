"""Execute the original sign-bit helper and compare native EAX over arbitrary bit patterns."""
import argparse
import ctypes
import json
import random
from pathlib import Path

from oracle_kit import build
from original import Original
from unicorn.x86_const import UC_X86_REG_EDX


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    parser.add_argument("--cases", type=int, default=8192)
    args = parser.parse_args()
    native = build(args.build_dir, "rtl-single-negate", ["rtl_bits.c"])
    negate = native.vertrix_rtl_single_negate
    negate.argtypes = [ctypes.c_uint32]
    negate.restype = ctypes.c_uint32
    original = Original(args.executable)
    rng = random.Random(0x4eb5b4)
    edges = [0, 0x80000000, 1, 0x80000001, 0x7f800000, 0xff800000,
             0x7fc00000, 0xffc00000, 0x7f800001, 0xff800001, 0x7fffffff, 0xffffffff]
    count = 0
    for bits in edges + [rng.getrandbits(32) for _ in range(args.cases)]:
        edx = rng.getrandbits(32)
        expected = original.call(0x4eb5b4, eax=bits, edx=edx,
                                 ebx=rng.getrandbits(32), ecx=rng.getrandbits(32))
        actual = negate(bits)
        assert actual == expected, (hex(bits), hex(actual), hex(expected))
        assert original.cpu.reg_read(UC_X86_REG_EDX) == edx
        count += 1
    report = {"status": "passed", "address": "0x4eb5b4", "cases": count,
              "scope": "Complete original control flow versus native EAX for arbitrary single bit patterns, with zero, subnormal, infinity and NaN edges. Original EDX preservation checked independently. Native API exposes EAX only; caller flags and other lifted routines are not verified."}
    output = args.build_dir / "rtl-single-negate-verification.json"
    output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report))


if __name__ == "__main__":
    main()
