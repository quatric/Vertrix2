#!/usr/bin/env python3
"""Check recomp.py's x87 translation against a real x86 (Unicorn), one instruction form at a time.

Every distinct x87 instruction form in Vertrix3.exe (mnemonic and operand shape) runs twice from
the same state -- four values on the FPU stack, known bytes at its memory operand: once under
Unicorn, once as the C recomp.py writes for it, compiled against the runtime's cpu.c. The FPU
stack, condition codes, eax, the integer flags fcomi sets and the memory around the operand
must agree.

usage: x87_check.py Vertrix3.exe WORK_DIR [CC]
"""
import struct
import subprocess
import sys
from pathlib import Path

from capstone import x86 as X
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_PROT_ALL
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EBP, UC_X86_REG_EBX, UC_X86_REG_ECX,
                               UC_X86_REG_EDI, UC_X86_REG_EDX, UC_X86_REG_EFLAGS, UC_X86_REG_ESI,
                               UC_X86_REG_ESP)

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import recomp  # noqa: E402

STACK = [1.5, -2.75, 3.125, 10.0]  # ST(0)..ST(3)
REG = 0x180000      # every general register points here...
ESP = 0x180800      # ...but esp
CONSTS = 0x170000   # the stack's initial values
SAVE = 0x171000     # fnsave area
CODE = 0x10000
SKIP = {'fnstenv', 'fnsave', 'fldenv', 'frstor', 'fstenv', 'fsave', 'fxsave', 'fxrstor', 'femms',
        'fwait', 'wait', 'ffree', 'fnop', 'fdecstp', 'fincstp'}
REGS = {X.X86_REG_EAX: 'eax', X.X86_REG_ECX: 'ecx', X.X86_REG_EDX: 'edx', X.X86_REG_EBX: 'ebx',
        X.X86_REG_ESP: 'esp', X.X86_REG_EBP: 'ebp', X.X86_REG_ESI: 'esi', X.X86_REG_EDI: 'edi'}


def f80(v):
    """A double as x87 extended-precision bytes."""
    if v == 0:
        return bytes(10)
    sign = 0x8000 if v < 0 else 0
    import math
    m, e = math.frexp(abs(v))  # v = m * 2**e, 0.5 <= m < 1
    mant = int(m * (1 << 64))
    return struct.pack('<QH', mant, sign | (e - 1 + 16383))


def from_f80(b):
    mant, se = struct.unpack('<QH', b)
    e = se & 0x7fff
    if e == 0x7fff:
        return float('nan') if mant & 0x7fffffffffffffff else (-1) ** (se >> 15) * float('inf')
    if e == 0 and mant == 0:
        return -0.0 if se & 0x8000 else 0.0
    return (-1) ** (se >> 15) * mant * 2.0 ** (e - 16383 - 63)


def form(ins):
    shape = []
    for op in ins.operands:
        if op.type == X.X86_OP_REG:
            shape.append('st%d' % (op.reg - X.X86_REG_ST0) if X.X86_REG_ST0 <= op.reg <= X.X86_REG_ST7 else 'r')
        elif op.type == X.X86_OP_MEM:
            shape.append('m%d' % op.size)
        else:
            shape.append('i')
    return (ins.mnemonic, tuple(shape), ins.bytes[0])


def effective(op):
    mem = op.mem
    a = mem.disp
    if mem.base:
        a += ESP if mem.base == X.X86_REG_ESP else REG
    if mem.index:
        a += (ESP if mem.index == X.X86_REG_ESP else REG) * mem.scale
    return a & 0xffffffff


def operand_bytes(ins):
    """What the memory operand holds before the instruction."""
    mem = [op for op in ins.operands if op.type == X.X86_OP_MEM]
    if not mem:
        return None, b''
    op = mem[0]
    m = ins.mnemonic
    if m in ('fldcw',):
        return op, struct.pack('<H', 0x0e7f)  # round toward zero, 64-bit precision
    if m.startswith('fi') or m in ('fild',):
        return op, {2: struct.pack('<h', -7), 4: struct.pack('<i', 12345), 8: struct.pack('<q', -9876543210)}[op.size]
    if op.size == 4:
        return op, struct.pack('<f', 0.625)
    if op.size == 8:
        return op, struct.pack('<d', -0.3)
    if op.size == 10:
        return op, f80(2.5)
    return op, bytes(op.size)


def run_unicorn(ins, mem_op, mem_value):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0, 0x200000, UC_PROT_ALL)
    pages = set()
    if mem_op is not None:
        ea = effective(mem_op)
        if not 0 <= ea < 0x200000 - 64:
            base = ea & ~0xfff
            uc.mem_map(base - 0x1000, 0x3000, UC_PROT_ALL)
            pages.add(base)
        uc.mem_write(ea, mem_value)
    for k, v in enumerate(STACK):
        uc.mem_write(CONSTS + 8 * k, struct.pack('<d', v))
    code = b'\xdb\xe3'  # fninit
    for k in reversed(range(len(STACK))):
        code += b'\xdd\x05' + struct.pack('<I', CONSTS + 8 * k)  # fld qword [k]
    code += bytes(ins.bytes)
    code += b'\xdd\x35' + struct.pack('<I', SAVE)  # fnsave
    uc.mem_write(CODE, code)
    for r in (UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_EBP,
              UC_X86_REG_ESI, UC_X86_REG_EDI):
        uc.reg_write(r, REG)
    uc.reg_write(UC_X86_REG_ESP, ESP)
    uc.emu_start(CODE, CODE + len(code))
    save = bytes(uc.mem_read(SAVE, 108))
    sw = struct.unpack_from('<H', save, 4)[0]
    tw = struct.unpack_from('<H', save, 8)[0]
    top = (sw >> 11) & 7
    st = []
    for i in range(8):
        physical = (top + i) & 7
        valid = ((tw >> (2 * physical)) & 3) != 3
        st.append(from_f80(save[28 + 10 * i:38 + 10 * i]) if valid else None)
    flags = uc.reg_read(UC_X86_REG_EFLAGS)
    out = {'top': top, 'st': st, 'sw': sw, 'eax': uc.reg_read(UC_X86_REG_EAX),
           'zf': (flags >> 6) & 1, 'cf': flags & 1, 'pf': (flags >> 2) & 1}
    if mem_op is not None:
        ea = effective(mem_op)
        out['mem'] = bytes(uc.mem_read(ea - 8, 32))
    return out


def c_case(i, ins, lines, mem_op, mem_value):
    ea = effective(mem_op) if mem_op is not None else 0
    body = '\n'.join('    ' + l for l in lines)
    value = ', '.join('0x%02x' % b for b in mem_value) or '0'
    return f'''
static void case_{i}(Cpu *c)
{{
    uint32_t eax = c->eax, ecx = c->ecx, edx = c->edx, ebx = c->ebx;
    uint32_t esp = c->esp, ebp = c->ebp, esi = c->esi, edi = c->edi;
    uint32_t cf = 0, pf = 0, zf = 0, sf = 0, of = 0;
    uint32_t t0, t1, t2;
    uint64_t q;
    (void)t0; (void)t1; (void)t2; (void)q; (void)sf; (void)of;
{body}
    c->eax = eax; c->ecx = ecx; c->edx = edx; c->ebx = ebx; c->esp = esp; c->ebp = ebp;
    c->esi = esi; c->edi = edi; c->cf = cf; c->zf = zf; c->pf = pf;
}}

static void run_{i}(void)
{{
    static const uint8_t value[] = {{{value}}};
    Cpu cpu = {{0}}, *c = &cpu;
    cpu.eax = cpu.ecx = cpu.edx = cpu.ebx = cpu.ebp = cpu.esi = cpu.edi = 0x{REG:x}u;
    cpu.esp = 0x{ESP:x}u;
    prepare(c);
    {'memcpy(MEM(0x%xu), value, sizeof value);' % ea if mem_op is not None else ''}
    case_{i}(c);
    report({i}, c, 0x{ea:x}u, {1 if mem_op is not None else 0});
}}
'''


PRELUDE = r'''/* Generated by vertrix3/x87_check.py. */
#include "cpu.h"
#include "runtime.h"
#include <stdio.h>
#include <sys/mman.h>

static const double STACK[] = {%s};

static void prepare(Cpu *c)
{
    v3_fpu_init(c);
    for (int k = (int)(sizeof STACK / sizeof STACK[0]) - 1; k >= 0; --k)
    {
        FPUSH(STACK[k]);
    }
    memset(MEM(0x170000u), 0, 0x20000);
}

static void report(int i, Cpu *c, uint32_t ea, int has_mem)
{
    printf("%%d top %%u sw %%04x eax %%08x zf %%u cf %%u pf %%u st", i, c->top, FPU_SW(), c->eax,
           c->zf, c->cf, c->pf);
    for (int k = 0; k < 8; ++k)
    {
        const unsigned p = (c->top + k) & 7u;
        if (c->tags >> p & 1u)
            printf(" %%a", c->st[p]);
        else
            printf(" -");
    }
    printf(" mem ");
    if (has_mem)
        for (int k = -8; k < 24; ++k)
            printf("%%02x", v3_r8(ea + k));
    printf("\n");
}
'''

MAIN = r'''
int main(void)
{
    v3_memory = mmap(NULL, (size_t)1 << 32, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANON | MAP_NORESERVE, -1, 0);
%s
    return 0;
}
'''

STUBS = r'''/* What cpu.c needs from the rest of the runtime, for the x87 check. */
#include "runtime.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
void v3_log(const char *f, ...) { va_list a; va_start(a, f); vfprintf(stderr, f, a); fputc('\n', stderr); va_end(a); }
_Noreturn void v3_fatal(const char *f, ...) { va_list a; va_start(a, f); vfprintf(stderr, f, a); va_end(a); exit(2); }
uint64_t v3_microseconds(void) { return 0; }
const V3Function v3_functions[1];
const unsigned v3_function_count = 0;
int v3_contiguous(uint32_t a, uint32_t n) { (void)a; (void)n; return 1; }
const void *v3_region_of(uint32_t a) { (void)a; return "";}
'''


def main():
    exe, work = sys.argv[1], Path(sys.argv[2])
    cc = sys.argv[3] if len(sys.argv) > 3 else 'cc'
    work.mkdir(parents=True, exist_ok=True)
    p = recomp.Program(exe)
    funcs, entries = recomp.discover(p)
    forms = {}
    for f in funcs.values():
        for a, ins in f.insns.items():
            if ins is None or not ins.mnemonic.startswith('f') or ins.mnemonic in SKIP:
                continue
            forms.setdefault(form(ins), ins)
    gen = recomp.Gen(p, None, set(), set())
    cases, expected = [], {}
    for i, (key, ins) in enumerate(sorted(forms.items(), key=lambda kv: kv[1].address)):
        try:
            lines = gen.x87(ins, recomp.ALL)
        except recomp.Unsupported as e:
            print('unsupported %x %s %s: %s' % (ins.address, ins.mnemonic, ins.op_str, e))
            continue
        mem_op, mem_value = operand_bytes(ins)
        expected[i] = (ins, run_unicorn(ins, mem_op, mem_value))
        cases.append(c_case(i, ins, lines, mem_op, mem_value))
    source = PRELUDE % ', '.join(repr(v) for v in STACK) + ''.join(cases) + MAIN % '\n'.join(
        '    run_%d();' % i for i in expected)
    (work / 'x87_cases.c').write_text(source)
    (work / 'x87_stubs.c').write_text(STUBS)
    runtime = HERE / 'runtime'
    binary = work / 'x87_cases'
    subprocess.run([cc, '-std=gnu11', '-O0', '-w', '-I', str(runtime), str(work / 'x87_cases.c'),
                    str(work / 'x87_stubs.c'), str(runtime / 'cpu.c'), '-lm', '-o', str(binary)],
                   check=True)
    got = {}
    for line in subprocess.run([str(binary)], check=True, capture_output=True, text=True).stdout.splitlines():
        words = line.split()
        i = int(words[0])
        st_at = words.index('st')
        mem_at = words.index('mem')
        got[i] = {'top': int(words[2]), 'sw': int(words[4], 16), 'eax': int(words[6], 16),
                  'zf': int(words[8]), 'cf': int(words[10]), 'pf': int(words[12]),
                  'st': [None if w == '-' else float.fromhex(w) for w in words[st_at + 1:mem_at]],
                  'mem': bytes.fromhex(words[mem_at + 1]) if mem_at + 1 < len(words) else None}
    bad = 0
    for i, (ins, want) in expected.items():
        have = got.get(i)
        problems = []
        if have is None:
            problems.append('no result')
        else:
            if have['top'] != want['top']:
                problems.append('top %d, want %d' % (have['top'], want['top']))
            for k in range(8):
                a, b = have['st'][k], want['st'][k]
                if (a is None) != (b is None):
                    problems.append('st(%d) %s, want %s' % (k, a, b))
                elif a is not None and not close(a, b):
                    problems.append('st(%d) %r, want %r' % (k, a, b))
            if (have['sw'] & 0x4500) != (want['sw'] & 0x4500):
                problems.append('C3/C2/C0 %04x, want %04x' % (have['sw'] & 0x4500, want['sw'] & 0x4500))
            if ins.mnemonic in ('fnstsw', 'fstsw') and not any(o.type == X.X86_OP_MEM for o in ins.operands):
                if (have['eax'] & 0x4500) != (want['eax'] & 0x4500) or (have['eax'] >> 11 & 7) != (want['eax'] >> 11 & 7):
                    problems.append('ax %04x, want %04x' % (have['eax'] & 0xffff, want['eax'] & 0xffff))
            if ins.mnemonic.startswith(('fcomi', 'fucomi')):
                for flag in ('zf', 'cf', 'pf'):
                    if have[flag] != want[flag]:
                        problems.append('%s %d, want %d' % (flag, have[flag], want[flag]))
            if want.get('mem') is not None and have['mem'] != want['mem'] and not mem_close(ins, have['mem'], want['mem']):
                problems.append('memory %s, want %s' % (have['mem'].hex(), want['mem'].hex()))
        if problems:
            bad += 1
            print('%x %-8s %-28s %s' % (ins.address, ins.mnemonic, ins.op_str, '; '.join(problems)))
    print('%d forms, %d differ' % (len(expected), bad))
    return 1 if bad else 0


def close(a, b):
    if a != a and b != b:
        return True
    if a == b:
        return True
    return abs(a - b) <= 1e-12 * max(abs(a), abs(b))


def mem_close(ins, have, want):
    """A float written to memory may differ in its last bit (doubles against 80-bit values)."""
    sizes = [o.size for o in ins.operands if o.type == X.X86_OP_MEM]
    if not sizes or ins.mnemonic.startswith(('fi', 'fn', 'fst')) is False:
        return False
    size = sizes[0]
    if have[:8] != want[:8] or have[8 + size:] != want[8 + size:]:
        return False
    h, w = have[8:8 + size], want[8:8 + size]
    if size == 4:
        a, b = struct.unpack('<f', h)[0], struct.unpack('<f', w)[0]
        return abs(a - b) <= 1e-6 * max(abs(a), abs(b))
    if size == 8:
        a, b = struct.unpack('<d', h)[0], struct.unpack('<d', w)[0]
        return close(a, b)
    if size == 10:
        return close(from_f80(h), from_f80(w))
    return False


if __name__ == '__main__':
    sys.exit(main())
