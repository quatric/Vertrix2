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

VTABLE = 0x900000
LEAF = 0x700404
virtual = meta.get('virtual', [])
meta['callees']['0x%x' % LEAF] = [0, False]


def leaf(count):
    return LEAF + 0x10 * count


for _field, _slot, _count in virtual:
    meta['callees']['0x%x' % leaf(_count)] = [_count, False]


import re  # noqa: E402

source_text = (scratch / (name + '.c')).read_text()
pointer_offsets = set(meta.get('pointer_fields', [])) | {f for f, _, _ in virtual if f >= 0}
scalar_reads = sorted({(int(m.group(1), 16), int(m.group(2))) for m in re.finditer(
    r'lift_load\(&env, e\w\w, 0x([0-9a-f]+)u, (\d)\)', source_text)
    if int(m.group(1), 16) not in pointer_offsets})


def vtable_patch(rng, handle, data):
    for offset, size in scalar_reads:
        if offset + size <= len(data):
            value = rng.choice([0, 1, 2, 3, 0xffffffff, rng.randrange(0, 30), rng.randrange(0, 256)])
            data[offset:offset + size] = (value & ((1 << (8 * size)) - 1)).to_bytes(size, 'little')
    for field, slot, _count in virtual:
        if field >= 0 and field + 4 <= len(data):
            data[field:field + 4] = VTABLE.to_bytes(4, 'little')


slots = [int(k[5:], 16) for k in meta['callees'] if k.startswith('slot_')]
for index, slot in enumerate(slots):
    meta['callees']['0x%x' % (0x700800 + 16 * index)] = meta['callees'][ 'slot_%x' % slot]


pointer_globals = [g for g in meta.get('pointer_globals', []) if g not in slots]


imports = [int(k, 16) for k in meta['callees'] if k.startswith('0x') and
           0x4f1000 <= int(k, 16) < 0x4f4000]


def vtable_setup(cpu):
    try:
        cpu.mem_map(0x900000, 0x10000)
    except Exception:  # noqa: BLE001 - already mapped
        pass
    for address in imports:
        cpu.mem_write(address, struct.pack('<I', address))
    for address in pointer_globals:
        cpu.mem_write(address, struct.pack('<I', 0x806000))
    for index, slot in enumerate(slots):
        cpu.mem_write(slot, struct.pack('<I', 0x700800 + 16 * index))
    for field, slot, count in virtual:
        cpu.mem_write(VTABLE + slot, struct.pack('<I', leaf(count)))


OBJECT = 0x900800


def co_create(cpu, rng, eax, edx, ebx, ecx, stack):
    cpu.mem_write(OBJECT, struct.pack('<I', VTABLE))
    try:
        cpu.mem_write(stack[4], struct.pack('<I', OBJECT))
    except Exception:  # noqa: BLE001 - map the page of a garbage pointer
        cpu.mem_map(stack[4] & ~0xfff, 0x2000)
        cpu.mem_write(stack[4], struct.pack('<I', OBJECT))
    return OBJECT


com = {0x4f175c: co_create} if 0x4f175c in imports else None
spec = dict(effects=com, fixed_returns={0x4f175c: 0} if com else None, address=meta['address'], arguments=meta['arguments'], small=True, keep=tuple(slots) + tuple(pointer_globals) + tuple(imports), mixed=True, handles=True, automap=True,
            pool_size=0x1000, patch=vtable_patch,
            setup_case=lambda rng, pool, cpu, kwargs: vtable_setup(cpu),
            setup=vtable_setup if virtual or slots or pointer_globals or imports else None)
verify_lifted.run(name, spec, meta, scratch / (name + '.c'))
