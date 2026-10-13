"""Remove the lifted routines that nothing in the original can reach.

usage: drop_unreachable.py [--dry-run]

A routine is reachable when it is the entry point, when its address appears as a dword anywhere in
the original executable (code and data alike: method tables, callback tables and every absolute
operand), when hand-written source names its address, or when a reachable lifted routine names
it. Every other lifted routine (verified chunk or unverified tier) is deleted with its metadata;
docs/unreachable.json records each one. Clean and native ports are never touched. tools/lift.py
lifts any of them again from the original if one is ever needed. Running it again changes
nothing."""
import glob
import json
import re
import struct
import sys
from collections import defaultdict
from pathlib import Path

import pefile

from dispatch_boundaries import NATIVE_PORTS, NATIVE_UNVERIFIED_BOUNDARIES, PORTS
from drop_ported import drop
from lift import EXE

ROOT = Path(__file__).resolve().parents[1]
SCREENS = {'game_screen', 'hud_decor', 'select_screen', 'title_screen'}


def lifted_routines():
    """{address: (chunk, name)} for every lifted routine in a chunk or the unverified tier."""
    routines = {}
    for path in sorted(glob.glob(str(ROOT / 'docs' / 'lift' / '*.json'))):
        chunk = Path(path).stem
        if chunk in SCREENS:
            continue
        for name, meta in json.loads(Path(path).read_text()).items():
            routines[meta['address']] = (chunk, name)
    return routines


def main():
    routines = lifted_routines()
    kept = set(PORTS) | set(NATIVE_PORTS) | set(NATIVE_UNVERIFIED_BOUNDARIES)
    known = set(routines) | kept
    pe = pefile.PE(str(EXE))
    roots = {pe.OPTIONAL_HEADER.ImageBase + pe.OPTIONAL_HEADER.AddressOfEntryPoint}
    for section in pe.sections:
        data = section.get_data()
        for offset in range(len(data) - 3):
            value = struct.unpack_from('<I', data, offset)[0]
            if value in known:
                roots.add(value)
    constant = re.compile(r'\b0x([0-9a-fA-F]{6})u?\b')
    for path in glob.glob(str(ROOT / 'source' / '*.[ch]')):
        if Path(path).name.startswith('lifted_'):
            continue
        roots |= {int(c, 16) for c in constant.findall(Path(path).read_text())} & known
    roots |= kept
    by_name = {'lifted_' + name: address for address, (chunk, name) in routines.items()}
    edges = defaultdict(set)
    for path in glob.glob(str(ROOT / 'source' / 'lifted_*.c')):
        current = None
        for line in Path(path).read_text().splitlines():
            match = re.match(r'uint32_t (lifted_\w+)\(', line)
            if match:
                current = by_name.get(match.group(1))
                continue
            if current is not None:
                edges[current] |= {int(c, 16) for c in constant.findall(line)} & known
    reached = set()
    pending = list(roots)
    while pending:
        address = pending.pop()
        if address not in reached:
            reached.add(address)
            pending.extend(edges[address])
    unreachable = sorted(set(routines) - reached)
    print('%d lifted routines, %d reachable, %d unreachable'
          % (len(routines), len(set(routines) & reached), len(unreachable)))
    if '--dry-run' in sys.argv:
        return
    record_path = ROOT / 'docs' / 'unreachable.json'
    record = json.loads(record_path.read_text()) if record_path.exists() else {}
    by_chunk = defaultdict(list)
    for address in unreachable:
        by_chunk[routines[address][0]].append(address)
    for chunk, addresses in by_chunk.items():
        meta_path = ROOT / 'docs' / 'lift' / (chunk + '.json')
        metas = json.loads(meta_path.read_text())
        for address in addresses:
            name = routines[address][1]
            drop(chunk, name, address)
            del metas[name]
            record['0x%x' % address] = {'lifted': 'lifted_' + name, 'chunk': chunk}
        meta_path.write_text(json.dumps(metas, indent=1))
        if chunk == 'unverified':
            list_path = ROOT / 'docs' / 'lift' / 'unverified-list.txt'
            if list_path.exists():
                names = {'f%x' % a for a in addresses}
                lines = [line for line in list_path.read_text().splitlines()
                         if line.strip() not in names]
                list_path.write_text('\n'.join(lines) + '\n')
    record_path.write_text(json.dumps(dict(sorted(record.items())), indent=1) + '\n')


if __name__ == '__main__':
    main()
