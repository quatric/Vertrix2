"""Compare the original square root 0x4c9b10 with the native recovery."""
import argparse
import ctypes as c
import json
import math
import random
import struct
from pathlib import Path

from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX

from original import Original, STACK
from oracle_kit import Stubs, build

U = c.c_uint32
FLAG = 0x5054a1


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(14)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'sqrt', ['rtl_glue.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_rtl_square_root.argtypes = [c.POINTER(Calls), U, U, U, U]
    n.vertrix_rtl_square_root.restype = c.c_uint64
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4c9b10)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address in (0x4dad2e, 0x4db10a):
        stubs.add(address, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {'hardware': 0, 'software': 0, 'error': 0}
    exact = 0
    for case in range(args.cases):
        kind = rng.choice(['hardware', 'software', 'error'])
        if kind == 'error':
            value = -rng.uniform(0, 100)
        else:
            value = rng.choice([0.0, 1.0, 2.0, 4.0, 1e-310, rng.uniform(0, 1000), math.exp(
                rng.uniform(-20, 20))])
        bits = struct.unpack('<Q', struct.pack('<d', value))[0]
        flag = 1 if kind == 'hardware' else 0
        cpu.mem_write(FLAG, bytes([flag]))
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        original.call(0x4c9b10, eax=bits & 0xffffffff, edx=bits >> 32)
        expected = cpu.reg_read(UC_X86_REG_EDX) << 32 | cpu.reg_read(UC_X86_REG_EAX)
        replay[:] = list(returns)
        got = n.vertrix_rtl_square_root(c.byref(calls), STACK - 4, flag, bits & 0xffffffff,
                                        bits >> 32)
        assert got == expected, (kind, value, hex(got), hex(expected))
        assert native_log == stubs.log and not replay, (native_log, stubs.log)
        totals[kind] += 1
    # the hardware path is cheap to run: hunt for the double rounding cases of fsqrt
    cpu.mem_write(FLAG, bytes([1]))
    hunted = rounded = 0
    for case in range(args.cases * 5):
        value = math.exp(rng.uniform(-20, 20)) if case % 3 == 1 else rng.uniform(0, 1000)
        bits = struct.unpack('<Q', struct.pack('<d', value))[0]
        original.call(0x4c9b10, eax=bits & 0xffffffff, edx=bits >> 32)
        expected = cpu.reg_read(UC_X86_REG_EDX) << 32 | cpu.reg_read(UC_X86_REG_EAX)
        got = n.vertrix_rtl_square_root(c.byref(calls), STACK - 4, 1, bits & 0xffffffff, bits >> 32)
        assert got == expected, (value, hex(got), hex(expected))
        hunted += 1
        rounded += struct.unpack('<d', struct.pack('<Q', expected))[0] != math.sqrt(value)
    totals['hardware_hunted'] = hunted
    totals['double_rounding_cases'] = rounded
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'The routine executes completely in the original (fsqrt on the hardware '
                       'path) with 0x4dad2e and 0x4db10a stubbed and logged; the result pair '
                       'edx:eax and every callee call compare bit for bit, including the cases '
                       'where fsqrt double rounding differs from the correctly rounded root.'}
    (args.build_dir / 'sqrt-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
