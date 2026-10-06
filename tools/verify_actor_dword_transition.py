"""Compare the original dword transitions 0x4ad6e0 and 0x4ad790 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import build

ACTOR, SIZE = 0x80a000, 0x200
U = c.c_uint32


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=8192)
    args = parser.parse_args()
    n = build(args.build_dir, 'actor-dword-transition', ['dword_transition.c', 'actor_storage.c'])
    n.vertrix_actor_dword_transition.argtypes = [c.c_void_p, c.c_size_t, c.c_size_t, U,
                                                 c.POINTER(U)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4ad790)
    totals = {}
    edges = [0, 1, 0x7fffffff, 0x80000000, 0xffffffff, 100, 0xffffff9c]
    for case in range(args.cases):
        address, first = ((0x4ad6e0, 0x58), (0x4ad790, 0x70))[case % 2]
        raw = bytearray(rng.randbytes(SIZE))
        for offset in range(3):
            if rng.random() < 0.5:
                struct.pack_into('<I', raw, first + 4 * offset, rng.choice(edges))
        if rng.random() < 0.2:
            struct.pack_into('<I', raw, first + 4, struct.unpack_from('<I', raw, first)[0])
        cycles = rng.choice(edges + [rng.randrange(1 << 32), rng.randrange(0, 50)])
        cpu.mem_write(ACTOR, bytes(raw))
        result = original.call(address, eax=ACTOR, edx=cycles) & 0xff
        native = c.create_string_buffer(bytes(raw), SIZE)
        moving = U()
        assert n.vertrix_actor_dword_transition(native, SIZE, first, cycles, c.byref(moving)), case
        assert moving.value == result, (case, moving.value, result)
        assert native.raw == bytes(cpu.mem_read(ACTOR, SIZE)), case
        key = hex(address) + ('_moving' if result else '_arrived')
        totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 4ad6e0 and 4ad790 execute in the original over edge and random '
                       'fields; the result and the whole object compare.'}
    (args.build_dir / 'actor-dword-transition-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
