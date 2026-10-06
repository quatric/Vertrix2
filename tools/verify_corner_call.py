"""Compare the original corner call 0x440ca0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK, STACK
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


CALLEES = {0x4408e0: 7, 0x440a20: 2}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'corner-call', ['object_glue.c', 'call_glue.c', 'actor_storage.c', 'table_queries.c'])
    n.vertrix_object_corner_call.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U, U, U,
                                             U * 4]
    n.vertrix_object_corner_call.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x440ca0)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay, pairs = [], [], [], []
    current = [0, 0]

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4408e0:
            values = [rng.getrandbits(32) for _ in range(4)]
            for pointer, value in zip(stack[3:7], values):
                cpu.mem_write(pointer, struct.pack('<I', value))
            pairs.append((values[3], values[2]))
        returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) +
                          (s.stack, s.stack_next, s.stack_third, s.rest0, s.rest1, s.rest2, s.rest3)[:CALLEES[s.target]])
        if s.target == 0x4408e0:
            s.out_ebx, s.out_ecx = pairs.pop(0)
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    count = 0
    for case in range(args.cases):
        pool.fill(rng)
        obj, arg4 = rng.choice(pool.handles), rng.choice(pool.handles)
        edx, ebx, ecx = (rng.getrandbits(32) for _ in range(3))
        arguments = [rng.getrandbits(32) for _ in range(3)] + [arg4]
        pairs.clear()
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x440ca0, eax=obj, edx=edx, ebx=ebx, ecx=ecx,
                               args=tuple(arguments)) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_object_corner_call(c.byref(calls), c.byref(services), STACK - 4, obj, edx,
                                           ebx, ecx, (U * 4)(*arguments))
        assert native_log == stubs.log and not replay, (native_log, stubs.log)
        assert pool.same(), (pool.diff(), hex(obj), hex(source), pointers, [hex(x) for x in returns])
        count += 1
    report = {'status': 'passed', 'complete_original_executions': {'0x440ca0': count},
              'scope': 'The routine executes completely in the original with its callees stubbed '
                       'and logged (0x4408e0 storing two result dwords through its stack pointers); '
                       'every callee call (registers and seven or two stack arguments) and every '
                       'pool object compare. The original eax is the restored exception chain.'}
    (args.build_dir / 'corner-call-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
