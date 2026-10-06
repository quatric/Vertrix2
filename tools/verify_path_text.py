"""Compare the original path separator scanners with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import build

PATH = 0x808400
LENGTH = 40


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'path-text', ['path_text.c'])
    n.vertrix_path_last_separator.argtypes = [c.c_void_p, c.c_size_t, c.c_size_t]
    n.vertrix_path_last_separator.restype = c.c_size_t
    n.vertrix_path_is_network.argtypes = [c.c_void_p]
    n.vertrix_path_is_network.restype = c.c_uint32
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4885a0)
    totals = {}
    for case in range(args.cases):
        alphabet = [0x5c, 0x5c, 0x41, 0x2f, 0x2e, 0x62]
        data = bytes(rng.choice(alphabet) for _ in range(LENGTH))
        cpu.mem_write(PATH, data)
        buffer = (c.c_uint8 * LENGTH).from_buffer_copy(data)
        first, last = rng.randrange(0, LENGTH), rng.randrange(0, LENGTH)
        got = n.vertrix_path_last_separator(buffer, first, last)
        result = original.call(0x4885a0, eax=PATH + first, edx=PATH + last) - PATH
        assert got == result, (case, first, last, got, result)
        totals['0x4885a0'] = totals.get('0x4885a0', 0) + 1
        offset = rng.randrange(0, 5)
        got = n.vertrix_path_is_network(c.byref(buffer, offset))
        result = original.call(0x488940, eax=PATH + offset) & 0xffffffff
        assert got == result, (case, offset, got, result)
        totals['0x488940'] = totals.get('0x488940', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Both scanners execute completely in the original over random separator '
                       'heavy buffers; the returned index and flag compare.'}
    (args.build_dir / 'path-text-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
