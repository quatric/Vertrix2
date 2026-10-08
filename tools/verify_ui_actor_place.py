"""Compare original 0x4710d0 (UI actor placement) with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import build

U = c.c_uint32
SIZE = 0x1000
BUFFER = 0x807000


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'ui-actor-place',
              ['ui_actor_storage.c', 'actor_storage.c', 'actor_fields.c', 'block_factory.c', 'call_glue.c',
               'ui_display_layout.c', 'board_cells.c'])
    n.vertrix_ui_actor_place.argtypes = [c.c_void_p, c.c_size_t, c.c_int16, c.c_int16, U]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4710d0)
    totals = {'0x4710d0': 0}
    words = [0, 1, 0x7fff, 0x8000, 0xffff, 24, 312, rng.getrandbits(16)]
    for _ in range(args.cases):
        x = rng.choice(words)
        y = rng.choice(words)
        frame = rng.choice([0, 1, 5, rng.getrandbits(32)])
        data = bytes(rng.getrandbits(8) for _ in range(SIZE))
        cpu.mem_write(BUFFER, data)
        original.call(0x4710d0, eax=BUFFER, edx=(rng.getrandbits(16) << 16) | x,
                      ebx=(rng.getrandbits(16) << 16) | y, ecx=frame)
        expected = bytes(cpu.mem_read(BUFFER, SIZE))
        host = c.create_string_buffer(data, SIZE)
        assert n.vertrix_ui_actor_place(host, SIZE, c.c_int16(x - 0x10000 if x >= 0x8000 else x),
                                         c.c_int16(y - 0x10000 if y >= 0x8000 else y),
                                         frame) == 1
        assert host.raw == expected, (hex(x), hex(y), hex(frame))
        totals['0x4710d0'] += 1
    tiny = c.create_string_buffer(b'\xaa' * 8, 8)
    assert not n.vertrix_ui_actor_place(tiny, 8, 0, 0, 0)
    assert tiny.raw == b'\xaa' * 8
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 4710d0 executes in the original over random actors, coordinates '
                       'including negative words, and frames; whole objects compare, plus a '
                       'short-storage preservation check.'}
    (args.build_dir / 'ui-actor-place-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
