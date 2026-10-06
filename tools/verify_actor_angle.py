"""Compare complete original actor angle routines with the native recovery."""
import argparse, ctypes as c, json, random, struct
from pathlib import Path
from original import Original
from oracle_kit import build

ACTOR, SIZE = 0x801000, 0x200
X_TABLE, Y_TABLE = 0x59939c, 0x598dfc
U = c.c_uint32


class Tables(c.Structure):
    _fields_ = [('x', c.c_int32 * 360), ('y', c.c_int32 * 360)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'actor-angle', ['actor_angle.c', 'actor_storage.c', 'fixed_point.c'])
    S, Z, T = c.c_void_p, c.c_size_t, c.POINTER(Tables)
    n.vertrix_actor_spin.argtypes = [S, Z, U]
    n.vertrix_actor_turn_toward.argtypes = [S, Z, c.c_int32, c.POINTER(U)]
    for name in ('polar_offset', 'polar_offset_second'):
        getattr(n, 'vertrix_actor_' + name).argtypes = [S, Z, T, c.c_int32, c.c_int32,
                                                        c.POINTER(c.c_int32), c.POINTER(c.c_int32)]
    n.vertrix_actor_orbit_point.argtypes = [S, Z, T, c.POINTER(c.c_uint16), c.POINTER(c.c_uint16)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4ace40)
    xs = [rng.randrange(-70000, 70000) for _ in range(360)]
    ys = [rng.randrange(-70000, 70000) for _ in range(360)]
    cpu.mem_write(X_TABLE, struct.pack('<360i', *xs))
    cpu.mem_write(Y_TABLE, struct.pack('<360i', *ys))
    tables = Tables((c.c_int32 * 360)(*xs), (c.c_int32 * 360)(*ys))
    totals, invalid = {}, 0

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    def signed(v):
        return v - (1 << 32) if v & 0x80000000 else v

    def angle():
        return rng.choice([0, 1, 359, 360, 361, 0x7fff, 0x8000, 0xffff, 0xfffe, rng.randrange(360),
                           rng.randrange(360), rng.getrandbits(16), (-rng.randrange(1, 400)) & 0xffff])

    for case in range(args.cases):
        raw = bytearray(rng.randbytes(SIZE))
        for off in (0x24, 0x26, 0x34):
            struct.pack_into('<H', raw, off, angle())
        struct.pack_into('<H', raw, 0x28, rng.choice([0, 1, 2, 5, 90, 0xffff, 0xfffb, 0x8000, rng.getrandbits(16)]))
        struct.pack_into('<H', raw, 0x38, rng.choice([0, 1, 5, 90, 0xffff, 0xfffb, 359, 360, rng.getrandbits(16)]))
        if rng.random() < 0.3:
            struct.pack_into('<H', raw, 0x26, struct.unpack_from('<H', raw, 0x24)[0])
        if rng.random() < 0.5:
            for off in (0x24, 0x34):
                struct.pack_into('<H', raw, off, rng.randrange(360))
        rate = struct.unpack_from('<h', raw, 0x38)[0]

        def run(address, **registers):
            cpu.mem_write(ACTOR, bytes(raw))
            result = original.call(address, eax=ACTOR, **registers)
            return result, bytes(cpu.mem_read(ACTOR, SIZE))

        def fresh():
            return c.create_string_buffer(bytes(raw), SIZE)

# 4ad110 spin(loop count kept small)
        steps = rng.choice([0, 1, 2, 3, 10, rng.randrange(60)])
        result, after = run(0x4ad110, edx=steps)
        buffer = fresh()
        assert n.vertrix_actor_spin(buffer, SIZE, steps) == result & 0xffffffff, ('spin', case)
        assert buffer.raw == after, ('spin', case)
        count('spin')
# 4ace40 turn toward
        mult = rng.choice([0, 1, 2, 3, 0xffffffff, 0xfffffffe, 10, rng.randrange(20),
                           (-rng.randrange(20)) & 0xffffffff, rng.getrandbits(32)])
        result, after = run(0x4ace40, edx=mult)
        buffer = fresh()
        out = U()
        assert n.vertrix_actor_turn_toward(buffer, SIZE, signed(mult), c.byref(out))
        assert buffer.raw == after and out.value == result & 0xff, ('turn', case)
        count('turn_toward')
#polar offsets : 4ad1c0(angle + 0x24) and 4ad210(angle + 0x34)
        rx, ry = (rng.choice([0, 1, 0xffffffff, rng.getrandbits(32), rng.randrange(-300, 300) & 0xffffffff])
                  for _ in range(2))
        for address, name, off in ((0x4ad1c0, 'polar_offset', 0x24), (0x4ad210, 'polar_offset_second', 0x34)):
            ax, ay = U(), U()
            cpu.mem_write(0x808000, bytes(8))
            cpu.mem_write(ACTOR, bytes(raw))
            valid = 0 <= struct.unpack_from('<h', raw, off)[0] < 360
            ox, oy = c.c_int32(), c.c_int32()
            got = getattr(n, 'vertrix_actor_' + name)(fresh(), SIZE, c.byref(tables), signed(rx),
                                                      signed(ry), c.byref(ox), c.byref(oy))
            if not valid:
                assert not got
                continue
            original.call(address, eax=ACTOR, edx=rx, ebx=ry, ecx=0x808000, args=(0x808004,))
            ex, ey = struct.unpack('<ii', bytes(cpu.mem_read(0x808000, 8)))
            assert got and (ox.value, oy.value) == (ex, ey), (name, case)
            count(name)
# 4ad260 orbit point
        struct.pack_into('<H', raw, 0x24, rng.randrange(360) if rng.random() < 0.9 else angle())
        valid = 0 <= struct.unpack_from('<h', raw, 0x24)[0] < 360
        x, y = c.c_uint16(), c.c_uint16()
        got = n.vertrix_actor_orbit_point(fresh(), SIZE, c.byref(tables), c.byref(x), c.byref(y))
        if valid:
            cpu.mem_write(ACTOR, bytes(raw))
            cpu.mem_write(0x808000, bytes(8))
            original.call(0x4ad260, eax=ACTOR, edx=0x808000, ebx=0x808002)
            ex, ey = struct.unpack('<HH', bytes(cpu.mem_read(0x808000, 4)))
            assert got and (x.value, y.value) == (ex, ey), ('orbit', case)
            count('orbit_point')
        else:
            assert not got
            invalid += 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'out_of_table_angles_rejected': invalid,
              'scope': 'Complete 4ad110, 4ace40, 4ad1c0, 4ad210 and 4ad260 execute in the original over '
                       'random actors and random 360-entry tables; whole object, results and outputs '
                       'compare. Angles outside 0..359 would read past the tables in the original and '
                       'are rejected natively. Scratch globals 0x5bb5dc..0x5bb608 are dead temporaries.'}
    (args.build_dir / 'actor-angle-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
