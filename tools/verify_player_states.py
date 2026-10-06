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


STACK = 0x708000
CHOICE = {address: 0 for address in (0x42a1b0, 0x4ac8f0, 0x42a190, 0x43acd0, 0x43ccb0, 0x43c140,
                                     0x43bbf0, LEAF)}
CHOICE[0x42a170] = 1
CHOICE_CHOICES = {0x42a1b0: [0, 1], 0x42a190: [1, 1, 0, 2], 0x43ccb0: [0, 1], 0x43c140: [0, 1]}


def cell_effect(cpu, rng, eax, edx, ebx, ecx, stack):
    first, second = rng.getrandbits(32), rng.getrandbits(32)
    cpu.mem_write(stack[0], struct.pack('<I', first))
    cpu.mem_write(ecx, struct.pack('<I', second))
    return first, 0, second


def choice_apply_case(rng, pool, cpu):
    player, ecx = rng.choice(pool.handles), rng.getrandbits(32)
    return {'eax': player, 'ecx': ecx}, (), (STACK - 4, player, ecx)


run_screen('state-choice-check', 0x451dd0, ['player_states.c'], 'vertrix_state_choice_check',
           [U, U], U, CHOICE, player_edx, TEXT, **{**COMMON, 'choices': CHOICE_CHOICES})
run_screen('state-choice-apply', 0x451e20, ['player_states.c'], 'vertrix_state_choice_apply',
           [U, U, U], U, CHOICE, choice_apply_case,
           TEXT + ' 0x42a170 stores two random dwords through its pointers (frame locals), carried '
           'through the call site.',
           effects={0x42a170: cell_effect}, **{**COMMON, 'choices': CHOICE_CHOICES})


TAKE = {address: 0 for address in (0x42a190, 0x42a140, 0x4ac8f0, 0x43bae0, 0x43c0e0, 0x43bbf0,
                                   LEAF)}
TAKE[0x42a170] = 1
TAKE[0x43bd90] = 2
MATCH = {address: 0 for address in (0x4328a0, 0x4ac7d0, 0x4ac510, 0x4ac8f0, 0x452250, 0x43ba70,
                                    0x43bae0, 0x43ba80, LEAF)}
ATTACK = {address: 0 for address in (0x4316c0, 0x4ac7b0, 0x4ac510, 0x4ac8f0, 0x43c0e0, 0x43bbf0,
                                     LEAF)}
TABLES = ((0x4f7bf4, 0x4c), (0x4f81ac, 4), (0x4f8188, 4), (0x4f7be8, 0x28))


def take_effects():
    def first(cpu, rng, eax, edx, ebx, ecx, stack):
        value = rng.getrandbits(32)
        cpu.mem_write(ecx, struct.pack('<I', value))
        return 0, 0, value

    def sounds(cpu, rng, eax, edx, ebx, ecx, stack):
        second, third = rng.getrandbits(32), rng.getrandbits(32)
        cpu.mem_write(stack[0], struct.pack('<I', second))
        cpu.mem_write(ecx, struct.pack('<I', third))
        return second, 0, third
    def cell(cpu, rng, eax, edx, ebx, ecx, stack):
        value = rng.getrandbits(32)
        cpu.mem_write(stack[0], struct.pack('<I', value))
        return value

    return {0x43bae0: first, 0x42a170: cell, 0x43bd90: sounds}


def patch_more(rng, handle, data):
    patch(rng, handle, data)
    handles = [0x806000 + 0x1000 * i for i in range(4)]
    data[0x3b0:0x3b4] = rng.choice(handles).to_bytes(4, 'little')
    data[0x44c:0x450] = rng.choice([0, 1, 1, 2]).to_bytes(4, 'little')


def take_case(rng, pool, cpu):
    player, ecx = rng.choice(pool.handles), rng.getrandbits(32)
    return {'eax': player, 'ecx': ecx}, (), (STACK - 4, player, ecx)


def attack_case(rng, pool, cpu):
    player = rng.choice(pool.handles)
    cpu.mem_write(0x532bbc, struct.pack('<I', rng.randrange(0, 10)))
    return {'eax': player}, (), (player,)


MORE = {**COMMON, 'patch': patch_more, 'globals_ranges': TABLES}
MORE_CHOICES = {0x42a190: [1, 1, 0, 2], 0x4328a0: [1, 1, 0, 3], 0x43ba70: [1, 1, 0],
                0x4316c0: [1, 1, 0, 2]}
run_screen('state-choice-take', 0x451f50, ['player_states.c'], 'vertrix_state_choice_take',
           [U, U, U], U, TAKE, take_case,
           TEXT + ' 0x43bae0, 0x42a170 and 0x43bd90 store random dwords through their pointers '
           '(frame locals), carried through the call site.',
           effects=take_effects(), **{**MORE, 'choices': MORE_CHOICES})
run_screen('state-match-452160', 0x452160, ['player_states.c'], 'vertrix_state_match_452160',
           [U, U], U, MATCH, player_edx, TEXT, **{**MORE, 'choices': MORE_CHOICES})
run_screen('state-attack-452440', 0x452440, ['player_states.c'], 'vertrix_state_attack_452440',
           [U], U, ATTACK, attack_case, TEXT, **{**MORE, 'choices': MORE_CHOICES})
