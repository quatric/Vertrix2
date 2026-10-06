"""Compare the original node pool takers 0x4d8490, 0x4d8c20 and 0x4df070 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x100
CALLEES = {0x4e23e0: 3, 0x4ca060: 0, 0x4eb5e0: 0}


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'node-pool', ['node_pool.c', 'call_glue.c', 'actor_storage.c'])
    P, V, O = c.POINTER(Calls), c.POINTER(Services), c.POINTER(U)
    n.vertrix_node_pool_take_pair.argtypes = [P, V, U, U, U, U, O]
    n.vertrix_node_pool_take_initialised.argtypes = [P, V, U, U, U, U, O]
    n.vertrix_node_pool_take_quad.argtypes = [P, V, U, U, U, O, O]
    for name in ('pair', 'initialised', 'quad'):
        getattr(n, 'vertrix_node_pool_take_' + name).restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4d8490)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4e23e0:
            returns.append(pool.handles[2])
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) + (
            (s.stack, s.stack_next, s.stack_third) if s.target == 0x4e23e0 else ()))
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve)
    totals = {}
    for case in range(args.cases):
        for address, name in ((0x4d8490, 'pair'), (0x4d8c20, 'initialised'), (0x4df070, 'quad')):
            pool.fill(rng)
            owner, head, block = pool.handles[:3]
            data = bytearray(rng.randbytes(SIZE))
            has_head = rng.random() < 0.5
            struct.pack_into('<IIII', data, 0xc, rng.randrange(0, 100), head if has_head else 0,
                             rng.getrandbits(32), rng.choice([1, 2, 3, 5]))
            cpu.mem_write(owner, bytes(data))
            c.memmove(pool.buffers[owner], bytes(data), SIZE)
            ebx, edx, ecx = (rng.getrandbits(32) for _ in range(3))
            stubs.log.clear()
            returns.clear()
            native_log.clear()
            result = original.call(address, eax=owner, ebx=ebx, edx=edx, ecx=ecx) & 0xffffffff
            replay[:] = list(returns)
            node = U()
            if name == 'quad':
                ok = n.vertrix_node_pool_take_quad(c.byref(calls), c.byref(services), owner, edx,
                                                   ecx, c.byref(node), c.byref(U()))
            else:
                ok = getattr(n, 'vertrix_node_pool_take_' + name)(
                    c.byref(calls), c.byref(services), owner, ebx, edx, ecx, c.byref(node))
            assert ok, (case, name)
            assert node.value == result, (case, name, hex(node.value), hex(result))
            assert native_log == stubs.log, (case, name, native_log, stubs.log)
            assert not replay and pool.same(), (case, name, pool.diff())
            key = (name, 'alloc' if native_log and native_log[0][0] == 0x4e23e0 else 'reuse')
            totals[str(key)] = totals.get(str(key), 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Each routine executes completely in the original with 0x4e23e0, 0x4ca060 and '
                       '0x4eb5e0 stubbed and logged; every callee call, the returned node and '
                       'every pool object compare, with and without a block refill.'}
    (args.build_dir / 'node-pool-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
