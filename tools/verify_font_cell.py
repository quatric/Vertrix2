"""Compare original font loader crop traversal with hooked image services."""
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


class Cell(c.Structure):
    _fields_ = [(name, c.c_uint32) for name in ('x', 'y', 'width', 'height', 'count')]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    library = args.build_dir.resolve() / 'cell.dylib'
    source = Path(__file__).resolve().parents[1] / 'source/font_cell.c'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    str(source), '-o', str(library)], check=True)
    native = c.CDLL(str(library)).vertrix_font_cell
    native.argtypes = [c.c_uint32] * 5 + [c.POINTER(Cell)]
    original = Original(args.executable)
    calls = []
    checks = 0

    def boundary(cpu, address, size, context):
        nonlocal checks
        stack = cpu.reg_read(UC_X86_REG_ESP)
        cleanup = 4
        if address == 0x45f590:
            cpu.reg_write(UC_X86_REG_EAX, int(checks == 0))
            checks += 1
        elif address == 0x489b40:
            cpu.reg_write(UC_X86_REG_EAX, 1)
        elif address == 0x473f10:
            cpu.reg_write(UC_X86_REG_EAX, 0x804000)
        elif address == 0x478f10:
            cpu.reg_write(UC_X86_REG_EAX, 0)
        elif address == 0x482f80:
            x, y, width = [cpu.reg_read(r) for r in
                           (UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX)]
            height = struct.unpack('<I', cpu.mem_read(stack + 4, 4))[0]
            calls.append((x, y, width, height))
            cpu.reg_write(UC_X86_REG_EAX, 0x805000)
            cleanup += 44
        destination = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
        cpu.reg_write(UC_X86_REG_ESP, stack + cleanup)
        cpu.reg_write(UC_X86_REG_EIP, destination)

    for address in (0x45f540, 0x45f590, 0x489b40, 0x473f10, 0x478f10,
                    0x4799f0, 0x482f80, 0x483ed0, 0x478d80):
        original.cpu.hook_add(UC_HOOK_CODE, boundary, begin=address, end=address)
    rng = random.Random(0x43f200)
    cells = 0
    for case in range(256):
        width, height = rng.randrange(1, 40), rng.randrange(1, 40)
        sw = rng.randrange(0, 9) * (width + 1) + rng.randrange(width + 1)
        sh = rng.randrange(0, 9) * (height + 1) + rng.randrange(height + 1)
        original.cpu.mem_write(0x804000, struct.pack('<3I', 0x806000, sw, sh))
        calls.clear()
        checks = 0
        original.call(0x43f200, eax=22, edx=0, ebx=width, ecx=height,
                      args=(rng.randrange(100),))
        assert len(calls) == (sw // (width + 1)) * (sh // (height + 1))
        for index, expected in enumerate(calls):
            output = Cell()
            assert native(sw, sh, width, height, index, c.byref(output))
            assert (output.x, output.y, output.width, output.height) == expected
            assert output.count == len(calls)
            cells += 1
        sentinel = Cell(1, 2, 3, 4, 5)
        assert not native(sw, sh, width, height, len(calls), c.byref(sentinel))
        assert bytes(sentinel) == bytes(Cell(1, 2, 3, 4, 5))
    report = {'status': 'passed', 'sheets': 256, 'cells': cells,
              'scope': 'Actual0x43f200 traversal. File/string/image creation, fallback '
                       'alpha, crop allocation/pixels, color conversion and destruction '
                       'are explicit service hooks. All crop rectangles/order/counts '
                       'compared, including empty grids, partial borders and arbitrary '
                       'progress counts. Actual VF font pixels remain separate.'}
    (args.build_dir / 'font-cell-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
