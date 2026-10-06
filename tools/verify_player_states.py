"""Compare the original player state handlers 0x451490, 0x451520, 0x451580, 0x451630, 0x451690
and 0x451730 with the native recovery."""
import ctypes as c
import struct

from oracle_screen import run_screen

U = c.c_uint32
VTABLE = 0x80f000
LEAF = 0x700404
CALLEES = {address: 0 for address in (
    0x4ac500, 0x4ac520, 0x4ac540, 0x4ac5b0, 0x4342f0, 0x433e20, 0x4323d0, 0x4ac8f0, 0x4334b0,
    0x433550, 0x433840, 0x42eee0, 0x43c0e0, 0x42eca0, 0x42ecc0, 0x42ebe0, 0x4322f0, 0x4334a0,
    0x43bad0, 0x4ac7b0, LEAF)}
CHOICES = {0x4ac520: [1, 1, 0, 2], 0x4ac540: [0, 1, 2, 3], 0x433e20: [0, 5], 0x4334b0: [0, 3],
           0x42eca0: [0, 1], 0x42ecc0: [0, 1], 0x4322f0: [1, 1, 0, 2]}
GLOBALS = ((0x4f81ac, 4), (0x4f819c, 4), (0x4f8184, 4), (0x4f7be8, 0x28))


def setup(cpu):
    cpu.mem_write(VTABLE + 4, struct.pack('<I', LEAF))


def patch(rng, handle, data):
    handles = [0x806000 + 0x1000 * i for i in range(4)]
    data[0x15c:0x160] = rng.choice(handles).to_bytes(4, 'little')
    data[0x158:0x15c] = VTABLE.to_bytes(4, 'little')
    data[0x838] = rng.choice([0, 0, 1, 2, 3])
    data[0x4cd] = rng.choice([0, rng.randrange(1, 256)])
    data[0xbd8:0xbdc] = rng.choice([0, rng.getrandbits(32)]).to_bytes(4, 'little')


def player_edx_ebx(rng, pool, cpu):
    player, edx, ebx = rng.choice(pool.handles), rng.getrandbits(32), rng.getrandbits(32)
    cpu.mem_write(0x532bbc, struct.pack('<I', rng.randrange(0, 10)))
    return {'eax': player, 'edx': edx, 'ebx': ebx}, (), (player, edx, ebx)


def player_edx(rng, pool, cpu):
    player, edx = rng.choice(pool.handles), rng.getrandbits(32)
    cpu.mem_write(0x532bbc, struct.pack('<I', rng.randrange(0, 10)))
    return {'eax': player, 'edx': edx}, (), (player, edx)


def player_only(rng, pool, cpu):
    player = rng.choice(pool.handles)
    return {'eax': player}, (), (player,)


COMMON = dict(patch=patch, setup=setup, choices=CHOICES, globals_ranges=GLOBALS, pool_size=0x1000)
TEXT = ('The original executes completely with its callees stubbed and logged (the virtual call '
        'through a fake vtable); the timer and gate results are drawn from small sets so every '
        'branch is taken. Every call with its registers, the returned eax and every pool object '
        'compare.')
run_screen('state-steps-451490', 0x451490, ['player_states.c'], 'vertrix_state_steps_451490',
           [U, U, U], U, CALLEES, player_edx_ebx, TEXT, **COMMON)
run_screen('state-steps-451730', 0x451730, ['player_states.c'], 'vertrix_state_steps_451730',
           [U, U, U], U, CALLEES, player_edx_ebx, TEXT, **COMMON)
run_screen('state-gate-451520', 0x451520, ['player_states.c'], 'vertrix_state_gate_451520', [U, U],
           U, CALLEES, player_edx, TEXT, **COMMON)
run_screen('state-drain-451580', 0x451580, ['player_states.c'], 'vertrix_state_drain_451580',
           [U, U], U, CALLEES, player_edx, TEXT, **COMMON)
run_screen('state-check-451630', 0x451630, ['player_states.c'], 'vertrix_state_check_451630', [U],
           U, CALLEES, player_only, TEXT, **COMMON)
run_screen('state-start-451690', 0x451690, ['player_states.c'], 'vertrix_state_start_451690',
           [U, U], U, CALLEES, player_edx, TEXT, **COMMON)
