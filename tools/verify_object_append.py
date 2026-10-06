"""Compare scene registration append within reserved original storage."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original, MASK


class List(c.Structure):
    _fields_ = [('items', c.POINTER(c.c_uint32)), ('count', c.c_size_t), ('capacity', c.c_size_t)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'object-append.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', str(source / 'object_list.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_object_list_append.argtypes = [c.POINTER(List), c.c_uint32]
    original = Original(args.executable)
    rng = random.Random(0x4b5e70)
    for case in range(2048):
        capacity = rng.randrange(1, 129)
        count = rng.randrange(capacity)
        values = [rng.randrange(1, 2 ** 32) for _ in range(capacity)]
        handle = rng.choice(values) if case % 2 else rng.randrange(1, 2 ** 32)
        original.cpu.mem_write(0x803000, struct.pack('<' + 'I' * capacity, * values))
        descriptor = struct.pack('<5I', 0, 0x803000, count, capacity, 0)
        original.cpu.mem_write(MASK, descriptor)
        assert original.call(0x4b5e70, eax=MASK, edx=handle) == 0
        items = (c.c_uint32 * capacity)(* values)
        listed = List(items, count, capacity)
        assert native.vertrix_object_list_append(c.byref(listed), handle)
        expected = bytearray(descriptor)
        struct.pack_into('<I', expected, 8, count + 1)
        assert bytes(original.cpu.mem_read(MASK, len(descriptor))) == bytes(expected)
        assert bytes(items) == bytes(original.cpu.mem_read(0x803000, capacity * 4))
        assert listed.count == count + 1 and listed.capacity == capacity
    before = bytes(items)
    listed.count = listed.capacity
    assert not native.vertrix_object_list_append(c.byref(listed), handle)
    assert bytes(items) == before and listed.count == listed.capacity
    listed.count = 0
    assert not native.vertrix_object_list_append(c.byref(listed), 0)
    assert bytes(items) == before and listed.count == 0
    report = {'status': 'passed', 'cases': 2048, 'scope': 'Complete original4b5e70/4d88a0/4d8770 append with reserved capacity ' 'executes without hooks. Whole original descriptor and all list slots match ' 'native registration, including duplicate handles and stale tail storage. ' 'Full/null-handle rejection checked natively. Allocation growth is external ' 'and outside this proof; full scene registration/application remains unfinished.'}
    (args.build_dir / 'object-append-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
