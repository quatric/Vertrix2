"""Compare the original line pass 0x4346b0 with the address-space port."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, BOARD, MASK, COUNTER
from oracle_kit import build
from port_oracle import Memory, Mirror, U

CELLS = 65


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=8192)
    args = parser.parse_args()
    n = build(args.build_dir, 'line-pass-port', ['native_ports.c', 'native_memory.c',
                                                 'call_glue.c', 'actor_storage.c'])
    n.vertrix_port_line_pass.argtypes = [c.POINTER(Memory), U, U, U, U]
    n.vertrix_port_line_pass.restype = U
    original = Original(args.executable)
    mirror = Mirror(original.cpu, {BOARD: 0x100, MASK: 0x200, COUNTER: 0x10})
    rng = random.Random(0x4346b0)
    totals = {}
    for case in range(args.cases):
        palette = rng.choice([[0, 1, 2, 3, 255, 255], [0, 0, 1, 255], [0, 255], [0, 1, 5, 6, 255],
                              [0, 1, 7, 255], [rng.randrange(256) for _ in range(3)] + [255],
                              list(range(256))])
        board = [rng.choice(palette) for _ in range(CELLS)]
        if case % 2:
            for x in range(5):
                column = [v for v in board[x * 13:x * 13 + 13] if v != 255]
                board[x * 13:x * 13 + 13] = [255] * (13 - len(column)) + column
        mask = [rng.choice([0, 0, 0, 1, rng.getrandbits(32), 0x100, 0x10000, 0x1000000])
                for _ in range(CELLS)]
        reward = rng.choice([0, 75, rng.getrandbits(32), 0xffffffff])
        threshold = rng.choice([0, 1, 2, 2, 3, 4, 12, 0x7f, 0x80, 0xfe, 255]) | (
            rng.getrandbits(24) << 8 if rng.random() < 0.3 else 0)

        def fill(base, size):
            blob = bytearray(rng.randbytes(size))
            if base == BOARD:
                blob[:CELLS] = bytes(board)
            elif base == MASK:
                blob[:4 * CELLS] = struct.pack('<65I', *mask)
            else:
                blob[:4] = struct.pack('<I', reward)
            return bytes(blob)

        mirror.load(fill)
        want = original.call(0x4346b0, eax=BOARD, edx=MASK, ebx=threshold, ecx=COUNTER) & 0xffffffff
        global_mode = case % 3 == 0
        memory = mirror.memory(global_mode)
        got = n.vertrix_port_line_pass(c.byref(memory), BOARD, MASK, threshold, COUNTER)
        assert memory.ok and not mirror.other, case
        assert got == want, (case, got, want)
        assert not mirror.differences(), (case, mirror.differences(), board, threshold)
        key = '%s, %s' % ('globals' if global_mode else 'objects', 'found' if want else 'none')
        totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4346b0': totals},
              'scope': 'Complete original 0x4346b0 executions against the address-space port '
                       'over any board byte (game palettes and arbitrary values, with and without '
                       'gravity), arbitrary mask dwords, reward words including 16 bit wrap-around and '
                       'any threshold byte (with garbage in the upper ebx bits); a third of the '
                       'cases go through the globals reader and the store pseudo call. The full '
                       'eax and the board, mask and reward regions compare.'}
    (args.build_dir / 'line-pass-port-verification.json').write_text(json.dumps(report, indent=2)
                                                                      + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
