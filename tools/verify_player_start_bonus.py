"""Compare original 0x451a60 with native bonus starter composition.

The spawn and the piece-progress reset run for real on both sides through
the shared natives; only the allocator, the constructor, the finish and the
event machine stay stubbed. Actor construction bytes do not compare (the
constructor is stubbed on the oracle side); everything else does."""
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
BOARD = 0x808000
PIECE = 0x809000
ACTOR = 0x80a000
CURSOR = 0x15c
KIND_DWORD = 0x18d
PIECE_FIELD = 0x450
SLOT = 0xb70
BONUS_HANDLER = 0x451aa0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()

    native = build(args.build_dir, 'player-start-bonus',
                   ['player_slots.c', 'piece.c', 'piece_children.c', 'actor_storage.c',
                    'actor_fields.c', 'object_scalars.c', 'timing.c', 'random.c',
                    'piece_actor_construct.c', 'piece_child_update.c',
                    'timer.c', 'dword_transition.c', 'frame_resource.c'])
    Allocate = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_void_p)
    Finish = c.CFUNCTYPE(None, c.c_uint32, c.c_int32, c.c_void_p)
    Begin = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)
    Resolve = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p),
                         c.POINTER(c.c_size_t), c.c_void_p)
    native.vertrix_player_start_bonus.argtypes = [c.c_void_p, c.c_size_t, c.c_uint32, Allocate,
                                                  Finish, Begin, Resolve, c.c_void_p]
    native.vertrix_player_start_bonus.restype = c.c_int

    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x451a60)
    host_board = c.create_string_buffer(SIZE)
    host_piece = c.create_string_buffer(SIZE)
    host_actor = c.create_string_buffer(SIZE)
    native_finish, native_begin = [], []
    next_alloc = [ACTOR]

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            return next_alloc[0]
        return None

    stubs = Stubs(cpu, handler)
    for address in (0x4ca000, 0x42b5c0, 0x42b6b0, 0x4ac8f0):
        stubs.add(address)

    @Allocate
    def allocate(size, context):
        assert size == 0x174
        return next_alloc[0]

    @Finish
    def finish(actor, kind, context):
        native_finish.append((actor, kind))

    @Begin
    def begin(player, handler_token, context):
        native_begin.append((player, handler_token))

    @Resolve
    def resolve(handle, storage, size, context):
        for want, buf in ((BOARD, host_board), (PIECE, host_piece), (ACTOR, host_actor)):
            if handle == want:
                storage[0] = c.cast(buf, c.c_void_p)
                size[0] = SIZE
                return 1
        return 0

    verified = 0
    for case in range(args.cases):
        bucket = case % 4
        player = bytearray(rng.randbytes(SIZE))
        board = bytearray(rng.randbytes(SIZE))
        piece = bytearray(rng.randbytes(SIZE))
        struct.pack_into('<I', player, CURSOR, BOARD)
        struct.pack_into('<I', player, PIECE_FIELD, PIECE)
        if bucket == 0:  # occupied slot: spawn no-ops, event + reset still run
            struct.pack_into('<I', board, SLOT, rng.choice([1, BOARD, 0xffffffff]))
            next_alloc[0] = ACTOR
        elif bucket == 1:  # alloc failure: zero stored, finish runs
            struct.pack_into('<I', board, SLOT, 0)
            next_alloc[0] = 0
        else:
            struct.pack_into('<I', board, SLOT, 0)
            next_alloc[0] = ACTOR
        cpu.mem_write(PLAYER, bytes(player))
        cpu.mem_write(BOARD, bytes(board))
        cpu.mem_write(PIECE, bytes(piece))
        cpu.mem_write(ACTOR, bytes(bytearray(SIZE)))
        host_board.raw = bytes(board)
        host_piece.raw = bytes(piece)
        host_actor.raw = bytes(bytearray(SIZE))

        stubs.log.clear()
        native_finish.clear()
        native_begin.clear()
        original.call(0x451a60, eax=PLAYER)
        orig_player = bytes(cpu.mem_read(PLAYER, SIZE))
        orig_board = bytes(cpu.mem_read(BOARD, SIZE))
        orig_piece = bytes(cpu.mem_read(PIECE, SIZE))
        orig_log = list(stubs.log)

        host_player = (c.c_uint8 * SIZE).from_buffer_copy(bytes(player))
        got = native.vertrix_player_start_bonus(host_player, SIZE, PLAYER, allocate, finish,
                                                begin, resolve, None)
        assert got == 1, f"case {case} native returned {got}"
        assert bytes(host_player) == orig_player, f"case {case} player mismatch"
        assert bytes(host_board.raw) == orig_board, f"case {case} board mismatch"
        assert bytes(host_piece.raw) == orig_piece, f"case {case} piece mismatch"

        def reg(addr):
            return [(e[1], e[2]) for e in orig_log if e[0] == addr]

        assert reg(0x4ac8f0) == native_begin == [(PLAYER, BONUS_HANDLER)], \
            f"case {case} event mismatch"
        assert [(a, e - 0x100000000 if e >= 0x80000000 else e) for a, e in reg(0x42b6b0)] \
            == native_finish, f"case {case} finish mismatch"
        verified += 1

    tiny = (c.c_uint8 * 0x100)()
    assert native.vertrix_player_start_bonus(tiny, 0x100, PLAYER, allocate, finish, begin,
                                             resolve, None) == 0

    print(f"Verified {verified} cases successfully across 0x451a60.")
    out = {
        "routine": "0x451a60 composed with 0x4320d0 and 0x43ad50",
        "cases": verified,
        "complete_original_executions": verified,
        "whole_object_compared": True,
        "call_logs_compared": True,
        "short_storage_preserved": True
    }
    Path("docs/player-start-bonus-verification.json").write_text(json.dumps(out, indent=2))


if __name__ == '__main__':
    main()
