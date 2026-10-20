"""Recompile Vertrix (1997)'s VERTRIX.EXE into C, function by function.

VERTRIX.EXE is a Linear Executable bound to the PMODE/W v1.33 DOS extender and built with Watcom
C/C++32. Its two objects (code at 0x10000, data and stack at 0x60000) are laid out at their link
addresses, which makes every fixup the identity, and the code is translated with the generator of
vertrix3/recomp.py: each function becomes `void F_<address>(Cpu *c)` running on the guest's own
flat stack (see that file for the scheme).

What differs from the Windows executables:

- Function discovery is guided by the LE fixups: every absolute address the image holds is a
  fixup, so a code address is taken as an entry only where a fixup puts it (an instruction's
  immediate or a pointer in data), never because a constant happens to look like one. The
  Watcom debug information at the end of the file names the functions.
- The program talks to the hardware: `in`/`out` become calls into the machine model
  (vertrix1/runtime/ports.c), `int n` goes to the guest's own handler or to the DOS, DPMI and
  BIOS services the runtime provides (dos.c), `cli`/`sti`/`iretd`/`pushfd` keep the interrupt
  flag, and far calls and jumps through 48-bit pointers chain to old interrupt handlers.
- Hardware interrupts (the timer, the keyboard, the Sound Blaster) arrive at safe points: every
  function entry and every loop head polls the runtime (POLL), which delivers a pending
  interrupt the way the processor would, by pushing an interrupt frame and calling the handler.
- Memory at 0xA0000-0xAFFFF is the VGA's window and goes through the VGA model; an access that
  cannot reach it (on the stack, or at a fixed address elsewhere) stays a plain memory access.
- Segment registers hold selectors with bases (vertrix1/runtime/dos.c's descriptor table); an
  explicit es, fs or gs override and the implicit es of string instructions add the base.

usage: recomp.py VERTRIX_EXE OUT_DIR
"""
import argparse
import hashlib
import importlib.util
import re
import struct
import sys
from collections import defaultdict
from pathlib import Path

# vertrix3/recomp.py, loaded under its own name (this file has the same one).
_spec = importlib.util.spec_from_file_location(
    'vertrix3_recomp', Path(__file__).resolve().parent.parent / 'vertrix3' / 'recomp.py')
r3 = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(r3)
from capstone import CS_ARCH_X86, CS_MODE_32, Cs  # noqa: E402
from capstone import x86_const as X  # noqa: E402

GAMES = {
    '4785d692a783c216ae93071c4a3b7c6131ca06c21423edfdda06e298c1866f04': ('VERTRIX.EXE', 'Vertrix'),
}
VGA_START, VGA_END = 0xa0000, 0xb0000
SEG_INDEX = {X.X86_REG_ES: 0, X.X86_REG_CS: 1, X.X86_REG_SS: 2, X.X86_REG_DS: 3,
             X.X86_REG_FS: 4, X.X86_REG_GS: 5}
PORT_INSNS = ('in', 'out')


class LEProgram:
    """The image of an LE executable at its link addresses, in the shape vertrix3/recomp.py's
    Function and Gen expect of a program."""

    def __init__(self, path):
        data = Path(path).read_bytes()
        self.sha256 = hashlib.sha256(data).hexdigest()
        self.executable, self.game = GAMES.get(self.sha256, (None, None))
        if self.executable is None:
            sys.exit('not VERTRIX.EXE (sha256 %s)' % self.sha256)
        self.data = data
        le = struct.unpack_from('<I', data, 0x3c)[0]
        if data[le:le + 2] != b'LE':
            sys.exit('no LE header')
        self.le = le
        h = self.header
        page_size, pages, last = h(0x28), h(0x14), h(0x2c)
        self.objects = []
        for i in range(h(0x44)):
            size, base, flags, page, count, _ = struct.unpack_from('<6I', data, le + h(0x40) + 24 * i)
            self.objects.append({'size': size, 'base': base, 'flags': flags, 'page': page,
                                 'count': count})
        self.base = min(o['base'] for o in self.objects)
        end = max(o['base'] + o['size'] for o in self.objects)
        image = bytearray(end - self.base)
        page_address = {}
        for o in self.objects:
            for k in range(o['count']):
                n = o['page'] + k
                entry = data[le + h(0x48) + 4 * (n - 1):][:4]
                number = entry[0] << 16 | entry[1] << 8 | entry[2]
                if entry[3] != 0:
                    sys.exit('page %d: unsupported page type %d' % (n, entry[3]))
                size = last if number == pages else page_size
                at = h(0x80) + (number - 1) * page_size
                start = o['base'] + k * page_size - self.base
                image[start:start + size] = data[at:at + size]
                page_address[n] = o['base'] + k * page_size
        # Internal 32-bit offset fixups only (the image has no other kind): the target object's
        # link address plus the offset. Applied, they leave the pages as linked.
        self.fixups = {}
        table, records = le + h(0x68), le + h(0x6c)
        for n in range(1, pages + 1):
            start, stop = struct.unpack_from('<II', data, table + 4 * (n - 1))
            o = records + start
            while o < records + stop:
                source, flags = data[o], data[o + 1]
                offset = struct.unpack_from('<h', data, o + 2)[0]
                o += 4
                if source != 7 or flags & ~0x50:
                    sys.exit('fixup %02x/%02x at page %d is not a 32-bit internal offset'
                             % (source, flags, n))
                if flags & 0x40:
                    obj = struct.unpack_from('<H', data, o)[0]
                    o += 2
                else:
                    obj = data[o]
                    o += 1
                if flags & 0x10:
                    target = struct.unpack_from('<I', data, o)[0]
                    o += 4
                else:
                    target = struct.unpack_from('<H', data, o)[0]
                    o += 2
                at = page_address[n] + offset
                value = self.objects[obj - 1]['base'] + target
                struct.pack_into('<I', image, at - self.base, value)
                self.fixups[at] = value
        self.image = bytes(image)
        eip_object = self.objects[h(0x18) - 1]
        self.entry = eip_object['base'] + h(0x1c)
        stack_object = self.objects[h(0x20) - 1]
        self.stack_top = stack_object['base'] + h(0x24)
        # Objects with the executable flag are code; the shape vertrix3's discovery expects.
        self.sections = [(o['base'], o['base'] + o['size'],
                          0x20000000 if o['flags'] & 4 else 0) for o in self.objects]
        self.code = [(a, b) for a, b, ch in self.sections if ch & 0x20000000]
        self.symbols = self.debug_symbols()
        self.md = Cs(CS_ARCH_X86, CS_MODE_32)
        self.md.detail = True
        self.cache = {}

    def header(self, offset):
        return struct.unpack_from('<I', self.data, self.le + offset)[0]

    def debug_symbols(self):
        """Watcom debug information v3 (the master header's signature 0x8386 ends the file):
        the modules and the global symbols, each an object-relative address with a name and the
        module that defines it."""
        data = self.data
        signature, _, _, _, _, lang, segments, size = struct.unpack_from('<HBBBBHHI', data,
                                                                         len(data) - 14)
        self.modules = []
        self.symbol_module = {}
        if signature != 0x8386:
            return {}
        section = len(data) - size + lang + segments
        modules_at, globals_at, addresses_at = struct.unpack_from('<III', data, section)
        o = section + modules_at
        while o < section + globals_at:
            n = data[o + 20]
            self.modules.append(data[o + 21:o + 21 + n].decode('latin1'))
            o += 21 + n
        symbols = {}
        o = section + globals_at
        while o < section + addresses_at:
            offset, segment, module, _, n = struct.unpack_from('<IHHBB', data, o)
            name = data[o + 10:o + 10 + n].decode('latin1')
            if 1 <= segment <= len(self.objects):
                address = self.objects[segment - 1]['base'] + offset
                if address not in symbols:
                    symbols[address] = name
                    self.symbol_module[address] = self.modules[module] if module < len(
                        self.modules) else ''
            o += 10 + n
        return symbols

    def data_symbol(self, a):
        """Whether a data symbol starts at `a`: the game's C variables (Watcom names them `_name`,
        its register-convention functions `name_`) that it keeps in the code object, and the
        code object's start marker."""
        name = self.symbols.get(a)
        if name is None:
            return False
        if name == '___begtext':
            return True
        return self.symbol_module.get(a, '').upper().endswith('VERTRIX.C') and \
            name.startswith('_') and not name.endswith('_')

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
            if got is not None and got.mnemonic.startswith('notrack '):
                got = Renamed(got, got.mnemonic[len('notrack '):])
            self.cache[a] = got
        return self.cache[a]


class Renamed:
    """An instruction under another mnemonic: Capstone calls an indirect jump with a ds prefix
    (3e) `notrack jmp`, the prefix's meaning for CET; on a 386 it is a plain segment prefix."""

    def __init__(self, ins, mnemonic):
        self._ins = ins
        self.mnemonic = mnemonic

    def __getattr__(self, name):
        return getattr(self._ins, name)


def has_fixup(p, ins):
    return any(ins.address <= at < ins.address + ins.size for at in
               range(ins.address, ins.address + ins.size) if at in p.fixups)


def discover(p):
    """Recursive descent from the entry, as vertrix3's discovery, with code addresses taken
    only from fixups: an instruction's immediate that a fixup relocates, and every pointer the
    loader relocates outside the decoded instructions (data, and the read-only data Watcom
    keeps in the code object)."""
    entries = {p.entry}
    seeds = [p.entry]
    funcs = {}
    while True:
        while seeds:
            e = seeds.pop()
            if e in funcs:
                continue
            f = r3.Function(p, e, entries)
            funcs[e] = f
            found = set(f.calls) | set(f.tail)
            for a, ins in f.insns.items():
                if ins is not None and has_fixup(p, ins):
                    for op in ins.operands:
                        if op.type == X.X86_OP_IMM and p.in_code(op.imm & 0xffffffff) and \
                                ins.mnemonic not in ('call', 'jmp') and not ins.mnemonic.startswith('j'):
                            found.add(op.imm & 0xffffffff)
            for t in found:
                if t not in entries and p.insn(t) is not None and not p.data_symbol(t):
                    entries.add(t)
                    seeds.append(t)
        covered = set()
        switch_tables = set()
        for f in funcs.values():
            for a, ins in f.insns.items():
                if ins is not None:
                    covered.update(range(a, a + ins.size))
            for table, targets in f.switches.values():
                switch_tables.update(range(table, table + 4 * len(targets)))
        added = False
        for at, value in sorted(p.fixups.items()):
            if at in covered or at in switch_tables or not p.in_code(value) or value in entries:
                continue
            if p.insn(value) is None:
                continue
            # A pointer into the code object: a function, unless a data symbol starts there.
            if p.data_symbol(value):
                continue
            entries.add(value)
            seeds.append(value)
            added = True
        if not added:
            break
    while True:
        funcs = {e: r3.Function(p, e, entries) for e in sorted(entries)}
        extra = set()
        for f in funcs.values():
            extra |= (set(f.calls) | set(f.tail)) - entries
        if not extra:
            return funcs, entries
        entries |= extra


# ----------------------------------------------------------------------------------------------
# Flags: `int` hands the flags to the handler and takes them back; port accesses keep them.

_flag_effect = r3.flag_effect


def flag_effect(ins):
    m = ins.mnemonic
    if m == 'int':
        return r3.ALL, r3.ALL
    if m in ('in', 'out', 'cli', 'sti'):
        return 0, 0
    if m == 'iretd':
        return 0, 0
    # vertrix3's table has these write every flag; they write the carry only (the MOD player
    # tests a comparison's zero flag after `stc`).
    if m in ('stc', 'clc'):
        return 0, r3.CF
    if m == 'cmc':
        return r3.CF, r3.CF
    return _flag_effect(ins)


r3.flag_effect = flag_effect


def flag_returners(p, funcs, readers=frozenset()):
    """vertrix3's flag_returners without its six-instruction window: the MOD player's
    _MODDetectCard stores three results and pops every register (pushal/popal) before it reads
    the carry its callee returned (`sbb eax, eax`), eight instructions after the call."""
    found = set()
    while True:
        before = len(found)
        for f in funcs.values():
            for a, ins in f.insns.items():
                if ins is None or ins.mnemonic != 'call' or ins.operands[0].type != X.X86_OP_IMM:
                    continue
                callee = ins.operands[0].imm & 0xffffffff
                cur = a + ins.size
                while True:
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
                    if w == r3.ALL or i2.mnemonic == 'jmp' or r3.JCC.get(i2.mnemonic) or \
                            f.succ.get(cur, []) != [cur + i2.size]:
                        break
                    cur += i2.size
        if len(found) == before:
            return found


PREFIXES = {0x26, 0x2e, 0x36, 0x3e, 0x64, 0x65, 0x66, 0x67, 0xf0, 0xf2, 0xf3}


def far_indirect(ins):
    """Whether an instruction is a far call or jump through memory (opcode FF, ModRM reg 3 or
    5): Capstone gives `call m16:32` a 4-byte operand, so the encoding decides."""
    raw = bytes(ins.bytes)
    i = 0
    while i < len(raw) and raw[i] in PREFIXES:
        i += 1
    return i + 1 < len(raw) and raw[i] == 0xff and (raw[i + 1] >> 3) & 7 in (3, 5) and \
        raw[i + 1] >> 6 != 3


class DosGen(r3.Gen):
    """vertrix3's generator with the DOS machine's instructions."""

    def __init__(self, p, f, entries, flag_returners, flag_readers=frozenset()):
        super().__init__(p, f, entries, flag_returners, flag_readers)
        self.polls = set()
        # A function that loads ds (the start-up reads the PSP and the environment through it)
        # adds ds's base to the memory operands that default to it.
        self.ds_loaded = any(
            ins is not None and (ins.mnemonic == 'lds' or ins.mnemonic in ('mov', 'pop') and
                                 ins.operands[0].type == X.X86_OP_REG and
                                 ins.operands[0].reg == X.X86_REG_DS)
            for ins in f.insns.values())

    # -- memory: the VGA window and segment bases ---------------------------------------------
    def addr(self, op):
        return self.address(op, True)

    def address(self, op, segmented):
        mem = op.mem
        parts = []
        if mem.base != 0:
            parts.append(r3.REG32[mem.base] if mem.base in r3.REG32 else self.unsupported('base'))
        if mem.index != 0:
            r = r3.REG32[mem.index]
            parts.append('%s * %d' % (r, mem.scale) if mem.scale != 1 else r)
        if mem.disp or not parts:
            parts.append('0x%xu' % (mem.disp & 0xffffffff))
        expr = ' + '.join(parts)
        if segmented and mem.segment in (X.X86_REG_ES, X.X86_REG_FS, X.X86_REG_GS):
            expr = 'c->seg_base[%d] + %s' % (SEG_INDEX[mem.segment], expr)
        elif segmented and self.uses_ds(op):
            expr = 'c->seg_base[3] + %s' % expr
        return '(uint32_t)(%s)' % expr

    def uses_ds(self, op):
        """Whether a memory operand goes through a ds this function loads: an explicit ds, or
        the default one (any base but esp and ebp, which default to ss)."""
        mem = op.mem
        if not self.ds_loaded:
            return False
        if mem.segment == X.X86_REG_DS:
            return True
        return mem.segment == 0 and mem.base not in (X.X86_REG_ESP, X.X86_REG_EBP)

    def plain(self, op):
        """Whether a memory operand can never reach the VGA window: on the stack, or at a fixed
        address outside it, with no segment base added."""
        mem = op.mem
        if mem.segment in (X.X86_REG_ES, X.X86_REG_FS, X.X86_REG_GS) or self.uses_ds(op):
            return False
        if mem.base == X.X86_REG_ESP:
            return True
        if mem.base == 0 and mem.index == 0:
            a = mem.disp & 0xffffffff
            return not (VGA_START - 8 < a < VGA_END)
        return False

    def read(self, op, size=None):
        size = size or op.size
        if op.type == X.X86_OP_MEM:
            prefix = '' if self.plain(op) else 'V'
            return '%sR%d(%s)' % (prefix, 8 * size, self.addr(op))
        return super().read(op, size)

    def write(self, op, value):
        if op.type == X.X86_OP_MEM:
            prefix = '' if self.plain(op) else 'V'
            return '%sW%d(%s, %s);' % (prefix, 8 * op.size, self.addr(op), value)
        return super().write(op, value)

    def string(self, m, base, live):
        rep = m.split(' ')[0] in ('rep', 'repe', 'repne', 'repz', 'repnz')
        cond = 'repe' if m.startswith(('repe ', 'repz ')) else ('repne' if m.startswith(('repne ', 'repnz ')) else None)
        s = {'b': 1, 'w': 2, 'd': 4}[base[-1]]
        kind = base[:-1]
        step = 'c->df ? -%d : %d' % (s, s)
        dst = '(c->seg_base[0] + edi)'
        src_base = 'c->seg_base[3]' if self.ds_loaded else '0u'
        src = '(%s + esi)' % src_base if self.ds_loaded else 'esi'
        mask, sign = r3.MASK[s], r3.SIGN[s]
        body = {
            'movs': 'VW%d(%s, VR%d(%s)); esi += (uint32_t)(%s); edi += (uint32_t)(%s);' % (8 * s, dst, 8 * s, src, step, step),
            'stos': 'VW%d(%s, eax & %s); edi += (uint32_t)(%s);' % (8 * s, dst, mask, step),
            'lods': '%s esi += (uint32_t)(%s);' % ('eax = (eax & ~%s) | VR%d(%s);' % (mask, 8 * s, src) if s != 4 else 'eax = VR32(%s);' % src, step),
            'cmps': 't0 = VR%d(%s); t1 = VR%d(%s); t2 = (t0 - t1) & %s; cf = t0 < t1; zf = t2 == 0; sf = (t2 & %s) != 0; of = (((t0 ^ t1) & (t0 ^ t2)) & %s) != 0; pf = PARITY(t2); esi += (uint32_t)(%s); edi += (uint32_t)(%s);' % (8 * s, src, 8 * s, dst, mask, sign, sign, step, step),
            'scas': 't0 = eax & %s; t1 = VR%d(%s); t2 = (t0 - t1) & %s; cf = t0 < t1; zf = t2 == 0; sf = (t2 & %s) != 0; of = (((t0 ^ t1) & (t0 ^ t2)) & %s) != 0; pf = PARITY(t2); edi += (uint32_t)(%s);' % (mask, 8 * s, dst, mask, sign, sign, step),
        }[kind]
        if not rep:
            return [body]
        if kind in ('movs', 'stos') and s in (1, 2, 4):
            return ['V1_REP_%s(c, %d, &ecx, &esi, &edi, eax, %s);' % (kind.upper(), s, src_base)]
        stop = ''
        if cond == 'repe':
            stop = ' if (!zf) break;'
        elif cond == 'repne':
            stop = ' if (zf) break;'
        return ['while (ecx != 0) { %s ecx -= 1;%s }' % (body, stop)]

    # -- interrupts -----------------------------------------------------------------------------
    def emit(self):
        f = self.f
        for a, succ in f.succ.items():
            for t in succ:
                if t <= a and t in f.insns:
                    self.polls.add(t)
        self.polls.add(f.entry)
        text = super().emit()
        lines = text.split('\n')
        out = []
        for line in lines:
            out.append(line)
            m = re.match(r'L_([0-9a-f]+):$', line)
            if m and int(m.group(1), 16) in self.polls:
                out.append('    POLL(0x%su);' % m.group(1))
            elif line.startswith('    HISTORY(') and f.entry in self.polls and \
                    not any(l.startswith('L_%x:' % f.entry) for l in lines):
                out.append('    POLL(0x%xu);' % f.entry)
        return '\n'.join(out)

    def full_sync_out(self):
        return self.sync_out(True)

    def full_sync_in(self):
        return self.sync_in(True)

    def segment_load(self, sreg, value):
        return '%s v1_load_segment(c, %d, %s); %s' % (
            self.sync_out(), SEG_INDEX[sreg], value, self.sync_in(True))

    def insn(self, ins):
        m = r3.mnemonic_of(ins)
        ops = ins.operands
        a = ins.address
        L = []
        if m == 'in':
            port = 'edx & 0xffffu' if ops[1].type == X.X86_OP_REG else '0x%xu' % (ops[1].imm & 0xff)
            size = ops[0].size
            if size == 1:
                return ['eax = (eax & 0xffffff00u) | V1_IN(c, %s, 1);' % port]
            if size == 2:
                return ['eax = (eax & 0xffff0000u) | V1_IN(c, %s, 2);' % port]
            return ['eax = V1_IN(c, %s, 4);' % port]
        if m == 'out':
            port = 'edx & 0xffffu' if ops[0].type == X.X86_OP_REG else '0x%xu' % (ops[0].imm & 0xff)
            size = ops[1].size
            return ['V1_OUT(c, %s, eax & %s, %d);' % (port, r3.MASK[size], size)]
        if m == 'int':
            n = ops[0].imm & 0xff
            return ['%s v1_int(c, 0x%xu, 0x%xu); %s' % (self.full_sync_out(), n, a + ins.size,
                                                      self.full_sync_in())]
        if m == 'cli':
            return ['c->iflag = 0;']
        if m == 'sti':
            return ['c->iflag = 1;']
        if m in ('pushfd', 'pushf'):
            return ['esp -= 4;', 'W32(esp, V1_FLAGS_PACK());']
        if m in ('popfd', 'popf'):
            return ['t0 = R32(esp);', 'esp += 4;', 'FLAGS_UNPACK(t0); c->iflag = (t0 >> 9) & 1u;']
        if m == 'iretd':
            return ['c->ret = R32(esp); t0 = R32(esp + 8); esp += 12;',
                    'FLAGS_UNPACK(t0); c->iflag = (t0 >> 9) & 1u;',
                    '%s return;' % self.sync_out(True)]
        if m == 'retf':
            n = ops[0].imm if ops else 0
            return ['c->ret = R32(esp); esp += %d;' % (8 + n), '%s return;' % self.sync_out(True)]
        if m in ('call', 'jmp') and ops and ops[0].type == X.X86_OP_MEM and far_indirect(ins):
            # Far, through a 48-bit pointer: the old interrupt handlers the game chains to.
            ad = self.addr(ops[0])
            if m == 'jmp':
                return ['t0 = R32(%s);' % ad, '%s JUMP(c, t0); return;' % self.sync_out()]
            ret = a + ins.size
            return ['t0 = R32(%s);' % ad, 'esp -= 4; W32(esp, c->sreg[1]);',
                    'esp -= 4; W32(esp, 0x%xu);' % ret,
                    '%s CALL(c, t0); %s' % (self.full_sync_out(), self.full_sync_in())]
        if m in ('lcall', 'ljmp'):
            return ['TRAP(0x%xu, "%s");' % (a, m)]
        # Segment registers.
        if m == 'mov' and ops[0].type == X.X86_OP_REG and ops[0].reg in SEG_INDEX:
            if ops[0].reg == X.X86_REG_CS:
                self.unsupported('mov cs')
            src = ops[1]
            v = self.read(src, 2) if src.type != X.X86_OP_REG else '(%s & 0xffffu)' % r3.reg_of(src.reg)[0]
            return [self.segment_load(ops[0].reg, v)]
        if m in ('mov', 'movzx') and ops[1].type == X.X86_OP_REG and ops[1].reg in SEG_INDEX:
            v = 'c->sreg[%d]' % SEG_INDEX[ops[1].reg]
            if ops[0].type == X.X86_OP_MEM:
                return ['W16(%s, %s);' % (self.addr(ops[0]), v) if self.plain(ops[0]) else
                        'VW16(%s, %s);' % (self.addr(ops[0]), v)]
            r, s, _ = r3.reg_of(ops[0].reg)
            if s == 4:
                return ['%s = %s;' % (r, v)]
            return ['%s = (%s & 0xffff0000u) | %s;' % (r, r, v)]
        if m == 'push' and ops[0].type == X.X86_OP_REG and ops[0].reg in SEG_INDEX:
            return ['esp -= 4;', 'W32(esp, c->sreg[%d]);' % SEG_INDEX[ops[0].reg]]
        if m == 'pop' and ops[0].type == X.X86_OP_REG and ops[0].reg in SEG_INDEX:
            return ['t0 = R16(esp);', 'esp += 4;', self.segment_load(ops[0].reg, 't0')]
        if m in ('lds', 'les', 'lfs', 'lgs', 'lss'):
            sreg = {'lds': X.X86_REG_DS, 'les': X.X86_REG_ES, 'lfs': X.X86_REG_FS,
                    'lgs': X.X86_REG_GS, 'lss': X.X86_REG_SS}[m]
            ad = self.addr(ops[1])
            return ['t0 = VR32(%s); t1 = VR16(%s + 4u);' % (ad, ad),
                    self.write(ops[0], 't0'), self.segment_load(sreg, 't1')]
        if m == 'lsl':
            src = ops[1]
            v = self.read(src, 2) if src.type != X.X86_OP_REG else '(%s & 0xffffu)' % r3.reg_of(src.reg)[0]
            return ['t1 = %s;' % v, 'zf = v1_segment_valid(t1);',
                    'if (zf) { %s }' % self.write(ops[0], 'v1_segment_limit(t1)')]
        if m == 'lea':
            return [self.write(ops[0], self.address(ops[1], False))]
        if m == 'mov' and any(o.type == X.X86_OP_REG and X.X86_REG_CR0 <= o.reg <= X.X86_REG_CR15
                              for o in ops):
            # The C library's x87 emulator set-up reads and writes cr0 (EM, MP, TS).
            if ops[0].type == X.X86_OP_REG and ops[0].reg == X.X86_REG_CR0:
                return ['c->cr0 = %s;' % self.read(ops[1])]
            if ops[1].type == X.X86_OP_REG and ops[1].reg == X.X86_REG_CR0:
                return [self.write(ops[0], 'c->cr0')]
            self.unsupported('control register')
        if m == 'smsw':
            return [self.write(ops[0], 'c->cr0 & 0xffffu')]
        if m == 'aam':
            n = ops[0].imm & 0xff if ops else 10
            return ['t0 = eax & 0xffu;', 'if (0x%xu == 0) DIVIDE_ERROR(0x%xu);' % (n, a),
                    't2 = t0 %% 0x%xu;' % n,
                    'eax = (eax & 0xffff0000u) | ((t0 / 0x%xu) << 8) | t2;' % n,
                    'zf = t2 == 0; sf = (t2 & 0x80u) != 0; pf = PARITY(t2); cf = 0; of = 0;']
        if m == 'aad':
            n = ops[0].imm & 0xff if ops else 10
            return ['t2 = ((eax & 0xffu) + ((eax >> 8) & 0xffu) * 0x%xu) & 0xffu;' % n,
                    'eax = (eax & 0xffff0000u) | t2;',
                    'zf = t2 == 0; sf = (t2 & 0x80u) != 0; pf = PARITY(t2); cf = 0; of = 0;']
        if m in ('fincstp', 'fdecstp'):
            return ['c->top = (c->top %s 1u) & 7u;' % ('+' if m == 'fincstp' else '-')]
        if m in ('fdisi8087_nop', 'feni8087_nop', 'fsetpm287_nop'):
            return ['/* %s */' % m]
        if m in ('xlatb',):
            return ['eax = (eax & 0xffffff00u) | VR8(ebx + (eax & 0xffu));']
        if m in ('hlt', 'insb', 'insd', 'insw', 'outsb', 'outsd', 'outsw', 'arpl', 'into',
                 'bound', 'sgdt', 'sldt', 'lgdt', 'lidt', 'ltr', 'str', 'lar', 'verr', 'verw',
                 'sidt', 'daa', 'das', 'aaa', 'aas'):
            # (The decimal adjustments need the auxiliary carry, which is not kept; they only
            # appear in data the C library's number tables hold after a call.)
            return ['TRAP(0x%xu, "%s");' % (a, m)]
        return super().insn(ins)


HEADER = '''/* Generated by vertrix1/recomp.py from %s (sha256 %s). Do not edit. */
#include "v3_functions.h"
'''


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('exe')
    parser.add_argument('out', type=Path)
    args = parser.parse_args()
    p = LEProgram(args.exe)
    funcs, entries = discover(p)
    readers = r3.flag_readers(p, funcs, entries)
    returners = flag_returners(p, funcs, readers)
    print('%d functions read their caller\'s flags, %d return flags' % (len(readers), len(returners)))
    args.out.mkdir(parents=True, exist_ok=True)
    for old in args.out.glob('v1_code_*.c'):
        old.unlink()
    names = sorted(funcs)
    unsupported = defaultdict(int)
    for k in range(0, len(names), r3.PER_FILE):
        chunk = names[k:k + r3.PER_FILE]
        text = [HEADER % ('%s, %s' % (p.executable, p.game), p.sha256)]
        for e in chunk:
            g = DosGen(p, funcs[e], entries, returners, readers)
            body = g.emit()
            for line in body.split('\n'):
                if 'UNSUPPORTED(' in line:
                    unsupported[line.split('"')[1].split()[0]] += 1
            if e in p.symbols:
                text.append('/* %s */' % p.symbols[e])
            text.append(body)
            text.append('')
        (args.out / ('v1_code_%03d.c' % (k // r3.PER_FILE))).write_text('\n'.join(text))
    proto = ['/* Generated by vertrix1/recomp.py. */', '#ifndef V3_FUNCTIONS_H', '#define V3_FUNCTIONS_H',
             '#include "cpu.h"']
    proto += ['void F_%x(Cpu *c);' % e for e in names]
    proto += ['#endif', '']
    (args.out / 'v3_functions.h').write_text('\n'.join(proto))
    (args.out / 'v1_image.bin').write_bytes(p.image)
    table = ['/* Generated by vertrix1/recomp.py. */', '#include "v3_functions.h"',
             '#include "dos.h"', 'const V3Function v3_functions[] = {']
    table += ['    {0x%xu, F_%x},' % (e, e) for e in names]
    table += ['};', 'const unsigned v3_function_count = %d;' % len(names)]
    symbols = sorted((a, n) for a, n in p.symbols.items() if p.in_code(a))
    table += ['const V1Symbol v1_symbols[] = {']
    table += ['    {0x%xu, "%s"},' % (a, n) for a, n in symbols]
    table += ['};', 'const unsigned v1_symbol_count = %d;' % len(symbols)]
    table += ['const V1Image v1_image = {0x%xu, 0x%xu, 0x%xu, 0x%xu};' % (
        p.base, len(p.image), p.entry, p.stack_top), '']
    (args.out / 'v3_table.c').write_text('\n'.join(table))
    print('functions %d, entry %x, stack %x' % (len(names), p.entry, p.stack_top))
    print('unsupported:', dict(sorted(unsupported.items(), key=lambda x: -x[1])))


if __name__ == '__main__':
    main()
