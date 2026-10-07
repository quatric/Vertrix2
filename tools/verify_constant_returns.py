"""Verify complete constant-return entrypoints without inferring game-specific roles."""
import ctypes as c
import json
from pathlib import Path
import random
import subprocess
import tempfile

from original import Original
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import (
    UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX,
    UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP, UC_X86_REG_EFLAGS,
)


def main():
    root = Path(__file__).resolve().parents[1]
    registers = (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX,
                 UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP)
    routines = ((0x4ba210, 'vertrix_return_zero', 0),
                (0x4e9d00, 'vertrix_return_zero', 0),
                (0x4d2fc0, 'vertrix_rtl_scope_refresh_address', 0x4d2390))
    original = Original(root / 'Vertrix2.exe')
    rng = random.Random(0x4d2fc0)
    writes = []
    original.cpu.hook_add(UC_HOOK_MEM_WRITE,
                          lambda cpu, access, address, width, value, context:
                          writes.append((address, width, value)))
    totals = {}
    with tempfile.TemporaryDirectory(prefix='vertrix-constant-returns-') as directory:
        library = Path(directory) / 'constants.so'
        sources = [root / 'source' / name for name in
                   ('rtl_glue.c', 'call_glue.c', 'actor_storage.c')]
        subprocess.run(['cc', '-std=c11', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra',
                        '-Werror', *map(str, sources), '-o', str(library)], check=True)
        native = c.CDLL(str(library))
        for address, name, expected in routines:
            function = getattr(native, name)
            function.argtypes = []
            function.restype = c.c_uint32
            for case in range(1024):
                values = [rng.getrandbits(32) for _ in registers]
                for register, value in zip(registers, values):
                    original.cpu.reg_write(register, value)
                flags = 0x202 | (rng.getrandbits(12) & 0x8d5)
                original.cpu.reg_write(UC_X86_REG_EFLAGS, flags)
                writes.clear()
                result = original.call(address, eax=values[0], edx=values[1],
                                       ebx=values[2], ecx=values[3])
                assert result == function() == expected, (hex(address), case)
                values[0] = expected
                assert [original.cpu.reg_read(r) for r in registers] == values
                actual_flags = original.cpu.reg_read(UC_X86_REG_EFLAGS)
                if expected:
                    assert actual_flags == flags
                else:
                    # XOR EAX,EAX defines these arithmetic flags; AF is undefined.
                    assert actual_flags & 0x8c5 == 0x44
                    assert actual_flags & ~0x8d5 == flags & ~0x8d5
                assert not writes, (hex(address), case, writes)
            totals[hex(address)] = 1024
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Native return values match complete original entrypoints. Original non-EAX registers and defined flags are checked; no original memory writes. The address getter does not invoke its target.'}
    (root / 'docs/constant-return-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report))


if __name__ == '__main__':
    main()
