"""Compare the complete original string append 0x45f540 with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import build

DST = 0x807000
SRC = 0x807400
SUFFIX = 0x807600
SIZE = 0x200


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'string-append', ['path_text.c'])
    n.vertrix_string_append.argtypes = [c.c_char_p, c.c_size_t, c.c_char_p, c.c_char_p]
    n.vertrix_string_append.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x45f540)
    totals = {}
    for case in range(args.cases):
        src = rng.randbytes(rng.randrange(0, 64)) + b'\x00'
        suffix = rng.randbytes(rng.randrange(0, 64)) + b'\x00'
        fill = bytes(rng.randbytes(SIZE))
        cpu.mem_write(SRC, src)
        cpu.mem_write(SUFFIX, suffix)
        cpu.mem_write(DST, fill)
        host = c.create_string_buffer(bytes(fill), SIZE)
        expect = original.call(0x45f540, eax=DST, edx=SRC, ebx=SUFFIX) & 0xffffffff
        got = n.vertrix_string_append(host, SIZE, src, suffix)
        assert got == 1, (case, got)
        assert expect == DST, (case, hex(expect))
        assert host.raw == bytes(cpu.mem_read(DST, SIZE)), case
        result = src.split(b'\x00')[0] + suffix.split(b'\x00')[0] + b'\x00'
        assert host.raw == result + fill[len(result):], (case, src, suffix)
        totals['0x45f540'] = totals.get('0x45f540', 0) + 1
    tiny = c.create_string_buffer(b'\xaa' * 8, 8)
    assert n.vertrix_string_append(tiny, 8, b'12345678', b'') == 0
    assert tiny.raw == b'\xaa' * 8
    assert n.vertrix_string_append(None, 8, b'a', b'b') == 0
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete original 0x45f540 executions over random source/suffix '
                       'strings (including empties); the returned destination, the full '
                       'destination buffer and the exact concatenation compare, plus '
                       'native-only short/null guards.'}
    (args.build_dir / 'string-append-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
