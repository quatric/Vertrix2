"""Compare original 0x43b980/ce00/b930/ce30 (player side lifecycle) with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path

from original import Original
from oracle_kit import Stubs, build

U = c.c_uint32
SIZE = 0x1000
SIDE_SIZE = 0x15c
#The oracle RNG sample buffer lives at 0x804000..0x806002. All test objects
#stay clear of it; 0x807000 + is safe within the mapped region.
PLAYER = 0x807000
PREVIEW = 0x809000
SIDES = 0x80b000
SIDE_STRIDE = 0x200
OPPONENT = 0x80c000
OPP_PREVIEW = 0x80d000
RNG_STATE = 0x598d30
DIFFICULTY = 0x532bbc
STEPS_TABLE = 0x4f9c14
MODE = 0x4c8
SIDE = 0x4e8
RESOURCE = 0x158
METHOD = 0x707000


class NativeRandom(c.Structure):
    _fields_ = [
        ("samples", c.c_uint16 * 4097),
        ("position", c.c_uint16),
        ("seed", c.c_uint32),
        ("clock", c.c_void_p),
        ("clock_context", c.c_void_p),
    ]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'player-side',
              ['player_slots.c', 'piece.c', 'piece_children.c', 'actor_storage.c', 'actor_fields.c',
               'object_scalars.c', 'timing.c', 'random.c', 'object_glue.c', 'call_glue.c',
               'table_queries.c', 'engine_helpers.c', 'piece_actor_construct.c',
               'block_factory.c', 'board_cells.c', 'particle_spawn.c', 'actor_chain_visit.c',
               'piece_child_update.c', 'timer.c', 'dword_transition.c', 'frame_resource.c'])
    Allocate = c.CFUNCTYPE(U, U, c.c_void_p)
    Destroy = c.CFUNCTYPE(None, U, c.c_void_p)
    Refresh = c.CFUNCTYPE(None, U, c.c_void_p)
    Resolve = c.CFUNCTYPE(c.c_int, U, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t), c.c_void_p)
    n.vertrix_player_release_side.argtypes = [c.c_void_p, c.c_size_t, U, c.POINTER(NativeRandom),
                                              Destroy, Refresh, Resolve, c.c_void_p]
    n.vertrix_player_reset_side.argtypes = [c.c_void_p, c.c_size_t, U, c.POINTER(NativeRandom),
                                            Destroy, Refresh, Resolve, c.c_void_p]
    n.vertrix_player_alloc_side.argtypes = [c.c_void_p, c.c_size_t, U, U, c.POINTER(NativeRandom),
                                            Allocate, Destroy, Refresh, Resolve, c.c_void_p]
    n.vertrix_player_setup_side.argtypes = [c.c_void_p, c.c_size_t, U, U, c.POINTER(NativeRandom),
                                            Allocate, Destroy, Refresh, Resolve, c.c_void_p]
    n.vertrix_player_conditional_reset.argtypes = [c.c_void_p, c.c_size_t, U, c.c_uint8,
                                                   c.POINTER(NativeRandom), Destroy, Refresh,
                                                   Resolve, c.c_void_p]
    n.vertrix_player_clear_field_18c.argtypes = [c.c_void_p, c.c_size_t]
    n.vertrix_player_gated_reset.argtypes = [c.c_void_p, c.c_size_t, U, c.POINTER(NativeRandom),
                                             Destroy, Refresh, Resolve, c.c_void_p]
    n.vertrix_player_setup_side_2b.argtypes = [c.c_void_p, c.c_size_t, U, U,
                                               c.POINTER(NativeRandom), Allocate, Destroy, Refresh,
                                               Resolve, c.c_void_p]
    n.vertrix_player_setup_side_2c.argtypes = [c.c_void_p, c.c_size_t, U, U,
                                               c.POINTER(NativeRandom), Allocate, Destroy, Refresh,
                                               Resolve, c.c_void_p]
    n.vertrix_player_adopt_side.argtypes = [c.c_void_p, c.c_size_t, U, U, c.POINTER(NativeRandom),
                                            Destroy, Refresh, Resolve, c.c_void_p]
    n.vertrix_random_seed.argtypes = [c.POINTER(NativeRandom), c.c_uint32]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43b980)
    totals = {}
    seeds = [0, 0x12345678]
    sides_free = [SIDES + i * SIDE_STRIDE for i in range(8)]
    allocations, replay = [], []
    next_alloc = [0]
    native_destroy, native_refresh = [], []
    host_sides = {}
    host_preview = c.create_string_buffer(SIZE)
    host_opp_preview = c.create_string_buffer(SIZE)
    host_opp_box = {}

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            allocations.append(next_alloc[0])
            return next_alloc[0]
        return None

    stubs = Stubs(cpu, handler)
    stubs.add(0x4ca000)
    stubs.add(0x4726d0)
    stubs.add(METHOD)

    @Allocate
    def allocate(size, context):
        assert size == SIDE_SIZE
        return replay.pop(0)

    @Destroy
    def destroy(side, context):
        native_destroy.append((side, 2))

    @Refresh
    def refresh(handle, context):
        native_refresh.append(handle)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == PREVIEW or handle == OPP_PREVIEW:
            storage[0] = c.cast(host_preview if handle == PREVIEW else host_opp_preview,
                                c.c_void_p)
            size[0] = SIZE
            return 1
        if handle == OPPONENT and 'buf' in host_opp_box:
            storage[0] = c.cast(host_opp_box['buf'], c.c_void_p)
            size[0] = SIZE
            return 1
        if handle in host_sides:
            storage[0] = c.cast(host_sides[handle], c.c_void_p)
            size[0] = SIDE_STRIDE
            return 1
        return 0

    def refresh_events():
        return [e[1] for e in stubs.log if e[0] == 0x4726d0]

    def destroy_events():
        return [(e[1], e[2]) for e in stubs.log if e[0] == METHOD]

    def rng_pos():
        return struct.unpack('<H', cpu.mem_read(RNG_STATE + 12, 2))[0]

    def fresh_player(mode, side):
        player = bytearray(rng.getrandbits(8) for _ in range(SIZE))
        preview = bytearray(rng.getrandbits(8) for _ in range(SIZE))
        struct.pack_into('<I', player, MODE, mode)
        struct.pack_into('<I', player, SIDE, side)
        struct.pack_into('<I', player, 0x3b4, PREVIEW)
        cpu.mem_write(PLAYER, bytes(player))
        cpu.mem_write(PREVIEW, bytes(preview))
        return player, preview

    def fresh_side(side):
        data = bytearray(rng.getrandbits(8) for _ in range(SIDE_STRIDE))
        res = side + 0x100
        struct.pack_into('<I', data, RESOURCE, res)
        cpu.mem_write(side, bytes(data))
        cpu.mem_write(res, struct.pack('<I', METHOD))
        return bytes(data)

    def sync_hosts(player, preview):
        host_player = c.create_string_buffer(bytes(player), SIZE)
        host_preview.raw = bytes(preview)
        return host_player

    per_routine = (args.cases + 1) // 2
    for seed in seeds:
        state = NativeRandom()
        n.vertrix_random_seed(c.byref(state), seed)
        original.piece_seed(seed)
#clear_18c : single - store leaf with no return contract; state only.
        for _ in range(per_routine):
            player = bytearray(rng.getrandbits(8) for _ in range(SIZE))
            cpu.mem_write(PLAYER, bytes(player))
            original.call(0x43ba80, eax=PLAYER)
            host_player = c.create_string_buffer(bytes(player), SIZE)
            assert n.vertrix_player_clear_field_18c(host_player, SIZE) == 1
            assert bytes(cpu.mem_read(PLAYER, SIZE)) == host_player.raw, 'clear player'
            totals['0x43ba80'] = totals.get('0x43ba80', 0) + 1
#release_side : null path returns at once; present path destroys,
#clears and runs the full reset.The null - path return value is a
#native convention(the original leaves stale eax), so only state
#and event logs compare.
        for _ in range(per_routine):
            use_side = rng.random() < 0.5
            side = sides_free[rng.randrange(len(sides_free))] if use_side else 0
            if use_side:
                fresh_side(side)
            player, preview = fresh_player(rng.getrandbits(32), side)
            stubs.log.clear()
            native_destroy.clear()
            native_refresh.clear()
            original.call(0x43b980, eax=PLAYER)
            host_player = sync_hosts(player, preview)
            host_sides.clear()
            n.vertrix_player_release_side(host_player, SIZE, PLAYER, c.byref(state), destroy,
                                          refresh, resolve, None)
            assert bytes(cpu.mem_read(PLAYER, SIZE)) == host_player.raw, 'release player'
            assert bytes(cpu.mem_read(PREVIEW, SIZE)) == host_preview.raw, 'release preview'
            assert destroy_events() == native_destroy, 'release destroy'
            assert refresh_events() == native_refresh, 'release refresh'
            assert rng_pos() == state.position, 'release rng'
            totals['0x43b980'] = totals.get('0x43b980', 0) + 1
#reset_side : release, mode 0, reset - state mark, preview regen.
        for _ in range(per_routine):
            use_side = rng.random() < 0.5
            side = sides_free[rng.randrange(len(sides_free))] if use_side else 0
            if use_side:
                fresh_side(side)
            player, preview = fresh_player(rng.getrandbits(32), side)
            stubs.log.clear()
            native_destroy.clear()
            native_refresh.clear()
            original.call(0x43ce00, eax=PLAYER)
            host_player = sync_hosts(player, preview)
            host_sides.clear()
            assert n.vertrix_player_reset_side(host_player, SIZE, PLAYER, c.byref(state), destroy,
                                               refresh, resolve, None) == 1
            assert bytes(cpu.mem_read(PLAYER, SIZE)) == host_player.raw, 'reset player'
            assert bytes(cpu.mem_read(PREVIEW, SIZE)) == host_preview.raw, 'reset preview'
            assert destroy_events() == native_destroy, 'reset destroy'
            assert refresh_events() == native_refresh, 'reset refresh'
            assert rng_pos() == state.position, 'reset rng'
            totals['0x43ce00'] = totals.get('0x43ce00', 0) + 1
#alloc_side : reset as above, then allocate / construct / period - set the
#side.Steps arrive in edx and are supplied to the native version.
        for _ in range(per_routine):
            use_side = rng.random() < 0.5
            side = sides_free[rng.randrange(len(sides_free))] if use_side else 0
            if use_side:
                fresh_side(side)
            steps = rng.choice([0, 1, 5, rng.getrandbits(16)])
            player, preview = fresh_player(rng.getrandbits(32), side)
            new_side = rng.choice([h for h in sides_free if h != side])
            next_alloc[0] = new_side
            new_data = bytearray(rng.getrandbits(8) for _ in range(SIDE_STRIDE))
            cpu.mem_write(new_side, bytes(new_data))
            start = len(allocations)
            stubs.log.clear()
            native_destroy.clear()
            native_refresh.clear()
            original.call(0x43b930, eax=PLAYER, edx=steps)
            assert allocations[start:] == [new_side], allocations[start:]
            replay.extend(allocations[start:])
            host_player = sync_hosts(player, preview)
            host_sides.clear()
            host_sides[new_side] = c.create_string_buffer(bytes(new_data), SIDE_STRIDE)
            assert n.vertrix_player_alloc_side(host_player, SIZE, PLAYER, steps, c.byref(state),
                                               allocate, destroy, refresh, resolve,
                                               None) == 1
            assert not replay, 'alloc replay consumed'
            assert bytes(cpu.mem_read(PLAYER, SIZE)) == host_player.raw, 'alloc player'
            assert bytes(cpu.mem_read(PREVIEW, SIZE)) == host_preview.raw, 'alloc preview'
            assert bytes(cpu.mem_read(new_side, SIDE_STRIDE)) == host_sides[new_side].raw, \
                'alloc side'
            assert destroy_events() == native_destroy, 'alloc destroy'
            assert refresh_events() == native_refresh, 'alloc refresh'
            assert rng_pos() == state.position, 'alloc rng'
            totals['0x43b930'] = totals.get('0x43b930', 0) + 1
#setup_side : alloc as above, then reset - state mark, mode 0x30 and
#state 4. Steps come from the difficulty table and are read live.
        for _ in range(per_routine):
            use_side = rng.random() < 0.5
            side = sides_free[rng.randrange(len(sides_free))] if use_side else 0
            if use_side:
                fresh_side(side)
            difficulty = rng.choice([0, 1, 2])
            player, preview = fresh_player(rng.getrandbits(32), side)
            new_side = rng.choice([h for h in sides_free if h != side])
            next_alloc[0] = new_side
            new_data = bytearray(rng.getrandbits(8) for _ in range(SIDE_STRIDE))
            cpu.mem_write(new_side, bytes(new_data))
            cpu.mem_write(DIFFICULTY, struct.pack('<I', difficulty))
            steps = struct.unpack('<I', cpu.mem_read(STEPS_TABLE + difficulty * 4, 4))[0]
            start = len(allocations)
            stubs.log.clear()
            native_destroy.clear()
            native_refresh.clear()
            original.call(0x43ce30, eax=PLAYER)
            assert allocations[start:] == [new_side], allocations[start:]
            replay.extend(allocations[start:])
            host_player = sync_hosts(player, preview)
            host_sides.clear()
            host_sides[new_side] = c.create_string_buffer(bytes(new_data), SIDE_STRIDE)
            assert n.vertrix_player_setup_side(host_player, SIZE, PLAYER, steps, c.byref(state),
                                               allocate, destroy, refresh, resolve,
                                               None) == 1
            assert not replay, 'setup replay consumed'
            assert bytes(cpu.mem_read(PLAYER, SIZE)) == host_player.raw, 'setup player'
            assert bytes(cpu.mem_read(PREVIEW, SIZE)) == host_preview.raw, 'setup preview'
            assert bytes(cpu.mem_read(new_side, SIDE_STRIDE)) == host_sides[new_side].raw, \
                'setup side'
            assert destroy_events() == native_destroy, 'setup destroy'
            assert refresh_events() == native_refresh, 'setup refresh'
            assert rng_pos() == state.position, 'setup rng'
            totals['0x43ce30'] = totals.get('0x43ce30', 0) + 1
#gated_reset : group - A modes run the reset + refresh and return 1;
#anything else returns 0 with no effect.
        for _ in range(per_routine):
            in_group = rng.random() < 0.5
            mode = rng.choice([0x25, 0x26, 0x27]) if in_group else rng.choice(
                [0, 1, 0x22, 0x28, 0x30, rng.getrandbits(32)])
            use_side = rng.random() < 0.5
            side = sides_free[rng.randrange(len(sides_free))] if use_side else 0
            if use_side:
                fresh_side(side)
            player, preview = fresh_player(mode, side)
            stubs.log.clear()
            native_destroy.clear()
            native_refresh.clear()
            result = original.call(0x43cd30, eax=PLAYER)
            host_player = sync_hosts(player, preview)
            host_sides.clear()
            found = n.vertrix_player_gated_reset(host_player, SIZE, PLAYER, c.byref(state),
                                                 destroy, refresh, resolve, None)
            assert found == (result & 0xffffffff), (mode, result, found)
            assert bytes(cpu.mem_read(PLAYER, SIZE)) == host_player.raw, 'gated player'
            assert bytes(cpu.mem_read(PREVIEW, SIZE)) == host_preview.raw, 'gated preview'
            assert destroy_events() == native_destroy, 'gated destroy'
            assert refresh_events() == native_refresh, 'gated refresh'
            assert rng_pos() == state.position, 'gated rng'
            totals['0x43cd30'] = totals.get('0x43cd30', 0) + 1
#setup_2b / 2c : alloc shape with fixed modes 0x2b / 0x2c.
        for address, native, name in ((0x43cd60, n.vertrix_player_setup_side_2b, '0x43cd60'),
                                      (0x43cda0, n.vertrix_player_setup_side_2c, '0x43cda0')):
            for _ in range(per_routine):
                use_side = rng.random() < 0.5
                side = sides_free[rng.randrange(len(sides_free))] if use_side else 0
                if use_side:
                    fresh_side(side)
                difficulty = rng.choice([0, 1, 2])
                player, preview = fresh_player(rng.getrandbits(32), side)
                new_side = rng.choice([h for h in sides_free if h != side])
                next_alloc[0] = new_side
                new_data = bytearray(rng.getrandbits(8) for _ in range(SIDE_STRIDE))
                cpu.mem_write(new_side, bytes(new_data))
                cpu.mem_write(DIFFICULTY, struct.pack('<I', difficulty))
                steps = struct.unpack('<I', cpu.mem_read(STEPS_TABLE + difficulty * 4, 4))[0]
                start = len(allocations)
                stubs.log.clear()
                native_destroy.clear()
                native_refresh.clear()
                original.call(address, eax=PLAYER)
                assert allocations[start:] == [new_side], allocations[start:]
                replay.extend(allocations[start:])
                host_player = sync_hosts(player, preview)
                host_sides.clear()
                host_sides[new_side] = c.create_string_buffer(bytes(new_data), SIDE_STRIDE)
                assert native(host_player, SIZE, PLAYER, steps, c.byref(state), allocate,
                              destroy, refresh, resolve, None) == 1
                assert not replay, 'setup26 replay consumed'
                assert bytes(cpu.mem_read(PLAYER, SIZE)) == host_player.raw, 'setup26 player'
                assert bytes(cpu.mem_read(PREVIEW, SIZE)) == host_preview.raw, 'setup26 preview'
                assert bytes(cpu.mem_read(new_side, SIDE_STRIDE)) == host_sides[new_side].raw, \
                    'setup26 side'
                assert destroy_events() == native_destroy, 'setup26 destroy'
                assert refresh_events() == native_refresh, 'setup26 refresh'
                assert rng_pos() == state.position, 'setup26 rng'
                totals[name] = totals.get(name, 0) + 1
#adopt_side : release, store the value, mode = value + 0x25, marks,
#clears and a second refresh.Values are 0 or live side handles.
        for _ in range(per_routine):
            use_side = rng.random() < 0.5
            side = sides_free[rng.randrange(len(sides_free))] if use_side else 0
            if use_side:
                fresh_side(side)
            value = 0 if rng.random() < 0.5 else rng.choice(
                [h for h in sides_free if h != side])
            player, preview = fresh_player(rng.getrandbits(32), side)
            stubs.log.clear()
            native_destroy.clear()
            native_refresh.clear()
            original.call(0x43ccf0, eax=PLAYER, edx=value)
            host_player = sync_hosts(player, preview)
            host_sides.clear()
            assert n.vertrix_player_adopt_side(host_player, SIZE, PLAYER, value, c.byref(state),
                                               destroy, refresh, resolve, None) == 1
            assert bytes(cpu.mem_read(PLAYER, SIZE)) == host_player.raw, 'adopt player'
            assert bytes(cpu.mem_read(PREVIEW, SIZE)) == host_preview.raw, 'adopt preview'
            assert destroy_events() == native_destroy, 'adopt destroy'
            assert refresh_events() == native_refresh, 'adopt refresh'
            assert rng_pos() == state.position, 'adopt rng'
            totals['0x43ccf0'] = totals.get('0x43ccf0', 0) + 1
#conditional_reset : nonzero B01 refreshes only(return value is a
#native convention); zero B01 with group - A mode resets the opponent,
#then releases and resets the player with a trailing refresh.
        for _ in range(per_routine):
            b01 = rng.choice([0, 0, 1, 2, 255])
            in_group = rng.random() < 0.5
            mode = rng.choice([0x25, 0x26, 0x27]) if in_group else rng.choice(
                [0, 1, 0x22, 0x30, rng.getrandbits(32)])
            use_side = rng.random() < 0.5
            side = sides_free[rng.randrange(len(sides_free))] if use_side else 0
            if use_side:
                fresh_side(side)
            use_opp_side = rng.random() < 0.5
            pool = [h for h in sides_free if h != side]
            opp_side = rng.choice(pool) if use_opp_side else 0
            if use_opp_side:
                fresh_side(opp_side)
            player, preview = fresh_player(mode, side)
            opponent = bytearray(rng.getrandbits(8) for _ in range(SIZE))
            opp_preview = bytearray(rng.getrandbits(8) for _ in range(SIZE))
            struct.pack_into('<I', player, 0x3b0, OPPONENT)
            struct.pack_into('<I', opponent, SIDE, opp_side)
            struct.pack_into('<I', opponent, 0x3b4, OPP_PREVIEW)
            cpu.mem_write(PLAYER, bytes(player))
            cpu.mem_write(OPPONENT, bytes(opponent))
            cpu.mem_write(OPP_PREVIEW, bytes(opp_preview))
            stubs.log.clear()
            native_destroy.clear()
            native_refresh.clear()
            original.call(0x43bb00, eax=PLAYER, edx=b01)
            host_player = sync_hosts(player, preview)
            host_opponent = c.create_string_buffer(bytes(opponent), SIZE)
            host_opp_preview.raw = bytes(opp_preview)
            host_opp_box.clear()
            host_opp_box['buf'] = host_opponent
            host_sides.clear()
            n.vertrix_player_conditional_reset(host_player, SIZE, PLAYER, b01, c.byref(state),
                                               destroy, refresh, resolve, None)
            exp0 = bytes(cpu.mem_read(PLAYER, SIZE))
            diffs = [(hex(i), a, b) for i, (a, b) in enumerate(zip(exp0, host_player.raw))
                     if a != b][:8]
            assert exp0 == host_player.raw, \
                ('cond player', hex(b01), hex(mode), hex(side), hex(opp_side), diffs)
            assert bytes(cpu.mem_read(PREVIEW, SIZE)) == host_preview.raw, 'cond preview'
            assert bytes(cpu.mem_read(OPPONENT, SIZE)) == host_opponent.raw, 'cond opponent'
            assert bytes(cpu.mem_read(OPP_PREVIEW, SIZE)) == host_opp_preview.raw, 'cond oppprev'
            assert destroy_events() == native_destroy, 'cond destroy'
            assert refresh_events() == native_refresh, 'cond refresh'
            assert rng_pos() == state.position, \
                'cond rng' 
            totals['0x43bb00'] = \
                totals.get('0x43bb00', 0) + 1
    # Native-only guards: failing allocator and short storage never execute
    # against the original.
    @Allocate
    def fail_alloc(size, context):
        return 0

    host_player = c.create_string_buffer(SIZE)
    struct.pack_into('<I', host_player, SIDE, 0)
    struct.pack_into('<I', host_player, 0x3b4, PREVIEW)
    host_preview.raw = bytes(SIZE)
    assert not n.vertrix_player_alloc_side(
        host_player, SIZE, PLAYER, 0, c.byref(state), fail_alloc, destroy, refresh, resolve,
        None)
    tiny = c.create_string_buffer(b'\xaa' * 0x4e8, 0x4e8)
    assert not n.vertrix_player_release_side(tiny, 0x4e8, PLAYER, c.byref(state), destroy,
                                              refresh, resolve, None)
    assert tiny.raw == b'\xaa' * 0x4e8
    report = {
        'status': 'passed',
        'complete_original_executions': totals,
        'scope': 'Complete 43ba80, 43b980, 43ce00, 43b930, 43ce30, 43cd30, 43cd60, 43cda0, '
                 '43ccf0 and 43bb00 execute in the original (allocator, refresh and '
                 'destructor stubbed and logged); player, opponent, side, preview and RNG '
                 'position compare, plus native-only failure guards.'
    }
    (args.build_dir / 'player-side-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
