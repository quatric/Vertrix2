"""Verify original numeric text selection with string/font service hooks."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original, BOARD
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source/number_text.c'
    library = args.build_dir.resolve() / 'number.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', str(source), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_number_text.argtypes = [c.c_uint32, c.c_uint32, c.c_uint32, c.c_uint32, c.c_void_p, c.c_size_t]
    original = Original(args.executable)
    cpu = original.cpu
    strings = {}
    captured = []
    heap = [0x805000]
    def word(address):
        return struct.unpack('<I', cpu.mem_read(address, 4))[0]
    def read_string(pointer):
        data = bytearray()
        while cpu.mem_read(pointer + len(data), 1) != b'\0':
            data += cpu.mem_read(pointer + len(data), 1)
        return bytes(data)
    def assign(slot, text):
        pointer = strings[slot]
        cpu.mem_write(pointer, text + b'\0')
        cpu.mem_write(pointer - 8, struct.pack('<I', len(text)))
    services = {0x4ca070, 0x4cdfb0, 0x4ca370, 0x4ca600, 0x4ca650, 0x4ca210, 0x4b65d0}
    def hook(cpu, address, size, context):
        if address not in services:
            return
        eax = cpu.reg_read(UC_X86_REG_EAX)
        edx = cpu.reg_read(UC_X86_REG_EDX)
        esp = cpu.reg_read(UC_X86_REG_ESP)
        cleanup = 0
        if address == 0x4ca070:
            pointer = heap[0] + 16
            heap[0] += 256
            strings[eax] = pointer
            cpu.mem_write(eax, struct.pack('<I', pointer))
            assign(eax, b'')
        elif address == 0x4cdfb0:
            slot, fmt, value = struct.unpack('<3I', cpu.mem_read(esp + 4, 12))
            assert read_string(fmt) == b'%u'
            assign(slot, str(value).encode())
        elif address == 0x4ca370:
            assign(eax, read_string(edx))
        elif address == 0x4ca600:
            assign(eax, read_string(strings[eax]) + read_string(edx))
        elif address == 0x4ca650:
            assign(eax, read_string(strings[eax]) + read_string(word(edx)))
        elif address == 0x4b65d0:
            captured.append(read_string(edx))
            cleanup = 12
        cpu.reg_write(UC_X86_REG_EIP, word(esp))
        cpu.reg_write(UC_X86_REG_ESP, esp + 4 + cleanup)
    cpu.hook_add(UC_HOOK_CODE, hook)
    rng = random.Random(0x4b58a0)
    for case in range(1024):
        value = 0 if case % 8 == 0 else rng.getrandbits(32)
        mode = rng.choice([0, 1, 2, 0xffffffff])
        width = rng.randrange(65)
        show_zero = rng.randrange(2)
        raw = bytearray(rng.randbytes(0x194))
        struct.pack_into('<I', raw, 0x184, mode)
        struct.pack_into('<I', raw, 0x188, width)
        struct.pack_into('<I', raw, 0x190, show_zero)
        cpu.mem_write(BOARD, bytes(raw))
        strings.clear()
        captured.clear()
        heap[0] = 0x805000
        original.call(0x4b58a0, eax=BOARD, edx=value)
        output = c.create_string_buffer(80)
        assert native.vertrix_number_text(value, mode, width, show_zero, output, len(output))
        assert captured == [output.value], (case, captured, output.value)
        struct.pack_into('<I', raw, 0x180, value)
        assert bytes(raw) == bytes(cpu.mem_read(BOARD, len(raw)))
        short = c.create_string_buffer(b'unchanged', 10)
        before = bytes(short)
        assert not native.vertrix_number_text(0xffffffff, 1, 64, 1, short, len(short))
        assert bytes(short) == before
    report = {'status': 'passed', 'cases': 1024, 'scope': 'Original 0x4b58a0 numeric selection/control flow, with hooks for ' 'string construction/format/append/free and final font binding. ' 'Those services and font rendering are not verified by this comparison.'}
    (args.build_dir / 'number-text-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
