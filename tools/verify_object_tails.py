"""Compare the original object tail wrappers with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x1000
FLAG = 0x532a08


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next')]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


CALLEES = {0x476480: 0, 0x4762e0: 0, 0x475a20: 0, 0x4b8170: 0, 0x4b78d0: 0, 0x4b4690: 0,
           0x4b7a80: 0, 0x4b5eb0: 0, 0x4123d0: 0, 0x481b20: 0, 0x4830f0: 0}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'object-tails', ['object_tails.c', 'object_glue.c', 'call_glue.c', 'actor_storage.c', 'table_queries.c'])
    P, V, S = c.POINTER(Calls), c.c_void_p, c.c_size_t
    n.vertrix_slot_toggle.argtypes = [P, c.POINTER(U)]
    n.vertrix_slot_table_init.argtypes = [P, U]
    n.vertrix_call_unless_zero.argtypes = [P, U]
    n.vertrix_object_table_517644.argtypes = [P, c.POINTER(Services), U, U]
    n.vertrix_object_step_text_length.argtypes = [P, U, V, S, U]
    n.vertrix_object_slot_present.argtypes = [P, V, S, S, U]
    n.vertrix_forward_a2f0.argtypes = [P, U, U]
    n.vertrix_object_table_516d34.argtypes = [P, c.POINTER(Services), U]
    n.vertrix_object_clear_with_table.argtypes = [V, S, U]
    n.vertrix_object_clear_with_ones.argtypes = [V, S, U]
    n.vertrix_object_text_length_reset.argtypes = [P, c.POINTER(Services), U, V, S]
    n.vertrix_object_slot_present_unowned.argtypes = [P, V, S, U]
    n.vertrix_object_release_items.argtypes = [P, c.POINTER(Services), V, S]
    for name in ('table_516d34', 'clear_with_table', 'clear_with_ones', 'text_length_reset',
                 'slot_present_unowned', 'release_items'):
        getattr(n, 'vertrix_object_' + name).restype = U
    n.vertrix_list_notify_pair.argtypes = [P, U, U]
    n.vertrix_list_clear_hit.argtypes = [P, c.POINTER(Services), U, U]
    n.vertrix_object_clear_block.argtypes = [V, S]
    for name in ('list_notify_pair', 'list_clear_hit'):
        getattr(n, 'vertrix_' + name).restype = U
    for name in ('slot_toggle', 'slot_table_init', 'call_unless_zero', 'object_table_517644',
                 'object_step_text_length', 'object_slot_present', 'forward_a2f0'):
        getattr(n, 'vertrix_' + name).restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x41de80)
    pool = Pool(cpu, 8, SIZE)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address in (0x4b78d0, 0x481b20):
            returns.append(rng.choice(pool.handles) + (0x10 if address == 0x481b20 else 0))
        elif address == 0x4b5eb0:
            returns.append(rng.choice(pool.handles + [0]))
        else:
            returns.append(rng.choice([0, 1, 1, rng.getrandbits(32)]))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    totals = {}

    def patch(handle, data):
        struct.pack_into('<i', data, 0x170, rng.randrange(-3, 6))
        struct.pack_into('<H', data, 0x15c, rng.choice([0, rng.getrandbits(16)]))
        struct.pack_into('<H', data, 0x172, rng.choice([0, rng.getrandbits(16)]))
        struct.pack_into('<I', data, 0x160, rng.choice([0] + pool.handles))
        struct.pack_into('<I', data, 0x4, rng.choice(pool.handles))
        struct.pack_into('<I', data, 0x8, rng.randrange(0, 3))
        struct.pack_into('<I', data, 0x0, rng.choice(pool.handles))
        struct.pack_into('<I', data, 0xb4, rng.choice([0, 0, rng.getrandbits(32)]))
        data[0x1f0] = 0

    def run(name, address, native, **registers):
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(address, **registers) & 0xffffffff
        replay[:] = list(returns)
        got = native()
        assert got == result, (name, hex(got), hex(result))
        assert native_log == stubs.log, (name, native_log, stubs.log)
        assert not replay, name
        assert pool.same(), (name, pool.diff())
        totals[hex(address)] = totals.get(hex(address), 0) + 1

    for case in range(args.cases):
        pool.fill(rng, patch)
        obj = rng.choice(pool.handles)
        buffer = pool.buffers[obj]
        flag = U(rng.getrandbits(32))
        cpu.mem_write(FLAG, struct.pack('<I', flag.value))
        run('toggle', 0x41de80, lambda: n.vertrix_slot_toggle(c.byref(calls), c.byref(flag)),
            eax=0, edx=0)
        assert flag.value == int.from_bytes(cpu.mem_read(FLAG, 4), 'little'), case
        table = rng.getrandbits(32)
        run('init', 0x476090, lambda: n.vertrix_slot_table_init(c.byref(calls), table), eax=table,
            edx=0)
        eax = rng.choice([0, rng.getrandbits(32)])
        run('unless', 0x482b30, lambda: n.vertrix_call_unless_zero(c.byref(calls), eax), eax=eax,
            edx=0)
        run('517644', 0x489f90, lambda: n.vertrix_object_table_517644(
            c.byref(calls), c.byref(services), 0, 0), eax=0, edx=0)
        for address, mode in ((0x4b4600, 0), (0x4b4610, 1), (0x4b4620, 2)):
            run('step', address, lambda: n.vertrix_object_step_text_length(
                c.byref(calls), obj, buffer, SIZE, mode), eax=obj, edx=0)
        for address, field in ((0x4b5500, 0x15c), (0x4b6700, 0x172)):
            run('present', address, lambda: n.vertrix_object_slot_present(
                c.byref(calls), buffer, SIZE, field, obj), eax=obj, edx=0)
        edx = rng.getrandbits(32)
        run('a2f0', 0x48a2f0, lambda: n.vertrix_forward_a2f0(c.byref(calls), obj, edx), eax=obj,
            edx=edx)
        ebx, ecx = rng.getrandbits(32), rng.getrandbits(32)
        run('pair', 0x471e10, lambda: n.vertrix_list_notify_pair(c.byref(calls), ecx, ebx),
            eax=ecx, edx=0, ebx=ebx)
        run('hit', 0x4725f0, lambda: n.vertrix_list_clear_hit(c.byref(calls), c.byref(services),
                                                               ebx, ecx), eax=0, edx=0, ebx=ebx,
            ecx=ecx)
        run('516d34', 0x484a60, lambda: n.vertrix_object_table_516d34(
            c.byref(calls), c.byref(services), obj), eax=obj, edx=0)
        run('unowned', 0x4b5d40, lambda: n.vertrix_object_slot_present_unowned(
            c.byref(calls), buffer, SIZE, obj), eax=obj, edx=0)
        run('release', 0x4b6020, lambda: n.vertrix_object_release_items(
            c.byref(calls), c.byref(services), buffer, SIZE), eax=obj, edx=0)
        for address, name in ((0x48d330, 'table'), (0x48d500, 'ones')):
            original.call(address, eax=obj)
            got = getattr(n, 'vertrix_object_clear_with_' + name)(buffer, SIZE, obj)
            assert got == obj and pool.same(), (name, pool.diff())
            totals[hex(address)] = totals.get(hex(address), 0) + 1
        for handle in pool.handles:
            pointer = struct.pack('<I', rng.choice(pool.handles))
            cpu.mem_write(handle + 0x15c, pointer)
            pool.buffers[handle][0x15c:0x160] = pointer
            cpu.mem_write(handle + 0x160, pointer)
            pool.buffers[handle][0x160:0x164] = pointer
        run('reset', 0x4b4630, lambda: n.vertrix_object_text_length_reset(
            c.byref(calls), c.byref(services), obj, buffer, SIZE), eax=obj, edx=0)
        original.call(0x48d480, eax=obj)
        assert n.vertrix_object_clear_block(buffer, SIZE)
        assert pool.same(), ('clear', pool.diff())
        totals['0x48d480'] = totals.get('0x48d480', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Each wrapper executes completely in the original with its callees stubbed '
                       'and logged; every callee call, the returned eax, the flag 0x532a08 and every '
                       'pool object compare.'}
    (args.build_dir / 'object-tails-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
