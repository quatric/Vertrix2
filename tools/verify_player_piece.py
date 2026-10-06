"""Compare complete original player piece create/release methods."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from verify_piece_actor_construct import Placement
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP
PLAYER, PARENT, ACTORS, CHILDREN, VTABLE, STUB = 0x800000, 0x801000, 0x802000, 0x900000, 0x804000, 0x804100
Resolve = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t), c.c_void_p)
Destroy = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_void_p)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'player-piece.dylib'
    names = ['player_piece.c', 'piece_actor_construct.c', 'piece_actor_layout.c', 'piece_child_update.c', 'actor_storage.c', 'timer.c', 'timing.c', 'dword_transition.c', 'frame_resource.c', 'piece_actor_update.c']
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror', * [str(source / n) for n in names], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_player_piece_create.argtypes = [c.c_void_p, c.c_size_t, c.c_uint32, c.c_void_p, c.c_size_t, c.c_void_p, c.c_size_t, c.POINTER(c.c_uint32), c.POINTER(c.c_uint32), c.c_uint8, c.c_int, c.c_int, c.POINTER(Placement)]
    for name in ('vertrix_player_piece_release', 'vertrix_player_preview_release'):
        getattr(native, name).argtypes = [c.c_void_p, c.c_size_t, Resolve, c.c_void_p, Destroy, c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_map(0x900000, 0x3000)
    cpu.mem_write(STUB, b'\xc3')
    destroyed = []
    def record(cpu, address, size, context):
        destroyed.append((cpu.reg_read(UC_X86_REG_EAX), cpu.reg_read(UC_X86_REG_EDX)))
    cpu.hook_add(UC_HOOK_CODE, record, begin=STUB, end=STUB)
    children_addresses = [CHILDREN + i * 0x200 for i in range(7)]
    allocated = []
    def allocate(cpu, address, size, context):
        request = cpu.reg_read(UC_X86_REG_EAX)
        result = PARENT if request == 0x18c else children_addresses[len(allocated)]
        if request != 0x18c:
            assert request == 0x15c
            allocated.append(result)
        stack = cpu.reg_read(UC_X86_REG_ESP)
        destination = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
        cpu.reg_write(UC_X86_REG_EAX, result)
        cpu.reg_write(UC_X86_REG_ESP, stack + 4)
        cpu.reg_write(0x1a, destination)
# UC_X86_REG_EIP
    cpu.hook_add(UC_HOOK_CODE, allocate, begin=0x4ca000, end=0x4ca000)
    rng = random.Random(0x432160)
    actors = {}
    counts = {'create': 0, 'create_existing': 0, 'release': 0, 'release_empty': 0, 'preview': 0, 'preview_empty': 0}
    @ Resolve
    def resolve(handle, storage, size, context):
        if handle not in actors:
            return 0
        storage[0], size[0] = c.addressof(actors[handle]), len(actors[handle])
        return 1
    @ Destroy
    def destroy(handle, context):
        destroyed_native.append(handle)
        return 1
    destroyed_native = []
    def seed_actors():
        actors.clear()
        for i in range(8):
            handle = ACTORS + i * 0x200
            raw = bytearray(rng.randbytes(0x200))
            actors[handle] = c.create_string_buffer(bytes(raw), len(raw))
            cpu.mem_write(handle, bytes(raw))
    for case in range(2048):
        player_raw = bytearray(rng.randbytes(0xd00))
#create
        existing = case % 4 == 0
        struct.pack_into('<I', player_raw, 0xb78, rng.getrandbits(32) | 1 if existing else 0)
        parent_raw = rng.randbytes(0x1a0)
        child_raw = rng.randbytes(7 * 0x15c)
        count = case % 8
        values = [rng.getrandbits(32) for _ in range(count)] + [0xffffffff] * (7 - count)
        rng.shuffle(values)
        frames = (c.c_uint32 * 7)(* values)
        handles = (c.c_uint32 * 7)(* children_addresses)
        side, difficulty, level = rng.randrange(256), case % 3, (case // 3) % 10
        spacing = rng.choice([14, 0, 65535, rng.randrange(65536)])
        geometry_values = [138, 248, 488, 248, 14, 202] if case % 2 == 0 else [rng.choice([0, 1, 65535, rng.getrandbits(32)]) for _ in range(6)]
        geometry = Placement(* geometry_values, spacing)
        cpu.mem_write(0x532bbc, struct.pack('<I', difficulty))
        cpu.mem_write(0x4f90ac, struct.pack('<H', spacing))
        cpu.mem_write(0x4f89e8, struct.pack('<6I', * geometry_values))
        cpu.mem_write(0x803000, bytes(frames))
        cpu.mem_write(PLAYER, bytes(player_raw))
        cpu.mem_write(PARENT, parent_raw)
        for i, address in enumerate(children_addresses):
            cpu.mem_write(address, child_raw[i * 0x15c: (i + 1) * 0x15c])
        allocated.clear()
        original.call(0x432160, eax=PLAYER, edx=side, ecx=0x803000, ebx=level)
        player = c.create_string_buffer(bytes(player_raw), len(player_raw))
        parent = c.create_string_buffer(parent_raw, len(parent_raw))
        children = c.create_string_buffer(child_raw, len(child_raw))
        assert native.vertrix_player_piece_create(player, len(player_raw), PARENT, parent, len(parent_raw), children, len(child_raw), frames, handles, side, difficulty, level, c.byref(geometry))
        assert player.raw == bytes(cpu.mem_read(PLAYER, len(player_raw))), case
        assert parent.raw == bytes(cpu.mem_read(PARENT, len(parent_raw))), case
        for i, address in enumerate(children_addresses):
            assert children.raw[i * 0x15c: (i + 1) * 0x15c] == bytes(cpu.mem_read(address, 0x15c)), (case, i)
        counts['create_existing' if existing else 'create'] += 1
        before = player.raw, parent.raw, children.raw
        assert not native.vertrix_player_piece_create(player, 0xb7b, PARENT, parent, len(parent_raw), children, len(child_raw), frames, handles, side, difficulty, level, c.byref(geometry))
        if not existing:
            c.memmove(c.addressof(player) + 0xb78, bytes(4), 4)
            before = player.raw, parent.raw, children.raw
            assert not native.vertrix_player_piece_create(player, len(player_raw), 0, parent, len(parent_raw), children, len(child_raw), frames, handles, side, difficulty, level, c.byref(geometry))
            assert not native.vertrix_player_piece_create(player, len(player_raw), PARENT, parent, 0x18b, children, len(child_raw), frames, handles, side, difficulty, level, c.byref(geometry))
            assert not native.vertrix_player_piece_create(player, len(player_raw), PARENT, parent, len(parent_raw), children, len(child_raw), frames, handles, side, 3, level, c.byref(geometry))
        assert (player.raw, parent.raw, children.raw) == before
#release active piece
        seed_actors()
        piece = bytearray(rng.randbytes(0x1a0))
        pieces = list(actors)
        empty = case % 5 == 0
        slot_count = rng.randrange(1, 8)
        struct.pack_into('<I', piece, 0x158, VTABLE)
        struct.pack_into('<I', piece, 0x188, slot_count)
        for i in range(7):
            struct.pack_into('<I', piece, 0x15c + i * 4, rng.choice(pieces))
        struct.pack_into('<I', piece, 0x158 + slot_count * 4, rng.choice(pieces))
        player_raw = bytearray(rng.randbytes(0xd00))
        struct.pack_into('<I', player_raw, 0xb78, 0 if empty else PARENT)
        struct.pack_into('<I', player_raw, 0xb70, 0 if case % 3 == 0 else PARENT)
        cpu.mem_write(VTABLE, struct.pack('<I', STUB))
        cpu.mem_write(PARENT, bytes(piece))
        cpu.mem_write(PLAYER, bytes(player_raw))
        actors[PARENT] = c.create_string_buffer(bytes(piece), len(piece))
        for handle, actor in actors.items():
            if handle != PARENT:
                cpu.mem_write(handle, actor.raw)
        player = c.create_string_buffer(bytes(player_raw), len(player_raw))
        destroyed.clear()
        destroyed_native.clear()
        original.call(0x4321b0, eax=PLAYER)
        assert native.vertrix_player_piece_release(player, len(player_raw), resolve, None, destroy, None)
        assert player.raw == bytes(cpu.mem_read(PLAYER, len(player_raw))), case
        assert destroyed_native == ([] if empty else [PARENT])
        assert destroyed == ([] if empty else [(PARENT, 2)])
        counts['release_empty' if empty else 'release'] += 1
#failure preservation
        if not empty:
            c.memmove(c.addressof(player) + 0xb78, struct.pack('<I', PARENT), 4)
            before = player.raw
            assert not native.vertrix_player_piece_release(player, 0xb7b, resolve, None, destroy, None)
            c.memmove(c.addressof(actors[PARENT]) + 0x188, struct.pack('<I', 0), 4)
            assert not native.vertrix_player_piece_release(player, len(player_raw), resolve, None, destroy, None)
            assert player.raw == before
#release preview
            player = c.create_string_buffer(bytes(player_raw), len(player_raw))
            cpu.mem_write(PLAYER, bytes(player_raw))
            preview = bytearray(rng.randbytes(0x1a0))
            struct.pack_into('<I', preview, 0x158, VTABLE)
            actors[PARENT] = c.create_string_buffer(bytes(preview), len(preview))
            cpu.mem_write(PARENT, bytes(preview))
            player_raw2 = bytearray(player_raw)
            struct.pack_into('<I', player_raw2, 0xb70, 0 if case % 3 == 0 else PARENT)
            player = c.create_string_buffer(bytes(player_raw2), len(player_raw2))
            cpu.mem_write(PLAYER, bytes(player_raw2))
            destroyed.clear()
            destroyed_native.clear()
            original.call(0x432110, eax=PLAYER)
            assert native.vertrix_player_preview_release(player, len(player_raw2), resolve, None, destroy, None)
            assert player.raw == bytes(cpu.mem_read(PLAYER, len(player_raw2))), case
            empty_preview = case % 3 == 0
            assert destroyed == ([] if empty_preview else [(PARENT, 2)])
            assert destroyed_native == ([] if empty_preview else [PARENT])
            counts['preview_empty' if empty_preview else 'preview'] += 1
    report = {'status': 'passed', 'cases': 2048, ** counts, 'scope': 'Complete 432160, 4321b0 and 432110 execute in the original with heap allocation ' 'and the virtual destructor supplied as boundaries (identity and flag-2 argument ' 'asserted). Whole player, parent and child storage compare. Destructor bodies, ' 'preview construction 4320d0/42b6b0 and game-loop integration remain separate.'}
    (build / 'player-piece-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
