"""Compare original mode-setup routines with the native recovery."""
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
RNG_STATE = 0x598d30
DIFFICULTY = 0x532bbc
T14 = 0x4f9c14
T20 = 0x4f9c20
T2C = 0x4f9c2c
T38 = 0x4f9c38
SIDE = 0x4e8
RESOURCE = 0x158
METHOD = 0x707000

MEMBERS = (
    (0x43cf30, 'vertrix_player_setup_side_23', T14),
    (0x43cf70, 'vertrix_player_setup_side_22', T14),
    (0x43cfb0, 'vertrix_player_setup_side_24', T14),
    (0x43cff0, 'vertrix_player_setup_side_28', T14),
    (0x43d030, 'vertrix_player_setup_side_29', T20),
    (0x43d070, 'vertrix_player_setup_side_2a', T2C),
    (0x43d0b0, 'vertrix_player_setup_side_2d', T14),
    (0x43d0f0, 'vertrix_player_setup_side_2e', T14),
    (0x43ceb0, 'vertrix_player_setup_side_2f', T14),
    (0x43cef0, 'vertrix_player_setup_side_31', T14),
)


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
    n = build(args.build_dir, 'player-modes',
              ['player_slots.c', 'piece.c', 'piece_children.c', 'actor_storage.c', 'actor_fields.c',
               'object_scalars.c', 'timing.c', 'random.c'])
    Allocate = c.CFUNCTYPE(U, U, c.c_void_p)
    Destroy = c.CFUNCTYPE(None, U, c.c_void_p)
    Refresh = c.CFUNCTYPE(None, U, c.c_void_p)
    Resolve = c.CFUNCTYPE(c.c_int, U, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t), c.c_void_p)
    natives = {}
    for _, name, _ in MEMBERS:
        getattr(n, name).argtypes = [c.c_void_p, c.c_size_t, U, U, c.POINTER(NativeRandom),
                                     Allocate, Destroy, Refresh, Resolve, c.c_void_p]
        natives[name] = getattr(n, name)
    n.vertrix_player_setup_indexed.argtypes = [c.c_void_p, c.c_size_t, U, U,
                                               c.POINTER(NativeRandom), Allocate, Destroy, Refresh,
                                               Resolve, c.c_void_p]
    n.vertrix_random_seed.argtypes = [c.POINTER(NativeRandom), c.c_uint32]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43cf30)
    totals = {}
    seeds = [0, 0x12345678]
    sides_free = [SIDES + i * SIDE_STRIDE for i in range(8)]
    allocations, replay = [], []
    next_alloc = [0]
    native_destroy, native_refresh = [], []
    host_sides = {}
    host_preview = c.create_string_buffer(SIZE)

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
        if handle == PREVIEW:
            storage[0] = c.cast(host_preview, c.c_void_p)
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

    per_member = (args.cases + len(MEMBERS) - 1) // len(MEMBERS)
    for seed in seeds:
        state = NativeRandom()
        n.vertrix_random_seed(c.byref(state), seed)
        original.piece_seed(seed)
        for address, name, table in MEMBERS:
            for _ in range(per_member):
                use_side = rng.random() < 0.5
                side = sides_free[rng.randrange(len(sides_free))] if use_side else 0
                if use_side:
                    data = bytearray(rng.getrandbits(8) for _ in range(SIDE_STRIDE))
                    res = side + 0x100
                    struct.pack_into('<I', data, RESOURCE, res)
                    cpu.mem_write(side, bytes(data))
                    cpu.mem_write(res, struct.pack('<I', METHOD))
                difficulty = rng.choice([0, 1, 2])
                player = bytearray(rng.getrandbits(8) for _ in range(SIZE))
                preview = bytearray(rng.getrandbits(8) for _ in range(SIZE))
                struct.pack_into('<I', player, SIDE, side)
                struct.pack_into('<I', player, 0x3b4, PREVIEW)
                new_side = rng.choice([h for h in sides_free if h != side])
                next_alloc[0] = new_side
                new_data = bytearray(rng.getrandbits(8) for _ in range(SIDE_STRIDE))
                cpu.mem_write(new_side, bytes(new_data))
                cpu.mem_write(PLAYER, bytes(player))
                cpu.mem_write(PREVIEW, bytes(preview))
                cpu.mem_write(DIFFICULTY, struct.pack('<I', difficulty))
                steps = struct.unpack('<I', cpu.mem_read(table + difficulty * 4, 4))[0]
                start = len(allocations)
                stubs.log.clear()
                native_destroy.clear()
                native_refresh.clear()
                original.call(address, eax=PLAYER)
                assert allocations[start:] == [new_side], allocations[start:]
                replay.extend(allocations[start:])
                host_player = c.create_string_buffer(bytes(player), SIZE)
                host_preview.raw = bytes(preview)
                host_sides.clear()
                host_sides[new_side] = c.create_string_buffer(bytes(new_data), SIDE_STRIDE)
                assert natives[name](host_player, SIZE, PLAYER, steps, c.byref(state), allocate,
                                      destroy, refresh, resolve, None) == 1
                assert not replay, 'replay consumed'
                assert bytes(cpu.mem_read(PLAYER, SIZE)) == host_player.raw, (name, 'player')
                assert bytes(cpu.mem_read(PREVIEW, SIZE)) == host_preview.raw, (name, 'preview')
                assert bytes(cpu.mem_read(new_side, SIDE_STRIDE)) == host_sides[new_side].raw, \
                    (name, 'side')
                assert destroy_events() == native_destroy, (name, 'destroy')
                assert refresh_events() == native_refresh, (name, 'refresh')
                assert rng_pos() == state.position, (name, 'rng')
                totals[hex(address)] = totals.get(hex(address), 0) + 1
# 0x43ce70 : steps and mode base both derive from the + 0x3fc index.
        for _ in range(per_member):
            use_side = rng.random() < 0.5
            side = sides_free[rng.randrange(len(sides_free))] if use_side else 0
            if use_side:
                data = bytearray(rng.getrandbits(8) for _ in range(SIDE_STRIDE))
                res = side + 0x100
                struct.pack_into('<I', data, RESOURCE, res)
                cpu.mem_write(side, bytes(data))
                cpu.mem_write(res, struct.pack('<I', METHOD))
            index = rng.choice([0, 1, 2, 3])
            player = bytearray(rng.getrandbits(8) for _ in range(SIZE))
            preview = bytearray(rng.getrandbits(8) for _ in range(SIZE))
            struct.pack_into('<I', player, SIDE, side)
            struct.pack_into('<I', player, 0x3b4, PREVIEW)
            struct.pack_into('<I', player, 0x3fc, index)
            new_side = rng.choice([h for h in sides_free if h != side])
            next_alloc[0] = new_side
            new_data = bytearray(rng.getrandbits(8) for _ in range(SIDE_STRIDE))
            cpu.mem_write(new_side, bytes(new_data))
            cpu.mem_write(PLAYER, bytes(player))
            cpu.mem_write(PREVIEW, bytes(preview))
            steps = struct.unpack('<I', cpu.mem_read(T38 + index * 4, 4))[0]
            start = len(allocations)
            stubs.log.clear()
            native_destroy.clear()
            native_refresh.clear()
            original.call(0x43ce70, eax=PLAYER)
            assert allocations[start:] == [new_side], allocations[start:]
            replay.extend(allocations[start:])
            host_player = c.create_string_buffer(bytes(player), SIZE)
            host_preview.raw = bytes(preview)
            host_sides.clear()
            host_sides[new_side] = c.create_string_buffer(bytes(new_data), SIDE_STRIDE)
            assert n.vertrix_player_setup_indexed(host_player, SIZE, PLAYER, steps, c.byref(state),
                                                  allocate, destroy, refresh, resolve,
                                                  None) == 1
            assert not replay, 'indexed replay consumed'
            assert bytes(cpu.mem_read(PLAYER, SIZE)) == host_player.raw, 'indexed player'
            assert bytes(cpu.mem_read(PREVIEW, SIZE)) == host_preview.raw, 'indexed preview'
            assert bytes(cpu.mem_read(new_side, SIDE_STRIDE)) == host_sides[new_side].raw, \
                'indexed side'
            assert destroy_events() == native_destroy, 'indexed destroy'
            assert refresh_events() == native_refresh, 'indexed refresh'
            assert rng_pos() == state.position, 'indexed rng'
            totals['0x43ce70'] = totals.get('0x43ce70', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete mode-setup routines execute in the original (allocator, refresh '
                       'and destructor stubbed and logged); player, side, preview and RNG '
                       'position compare.'}
    (args.build_dir / 'player-modes-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
