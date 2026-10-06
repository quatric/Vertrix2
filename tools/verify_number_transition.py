"""Compare all three player numeric transition phases with original x86."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original, BOARD, MASK
from verify_number_player import Number


class Timer(c.Structure):
    _fields_ = [('counter', c.c_uint32), ('period', c.c_uint32)]


class Transition(c.Structure):
    _fields_ = [('id', c.c_uint32), ('source', c.c_uint32), ('handler', c.c_uint32),
               ('effect', c.c_int16), ('target', c.c_int16), ('step', c.c_int16),
               ('timer', Timer)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'number-transition.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    *[str(source / name) for name in
                      ['number_transition.c', 'timer.c', 'word_transition.c']],
                    '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_number_transition_update.argtypes = [c.POINTER(Transition), c.POINTER(Number),
        c.POINTER(c.c_uint32), c.c_size_t, c.c_uint32]
    native.vertrix_number_transition_configured.argtypes = [c.POINTER(Transition), c.POINTER(Number),
        c.POINTER(c.c_uint32), c.c_size_t, c.c_uint32, c.c_uint32, c.c_uint32]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x44fad0)
    phase_changes = 0
    for case in range(16384):
        raw = bytearray(rng.randbytes(0x160))
        linked = bytearray(rng.randbytes(0x194))
        handler = [0x44fad0, 0x44fb40, 0x44fbb0, 0x44fc60, 0x44fcf0,
                   0x44fd60, 0x44fdb0, 0x44fe30][case % 8]
        identity = rng.randrange(4)
        list_id = rng.getrandbits(32)
        players = [rng.getrandbits(32) for _ in range(4)]
        value = players[identity] if (case // 8) % 2 else rng.getrandbits(32)
        config_mode = rng.choice([0, 1, 2, 0xffffffff])
        config_value = players[identity] if (case // 8) % 3 else rng.getrandbits(32)
        counter = rng.getrandbits(32) if case % 5 == 0 else rng.randrange(1000)
        period = rng.choice([0, 1, 10, 100, 1000, 0xffffffff])
        elapsed = rng.getrandbits(32) if case % 7 == 0 else rng.randrange(1000)
        state = Transition(list_id, rng.getrandbits(32), handler,
                           rng.choice([-100, 50, rng.randrange(-32768, 32768)]),
                           rng.randrange(-32768, 32768), rng.randrange(-32768, 32768),
                           Timer(counter, period))
        number = Number(identity, value, 0, 0, 0, rng.getrandbits(32), -1, 0)
        offsets = [('id', 4, 'I'), ('source', 0x134, 'I'), ('handler', 0x154, 'I'),
                   ('effect', 0x48, 'h'), ('target', 0x4a, 'h'), ('step', 0x4c, 'h')]
        for name, offset, fmt in offsets:
            struct.pack_into('<' + fmt, raw, offset, getattr(state, name))
        struct.pack_into('<2I', raw, 0xbc, counter, period)
        struct.pack_into('<2I', linked, 0, list_id, identity)
        struct.pack_into('<I', linked, 0x180, value)
        struct.pack_into('<I', linked, 0x154, number.handler)
        cpu.mem_write(BOARD, bytes(raw))
        cpu.mem_write(0x804000, bytes(linked))
        cpu.mem_write(MASK, struct.pack('<I', 0x804000))
        cpu.mem_write(0x54671c, struct.pack('<3I', 0, MASK, 1))
        handles = [0x808000 + i * 512 for i in range(4)]
        cpu.mem_write(0x540f88, struct.pack('<4I', *handles))
        for address, player_value in zip(handles, players):
            field = 0x17c if handler in [0x44fad0, 0x44fb40, 0x44fbb0] else 0x178
            other_field = 0x178 if field == 0x17c else 0x17c
            cpu.mem_write(address + field, struct.pack('<I', player_value))
            cpu.mem_write(address + other_field, struct.pack('<I', rng.getrandbits(32)))
        cpu.mem_write(0x532bc8, struct.pack('<I', config_mode))
        cpu.mem_write(0x532b34, struct.pack('<I', config_value))
        cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        original.call(handler, eax=BOARD)
        values = (c.c_uint32 * 4)(*players)
        assert native.vertrix_number_transition_configured(c.byref(state), c.byref(number),
                                                           values, 4, elapsed,
                                                           config_mode, config_value)
        for name, offset, fmt in offsets:
            struct.pack_into('<' + fmt, raw, offset, getattr(state, name))
        struct.pack_into('<2I', raw, 0xbc, state.timer.counter, state.timer.period)
        struct.pack_into('<I', linked, 0x154, number.handler)
        assert bytes(raw) == bytes(cpu.mem_read(BOARD, len(raw))), (case, hex(handler))
        assert bytes(linked) == bytes(cpu.mem_read(0x804000, len(linked))), case
        phase_changes += state.handler != handler
    report = {'status': 'passed', 'cases': 16384, 'phase_changes': phase_changes,
              'scope': 'Complete original44fad0/44fb40/44fbb0/44fc60/44fcf0/44fd60/44fdb0/44fe30 execution without hooks. '
                       'Whole effect and linked numeric objects match, including timers, '
                       'signed transitions, value comparison and numeric handler handoff. '
                       'Caller resolves the linked object; full player scheduling remains unfinished.'}
    (args.build_dir / 'number-transition-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
