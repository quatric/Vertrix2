"""Compare original 0x43b800 with native player level-bump composition."""
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
LEVEL = 0x17c
CURSOR = 0x15c


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()

    native = build(args.build_dir, 'player-bump',
                   ['player_slots.c', 'piece.c', 'piece_children.c', 'actor_storage.c',
                    'actor_fields.c', 'object_scalars.c', 'timing.c', 'random.c', 'piece_actor_construct.c', 'piece_child_update.c', 'dword_transition.c', 'frame_resource.c', 'timer.c'])
    Notify = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)
    native.vertrix_player_bump_level.argtypes = [c.c_void_p, c.c_size_t, c.c_int32, Notify,
                                                 c.c_void_p]
    native.vertrix_player_bump_level.restype = c.c_int

    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43b800)
    native_notify = []

    stubs = Stubs(cpu, lambda address, eax, edx, ebx, ecx, stack: None)
    stubs.add(0x431400)

    @Notify
    def notify(child, level, context):
        native_notify.append((child, level))

    verified = 0
    for case in range(args.cases):
        bucket = case % 8
        player = bytearray(rng.randbytes(SIZE))
        if bucket == 0:  # +1 like the reward loop
            struct.pack_into('<I', player, LEVEL, rng.randrange(0, 9))
            delta = 1
        elif bucket == 1:  # clamp to 9
            struct.pack_into('<I', player, LEVEL, rng.randrange(0, 10))
            delta = rng.randrange(5, 100)
        elif bucket == 2:  # clamp to 0
            struct.pack_into('<I', player, LEVEL, rng.randrange(0, 5))
            delta = -rng.randrange(5, 100)
        elif bucket == 3:  # unchanged
            struct.pack_into('<I', player, LEVEL, rng.randrange(0, 10))
            delta = 0
        elif bucket == 4:  # wrap: huge level + delta
            struct.pack_into('<I', player, LEVEL, rng.getrandbits(32))
            delta = rng.randrange(-10, 10)
        elif bucket == 5:  # negative delta, stays in range
            struct.pack_into('<I', player, LEVEL, rng.randrange(2, 10))
            delta = -1
        else:
            struct.pack_into('<I', player, LEVEL, rng.getrandbits(32))
            delta = rng.randrange(-100, 100)
        struct.pack_into('<I', player, CURSOR, rng.getrandbits(32))
        cpu.mem_write(PLAYER, bytes(player))

        stubs.log.clear()
        native_notify.clear()
        orig_ret = original.call(0x43b800, eax=PLAYER, edx=delta & 0xffffffff)
        orig_player = bytes(cpu.mem_read(PLAYER, SIZE))
        orig_notify = [(e[1], e[2]) for e in stubs.log if e[0] == 0x431400]

        host_player = (c.c_uint8 * SIZE).from_buffer_copy(bytes(player))
        got = native.vertrix_player_bump_level(host_player, SIZE, delta, notify, None)
        assert got == orig_ret, f"case {case} return {got} vs {orig_ret:#x}"
        assert bytes(host_player) == orig_player, f"case {case} player mismatch"
        assert native_notify == orig_notify, f"case {case} notify mismatch"
        verified += 1

    tiny = (c.c_uint8 * 0x100)()
    assert native.vertrix_player_bump_level(tiny, 0x100, 1, notify, None) == -1

    print(f"Verified {verified} cases successfully across 0x43b800.")
    out = {
        "routine": "0x43b800",
        "cases": verified,
        "complete_original_executions": verified,
        "whole_object_compared": True,
        "notify_log_compared": True,
        "short_storage_preserved": True
    }
    Path("docs/player-bump-verification.json").write_text(json.dumps(out, indent=2))


if __name__ == '__main__':
    main()
