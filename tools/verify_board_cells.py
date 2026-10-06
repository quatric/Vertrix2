"""Compare complete original board marking and column fall routines with the native recovery."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX

BOARD, SIZE = 0x801000, 0xe00
#(scene.slots start, original board offset, count) in scene collection order.
ACTIVE, EXTRA = 0xa60, 0xce0
COLLECTIONS = ((0, 0x220, 65), (65, 0x87c, 65), (130, 0x988, 5), (135, 0x9e8, 13), (148, 0xa2c, 13),
               (161, 0x324, 260), (421, 0xbdc, 65))


class Scene(c.Structure):
    _fields_ = [('slots', c.c_uint32 * 486), ('active', c.c_uint32), ('extra', c.c_uint32),
                ('suppress_layout', c.c_uint32), ('active_a', c.c_uint8), ('active_b', c.c_uint8),
                ('cell_a', c.c_uint8 * 65), ('cell_b', c.c_uint8 * 65), ('columns_a', c.c_uint8 * 5),
                ('columns_b', c.c_uint8 * 5), ('rows', (c.c_uint8 * 13) * 4)]


def scene_from_memory(memory):
    scene = Scene()
    for first, offset, count in COLLECTIONS:
        for i in range(count):
            scene.slots[first + i] = struct.unpack_from('<I', memory, offset + 4 * i)[0]
    scene.active = struct.unpack_from('<I', memory, ACTIVE)[0]
    scene.extra = struct.unpack_from('<I', memory, EXTRA)[0]
    scene.cell_a[:] = memory[0x15c:0x15c + 65]
    scene.cell_b[:] = memory[0x19d:0x19d + 65]
    scene.columns_a[:] = memory[0x99c:0x99c + 5]
    scene.columns_b[:] = memory[0x9a1:0x9a1 + 5]
    for row in range(4):
        scene.rows[row][:] = memory[0x9a6 + 13 * row:0x9a6 + 13 * row + 13]
    return scene


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'board-cells.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    str(source / 'board_cells.c'), str(source / 'actor_fields.c'),
                    str(source / 'actor_storage.c'), '-o', str(library)], check=True)
    n = c.CDLL(str(library))
    for name in ('mark_columns', 'mark_rows_first', 'mark_rows_second'):
        getattr(n, 'vertrix_board_' + name).argtypes = [c.POINTER(Scene), c.c_uint8]
    Destroy = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)
    n.vertrix_board_drop_columns.argtypes = [c.POINTER(Scene), Destroy, c.c_void_p]
    Resolve = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t), c.c_void_p)
    n.vertrix_board_release_active.argtypes = [c.POINTER(Scene), Destroy, c.c_void_p]
    n.vertrix_board_release_extra.argtypes = [c.POINTER(Scene), Destroy, c.c_void_p]
    n.vertrix_board_ready_previews.argtypes = [c.POINTER(Scene), Resolve, c.c_void_p]
    n.vertrix_board_restart_slots.argtypes = [c.POINTER(Scene), c.c_uint32, Resolve, c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x42f760)
    VTABLE, STUB, POOL = 0x80f000, 0x80f100, 0x806000
    cpu.mem_write(STUB, b'\xc3')
    cpu.mem_write(VTABLE, struct.pack('<I', STUB))
    events, native_events = [], []
    cpu.hook_add(UC_HOOK_CODE, lambda cpu, a, s, x: events.append(
        (cpu.reg_read(UC_X86_REG_EAX), cpu.reg_read(UC_X86_REG_EDX))), begin=STUB, end=STUB)

    @Destroy
    def destroy(handle, flag, context):
        native_events.append((handle, flag))
    routines = ((0x42f210, 'mark_columns'), (0x42f440, 'mark_rows_first'), (0x42f4b0, 'mark_rows_second'),
                (0x42f760, 'drop_columns'))
    totals = {name: 0 for _, name in routines}
    for case in range(args.cases):
        for address, name in routines:
            memory = bytearray(rng.randbytes(SIZE))
            for first, offset, count in COLLECTIONS:
                for i in range(count):
                    if rng.random() < 0.5:
                        struct.pack_into('<I', memory, offset + 4 * i, 0)
            if name == 'drop_columns':
                for slot in range(65):
                    handle = POOL + 0x200 * slot if rng.random() < 0.6 else 0
                    struct.pack_into('<I', memory, 0x220 + 4 * slot, handle)
                    if handle:
                        cpu.mem_write(handle + 0x158, struct.pack('<I', VTABLE))
            cpu.mem_write(BOARD, bytes(memory))
            scene = scene_from_memory(memory)
            events.clear(); native_events.clear()
            original.call(address, eax=BOARD)
            after = bytes(cpu.mem_read(BOARD, SIZE))
            native = getattr(n, 'vertrix_board_' + name)
            if name == 'drop_columns':
                native(c.byref(scene), destroy, None)
                assert events == native_events, (case, events, native_events)
            else:
                native(c.byref(scene), memory[0x58])
            expected = scene_from_memory(after)
            assert bytes(scene) == bytes(expected), (case, name)
            totals[name] += 1

    n.vertrix_board_place_extra.argtypes = [c.c_void_p, c.c_size_t, c.c_uint16, c.c_uint16, c.c_int]
    for name in ('has_type_one', 'has_kind_six', 'has_type_one_extra'):
        getattr(n, 'vertrix_board_' + name).argtypes = [c.POINTER(Scene), Resolve, c.c_void_p]
        getattr(n, 'vertrix_board_' + name).restype = c.c_int
    n.vertrix_board_purge_type_two.argtypes = [c.POINTER(Scene), Resolve, Destroy, c.c_void_p]
    n.vertrix_board_swap_slots.argtypes = [c.POINTER(c.c_uint32), c.c_uint32, c.c_uint32,
                                           c.POINTER(c.c_uint32), c.c_uint32, c.c_uint32]
    n.vertrix_board_set_actor_clip.argtypes = [c.c_void_p, c.c_size_t, c.c_void_p, c.c_size_t]
    objects = {}

    @Resolve
    def resolve(handle, storage, size, context):
        if handle not in objects:
            return 0
        storage[0] = c.addressof(objects[handle])
        size[0] = len(objects[handle])
        return 1

    def load_objects(handles):
        objects.clear()
        for handle in handles:
            if handle:
                objects[handle] = c.create_string_buffer(bytes(cpu.mem_read(handle, 0x200)), 0x200)

    def same_objects():
        for handle, buffer in objects.items():
            assert buffer.raw == bytes(cpu.mem_read(handle, 0x200)), hex(handle)

    pool = [POOL + 0x200 * k for k in range(70)]
    object_totals = {'release_active': 0, 'release_extra': 0, 'ready_previews': 0, 'restart_slots': 0}
    for case in range(args.cases):
        for address, name in ((0x42eb60, 'release_active'), (0x430150, 'release_extra'),
                              (0x42ee20, 'ready_previews'), (0x42ee80, 'restart_slots')):
            memory = bytearray(rng.randbytes(SIZE))
            for first, offset, count in COLLECTIONS:
                for i in range(count):
                    handle = rng.choice(pool) if rng.random() < 0.5 else 0
                    struct.pack_into('<I', memory, offset + 4 * i, handle)
            active = rng.choice(pool) if rng.random() < 0.8 else 0
            struct.pack_into('<I', memory, ACTIVE, active)
            struct.pack_into('<I', memory, EXTRA, rng.choice(pool) if rng.random() < 0.8 else 0)
            cpu.mem_write(BOARD, bytes(memory))
            for handle in pool:
                data = bytearray(rng.randbytes(0x200))
                struct.pack_into('<I', data, 0x158, VTABLE)
                for child in range(3):
                    struct.pack_into('<I', data, 0x15c + 4 * child,
                                     rng.choice(pool) if rng.random() < 0.6 else 0)
                cpu.mem_write(handle, bytes(data))
            scene = scene_from_memory(memory)
            load_objects(pool)
            steps = rng.getrandbits(32)
            events.clear(); native_events.clear()
            original.call(address, eax=BOARD, edx=steps)
            after = bytes(cpu.mem_read(BOARD, SIZE))
            if name in ('release_active', 'release_extra'):
                getattr(n, 'vertrix_board_' + name)(c.byref(scene), destroy, None)
                assert events == native_events, (case, name)
            elif name == 'ready_previews':
                assert n.vertrix_board_ready_previews(c.byref(scene), resolve, None)
            else:
                assert n.vertrix_board_restart_slots(c.byref(scene), steps, resolve, None)
            assert bytes(scene) == bytes(scene_from_memory(after)), (case, name)
            same_objects()
            object_totals[name] += 1
    scans = ((0x432200, 'purge_type_two'), (0x432280, 'has_type_one'), (0x4322f0, 'has_kind_six'),
             (0x4334b0, 'has_type_one_extra'))
    for case in range(args.cases):
        for address, name in scans:
            memory = bytearray(rng.randbytes(SIZE))
            density = rng.choice([0.05, 0.3, 0.8])
            for first, offset, count in COLLECTIONS:
                for i in range(count):
                    handle = rng.choice(pool) if rng.random() < density else 0
                    struct.pack_into('<I', memory, offset + 4 * i, handle)
            cpu.mem_write(BOARD, bytes(memory))
            for handle in pool:
                data = bytearray(rng.randbytes(0x200))
                struct.pack_into('<I', data, 0x158, VTABLE)
                data[0x15c] = rng.choice([0, 1, 5, 6, 6, 7])
                data[0x15d] = rng.choice([0, 1, 2, 2, 3])
                cpu.mem_write(handle, bytes(data))
            scene = scene_from_memory(memory)
            load_objects(pool)
            events.clear(); native_events.clear()
            result = original.call(address, eax=BOARD)
            after = bytes(cpu.mem_read(BOARD, SIZE))
            if name == 'purge_type_two':
                assert n.vertrix_board_purge_type_two(c.byref(scene), resolve, destroy, None)
                assert events == native_events, (case, name)
            else:
                found = getattr(n, 'vertrix_board_' + name)(c.byref(scene), resolve, None)
                assert found == (result & 0xffffffff), (case, name, found, result)
            assert bytes(scene) == bytes(scene_from_memory(after)), (case, name)
            same_objects()
            object_totals[name] = object_totals.get(name, 0) + 1
    for case in range(args.cases):
        memory = bytearray(rng.randbytes(SIZE))
        cpu.mem_write(BOARD, bytes(memory))
        grid = (c.c_uint32 * 65).from_buffer_copy(bytes(memory[0x220:0x220 + 260]))
        col_a, row_a, col_b, row_b = rng.randrange(5), rng.randrange(13), rng.randrange(5), rng.randrange(13)
        original.call(0x432ba0, eax=BOARD + 0x220, edx=col_a, ebx=row_a, ecx=BOARD + 0x220,
                      args=(col_b, row_b))
        assert n.vertrix_board_swap_slots(grid, col_a, row_a, grid, col_b, row_b)
        assert bytes(grid) == bytes(cpu.mem_read(BOARD + 0x220, 260)), case
        before = bytes(grid)
        assert not n.vertrix_board_swap_slots(grid, 5, 0, grid, 0, 0) and bytes(grid) == before
        object_totals['swap_slots'] = object_totals.get('swap_slots', 0) + 1
    for case in range(args.cases):
        for address, lower in ((0x4300b0, 0), (0x430100, 1)):
            memory = bytearray(rng.randbytes(SIZE))
            extra = rng.choice(pool)
            struct.pack_into('<I', memory, EXTRA, extra)
            cpu.mem_write(BOARD, bytes(memory))
            cpu.mem_write(extra, rng.randbytes(0x200))
            cpu.mem_write(0x532bbc, struct.pack('<I', rng.randrange(0, 64)))
            before = bytes(cpu.mem_read(extra, 0x200))
            buffer = c.create_string_buffer(before, 0x200)
            original.call(address, eax=BOARD)
            index = struct.unpack('<I', bytes(cpu.mem_read(0x532bbc, 4)))[0]
            table_word = struct.unpack('<H', bytes(cpu.mem_read(0x4f7d08 + 4 * index, 2)))[0]
            board_y = struct.unpack_from('<H', memory, 0x16)[0]
            assert n.vertrix_board_place_extra(buffer, 0x200, board_y, table_word, lower)
            assert buffer.raw == bytes(cpu.mem_read(extra, 0x200)), (case, lower)
            assert not n.vertrix_board_place_extra(buffer, 0x157, board_y, table_word, lower)
            object_totals['place_extra'] = object_totals.get('place_extra', 0) + 1
    for case in range(args.cases):
        memory = bytearray(rng.randbytes(SIZE))
            actor = rng.choice(pool) cpu.mem_write(BOARD, bytes(memory))
                        cpu.mem_write(actor, rng.randbytes(0x200))
                            before = bytes(cpu.mem_read(actor, 0x200))
                buffer = c.create_string_buffer(before, 0x200)
                             board = c.create_string_buffer(bytes(memory), SIZE)
                                         original.call(0x42ff10, eax = BOARD, edx = actor) assert
                                             n.vertrix_board_set_actor_clip(board, SIZE, buffer,
                                                                            0x200) assert buffer.raw
                                     == bytes(cpu.mem_read(actor, 0x200)),
        case kept = buffer.raw assert
                    not n.vertrix_board_set_actor_clip(board, 0x10, buffer, 0x200) and
                    buffer.raw == kept assert
                                  not n.vertrix_board_set_actor_clip(board, SIZE, buffer, 0x100) and
                    buffer.raw == kept object_totals['set_actor_clip'] =
                        object_totals.get('set_actor_clip', 0) +
                        1 totals.update(object_totals) report = {'status':
            'passed', 'complete_original_executions' : totals,
                                                       'scope'
                : 'Complete 42f210, 42f440, 42f4b0, 42f760, 42eb60, 430150, 42ee20, 42ee80, 4300b0, 430100, 432200, 432280, 4322f0, 4334b0 and 432ba0 and 42ff10 execute in the original over random ' 'board storage; every modeled scene collection and cell array compares whole.'
        }
        (build / 'board-cells-verification.json')
                .write_text(json.dumps(report, indent = 2) + '\n')
                    print(json.dumps(report, indent = 2))

                        if __name__ == '__main__' : main()
