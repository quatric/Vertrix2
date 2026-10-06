"""Compare the original item attach 0x40f910 with the native recovery."""
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
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


CALLEES = {0x4eb860: 0, 0x4ec160: 0, 0x40ac50: 0, 0x40c220: 0, 0x40acd0: 0}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'attach-item', ['object_glue.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_object_attach_item.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U]
    n.vertrix_object_attach_item.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x40f910)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay, pointers = [], [], [], []
    current = [0, 0]

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ec160:
            # a fresh allocation never aliases the object or the source
            returns.append(rng.choice([h for h in pool.handles if h not in current] + [0]))
        elif address == 0x40ac50:
            handles = [h for h in pool.handles if h not in current and h != returns[-1]]
            pointers.append(rng.choice(handles))
            returns.append(rng.choice([0, 0, 0, 1, rng.getrandbits(32)]))
            if returns[-1] == 0:
                # the buffer pointer is only stored on success
                cpu.mem_write(eax, struct.pack('<I', pointers[-1]))
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
                          (s.stack, s.stack_next, s.stack_third, s.rest0, s.rest1)[:CALLEES[s.target]])
        if s.target == 0x40ac50:
            s.out_value = pointers.pop(0)
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    count = 0
    for case in range(args.cases):
        def patch(handle, data):
            struct.pack_into('<I', data, 0x18, rng.choice([0, rng.randrange(1, 0x60)]))
            struct.pack_into('<I', data, 0x1c, rng.randrange(0, 0x40))
            struct.pack_into('<I', data, 0x20, rng.randrange(0, 0x80))

        pool.fill(rng, patch)
        obj, source = rng.sample(pool.handles, 2)
        current[:] = [obj, source]
        pointers.clear()
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x40f910, eax=obj, edx=source) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_object_attach_item(c.byref(calls), c.byref(services), obj, source)
        assert got == result, (hex(got), hex(result))
        assert native_log == stubs.log and not replay, (native_log, stubs.log)
        assert pool.same(), (pool.diff(), hex(obj), hex(source), pointers, [hex(x) for x in returns])
        count += 1
    report = {'status': 'passed', 'complete_original_executions': {'0x40f910': count},
              'scope': 'The routine executes completely in the original with its callees stubbed '
                       'and logged; every callee call, the returned eax, every pool object '
                       'compare. The register arguments of the release calls are the loop state.'}
    (args.build_dir / 'attach-item-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
