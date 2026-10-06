"""Compare the original list text readers with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x200
LABEL_FRAME = STACK - 4


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third',
                                       'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


class Spec(c.Structure):
    _fields_ = [(name, U) for name in ('name', 'field', 'format_ebx', 'format_edx', 'format_ecx')]


CALLEES = {0x4b6fa0: (0, False), 0x4ca280: (0, False), 0x415ed0: (0, False), 0x4ca370: (0, False),
           0x4ca310: (0, False), 0x4cdfb0: (3, True), 0x4ccfe0: (0, False),
           0x4ca070: (0, False), 0x4ca210: (0, False), 0x4ca000: (0, False), 0x4b79c0: (0, False),
           0x4ca090: (0, False), 0x4d88a0: (0, False), 0x4ca050: (0, False), 0x4ca600: (0, False), 0x4ca4a0: (4, False), 0x4ca430: (2, False), 0x4cda12: (0, False), 0x4cda10: (0, False), 0x47faf0: (0, False),
           0x4d8770: (0, False)}
SPECS = ((0x4b7080, Spec(0x5110bc, 0, 0x4f80e4, 0x532c44, 3)),
         (0x4b7120, Spec(0x5110bd, 4, 0x4f80f0, 0x532c50, 0xa)),
         (0x4b71c0, Spec(0x5110be, 8, 0x4f8118, 0x532c78, 2)),
         (0x4b7260, Spec(0x5110bf, 0xc, 0x4f8120, 0x532c80, 2)),
         (0x4b7300, Spec(0x5110c0, 0x10, 0x4f8168, 0x532c88, 2)))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'list-text', ['list_text.c', 'call_glue.c', 'actor_storage.c', 'rtl_glue.c'])
    P, S = c.POINTER(Calls), c.POINTER(Services)
    n.vertrix_list_text_dword.argtypes = [P, S, c.POINTER(Spec), U, U, U]
    n.vertrix_list_text_name.argtypes = [P, U, U, U]
    n.vertrix_list_text_format.argtypes = [P, S, U, U, U]
    n.vertrix_list_cycle.argtypes = [P, S, U, c.c_void_p, c.c_size_t, c.c_uint]
    n.vertrix_object_label_format.argtypes = [P, S, U, U, U, c.c_void_p, c.c_size_t]
    n.vertrix_object_label_format.restype = U
    n.vertrix_object_label_format_alternate.argtypes = n.vertrix_object_label_format.argtypes
    n.vertrix_object_label_format_alternate.restype = U
    n.vertrix_list_cycle.restype = U
    n.vertrix_object_load_script.argtypes = [P, U, U]
    n.vertrix_object_load_script.restype = U
    n.vertrix_clock_text.argtypes = [P, U, U, U]
    n.vertrix_clock_text.restype = U
    n.vertrix_object_describe.argtypes = [P, S, U, U]
    n.vertrix_object_describe.restype = U
    n.vertrix_list_text_lookup.argtypes = [P, S, U, U, U, U, U]
    n.vertrix_list_text_lookup.restype = U
    n.vertrix_list_text_lookup_slot.argtypes = [P, S, U, U, U, U, U]
    n.vertrix_list_text_lookup_slot.restype = U
    n.vertrix_list_resize_call.argtypes = [P, S, U, U, U, U]
    n.vertrix_list_resize_call.restype = U
    n.vertrix_list_release_entries.argtypes = [P, S, U]
    n.vertrix_list_release_entries.restype = U
    n.vertrix_list_text_indexed.argtypes = [P, S, U, U, U]
    n.vertrix_list_text_indexed.restype = U
    for name in ('dword', 'name', 'format'):
        getattr(n, 'vertrix_list_text_' + name).restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4b7080)
    pool = Pool(cpu, 8, SIZE)
    returns, native_log, replay = [], [], []

    outs = []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4cdfb0 and stack[0] in (LABEL_FRAME - 0x14, LABEL_FRAME - 0x18):
            outs.append(rng.getrandbits(32))
            cpu.mem_write(stack[0], struct.pack('<I', outs[-1]))
        if address in (0x4b6fa0, 0x4b79c0):
            returns.append(rng.choice(pool.handles + [0]))
        elif address in (0x4ca000, 0x4ca090):
            returns.append(rng.choice([0, 1, rng.getrandbits(32)]))
        elif address == 0x4ccfe0:
            returns.append(rng.choice([0, 0, 1, rng.getrandbits(32)]))
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, (count, cdecl) in CALLEES.items():
        stubs.add(address, count, cdecl)

    @Call
    def call(site, context):
        s = site.contents
        count = CALLEES[s.target][0]
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) +
                          (s.stack, s.stack_next, s.stack_third, s.rest0)[:count])
        if s.target == 0x4cdfb0 and s.stack in (LABEL_FRAME - 0x14, LABEL_FRAME - 0x18):
            s.out_value = outs.pop(0)
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    totals = {}

    def run(name, address, native, compare=True, **registers):
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(address, **registers) & 0xffffffff
        replay[:] = list(returns)
        got = native()
        assert not compare or got == result, (name, hex(got), hex(result))
        assert native_log == stubs.log, (name, native_log, stubs.log)
        assert not replay, name
        assert pool.same(), (name, pool.diff())
        totals[hex(address)] = totals.get(hex(address), 0) + 1

    for case in range(args.cases):
        def patch(handle, data):
            struct.pack_into('<I', data, 0x160, rng.choice(pool.handles))
            struct.pack_into('<I', data, 0x170, rng.choice(pool.handles))
            struct.pack_into('<I', data, 0x174, rng.randrange(0, 9))
            struct.pack_into('<I', data, 4, rng.choice(pool.handles))
            struct.pack_into('<I', data, 8, rng.randrange(0, 9))

        pool.fill(rng, patch)
        reader, slot, ebx = rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32)
        for address, spec in SPECS:
            run('dword', address, lambda: n.vertrix_list_text_dword(
                c.byref(calls), c.byref(services), c.byref(spec), reader, slot, ebx), eax=reader,
                edx=slot, ebx=ebx)
        run('name', 0x4b73a0, lambda: n.vertrix_list_text_name(c.byref(calls), reader, slot, ebx),
            eax=reader, edx=slot, ebx=ebx)
        obj = rng.choice(pool.handles)
        for address, mode in ((0x4b3740, 0), (0x4b37e0, 1), (0x4b3880, 2), (0x4b3940, 3)):
            run('cycle', address, lambda: n.vertrix_list_cycle(
                c.byref(calls), c.byref(services), obj, pool.buffers[obj], SIZE, mode), eax=obj)
        run('format', 0x4b7420, lambda: n.vertrix_list_text_format(
            c.byref(calls), c.byref(services), reader, slot, ebx), eax=reader, edx=slot, ebx=ebx)
        index = rng.randrange(0, 12)
        run('indexed', 0x4b7710, lambda: n.vertrix_list_text_indexed(
            c.byref(calls), c.byref(services), obj, slot, index), eax=obj, edx=slot, ebx=index)
        run('resize', 0x4b76d0, lambda: n.vertrix_list_resize_call(
            c.byref(calls), c.byref(services), obj, slot, ebx, reader), eax=obj, edx=slot, ebx=ebx,
            ecx=reader)
        run('release', 0x4b7830, lambda: n.vertrix_list_release_entries(
            c.byref(calls), c.byref(services), obj), eax=obj, compare=False)
        run('lookup', 0x4b79e0, lambda: n.vertrix_list_text_lookup(
            c.byref(calls), c.byref(services), STACK - 16, reader, slot, ebx, index), eax=reader,
            edx=slot, ebx=ebx, ecx=index)
        run('lookup_slot', 0x48a300, lambda: n.vertrix_list_text_lookup_slot(
            c.byref(calls), c.byref(services), STACK, reader, slot, ebx, index), eax=reader,
            edx=slot, ebx=ebx, ecx=index)
        value = rng.getrandbits(32)
        outs.clear()
        run('label', 0x4b4fb0, lambda: n.vertrix_object_label_format(
            c.byref(calls), c.byref(services), LABEL_FRAME, obj, value, pool.buffers[obj], SIZE),
            eax=obj, edx=value)
        outs.clear()
        run('label', 0x4b3c40, lambda: n.vertrix_object_label_format_alternate(
            c.byref(calls), c.byref(services), LABEL_FRAME, obj, value, pool.buffers[obj], SIZE),
            eax=obj, edx=value)
    for case in range(args.cases):
        def kind_patch(handle, data):
            data[0xd] = rng.choice([0, 1, 2, 3, 4, 5, rng.getrandbits(8)])
            struct.pack_into('<I', data, 0x10, rng.choice([1, 0, rng.getrandbits(32)]))

        pool.fill(rng, kind_patch)
        obj = rng.choice(pool.handles)
        run('describe', 0x478dd0, lambda: n.vertrix_object_describe(
            c.byref(calls), c.byref(services), LABEL_FRAME, obj), compare=False, eax=obj)
    for case in range(args.cases):
        pool.fill(rng)
        obj = rng.choice(pool.handles)
        outs.clear()
        run('script', 0x416a80, lambda: n.vertrix_object_load_script(
            c.byref(calls), LABEL_FRAME, obj), compare=False, eax=obj)
    for case in range(args.cases):
        pool.fill(rng)
        variable = rng.choice(pool.handles)
        value = rng.choice([rng.randrange(0, 100), rng.getrandbits(32)])
        outs.clear()
        run('clock', 0x418170, lambda: n.vertrix_clock_text(c.byref(calls), LABEL_FRAME, variable,
                                                           value), eax=variable, edx=value)
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Each reader executes completely in the original, exception frame included, '
                       'with its callees stubbed and logged (0x4cdfb0 as a cdecl call); every callee '
                       'call and the returned slot compare.'}
    (args.build_dir / 'list-text-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
