"""Compare the complete original effect mode color chooser with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path
from original import Original
from oracle_kit import build
U = c.c_uint32
BOARD = 0x800000
GLOBALS = {'base': 0x4f81cc, 'first': 0x4f8198, 'second': 0x4f81a4, 'third': 0x4f818c, 'fourth': 0x4f81ac}


class Colors(c.Structure):
    _fields_ = [(name, U) for name in GLOBALS]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=8192)
    args = parser.parse_args()
    n = build(args.build_dir, 'mode-colors', ['mode_colors.c'])
    n.vertrix_mode_colors.argtypes = [c.POINTER(Colors), c.c_uint8, c.c_uint8, U, c.POINTER(U), c.POINTER(U)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43bd90)
    seen = set()
    for case in range(args.cases):
        values = [rng.choice([0, 1, 2, 3, 0xffffffff, rng.getrandbits(32)]) for _ in GLOBALS]
        if rng.random() < 0.5:
            values = [rng.getrandbits(32) for _ in GLOBALS]
        for (name, address), value in zip(GLOBALS.items(), values):
            cpu.mem_write(address, struct.pack('<I', value))
        mode = rng.randrange(256) if rng.random() < 0.3 else rng.randrange(0x38)
        sub = rng.randrange(11) if rng.random() < 0.8 else rng.randrange(256)
        flag = rng.choice([0, 1, 1, 2, 0xffffffff])
        cpu.mem_write(BOARD, struct.pack('<2I', 0x11111111, 0x22222222))
        original.call(0x43bd90, edx=mode, ebx=sub, ecx=BOARD, args=(BOARD + 4, flag))
        expected = struct.unpack('<2I', cpu.mem_read(BOARD, 8))
        after = struct.unpack('<5I', b''.join(bytes(cpu.mem_read(a, 4)) for a in GLOBALS.values()))
        assert after == tuple(values), case
        primary, secondary = U(1), U(2)
        n.vertrix_mode_colors(c.byref(Colors(* values)), mode, sub, flag, c.byref(primary), c.byref(secondary))
        assert (primary.value, secondary.value) == expected, (case, mode, sub, flag)
        seen.add(mode)
    report = {'status': 'passed', 'complete_original_executions': {'mode_colors': args.cases}, 'distinct_modes': len(seen), 'scope': 'Complete 43bd90 executes in the original with random palette globals; ' 'both outputs compare and the palette globals are written back unchanged.'}
    (args.build_dir / 'mode-colors-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
