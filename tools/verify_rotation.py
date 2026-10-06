"""Compare original per-cycle rotation and global trace outputs."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original, BOARD


class Trace(c.Structure):
    _fields_ = [('iterations', c.c_uint32), ('unwrapped', c.c_uint32)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = a.build_dir.resolve() / 'rotation.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    str(source / 'rotation.c'), '-o', str(library)], check=True)
    n = c.CDLL(str(library))
    n.vertrix_rotation_advance.argtypes = [c.POINTER(c.c_int16), c.c_int16,
                                         c.c_uint32, c.POINTER(Trace)]
    o = Original(a.executable)
    rng = random.Random(0x4ad060)
    for case in range(1024):
        raw = bytearray(rng.randbytes(0x160))
        angle = c.c_int16(rng.choice(
            [-32768, -360, -1, 0, 359, 360, 32767, rng.randrange(-32768, 32768)]))
        step = rng.choice([-32768, -360, -1, 0, 1, 360, 32767, rng.randrange(-32768, 32768)])
        cycles = rng.randrange(257)
        trace = Trace(rng.getrandbits(32), rng.getrandbits(32))
        struct.pack_into('<h', raw, 0x24, angle.value)
        struct.pack_into('<h', raw, 0x28, step)
        o.cpu.mem_write(BOARD, bytes(raw))
        o.cpu.mem_write(0x5bb5f8, struct.pack('<I', trace.iterations))
        o.cpu.mem_write(0x5bb5f4, struct.pack('<I', trace.unwrapped))
        expected_return = o.call(0x4ad060, eax=BOARD, edx=cycles)
        assert n.vertrix_rotation_advance(c.byref(angle), step, cycles,
                                          c.byref(trace)) == expected_return
        struct.pack_into('<h', raw, 0x24, angle.value)
        assert bytes(raw) == bytes(o.cpu.mem_read(BOARD, len(raw))), case
        assert (trace.iterations, trace.unwrapped) == (
            struct.unpack('<I', o.cpu.mem_read(0x5bb5f8, 4))[0],
            struct.unpack('<I', o.cpu.mem_read(0x5bb5f4, 4))[0]), case
    report = {
        'status': 'passed',
        'cases': 1024,
        'scope': 'Actual original 0x4ad060 without hooks; full object storage, return '
                 'value and both global trace fields match signed-word angle and step extremes. '
                 'Coordinate lookup and the enclosing actor handler remain incomplete.'
    }
    (a.build_dir / 'rotation-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
