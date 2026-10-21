"""Check a recompiled game's function discovery against a disassembler's function list.

    rea_coverage.py EXE GEN_DIR FUNCTIONS OUT.json

FUNCTIONS is the function list from rea's Rizin provider (`execute_rizin_command` with
`aaa; aflq > FILE`, one `0xADDRESS name` per line; any file whose lines start with an address
works). GEN_DIR is the recompiler's output (`vertrix3/recomp.py EXE GEN_DIR`): every instruction
it translated is a `L_<address>:` label there.

A function the list has and the generated code does not is code the recompiler never reached. It
matters only if something can still reach it. Each one belongs to a run of code the recompiler
did not translate (from the end of the last translated instruction before it). Entering a run
takes a branch or a pointer into it: a call, jmp or conditional jump (rel8 or rel32) whose target
lies in the run, or an address in it that the image holds (a base relocation's dword: an
immediate in code or a pointer in a table). A branch from translated
code, or a relocated address, makes the run reachable; a branch from untranslated code means that
code's run is walked in turn. The report lists each group of runs and what refers to its roots.
"""
import bisect
import json
import re
import struct
import sys
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs


def main():
    exe, gen_dir, functions, out = sys.argv[1:5]
    pe = pefile.PE(exe)
    base = pe.OPTIONAL_HEADER.ImageBase
    image = bytes(pe.get_memory_mapped_image())
    # Watcom leaves VirtualSize at 0; the section then spans its raw data (as in recomp.py).
    code = [(base + s.VirtualAddress,
             base + s.VirtualAddress + max(s.Misc_VirtualSize, s.SizeOfRawData))
            for s in pe.sections if s.Characteristics & 0x20000000]
    md = Cs(CS_ARCH_X86, CS_MODE_32)

    translated = set()
    for path in sorted(Path(gen_dir).glob('v3_code_*.c')):
        translated.update(int(m, 16) for m in re.findall(r'^L_([0-9a-f]+):', path.read_text(),
                                                          re.M))
    ordered = sorted(translated)
    listed = set()
    for line in Path(functions).read_text().splitlines():
        if line.strip():
            listed.add(int(line.split()[0], 16))
    missed = sorted(listed - translated)

    def run_of(a):
        """The untranslated run holding a: from the end of the translated instruction before it
        to the next translated instruction."""
        i = bisect.bisect_right(ordered, a)
        start = code[0][0]
        if i > 0:
            p = ordered[i - 1]
            ins = next(md.disasm(image[p - base:p - base + 16], p), None)
            start = p + (ins.size if ins else 1)
        end = ordered[i] if i < len(ordered) else code[-1][1]
        return start, end

    # Every branch of the code sections by target: e8/e9 rel32, eb and 70-7f rel8, 0f 80-8f rel32.
    # Read at every byte, so some are not real instructions; they only ever add callers.
    branches = {}
    for start, end in code:
        for a in range(start, end - 6):
            o = a - base
            op = image[o]
            if op in (0xe8, 0xe9):
                target = a + 5 + struct.unpack_from('<i', image, o + 1)[0]
            elif op == 0xeb or 0x70 <= op <= 0x7f:
                target = a + 2 + struct.unpack_from('<b', image, o + 1)[0]
            elif op == 0x0f and 0x80 <= image[o + 1] <= 0x8f:
                target = a + 6 + struct.unpack_from('<i', image, o + 2)[0]
            else:
                continue
            branches.setdefault(target, []).append(a)
    targets = sorted(branches)
    # Every address the image holds, in code (immediates) or data (tables): the loader relocates
    # each one, so the base relocations list them all.
    dwords = {}
    for block in pe.DIRECTORY_ENTRY_BASERELOC:
        for entry in block.entries:
            if entry.type == 3:  # IMAGE_REL_BASED_HIGHLOW
                v = struct.unpack_from('<I', image, entry.rva)[0]
                dwords.setdefault(v, []).append(base + entry.rva)
    pointed = sorted(dwords)

    def switch_table(site):
        """The translated `jmp [index*4 + table]` whose table address is at site (the
        recompiler read that table as a switch, and what lies there is data), or None."""
        i = bisect.bisect_right(ordered, site)
        if i == 0:
            return None
        p = ordered[i - 1]
        ins = next(md.disasm(image[p - base:p - base + 16], p), None)
        if (ins is not None and p <= site < p + ins.size and ins.mnemonic == 'jmp'
                and '[' in ins.op_str):
            return p
        return None

    def into(sorted_keys, table, start, end):
        lo, hi = bisect.bisect_left(sorted_keys, start), bisect.bisect_left(sorted_keys, end)
        return [(k, s) for k in sorted_keys[lo:hi] for s in table[k]]

    groups, seen, switch_tables = [], set(), set()
    for first in missed:
        if run_of(first) in seen:
            continue
        runs, roots, todo = set(), {}, [run_of(first)]
        while todo:
            run = todo.pop()
            if run in runs:
                continue
            runs.add(run)
            entries = [(t, s) for t, s in into(targets, branches, *run)
                       if not run[0] <= s < run[1]]
            data = [(t, d) for t, d in into(pointed, dwords, *run) if not run[0] <= d < run[1]]
            tables = [(t, d) for t, d in data if switch_table(d) is not None]
            data = [(t, d) for t, d in data if (t, d) not in tables]
            switch_tables.update('%#x (read by the switch at %#x)' % (t, switch_table(d))
                                 for t, d in tables)
            from_code = [(t, s) for t, s in entries if s in translated]
            if from_code or data:
                roots['%#x-%#x' % run] = {
                    'from_translated_code': ['%#x -> %#x' % (s, t) for t, s in from_code],
                    'dwords_holding_it': ['%#x = %#x' % (d, t) for t, d in data]}
            todo.extend(run_of(s) for t, s in entries if s not in translated)
        seen |= runs
        inside = sorted(f for f in missed if any(s <= f < e for s, e in runs))
        groups.append({'functions': [hex(f) for f in inside],
                       'runs': ['%#x-%#x' % r for r in sorted(runs)],
                       'roots': roots,
                       'reachable': bool(roots)})

    report = {'executable': Path(exe).name,
              'functions_listed': len(listed),
              'instructions_translated': len(translated),
              'listed_but_not_translated': len(missed),
              'switch_tables_listed_as_code': sorted(switch_tables),
              'groups': groups}
    Path(out).write_text(json.dumps(report, indent=1) + '\n')
    reachable = [g for g in groups if g['reachable']]
    print('%d listed, %d not translated, in %d groups; %d groups referenced; switch tables: %s'
          % (len(listed), len(missed), len(groups), len(reachable),
             ', '.join(sorted(switch_tables)) or 'none'))
    for g in reachable:
        print('referenced:', g['functions'], g['roots'])


if __name__ == '__main__':
    main()
