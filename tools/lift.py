"""Lift a routine of the original Vertrix2.exe into C, one x86 instruction at a time.

The generated function keeps the original's registers, its stack frame (locals as a byte array),
its flags and its control flow (goto) and performs every call of an unrecovered routine through
the VertrixCalls boundary with the registers and stack arguments the original holds at that call.
It is meant for the large screen builders whose bodies are long chains of the same few
instructions; the differential oracle (tools/verify_lifted.py) proves each lifted routine against
the original executing in Unicorn.

usage: lift.py ADDRESS NAME [--args N] [--locals N] > source/lifted_NAME.c
"""
import argparse
import json
import sys
from pathlib import Path

import capstone
import pefile
from capstone import x86_const as X

EXE = Path('/Volumes/SSD/larsen/Documents/Codex/2026-10-03/goal-ok-i-have-a-big/work/original/'
           'Vertrix2.exe')
pe = pefile.PE(str(EXE))
BASE = pe.OPTIONAL_HEADER.ImageBase
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True

REG32 = {X.X86_REG_EAX: 'eax', X.X86_REG_ECX: 'ecx', X.X86_REG_EDX: 'edx', X.X86_REG_EBX: 'ebx',
         X.X86_REG_ESI: 'esi', X.X86_REG_EDI: 'edi'}
REG16 = {X.X86_REG_AX: 'eax', X.X86_REG_CX: 'ecx', X.X86_REG_DX: 'edx', X.X86_REG_BX: 'ebx',
         X.X86_REG_SI: 'esi', X.X86_REG_DI: 'edi'}
REG8L = {X.X86_REG_AL: 'eax', X.X86_REG_CL: 'ecx', X.X86_REG_DL: 'edx', X.X86_REG_BL: 'ebx'}
REG8H = {X.X86_REG_AH: 'eax', X.X86_REG_CH: 'ecx', X.X86_REG_DH: 'edx', X.X86_REG_BH: 'ebx'}

CONDITIONS = {
    'je': 'fl.zf', 'jne': '!fl.zf', 'jb': 'fl.cf', 'jae': '!fl.cf', 'ja': '(!fl.cf && !fl.zf)', 'jbe': '(fl.cf || fl.zf)',
    'jl': '(fl.sf != fl.of)', 'jge': '(fl.sf == fl.of)', 'jle': '(fl.zf || fl.sf != fl.of)', 'jg': '(!fl.zf && fl.sf == fl.of)',
    'js': 'fl.sf', 'jns': '!fl.sf', 'jo': 'fl.of', 'jno': '!fl.of',
}


def code_at(address, size=16):
    return pe.get_data(address - BASE, size)


def insn_at(address):
    found = list(md.disasm(code_at(address), address, 1))
    return found[0] if found else None


def callee_args(target, depth=0):
    """The number of stack dwords a callee removes with its ret."""
    address = target
    for _ in range(400):
        insn = insn_at(address)
        if insn is None:
            return None
        if insn.mnemonic == 'ret':
            return insn.operands[0].imm // 4 if insn.operands else 0
        if insn.mnemonic == 'jmp' and insn.operands[0].type == X.X86_OP_IMM and depth < 4:
            return callee_args(insn.operands[0].imm, depth + 1)
        address += insn.size
    return None


def trace(start):
    """Every reachable instruction of the routine, keyed by address."""
    seen, todo = {}, [start]
    while todo:
        address = todo.pop()
        while address not in seen:
            insn = insn_at(address)
            if insn is None:
                break
            seen[address] = insn
            mnemonic = insn.mnemonic
            if mnemonic in CONDITIONS or mnemonic == 'jmp':
                op = insn.operands[0]
                if op.type == X.X86_OP_IMM:
                    todo.append(op.imm)
                if mnemonic == 'jmp':
                    break
            if mnemonic == 'ret':
                break
            address += insn.size
    return seen


class Lifter:
    def __init__(self, start, name, argument_count, locals_size):
        self.start = start
        self.name = name
        self.argument_count = argument_count
        self.locals_size = locals_size
        self.insns = trace(start)
        self.order = sorted(self.insns)
        self.targets = set()
        self.callees = {}
        self.out = []
        self.skip = set()
        self.min_disp = 0
        for address, insn in self.insns.items():
            if insn.mnemonic in CONDITIONS or insn.mnemonic == 'jmp':
                op = insn.operands[0]
                if op.type == X.X86_OP_IMM:
                    self.targets.add(op.imm)
        self.find_frame()

    # ---- prologue and epilogue -------------------------------------------------------------
    def find_frame(self):
        address = self.start
        while True:
            insn = self.insns[address]
            text = insn.mnemonic + ' ' + insn.op_str
            if (insn.mnemonic == 'push' and insn.op_str in ('ebp', 'ebx', 'ecx', 'edx', 'esi', 'edi')
                    or text == 'mov ebp, esp' or insn.mnemonic == 'sub' and insn.op_str.startswith(
                        'esp,')):
                if insn.mnemonic == 'sub':
                    self.frame_extra = int(insn.op_str.split(',')[1], 0)
                self.skip.add(address)
                address += insn.size
                continue
            break
        self.body = address
        # epilogue: pops and lea esp before ret
        for address, insn in self.insns.items():
            if insn.mnemonic == 'ret':
                previous = address
                # walk backwards through the sorted instruction list
                index = self.order.index(address) - 1
                while index >= 0:
                    prior = self.insns[self.order[index]]
                    if prior.mnemonic == 'pop' or (prior.mnemonic == 'lea' and
                                                   prior.op_str.startswith('esp,')):
                        self.skip.add(prior.address)
                        index -= 1
                    else:
                        break

    # ---- operand helpers -------------------------------------------------------------------
    def reg_read(self, reg):
        if reg in REG32:
            return REG32[reg]
        if reg == X.X86_REG_EBP:
            return 'frame'
        if reg in REG16:
            return '(%s & 0xffffu)' % REG16[reg]
        if reg in REG8L:
            return '(%s & 0xffu)' % REG8L[reg]
        if reg in REG8H:
            return '((%s >> 8) & 0xffu)' % REG8H[reg]
        raise ValueError('register %s' % reg)

    def reg_write(self, reg, value):
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
        return mem.base, base, index, mem.disp

    def address_expr(self, op):
        base_reg, base, index, disp = self.address_parts(op)
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

    def mem_read(self, op):
        size = op.size
        if self.is_chain(op):
            return 'env.chain'
        base_reg, base, index, disp = self.address_parts(op)
        if base_reg == X.X86_REG_EBP and not index:
            self.min_disp = min(self.min_disp, disp)
            return 'lift_local_read(&env, %d, %d)' % (disp, size)
        offset = []
        if index:
            offset.append(index)
        offset.append('0x%xu' % (disp & 0xffffffff))
        return 'lift_load(&env, %s, %s, %d)' % (base or '0u', ' + '.join(offset), size)

    def mem_write(self, op, value):
        size = op.size
        if self.is_chain(op):
            return 'env.chain = %s;' % value
        base_reg, base, index, disp = self.address_parts(op)
        if base_reg == X.X86_REG_EBP and not index:
            self.min_disp = min(self.min_disp, disp)
            return 'lift_local_write(&env, %d, %d, %s);' % (disp, size, value)
        offset = []
        if index:
            offset.append(index)
        offset.append('0x%xu' % (disp & 0xffffffff))
        return 'lift_store(&env, %s, %s, %d, %s);' % (base or '0u', ' + '.join(offset), size,
                                                     value)

    def read(self, op, size=None):
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

    # ---- instruction translation -----------------------------------------------------------
    def emit(self, text):
        self.out.append('    ' + text)

    def translate(self, insn, next_insn):
        m = insn.mnemonic
        ops = insn.operands
        label = 'L_%x' % insn.address
        if insn.address in self.targets:
            self.out.append('%s:' % label)
        if insn.address in self.skip:
            return None
        if m == 'nop':
            return None
        if m == 'mov':
            self.emit(self.write(ops[0], self.read(ops[1])))
        elif m in ('movzx', 'movsx'):
            value = self.read(ops[1])
            if m == 'movsx':
                size = ops[1].size
                value = '(uint32_t)(int32_t)(int%d_t)(uint%d_t)%s' % (size * 8, size * 8, value)
            self.emit(self.write(ops[0], value))
        elif m == 'cwde':
            self.emit('eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;')
        elif m == 'lea':
            self.emit(self.write(ops[0], self.address_expr(ops[1]) if not self.uses_ebp(ops[1])
                                 else self.ebp_address(ops[1])))
        elif m in ('add', 'sub', 'and', 'or', 'xor', 'cmp', 'test'):
            self.arith(m, ops)
        elif m in ('inc', 'dec'):
            bits = self.bits(ops[0])
            self.emit('{ uint32_t a = %s; uint32_t r = lift_%s(%d, a, &fl, 1); %s }' % (
                self.read(ops[0]), m, bits, self.write(ops[0], 'r')))
        elif m == 'neg':
            bits = self.bits(ops[0])
            self.emit('{ uint32_t a = %s; uint32_t r = lift_sub(%d, 0, a, &fl); %s }' % (
                self.read(ops[0]), bits, self.write(ops[0], 'r')))
        elif m == 'imul':
            self.imul(ops)
        elif m in ('shl', 'shr', 'sar'):
            bits = self.bits(ops[0])
            count = self.read(ops[1]) if len(ops) > 1 else '1u'
            self.emit('{ uint32_t a = %s; uint32_t r = lift_%s(%d, a, %s, &fl); %s }' % (
                self.read(ops[0]), m, bits, count, self.write(ops[0], 'r')))
        elif m == 'push':
            value = 'env.chain' if (ops[0].type == X.X86_OP_MEM and self.is_chain(ops[0])) else \
                self.read(ops[0])
            self.emit('env.stack[env.sp++] = %s;' % value)
        elif m == 'pop':
            self.emit(self.write(ops[0], 'env.stack[--env.sp]'))
        elif m == 'call':
            self.call(insn, next_insn)
        elif m == 'jmp':
            self.emit('goto L_%x;' % ops[0].imm)
        elif m in CONDITIONS:
            self.emit('if (%s) goto L_%x;' % (CONDITIONS[m], ops[0].imm))
        elif m == 'ret':
            n = ops[0].imm // 4 if ops else 0
            self.emit('return env.failed ? 0u : eax;')
        elif m == 'xchg':
            self.emit('{ uint32_t t = %s; %s %s }' % (self.read(ops[0]),
                                                      self.write(ops[0], self.read(ops[1])),
                                                      self.write(ops[1], 't')))
        else:
            raise NotImplementedError('%x %s %s' % (insn.address, m, insn.op_str))

    def uses_ebp(self, op):
        return op.type == X.X86_OP_MEM and op.mem.base == X.X86_REG_EBP

    def ebp_address(self, op):
        self.min_disp = min(self.min_disp, op.mem.disp)
        base_reg, base, index, disp = self.address_parts(op)
        parts = [base]
        if index:
            parts.append(index)
        if disp:
            parts.append('0x%xu' % (disp & 0xffffffff))
        return '(' + ' + '.join(parts) + ')'

    def arith(self, m, ops):
        bits = self.bits(ops[0])
        a = self.read(ops[0])
        b = self.read(ops[1])
        if ops[1].type == X.X86_OP_IMM:
            # sign-extended immediates take the operand size
            b = '0x%xu' % (ops[1].imm & ((1 << bits) - 1))
        func = {'add': 'lift_add', 'sub': 'lift_sub', 'cmp': 'lift_sub', 'and': 'lift_and',
                'test': 'lift_and', 'or': 'lift_or', 'xor': 'lift_xor'}[m]
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
        self.emit('{ uint32_t r = lift_imul(%d, %s, %s, &fl); %s }' % (
            bits, a, b, self.write(ops[0], 'r')))

    def call(self, insn, next_insn):
        op = insn.operands[0]
        cdecl = (next_insn is not None and next_insn.mnemonic == 'add'
                 and next_insn.op_str.startswith('esp,'))
        if op.type == X.X86_OP_IMM:
            target = op.imm
            target_expr = '0x%xu' % target
            count = callee_args(target)
            if count is None:
                raise ValueError('callee %x' % target)
            if cdecl:
                count = int(next_insn.op_str.split(',')[1], 0) // 4
                self.skip.add(next_insn.address)
            self.callees[target] = (count, cdecl)
        else:
            target_expr = self.read(op)
            count = int(next_insn.op_str.split(',')[1], 0) // 4 if cdecl else 0
            if cdecl:
                self.skip.add(next_insn.address)
            self.callees[('virtual', insn.address)] = (count, cdecl)
        self.emit('eax = lift_call(&env, %s, eax, edx, ebx, ecx, %d);' % (target_expr, count))

    def pointer_callees(self):
        """Callees whose result is used as the base of a memory operand before the next call."""
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
                    holding -= {X.X86_REG_EAX, X.X86_REG_ECX, X.X86_REG_EDX}
                    if not holding:
                        break
                    continue
                ops = nxt.operands
                for op in ops:
                    if op.type == X.X86_OP_MEM and (op.mem.base in holding):
                        found.add(target)
                if nxt.mnemonic == 'mov' and ops[0].type == X.X86_OP_REG and \
                        ops[1].type == X.X86_OP_REG and ops[1].reg in holding:
                    holding.add(ops[0].reg)
                elif nxt.mnemonic in ('mov', 'xor', 'lea', 'pop') and ops[0].type == X.X86_OP_REG:
                    holding.discard(ops[0].reg)
                if not holding:
                    break
        return found

    def pointer_fields(self):
        """Offsets of object dwords that are loaded into a register used as a memory base."""
        found = set()
        for index, address in enumerate(self.order):
            insn = self.insns[address]
            ops = insn.operands
            if insn.mnemonic != 'mov' or ops[0].type != X.X86_OP_REG or ops[1].type != X.X86_OP_MEM:
                continue
            mem = ops[1].mem
            if ops[1].size != 4 or not mem.base or mem.base == X.X86_REG_EBP or mem.index or \
                    mem.segment == X.X86_REG_FS:
                continue
            holding = {ops[0].reg}
            for follower in self.order[index + 1:index + 40]:
                nxt = self.insns[follower]
                if nxt.mnemonic in ('ret', 'jmp'):
                    break
                if nxt.mnemonic == 'call':
                    holding -= {X.X86_REG_EAX, X.X86_REG_ECX, X.X86_REG_EDX}
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

    def lift(self):
        addresses = [a for a in self.order if a >= self.body or a in self.skip]
        order = self.order
        for index, address in enumerate(order):
            insn = self.insns[address]
            next_insn = self.insns.get(order[index + 1]) if index + 1 < len(order) else None
            if address < self.body:
                continue
            # pre-mark the add esp that follows a cdecl call before it is visited
            if insn.mnemonic == 'call' and next_insn and next_insn.mnemonic == 'add' and \
                    next_insn.op_str.startswith('esp,'):
                self.skip.add(next_insn.address)
            self.translate(insn, next_insn)
            if insn.mnemonic in ('jmp', 'ret') and index + 1 < len(order):
                following = order[index + 1]
                if following != address + insn.size:
                    pass
        return self.out


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('address')
    parser.add_argument('name')
    parser.add_argument('--args', type=int, default=0, help='stack dwords above the return address')
    parser.add_argument('--locals', type=int, default=0)
    parser.add_argument('--meta', type=Path)
    options = parser.parse_args()
    start = int(options.address, 16)
    lifter = Lifter(start, options.name, options.args, options.locals)
    body = lifter.lift()
    locals_size = options.locals or ((-lifter.min_disp + 0x10 + 3) & ~3)
    header = '''/* Lifted from the original routine at 0x%x by tools/lift.py: every instruction of the original
 * is translated in order (registers, frame, flags and gotos) and every unrecovered callee goes
 * through the call boundary with the registers and stack arguments the original holds there.
 * Verified against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_%s.h"

uint32_t lifted_%s(const VertrixCalls *calls, const VertrixFactoryServices *services,
                   const VertrixGlobals *globals, uint32_t frame, uint32_t eax, uint32_t edx,
                   uint32_t ebx, uint32_t ecx, const uint32_t *arguments, const uint8_t *garbage,
                   uint32_t chain)
{
    uint8_t local[LIFTED_%s_LOCALS + 8 + 4 * %d + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0};
    uint32_t esi = 0;
    uint32_t edi = 0;
    lift_begin(&env, calls, services, globals, frame, local, LIFTED_%s_LOCALS, %d, garbage,
               arguments, chain);
''' % (start, options.name, options.name, options.name.upper(), options.args,
       options.name.upper(), options.args)
    footer = '''}
'''
    text = header + '\n'.join(body) + '\n' + footer
    sys.stdout.write(text)
    header_path = Path(__file__).resolve().parents[1] / 'source' / ('lifted_%s.h' % options.name)
    header_path.write_text('''#ifndef VERTRIX_LIFTED_%s_H
#define VERTRIX_LIFTED_%s_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_%s_LOCALS = %d
};

/* The original routine 0x%x lifted instruction by instruction (see tools/lift.py). `frame` is the
 * token for ebp, eax/edx/ebx/ecx the entry registers, `arguments` the stack dwords above the return
 * address, `garbage` the LIFTED_%s_LOCALS bytes of stack below ebp the routine may read before it
 * writes them and `chain` the value of fs:[0] at entry (the routine returns it). */
uint32_t lifted_%s(const VertrixCalls *calls, const VertrixFactoryServices *services,
                   const VertrixGlobals *globals, uint32_t frame, uint32_t eax, uint32_t edx,
                   uint32_t ebx, uint32_t ecx, const uint32_t *arguments, const uint8_t *garbage,
                   uint32_t chain);
#endif
''' % (options.name.upper(), options.name.upper(), options.name.upper(), locals_size, start,
       options.name.upper(), options.name))
    if options.meta:
        callees = {('0x%x' % k if isinstance(k, int) else 'virtual_%x' % k[1]): v
                   for k, v in lifter.callees.items()}
        options.meta.write_text(json.dumps({'callees': callees, 'locals': locals_size,
                                                'pointer_callees': sorted('0x%x' % t for t in lifter.pointer_callees()),
                                                'pointer_fields': sorted(lifter.pointer_fields())}, indent=1))


if __name__ == '__main__':
    main()
