"""Verify one batch-lifted routine: verify_one.py SCRATCH NAME CASES."""
import json
import sys
from pathlib import Path

scratch, name, cases = Path(sys.argv[1]), sys.argv[2], sys.argv[3]
meta = json.loads((scratch / (name + '.json')).read_text())
sys.argv = ['verify_one', str(Path(__file__).resolve().parents[1] / 'Vertrix2.exe'), '--build-dir',
            str(Path(__file__).resolve().parents[1] / 'build' / 'batch'), '--cases', cases]
import verify_lifted  # noqa: E402

import struct  # noqa: E402

VTABLE = 0x80f000
LEAF = 0x700404
virtual = meta.get('virtual', [])
meta['callees']['0x%x' % LEAF] = [0, False]


import re  # noqa: E402

source_text = (scratch / (name + '.c')).read_text()
pointer_offsets = set(meta.get('pointer_fields', [])) | {f for f, _ in virtual if f >= 0}
scalar_reads = sorted({(int(m.group(1), 16), int(m.group(2))) for m in re.finditer(
    r'lift_load\(&env, e\w\w, 0x([0-9a-f]+)u, (\d)\)', source_text)
    if int(m.group(1), 16) not in pointer_offsets})


def vtable_patch(rng, handle, data):
    for offset, size in scalar_reads:
        if offset + size <= len(data):
            value = rng.choice([0, 1, 2, 3, 0xffffffff, rng.randrange(0, 30), rng.randrange(0, 256)])
            data[offset:offset + size] = (value & ((1 << (8 * size)) - 1)).to_bytes(size, 'little')
    for field, slot in virtual:
        if field >= 0 and field + 4 <= len(data):
            data[field:field + 4] = VTABLE.to_bytes(4, 'little')


def vtable_setup(cpu):
    for field, slot in virtual:
        cpu.mem_write(VTABLE + slot, struct.pack('<I', LEAF))


spec = dict(address=meta['address'], arguments=meta['arguments'], small=True, mixed=True, handles=True,
            pool_size=0x1000, patch=vtable_patch,
            setup=vtable_setup if virtual else None)
verify_lifted.run(name, spec, meta, scratch / (name + '.c'))
