"""Recompile Vertrix3.exe (or Vertrix 2 v1.2's Vertrix2.exe) into C, function by function.

Every x86 function becomes `void F_<address>(Cpu *c)`. The original's memory is one flat 32-bit
address space (vertrix3/runtime/cpu.h: the image at its preferred base, the stacks, the heaps),
so the generated code keeps the original's stack, return addresses and pointers exactly: a call
pushes the real return address and calls the callee's C function, `ret` pops it and returns.
Registers live in C locals inside a function and in the Cpu across calls. Flags are computed only
where a later instruction reads them (backward liveness over each function's control flow).

Functions are found by recursive descent from the entry, every direct call, every code address
an instruction uses as an immediate (window procedures, thread procedures, exception handlers)
and every code address stored in data (virtual tables, callback tables). Any branch that leaves
a function -- a jump to another entry, falling into one, an indirect jump that is not a resolved
switch -- continues there as a tail call, which the flat stack makes exact. Imports and anything
else outside the recompiled code go through the dispatcher (vertrix3/runtime/dispatch.c).

usage: recomp.py VERTRIX3_EXE OUT_DIR
"""
import argparse
import hashlib
import struct
import sys
from collections import defaultdict
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from capstone import x86_const as X

# The executables this recompiles, by SHA-256: Vertrix 3 (Visual C++ 9) and Vertrix 2 v1.2
# (Watcom; docs/VERTRIX2-V12.md).
# Each with the directory the game is told it runs from.
# Each executable: its name, the game's title, the directory it believes it runs from, its
# archive, and the Wii's application folder (sd:/apps/<folder>, as source/games.c names it).
GAMES = {
    'db625cfe1acb3f5f70d30d041362831ca59ec72b5693e463331cf2f29738f7e9':
        ('Vertrix3.exe', 'Vertrix 3', 'C:\\Vertrix3', 'VERTRIX3.VF', 'vertrix3'),
    '8e27c76d75c28dba6b39f9e9e6162e04b04d712771cb4b03c4d9eb9ef4141999':
        ('Vertrix2.exe', 'Vertrix 2 v1.2', 'C:\\Vertrix2', 'Vertrix2.vf', 'vertrix2-v12'),
}
SEGMENTS = (X.X86_REG_SS, X.X86_REG_CS, X.X86_REG_DS, X.X86_REG_ES, X.X86_REG_FS, X.X86_REG_GS)
PER_FILE = 150

REG32 = {X.X86_REG_EAX: 'eax', X.X86_REG_ECX: 'ecx', X.X86_REG_EDX: 'edx', X.X86_REG_EBX: 'ebx',
         X.X86_REG_ESP: 'esp', X.X86_REG_EBP: 'ebp', X.X86_REG_ESI: 'esi', X.X86_REG_EDI: 'edi'}
REG16 = {X.X86_REG_AX: 'eax', X.X86_REG_CX: 'ecx', X.X86_REG_DX: 'edx', X.X86_REG_BX: 'ebx',
         X.X86_REG_SP: 'esp', X.X86_REG_BP: 'ebp', X.X86_REG_SI: 'esi', X.X86_REG_DI: 'edi'}
REG8L = {X.X86_REG_AL: 'eax', X.X86_REG_CL: 'ecx', X.X86_REG_DL: 'edx', X.X86_REG_BL: 'ebx'}
REG8H = {X.X86_REG_AH: 'eax', X.X86_REG_CH: 'ecx', X.X86_REG_DH: 'edx', X.X86_REG_BH: 'ebx'}
REGS = ('eax', 'ecx', 'edx', 'ebx', 'esp', 'ebp', 'esi', 'edi')

CF, PF, ZF, SF, OF, DF = 1, 2, 4, 8, 16, 32
ALL = CF | PF | ZF | SF | OF
FLAG_NAMES = ((CF, 'cf'), (PF, 'pf'), (ZF, 'zf'), (SF, 'sf'), (OF, 'of'))

# condition -> (flags read, C expression)
CONDITIONS = {
    'o': (OF, 'of'), 'no': (OF, '!of'), 'b': (CF, 'cf'), 'ae': (CF, '!cf'),
    'e': (ZF, 'zf'), 'ne': (ZF, '!zf'), 'be': (CF | ZF, '(cf || zf)'),
    'a': (CF | ZF, '(!cf && !zf)'), 's': (SF, 'sf'), 'ns': (SF, '!sf'), 'p': (PF, 'pf'),
    'np': (PF, '!pf'), 'l': (SF | OF, '(sf != of)'), 'ge': (SF | OF, '(sf == of)'),
    'le': (ZF | SF | OF, '(zf || sf != of)'), 'g': (ZF | SF | OF, '(!zf && sf == of)'),
}
JCC = {'j' + k: k for k in CONDITIONS}
JCC.update({'jnae': 'b', 'jnb': 'ae', 'jz': 'e', 'jnz': 'ne', 'jna': 'be', 'jnbe': 'a',
            'jpe': 'p', 'jpo': 'np', 'jnge': 'l', 'jnl': 'ge', 'jng': 'le', 'jnle': 'g'})
SETCC = {'set' + k: v for k, v in [(j[1:], c) for j, c in JCC.items()]}
CMOVCC = {'cmov' + k: v for k, v in [(j[1:], c) for j, c in JCC.items()]}

STRINGS = {'movsb', 'movsw', 'movsd', 'stosb', 'stosw', 'stosd', 'lodsb', 'lodsw', 'lodsd', 'cmpsb',
           'cmpsw', 'cmpsd', 'scasb', 'scasw', 'scasd'}
MASK = {1: '0xffu', 2: '0xffffu', 4: '0xffffffffu'}
SIGN = {1: '0x80u', 2: '0x8000u', 4: '0x80000000u'}
CTYPE = {1: 'uint8_t', 2: 'uint16_t', 4: 'uint32_t'}
STYPE = {1: 'int8_t', 2: 'int16_t', 4: 'int32_t'}


class Unsupported(Exception):
    pass


class Program:
    def __init__(self, path):
        data = Path(path).read_bytes()
        self.sha256 = hashlib.sha256(data).hexdigest()
        if self.sha256 not in GAMES:
            sys.exit('not an executable this recompiles: %s' % ', '.join(
                '%s (%s)' % (g[0], g[1]) for g in GAMES.values()))
        self.executable, self.game, self.directory, self.archive, self.wii_folder = \
            GAMES[self.sha256]
        self.pe = pefile.PE(data=data)
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        self.image = bytearray(self.pe.get_memory_mapped_image())
        # A section with no file data (Watcom's .bss) is zero-filled by the loader; pefile maps
        # the file's first bytes there instead.
        for section in self.pe.sections:
            if section.PointerToRawData == 0:
                start = section.VirtualAddress
                end = min(len(self.image),
                          start + max(section.Misc_VirtualSize, section.SizeOfRawData))
                self.image[start:end] = bytes(end - start)
        self.image = bytes(self.image)
        self.entry = self.base + self.pe.OPTIONAL_HEADER.AddressOfEntryPoint
        self.sections = [(self.base + s.VirtualAddress,
                          self.base + s.VirtualAddress + max(s.Misc_VirtualSize, s.SizeOfRawData),
                          s.Characteristics) for s in self.pe.sections]
        self.code = [(a, b) for a, b, ch in self.sections if ch & 0x20000000]
        self.iat = {}
        for entry in self.pe.DIRECTORY_ENTRY_IMPORT:
            for imp in entry.imports:
                name = imp.name.decode() if imp.name else '#%d' % imp.ordinal
                self.iat[imp.address] = (entry.dll.decode().upper(), name)
        self.md = Cs(CS_ARCH_X86, CS_MODE_32)
        self.md.detail = True
        self.cache = {}

    def in_code(self, a):
        return any(s <= a < e for s, e in self.code)

    def in_image(self, a):
        return any(s <= a < e for s, e, _ in self.sections)

    def u32(self, a):
        o = a - self.base
        return struct.unpack_from('<I', self.image, o)[0] if 0 <= o <= len(self.image) - 4 else None

    def insn(self, a):
        if a not in self.cache:
            o = a - self.base
            got = next(self.md.disasm(self.image[o:o + 16], a), None) if self.in_code(a) else None
            self.cache[a] = got
        return self.cache[a]


def reg_of(op_reg):
    if op_reg in REG32:
        return REG32[op_reg], 4, 0
    if op_reg in REG16:
        return REG16[op_reg], 2, 0
    if op_reg in REG8L:
        return REG8L[op_reg], 1, 0
    if op_reg in REG8H:
        return REG8H[op_reg], 1, 8
    raise Unsupported('register %d' % op_reg)


class Function:
    """The instructions reachable from an entry without entering another function."""

    def __init__(self, program, entry, entries):
        self.p = program
        self.entry = entry
        self.insns = {}
        self.succ = {}
        self.labels = {entry}
        self.switches = {}
        self.calls = set()
        self.tail = set()
        self.immediates = set()
        self.bad = set()
        work = [entry]
        while work:
            a = work.pop()
            while a not in self.insns:
                if a != entry and a in entries:
                    self.tail.add(a)
                    break
                ins = program.insn(a)
                if ins is None:
                    self.bad.add(a)
                    self.insns[a] = None
                    self.succ[a] = []
                    break
                self.insns[a] = ins
                nxt = a + ins.size
                m = ins.mnemonic
                for op in ins.operands:
                    if op.type == X.X86_OP_IMM and program.in_code(op.imm & 0xffffffff) and m not in (
                            'call', 'jmp') and not m.startswith('j') and not m.startswith('loop'):
                        self.immediates.add(op.imm & 0xffffffff)
                if m in ('call', 'jmp') and ins.operands[0].type == X.X86_OP_MEM:
                    # Through a pointer at a fixed address (`call [0x4fce13]` in Vertrix 2 v1.2's
                    # runtime, unaligned): the function it holds at load is an entry.
                    mem = ins.operands[0].mem
                    if mem.base == 0 and mem.index == 0:
                        v = program.u32(mem.disp & 0xffffffff)
                        if v is not None and program.in_code(v):
                            self.immediates.add(v)
                if m == 'call':
                    op = ins.operands[0]
                    if op.type == X.X86_OP_IMM:
                        self.calls.add(op.imm & 0xffffffff)
                    self.succ[a] = [nxt]
                    a = nxt
                elif m in ('ret', 'retf', 'iretd', 'hlt', 'int3', 'ud2') or m.startswith('repz ret'):
                    self.succ[a] = []
                    break
                elif m == 'jmp':
                    op = ins.operands[0]
                    if op.type == X.X86_OP_IMM:
                        t = op.imm & 0xffffffff
                        if t in entries and t != entry:
                            self.tail.add(t)
                            self.succ[a] = []
                        else:
                            self.succ[a] = [t]
                            self.labels.add(t)
                            work.append(t)
                    else:
                        targets = self.switch(a, ins)
                        self.succ[a] = sorted(set(targets))
                        for t in targets:
                            self.labels.add(t)
                            work.append(t)
                    break
                elif m in JCC or m in ('jecxz', 'jcxz', 'loop', 'loope', 'loopne'):
                    t = ins.operands[0].imm & 0xffffffff
                    self.succ[a] = [nxt, t]
                    if t in entries and t != entry:
                        self.tail.add(t)
                    else:
                        self.labels.add(t)
                        work.append(t)
                    a = nxt
                else:
                    self.succ[a] = [nxt]
                    a = nxt
            else:
                continue

    def previous(self, a):
        """The instruction that ends at `a`, or None: one this function decoded on its way
        there, else the shortest that decodes to end there."""
        for size in range(1, 16):
            known = self.insns.get(a - size)
            if known is not None and known.address + known.size == a:
                return known
        for size in range(1, 16):
            cand = self.p.insn(a - size)
            if cand is not None and cand.address + cand.size == a:
                return cand
        return None

    def shifted_switch(self, a, op):
        """`shl reg, 2; jmp [reg + table]` (Vertrix 2 v1.2), the index shifted before the jump and
        its bound checked earlier by `cmp <index>, n; ja`, often on the index's stack slot."""
        table = op.mem.disp & 0xffffffff
        if not self.p.in_image(table):
            return []
        base = REG32.get(op.mem.base)
        shifted = False
        bound = None
        back = a
        for _ in range(8):
            prev = self.previous(back)
            if prev is None:
                break
            back = prev.address
            ops = prev.operands
            if not shifted:
                if prev.mnemonic == 'shl' and ops[0].type == X.X86_OP_REG and \
                        REG32.get(ops[0].reg) == base and ops[1].type == X.X86_OP_IMM and ops[1].imm == 2:
                    shifted = True
                continue
            if prev.mnemonic == 'cmp' and ops[1].type == X.X86_OP_IMM:
                bound = (ops[1].imm & 0xffffffff) + 1
                break
        if not shifted:
            return []
        targets = []
        for n in range(bound if bound is not None and bound <= 256 else 256):
            v = self.p.u32(table + 4 * n)
            if v is None or not self.p.in_code(v):
                break
            targets.append(v)
        self.switches[a] = (table, targets)
        return targets

    def switch(self, a, ins):
        """`jmp [table + reg*4]`: the table's entries, bounded by a preceding `cmp reg, n; ja`."""
        op = ins.operands[0]
        if op.type == X.X86_OP_MEM and op.mem.base != 0 and op.mem.index == 0:
            return self.shifted_switch(a, op)
        if op.type != X.X86_OP_MEM or op.mem.base != 0 or op.mem.index == 0 or op.mem.scale != 4:
            return []
        table = op.mem.disp & 0xffffffff
        bound = None
        index = op.mem.index
        # Look back a few instructions for the bound check.
        back = a
        for _ in range(12):
            prev = None
            for size in range(1, 16):
                cand = self.p.insn(back - size)
                if cand is not None and cand.address + cand.size == back:
                    prev = cand
                    break
            if prev is None:
                break
            back = prev.address
            if prev.mnemonic == 'cmp' and prev.operands[1].type == X.X86_OP_IMM and \
                    prev.operands[0].type == X.X86_OP_REG and \
                    reg_of(prev.operands[0].reg)[0] == REG32.get(index):
                bound = (prev.operands[1].imm & 0xffffffff) + 1
                break
            if prev.mnemonic == 'and' and prev.operands[1].type == X.X86_OP_IMM and \
                    prev.operands[0].type == X.X86_OP_REG and \
                    reg_of(prev.operands[0].reg)[0] == REG32.get(index):
                bound = (prev.operands[1].imm & 0xffffffff) + 1
                break
            # The index register written by something else: no bound to find.
            if any(op.type == X.X86_OP_REG and op.access & 2 and op.reg in REG32 and REG32[op.reg] == REG32.get(index)
                   for op in prev.operands) and prev.mnemonic not in ('cmp', 'test'):
                break
        # Entries the index never reaches may overlap other bytes (the runtime's memcpy indexes
        # one table from 1): skip a few leading entries that are not code addresses.
        targets = []
        n = 0
        while (bound is None or n < bound) and n <= 256:
            v = self.p.u32(table + 4 * n)
            if v is None or not self.p.in_code(v):
                if targets or n >= 4:
                    break
            else:
                targets.append(v)
            n += 1
        # memcpy also indexes with negative registers (`jmp [ecx*4 + table]`, ecx down to -7): take
        # the code addresses just below the table too.
        for k in range(1, 9):
            v = self.p.u32(table - 4 * k)
            if v is None or not self.p.in_code(v):
                break
            targets.append(v)
        self.switches[a] = (table, targets)
        return targets


def idle(ins):
    """An instruction that changes nothing: nop, `mov r, r`, `xchg r, r` or `lea r, [r + 0]`."""
    ops = ins.operands
    if ins.mnemonic == 'nop':
        return True
    if ins.mnemonic in ('mov', 'xchg') and len(ops) == 2 and ops[0].type == ops[1].type == X.X86_OP_REG:
        return ops[0].reg == ops[1].reg
    if ins.mnemonic == 'lea' and ops[1].type == X.X86_OP_MEM:
        m = ops[1].mem
        return m.base == ops[0].reg and m.index == 0 and m.disp == 0 and m.segment == 0
    return False


def filler_before(p, v):
    """Whether the bytes just before `v` are padding Watcom fills with idle instructions: some
    run of them that ends exactly at `v`, up to 15 bytes long."""
    for k in range(2, 16):
        a = v - k
        while a < v:
            ins = p.insn(a)
            if ins is None or not idle(ins):
                break
            a += ins.size
        if a == v:
            return True
    return False


def plausible_entry(p, slot, v):
    """A code address stored in data starts a function when it follows padding or a return,
    or when it sits in a table of code addresses (a virtual table)."""
    before = p.image[v - p.base - 1] if v > p.base else 0
    if before in (0xcc, 0x90, 0xc3):
        return True
    if p.image[v - p.base - 3] == 0xc2:  # ret n
        return True
    # Watcom 2.18 as Vertrix 2 v1.2 was linked pads between functions with zeros: an aligned
    # address after a return and up to 15 zero bytes.
    if before == 0 and v % 16 == 0:
        k = v - p.base - 1
        while k > v - p.base - 16 and p.image[k] == 0:
            k -= 1
        if p.image[k] == 0xc3 or 0xc2 in (p.image[k - 1], p.image[k - 2]):
            return True
    # ... or with instructions that do nothing (`mov eax, eax`, `lea edx, [edx + 0]`, nop).
    if v % 16 == 0 and filler_before(p, v):
        return True
    for neighbour in (slot - 4, slot + 4):
        w = p.u32(neighbour)
        if w is not None and p.in_code(w):
            return True
    return False


def initializer_routines(p):
    """Watcom's start-up and exit tables (XI/YI): 6-byte records of a zero type byte, a priority
    byte and a routine's address, at any alignment, which the runtime calls through. Taken from
    runs of three or more records that all point into code."""
    found = set()
    for s, e, ch in p.sections:
        if ch & 0x20000000:
            continue
        data = p.image[s - p.base:e - p.base]
        for start in range(0, len(data) - 18):
            run = []
            at = start
            while at + 6 <= len(data) and data[at] == 0:
                v = struct.unpack_from('<I', data, at + 2)[0]
                if not p.in_code(v):
                    break
                run.append(v)
                at += 6
            if len(run) >= 3:
                found.update(run)
    return found


def discover(p):
    entries = {p.entry} | {v for v in initializer_routines(p) if p.insn(v) is not None}
    seeds = sorted(entries)
    funcs = {}
    switch_tables = set()
    while True:
        while seeds:
            e = seeds.pop()
            if e in funcs:
                continue
            f = Function(p, e, entries)
            funcs[e] = f
            for t in f.calls | f.immediates | f.tail:
                if t not in entries:
                    entries.add(t)
                    seeds.append(t)
            for table, targets in f.switches.values():
                switch_tables.update(range(table, table + 4 * len(targets)))
        # Code addresses stored in data, outside switch tables.
        added = False
        for s, e, ch in p.sections:
            if ch & 0x20000000:
                continue
            for a in range(s, e - 3, 4):
                if a in switch_tables:
                    continue
                v = p.u32(a)
                if v is not None and p.in_code(v) and v not in entries and p.insn(v) is not None \
                        and plausible_entry(p, a, v):
                    entries.add(v)
                    seeds.append(v)
                    added = True
        if not added:
            break
    # A new entry splits functions found before it: rebuild all against the final set.
    while True:
        funcs = {e: Function(p, e, entries) for e in sorted(entries)}
        extra = set()
        for f in funcs.values():
            extra |= (f.calls | f.immediates | f.tail) - entries
        if not extra:
            return funcs, entries
        entries |= extra


# ----------------------------------------------------------------------------------------------
# Flags: what each instruction reads and writes.

ARITH_ALL = {'add', 'sub', 'cmp', 'neg', 'adc', 'sbb', 'and', 'or', 'xor', 'test', 'imul', 'mul',
             'shl', 'sal', 'shr', 'sar', 'cmpsb', 'cmpsw', 'cmpsd', 'scasb', 'scasw', 'scasd',
             'repe cmpsb', 'repe cmpsd', 'repne scasb', 'repne scasd', 'repe scasb', 'bsf', 'bsr',
             'rol', 'ror', 'rcl', 'rcr', 'bt', 'bts', 'btr', 'btc', 'shld', 'shrd', 'xadd',
             'cmpxchg', 'popfd', 'sahf', 'div', 'idiv', 'aaa', 'aas', 'daa', 'das', 'aam', 'aad',
             'fcomi', 'fcomip', 'fucomi', 'fucomip', 'comiss', 'comisd', 'ucomiss', 'ucomisd',
             'stc', 'clc', 'cmc'}


STRING_OPCODES = {0xa4, 0xa5, 0xa6, 0xa7, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf}


def mnemonic_of(ins):
    """The mnemonic with a string instruction's repeat prefix, which Capstone drops from
    `repne movsd` (f2 a5, as Watcom's memcpy writes it), even from its prefix list: f2 repeats
    movs, stos and lods as f3 does, and cmps and scas while unequal. A string instruction's
    opcode is its last byte, after its prefixes."""
    m = ins.mnemonic
    raw = bytes(ins.bytes)
    if raw[-1] in STRING_OPCODES and ' ' not in m:
        if 0xf3 in raw[:-1]:
            return ('repe ' if m[:4] in ('cmps', 'scas') else 'rep ') + m
        if 0xf2 in raw[:-1]:
            return ('repne ' if m[:4] in ('cmps', 'scas') else 'rep ') + m
    return m

def flag_effect(ins):
    """(read, written) flag masks."""
    m = mnemonic_of(ins)
    for prefix in ('rep ', 'repe ', 'repne ', 'repz ', 'repnz '):
        if m.startswith(prefix):
            base = m[len(prefix):]
            return (ALL, ALL) if base[:4] in ('cmps', 'scas') else (0, 0)
    if m in JCC:
        return CONDITIONS[JCC[m]][0], 0
    if m in SETCC:
        return CONDITIONS[SETCC[m]][0], 0
    if m in CMOVCC:
        return CONDITIONS[CMOVCC[m]][0], 0
    if m in ('adc', 'sbb', 'rcl', 'rcr', 'cmc'):
        return CF, ALL
    if m in ('inc', 'dec'):
        return 0, ALL & ~CF
    if m in ('lahf', 'pushfd', 'pushf'):
        return ALL, 0
    if m in ('loope', 'loopne'):
        return ZF, 0
    if m in ('shl', 'sal', 'shr', 'sar', 'rol', 'ror'):
        # A count of zero leaves the flags: unless the count is a nonzero immediate, they pass.
        cnt = ins.operands[1] if len(ins.operands) > 1 else None
        if cnt is not None and cnt.type == X.X86_OP_IMM and cnt.imm & 31:
            return 0, ALL if m not in ('rol', 'ror') else CF | OF
        return ALL, ALL
    if m in ('shld', 'shrd'):
        return ALL, ALL
    if m in ARITH_ALL:
        return 0, ALL
    if m == 'call':
        return 0, ALL
    return 0, 0


# ----------------------------------------------------------------------------------------------
# Code generation.

class Gen:
    def __init__(self, p, f, entries, flag_returners, flag_readers=frozenset()):
        self.p = p
        self.f = f
        self.entries = entries
        self.out = []
        self.flag_returners = flag_returners
        self.flag_readers = flag_readers  # functions that read flags their caller set
        self.live_after = {}

    # -- liveness ------------------------------------------------------------------------------
    def liveness(self):
        f = self.f
        order = sorted(a for a in f.insns if f.insns[a] is not None)
        effect = {a: flag_effect(f.insns[a]) for a in order}
        live_in = {a: 0 for a in order}
        exit_live = ALL if f.entry in self.flag_returners else 0
        changed = True
        while changed:
            changed = False
            for a in reversed(order):
                ins = f.insns[a]
                out = 0
                succs = f.succ.get(a, [])
                # Leaving by `ret` hands the caller only what a flag-returning function
                # returns; any other way out (a tail call, falling into the next function, an
                # indirect jump) continues the same instruction stream, so every flag lives.
                if ins.mnemonic in ('ret', 'repz ret'):
                    out |= exit_live
                elif not succs and ins.mnemonic not in ('int3', 'hlt', 'ud2'):
                    out |= ALL
                if a + ins.size in f.tail and ins.mnemonic not in ('ret', 'jmp', 'repz ret'):
                    out |= ALL
                for s in succs:
                    if s in live_in:
                        out |= live_in[s]
                    else:
                        out |= ALL
                if ins.mnemonic == 'jmp' and ins.operands[0].type != X.X86_OP_IMM:
                    out |= ALL
                if ins.mnemonic in JCC and (ins.operands[0].imm & 0xffffffff) in f.tail:
                    out |= ALL
                if ins.mnemonic == 'call':
                    target = ins.operands[0].imm & 0xffffffff if ins.operands[0].type == X.X86_OP_IMM else None
                    # The call sets every flag; a callee that reads its caller's flags reads them all.
                    self.live_after[a] = out
                    new = ALL if target in self.flag_readers else 0
                else:
                    r, w = effect[a]
                    self.live_after[a] = out
                    new = (out & ~w) | r
                if new != live_in[a]:
                    live_in[a] = new
                    changed = True
        self.live_in = live_in

    # -- operands -------------------------------------------------------------------------------
    def addr(self, op):
        mem = op.mem
        parts = []
        if mem.base != 0:
            parts.append(REG32[mem.base] if mem.base in REG32 else self.unsupported('base'))
        if mem.index != 0:
            r = REG32[mem.index]
            parts.append('%s * %d' % (r, mem.scale) if mem.scale != 1 else r)
        if mem.disp or not parts:
            parts.append('0x%xu' % (mem.disp & 0xffffffff))
        expr = ' + '.join(parts)
        if mem.segment == X.X86_REG_FS:
            expr = 'c->fs_base + ' + expr
        elif mem.segment not in (0, X.X86_REG_DS, X.X86_REG_SS, X.X86_REG_ES, X.X86_REG_CS):
            self.unsupported('segment')
        return '(uint32_t)(%s)' % expr

    def unsupported(self, why):
        raise Unsupported(why)

    def read(self, op, size=None):
        size = size or op.size
        if op.type == X.X86_OP_REG:
            r, s, shift = reg_of(op.reg)
            if s == 4:
                return r
            if shift:
                return '((%s >> 8) & 0xffu)' % r
            return '(%s & %s)' % (r, MASK[s])
        if op.type == X.X86_OP_IMM:
            return '0x%xu' % (op.imm & int(MASK[size][:-1], 16))
        if op.type == X.X86_OP_MEM:
            return 'R%d(%s)' % (8 * size, self.addr(op))
        self.unsupported('operand')

    def write(self, op, value):
        if op.type == X.X86_OP_REG:
            r, s, shift = reg_of(op.reg)
            if s == 4:
                return '%s = %s;' % (r, value)
            if shift:
                return '%s = (%s & 0xffff00ffu) | (((uint32_t)(%s) & 0xffu) << 8);' % (r, r, value)
            return '%s = (%s & ~%s) | ((uint32_t)(%s) & %s);' % (r, r, MASK[s], value, MASK[s])
        if op.type == X.X86_OP_MEM:
            return 'W%d(%s, %s);' % (8 * op.size, self.addr(op), value)
        self.unsupported('destination')

    def sign(self, expr, size):
        return '(int32_t)(%s)%s' % (STYPE[size], expr)

    # -- flags ----------------------------------------------------------------------------------
    def zsp(self, live, r, size, lines):
        if live & ZF:
            lines.append('zf = (%s & %s) == 0;' % (r, MASK[size]))
        if live & SF:
            lines.append('sf = (%s & %s) != 0;' % (r, SIGN[size]))
        if live & PF:
            lines.append('pf = PARITY(%s);' % r)

    # -- whole function -----------------------------------------------------------------------
    def emit(self):
        f = self.f
        self.liveness()
        name = 'F_%x' % f.entry
        o = self.out
        o.append('void %s(Cpu *c)' % name)
        o.append('{')
        o.append('    uint32_t eax = c->eax, ecx = c->ecx, edx = c->edx, ebx = c->ebx;')
        o.append('    uint32_t esp = c->esp, ebp = c->ebp, esi = c->esi, edi = c->edi;')
        o.append('    uint32_t cf = c->cf, pf = c->pf, zf = c->zf, sf = c->sf, of = c->of;')
        o.append('    uint32_t t0, t1, t2;')
        o.append('    uint64_t q;')
        o.append('    (void)t0; (void)t1; (void)t2; (void)q;')
        o.append('    HISTORY(0x%xu);' % f.entry)
        if f.entry not in f.insns or f.insns[f.entry] is None:
            o.append('    UNDECODED(0x%xu);' % f.entry)
            o.append('}')
            return '\n'.join(o)
        order = sorted(f.insns)
        if order[0] != f.entry:
            # Blocks below the entry (reached by jumping backwards) come first in address order.
            o.append('    goto L_%x;' % f.entry)
        jumped = set(f.labels)
        for a in order:
            ins = f.insns[a]
            if ins is None:
                continue
            for s in f.succ.get(a, []):
                jumped.add(s)
        previous_end = None
        for a in order:
            ins = f.insns[a]
            if a in jumped or previous_end != a:
                o.append('L_%x:' % a)
            if ins is None:
                o.append('    UNDECODED(0x%xu);' % a)
                previous_end = None
                continue
            try:
                lines = self.insn(ins)
            except Unsupported as e:
                lines = ['UNSUPPORTED(0x%xu, "%s %s");' % (a, ins.mnemonic, ins.op_str.replace('"', ''))]
            o.append('    /* %x: %s %s */' % (a, ins.mnemonic, ins.op_str))
            for line in lines:
                o.append('    ' + line)
            end = a + ins.size
            succ = f.succ.get(a, [])
            terminal = ins.mnemonic in ('ret', 'jmp', 'hlt', 'int3', 'ud2', 'retf', 'iretd') or (
                not succ and ins.mnemonic != 'call')
            if not terminal and end not in f.insns:
                # Falls into another function (or past the end of what was decoded).
                o.append('    ' + self.tail_to(end))
            previous_end = end if not terminal else None
        o.append('}')
        return '\n'.join(o)

    def sync_out(self, flags=True):
        s = 'c->eax = eax; c->ecx = ecx; c->edx = edx; c->ebx = ebx; c->esp = esp; ' \
            'c->ebp = ebp; c->esi = esi; c->edi = edi;'
        if flags:
            s += ' c->cf = cf; c->pf = pf; c->zf = zf; c->sf = sf; c->of = of;'
        return s

    def sync_in(self, flags):
        s = 'eax = c->eax; ecx = c->ecx; edx = c->edx; ebx = c->ebx; esp = c->esp; ' \
            'ebp = c->ebp; esi = c->esi; edi = c->edi;'
        if flags:
            s += ' cf = c->cf; pf = c->pf; zf = c->zf; sf = c->sf; of = c->of;'
        return s

    def tail_to(self, target):
        if target in self.entries:
            return '%s F_%x(c); return;' % (self.sync_out(), target)
        return '%s JUMP(c, 0x%xu); return;' % (self.sync_out(), target)

    def goto(self, target):
        if target in self.f.insns:
            return 'goto L_%x;' % target
        return self.tail_to(target)

    def insn(self, ins):
        m = mnemonic_of(ins)
        ops = ins.operands
        a = ins.address
        live = self.live_after.get(a, ALL)
        L = []
        size = ops[0].size if ops else 4

        if m == 'nop' or m in ('wait', 'fwait', 'prefetchw', 'prefetchnta', 'prefetcht0', 'cld') and m != 'cld':
            return ['/* nop */']
        if m == 'cld':
            return ['c->df = 0;']
        if m == 'std':
            return ['c->df = 1;']
        if m in ('mov', 'movsx', 'movzx', 'movsxd'):
            src = ops[1]
            if src.type == X.X86_OP_REG and src.reg in (X.X86_REG_SS, X.X86_REG_CS, X.X86_REG_DS,
                                                        X.X86_REG_ES, X.X86_REG_FS, X.X86_REG_GS):
                v = {X.X86_REG_FS: '0x3bu', X.X86_REG_CS: '0x1bu'}.get(src.reg, '0x23u')
                return [self.write(ops[0], v)]
            if ops[0].type == X.X86_OP_REG and ops[0].reg in (X.X86_REG_SS, X.X86_REG_DS, X.X86_REG_ES,
                                                               X.X86_REG_FS, X.X86_REG_GS):
                return ['/* segment load ignored */']
            v = self.read(src)
            if m == 'movsx':
                v = '(uint32_t)%s' % self.sign(v, src.size)
            return [self.write(ops[0], v)]
        if m == 'lea':
            return [self.write(ops[0], self.addr(ops[1]).replace('c->fs_base + ', ''))]
        if m == 'xchg':
            if ops[0].type == X.X86_OP_REG and ops[1].type == X.X86_OP_REG and ops[0].reg == ops[1].reg:
                return ['/* nop */']
            return ['t0 = %s;' % self.read(ops[0]), 't1 = %s;' % self.read(ops[1]),
                    self.write(ops[0], 't1'), self.write(ops[1], 't0')]
        if m == 'push' and ops[0].type == X.X86_OP_REG and ops[0].reg in SEGMENTS:
            # A flat process's selectors (Watcom's runtime saves es around string moves).
            v = {X.X86_REG_FS: '0x3bu', X.X86_REG_CS: '0x1bu'}.get(ops[0].reg, '0x23u')
            return ['esp -= 4;', 'W32(esp, %s);' % v]
        if m == 'pop' and ops[0].type == X.X86_OP_REG and ops[0].reg in SEGMENTS:
            return ['esp += 4; /* segment load ignored */']
        if m == 'push':
            v = self.read(ops[0], 4) if ops[0].type != X.X86_OP_IMM else '0x%xu' % (ops[0].imm & 0xffffffff)
            if ops[0].size == 2:
                return ['t0 = %s;' % v, 'esp -= 2;', 'W16(esp, t0);']
            return ['t0 = %s;' % v, 'esp -= 4;', 'W32(esp, t0);']
        if m == 'pop':
            if ops[0].size == 2:  # pop ax (Watcom's FPU set-up saves ax with a 16-bit push)
                return ['t0 = R16(esp);', 'esp += 2;', self.write(ops[0], 't0')]
            return ['t0 = R32(esp);', 'esp += 4;', self.write(ops[0], 't0')]
        if m in ('pushal', 'pushad'):
            return ['t0 = esp;'] + ['esp -= 4; W32(esp, %s);' % r for r in
                                    ('eax', 'ecx', 'edx', 'ebx', 't0', 'ebp', 'esi', 'edi')]
        if m in ('popal', 'popad'):
            return ['edi = R32(esp); esi = R32(esp + 4); ebp = R32(esp + 8); ebx = R32(esp + 16); '
                    'edx = R32(esp + 20); ecx = R32(esp + 24); eax = R32(esp + 28); esp += 32;']
        if m in ('pushfd', 'pushf'):
            return ['esp -= 4;', 'W32(esp, FLAGS_PACK());']
        if m in ('popfd', 'popf'):
            return ['t0 = R32(esp);', 'esp += 4;', 'FLAGS_UNPACK(t0);']
        if m == 'lahf':
            return ['eax = (eax & 0xffff00ffu) | ((FLAGS_PACK() & 0xffu) << 8);']
        if m == 'sahf':
            return ['t0 = (eax >> 8) & 0xffu;', 'cf = t0 & 1; pf = (t0 >> 2) & 1; zf = (t0 >> 6) & 1; sf = (t0 >> 7) & 1;']
        if m == 'leave':
            return ['esp = ebp;', 'ebp = R32(esp);', 'esp += 4;']
        if m == 'enter':
            if ops[1].imm != 0:
                self.unsupported('enter nesting')
            return ['esp -= 4; W32(esp, ebp);', 'ebp = esp;', 'esp -= 0x%xu;' % (ops[0].imm & 0xffff)]

        if m in ('add', 'sub', 'cmp', 'adc', 'sbb'):
            s = size
            d = self.read(ops[0])
            v = self.read(ops[1], s) if ops[1].type != X.X86_OP_IMM else '0x%xu' % (ops[1].imm & int(MASK[s][:-1], 16))
            L.append('t0 = %s;' % d)
            L.append('t1 = %s;' % v)
            carry_in = ' + cf' if m == 'adc' else (' - cf' if m == 'sbb' else '')
            op = '+' if m in ('add', 'adc') else '-'
            L.append('t2 = (t0 %s t1%s) & %s;' % (op, carry_in, MASK[s]))
            if live & CF:
                if m == 'add':
                    L.append('cf = t2 < t0;')
                elif m == 'adc':
                    L.append('cf = (uint64_t)t0 + t1 + cf > %s;' % MASK[s])
                elif m == 'sbb':
                    L.append('cf = (uint64_t)t0 < (uint64_t)t1 + cf;')
                else:
                    L.append('cf = t0 < t1;')
            if live & OF:
                if op == '+':
                    L.append('of = (((t0 ^ t2) & (t1 ^ t2)) & %s) != 0;' % SIGN[s])
                else:
                    L.append('of = (((t0 ^ t1) & (t0 ^ t2)) & %s) != 0;' % SIGN[s])
            self.zsp(live, 't2', s, L)
            if m != 'cmp':
                L.append(self.write(ops[0], 't2'))
            return L
        if m in ('and', 'or', 'xor', 'test'):
            s = size
            cop = {'and': '&', 'test': '&', 'or': '|', 'xor': '^'}[m]
            if m == 'xor' and ops[0].type == X.X86_OP_REG and ops[1].type == X.X86_OP_REG and ops[0].reg == ops[1].reg:
                L.append(self.write(ops[0], '0'))
                L.append('t2 = 0;')
            else:
                v = self.read(ops[1], s) if ops[1].type != X.X86_OP_IMM else '0x%xu' % (ops[1].imm & int(MASK[s][:-1], 16))
                L.append('t2 = (%s %s %s) & %s;' % (self.read(ops[0]), cop, v, MASK[s]))
                if m != 'test':
                    L.append(self.write(ops[0], 't2'))
            if live & CF:
                L.append('cf = 0;')
            if live & OF:
                L.append('of = 0;')
            self.zsp(live, 't2', s, L)
            return L
        if m in ('inc', 'dec'):
            s = size
            L.append('t0 = %s;' % self.read(ops[0]))
            L.append('t2 = (t0 %s 1) & %s;' % ('+' if m == 'inc' else '-', MASK[s]))
            if live & OF:
                L.append('of = t2 == %s;' % (SIGN[s] if m == 'inc' else '(%s - 1)' % SIGN[s]))
            self.zsp(live, 't2', s, L)
            L.append(self.write(ops[0], 't2'))
            return L
        if m == 'neg':
            s = size
            L.append('t0 = %s;' % self.read(ops[0]))
            L.append('t2 = (0u - t0) & %s;' % MASK[s])
            if live & CF:
                L.append('cf = t0 != 0;')
            if live & OF:
                L.append('of = t0 == %s;' % SIGN[s])
            self.zsp(live, 't2', s, L)
            L.append(self.write(ops[0], 't2'))
            return L
        if m == 'not':
            return [self.write(ops[0], '~%s' % self.read(ops[0]))]
        if m in ('shl', 'sal', 'shr', 'sar', 'rol', 'ror', 'rcl', 'rcr'):
            s = size
            if len(ops) == 1:
                cnt = '1u'
            else:
                cnt = self.read(ops[1], 1) if ops[1].type != X.X86_OP_IMM else '0x%xu' % (ops[1].imm & 0xff)
            L.append('t1 = %s & 31u;' % cnt)
            L.append('t0 = %s;' % self.read(ops[0]))
            L.append('if (t1 != 0) {')
            bits = 8 * s
            if m in ('shl', 'sal'):
                L.append('    t2 = (t0 << t1) & %s;' % MASK[s])
                if live & CF:
                    L.append('    cf = t1 <= %d ? (t0 >> (%d - t1)) & 1u : 0u;' % (bits, bits))
                if live & OF:
                    L.append('    of = ((t2 & %s) != 0) != cf;' % SIGN[s] if live & CF else
                             '    of = ((t2 & %s) != 0) != (t1 <= %d ? (t0 >> (%d - t1)) & 1u : 0u);' % (SIGN[s], bits, bits))
            elif m == 'shr':
                L.append('    t2 = t1 < 32 ? (t0 >> t1) : 0u;')
                if live & CF:
                    L.append('    cf = (t0 >> (t1 - 1)) & 1u;')
                if live & OF:
                    L.append('    of = (t0 & %s) != 0;' % SIGN[s])
            elif m == 'sar':
                L.append('    t2 = (uint32_t)(%s >> (t1 < %d ? t1 : %d)) & %s;' % (self.sign('t0', s), bits, bits - 1, MASK[s]))
                if live & CF:
                    L.append('    cf = ((uint32_t)(%s >> (t1 - 1 < %d ? t1 - 1 : %d))) & 1u;' % (self.sign('t0', s), bits, bits - 1))
                if live & OF:
                    L.append('    of = 0;')
            elif m in ('rol', 'ror'):
                L.append('    t1 %%= %d;' % bits)
                if m == 'rol':
                    L.append('    t2 = t1 ? ((t0 << t1) | (t0 >> (%d - t1))) & %s : t0;' % (bits, MASK[s]))
                    if live & CF:
                        L.append('    cf = t2 & 1u;')
                    if live & OF:
                        L.append('    of = ((t2 & %s) != 0) != (t2 & 1u);' % SIGN[s])
                else:
                    L.append('    t2 = t1 ? ((t0 >> t1) | (t0 << (%d - t1))) & %s : t0;' % (bits, MASK[s]))
                    if live & CF:
                        L.append('    cf = (t2 & %s) != 0;' % SIGN[s])
                    if live & OF:
                        L.append('    of = (((t2 << 1) ^ t2) & %s) != 0;' % SIGN[s])
            else:  # rcl, rcr: bit by bit
                L.append('    t1 %%= %d;' % (bits + 1))
                L.append('    t2 = t0;')
                L.append('    while (t1--) {')
                if m == 'rcl':
                    L.append('        q = (t2 & %s) != 0; t2 = ((t2 << 1) | cf) & %s; cf = (uint32_t)q;' % (SIGN[s], MASK[s]))
                else:
                    L.append('        q = t2 & 1u; t2 = (t2 >> 1) | (cf ? %s : 0u); cf = (uint32_t)q;' % SIGN[s])
                L.append('    }')
            if m not in ('rol', 'ror', 'rcl', 'rcr'):
                self.zsp(live, 't2', s, L_ind := [])
                L.extend('    ' + x for x in L_ind)
            L.append('    ' + self.write(ops[0], 't2'))
            L.append('}')
            return L
        if m in ('shld', 'shrd'):
            s = size
            if s != 4:
                self.unsupported('16-bit double shift')
            cnt = self.read(ops[2], 1) if ops[2].type != X.X86_OP_IMM else '0x%xu' % (ops[2].imm & 0xff)
            L.append('t1 = %s & 31u;' % cnt)
            L.append('t0 = %s;' % self.read(ops[0]))
            L.append('if (t1 != 0) {')
            if m == 'shld':
                L.append('    t2 = (t0 << t1) | (%s >> (32 - t1));' % self.read(ops[1]))
                L.append('    cf = (t0 >> (32 - t1)) & 1u;')
            else:
                L.append('    t2 = (t0 >> t1) | (%s << (32 - t1));' % self.read(ops[1]))
                L.append('    cf = (t0 >> (t1 - 1)) & 1u;')
            L.append('    zf = t2 == 0; sf = t2 >> 31; pf = PARITY(t2); of = 0;')
            L.append('    ' + self.write(ops[0], 't2'))
            L.append('}')
            return L
        if m in ('mul', 'imul') and len(ops) == 1:
            s = size
            v = self.read(ops[0])
            if s == 4:
                if m == 'mul':
                    L.append('q = (uint64_t)eax * (uint64_t)%s;' % v)
                    L.append('eax = (uint32_t)q; edx = (uint32_t)(q >> 32);')
                    L.append('cf = of = edx != 0;')
                else:
                    L.append('q = (uint64_t)((int64_t)(int32_t)eax * (int64_t)(int32_t)%s);' % v)
                    L.append('eax = (uint32_t)q; edx = (uint32_t)(q >> 32);')
                    L.append('cf = of = (int64_t)q != (int64_t)(int32_t)eax;')
            elif s == 1:
                if m == 'mul':
                    L.append('t2 = (eax & 0xffu) * %s;' % v)
                    L.append('cf = of = (t2 >> 8) != 0;')
                else:
                    L.append('t2 = (uint32_t)((int32_t)(int8_t)eax * %s) & 0xffffu;' % self.sign(v, 1))
                    L.append('cf = of = (int32_t)(int16_t)t2 != (int32_t)(int8_t)t2;')
                L.append('eax = (eax & 0xffff0000u) | (t2 & 0xffffu);')
            else:
                if m == 'mul':
                    L.append('t2 = (eax & 0xffffu) * %s;' % v)
                else:
                    L.append('t2 = (uint32_t)((int32_t)(int16_t)eax * %s);' % self.sign(v, 2))
                L.append('eax = (eax & 0xffff0000u) | (t2 & 0xffffu); edx = (edx & 0xffff0000u) | (t2 >> 16);')
                L.append('cf = of = %s;' % ('(t2 >> 16) != 0' if m == 'mul' else '(int32_t)t2 != (int32_t)(int16_t)t2'))
            return L
        if m == 'imul':
            s = size
            if len(ops) == 2:
                a1, a2 = self.read(ops[0]), self.read(ops[1])
            else:
                a1, a2 = self.read(ops[1]), '0x%xu' % (ops[2].imm & 0xffffffff)
            L.append('q = (uint64_t)((int64_t)%s * (int64_t)%s);' % (self.sign(a1, s), self.sign(a2, s)))
            L.append('t2 = (uint32_t)q & %s;' % MASK[s])
            L.append('cf = of = (int64_t)q != (int64_t)%s;' % self.sign('t2', s))
            L.append(self.write(ops[0], 't2'))
            return L
        if m in ('div', 'idiv'):
            s = size
            v = self.read(ops[0])
            L.append('t1 = %s;' % v)
            L.append('if ((t1 & %s) == 0) DIVIDE_ERROR(0x%xu);' % (MASK[s], a))
            if s == 4:
                if m == 'div':
                    L.append('q = ((uint64_t)edx << 32) | eax;')
                    L.append('eax = (uint32_t)(q / t1); edx = (uint32_t)(q % t1);')
                else:
                    L.append('q = ((uint64_t)edx << 32) | eax;')
                    L.append('{ int64_t n = (int64_t)q, d = (int32_t)t1; eax = (uint32_t)(n / d); edx = (uint32_t)(n % d); }')
            elif s == 2:
                if m == 'div':
                    L.append('t0 = ((edx & 0xffffu) << 16) | (eax & 0xffffu);')
                    L.append('t2 = t0 / (t1 & 0xffffu); t0 = t0 % (t1 & 0xffffu);')
                else:
                    L.append('{ int32_t n = (int32_t)(((edx & 0xffffu) << 16) | (eax & 0xffffu)), d = (int16_t)t1; t2 = (uint32_t)(n / d); t0 = (uint32_t)(n % d); }')
                L.append('eax = (eax & 0xffff0000u) | (t2 & 0xffffu); edx = (edx & 0xffff0000u) | (t0 & 0xffffu);')
            else:
                if m == 'div':
                    L.append('t0 = eax & 0xffffu; t2 = t0 / (t1 & 0xffu); t0 = t0 % (t1 & 0xffu);')
                else:
                    L.append('{ int32_t n = (int16_t)eax, d = (int8_t)t1; t2 = (uint32_t)(n / d); t0 = (uint32_t)(n % d); }')
                L.append('eax = (eax & 0xffff0000u) | ((t0 & 0xffu) << 8) | (t2 & 0xffu);')
            return L
        if m == 'cdq':
            return ['edx = (int32_t)eax < 0 ? 0xffffffffu : 0u;']
        if m == 'cwde':
            return ['eax = (uint32_t)(int32_t)(int16_t)eax;']
        if m == 'cbw':
            return ['eax = (eax & 0xffff0000u) | ((uint32_t)(int16_t)(int8_t)eax & 0xffffu);']
        if m == 'cwd':
            return ['edx = (edx & 0xffff0000u) | ((eax & 0x8000u) ? 0xffffu : 0u);']
        if m in SETCC:
            return [self.write(ops[0], '(%s) ? 1u : 0u' % CONDITIONS[SETCC[m]][1])]
        if m in CMOVCC:
            return ['if (%s) { %s }' % (CONDITIONS[CMOVCC[m]][1], self.write(ops[0], self.read(ops[1])))]
        if m in ('bt', 'bts', 'btr', 'btc'):
            s = size
            if ops[0].type == X.X86_OP_MEM and ops[1].type == X.X86_OP_REG:
                self.unsupported('bt memory register')
            L.append('t1 = %s & %du;' % (self.read(ops[1]) if ops[1].type != X.X86_OP_IMM else '0x%xu' % ops[1].imm, 8 * s - 1))
            L.append('t0 = %s;' % self.read(ops[0]))
            L.append('cf = (t0 >> t1) & 1u;')
            if m != 'bt':
                v = {'bts': 't0 | (1u << t1)', 'btr': 't0 & ~(1u << t1)', 'btc': 't0 ^ (1u << t1)'}[m]
                L.append(self.write(ops[0], v))
            return L
        if m in ('bsf', 'bsr'):
            L.append('t0 = %s;' % self.read(ops[1]))
            L.append('zf = t0 == 0;')
            L.append('if (t0) { %s }' % self.write(ops[0], '__builtin_ctz(t0)' if m == 'bsf' else '31 - __builtin_clz(t0)'))
            return L
        if m == 'bswap':
            return [self.write(ops[0], '__builtin_bswap32(%s)' % self.read(ops[0]))]
        if m == 'xadd':
            s = size
            return ['t0 = %s; t1 = %s; t2 = (t0 + t1) & %s;' % (self.read(ops[0]), self.read(ops[1]), MASK[s]),
                    'cf = t2 < t0; zf = t2 == 0; sf = (t2 & %s) != 0; of = (((t0 ^ t2) & (t1 ^ t2)) & %s) != 0; pf = PARITY(t2);' % (SIGN[s], SIGN[s]),
                    self.write(ops[1], 't0'), self.write(ops[0], 't2')]
        if m == 'cmpxchg':
            s = size
            return ['t0 = %s;' % self.read(ops[0]),
                    't2 = ((eax & %s) - t0) & %s; cf = (eax & %s) < t0; zf = t2 == 0; sf = (t2 & %s) != 0; of = 0; pf = PARITY(t2);' % (MASK[s], MASK[s], MASK[s], SIGN[s]),
                    'if (zf) { %s } else { eax = (eax & ~%s) | t0; }' % (self.write(ops[0], self.read(ops[1])), MASK[s])]
        if m in ('stc', 'clc', 'cmc'):
            return [{'stc': 'cf = 1;', 'clc': 'cf = 0;', 'cmc': 'cf = !cf;'}[m]]
        if m == 'cpuid':
            return ['CPUID(c, &eax, &ebx, &ecx, &edx);']
        if m == 'rdtsc':
            return ['q = RDTSC(c); eax = (uint32_t)q; edx = (uint32_t)(q >> 32);']
        if m == 'xlatb':
            return ['eax = (eax & 0xffffff00u) | R8(ebx + (eax & 0xffu));']

        # String instructions.
        base = m.replace('rep ', '').replace('repe ', '').replace('repne ', '').replace('repz ', '').replace('repnz ', '')
        if base in STRINGS and not any(o.type == X.X86_OP_REG and X.X86_REG_XMM0 <= o.reg <= X.X86_REG_XMM7
                                       for o in ops):
            return self.string(m, base, live)
        if m in ('jmp',):
            op = ops[0]
            if op.type == X.X86_OP_IMM:
                return [self.goto(op.imm & 0xffffffff)]
            target = self.read(op, 4)
            L.append('t0 = %s;' % target)
            if a in self.f.switches and self.f.switches[a][1]:
                L.append('switch (t0) {')
                for t in sorted(set(self.f.switches[a][1])):
                    # A target that starts another function continues there as a tail call.
                    L.append('case 0x%xu: %s' % (t, self.goto(t)))
                L.append('}')
            L.append('%s JUMP(c, t0); return;' % self.sync_out())
            return L
        if m in JCC:
            t = ops[0].imm & 0xffffffff
            return ['if (%s) { %s }' % (CONDITIONS[JCC[m]][1], self.goto(t))]
        if m in ('jecxz', 'jcxz'):
            t = ops[0].imm & 0xffffffff
            return ['if (ecx == 0) { %s }' % self.goto(t)]
        if m in ('loop', 'loope', 'loopne'):
            t = ops[0].imm & 0xffffffff
            cond = {'loop': 'ecx != 0', 'loope': 'ecx != 0 && zf', 'loopne': 'ecx != 0 && !zf'}[m]
            return ['ecx -= 1;', 'if (%s) { %s }' % (cond, self.goto(t))]
        if m == 'call':
            op = ops[0]
            ret = a + ins.size
            flags_needed = self.live_after.get(a, 0) & ALL
            if op.type == X.X86_OP_IMM:
                L.append('esp -= 4; W32(esp, 0x%xu);' % ret)
                t = op.imm & 0xffffffff
                call = 'F_%x(c);' % t if t in self.entries else 'CALL(c, 0x%xu);' % t
                L.append('%s %s %s' % (self.sync_out(flags=t in self.flag_readers), call,
                                       self.sync_in(flags_needed != 0)))
            else:
                # The target is read before the return address is pushed (`call [esp + n]`).
                L.append('t0 = %s;' % self.read(op, 4) if op.type != X.X86_OP_MEM else 't0 = R32(%s);' % self.addr(op))
                L.append('esp -= 4; W32(esp, 0x%xu);' % ret)
                L.append('%s CALL(c, t0); %s' % (self.sync_out(flags=False), self.sync_in(flags_needed != 0)))
            return L
        if m in ('ret', 'repz ret'):
            n = ops[0].imm if ops else 0
            flags = self.f.entry in self.flag_returners
            return ['c->ret = R32(esp); esp += %d;' % (4 + n), '%s return;' % self.sync_out(flags)]
        if m in ('int3', 'hlt', 'ud2', 'int', 'iretd', 'retf', 'in', 'out', 'insb', 'sti', 'cli',
                 'lcall', 'arpl', 'lds', 'les', 'sgdt', 'sldt', 'into', 'bound'):
            return ['TRAP(0x%xu, "%s");' % (a, m)]
        if m.startswith('f') or m in ('wait',):
            return self.x87(ins, live)
        self.unsupported(m)

    def string(self, m, base, live):
        rep = m.startswith('rep ') or m.startswith('repe ') or m.startswith('repne ') or m.startswith('repz ') or m.startswith('repnz ')
        cond = 'repe' if m.startswith(('repe ', 'repz ')) else ('repne' if m.startswith(('repne ', 'repnz ')) else None)
        s = {'b': 1, 'w': 2, 'd': 4}[base[-1]]
        kind = base[:-1]
        step = 'c->df ? -%d : %d' % (s, s)
        body = {
            'movs': 'W%d(edi, R%d(esi)); esi += (uint32_t)(%s); edi += (uint32_t)(%s);' % (8 * s, 8 * s, step, step),
            'stos': 'W%d(edi, eax & %s); edi += (uint32_t)(%s);' % (8 * s, MASK[s], step),
            'lods': '%s esi += (uint32_t)(%s);' % ('eax = (eax & ~%s) | R%d(esi);' % (MASK[s], 8 * s) if s != 4 else 'eax = R32(esi);', step),
            'cmps': 't0 = R%d(esi); t1 = R%d(edi); t2 = (t0 - t1) & %s; cf = t0 < t1; zf = t2 == 0; sf = (t2 & %s) != 0; of = (((t0 ^ t1) & (t0 ^ t2)) & %s) != 0; pf = PARITY(t2); esi += (uint32_t)(%s); edi += (uint32_t)(%s);' % (8 * s, 8 * s, MASK[s], SIGN[s], SIGN[s], step, step),
            'scas': 't0 = eax & %s; t1 = R%d(edi); t2 = (t0 - t1) & %s; cf = t0 < t1; zf = t2 == 0; sf = (t2 & %s) != 0; of = (((t0 ^ t1) & (t0 ^ t2)) & %s) != 0; pf = PARITY(t2); edi += (uint32_t)(%s);' % (MASK[s], 8 * s, MASK[s], SIGN[s], SIGN[s], step),
        }[kind]
        if not rep:
            return [body]
        if kind in ('movs', 'stos') and s == 4:
            fast = 'REP_%s32(c, &ecx, &esi, &edi, eax);' % kind.upper()
            return [fast]
        if kind in ('movs', 'stos') and s == 1:
            return ['REP_%s8(c, &ecx, &esi, &edi, eax);' % kind.upper()]
        stop = ''
        if cond == 'repe':
            stop = ' if (!zf) break;'
        elif cond == 'repne':
            stop = ' if (zf) break;'
        return ['while (ecx != 0) { %s ecx -= 1;%s }' % (body, stop)]

    # -- x87 ------------------------------------------------------------------------------------
    def fmem(self, op, kind):
        """A memory operand read as a double: kind f (float by size) or i (integer by size)."""
        ad = self.addr(op)
        if kind == 'f':
            return {4: 'RF32(%s)', 8: 'RF64(%s)', 10: 'RF80(%s)'}[op.size] % ad
        return {2: '(double)(int16_t)R16(%s)', 4: '(double)(int32_t)R32(%s)', 8: '(double)(int64_t)R64(%s)'}[op.size] % ad

    def x87(self, ins, live):
        m = ins.mnemonic
        ops = ins.operands
        regs = [o for o in ops if o.type == X.X86_OP_REG]

        def st(op):
            return 'ST(%d)' % (op.reg - X.X86_REG_ST0)

        if m == 'fld':
            if ops[0].type == X.X86_OP_MEM:
                return ['FPUSH(%s);' % self.fmem(ops[0], 'f')]
            return ['{ double v = %s; FPUSH(v); }' % st(ops[0])]
        if m == 'fild':
            return ['FPUSH(%s);' % self.fmem(ops[0], 'i')]
        consts = {'fldz': '0.0', 'fld1': '1.0', 'fldpi': '3.141592653589793238', 'fldl2e': '1.4426950408889634074',
                  'fldl2t': '3.3219280948873623479', 'fldlg2': '0.30102999566398119521', 'fldln2': '0.69314718055994530942'}
        if m in consts:
            return ['FPUSH(%s);' % consts[m]]
        if m in ('fst', 'fstp'):
            pop = ' FPOP();' if m == 'fstp' else ''
            if ops[0].type == X.X86_OP_MEM:
                w = {4: 'WF32(%s, ST(0));', 8: 'WF64(%s, ST(0));', 10: 'WF80(%s, ST(0));'}[ops[0].size] % self.addr(ops[0])
                return [w + pop]
            return ['%s = ST(0);%s' % (st(ops[0]), pop)]
        if m in ('fist', 'fistp', 'fisttp'):
            pop = ' FPOP();' if m != 'fist' else ''
            conv = 'FIST%d(c, ST(0))' % (8 * ops[0].size) if m != 'fisttp' else '(int64_t)ST(0)'
            w = {2: 'W16(%s, (uint16_t)%s);', 4: 'W32(%s, (uint32_t)%s);', 8: 'W64(%s, (uint64_t)%s);'}[ops[0].size] % (self.addr(ops[0]), conv)
            return [w + pop]
        if m == 'fxch':
            # Capstone lists st(0) first: `fxch st(i)` has operands st(0), st(i).
            r = st(regs[-1]) if regs else 'ST(1)'
            return ['{ double v = ST(0); ST(0) = %s; %s = v; }' % (r, r)]
        arith = {'fadd': '+', 'fsub': '-', 'fsubr': 'r-', 'fmul': '*', 'fdiv': '/', 'fdivr': 'r/'}
        for base_op, sym in arith.items():
            if m in (base_op, base_op + 'p', 'fi' + base_op[1:]):
                rev = sym.startswith('r')
                cop = sym[-1]
                if m.startswith('fi'):
                    v = self.fmem(ops[0], 'i')
                    return ['ST(0) = %s;' % (('%s %s ST(0)' % (v, cop)) if rev else ('ST(0) %s %s' % (cop, v)))]
                if not ops or (m.endswith('p') and len(regs) == 0):
                    # faddp with no operands: st(1) = st(1) op st(0); pop
                    expr = ('ST(0) %s ST(1)' % cop) if rev else ('ST(1) %s ST(0)' % cop)
                    return ['ST(1) = %s; FPOP();' % expr]
                if ops[0].type == X.X86_OP_MEM:
                    v = self.fmem(ops[0], 'f')
                    return ['ST(0) = %s;' % (('%s %s ST(0)' % (v, cop)) if rev else ('ST(0) %s %s' % (cop, v)))]
                if len(regs) == 2:
                    d, s_ = st(regs[0]), st(regs[1])
                elif m.endswith('p'):
                    # `faddp st(i)`: st(i) = st(i) op st(0), then pop.
                    d, s_ = st(regs[0]), 'ST(0)'
                else:
                    d, s_ = 'ST(0)', st(regs[0])
                expr = ('%s %s %s' % (s_, cop, d)) if rev else ('%s %s %s' % (d, cop, s_))
                return ['%s = %s;%s' % (d, expr, ' FPOP();' if m.endswith('p') else '')]
        if m in ('fcom', 'fcomp', 'fcompp', 'fucom', 'fucomp', 'fucompp', 'ficom', 'ficomp', 'ftst'):
            if m == 'ftst':
                v = '0.0'
            elif not ops:
                v = 'ST(1)'
            elif ops[0].type == X.X86_OP_MEM:
                v = self.fmem(ops[0], 'i' if m.startswith('fic') else 'f')
            else:
                v = st(regs[-1])
            pops = 2 if m.endswith('pp') else (1 if m.endswith('p') else 0)
            return ['FCOMPARE(ST(0), %s);%s' % (v, ' FPOP();' * pops)]
        if m in ('fcomi', 'fcomip', 'fucomi', 'fucomip'):
            v = st(regs[-1])
            return ['{ double a_ = ST(0), b_ = %s; zf = a_ == b_ || a_ != a_ || b_ != b_; cf = a_ < b_ || a_ != a_ || b_ != b_; pf = a_ != a_ || b_ != b_; }%s' % (v, ' FPOP();' if m.endswith('p') else '')]
        if m in ('fnstsw', 'fstsw'):
            if ops and ops[0].type == X.X86_OP_MEM:
                return ['W16(%s, FPU_SW());' % self.addr(ops[0])]
            return ['eax = (eax & 0xffff0000u) | FPU_SW();']
        if m in ('fnstcw', 'fstcw'):
            return ['W16(%s, c->fpu_cw);' % self.addr(ops[0])]
        if m == 'fldcw':
            return ['c->fpu_cw = R16(%s);' % self.addr(ops[0])]
        if m in ('fnclex', 'fclex'):
            return ['c->fpu_sw &= 0x7f00u;']
        if m in ('fninit', 'finit'):
            return ['FPU_INIT(c);']
        unary = {'fchs': '-ST(0)', 'fabs': 'fabs(ST(0))', 'fsqrt': 'sqrt(ST(0))', 'fsin': 'sin(ST(0))',
                 'fcos': 'cos(ST(0))', 'frndint': 'FPU_ROUND(c, ST(0))', 'f2xm1': '(exp2(ST(0)) - 1.0)'}
        if m in unary:
            return ['ST(0) = %s;' % unary[m]]
        if m == 'fsincos':
            return ['{ double v = ST(0); ST(0) = sin(v); FPUSH(cos(v)); }']
        if m == 'fptan':
            return ['ST(0) = tan(ST(0)); FPUSH(1.0);']
        if m == 'fpatan':
            return ['ST(1) = atan2(ST(1), ST(0)); FPOP();']
        if m == 'fyl2x':
            return ['ST(1) = ST(1) * log2(ST(0)); FPOP();']
        if m == 'fscale':
            return ['ST(0) = ldexp(ST(0), (int)trunc(ST(1)));']
        if m in ('fprem', 'fprem1'):
            return ['ST(0) = %s(ST(0), ST(1)); c->fpu_sw &= ~0x0400u;' % ('fmod' if m == 'fprem' else 'remainder')]
        if m == 'fxam':
            return ['FXAM(c);']
        if m == 'ffree':
            return ['/* ffree */']
        if m == 'fnop':
            return ['/* fnop */']
        if m in ('fnstenv', 'fnsave', 'fldenv', 'frstor', 'fstenv', 'fsave'):
            return ['FPU_STATE(c, "%s", %s);' % (m, self.addr(ops[0]))]
        if m == 'femms':
            self.unsupported(m)
        self.unsupported(m)


def flag_readers(p, funcs, entries):
    """Functions that read, before writing, flags their caller set (the CRT's sqrt reads the
    zero flag its caller's previous call left). Grows to a fixed point: calling such a function
    makes its flags live in the caller too."""
    readers = set()
    while True:
        found = set()
        for e, f in funcs.items():
            if f.entry not in f.insns or f.insns[f.entry] is None:
                continue
            g = Gen(p, f, entries, set(), readers)
            g.liveness()
            if g.live_in.get(f.entry, 0):
                found.add(e)
        if found <= readers:
            return readers
        readers |= found


def flag_returners(p, funcs, readers=frozenset()):
    """Functions whose caller reads a flag the callee set (hand-written runtime helpers): the
    caller tests it after the call, hands it to a function that reads it, or returns it to its
    own caller."""
    found = set()
    while True:
        before = len(found)
        for f in funcs.values():
            for a, ins in f.insns.items():
                if ins is None or ins.mnemonic != 'call' or ins.operands[0].type != X.X86_OP_IMM:
                    continue
                callee = ins.operands[0].imm & 0xffffffff
                # Scan forward in straight line for a flag reader before a writer.
                cur = a + ins.size
                for _ in range(6):
                    i2 = f.insns.get(cur)
                    if i2 is None:
                        break
                    r, w = flag_effect(i2)
                    if r:
                        found.add(callee)
                        break
                    if i2.mnemonic == 'call':
                        t = i2.operands[0].imm & 0xffffffff if i2.operands[0].type == X.X86_OP_IMM else None
                        if t in readers:
                            found.add(callee)
                        break
                    if i2.mnemonic in ('ret', 'repz ret'):
                        if f.entry in found:
                            found.add(callee)
                        break
                    if w == ALL or i2.mnemonic == 'jmp':
                        break
                    cur += i2.size
        if len(found) == before:
            return found


HEADER = '''/* Generated by vertrix3/recomp.py from %s (sha256 %s). Do not edit. */
#include "v3_functions.h"
'''


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('exe')
    parser.add_argument('out', type=Path)
    args = parser.parse_args()
    p = Program(args.exe)
    funcs, entries = discover(p)
    readers = flag_readers(p, funcs, entries)
    returners = flag_returners(p, funcs, readers)
    print('%d functions read their caller\'s flags, %d return flags' % (len(readers), len(returners)))
    args.out.mkdir(parents=True, exist_ok=True)
    for old in args.out.glob('v3_code_*.c'):
        old.unlink()
    names = sorted(funcs)
    unsupported = defaultdict(int)
    files = []
    for k in range(0, len(names), PER_FILE):
        chunk = names[k:k + PER_FILE]
        text = [HEADER % ('%s, %s' % (p.executable, p.game), p.sha256)]
        for e in chunk:
            g = Gen(p, funcs[e], entries, returners, readers)
            body = g.emit()
            for line in body.split('\n'):
                if 'UNSUPPORTED(' in line:
                    unsupported[line.split('"')[1].split()[0]] += 1
            text.append(body)
            text.append('')
        path = args.out / ('v3_code_%03d.c' % (k // PER_FILE))
        path.write_text('\n'.join(text))
        files.append(path.name)
    # Function table and prototypes.
    proto = ['/* Generated by vertrix3/recomp.py. */', '#ifndef V3_FUNCTIONS_H', '#define V3_FUNCTIONS_H',
             '#include "cpu.h"']
    proto += ['void F_%x(Cpu *c);' % e for e in names]
    proto += ['#endif', '']
    (args.out / 'v3_functions.h').write_text('\n'.join(proto))
    image = bytearray(p.image)
    image.extend(b'\0' * (p.pe.OPTIONAL_HEADER.SizeOfImage - len(image)))
    (args.out / 'v3_image.bin').write_bytes(bytes(image[:p.pe.OPTIONAL_HEADER.SizeOfImage]))
    table = ['/* Generated by vertrix3/recomp.py. */', '#include "v3_functions.h"',
             'const V3Function v3_functions[] = {']
    table += ['    {0x%xu, F_%x},' % (e, e) for e in names]
    table += ['};', 'const unsigned v3_function_count = %d;' % len(names)]
    imports = ['const V3Import v3_imports[] = {']
    for address, (dll, name) in sorted(p.iat.items()):
        imports.append('    {0x%xu, "%s", "%s"},' % (address, dll, name))
    imports += ['};', 'const unsigned v3_import_count = %d;' % len(p.iat),
                'const uint32_t v3_entry_offset = 0x%xu;' % (p.entry - p.base),
                'const char v3_game_directory[] = "%s";' % p.directory.replace('\\', '\\\\'),
                'const char v3_executable[] = "%s";' % p.executable,
                'const char v3_game_title[] = "%s";' % p.game,
                'const char v3_archive[] = "%s";' % p.archive,
                'const char v3_wii_folder[] = "%s";' % p.wii_folder, '']
    (args.out / 'v3_table.c').write_text('\n'.join(table + imports))
    print('functions %d, files %d, flag-returning %d' % (len(names), len(files), len(returners)))
    print('unsupported:', dict(sorted(unsupported.items(), key=lambda x: -x[1])))


if __name__ == '__main__':
    main()
