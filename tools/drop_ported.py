"""Remove the lifted copies of the routines that have clean ports (PORTS in dispatch_boundaries.py).

usage: drop_ported.py

For each port, the lifted routine is deleted from its chunk (source/lifted_whole_N.c and .h) and
from the chunk's metadata (docs/lift/whole_N.json); docs/ports.json records which lifted routine
each port replaced. tools/verify_port.py lifts the routine again from the original whenever it
checks a port, so nothing is lost. Running it again changes nothing."""
import glob
import json
import re
from pathlib import Path

from dispatch_boundaries import PORTS

ROOT = Path(__file__).resolve().parents[1]


def drop(chunk, name, address):
    source_path = ROOT / 'source' / ('lifted_%s.c' % chunk)
    header_path = ROOT / 'source' / ('lifted_%s.h' % chunk)
    source = source_path.read_text()
    start = source.index('\nuint32_t lifted_%s(' % name) + 1
    end = source.index('\n}\n', start) + 3
    if source[end:end + 1] == '\n':
        end += 1
    source_path.write_text(source[:start] + source[end:])
    header = header_path.read_text()
    header = re.sub(r'\n    LIFTED_%s_STACK = \d+,?' % name.upper(), '', header)
    header = re.sub(r'(/\* Original 0x%x\. \*/\n)?uint32_t lifted_%s\([^;]*\);\n\n?'
                    % (address, name), '', header)
    header_path.write_text(re.sub(r',\n};', '\n};', header))


def main():
    record_path = ROOT / 'docs' / 'ports.json'
    record = json.loads(record_path.read_text()) if record_path.exists() else {}
    dropped = 0
    for path in sorted(glob.glob(str(ROOT / 'docs' / 'lift' / 'whole_*.json'))):
        chunk = Path(path).stem
        metas = json.loads(Path(path).read_text())
        names = [name for name, meta in metas.items() if meta['address'] in PORTS]
        for name in names:
            address = metas[name]['address']
            drop(chunk, name, address)
            record['0x%x' % address] = {'port': PORTS[address], 'lifted': 'lifted_' + name,
                                        'chunk': chunk}
            del metas[name]
            dropped += 1
        if names:
            Path(path).write_text(json.dumps(metas, indent=1))
    record_path.write_text(json.dumps(dict(sorted(record.items())), indent=1) + '\n')
    print('dropped', dropped, 'lifted copies;', len(record), 'ports recorded')


if __name__ == '__main__':
    main()
