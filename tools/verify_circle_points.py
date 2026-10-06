"""Compare the original midpoint circle 0x479e50 with the native recovery."""
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
STATE, STATE_SIZE = 0x558a60, 0x20


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
    n = build(args.build_dir, 'circle-points', ['circle_points.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_circle_points.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U]
    n.vertrix_circle_points.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x479e50)
    pool = Pool(cpu, 2, SIZE)
    state = c.create_string_buffer(STATE_SIZE)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == STATE:
            storage[0], size[0] = c.addressof(state), STATE_SIZE
            return 1
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    stubs.add(0x479df0, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    steps = 0
    for case in range(args.cases):
        pool.fill(rng)
        surface = pool.handles[0]
        data = bytearray(cpu.mem_read(surface, SIZE))
        struct.pack_into('<II', data, 4, rng.randrange(0, 400), rng.randrange(0, 400))
        cpu.mem_write(surface, bytes(data))
        c.memmove(pool.buffers[surface], bytes(data), SIZE)
        blob = rng.randbytes(STATE_SIZE)
        cpu.mem_write(STATE, blob)
        c.memmove(state, blob, STATE_SIZE)
        argument = rng.getrandbits(32)
        radius = rng.choice([0, 1, 2, 3, rng.randrange(0, 60), rng.randrange(0, 200)])
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        original.call(0x479e50, eax=surface, edx=argument, ebx=radius)
        replay[:] = list(returns)
        assert n.vertrix_circle_points(c.byref(calls), c.byref(services), surface, argument,
                                       radius), case
        assert native_log == stubs.log, (case, radius, len(native_log), len(stubs.log),
                                         [(i, a, b) for i, (a, b) in enumerate(zip(native_log, stubs.log)) if a != b][:2])
        assert not replay and pool.same(), (case, pool.diff())
        want = bytes(cpu.mem_read(STATE, STATE_SIZE))
        assert state.raw == want, (case, radius, state.raw.hex(), want.hex())
        steps += len(native_log) // 4
    report = {'status': 'passed', 'complete_original_executions': {'0x479e50': args.cases},
              'plot_steps': steps,
              'scope': 'The routine executes completely in the original with 0x479df0 stubbed and '
                       'logged; every plot call with its registers and the scratch word region '
                       'compare.'}
    (args.build_dir / 'circle-points-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
