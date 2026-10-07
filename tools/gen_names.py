"""Collect readable names for original routines from the recovered headers.

A header comment 'Original 0xADDR ...' directly above a prototype names that routine. The result
(docs/names.json, address -> name) feeds tools/rename_lifted.py; names are the recovered
functions' own, never guesses.
"""
import json
import re
from pathlib import Path

root = Path(__file__).resolve().parents[1]
names = {}
comment = re.compile(r'/\*\s*(?:Originals?|Original routines?)\s+((?:0x[0-9a-f]+[,\s]*(?:and\s+)?)+)', re.I)
proto = re.compile(r'^\s*(?:static\s+inline\s+)?[A-Za-z_][\w\s\*]*?\b(vertrix_\w+)\s*\(', re.M)
for header in sorted((root / 'source').glob('*.h')):
    if header.name.startswith(('lifted_', 'lift_')):
        continue
    text = header.read_text()
    for match in comment.finditer(text):
        addresses = re.findall(r'0x([0-9a-f]+)', match.group(1))
        end = text.find('*/', match.end())
        found = proto.search(text, end if end >= 0 else match.end())
        if not found or not addresses:
            continue
        # the first listed address names the prototype that follows the comment
        names.setdefault(int(addresses[0], 16), found.group(1))
(root / 'docs' / 'names.json').write_text(
    json.dumps({'0x%x' % a: n for a, n in sorted(names.items())}, indent=1) + '\n')
print(len(names), 'names')
