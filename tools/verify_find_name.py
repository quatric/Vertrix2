"""Compare the original name search 0x487fd0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, build

U = c.c_uint32
SIZE = 0x40


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'find-name', ['list_text.c', 'rtl_glue.c', 'call_glue.c',
                                            'actor_storage.c'])
    n.vertrix_list_find_name.argtypes = [c.POINTER(Services), U, U, c.POINTER(U)]
    n.vertrix_list_find_name.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x487fd0)
    pool = Pool(cpu, 8, SIZE)
    services = Services(pool.resolve)
    alphabet = b'aAbBz'
    totals = {}

    def write(handle, blob):
        cpu.mem_write(handle, blob)
        c.memmove(pool.buffers[handle], blob, len(blob))

    for case in range(args.cases):
        pool.fill(rng)
        lst, array, query, *names = pool.handles
        names = names[:5]
        for handle in [query] + names:
            length = rng.randrange(0, 4)
            write(handle, bytes(rng.choice(alphabet) for _ in range(length)) + b'\0' * (SIZE - length))
        count = rng.randrange(0, 5)
        entries = [rng.choice(names + [0]) for _ in range(count)]
        write(array, struct.pack('<%dI' % count, *entries) + bytes(SIZE - 4 * count))
        data = bytearray(rng.randbytes(SIZE))
        struct.pack_into('<I', data, 0x14, count)
        struct.pack_into('<I', data, 0x20, array)
        write(lst, bytes(data))
        result = original.call(0x487fd0, eax=lst, edx=query) & 0xffffffff
        out = U()
        assert n.vertrix_list_find_name(c.byref(services), lst, query, c.byref(out))
        assert out.value == result, (case, hex(out.value), hex(result))
        assert pool.same(), pool.diff()
        key = 'found' if result != 0xffffffff else 'missing'
        totals[key] = totals.get(key, 0) + 1
    assert totals.get('found', 0) > 50 and totals.get('missing', 0) > 50, totals
    report = {'status': 'passed', 'complete_original_executions': {'0x487fd0': args.cases},
              'results': totals,
              'scope': 'The routine executes completely in the original (0x489d00 unstubbed); the '
                       'returned index compares over random name arrays.'}
    (args.build_dir / 'find-name-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
