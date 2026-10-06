"""Compare the original client area hit test 0x4b4270 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, build

U = c.c_uint32


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'object-bounds', ['object_bounds.c', 'actor_storage.c'])
    n.vertrix_object_contains_point.argtypes = [c.POINTER(Services), U, c.c_int32, c.c_int32]
    n.vertrix_object_contains_point.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4b4270)
    pool = Pool(cpu, 6, 0x200)
    services = Services(pool.resolve)
    totals, inside = {}, 0

    def patch(handle, data):
        for offset in (0x17c, 0x180, 0xb4):
            struct.pack_into('<I', data, offset, rng.choice(pool.handles))
        for offset in (0xc, 0x14):
            struct.pack_into('<i', data, offset, rng.randrange(-20, 60) << 16 | rng.randrange(0x10000))
        for offset in (0x4, 0xf4, 0xf8):
            struct.pack_into('<i', data, offset, rng.randrange(-5, 120))

    for case in range(args.cases):
        pool.fill(rng, patch)
        handle = rng.choice(pool.handles)
        x, y = rng.randrange(-60, 160), rng.randrange(-60, 160)
        result = original.call(0x4b4270, eax=handle, edx=x & 0xffffffff, ebx=y & 0xffffffff)
        got = n.vertrix_object_contains_point(c.byref(services), handle, x, y)
        assert got == result & 0xffffffff, (case, got, result)
        assert pool.same(), case
        inside += got
        totals['0x4b4270'] = totals.get('0x4b4270', 0) + 1
    assert inside, 'no case landed inside'
    report = {'status': 'passed', 'complete_original_executions': totals, 'inside_cases': inside,
              'scope': 'The original executes completely over pools of linked objects with small '
                       'positions, extents and insets; the hit result and all objects compare.'}
    (args.build_dir / 'object-bounds-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
