"""Compare the original object event handlers with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x600
FLAG = 0x532a3c


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next')]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


CALLEES = {0x4ac370: 0, 0x4ac390: 0, 0x4ac3b0: 0, 0x4ac380: 0, 0x4ac810: 0, 0x4826c0: 0,
           0x43f420: 0, 0x4ac950: 0, 0x4ac8f0: 0, 0x43bb00: 0, 0x43bae0: 0, 0x43bb60: 0}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'object-events', ['object_events.c', 'call_glue.c', 'actor_storage.c'])
    P, V, S = c.POINTER(Calls), c.c_void_p, c.c_size_t
    n.vertrix_object_flip_side.argtypes = [P, U, V, S]
    n.vertrix_object_start_hold.argtypes = [P, c.POINTER(Services), U, V, S, c.POINTER(U)]
    n.vertrix_object_arm_hold.argtypes = [P, c.POINTER(Services), U, V, S]
    for name in ('flip_side', 'start_hold', 'arm_hold'):
        getattr(n, 'vertrix_object_' + name).restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x457810)
    pool = Pool(cpu, 8, SIZE)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4826c0:
            returns.append(rng.randrange(edx & 0xffff))
        elif address == 0x4ac390:
            returns.append(rng.choice([1, 1, 0, 5]))
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    totals = {}

    def patch(handle, data):
        struct.pack_into('<I', data, 0x3b0, rng.choice(pool.handles))
        data[0x4c5] = rng.choice([0, 1, 1])
        struct.pack_into('<I', data, 0x464, rng.choice([0, 1, 2]))
        struct.pack_into('<I', data, 0x188, rng.choice([0, 1, 7]))

    def run(name, address, native, **registers):
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(address, **registers) & 0xffffffff
        replay[:] = list(returns)
        got = native()
        assert got == result, (name, hex(got), hex(result))
        assert native_log == stubs.log, (name, native_log, stubs.log)
        assert not replay, name
        assert pool.same(), (name, pool.diff())
        totals[hex(address)] = totals.get(hex(address), 0) + 1

    for case in range(args.cases):
        pool.fill(rng, patch)
        obj = rng.choice(pool.handles)
        buffer = pool.buffers[obj]
        run('flip', 0x457810, lambda: n.vertrix_object_flip_side(c.byref(calls), obj, buffer, SIZE),
            eax=obj, edx=0)
        flag = U(0)
        cpu.mem_write(FLAG, bytes(4))
        run('start', 0x450f80, lambda: n.vertrix_object_start_hold(
            c.byref(calls), c.byref(services), obj, buffer, SIZE, c.byref(flag)), eax=obj, edx=0)
        assert flag.value == int.from_bytes(cpu.mem_read(FLAG, 4), 'little'), case
        run('arm', 0x452250, lambda: n.vertrix_object_arm_hold(
            c.byref(calls), c.byref(services), obj, buffer, SIZE), eax=obj, edx=0, ebx=0)
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Each handler executes completely in the original with its callees stubbed '
                       'and logged (the draw 0x4826c0 replayed); every callee call, the returned '
                       'eax, the global 0x532a3c and every pool object compare.'}
    (args.build_dir / 'object-events-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
