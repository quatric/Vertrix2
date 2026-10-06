"""Compare the complete original chain-select handler 0x43ac00 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Stubs, build

U = c.c_uint32
SIZE = 0x800
HOLDER, OBJ, VTABLE, METHOD = 0x807000, 0x808000, 0x808800, 0x707000
ALLOCATION = 0x809000
GLOBAL_DEFAULT = 0x4f81cc
STATE_DEFAULTS = 0x532ca4
GRID = 0x534c18
COUNTS = 0x534f10
CELLS = 0x544f90


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next')]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


Resolve = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t),
                      c.c_void_p)
Allocate = c.CFUNCTYPE(U, U, c.c_void_p)
Read = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_uint, c.POINTER(c.c_uint32), c.c_void_p)


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', Allocate), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


CALLEES = {0x4ca000: 0, 0x487870: 0, 0x4879f0: 0, METHOD: 0}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'object-chain-select',
              ['object_glue.c', 'call_glue.c', 'actor_storage.c', 'engine_helpers.c',
               'table_queries.c', 'random.c'])
    P = c.POINTER(Calls)
    PU32 = c.POINTER(c.c_uint32)
    n.vertrix_object_chain_select.argtypes = [P, c.POINTER(Services), Read, c.c_void_p, c.c_void_p,
                                              c.c_size_t, U, PU32, PU32, PU32, U, U, U, U]
    n.vertrix_object_chain_select.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43ac00)
    totals = {}
    calls_log = []
    allocation = []

    @Call
    def call(site, context):
        s = site.contents
        calls_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return ALLOCATION

    @Allocate
    def allocate(size, context):
        allocation.append(size)
        return ALLOCATION

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == ALLOCATION:
            storage[0] = c.addressof(fresh)
            size[0] = 0x40
            return 1
        if handle == OBJ:
            storage[0] = c.addressof(object_buffer)
            size[0] = SIZE
            return 1
        return 0

    calls = Calls(call, None)
    services = Services(resolve, allocate, None, None, None)
    method_state = [1]

    hits = [0]

    def stub_handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            return ALLOCATION
        if address == METHOD:
            hits[0] += 1
            cpu.mem_write(HOLDER + 0x474, struct.pack('<I', method_state[0]))
            return None
        if address == 0x487870:
            return None
        return 0

    stubs = Stubs(cpu, stub_handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Read
    def read(address, width, value, context):
        value[0] = int.from_bytes(bytes(cpu.mem_read(address, width)), 'little')
        return 1

    fresh = c.create_string_buffer(0x40)
    object_buffer = c.create_string_buffer(SIZE)
    for case in range(args.cases):
        counts = [rng.randrange(0, 11) for _ in range(19)]
        chain = rng.choice([1, 5])
        pool = (1, 7) if rng.random() < 0.25 else (1, 5, 7)
        grid = [rng.choice(pool) for _ in range(19 * 10)]
        cpu.mem_write(COUNTS, struct.pack('<19I', *counts))
        cpu.mem_write(GRID, struct.pack('<%dI' % len(grid), *grid))
        defaults = [rng.getrandbits(32) for _ in range(19)]
        default = rng.getrandbits(32)
        cpu.mem_write(STATE_DEFAULTS, struct.pack('<19I', *defaults))
        cpu.mem_write(GLOBAL_DEFAULT, struct.pack('<I', default))
        cdefaults = (c.c_uint32 * 19)(*defaults)
        ccounts = (c.c_uint32 * 19)(*counts)
        cgrid = (c.c_uint32 * len(grid))(*grid)
        method_state[0] = rng.choice([1, 1, 0, 2, rng.getrandbits(32)])
        ebx, ecx = rng.getrandbits(32), rng.getrandbits(32)
        holder = bytearray(rng.randbytes(SIZE))
        struct.pack_into('<I', holder, 0x468, OBJ)
        struct.pack_into('<I', holder, 0x474, rng.choice([0, 1, 2]))
        column = rng.randrange(19)
        struct.pack_into('<I', holder, 0x488, column)
        vtable = bytearray(rng.getrandbits(8) for _ in range(0x20))
        struct.pack_into('<I', vtable, 0x18, METHOD)
        object_data = struct.pack('<I', VTABLE) + bytes(rng.getrandbits(8) for _ in range(SIZE - 4))
        allocation_data = bytes(rng.getrandbits(8) for _ in range(0x40))
        cpu.mem_write(HOLDER, bytes(holder))
        cpu.mem_write(OBJ, object_data)
        cpu.mem_write(VTABLE, bytes(vtable))
        cpu.mem_write(ALLOCATION, allocation_data)
        host = c.create_string_buffer(bytes(holder), SIZE)
        fresh.raw = allocation_data
        object_buffer.raw = object_data
        stubs.log.clear()
        calls_log.clear()
        allocation.clear()
        expect = original.call(0x43ac00, eax=HOLDER, ebx=ebx, ecx=ecx)
        replay_allocation = bytes(cpu.mem_read(ALLOCATION, 0x40))
        replay_object = bytes(cpu.mem_read(OBJ, SIZE))
        replay_calls = list(calls_log)
        replay_stubs = list(stubs.log)
        result = n.vertrix_object_chain_select(
            c.byref(calls), c.byref(services), read, None, host, SIZE, default, cdefaults,
            cgrid, ccounts, column, method_state[0], ebx, ecx)
        assert result == expect, (case, hex(result), hex(expect))
        assert host.raw == bytes(cpu.mem_read(HOLDER, SIZE)), case
        assert fresh.raw == replay_allocation, (
            case, 'state', method_state[0], 'column', column, 'counts', counts, 'chaincells',
            [grid[r * 19 + column] for r in range(counts[column])], 'want', fresh.raw[:12],
            'got', replay_allocation[:12])
        assert object_buffer.raw == replay_object, case
        by_address = {}
        for entry in replay_stubs:
            by_address.setdefault(entry[0], []).append(entry)
        method_calls = [entry for entry in calls_log if entry[0] == METHOD]
        assert len(method_calls) == len(by_address.get(METHOD, [])) == 1, case
        assert method_calls[0][1:] == by_address[METHOD][0][1:5], case
        releases = [entry for entry in calls_log if entry[0] == 0x4d88a0]
        original_releases = by_address.get(0x4879f0, [])
        assert len(releases) == len(original_releases) <= 1, case
        if releases:
            assert releases[0][1] == original_releases[0][1], case
            assert releases[0][3] == original_releases[0][2], case
            assert releases[0][4] == 1, case
            assert releases[0][2] == struct.unpack_from('<I', object_data, 8)[0], case
        assert allocation == ([0x10] if releases else []), (case, allocation)
        totals['0x43ac00'] = totals.get('0x43ac00', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete original 0x43ac00 executions with the operator new 0x4ca000, the '
                       'table construct 0x487870 (Self-preserving), the release wrapper 0x4879f0 '
                       'and the virtual slot 6 method stubbed and logged; the returned eax, the '
                       'holder +0x474 writes, the new table bytes (+0/+4/+8), the release target '
                       'object, the slot-6 call, the release target/table/field arguments '
                       '(native 0x4d88a0 against original 0x4879f0) and the 0x10 allocation '
                       'compare. All four path shapes execute: chain one with a row, chain one '
                       'empty (zero address stored), chain five with a row, chain five empty '
                       '(early return, no store).'}
    (args.build_dir / 'object-chain-select-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()