"""Compare original board accessors and two extra actor accessors with the native recovery."""
import argparse, ctypes as c, json, random, subprocess
from pathlib import Path
from original import Original
BOARD, OBJ_A, OBJ_B, SIZE, OBJ_SIZE = 0x801000, 0x804000, 0x806000, 0xd00, 0x200
RESOLVE = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t), c.c_void_p)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'board-fields.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror', str(source / 'board_fields.c'), str(source / 'actor_fields.c'), str(source / 'actor_storage.c'), '-o', str(library)], check=True)
    n = c.CDLL(str(library))
    P, SZ, U32 = c.c_void_p, c.c_size_t, c.c_uint32
    U32P = c.POINTER(U32)
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x432010)
    totals = {}
    objects = {}
    def resolve(handle, storage, size, _context):
        if handle not in objects:
            return 0
        storage[0] = c.addressof(objects[handle])
        size[0] = OBJ_SIZE
        return 1
    callback = RESOLVE(resolve)
    getters = ((0x431380, 0xa60, 0x168), (0x432000, 0xa60, 0x17c), (0x431480, 0xb70, 0x170), (0x431490, 0xb78, 0x178))
    n.vertrix_board_object_field.argtypes = [P, SZ, U32, U32, RESOLVE, P, U32P]
    n.vertrix_board_set_a68.argtypes = [P, SZ, U32]
    n.vertrix_board_reset_counter.argtypes = [P, SZ, c.c_uint8]
    n.vertrix_board_bump_counter.argtypes = [P, SZ]
    n.vertrix_board_piece_below_top.argtypes = [P, SZ, RESOLVE, P, U32P]
    n.vertrix_board_extra_is_idle.argtypes = [P, SZ, RESOLVE, P, U32P]
    n.vertrix_actor_set_d0_steps.argtypes = [P, SZ, U32]
    n.vertrix_actor_get_handler.argtypes = [P, SZ, U32P]
    def count(name):
        totals[name] = totals.get(name, 0) + 1
    for case in range(4096):
        raw = bytearray(rng.randbytes(SIZE))
        obj_a, obj_b = rng.randbytes(OBJ_SIZE), bytearray(rng.randbytes(OBJ_SIZE))
        if rng.random() < 0.5:
            obj_b[0x154: 0x158] = (0x44c860).to_bytes(4, 'little')
        for offset in (0xa60, 0xb70, 0xb78, 0xce0):
            raw[offset: offset + 4] = rng.choice((OBJ_A, OBJ_B)).to_bytes(4, 'little')
        objects.clear()
        objects[OBJ_A] = c.create_string_buffer(obj_a, OBJ_SIZE)
        objects[OBJ_B] = c.create_string_buffer(bytes(obj_b), OBJ_SIZE)
        cpu.mem_write(BOARD, bytes(raw))
        cpu.mem_write(OBJ_A, obj_a)
        cpu.mem_write(OBJ_B, bytes(obj_b))
        board = c.create_string_buffer(bytes(raw), SIZE)
        for address, pointer, field in getters:
            expect = original.call(address, eax=BOARD)
            out = U32()
            assert n.vertrix_board_object_field(board, SIZE, pointer, field, callback, None, c.byref(out)) and out.value == expect, (case, hex(address))
            count(hex(address))
        value = rng.getrandbits(32)
        original.call(0x431d80, eax=BOARD, edx=value)
        assert n.vertrix_board_set_a68(board, SIZE, value)
        assert board.raw == bytes(cpu.mem_read(BOARD, SIZE)), case
        count('0x431d80')
        byte = rng.getrandbits(8)
        original.call(0x4334a0, eax=BOARD, edx=byte)
        assert n.vertrix_board_reset_counter(board, SIZE, byte)
        assert board.raw == bytes(cpu.mem_read(BOARD, SIZE)), case
        count('0x4334a0')
        original.call(0x4342f0, eax=BOARD)
        assert n.vertrix_board_bump_counter(board, SIZE)
        assert board.raw == bytes(cpu.mem_read(BOARD, SIZE)), case
        count('0x4342f0')
        expect = original.call(0x432010, eax=BOARD) & 0xff
        out = U32()
        assert n.vertrix_board_piece_below_top(board, SIZE, callback, None, c.byref(out))
        assert out.value == expect, case
        count('0x432010')
        expect = original.call(0x430090, eax=BOARD) & 0xff
        assert n.vertrix_board_extra_is_idle(board, SIZE, callback, None, c.byref(out))
        assert out.value == expect, case
        count('0x430090')
        steps = rng.getrandbits(32)
        cpu.mem_write(OBJ_A, obj_a)
        original.call(0x4ac470, eax=OBJ_A, edx=steps)
        actor = c.create_string_buffer(obj_a, OBJ_SIZE)
        assert n.vertrix_actor_set_d0_steps(actor, OBJ_SIZE, steps)
        assert actor.raw == bytes(cpu.mem_read(OBJ_A, OBJ_SIZE)), case
        count('0x4ac470')
        out = U32()
        assert n.vertrix_actor_get_handler(actor, OBJ_SIZE, c.byref(out))
        assert out.value == original.call(0x4ac900, eax=OBJ_A), case
        count('0x4ac900')
        assert not n.vertrix_board_set_a68(board, 0xa68 + 3, value)
        assert not n.vertrix_board_bump_counter(board, 0x838)
    report = {'status': 'passed', 'complete_original_executions': totals, 'scope': 'Complete 431380, 432000, 431480, 431490, 431d80, 4334a0, 4342f0, 432010, ' '430090, 4ac470 and 4ac900 execute in the original; whole board and actor ' 'storage and returned values compare for random contents.'}
    (build / 'board-fields-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
