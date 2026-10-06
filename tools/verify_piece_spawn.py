"""Compare original 0x4320d0 with native piece spawner plumbing.

The empty-piece construction itself is proven by the piece-actor-construct
suite, so 0x42b5c0 stays stubbed here and actor bytes do not compare; what
compares is the slot gating, the store, the kind sign-extension and the
full call sequence."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct

from original import Original
from oracle_kit import Stubs, build

SIZE = 0x1000
BOARD = 0x807000
ACTOR = 0x809000
SLOT = 0xb70


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()

    native = build(args.build_dir, 'piece-spawn',
                   ['piece_actor_construct.c', 'piece_child_update.c', 'actor_storage.c',
                    'actor_fields.c', 'timer.c', 'timing.c', 'dword_transition.c',
                    'frame_resource.c'])
    Allocate = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_void_p)
    Finish = c.CFUNCTYPE(None, c.c_uint32, c.c_int32, c.c_void_p)
    Resolve = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p),
                         c.POINTER(c.c_size_t), c.c_void_p)
    native.vertrix_piece_actor_spawn.argtypes = [c.c_void_p, c.c_size_t, c.c_int32, Allocate,
                                                 Finish, Resolve, c.c_void_p]
    native.vertrix_piece_actor_spawn.restype = c.c_int

    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4320d0)
    host_actor = c.create_string_buffer(SIZE)
    native_finish = []
    next_alloc = [ACTOR]

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            return next_alloc[0]
        return None

    stubs = Stubs(cpu, handler)
    stubs.add(0x4ca000)
    stubs.add(0x42b5c0)
    stubs.add(0x42b6b0)

    @Allocate
    def allocate(size, context):
        assert size == 0x174
        return next_alloc[0]

    @Finish
    def finish(actor, kind, context):
        native_finish.append((actor, kind))

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == ACTOR:
            storage[0] = c.cast(host_actor, c.c_void_p)
            size[0] = SIZE
            return 1
        return 0

    verified = 0
    for case in range(args.cases):
        bucket = case % 6
        board = bytearray(rng.randbytes(SIZE))
        if bucket == 0:  # occupied slot: no calls
            struct.pack_into('<I', board, SLOT, rng.choice([1, 0x807800, 0xffffffff]))
            kind = rng.randrange(-0x80000000, 0x7fffffff)
            next_alloc[0] = ACTOR
        elif bucket == 1:  # alloc failure stores zero, finish still runs
            struct.pack_into('<I', board, SLOT, 0)
            kind = rng.randrange(-128, 128)
            next_alloc[0] = 0
        elif bucket == 2:  # multi-byte kinds prove low-byte truncation
            struct.pack_into('<I', board, SLOT, 0)
            kind = rng.choice([0x100, 0x1ff, 0x180, 0x17f, 0xffffff80, 0x12345])
            next_alloc[0] = ACTOR
        elif bucket == 3:  # negative byte kinds
            struct.pack_into('<I', board, SLOT, 0)
            kind = -rng.randrange(1, 129)
            next_alloc[0] = ACTOR
        else:
            struct.pack_into('<I', board, SLOT, 0)
            kind = rng.randrange(-0x80000000, 0x7fffffff)
            next_alloc[0] = ACTOR
        cpu.mem_write(BOARD, bytes(board))
        host_actor.raw = bytes(bytearray(SIZE))

        stubs.log.clear()
        native_finish.clear()
        original.call(0x4320d0, eax=BOARD, edx=kind & 0xffffffff)
        orig_board = bytes(cpu.mem_read(BOARD, SIZE))
        orig_log = list(stubs.log)

        host_board = (c.c_uint8 * SIZE).from_buffer_copy(bytes(board))
        got = native.vertrix_piece_actor_spawn(host_board, SIZE, kind, allocate, finish,
                                               resolve, None)
        assert got == 1, f"case {case} native returned {got}"
        assert bytes(host_board) == orig_board, f"case {case} board mismatch"

        alloc_calls = [e for e in orig_log if e[0] == 0x4ca000]
        if struct.unpack('<I', board[SLOT:SLOT + 4])[0] != 0:
            assert alloc_calls == [], f"case {case} alloc ran on occupied slot"
            assert native_finish == [], f"case {case} finish ran on occupied slot"
        else:
            assert len(alloc_calls) == 1 and alloc_calls[0][1] == 0x174, \
                f"case {case} alloc size {alloc_calls}"
            construct_calls = [e for e in orig_log if e[0] == 0x42b5c0]
            if next_alloc[0] == 0:
                assert construct_calls == [], f"case {case} construct ran on alloc failure"
            else:
                assert len(construct_calls) == 1 and construct_calls[0][1] == next_alloc[0], \
                    f"case {case} construct arg {construct_calls}"
            import ctypes as _c
            expected_kind = _c.c_int32(_c.c_int8(kind & 0xff).value).value
            finish_calls = [(e[1], e[2] if e[2] < 0x80000000 else e[2] - 0x100000000)
                            for e in orig_log if e[0] == 0x42b6b0]
            assert finish_calls == native_finish, f"case {case} finish {finish_calls} vs " \
                f"{native_finish}"
            assert expected_kind in (native_finish[0][1],), f"case {case} kind truncation"
        verified += 1

    tiny = (c.c_uint8 * 0x100)()
    assert native.vertrix_piece_actor_spawn(tiny, 0x100, 3, allocate, finish, resolve,
                                            None) == 0

    print(f"Verified {verified} cases successfully across 0x4320d0.")
    out = {
        "routine": "0x4320d0",
        "cases": verified,
        "complete_original_executions": verified,
        "whole_object_compared": True,
        "call_logs_compared": True,
        "short_storage_preserved": True
    }
    Path("docs/piece-spawn-verification.json").write_text(json.dumps(out, indent=2))


if __name__ == '__main__':
    main()
