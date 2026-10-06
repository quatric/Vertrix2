"""Compare original 0x43ba70 with native player bonus-ready recovery."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random

from original import Original
from oracle_kit import build

SIZE = 0x1000
PLAYER = 0x807000
FIELD = 0x18c


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()

    native = build(args.build_dir, 'player-bonus',
                   ['player_slots.c', 'piece.c', 'piece_children.c', 'actor_storage.c',
                    'actor_fields.c', 'object_scalars.c', 'timing.c', 'random.c'])
    native.vertrix_player_bonus_ready.argtypes = [c.c_void_p, c.c_size_t]
    native.vertrix_player_bonus_ready.restype = c.c_int

    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43ba70)
    verified = 0
    for case in range(args.cases):
        player = bytearray(rng.randbytes(SIZE))
        # Bias some cases to the ready value 3.
        if case % 4 == 0:
            player[FIELD] = 3
            player[FIELD + 1] = 0
            player[FIELD + 2] = 0
            player[FIELD + 3] = 0
        cpu.mem_write(PLAYER, bytes(player))
        expected = 1 if int.from_bytes(player[FIELD:FIELD + 4], 'little') == 3 else 0
        orig = original.call(0x43ba70, eax=PLAYER)
        buf = (c.c_uint8 * SIZE).from_buffer_copy(bytes(player))
        got = native.vertrix_player_bonus_ready(buf, SIZE)
        assert orig == expected, f"case {case} oracle mismatch"
        assert got == expected, f"case {case} native mismatch"
        verified += 1

    short_buf = (c.c_uint8 * 0x100)()
    assert native.vertrix_player_bonus_ready(short_buf, 0x100) == -1

    print(f"Verified {verified} cases successfully across 0x43ba70.")
    out = {
        "routine": "0x43ba70",
        "cases": verified,
        "complete_original_executions": verified,
        "whole_object_compared": True,
        "short_storage_preserved": True
    }
    Path("docs/player-bonus-verification.json").write_text(json.dumps(out, indent=2))


if __name__ == '__main__':
    main()
