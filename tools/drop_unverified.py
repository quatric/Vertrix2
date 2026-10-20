"""Remove routines from the unverified lifted tier once a verified copy exists.

usage: drop_unverified.py ADDRESS...

Edits docs/lift/unverified.json, docs/lift/unverified-list.txt, source/lifted_unverified.c and
source/lifted_unverified.h, so a routine combined into a verified chunk is not defined twice."""
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def main():
    addresses = {int(a, 16) for a in sys.argv[1:]}
    meta_path = ROOT / 'docs' / 'lift' / 'unverified.json'
    metas = json.loads(meta_path.read_text())
    names = [name for name, meta in metas.items() if meta['address'] in addresses]
    for name in names:
        del metas[name]
    meta_path.write_text(json.dumps(metas, indent=1))
    list_path = ROOT / 'docs' / 'lift' / 'unverified-list.txt'
    if list_path.exists():
        drop = {'f%x' % a for a in addresses}
        lines = [line for line in list_path.read_text().splitlines() if line.strip() not in drop]
        list_path.write_text('\n'.join(lines) + '\n')
    source_path = ROOT / 'source' / 'lifted_unverified.c'
    source = source_path.read_text()
    header_path = ROOT / 'source' / 'lifted_unverified.h'
    header = header_path.read_text()
    for name in names:
        start = source.index('\nuint32_t lifted_%s(' % name) + 1
        end = source.index('\n}\n', start) + 3
        if source[end:end + 1] == '\n':
            end += 1
        source = source[:start] + source[end:]
        header = re.sub(r'\n    LIFTED_%s_STACK = \d+,?' % name.upper(), '', header)
        header = re.sub(r'/\* Original 0x[0-9a-f]+\. \*/\nuint32_t lifted_%s\([^;]*\);\n\n?' % name,
                        '', header)
    header = re.sub(r',\n};', '\n};', header)
    # With no routine left the stack sizes' enum is empty, which C does not allow.
    header = re.sub(r'\nenum\n\{\n\};\n', '\n', header)
    source_path.write_text(source)
    header_path.write_text(header)
    print('dropped', len(names), 'of', len(addresses))


if __name__ == '__main__':
    main()
