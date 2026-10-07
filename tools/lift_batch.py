"""Lift many routines, verify each against the original and combine the verified ones.

usage: lift_batch.py lift SCRATCH ADDRESS...
       lift_batch.py verify SCRATCH [--jobs N] [--cases N]
       lift_batch.py combine SCRATCH NAME OUT_DIR
"""
import json
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

import lift

ROOT = Path(__file__).resolve().parents[1]


def lift_all(scratch, addresses):
    scratch.mkdir(parents=True, exist_ok=True)
    skipped = {}
    for address in addresses:
        name = 'f%x' % address
        try:
            text, header, meta = lift.render(address, name, lift.return_arguments(address))
        except Exception as error:  # noqa: BLE001 - recorded per routine
            skipped['%x' % address] = '%s: %s' % (type(error).__name__, error)
            continue
        (scratch / (name + '.c')).write_text(text)
        (scratch / ('lifted_%s.h' % name)).write_text(header)
        meta['address'] = address
        (scratch / (name + '.json')).write_text(json.dumps(meta))
    (scratch / 'skipped.json').write_text(json.dumps(skipped, indent=1))
    print('lifted', len(addresses) - len(skipped), 'skipped', len(skipped))


def verify_one(scratch, name, cases):
    last = ''
    for mode in ('wide', 'small'):
        command = [sys.executable, str(Path(__file__).with_name('verify_one.py')), str(scratch),
                   name, str(cases), mode]
        try:
            done = subprocess.run(command, capture_output=True, text=True, timeout=600,
                                  cwd=ROOT / 'tools')
        except subprocess.TimeoutExpired:
            last = 'timeout'
            continue
        if done.returncode == 0:
            return name, True, ''
        last = (done.stderr.strip().splitlines() or [''])[-1][:200]
    return name, False, last


def verify_all(scratch, jobs, cases):
    names = sorted(p.stem for p in scratch.glob('f*.c'))
    results = {}
    with ThreadPoolExecutor(jobs) as pool:
        for name, ok, detail in pool.map(lambda n: verify_one(scratch, n, cases), names):
            results[name] = {'ok': ok, 'detail': detail}
    (scratch / 'results.json').write_text(json.dumps(results, indent=1))
    passed = [n for n, r in results.items() if r['ok']]
    print('passed', len(passed), 'of', len(names))
    failures = {}
    for n, r in results.items():
        if not r['ok']:
            failures.setdefault(r['detail'], []).append(n)
    for detail, group in sorted(failures.items(), key=lambda item: -len(item[1])):
        print(len(group), detail, group[:3])


def readable_names():
    """address -> short name from docs/names.json (first address wins a name)."""
    path = ROOT / 'docs' / 'names.json'
    if not path.exists():
        return {}
    taken, result = set(), {}
    for address, full in sorted(json.loads(path.read_text()).items(), key=lambda i: int(i[0], 16)):
        short = full[len('vertrix_'):] if full.startswith('vertrix_') else full
        if short not in taken:
            taken.add(short)
            result[int(address, 16)] = short
    return result


def combine(scratch, name, out_dir, first=0, count=None):
    results = json.loads((scratch / 'results.json').read_text())
    passed = sorted(n for n, r in results.items() if r['ok'])[first:first + count if count else None]
    body = ['/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified\n'
            ' * against the original by tools/verify_lifted.py. */\n#include "lift_runtime.h"\n'
            '\n#include "lifted_%s.h"\n' % name]
    enums, protos, metas = [], [], {}
    readable = readable_names()
    for n in passed:
        text = (scratch / (n + '.c')).read_text()
        meta = json.loads((scratch / (n + '.json')).read_text())
        pretty = readable.get(meta['address'], n)
        function = text[text.index('uint32_t lifted_'):]
        header = (scratch / ('lifted_%s.h' % n)).read_text()
        proto = header[header.index('uint32_t lifted_'):header.index('#endif')]
        if pretty != n:
            function = function.replace('lifted_%s(' % n, 'lifted_%s(' % pretty)
            function = function.replace('LIFTED_%s_STACK' % n.upper(), 'LIFTED_%s_STACK' % pretty.upper())
            proto = proto.replace('lifted_%s(' % n, 'lifted_%s(' % pretty)
        body.append(function)
        enums.append('    LIFTED_%s_STACK = %d' % (pretty.upper(), meta['stack']))
        protos.append('/* Original 0x%x. */\n%s' % (meta['address'], proto.strip()))
        metas[pretty] = meta
    out = Path(out_dir)
    (out / ('lifted_%s.c' % name)).write_text('\n'.join(body))
    (out / ('lifted_%s.h' % name)).write_text(
        '#ifndef VERTRIX_LIFTED_%s_H\n#define VERTRIX_LIFTED_%s_H\n#include <stdint.h>\n\n'
        '#include "actor_build.h"\n\nenum\n{\n%s\n};\n\n%s\n#endif\n' % (
            name.upper(), name.upper(), ',\n'.join(enums), '\n\n'.join(protos)))
    (ROOT / 'docs' / 'lift' / (name + '.json')).write_text(json.dumps(metas, indent=1))
    print('combined', len(passed))


if __name__ == '__main__':
    command, scratch = sys.argv[1], Path(sys.argv[2]).resolve()
    if command == 'lift':
        lift_all(scratch, [int(a, 16) for a in sys.argv[3:]])
    elif command == 'verify':
        jobs = int(sys.argv[sys.argv.index('--jobs') + 1]) if '--jobs' in sys.argv else 8
        cases = int(sys.argv[sys.argv.index('--cases') + 1]) if '--cases' in sys.argv else 256
        verify_all(scratch, jobs, cases)
    elif command == 'combine':
        combine(scratch, sys.argv[3], sys.argv[4], *map(int, sys.argv[5:7]))
