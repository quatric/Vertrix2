"""Compare original 0x43b720 with native player progress-update recovery."""
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
WIN_EFFECT = 0x4f81b4
PROGRESS = 0x178
OPPONENT_FIELD = 0x3b0
ALIVE_FIELD = 0x4c5


class ProgressGlobals(c.Structure):
    _fields_ = [("mode_flag", c.c_uint32), ("race_limit", c.c_uint32),
                ("loser_flag", c.c_uint32), ("effect", c.c_uint32)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()

    native = build(args.build_dir, 'player-progress',
                   ['player_slots.c', 'piece.c', 'piece_children.c', 'actor_storage.c',
                    'actor_fields.c', 'object_scalars.c', 'timing.c', 'random.c',
                    'object_glue.c', 'call_glue.c', 'table_queries.c', 'engine_helpers.c',
                    'piece_actor_construct.c', 'block_factory.c', 'board_cells.c',
                    'particle_spawn.c', 'actor_chain_visit.c', 'piece_child_update.c',
                    'timer.c', 'dword_transition.c', 'frame_resource.c'])
    Reset = c.CFUNCTYPE(None, c.c_uint32, c.c_uint8, c.c_void_p)
    Letter = c.CFUNCTYPE(None, c.c_uint32, c.c_void_p)
    Effect = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)
    Win = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_uint32, c.c_uint32, c.c_void_p)
    Refresh = c.CFUNCTYPE(None, c.c_uint32, c.c_void_p)
    Resolve = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p),
                         c.POINTER(c.c_size_t), c.c_void_p)
    Read = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_uint, c.POINTER(c.c_uint32), c.c_void_p)
    U = c.c_uint32
    Allocate = c.CFUNCTYPE(U, U, c.c_void_p)

    class Site(c.Structure):
        _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack',
                                           'stack_next')]

    Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)

    class Calls(c.Structure):
        _fields_ = [('call', Call), ('context', c.c_void_p)]

    class Services(c.Structure):
        _fields_ = [('resolve', Resolve), ('allocate', Allocate), ('draw', c.c_void_p),
                    ('range', c.c_void_p), ('context', c.c_void_p)]
    native.vertrix_player_progress_update.argtypes = [
        c.c_void_p, c.c_size_t, c.c_uint32, c.c_int32, c.POINTER(ProgressGlobals),
        Reset, Letter, Effect, Win, Refresh, Resolve, c.c_void_p]
    native.vertrix_player_progress_update.restype = c.c_int
    P = c.POINTER(Calls)
    PU32 = c.POINTER(U)
    native.vertrix_object_chain_select.argtypes = [P, c.POINTER(Services), Read, c.c_void_p,
                                                   c.c_void_p, c.c_size_t, U, PU32, PU32, PU32,
                                                   U, U, U, U]
    native.vertrix_object_chain_select.restype = U

    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43b720)
    TARGET, VTABLE, METHOD = 0x808000, 0x808200, 0x707020
    GRID, COUNTS, DEFAULTS, GLOBAL_DEFAULT = 0x534c18, 0x534f10, 0x532ca4, 0x4f81cc
    native_reset, native_letter, native_effect, native_win, native_refresh = [], [], [], [], []
    native_calls, native_releases = [], []
    alloc_order = []
    buffers = {}
    host_opp = {}
    top = [0x810000]
    cpu.mem_map(0x810000, 0x10000)

    def take(size):
        handle = top[0]
        top[0] += (size + 0xf) & ~0xf
        buffers[handle] = c.create_string_buffer(size)
        cpu.mem_write(handle, bytes(size))
        buffers[handle].raw = bytes(size)
        return handle

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            assert eax == 0x10, hex(eax)
            handle = take(0x40)
            alloc_order.append(handle)
            return handle
        if address == 0x487870:
            return None
        if address == 0x4879f0:
            return 0
        if address == METHOD:
            return None
        return None

    stubs = Stubs(cpu, handler)
    for addr in (0x43bb00, 0x4715a0, 0x43c0e0, 0x4726d0, 0x4ca000, 0x487870, 0x4879f0):
        stubs.add(addr)
    stubs.add(METHOD)

    @Reset
    def reset(player, b01, context):
        native_reset.append((player, b01))

    @Letter
    def letter(mode, context):
        native_letter.append(mode)

    @Effect
    def effect(player, eff, context):
        native_effect.append((player, eff))

    @Win
    def win(player, ebx, ecx, context):
        host = host_opp[player]
        column = struct.unpack('<I', bytes(host[0x488:0x48c]))[0]
        state = struct.unpack('<I', bytes(host[0x474:0x478]))[0]
        grid = (U * 190).from_buffer_copy(bytes(cpu.mem_read(GRID, 19 * 10 * 4)))
        counts = (U * 19).from_buffer_copy(bytes(cpu.mem_read(COUNTS, 19 * 4)))
        defaults = (U * 19).from_buffer_copy(bytes(cpu.mem_read(DEFAULTS, 19 * 4)))
        default = struct.unpack('<I', cpu.mem_read(GLOBAL_DEFAULT, 4))[0]
        result = native.vertrix_object_chain_select(
            c.byref(calls), c.byref(services), read, None, host, SIZE, default, defaults,
            grid, counts, column, state, ebx, ecx)
        native_win.append((player, result))
        return result

    @Refresh
    def refresh(arg, context):
        native_refresh.append(arg)

    @Allocate
    def allocate(size, context):
        assert size == 0x10, hex(size)
        return alloc_order.pop(0)

    @Call
    def call(site, context):
        s = site.contents
        if s.target == METHOD:
            native_calls.append((s.eax, s.edx, s.ebx, s.ecx))
            return method_returns.pop(0)
        if s.target == 0x4d88a0:
            native_releases.append((s.eax, s.edx, s.ebx, s.ecx))
            return 0
        raise AssertionError(hex(s.target))

    @Read
    def read(address, width, value, context):
        value[0] = int.from_bytes(bytes(cpu.mem_read(address, width)), 'little')
        return 1

    @Resolve
    def resolve(handle, storage, size, context):
        if handle in host_opp:
            storage[0] = c.cast(host_opp[handle], c.c_void_p)
            size[0] = SIZE
            return 1
        buffer = buffers.get(handle)
        if buffer is None:
            return 0
        storage[0] = c.addressof(buffer)
        size[0] = len(buffer.raw)
        return 1

    calls = Calls(call, None)
    services = Services(resolve, allocate, None, None, None)
    method_returns = []

    def stub_calls(addr):
        return [(e[1], e[2]) for e in stubs.log if e[0] == addr]

    verified = 0
    for case in range(args.cases):
        top[0] = 0x810000
        bucket = case % 7
        player = bytearray(rng.randbytes(SIZE))
        opponent = bytearray(rng.randbytes(SIZE))
        if bucket == 0:  # floor to zero
            struct.pack_into('<i', player, PROGRESS, rng.randrange(0, 10))
            delta = -rng.randrange(10, 1000)
            flag, limit = 0, rng.getrandbits(32)
        elif bucket == 1:  # unchanged
            struct.pack_into('<I', player, PROGRESS, rng.getrandbits(32) & 0x7fffffff)
            delta = 0
            flag, limit = 0, rng.getrandbits(32)
        elif bucket == 2:  # normal increase, race off
            struct.pack_into('<I', player, PROGRESS, rng.randrange(0, 1000))
            delta = rng.randrange(1, 100)
            flag, limit = 0, rng.getrandbits(32)
        elif bucket == 3:  # race on, below limit
            struct.pack_into('<I', player, PROGRESS, 5)
            delta, flag, limit = 2, 1, 10
        elif bucket == 4:  # race win, opponent alive
            struct.pack_into('<I', player, PROGRESS, 8)
            delta, flag, limit = 5, 1, 10
            opponent[ALIVE_FIELD] = rng.choice([1, 2, 255])
        elif bucket == 5:  # race win, opponent dead
            struct.pack_into('<I', player, PROGRESS, 8)
            delta, flag, limit = 5, 1, 10
            opponent[ALIVE_FIELD] = 0
        else:  # random race flag
            struct.pack_into('<I', player, PROGRESS, rng.randrange(0, 20))
            delta = rng.randrange(-5, 15)
            flag = rng.choice([0, 1, 2])
            limit = rng.randrange(0, 25)
            opponent[ALIVE_FIELD] = rng.randrange(256)
        loser = rng.getrandbits(32)
        effect_id = rng.getrandbits(32)
        struct.pack_into('<I', player, OPPONENT_FIELD, OPPONENT)
        struct.pack_into('<I', player, 0x488, rng.randrange(19))
        struct.pack_into('<I', player, 0x468, TARGET)
        cpu.mem_write(PLAYER, bytes(player))
        cpu.mem_write(OPPONENT, bytes(opponent))
        cpu.mem_write(MODE_FLAG, struct.pack('<I', flag))
        cpu.mem_write(RACE_LIMIT, struct.pack('<I', limit))
        cpu.mem_write(LOSER_FLAG, struct.pack('<I', loser))
        cpu.mem_write(WIN_EFFECT, struct.pack('<I', effect_id))
        target_block = struct.pack('<II', VTABLE, rng.getrandbits(32)) + bytes(0x38)
        cpu.mem_write(TARGET, target_block)
        buffers[TARGET] = c.create_string_buffer(target_block, 0x40)
        vtable_block = bytes(0x18) + struct.pack('<I', METHOD) + bytes(0x8)
        cpu.mem_write(VTABLE, vtable_block)
        buffers[VTABLE] = c.create_string_buffer(vtable_block, 0x24)

        stubs.log.clear()
        native_reset.clear()
        native_letter.clear()
        native_effect.clear()
        native_win.clear()
        native_refresh.clear()
        native_calls.clear()
        native_releases.clear()
        method_returns.clear()
        method_returns.append(rng.getrandbits(32))

        orig_ret = original.call(0x43b720, eax=PLAYER, edx=delta & 0xffffffff)
        orig_player = bytes(cpu.mem_read(PLAYER, SIZE))
        orig_opp = bytes(cpu.mem_read(OPPONENT, SIZE))
        orig_loser = struct.unpack('<I', cpu.mem_read(LOSER_FLAG, 4))[0]
        orig_log = list(stubs.log)
        orig_target = bytes(cpu.mem_read(TARGET, 0x40))

        host_player = (c.c_uint8 * SIZE).from_buffer_copy(bytes(player))
        host_opp.clear()
        host_opp[OPPONENT] = (c.c_uint8 * SIZE).from_buffer_copy(bytes(opponent))
        host_opp[PLAYER] = host_player
        globs = ProgressGlobals(flag, limit, loser, effect_id)
        method_returns.clear()
        method_returns.append(TARGET)
        tables = list(alloc_order)
        got = native.vertrix_player_progress_update(host_player, SIZE, PLAYER, delta,
                                                    globs, reset, letter, effect,
                                                    win, refresh, resolve, None)

        # Return value: eax low byte? Original returns 0/1 in eax.
        assert got == (orig_ret & 0xffffffff) or got == orig_ret, \
            f"case {case} return mismatch {got} vs {orig_ret:#x}"
        assert bytes(host_player) == orig_player, f"case {case} player mismatch"
        assert bytes(host_opp[OPPONENT]) == orig_opp, f"case {case} opponent touched"
        assert globs.loser_flag == orig_loser, f"case {case} loser flag mismatch"
        assert globs.mode_flag == flag and globs.race_limit == limit, \
            f"case {case} input globals clobbered"
        # Call parity: reset(eax,edx-lo), letter(eax), effect(eax,edx), win(eax)->ret, refresh(eax)
        assert stub_calls(0x43bb00) == native_reset, f"case {case} reset {stub_calls(0x43bb00)} vs {native_reset}"
        assert [e[1] for e in orig_log if e[0] == 0x4715a0] == native_letter, \
            f"case {case} letter mismatch"
        assert stub_calls(0x43c0e0) == native_effect, f"case {case} effect mismatch"
        nwins = sum(1 for e in orig_log if e[0] == 0x4ca000)
        assert len(native_win) == nwins, f"case {case} win count mismatch"
        assert all(value == 0 for _, value in native_win), f"case {case} win value"
        assert [p for p, _ in native_win] == [PLAYER] * nwins, \
            f"case {case} win arg mismatch"
        assert [e[1:5] for e in orig_log if e[0] == METHOD] == native_calls, \
            f"case {case} slot6 mismatch"
        orig_releases = [(e[1], e[2]) for e in orig_log if e[0] == 0x4879f0]
        assert len(native_releases) == len(orig_releases), \
            f"case {case} release count {native_releases} vs {orig_releases}"
        for (robj, rfield, rtable, rone), (oobj, otable) in zip(native_releases, orig_releases):
            assert robj == oobj and rtable == otable and rone == 1, \
                f"case {case} release args {(robj, rtable)} vs {(oobj, otable)}"
        for handle in tables:
            assert buffers[handle].raw == bytes(cpu.mem_read(handle, 0x40)), \
                (case, hex(handle))
        assert buffers[TARGET].raw == bytes(cpu.mem_read(TARGET, 0x40)), \
            f"case {case} release target mismatch"
        assert [e[1] for e in orig_log if e[0] == 0x4726d0] == native_refresh, \
            f"case {case} refresh {[hex(e[1]) for e in orig_log if e[0]==0x4726d0]} vs {[hex(v) for v in native_refresh]}"
        verified += 1

    # Native-only guards: short storage and unresolvable opponent on the win path.
    tiny = (c.c_uint8 * 0x100)()
    tiny_globs = ProgressGlobals(1, 10, 0, 0)
    assert native.vertrix_player_progress_update(tiny, 0x100, PLAYER, 5, tiny_globs, reset,
                                                 letter, effect, win, refresh,
                                                 resolve, None) == -1
    big = (c.c_uint8 * SIZE).from_buffer_copy(bytes(bytearray(SIZE)))
    struct.pack_into('<I', big, PROGRESS, 8)
    struct.pack_into('<I', big, OPPONENT_FIELD, 0xdead000)
    win_globs = ProgressGlobals(1, 10, 0, 0)
    assert native.vertrix_player_progress_update(big, SIZE, PLAYER, 5, win_globs, reset, letter,
                                                 effect, win, refresh, resolve, None) == -1

    print(f"Verified {verified} cases successfully across 0x43b720.")
    out = {
        "routine": "0x43b720",
        "cases": verified,
        "complete_original_executions": verified,
        "whole_object_compared": True,
        "call_logs_compared": True,
        "short_storage_preserved": True,
        "scope": "Complete original 0x43b720 executions with the win handler 0x43ac00 "
                 "executing for real (chain-select with live grid/counts/defaults, slot-6 "
                 "dispatch, table allocation and release call all compared); the win return, "
                 "the table bytes, the release target and the slot-6/release call logs "
                 "compare alongside the progress return, objects, globals and boundary logs."
    }
    Path("docs/player-progress-verification.json").write_text(json.dumps(out, indent=2))


if __name__ == '__main__':
    main()
