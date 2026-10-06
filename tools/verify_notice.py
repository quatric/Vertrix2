"""Compare the original notice routine 0x416010 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from oracle_kit import Stubs, build

U = c.c_uint32


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


CALLEES = (0x47f9b0, 0x4ca280, 0x4b76d0, 0x4ca210)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=512)
    args = parser.parse_args()
    n = build(args.build_dir, 'notice', ['call_glue.c', 'actor_storage.c'])
    n.vertrix_notice_call.argtypes = [c.POINTER(Calls), U, U, U, c.POINTER(U)]
    n.vertrix_notice_call.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x416010)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        returns.append(rng.choice([1, 1, 0, rng.getrandbits(32)]) if address == 0x47f9b0
                       else rng.getrandbits(32))
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
    count = 0
    for case in range(args.cases):
        current = rng.getrandbits(32)
        expected = current if rng.random() < 0.7 else rng.getrandbits(32)
        cpu.mem_write(0x532bf8, struct.pack('<I', current))
        cpu.mem_write(0x4f8160, struct.pack('<I', expected))
        cpu.mem_write(0x532c40, bytes(4))
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        original.call(0x416010)
        replay[:] = list(returns)
        flag = U(0)
        n.vertrix_notice_call(c.byref(calls), STACK - 4, current, expected, c.byref(flag))
        assert native_log == stubs.log, (native_log, stubs.log)
        assert not replay
        assert flag.value == int.from_bytes(cpu.mem_read(0x532c40, 4), 'little')
        count += 1
    report = {'status': 'passed', 'complete_original_executions': {'0x416010': count},
              'scope': 'The routine executes completely in the original with its callees stubbed '
                       'and logged; every callee call and the global 0x532c40 compare (the '
                       'original eax is the restored exception chain).'}
    (args.build_dir / 'notice-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
