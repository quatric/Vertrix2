"""Compare the original text rebuild 0x488d80 with the native recovery."""
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
CALLEES = {0x4ca280: 0, 0x4ca370: 0}
OLD = {0x4ca280: 0, 0x4ca070: 0, 0x4cdb70: 0, 0x4cdaf0: 0, 0x4ca310: 0, 0x4ca210: 0,
           0x4ca430: 3, 0x4ca370: 0, 0x4cda10: 0}


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
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'kind-text', ['list_text.c', 'rtl_glue.c', 'call_glue.c',
                                               'actor_storage.c'])
    n.vertrix_object_kind_text.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U]
    n.vertrix_object_kind_text.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x488d80)
    pool = Pool(cpu, 1, SIZE)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
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
    services = Services(pool.resolve)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        obj, = pool.handles[:1]
        data = bytearray(cpu.mem_read(obj, SIZE))
        kind = rng.choice([rng.randrange(0, 16), rng.randrange(0, 15), rng.getrandbits(32)])
        struct.pack_into('<I', data, 8, kind)
        cpu.mem_write(obj, bytes(data))
        c.memmove(pool.buffers[obj], bytes(data), SIZE)
        variable = rng.getrandbits(32)
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        want = original.call(0x488d80, eax=variable, edx=obj) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_object_kind_text(c.byref(calls), c.byref(services), variable, obj)
        assert got == want, (case, got, want)
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert not replay and pool.same(), (case, pool.diff())
        key = 'default' if len(stubs.log) == 1 else 'text'
        totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': {'0x488d80': totals},
              'scope': 'The routine executes completely in the original with the string runtime '
                       'stubbed and logged ; the returned variable compares; every callee call '
                       'and every pool object compare.'}
    (args.build_dir / 'kind-text-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
