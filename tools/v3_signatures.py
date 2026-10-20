"""Match Vertrix 3's functions to the known Vertrix 2 routines by signature.

Vertrix 2 was built with Watcom C and Vertrix 3 with Visual C++ 9, so instruction bytes rarely
agree. A function's signature is what survives a change of compiler: the strings it refers to, its
imported calls, its distinctive immediate and floating constants (Watcom passes floats as integer
immediates to its runtime, Visual C++ loads them from .rdata, so both become values), and the
shape of its calls. Each pair is scored by the shared signature tokens weighted by rarity; mutual
best pairs above a threshold are anchors, and matches then spread along the call graph: callees in
the same position of two matched functions pair up when their own signatures agree.

usage: v3_signatures.py VERTRIX3_EXE [--json OUT]
"""
import argparse
import hashlib
import json
import math
import re
import struct
from collections import Counter, defaultdict
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from capstone.x86_const import X86_OP_IMM, X86_OP_MEM

ROOT = Path(__file__).resolve().parents[1]

THRESHOLD = 0.45
MARGIN = 1.25


class Image:
    def __init__(self, path):
        self.pe = pefile.PE(str(path))
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        self.image = self.pe.get_memory_mapped_image()
        self.sections = []
        for s in self.pe.sections:
            start = self.base + s.VirtualAddress
            self.sections.append((s.Name.rstrip(b'\0').decode(errors='replace'), start,
                                  start + max(s.Misc_VirtualSize, s.SizeOfRawData),
                                  s.Characteristics))
        self.imports = {}
        for entry in getattr(self.pe, 'DIRECTORY_ENTRY_IMPORT', []):
            for imp in entry.imports:
                self.imports[imp.address] = (imp.name.decode() if imp.name else
                                             '%s#%d' % (entry.dll.decode(), imp.ordinal))
        self.code = [(a, b) for _, a, b, ch in self.sections if ch & 0x20000000]
        self.strings = {}
        for _, start, end, ch in self.sections:
            if not ch & 0x20000000:
                data = self.bytes_at(start, end - start)
                for m in re.finditer(rb'[\x20-\x7e\t\r\n]{4,}\x00', data):
                    self.strings[start + m.start()] = m.group()[:-1].decode()
        self.md = Cs(CS_ARCH_X86, CS_MODE_32)
        self.md.detail = True

    def bytes_at(self, address, size):
        return self.image[address - self.base:address - self.base + size]

    def in_code(self, address):
        return any(a <= address < b for a, b in self.code)

    def in_image(self, address):
        return any(a <= address < b for _, a, b, _ in self.sections)

    def thunk_import(self, address):
        """An import reached through a jmp [iat] thunk."""
        code = self.bytes_at(address, 6)
        if code[:2] == b'\xff\x25':
            return self.imports.get(struct.unpack('<I', code[2:6])[0])
        return None

    def sweep(self, start, end, detail=False):
        """Linear disassembly that steps over undecodable bytes instead of stopping there."""
        data = self.bytes_at(start, end - start)
        offset = 0
        while offset < len(data):
            last = offset
            run = (self.md.disasm(data[offset:], start + offset) if detail else
                   self.md.disasm_lite(data[offset:], start + offset))
            for insn in run:
                yield insn
                last = (insn.address + insn.size if detail else insn[0] + insn[1]) - start
            offset = last + 1 if last < len(data) else last


def float_value(bits):
    """A 32-bit pattern that reads as an ordinary float constant (1.5, 640.0, 0.01), or None."""
    exponent = (bits >> 23) & 0xff
    if bits & 0x7fffffff == 0 or not 0x70 <= exponent <= 0x8f or bits & 0x3ff:
        return None
    return round(struct.unpack('<f', struct.pack('<I', bits))[0], 4)


def features(img, start, end):
    """The compiler-independent signature tokens and calls of the code in [start, end)."""
    tokens, calls = Counter(), []
    for insn in img.sweep(start, end, detail=True):
        if insn.mnemonic in ('ret', 'int3') and insn.address + insn.size >= end:
            break
        if insn.mnemonic == 'call':
            op = insn.operands[0]
            target = None
            if op.type == X86_OP_IMM:
                name = img.thunk_import(op.imm)
                target = ('import', name) if name else ('call', op.imm & 0xffffffff)
            elif op.type == X86_OP_MEM and op.mem.base == 0 and op.mem.index == 0:
                name = img.imports.get(op.mem.disp & 0xffffffff)
                target = ('import', name) if name else ('indirect', None)
            else:
                target = ('indirect', None)
            calls.append(target)
            if target[0] == 'import':
                tokens['i:' + target[1]] += 1
            continue
        for op in insn.operands:
            if op.type == X86_OP_IMM:
                value = op.imm & 0xffffffff
            elif op.type == X86_OP_MEM and op.mem.base == 0 and op.mem.index == 0:
                value = op.mem.disp & 0xffffffff
            else:
                continue
            if value in img.strings:
                tokens['s:' + img.strings[value]] += 1
            elif img.in_image(value):
                if op.type == X86_OP_MEM and insn.mnemonic.startswith('f') and op.size in (4, 8):
                    raw = img.bytes_at(value, op.size)
                    number = struct.unpack('<f' if op.size == 4 else '<d', raw)[0]
                    if number == number and abs(number) < 1e9:
                        tokens['f:%g' % round(number, 4)] += 1
            elif value > 0x40 and value not in (0xffffffff, 0xffff, 0xff00, 0x7fffffff, 0x80000000):
                f = float_value(value)
                tokens['f:%g' % f if f is not None else 'c:%x' % value] += 1
    return dict(tokens=tokens, calls=calls, size=end - start)


def function_starts(img, known=()):
    """The entry, direct call targets, code after padding, and code pointers in data."""
    starts = set(known) | {img.pe.OPTIONAL_HEADER.AddressOfEntryPoint + img.base}
    for a, b in img.code:
        for address, size, mnemonic, operand in img.sweep(a, b):
            if mnemonic == 'call' and operand.startswith('0x'):
                target = int(operand, 16)
                if a <= target < b:
                    starts.add(target)
        data = img.bytes_at(a, b - a)
        for m in re.finditer(rb'(?:\xcc{2,}|\xc3\xcc+|\xc3\x90+)(?=[\x55\x56\x57\x53\x83\x8b\x6a\x81\xa1\xb8])',
                             data):
            starts.add(a + m.end())
    for _, a, b, ch in img.sections:
        if ch & 0x20000000:
            continue
        data = img.bytes_at(a, b - a)
        for i in range(0, len(data) - 3, 4):
            value = struct.unpack_from('<I', data, i)[0]
            if img.in_code(value) and img.bytes_at(value - 1, 1) in (b'\xcc', b'\xc3', b'\x90'):
                starts.add(value)
    return sorted(s for s in starts if img.in_code(s))


def table(img, starts):
    end = max(b for _, b in img.code)
    out = {}
    for i, s in enumerate(starts):
        e = starts[i + 1] if i + 1 < len(starts) else end
        out[s] = features(img, s, min(e, s + 0x8000))
    return out


class Scorer:
    def __init__(self, v2, v3):
        df = Counter()
        for side in (v2, v3):
            for f in side.values():
                df.update(set(f['tokens']))
        n = len(v2) + len(v3)
        self.weight = {t: math.log(n / c) * (2.0 if t.startswith('s:') else 1.0)
                       for t, c in df.items()}
        self.index = defaultdict(set)
        for address, f in v3.items():
            for t in f['tokens']:
                self.index[t].add(address)

    def mass(self, f):
        return sum(self.weight[t] for t in f['tokens'])

    def score(self, a, b):
        ta, tb = set(a['tokens']), set(b['tokens'])
        common = sum(self.weight[t] for t in ta & tb)
        union = sum(self.weight[t] for t in ta | tb)
        size = max(a['size'], b['size']) / max(1, min(a['size'], b['size']))
        return common / union / (1 + 0.1 * max(0, math.log2(size) - 1)) if union else 0.0


def match(v2, v3):
    scorer = Scorer(v2, v3)
    best2, best3 = {}, defaultdict(list)
    for a, f in v2.items():
        if scorer.mass(f) < 6:
            continue
        candidates = set()
        for t in f['tokens']:
            if scorer.weight[t] > 2:
                candidates |= scorer.index[t]
        ranked = sorted(((scorer.score(f, v3[b]), b) for b in candidates), reverse=True)
        if ranked and ranked[0][0] >= THRESHOLD and (len(ranked) == 1 or
                                                    ranked[0][0] >= MARGIN * ranked[1][0]):
            best2[a] = ranked[0]
            best3[ranked[0][1]].append((ranked[0][0], a))
    matches, reasons = {}, {}
    for b, pairs in best3.items():
        pairs.sort(reverse=True)
        if len(pairs) == 1 or pairs[0][0] >= MARGIN * pairs[1][0]:
            score, a = pairs[0]
            matches[a] = b
            reasons[a] = 'signature %.2f' % score
    # Spread along the call graph.
    changed = True
    while changed:
        changed = False
        taken = set(matches.values())
        for a, b in list(matches.items()):
            ca = [c[1] for c in v2[a]['calls'] if c[0] == 'call' and c[1] in v2]
            cb = [c[1] for c in v3[b]['calls'] if c[0] == 'call' and c[1] in v3]
            if not ca or len(ca) != len(cb):
                continue
            for x, y in zip(ca, cb):
                if x in matches or y in taken:
                    continue
                fx, fy = v2[x], v3[y]
                agree = scorer.score(fx, fy)
                silent = not fx['tokens'] and not fy['tokens']
                ratio = max(fx['size'], fy['size']) / max(1, min(fx['size'], fy['size']))
                if agree >= 0.2 or (silent and ratio < 3):
                    matches[x] = y
                    reasons[x] = 'called from %#x' % a
                    taken.add(y)
                    changed = True
        changed |= vote(v2, v3, scorer, matches, reasons)
    return matches, reasons


def neighbours(side):
    callees = {a: {c[1] for c in f['calls'] if c[0] == 'call' and c[1] in side}
               for a, f in side.items()}
    callers = defaultdict(set)
    for a, targets in callees.items():
        for t in targets:
            callers[t].add(a)
    return callees, callers


def vote(v2, v3, scorer, matches, reasons):
    """Pair an unmatched function with the one whose matched callers and callees agree with
    its own: at least two agreeing neighbours, a unique best, and no contradicting signature."""
    callees2, callers2 = neighbours(v2)
    callees3, callers3 = neighbours(v3)
    taken = set(matches.values())
    found = {}
    for a in v2:
        if a in matches:
            continue
        votes = Counter()
        for c in callees2[a]:
            if c in matches:
                for y in callers3[matches[c]]:
                    votes[y] += 1
        for c in callers2[a]:
            if c in matches:
                for y in callees3[matches[c]]:
                    votes[y] += 1
        ranked = [(n, y) for y, n in votes.most_common(2) if y not in taken]
        if not ranked or ranked[0][0] < 2 or (len(ranked) > 1 and ranked[1][0] == ranked[0][0]):
            continue
        n, y = ranked[0]
        fx, fy = v2[a], v3[y]
        ratio = max(fx['size'], fy['size']) / max(1, min(fx['size'], fy['size']))
        if ratio > 4 or ((fx['tokens'] or fy['tokens']) and scorer.score(fx, fy) < 0.15):
            continue
        found.setdefault(y, []).append((n, a))
    added = False
    for y, pairs in found.items():
        if len(pairs) == 1:
            n, a = pairs[0]
            matches[a] = y
            reasons[a] = 'neighbours %d' % n
            added = True
    return added


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('vertrix3', type=Path)
    parser.add_argument('--json', type=Path, default=ROOT / 'docs' / 'v3-signature-matches.json')
    args = parser.parse_args()
    digest = hashlib.sha256(args.vertrix3.read_bytes()).hexdigest()
    names = json.loads((ROOT / 'docs' / 'names.json').read_text())
    ports = json.loads((ROOT / 'docs' / 'ports.json').read_text())
    i2, i3 = Image(ROOT / 'Vertrix2.exe'), Image(args.vertrix3)
    known = {int(a, 16) for a in list(names) + list(ports)}
    v2 = table(i2, function_starts(i2, known))
    v3 = table(i3, function_starts(i3))
    matches, reasons = match(v2, v3)
    rows = []
    for a in sorted(matches):
        h = '%#x' % a
        entry = ports.get(h)
        strings = sorted(t[2:] for t in v2[a]['tokens'] if t.startswith('s:'))
        rows.append(dict(vertrix2=h, vertrix3='%#x' % matches[a], name=names.get(h),
                         port=entry.get('port') if isinstance(entry, dict) else None,
                         by=reasons[a], strings=strings[:3]))
    kinds = Counter(r.split()[0] for r in reasons.values())
    summary = dict(vertrix3_sha256=digest, vertrix2_functions=len(v2), vertrix3_functions=len(v3),
                   matched=len(rows), matched_known=sum(1 for r in rows if int(r['vertrix2'], 16) in known),
                   matched_ported=sum(1 for r in rows if r['port']), by=dict(kinds))
    args.json.write_text(json.dumps(dict(summary, matches=rows), indent=1) + '\n')
    print(json.dumps(summary))


if __name__ == '__main__':
    main()
