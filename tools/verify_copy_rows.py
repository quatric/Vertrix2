"""Compare the original row copy 0x4c9860 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, build

U = c.c_uint32
SIZE = 0x100


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'copy-rows', ['rtl_glue.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_rtl_copy_rows.argtypes = [c.POINTER(Services), U, U, U, U, c.c_int32, U]
    n.vertrix_rtl_copy_rows.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4c9860)
    pool = Pool(cpu, 6, SIZE)
    services = Services(pool.resolve)
    for case in range(args.cases):
        pool.fill(rng)
        src_array, dst_array, *rows = pool.handles
        for array in (src_array, dst_array):
            blob = struct.pack('<6I', *(rng.choice(rows) for _ in range(6))) + bytes(SIZE - 24)
            cpu.mem_write(array, blob)
            c.memmove(pool.buffers[array], blob, SIZE)
        count = rng.choice([0, 1, 2, 3, -1, rng.randrange(0, 3)])
        sidx, didx = rng.randrange(0, 3), rng.randrange(0, 3)
        size = rng.choice([0, 1, 2, 3, 4, 5, 7, 8, 13, 64, rng.randrange(0, 0x100)])
        original.call(0x4c9860, eax=src_array, edx=sidx, ebx=dst_array, ecx=didx,
                      args=(count & 0xffffffff, size))
        assert n.vertrix_rtl_copy_rows(c.byref(services), src_array, sidx, dst_array, didx, count,
                                       size), case
        assert pool.same(), (case, pool.diff())
    report = {'status': 'passed', 'complete_original_executions': {'0x4c9860': args.cases},
              'scope': 'The routine executes completely in the original over random pointer '
                       'arrays, row counts (including overlapping rows) and sizes; every pool '
                       'object compares. The original eax is scratch.'}
    (args.build_dir / 'copy-rows-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
