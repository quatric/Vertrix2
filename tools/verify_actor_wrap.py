"""Compare the original counter wraps 0x4ac5b0 and 0x4ac6b0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import build

ACTOR, SIZE = 0x80a000, 0x200


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=8192)
    args = parser.parse_args()
    n = build(args.build_dir, 'actor-wrap', ['actor_fields.c', 'actor_storage.c'])
    for name in ('counter', 'progress'):
        getattr(n, 'vertrix_actor_%s_wrap' % name).argtypes = [c.c_void_p, c.c_size_t]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4ac5b0)
    totals = {}
    for case in range(args.cases):
        address, name, first = ((0x4ac5b0, 'counter', 0xbc), (0x4ac6b0, 'progress', 0xdc))[case % 2]
        raw = bytearray(rng.randbytes(SIZE))
        edges = [0, 1, 2, 3, 0x7fffffff, 0x80000000, 0xffffffff]
        for offset in (0, 4):
            if rng.random() < 0.7:
                struct.pack_into('<I', raw, first + offset,
                                 rng.choice(edges) if rng.random() < 0.5 else rng.randrange(0, 40))
        cpu.mem_write(ACTOR, bytes(raw))
        original.call(address, eax=ACTOR)
        native = c.create_string_buffer(bytes(raw), SIZE)
        assert getattr(n, 'vertrix_actor_%s_wrap' % name)(native, SIZE), case
        assert native.raw == bytes(cpu.mem_read(ACTOR, SIZE)), (case, name)
        totals[name] = totals.get(name, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 4ac5b0 and 4ac6b0 execute in the original over edge and random '
                       'fields; the whole object compares.'}
    (args.build_dir / 'actor-wrap-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
