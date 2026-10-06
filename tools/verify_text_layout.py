"""Compare original signed-word font/text positioning without hooks."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original, BOARD, MASK


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source/text_layout.c'
    library = a.build_dir.resolve() / 'layout.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    str(source), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_text_layout.argtypes = [c.c_int16] * 6 + [c.POINTER(c.c_int16)] * 2
    original = Original(a.executable)
    rng = random.Random(0x440990)
    early = 0
    for case in range(4096):
        width, height, left, right, top, bottom = [rng.randrange(-32768, 32768) for _ in range(6)]
        if case % 4 == 0:
            width, height = rng.randrange(512), rng.randrange(512)
            left, top = rng.randrange(-100, 100), rng.randrange(-100, 100)
            right, bottom = left + rng.randrange(512), top + rng.randrange(512)
        raw_x, raw_y = rng.randbytes(16), rng.randbytes(16)
        original.cpu.mem_write(BOARD, raw_x)
        original.cpu.mem_write(MASK, raw_y)
        original.call(0x440990, eax=BOARD, edx=MASK, ebx=width & 0xffff,
                      ecx=height & 0xffff, args=tuple(v & 0xffff for v in [left, right, top, bottom]))
        x, y = c.c_int16(), c.c_int16()
        assert native.vertrix_text_layout(width, height, left, right, top, bottom, c.byref(x), c.byref(y))
        assert struct.pack('<h', x.value) + raw_x[2:] == bytes(original.cpu.mem_read(BOARD, 16)), case
        assert struct.pack('<h', y.value) + raw_y[2:] == bytes(original.cpu.mem_read(MASK, 16)), case
        early += x.value < 0 or y.value < 0
    assert not native.vertrix_text_layout(1, 1, 0, 1, 0, 1, None, c.byref(y))
    report = {'status':
            'passed', 'cases' : 4096,
                'scope'
                : 'Original 0x440990 without hooks, full signed-word dimensions/bounds, ' 'narrowing, truncation and early-return origin behavior. Font measurement/rendering remain unfinished.'
            }
            (a.build_dir / 'text-layout-verification.json')
                    .write_text(json.dumps(report, indent = 2) + '\n')
                        print(json.dumps(report, indent = 2))

                            if __name__ == '__main__' : main()
