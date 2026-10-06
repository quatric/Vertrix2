"""Compare the original setjmp 0x4d9f06 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from unicorn.x86_const import (UC_X86_REG_EBP, UC_X86_REG_EDI, UC_X86_REG_ESI, UC_X86_REG_ESP,
                               UC_X86_REG_CS, UC_X86_REG_DS, UC_X86_REG_ES, UC_X86_REG_FS,
                               UC_X86_REG_GS, UC_X86_REG_SS)

from original import Original, STACK, RETURN
from oracle_kit import build

U = c.c_uint32
BUFFER = 0x80a000


class State(c.Structure):
    _fields_ = [(name, U) for name in ('ebx', 'ecx', 'edx', 'esi', 'edi', 'ebp', 'return_address',
                                       'esp', 'es', 'ds', 'cs', 'fs', 'gs', 'ss', 'chain')]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=256)
    args = parser.parse_args()
    n = build(args.build_dir, 'jump-capture', ['rtl_glue.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_rtl_jump_capture.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(State)]
    n.vertrix_rtl_jump_capture.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4d9f06)
    for case in range(args.cases):
        esi, edi, ebp, ebx, ecx, edx = (rng.getrandbits(32) for _ in range(6))
        chain = rng.getrandbits(32)
        cpu.mem_write(0, struct.pack('<I', chain))
        cpu.mem_write(BUFFER, bytes(0x40))
        cpu.reg_write(UC_X86_REG_ESI, esi)
        cpu.reg_write(UC_X86_REG_EDI, edi)
        cpu.reg_write(UC_X86_REG_EBP, ebp)
        result = original.call(0x4d9f06, eax=BUFFER, ebx=ebx, ecx=ecx, edx=edx)
        assert result == 0
        state = State(ebx, ecx, edx, esi, edi, ebp, RETURN, STACK + 4,
                      *(cpu.reg_read(r) for r in (UC_X86_REG_ES, UC_X86_REG_DS, UC_X86_REG_CS,
                                                  UC_X86_REG_FS, UC_X86_REG_GS, UC_X86_REG_SS)),
                      chain)
        buffer = c.create_string_buffer(0x40)
        assert n.vertrix_rtl_jump_capture(buffer, 0x40, c.byref(state))
        assert buffer.raw == bytes(cpu.mem_read(BUFFER, 0x40)), (case, buffer.raw, bytes(cpu.mem_read(BUFFER, 0x40)))
    report = {'status': 'passed', 'complete_original_executions': {'0x4d9f06': args.cases},
              'scope': 'The routine executes completely in the original over random registers '
                       'and exception chains; the stored record compares byte for byte.'}
    (args.build_dir / 'jump-capture-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
