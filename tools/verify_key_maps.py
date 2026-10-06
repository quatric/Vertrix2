"""Compare the complete original key binding installers with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import Pool, build

SIZE = 0x300
ADDRESSES = (0x43f550, 0x43f630, 0x43f710, 0x43f7f0, 0x43f8d0, 0x43f9b0, 0x43fa90, 0x43fb70)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=512)
    args = parser.parse_args()
    n = build(args.build_dir, 'key-maps', ['key_maps.c', 'object_dwords.c', 'actor_storage.c'])
    n.vertrix_key_binding_apply.argtypes = [c.c_void_p, c.c_size_t, c.c_uint]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43f550)
    pool = Pool(cpu, 1, SIZE)
    obj = pool.handles[0]
    totals = {}
    for case in range(args.cases):
        for
        set_index,
            address in enumerate(ADDRESSES)
            : pool.fill(rng) original.call(address, eax = obj) assert n
                  .vertrix_key_binding_apply(pool.buffers[obj], SIZE, set_index) assert pool.same(),
        (case, hex(address), pool.diff())totals[hex(
            address)] = totals.get(hex(address), 0) +
                        1 pool.fill(rng) before = pool.buffers[obj]
                                                      .raw assert not n
                                                      .vertrix_key_binding_apply(
                                                          pool.buffers[obj], SIZE, 8) assert not n
                                                      .vertrix_key_binding_apply(
                                                          pool.buffers[obj], 0x207, 0) assert pool
                                                      .buffers[obj]
                                                      .raw
                                                  == before report = {
            'status' : 'passed',
            'complete_original_executions' : totals,
            'scope' :
                'Complete 43f550, 43f630, 43f710, 43f7f0, 43f8d0, 43f9b0, 43fa90 and ' '43fb70 execute in the original (the recovered setter 48abf0 runs for ' 'real); the whole input object compares.'
        }(args.build_dir / 'key-maps-verification.json')
                                                                         .write_text(
                                                                             json.dumps(report,
                                                                                        indent =
                                                                                            2) +
                                                                             '\n')
                                                                             print(json.dumps(
                                                                                 report,
                                                                                 indent = 2))

                                                                                 if __name__
                                                                     == '__main__' : main()
