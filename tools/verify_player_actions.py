"""Compare complete original player action routines with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path
from original import Original
from oracle_kit import Pool, Resolve, Stubs, build
U = c.c_uint32
SIZE = 0x1000
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
Notify = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'player-actions', ['player_actions.c', 'player_slots.c', 'event_stack.c', 'actor_storage.c', 'actor_fields.c', 'board_cells.c', 'random.c'])
    P, SZ = c.c_void_p, c.c_size_t
    n.vertrix_player_push_event.argtypes = [P, SZ, Resolve, P]
    UP = c.POINTER(U)
    for name in ('enter_452370', 'enter_4523d0'):
        getattr(n, 'vertrix_player_' + name).argtypes = [P, SZ, Resolve, P]
    for name in ('enter_452070', 'enter_4520b0'):
        getattr(n, 'vertrix_player_' + name).argtypes = [P, SZ, Resolve, P, UP]
    Read = c.CFUNCTYPE(c.c_int, U, c.c_uint, UP, c.c_void_p)
    class Globals(c.Structure):
        _fields_ = [('selector', U), ('low', U), ('width', U)]
    n.vertrix_player_draw_table_value.argtypes = [P, SZ, U, U, U, Read, P, Draw, P, c.POINTER(Globals), UP]
    @ Read
    def read(address, width, value, context):
        value[0] = int.from_bytes(bytes(cpu.mem_read(address, width)), 'little')
        return 1
    n.vertrix_player_randomize_level.argtypes = [P, SZ, Draw, P, Notify, P]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43bb60)
    pool = Pool(cpu, 3, SIZE)
    player, board, opponent = pool.handles
    draws, logged, replay = [], [], iter([])
    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4826c0:
            draws.append(rng.randrange(edx & 0xffff))
            return draws[- 1]
        return None
    stubs = Stubs(cpu, handler)
    stubs.add(0x4826c0)
    stubs.add(0x431400)
    @ Draw
    def draw(divisor, context):
        value = next(replay)
        assert value < divisor
        return value
    @ Notify
    def notify(child, level, context):
        logged.append((child, level))
    totals = {}
    def count(name):
        totals[name] = totals.get(name, 0) + 1
    def fresh():
        def patch(handle, data):
            if handle == opponent:
                struct.pack_into('<I', data, 0x15c, board)
                data[0x4c4] = rng.choice([0, 1, 1, 2])
                data[0x4cc] = rng.choice([0, 1, 1, 4, 4, 5])
                struct.pack_into('<I', data, 0x3b0, player)
            if handle == player:
                struct.pack_into('<I', data, 0x15c, board)
                struct.pack_into('<I', data, 0x3b0, opponent)
                data[0x3a4] = rng.choice([0, 1, 4, 8, 9, 10, 200])
                struct.pack_into('<I', data, 0x17c, rng.randrange(0, 10))
        pool.fill(rng, patch)
    for case in range(args.cases):
        fresh()
        original.call(0x43bb60, eax=player)
        assert n.vertrix_player_push_event(pool.buffers[player], SIZE, pool.resolve, None)
        assert pool.same(), (case, pool.diff())
        count('0x43bb60')
        fresh()
        draws.clear()
        stubs.log.clear()
        logged.clear()
        result = original.call(0x43b7c0, eax=player)
        replay = iter(list(draws))
        native = n.vertrix_player_randomize_level(pool.buffers[player], SIZE, draw, None, notify, None)
        assert next(replay, None) is None, case
        assert pool.same(), (case, pool.diff())
        assert [(e[1], e[2]) for e in stubs.log if e[0] == 0x431400] == logged, (case, stubs.log, logged, draws)
        count('0x43b7c0')
        for address, name in ((0x43bc90, 'enter_452070'), (0x43bce0, 'enter_452370'), (0x43ccb0, 'enter_4520b0'), (0x43bd00, 'enter_4523d0')):
            fresh()
            result = original.call(address, eax=player)
            function = getattr(n, 'vertrix_player_' + name)
            changed = U()
            if name in ('enter_452070', 'enter_4520b0'):
                assert function(pool.buffers[player], SIZE, pool.resolve, None, c.byref(changed))
                assert changed.value == result & 0xff, (case, name, result)
            else:
                assert function(pool.buffers[player], SIZE, pool.resolve, None)
                assert pool.same(), (case, name, pool.diff())
                count('0x%x' % address)
        fresh()
        struct.pack_into('<I', pool.buffers[player], 0x488, rng.randrange(0, 4))
        cpu.mem_write(player, bytes(pool.buffers[player].raw))
        low_row, width_row = rng.randrange(0, 5), rng.randrange(0, 5)
        level = struct.unpack('<I', bytes(cpu.mem_read(0x532bbc, 4)))[0]
        draws.clear()
        result = original.call(0x43b6a0, eax=player, edx=low_row, ebx=width_row) & 0xffffffff
        replay = iter(list(draws))
        got, out = Globals(), U()
        assert n.vertrix_player_draw_table_value(pool.buffers[player], SIZE, low_row, width_row, level, read, None, draw, None, c.byref(got), c.byref(out))
        assert out.value == result, (case, out.value, result)
        assert next(replay, None) is None, case
        assert [got.selector, got.low, got.width] == list(struct.unpack('<3I', bytes(cpu.mem_read(0x540f80, 4)) + bytes(cpu.mem_read(0x540f78, 4)) + bytes(cpu.mem_read(0x540f7c, 4)))), case
        count('0x43b6a0')
    report = {'status': 'passed', 'complete_original_executions': totals, 'scope': 'Complete 43b6a0, 43bb60, 43b7c0, 43bc90, 43bce0, 43ccb0 and 43bd00 execute in the original (the recovered ' '482060, 482750 and 43b810 run for real, 4826c0 draws stubbed and ' 'replayed, 431400 stubbed and logged); whole objects, notifications and the ' 'draws consumed compare.'}
    (args.build_dir / 'player-actions-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
