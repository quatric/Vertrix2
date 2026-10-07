"""List the lifted routines that also have a hand-recovered port, and whether that port has a
passing verification record. Writes docs/lifted-overlap.json.

A hand port is a function in a non-lifted source file whose comment says "Original 0x<address>"
(or lists the address among the routines it covers). A verification record is a
docs/*-verification.json with status "passed" whose scope names the address."""
import glob
import json
import os
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
lifted = {}
for path in glob.glob(str(ROOT / 'docs' / 'lift' / '*.json')):
    data = json.loads(Path(path).read_text())
    if 'stack' in data:
        continue
    for name, meta in data.items():
        lifted[meta['address']] = name

ports = {}  # address -> set of files
pattern = re.compile(r'0x(4[0-9a-fA-F]{5})\b')
for path in glob.glob(str(ROOT / 'source' / '*.[ch]')):
    base = os.path.basename(path)
    if base.startswith(('lifted_', 'lift_')):
        continue
    text = Path(path).read_text()
    for comment in re.findall(r'/\*.*?\*/', text, re.S):
        if not re.search(r'[Oo]riginal|[Rr]ecovers?|[Pp]ort', comment):
            continue
        for found in pattern.findall(comment):
            ports.setdefault(int(found, 16), set()).add(base)

verified = {}  # address -> set of verification records
for path in glob.glob(str(ROOT / 'docs' / '*verification*.json')):
    try:
        data = json.loads(Path(path).read_text())
    except ValueError:
        continue
    if not isinstance(data, dict) or data.get('status') != 'passed':
        continue
    executions = data.get('complete_original_executions', {})
    scope = str(data.get('scope', '')) + ' ' + (' '.join(map(str, executions))
                                              if isinstance(executions, dict) else '')
    for found in re.findall(r'\b(?:0x)?(4[0-9a-fA-F]{5})\b', scope):
        verified.setdefault(int(found, 16), set()).add(os.path.basename(path))

rows = {}
for address, name in sorted(lifted.items()):
    rows[hex(address)] = {
        'lifted': name,
        'hand_files': sorted(ports.get(address, [])),
        'verification': sorted(verified.get(address, [])),
    }
both = [a for a, r in rows.items() if r['hand_files'] and r['verification']]
(ROOT / 'docs' / 'lifted-overlap.json').write_text(json.dumps(rows, indent=1))
print('lifted', len(rows), 'with a hand port', sum(1 for r in rows.values() if r['hand_files']),
      'with a passing verification record', sum(1 for r in rows.values() if r['verification']),
      'both', len(both))
