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
                (0x4d2fc0, 'vertrix_rtl_scope_refresh_address', 0x4d2390),
                (0x4241d0, 'vertrix_return_constant_419f60', 0x419f60),
                (0x4241e0, 'vertrix_return_constant_419ea0', 0x419ea0),
                (0x4241f0, 'vertrix_return_constant_424160', 0x424160),
                (0x424200, 'vertrix_return_constant_419f80', 0x419f80),
                (0x4ca060, 'vertrix_return_constant_50081c', 0x50081c),
                (0x4cb390, 'vertrix_return_constant_4cc7a0', 0x4cc7a0),
                (0x4cb3a0, 'vertrix_return_constant_4ccaf0', 0x4ccaf0),
                (0x4cb3b0, 'vertrix_return_constant_4ccb40', 0x4ccb40),
                (0x4d25e0, 'vertrix_return_constant_ffff', 0xffff),
                (0x4d2ea0, 'vertrix_return_constant_4d09b0', 0x4d09b0),
                (0x4d2eb0, 'vertrix_return_constant_4d05e0', 0x4d05e0),
                (0x4d2ec0, 'vertrix_return_constant_4d0740', 0x4d0740),
                (0x4d2ed0, 'vertrix_return_constant_4d24a0', 0x4d24a0),
                (0x4d2ee0, 'vertrix_return_constant_4d0620', 0x4d0620),
                (0x4d2ef0, 'vertrix_return_constant_4d2460', 0x4d2460),
                (0x4d2f00, 'vertrix_return_constant_4d2420', 0x4d2420),
                (0x4d2f10, 'vertrix_return_constant_4d2440', 0x4d2440),
                (0x4d2f20, 'vertrix_return_constant_4d0650', 0x4d0650),
                (0x4d2f30, 'vertrix_return_constant_4d0670', 0x4d0670),
                (0x4d2f40, 'vertrix_return_constant_4d06a0', 0x4d06a0),
                (0x4d2f50, 'vertrix_return_constant_4d02a0', 0x4d02a0),
                (0x4d2f60, 'vertrix_return_constant_4d2170', 0x4d2170),
                (0x4d2f70, 'vertrix_return_constant_4d21d0', 0x4d21d0),
                (0x4d2f80, 'vertrix_return_constant_4d2260', 0x4d2260),
                (0x4d2f90, 'vertrix_return_constant_4d22b0', 0x4d22b0),
                (0x4d2fa0, 'vertrix_return_constant_4d2310', 0x4d2310),
                (0x4d2fb0, 'vertrix_return_constant_4d21a0', 0x4d21a0),
                (0x4d2fd0, 'vertrix_return_constant_4d23f0', 0x4d23f0),
                (0x4d6490, 'vertrix_return_constant_4d54c0', 0x4d54c0),
                (0x4d64a0, 'vertrix_return_constant_4d5660', 0x4d5660),
                (0x4d64b0, 'vertrix_return_constant_4d57a0', 0x4d57a0),
                (0x4d64c0, 'vertrix_return_constant_4d57c0', 0x4d57c0),
                (0x4d64d0, 'vertrix_return_constant_4d6080', 0x4d6080),
                (0x4d64e0, 'vertrix_return_constant_4d58e0', 0x4d58e0),
                (0x4d64f0, 'vertrix_return_constant_4d4e00', 0x4d4e00),
                (0x4d6500, 'vertrix_return_constant_4d4e30', 0x4d4e30),
                (0x4d6510, 'vertrix_return_constant_4d5360', 0x4d5360),
                (0x4d6520, 'vertrix_return_constant_4d4990', 0x4d4990),
                (0x4d6530, 'vertrix_return_constant_4d4d10', 0x4d4d10),
                (0x4d6540, 'vertrix_return_constant_4d4c00', 0x4d4c00),
                (0x4d6550, 'vertrix_return_constant_4d62e0', 0x4d62e0),
                (0x4d6560, 'vertrix_return_constant_4d6300', 0x4d6300),
                (0x4d6570, 'vertrix_return_constant_4d4ee0', 0x4d4ee0),
                (0x4d6580, 'vertrix_return_constant_4d4fd0', 0x4d4fd0),
                (0x4d6590, 'vertrix_return_constant_4d5010', 0x4d5010),
                (0x4d65a0, 'vertrix_return_constant_4d50d0', 0x4d50d0),
                (0x4d65b0, 'vertrix_return_constant_4d5150', 0x4d5150),
                (0x4d65c0, 'vertrix_return_constant_4d5180', 0x4d5180),
                (0x4d65d0, 'vertrix_return_constant_4d4270', 0x4d4270),
                (0x4d65e0, 'vertrix_return_constant_4d4630', 0x4d4630),
                (0x4d65f0, 'vertrix_return_constant_4d41c0', 0x4d41c0),
                (0x4d6600, 'vertrix_return_constant_4d41a0', 0x4d41a0),
                (0x4d6610, 'vertrix_return_constant_4d42a0', 0x4d42a0),
                (0x4d6620, 'vertrix_return_constant_4d4300', 0x4d4300),
                (0x4d6630, 'vertrix_return_constant_4d4e60', 0x4d4e60),
                (0x4d6640, 'vertrix_return_constant_4d5a30', 0x4d5a30),
                (0x4d6650, 'vertrix_return_constant_4d5a70', 0x4d5a70),
                (0x4d6660, 'vertrix_return_constant_4d5bf8', 0x4d5bf8),
                (0x4d6670, 'vertrix_return_constant_4d5c70', 0x4d5c70),
                (0x4d6680, 'vertrix_return_constant_4d5ab0', 0x4d5ab0),
                (0x4d6690, 'vertrix_return_constant_4d51c0', 0x4d51c0),
                (0x4d66a0, 'vertrix_return_constant_4d5280', 0x4d5280),
                (0x4d66b0, 'vertrix_return_constant_4d5330', 0x4d5330),
                (0x4d7430, 'vertrix_return_constant_4d73b0', 0x4d73b0),
                (0x4d7460, 'vertrix_return_constant_4d73c0', 0x4d73c0),
                (0x4d7470, 'vertrix_return_constant_4d7400', 0x4d7400),
                (0x4d7480, 'vertrix_return_constant_4d25e0', 0x4d25e0),
                (0x4d7490, 'vertrix_return_constant_4d7140', 0x4d7140),
                (0x4d74a0, 'vertrix_return_constant_4d7110', 0x4d7110),
                (0x4ee7f0, 'vertrix_return_constant_4ee730', 0x4ee730),
                (0x4ee800, 'vertrix_return_constant_4ee750', 0x4ee750),
                (0x4ee810, 'vertrix_return_constant_4ee6a0', 0x4ee6a0),
                )
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
                   ('rtl_glue.c', 'call_glue.c', 'actor_storage.c', 'constant_getters.c')]
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
