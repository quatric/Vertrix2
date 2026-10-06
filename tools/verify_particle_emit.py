"""Compare the original particle emission 0x43dc80 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
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


class Screen(c.Structure):
    _fields_ = [('width', c.c_uint16), ('height', c.c_uint16)]


class Scratch(c.Structure):
    _fields_ = [('scratch', c.c_uint16 * 4)]


CALLEES = (0x4826c0, 0x4ac8d0, 0x4ac7b0, 0x415470, 0x4ac490, 0x4ac710, 0x4ac470, 0x4ac7d0, 0x4ac8a0)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'particle-emit',
              ['particle_emit.c', 'call_glue.c', 'actor_storage.c'])
    P, V, S = c.POINTER(Calls), c.c_void_p, c.c_size_t
    n.vertrix_particle_emit.argtypes = [P, c.POINTER(Services), U, V, S, U, V, S, c.POINTER(Screen),
                                        c.POINTER(Scratch)]
    n.vertrix_particle_emit.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43dc80)
    pool = Pool(cpu, 4, 0xa00)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4826c0:
            returns.append(rng.randrange(max(1, edx)))
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address in CALLEES:
        stubs.add(address, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}
    modes = {}
    for case in range(args.cases):
        pool.fill(rng)
        emitter, particle = rng.sample(pool.handles, 2)
        mode = rng.choice([0, 1, 1, 2])
        data = struct.pack('<I', mode)
        cpu.mem_write(emitter + 0x94c, data)
        pool.buffers[emitter][0x94c:0x950] = data
        width, height = rng.randrange(1, 700), rng.randrange(1, 700)
        cpu.mem_write(0x5b9c8e, struct.pack('<HH', width, height))
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        services = Services(pool.resolve, None, None, None, None)
        result = original.call(0x43dc80, eax=emitter, edx=particle) & 0xffffffff
        replay[:] = list(returns)
        scratch = Scratch()
        got = n.vertrix_particle_emit(c.byref(calls), c.byref(services), emitter,
                                      pool.buffers[emitter], 0xa00, particle,
                                      pool.buffers[particle], 0xa00, c.byref(Screen(width, height)),
                                      c.byref(scratch))
        assert native_log == stubs.log, (case, native_log[:3], stubs.log[:3])
        assert got == result, (case, hex(got), hex(result))
        assert not replay, case
        assert pool.same(), (case, pool.diff())
        assert list(scratch.scratch) == list(struct.unpack('<4H', bytes(cpu.mem_read(0x540fcc, 8)))), case
        modes[mode] = modes.get(mode, 0) + 1
        totals['0x43dc80'] = totals.get('0x43dc80', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals, 'modes': modes,
              'scope': 'The original executes completely with its callees stubbed and logged (the '
                       'draw 0x4826c0 replayed); every callee call, the returned eax, the scratch '
                       'words 0x540fcc..0x540fd2 and both objects compare.'}
    (args.build_dir / 'particle-emit-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
