"""Compare the original region comparison 0x427ae0 and its verdict wrapper 0x43ab80 with the native
recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x800


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(14)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


CALLEES = {0x432820: 0, 0x428110: 0, 0x427c10: 5, 0x428610: 0}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'regions', ['object_glue.c', 'call_glue.c', 'actor_storage.c', 'table_queries.c'])
    n.vertrix_object_compare_regions.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U,
                                                 U, c.c_char_p, c.c_char_p]
    n.vertrix_object_compare_regions.restype = U
    n.vertrix_object_region_verdict.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U,
                                                c.c_char_p, c.c_char_p]
    n.vertrix_object_region_verdict.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x427ae0)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay, picked = [], [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        returns.append(rng.choice([rng.randrange(0, 9), rng.getrandbits(32)])
                       if address == 0x428610 else rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) +
                          (s.stack, s.stack_next, s.stack_third, s.rest0, s.rest1)[:CALLEES[s.target]])
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    count = 0
    verdicts = {}
    for case in range(args.cases):
        def patch(handle, data):
            struct.pack_into('<I', data, 0x3b0, rng.choice(pool.handles))
            struct.pack_into('<I', data, 0x15c, rng.choice(pool.handles))

        pool.fill(rng, patch)
        obj, second = rng.choice(pool.handles), rng.choice(pool.handles)
        ebx = rng.getrandbits(32)
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x427ae0, eax=obj, edx=second, ebx=ebx) & 0xffffffff
        replay[:] = list(returns)
        first_copy, second_copy = c.create_string_buffer(0x41), c.create_string_buffer(0x41)
        got = n.vertrix_object_compare_regions(c.byref(calls), c.byref(services), STACK - 4, obj,
                                               second, ebx, first_copy, second_copy)
        assert first_copy.raw == bytes(cpu.mem_read(STACK - 4 - 0xa4, 0x41))
        assert second_copy.raw == bytes(cpu.mem_read(STACK - 4 - 0x60, 0x41))
        assert got == result, (hex(got), hex(result))
        assert native_log == stubs.log and not replay and pool.same(), (native_log, stubs.log)
        count += 1

        def verdict_patch(handle, data):
            patch(handle, data)
            struct.pack_into('<I', data, 0x450, rng.choice(pool.handles))
            data[0x4c5] = rng.choice([0, 1, 1, 1])

        pool.fill(rng, verdict_patch)
        obj = rng.choice(pool.handles)
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x43ab80, eax=obj, ebx=ebx) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_object_region_verdict(c.byref(calls), c.byref(services), STACK - 4, obj,
                                              ebx, first_copy, second_copy)
        assert got == result, ("verdict", hex(got), hex(result))
        assert native_log == stubs.log, [(i, a, b) for i, (a, b) in enumerate(zip(native_log, stubs.log)) if a != b][:2]
        assert not replay and pool.same()
        verdicts[got] = verdicts.get(got, 0) + 1
        count += 1
    assert len(verdicts) >= 3, verdicts
    report = {'status': 'passed', 'complete_original_executions': {'0x427ae0': count // 2, '0x43ab80': count // 2},
              'scope': 'The routine executes completely in the original with its callees stubbed '
                       'and logged; every callee call, the returned eax, every pool object and '
                       'the two local copies compare (0x43ab80 runs 0x427ae0 itself, all three verdicts).'}
    (args.build_dir / 'regions-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
