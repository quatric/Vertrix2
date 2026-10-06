"""Compare recovered RGB-to-HSV against complete original474560."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from unicorn.x86_const import UC_X86_REG_EAX


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'palette-rgb.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-ffp-contract=off', '-Wall', '-Wextra',
        '-Werror', str(source / 'palette_color.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_palette_rgb.argtypes = [c.c_uint16, c.c_uint16, c.c_uint16,
        c.POINTER(c.c_uint16), c.POINTER(c.c_uint32)]
    original = Original(args.executable)
    rng = random.Random(0x474560)
    cases = [(i, i, i) for i in range(256)]
    cases += [tuple(rng.randrange(256) for _ in range(3)) for _ in range(8192)]
    cases += [((i >> 12) * 4, ((i >> 6) & 63) * 4, (i & 63) * 4)
              for i in range(262144)]
    for case, (r, g, b) in enumerate(cases):
        original.call(0x474560, eax=r, edx=g, ebx=b, ecx=0x804000,
                      args=(0x804004, 0x804008))
        expected = tuple(struct.unpack('<H', original.cpu.mem_read(0x804000 + i * 4, 2))[0]
                         for i in range(3))
        flag = original.cpu.reg_read(UC_X86_REG_EAX)
        output = (c.c_uint16 * 3)()
        chromatic = c.c_uint32()
        assert native.vertrix_palette_rgb(r, g, b, output, c.byref(chromatic)) == 1
        assert (tuple(output), chromatic.value) == (expected, flag), (
            case, (r, g, b), tuple(output), expected, chromatic.value, flag)
    report = {'status': 'passed', 'cases': len(cases),
        'scope': 'Complete original474560 including software float helpers matches '
                 'native RGB-to-HSV and chromatic flag. Full lookup generation remains unfinished.'}
    (args.build_dir / 'palette-rgb-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
