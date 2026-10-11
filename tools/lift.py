"""Lift a routine of the original Vertrix2.exe into C, one x86 instruction at a time.

The generated function keeps the original's registers (including ebp and esp), its stack (a byte
array below the entry esp whose unwritten bytes are supplied by the caller), its flags and its
control flow (goto) and performs every call of an unrecovered routine through the VertrixCalls
boundary with the registers and stack arguments the original holds at that call. It is meant for
the large builders whose bodies are long chains of the same few instructions; the differential
oracle (tools/verify_lifted.py) proves each lifted routine against the original executing in
Unicorn.

usage: lift.py ADDRESS NAME [--args N] [--meta FILE] > source/lifted_NAME.c
"""
import argparse
import json
import sys
from pathlib import Path

import capstone
import pefile

from import_args import BY_SLOT
from capstone import x86_const as X

EXE = Path('/Volumes/SSD/larsen/Documents/Codex/2026-10-03/goal-ok-i-have-a-big/work/original/'
           'Vertrix2.exe')
pe = pefile.PE(str(EXE))
BASE = pe.OPTIONAL_HEADER.ImageBase
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True

REG32 = {X.X86_REG_EAX: 'eax', X.X86_REG_ECX: 'ecx', X.X86_REG_EDX: 'edx', X.X86_REG_EBX: 'ebx',
         X.X86_REG_ESI: 'esi', X.X86_REG_EDI: 'edi', X.X86_REG_EBP: 'ebp', X.X86_REG_ESP: 'esp'}
REG16 = {X.X86_REG_AX: 'eax', X.X86_REG_CX: 'ecx', X.X86_REG_DX: 'edx', X.X86_REG_BX: 'ebx',
         X.X86_REG_SI: 'esi', X.X86_REG_DI: 'edi', X.X86_REG_BP: 'ebp'}
REG8L = {X.X86_REG_AL: 'eax', X.X86_REG_CL: 'ecx', X.X86_REG_DL: 'edx', X.X86_REG_BL: 'ebx'}
SEGMENTS = {X.X86_REG_DS, X.X86_REG_ES, X.X86_REG_SS, X.X86_REG_CS, X.X86_REG_GS, X.X86_REG_FS}
REG8H = {X.X86_REG_AH: 'eax', X.X86_REG_CH: 'ecx', X.X86_REG_DH: 'edx', X.X86_REG_BH: 'ebx'}

CONDITIONS = {
    'je': 'fl.zf', 'jne': '!fl.zf', 'jb': 'fl.cf', 'jae': '!fl.cf', 'ja': '!fl.cf && !fl.zf',
    'jbe': 'fl.cf || fl.zf', 'jl': 'fl.sf != fl.of', 'jge': 'fl.sf == fl.of',
    'jle': 'fl.zf || fl.sf != fl.of', 'jg': '!fl.zf && fl.sf == fl.of', 'js': 'fl.sf',
    'jns': '!fl.sf', 'jo': 'fl.of', 'jno': '!fl.of', 'jp': 'fl.pf', 'jnp': '!fl.pf',
}
for alias, canonical in (('jz', 'je'), ('jnz', 'jne'), ('jnae', 'jb'), ('jc', 'jb'), ('jnb', 'jae'),
                         ('jnc', 'jae'), ('jna', 'jbe'), ('jnbe', 'ja'), ('jnge', 'jl'),
                         ('jnl', 'jge'), ('jng', 'jle'), ('jnle', 'jg'), ('jpe', 'jp'),
                         ('jpo', 'jnp')):
    CONDITIONS[alias] = CONDITIONS[canonical]

STRING_OPS = {'movsb': ('mov', 1), 'movsw': ('mov', 2), 'movsd': ('mov', 4),
              'stosb': ('stos', 1), 'stosw': ('stos', 2), 'stosd': ('stos', 4),
              'lodsb': ('lods', 1), 'lodsw': ('lods', 2), 'lodsd': ('lods', 4),
              'scasb': ('scas', 1), 'scasw': ('scas', 2), 'scasd': ('scas', 4),
              'cmpsb': ('cmps', 1), 'cmpsw': ('cmps', 2), 'cmpsd': ('cmps', 4)}
STRING_KIND = {'mov': 0, 'stos': 1, 'lods': 2, 'scas': 3, 'cmps': 4}
REPEATS = {'': 0, 'rep': 1, 'repe': 2, 'repz': 2, 'repne': 3, 'repnz': 3}
JUMPS = tuple(CONDITIONS) + ('jmp', 'loop', 'jecxz')


def code_at(address, size=16):
    return pe.get_data(address - BASE, size)


def insn_at(address):
    found = list(md.disasm(code_at(address), address, 1))
    return found[0] if found else None


def callee_args(target, depth=0):
    """The number of stack dwords a callee removes with its ret."""
    for limit in (400, 4000):  # a long routine reaches its first ret late; try the short scan first
        address = target
        for _ in range(limit):
            insn = insn_at(address)
            if insn is None:
                break
            if insn.mnemonic == 'ret':
                return insn.operands[0].imm // 4 if insn.operands else 0
            if insn.mnemonic == 'jmp' and insn.operands[0].type == X.X86_OP_IMM and depth < 4:
                return callee_args(insn.operands[0].imm, depth + 1)
            if (insn.mnemonic == 'jmp' and insn.operands[0].type == X.X86_OP_MEM and
                    not insn.operands[0].mem.base and not insn.operands[0].mem.index and
                    insn.operands[0].mem.disp in BY_SLOT):
                return BY_SLOT[insn.operands[0].mem.disp]  # an import thunk: jmp [slot]
            address += insn.size
    return None


TABLES = {}


def jump_table(seen, insn):
    """The targets of `jmp [index*4 + table]`; the bound comes from the cmp before it."""
    mem = insn.operands[0].mem
    if insn.operands[0].type != X.X86_OP_MEM or mem.base or not mem.index or mem.scale != 4:
        raise NotImplementedError('%x indirect jmp' % insn.address)
    count = None
    for address in sorted((a for a in seen if a < insn.address), reverse=True)[:8]:
        prior = seen[address]
        if prior.mnemonic == 'cmp' and prior.operands[1].type == X.X86_OP_IMM:
            count = prior.operands[1].imm + 1
            break
    if count is None or not 0 < count <= 512:
        raise NotImplementedError('%x indirect jmp without a bound' % insn.address)
    base = mem.disp & 0xffffffff
    targets = []
    for i in range(count):
        target = int.from_bytes(pe.get_data(base - BASE + 4 * i, 4), 'little')
        if not BASE <= target < BASE + 0xf1000:
            raise NotImplementedError('%x jump table entry' % insn.address)
        targets.append(target)
    return targets


def trace(start):
    """Every reachable instruction of the routine, keyed by address."""
    seen, todo = {}, [start]
    while todo:
        address = todo.pop()
        while address not in seen:
            insn = insn_at(address)
            if insn is None:
                raise ValueError('undecodable %x' % address)
            seen[address] = insn
            mnemonic = insn.mnemonic
            if mnemonic in JUMPS:
                op = insn.operands[0]
                if op.type == X.X86_OP_IMM:
                    todo.append(op.imm)
                elif mnemonic == 'jmp':
                    targets = jump_table(seen, insn)
                    TABLES[insn.address] = targets
                    todo.extend(targets)
                if mnemonic == 'jmp':
                    break
            if mnemonic == 'ret':
                break
            address += insn.size
    return seen


class Lifter:
    def __init__(self, start, name):
        self.start = start
        self.name = name
        self.insns = trace(start)
        self.order = sorted(self.insns)
        self.targets = set()
        self.callees = {}
        self.out = []
        for address, insn in self.insns.items():
            if insn.mnemonic in JUMPS:
                op = insn.operands[0]
                if op.type == X.X86_OP_IMM:
                    self.targets.add(op.imm)
                elif address in TABLES:
                    self.targets.update(TABLES[address])
        pushes = sum(1 for i in self.insns.values() if i.mnemonic in ('push', 'call'))
        def frame(i):  # `sub esp, reg` is a dynamic allocation: reserve a generous 0x400
            try:
                return int(i.op_str.split(',')[1], 0)
            except ValueError:
                return 0x400
        sub_esp = sum(frame(i) for i in self.insns.values()
                      if i.mnemonic == 'sub' and i.op_str.startswith('esp,'))
        self.compute_flag_liveness()
        self.stack_size = (sub_esp + 4 * pushes + 0x40 + 3) & ~3

    # ---- flag liveness ---------------------------------------------------------------------
    @staticmethod
    def reads_flags(insn):
        m = insn.mnemonic
        return (m in CONDITIONS or m in ('adc', 'sbb', 'rcl', 'rcr', 'cmc', 'ret') or  # ret: the flags are the callee's answer
                (m.startswith('set') and 'j' + m[3:] in CONDITIONS) or
                (m.startswith('cmov') and 'j' + m[4:] in CONDITIONS) or
                m in STRING_OPS or (len(m.split(' ')) == 2 and m.split(' ')[1] in STRING_OPS))

    @staticmethod
    def kills_flags(insn):
        m = insn.mnemonic
        if m in ('add', 'sub', 'and', 'or', 'xor', 'cmp', 'test', 'neg', 'adc', 'sbb', 'call',
                 'mul', 'imul', 'div', 'idiv', 'bsr', 'bsf'):
            return True
        if m in ('shl', 'sal', 'shr', 'sar') and len(insn.operands) == 2 and \
                insn.operands[1].type == X.X86_OP_IMM and insn.operands[1].imm & 31:
            return True
        return False

    def successors(self, insn):
        m = insn.mnemonic
        following = insn.address + insn.size
        if m == 'ret':
            return []
        if m == 'jmp':
            if insn.operands[0].type == X.X86_OP_IMM:
                return [insn.operands[0].imm]
            return list(TABLES.get(insn.address, []))
        result = [following] if following in self.insns else []
        if m in CONDITIONS or m in ('loop', 'jecxz'):
            result.append(insn.operands[0].imm)
        return result

    def compute_flag_liveness(self):
        live_in = {a: False for a in self.insns}
        live_out = {a: False for a in self.insns}
        changed = True
        while changed:
            changed = False
            for a in reversed(self.order):
                insn = self.insns[a]
                out = any(live_in.get(t, True) for t in self.successors(insn))
                inn = self.reads_flags(insn) or (out and not self.kills_flags(insn))
                if out != live_out[a] or inn != live_in[a]:
                    live_out[a], live_in[a] = out, inn
                    changed = True
        self.flags_live = live_out

    def dead(self, insn):
        """True when no later instruction reads the flags this one would set."""
        return not self.flags_live.get(insn.address, True)

    # ---- operand helpers -------------------------------------------------------------------
    def reg_read(self, reg):
        if reg in SEGMENTS:
            return '0u'
        if reg in REG32:
            return REG32[reg]
        if reg in REG16:
            return '(%s & 0xffffu)' % REG16[reg]
        if reg in REG8L:
            return '(%s & 0xffu)' % REG8L[reg]
        if reg in REG8H:
            return '((%s >> 8) & 0xffu)' % REG8H[reg]
        raise ValueError('register %s' % reg)

    def reg_write(self, reg, value):
        if reg in SEGMENTS:
            return '(void)(%s);' % value
        if reg in REG32:
            return '%s = %s;' % (REG32[reg], value)
        if reg in REG16:
            r = REG16[reg]
            return '%s = (%s & 0xffff0000u) | ((%s) & 0xffffu);' % (r, r, value)
        if reg in REG8L:
            r = REG8L[reg]
            return '%s = (%s & 0xffffff00u) | ((%s) & 0xffu);' % (r, r, value)
        if reg in REG8H:
            r = REG8H[reg]
            return '%s = (%s & 0xffff00ffu) | (((%s) & 0xffu) << 8);' % (r, r, value)
        raise ValueError('register write %s' % reg)

    def address_parts(self, op):
        mem = op.mem
        base = self.reg_read(mem.base) if mem.base else None
        index = None
        if mem.index:
            index = self.reg_read(mem.index)
            if mem.scale != 1:
                index = '(%s * %du)' % (index, mem.scale)
        return base, index, mem.disp

    def address_expr(self, op):
        base, index, disp = self.address_parts(op)
        parts = []
        if base:
            parts.append(base)
        if index:
            parts.append(index)
        if disp or not parts:
            parts.append('0x%xu' % (disp & 0xffffffff))
        return '(' + ' + '.join(parts) + ')'

    def is_chain(self, op):
        return op.mem.segment == X.X86_REG_FS

    def offset_expr(self, index, disp):
        offset = []
        if index:
            offset.append(index)
        offset.append('0x%xu' % (disp & 0xffffffff))
        return ' + '.join(offset)

    def mem_read(self, op):
        if self.is_chain(op):
            return 'env.chain'
        base, index, disp = self.address_parts(op)
        return 'lift_load(&env, %s, %s, %d)' % (base or '0u', self.offset_expr(index, disp),
                                                op.size)

    def mem_write(self, op, value):
        if self.is_chain(op):
            return 'env.chain = %s;' % value
        base, index, disp = self.address_parts(op)
        return 'lift_store(&env, %s, %s, %d, %s);' % (base or '0u', self.offset_expr(index, disp),
                                                     op.size, value)

    def read(self, op):
        if op.type == X.X86_OP_REG:
            return self.reg_read(op.reg)
        if op.type == X.X86_OP_IMM:
            return '0x%xu' % (op.imm & 0xffffffff)
        if op.type == X.X86_OP_MEM:
            return self.mem_read(op)
        raise ValueError('operand')

    def write(self, op, value):
        if op.type == X.X86_OP_REG:
            return self.reg_write(op.reg, value)
        if op.type == X.X86_OP_MEM:
            return self.mem_write(op, value)
        raise ValueError('write operand')

    def bits(self, op):
        return op.size * 8

    def emit(self, text):
        self.out.append('    ' + text)

    # ---- instruction translation -----------------------------------------------------------
    def translate(self, insn, next_insn):
        m = insn.mnemonic
        ops = insn.operands
        if insn.address in self.targets:
            self.out.append('L_%x:' % insn.address)
        if m == 'nop':
            return
        if m in ('cld', 'std'):
            self.emit('fl.df = %d;' % (m == 'std'))
            return
        if m == 'mov' and ops[0].type == X.X86_OP_REG and ops[1].type == X.X86_OP_REG and \
                ops[0].reg == ops[1].reg and ops[0].reg in REG32:
            return
        if m == 'lea' and ops[1].type == X.X86_OP_MEM and ops[0].type == X.X86_OP_REG and \
                ops[1].mem.base == ops[0].reg and not ops[1].mem.index and not ops[1].mem.disp:
            return
        parts = m.split(' ')
        if len(parts) == 2 and parts[0] in REPEATS and parts[1] in STRING_OPS:
            self.string_op(parts[1], parts[0])
            return
        if m in STRING_OPS:
            # Capstone drops the F2/F3 prefix of `f2 a5` (the Delphi runtime's bulk dword copy);
            # read it from the encoding so the copy repeats.
            prefix = {0xf2: 'repne', 0xf3: 'rep'}.get(insn.bytes[0], '')
            self.string_op(m, prefix)
            return
        if m in ('stc', 'clc', 'cmc'):
            self.emit({'stc': 'fl.cf = 1;', 'clc': 'fl.cf = 0;', 'cmc': 'fl.cf = !fl.cf;'}[m])
            return
        if m == 'wait':
            return
        if m in ('shld', 'shrd'):
            bits = self.bits(ops[0])
            self.emit('{ uint32_t a = %s; uint32_t r = lift_%s(%d, a, %s, %s, &fl); %s }' % (
                self.read(ops[0]), m, bits, self.read(ops[1]), self.read(ops[2]),
                self.write(ops[0], 'r')))
            return
        if m == 'mov':
            self.emit(self.write(ops[0], self.read(ops[1])))
        elif m in ('movzx', 'movsx'):
            value = self.read(ops[1])
            if m == 'movsx':
                size = ops[1].size
                value = '(uint32_t)(int32_t)(int%d_t)(uint%d_t)%s' % (size * 8, size * 8, value)
            self.emit(self.write(ops[0], value))
        elif m == 'les':
            # far pointer: the offset dword goes to the register, the selector is ignored (flat)
            base, index, disp = self.address_parts(ops[1])
            self.emit(self.write(ops[0], 'lift_load(&env, %s, %s, 4)' % (
                base or '0u', self.offset_expr(index, disp))))
        elif m == 'cwde':
            self.emit('eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;')
        elif m == 'cbw':
            self.emit('eax = (eax & 0xffff0000u) | (uint32_t)(uint16_t)(int16_t)(int8_t)eax;')
        elif m == 'cdq':
            self.emit('edx = (eax & 0x80000000u) ? 0xffffffffu : 0u;')
        elif m == 'cwd':
            self.emit('edx = (edx & 0xffff0000u) | ((eax & 0x8000u) ? 0xffffu : 0u);')
        elif m == 'lea':
            self.emit(self.write(ops[0], self.address_expr(ops[1])))
        elif m in ('add', 'sub', 'and', 'or', 'xor', 'cmp', 'test', 'adc', 'sbb'):
            self.arith(m, ops, insn)
        elif m in ('inc', 'dec') and self.dead(insn):
            self.emit(self.write(ops[0], '%s %s 1u' % (self.read(ops[0]),
                                                      '+' if m == 'inc' else '-')))
        elif m == 'neg' and self.dead(insn):
            self.emit(self.write(ops[0], '0u - %s' % self.read(ops[0])))
        elif m in ('inc', 'dec'):
            bits = self.bits(ops[0])
            self.emit('{ uint32_t a = %s; uint32_t r = lift_%s(%d, a, &fl, 1); %s }' % (
                self.read(ops[0]), m, bits, self.write(ops[0], 'r')))
        elif m == 'neg':
            bits = self.bits(ops[0])
            self.emit('{ uint32_t a = %s; uint32_t r = lift_sub(%d, 0, a, &fl); %s }' % (
                self.read(ops[0]), bits, self.write(ops[0], 'r')))
        elif m == 'not':
            bits = self.bits(ops[0])
            self.emit('{ uint32_t a = %s; %s }' % (
                self.read(ops[0]), self.write(ops[0], '(~a) & lift_mask(%d)' % (bits // 8))))
        elif m == 'imul' and len(ops) >= 2:
            self.imul(ops)
        elif m in ('mul', 'imul', 'div', 'idiv'):
            self.emit('lift_%s1(%d, %s, &eax, &edx, &fl);' % (m, self.bits(ops[0]),
                                                            self.read(ops[0])))
        elif m in ('shl', 'sal', 'shr', 'sar', 'rol', 'ror', 'rcl', 'rcr'):
            name = 'shl' if m == 'sal' else m
            bits = self.bits(ops[0])
            count = self.read(ops[1]) if len(ops) > 1 else '1u'
            self.emit('{ uint32_t a = %s; uint32_t r = lift_%s(%d, a, %s, &fl); %s }' % (
                self.read(ops[0]), name, bits, count, self.write(ops[0], 'r')))
        elif m in ('bsr', 'bsf'):
            self.emit('{ uint32_t a = %s; fl.zf = a == 0; if (a != 0) { %s } }' % (
                self.read(ops[1]), self.write(ops[0], 'lift_%s(a)' % m)))
        elif m == 'xchg':
            self.emit('{ uint32_t t = %s; %s %s }' % (self.read(ops[0]),
                                                      self.write(ops[0], self.read(ops[1])),
                                                      self.write(ops[1], 't')))
        elif m == 'push':
            value = 'env.chain' if (ops[0].type == X.X86_OP_MEM and self.is_chain(ops[0])) else \
                self.read(ops[0])
            if ops[0].type == X.X86_OP_IMM:
                value = '0x%xu' % (ops[0].imm & 0xffffffff)
            self.emit('{ uint32_t v = %s; esp -= 4u; lift_store(&env, esp, 0u, 4, v); }' % value)
        elif m == 'pop':
            target = 'env.chain = v;' if (ops[0].type == X.X86_OP_MEM and
                                          self.is_chain(ops[0])) else self.write(ops[0], 'v')
            self.emit('{ uint32_t v = lift_load(&env, esp, 0u, 4); esp += 4u; %s }' % target)
        elif m == 'leave':
            self.emit('esp = ebp; ebp = lift_load(&env, esp, 0u, 4); esp += 4u;')
        elif m == 'call':
            self.call(insn, next_insn)
        elif m == 'jmp' and ops[0].type == X.X86_OP_MEM:
            cases = ' '.join('case %d: goto L_%x;' % (i, t)
                             for i, t in enumerate(TABLES[insn.address]))
            self.emit('{ uint32_t i = %s; switch (i) { %s default: return 0u; } }' % (
                self.reg_read(ops[0].mem.index), cases))
        elif m == 'jmp':
            self.emit('goto L_%x;' % ops[0].imm)
        elif m in CONDITIONS:
            self.emit('if (%s) goto L_%x;' % (CONDITIONS[m], ops[0].imm))
        elif m == 'loop':
            self.emit('ecx -= 1u; if (ecx != 0u) goto L_%x;' % ops[0].imm)
        elif m == 'jecxz':
            self.emit('if (ecx == 0u) goto L_%x;' % ops[0].imm)
        elif m.startswith('set') and 'j' + m[3:] in CONDITIONS:
            self.emit(self.write(ops[0], '(%s) ? 1u : 0u' % CONDITIONS['j' + m[3:]]))
        elif m.startswith('cmov') and 'j' + m[4:] in CONDITIONS:
            self.emit('if (%s) { %s }' % (CONDITIONS['j' + m[4:]],
                                          self.write(ops[0], self.read(ops[1]))))
        elif m == 'ret':
            self.emit('vertrix_lift_edx = edx;')
            self.emit('vertrix_lift_fl = fl;')
            self.emit('return env.failed ? 0u : eax;')
        else:
            raise NotImplementedError('%x %s %s' % (insn.address, m, insn.op_str))

    def arith(self, m, ops, insn=None):
        bits = self.bits(ops[0])
        a = self.read(ops[0])
        b = self.read(ops[1])
        if ops[1].type == X.X86_OP_IMM:
            b = '0x%xu' % (ops[1].imm & ((1 << bits) - 1))
        func = {'add': 'lift_add', 'sub': 'lift_sub', 'cmp': 'lift_sub', 'and': 'lift_and',
                'test': 'lift_and', 'or': 'lift_or', 'xor': 'lift_xor', 'adc': 'lift_adc',
                'sbb': 'lift_sbb'}[m]
        if insn is not None and self.dead(insn):
            if m in ('cmp', 'test'):
                return
            plain = {'add': '%s + %s', 'sub': '%s - %s', 'and': '%s & %s', 'or': '%s | %s',
                     'xor': '%s ^ %s', 'adc': '%s + %s + fl.cf', 'sbb': '%s - %s - fl.cf'}[m]
            self.emit(self.write(ops[0], plain % (a, b)))
            return
        if m in ('cmp', 'test'):
            self.emit('{ (void)%s(%d, %s, %s, &fl); }' % (func, bits, a, b))
        else:
            self.emit('{ uint32_t r = %s(%d, %s, %s, &fl); %s }' % (
                func, bits, a, b, self.write(ops[0], 'r')))

    def imul(self, ops):
        bits = self.bits(ops[0])
        if len(ops) == 2:
            a, b = self.read(ops[0]), self.read(ops[1])
        else:
            a, b = self.read(ops[1]), self.read(ops[2])
            if ops[2].type == X.X86_OP_IMM:
                b = '0x%xu' % (ops[2].imm & ((1 << bits) - 1))
        self.emit('{ uint32_t r = lift_imul(%d, %s, %s, &fl); %s }' % (
            bits, a, b, self.write(ops[0], 'r')))

    def string_op(self, name, prefix):
        kind, size = STRING_OPS[name]
        self.emit('lift_string(&env, %d, %d, %d, &eax, &ecx, &esi, &edi, &fl);' % (
            STRING_KIND[kind], size, REPEATS[prefix]))

    def prologue_end(self):
        """The address after the register saves and frame setup at the start of the routine."""
        address = self.start
        while True:
            insn = self.insns.get(address)
            # Only register pushes are saves: 0x486da0 pushes an immediate argument (`push 0`)
            # straight after its saves.
            if insn is None or not ((insn.mnemonic == 'push' and
                                     insn.operands[0].type == X.X86_OP_REG) or
                                    (insn.mnemonic == 'mov' and insn.op_str == 'ebp, esp') or
                                    (insn.mnemonic == 'sub' and insn.op_str.startswith('esp,'))):
                return address
            address += insn.size

    def pending_pushes(self, insn):
        """Pushes directly preceding an import call (the stdcall argument count)."""
        index = self.order.index(insn.address)
        count = 0
        prologue = self.prologue_end()
        for address in reversed(self.order[:index]):
            p = self.insns[address]
            if address < prologue:
                break
            if p.mnemonic == 'push':
                count += 1
            elif p.mnemonic in ('call', 'ret', 'jmp') or p.mnemonic in CONDITIONS or \
                    address in self.targets:
                break
        return count

    def deferred_cleanup(self, insn):
        """The `add esp, n` of a cdecl call that is not the next instruction: the caller may do
        register work first (0x465383 calls sprintf 0x4cdfb0, loads eax, then `add esp, 0xc`).
        The instructions between must not touch esp or be branch targets, and the cleanup must not
        remove more than the pushes directly before the call."""
        address = insn.address + insn.size
        for _ in range(8):
            nxt = self.insns.get(address)
            if nxt is None or address in self.targets:
                return None
            if nxt.mnemonic == 'add' and nxt.op_str.startswith('esp,'):
                count = int(nxt.op_str.split(',')[1], 0) // 4
                return nxt if 0 < count <= self.pending_pushes(insn) else None
            if nxt.mnemonic in ('call', 'ret', 'jmp', 'push', 'pop', 'leave', 'pushfd', 'popfd',
                                'pushal', 'popal') or nxt.mnemonic in CONDITIONS or \
                    'esp' in nxt.op_str:
                return None
            address += nxt.size
        return None

    def call(self, insn, next_insn):
        op = insn.operands[0]
        cdecl = (next_insn is not None and next_insn.mnemonic == 'add' and
                 next_insn.op_str.startswith('esp,'))
        # With no push before the call, an `add esp` right after it releases the caller's own
        # locals (0x4daae8: `sub esp, 0xc` at entry, `call 0x4daab0; add esp, 0xc` at the end).
        if cdecl and op.type == X.X86_OP_IMM and self.pending_pushes(insn) == 0:
            cdecl = False
        if not cdecl and op.type == X.X86_OP_IMM:
            deferred = self.deferred_cleanup(insn)
            if deferred is not None:
                cdecl, next_insn = True, deferred
        if op.type == X.X86_OP_IMM:
            target = op.imm
            target_expr = '0x%xu' % target
            count = callee_args(target)
            if count is None:
                raise ValueError('callee %x' % target)
            # A callee that removes its own arguments (ret N) is not cdecl: an `add esp` after the
            # call then belongs to the caller's epilogue.
            cdecl = cdecl and count == 0
            if cdecl:
                count = int(next_insn.op_str.split(',')[1], 0) // 4
            self.callees[target] = (count, cdecl)
            pops = 0 if cdecl else count
        elif op.type == X.X86_OP_MEM and not op.mem.base and not op.mem.index and \
                op.mem.segment != X.X86_REG_FS and 0x4f1000 <= op.mem.disp < 0x4f4000:
            # an import: the slot address is the target (stdcall)
            target_expr = '0x%xu' % op.mem.disp
            # A stdcall import with arguments pops them itself: an `add esp` after the call is the
            # caller's epilogue (0x4cfd20 calls SetWindowLongA just before `add esp, 8`).
            cdecl = cdecl and not BY_SLOT.get(op.mem.disp)
            if cdecl:
                count = int(next_insn.op_str.split(',')[1], 0) // 4
            else:
                count = BY_SLOT.get(op.mem.disp, None)
                if count is None:
                    count = self.pending_pushes(insn)
            self.callees[op.mem.disp] = (count, cdecl)
            pops = 0 if cdecl else count
        elif op.type == X.X86_OP_MEM and not op.mem.base and not op.mem.index and \
                op.mem.segment != X.X86_REG_FS:
            # a function pointer held in a global slot
            target_expr = self.read(op)
            count = int(next_insn.op_str.split(',')[1], 0) // 4 if cdecl else \
                self.pending_pushes(insn)
            self.callees[('slot', op.mem.disp)] = (count, cdecl)
            pops = 0 if cdecl else count
        else:
            target_expr = self.read(op)
            count = int(next_insn.op_str.split(',')[1], 0) // 4 if cdecl else \
                self.pending_pushes(insn)
            self.callees[('virtual', insn.address)] = (count, cdecl)
            pops = 0 if cdecl else count
        self.emit('vertrix_lift_fl = fl;')
        self.emit('eax = lift_call(&env, %s, eax, edx, ebx, ecx, %d, esp);' % (target_expr, count))
        self.emit('edx = vertrix_lift_edx;')
        self.emit('fl = vertrix_lift_fl;')
        if pops:
            self.emit('esp += %du;' % (4 * pops))

    # ---- analyses used by the verifier -----------------------------------------------------
    def pointer_callees(self):
        """Callees whose result is used as the base of a memory operand before it is replaced."""
        found = set()
        for index, address in enumerate(self.order):
            insn = self.insns[address]
            if insn.mnemonic != 'call' or insn.operands[0].type != X.X86_OP_IMM:
                continue
            target = insn.operands[0].imm
            holding = {X.X86_REG_EAX}
            for follower in self.order[index + 1:index + 40]:
                nxt = self.insns[follower]
                if nxt.mnemonic in ('ret', 'jmp') or nxt.mnemonic in CONDITIONS and \
                        nxt.operands[0].imm < follower:
                    break
                if nxt.mnemonic == 'call':
                    holding -= {X.X86_REG_EAX}
                    if not holding:
                        break
                    continue
                for op in nxt.operands:
                    if op.type == X.X86_OP_MEM and (op.mem.base in holding):
                        found.add(target)
                if nxt.mnemonic == 'mov' and nxt.operands[0].type == X.X86_OP_REG and \
                        nxt.operands[1].type == X.X86_OP_REG and nxt.operands[1].reg in holding:
                    holding.add(nxt.operands[0].reg)
                elif nxt.mnemonic in ('mov', 'xor', 'lea', 'pop') and \
                        nxt.operands[0].type == X.X86_OP_REG:
                    holding.discard(nxt.operands[0].reg)
                if not holding:
                    break
        return found

    def pointer_fields(self, absolute=False):
        """Offsets of object dwords that are loaded into a register used as a memory base
        (with absolute, the global dwords instead)."""
        found = set()
        for index, address in enumerate(self.order):
            insn = self.insns[address]
            ops = insn.operands
            if insn.mnemonic != 'mov' or ops[0].type != X.X86_OP_REG or \
                    ops[1].type != X.X86_OP_MEM:
                continue
            mem = ops[1].mem
            if ops[1].size != 4 or mem.index or mem.segment == X.X86_REG_FS:
                continue
            if absolute != (not mem.base):
                continue
            if mem.base in (X.X86_REG_EBP, X.X86_REG_ESP):
                continue
            holding = {ops[0].reg}
            for follower in self.order[index + 1:index + 40]:
                nxt = self.insns[follower]
                if nxt.mnemonic in ('ret', 'jmp'):
                    break
                if nxt.mnemonic == 'call':
                    holding -= {X.X86_REG_EAX}
                    if not holding:
                        break
                    continue
                for op in nxt.operands:
                    if op.type == X.X86_OP_MEM and op.mem.base in holding:
                        found.add(mem.disp)
                if nxt.mnemonic == 'mov' and nxt.operands[0].type == X.X86_OP_REG and \
                        nxt.operands[1].type == X.X86_OP_REG and nxt.operands[1].reg in holding:
                    holding.add(nxt.operands[0].reg)
                elif nxt.mnemonic in ('mov', 'xor', 'lea', 'pop') and \
                        nxt.operands[0].type == X.X86_OP_REG:
                    holding.discard(nxt.operands[0].reg)
                if not holding:
                    break
        return found

    def constants(self):
        """Immediates the routine compares against (and their neighbours): good scalar inputs."""
        found = set()
        for insn in self.insns.values():
            if insn.mnemonic in ('cmp', 'test', 'sub') and len(insn.operands) == 2 and \
                    insn.operands[1].type == X.X86_OP_IMM:
                value = insn.operands[1].imm
                for delta in (-1, 0, 1):
                    found.add((value + delta) & 0xffffffff)
        return found

    def pointer_maybe(self):
        """Object dwords that are loaded and spilled to a local (they may be object pointers)."""
        found = set()
        for index, address in enumerate(self.order):
            insn = self.insns[address]
            ops = insn.operands
            if insn.mnemonic != 'mov' or ops[0].type != X.X86_OP_REG or \
                    ops[1].type != X.X86_OP_MEM:
                continue
            mem = ops[1].mem
            if ops[1].size != 4 or not mem.base or mem.index or \
                    mem.base in (X.X86_REG_EBP, X.X86_REG_ESP) or mem.segment == X.X86_REG_FS:
                continue
            # Follow the loaded register until it is overwritten (0x452960 spills [eax + 0x15c]
            # four instructions later, after unrelated register setup).
            for follower in self.order[index + 1:index + 12]:
                nxt = self.insns[follower]
                if nxt.mnemonic in ('call', 'ret', 'jmp') or nxt.mnemonic in CONDITIONS:
                    break
                if nxt.mnemonic == 'mov' and nxt.operands[0].type == X.X86_OP_MEM and \
                        nxt.operands[0].mem.base == X.X86_REG_EBP and \
                        nxt.operands[1].type == X.X86_OP_REG and \
                        nxt.operands[1].reg == ops[0].reg:
                    found.add(mem.disp)
                    break
                if nxt.operands and nxt.operands[0].type == X.X86_OP_REG and \
                        nxt.operands[0].reg == ops[0].reg and nxt.mnemonic not in ('cmp', 'test'):
                    break
        return found

    def virtual_calls(self):
        """(object field, vtable slot) pairs of `call [reg + slot]` where reg came from a field."""
        found = set()
        for index, address in enumerate(self.order):
            insn = self.insns[address]
            if insn.mnemonic != 'call' or insn.operands[0].type != X.X86_OP_MEM:
                continue
            mem = insn.operands[0].mem
            if not mem.base or mem.index:
                continue
            field = None
            for prior in reversed(self.order[max(0, index - 12):index]):
                p = self.insns[prior]
                if p.mnemonic in ('call', 'ret', 'jmp') or p.mnemonic in CONDITIONS:
                    break
                if p.operands and p.operands[0].type == X.X86_OP_REG and \
                        p.operands[0].reg == mem.base:
                    if p.mnemonic == 'mov' and p.operands[1].type == X.X86_OP_MEM and \
                            not p.operands[1].mem.index and \
                            p.operands[1].mem.base not in (X.X86_REG_EBP, X.X86_REG_ESP):
                        field = p.operands[1].mem.disp
                    break
            nxt = self.insns.get(address + insn.size)
            if nxt is not None and nxt.mnemonic == 'add' and nxt.op_str.startswith('esp,'):
                count = int(nxt.op_str.split(',')[1], 0) // 4
            else:
                count = self.pending_pushes(insn)
            found.add((field, mem.disp, count))
        return found

    def lift(self):
        order = self.order
        # Code is emitted in address order. A routine that jumps to code below its entry (a
        # shared `xor eax, eax; ret` tail, as 0x47f410 uses) must start with a jump to the entry.
        if order and order[0] != self.start:
            self.targets.add(self.start)
            self.emit('goto L_%x;' % self.start)
        for index, address in enumerate(order):
            insn = self.insns[address]
            next_insn = self.insns.get(address + insn.size)
            self.translate(insn, next_insn)
            if insn.mnemonic in ('call',) and next_insn is not None and \
                    next_insn.mnemonic == 'add' and next_insn.op_str.startswith('esp,'):
                pass
        return self.out


def render(start, name, argument_count=None, include_prelude=True):
    """Lift one routine. Returns (C text, prototype header text, meta dict)."""
    if argument_count is None:
        argument_count = 0
    lifter = Lifter(start, name)
    body = lifter.lift()
    stack_size = lifter.stack_size
    upper = name.upper()
    prelude = '''/* Lifted from the original routine at 0x%x by tools/lift.py: every instruction of the original
 * is translated in order (registers, stack, flags and gotos) and every unrecovered callee goes
 * through the call boundary with the registers and stack arguments the original holds there.
 * Verified against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_%s.h"

''' % (start, name)
    function = '''uint32_t lifted_%s(const VertrixCalls *calls, const VertrixFactoryServices *services,
                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_%s_STACK + 4 + 4 * %d + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_%s_STACK, %d, entry);
''' % (name, upper, argument_count, upper, argument_count)
    text = (prelude if include_prelude else '') + function + '\n'.join(body) + '\n}\n'
    header = '''#ifndef VERTRIX_LIFTED_%s_H
#define VERTRIX_LIFTED_%s_H
#include <stdint.h>

#include "lift_runtime.h"

enum
{
    LIFTED_%s_STACK = %d
};

/* The original routine 0x%x lifted instruction by instruction (see tools/lift.py). `entry` holds
 * the registers at entry, esp (the address of the return slot), the stack dwords above it and
 * the LIFTED_%s_STACK bytes below it the routine may read before it writes them. */
uint32_t lifted_%s(const VertrixCalls *calls, const VertrixFactoryServices *services,
                   const VertrixGlobals *globals, const LiftEntry *entry);
#endif
''' % (upper, upper, upper, stack_size, start, upper, name)
    callees = {('0x%x' % k if isinstance(k, int) else '%s_%x' % (k[0], k[1])): v
               for k, v in lifter.callees.items()}
    meta = {'callees': callees, 'stack': stack_size, 'arguments': argument_count,
            'pointer_callees': sorted('0x%x' % t for t in lifter.pointer_callees()),
            'pointer_fields': sorted(lifter.pointer_fields()),
            'pointer_globals': sorted(lifter.pointer_fields(True)),
            'pointer_maybe': sorted(lifter.pointer_maybe()),
            'constants': sorted(lifter.constants())[:64],
            'virtual': sorted([f if f is not None else -1, sl, n]
                              for f, sl, n in lifter.virtual_calls())}
    return text, header, meta


def return_arguments(start):
    """The stack dwords the routine removes with its ret (the incoming arguments)."""
    return callee_args(start) or 0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('address')
    parser.add_argument('name')
    parser.add_argument('--args', type=int, default=None,
                        help='stack dwords above the return address')
    parser.add_argument('--meta', type=Path)
    options = parser.parse_args()
    start = int(options.address, 16)
    arguments = options.args if options.args is not None else return_arguments(start)
    text, header, meta = render(start, options.name, arguments)
    sys.stdout.write(text)
    header_path = Path(__file__).resolve().parents[1] / 'source' / ('lifted_%s.h' % options.name)
    header_path.write_text(header)
    if options.meta:
        options.meta.write_text(json.dumps(meta, indent=1))


if __name__ == '__main__':
    main()
