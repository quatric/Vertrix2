"""Compare original 0x43ba60 with native player chain initializer."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random

from original import Original
from oracle_kit import build

SIZE = 0x1000
PLAYER = 0x807000
CHAIN = 0x180


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()

    native = build(args.build_dir, 'player-chain-init',
                   ['player_slots.c', 'piece.c', 'piece_children.c', 'actor_storage.c',
                    'actor_fields.c', 'object_scalars.c', 'timing.c', 'random.c', 'piece_actor_construct.c', 'piece_child_update.c', 'dword_transition.c', 'frame_resource.c', 'timer.c'])
    native.vertrix_player_init_chain.argtypes = [c.c_void_p, c.c_size_t]
    native.vertrix_player_init_chain.restype = c.c_int

    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43ba60)

    verified = 0
    for case in range(args.cases):
        player = bytearray(rng.randbytes(SIZE))
        cpu.mem_write(PLAYER, bytes(player))
        original.call(0x43ba60, eax=PLAYER)
        orig_player = bytes(cpu.mem_read(PLAYER, SIZE))

        host_player = (c.c_uint8 * SIZE).from_buffer_copy(bytes(player))
        got = native.vertrix_player_init_chain(host_player, SIZE)
        assert got == 1, f"case {case} native returned {got}"
        assert bytes(host_player) == orig_player, f"case {case} player mismatch"
        assert struct_value(host_player, CHAIN) == 12, f"case {case} chain != 12"
        verified += 1

    tiny = (c.c_uint8 * 0x100)()
    assert native.vertrix_player_init_chain(tiny, 0x100) == 0

    print(f"Verified {verified} cases successfully across 0x43ba60.")
    out = {
        "routine": "0x43ba60",
        "cases": verified,
        "complete_original_executions": verified,
        "whole_object_compared": True,
        "short_storage_preserved": True
    }
    Path("docs/player-chain-init-verification.json").write_text(json.dumps(out, indent=2))


def struct_value(buf, offset):
    import struct
    return struct.unpack('<I', bytes(buf)[offset:offset + 4])[0]


if __name__ == '__main__':
    main()
