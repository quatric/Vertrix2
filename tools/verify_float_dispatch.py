"""Compare the original float add and subtract entries 0x4d80a6 and 0x4d809c with the native
recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import Stubs, build

U = c.c_uint32
TABLE = 0x503ea0


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(14)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'float-dispatch', ['rtl_glue.c', 'call_glue.c', 'actor_storage.c'])
    for name in ('add', 'subtract'):
        function = getattr(n, 'vertrix_float_' + name)
        function.argtypes = [c.POINTER(Calls), U, U, U]
        function.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    helper = int.from_bytes(cpu.mem_read(TABLE, 4), 'little')
    rng = random.Random(0x4d809c)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    stubs.add(helper, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}
    values = [0, 0x80000000, 0x3f800000]
    for case in range(args.cases):
        for address, name in ((0x4d80a6, 'add'), (0x4d809c, 'subtract')):
            eax, edx = (rng.choice(values + [rng.getrandbits(32)]) for _ in range(2))
            ebx, ecx = rng.getrandbits(32), rng.getrandbits(32)
            stubs.log.clear()
            returns.clear()
            native_log.clear()
            result = original.call(address, eax=eax, edx=edx, ebx=ebx, ecx=ecx) & 0xffffffff
            replay[:] = list(returns)
            got = getattr(n, 'vertrix_float_' + name)(c.byref(calls), helper, eax, edx)
            assert got == result, (name, hex(eax), hex(edx), hex(got), hex(result))
            assert [(t, a, d) for t, a, d, _, _ in native_log] == [
                (t, a, d) for t, a, d, _, _ in stubs.log[:len(native_log)]] and \
                len(native_log) == len(stubs.log), (name, native_log, stubs.log)
            assert not replay
            totals[hex(address)] = totals.get(hex(address), 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Both entries execute completely in the original with the helper behind '
                       'the dword at 0x503ea0 stubbed (the jump target) and logged; the callee '
                       'registers eax and edx and the returned eax compare for zero, signed zero '
                       'and random operands.'}
    (args.build_dir / 'float-dispatch-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
