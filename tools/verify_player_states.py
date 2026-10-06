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


ADVANCE = {address: 0 for address in (0x4328a0, 0x4ac500, 0x4ac510, 0x432a30, 0x432b10, 0x4ac8f0,
                                      LEAF)}
ADVANCE[0x4ac590] = 0


def patch_advance(rng, handle, data):
    patch(rng, handle, data)
    data[0x58:0x5c] = struct.pack('<i', rng.randrange(-5, 120))
    data[0x18:0x1c] = rng.getrandbits(32).to_bytes(4, 'little')


run_screen('state-advance-452770', 0x452770, ['player_states.c'], 'vertrix_state_advance_452770',
           [U, U], U, ADVANCE, player_edx, TEXT,
           **{**COMMON, 'patch': patch_advance,
              'choices': {0x4328a0: [1, 1, 0, 2], 0x4ac590: [0, 1, 2, 5]}})


PAIR = {address: 0 for address in (0x42eca0, 0x42ecc0, 0x42edf0, 0x42eb60, 0x42ebe0, 0x43bbf0,
                                   LEAF)}


def pair_case(rng, pool, cpu):
    player = rng.choice(pool.handles)
    return {'eax': player}, (), (player,)


run_screen('state-pair-453050', 0x453050, ['player_states.c'], 'vertrix_state_pair_453050', [U],
           U, PAIR, pair_case, TEXT,
           **{**MORE, 'choices': {0x42eca0: [1, 1, 1, 0], 0x42ecc0: [1, 1, 1, 0],
                                  0x42edf0: [1, 0, 1, 1, 0]}})


COMBINE = {address: 0 for address in (0x43c0e0, 0x436aa0, 0x4ac8f0, LEAF)}
COMBINE[0x436d80] = 1


def combine_case(rng, pool, cpu):
    player, ebx, ecx = rng.choice(pool.handles), rng.getrandbits(32), rng.getrandbits(32)
    return {'eax': player, 'ebx': ebx, 'ecx': ecx}, (), (player, ebx, ecx)


run_screen('state-combine-453320', 0x453320, ['player_states.c'], 'vertrix_state_combine_453320',
           [U, U, U], U, COMBINE, combine_case, TEXT, **MORE)


run_screen('state-pair-4533b0', 0x4533b0, ['player_states.c'], 'vertrix_state_pair_4533b0', [U],
           U, PAIR, pair_case, TEXT,
           **{**MORE, 'choices': {0x42eca0: [1, 1, 1, 0], 0x42ecc0: [1, 1, 1, 0]}})


run_screen('state-ask-453ef0', 0x453ef0, ['player_states.c'], 'vertrix_state_ask_453ef0', [U], U,
           PAIR, pair_case, TEXT, **{**MORE, 'choices': {0x42eca0: [1, 0, 1]}})

run_screen('state-ask-454200', 0x454200, ['player_states.c'], 'vertrix_state_ask_454200', [U], U,
           PAIR, pair_case, TEXT, **{**MORE, 'choices': {0x42eca0: [1, 0, 1]}})

for address, name in ((0x454510, 'ask-454510'), (0x454760, 'ask-454760')):
    run_screen('state-' + name, address, ['player_states.c'],
               'vertrix_state_' + name.replace('-', '_'), [U], U, PAIR, pair_case, TEXT,
               **{**MORE, 'choices': {0x42eca0: [1, 0, 1]}})

CYCLE = {address: 0 for address in (0x4ac500, 0x4ac520, 0x4ac540, 0x4ac5b0, 0x4ad750, 0x438c60,
                                    0x43b970, 0x438b90, 0x4ac8f0, LEAF)}


def patch_cycle(rng, handle, data):
    patch_more(rng, handle, data)
    data[0x3ec:0x3f0] = rng.choice([0, 1, 1, 2]).to_bytes(4, 'little')
    data[0x448:0x44c] = struct.pack('<i', rng.randrange(-2, 14))


run_screen('state-cycle-4546a0', 0x4546a0, ['player_states.c'], 'vertrix_state_cycle_4546a0',
           [U, U], U, CYCLE, player_edx, TEXT,
           **{**MORE, 'patch': patch_cycle,
              'choices': {0x4ac520: [1, 1, 0, 2], 0x4ac540: [0, 1, 2, 3], 0x4ad750: [0, 0, 1],
                          0x43b970: [0, 1]}})


DRAIN = {address: 0 for address in (0x4ac500, 0x4ac520, 0x4ac540, 0x4ac5b0, 0x436440, 0x43c0e0,
                                    0x4ac8f0, LEAF)}


def patch_drain(rng, handle, data):
    patch_more(rng, handle, data)
    data[0x438:0x43c] = struct.pack('<i', rng.randrange(-1, 6))


def drain_case(rng, pool, cpu):
    player, edx, ebx = rng.choice(pool.handles), rng.getrandbits(32), rng.getrandbits(32)
    return {'eax': player, 'edx': edx, 'ebx': ebx}, (), (player, edx, ebx)


run_screen('state-drain-454b20', 0x454b20, ['player_states.c'], 'vertrix_state_drain_454b20',
           [U, U, U], U, DRAIN, drain_case, TEXT,
           **{**MORE, 'patch': patch_drain,
              'choices': {0x4ac520: [1, 1, 1, 0], 0x4ac540: [0, 1, 2, 3, 6],
                          0x436440: [1, 1, 1, 0]}})
run_screen('state-done-454bd0', 0x454bd0, ['player_states.c'], 'vertrix_state_done_454bd0', [U],
           U, PAIR, pair_case, TEXT,
           **{**MORE, 'choices': {0x42eca0: [1, 1, 0], 0x42ecc0: [1, 1, 0]}})

DRAIN2 = {**DRAIN, 0x4365c0: 0}
del DRAIN2[0x436440]
run_screen('state-drain-454d80', 0x454d80, ['player_states.c'], 'vertrix_state_drain_454d80',
           [U, U, U], U, DRAIN2, drain_case, TEXT,
           **{**MORE, 'patch': patch_drain,
              'choices': {0x4ac520: [1, 1, 1, 0], 0x4ac540: [0, 1, 2, 3, 6],
                          0x4365c0: [1, 1, 1, 0]}})
run_screen('state-done-454e30', 0x454e30, ['player_states.c'], 'vertrix_state_done_454e30', [U],
           U, PAIR, pair_case, TEXT,
           **{**MORE, 'choices': {0x42eca0: [1, 1, 0], 0x42ecc0: [1, 1, 0]}})
run_screen('state-done-454fc0', 0x454fc0, ['player_states.c'], 'vertrix_state_done_454fc0', [U],
           U, PAIR, pair_case, TEXT,
           **{**MORE, 'choices': {0x42eca0: [1, 1, 0], 0x42ecc0: [1, 1, 0]}})


GUARD = {address: 0 for address in (0x42ed40, 0x42ed70, 0x42eba0, 0x43a510, 0x43bbf0, 0x4ac8f0,
                                    LEAF)}


def patch_guard(rng, handle, data):
    patch_more(rng, handle, data)
    for field in (0x4d0, 0x4d4, 0x4d8):
        data[field:field + 4] = rng.choice([0, 0, 0, rng.getrandbits(32)]).to_bytes(4, 'little')
    data[0x3b4:0x3b8] = rng.choice(
        [0x806000 + 0x1000 * i for i in range(4)]).to_bytes(4, 'little')


def guard_case(rng, pool, cpu):
    player, ebx, ecx = rng.choice(pool.handles), rng.getrandbits(32), rng.getrandbits(32)
    return {'eax': player, 'ebx': ebx, 'ecx': ecx}, (), (player, ebx, ecx)


def guard_ebx_case(rng, pool, cpu):
    player, ebx = rng.choice(pool.handles), rng.getrandbits(32)
    return {'eax': player, 'ebx': ebx}, (), (player, ebx)


run_screen('state-done-4552b0', 0x4552b0, ['player_states.c'], 'vertrix_state_done_4552b0', [U],
           U, GUARD, pair_case, TEXT,
           **{**MORE, 'choices': {0x42ed40: [1, 1, 0], 0x42ed70: [1, 1, 0]}})
run_screen('state-guard-455320', 0x455320, ['player_states.c'], 'vertrix_state_guard_455320',
           [U, U], U, GUARD, guard_ebx_case, TEXT, **{**MORE, 'patch': patch_guard})
run_screen('state-guard-4553a0', 0x4553a0, ['player_states.c'], 'vertrix_state_guard_4553a0',
           [U, U, U], U, GUARD, guard_case, TEXT,
           **{**MORE, 'patch': patch_guard,
              'choices': {0x42ed40: [1, 1, 0], 0x42ed70: [1, 1, 0]}})

run_screen('state-done-455c30', 0x455c30, ['player_states.c'], 'vertrix_state_done_455c30', [U],
           U, PAIR, pair_case, TEXT,
           **{**MORE, 'choices': {0x42eca0: [1, 1, 0], 0x42ecc0: [1, 1, 0]}})
run_screen('state-ask-455e00', 0x455e00, ['player_states.c'], 'vertrix_state_ask_455e00', [U], U,
           PAIR, pair_case, TEXT, **{**MORE, 'choices': {0x42eca0: [1, 0, 1]}})
REPLACE = {address: 0 for address in (0x42eca0, 0x4387b0, 0x4ac8f0, LEAF)}
run_screen('state-replace-455db0', 0x455db0, ['player_states.c'], 'vertrix_state_replace_455db0',
           [U], U, REPLACE, pair_case, TEXT, **{**MORE, 'choices': {0x42eca0: [1, 0, 1]}})
