"""Compare all font-map initializer writes against the original executable."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP
from original import Original
from verify_font_map import FontMap


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    library = args.build_dir.resolve() / 'initialize.dylib'
    source = Path(__file__).resolve().parents[1] / 'source/font_map.c'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    str(source), '-o', str(library)], check=True)
    native = c.CDLL(str(library)).vertrix_font_maps_initialize
    native.argtypes = [c.POINTER(FontMap), c.c_size_t] + [c.c_uint32] * 4
    original = Original(args.executable)
    calls = []

    def resource(cpu, address, size, context):
        index = cpu.reg_read(UC_X86_REG_EDX)
        calls.append(index)
        cpu.reg_write(UC_X86_REG_EAX, 0x805000 if index == 6 else 0x805040)
        stack = cpu.reg_read(UC_X86_REG_ESP)
        destination = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
        cpu.reg_write(UC_X86_REG_ESP, stack + 4)
        cpu.reg_write(UC_X86_REG_EIP, destination)

    original.cpu.hook_add(UC_HOOK_CODE, resource, begin=0x4877f0, end=0x4877f0)
    rng = random.Random(0x43fc50)
    for case in range(256):
        maps = (FontMap * 20)()
        tails = []
        for font in range(20):
            raw = rng.randbytes(c.sizeof(FontMap))
            c.memmove(c.addressof(maps[font]), raw, len(raw))
            tails.append(rng.randbytes(4))
            original.cpu.mem_write(0x541988 + font * 524, raw + tails[-1])
        dimensions = [rng.getrandbits(32) for _ in range(4)]
        original.cpu.mem_write(0x805000, struct.pack('<3I', 0, *dimensions[:2]))
        original.cpu.mem_write(0x805040, struct.pack('<3I', 0, *dimensions[2:]))
        calls.clear()
        original.call(0x43fc50)
        assert calls == [6, 9, 9], calls
        assert native(maps, 20, *dimensions)
        for font in range(20):
            expected = bytes(original.cpu.mem_read(0x541988 + font * 524, 524))
            assert bytes(maps[font]) + tails[font] == expected, (case, font)
    before = bytes(maps)
    assert not native(maps, 18, 0, 0, 0, 0)
    assert bytes(maps) == before
    report = {'status': 'passed', 'cases': 256, 'maps_compared': 5120,
              'scope': 'Original0x43fc50 and actual punctuation helpers; only4877f0 '
                       'resource lookup hooked with randomized dimensions. All glyphs, '
                       'space sizes, trailing words and untouched slot19 compared. '
                       'VF font-resource construction and text rendering remain unfinished.'}
    (args.build_dir / 'font-initialize-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
