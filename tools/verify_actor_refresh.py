"""Compare the original actor refresh routines 0x45afe0 and 0x45cff0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x200
FRAME = STACK - 4
LOCAL = FRAME - 0x1c


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


CALLEES = {0x4ac600: 0, 0x4ac620: 0, 0x4ac640: 0, 0x4ac6b0: 0, 0x4ad060: 0, 0x4826c0: 0,
           0x4ac860: 0, 0x4ad1c0: 1, 0x4adfe0: 0}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'actor-refresh', ['actor_refresh.c', 'call_glue.c', 'actor_storage.c'])
    P, V = c.POINTER(Calls), c.POINTER(Services)
    n.vertrix_actor_refresh.argtypes = [P, V, U, U, U, U, U]
    n.vertrix_actor_refresh.restype = U
    n.vertrix_actor_refresh_if_active.argtypes = n.vertrix_actor_refresh.argtypes
    n.vertrix_actor_refresh_if_active.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x45afe0)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay, outs = [], [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ad1c0:
            outs.append(rng.choice([0, 0, rng.getrandbits(32)]))
            cpu.mem_write(stack[0], struct.pack('<I', outs[-1]))
        if address == 0x4ac620:
            returns.append(rng.choice([1, 1, 1, 0, rng.getrandbits(32)]))
        elif address == 0x4ad060:
            returns.append(rng.choice([0, 0, rng.getrandbits(32)]))
        elif address == 0x4ad1c0:
            returns.append(rng.getrandbits(32))
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) +
                          ((s.stack,) if CALLEES[s.target] else ()))
        if s.target == 0x4ad1c0:
            s.out_value = outs.pop(0)
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    totals = {}

    def patch(handle, data):
        struct.pack_into('<I', data, 0x58, rng.choice([1, 1, rng.getrandbits(32)]))
        if rng.random() < 0.5:
            struct.pack_into('<H', data, 0x16, rng.getrandbits(16))
            struct.pack_into('<H', data, 0xe, rng.getrandbits(16))
            struct.pack_into('<H', data, 0xa, 0)
            struct.pack_into('<I', data, 0x2e, rng.choice([0, 0x10000, rng.getrandbits(32)]))

    for case in range(args.cases):
        for address in (0x45afe0, 0x45cff0):
            pool.fill(rng, patch)
            obj = rng.choice(pool.handles)
            edx, ebx, ecx = (rng.getrandbits(32) for _ in range(3))
            stubs.log.clear()
            returns.clear()
            native_log.clear()
            outs.clear()
            result = original.call(address, eax=obj, edx=edx, ebx=ebx, ecx=ecx) & 0xffffffff
            replay[:] = list(returns)
            got = n.vertrix_actor_refresh(c.byref(calls), c.byref(services), FRAME, obj, edx, ebx,
                                          ecx)
            assert got == result, (hex(address), hex(got), hex(result))
            assert native_log == stubs.log, (hex(address), native_log, stubs.log)
            assert not replay and pool.same(), (hex(address), pool.diff())
            totals[hex(address)] = totals.get(hex(address), 0) + 1
    for case in range(args.cases):
        pool.fill(rng, patch)
        obj = rng.choice(pool.handles)
        edx, ebx, ecx = (rng.getrandbits(32) for _ in range(3))
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        outs.clear()
        result = original.call(0x45cdc0, eax=obj, edx=edx, ebx=ebx, ecx=ecx) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_actor_refresh_if_active(c.byref(calls), c.byref(services), FRAME, obj,
                                                edx, ebx, ecx)
        assert got == result, hex(got)
        assert native_log == stubs.log and not replay and pool.same()
        totals['0x45cdc0'] = totals.get('0x45cdc0', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Both routines execute completely in the original with their callees '
                       'stubbed and logged (0x4ad1c0 storing a dword through its stack argument); '
                       'every callee call, the returned eax and every pool object compare.'}
    (args.build_dir / 'actor-refresh-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
