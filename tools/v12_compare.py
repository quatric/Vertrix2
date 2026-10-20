"""Compare Vertrix 2 v1.2 (2001) with v2.0 (2003), the version the ports come from.

Both executables come from the same Watcom linker, so a routine that did not change between the
versions has the same instructions, only moved: its branch displacements and the absolute
addresses the loader relocates differ. Each function is reduced to its instruction bytes with
those fields masked (relocated dwords from .reloc, rel8/rel32 branch and call displacements), and
functions are paired when the masked bytes are equal and the pairing is unique. Pairs then
spread through the call graph: when two paired functions call, at the same call site, functions
of equal length and equal masked bytes up to the calls, the callees pair too.

usage: v12_compare.py V20_EXE V12_EXE DISPATCH_C OUT_JSON
"""

import hashlib
import json
import re
import sys
from collections import defaultdict
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from capstone import x86 as X

sys.path.insert(0, str(Path(__file__).resolve().parent))
from v3_signatures import Image, function_starts  # noqa: E402

V20_SHA256 = '4db546b7957136179bedf22a37b7e5db401ea25bc668b715643adf84ce525e28'
V12_SHA256 = '8e27c76d75c28dba6b39f9e9e6162e04b04d712771cb4b03c4d9eb9ef4141999'


def relocations(pe):
    out = set()
    pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY['IMAGE_DIRECTORY_ENTRY_BASERELOC']])
    for block in getattr(pe, 'DIRECTORY_ENTRY_BASERELOC', []):
        for entry in block.entries:
            if entry.type == 3:  # HIGHLOW
                out.add(pe.OPTIONAL_HEADER.ImageBase + entry.rva)
    return out


class Side:
    def __init__(self, path, sha, known=()):
        data = Path(path).read_bytes()
        if hashlib.sha256(data).hexdigest() != sha:
            sys.exit('%s: not the expected executable' % path)
        self.img = Image(path)
        self.relocs = relocations(self.img.pe)
        self.starts = function_starts(self.img, known)
        end = max(b for _, b in self.img.code)
        self.extent = {}
        for i, s in enumerate(self.starts):
            self.extent[s] = (s, min(self.starts[i + 1] if i + 1 < len(self.starts) else end,
                                     s + 0x10000))
        self.md = Cs(CS_ARCH_X86, CS_MODE_32)
        self.md.detail = True
        self.masked = {}
        self.calls = {}
        for s, (a, b) in self.extent.items():
            self.masked[s], self.calls[s] = self.reduce(a, b)

    def reduce(self, a, b):
        """The masked bytes of [a, b) up to the function's last return, and its direct calls."""
        out = bytearray()
        calls = []
        last_end = a
        for ins in self.md.disasm(self.img.bytes_at(a, b - a), a):
            raw = bytearray(ins.bytes)
            for k in range(ins.size - 3):
                if ins.address + k in self.relocs:
                    raw[k:k + 4] = b'\0\0\0\0'
            if ins.group(X.X86_GRP_JUMP) or ins.group(X.X86_GRP_CALL):
                op = ins.operands[0] if ins.operands else None
                if op is not None and op.type == X.X86_OP_IMM:
                    width = 1 if ins.size == 2 else 4  # short branches: rel8
                    raw[ins.size - width:] = b'\0' * width
                    if ins.mnemonic == 'call':
                        calls.append((len(out), op.imm))
            out += raw
            if ins.mnemonic in ('ret', 'retf') or (ins.mnemonic == 'jmp' and ins.address + ins.size
                                                   >= b - 1):
                last_end = len(out)
        return bytes(out[:last_end] if last_end > 0 else out), calls


def main():
    v20_path, v12_path, dispatch_path, out_path = sys.argv[1:5]
    known = [int(m, 16) for m in re.findall(r'\{(0x4[0-9a-f]{5})u?,',
                                            Path(dispatch_path).read_text())]
    v20 = Side(v20_path, V20_SHA256, known)
    v12 = Side(v12_path, V12_SHA256)
    print('functions: v2.0 %d (%d dispatched), v1.2 %d' % (len(v20.starts), len(set(known)),
                                                           len(v12.starts)))

    by_bytes = defaultdict(lambda: ([], []))
    for s, m in v20.masked.items():
        by_bytes[m][0].append(s)
    for s, m in v12.masked.items():
        by_bytes[m][1].append(s)
    pairs = {}
    for m, (a, b) in by_bytes.items():
        if len(a) == 1 and len(b) == 1 and len(m) >= 8:
            pairs[a[0]] = (b[0], 'bytes')

    # Spread through call sites of paired functions with equal masked bytes.
    changed = True
    while changed:
        changed = False
        taken = {v for v, _ in pairs.values()}
        for s20, (s12, _) in list(pairs.items()):
            c20, c12 = v20.calls.get(s20, []), v12.calls.get(s12, [])
            if v20.masked[s20] != v12.masked[s12] or len(c20) != len(c12):
                continue
            for (o20, t20), (o12, t12) in zip(c20, c12):
                if o20 != o12 or t20 in pairs or t12 in taken:
                    continue
                if t20 in v20.masked and t12 in v12.masked:
                    pairs[t20] = (t12, 'call site')
                    taken.add(t12)
                    changed = True

    dispatched = set(known)
    same = {a: b for a, (b, _) in pairs.items()}
    covered = [a for a in dispatched if a in same]
    v20_bytes = sum(len(v20.masked[a]) for a in v20.starts)
    same_bytes = sum(len(v20.masked[a]) for a in same)
    print('identical routines: %d of %d v2.0 functions (%.1f%% of its code), %d of %d dispatched'
          % (len(same), len(v20.starts), 100.0 * same_bytes / v20_bytes, len(covered),
             len(dispatched)))
    result = {
        'v20_sha256': V20_SHA256,
        'v12_sha256': V12_SHA256,
        'v20_functions': len(v20.starts),
        'v12_functions': len(v12.starts),
        'identical': {'%#x' % a: '%#x' % b for a, b in sorted(same.items())},
        'v20_unmatched': ['%#x' % a for a in v20.starts if a not in same],
        'v12_unmatched': ['%#x' % b for b in v12.starts if b not in set(same.values())],
    }
    Path(out_path).write_text(json.dumps(result, indent=1) + '\n')


if __name__ == '__main__':
    main()
