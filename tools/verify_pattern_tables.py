"""Compare the original pattern table builder 0x441f20 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x100
SOURCE, SOURCE_SIZE = 0x4fba48, 0x80
TARGET, TARGET_SIZE = 0x5440f6, 0x7a0


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
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'pattern-tables', ['pattern_tables.c', 'call_glue.c',
                                                 'actor_storage.c'])
    n.vertrix_pattern_tables.argtypes = [c.POINTER(Calls), c.POINTER(Services), U]
    n.vertrix_pattern_tables.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x441f20)
    pool = Pool(cpu, 30, SIZE)
    source = c.create_string_buffer(bytes(cpu.mem_read(SOURCE, SOURCE_SIZE)), SOURCE_SIZE)
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
    free = []
    zero_odds = [0.93]

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ec160:
            returns.append(free.pop(0))
        else:
            returns.append(0 if rng.random() < zero_odds[0] else rng.randrange(1, 256))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    stubs.add(0x478f10, 0)
    stubs.add(0x4ec160, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {'patterns': 0}
    for case in range(args.cases):
        pool.fill(rng)
        surface = pool.handles[0]
        data = bytearray(cpu.mem_read(surface, SIZE))
        struct.pack_into('<I', data, 4, rng.randrange(0, 9))
        cpu.mem_write(surface, bytes(data))
        c.memmove(pool.buffers[surface], bytes(data), SIZE)
        tdata = rng.randbytes(TARGET_SIZE)
        cpu.mem_write(TARGET, tdata)
        c.memmove(target, tdata, TARGET_SIZE)
        free[:] = pool.handles[1:]
        zero_odds[0] = rng.choice([0.5, 0.93, 0.97])
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        original.call(0x441f20, eax=surface)
        replay[:] = list(returns)
        free[:] = pool.handles[1:]
        assert n.vertrix_pattern_tables(c.byref(calls), c.byref(services), surface), case
        assert native_log == stubs.log, (case, len(native_log), len(stubs.log),
                                         [(i, a, b) for i, (a, b) in enumerate(zip(native_log, stubs.log)) if a != b][:2])
        assert not replay and pool.same(), (case, pool.diff())
        want = bytes(cpu.mem_read(TARGET, TARGET_SIZE))
        assert target.raw == want, (case, [hex(TARGET + i) for i in range(TARGET_SIZE) if target.raw[i] != want[i]][:8])
        totals['patterns'] += sum(1 for e in stubs.log if e[0] == 0x4ec160)
    assert totals['patterns'] > 100, totals
    report = {'status': 'passed', 'complete_original_executions': {'0x441f20': args.cases},
              'allocations': totals['patterns'],
              'scope': 'The routine executes completely in the original with 0x478f10 and 0x4ec160 '
                       'stubbed and logged; every call with its registers, the working tables and '
                       'the copied pattern buffers compare. The original eax is scratch.'}
    (args.build_dir / 'pattern-tables-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
