"""Compare the original window table builder 0x40a590 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from unicorn.x86_const import UC_X86_REG_EDX

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x100
SOURCE, SOURCE_SIZE = 0x4f5f90, 0x420
TARGET, TARGET_SIZE = 0x52e784, 0x900
HELPERS = (0x4d6768, 0x4db507, 0x4db350, 0x4eb652, 0x4c9dd6, 0x4eb606)


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
    parser.add_argument('--cases', type=int, default=60)
    args = parser.parse_args()
    n = build(args.build_dir, 'window-tables', ['window_tables.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_window_tables.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U]
    n.vertrix_window_tables.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x40a590)
    pool = Pool(cpu, 5, SIZE)
    source = c.create_string_buffer(SOURCE_SIZE)
    target = c.create_string_buffer(TARGET_SIZE)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == SOURCE:
            storage[0], size[0] = c.addressof(source), SOURCE_SIZE
            return 1
        if handle == TARGET:
            storage[0], size[0] = c.addressof(target), TARGET_SIZE
            return 1
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        high = rng.getrandbits(32)
        cpu.reg_write(UC_X86_REG_EDX, high)
        returns.append((rng.getrandbits(32), high))
        return returns[-1][0]

    stubs = Stubs(cpu, handler)
    for address in HELPERS:
        stubs.add(address, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        result, high = replay.pop(0)
        s.out_value = high
        return result

    calls = Calls(call, None)
    for case in range(args.cases):
        pool.fill(rng)
        blob = bytearray(rng.randbytes(SOURCE_SIZE))
        for k in range(5):
            struct.pack_into('<I', blob, 4 * k, pool.handles[k])
        cpu.mem_write(SOURCE, bytes(blob))
        c.memmove(source, bytes(blob), SOURCE_SIZE)
        tdata = rng.randbytes(TARGET_SIZE)
        cpu.mem_write(TARGET, tdata)
        c.memmove(target, tdata, TARGET_SIZE)
        sign, ebx, ecx = (rng.getrandbits(32) for _ in range(3))
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        original.call(0x40a590, eax=sign, ebx=ebx, ecx=ecx)
        replay[:] = list(returns)
        assert n.vertrix_window_tables(c.byref(calls), c.byref(services), sign, ebx, ecx), case
        assert native_log == stubs.log, (case, len(native_log), len(stubs.log),
                                         [(i, a, b) for i, (a, b) in enumerate(zip(native_log, stubs.log)) if a != b][:2])
        assert not replay and pool.same(), (case, pool.diff())
        assert target.raw == bytes(cpu.mem_read(TARGET, TARGET_SIZE)), case
    report = {'status': 'passed', 'complete_original_executions': {'0x40a590': args.cases},
              'scope': 'The routine executes completely in the original with the six floating '
                       'point helpers stubbed (random eax:edx results) and logged; every call '
                       'with all four registers (about 4000 a run), the five window arrays and the '
                       'scaled table compare.'}
    (args.build_dir / 'window-tables-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
