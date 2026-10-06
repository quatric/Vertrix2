"""Compare the original settings defaults 0x4290c0 with the native recovery."""
import argparse, ctypes as c, json, random, struct
from pathlib import Path
from original import Original
from oracle_kit import build

SETTINGS, SIZE = 0x801000, 0x240
GLOBALS = (0x532c98, 0x4f8300, 0x4f8370, 0x4f81d0)


class Globals(c.Structure):
    _fields_ = [('first', c.c_uint32), ('second', c.c_uint32), ('third', c.c_uint32),
                ('fourth', c.c_uint32)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'settings-defaults', ['settings_defaults.c', 'actor_storage.c'])
    n.vertrix_settings_defaults.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(Globals)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4290c0)
    total = 0
    for case in range(args.cases):
        values = [rng.getrandbits(32) for _ in GLOBALS]
        for address, value in zip(GLOBALS, values):
            cpu.mem_write(address, struct.pack('<I', value))
        raw = rng.randbytes(SIZE)
        cpu.mem_write(SETTINGS, raw)
        original.call(0x4290c0, eax=SETTINGS)
        native = c.create_string_buffer(raw, SIZE)
        assert n.vertrix_settings_defaults(native, SIZE, c.byref(Globals(*values))), case
        assert native.raw == bytes(cpu.mem_read(SETTINGS, SIZE)), case
        total += 1
    short = c.create_string_buffer(0x100)
    assert not n.vertrix_settings_defaults(short, 0x100, c.byref(Globals(0, 0, 0, 0)))
    report = {
        'status': 'passed',
        'complete_original_executions': {'0x4290c0': total},
        'scope': 'Complete 4290c0 executes in the original with random globals and random '
                 'prior object bytes; the whole settings object compares byte for byte.'
    }
    (args.build_dir / 'settings-defaults-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
