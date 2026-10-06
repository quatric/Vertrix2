"""Verify original HSV stages used to build palette channel maps."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from unicorn.x86_const import UC_X86_REG_EIP


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'palette-color.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-ffp-contract=off', '-Wall', '-Wextra', '-Werror', str(source / 'palette_color.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_palette_color.argtypes = [c.c_uint16, c.c_uint16, c.c_uint16, c.POINTER(c.c_uint16)]
    native.vertrix_palette_channels.argtypes = [c.c_void_p, c.c_size_t]
    original = Original(args.executable)
    rng = random.Random(0x474910)
    cases = [(0, s, v) for s in range(101) for v in range(101)]
    cases += [(h, rng.randrange(101), rng.randrange(101)) for h in range(361) for _ in range(16)]
    for case, (h, s, v) in enumerate(cases):
        original.cpu.mem_write(0x804000, bytes(12))
        original.call(0x474910, eax=h, edx=s, ebx=v, ecx=0x804000, args=(0x804004, 0x804008))
        expected = tuple(struct.unpack('<H', original.cpu.mem_read(0x804000 + i * 4, 2))[0] for i in range(3))
        output = (c.c_uint16 * 3)()
        assert native.vertrix_palette_color(h, s, v, output) == 1
        assert tuple(output) == expected, (case, (h, s, v), tuple(output), expected)
    try:
        original.call(0x474cd0)
    except RuntimeError:
        original.cpu.emu_start(original.cpu.reg_read(UC_X86_REG_EIP), 0x700000, count=100_000_000)
    assert original.cpu.reg_read(UC_X86_REG_EIP) == 0x700000
    channels = c.create_string_buffer(201 * 101)
    assert native.vertrix_palette_channels(channels, len(channels)) == 1
    expected_channels = bytes(original.cpu.mem_read(0x5468b0, len(channels)))
    assert channels.raw == expected_channels, [(i // 101, i % 101, a, b) for i, (a, b) in enumerate(zip(channels.raw, expected_channels)) if a != b][: 20]
    report = {'status': 'passed', 'cases': len(cases), 'channel_table_bytes': len(channels), 'scope': 'Complete original474910 runs unchanged, including software floating ' 'point helpers. Native matches all hue-zero channel-map inputs and ' 'random saturation/value combinations for every hue0..360. ' 'Complete original474cd0 also matches all20301 channel table bytes. ' 'Complete lookup generation and draw integration remain unfinished.'}
    (args.build_dir / 'palette-color-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
