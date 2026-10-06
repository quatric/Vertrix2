"""Compare the original case-insensitive text comparison 0x489d00 with the native recovery."""
import argparse
import ctypes as c
import json
import random
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
    n = build(args.build_dir, 'text-equal', ['rtl_glue.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_rtl_text_equal.argtypes = [c.POINTER(Services), U, U, c.POINTER(U)]
    n.vertrix_rtl_text_equal.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x489d00)
    pool = Pool(cpu, 4, SIZE)
    services = Services(pool.resolve)
    alphabet = b'aAbBzZ`{@[ 09'
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        first, second = rng.sample(pool.handles, 2)
        length = rng.choice([0, 1, 2, 3, rng.randrange(0, 20)])
        text = bytes(rng.choice(alphabet) for _ in range(length))
        other = bytearray(text if rng.random() < 0.7 else
                          bytes(rng.choice(alphabet) for _ in range(length + rng.choice([0, 0, 1]))))
        for i in range(len(other)):
            if rng.random() < 0.5 and i < len(text):
                other[i] = text[i] ^ rng.choice([0, 0x20, 0x20, 1])
        for handle, data in ((first, text), (second, bytes(other))):
            blob = data + b'\0' + bytes(rng.choice(alphabet) for _ in range(SIZE - len(data) - 1))
            cpu.mem_write(handle, blob)
            c.memmove(pool.buffers[handle], blob, SIZE)
        result = original.call(0x489d00, eax=first, edx=second) & 0xffffffff
        out = U()
        assert n.vertrix_rtl_text_equal(c.byref(services), first, second, c.byref(out))
        assert out.value == result, (case, text, bytes(other), out.value, result)
        assert pool.same(), pool.diff()
        totals[result] = totals.get(result, 0) + 1
    assert totals.get(0, 0) > 20 and totals.get(1, 0) > 20, totals
    report = {'status': 'passed', 'complete_original_executions': {'0x489d00': args.cases},
              'results': {str(k): v for k, v in totals.items()},
              'scope': 'The routine executes completely in the original (0x4dabb0 unstubbed) over '
                       'random strings including last character mismatches; the result compares.'}
    (args.build_dir / 'text-equal-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
