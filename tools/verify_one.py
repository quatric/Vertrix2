"""Verify one batch-lifted routine: verify_one.py SCRATCH NAME CASES."""
import json
import sys
from pathlib import Path

scratch, name, cases = Path(sys.argv[1]), sys.argv[2], sys.argv[3]
SMALL = len(sys.argv) > 4 and sys.argv[4] == 'small'
meta = json.loads((scratch / (name + '.json')).read_text())
sys.argv = ['verify_one', str(Path(__file__).resolve().parents[1] / 'Vertrix2.exe'), '--build-dir',
            str(Path(__file__).resolve().parents[1] / 'build' / 'batch'), '--cases', cases]
import verify_lifted  # noqa: E402

import struct  # noqa: E402

from oracle_screen import host_write  # noqa: E402

from unicorn.x86_const import UC_X86_REG_EDX  # noqa: E402

# The stub vtable sits inside the mapped page 0x900000..0x910000 with room below it: Delphi
# reaches class data through negative slots (down to -864 in 0x4bf940).
VTABLE = 0x904000
LEAF = 0x700404
virtual = meta.get('virtual', [])
meta['callees']['0x%x' % LEAF] = [0, False]


def leaf(count):
    return LEAF + 0x10 * count


for _field, _slot, _count in virtual:
    meta['callees']['0x%x' % leaf(_count)] = [_count, False]


import re  # noqa: E402

source_text = (scratch / (name + '.c')).read_text()
pointer_offsets = set(meta.get('pointer_fields', [])) | set(meta.get('pointer_maybe', [])) | {f for f, _, _ in virtual if f >= 0}
scalar_reads = sorted({(int(m.group(1), 16), int(m.group(2))) for m in re.finditer(
    r'lift_load\(&env, e\w\w, 0x([0-9a-f]+)u, (\d)\)', source_text)
    if int(m.group(1), 16) not in pointer_offsets})


constants = meta.get('constants', [])


def vtable_patch(rng, handle, data):
    for offset in meta.get('pointer_maybe', []):
        if 0 <= offset and offset + 4 <= len(data) and rng.random() < 0.6:
            data[offset:offset + 4] = rng.choice(
                [0x806000 + 0x1000 * i for i in range(4)]).to_bytes(4, 'little')
    for offset, size in scalar_reads:
        if offset + size <= len(data):
            value = rng.choice([0, 1, 2, 3, 0xffffffff, rng.randrange(0, 30), rng.randrange(0, 256)])
            if constants and rng.random() < 0.5:
                value = rng.choice(constants)
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
    host_write(cpu, OBJECT, struct.pack('<I', VTABLE))
    try:
        host_write(cpu, stack[4], struct.pack('<I', OBJECT))
    except Exception:  # noqa: BLE001 - map the page of a garbage pointer
        cpu.mem_map(stack[4] & ~0xfff, 0x2000)
        host_write(cpu, stack[4], struct.pack('<I', OBJECT))
    return OBJECT


def string_store(cpu, rng, eax, edx, ebx, ecx, stack):
    """0x4ca280 and 0x4ca370 store a new string pointer through eax (lift_call stores the value the
    callee reports there): the stub stores the same drawn value in the original."""
    value = rng.choice([0, 0x806000, rng.getrandbits(32)])
    try:
        host_write(cpu, eax, struct.pack('<I', value))
    except Exception:  # noqa: BLE001 - map the page of a garbage pointer
        cpu.mem_map(eax & ~0xfff, 0x2000)
        host_write(cpu, eax, struct.pack('<I', value))
    return value


# The callees lift_call treats as returning a pair: their edx comes back in the call's out value.
PAIRS = (0x4db507, 0x4eb652, 0x4db350, 0x4d809c, 0x4d80a6, 0x4d8177, 0x4d81fe)


def edx_pair(cpu, rng, eax, edx, ebx, ecx, stack):
    """The stub leaves a drawn edx in the original, and the native call reports the same value."""
    value = rng.choice([0, 1, 2, 0xffffffff, rng.randrange(0, 64), rng.getrandbits(32)])
    cpu.reg_write(UC_X86_REG_EDX, value)
    return value


com = {0x4f175c: co_create} if 0x4f175c in imports else {}
com.update({t: string_store for t in (0x4ca280, 0x4ca370) if '0x%x' % t in meta['callees']})
com.update({t: edx_pair for t in PAIRS if '0x%x' % t in meta['callees']})
com = com or None
# Callees whose flags the lifted caller reads right after the call (compare helpers).
flag_targets = tuple(sorted({int(m.group(1), 16) for m in re.finditer(
    r'lift_call\(&env, 0x([0-9a-f]+)u[^;]*;\n\s*edx = vertrix_lift_edx;\n\s*fl = vertrix_lift_fl;'
    r'\n\s*if \(fl\.', source_text)}))
# The routine's own instructions: a callee among them is entered by jumps or by falling through
# as well as by calls.
import lift  # noqa: E402

internal = tuple(lift.trace(meta['address']))
spec = dict(internal=internal, flag_targets=flag_targets, effects=com, fixed_returns={0x4f175c: 0} if com else None, address=meta['address'], arguments=meta['arguments'], small=True, keep=tuple(slots) + tuple(pointer_globals) + tuple(imports), mixed=True, handles=True, automap=True, tolerate=True, smallregs=SMALL,
            pool_size=0x1000, patch=vtable_patch,
            setup_case=lambda rng, pool, cpu, kwargs: vtable_setup(cpu),
            setup=vtable_setup if virtual or slots or pointer_globals or imports else None)
verify_lifted.run(name, spec, meta, scratch / (name + '.c'))
