"""Compare original 0x417790 (score text) with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from unicorn.x86_const import UC_X86_REG_EIP, UC_X86_REG_ESP
from unicorn import UC_HOOK_CODE
from original import Original
OUTPUT = 0x800100


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    library = args.build_dir.resolve() / 'score-text.dylib'
    source = Path(__file__).resolve().parents[1] / 'source/score_text.c'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', str(source), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_score_text.argtypes = [c.c_uint32, c.c_void_p, c.c_size_t]
    original = Original(args.executable)
    cpu = original.cpu
    def hook(cpu, address, size, context):
        if address != 0x4cdfb0:
            return
        esp = cpu.reg_read(UC_X86_REG_ESP)
        buffer, fmt, value = struct.unpack('<3I', cpu.mem_read(esp + 4, 12))
        text = bytes(cpu.mem_read(fmt, 6))
        assert text == b'%08lu\0', text
        cpu.mem_write(buffer, ('%08u' % value).encode() + b'\0')
        cpu.reg_write(UC_X86_REG_EIP, struct.unpack('<I', cpu.mem_read(esp, 4))[0])
        cpu.reg_write(UC_X86_REG_ESP, esp + 4)
    cpu.hook_add(UC_HOOK_CODE, hook)
    rng = random.Random(0x417790)
    edges = [0, 1, 99999999, 100000000, 0xffffffff, 0x5f5e0ff, 0x5f5e100]
    for case in range(4096):
        value = edges[case] if case < len(edges) else rng.choice([rng.getrandbits(32), rng.randrange(0, 200000000), rng.randrange(0, 1000)])
        cpu.mem_write(OUTPUT, b'\xaa' * 16)
        original.call(0x417790, eax=value, edx=OUTPUT)
        expected = bytes(cpu.mem_read(OUTPUT, 16))
        out = c.create_string_buffer(b'\xaa' * 16, 16)
        assert native.vertrix_score_text(value, out, 16)
        assert out.raw == expected, (value, out.raw, expected)
        short = c.create_string_buffer(b'unchanged', 9)
        assert not native.vertrix_score_text(1, short, 8) and short.value == b'unchanged'
    report = {'status': 'passed', 'cases': 4096, 'scope': 'Complete 417790 executes in the original with the C runtime format call ' '4cdfb0 (%08lu) hooked; output bytes compare.'}
    (args.build_dir / 'score-text-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
