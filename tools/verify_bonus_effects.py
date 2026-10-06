"""Compare the original bonus effect handlers behind dispatcher 0x43c140 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0xd00
FRAME = STACK - 4
VTABLE = 0x80e000
SLOT_ONE = 0x700300
DRAW = 0x4826c0
CALLEES = (0x43acd0, 0x43ac00, 0x43bb60, 0x4ac8f0, 0x43bbf0)
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
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
                ('draw_context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'bonus-effects',
              ['bonus_effects.c', 'call_glue.c', 'choice_grid.c', 'actor_storage.c',
               'actor_fields.c'])
    n.vertrix_effect_forced_choice.argtypes = [c.POINTER(Services), U, U]
    n.vertrix_effect_forced_choice.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x453ad0)
    pool = Pool(cpu, 6, SIZE)
    returns, draws, native_log, replay, draw_replay = [], [], [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == DRAW:
            value = rng.randrange(max(1, edx & 0xffff))
            draws.append(value)
            return value
        value = rng.getrandbits(32)
        returns.append(value)
        return value

    stubs = Stubs(cpu, handler)
    stubs.add(DRAW)
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
        replay.pop(0)
        return 0

    @Draw
    def draw(divisor, context):
        return draw_replay.pop(0)

    calls = Calls(call, None)
    services = Services(c.pointer(calls), pool.resolve, None, virtual, None, draw, None)
    totals = {'forced_choice': 0, 'no_choice': 0, 'unresolved': 0}
    player, opponent, own_board, opponent_board, grid_handle, other = pool.handles
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
            if entry[0] == DRAW:
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
        assert got == 0, victim_index
        assert all(entry[0] != 0x43bbf0 for entry in native_log), (victim_index, native_log)
        if victim in (player, opponent, grid_handle):
            assert not native_log
            assert all(pool.buffers[h].raw == before[h] for h in before), victim_index
        totals['unresolved'] += 1
    report = {
        'status': 'passed',
        'complete_original_executions': {'0x453ad0': args.cases},
        'paths': totals,
        'scope': 'Complete original 0x453ad0 executes with 0x429fe0 running for real (its 0x4826c0 '
                 'draws stubbed and replayed) and the boundaries 0x43acd0, 0x43ac00, 0x43bb60, '
                 '0x4ac8f0, 0x43bbf0 and virtual slot 1 of the player board stubbed and logged; '
                 'the ordered call log with registers, every pool object and the result compare '
                 'with vertrix_effect_forced_choice. Unresolvable objects are rejected.'
    }
    (args.build_dir / 'bonus-effects-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
