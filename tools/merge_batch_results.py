"""Fold a re-verification batch (lift_batch.py verify SCRATCH) into the batch record.

usage: merge_batch_results.py SCRATCH NOTE

Routines that now pass move from `failures` to `passed_addresses`; the others keep their new
failure detail. NOTE is appended to the record's `reverifications` list."""
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def main():
    scratch, note = Path(sys.argv[1]), sys.argv[2]
    results = json.loads((scratch / 'results.json').read_text())
    path = ROOT / 'docs' / 'lifted-batch-verification.json'
    record = json.loads(path.read_text())
    passed = set(record['passed_addresses'])
    newly = []
    for name, result in sorted(results.items()):
        address = '0x' + name[1:]
        if result['ok']:
            record['failures'].pop(name, None)
            if address not in passed:
                passed.add(address)
                newly.append(address)
        elif name in record['failures']:
            record['failures'][name] = result['detail']
    record['passed_addresses'] = sorted(passed, key=lambda a: int(a, 16))
    record['passed_routines'] += len(newly)
    record['failed_routines'] = len(record['failures'])
    record.setdefault('reverifications', []).append({'note': note, 'attempted': len(results),
                                                     'newly_passed': newly})
    path.write_text(json.dumps(record, indent=1) + '\n')
    print('newly passed', len(newly), 'still failing', record['failed_routines'])


if __name__ == '__main__':
    main()
