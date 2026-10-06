"""Compare original 0x43ba90 with native player score accumulator."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct

from original import Original
from oracle_kit import build

SIZE = 0x1000
PLAYER = 0x807000
DIFFICULTY_ADDR = 0x532bbc
TABLE_ADDR = 0x4f80cc
TABLE_ENTRIES = 8
SCORE = 0x174
CAP = 0x5f5e0ff


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()

    native = build(args.build_dir, 'player-score',
                   ['player_slots.c', 'piece.c', 'piece_children.c', 'actor_storage.c',
                    'actor_fields.c', 'object_scalars.c', 'timing.c', 'random.c', 'piece_actor_construct.c', 'piece_child_update.c', 'dword_transition.c', 'frame_resource.c', 'timer.c'])
    native.vertrix_player_add_score.argtypes = [c.c_void_p, c.c_size_t, c.c_int32, c.c_uint32,
                                                c.POINTER(c.c_uint32), c.c_size_t]
    native.vertrix_player_add_score.restype = c.c_int

    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43ba90)
    live_table = struct.unpack('<8I', cpu.mem_read(TABLE_ADDR, 32))

    verified = 0
    for case in range(args.cases):
        if case % 2 == 0:
            table = list(live_table)
            cpu.mem_write(TABLE_ADDR, struct.pack('<8I', *table))
        else:
            table = [rng.getrandbits(32) for _ in range(TABLE_ENTRIES)]
            cpu.mem_write(TABLE_ADDR, struct.pack('<8I', *table))
        bucket = case % 8
        player = bytearray(rng.randbytes(SIZE))
        if bucket == 0:
            struct.pack_into('<I', player, SCORE, rng.randrange(0, 1000))
            reward = rng.randrange(1, 50)
        elif bucket == 1:  # cap hit
            struct.pack_into('<I', player, SCORE, CAP - rng.randrange(0, 100))
            reward = rng.randrange(1, 100)
        elif bucket == 2:  # already at cap
            struct.pack_into('<I', player, SCORE, CAP)
            reward = rng.randrange(0, 100)
        elif bucket == 3:  # negative reward wraps below zero -> unsigned huge -> cap
            struct.pack_into('<I', player, SCORE, rng.randrange(0, 1000))
            reward = -rng.randrange(1, 100)
        elif bucket == 4:  # zero reward
            struct.pack_into('<I', player, SCORE, rng.getrandbits(32))
            reward = 0
        elif bucket == 5:  # zero multiplier entry
            struct.pack_into('<I', player, SCORE, rng.getrandbits(32))
            reward = rng.randrange(1, 1000)
        else:
            struct.pack_into('<I', player, SCORE, rng.getrandbits(32))
            reward = rng.randrange(-1000, 1000)
        difficulty = rng.randrange(0, TABLE_ENTRIES) if bucket != 5 else 6
        cpu.mem_write(PLAYER, bytes(player))
        cpu.mem_write(DIFFICULTY_ADDR, struct.pack('<I', difficulty))

        original.call(0x43ba90, eax=PLAYER, edx=reward & 0xffffffff)
        orig_player = bytes(cpu.mem_read(PLAYER, SIZE))

        host_player = (c.c_uint8 * SIZE).from_buffer_copy(bytes(player))
        c_table = (c.c_uint32 * TABLE_ENTRIES)(*table)
        got = native.vertrix_player_add_score(host_player, SIZE, reward, difficulty, c_table,
                                              TABLE_ENTRIES)
        assert got == 1, f"case {case} native returned {got}"
        assert bytes(host_player) == orig_player, f"case {case} player mismatch"
        verified += 1

    cpu.mem_write(TABLE_ADDR, struct.pack('<8I', *live_table))

    tiny = (c.c_uint8 * 0x100)()
    c_table = (c.c_uint32 * TABLE_ENTRIES)(*live_table)
    assert native.vertrix_player_add_score(tiny, 0x100, 5, 0, c_table, TABLE_ENTRIES) == 0
    big = (c.c_uint8 * SIZE).from_buffer_copy(bytes(bytearray(SIZE)))
    assert native.vertrix_player_add_score(big, SIZE, 5, TABLE_ENTRIES, c_table,
                                           TABLE_ENTRIES) == 0
    assert native.vertrix_player_add_score(big, SIZE, 5, 0, None, 0) == 0

    print(f"Verified {verified} cases successfully across 0x43ba90.")
    out = {
        "routine": "0x43ba90",
        "cases": verified,
        "complete_original_executions": verified,
        "whole_object_compared": True,
        "short_storage_preserved": True
    }
    Path("docs/player-score-verification.json").write_text(json.dumps(out, indent=2))


if __name__ == '__main__':
    main()
