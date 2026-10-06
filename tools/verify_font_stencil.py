"""Compare original grayscale stencil transform pixels and descriptor geometry."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP
from original import Original


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    library = args.build_dir.resolve() / 'stencil.dylib'
    source = Path(__file__).resolve().parents[1] / 'source/font_stencil.c'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', str(source), '-o', str(library)], check=True)
    native = c.CDLL(str(library)).vertrix_font_stencil
    native.argtypes = [c.POINTER(c.c_uint32), c.c_uint32, c.c_uint32, c.POINTER(c.c_uint32), c.c_uint32, c.c_uint32, c.c_uint32, c.POINTER(c.c_uint32), c.c_size_t]
    original = Original(args.executable)
    def allocate(cpu, address, size, context):
        width, height, x, y = [cpu.reg_read(r) for r in (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX)]
        cpu.mem_write(0x805000, struct.pack('<5I', 0x808000, width, height, x, y))
        cpu.mem_write(0x808000, bytes(width * height * 4))
        stack = cpu.reg_read(UC_X86_REG_ESP)
        destination = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
        cpu.reg_write(UC_X86_REG_EAX, 0x805000)
        cpu.reg_write(UC_X86_REG_ESP, stack + 36)
        cpu.reg_write(UC_X86_REG_EIP, destination)
    original.cpu.hook_add(UC_HOOK_CODE, allocate, begin=0x483060, end=0x483060)
    rng = random.Random(0x4831b0)
    pixels_compared = 0
    for case in range(1024):
        width, height = rng.randrange(1, 17), rng.randrange(1, 17)
        sw, sh = rng.randrange(1, 10), rng.randrange(1, 10)
        if case % 64 == 0:
            width = height = sw = sh = 20
        solid = rng.randrange(3)
        words = [rng.getrandbits(24) | (rng.choice([0, 1, 255]) << 24) for _ in range(width * height)]
        stamp = [rng.getrandbits(24) | (rng.choice([0, 128, 255]) << 24) for _ in range(sw * sh)]
        if case % 64 == 0:
            words = [0xff000000] * len(words)
            stamp = [0xff000000] * len(stamp)
        source_words = (c.c_uint32 * len(words))(* words)
        stencil = (c.c_uint32 * len(stamp))(* stamp)
        ow, oh = width + (sw // 2) * 2, height + (sh // 2) * 2
        output = (c.c_uint32 * (ow * oh))()
        x, y = rng.getrandbits(32), rng.getrandbits(32)
        original.cpu.mem_write(0x804000, struct.pack('<5I', 0x806000, width, height, x, y))
        original.cpu.mem_write(0x804040, struct.pack('<5I', 0x807000, sw, sh, 0, 0))
        original.cpu.mem_write(0x806000, bytes(source_words))
        original.cpu.mem_write(0x807000, bytes(stencil))
        try:
            result = original.call(0x4831b0, eax=0x804000, edx=0x804040, ebx=solid)
        except RuntimeError:
#Dense saturation fixtures exceed the standard instruction budget.
            original.cpu.emu_start(original.cpu.reg_read(UC_X86_REG_EIP), 0x700000, count=10_000_000)
            assert original.cpu.reg_read(UC_X86_REG_EIP) == 0x700000
            result = original.cpu.reg_read(UC_X86_REG_EAX)
        assert result == 0x805000
        descriptor = struct.unpack('<5I', original.cpu.mem_read(0x805000, 20))
        assert descriptor == (0x808000, ow, oh, (x + sw // 2) & 0xffffffff, (y + sh // 2) & 0xffffffff)
        assert native(source_words, width, height, stencil, sw, sh, solid, output, len(output))
        assert bytes(output) == bytes(original.cpu.mem_read(0x808000, len(output) * 4)), case
        assert bytes(source_words) == bytes(original.cpu.mem_read(0x806000, len(words) * 4))
        pixels_compared += len(output)
    before = bytes(output)
    assert not native(source_words, width, height, stencil, sw, sh, solid, output, 0)
    assert bytes(output) == before
    report = {'status': 'passed', 'cases': 1024, 'pixels_compared': pixels_compared, 'scope': 'Actual0x4831b0 with only zeroed resource allocation483060 hooked. ' 'All pixels, unmodified source and output dimensions/origins compared. ' 'Even/odd stencil dimensions, solid0..2 and overlap saturation covered. ' 'Native implements pixels; resource construction/VF integration remain separate.'}
    (args.build_dir / 'font-stencil-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
