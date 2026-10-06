"""Compare five linked indicator phases with original x86 without hooks."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original, BOARD, MASK
from verify_number_transition import Timer


class Indicator(c.Structure):
    _fields_ = [('threshold', c.c_uint32), ('source', c.c_uint32), ('handler', c.c_uint32),
               ('timer', Timer), ('amount', c.c_uint8), ('target', c.c_uint8),
               ('stage', c.c_uint8), ('step', c.c_int16)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = a.build_dir.resolve() / 'linked-indicator.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    *[str(source / name) for name in
                      ['linked_indicator.c', 'timer.c', 'byte_transition.c',
                       'ui_indicator_update.c', 'actor_storage.c', 'actor_lookup.c',
                       'object_list.c']],
                    '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_linked_indicator_update.argtypes = [c.POINTER(Indicator), c.c_int,
                                                      c.c_uint32, c.c_uint32, c.c_uint32]
    storage_update = native.vertrix_ui_indicator_storage_update
    storage_update.argtypes = [c.c_void_p, c.c_size_t, c.c_int, c.c_uint32,
                               c.c_uint32, c.c_uint32]
    original = Original(a.executable)
    cpu = original.cpu
    rng = random.Random(0x44ff90)
    changes = 0
    for case in range(10240):
        handler = [0x44ff90, 0x44fff0, 0x450040, 0x4500b0, 0x450100][case % 5]
        threshold = rng.choice([0, 1, 0x7fffffff, 0x80000000, rng.getrandbits(32)])
        linked_state = rng.choice([threshold, 0, 0xffffffff, rng.getrandbits(32)])
        linked_value = rng.choice([0, 1, 2, rng.getrandbits(32)])
        present = (case // 5) % 3 != 0
        state = Indicator(threshold, rng.getrandbits(32), handler,
                          Timer(rng.getrandbits(32), rng.choice([0, 1, 100, 0xffffffff])),
                          rng.randrange(256), rng.randrange(256), rng.randrange(256),
                          rng.randrange(-32768, 32768))
        elapsed = rng.choice([0, 1, 100, rng.getrandbits(32)])
        raw = bytearray(rng.randbytes(0x160))
        offsets = [('threshold', 0x58, 'I'), ('source', 0x134, 'I'), ('handler', 0x154, 'I'),
                   ('amount', 0x4e, 'B'), ('target', 0x4f, 'B'), ('stage', 0x52, 'B'),
                   ('step', 0x50, 'h')]
        for name, offset, fmt in offsets:
            struct.pack_into('<' + fmt, raw, offset, getattr(state, name))
        struct.pack_into('<2I', raw, 0xbc, state.timer.counter, state.timer.period)
        identity = rng.getrandbits(32)
        struct.pack_into('<I', raw, 4, identity)
        linked = bytearray(rng.randbytes(0x160))
        struct.pack_into('<I', linked, 0, identity)
        struct.pack_into('<I', linked, 0x58, linked_value)
        struct.pack_into('<I', linked, 0x64, linked_state)
        cpu.mem_write(BOARD, bytes(raw))
        storage = c.create_string_buffer(bytes(raw), len(raw))
        cpu.mem_write(0x804000, bytes(linked))
        cpu.mem_write(MASK, struct.pack('<I', 0x804000))
        cpu.mem_write(0x54671c, struct.pack('<3I', 0, MASK, int(present)))
        cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        original.call(handler, eax=BOARD)
        assert native.vertrix_linked_indicator_update(c.byref(state), present, linked_value,
                                                     linked_state, elapsed)
        for name, offset, fmt in offsets:
            struct.pack_into('<' + fmt, raw, offset, getattr(state, name))
        struct.pack_into('<2I', raw, 0xbc, state.timer.counter, state.timer.period)
        assert bytes(raw) == bytes(cpu.mem_read(BOARD, len(raw))), case
        assert storage_update(storage, len(raw), present, linked_value, linked_state, elapsed)
        assert storage.raw == bytes(raw), case
        before = storage.raw
        assert not storage_update(storage, 0x15b, present, linked_value, linked_state, elapsed)
        assert storage.raw == before
        assert bytes(linked) == bytes(cpu.mem_read(0x804000, len(linked))), case
        changes += state.handler != handler
    report = {'status': 'passed', 'cases': 10240, 'handler_changes': changes,
              'serialized_storage_cases': 10240, 'short_storage_preservation_cases': 10240,
              'scope': 'Complete44ff90/44fff0/450040/4500b0/450100 without hooks. Whole object '
                       'matches with original lookup, timers and byte transition. Missing linked '
                       'objects, signed thresholds, wrap arithmetic and handler changes covered. '
                       'Caller resolves native linked object; full application remains unfinished.'}
    (a.build_dir / 'linked-indicator-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
