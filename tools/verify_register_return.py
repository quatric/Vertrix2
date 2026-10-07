"""Verify complete unchanged-return entrypoints before assigning shared names."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import subprocess
from original import Original
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import (
    UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX,
    UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP, UC_X86_REG_EFLAGS,
)

ADDRESSES = (0x404580, 0x425f40, 0x4523b0, 0x4713c0,
             0x471ee0, 0x477930, 0x47f8f0, 0x4b3360)
REGISTERS = (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX,
             UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    library = args.build_dir.resolve() / 'register-return.dylib'
    source = Path(__file__).resolve().parents[1] / 'source/register_return.c'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    str(source), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_return_unchanged.argtypes = [c.c_uint32]
    native.vertrix_return_unchanged.restype = c.c_uint32
    original = Original(args.executable)
    rng = random.Random(0x471ee0)
    writes = []
    original.cpu.hook_add(UC_HOOK_MEM_WRITE,
                          lambda uc, access, address, size, value, context:
                          writes.append((address, size, value)))
    totals = {}
    for address in ADDRESSES:
        completed = 0
        for case in range(1024):
            values = [rng.getrandbits(32) for _ in REGISTERS]
            values[0] = (0, 1, 0x7fffffff, 0x80000000, 0xffffffff)[case] if case < 5 else values[0]
            for register, value in zip(REGISTERS, values):
                original.cpu.reg_write(register, value)
            flags = 0x202 | (rng.getrandbits(12) & 0x8d5)
            original.cpu.reg_write(UC_X86_REG_EFLAGS, flags)
            writes.clear()
            result = original.call(address, eax=values[0], edx=values[1],
                                   ebx=values[2], ecx=values[3])
            assert result == native.vertrix_return_unchanged(values[0]) == values[0], (address, case)
            assert [original.cpu.reg_read(register) for register in REGISTERS] == values, (address, case)
            assert original.cpu.reg_read(UC_X86_REG_EFLAGS) == flags, (address, case)
            assert not writes, (address, case, writes)
            completed += 1
        assert completed == 1024
        totals[hex(address)] = completed
    report = {'status': 'passed', 'complete_original_executions': totals,
              'total_original_executions': sum(totals.values()),
              'scope': 'Complete callable entrypoints return incoming EAX with no memory writes, '
                       'unchanged general registers and arithmetic flags. No callees stubbed. '
                       'The shared name describes this behavior; game-specific roles remain unknown.'}
    (args.build_dir / 'register-return-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
