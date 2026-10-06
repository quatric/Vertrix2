"""Compare original 0x451920 with the native post-lock twin composition.

The match scan, the event machine, the cursor method, the letter, the win
handler, the allocator and the refresh/notify/play leaves stay stubbed
(logged and replayed); everything else runs for real on both sides,
including arm_hold, the full reward->progress->level chain, reset_side,
conditional_reset, set/level/score natives and the sfx dispatch routing.
"""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x1000
VTABLE = 0x706000
METHOD = 0x707000
PLAYER = 0x807000
SUPPRESS = 0x44c
OPPONENT = 0x808000
CURSOR = 0x809000
OPPCUR = 0x80a000
PREVIEW = 0x80b000
OPPPREV = 0x80c000
SIDE = 0x80d000
ALTER_GLOBAL = 0x532bbc
DELAY_TABLE = 0x4f7d50
FRAME_TABLE = 0x4f7dc8
RNG_STATE = 0x598d30
MODE_FLAG = 0x532bc8
RACE_LIMIT = 0x532b34
LOSER_FLAG = 0x532a3c
PROG_EFFECT = 0x4f81b4
LOOP_EFFECT = 0x4f8190
MODE_EFFECT = 0x4f8194
FLAG_EFFECT = 0x4f81ac
ALT_EFFECT = 0x532d88
DIFFICULTY = 0x532bbc
TABLE_ADDR = 0x4f80cc


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next')]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


Match = c.CFUNCTYPE(c.c_int, U, c.c_uint8, c.POINTER(U), c.POINTER(U), c.POINTER(U),
                    c.POINTER(U), c.c_void_p)
CursorMethod = c.CFUNCTYPE(U, U, U, c.c_void_p)
Event = c.CFUNCTYPE(None, U, U, c.c_void_p)
SfxLog = c.CFUNCTYPE(None, U, U, c.c_void_p)
Letter = c.CFUNCTYPE(None, U, c.c_void_p)
Refresh = c.CFUNCTYPE(None, U, c.c_void_p)
LevelNotify = c.CFUNCTYPE(None, U, U, c.c_void_p)
SfxPlay = c.CFUNCTYPE(None, U, U, c.c_void_p)
Win = c.CFUNCTYPE(U, U, U, U, c.c_void_p)
SideAlloc = c.CFUNCTYPE(U, U, c.c_void_p)
SideDestroy = c.CFUNCTYPE(None, U, c.c_void_p)


class NativeRandom(c.Structure):
    _fields_ = [("samples", c.c_uint16 * 4097), ("position", c.c_uint16), ("seed", c.c_uint32),
                ("clock", c.c_void_p), ("clock_context", c.c_void_p)]


class ProgressGlobals(c.Structure):
    _fields_ = [("mode_flag", U), ("race_limit", U), ("loser_flag", U), ("effect", U)]


class PostTables(c.Structure):
    _fields_ = [("mode_effect", U), ("chain_effect", U), ("flag_effect", U), ("alt_effect", U),
                ("loop_effect", U), ("difficulty", U), ("mult_table", c.POINTER(U)),
                ("mult_count", c.c_size_t)]


class PostServices(c.Structure):
    _fields_ = [("match", Match), ("cursor", CursorMethod), ("event", Event), ("sfx", SfxLog),
                ("tables", PostTables), ("progress", c.POINTER(ProgressGlobals)),
                ("pletter", Letter), ("refresh", Refresh), ("level_notify", LevelNotify),
                ("sfx_play", SfxPlay), ("win", Win), ("side_alloc", SideAlloc),
                ("side_destroy", SideDestroy), ("random", c.POINTER(NativeRandom)),
                ("resolve", Resolve), ("context", c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'object-post-lock-twin',
              ['object_events.c', 'call_glue.c', 'actor_storage.c', 'player_slots.c',
               'player_actions.c', 'piece.c', 'piece_children.c', 'actor_fields.c',
               'object_scalars.c', 'timing.c', 'random.c', 'event_stack.c', 'board_cells.c',
               'sfx_dispatch.c', 'piece_actor_construct.c', 'piece_child_update.c', 'timer.c',
               'dword_transition.c', 'frame_resource.c'])
    P, V, S = c.POINTER(Calls), c.c_void_p, c.c_size_t
    n.vertrix_object_post_lock_twin.argtypes = [P, c.POINTER(Services), U, V, S,
                                           c.POINTER(PostServices)]
    n.vertrix_object_post_lock_twin.restype = U
    n.vertrix_random_seed.argtypes = [c.POINTER(NativeRandom), U]
    n.vertrix_player_set_b08.argtypes = [c.c_void_p, c.c_size_t, c.c_uint8]
    n.vertrix_player_set_b08.restype = c.c_int
    n.vertrix_player_push_event.argtypes = [c.c_void_p, c.c_size_t, Resolve, c.c_void_p]
    n.vertrix_player_push_event.restype = c.c_int
    n.vertrix_player_level_side.argtypes = [Resolve, c.c_void_p, U, c.c_void_p, c.c_size_t, U,
                                            U, c.POINTER(U), c.POINTER(c.c_uint16)]
    n.vertrix_player_level_side.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x451920)
    live_table = struct.unpack('<8I', cpu.mem_read(TABLE_ADDR, 32))
    c_table = (U * 8)(*live_table)

    returns, native_log, replay = [], [], []
    log_match, log_cursor, log_event, log_sfx, log_letter = ([] for _ in range(5))
    log_refresh, log_notify, log_play, log_win = ([] for _ in range(4))
    match_script, win_values, alloc_replay = [], [], []
    host_map = {}

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x432480:
            # Stack args arrive last-push-first: stack[0] is &-0x20 (flag_b),
            # stack[1] is &-0x1c (flag_a); reward/mult come via ebx/edx.
            fa, fb, reward, mult, hit = match_script.pop(0)
            cpu.mem_write(stack[1], struct.pack('<I', fa))
            cpu.mem_write(stack[0], struct.pack('<I', fb))
            cpu.mem_write(ebx, struct.pack('<I', reward))
            cpu.mem_write(edx, struct.pack('<I', mult))
            return hit
        if address == 0x4ca000:
            return alloc_replay.pop(0)
        if address == 0x43ac00:
            return win_values.pop(0)
        if address in (0x4ac8f0, METHOD):
            returns.append(rng.getrandbits(32))
            return returns[-1]
        return None

    stubs = Stubs(cpu, handler)
    stubs.add(0x432480, 2)
    for address in (0x4ac8f0, METHOD, 0x4715a0, 0x43ac00, 0x4726d0, 0x4ca000,
                    0x43c0e0):
        stubs.add(address)

    @Call
    def call(site, context):
        s = site.contents
        if s.target == 0x4ac8f0:
            native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
            log_event.append((s.eax, s.edx))
            return replay.pop(0)
        if s.target == 0x43bae0:
            native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
            n.vertrix_player_set_b08(host_map[s.eax], SIZE, s.edx & 0xff)
            return s.eax
        if s.target == 0x43bb60:
            native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
            return n.vertrix_player_push_event(host_map[s.eax], SIZE, resolve, None)
        raise AssertionError(f"unexpected Calls target {s.target:#x}")

    @Match
    def match(cursor, side, fa, fb, reward, mult, context):
        script = match_script.pop(0)
        fa[0], fb[0], reward[0], mult[0] = script[:4]
        log_match.append((cursor, side, script[0], script[1], script[2], script[3], script[4]))
        return script[4]

    @CursorMethod
    def cursor_method(cursor, table, context):
        log_cursor.append((cursor, table))
        return replay.pop(0)

    @Event
    def event(player, handler_token, context):
        log_event.append((player, handler_token))
        replay.pop(0)

    @SfxLog
    def sfx(player, effect, context):
        log_sfx.append((player, effect))

    @Letter
    def pletter(mode, context):
        log_letter.append(mode)

    @Refresh
    def refresh(arg, context):
        log_refresh.append(arg)

    @LevelNotify
    def level_notify(child, level, context):
        host = host_map[child]
        alter = struct.unpack('<I', cpu.mem_read(ALTER_GLOBAL, 4))[0]
        delays = (U * 1024).from_buffer_copy(bytes(cpu.mem_read(DELAY_TABLE, 1024 * 4)))
        frames = (c.c_uint16 * 2048).from_buffer_copy(bytes(cpu.mem_read(FRAME_TABLE, 2048 * 2)))
        assert level + alter * 10 < 1024 and level * 2 + alter * 20 < 2048, (level, alter)
        result = n.vertrix_player_level_side(resolve, None, child, host, SIZE, level, alter,
                                             delays, frames)
        log_notify.append((child, level, result))
        return result

    @SfxPlay
    def play(effect, side, context):
        log_play.append((effect, side))

    @Win
    def win(player, ebx, ecx, context):
        value = win_values.pop(0)
        log_win.append((player, ebx, ecx, value))
        return value

    @SideAlloc
    def side_alloc(size, context):
        return alloc_replay.pop(0)

    @SideDestroy
    def side_destroy(side, context):
        log_destroy.append(side)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle in host_map:
            storage[0] = c.cast(host_map[handle], c.c_void_p)
            size[0] = len(bytes(host_map[handle]))
            return 1
        return 0

    log_destroy = []
    calls = Calls(call, None)
    services = Services(resolve, None, None, None, None)
    state = NativeRandom()
    totals = {'0x451920': 0}

    def rng_pos():
        return struct.unpack('<H', cpu.mem_read(RNG_STATE + 12, 2))[0]

    def mem(addr, size=SIZE):
        return bytes(cpu.mem_read(addr, size))

    for case in range(args.cases):
        seed = case
        original.piece_seed(seed)
        n.vertrix_random_seed(c.byref(state), seed)
        bucket = case % 8
        player = bytearray(rng.randbytes(SIZE))
        opponent = bytearray(rng.randbytes(SIZE))
        cursor = bytearray(rng.randbytes(SIZE))
        oppcur = bytearray(rng.randbytes(SIZE))
        preview = bytearray(rng.randbytes(SIZE))
        oppprev = bytearray(rng.randbytes(SIZE))
        struct.pack_into('<I', player, 0x15c, CURSOR)
        struct.pack_into('<I', player, 0x3b0, OPPONENT)
        struct.pack_into('<I', player, 0x3b4, PREVIEW)
        struct.pack_into('<I', player, 0x450, PREVIEW)
        struct.pack_into('<I', player, 0x4e8, 0)
        struct.pack_into('<I', opponent, 0x15c, OPPCUR)
        struct.pack_into('<I', opponent, 0x3b4, OPPPREV)
        struct.pack_into('<I', opponent, 0x3b0, PLAYER)
        struct.pack_into('<I', opponent, 0x4e8, 0)
        struct.pack_into('<I', opponent, 0x450, OPPPREV)
        struct.pack_into('<I', cursor, 0x158, VTABLE)
        struct.pack_into('<I', oppcur, 0x158, VTABLE)
        struct.pack_into('<I', cursor, 0xa60, SIDE)
        side_block = bytearray(rng.randbytes(SIZE))
        if rng.random() < 0.3:
            struct.pack_into('<I', side_block, 0x168, 0)
        side = rng.randrange(256)
        player[0x4dc] = side
        if bucket == 0:  # no match, suppressed, opponent dead
            hit, fa, fb, reward, mult = 0, 0, 0, 0, 0
            struct.pack_into('<I', player, 0x44c, 1)
            opponent[0x4c5] = 0
        elif bucket == 1:  # no match, suppressed, armed hold path
            hit, fa, fb, reward, mult = 0, 0, 0, 0, 0
            struct.pack_into('<I', player, 0x44c, 1)
            opponent[0x4c5] = 1
            struct.pack_into('<I', player, 0x188, rng.choice([0, 5]))
        elif bucket == 2:  # no match, bonus ready
            hit, fa, fb, reward, mult = 0, 0, 0, 0, 0
            struct.pack_into('<I', player, 0x44c, 0)
            struct.pack_into('<I', player, 0x18c, 3)
        elif bucket == 3:  # no match, normal spawn
            hit, fa, fb, reward, mult = 0, 0, 0, 0, 0
            struct.pack_into('<I', player, 0x44c, 0)
            struct.pack_into('<I', player, 0x18c, rng.choice([0, 1, 2, 4]))
        elif bucket == 4:  # match, bonus mode, chain hits 3, flag_a set (fb ignored)
            hit, fa, fb = 7, 1, rng.randrange(2)
            reward, mult = rng.randrange(0, 10), rng.randrange(0, 10)
            struct.pack_into('<I', player, 0x4c8, 0x24)
            struct.pack_into('<I', player, 0x184, 2)
            struct.pack_into('<I', player, 0x44c, 0)
        elif bucket == 5:  # match, plain mode, chain hits 6 (no second effect), flag_a clear
            hit, fa, fb = 7, 0, rng.randrange(2)
            reward, mult = rng.randrange(0, 10), rng.randrange(0, 10)
            struct.pack_into('<I', player, 0x4c8, rng.choice([0, 1, 0x22, 0x30]))
            struct.pack_into('<I', player, 0x184, 5)
            struct.pack_into('<I', player, 0x44c, 0)
        elif bucket == 6:  # match, plain mode, no flags
            hit, fa, fb = 7, 0, 0
            reward, mult = rng.randrange(0, 10), rng.randrange(0, 10)
            struct.pack_into('<I', player, 0x4c8, rng.choice([0, 1, 0x22, 0x30]))
            struct.pack_into('<I', player, 0x184, rng.randrange(0, 10))
            struct.pack_into('<I', player, 0x44c, 0)
        else:  # random match path with group-A modes and race play
            hit = rng.choice([0, 5])
            fa, fb = rng.randrange(2), rng.randrange(2)
            reward, mult = rng.randrange(0, 20), rng.randrange(0, 20)
            struct.pack_into('<I', player, 0x4c8,
                             rng.choice([0x24, 0x25, 0x26, 0x27, 0, 1, 0x30]))
            struct.pack_into('<I', player, 0x184, rng.randrange(0, 8))
            struct.pack_into('<I', player, 0x44c, rng.choice([0, 0, 1]))
            struct.pack_into('<I', player, 0x18c, rng.randrange(0, 5))
        struct.pack_into('<I', player, 0x178, rng.randrange(0, 20))
        struct.pack_into('<I', player, 0x17c, rng.randrange(0, 10))
        struct.pack_into('<I', player, 0x174, rng.randrange(0, 1000))
        struct.pack_into('<I', player, 0x188, rng.randrange(0, 10))
        struct.pack_into('<I', player, 0x180, rng.randrange(0, 30))
        struct.pack_into('<I', opponent, 0x178, rng.randrange(0, 20))
        mode_flag = rng.choice([0, 1])
        race_limit = rng.randrange(5, 25)
        loser = rng.getrandbits(32)
        loop_effect = rng.getrandbits(32)
        mode_effect = rng.getrandbits(32)
        chain_effect = rng.getrandbits(32)
        flag_effect = rng.getrandbits(32)
        alt_effect = rng.getrandbits(32)
        difficulty = rng.randrange(0, 8)
        for addr, data in ((PLAYER, player), (OPPONENT, opponent), (CURSOR, cursor),
                           (OPPCUR, oppcur), (PREVIEW, preview), (OPPPREV, oppprev),
                           (SIDE, side_block)):
            cpu.mem_write(addr, bytes(data))
        cpu.mem_write(VTABLE + 4, struct.pack('<I', METHOD))
        cpu.mem_write(MODE_FLAG, struct.pack('<I', mode_flag))
        cpu.mem_write(RACE_LIMIT, struct.pack('<I', race_limit))
        cpu.mem_write(LOSER_FLAG, struct.pack('<I', loser))
        cpu.mem_write(PROG_EFFECT, struct.pack('<I', chain_effect))
        cpu.mem_write(LOOP_EFFECT, struct.pack('<I', loop_effect))
        cpu.mem_write(MODE_EFFECT, struct.pack('<I', mode_effect))
        cpu.mem_write(FLAG_EFFECT, struct.pack('<I', flag_effect))
        cpu.mem_write(ALT_EFFECT, struct.pack('<I', alt_effect))
        cpu.mem_write(DIFFICULTY, struct.pack('<I', difficulty))

        match_script.clear()
        match_script.append((fa, fb, reward, mult, hit))
        win_seed = [rng.getrandbits(32) for _ in range(64)]
        win_values.clear()
        win_values.extend(win_seed)
        alloc_replay.clear()
        stubs.log.clear()
        returns.clear()
        replay.clear()
        for lst in (native_log, log_match, log_cursor, log_event, log_sfx, log_letter,
                    log_refresh, log_notify, log_play, log_win, log_destroy):
            lst.clear()
        snap = {a: mem(a) for a in (PLAYER, OPPONENT, CURSOR, OPPCUR, PREVIEW, OPPPREV, SIDE)}
        result = original.call(0x451920, eax=PLAYER) & 0xffffffff
        orig = {a: mem(a) for a in (PLAYER, OPPONENT, CURSOR, OPPCUR, PREVIEW, OPPPREV,
                                                SIDE)}
        orig_loser = struct.unpack('<I', mem(LOSER_FLAG, 4))[0]
        orig_rng = rng_pos()
        orig_log = list(stubs.log)

        host_map.clear()
        host_map[PLAYER] = (c.c_uint8 * SIZE).from_buffer_copy(snap[PLAYER])
        host_map[OPPONENT] = (c.c_uint8 * SIZE).from_buffer_copy(snap[OPPONENT])
        host_map[CURSOR] = (c.c_uint8 * SIZE).from_buffer_copy(snap[CURSOR])
        host_map[OPPCUR] = (c.c_uint8 * SIZE).from_buffer_copy(snap[OPPCUR])
        host_map[PREVIEW] = (c.c_uint8 * SIZE).from_buffer_copy(snap[PREVIEW])
        host_map[OPPPREV] = (c.c_uint8 * SIZE).from_buffer_copy(snap[OPPPREV])
        host_map[SIDE] = (c.c_uint8 * SIZE).from_buffer_copy(snap[SIDE])
        globs = ProgressGlobals(mode_flag, race_limit, loser, chain_effect)
        tables = PostTables(mode_effect, chain_effect, flag_effect, alt_effect, loop_effect,
                            difficulty, c_table, 8)
        post = PostServices(match, cursor_method, event, sfx, tables, c.pointer(globs), pletter,
                            refresh, level_notify, play, win, side_alloc, side_destroy,
                            c.pointer(state), resolve, None)
        match_script.clear()
        match_script.append((fa, fb, reward, mult, hit))
        win_values.clear()
        win_values.extend(win_seed)
        replay[:] = list(returns)
        got = n.vertrix_object_post_lock_twin(c.byref(calls), c.byref(services), PLAYER,
                                         host_map[PLAYER], SIZE, c.byref(post))
        assert got == result, (case, hex(got), hex(result))
        for a in (PLAYER, OPPONENT, CURSOR, OPPCUR, PREVIEW, OPPPREV, SIDE):
            assert bytes(host_map[a]) == orig[a], (case, hex(a))
        assert globs.loser_flag == orig_loser, (case,)
        assert state.position == orig_rng, (case,)

        def reg(addr):
            return [(e[1], e[2]) for e in orig_log if e[0] == addr]

        assert reg(0x4ac8f0) == log_event, (case, 'event')
        exp_arm = [(e[1], e[2], e[3], e[4]) for e in orig_log if e[0] == 0x4ac8f0]
        got_arm = [(a, b, c, d) for t, a, b, c, d in native_log if t == 0x4ac8f0]
        if hit == 0 and struct.unpack('<I', player[SUPPRESS:SUPPRESS + 4])[0] == 1:
            assert got_arm == exp_arm, (case, 'arm-event', got_arm, exp_arm)
        else:
            assert got_arm == [], (case, 'unexpected-calls-event', got_arm)
        assert [e[1] for e in orig_log if e[0] == METHOD] == [p for p, _ in log_cursor], \
            (case, 'cursor')
        assert [e[1] for e in orig_log if e[0] == 0x4715a0] == log_letter, (case, 'letter')
        assert [e[1] for e in orig_log if e[0] == 0x4726d0] == log_refresh, (case, 'refresh')
        assert all(p == CURSOR for p, _, _ in log_notify), (case, 'notify handles')
        assert all(r in (CURSOR, SIDE) for _, _, r in log_notify), (case, 'notify results')
        assert reg(0x43c0e0) == log_sfx, (case, 'sfx')
        assert [e[1] for e in orig_log if e[0] == 0x43ac00] == [p for p, _, _, _ in log_win], \
            (case, 'win')
        totals['0x451920'] += 1

    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': '0x451920 executes completely in the original with the match scan, the '
                       'event machine, the cursor method, the letter, the win handler, the '
                       'allocator, the refresh leaves and the sfx dispatch stubbed and '
                       'logged (win values replayed) and the level-side handler 0x431400 '
                       'executing for real with the side object compared; return value, '
                       'every call log, all seven objects, the loser flag and the RNG '
                       'position compare.'}
    Path("docs/object-post-lock-twin-verification.json").write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
