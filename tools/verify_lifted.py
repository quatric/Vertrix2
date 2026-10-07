"""Compare a routine lifted by tools/lift.py with the original executing in Unicorn.

usage: verify_lifted.py EXECUTABLE --build-dir DIR NAME  (NAME is a key of LIFTED)
"""
import ctypes as c
import json
import struct
import sys
from pathlib import Path

from unicorn.x86_const import (UC_X86_REG_EBP, UC_X86_REG_EDI, UC_X86_REG_ESI)

from original import STACK
from oracle_screen import run_screen

U = c.c_uint32


class LiftEntry(c.Structure):
    _fields_ = [('eax', U), ('edx', U), ('ebx', U), ('ecx', U), ('esi', U), ('edi', U),
                ('ebp', U), ('esp', U), ('arguments', c.POINTER(U)),
                ('garbage', c.POINTER(c.c_uint8)), ('chain', U)]


FRAME = STACK - 4
META = Path(__file__).resolve().parents[1] / 'docs' / 'lift'
HANDLE_CALLEES = (0x4ca000, 0x4b5400, 0x4b6350, 0x4abd70, 0x4b5c60)

# name -> address, argument count, globals ranges, choices, effects, extra callees
LIFTED = {}


def register(name, address, arguments=0, **options):
    LIFTED[name] = dict(address=address, arguments=arguments, **options)


def callees_for(name, meta=None):
    if meta is None:
        meta = json.loads((META / (name + '.json')).read_text())
    table = {}
    for target, (count, cdecl) in meta['callees'].items():
        if target.startswith('virtual_') or target.startswith('slot_'):
            continue
        table[int(target, 16)] = (count, True) if cdecl else count
    return table, meta['stack'], [int(t, 16) for t in meta.get('pointer_callees', [])], \
        meta.get('pointer_fields', [])


def absolute_reads(source_text):
    import re
    return sorted({int(m.group(1), 16) for m in re.finditer(
        r'lift_load\(&env, 0u, 0x([0-9a-f]+)u', source_text)})


def small_values(source_text, spec):
    addresses = [a for a in absolute_reads(source_text) if a not in spec.get('keep', ())]
    bounds = spec.get('bounds', ())

    def patch_globals(rng, cpu):
        for address in addresses:
            cpu.mem_write(address, struct.pack('<I', rng.choice([0, 1, 2, 3, rng.randrange(0, 40)])))
        for address in bounds:
            cpu.mem_write(address, struct.pack('<I', rng.choice([0, 1, 2, 3, 6, 11, 20])))
    return patch_globals


def run(name, spec=None, meta=None, source=None):
    spec = spec or LIFTED[name]
    source = source or (Path(__file__).resolve().parents[1] / 'source' / ('lifted_%s.c' % name))
    callees, locals_size, pointers, fields = callees_for(name, meta)
    user_patch = spec.get('patch')

    def patch(rng, handle, data):
        for offset in fields:
            if offset + 4 <= len(data):
                data[offset:offset + 4] = rng.choice(
                    [0x806000 + spec.get('pool_size', 0x200) * i for i in range(4)]).to_bytes(4, 'little')
        if user_patch:
            user_patch(rng, handle, data)
    callees.update(spec.get('extra_callees', {}))
    count = spec['arguments']
    small = small_values(Path(source).read_text(), spec) if spec.get('small') else None

    def generate(rng, pool, cpu):
        kwargs, stack_args = {}, ()
        for register_name in ('eax', 'edx', 'ebx', 'ecx'):
            kwargs[register_name] = rng.getrandbits(32)
            if spec.get('handles') and (register_name == 'eax' or rng.random() < 0.5):
                kwargs[register_name] = rng.choice(pool.handles)
        if spec.get('setup_case'):
            spec['setup_case'](rng, pool, cpu, kwargs)
        if small is not None:
            small(rng, cpu)
        stack_args = tuple(rng.getrandbits(32) for _ in range(count))
        garbage = bytes(cpu.mem_read(FRAME - locals_size, locals_size))
        chain = struct.unpack('<I', bytes(cpu.mem_read(0, 4)))[0]
        arguments = (U * max(count, 1))(*stack_args)
        buffer = (c.c_uint8 * locals_size).from_buffer_copy(garbage)
        entry = LiftEntry(kwargs['eax'], kwargs['edx'], kwargs['ebx'], kwargs['ecx'],
                          cpu.reg_read(UC_X86_REG_ESI), cpu.reg_read(UC_X86_REG_EDI),
                          cpu.reg_read(UC_X86_REG_EBP), FRAME, arguments, buffer, chain)
        keep.append((arguments, buffer, entry))
        del keep[:-4]
        return kwargs, stack_args, (c.pointer(entry),)

    keep = []

    def effects_for(table):
        return table

    handle_returns = tuple(sorted(set(t for t in HANDLE_CALLEES if t in callees) | set(pointers)))
    mixed = tuple(t for t in callees if t not in handle_returns and spec.get('mixed'))
    run_screen('lifted-' + name, spec['address'], [str(source)], 'lifted_' + name,
               [c.POINTER(LiftEntry)], U, callees, generate,
               'Lifted instruction by instruction from the original; every call with its '
               'registers and stack arguments, the returned eax, every stored global and every '
               'pool object compare against the original executing completely in Unicorn.',
               globals_ranges=spec.get('globals', ()), choices=spec.get('choices'),
               effects=spec.get('effects'), handle_returns=handle_returns, mixed_returns=mixed,
               pool_size=spec.get('pool_size', 0x200), patch=patch if fields or user_patch else None,
               setup=spec.get('setup'), fixed_returns=spec.get('fixed_returns'),
               post=spec.get('post'))


def hud_case(rng, pool, cpu, kwargs):
    kwargs['edx'] = rng.choice([0xffffffff, 0xffffffff, 0x20, 0x21, 0x22, rng.getrandbits(32)])
    cpu.mem_write(0x532a68, struct.pack('<I', rng.randrange(0, 19)))
    cpu.mem_write(0x532a6c, struct.pack('<I', rng.randrange(0, 19)))


register('hud_decor', 0x46b810, 0, setup_case=hud_case,
         globals=((0x4f888a, 0x4f8ce0 - 0x4f888a), (0x4fbf28, 0xc0), (0x5466c4, 4),
                  (0x5345d4, 0x50), (0x4f9c07, 4)),
         choices={0x4178d0: [0xffffffff, 0xffffffff, 0, 5], 0x4126f0: [1, 1, 0]})

register('title_screen', 0x465af0, 0, small=True, bounds=(0x4f86d4, 0x4f870c, 0x532a84))
register('select_screen', 0x466d60, 0, mixed=True, small=True)
register('game_screen', 0x46c9d0, 0, mixed=True, small=True, pool_size=0x1000)

if __name__ == '__main__':
    name = sys.argv.pop()
    run(name)
