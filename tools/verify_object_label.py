"""Compare the original label placement 0x4b3210 with the native recovery."""
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


CALLEES = {0x4ca070: 0, 0x4ca370: 0, 0x4ca210: 0, 0x4b65d0: 3}
LOCAL = STACK - 0x14


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'object-label', ['object_label.c', 'call_glue.c', 'actor_storage.c',
                                               'block_factory.c', 'actor_fields.c',
                                               'board_cells.c'])
    n.vertrix_object_place_label.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U, U, U,
                                             U, U]
    n.vertrix_object_place_label.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4b3210)
    pool = Pool(cpu, 4, SIZE)
    returns, outs, native_log, replay, replay_out = [], [], [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address in (0x4ca070, 0x4ca370):
            value = rng.getrandbits(32)
            cpu.mem_write(eax, struct.pack('<I', value))
            outs.append(value)
        returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        count = CALLEES[s.target]
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) +
                          (s.stack, s.stack_next, s.stack_third)[:count])
        if s.target in (0x4ca070, 0x4ca370):
            s.out_value = replay_out.pop(0)
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    branches = {}
    for case in range(args.cases):
        pool.fill(rng)
        object_handle = pool.handles[0]
        parent = rng.choice([0, pool.handles[1], pool.handles[2], object_handle])
        ebx, ecx = rng.getrandbits(32), rng.getrandbits(32)
        flag_x = rng.choice([0, 0, rng.getrandbits(32)])
        flag_y = rng.choice([0, 0, rng.getrandbits(32)])
        stubs.log.clear()
        returns.clear()
        outs.clear()
        native_log.clear()
        result = original.call(0x4b3210, eax=object_handle, edx=parent, ebx=ebx, ecx=ecx,
                               args=(flag_x, flag_y)) & 0xffffffff
        replay[:] = list(returns)
        replay_out[:] = list(outs)
        got = n.vertrix_object_place_label(c.byref(calls), c.byref(services), object_handle,
                                           parent, ebx, ecx, flag_x, flag_y, LOCAL)
        assert got == 1, (case, got)
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert not replay and not replay_out and pool.same(), (case, pool.diff())
        key = (parent == 0, flag_x == 0, flag_y == 0)
        branches[str(key)] = branches.get(str(key), 0) + 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4b3210': args.cases},
              'branches_seen': branches,
              'scope': 'The original executes completely with 0x4ca070, 0x4ca370, 0x4ca210 and '
                       '0x4b65d0 stubbed and logged (the first two store a random dword in the '
                       'string temporary); every call with its registers and stack arguments, '
                       'and every pool object compare. The '
                       "original's eax is the saved exception chain head and is not modeled."}
    (args.build_dir / 'object-label-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
