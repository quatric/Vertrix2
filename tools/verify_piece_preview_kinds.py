"""Compare original 0x43a4f0 (preview kind store) with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import Pool, build

U = c.c_uint32
SIZE = 0x200
OFFSET = 0x168


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'piece-preview-kinds',
              ['piece_children.c', 'actor_storage.c', 'actor_fields.c'])
    n.vertrix_piece_store_preview_kinds.argtypes = [c.c_void_p, c.c_size_t, c.c_uint8, c.c_uint8,
                                                    c.c_uint8]
    n.vertrix_piece_store_preview_kinds.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43a4f0)
    pool = Pool(cpu, 4, SIZE)
    piece = pool.handles[0]
    totals = {'0x43a4f0': 0}
    for case in range(args.cases):
        kinds = [rng.getrandbits(8) for _ in range(3)]
        pool.fill(rng)
        original.call(0x43a4f0, eax=piece, edx=kinds[0], ebx=kinds[1], ecx=kinds[2])
        assert n.vertrix_piece_store_preview_kinds(pool.buffers[piece], SIZE, kinds[0], kinds[1],
                                                   kinds[2]) == 1, case
        assert pool.same(), (case, pool.diff())
        totals['0x43a4f0'] += 1
    short = c.create_string_buffer(b'\xaa' * OFFSET, OFFSET)
    assert not n.vertrix_piece_store_preview_kinds(short, OFFSET, 1, 2, 3)
    assert short.raw == b'\xaa' * OFFSET
    report = {'status':
        'passed', 'complete_original_executions' : totals,
                                                   'scope'
            : 'Complete 43a4f0 executes in the original over random piece storage; ' 'whole objects compare, plus a short-storage preservation check.'
        }
        (args.build_dir / 'piece-preview-kinds-verification.json')
                .write_text(json.dumps(report, indent = 2) + '\n')
                    print(json.dumps(report, indent = 2))

                        if __name__ == '__main__' : main()
