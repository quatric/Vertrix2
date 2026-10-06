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
FLOW = {0x43d3b0: (0, 1), 0x438cd0: (0, 1), 0x43ab60: (0, 1, 1, 2), 0x4320c0: (1, 1, 1, 0), 0x4330d0: (1, 1, 1, 0)}
MATCH_CALLEES = (0x438cd0, 0x43ab60, 0x4320c0, 0x4330d0, 0x431d80, 0x42ee20, 0x42eda0, 0x42ee80,
                 0x433040, 0x43a560)
EFFECT_CODE = 0x450000
GRID, COMPANION, MARKERS = 0x220, 0x87c, 0xb94
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
Allocate = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_void_p)
Range = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_uint32), c.POINTER(c.c_uint32), c.c_void_p)


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


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('calls', c.POINTER(Calls)), ('resolve', Resolve), ('resolve_context', c.c_void_p),
                ('virtual_call', Virtual), ('virtual_context', c.c_void_p), ('draw', Draw),
                ('draw_context', c.c_void_p), ('factory', c.POINTER(Factory))]


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
        if address == ALLOCATE:
            handle = targets[len(allocations) % len(targets)]
            allocations.append(handle)
            return handle
        value = rng.choice(FLOW[address]) if address in FLOW else rng.getrandbits(32)
        returns.append(value)
        return value

    allocations, alloc_replay = [], []
    targets = pool.handles[6:]
    stubs = Gate(cpu, handler)
    stubs.add(DRAW)
    stubs.add(ALLOCATE)
    for address in CALLEES + (SLOT_ONE,):
        stubs.add(address, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
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

    factory = Factory(pool.resolve, allocate, draw, table_range, None)
    services = Services(c.pointer(calls), pool.resolve, None, virtual, None, draw, None,
                        c.pointer(factory))
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
                                        '0x453b90': args.cases, '0x453c00': args.cases},
        'paths': totals,
        'convert_paths': convert_totals,
        'match_paths': match_totals,
        'small_paths': small_totals,
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
