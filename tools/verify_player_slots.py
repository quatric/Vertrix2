"""Compare complete original player slot routines with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
Notify = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
G_FLAG, G_LAST, G_OUT = 0x532bc8, 0x532b34, 0x540f44


class Globals(c.Structure):
    _fields_ = [('mode_flag', U), ('last_index', U), ('candidate', U), ('level', U), ('draw', U),
                ('drawn', U)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'player-slots', ['player_slots.c', 'actor_storage.c'])
    n.vertrix_player_mode_in_group_a.argtypes = [c.c_void_p, c.c_size_t]
    n.vertrix_player_mode_in_group_b.argtypes = [c.c_void_p, c.c_size_t]
    n.vertrix_player_set_side.argtypes = [c.c_void_p, c.c_size_t, U, c.c_uint8, Resolve, c.c_void_p]
    n.vertrix_player_set_level.argtypes = [c.c_void_p, c.c_size_t, c.c_int32, Notify, c.c_void_p]
    n.vertrix_player_first_turn.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(Globals), Resolve, Draw,
                                            c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43aab0)
    pool = Pool(cpu, 8, 0x1000)
    draws = []
    stubs = Stubs(cpu, lambda address, eax, edx, ebx, ecx, stack:
                  draws.append(rng.randrange(edx & 0xffff)) or draws[-1] if address == 0x4826c0 else None)
    stubs.add(0x4826c0)
    stubs.add(0x431400)
    native = []
    replay = iter([])

    @Notify
    def notify(child, level, context):
        native.append((child, level))

    @Draw
    def draw(divisor, context):
        return next(replay)

    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    handles = pool.handles
    for case in range(args.cases):
        player = handles[0]

        def patch(handle, data):
            struct.pack_into('<I', data, 0x15c, rng.choice(handles))
            struct.pack_into('<I', data, 0x450, rng.choice(handles))
            struct.pack_into('<I', data, 0x3b0, rng.choice(handles))
            struct.pack_into('<I', data, 0x4c8, rng.choice([0x25, 0x26, 0x27, 0x32, 0x33, 0x34, 0x24,
                                                          0x28, 0x31, 0x35, 0, rng.getrandbits(32)]))
            struct.pack_into('<I', data, 0x178, rng.choice([0, 1, 2, 3, 0xffffffff, 0x80000000,
                                                          rng.getrandbits(32)]))
            struct.pack_into('<I', data, 0x17c, rng.choice([0, 1, 9, 10, rng.getrandbits(32)]))

        def fresh():
            pool.fill(rng, patch)

        def check(name):
            assert pool.same(), (case, name, pool.diff())
            count(name)

        for address, native_function, name in ((0x43d3b0, n.vertrix_player_mode_in_group_a, 'group_a'),
                                               (0x43d3d0, n.vertrix_player_mode_in_group_b, 'group_b')):
            fresh()
            result = original.call(address, eax=player)
            assert native_function(pool.buffers[player], 0x1000) == result & 0xffffffff, (case, name)
            check(name)
        fresh()
        side = rng.choice([0, 1, 2, 255, rng.randrange(256)])
        original.call(0x43aab0, eax=player, edx=side)
        assert n.vertrix_player_set_side(pool.buffers[player], 0x1000, player, side, pool.resolve, None)
        check('set_side')
        fresh()
        level = rng.choice([-5, -1, 0, 1, 5, 9, 10, 11, 100, 0x7fffffff, -0x80000000])
        stubs.log.clear()
        native.clear()
        result = original.call(0x43b810, eax=player, edx=level & 0xffffffff)
        assert n.vertrix_player_set_level(pool.buffers[player], 0x1000, level, notify, None) == result
        assert [(e[1], e[2]) for e in stubs.log] == native, case
        check('set_level')
        fresh()
        flag = rng.choice([0, 1, 1, 2])
        last = rng.choice([1, 2, 3, 4, rng.getrandbits(32)])
        own = struct.unpack('<I', cpu.mem_read(player + 0x178, 4))[0]
        if flag == 1 and rng.random() < 0.5:
            last = (own + 1) & 0xffffffff
        cpu.mem_write(G_FLAG, struct.pack('<I', flag))
        cpu.mem_write(G_LAST, struct.pack('<I', last))
        cpu.mem_write(G_OUT, struct.pack('<4I', *[0x11111111 * (k + 1) for k in range(4)]))
        draws.clear()
        result = original.call(0x43b1a0, eax=player)
        replay = iter(list(draws))
        globals_ = Globals(flag, last, 0x11111111, 0x22222222, 0x33333333, 0x44444444)
        found = n.vertrix_player_first_turn(pool.buffers[player], 0x1000, c.byref(globals_), pool.resolve,
                                            draw, None)
        assert found == result & 0xffffffff, case
        after = struct.unpack('<4I', cpu.mem_read(G_OUT, 16))
        assert (globals_.candidate, globals_.level, globals_.draw, globals_.drawn) == (
            after[0], after[1], after[2], after[3]), (case, after)
        assert next(replay, None) is None, case
        check('first_turn')
    report = {'status':
            'passed', 'complete_original_executions' : totals,
                                                       'scope'
                : 'Complete 43d3b0, 43d3d0, 43aab0, 43b810 and 43b1a0 execute in the original ' '(4826c0 draws stubbed and replayed, 431400 stubbed and logged); results, ' 'the shared globals and every pool object compare.'
            }
            (args.build_dir / 'player-slots-verification.json')
                    .write_text(json.dumps(report, indent = 2) + '\n')
                        print(json.dumps(report, indent = 2))

                            if __name__ == '__main__' : main()
