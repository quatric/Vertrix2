"""Compare shared signed-word transitions with all five original routines."""
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
                    str(source / 'word_transition.c'), '-o', str(library)], check=True)
    n = c.CDLL(str(library))
    n.vertrix_word_transition.argtypes = [c.POINTER(c.c_int16), c.c_int16, c.c_int16, c.c_uint32]
    o = Original(a.executable)
    rng = random.Random(0x4aca60)
    routines = [(0x4aca60, 0xe, 0x10, 0x12), (0x4acab0, 0x16, 0x18, 0x1a), (0x4ad530, 0x48, 0x4a, 0x4c), (0x4ad5e0, 0x2a, 0x30, 0x32), (0x4ad630, 0x3a, 0x40, 0x42)]
    for case in range(5120):
address, offset, target_offset,
    step_offset = routines[case % 5] raw = bytearray(rng.randbytes(0x160)) value =
        c.c_int16(rng.randrange(-32768, 32768)) target = rng.randrange(-32768, 32768) step =
            rng.choice([ -32768, -1, 0, 1, 32767, rng.randrange(-32768, 32768) ]) cycles =
                rng.choice([ 0, 1, 0xffffffff, rng.getrandbits(32) ]) if case % 8 == 0:
value
    .value = target struct.pack_into('<h', raw, offset, value.value) struct
                 .pack_into('<h', raw, target_offset,
                            target) struct.pack_into('<h', raw, step_offset,
                                                     step) o.cpu.mem_write(BOARD, bytes(raw))
                     expected_return = o.call(address, eax = BOARD, edx = cycles)
                                           assert n.vertrix_word_transition(c.byref(value), target,
                                                                            step, cycles) ==
                                       expected_return
                                       struct.pack_into('<h', raw, offset, value.value) assert
                                       bytes(raw) == bytes(o.cpu.mem_read(BOARD, len(raw))),
    (case, hex(address))assert n.vertrix_word_transition(None, 0, 1, 1) == -1 report =
        {
            'status' : 'passed',
            'cases' : 5120,
            'scope' :
                'Actual original 0x4aca60/0x4acab0/0x4ad530/0x4ad5e0/0x4ad630 without hooks; ' 'whole object and completion returns match full-width cycles and signed-word ' 'values. Does not execute the enclosing rotating actor handler.'
        }(a.build_dir / 'word-transition-verification.json')
            .write_text(json.dumps(report, indent = 2) + '\n') print(json.dumps(report, indent = 2))

                if __name__
        == '__main__' : main()
