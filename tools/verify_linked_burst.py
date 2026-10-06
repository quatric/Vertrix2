"""Compare five linked burst phases and shared random cursor with original x86."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original, BOARD, MASK
from verify_number_transition import Timer
from verify_random import NativeRandom


class Burst(c.Structure):
    _fields_ = [('repetitions', c.c_uint32), ('source', c.c_uint32), ('handler', c.c_uint32),
               ('effect', c.c_int16), ('target', c.c_int16), ('step', c.c_int16),
               ('delay', c.c_int32), ('delay_target', c.c_int32), ('delay_step', c.c_int32),
               ('timer', Timer)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = a.build_dir.resolve() / 'linked-burst.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    *[str(source / name) for name in ['linked_burst.c', 'timer.c',
                        'word_transition.c', 'dword_transition.c', 'random.c',
                        'ui_border_update.c', 'actor_storage.c', 'actor_lookup.c', 'object_list.c']],
                    '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_linked_burst_update.argtypes = [c.POINTER(Burst), c.c_int, c.c_uint32,
                                                  c.c_uint32, c.POINTER(NativeRandom)]
    storage_update = native.vertrix_ui_border_storage_update
    storage_update.argtypes = [c.c_void_p, c.c_size_t, c.c_int, c.c_uint32,
                               c.c_uint32, c.POINTER(NativeRandom)]
    original = Original(a.executable)
    cpu = original.cpu
    rng = random.Random(0x450130)
    random_state = NativeRandom()
    samples = [rng.randrange(65536) for _ in range(4097)]
    random_state.samples[:] = samples
    cpu.mem_write(0x804000, struct.pack('<4097H', *samples))
    changes = draws = 0
    for case in range(10240):
        handler = [0x450130, 0x4501a0, 0x450200, 0x450270, 0x450300][case % 5]
        present = (case // 5) % 3 != 0
        linked_value = rng.choice([0, 1, 2, rng.getrandbits(32)])
        state = Burst(rng.choice([0, 1, 2, 3, rng.getrandbits(32)]), rng.getrandbits(32), handler,
                      rng.choice([-100, 0, rng.randrange(-32768, 32768)]),
                      rng.choice([-100, 0, rng.randrange(-32768, 32768)]),
                      rng.randrange(-32768, 32768), rng.randrange(-2147483648, 2147483648),
                      rng.randrange(-2147483648, 2147483648),
                      rng.randrange(-2147483648, 2147483648),
                      Timer(rng.getrandbits(32), rng.choice([0, 1, 100, 0xffffffff])))
        elapsed = rng.choice([0, 1, 100, rng.getrandbits(32)])
        raw = bytearray(rng.randbytes(0x160))
        offsets = [('repetitions', 0x58, 'I'), ('source', 0x134, 'I'), ('handler', 0x154, 'I'),
                   ('effect', 0x48, 'h'), ('target', 0x4a, 'h'), ('step', 0x4c, 'h'),
                   ('delay', 0x70, 'i'), ('delay_target', 0x74, 'i'), ('delay_step', 0x78, 'i')]
        for name, offset, fmt in offsets:
            struct.pack_into('<' + fmt, raw, offset, getattr(state, name))
        struct.pack_into('<2I', raw, 0xbc, state.timer.counter, state.timer.period)
        identity = rng.getrandbits(32)
        struct.pack_into('<I', raw, 4, identity)
        linked = bytearray(rng.randbytes(0x160))
        struct.pack_into('<I', linked, 0, identity)
        struct.pack_into('<I', linked, 0x58, linked_value)
        cpu.mem_write(BOARD, bytes(raw))
        storage = c.create_string_buffer(bytes(raw), len(raw))
        cpu.mem_write(0x808000, bytes(linked))
        cpu.mem_write(MASK, struct.pack('<I', 0x808000))
        cpu.mem_write(0x54671c, struct.pack('<3I', 0, MASK, int(present)))
        cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        position = rng.randrange(4096)
        random_state.position = position
        cpu.mem_write(0x598d38, struct.pack('<IH', 0x804000 + 2 * position, position))
        original.call(handler, eax=BOARD)
        assert native.vertrix_linked_burst_update(c.byref(state), present, linked_value,
                                                 elapsed, c.byref(random_state))
        for name, offset, fmt in offsets:
            struct.pack_into('<' + fmt, raw, offset, getattr(state, name))
        struct.pack_into('<2I', raw, 0xbc, state.timer.counter, state.timer.period)
        assert bytes(raw) == bytes(cpu.mem_read(BOARD, len(raw))), (case, hex(handler))
        assert bytes(linked) == bytes(cpu.mem_read(0x808000, len(linked))), case
        cursor, original_position = struct.unpack('<IH', cpu.mem_read(0x598d38, 6))
        assert original_position == random_state.position, case
        assert cursor == 0x804000 + 2 * random_state.position, case
        adapted_random = NativeRandom.from_buffer_copy(bytes(random_state))
        adapted_random.position = position
        assert storage_update(storage, len(raw), present, linked_value, elapsed,
                              c.byref(adapted_random))
        assert storage.raw == bytes(raw), case
        assert bytes(adapted_random) == bytes(random_state), case
        before, random_before = storage.raw, bytes(adapted_random)
        assert not storage_update(storage, 0x15b, present, linked_value, elapsed,
                                  c.byref(adapted_random))
        assert not storage_update(storage, len(raw), present, linked_value, elapsed, None)
        assert storage.raw == before and bytes(adapted_random) == random_before
        changes += state.handler != handler
        draws += random_state.position != position
    report = {'status': 'passed', 'cases': 10240, 'handler_changes': changes, 'random_draws': draws,
              'serialized_actor_cases': 10240, 'failure_preservation_cases': 20480,
              'scope': 'All five original handlers without hooks, actual RNG modulo and transitions. '
                       'Whole effect object, unchanged linked object and shared random cursor match. '
                       'RNG refill has separate recovery evidence; these fixtures do not reach refill. '
                       'Full actor/application scheduling remains unfinished.'}
    (a.build_dir / 'linked-burst-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
