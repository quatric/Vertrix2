"""Compare original 0x43b9c0 with native player match-reward recovery."""
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
LOOP_EFFECT_ADDR = 0x4f8190
CHAIN = 0x180
SUPPRESS = 0x44c
METER = 0x18c
LOOP_FLAG = 0x3ac


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()

    native = build(args.build_dir, 'player-reward',
                   ['player_slots.c', 'piece.c', 'piece_children.c', 'actor_storage.c',
                    'actor_fields.c', 'object_scalars.c', 'timing.c', 'random.c'])
    Progress = c.CFUNCTYPE(None, c.c_uint32, c.c_int32, c.c_void_p)
    Level = c.CFUNCTYPE(None, c.c_uint32, c.c_int32, c.c_void_p)
    Effect = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)
    Refresh = c.CFUNCTYPE(None, c.c_uint32, c.c_void_p)
    native.vertrix_player_match_reward.argtypes = [
        c.c_void_p, c.c_size_t, c.c_uint32, c.c_int32, c.c_uint32,
        Progress, Level, Effect, Refresh, c.c_void_p]
    native.vertrix_player_match_reward.restype = c.c_int

    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43b9c0)
    native_progress, native_level, native_effect, native_refresh = [], [], [], []

    stubs = Stubs(cpu, lambda address, eax, edx, ebx, ecx, stack: None)
    for addr in (0x43b720, 0x43b800, 0x43c0e0, 0x4726d0):
        stubs.add(addr)

    @Progress
    def progress(player, delta, context):
        native_progress.append((player, delta))

    @Level
    def level(player, delta, context):
        native_level.append((player, delta))

    @Effect
    def effect(player, eff, context):
        native_effect.append((player, eff))

    @Refresh
    def refresh(arg, context):
        native_refresh.append(arg)

    verified = 0
    for case in range(args.cases):
        bucket = case % 8
        player = bytearray(rng.randbytes(SIZE))
        if bucket == 0:  # multi-iteration loop
            struct.pack_into('<I', player, CHAIN, 0)
            reward = 100
            suppress = 0
        elif bucket == 1:  # single loop iteration
            struct.pack_into('<I', player, CHAIN, 5)
            reward = 5
            suppress = 0
        elif bucket == 2:  # no loop
            struct.pack_into('<I', player, CHAIN, 10)
            reward = 2
            suppress = 0
        elif bucket == 3:  # suppress clears meter
            struct.pack_into('<I', player, CHAIN, 10)
            reward = 2
            suppress = 1
        elif bucket == 4:  # meter caps at 3
            struct.pack_into('<I', player, CHAIN, 10)
            struct.pack_into('<I', player, METER, 2)
            reward = 5
            suppress = 0
        elif bucket == 5:  # meter lands exactly 3
            struct.pack_into('<I', player, CHAIN, 10)
            struct.pack_into('<I', player, METER, 1)
            reward = 2
            suppress = 0
        elif bucket == 6:  # negative reward
            struct.pack_into('<I', player, CHAIN, 10)
            struct.pack_into('<I', player, METER, 2)
            reward = -1
            suppress = 0
        else:  # random
            struct.pack_into('<I', player, CHAIN, rng.randrange(0, 30))
            struct.pack_into('<I', player, METER, rng.randrange(0, 6))
            reward = rng.randrange(-5, 130)
            suppress = rng.choice([0, 0, 1, 2])
        struct.pack_into('<I', player, SUPPRESS, suppress)
        loop_effect = rng.getrandbits(32)
        cpu.mem_write(PLAYER, bytes(player))
        cpu.mem_write(LOOP_EFFECT_ADDR, struct.pack('<I', loop_effect))

        stubs.log.clear()
        for lst in (native_progress, native_level, native_effect, native_refresh):
            lst.clear()
        original.call(0x43b9c0, eax=PLAYER, edx=reward & 0xffffffff)
        orig_player = bytes(cpu.mem_read(PLAYER, SIZE))
        orig_log = list(stubs.log)

        host_player = (c.c_uint8 * SIZE).from_buffer_copy(bytes(player))
        got = native.vertrix_player_match_reward(host_player, SIZE, PLAYER, reward, loop_effect,
                                                 progress, level, effect, refresh, None)
        assert got == 1, f"case {case} native returned {got}"
        assert bytes(host_player) == orig_player, f"case {case} player mismatch"

        def calls(addr):
            return [(e[1], e[2]) for e in orig_log if e[0] == addr]

        assert calls(0x43b720) == native_progress, f"case {case} progress mismatch"
        assert calls(0x43b800) == native_level, f"case {case} level mismatch"
        assert calls(0x43c0e0) == native_effect, f"case {case} effect mismatch"
        assert [e[1] for e in orig_log if e[0] == 0x4726d0] == native_refresh, \
            f"case {case} refresh mismatch"
        verified += 1

    tiny = (c.c_uint8 * 0x100)()
    assert native.vertrix_player_match_reward(tiny, 0x100, PLAYER, 2, 0, progress, level,
                                              effect, refresh, None) == 0

    print(f"Verified {verified} cases successfully across 0x43b9c0.")
    out = {
        "routine": "0x43b9c0",
        "cases": verified,
        "complete_original_executions": verified,
        "whole_object_compared": True,
        "call_logs_compared": True,
        "short_storage_preserved": True
    }
    Path("docs/player-reward-verification.json").write_text(json.dumps(out, indent=2))


if __name__ == '__main__':
    main()
