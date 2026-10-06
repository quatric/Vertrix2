"""Compare the original device, queue and COM wrappers 0x475510, 0x475700, 0x4759e0, 0x475c80,
0x476160, 0x476810, 0x477c30 and 0x477c90 with the native recovery."""
import ctypes as c
import struct

from oracle_screen import run_screen

U = c.c_uint32
VTABLE = 0x80f000
FAKE = {0x00: 0x700400, 0x18: 0x700418, 0x1c: 0x70041c, 0x20: 0x700420}
IAT = (0x4f1a9c, 0x4f1ae4)


def setup(cpu):
    for offset, address in FAKE.items():
        cpu.mem_write(VTABLE + offset, struct.pack('<I', address))
    for slot in IAT:
        cpu.mem_write(slot, struct.pack('<I', slot))


def patch(rng, handle, data):
    data[0x0:0x4] = VTABLE.to_bytes(4, 'little')
    data[0x18:0x1c] = VTABLE.to_bytes(4, 'little')
    data[0xc:0x10] = rng.choice([0, rng.getrandbits(32)]).to_bytes(4, 'little')
    data[0x2c:0x30] = rng.choice([0, 1, 2, 3]).to_bytes(4, 'little')
    data[0x30:0x34] = rng.choice(POOL + [0]).to_bytes(4, 'little')


def patch_interface(rng, handle, data):
    patch(rng, handle, data)
    data[0x30:0x34] = rng.choice(POOL).to_bytes(4, 'little')


POOL = [0x806000 + 0x200 * i for i in range(4)]
COM = {0x700418: 3, 0x70041c: 1, 0x700420: 1, 0x4f1a9c: 1, 0x4f1ae4: 1}
LEAF = {0x700400: 0}


def queue_effect(cpu, rng, eax, edx, ebx, ecx, stack):
    count = rng.choice([0, 1, 2, 3])
    cpu.mem_write(eax + 0xc, struct.pack('<I', count))
    return count


def descriptor(cpu, regs, args):
    return struct.unpack('<5I', bytes(cpu.mem_read(args[2], 20)))


def one(rng, pool, cpu, *names):
    values = {name: rng.getrandbits(32) for name in names}
    return values


def release(rng, pool, cpu):
    return {}, (), ()


def destroy(rng, pool, cpu):
    obj, edx, ebx = rng.choice(pool.handles), rng.getrandbits(32), rng.getrandbits(32)
    return {'eax': obj, 'edx': edx, 'ebx': ebx}, (), (obj, edx, ebx)


def drain(rng, pool, cpu):
    obj, edx, ebx = rng.choice(pool.handles), rng.getrandbits(32), rng.getrandbits(32)
    return {'eax': obj, 'edx': edx, 'ebx': ebx}, (), (obj, edx, ebx)


def nextcase(rng, pool, cpu):
    obj, edx = rng.choice(pool.handles), rng.choice(pool.handles + [0])
    return {'eax': obj, 'edx': edx}, (), (obj, edx)


def table(rng, pool, cpu):
    ebx, edx = rng.getrandbits(32), rng.choice(pool.handles)
    return {'ebx': ebx, 'edx': edx}, (), (ebx, edx)


def entry(rng, pool, cpu):
    obj = rng.getrandbits(32)
    return {'eax': obj}, (), (obj,)


def capture(rng, pool, cpu):
    obj, ecx = rng.choice(pool.handles), rng.getrandbits(32)
    return {'eax': obj, 'ecx': ecx}, (), (obj, ecx)


def release_case(rng, pool, cpu):
    obj, edx, ecx = rng.choice(pool.handles), rng.getrandbits(32), rng.getrandbits(32)
    return {'eax': obj, 'edx': edx, 'ecx': ecx}, (), (STACK - 4, obj, edx, ecx)


STACK = 0x708000
RELEASE_PAIR = {0x4ea190: 0}
DESTROY = {0x4ca050: 0, 0x4ccb9f: 0, 0x4ca040: 0}
QUEUE = {0x4d8540: 0}
QUEUE.update(LEAF)
STRING = {0x4ca060: 0, 0x4ca370: 0}
ENTRY = {0x4cea15: 0}
CURSOR = dict(COM)
CURSOR[0x700418] = 3
FIX = {0x4ca060: 0x50081c}

run_screen('release-pair', 0x475510, ['device_glue.c'], 'vertrix_release_pair', [], c.c_int,
           RELEASE_PAIR, release,
           'The original executes completely with 0x4ea190 stubbed and logged; the dwords '
           '0x54b800 and 0x54b804 hold random data.',
           leading=('calls', 'globals'), globals_ranges=((0x54b800, 8),), compare=False)
run_screen('destroy-flags', 0x475700, ['device_glue.c'], 'vertrix_object_destroy_flags', [U, U, U],
           U, DESTROY, destroy,
           'The original executes completely with its callees stubbed and logged; edx covers '
           'every flag combination. Every call, the returned eax and every pool object compare.',
           leading=('calls', 'services'))
run_screen('queue-drain', 0x4759e0, ['device_glue.c'], 'vertrix_queue_drain', [U, U, U], U, QUEUE,
           drain,
           'The original executes completely with 0x4d8540 stubbed (it stores a new random count '
           'at +0x2c, carried through the call site), the entries deleted through fake COM '
           'vtables. Every call, the returned eax and every pool object compare.',
           patch=patch, setup=setup, effects={0x4d8540: queue_effect},
           lookups=(0x4d8540,))
run_screen('queue-next', 0x475c80, ['device_glue.c'], 'vertrix_queue_next', [U, U], U, QUEUE,
           nextcase,
           'The original executes completely with 0x4d8540 stubbed (it stores a new random count '
           'at +0x2c, carried through the call site), the entry deleted through a fake vtable. '
           'Every call, the returned eax and every pool object compare.',
           patch=patch, setup=setup, effects={0x4d8540: queue_effect},
           handle_returns=(0x4d8540,))
run_screen('string-table-assign', 0x476160, ['device_glue.c'], 'vertrix_string_table_assign',
           [U, U], U, STRING, table,
           'The original executes completely with 0x4ca060 returning 0x50081c and 0x4ca370 '
           'stubbed and logged; the dword 0x50081c holds random data. Every call, the returned '
           'variable and every pool object compare.',
           fixed_returns=FIX, globals_ranges=((0x50081c, 4),))
run_screen('resource-entry', 0x476810, ['device_glue.c'], 'vertrix_resource_entry_256', [U], U,
           ENTRY, entry,
           'The original executes completely with 0x4cea15 stubbed and logged.',
           leading=('calls',))
run_screen('cursor-capture', 0x477c30, ['device_glue.c'], 'vertrix_cursor_capture', [U, U], U,
           CURSOR, capture,
           'The original executes completely with the COM methods of a fake vtable and the '
           'imports SetCursor and ShowCursor (called through their import slots) stubbed and '
           'logged; ShowCursor returns random values until one is negative. Every call, the '
           'returned eax and every pool object compare.',
           patch=patch, setup=setup)
run_screen('cursor-release', 0x477c90, ['device_glue.c'], 'vertrix_cursor_release', [U, U, U, U],
           U, CURSOR, release_case,
           'The original executes completely with the COM methods of a fake vtable stubbed and '
           'logged; the descriptor handed to the vtable +0x18 method is logged with its five '
           'dwords. Every call, the returned eax and every pool object compare.',
           patch=patch_interface, setup=setup, extras={0x700418: descriptor},
           native_extras_arg={0x700418: lambda s: (s.rest0, s.rest1, s.rest2, s.rest3, s.rest4)})
