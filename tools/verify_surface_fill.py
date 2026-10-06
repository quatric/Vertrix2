"""Compare the original surface fill 0x478f50 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, build

U = c.c_uint32
SIZE = 0x200
STATE = 0x5589f4
STATE_SIZE = 0x60


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'surface-fill',
              ['surface_fill.c', 'object_value_helpers.c', 'actor_storage.c'])
    n.vertrix_surface_fill.argtypes = [c.POINTER(Services), U, U, c.POINTER(U)]
    n.vertrix_surface_fill.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x478f50)
    pool = Pool(cpu, 2, SIZE)
    surface, pixels = pool.handles
    state = c.create_string_buffer(STATE_SIZE)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == STATE:
            storage[0], size[0] = c.addressof(state), STATE_SIZE
            return 1
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    totals = {'flat': 0, 'rows': 0}
    for case in range(args.cases):
        flat = rng.random() < 0.5
        values = dict(width=rng.randrange(0, 7), height=rng.randrange(0, 6),
                      bytes=rng.choice([1, 2, 4, 4, 2, 1, 3, 8, 0]), format=rng.randrange(0, 4),
                      pitch=rng.randrange(0, 17))

        def patch(handle, data):
            if handle == surface:
                struct.pack_into('<III', data, 0, pixels, values['width'], values['height'])
                data[0xc], data[0xd] = values['bytes'], values['format']
                struct.pack_into('<I', data, 0x10, 0 if flat else rng.randrange(1, 9))
                struct.pack_into('<I', data, 0x18, values['pitch'])

        pool.fill(rng, patch)
        blob = rng.randbytes(STATE_SIZE)
        state.raw = blob
        cpu.mem_write(STATE, blob)
        colour = rng.getrandbits(32)
        want = original.call(0x478f50, eax=surface, edx=colour) & 0xffffffff
        result = U()
        assert n.vertrix_surface_fill(c.byref(services), surface, colour, c.byref(result)), case
        assert result.value == want, (case, result.value, want)
        assert state.raw == bytes(cpu.mem_read(STATE, STATE_SIZE)), case
        assert pool.same(), (case, pool.diff())
        totals['flat' if flat else 'rows'] += 1
    report = {'status': 'passed', 'complete_original_executions': {'0x478f50': totals},
              'scope': 'The routine executes completely in the original (0x479a40 included); the '
                       'returned eax, the scratch globals 0x5589f4 up to 0x558a50 and the filled '
                       'pixel memory compare.'}
    (args.build_dir / 'surface-fill-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
