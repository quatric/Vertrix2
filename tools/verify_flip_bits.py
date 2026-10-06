"""Compare original 0x410890 (high-bit flip) with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original

SIZE = 0x1000
BUFFER = 0x807000


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    import subprocess
    library = args.build_dir.resolve() / 'flip-bits.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    str(root / 'source/file_reads.c'), '-o', str(library)], check=True)
    n = c.CDLL(str(library))
    n.vertrix_flip_high_bits.argtypes = [c.c_void_p, c.c_size_t, c.c_uint32]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x410890)
    totals = {'0x410890': 0}
    for _ in range(args.cases):
        count = rng.choice([0, 1, 2, 7, 16, 255, 256, SIZE, rng.randrange(SIZE + 1)])
        data = bytes(rng.getrandbits(8) for _ in range(SIZE))
        cpu.mem_write(BUFFER, data)
        original.call(0x410890, eax=BUFFER, edx=count)
        expected = bytes(cpu.mem_read(BUFFER, SIZE))
        host = c.create_string_buffer(data, SIZE)
        assert n.vertrix_flip_high_bits(host, SIZE, count) == 1
        assert host.raw == expected, count
        totals['0x410890'] += 1
#Double application restores the original bytes.
    data = bytes(rng.getrandbits(8) for _ in range(64))
    host = c.create_string_buffer(data, 64)
    assert n.vertrix_flip_high_bits(host, 64, 64) == 1
    assert n.vertrix_flip_high_bits(host, 64, 64) == 1
    assert host.raw == data
    tiny = c.create_string_buffer(b'\xaa' * 8, 8)
    assert not n.vertrix_flip_high_bits(tiny, 8, 9)
    assert tiny.raw == b'\xaa' * 8
    assert not n.vertrix_flip_high_bits(None, 0, 0)
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 410890 executes in the original over random buffers and counts '
                       'including zero and whole-buffer spans; output bytes compare, plus '
                       'involution and overrun preservation checks.'}
    (args.build_dir / 'flip-bits-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
