"""Compare complete original one-field accessors (settings, score, stream objects) with the native
recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, build

U = c.c_uint32
SIZE = 0x500


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'field-accessors', ['field_accessors.c', 'actor_storage.c'])
    P, SZ, UP = c.c_void_p, c.c_size_t, c.POINTER(U)
    for name in ('flip_454',):
        getattr(n, 'vertrix_object_' + name).argtypes = [P, SZ]
    n.vertrix_object_set_464.argtypes = [P, SZ, U]
    for name in ('get_464', 'get_174', 'get_178'):
        getattr(n, 'vertrix_object_' + name).argtypes = [P, SZ, UP]
    n.vertrix_global_index_bytes.argtypes = [P]
    for name in ('flags_clear', 'flags_set', 'stream_init', 'stream_set_class', 'rect_commit'):
        getattr(n, 'vertrix_' + name).argtypes = [P, SZ]
    for name in ('flags_get', 'flags_idle', 'progress_done', 'progress_quotient', 'dword_set'):
        getattr(n, 'vertrix_' + name).argtypes = [P, SZ, UP]
    n.vertrix_flags_dword.argtypes = [P, SZ, c.c_uint, UP]
    n.vertrix_progress_set_40.argtypes = [P, SZ, U]
    n.vertrix_progress_set_3c.argtypes = [P, SZ, U]
    n.vertrix_rect_set.argtypes = [P, SZ] + [c.c_uint16] * 4
    n.vertrix_surface_cell_address.argtypes = [P, SZ, U, U, UP]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x471e60)
    pool = Pool(cpu, 2, SIZE)
    obj = pool.handles[0]
    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    def fresh():
        def patch(handle, data):
            for offset in (0x44, 0x48, 0x454):
                struct.pack_into('<I', data, offset, rng.choice([0, 1, 2, rng.getrandbits(32)]))
            data[0x5a] = rng.choice([0, 1, rng.getrandbits(8)])
        pool.fill(rng, patch)

    def buf():
        return pool.buffers[obj]

    def mutate(address, name, native, **registers):
        fresh()
        cpu.mem_write(0x540f88, struct.pack('<I', obj))
        registers.setdefault('eax', obj)
        original.call(address, **registers)
        assert native(), (name, 'rejected')
        assert pool.same(), (name, pool.diff())
        count(name)

    def query(address, name, native, mask=0xffffffff, **registers):
        fresh()
        expect = original.call(address, eax=obj, **registers) & mask
        out = U()
        assert native(c.byref(out)), name
        assert out.value == expect, (name, out.value, expect)
        count(name)

    for case in range(args.cases):
        value = rng.getrandbits(32)
        for address, global_cell in ((0x471e60, 0x540f8c), (0x471e80, 0x540f90)):
            fresh()
            cpu.mem_write(global_cell, struct.pack('<I', obj))
            original.call(address)
            assert n.vertrix_object_flip_454(buf(), SIZE)
            assert pool.same(), (case, hex(address))
            count(hex(address))
        cpu.mem_write(0x540f88, struct.pack('<I', obj))
        mutate(0x471ea0, '0x471ea0', lambda: n.vertrix_object_set_464(buf(), SIZE, value),
               eax=0, edx=value)
#table index 0 selects the object at 0x540f88 in the original
        original_get = lambda a, i=0: original.call(a, eax=i)
        for address, fn in ((0x471eb0, n.vertrix_object_get_464),
                            (0x471ec0, n.vertrix_object_get_174),
                            (0x471ed0, n.vertrix_object_get_178)):
            fresh()
            cpu.mem_write(0x540f88, struct.pack('<I', obj))
            expect = original_get(address)
            out = U()
            assert fn(buf(), SIZE, c.byref(out)) and out.value == expect, (case, hex(address))
            count(hex(address))
        data = bytes(rng.randbytes(7))
        cpu.mem_write(0x53bcc8, data)
        original.call(0x45f1e0)
        native = (c.c_uint8 * 7)(*data)
        n.vertrix_global_index_bytes(native)
        assert bytes(native) == bytes(cpu.mem_read(0x53bcc8, 7)), case
        count('0x45f1e0')
        mutate(0x4757b0, '0x4757b0', lambda: n.vertrix_flags_clear(buf(), SIZE))
        mutate(0x4759d0, '0x4759d0', lambda: n.vertrix_flags_set(buf(), SIZE))
        query(0x475800, '0x475800', lambda o: n.vertrix_flags_get(buf(), SIZE, o), mask=0xff)
        for address, index in ((0x475810, 1), (0x475820, 2), (0x475830, 3)):
            query(address, hex(address), lambda o: n.vertrix_flags_dword(buf(), SIZE, index, o))
        query(0x475b00, '0x475b00', lambda o: n.vertrix_flags_idle(buf(), SIZE, o), mask=0xff)
        mutate(0x475dd0, '0x475dd0', lambda: n.vertrix_progress_set_40(buf(), SIZE, value),
               edx=value)
        mutate(0x475e40, '0x475e40', lambda: n.vertrix_progress_set_3c(buf(), SIZE, value),
               edx=value)
        query(0x475df0, '0x475df0', lambda o: n.vertrix_progress_done(buf(), SIZE, o), mask=0xff)
        query(0x475e10, '0x475e10', lambda o: n.vertrix_progress_quotient(buf(), SIZE, o))
        mutate(0x477240, '0x477240', lambda: n.vertrix_stream_init(buf(), SIZE))
        mutate(0x477870, '0x477870', lambda: n.vertrix_stream_set_class(buf(), SIZE))
        words = [rng.getrandbits(16) for _ in range(4)]
        mutate(0x477e10, '0x477e10', lambda: n.vertrix_rect_set(buf(), SIZE, *words),
               edx=words[0], ebx=words[1], ecx=words[2], args=(words[3],))
        mutate(0x478460, '0x478460', lambda: n.vertrix_rect_commit(buf(), SIZE))
        row, column = rng.getrandbits(32), rng.getrandbits(32)
        query(0x479b30, '0x479b30',
              lambda o: n.vertrix_surface_cell_address(buf(), SIZE, row, column, o),
              edx=column, ebx=row)
        query(0x47e990, '0x47e990', lambda o: n.vertrix_dword_set(buf(), SIZE, o), mask=0xff)
    assert not n.vertrix_stream_init(buf(), 0x17)
    assert not n.vertrix_rect_set(buf(), 0x43, 1, 2, 3, 4)
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 471e60, 471e80, 471ea0, 471eb0, 471ec0, 471ed0, 45f1e0, 4757b0, '
                       '475800, 475810, 475820, 475830, 4759d0, 475b00, 475dd0, 475df0, 475e10, '
                       '475e40, 477240, 477870, 477e10, 478460, 479b30 and 47e990 execute in the '
                       'original; whole objects, globals and returned values compare.'}
    (args.build_dir / 'field-accessors-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
