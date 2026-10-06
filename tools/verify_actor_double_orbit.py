"""Compare the original orbit points 0x4ad3c0 and 0x4ad440 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import build

ACTOR, SIZE, OUT = 0x80a000, 0x200, 0x80b000
X_TABLE, Y_TABLE, SCRATCH = 0x59939c, 0x598dfc, 0x5bb620


class Tables(c.Structure):
    _fields_ = [('x', c.c_int32 * 360), ('y', c.c_int32 * 360)]


class Chain(c.Structure):
    _fields_ = [('x', c.c_int32), ('y', c.c_int32), ('first_x', c.c_uint16), ('first_y', c.c_uint16)]


class Scratch(c.Structure):
    _fields_ = [('x', c.c_int32), ('y', c.c_int32), ('radius', c.c_int32)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=8192)
    args = parser.parse_args()
    n = build(args.build_dir, 'actor-double-orbit', ['actor_angle.c', 'actor_storage.c', 'fixed_point.c'])
    n.vertrix_actor_double_orbit_point.argtypes = [
        c.c_void_p, c.c_size_t, c.POINTER(Tables), c.POINTER(c.c_uint16), c.POINTER(c.c_uint16),
        c.POINTER(Scratch)]
    n.vertrix_actor_chain_orbit_point.argtypes = [
        c.c_void_p, c.c_size_t, c.POINTER(Tables), c.POINTER(c.c_uint16), c.POINTER(c.c_uint16),
        c.POINTER(Chain)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4ad3c0)
    totals = {}
    for case in range(args.cases):
        raw = bytearray(rng.randbytes(SIZE))
        struct.pack_into('<H', raw, 0x24, rng.randrange(360))
        struct.pack_into('<H', raw, 0x34, rng.randrange(360))
        if rng.random() < 0.5:
            for offset in (0x2a, 0x3a):
                struct.pack_into('<h', raw, offset, rng.randrange(-300, 300))
        tables = Tables((c.c_int32 * 360)(*[rng.randrange(-70000, 70000) for _ in range(360)]),
                        (c.c_int32 * 360)(*[rng.randrange(-70000, 70000) for _ in range(360)]))
        cpu.mem_write(ACTOR, bytes(raw))
        cpu.mem_write(X_TABLE, bytes(tables.x))
        cpu.mem_write(Y_TABLE, bytes(tables.y))
        cpu.mem_write(OUT, bytes(8))
        cpu.mem_write(SCRATCH, rng.randbytes(0x18))
        x, y = c.c_uint16(), c.c_uint16()
        native = c.create_string_buffer(bytes(raw), SIZE)
        if case % 2 == 0:
            original.call(0x4ad3c0, eax=ACTOR, edx=OUT, ebx=OUT + 4)
            scratch = Scratch()
            assert n.vertrix_actor_double_orbit_point(native, SIZE, c.byref(tables), c.byref(x),
                                                      c.byref(y), c.byref(scratch)), case
            assert struct.unpack('<iii', bytes(cpu.mem_read(SCRATCH, 12))) == \
                (scratch.x, scratch.y, scratch.radius), case
            name = '0x4ad3c0'
        else:
            original.call(0x4ad440, eax=ACTOR, edx=OUT, ebx=OUT + 4)
            chain = Chain()
            assert n.vertrix_actor_chain_orbit_point(native, SIZE, c.byref(tables), c.byref(x),
                                                     c.byref(y), c.byref(chain)), case
            assert struct.unpack('<iiHH', bytes(cpu.mem_read(SCRATCH + 12, 12))) == \
                (chain.x, chain.y, chain.first_x, chain.first_y), case
            name = '0x4ad440'
        assert struct.unpack('<HH', bytes(cpu.mem_read(OUT, 2)) + bytes(cpu.mem_read(OUT + 4, 2))) \
            == (x.value, y.value), case
        assert native.raw == bytes(cpu.mem_read(ACTOR, SIZE)), case
        totals[name] = totals.get(name, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 4ad3c0 and 4ad440 execute in the original over random actors and tables; '
                       'the two output words, the scratch globals and the object compare.'}
    (args.build_dir / 'actor-double-orbit-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
