"""Compare the original text rebuild 0x4b6930 with the native recovery."""
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
CALLEES = {0x4cdb70: 0, 0x440610: 1, 0x4ca210: 0}
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
    n = build(args.build_dir, 'text-value', ['list_text.c', 'rtl_glue.c', 'call_glue.c',
                                               'actor_storage.c'])
    n.vertrix_object_text_value.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U,
                                              c.POINTER(U)]
    n.vertrix_object_text_value.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4b6930)
    pool = Pool(cpu, 3, SIZE)
    returns, native_log, replay = [], [], []

    outs = []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4cdb70:
            outs.append(pool.handles[1] + 0xc)
            cpu.mem_write(edx, struct.pack('<I', outs[-1]))
        elif address == 0x440610:
            outs.append(rng.getrandbits(32))
            cpu.mem_write(ecx, struct.pack('<I', outs[-1]))
        returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) + ((s.stack,) if s.target == 0x440610 else ()))
        if s.target == 0x4cdb70:
            s.out_value = outs.pop(0)
        elif s.target == 0x440610:
            s.out_ecx = outs.pop(0)
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        obj, header, _ = pool.handles
        data = bytearray(cpu.mem_read(header, SIZE))
        struct.pack_into('<I', data, 4, rng.choice([0, 0, 1, rng.getrandbits(32)]))
        cpu.mem_write(header, bytes(data))
        c.memmove(pool.buffers[header], bytes(data), SIZE)
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        edx = rng.getrandbits(32)
        outs.clear()
        want = original.call(0x4b6930, eax=obj, ebx=rng.getrandbits(32), ecx=rng.getrandbits(32),
                      edx=edx)
        outs[:] = list(outs)
        replay[:] = list(returns)
        result = U()
        assert n.vertrix_object_text_value(c.byref(calls), c.byref(services), STACK - 4, obj,
                                             edx, c.byref(result)), case
        assert result.value == want & 0xffffffff, (case, result.value, want)
        assert native_log == stubs.log, (case, native_log[:4], stubs.log[:4])
        assert not replay and pool.same(), (case, pool.diff())
        key = 'empty' if len(stubs.log) == 2 else 'converted'
        totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4b6930': totals},
              'scope': 'The routine executes completely in the original with the string runtime '
                       'stubbed and logged (0x4cdb70 and 0x440610 storing their out dwords); the returned value compares; every callee call '
                       'and every pool object compare.'}
    (args.build_dir / 'text-value-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
