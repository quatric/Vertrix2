"""Compare the original print format specification parser 0x4df6c8 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, build

U = c.c_uint32
SIZE = 0x200
ALPHABET = b'-#+ 0*.123456789hlwNFIL64xdsa%'


class Services(c.Structure):
    _fields_ = [('resolve', c.c_void_p), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=8192)
    args = parser.parse_args()
    n = build(args.build_dir, 'format-spec',
              ['format_spec.c', 'rtl_glue.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_format_spec.argtypes = [c.POINTER(Services), U, U, U, c.POINTER(U)]
    n.vertrix_format_spec.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4df6c8)
    pool = Pool(cpu, 4, SIZE)
    text, cell, arguments, spec = pool.handles
    services = Services(c.cast(pool.resolve, c.c_void_p))
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        body = bytes(rng.choice(ALPHABET) for _ in range(rng.randrange(0, 14))) + b'\0'
        words = [rng.choice([0, 1, 5, 12, 100, 0xffffffff, 0xfffffff0, 0x80000000, rng.getrandbits(32)])
                 for _ in range(4)]
        for handle, data in ((text, body), (cell, struct.pack('<I', arguments)),
                             (arguments, struct.pack('<4I', *words))):
            blob = bytearray(cpu.mem_read(handle, SIZE))
            blob[:len(data)] = data
            cpu.mem_write(handle, bytes(blob))
            c.memmove(pool.buffers[handle], bytes(blob), SIZE)
        want = original.call(0x4df6c8, eax=text, edx=cell, ebx=spec) & 0xffffffff
        result = U()
        assert n.vertrix_format_spec(c.byref(services), text, cell, spec, c.byref(result)), case
        assert result.value == want, (case, body, result.value, want)
        assert pool.same(), (case, body, pool.diff())
        key = (want - text)
        totals[min(key, 8)] = totals.get(min(key, 8), 0) + 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4df6c8': args.cases},
              'consumed': {str(k): v for k, v in sorted(totals.items())},
              'scope': 'The routine executes completely in the original (0x4df81c included); '
                       'the returned text position, the specification record and the argument '
                       'pointer compare.'}
    (args.build_dir / 'format-spec-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
