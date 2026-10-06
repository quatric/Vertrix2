"""Compare the original pair routines 0x473630, 0x4737d0 and 0x473960 with the native recovery."""
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
FIRST, SECOND, GATE_WORDS, GATE_FLAGS, VALUE = 0x540f8c, 0x540f90, 0x532a84, 0x532a7c, 0x5bd834


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


CALLEES = (0x476320, 0x476440, 0x476010, 0x4735e0, 0x473610, 0x476480)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'pair-sync', ['pair_sync.c', 'call_glue.c', 'actor_storage.c'])
    P, V = c.POINTER(Calls), c.POINTER(Services)
    n.vertrix_pair_words.argtypes = [P, V, U, U, U, U, U]
    n.vertrix_pair_words.restype = U
    n.vertrix_pair_flags.argtypes = [P, V, U, U, U, c.c_char_p]
    n.vertrix_pair_flags.restype = U
    n.vertrix_pair_scan.argtypes = [P, V, U, U, U, U, c.c_char_p]
    n.vertrix_pair_scan.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x473630)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
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
    services = Services(pool.resolve, None, None, None, None)
    totals = {}

    def run(address, native, **registers):
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(address, **registers) & 0xffffffff
        replay[:] = list(returns)
        got = native()
        assert got == result, (hex(address), hex(got), hex(result))
        assert native_log == stubs.log, (hex(address), [(i, a, b) for i, (a, b) in enumerate(zip(native_log, stubs.log)) if a != b][:2], len(native_log), len(stubs.log))
        assert not replay and pool.same(), (hex(address), pool.diff())
        totals[hex(address)] = totals.get(hex(address), 0) + 1

    for case in range(args.cases):
        pool.fill(rng)
        first, second = rng.choice(pool.handles), rng.choice(pool.handles)
        cpu.mem_write(FIRST, struct.pack('<I', first))
        cpu.mem_write(SECOND, struct.pack('<I', second))
        value = rng.getrandbits(32)
        cpu.mem_write(VALUE, struct.pack('<I', value))
        gate = rng.choice([0, 0, 1, 2])
        cpu.mem_write(GATE_WORDS, struct.pack('<I', gate))
        eax = rng.getrandbits(32)
        run(0x473630, lambda: n.vertrix_pair_words(c.byref(calls), c.byref(services), first,
                                                    second, gate, gate, value), eax=eax)
        gate = rng.choice([0, 1, 1, 2])
        cpu.mem_write(GATE_FLAGS, struct.pack('<I', gate))
        flags = rng.randbytes(16)
        cpu.mem_write(0x5bb4ec, flags[:12])
        cpu.mem_write(0x5bb4f8, flags[12:])
        for address, base in ((0x4737d0, 0x5bb4ec), (0x473960, 0x5bb4f0)):
            values = bytes(cpu.mem_read(base, 4)) + bytes(cpu.mem_read(base + 8, 4))
            run(address, lambda: n.vertrix_pair_flags(c.byref(calls), c.byref(services), first,
                                                       second, gate, values))
        gate = rng.choice([0, 1, 1, 2])
        cpu.mem_write(GATE_FLAGS, struct.pack('<I', gate))
        cpu.mem_write(0x5bb594, bytes(8))
        ebx = rng.getrandbits(32)
        out = c.create_string_buffer(8)
        run(0x473af0, lambda: n.vertrix_pair_scan(c.byref(calls), c.byref(services), first, second,
                                                   gate, ebx, out), ebx=ebx)
        assert out.raw[:8] == bytes(cpu.mem_read(0x5bb594, 8)), case
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Each routine executes completely in the original with its callees stubbed '
                       'and logged; every callee call, the returned eax and every pool object '
                       'compare. The gate global is constant during a run.'}
    (args.build_dir / 'pair-sync-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
