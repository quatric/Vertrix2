"""Compare the original hash map iterator step 0x4df220 with the native recovery."""
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
NONE = 0xffffffff


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'map-iterate', ['node_pool.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_map_iterate.argtypes = [c.POINTER(Services), U, U, U, U]
    n.vertrix_map_iterate.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4df220)
    pool = Pool(cpu, 8, SIZE)
    services = Services(pool.resolve)
    totals = {}

    def write(handle, blob):
        cpu.mem_write(handle, blob)
        c.memmove(pool.buffers[handle], blob, len(blob))

    for case in range(args.cases):
        pool.fill(rng)
        owner, array, cursor, key_out, value_out, *nodes = pool.handles
        count = rng.randrange(1, 7)
        write(owner, struct.pack('<IIII', rng.getrandbits(32), array, count, rng.getrandbits(32)))
        buckets = [rng.choice([0, 0] + nodes) for _ in range(count)]
        write(array, struct.pack('<%dI' % count, *buckets))
        for node in nodes:
            write(node, struct.pack('<IIII', rng.choice(nodes + [0, 0]), rng.randrange(0, count + 2),
                                    rng.getrandbits(32), rng.getrandbits(32)))
        start = rng.choice([NONE, NONE] + nodes)
        if start == NONE and not any(buckets):
            continue
        write(cursor, struct.pack('<I', start))
        original.call(0x4df220, eax=owner, edx=cursor, ebx=key_out, ecx=value_out)
        assert n.vertrix_map_iterate(c.byref(services), owner, cursor, key_out, value_out), case
        assert pool.same(), (case, pool.diff())
        key = 'first' if start == NONE else 'next'
        totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4df220': totals},
              'scope': 'The routine executes completely in the original over random bucket '
                       'arrays and chains; the cursor cell and both outputs compare through the '
                       'pool.'}
    (args.build_dir / 'map-iterate-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
