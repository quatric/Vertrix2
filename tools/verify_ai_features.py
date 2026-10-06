"""Compare complete original computer-player evaluation helpers with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path
from original import Original
from oracle_kit import Pool, build
U = c.c_uint32
BASE = 0x80c000


class Grid(c.Structure):
    _fields_ = [('cells', U * 28), ('values', U * 28), ('first', c.c_uint8 * 28), ('second', c.c_uint8 * 28)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=8192)
    args = parser.parse_args()
    n = build(args.build_dir, 'ai-features', ['ai_features.c'])
    B = c.c_uint8
    n.vertrix_ai_row_reach.argtypes = [B * 65, U, U, B * 5]
    n.vertrix_ai_features.argtypes = [U] * 7 + [B * 0x27]
    n.vertrix_ai_mode_flags.argtypes = [U, U, B * 0x2f]
    n.vertrix_ai_choice_scores.argtypes = [c.POINTER(Grid), U, B * 7]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4261b0)
    pool = Pool(cpu, 6, 0x1000)
    totals = {}
    def count(name):
        totals[name] = totals.get(name, 0) + 1
    def small():
        return rng.choice([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0x7fffffff, 0xffffffff, 0x80000000, rng.getrandbits(32)])
    for case in range(args.cases):
# 4261b0 : row reach
        cells = bytes(rng.choice([0xff, 0xff, 0, 1, 2, 3, 5, 6]) for _ in range(65))
        start, row = rng.randrange(6), rng.randrange(13)
        cpu.mem_write(BASE, cells)
        cpu.mem_write(BASE + 0x100, bytes([0xaa] * 8))
        original.call(0x4261b0, edx=BASE, ebx=BASE + 0x100, ecx=start, args=(row,))
        out = (B * 5)()
        assert n.vertrix_ai_row_reach((B * 65).from_buffer_copy(cells), start, row, out)
        assert bytes(out) == bytes(cpu.mem_read(BASE + 0x100, 5)), (case, start, row)
        assert bytes(cpu.mem_read(BASE + 0x105, 3)) == bytes([0xaa] * 3), case
        count('row_reach')
# 427c10 : features
        a, b, cc, d, e, f, g = [small() for _ in range(7)]
        if rng.random() < 0.5:
            a, g = rng.randrange(12), rng.randrange(12)
            b = rng.randrange(12)
            cc, d = rng.randrange(8), rng.randrange(8)
            e, f = rng.randrange(40), rng.randrange(40)
        data = bytes(rng.randrange(256) for _ in range(0x27))
        cpu.mem_write(BASE + 0x200, data)
        original.call(0x427c10, edx=a, ebx=b, ecx=cc, args=(d, e, f, g, BASE + 0x200))
        out = (B * 0x27).from_buffer_copy(data)
        n.vertrix_ai_features(a, b, cc, d, e, f, g, out)
        assert bytes(out) == bytes(cpu.mem_read(BASE + 0x200, 0x27)), (case, a, b, cc, d, e, f, g)
        count('features')
# 427e10 : mode flags
        def patch(handle, data):
            struct.pack_into('<I', data, 0x4c8, rng.choice([rng.randrange(0x20, 0x38), rng.randrange(0x20, 0x38), rng.getrandbits(32)]))
            struct.pack_into('<I', data, 0x3b0, rng.choice(pool.handles))
        pool.fill(rng, patch)
        player = pool.handles[0]
        own = struct.unpack_from('<I', pool.buffers[player].raw, 0x4c8)[0]
        opponent = struct.unpack_from('<I', pool.buffers[player].raw, 0x3b0)[0]
        opponent_mode = struct.unpack_from('<I', pool.buffers[opponent].raw, 0x4c8)[0]
        data = bytes(rng.randrange(256) for _ in range(0x30))
        cpu.mem_write(BASE + 0x300, data)
        original.call(0x427e10, edx=player, ebx=BASE + 0x300)
        flags = (B * 0x2f).from_buffer_copy(data[: 0x2f])
        n.vertrix_ai_mode_flags(own, opponent_mode, flags)
        assert bytes(flags) == bytes(cpu.mem_read(BASE + 0x300, 0x2f)), case
        assert data[0x2f] == cpu.mem_read(BASE + 0x32f, 1)[0], case
        assert pool.same(), case
        count('mode_flags')
# 428e70 : choice grid scores
        grid = Grid()
        for i in range(28):
            grid.values[i] = rng.choice([0, 1, 1, 2, 0xffffffff])
            grid.first[i] = rng.choice([0, 1, 5, 127, 128, 200, 255, rng.randrange(256)])
        if rng.random() < 0.2:
            for i in range(28):
                grid.values[i] = 0
        mode = rng.choice([0, 1, 2, 3, 4, 0xffffffff])
        cpu.mem_write(BASE + 0x400, bytes(grid.values))
        cpu.mem_write(BASE + 0x500, bytes(grid.first))
        cpu.mem_write(BASE + 0x600, bytes([0xaa] * 8))
        result = original.call(0x428e70, edx=BASE + 0x500, ebx=BASE + 0x600, ecx=BASE + 0x400, args=(mode,))
        scores = (B * 8)(* [0xaa] * 8)
        found = n.vertrix_ai_choice_scores(c.byref(grid), mode, c.cast(scores, c.POINTER(B * 7)).contents)
        assert found == result & 0xffffffff, case
        assert bytes(scores) == bytes(cpu.mem_read(BASE + 0x600, 8)), (case, mode)
        count('choice_scores')
    report = {'status': 'passed', 'complete_original_executions': totals, 'scope': 'Complete 4261b0, 427c10, 427e10 and 428e70 execute in the original (the ' 'fill routine 4eb5c0 runs for real); outputs, results and untouched bytes ' 'compare, including both players of 427e10 and every pool object.'}
    (args.build_dir / 'ai-features-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
