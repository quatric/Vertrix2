"""Compare original font outline transform and source mutation."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ESP, UC_X86_REG_EIP
from original import Original


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    library = args.build_dir.resolve() / 'outline.dylib'
    source = Path(__file__).resolve().parents[1] / 'source/font_outline.c'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', str(source), '-o', str(library)], check=True)
    native = c.CDLL(str(library)).vertrix_font_outline
    native.argtypes = [c.POINTER(c.c_uint32), c.POINTER(c.c_uint32), c.c_size_t] + [c.c_uint32] * 4
    original = Original(args.executable)
    def clone(cpu, address, size, context):
        descriptor = bytes(cpu.mem_read(cpu.reg_read(UC_X86_REG_EAX), 20))
        pixels, width, height, x, y = struct.unpack('<5I', descriptor)
        cpu.mem_write(0x805000, struct.pack('<5I', 0x808000, width, height, x, y))
        cpu.mem_write(0x808000, bytes(cpu.mem_read(pixels, width * height * 4)))
        stack = cpu.reg_read(UC_X86_REG_ESP)
        destination = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
        cpu.reg_write(UC_X86_REG_EAX, 0x805000)
        cpu.reg_write(UC_X86_REG_ESP, stack + 4)
        cpu.reg_write(UC_X86_REG_EIP, destination)
    original.cpu.hook_add(UC_HOOK_CODE, clone, begin=0x483110, end=0x483110)
    rng = random.Random(0x483400)
    pixels_compared = 0
    for case in range(1024):
        width, height = rng.randrange(1, 17), rng.randrange(1, 17)
        passes, diagonal = rng.randrange(5), rng.randrange(3)
        words = [rng.getrandbits(24) | (rng.choice([0, 1, 128, 255]) << 24) for _ in range(width * height)]
        if case % 8 == 0:
            words = [word | 0xff000000 for word in words]
        working = (c.c_uint32 * len(words))(* words)
        output = (c.c_uint32 * len(words))()
        original.cpu.mem_write(0x804000, struct.pack('<5I', 0x806000, width, height, 7, 9))
        original.cpu.mem_write(0x806000, bytes(working))
        assert original.call(0x483400, eax=0x804000, edx=passes, ebx=1, ecx=diagonal) == 0x805000
        assert native(working, output, len(words), width, height, passes, diagonal)
        assert bytes(working) == bytes(original.cpu.mem_read(0x806000, len(words) * 4)), case
        assert bytes(output) == bytes(original.cpu.mem_read(0x808000, len(words) * 4)), case
        pixels_compared += len(words) * 2
        before = bytes(working), bytes(output)
        assert not native(working, output, 0, width, height, passes, diagonal)
        assert (bytes(working), bytes(output)) == before
    report = {'status': 'passed', 'cases': 1024, 'pixels_compared': pixels_compared, 'scope': 'Actual0x483400 EBX=1 with only clone/allocation483110 hooked. ' 'Source mutation and output pixels match, passes0..4, diagonal0..2, ' 'sizes1..16 and all-opaque fixtures. Resource allocation, EBX=0 ' 'ownership path and VF font integration remain separate.'}
    (args.build_dir / 'font-outline-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
