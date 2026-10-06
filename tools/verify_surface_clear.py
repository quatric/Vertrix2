"""Compare the original surface wrappers 0x41ac70 and 0x4856a0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Stubs, build

U = c.c_uint32
PAIR = 0x558c80
PAIR_SIZE = 0xc


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)
Resolve = c.CFUNCTYPE(c.c_int, U, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t), c.c_void_p)


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
    n = build(args.build_dir, 'surface-clear', ['surface_clear.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_surface_clear_second.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U,
                                               c.POINTER(U)]
    n.vertrix_surface_clear_second.restype = c.c_int
    n.vertrix_surface_pair_make.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U]
    n.vertrix_surface_pair_make.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x41ac70)
    state = c.create_string_buffer(PAIR_SIZE)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == PAIR:
            storage[0], size[0] = c.addressof(state), PAIR_SIZE
            return 1
        return 0

    services = Services(resolve)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    stubs.add(0x4872c0, 0)
    stubs.add(0x478f50, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {'0x41ac70': 0, '0x4856a0': 0}
    for case in range(args.cases):
        blob = rng.randbytes(PAIR_SIZE)
        state.raw = blob
        cpu.mem_write(PAIR, blob)
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        eax, edx, ebx, ecx = (rng.getrandbits(32) for _ in range(4))
        if rng.random() < 0.5:
            want = original.call(0x41ac70, eax=eax, edx=edx, ebx=ebx, ecx=ecx) & 0xffffffff
            replay[:] = list(returns)
            result = U()
            assert n.vertrix_surface_clear_second(c.byref(calls), c.byref(services), ebx, ecx,
                                                  c.byref(result)), case
            assert result.value == want, (case, result.value, want)
            totals['0x41ac70'] += 1
        else:
            want = original.call(0x4856a0, eax=eax, edx=edx, ebx=ebx, ecx=ecx) & 0xffffffff
            replay[:] = list(returns)
            assert want == 1, case
            assert n.vertrix_surface_pair_make(c.byref(calls), c.byref(services), eax, edx, ebx), case
            totals['0x4856a0'] += 1
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert not replay and state.raw == bytes(cpu.mem_read(PAIR, PAIR_SIZE)), case
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'The wrappers execute completely in the original with 0x4872c0 and 0x478f50 '
                       'stubbed and logged; every call with its registers, the returned eax and '
                       'the surface globals compare.'}
    (args.build_dir / 'surface-clear-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
