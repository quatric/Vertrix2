"""Compare the original far string routines 0x4df884, 0x4df8a8 and 0x4df914 with the native
recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from unicorn.x86_const import UC_X86_REG_DS, UC_X86_REG_GDTR, UC_X86_REG_SS

from original import Original, STACK
from oracle_kit import Stubs, build

U = c.c_uint32


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


CALLEES = {0x4e636c: 0, 0x4e62e0: 0}
TEXT = 0x800b00
GDT = 0x700400


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'pad-zeros', ['rtl_glue.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_rtl_pad_zeros.argtypes = [c.POINTER(Calls), U, U, U, U, c.c_void_p]
    n.vertrix_rtl_pad_zeros.restype = U
    n.vertrix_rtl_length_limit.argtypes = [c.c_char_p, U]
    n.vertrix_rtl_length_limit.restype = U
    n.vertrix_rtl_wide_byte_count.argtypes = [c.POINTER(Calls), U, U, c.c_void_p, c.c_int32]
    n.vertrix_rtl_wide_byte_count.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    # the routine loads es from ds: give both a flat data descriptor
    cpu.mem_write(GDT, bytes(8) + bytes(8) + bytes.fromhex('ffff00000092cf00'))
    cpu.reg_write(UC_X86_REG_GDTR, (0, GDT, 0x18, 0))
    for register in (UC_X86_REG_DS, UC_X86_REG_SS):
        cpu.reg_write(register, 0x10)
    rng = random.Random(0x4df914)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        returns.append(rng.choice([0xffffffff, 1, 2, 3]) if address == 0x4e62e0
                       else rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    count = 0
    counts = {}
    for case in range(args.cases):
        width = rng.randrange(0, 0x30)
        length = rng.randrange(0, width + 1)
        digits = bytes(rng.choice(b'0123456789') for _ in range(length)) + b'\0'
        junk = rng.randbytes(0x40)
        image = bytearray(junk)
        image[:len(digits)] = digits
        cpu.mem_write(TEXT, bytes(image))
        buffer = c.create_string_buffer(bytes(image), 0x40)
        eax, ecx = rng.getrandbits(32), rng.getrandbits(32)
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x4df914, eax=eax, edx=TEXT, ebx=width, ecx=ecx) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_rtl_pad_zeros(c.byref(calls), eax, TEXT, ecx, width, buffer)
        assert got == result, (width, length, hex(got), hex(result))
        assert native_log == stubs.log, (native_log, stubs.log)
        assert buffer.raw == bytes(cpu.mem_read(TEXT, 0x40)), (width, length)
        assert not replay
        count += 1
        text = bytes(rng.randrange(1, 256) for _ in range(rng.randrange(0, 0x20))) + b'\0'
        cpu.mem_write(TEXT, text)
        limit = rng.randrange(0, 0x28)
        stubs.log.clear()
        result = original.call(0x4df884, eax=TEXT, edx=0x10, ebx=limit) & 0xffffffff
        assert n.vertrix_rtl_length_limit(text, limit) == result, (text, limit)
        counts['0x4df884'] = counts.get('0x4df884', 0) + 1
        wide = [rng.randrange(1, 0x10000) for _ in range(rng.randrange(0, 0x10))] + [0]
        cpu.mem_write(TEXT, struct.pack('<%dH' % len(wide), *wide))
        limit = rng.choice([-1, -1, rng.randrange(0, 0x20)])
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x4df8a8, eax=TEXT, edx=0x10, ebx=limit & 0xffffffff) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_rtl_wide_byte_count(c.byref(calls), STACK - 16, TEXT,
                                        (c.c_uint16 * len(wide))(*wide), limit)
        assert got == result, (wide, limit, hex(got), hex(result))
        assert native_log == stubs.log and not replay, (native_log, stubs.log)
        counts['0x4df8a8'] = counts.get('0x4df8a8', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': dict(counts, **{'0x4df914': count}),
              'scope': 'Each routine executes completely in the original with its callees stubbed '
                       'and logged; every callee call, the returned eax and the padded text '
                       'compare. es and ds hold a flat data descriptor.'}
    (args.build_dir / 'far-strings-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
