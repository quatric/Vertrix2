"""Compare original 0x43ad50 with native piece-progress reset."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random

from original import Original
from oracle_kit import build

SIZE = 0x1000
PLAYER = 0x807000
PIECE = 0x809000
TARGET = 0x450
PROGRESS = 0x178


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()

    native = build(args.build_dir, 'player-piece-progress',
                   ['player_slots.c', 'piece.c', 'piece_children.c', 'actor_storage.c',
                    'actor_fields.c', 'object_scalars.c', 'timing.c', 'random.c'])
    Resolve = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p),
                         c.POINTER(c.c_size_t), c.c_void_p)
    native.vertrix_player_reset_piece_progress.argtypes = [c.c_void_p, c.c_size_t, Resolve,
                                                           c.c_void_p]
    native.vertrix_player_reset_piece_progress.restype = c.c_int

    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43ad50)
    host_piece = c.create_string_buffer(SIZE)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == PIECE:
            storage[0] = c.cast(host_piece, c.c_void_p)
            size[0] = SIZE
            return 1
        return 0

    verified = 0
    for case in range(args.cases):
        player = bytearray(rng.randbytes(SIZE))
        piece = bytearray(rng.randbytes(SIZE))
        import struct
        struct.pack_into('<I', player, TARGET, PIECE)
        cpu.mem_write(PLAYER, bytes(player))
        cpu.mem_write(PIECE, bytes(piece))
        host_piece.raw = bytes(piece)

        original.call(0x43ad50, eax=PLAYER)
        orig_piece = bytes(cpu.mem_read(PIECE, SIZE))
        orig_player = bytes(cpu.mem_read(PLAYER, SIZE))

        host_player = (c.c_uint8 * SIZE).from_buffer_copy(bytes(player))
        got = native.vertrix_player_reset_piece_progress(host_player, SIZE, resolve, None)
        assert got == 1, f"case {case} native returned {got}"
        assert bytes(host_player) == orig_player, f"case {case} player touched"
        assert bytes(host_piece.raw) == orig_piece, f"case {case} piece mismatch"
        assert struct.unpack('<I', orig_piece[PROGRESS:PROGRESS + 4])[0] == 1, \
            f"case {case} progress != 1"
        verified += 1

    tiny = (c.c_uint8 * 0x100)()
    assert native.vertrix_player_reset_piece_progress(tiny, 0x100, resolve, None) == 0
    big = (c.c_uint8 * SIZE).from_buffer_copy(bytes(bytearray(SIZE)))
    import struct as st
    st.pack_into('<I', big, TARGET, 0xdead000)
    assert native.vertrix_player_reset_piece_progress(big, SIZE, resolve, None) == 0

    print(f"Verified {verified} cases successfully across 0x43ad50.")
    out = {
        "routine": "0x43ad50",
        "cases": verified,
        "complete_original_executions": verified,
        "whole_object_compared": True,
        "short_storage_preserved": True
    }
    Path("docs/player-piece-progress-verification.json").write_text(json.dumps(out, indent=2))


if __name__ == '__main__':
    main()
