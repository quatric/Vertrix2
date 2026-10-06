"""Composed proof: original 0x43b9c0 driving original 0x43b720/0x43b800 versus
native match_reward driving native progress_update/bump_level.

Only true boundaries are stubbed (0x43bb00, 0x4715a0, 0x43c0e0, 0x43ac00,
0x4726d0, 0x431400); the reward -> progress -> level nesting executes for
real on both sides through the shared implementations."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct

from original import Original
from oracle_kit import Stubs, build

SIZE = 0x1000
PLAYER = 0x807000
OPPONENT = 0x80c000
MODE_FLAG = 0x532bc8
RACE_LIMIT = 0x532b34
LOSER_FLAG = 0x532a3c
PROGRESS_EFFECT = 0x4f81b4
LOOP_EFFECT_ADDR = 0x4f8190
CHAIN = 0x180
SUPPRESS = 0x44c
METER = 0x18c
PROGRESS_FIELD = 0x178
LEVEL = 0x17c
CURSOR = 0x15c
OPPONENT_FIELD = 0x3b0
ALIVE = 0x4c5


class ProgressGlobals(c.Structure):
    _fields_ = [("mode_flag", c.c_uint32), ("race_limit", c.c_uint32),
                ("loser_flag", c.c_uint32), ("effect", c.c_uint32)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()

    native = build(args.build_dir, 'player-reward-composed',
                   ['player_slots.c', 'piece.c', 'piece_children.c', 'actor_storage.c',
                    'actor_fields.c', 'object_scalars.c', 'timing.c', 'random.c', 'piece_actor_construct.c', 'piece_child_update.c', 'dword_transition.c', 'frame_resource.c', 'timer.c'])
    Reset = c.CFUNCTYPE(None, c.c_uint32, c.c_uint8, c.c_void_p)
    Letter = c.CFUNCTYPE(None, c.c_uint32, c.c_void_p)
    Effect = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)
    Win = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_void_p)
    Refresh = c.CFUNCTYPE(None, c.c_uint32, c.c_void_p)
    Resolve = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p),
                         c.POINTER(c.c_size_t), c.c_void_p)
    LevelNotify = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)
    RewardProgress = c.CFUNCTYPE(None, c.c_uint32, c.c_int32, c.c_void_p)
    RewardLevel = c.CFUNCTYPE(None, c.c_uint32, c.c_int32, c.c_void_p)
    native.vertrix_player_progress_update.argtypes = [
        c.c_void_p, c.c_size_t, c.c_uint32, c.c_int32, c.POINTER(ProgressGlobals),
        Reset, Letter, Effect, Win, Refresh, Resolve, c.c_void_p]
    native.vertrix_player_progress_update.restype = c.c_int
    native.vertrix_player_bump_level.argtypes = [c.c_void_p, c.c_size_t, c.c_int32,
                                                 LevelNotify, c.c_void_p]
    native.vertrix_player_bump_level.restype = c.c_int
    native.vertrix_player_match_reward.argtypes = [
        c.c_void_p, c.c_size_t, c.c_uint32, c.c_int32, c.c_uint32,
        RewardProgress, RewardLevel, Effect, Refresh, c.c_void_p]
    native.vertrix_player_match_reward.restype = c.c_int

    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43b9c0 + 0x43b720)
    win_returns = []
    host_opp = {}
    host_player_box = {}
    globs_box = {}
    log_reset, log_letter, log_effect, log_win, log_refresh, log_notify = ([] for _ in range(6))

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x43ac00:
            return win_returns.pop(0)
        return None

    stubs = Stubs(cpu, handler)
    for addr in (0x43bb00, 0x4715a0, 0x43c0e0, 0x43ac00, 0x4726d0, 0x431400):
        stubs.add(addr)

    @Reset
    def preset(player, b01, context):
        log_reset.append((player, b01))

    @Letter
    def pletter(mode, context):
        log_letter.append(mode)

    @Effect
    def peffect(player, eff, context):
        log_effect.append((player, eff))

    @Win
    def pwin(player, context):
        value = win_returns.pop(0)
        log_win.append((player, value))
        return value

    @Refresh
    def refresh(arg, context):
        log_refresh.append(arg)

    @LevelNotify
    def level_notify(child, level, context):
        log_notify.append((child, level))

    @Resolve
    def resolve(handle, storage, size, context):
        if handle in host_opp:
            storage[0] = c.cast(host_opp[handle], c.c_void_p)
            size[0] = SIZE
            return 1
        return 0

    @RewardProgress
    def reward_progress(player, delta, context):
        hp = host_player_box['buf']
        gl = globs_box['globs']
        native.vertrix_player_progress_update(hp, SIZE, PLAYER, delta, gl, preset, pletter,
                                              peffect, pwin, refresh, resolve, None)

    @RewardLevel
    def reward_level(player, delta, context):
        hp = host_player_box['buf']
        native.vertrix_player_bump_level(hp, SIZE, delta, level_notify, None)

    @Effect
    def reward_effect(player, eff, context):
        log_effect.append((player, eff))

    verified = 0
    for case in range(args.cases):
        bucket = case % 5
        player = bytearray(rng.randbytes(SIZE))
        opponent = bytearray(rng.randbytes(SIZE))
        if bucket == 0:  # reward loop, progress normal (race off)
            struct.pack_into('<I', player, CHAIN, 0)
            reward, suppress = 30, 0
            struct.pack_into('<I', player, PROGRESS_FIELD, rng.randrange(0, 100))
            flag, limit = 0, rng.getrandbits(32)
            opponent[ALIVE] = rng.randrange(256)
        elif bucket == 1:  # reward loop, progress wins (opponent alive)
            struct.pack_into('<I', player, CHAIN, 0)
            reward, suppress = 25, 0
            struct.pack_into('<I', player, PROGRESS_FIELD, 9)
            flag, limit = 1, 10
            opponent[ALIVE] = rng.choice([1, 2, 255])
        elif bucket == 2:  # reward loop, progress wins (opponent dead)
            struct.pack_into('<I', player, CHAIN, 5)
            reward, suppress = 10, 0
            struct.pack_into('<I', player, PROGRESS_FIELD, 9)
            flag, limit = 1, 10
            opponent[ALIVE] = 0
        elif bucket == 3:  # no reward loop, meter path
            struct.pack_into('<I', player, CHAIN, 50)
            reward, suppress = 3, 0
            struct.pack_into('<I', player, PROGRESS_FIELD, rng.randrange(0, 100))
            flag, limit = 0, rng.getrandbits(32)
            opponent[ALIVE] = rng.randrange(256)
        else:
            struct.pack_into('<I', player, CHAIN, rng.randrange(0, 20))
            reward = rng.randrange(-5, 60)
            suppress = rng.choice([0, 0, 1])
            struct.pack_into('<I', player, PROGRESS_FIELD, rng.randrange(0, 15))
            flag = rng.choice([0, 1])
            limit = rng.randrange(5, 20)
            opponent[ALIVE] = rng.randrange(256)
        struct.pack_into('<I', player, SUPPRESS, suppress)
        struct.pack_into('<I', player, OPPONENT_FIELD, OPPONENT)
        struct.pack_into('<I', player, LEVEL, rng.randrange(0, 10))
        struct.pack_into('<I', player, CURSOR, rng.getrandbits(32))
        loser = rng.getrandbits(32)
        prog_effect = rng.getrandbits(32)
        loop_effect = rng.getrandbits(32)
        cpu.mem_write(PLAYER, bytes(player))
        cpu.mem_write(OPPONENT, bytes(opponent))
        cpu.mem_write(MODE_FLAG, struct.pack('<I', flag))
        cpu.mem_write(RACE_LIMIT, struct.pack('<I', limit))
        cpu.mem_write(LOSER_FLAG, struct.pack('<I', loser))
        cpu.mem_write(PROGRESS_EFFECT, struct.pack('<I', prog_effect))
        cpu.mem_write(LOOP_EFFECT_ADDR, struct.pack('<I', loop_effect))

        win_values = [rng.getrandbits(32) for _ in range(64)]
        win_returns.clear()
        win_returns.extend(win_values)
        stubs.log.clear()
        original.call(0x43b9c0, eax=PLAYER, edx=reward & 0xffffffff)
        orig_player = bytes(cpu.mem_read(PLAYER, SIZE))
        orig_opp = bytes(cpu.mem_read(OPPONENT, SIZE))
        orig_loser = struct.unpack('<I', cpu.mem_read(LOSER_FLAG, 4))[0]
        orig_log = list(stubs.log)

        host_player = (c.c_uint8 * SIZE).from_buffer_copy(bytes(player))
        host_player_box['buf'] = host_player
        host_opp.clear()
        host_opp[OPPONENT] = (c.c_uint8 * SIZE).from_buffer_copy(bytes(opponent))
        globs = ProgressGlobals(flag, limit, loser, prog_effect)
        globs_box['globs'] = globs
        for lst in (log_reset, log_letter, log_effect, log_win, log_refresh, log_notify):
            lst.clear()
        win_returns.clear()
        win_returns.extend(win_values)
        got = native.vertrix_player_match_reward(host_player, SIZE, PLAYER, reward, loop_effect,
                                                 reward_progress, reward_level,
                                                 reward_effect, refresh, None)
        assert got == 1, f"case {case} native returned {got}"
        assert bytes(host_player) == orig_player, f"case {case} player mismatch"
        assert bytes(host_opp[OPPONENT]) == orig_opp, f"case {case} opponent touched"
        assert globs.loser_flag == orig_loser, f"case {case} loser mismatch"

        def reg_calls(addr):
            return [(e[1], e[2]) for e in orig_log if e[0] == addr]

        assert reg_calls(0x43bb00) == log_reset, f"case {case} reset mismatch"
        assert [e[1] for e in orig_log if e[0] == 0x4715a0] == log_letter, \
            f"case {case} letter mismatch"
        assert reg_calls(0x43c0e0) == log_effect, f"case {case} effect mismatch"
        assert [e[1] for e in orig_log if e[0] == 0x43ac00] == [p for p, _ in log_win], \
            f"case {case} win mismatch"
        assert [e[1] for e in orig_log if e[0] == 0x4726d0] == log_refresh, \
            f"case {case} refresh mismatch"
        assert reg_calls(0x431400) == log_notify, f"case {case} notify mismatch"
        verified += 1

    print(f"Verified {verified} composed cases reward->progress->level.")
    out = {
        "routine": "0x43b9c0 composed with 0x43b720 and 0x43b800",
        "cases": verified,
        "complete_original_executions": verified,
        "whole_object_compared": True,
        "call_logs_compared": True,
        "boundaries_stubbed": ["0x43bb00", "0x4715a0", "0x43c0e0", "0x43ac00",
                               "0x4726d0", "0x431400"]
    }
    Path("docs/player-reward-composed-verification.json").write_text(json.dumps(out, indent=2))


if __name__ == '__main__':
    main()
