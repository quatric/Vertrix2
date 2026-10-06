"""Compare original first-ID object lookup used by player-linked effects."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original, BOARD, MASK


class ObjectList(c.Structure):
    _fields_ = [('items', c.POINTER(c.c_uint32)), ('count', c.c_size_t), ('capacity', c.c_size_t)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source/object_list.c'
    library = args.build_dir.resolve() / 'find.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', str(source), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    resolver_type = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_uint32), c.c_void_p)
    native.vertrix_object_list_find.argtypes = [c.POINTER(ObjectList), c.c_uint32, resolver_type, c.c_void_p, c.POINTER(c.c_uint32)]
    original = Original(args.executable)
    rng = random.Random(0x4b5eb0)
    matches = 0
    for case in range(2048):
        count = rng.randrange(65)
        handles = [0x804000 + 64 * i for i in range(count)]
        ids = [rng.randrange(16) if case % 2 else rng.getrandbits(32) for _ in handles]
        query = rng.choice(ids) if ids and case % 3 else rng.getrandbits(32)
        original.cpu.mem_write(MASK, struct.pack('<' + 'I' * count, * handles) or bytes(4))
        raw = bytearray(rng.randbytes(16))
        struct.pack_into('<2I', raw, 4, MASK, count)
        original.cpu.mem_write(BOARD, bytes(raw))
        identities = dict(zip(handles, ids))
        for handle, identity in identities.items():
            original.cpu.mem_write(handle, struct.pack('<I', identity))
        visits = []
        @ resolver_type
        def resolve(handle, value, context):
            visits.append(handle)
            value[0] = identities[handle]
            return 1
        storage = (c.c_uint32 * count)(* handles)
        listing = ObjectList(storage, count, count)
        result = c.c_uint32(0x12345678)
        expected = original.call(0x4b5eb0, eax=BOARD, edx=query)
        assert native.vertrix_object_list_find(c.byref(listing), query, resolve, None, c.byref(result))
        assert result.value == expected
        expected_visits = handles[: handles.index(expected) + 1] if expected else handles
        assert visits == expected_visits
        assert bytes(raw) == bytes(original.cpu.mem_read(BOARD, len(raw)))
        assert list(storage) == handles
        matches += bool(expected)
        @ resolver_type
        def unresolved(handle, value, context):
            return 0
        listing = ObjectList((c.c_uint32 * 1)(1), 1, 1)
        result = c.c_uint32(123)
        assert not native.vertrix_object_list_find(c.byref(listing), 1, unresolved, None, c.byref(result))
        assert result.value == 123
        listing.count = 2
        assert not native.vertrix_object_list_find(c.byref(listing), 1, unresolved, None, c.byref(result))
        assert result.value == 123
    report = {'status': 'passed', 'cases': 2048, 'matches': matches, 'scope': 'Original 0x4b5eb0 without hooks; first duplicate ID, missing/empty lists, ' 'read order and unchanged list storage. Player/resource integration remains unfinished.'}
    (args.build_dir / 'object-find-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
