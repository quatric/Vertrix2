"""Compare the original bonus effect handlers behind dispatcher 0x43c140 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from unicorn.x86_const import UC_X86_REG_ESP
from original import Original, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0xd00
FRAME = STACK - 4
VTABLE = 0x700400
SLOT_ONE = 0x700300
DRAW = 0x4826c0
CALLEES = (0x43acd0, 0x43ac00, 0x43bb60, 0x4ac8f0, 0x43bbf0, 0x43c0e0)
ALLOCATE = 0x4ca000
# 0x452e00 callees; the first four steer its flow and return small values
FLOW = {0x4ac540: (0, 1, 2, 3, 0xffffffff),
        0x438910: (0, 1, 1, 2), 0x4ac520: (0, 1, 1), 0x430090: (0, 1, 1),
        0x437350: (0, 1, 1), 0x4375f0: (0, 1, 1), 0x4378c0: (0, 1, 1), 0x437be0: (0, 1, 1),
        0x437d70: (0, 1, 1), 0x437060: (0, 1, 1), 0x42eca0: (0, 1, 1, 1), 0x42ecc0: (0, 1, 1, 1),
        0x4371b0: (0, 1, 1), 0x43b720: (0, 1, 1, 2), 0x43b800: (0, 1, 1, 2), 0x43b7c0: (0, 1, 1), 0x43d3b0: (0, 1), 0x438cd0: (0, 1), 0x43ab60: (0, 1, 1, 2), 0x4320c0: (1, 1, 1, 0), 0x4330d0: (1, 1, 1, 0)}
MATCH_CALLEES = (0x438cd0, 0x43ab60, 0x4320c0, 0x4330d0, 0x431d80, 0x42ee20, 0x42eda0, 0x42ee80,
                 0x433040, 0x43a560)
EFFECT_CODE = 0x450000
GRID, COMPANION, MARKERS = 0x220, 0x87c, 0xb94
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
Allocate = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_void_p)
Range = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_uint32), c.POINTER(c.c_uint32), c.c_void_p)


Global = c.CFUNCTYPE(U, U, c.c_void_p)


class Factory(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', Allocate), ('draw', Draw), ('range', Range),
                ('context', c.c_void_p)]


class Gate(Stubs):
    """0x4ac8f0 is a boundary only where the effect code calls it; inside the recovered 0x436b40 it
    runs for real."""

    def _hit(self, cpu, address, size, context):
        if address == 0x4ac8f0:
            esp = cpu.reg_read(UC_X86_REG_ESP)
            if struct.unpack('<I', bytes(cpu.mem_read(esp, 4)))[0] < EFFECT_CODE:
                return
        super()._hit(cpu, address, size, context)

Virtual = c.CFUNCTYPE(c.c_int32, c.c_void_p, U, U, U)


class Gate_(c.Structure):
    _fields_ = [('handler', U), ('kind', c.c_int), ('state', U), ('callee', U)]


class AttackCall(c.Structure):
    _fields_ = [('target', U), ('on_opponent', c.c_int), ('set_edx', c.c_int), ('edx', U)]


class Attack(c.Structure):
    _fields_ = [('routine', U), ('handler', U), ('source', U), ('destination', U), ('cleared', U),
                ('clear_b90', c.c_int), ('count', c.c_uint), ('calls', AttackCall * 8)]


class CheckBind(c.Structure):
    _fields_ = [('routine', U), ('first', U), ('second', U), ('kind', c.c_int), ('token', U)]


class SlideStart(c.Structure):
    _fields_ = [(name, U) for name in ('routine', 'check', 'first_offset', 'second_offset',
                                       'dword_table', 'word_table', 'word_offset', 'token')]


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(14)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('calls', c.POINTER(Calls)), ('resolve', Resolve), ('resolve_context', c.c_void_p),
                ('virtual_call', Virtual), ('virtual_context', c.c_void_p), ('draw', Draw),
                ('draw_context', c.c_void_p), ('factory', c.POINTER(Factory)),
                ('global_read', Global), ('global_context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'bonus-effects',
              ['bonus_effects.c', 'call_glue.c', 'choice_grid.c', 'actor_storage.c',
               'actor_fields.c', 'board_conversions.c', 'block_factory.c', 'board_markers.c',
               'board.c', 'board_cells.c', 'fixed_point.c', 'board_actions.c', 'random.c'])
    n.vertrix_effect_forced_choice.argtypes = [c.POINTER(Services), U, U]
    n.vertrix_effect_forced_choice.restype = U
    n.vertrix_effect_convert_blocks.argtypes = [c.POINTER(Services), U, U]
    n.vertrix_effect_convert_blocks.restype = U
    n.vertrix_effect_board_match.argtypes = [c.POINTER(Services), U, U]
    n.vertrix_effect_board_match.restype = U
    n.vertrix_effect_state_gate.argtypes = [c.POINTER(Services), U, c.POINTER(Gate_)]
    n.vertrix_effect_state_gate.restype = U
    gates = (Gate_ * 16).in_dll(n, 'vertrix_state_gates')
    for name in ('pair_sound', 'copy_speed'):
        function = getattr(n, 'vertrix_effect_' + name)
        function.argtypes = [c.POINTER(Services), U, U]
        function.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x453ad0)
    pool = Pool(cpu, 12, SIZE)
    returns, draws, native_log, replay, draw_replay = [], [], [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == DRAW:
            value = rng.randrange(max(1, edx & 0xffff))
            draws.append(value)
            return value
        if address == 0x43b7c0 and progress_effects is not None:
            # the callee changes the opponent's +0x17c; the native replay applies the same change
            new = rng.choice([rng.getrandbits(32), rng.getrandbits(4)])
            cpu.mem_write(opponent + 0x17c, struct.pack('<I', new))
            progress_effects.append(new)
        if address == ALLOCATE:
            handle = targets[len(allocations) % len(targets)]
            allocations.append(handle)
            return handle
        value = rng.choice(FLOW[address]) if address in FLOW else rng.getrandbits(32)
        returns.append(value)
        return value

    allocations, alloc_replay = [], []
    progress_effects = None
    targets = pool.handles[6:]
    stubs = Gate(cpu, handler)
    stubs.add(DRAW)
    stubs.add(ALLOCATE)
    for address in CALLEES + (SLOT_ONE,):
        stubs.add(address, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) + (
            (s.stack, s.stack_next, s.stack_third) if s.target == 0x43a5f0 else ()))
        if s.target == 0x43b7c0 and progress_effects:
            struct.pack_into('<I', pool.buffers[opponent], 0x17c, progress_effects.pop(0))
        return replay.pop(0)

    @Virtual
    def virtual(context, handle, slot, argument):
        native_log.append(('virtual', handle, slot))
        value = replay.pop(0)
        return value - (1 << 32) if value >= 1 << 31 else value

    @Draw
    def draw(divisor, context):
        return draw_replay.pop(0)

    calls = Calls(call, None)
    @Allocate
    def allocate(size, context):
        return alloc_replay.pop(0)

    @Range
    def table_range(index, lo, hi, context):
        lo[0] = struct.unpack('<I', bytes(cpu.mem_read((0x53bcd0 + 8 * index) & 0xffffffff, 4)))[0]
        hi[0] = struct.unpack('<I', bytes(cpu.mem_read((0x53bcd4 + 8 * index) & 0xffffffff, 4)))[0]
        return 1

    @Global
    def global_read(address, context):
        return struct.unpack('<I', bytes(cpu.mem_read(address, 4)))[0]

    factory = Factory(pool.resolve, allocate, draw, table_range, None)
    services = Services(c.pointer(calls), pool.resolve, None, virtual, None, draw, None,
                        c.pointer(factory), global_read, None)
    totals = {'forced_choice': 0, 'no_choice': 0, 'unresolved': 0}
    player, opponent, own_board, opponent_board, grid_handle, other = pool.handles[:6]
    cpu.mem_write(VTABLE + 4, struct.pack('<I', SLOT_ONE))

    def patch(handle, data):
        if handle == player:
            struct.pack_into('<II', data, 0x3b0, opponent, 0)
            struct.pack_into('<I', data, 0x15c, own_board)
        elif handle == opponent:
            struct.pack_into('<I', data, 0x15c, opponent_board)
            struct.pack_into('<I', data, 0x3b8, grid_handle)
        elif handle == own_board:
            struct.pack_into('<I', data, 0x158, VTABLE)
        elif handle == grid_handle:
            density = rng.choice([0, 1, 2, 4, 6])
            for cell in range(28):
                value = 1 if rng.randrange(7) < density else rng.choice([0, 2, 3, 0xffffffff])
                struct.pack_into('<I', data, 0x1cc + 4 * cell, value)

    def normalized(entries):
        result = []
        for entry in entries:
            if entry[0] in (DRAW, ALLOCATE):
                continue
            if entry[0] == SLOT_ONE:
                result.append(('virtual', entry[1], 1))
            elif entry[0] == 0x43a5f0:
                result.append(tuple(entry[:8]))
            else:
                result.append(tuple(entry[:5]))
        return result

    for case in range(args.cases):
        pool.fill(rng, patch)
        stubs.log.clear()
        returns.clear()
        draws.clear()
        native_log.clear()
        result = original.call(0x453ad0, eax=player) & 0xffffffff
        replay[:] = list(returns)
        draw_replay[:] = list(draws)
        got = n.vertrix_effect_forced_choice(c.byref(services), player, FRAME)
        expected = normalized(stubs.log)
        assert native_log == expected, (case, native_log, expected)
        assert got == result, (case, hex(got), hex(result))
        assert not replay and not draw_replay, case
        assert pool.same(), (case, pool.diff())
        totals['forced_choice' if any(e[0] == 0x4ac8f0 for e in expected) else 'no_choice'] += 1
    # 0x453150: the block conversion effect (ids 4 and 5)
    usable = [i for i in range(20) if (struct.unpack('<I', bytes(cpu.mem_read(0x53bcd4 + 8 * i, 4)))[0]
              - struct.unpack('<I', bytes(cpu.mem_read(0x53bcd0 + 8 * i, 4)))[0] + 1) & 0xffff]

    def patch_convert(handle, data):
        if handle == player:
            struct.pack_into('<II', data, 0x3b0, opponent, 0)
            struct.pack_into('<I', data, 0x15c, own_board)
            struct.pack_into('<I', data, 0x3dc, rng.choice([5, 6, 5, 6, 0, 1, 2, 3, 4, 7]))
        elif handle == opponent:
            struct.pack_into('<I', data, 0x15c, opponent_board)
        elif handle in (own_board, opponent_board):
            if handle == own_board:
                struct.pack_into('<I', data, 0x158, VTABLE)
            fill = rng.choice([0.1, 0.5, 0.9])
            for grid in (GRID, COMPANION):
                for i in range(65):
                    struct.pack_into('<I', data, grid + 4 * i,
                                     rng.choice(targets) if rng.random() < fill else 0)
            struct.pack_into('<H', data, 0xe, rng.randrange(0, 200))
            struct.pack_into('<H', data, 0x16, rng.randrange(0, 200))
        elif handle in targets:
            data[0x15c] = rng.choice([5, 6, 5, 6, 0, 1, 2, 3, 4, 7, 0xff])
    convert_totals = {'equal': 0, 'first_more': 0, 'first_fewer': 0, 'converted_second': 0}
    for case in range(args.cases):
        pool.fill(rng, patch_convert)
        stubs.log.clear()
        returns.clear()
        draws.clear()
        allocations.clear()
        native_log.clear()
        result = original.call(0x453150, eax=player) & 0xffffffff
        replay[:] = list(returns)
        draw_replay[:] = list(draws)
        alloc_replay[:] = list(allocations)
        got = n.vertrix_effect_convert_blocks(c.byref(services), player, FRAME)
        expected = normalized(stubs.log)
        assert native_log == expected, (case, native_log, expected)
        assert got == result, (case, hex(got), hex(result))
        assert not replay and not draw_replay and not alloc_replay, case
        assert pool.same(), (case, pool.diff())
        if not any(e[0] == 0x4ac8f0 for e in expected):
            convert_totals['equal'] += 1
        else:
            convert_totals['first_more' if expected[0][0] == 0x43ac00 else 'first_fewer'] += 1
            struct_second = struct.unpack_from('<I', pool.buffers[player].raw, 0x440)[0]
            convert_totals['converted_second'] += struct_second > 0
    # 0x452e00: the board match effect (id 1)
    for address in MATCH_CALLEES:
        stubs.add(address, 0)

    def patch_match(handle, data):
        patch_convert(handle, data)
        if handle == player:
            struct.pack_into('<I', data, 0x3dc, 0)
        elif handle == opponent:
            struct.pack_into('<I', data, 0x3b4, rng.getrandbits(32))
            struct.pack_into('<I', data, 0x170, rng.choice([1, 1, 0, 2]))
        elif handle == opponent_board:
            struct.pack_into('<I', data, 0xa60, targets[0])
        elif handle == targets[0]:
            struct.pack_into('<III', data, 0x15c, *targets[1:4])
        elif handle in targets[1:4]:
            data[0x15c] = rng.choice([0, 1, 2, 3, 4, 5, 6, 0xff, 0x80])
    match_totals = {'equal_boards': 0, 'chain': 0, 'pending_cleared': 0, 'plain': 0}
    for case in range(args.cases):
        pool.fill(rng, patch_match)
        stubs.log.clear()
        returns.clear()
        draws.clear()
        native_log.clear()
        entry_ebx = rng.getrandbits(32)
        result = original.call(0x452e00, eax=player, ebx=entry_ebx) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_effect_board_match(c.byref(services), player, entry_ebx)
        expected = normalized(stubs.log)
        assert native_log == expected, (case, native_log, expected)
        assert got == result, (case, hex(got), hex(result))
        assert not replay, case
        assert pool.same(), (case, pool.diff())
        targets_hit = {e[0] for e in expected if e[0] != 'virtual'}
        if 0x43ab60 not in targets_hit:
            match_totals['equal_boards'] += 1
        elif 0x43a560 in targets_hit:
            match_totals['pending_cleared'] += 1
        elif 0x431d80 in targets_hit:
            match_totals['chain'] += 1
        else:
            match_totals['plain'] += 1
    # 0x453b90 and 0x453c00
    for address in (0x43d3b0, 0x43ccf0, 0x43bae0):
        stubs.add(address, 0)

    def patch_small(handle, data):
        patch_convert(handle, data)
        if handle == player:
            struct.pack_into('<II', data, 0x3f8, rng.getrandbits(32), 0)
            struct.pack_into('<I', data, 0x3cc, rng.getrandbits(32))
    small_totals = {'pair_sound_sound': 0, 'pair_sound_plain': 0, 'copy_speed': 0}
    for name, address, function in (('0x453b90', 0x453b90, n.vertrix_effect_pair_sound),
                                    ('0x453c00', 0x453c00, n.vertrix_effect_copy_speed)):
        for case in range(args.cases):
            pool.fill(rng, patch_small)
            stubs.log.clear()
            returns.clear()
            draws.clear()
            native_log.clear()
            entry_edx = rng.getrandbits(32)
            result = original.call(address, eax=player, edx=entry_edx) & 0xffffffff
            replay[:] = list(returns)
            got = function(c.byref(services), player, entry_edx)
            expected = normalized(stubs.log)
            assert native_log == expected, (name, case, native_log, expected)
            assert got == result, (name, case, hex(got), hex(result))
            assert not replay, case
            assert pool.same(), (name, case, pool.diff())
            if address == 0x453c00:
                small_totals['copy_speed'] += 1
            else:
                small_totals['pair_sound_sound' if any(e[0] == 0x43ccf0 for e in expected)
                             else 'pair_sound_plain'] += 1
    # The sixteen state gate handlers 0x4535d0..0x453a80
    for callee in sorted({gate.callee for gate in gates}):
        stubs.add(callee, 0)
    gate_totals = {'matched': 0, 'other': 0}

    def patch_gate(gate):
        def patch(handle, data):
            patch_convert(handle, data)
            if handle in (player, opponent):
                matched = rng.random() < 0.5
                state = gate.state if matched else rng.choice([gate.state + 1, 0, 0x22])
                struct.pack_into('<I', data, 0x4c8, state if rng.random() < 0.9 else
                                 rng.getrandbits(32))
        return patch
    for gate in gates:
        for case in range(max(1, args.cases // 4)):
            pool.fill(rng, patch_gate(gate))
            stubs.log.clear()
            returns.clear()
            draws.clear()
            native_log.clear()
            result = original.call(gate.handler, eax=player) & 0xffffffff
            replay[:] = list(returns)
            got = n.vertrix_effect_state_gate(c.byref(services), player, c.byref(gate))
            expected = normalized(stubs.log)
            assert native_log == expected, (hex(gate.handler), case, native_log, expected)
            assert got == result, (hex(gate.handler), case, hex(got), hex(result))
            assert not replay, case
            assert pool.same(), (hex(gate.handler), case, pool.diff())
            gate_totals['matched' if expected[0][0] == 0x43acd0 else 'other'] += 1
    # 0x452830, 0x452880 and 0x4528e0
    for address in (0x43b800, 0x43b7c0):
        stubs.add(address, 0)
    progress_effects = []
    function_gate = {0x452830: n.vertrix_effect_negated_gate, 0x452880: n.vertrix_effect_value_gate,
                     0x4528e0: n.vertrix_effect_progress_gate}
    for function in function_gate.values():
        function.argtypes = [c.POINTER(Services), U]
        function.restype = U

    def patch_values(handle, data):
        patch_convert(handle, data)
        if handle == player:
            struct.pack_into('<II', data, 0x3bc, rng.getrandbits(32), rng.getrandbits(32))
    value_totals = {}
    for address, function in function_gate.items():
        for case in range(args.cases):
            pool.fill(rng, patch_values)
            stubs.log.clear()
            returns.clear()
            draws.clear()
            native_log.clear()
            progress_effects.clear()
            result = original.call(address, eax=player) & 0xffffffff
            replay[:] = list(returns)
            got = function(c.byref(services), player)
            expected = normalized(stubs.log)
            assert native_log == expected, (hex(address), case, native_log, expected)
            assert got == result, (hex(address), case, hex(got), hex(result))
            assert not replay and not progress_effects, case
            assert pool.same(), (hex(address), case, pool.diff())
            path = tuple(e[0] for e in expected if e[0] not in ('virtual', 0x43bbf0))
            key = hex(address) + ':' + ','.join(hex(t) for t in path)
            value_totals[key] = value_totals.get(key, 0) + 1
    # 0x452a30 family: the arming step and its four handlers; 0x452d10 and 0x452d70
    for address in (0x43bad0, 0x43b810, 0x43b720):
        stubs.add(address, 0)
    stubs.add(0x43a5f0, 3)
    for name in ('arm_handler', 'armed_handler'):
        function = getattr(n, 'vertrix_effect_' + name)
        function.argtypes = [c.POINTER(Services), U, U, c.c_uint]
        function.restype = U
    for name in ('progress_update_gate', 'progress_compare'):
        function = getattr(n, 'vertrix_effect_' + name)
        function.argtypes = [c.POINTER(Services), U]
        function.restype = U

    def patch_arm(handle, data):
        patch_convert(handle, data)
        if handle == player:
            data[0x4cd] = rng.choice([0, 1, 1, 2, 2, 3, 3, 4, 4, 5])
            struct.pack_into('<I', data, 0x3c4, rng.choice([0, 1, 1, 2, 3]))
            for offset in (0x4d0, 0x4d4, 0x4d8):
                struct.pack_into('<I', data, offset,
                                 0 if rng.random() < 0.8 else rng.getrandbits(32))
            struct.pack_into('<I', data, 0x3b4, rng.getrandbits(32))
            struct.pack_into('<I', data, 0x3c8, rng.getrandbits(32))
            struct.pack_into('<I', data, 0x3e0, rng.getrandbits(32))
            struct.pack_into('<I', data, 0x17c, rng.choice([0, 1, 2, 0xffffffff]))
        elif handle == opponent:
            struct.pack_into('<I', data, 0x17c, rng.choice([0, 1, 2, 0xffffffff]))
    arm_totals = {}

    def check_one(label, case, address, native, *extra, **registers):
        pool.fill(rng, patch_arm)
        stubs.log.clear()
        returns.clear()
        draws.clear()
        native_log.clear()
        result = original.call(address, eax=player, **registers) & 0xffffffff
        replay[:] = list(returns)
        got = native(c.byref(services), player, *extra)
        expected = normalized(stubs.log)
        assert native_log == expected, (label, case, native_log, expected)
        assert got == result, (label, case, hex(got), hex(result))
        assert not replay, (label, case)
        assert pool.same(), (label, case, pool.diff())
        key = label + ':' + ','.join(hex(e[0]) if e[0] != 'virtual' else 'v' for e in expected)
        arm_totals[key] = arm_totals.get(key, 0) + 1
    for index, address in enumerate((0x452a30, 0x452b00, 0x452bb0, 0x452c60), 1):
        for case in range(args.cases):
            ebx = rng.getrandbits(32)
            check_one(hex(address), case, address, n.vertrix_effect_arm_handler, ebx, index,
                      ebx=ebx)
    for which, address in enumerate((0x452a50, 0x452b20, 0x452bd0, 0x452c80)):
        for case in range(args.cases):
            ebx = rng.getrandbits(32)
            check_one(hex(address), case, address, n.vertrix_effect_armed_handler, ebx, which,
                      ebx=ebx)
    for address, native in ((0x452d10, n.vertrix_effect_progress_update_gate),
                            (0x452d70, n.vertrix_effect_progress_compare)):
        for case in range(args.cases):
            check_one(hex(address), case, address, native)
    # 0x453460, 0x4534e0 and 0x453570: the stone handlers
    for address in (0x436fe0, 0x437060, 0x42eca0, 0x42ecc0, 0x4371b0, 0x42ebe0):
        stubs.add(address, 0)
    for name in ('stone_apply', 'stone_clear'):
        function = getattr(n, 'vertrix_effect_' + name)
        function.argtypes = [c.POINTER(Services), U]
        function.restype = U
    n.vertrix_effect_stone_arm.argtypes = [c.POINTER(Services), U, U]
    n.vertrix_effect_stone_arm.restype = U
    for case in range(args.cases):
        edx = rng.getrandbits(32)
        check_one('0x453460', case, 0x453460, n.vertrix_effect_stone_arm, edx, edx=edx)
    for address, native in ((0x4534e0, n.vertrix_effect_stone_apply),
                            (0x453570, n.vertrix_effect_stone_clear)):
        for case in range(args.cases):
            check_one(hex(address), case, address, native)
    # The twelve attack handlers that bind a follow-up handler to the opponent
    n.vertrix_effect_attack.argtypes = [c.POINTER(Services), U, U, c.POINTER(Attack)]
    n.vertrix_effect_attack.restype = U
    attacks = (Attack * 12).in_dll(n, 'vertrix_attacks')
    for address in (0x43ce00, 0x43baf0, 0x43b860):
        stubs.add(address, 0)

    def patch_attack(handle, data):
        patch_convert(handle, data)
        if handle == player:
            for offset in (0x3cc, 0x3d0, 0x3d4, 0x3d8, 0x3e8):
                struct.pack_into('<I', data, offset, rng.getrandbits(32))
    for attack in attacks:
        for case in range(args.cases):
            pool.fill(rng, patch_attack)
            stubs.log.clear()
            returns.clear()
            draws.clear()
            native_log.clear()
            entry_edx = rng.getrandbits(32)
            result = original.call(attack.routine, eax=player, edx=entry_edx) & 0xffffffff
            replay[:] = list(returns)
            got = n.vertrix_effect_attack(c.byref(services), player, entry_edx, c.byref(attack))
            expected = normalized(stubs.log)
            assert native_log == expected, (hex(attack.routine), case, native_log, expected)
            assert got == result, (hex(attack.routine), case, hex(got), hex(result))
            assert not replay, case
            assert pool.same(), (hex(attack.routine), case, pool.diff())
    # The check-and-bind handlers and their field follow-up
    n.vertrix_effect_check_bind.argtypes = [c.POINTER(Services), U, U, c.POINTER(CheckBind)]
    n.vertrix_effect_check_bind.restype = U
    n.vertrix_effect_field_bind.argtypes = [c.POINTER(Services), U]
    n.vertrix_effect_field_bind.restype = U
    checks = (CheckBind * 6).in_dll(n, 'vertrix_check_binds')
    for address in (0x4372c0, 0x437240, 0x437350, 0x4375a0, 0x4375f0, 0x4378c0, 0x437be0,
                    0x437d70, 0x4ac7b0, 0x4ac510, 0x437460):
        stubs.add(address, 0)
    for check in checks:
        for case in range(args.cases):
            cpu.mem_write(0x532bbc, struct.pack('<I', rng.randrange(0, 4)))
            pool.fill(rng, patch_attack)
            stubs.log.clear()
            returns.clear()
            draws.clear()
            native_log.clear()
            entry_edx = rng.getrandbits(32)
            result = original.call(check.routine, eax=player, edx=entry_edx) & 0xffffffff
            replay[:] = list(returns)
            got = n.vertrix_effect_check_bind(c.byref(services), player, entry_edx, c.byref(check))
            expected = normalized(stubs.log)
            assert native_log == expected, (hex(check.routine), case, native_log, expected)
            assert got == result, (hex(check.routine), case, hex(got), hex(result))
            assert not replay, case
            assert pool.same(), (hex(check.routine), case, pool.diff())
    for case in range(args.cases):
        pool.fill(rng, patch_attack)
        stubs.log.clear()
        returns.clear()
        draws.clear()
        native_log.clear()
        result = original.call(0x455510, eax=player) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_effect_field_bind(c.byref(services), player)
        expected = normalized(stubs.log)
        assert native_log == expected, ('0x455510', case, native_log, expected)
        assert got == result, ('0x455510', case, hex(got), hex(result))
        assert not replay, case
        assert pool.same(), ('0x455510', case, pool.diff())
    # The slide handlers 0x455e50, 0x455f10, 0x455f80 and 0x456060
    for address in (0x438910, 0x4ac500, 0x4ac520, 0x4ac5b0, 0x4ac540, 0x42f2e0, 0x42f760, 0x430090,
                    0x430100, 0x43d2b0, 0x4300b0):
        stubs.add(address, 0)

    def patch_slide(handle, data):
        patch_attack(handle, data)
        if handle == player:
            struct.pack_into('<II', data, 0x3e4, rng.getrandbits(32), 0)
            struct.pack_into('<I', data, 0x444, rng.choice([0, 1, 5, 0xffffffff]))
        elif handle == own_board:
            struct.pack_into('<I', data, 0x58, rng.choice([0, 5, 23, 24, 25, 47, 48, 100,
                                                           0xffffffff, rng.randrange(0, 600)]))
            struct.pack_into('<I', data, 0x18,
                             ((rng.randrange(-3, 4) << 16) & 0xffff0000) | rng.getrandbits(16))
    slide_calls = (
        (0x455e50, n.vertrix_effect_slide_begin, ()),
        (0x455f10, n.vertrix_effect_slide_wait, ('edx',)),
        (0x455f80, n.vertrix_effect_slide_advance, ('ebx', 'edx')),
        (0x456060, n.vertrix_effect_slide_end, ('ebx',)))
    for address, native, registers in slide_calls:
        native.argtypes = [c.POINTER(Services), U] + [U] * len(registers)
        native.restype = U
        for case in range(args.cases):
            cpu.mem_write(0x532bbc, struct.pack('<I', rng.randrange(0, 4)))
            pool.fill(rng, patch_slide)
            stubs.log.clear()
            returns.clear()
            draws.clear()
            native_log.clear()
            values = {name: rng.getrandbits(32) for name in registers}
            result = original.call(address, eax=player, **values) & 0xffffffff
            replay[:] = list(returns)
            got = native(c.byref(services), player, *[values[name] for name in registers])
            expected = normalized(stubs.log)
            assert native_log == expected, (hex(address), case, native_log, expected)
            assert got == result, (hex(address), case, hex(got), hex(result))
            assert not replay, case
            assert pool.same(), (hex(address), case, pool.diff())
    # The slide starts 0x453c90, 0x453fd0 and 0x4542e0
    n.vertrix_effect_slide_start.argtypes = [c.POINTER(Services), U, c.POINTER(SlideStart)]
    n.vertrix_effect_slide_start.restype = U
    starts = (SlideStart * 3).in_dll(n, 'vertrix_slide_starts')
    for address in (0x4314a0, 0x431780, 0x431930):
        FLOW[address] = (0, 1, 1)
        stubs.add(address, 0)
    for start in starts:
        for case in range(args.cases):
            cpu.mem_write(0x532bbc, struct.pack('<I', rng.randrange(0, 4)))
            pool.fill(rng, patch_slide)
            stubs.log.clear()
            returns.clear()
            draws.clear()
            native_log.clear()
            result = original.call(start.routine, eax=player) & 0xffffffff
            replay[:] = list(returns)
            got = n.vertrix_effect_slide_start(c.byref(services), player, c.byref(start))
            expected = normalized(stubs.log)
            assert native_log == expected, (hex(start.routine), case, native_log, expected)
            assert got == result, (hex(start.routine), case, hex(got), hex(result))
            assert not replay, case
            assert pool.same(), (hex(start.routine), case, pool.diff())
    # Objects that do not resolve: the effect stops where the original would have read them. Before
    # the first call (player, opponent, grid) nothing is called or stored; later failures still
    # never reach the final 0x43bbf0.
    for victim_index, victim in enumerate((player, opponent, grid_handle, own_board,
                                           opponent_board)):
        pool.fill(rng, patch)
        removed = pool.buffers.pop(victim)
        native_log.clear()
        replay[:] = [rng.getrandbits(32) for _ in range(16)]
        draw_replay[:] = [0] * 64
        before = {handle: pool.buffers[handle].raw for handle in pool.buffers}
        got = n.vertrix_effect_forced_choice(c.byref(services), player, FRAME)
        pool.buffers[victim] = removed
        if victim == opponent_board and not any(e[0] == 0x4ac8f0 for e in native_log):
            # without a drawn cell the opponent's board is never read
            totals['unresolved'] += 1
            continue
        assert got == 0, victim_index
        assert all(entry[0] != 0x43bbf0 for entry in native_log), (victim_index, native_log)
        if victim in (player, opponent, grid_handle):
            assert not native_log
            assert all(pool.buffers[h].raw == before[h] for h in before), victim_index
        totals['unresolved'] += 1
    for victim in (player, opponent, own_board, opponent_board):
        pool.fill(rng, patch_convert)
        removed = pool.buffers.pop(victim)
        native_log.clear()
        got = n.vertrix_effect_convert_blocks(c.byref(services), player, FRAME)
        pool.buffers[victim] = removed
        assert got == 0 and not native_log, victim
        totals['unresolved'] += 1
    report = {
        'status': 'passed',
        'complete_original_executions': {'0x453ad0': args.cases, '0x453150': args.cases,
                                        '0x452e00': args.cases,
                                        '0x453b90': args.cases, '0x453c00': args.cases,
                                        'state_gates_16': max(1, args.cases // 4) * 16,
                                        '0x452830': args.cases, '0x452880': args.cases,
                                        '0x4528e0': args.cases,
                                        **{hex(a): args.cases for a in (
                                            0x452a30, 0x452b00, 0x452bb0, 0x452c60, 0x452a50,
                                            0x452b20, 0x452bd0, 0x452c80, 0x452d10, 0x452d70,
                                            0x453460, 0x4534e0, 0x453570,
                                            0x453f40, 0x454250, 0x454560, 0x4547b0, 0x4549d0,
                                            0x454c30, 0x454e90, 0x455020, 0x455b20, 0x455ca0,
                                            0x45b9c0, 0x4554a0, 0x455600, 0x455670, 0x455790,
                                            0x4558e0, 0x455a00, 0x455510, 0x455e50, 0x455f10,
                                            0x455f80, 0x456060, 0x453c90, 0x453fd0, 0x4542e0)}},
        'paths': totals,
        'convert_paths': convert_totals,
        'match_paths': match_totals,
        'small_paths': small_totals,
        'gate_paths': gate_totals,
        'value_gate_paths': value_totals,
        'arm_paths': arm_totals,
        'scope': 'Complete original 0x453ad0 executes with 0x429fe0 running for real (its 0x4826c0 '
                 'draws stubbed and replayed) and the boundaries 0x43acd0, 0x43ac00, 0x43bb60, '
                 '0x4ac8f0, 0x43bbf0 and virtual slot 1 of the player board stubbed and logged; '
                 'the ordered call log with registers, every pool object and the result compare '
                 'with vertrix_effect_forced_choice. Unresolvable objects are rejected. Complete original 0x453150 runs the same way with the '
                 'real 0x436b40 and its callees (0x4ac8f0 only counts as a boundary where 0x453150 '
                 'calls it; allocation 0x4ca000 and draws are replayed) and 0x43c0e0 stubbed; the '
                 'registers left by 0x436b40 are compared through the boundary log. Complete original '
                 '0x452e00 runs with every callee (0x438cd0, 0x43ab60, 0x4320c0, 0x4330d0, 0x431d80, '
                 '0x42ee20, 0x42eda0, 0x42ee80, 0x433040, 0x43a560, 0x43bb60, 0x4ac8f0, 0x43c0e0, '
                 '0x43acd0, 0x43ac00, 0x43bbf0) stubbed and logged with registers; the flow '
                 'callees return replayed small values. Complete originals 0x453b90 and 0x453c00 '
                 'run with 0x43d3b0, 0x43ccf0, 0x43bae0 and the other callees stubbed and logged; '
                 'the entry edx is random.'
    }
    (args.build_dir / 'bonus-effects-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
