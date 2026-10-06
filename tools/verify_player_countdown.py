"""Compare player countdown phases and flag changes with original x86 without hooks."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original, BOARD
from verify_number_transition import Timer


class Indicator(c.Structure):
    _fields_ = [('value', c.c_uint32), ('state', c.c_uint32), ('target', c.c_uint32), ('handler', c.c_uint32),
               ('primary', Timer), ('secondary', Timer)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = a.build_dir.resolve() / 'player-indicator.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    str(source / 'player_indicator.c'), str(source / 'timer.c'),
                    '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_player_countdown_update.argtypes = [c.POINTER(Indicator), c.c_uint32,
                                                       c.POINTER(c.c_uint32), c.c_uint32]
    original = Original(a.executable)
    cpu = original.cpu
    rng = random.Random(0x44fe80)
    for case in range(12288):
        handler = [0x450750, 0x4507e0, 0x450830][case % 3]
        player_state = rng.choice([0, 1, 2, 3, 4, 0xffffffff])
        elapsed = rng.choice([0, 1, 100, rng.getrandbits(32)])
        state = Indicator(rng.getrandbits(32), rng.choice([0, 1, 2, 0x80000000, rng.getrandbits(32)]), rng.getrandbits(32), handler,
                          Timer(rng.getrandbits(32), rng.choice([0, 1, 100, 0xffffffff])),
                          Timer(rng.getrandbits(32), rng.choice([0, 1, 100, 0xffffffff])))
        raw = bytearray(rng.randbytes(0x160))
        offsets = [('value', 0x58), ('state', 0x64), ('target', 0x70), ('handler', 0x154)]
        for name, offset in offsets:
            struct.pack_into('<I', raw, offset, getattr(state, name))
        for timer, offset in [(state.primary, 0xbc), (state.secondary, 0xdc)]:
            struct.pack_into('<2I', raw, offset, timer.counter, timer.period)
        index = rng.randrange(4)
        struct.pack_into('<I', raw, 4, index)
        cpu.mem_write(BOARD, bytes(raw))
        cpu.mem_write(0x540f88 + 4 * index, struct.pack('<I', 0x804000))
        cpu.mem_write(0x804180, struct.pack('<I', player_state))
        flag = c.c_uint32(rng.choice([0, 1, 2]))
        cpu.mem_write(0x8043ac, struct.pack('<I', flag.value))
        cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        original.call(handler, eax=BOARD)
        assert native.vertrix_player_countdown_update(c.byref(state), player_state, c.byref(flag), elapsed)
        assert flag.value == struct.unpack('<I', cpu.mem_read(0x8043ac, 4))[0]
        for name, offset in offsets:
            struct.pack_into('<I', raw, offset, getattr(state, name))
        for timer, offset in [(state.primary, 0xbc), (state.secondary, 0xdc)]:
            struct.pack_into('<2I', raw, offset, timer.counter, timer.period)
        assert bytes(raw) == bytes(cpu.mem_read(BOARD, len(raw))), case
    report = {'status':
        'passed', 'cases' : 12288, 'handlers' : [ '450750', '4507e0', '450830' ],
                                                'scope'
            : 'All three original countdown handlers without hooks. Whole objects and player flag match signed comparisons, timers, reset, phase handoff and return. Full application remains unfinished.'
        }
        (a.build_dir / 'player-countdown-verification.json')
                .write_text(json.dumps(report, indent = 2) + '\n')
                    print(json.dumps(report, indent = 2))

                        if __name__ == '__main__' : main()
