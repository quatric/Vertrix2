"""Compare original font measurement with descriptor and allocation service hooks."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original, BOARD, MASK
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP


class Dimensions(c.Structure):
    _fields_ = [('width', c.c_uint16), ('height', c.c_uint16)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = a.build_dir.resolve() / 'font.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
        *[str(source / name) for name in ['font_measure.c', 'render_geometry.c', 'surface.c', 'render_dispatch.c']],
        '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    callback = c.CFUNCTYPE(c.c_int, c.c_uint8, c.POINTER(Dimensions), c.c_void_p)
    native.vertrix_font_measure.argtypes = [c.c_void_p, c.c_size_t, Dimensions,
        c.c_uint8, c.c_uint8, c.c_uint8, callback, c.c_void_p,
        c.POINTER(c.c_uint32), c.POINTER(c.c_uint32)]
    original = Original(a.executable)
    original.call(0x4b9050)
    cpu = original.cpu
    descriptors = {}
    def word(address):
        return struct.unpack('<I', cpu.mem_read(address, 4))[0]
    def hook(cpu, address, size, context):
        services = {0x4ccfe0, 0x43f420, 0x4ca000, 0x4abd70, 0x4adf20, 0x700300}
        if address not in services:
            return
        eax = cpu.reg_read(UC_X86_REG_EAX)
        edx = cpu.reg_read(UC_X86_REG_EDX)
        esp = cpu.reg_read(UC_X86_REG_ESP)
        cleanup = 0
        if address == 0x4ccfe0:
            cpu.reg_write(UC_X86_REG_EAX, int(cpu.mem_read(eax, 1) != b'\0'))
        elif address == 0x43f420:
            cpu.reg_write(UC_X86_REG_EAX, descriptors.get(edx & 255, 0))
        elif address == 0x4ca000:
            cpu.reg_write(UC_X86_REG_EAX, 0x804000)
        elif address == 0x4abd70:
            cpu.mem_write(eax, bytes(0x15c))
            cpu.mem_write(eax + 0x158, struct.pack('<I', 0x806000))
        elif address == 0x4adf20:
            cpu.mem_write(eax + 0xb4, struct.pack('<I', word(esp + 12)))
            cleanup = 20
        cpu.reg_write(UC_X86_REG_EIP, word(esp))
        cpu.reg_write(UC_X86_REG_ESP, esp + 4 + cleanup)
    cpu.hook_add(UC_HOOK_CODE, hook)
    cpu.mem_write(0x806000, struct.pack('<I', 0x700300))
    rng = random.Random(0x440610)
    for case in range(1024):
        space = Dimensions(rng.randrange(65), rng.randrange(65))
        cpu.mem_write(0x541988, struct.pack('<2I', space.width, space.height))
        dimensions = {code: Dimensions(rng.randrange(65), rng.randrange(65))
                      for code in range(33, 80) if rng.randrange(4)}
        descriptors.clear()
        for code, dims in dimensions.items():
            pointer = 0x808000 + code * 32
            descriptors[code] = pointer
            cpu.mem_write(pointer, struct.pack('<3I', 0, dims.width, dims.height) + bytes(20))
        text = bytes(rng.randrange(32, 80) for _ in range(rng.randrange(65))) + b'\0'
        cpu.mem_write(0x802000, text)
        mode, unscaled, screen_mode = rng.randrange(17), rng.randrange(2), rng.randrange(17)
        cpu.mem_write(0x544070, struct.pack('<I', 0x809000))
        cpu.mem_write(0x809220, bytes([unscaled, screen_mode]))
        @callback
        def glyph(code, output, context):
            if code not in dimensions:
                return 0
            output[0] = dimensions[code]
            return 1
        original.call(0x440610, eax=0, edx=0x802000, ebx=mode, ecx=BOARD, args=(MASK,))
        width, height = c.c_uint32(), c.c_uint32()
        assert native.vertrix_font_measure(text, len(text), space, mode, unscaled,
            screen_mode, glyph, None, c.byref(width), c.byref(height))
        assert width.value == word(BOARD) and height.value == word(MASK), case
    report = {'status':
        'passed', 'cases' : 1024,
            'scope'
            : 'Original 0x440610 control flow and actual resource measurement4b14c0. ' 'Empty-string comparison, glyph lookup, allocation/constructor/resource attach/destructor ' 'are hooked. VF font mapping and runtime rendering remain unverified.'
        }
        (a.build_dir / 'font-measure-verification.json')
                .write_text(json.dumps(report, indent = 2) + '\n')
                    print(json.dumps(report, indent = 2))

                        if __name__ == '__main__' : main()
