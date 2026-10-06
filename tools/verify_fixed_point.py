"""Compare complete original fixed-point and angle routines with the native recovery."""
import argparse, ctypes as c, json, random
from pathlib import Path
from original import Original
from oracle_kit import build
TABLE = 0x59993c
U16, I32, U32 = c.c_uint16, c.c_int32, c.c_uint32


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=8192)
    args = parser.parse_args()
    n = build(args.build_dir, 'fixed-point', ['fixed_point.c'])
    P = c.POINTER(c.c_int)
    n.vertrix_fixed_multiply.argtypes = [I32, I32]
    n.vertrix_fixed_multiply.restype = I32
    n.vertrix_fixed_divide.argtypes = [I32, I32, P]
    n.vertrix_fixed_divide.restype = I32
    n.vertrix_integer_root.argtypes = [U32, P]
    n.vertrix_integer_root.restype = U32
    n.vertrix_point_distance.argtypes = [U16] * 4 + [P]
    n.vertrix_point_distance.restype = U32
    n.vertrix_angle_from_ratio.argtypes = [c.c_void_p, I32]
    n.vertrix_angle_from_ratio.restype = U32
    n.vertrix_point_heading.argtypes = [c.c_void_p] + [U16] * 4 + [P]
    n.vertrix_point_heading.restype = U16
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4849e0)
    raw = rng.randbytes(0x20000)
    cpu.mem_write(TABLE, raw)
    table = (U16 * 0x10000).from_buffer_copy(raw)
    totals, skipped = {}, {}


def count(name):
    totals[name] = totals.get(name, 0) + 1
    def number():
        return rng.choice([0, 1, 2, 3, 0xffff, 0x10000, 0x7fffffff, 0x80000000, 0xffffffff, rng.getrandbits(32), rng.getrandbits(16), rng.getrandbits(8), (- rng.getrandbits(16)) & 0xffffffff])
        def small():
            return rng.choice([0, 1, 0xffff, 0x8000, 0x7fff, rng.getrandbits(16), rng.randrange(0, 40), (- rng.randrange(1, 40)) & 0xffff])
            def run(address, ** registers):
                try:
                    return original.call(address, ** registers)
                except Exception:
                    return None
    def signed(v):
        return v - (1 << 32) if v & 0x80000000 else v
    for case in range(args.cases):
        a, b = number(), number()
        result = original.call(0x4849e0, eax=a, edx=b)
        assert n.vertrix_fixed_multiply(signed(a), signed(b)) & 0xffffffff == result, case
        count('fixed_multiply')
        result = run(0x4849f0, eax=a, edx=b)
        valid = c.c_int()
        got = n.vertrix_fixed_divide(signed(a), signed(b), c.byref(valid))
        if result is None:
            assert not valid.value, ('divide fault', case)
            skipped['fixed_divide'] = skipped.get('fixed_divide', 0) + 1
        else:
            assert valid.value and got & 0xffffffff == result, case
            count('fixed_divide')
        value = number()
        for address in (0x484630,):
            result = run(address, eax=value)
            got = n.vertrix_integer_root(value, c.byref(valid))
            if result is None:
                assert not valid.value
                skipped['integer_root'] = skipped.get('integer_root', 0) + 1
            else:
                assert valid.value and got == result, (case, hex(value))
                count('integer_root')
                x1, y1, x2, y2 = small(), small(), small(), small()
                result = run(0x484680, eax=x1 | rng.getrandbits(16) << 16, edx=y1 | rng.getrandbits(16) << 16, ebx=x2 | rng.getrandbits(16) << 16, ecx=y2 | rng.getrandbits(16) << 16)
                got = n.vertrix_point_distance(x1, y1, x2, y2, c.byref(valid))
                if result is None:
                    assert not valid.value
                    skipped['point_distance'] = skipped.get('point_distance', 0) + 1
                else:
                    assert valid.value and got == result, (case, 'distance')
                    count('point_distance')
                    ratio = rng.choice([number(), rng.randrange(- 70000, 70000) & 0xffffffff, rng.getrandbits(17)])
                    result = original.call(0x4845d0, eax=ratio)
                    assert n.vertrix_angle_from_ratio(table, signed(ratio)) == result, (case, hex(ratio))
                    count('angle_from_ratio')
                    result = run(0x484700, eax=x1 | rng.getrandbits(16) << 16, edx=y1 | rng.getrandbits(16) << 16, ebx=x2 | rng.getrandbits(16) << 16, ecx=y2 | rng.getrandbits(16) << 16)
                    got = n.vertrix_point_heading(table, x1, y1, x2, y2, c.byref(valid))
                    if result is None:
                        assert not valid.value
                        skipped['point_heading'] = skipped.get('point_heading', 0) + 1
                    else:
                        assert valid.value and got == result & 0xffff, (case, 'heading')
                        count('point_heading')
    report = {'status': 'passed', 'complete_original_executions': totals, 'faulting_original_cases_matched_as_invalid': skipped, 'scope': 'Complete 4849e0, 4849f0, 484630, 484680, 4845d0 and 484700 execute in the original ' 'over random inputs and a random 65536-word table; results compare (only the low ' '16 bits of the heading, as the original leaves the rest undefined). Original ' 'scratch globals (0x598db4..0x598df8) are dead temporaries and are not reproduced.'}
    (args.build_dir / 'fixed-point-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
