"""Compare original virtual dispatches with the native recovery."""
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
HOLDER, OBJ, VTABLE = 0x807000, 0x808000, 0x808800
METHOD = 0x707000
RETURN = 0x51ab1e


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next')]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


Read = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_uint, c.POINTER(c.c_uint32), c.c_void_p)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'object-dispatch',
              ['object_glue.c', 'call_glue.c', 'actor_storage.c', 'block_factory.c',
               'board_cells.c', 'particle_spawn.c', 'actor_fields.c', 'actor_chain_visit.c'])
    P = c.POINTER(Calls)
    n.vertrix_object_virtual_slot6.argtypes = [P, Read, c.c_void_p, c.c_void_p, c.c_size_t, U, U]
    n.vertrix_object_virtual_slot6.restype = U
    n.vertrix_object_invoke_callback.argtypes = [P, U, c.c_void_p, c.c_size_t, U, U]
    n.vertrix_object_invoke_callback.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43d320)
    totals = {}
    calls_log = []

    @Call
    def call(site, context):
        s = site.contents
        calls_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return RETURN

    calls = Calls(call, None)
    stubs = Stubs(cpu, lambda address, eax, edx, ebx, ecx, stack: RETURN)
    stubs.add(METHOD)

    @Read
    def read(address, width, value, context):
        value[0] = int.from_bytes(bytes(cpu.mem_read(address, width)), 'little')
        return 1

    def stub_events():
        return [(e[0], e[1], e[2], e[3], e[4]) for e in stubs.log if e[0] == METHOD]

    for _ in range(args.cases):
        # 0x43d320: holder -> object -> vtable -> slot 6.
        holder = bytearray(rng.getrandbits(8) for _ in range(SIZE))
        struct.pack_into('<I', holder, 0x468, OBJ)
        cpu.mem_write(HOLDER, bytes(holder))
        cpu.mem_write(OBJ, struct.pack('<I', VTABLE) + bytes(rng.getrandbits(8) for _ in range(60)))
        vtable = bytearray(rng.getrandbits(8) for _ in range(0x20))
        struct.pack_into('<I', vtable, 0x18, METHOD)
        cpu.mem_write(VTABLE, bytes(vtable))
        ebx, ecx = rng.getrandbits(32), rng.getrandbits(32)
        stubs.log.clear()
        calls_log.clear()
        expect = original.call(0x43d320, eax=HOLDER, ebx=ebx, ecx=ecx)
        host = c.create_string_buffer(bytes(holder), SIZE)
        assert n.vertrix_object_virtual_slot6(c.byref(calls), read, None, host, SIZE, ebx,
                                              ecx) == expect
        assert host.raw == bytes(cpu.mem_read(HOLDER, SIZE))
        assert calls_log == [(METHOD, OBJ, VTABLE, ebx, ecx)]
        assert stub_events() == [(METHOD, OBJ, VTABLE, ebx, ecx)]
        totals['0x43d320'] = totals.get('0x43d320', 0) + 1
        # 0x418850: stored slot, null (returns object) or set (calls it).
        target = 0 if rng.random() < 0.5 else METHOD
        holder = bytearray(rng.getrandbits(8) for _ in range(SIZE))
        struct.pack_into('<I', holder, 0xbc, target)
        cpu.mem_write(HOLDER, bytes(holder))
        stubs.log.clear()
        calls_log.clear()
        expect = original.call(0x418850, eax=HOLDER, ebx=ebx, ecx=ecx)
        host = c.create_string_buffer(bytes(holder), SIZE)
        assert n.vertrix_object_invoke_callback(c.byref(calls), HOLDER, host, SIZE, ebx,
                                                ecx) == expect
        assert host.raw == bytes(cpu.mem_read(HOLDER, SIZE))
        if target:
            assert calls_log == [(METHOD, HOLDER, HOLDER, ebx, ecx)]
            assert stub_events() == [(METHOD, HOLDER, HOLDER, ebx, ecx)]
        else:
            assert calls_log == [] and stub_events() == []
            assert expect == HOLDER
        totals['0x418850'] = totals.get('0x418850', 0) + 1
    tiny = c.create_string_buffer(b'\xaa' * 8, 8)
    assert not n.vertrix_object_virtual_slot6(c.byref(calls), read, None, tiny, 8, 0, 0)
    assert not n.vertrix_object_invoke_callback(c.byref(calls), HOLDER, tiny, 8, 0, 0)
    assert tiny.raw == b'\xaa' * 8
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 43d320 and 418850 execute in the original (method stubbed and '
                       'logged); returns, register arguments and storage compare, plus '
                       'short-storage preservation checks.'}
    (args.build_dir / 'object-dispatch-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
