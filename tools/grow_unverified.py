"""Lift the given original addresses (when they are not already in the dispatcher) and add them to
the unverified tier: docs/lift/unverified.json plus source/lifted_unverified.[ch].
usage: grow_unverified.py SCRATCH ADDRESS... (SCRATCH is the lift_batch scratch directory)
The names of the routines in the tier are kept in docs/lift/unverified-list.txt."""
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import lift_batch  # noqa: E402

scratch = Path(sys.argv[1])
listing = ROOT / 'docs' / 'lift' / 'unverified-list.txt'
names = set(listing.read_text().split()) if listing.exists() else set()
fresh = Path('/tmp/grow_scratch')
results = json.loads((scratch / 'results.json').read_text())
verified = {n for n, r in results.items() if r['ok']}
for text in sys.argv[2:]:
    address = int(text, 16)
    name = 'f%x' % address
    if name in verified:
        continue
    if not (scratch / (name + '.c')).exists():
        lift_batch.lift_all(fresh, [address])
        if not (fresh / (name + '.c')).exists():
            print('cannot lift', text, json.loads((fresh / 'skipped.json').read_text()))
            continue
        for path in fresh.glob('*%s*' % name):
            (scratch / path.name).write_bytes(path.read_bytes())
    results.setdefault(name, {'ok': False, 'detail': 'lifted; unverified'})
    names.add(name)
(scratch / 'results.json').write_text(json.dumps(results, indent=1))
listing.write_text('\n'.join(sorted(names)) + '\n')
lift_batch.combine(scratch, 'unverified', ROOT / 'source', unverified=True, only=sorted(names))
