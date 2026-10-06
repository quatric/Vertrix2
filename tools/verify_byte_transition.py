"""Compare shared byte transitions with all three original routines."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original, BOARD


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = a.build_dir.resolve() / 'word.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    str(source / 'byte_transition.c'), '-o', str(library)], check=True)
    n = c.CDLL(str(library))
    n.vertrix_byte_transition.argtypes = [c.POINTER(c.c_uint8), c.c_uint8, c.c_int16, c.c_uint32]
    o = Original(a.executable)
    rng = random.Random(0x4aca60)
    routines = [(0x4acc10, 0x44), (0x4ad580, 0x4e)]
    for case in range(3072):
        address, offset = routines[case % 2]
        raw = bytearray(rng.randbytes(0x160))
        value = c.c_uint8(rng.randrange(256))
        target = rng.randrange(256)
        step = rng.choice([-32768, -1, 0, 1, 32767, rng.randrange(-32768, 32768)])
        cycles = rng.choice([0, 1, 0xffffffff, rng.getrandbits(32)])
        if case % 8 == 0:
            value.value = target
        struct.pack_into('<BBh', raw, offset, value.value, target, step)
        o.cpu.mem_write(BOARD, bytes(raw))
        expected_return = o.call(address, eax=BOARD, edx=cycles)
        assert n.vertrix_byte_transition(c.byref(value), target, step, cycles) == expected_return
        struct.pack_into('<B', raw, offset, value.value)
        assert bytes(raw) == bytes(o.cpu.mem_read(BOARD, len(raw))), (case, hex(address))
    assert n.vertrix_byte_transition(None, 0, 1, 1) == -1
    report = {
        'status': 'passed',
        'cases': 3072,
        'scope': 'Actual original 0x4acc10/0x4ad580 without hooks; '
                 'whole object and completion returns match full-width cycles and signed-word '
                 'values. Does not execute the enclosing rotating actor handler.'
    }
    (a.build_dir / 'byte-transition-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
