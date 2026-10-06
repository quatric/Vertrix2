"""Compare complete original board overlay routine with the native recovery."""
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
    n = build(args.build_dir, 'board-overlay', ['board_overlay.c', 'actor_style_storage.c', 'block_factory.c', 'board_markers.c', 'board.c', 'board_cells.c', 'actor_storage.c', 'actor_fields.c', 'random.c'])
    S = c.POINTER(Services)
    P, SZ, UP = c.c_void_p, c.c_size_t, c.POINTER(U)
    P, SZ = c.c_void_p, c.c_size_t
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x42ff50)
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
    Read = c.CFUNCTYPE(c.c_int, U, c.c_uint, c.POINTER(U), c.c_void_p)
    @ Read
    def read(address, width, value, context):
        value[0] = int.from_bytes(bytes(cpu.mem_read(address, width)), 'little')
        return 1
    n.vertrix_board_create_overlay.argtypes = [P, SZ, U, U, U, S, Read, c.c_void_p]
    n.vertrix_player_create_overlay.argtypes = [P, SZ, U, U, U, S, Read, c.c_void_p]
    totals = {}
    TABLE = 0x800100
    def begin():
        replay['draws'] = list(draws)
        replay['allocs'] = list(allocations)
    player = pool.handles[1]
    for case in range(args.cases):
        def patch(handle, data):
            if handle == board:
                struct.pack_into('<I', data, 0xce4, TABLE)
            if handle == player:
                struct.pack_into('<I', data, 0, rng.choice([0, 1, 2, 3]))
                struct.pack_into('<I', data, 0x15c, board)
            if handle == board:
                struct.pack_into('<I', data, 0xc, rng.getrandbits(32))
                struct.pack_into('<I', data, 0x14, rng.getrandbits(32))
                struct.pack_into('<H', data, 0xe, rng.getrandbits(16))
                struct.pack_into('<H', data, 0x16, rng.getrandbits(16))
        pool.fill(rng, patch)
        draws.clear()
        allocations.clear()
        cpu.mem_write(TABLE, bytes(rng.getrandbits(8) for _ in range(12)))
        variant, d0 = rng.choice([0, 1, 2]), rng.getrandbits(32)
        steps = struct.unpack('<I', bytes(cpu.mem_read(0x4f7cfc + 4 * struct.unpack('<I', bytes(cpu.mem_read(0x532bbc, 4)))[0], 4)))[0]
        original.call(0x42ff50, eax=board, edx=variant, ebx=d0)
        begin()
        ok = n.vertrix_board_create_overlay(pool.buffers[board], SIZE, variant, d0, steps, c.byref(services), read, None)
        assert ok == 1, case
        if not pool.same():
            h = int(pool.diff()[0], 16)
            a = bytes(pool.buffers[h].raw)
            b = bytes(cpu.mem_read(h, len(a)))
            print(hex(h), [(hex(i), a[i], b[i]) for i in range(len(a)) if a[i] != b[i]][: 20])
            raise SystemExit(1)
        assert not replay['allocs'], case
        totals['0x42ff50'] = totals.get('0x42ff50', 0) + 1
        pool.fill(rng, patch)
        draws.clear()
        allocations.clear()
        cpu.mem_write(TABLE, bytes(rng.getrandbits(8) for _ in range(12)))
        fallback = rng.getrandbits(32)
        table_d0 = struct.unpack('<I', bytes(cpu.mem_read(0x5347a0 + 4 * struct.unpack('<I', bytes(cpu.mem_read(0x532a70, 4)))[0], 4)))[0]
        original.call(0x43d2b0, eax=player, edx=fallback)
        begin()
        assert n.vertrix_player_create_overlay(pool.buffers[player], SIZE, fallback, table_d0, steps, c.byref(services), read, None) == 1, case
        assert pool.same(), (case, '0x43d2b0', pool.diff())
        totals['0x43d2b0'] = totals.get('0x43d2b0', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals, 'scope': 'Complete 42ff50 and 43d2b0 execute in the original (operator new 4ca000 stubbed and ' 'replayed, recovered building blocks executed for real); the whole board ' 'and every object compare.'}
    (args.build_dir / 'board-overlay-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
