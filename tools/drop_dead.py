"""Remove lifted routines that nothing calls any more.

usage: drop_dead.py [--dry-run]

A lifted routine is dead when no source, header or tool outside its own chunk names it: the
dispatcher serves its address from a native routine or a port (or never serves it), and no other
lifted routine calls it directly. Each dead routine is deleted from its chunk
(source/lifted_*.c and .h) and from the chunk's metadata (docs/lift/*.json); a chunk left
empty goes with its files. tools/verify_port.py lifts a routine again from the original whenever
it checks a port, so nothing is lost. Running it again changes nothing."""
import glob
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
NAME = re.compile(r'\blifted_\w+\b')


def definitions():
    found = {}
    for path in sorted(glob.glob(str(ROOT / 'source' / 'lifted_*.c'))):
        chunk = Path(path).stem[len('lifted_'):]
        text = Path(path).read_text()
        for m in re.finditer(r'^uint32_t (lifted_\w+)\(', text, re.M):
            found[m.group(1)] = chunk
    return found


def users():
    """Each lifted name and the files that mention it."""
    seen = {}
    paths = glob.glob(str(ROOT / 'source' / '*.[ch]')) + glob.glob(str(ROOT / 'tools' / '*.[ch]'))
    paths += glob.glob(str(ROOT / 'tools' / '*.py'))
    for path in paths:
        for name in set(NAME.findall(Path(path).read_text())):
            seen.setdefault(name, set()).add(Path(path).name)
    return seen


def drop(chunk, name):
    source_path = ROOT / 'source' / ('lifted_%s.c' % chunk)
    header_path = ROOT / 'source' / ('lifted_%s.h' % chunk)
    source = source_path.read_text()
    start = source.index('\nuint32_t %s(' % name) + 1
    comment = source.rfind('\n/* ', 0, start - 1)
    if comment >= 0 and source[comment:start].count('*/') == 1 and \
            source[comment:start].rstrip().endswith('*/'):
        start = comment + 1
    end = source.index('\n}\n', start) + 3
    if source[end:end + 1] == '\n':
        end += 1
    source_path.write_text(source[:start] + source[end:])
    header = header_path.read_text()
    header = re.sub(r'\n    %s_STACK = \d+,?' % name.upper(), '', header)
    header = re.sub(r'(/\* Original 0x[0-9a-f]+\. \*/\n)?uint32_t %s\([^;]*\);\n\n?' % name, '',
                    header)
    header_path.write_text(re.sub(r',\n};', '\n};', header))


def drop_meta(chunk, name):
    meta_path = ROOT / 'docs' / 'lift' / ('%s.json' % chunk)
    if not meta_path.exists():
        return None
    metas = json.loads(meta_path.read_text())
    for key in list(metas):
        if 'lifted_' + key == name or key == name:
            del metas[key]
    meta_path.write_text(json.dumps(metas, indent=1))
    return metas


def main():
    dry = '--dry-run' in sys.argv
    defined = definitions()
    mentions = users()
    dead = []
    for name, chunk in sorted(defined.items()):
        own = {'lifted_%s.c' % chunk, 'lifted_%s.h' % chunk}
        others = mentions.get(name, set()) - own
        own_source = (ROOT / 'source' / ('lifted_%s.c' % chunk)).read_text()
        inside = len(re.findall(r'\b%s\b' % name, own_source)) > 1
        if not others and not inside:
            dead.append((chunk, name))
    for chunk, name in dead:
        print('dead', name, 'in', chunk)
        if dry:
            continue
        drop(chunk, name)
        metas = drop_meta(chunk, name)
        source = (ROOT / 'source' / ('lifted_%s.c' % chunk)).read_text()
        if metas == {} and not re.search(r'^uint32_t lifted_\w+\(', source, re.M):
            for emptied in (ROOT / 'docs' / 'lift' / ('%s.json' % chunk),
                            ROOT / 'source' / ('lifted_%s.c' % chunk),
                            ROOT / 'source' / ('lifted_%s.h' % chunk)):
                emptied.unlink()
            print('chunk', chunk, 'emptied')
    print('dropped' if not dry else 'would drop', len(dead), 'dead lifted routines')


if __name__ == '__main__':
    main()
