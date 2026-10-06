"""Compare the original array list table wrappers with the native recovery."""
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
LIST = 0x1c


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


RUNS = ((0x45e830, 0x546458, 5), (0x45e8f0, 0x544d7c, 19))
SINGLES = ((0x45e740, 0x5464e4), (0x45e810, 0x544a34), (0x45e820, 0x544a50))
EVERYTHING = [0x5466a4, 0x546618, 0x546634, 0x546688, 0x54666c, 0x546650, 0x546538, 0x54651c,
              0x546500, 0x5449c4, 0x5449e0, 0x5449fc, 0x544a18, 0x544bf4, 0x544d0c, 0x544c64,
              0x544cf0, 0x544cd4, 0x544c9c, 0x544cb8, 0x544c80, 0x544c2c, 0x544c48, 0x544c10,
              0x544a6c, 0x544aa4, 0x544d28, 0x544b84, 0x544ba0, 0x544bbc, 0x544bd8]
ALL_LISTS = (EVERYTHING + [0x5464e4, 0x544a34, 0x544a50, 0x544d44, 0x544d60, 0x544a88] +
             [0x546458 + LIST * i for i in range(5)] + [0x544d7c + LIST * i for i in range(19)] +
             [0x544ac0 + LIST * i for i in range(7)] + [0x546554 + LIST * i for i in range(7)] +
             [0x544f90 + 0x118 * r + LIST * i for r in range(19) for i in range(10)])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=256)
    args = parser.parse_args()
    n = build(args.build_dir, 'table-release', ['table_release.c', 'array_list.c', 'call_glue.c',
                                                'actor_storage.c'])
    P, V = c.POINTER(Calls), c.POINTER(Services)
    for name, types in (('release_one', [U, U]), ('release_by_flag', [U, U]), ('visit_all', []),
                        ('release_run', [U, U]), ('release_rows', []), ('release_pair', []),\
                        ('fill_slot', [U, U, U, U, U, U, U, U]),
                        ('fill_indexed', [U, U, U, U, U, U, U, U]),
                        ('release_everything', [U]), ('build_pair', []),
                        ('build_by_flag', [U, U])):
        function = getattr(n, 'vertrix_table_' + name)
        function.argtypes = [P, V] + types
        function.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x45e830)
    pool = Pool(cpu, 4, SIZE)
    objects = {}

    @Resolve
    def resolve(handle, storage, size, context):
        if handle in objects:
            storage[0] = c.addressof(objects[handle])
            size[0] = LIST
            return 1
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ec160:
            returns.append(rng.choice(pool.handles))
            return returns[-1]
        returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in ((0x4830f0, 0), (0x4ea190, 0), (0x483790, 0), (0x483060, 8), (0x4877f0, 0),
                           (0x482e10, 0), (0x483ed0, 0), (0x4ec160, 0)):
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) + (
            (s.stack, s.stack_next, s.stack_third, s.rest0, s.rest1, s.rest2, s.rest3, s.rest4)
            if s.target == 0x483060 else ()))
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}

    def fresh():
        pool.fill(rng)
        objects.clear()
        for address in ALL_LISTS:
            data = bytearray(rng.randbytes(LIST))
            struct.pack_into('<I', data, 0, rng.choice(pool.handles + [0]))
            struct.pack_into('<I', data, 4, rng.randrange(0, 5))
            struct.pack_into('<I', data, 0x14, rng.choice([0, 0, 1]))
            for offset in (8, 0xc, 0x10):
                struct.pack_into('<I', data, offset, rng.choice([0, rng.getrandbits(32)]))
            cpu.mem_write(address, bytes(data))
            objects[address] = c.create_string_buffer(bytes(data), LIST)

    def run(address, native, **registers):
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(address, **registers) & 0xffffffff
        replay[:] = list(returns)
        got = native()
        assert got == result, (hex(address), hex(got), hex(result))
        assert native_log == stubs.log, (hex(address), native_log[:3], stubs.log[:3])
        assert not replay and pool.same(), hex(address)
        for handle, buffer in objects.items():
            assert buffer.raw == bytes(cpu.mem_read(handle, LIST)), (hex(address), hex(handle))
        totals[hex(address)] = totals.get(hex(address), 0) + 1

    byref_c, byref_s = c.byref(calls), c.byref(services)
    for case in range(args.cases):
        edx = rng.getrandbits(32)
        for address, target in SINGLES:
            fresh()
            run(address, lambda: n.vertrix_table_release_one(byref_c, byref_s, target, edx),
                edx=edx)
        for flag in (0, rng.getrandbits(32) | 1):
            fresh()
            run(0x45e670, lambda: n.vertrix_table_release_by_flag(byref_c, byref_s, flag, edx), eax=flag,
                edx=edx)
        fresh()
        run(0x45ed40, lambda: n.vertrix_table_visit_all(byref_c, byref_s))
        for address, first, count in RUNS:
            fresh()
            run(address, lambda: n.vertrix_table_release_run(byref_c, byref_s, first, count))
        fresh()
        run(0x45e910, lambda: n.vertrix_table_release_rows(byref_c, byref_s))
        fresh()
        run(0x45e260, lambda: n.vertrix_table_release_everything(byref_c, byref_s, edx), edx=edx)
        fresh()
        run(0x45e440, lambda: n.vertrix_table_build_pair(byref_c, byref_s))
        for flag in (0, rng.getrandbits(32) | 1):
            fresh()
            count = rng.randrange(0, 4)
            run(0x45e630, lambda: n.vertrix_table_build_by_flag(byref_c, byref_s, flag, count),
                eax=flag, edx=count)
        fresh()
        run(0x45ea80, lambda: n.vertrix_table_release_pair(byref_c, byref_s))
    for case in range(args.cases):
        for address, table, flag in ((0x45e750, 0x5464e4, 0), (0x45e7b0, 0x544a34, 1)):
            fresh()
            record = (rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32))
            cpu.mem_write(0x800900, struct.pack('<III', *record))
            # the table's array must be a pool handle that is not the table itself
            data = bytearray(cpu.mem_read(table, LIST))
            struct.pack_into('<I', data, 0, rng.choice(pool.handles))
            cpu.mem_write(table, bytes(data))
            objects[table] = c.create_string_buffer(bytes(data), LIST)
            index = rng.randrange(0, 8)
            ebx, ecx = rng.getrandbits(32), rng.getrandbits(32)
            pair = (0, 0) if flag == 0 else (ebx, ecx)
            run(address, lambda: n.vertrix_table_fill_slot(
                byref_c, byref_s, table, index, 0x800900, record[1], record[2], pair[0], pair[1],
                flag), eax=index, edx=0x800900, ebx=ebx, ecx=ecx)
    for case in range(args.cases):
        for address, base, rows in ((0x45e850, 0x546458, 5), (0x45e9e0, 0x544d7c, 19)):
            fresh()
            row = rng.randrange(0, rows)
            table = base + LIST * row
            record = (rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32))
            cpu.mem_write(0x800900, struct.pack('<III', *record))
            data = bytearray(cpu.mem_read(table, LIST))
            struct.pack_into('<I', data, 0, rng.choice(pool.handles))
            cpu.mem_write(table, bytes(data))
            objects[table] = c.create_string_buffer(bytes(data), LIST)
            index = rng.randrange(0, 8)
            ecx, argument = rng.getrandbits(32), rng.getrandbits(32)
            run(address, lambda: n.vertrix_table_fill_indexed(
                byref_c, byref_s, base, row, index, 0x800900, record[1], record[2], ecx, argument),
                eax=row, edx=index, ebx=0x800900, ecx=ecx, args=(argument,))
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Each wrapper executes completely in the original with 0x4830f0, 0x4ea190 '
                       'and 0x483790 stubbed and logged; every callee call, the returned eax, all '
                       'array list objects and arrays compare.'}
    (args.build_dir / 'table-release-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
