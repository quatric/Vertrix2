"""Compare the original label text placement 0x4b65d0 with the native recovery."""
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


CALLEES = {0x4ca370: 0, 0x4408e0: 7}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'object-label-text', ['object_label.c', 'call_glue.c',
                                                    'actor_storage.c', 'block_factory.c',
                                                    'actor_fields.c', 'board_cells.c'])
    n.vertrix_object_label_text.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U, U, U,
                                            U * 3, c.POINTER(U)]
    n.vertrix_object_label_text.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4b65d0)
    pool = Pool(cpu, 4, SIZE)
    returns, outs, native_log, replay = [], [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4408e0:
            values = [rng.getrandbits(32) for _ in range(4)]
            for pointer, value in zip(stack[3:7], values):
                cpu.mem_write(pointer, struct.pack('<I', value))
            outs.append(values)
        returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) +
                          (s.stack, s.stack_next, s.stack_third, s.rest0, s.rest1, s.rest2,
                           s.rest3)[:CALLEES[s.target]])
        if s.target == 0x4408e0:
            v = outs.pop(0)
            s.out_value, s.rest4, s.out_ebx, s.out_ecx = v[0], v[1], v[2], v[3]
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    for case in range(args.cases):
        pool.fill(rng)
        obj = rng.choice(pool.handles)
        text, x1, glyph = (rng.getrandbits(32) for _ in range(3))
        arguments = [rng.getrandbits(32) for _ in range(3)]
        stubs.log.clear()
        returns.clear()
        outs.clear()
        native_log.clear()
        result = original.call(0x4b65d0, eax=obj, edx=text, ebx=glyph, ecx=x1,
                               args=tuple(arguments)) & 0xffffffff
        replay[:] = list(returns)
        eax = U(0)
        ok = n.vertrix_object_label_text(c.byref(calls), c.byref(services), STACK - 4, obj, text,
                                         x1, glyph, (U * 3)(*arguments), c.byref(eax))
        assert ok == 1 and eax.value == result, (case, ok, hex(eax.value), hex(result))
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert not replay and not outs and pool.same(), (case, pool.diff())
    report = {'status': 'passed', 'complete_original_executions': {'0x4b65d0': args.cases},
              'scope': 'The original executes completely with 0x4ca370 and 0x4408e0 stubbed and '
                       'logged (0x4408e0 stores four random dwords through its stack pointers); '
                       'every call with its registers and seven stack arguments, the returned eax '
                       'and every pool object compare.'}
    (args.build_dir / 'object-label-text-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
