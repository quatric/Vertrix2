"""Compare original fast/alpha/prepared operation selection without drawing."""
import argparse
import ctypes as c
import json
from pathlib import Path
import struct
import subprocess
from original import Original
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EBP, UC_X86_REG_ESI, UC_X86_REG_ESP, UC_X86_REG_EIP


class Operation(c.Structure):
    _fields_ = [('address', c.c_uint32), ('prepare', c.c_uint32)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'operation.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
        str(source / 'render_dispatch.c'), str(source / 'surface.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_render_operation.argtypes = [c.c_uint32, c.c_uint32, c.c_uint32,
        c.c_uint8, c.c_uint32, c.POINTER(Operation)]
    original = Original(args.executable)
    operations = set(struct.unpack('<8I', original.cpu.mem_read(0x4ff5e4, 32)))
    operations.update(struct.unpack('<32I', original.cpu.mem_read(0x4ff604, 128)))
    operations.update(struct.unpack('<16I', original.cpu.mem_read(0x4ff684, 64)))
    observed = Operation()

    def boundary(cpu, address, size, data):
        if address == 0x4ae250:
            observed.prepare = 1
            stack = cpu.reg_read(UC_X86_REG_ESP)
            target = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
            cpu.reg_write(UC_X86_REG_ESP, stack + 4)
            cpu.reg_write(UC_X86_REG_EIP, target)
        elif address in operations:
            observed.address = address
            cpu.reg_write(UC_X86_REG_EIP, 0x4af7b9)

    hook = original.cpu.hook_add(UC_HOOK_CODE, boundary)
    cases = 0
    for fmt_index, fmt in enumerate((4, 2, 1, 0)):
        for index in range(8):
            for group in range(4):
                for rule in (0, 1, 46, 91):
                    for alpha in (0, 1, 0xffffffff):
                        observed.address = observed.prepare = 0
                        original.cpu.reg_write(UC_X86_REG_EBP, 0x708800)
                        original.cpu.reg_write(UC_X86_REG_ESI, 0x800000)
                        original.cpu.mem_write(0x800150, struct.pack('<I', alpha))
                        for offset, value in ((0x20, rule), (0x18, index), (0x24, index * 4), (0x1c, 1)):
                            original.cpu.mem_write(0x708800 - offset, struct.pack('<I', value))
                        row = struct.unpack('<I', original.cpu.mem_read(0x4ff6c4 + fmt_index * 32 + index * 4, 4))[0]
                        image = struct.unpack('<I', original.cpu.mem_read(0x4ff684 + fmt_index * 16 + group * 4, 4))[0]
                        original.call(0x4af786, eax=group, ecx=fmt_index, ebx=row, edx=image, stop=0x4af7b9)
                        result = Operation()
                        assert native.vertrix_render_operation(rule, index, group, fmt,
                            alpha, c.byref(result)) == 1
                        assert bytes(result) == bytes(observed), (fmt, index, group, rule, alpha)
                        before = bytes(result)
                        assert native.vertrix_render_operation(92, index, group, fmt,
                            alpha, c.byref(result)) == 0
                        assert bytes(result) == before
                        cases += 1
    original.cpu.hook_del(hook)
    report = {'status': 'passed', 'operation_selection_cases': cases,
        'invalid_preservation_cases': cases,
        'scope': 'Original 0x4af786..0x4af86d selects and invokes the observed address. '
                 'Preparation and drawing calls are supplied boundaries; their bodies, '
                 'full actor dispatch and playable application are not verified here.'}
    (args.build_dir / 'render-operation-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
