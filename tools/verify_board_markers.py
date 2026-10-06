"""Compare complete original board marker routines with the native recovery."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original
# NOTE: verify_board_cells.py is currently unparseable (stray damage at line
# 233+, predates this work), so BOARD is defined locally instead of imported.
BOARD = 0x801000

POOL = 0x806000
KINDS, MARKERS, SLOTS, MASK, OUT = 0x1de, 0xb94, 0x220, 0x300, 0xf00
Resolve = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t), c.c_void_p)


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
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'board-markers.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    str(source / 'board_markers.c'), str(source / 'board.c'), str(source / 'actor_storage.c'), str(source / 'random.c'), '-o', str(library)],
                   check=True)
    n = c.CDLL(str(library))
    B65, U = c.c_uint8 * 65, c.c_uint32
    n.vertrix_board_snapshot_kinds.argtypes = [c.POINTER(U), U, Resolve, c.c_void_p, c.POINTER(c.c_uint8)]
    n.vertrix_board_mark_filled.argtypes = [c.POINTER(U), Resolve, c.c_void_p, B65, B65]
    n.vertrix_board_mark_stones_not_bombs.argtypes = [c.POINTER(U), Resolve, c.c_void_p, B65, B65]
    n.vertrix_board_mark_stones.argtypes = [c.POINTER(U), Resolve, c.c_void_p, B65, B65]
    n.vertrix_board_any_falling.argtypes = [c.POINTER(U), Resolve, c.c_void_p, B65, c.POINTER(U)]
    n.vertrix_board_mark_falling_cells.argtypes = [c.POINTER(U), Resolve, c.c_void_p, B65, c.c_uint8, B65]
    n.vertrix_board_clear_mask.argtypes = [c.POINTER(U)]
    n.vertrix_board_markers_for_mode.argtypes = [B65, U, B65]
    n.vertrix_board_markers_top.argtypes = [B65, B65]
    n.vertrix_board_marker_count.argtypes = [B65, c.c_uint8]
    n.vertrix_board_marker_count.restype = U
    n.vertrix_board_markers_checker.argtypes = [B65, c.c_int, B65]
    n.vertrix_board_markers_stones.argtypes = [B65, B65]
    n.vertrix_board_markers_kind.argtypes = [B65, U, B65]
    n.vertrix_board_markers_kind.restype = U
    n.vertrix_board_markers_for_power.argtypes = [B65, U, B65]
    n.vertrix_board_marker_in_column.argtypes = [B65, c.c_uint8, U, U, c.POINTER(U), c.POINTER(U)]
    n.vertrix_board_marker_in_column.restype = c.c_int
    n.vertrix_board_stamp_companions.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(NativeRandom),
                                                 Resolve, c.c_void_p]
    n.vertrix_board_any_bottom.argtypes = [c.POINTER(U), c.c_int32, c.c_int32, Resolve, c.c_void_p, B65,
                                           c.POINTER(U)]
    n.vertrix_board_any_block.argtypes = n.vertrix_board_any_bottom.argtypes
    for name in ('by_column', 'by_row'):
        getattr(n, 'vertrix_board_marker_nth_' + name).argtypes = [B65, c.c_uint8, U, c.POINTER(U), c.POINTER(U)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x435e80)
    objects = {}

    @Resolve
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

    def board_bytes():
        return bytes(cpu.mem_read(BOARD + KINDS, 65)), bytes(cpu.mem_read(BOARD + MARKERS, 65))

    for case in range(args.cases):
        memory = bytearray(rng.randbytes(0xf10))
        density = rng.choice([0.1, 0.5, 0.9])
        for i in range(65):
            struct.pack_into('<I', memory, SLOTS + 4 * i, rng.choice(pool) if rng.random() < density else 0)
        kinds = bytes(rng.choice([0xff, 0xff, 0, 1, 2, 3, 4, 5, 6, 7]) for _ in range(65))
        memory[KINDS:KINDS + 65] = kinds
        markers = bytes(rng.choice([0, 0, 1, 2, 3]) for _ in range(65))
        memory[MARKERS:MARKERS + 65] = markers

        def fresh():
            cpu.mem_write(BOARD, bytes(memory))
            objects.clear()
            for handle in pool:
                data = bytearray(rng.randbytes(0x200))
                data[0x15c] = rng.choice([0, 1, 2, 3, 4, 5, 6, 7, 0xff])
                cpu.mem_write(handle, bytes(data))
                objects[handle] = c.create_string_buffer(bytes(data), 0x200)

# 4327e0 : snapshot of slot kinds
        fresh()
        slot_values = (U * 65).from_buffer_copy(bytes(memory[SLOTS:SLOTS + 260]))
        out = B65()
        limit = rng.choice([65, 65, 13, 0])
        original.call(0x4327e0, eax=BOARD + SLOTS, edx=BOARD + KINDS, ebx=limit)
        assert n.vertrix_board_snapshot_kinds(slot_values, limit, resolve, None, out)
        assert bytes(out)[:limit] == board_bytes()[0][:limit], case
        count('snapshot')
        for address, name in ((0x4375a0, 'mark_filled'), (0x4383f0, 'mark_stones'),
                              (0x437f60, 'mark_stones_not_bombs'),
                              (0x4328a0, 'any_falling'),
                              (0x432820, 'snapshot_first_grid')):
            fresh()
            expect = original.call(address, eax=BOARD)
            snap, marks = board_bytes()
            kinds_out, markers_out = B65(), B65()
            if name in ('mark_filled', 'mark_stones', 'mark_stones_not_bombs'):
                assert getattr(n, 'vertrix_board_' + name)(slot_values, resolve, None, kinds_out, markers_out)
                assert bytes(kinds_out) == snap and bytes(markers_out) == marks, (case, name)
            else:
                falling = U()
                assert n.vertrix_board_any_falling(slot_values, resolve, None, kinds_out,
                                                   c.byref(falling))
                assert bytes(kinds_out) == snap, (case, name)
                if name == 'any_falling':
                    assert falling.value == expect & 0xffffffff, (case, name)
            count(name)
        fresh()
        original.call(0x432b10, eax=BOARD)
        kinds_out, cells_out = B65(), B65.from_buffer_copy(bytes(memory[0x19d:0x19d + 65]))
        assert n.vertrix_board_mark_falling_cells(slot_values, resolve, None, kinds_out, memory[0x58], cells_out)
        assert bytes(cells_out) == bytes(cpu.mem_read(BOARD + 0x19d, 65)), case
        assert bytes(kinds_out) == board_bytes()[0], case
        count('mark_falling_cells')
# 432840 : clear mask
        cpu.mem_write(BOARD, bytes(memory))
        mask = (U * 65).from_buffer_copy(bytes(memory[MASK:MASK + 260]))
        original.call(0x432840, eax=BOARD + MASK)
        n.vertrix_board_clear_mask(mask)
        assert bytes(mask) == bytes(cpu.mem_read(BOARD + MASK, 260)), case
        count('clear_mask')
# 435e80 / 435f30 : marker construction through the original's own snapshot
        for mode in (rng.choice([0, 1, 2, 3, 0xffffffff]),):
            fresh()
            original.call(0x435e80, eax=BOARD, edx=mode)
            snap, marks = board_bytes()
            expected = B65()
            n.vertrix_board_markers_for_mode(B65.from_buffer_copy(snap), mode, expected)
            assert bytes(expected) == marks, (case, mode)
            count('markers_for_mode')
        fresh()
        original.call(0x435f30, eax=BOARD)
        snap, marks = board_bytes()
        expected = B65()
        n.vertrix_board_markers_top(B65.from_buffer_copy(snap), expected)
        assert bytes(expected) == marks, case
        count('markers_top')
#finders over the random marker grid
        grid = B65.from_buffer_copy(markers)
        for address, kind in ((0x436030, 1), (0x436070, 2)):
            cpu.mem_write(BOARD, bytes(memory))
            result = original.call(address, eax=BOARD)
            assert n.vertrix_board_marker_count(grid, kind) == result & 0xffffffff, (case, address)
            count('marker_count')
        for address, kind, native in ((0x435fe0, 1, 'by_column'), (0x4360b0, 1, 'by_row'),
                                      (0x436100, 2, 'by_row')):
            cpu.mem_write(BOARD, bytes(memory))
            cpu.mem_write(BOARD + OUT, struct.pack('<II', 0xdead, 0xbeef))
            wanted = rng.randrange(0, 20)
            original.call(address, eax=BOARD, edx=wanted, ebx=BOARD + OUT, ecx=BOARD + OUT + 4)
            column, row = U(0xdead), U(0xbeef)
            found = getattr(n, 'vertrix_board_marker_nth_' + native)(grid, kind, wanted, c.byref(column),
                                                                   c.byref(row))
            assert (column.value, row.value) == struct.unpack('<II', bytes(cpu.mem_read(BOARD + OUT, 8))), \
                (case, address, wanted)
            count('marker_nth')
    for case in range(args.cases):
        memory = bytearray(rng.randbytes(0xf10))
        markers = bytes(rng.choice([0, 0, 1, 2, 3]) for _ in range(65))
        memory[MARKERS:MARKERS + 65] = markers
        grid = B65.from_buffer_copy(markers)
        cpu.mem_write(BOARD, bytes(memory))
        cpu.mem_write(BOARD + OUT, struct.pack('<II', 0xdead, 0xbeef))
        column = rng.randrange(5)
        result = original.call(0x439140, eax=BOARD, edx=BOARD + OUT, ebx=BOARD + OUT + 4, ecx=column)
        found_column, found_row = U(0xdead), U(0xbeef)
        assert n.vertrix_board_marker_in_column(grid, 1, column, 0, c.byref(found_column),
                                                c.byref(found_row)) == result & 0xffffffff, case
        assert (found_column.value, found_row.value) == struct.unpack(
            '<II', bytes(cpu.mem_read(BOARD + OUT, 8))), case
        count('first_marker_in_column')
        for address, kind in ((0x438830, 1), (0x4388a0, 2)):
            cpu.mem_write(BOARD, bytes(memory))
            cpu.mem_write(BOARD + OUT, struct.pack('<II', 0xdead, 0xbeef))
            wanted, column = rng.randrange(0, 8), rng.randrange(5)
            result = original.call(address, eax=BOARD, edx=wanted, ebx=BOARD + OUT, ecx=BOARD + OUT + 4,
                                   args=(column,))
            found_column, found_row = U(0xdead), U(0xbeef)
            found = n.vertrix_board_marker_in_column(grid, kind, column, wanted, c.byref(found_column),
                                                     c.byref(found_row))
            assert found == result & 0xffffffff, (case, address)
            assert (found_column.value, found_row.value) == struct.unpack(
                '<II', bytes(cpu.mem_read(BOARD + OUT, 8))), (case, address)
            count('marker_in_column')
        memory = bytearray(rng.randbytes(0xf10))
        for i in range(65):
            struct.pack_into('<I', memory, SLOTS + 4 * i, rng.choice(pool) if rng.random() < 0.3 else 0)
        for index in range(65):
            if rng.random() < 0.3:
                struct.pack_into('<I', memory, SLOTS + 4 * index, 0)
        cpu.mem_write(BOARD, bytes(memory))
        objects.clear()
        for handle in pool:
            data = bytearray(rng.randbytes(0x200))
            data[0x15c] = rng.choice([0, 1, 5, 6, 0xff])
            cpu.mem_write(handle, bytes(data))
            objects[handle] = c.create_string_buffer(bytes(data), 0x200)
        first, second = rng.randrange(-3, 4), rng.randrange(-3, 4)
        slot_values = (U * 65).from_buffer_copy(bytes(memory[SLOTS:SLOTS + 260]))
        for address, native, name in ((0x438910, n.vertrix_board_any_bottom, 'any_bottom'),
                                      (0x438d50, n.vertrix_board_any_block, 'any_block')):
            cpu.mem_write(BOARD, bytes(memory))
            result = original.call(address, eax=BOARD, edx=first & 0xffffffff, ebx=second & 0xffffffff)
            kinds_out, occupied = B65(*memory[KINDS:KINDS + 65]), U(7)
            assert native(slot_values, first, second, resolve, None, kinds_out, c.byref(occupied))
            assert occupied.value == result & 0xffffffff, (case, first, second, name)
            assert bytes(kinds_out) == board_bytes()[0], (case, name)
            count(name)
        memory = bytearray(rng.randbytes(0xf10))
        for i in range(65):
            struct.pack_into('<I', memory, SLOTS + 4 * i, rng.choice(pool) if rng.random() < 0.7 else 0)
        memory[MARKERS:MARKERS + 65] = rng.randbytes(65)
        memory[MARKERS:MARKERS + 65] = rng.randbytes(65)

        def fresh():
            cpu.mem_write(BOARD, bytes(memory))
            objects.clear()
            for handle in pool:
                data = bytearray(rng.randbytes(0x200))
                data[0x15c] = rng.choice([0, 1, 2, 3, 4, 5, 6, 7, 0xff, 0x80])
                cpu.mem_write(handle, bytes(data))
        for address, name in ((0x436850, 'checker0'), (0x4372c0, 'checker1'), (0x436fe0, 'stones'),
                              (0x437240, 'stones'), (0x436a10, 'kind'), (0x436aa0, 'power'), (0x439370, 'equal')):
            fresh()
            argument = rng.choice([0, 1, 2, 3, 4, 5, 6, 7, 0xff, 0xffffffff, 0xffffff80, 0x80])
            cpu.mem_write(BOARD + OUT, struct.pack('<I', 0xdead))
            wanted_value = rng.choice([0, 1, 5, 6, 0xffffffff, 0x80, 0xffffff80, rng.getrandbits(32)])
            cpu.mem_write(BOARD + OUT + 8, struct.pack('<I', wanted_value))
            cpu.mem_write(BOARD + OUT + 4, struct.pack('<I', wanted_value))
            if name == 'equal':
                original.call(address, eax=BOARD, edx=BOARD + OUT + 8, ebx=0)
            else:
                original.call(address, eax=BOARD, edx=argument, ebx=BOARD + OUT)
            snap, marks = board_bytes()
            kinds, expected = B65.from_buffer_copy(snap), B65()
            if name == 'checker0':
                n.vertrix_board_markers_checker(kinds, 0, expected)
            elif name == 'checker1':
                n.vertrix_board_markers_checker(kinds, 1, expected)
            elif name == 'stones':
                n.vertrix_board_markers_stones(kinds, expected)
            elif name == 'equal':
                wanted = struct.unpack('<i', bytes(cpu.mem_read(BOARD + OUT + 8, 4)))[0]
                n.vertrix_board_markers_equal(kinds, wanted, expected)
            elif name == 'kind':
                total = n.vertrix_board_markers_kind(kinds, argument, expected)
                assert total == struct.unpack('<I', bytes(cpu.mem_read(BOARD + OUT, 4)))[0], (case, argument)
            else:
                n.vertrix_board_markers_for_power(kinds, argument, expected)
            assert bytes(expected) == marks, (case, name, argument)
            count('marker_' + name)
    # 0x437b70 over a manual board + companions clear of the RNG buffer. The
    # draw below 48 is discarded by the original but advances RNG position.
    SBOARD, SCOMP = 0x807000, 0x809000
    COMP_STRIDE = 0x200
    n.vertrix_random_seed.argtypes = [c.POINTER(NativeRandom), c.c_uint32]
    s_rng = random.Random(0x437b70)
    companions = [SCOMP + i * COMP_STRIDE for i in range(8)]
    host_companions = {}
    for seed in (0, 0x12345678):
        state = NativeRandom()
        n.vertrix_random_seed(c.byref(state), seed)
        original.piece_seed(seed)
        for _ in range(args.cases // 2):
            board = bytearray(s_rng.getrandbits(8) for _ in range(0xd00))
            for row in range(13):
                for address in range(4 * row, 0x104, 0x34):
                    if s_rng.random() < 0.5:
                        handle = companions[s_rng.randrange(len(companions))]
                        struct.pack_into('<I', board, 0x87c + address, handle)
                    else:
                        struct.pack_into('<I', board, 0x87c + address, 0)
            for handle in companions:
                data = bytearray(s_rng.getrandbits(8) for _ in range(COMP_STRIDE))
                cpu.mem_write(handle, bytes(data))
                host_companions[handle] = c.create_string_buffer(bytes(data), COMP_STRIDE)
            cpu.mem_write(SBOARD, bytes(board))

            @Resolve
            def stamp_resolve(handle, storage, size, context):
                if handle not in host_companions:
                    return 0
                storage[0] = c.cast(host_companions[handle], c.c_void_p)
                size[0] = COMP_STRIDE
                return 1

            original.call(0x437b70, eax=SBOARD)
            host_board = c.create_string_buffer(bytes(board), 0xd00)
            assert n.vertrix_board_stamp_companions(host_board, 0xd00, c.byref(state),
                                                    stamp_resolve, None) == 1
            assert host_board.raw == bytes(cpu.mem_read(SBOARD, 0xd00)), 'stamp board'
            for handle in companions:
                assert host_companions[handle].raw == bytes(cpu.mem_read(handle, COMP_STRIDE)), \
                    handle
            assert struct.unpack('<H', cpu.mem_read(0x598d30 + 12, 2))[0] == state.position
            count('0x437b70')
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 4327e0, 432820, 432b10, 4328a0, 4375a0, 432840, 435e80, 435f30, 435fe0, 436030, 436070, 4360b0 and '
                       '436100, 436850, 4372c0, 436fe0, 437240, 436a10, 436aa0, 439370, 438830, 4388a0, 438910, 438d50, 439140 and 437b70 execute in the original; kind snapshots, marker grids, counts, found '
                       'cells and companion stamps compare, including unfound requests leaving outputs untouched.'}
    (build / 'board-markers-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
