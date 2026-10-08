"""Compare the original distance search 0x433550 with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, build

U = c.c_uint32
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
Allocate = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_void_p)
Range = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_uint32), c.POINTER(c.c_uint32), c.c_void_p)
SIZE = 0xd00
GRID, MODE = 0x220, 0x839


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', Allocate), ('draw', Draw), ('range', Range),
                ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'board-reach',
              ['board_conversions.c', 'block_factory.c', 'call_glue.c', 'board_markers.c', 'board.c',
               'board_cells.c', 'actor_storage.c', 'actor_fields.c', 'fixed_point.c',
               'board_actions.c', 'random.c'])
    n.vertrix_board_marker_reach.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(Services),
                                             c.POINTER(U)]
    original = Original(args.executable)
    pool = Pool(original.cpu, 8, SIZE)
    board = pool.handles[0]
    targets = pool.handles[1:]
    services = Services(pool.resolve, Allocate(lambda s, c_: 0), Draw(lambda d, c_: 0),
                        Range(lambda i, a, b, c_: 0), None)
    totals = {}
    for case in range(args.cases):
        density = random.Random(case).choice([0.02, 0.1, 0.5, 1.0])
        rng = random.Random(0x433550 + case)

        def patch(handle, data):
            if handle == board:
                for i in range(65):
                    data[GRID + 4 * i:GRID + 4 * i + 4] = (
                        rng.choice(targets) if rng.random() < density else 0).to_bytes(4, 'little')
                data[MODE] = rng.choice([0, 1, 2, 3, 4, 4, 5])
            else:
                data[0x15c] = rng.choice([0, 1, 5, 6, 6, 6, 0xff])
        pool.fill(rng, patch)
        result = original.call(0x433550, eax=board) & 0xff
        reach = U()
        assert n.vertrix_board_marker_reach(pool.buffers[board], SIZE, c.byref(services),
                                            c.byref(reach)), case
        assert reach.value == result, (case, reach.value, result)
        assert pool.same(), (case, pool.diff())
        key = 'mode_%d' % pool.buffers[board].raw[MODE]
        totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 433550 executes in the original over random boards, kinds and '
                       'mode bytes; the result, the board (kind snapshot included) and every '
                       'object compare.'}
    (args.build_dir / 'board-reach-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
