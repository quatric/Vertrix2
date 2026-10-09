"""Replace verified routines in their lifted chunks with a new, re-verified lift.

usage: replace_lifted.py SCRATCH ADDRESS...

For each address, the chunk whose docs/lift/<chunk>.json lists it gets the function from
SCRATCH/f<address>.c (renamed to the chunk's name for it), the new stack size in
source/lifted_<chunk>.h, and the new metadata. Run it after a lifter fix changes a routine that is
already verified, and only once the new lift passes tools/verify_one.py."""
import glob
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def chunk_of(address):
    for path in sorted(glob.glob(str(ROOT / 'docs' / 'lift' / '*.json'))):
        if 'unverified' in path:
            continue
        metas = json.loads(Path(path).read_text())
        for pretty, meta in metas.items():
            if isinstance(meta, dict) and meta.get('address') == address:
                return Path(path).stem, pretty, metas
    raise SystemExit('0x%x is in no verified chunk' % address)


def main():
    scratch = Path(sys.argv[1])
    touched = set()
    for text in sys.argv[2:]:
        address = int(text, 16)
        name = 'f%x' % address
        chunk, pretty, metas = chunk_of(address)
        lifted = (scratch / (name + '.c')).read_text()
        function = lifted[lifted.index('uint32_t lifted_'):]
        meta = json.loads((scratch / (name + '.json')).read_text())
        if pretty != name:
            function = function.replace('lifted_%s(' % name, 'lifted_%s(' % pretty)
            function = function.replace('LIFTED_%s_STACK' % name.upper(),
                                        'LIFTED_%s_STACK' % pretty.upper())
        source_path = ROOT / 'source' / ('lifted_%s.c' % chunk)
        source = source_path.read_text()
        start = source.index('\nuint32_t lifted_%s(' % pretty) + 1
        end = source.index('\n}\n', start) + 3
        source = source[:start] + function.rstrip('\n') + '\n' + source[end:]
        source_path.write_text(source)
        header_path = ROOT / 'source' / ('lifted_%s.h' % chunk)
        header = re.sub(r'(LIFTED_%s_STACK = )\d+' % pretty.upper(),
                        lambda m: m.group(1) + str(meta['stack']), header_path.read_text())
        header_path.write_text(header)
        metas[pretty] = meta
        (ROOT / 'docs' / 'lift' / (chunk + '.json')).write_text(json.dumps(metas, indent=1))
        touched.update({source_path, header_path})
        print('replaced 0x%x in %s' % (address, chunk))
    subprocess.run(['clang-format', '-i', '--style=file:' + str(ROOT / '.clang-format')] +
                   [str(p) for p in sorted(touched)], check=True)


if __name__ == '__main__':
    main()
