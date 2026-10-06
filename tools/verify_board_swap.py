"""Compare the original marked block swap 0x436150 with the native recovery."""
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
GRID, COMPANION, MARKERS, CLASSES = 0x220, 0x87c, 0xb94, 0x53bcc8


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', Allocate), ('draw', Draw), ('range', Range),
                ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'board-swap',
              ['board_conversions.c', 'block_factory.c', 'board_markers.c', 'board.c',
               'board_cells.c', 'actor_storage.c', 'actor_fields.c', 'fixed_point.c',
               'board_actions.c'])
    n.vertrix_board_swap_marked.argtypes = [c.c_void_p, c.c_size_t, c.c_char_p, c.c_size_t,
                                            c.POINTER(Services), c.POINTER(U)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x436150)
    pool = Pool(cpu, 12, SIZE)
    board = pool.handles[0]
    targets = pool.handles[1:]
    draws, allocations = [], []
    replay = {'draws': [], 'allocs': []}

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            handle = targets[len(allocations) % len(targets)]
            allocations.append(handle)
            return handle
        draws.append(rng.randrange(edx & 0xffff))
        return draws[-1]

    stubs = Stubs(cpu, handler)
    stubs.add(0x4ca000)
    stubs.add(0x4826c0)

    @Draw
    def draw(divisor, context):
        value = replay['draws'].pop(0)
        assert value < divisor
        return value

    @Allocate
    def allocate(size, context):
        return replay['allocs'].pop(0)

    @Range
    def table_range(index, lo, hi, context):
        lo[0] = struct.unpack('<I', bytes(cpu.mem_read((0x53bcd0 + 8 * index) & 0xffffffff, 4)))[0]
        hi[0] = struct.unpack('<I', bytes(cpu.mem_read((0x53bcd4 + 8 * index) & 0xffffffff, 4)))[0]
        return 1

    services = Services(pool.resolve, allocate, draw, table_range, None)
    usable = [i for i in range(7)
              if (struct.unpack('<I', bytes(cpu.mem_read(0x53bcd4 + 8 * i, 4)))[0]
                  - struct.unpack('<I', bytes(cpu.mem_read(0x53bcd0 + 8 * i, 4)))[0] + 1)
              & 0xffff]
    totals = {}
    for case in range(args.cases):
        classes = bytes(rng.randrange(0, 3) for _ in range(8))
        cpu.mem_write(CLASSES, classes)

        def patch(handle, data):
            if handle == board:
                # the original dereferences the block of every marked cell: keep them present
                for i in range(65):
                    struct.pack_into('<I', data, GRID + 4 * i, rng.choice(targets))
                    struct.pack_into('<I', data, COMPANION + 4 * i,
                                     rng.choice(targets) if rng.random() < 0.7 else 0)
                density = rng.choice([0.0, 0.02, 0.1, 0.5])
                for i in range(65):
                    data[MARKERS + i] = rng.choice([1, 2]) if rng.random() < density else 0
            else:
                data[0x15c] = rng.choice(usable)
        pool.fill(rng, patch)
        draws.clear()
        allocations.clear()
        result = original.call(0x436150, eax=board) & 0xff
        replay['draws'] = list(draws)
        replay['allocs'] = list(allocations)
        swapped = U()
        assert n.vertrix_board_swap_marked(pool.buffers[board], SIZE, classes, len(classes),
                                           c.byref(services), c.byref(swapped)), case
        assert swapped.value == result, (case, swapped.value, result)
        assert pool.same(), (case, pool.diff())
        assert not replay['draws'] and not replay['allocs'], case
        key = 'swapped' if result else 'skipped'
        totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 436150 executes in the original (operator new 4ca000 and the draw '
                       '4826c0 stubbed and replayed); the result, the board and every object '
                       'compare.'}
    (args.build_dir / 'board-swap-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
