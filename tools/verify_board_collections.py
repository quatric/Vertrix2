"""Compare complete original board collection wrappers with the native recovery."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX
from verify_board_cells import COLLECTIONS, Scene, scene_from_memory, BOARD, SIZE, ACTIVE
POOL, VTABLE, STUB = 0x806000, 0x80f000, 0x80f100
HANDLERS = (0x44c370, 0x44c2b0, 0x44c2a0)
CLEAR = ((0x42ebc0, 0), (0x42ebe0, 1), (0x42ec00, 2), (0x42ec20, 3), (0x42ec40, 4), (0x42ec60, 5))
ALL = ((0x42eca0, 0), (0x42ecc0, 1), (0x42ece0, 2), (0x42ed00, 3), (0x42ed20, 4), (0x42ec80, 5))
Destroy = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)
Resolve = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t), c.c_void_p)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'board-collections.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror', str(source / 'board_collections.c'), str(source / 'board_cells.c'), str(source / 'actor_fields.c'), str(source / 'actor_storage.c'), '-o', str(library)], check=True)
    n = c.CDLL(str(library))
    P, U, V = c.POINTER(Scene), c.c_uint32, c.c_void_p
    n.vertrix_board_clear_collection.argtypes = [P, c.c_int, Destroy, V]
    n.vertrix_board_collection_all_handler.argtypes = [P, c.c_int, U, Resolve, V, c.POINTER(U)]
    n.vertrix_board_collection_set_handler.argtypes = [P, c.c_int, U, Resolve, V]
    n.vertrix_board_piece_all_handler.argtypes = [P, c.c_int, U, Resolve, V, c.POINTER(U)]
    n.vertrix_board_piece_set_handler.argtypes = [P, U, Resolve, V]
    n.vertrix_board_prepare_slots.argtypes = [P, Resolve, V]
    n.vertrix_board_clear_marked_extra.argtypes = [P, c.c_uint8 * 65, Destroy, V]
    n.vertrix_board_destroy_marked.argtypes = [P, c.c_uint8 * 65, Destroy, V]
    n.vertrix_board_assign_effect.argtypes = [P, c.c_uint8, Resolve, V]
    n.vertrix_board_apply_pattern.argtypes = [P, c.c_uint8 * 65, Resolve, V]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4b2300)
    cpu.mem_write(STUB, b'\xc3')
    cpu.mem_write(VTABLE, struct.pack('<I', STUB))
    events, native_events, objects = [], [], {}
    cpu.hook_add(UC_HOOK_CODE, lambda cpu, a, s, x: events.append((cpu.reg_read(UC_X86_REG_EAX), cpu.reg_read(UC_X86_REG_EDX))), begin=STUB, end=STUB)
    @ Destroy
    def destroy(handle, flag, context):
        native_events.append((handle, flag))
    @ Resolve
    def resolve(handle, storage, size, context):
        if handle not in objects:
            return 0
        storage[0] = c.addressof(objects[handle])
        size[0] = len(objects[handle])
        return 1
    pool = [POOL + 0x200 * k for k in range(70)]
    totals = {}
    def count(name):
        totals[name] = totals.get(name, 0) + 1
    for case in range(args.cases):
        memory = bytearray(rng.randbytes(SIZE))
        density = rng.choice([0.05, 0.4, 0.9])
        for first, offset, size in COLLECTIONS:
            for i in range(size):
                struct.pack_into('<I', memory, offset + 4 * i, rng.choice(pool) if rng.random() < density else 0)
        struct.pack_into('<I', memory, ACTIVE, rng.choice(pool) if rng.random() < 0.85 else 0)
        agreeing = rng.random() < 0.5
        main_handler = rng.choice(HANDLERS)
        for handle in pool:
            data = bytearray(rng.randbytes(0x200))
            struct.pack_into('<I', data, 0x158, VTABLE)
            struct.pack_into('<I', data, 0x154, main_handler if agreeing and rng.random() < 0.97 else rng.choice(HANDLERS))
            for child in range(10):
                struct.pack_into('<I', data, 0x15c + 4 * child, rng.choice(pool) if rng.random() < 0.7 else 0)
            cpu.mem_write(handle, bytes(data))
        handler = main_handler if rng.random() < 0.8 else rng.choice(HANDLERS)
        def fresh():
            cpu.mem_write(BOARD, bytes(memory))
            objects.clear()
            for handle in pool:
                objects[handle] = c.create_string_buffer(bytes(cpu.mem_read(handle, 0x200)), 0x200)
            return scene_from_memory(memory)
        def check(scene, name):
            assert bytes(scene) == bytes(scene_from_memory(bytes(cpu.mem_read(BOARD, SIZE)))), (case, name)
            for handle, buffer in objects.items():
                assert buffer.raw == bytes(cpu.mem_read(handle, 0x200)), (case, name, hex(handle))
        for address, which in CLEAR:
            scene = fresh()
            events.clear()
            native_events.clear()
            original.call(address, eax=BOARD)
            assert n.vertrix_board_clear_collection(c.byref(scene), which, destroy, None)
            assert events == native_events, (case, address)
            check(scene, 'clear')
            count('clear')
        for address, which in ALL:
            scene = fresh()
            result = original.call(address, eax=BOARD, edx=handler)
            out = c.c_uint32(7)
            assert n.vertrix_board_collection_all_handler(c.byref(scene), which, handler, resolve, None, c.byref(out))
            assert out.value == result & 0xffffffff, (case, address)
            check(scene, 'all')
            count('all')
        scene = fresh()
        original.call(0x42eda0, eax=BOARD, edx=handler)
        assert n.vertrix_board_collection_set_handler(c.byref(scene), 0, handler, resolve, None)
        check(scene, 'set')
        count('set')
        for address, list_index in ((0x42ed40, 0), (0x42edf0, 0), (0x42ed70, 1)):
            scene = fresh()
            result = original.call(address, eax=BOARD, edx=handler)
            out = c.c_uint32(7)
            assert n.vertrix_board_piece_all_handler(c.byref(scene), list_index, handler, resolve, None, c.byref(out))
            assert out.value == result & 0xffffffff, (case, address)
            check(scene, 'piece_all')
            count('piece_all')
        marks = bytes(rng.choice([0, 1, 2, 2, 3]) for _ in range(65))
        for address, name in ((0x4398c0, 'clear_marked_extra'), (0x439190, 'destroy_marked')):
            memory[0xb94: 0xb94 + 65] = marks
            scene = fresh()
            cpu.mem_write(BOARD + 0xb94, marks)
            events.clear()
            native_events.clear()
            original.call(address, eax=BOARD)
            grid = (c.c_uint8 * 65).from_buffer_copy(marks)
            if name == 'clear_marked_extra':
                n.vertrix_board_clear_marked_extra(c.byref(scene), grid, destroy, None)
            else:
                assert n.vertrix_board_destroy_marked(c.byref(scene), grid, destroy, None)
            assert events == native_events, (case, name)
            check(scene, name)
            count(name)
        for mode in range(7):
            scene = fresh()
            original.call(0x438b90, eax=BOARD, edx=mode)
            assert n.vertrix_board_assign_effect(c.byref(scene), mode, resolve, None)
            check(scene, 'effect')
            count('assign_effect')
        scene = fresh()
        table_index = rng.randrange(0, 12)
        pattern = bytes(cpu.mem_read(0x4f7e40 + 65 * table_index, 65))
        original.call(0x438c60, eax=BOARD, edx=table_index)
        assert n.vertrix_board_apply_pattern(c.byref(scene), (c.c_uint8 * 65).from_buffer_copy(pattern), resolve, None)
        check(scene, 'pattern')
        count('pattern')
        scene = fresh()
        original.call(0x42edc0, eax=BOARD, edx=handler)
        assert n.vertrix_board_piece_set_handler(c.byref(scene), handler, resolve, None)
        check(scene, 'piece_set')
        count('piece_set')
        for handle in pool:
            data = bytearray(cpu.mem_read(handle, 0x200))
            data[0x44] = rng.choice([0x10, 0x10, 0, 3])
            data[0x15c] = rng.choice([5, 5, 1, 6])
            cpu.mem_write(handle, bytes(data))
        scene = fresh()
        original.call(0x4387b0, eax=BOARD)
        assert n.vertrix_board_prepare_slots(c.byref(scene), resolve, None)
        check(scene, 'prepare')
        count('prepare')
    expected = {'clear': 6, 'all': 6, 'set': 1, 'piece_all': 3,
                'clear_marked_extra': 1, 'destroy_marked': 1, 'assign_effect': 7,
                'pattern': 1, 'piece_set': 1, 'prepare': 1}
    assert totals == {name: multiplier * args.cases for name, multiplier in expected.items()}
    report = {'status': 'passed', 'complete_original_executions': totals, 'scope': 'Complete 42ebc0..42ec60 (clear), 42ec80..42ed20 (all handler), 42eda0 (set), ' '42ed40, 42ed70, 42edf0 (piece lists) and 42edc0, 4387b0, 438c60, 4398c0, 439190 and 438b90 execute in the original with real ' '4b22c0, 4b2300 and 4b2340. Whole scene collections, every object and destruction ' 'order compare.'}
    (build / 'board-collections-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
