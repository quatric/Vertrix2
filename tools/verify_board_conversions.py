"""Compare complete original board conversion routines with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path
from original import Original
from oracle_kit import Pool, Resolve, Stubs, build
U = c.c_uint32
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
Allocate = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_void_p)
Range = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_uint32), c.POINTER(c.c_uint32), c.c_void_p)
SIZE = 0xd00
GRID, COMPANION, MARKERS = 0x220, 0x87c, 0xb94


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', Allocate), ('draw', Draw), ('range', Range), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'board-conversions', ['board_conversions.c', 'block_factory.c', 'board_markers.c', 'board.c', 'board_cells.c', 'actor_storage.c', 'actor_fields.c', 'fixed_point.c', 'board_actions.c'])
    S = c.POINTER(Services)
    P, SZ, UP = c.c_void_p, c.c_size_t, c.POINTER(U)
    n.vertrix_board_replace_marked.argtypes = [P, SZ, U, S]
    n.vertrix_board_replace_marked_scaled.argtypes = [P, SZ, c.c_int32, S]
    n.vertrix_board_mirror_marked.argtypes = [P, SZ, S]
    n.vertrix_board_scatter_marked.argtypes = [P, SZ, P, S]
    n.vertrix_board_prime_companions.argtypes = [P, SZ, S]
    n.vertrix_board_split_marked.argtypes = [P, SZ, S]
    n.vertrix_piece_replace_children.argtypes = [P, SZ, UP, S]
    n.vertrix_boards_convert_random.argtypes = [P, SZ, P, SZ, U, U, U, S]
    n.vertrix_board_collapse_marked.argtypes = [P, SZ, S, UP]
    n.vertrix_board_pick_kinds.argtypes = [P, SZ, S, UP, UP]
    n.vertrix_board_spin_marked.argtypes = [P, SZ, S, UP]
    n.vertrix_board_set_motion.argtypes = [P, SZ, c.c_uint8, S]
    n.vertrix_board_swirl_marked.argtypes = [P, SZ, S]
    n.vertrix_boards_convert_counts.argtypes = [P, SZ, P, SZ, U, U, S]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x436720)
    pool = Pool(cpu, 12, SIZE)
    board, other = pool.handles[0], pool.handles[1]
    targets = pool.handles[2:
        ]
    draws, allocations, replay = [], [], {'draws': [], 'allocs': []}
    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            handle = targets[len(allocations) % len(targets)]
            allocations.append(handle)
            return handle
        draws.append(rng.randrange(edx & 0xffff))
        return draws[- 1]
    stubs = Stubs(cpu, handler)
    stubs.add(0x4ca000)
    stubs.add(0x4826c0)
    @ Draw
    def draw(divisor, context):
        value = replay['draws'].pop(0)
        assert value < divisor
        return value
    @ Allocate
    def allocate(size, context):
        return replay['allocs'].pop(0)
    @ Range
    def table_range(index, lo, hi, context):
        lo[0] = struct.unpack('<I', bytes(cpu.mem_read((0x53bcd0 + 8 * index) & 0xffffffff, 4)))[0]
        hi[0] = struct.unpack('<I', bytes(cpu.mem_read((0x53bcd4 + 8 * index) & 0xffffffff, 4)))[0]
        return 1
    services = Services(pool.resolve, allocate, draw, table_range, None)
    usable = [i for i in range(20) if (struct.unpack('<I', bytes(cpu.mem_read(0x53bcd4 + 8 * i, 4)))[0] - struct.unpack('<I', bytes(cpu.mem_read(0x53bcd0 + 8 * i, 4)))[0] + 1) & 0xffff]
    assert 6 in usable
    totals = {}
    def count(name):
        totals[name] = totals.get(name, 0) + 1
    def fresh(markers=False, full=False, piece=True, stone=False):
        def patch(handle, data):
            if handle in (board, other):
                for grid in (GRID, COMPANION):
                    for i in range(65):
                        fill = full or rng.random() < 0.5
                        struct.pack_into('<I', data, grid + 4 * i, rng.choice(targets) if fill else 0)
            if handle == board:
                struct.pack_into('<H', data, 0xe, rng.randrange(0, 200))
                struct.pack_into('<H', data, 0x16, rng.randrange(0, 200))
                struct.pack_into('<I', data, 0xa60, rng.choice(targets))
                for i in range(65):
                    data[MARKERS + i] = rng.choice([0, 0, 1, 1, 2, 3]) if markers else data[MARKERS + i]
            elif handle in targets:
                data[0x15c] = rng.choice(usable)
        pool.fill(rng, patch)
        draws.clear()
        allocations.clear()
        if piece:
            piece_handle = struct.unpack_from('<I', pool.buffers[board].raw, 0xa60)[0]
            bx = struct.unpack_from('<H', pool.buffers[board].raw, 0xe)[0]
            by = struct.unpack_from('<H', pool.buffers[board].raw, 0x16)[0]
            px = (bx + 24 * rng.randrange(- 1, 6) + rng.randrange(0, 24)) & 0xffff
            py = (by + rng.randrange(- 60, 340)) & 0xffff
            for buffer in (pool.buffers[piece_handle],):
                struct.pack_into('<H', buffer, 0xe, px)
                struct.pack_into('<H', buffer, 0x16, py)
            data = bytes(pool.buffers[piece_handle].raw)
            cpu.mem_write(piece_handle, data)
    def begin():
        replay['draws'] = list(draws)
        replay['allocs'] = list(allocations)
    totals = {}
    def count(name):
        totals[name] = totals.get(name, 0) + 1
    def fresh(markers=False, full=False, piece=True, stone=False):
        def patch(handle, data):
            if handle in (board, other):
                for grid in (GRID, COMPANION):
                    for i in range(65):
                        fill = full or rng.random() < 0.5
                        struct.pack_into('<I', data, grid + 4 * i, rng.choice(targets) if fill else 0)
            if handle == board:
                struct.pack_into('<H', data, 0xe, rng.randrange(0, 200))
                struct.pack_into('<H', data, 0x16, rng.randrange(0, 200))
                struct.pack_into('<I', data, 0xa60, rng.choice(targets))
                for i in range(65):
                    data[MARKERS + i] = rng.choice([0, 0, 1, 1, 2, 3]) if markers else data[MARKERS + i]
            elif handle in targets:
                data[0x15c] = rng.choice(usable)
        pool.fill(rng, patch)
        draws.clear()
        allocations.clear()
        if piece:
            piece_handle = struct.unpack_from('<I', pool.buffers[board].raw, 0xa60)[0]
            bx = struct.unpack_from('<H', pool.buffers[board].raw, 0xe)[0]
            by = struct.unpack_from('<H', pool.buffers[board].raw, 0x16)[0]
            px = (bx + 24 * rng.randrange(- 1, 6) + rng.randrange(0, 24)) & 0xffff
            py = (by + rng.randrange(- 60, 340)) & 0xffff
            for buffer in (pool.buffers[piece_handle],):
                struct.pack_into('<H', buffer, 0xe, px)
                struct.pack_into('<H', buffer, 0x16, py)
            data = bytes(pool.buffers[piece_handle].raw)
            cpu.mem_write(piece_handle, data)
    def begin():
        replay['draws'] = list(draws)
        replay['allocs'] = list(allocations)
    for case in range(args.cases):
        for name, address in (('0x436720', 0x436720), ('0x437060', 0x437060), ('0x437350', 0x437350)):
            fresh(markers=True, full=True, piece=False)
            index = rng.choice(usable)
            mode = rng.choice([6, - 2])
            if address == 0x436720:
                result = original.call(address, eax=board, edx=index)
            elif address == 0x437060:
                result = original.call(address, eax=board, edx=mode & 0xffffffff)
            else:
                result = original.call(address, eax=board)
            begin()
            b = pool.buffers[board]
            if address == 0x436720:
                ok = n.vertrix_board_replace_marked(b, SIZE, index, c.byref(services))
            elif address == 0x437060:
                ok = n.vertrix_board_replace_marked_scaled(b, SIZE, mode, c.byref(services))
            else:
                ok = n.vertrix_board_mirror_marked(b, SIZE, c.byref(services))
            assert ok == 1 and (result & 0xff) == 1, (case, name, ok, result)
            assert pool.same(), (case, name, pool.diff())
            assert not replay['draws'] and not replay['allocs'], (case, name)
            count(name)
# 437be0 : scatter, with the original angle table filled randomly
    table_bytes = rng.randbytes(0x20000)
    cpu.mem_write(0x59993c, table_bytes)
    angle_table = (c.c_uint16 * 0x10000).from_buffer_copy(table_bytes)
    for case in range(args.cases):
        fresh(markers=True, full=True, piece=False)
        try:
            result = original.call(0x437be0, eax=board) & 0xff
            faulted = False
        except Exception:
            faulted = True
        begin()
        b = pool.buffers[board]
        ok = n.vertrix_board_scatter_marked(b, SIZE, angle_table, c.byref(services))
        if faulted:
            count('0x437be0_fault')
            assert not ok, (case, 'fault')
            continue
        assert ok == result, (case, ok, result)
        assert pool.same(), (case, pool.diff())
        assert not replay['draws'], case
        count('0x437be0' if ok else '0x437be0_empty')
    for case in range(args.cases):
        fresh(piece=False)
        original.call(0x437b70, eax=board)
        begin()
        assert n.vertrix_board_prime_companions(pool.buffers[board], SIZE, c.byref(services)), case
        assert pool.same(), (case, pool.diff())
        assert not replay['draws'], case
        count('0x437b70')
    for case in range(args.cases):
        fresh(markers=True, full=True, piece=False)
        result = original.call(0x437d70, eax=board) & 0xff
        begin()
        ok = n.vertrix_board_split_marked(pool.buffers[board], SIZE, c.byref(services))
        assert ok == result, (case, ok, result)
        assert pool.same(), (case, pool.diff())
        assert not replay['draws'] and not replay['allocs'], case
        count('0x437d70' if ok else '0x437d70_empty')
    for case in range(args.cases):
# 4368e0 : the children of the active piece
        fresh(piece=False)
        piece_handle = struct.unpack_from('<I', pool.buffers[board].raw, 0xa60)[0]
        for slot in range(3):
            child = rng.choice(targets + [0, 0])
            struct.pack_into('<I', pool.buffers[piece_handle], 0x15c + 4 * slot, child)
        cpu.mem_write(piece_handle, bytes(pool.buffers[piece_handle].raw))
        kinds = [rng.choice(usable) for _ in range(3)]
        original.call(0x4368e0, eax=board, edx=kinds[0], ebx=kinds[1], ecx=kinds[2])
        begin()
        assert n.vertrix_piece_replace_children(pool.buffers[board], SIZE, (U * 3)(* kinds), c.byref(services)), case
        assert pool.same(), (case, pool.diff())
        assert not replay['draws'] and not replay['allocs'], case
        count('0x4368e0')
# 436b40 : counted conversions on two boards
        fresh(markers=True, full=True, piece=False)
        marks = bytes(rng.choice([0, 1, 1, 2]) for _ in range(65))
        pool.buffers[other][MARKERS: MARKERS + 65] = marks
        cpu.mem_write(other, bytes(pool.buffers[other].raw))
        first = sum(1 for m in pool.buffers[board].raw[MARKERS: MARKERS + 65] if m == 1)
        second = marks.count(1)
        count_first, count_second = rng.randrange(first + 1), rng.randrange(second + 1)
        original.call(0x436b40, eax=board, edx=other, ecx=count_first, args=(count_second,))
        begin()
        assert n.vertrix_boards_convert_counts(pool.buffers[board], SIZE, pool.buffers[other], SIZE, count_first, count_second, c.byref(services)), case
        assert pool.same(), (case, pool.diff())
        assert not replay['draws'] and not replay['allocs'], case
        count('0x436b40')
    for case in range(args.cases):
        fresh(markers=True, full=True, piece=False)
        marks = bytes(rng.choice([0, 1, 1, 2]) for _ in range(65))
        pool.buffers[other][MARKERS: MARKERS + 65] = marks
        cpu.mem_write(other, bytes(pool.buffers[other].raw))
        kind = rng.choice(usable)
        count_first, count_second = rng.randrange(6), rng.randrange(6)
        original.call(0x436d80, eax=board, edx=other, ebx=kind, ecx=count_second, args=(count_first,))
        begin()
        assert n.vertrix_boards_convert_random(pool.buffers[board], SIZE, pool.buffers[other], SIZE, kind, count_first, count_second, c.byref(services)), case
        assert pool.same(), (case, pool.diff())
        assert not replay['draws'] and not replay['allocs'], case
        count('0x436d80')
    for case in range(args.cases):
        fresh(markers=True, full=True, piece=False)
        if case % 4 == 0:
#one marker of each kind, with blocks that already stand on their destination cells:
#the first run of the original teaches the targets, which become the positions
            cells = rng.sample(range(65), 2)
            for k in range(65):
                pool.buffers[board][MARKERS + k] = 2 if k == cells[0] else 1 if k == cells[1] else 0
            cpu.mem_write(board, bytes(pool.buffers[board].raw))
            saved = {h: bytes(pool.buffers[h].raw) for h in pool.handles}
            original.call(0x438540, eax=board)
            for handle in targets:
                tx, ty = struct.unpack('<HH', bytes(cpu.mem_read(handle + 0x10, 4)))
                ty = struct.unpack('<H', bytes(cpu.mem_read(handle + 0x18, 2)))[0]
                buffer = pool.buffers[handle]
                struct.pack_into('<H', buffer, 0xe, tx)
                struct.pack_into('<H', buffer, 0x16, ty)
            for handle in pool.handles:
                if handle not in targets:
                    pool.buffers[handle].raw = saved[handle]
            for handle in targets:
                raw = bytearray(saved[handle])
                raw[0xe: 0x10] = bytes(pool.buffers[handle].raw[0xe: 0x10])
                raw[0x16: 0x18] = bytes(pool.buffers[handle].raw[0x16: 0x18])
                pool.buffers[handle].raw = bytes(raw)
            for handle in pool.handles:
                cpu.mem_write(handle, bytes(pool.buffers[handle].raw))
        elif case % 4 == 1:
            kind = rng.choice([1, 2])
            for k in range(65):
                if pool.buffers[board].raw[MARKERS + k] == kind:
                    pool.buffers[board][MARKERS + k] = 0
            cpu.mem_write(board, bytes(pool.buffers[board].raw))
        result = original.call(0x438540, eax=board) & 0xff
        moving = U()
        begin()
        assert n.vertrix_board_collapse_marked(pool.buffers[board], SIZE, c.byref(services), c.byref(moving)), case
        assert moving.value == result, (case, moving.value, result)
        assert pool.same(), (case, pool.diff())
        count('0x438540_%d_%s' % (case % 4, 'moving' if moving.value else 'settled'))
    for case in range(args.cases):
        fresh(full=rng.random() < 0.5, piece=False)
        out_array, out_count = 0xc00, 0xc30
        original.call(0x439260, eax=board, edx=other + out_array, ebx=other + out_count)
        begin()
        array = (U * 5).from_buffer(pool.buffers[other], out_array)
        counter = U.from_buffer(pool.buffers[other], out_count)
        assert n.vertrix_board_pick_kinds(pool.buffers[board], SIZE, c.byref(services), array, c.byref(counter)), case
#entries past the list length are stale stack words in the original : not defined
        snapshot = bytes(cpu.mem_read(board + 0x1de, 65))
        length = len({k for k in snapshot if k < 5})
        cpu.mem_write(other + out_array + 4 * length, bytes(4 * (5 - length)))
        assert pool.same(), (case, pool.diff())
        assert not replay['draws'], case
        count('0x439260')
    for case in range(args.cases):
        fresh(markers=True, full=True, piece=False)
        if case % 8 == 0:
            for k in range(65):
                pool.buffers[board][MARKERS + k] = 0
            cpu.mem_write(board, bytes(pool.buffers[board].raw))
        result = original.call(0x437fe0, eax=board) & 0xff
        begin()
        flag = U()
        assert n.vertrix_board_spin_marked(pool.buffers[board], SIZE, c.byref(services), c.byref(flag)), case
        assert flag.value == result, (case, flag.value, result)
        assert pool.same(), (case, pool.diff())
        assert not replay['draws'] and not replay['allocs'], case
        count('0x437fe0')
    for case in range(args.cases):
        fresh(markers=True, full=True, piece=False)
        if case % 8 == 0:
            for k in range(65):
                pool.buffers[board][MARKERS + k] = 0
            cpu.mem_write(board, bytes(pool.buffers[board].raw))
        result = original.call(0x4378c0, eax=board) & 0xff
        begin()
        ok = n.vertrix_board_swirl_marked(pool.buffers[board], SIZE, c.byref(services))
        assert ok == result, (case, ok, result)
        assert pool.same(), (case, pool.diff())
        assert not replay['draws'] and not replay['allocs'], case
        count('0x4378c0' if ok else '0x4378c0_empty')
    for case in range(args.cases):
        fresh(piece=False)
        mode = rng.choice([0, 1, 2, 3, 4, 5, 9, 0xff])
        original.call(0x438960, eax=board, edx=mode)
        begin()
        assert n.vertrix_board_set_motion(pool.buffers[board], SIZE, mode, c.byref(services)), case
        assert pool.same(), (case, mode, pool.diff())
        assert not replay['draws'] and not replay['allocs'], case
        count('0x438960')
    report = {'status': 'passed', 'complete_original_executions': totals, 'scope': 'Complete 436720, 437060, 437350 and 437be0 and 437b70 and 437d70, 4368e0, 436b40, 436d80, 438540, 439260, 437fe0, 4378c0 and 438960 execute in the original (operator new ' '4ca000 and the draw 4826c0 stubbed and replayed, recovered building blocks ' 'executed for real); returned values, whole boards and objects, and the ' 'draws and allocations consumed compare.'}
    (args.build_dir / 'board-conversions-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
