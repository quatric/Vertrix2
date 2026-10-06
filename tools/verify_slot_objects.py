"""Compare the original slot actor builder 0x429bf0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x300
FRAME = STACK - 4
CALLEES = {0x4178d0: 0, 0x417930: 0, 0x4ca000: 0, 0x43a080: 0, 0x4adf20: 5, 0x4ac8a0: 0,
           0x4ac7d0: 0, 0x4ac8f0: 0}


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


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'slot-objects', ['slot_objects.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_slot_objects_make.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U]
    n.vertrix_slot_objects_make.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x429bf0)
    pool = Pool(cpu, 29, SIZE)

    @Resolve
    def resolve(handle, storage, size, context):
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    returns, outs, native_log, replay, free = [], [], [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4178d0:
            first, second = rng.getrandbits(8), rng.getrandbits(8)
            cpu.mem_write(ebx, bytes([first]))
            cpu.mem_write(ecx, bytes([second]))
            outs.append((first, second))
            returns.append(0xffffffff if rng.random() < 0.3 else rng.getrandbits(32))
        elif address == 0x4ca000:
            returns.append(1)
        elif address == 0x43a080:
            returns.append(free.pop(0))
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
            (s.stack, s.stack_next, s.stack_third, s.rest0, s.rest1) if s.target == 0x4adf20 else ()))
        if s.target == 0x4178d0:
            s.out_ebx, s.out_ecx = outs.pop(0)
        return replay.pop(0)

    calls = Calls(call, None)
    for case in range(args.cases):
        pool.fill(rng)
        owner = pool.handles[0]
        kind = rng.getrandbits(32)
        stubs.log.clear()
        returns.clear()
        outs.clear()
        native_log.clear()
        free[:] = pool.handles[1:]
        original.call(0x429bf0, eax=owner, edx=kind)
        replay[:] = list(returns)
        free[:] = pool.handles[1:]
        assert n.vertrix_slot_objects_make(c.byref(calls), c.byref(services), FRAME, owner, kind), case
        assert native_log == stubs.log, (case, len(native_log), len(stubs.log),
                                         [(i, a, b) for i, (a, b) in enumerate(zip(native_log, stubs.log)) if a != b][:2])
        assert not replay and pool.same(), (case, pool.diff())
    report = {'status': 'passed', 'complete_original_executions': {'0x429bf0': args.cases},
              'scope': 'The routine executes completely in the original with the slot query, the '
                       'allocation and the actor setters stubbed and logged (0x4178d0 storing its '
                       'two bytes through its ebx and ecx pointers); every call with its registers '
                       'and stack arguments and every object compare.'}
    (args.build_dir / 'slot-objects-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
