"""Compare original styled text draw traversal before sprite rendering."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_EBP
from original import Original
from verify_font_bank import Bank
from verify_font_map import FontMap


class Placement(c.Structure):
    _fields_ = [('descriptor', c.c_uint16), ('x', c.c_int16), ('y', c.c_int16), ('glyph', c.c_uint8)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'scaled-run.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
        *[str(source / name) for name in ('font_run.c', 'font_binding.c', 'font_measure.c',
          'render_geometry.c', 'surface.c', 'render_dispatch.c')], '-o', str(library)], check=True)
    native = c.CDLL(str(library)).vertrix_font_run_scaled
    native.argtypes = [c.POINTER(Bank), c.POINTER(FontMap), c.c_void_p, c.c_size_t,
        c.c_int16, c.c_int16, c.c_uint8, c.c_uint8, c.c_uint8, c.c_uint8, c.POINTER(Placement), c.c_size_t,
        c.POINTER(c.c_size_t), c.POINTER(c.c_int16)]
    original = Original(args.executable)
    original.call(0x4b9050)
    cpu = original.cpu
    cpu.mem_map(0x900000, 0x10000)
    draws = []
    terminal = 0

    def word(address):
        return struct.unpack('<I', cpu.mem_read(address, 4))[0]

    def boundary(cpu, address, size, context):
        nonlocal terminal
        if address == 0x440b29:
            terminal = struct.unpack('<h', cpu.mem_read(cpu.reg_read(UC_X86_REG_EBP) - 0x10, 2))[0]
            return
        eax, edx, ebx, stack = [cpu.reg_read(r) for r in
            (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ESP)]
        cleanup = 0
        if address == 0x4ca000:
            cpu.reg_write(UC_X86_REG_EAX, 0x804000)
        elif address == 0x4abd70:
            cpu.mem_write(eax, bytes(0x15c))
            cpu.mem_write(eax + 0x158, struct.pack('<I', 0x806000))
        elif address == 0x4adf20:
            cpu.mem_write(eax + 0xe, struct.pack('<H', edx & 65535))
            cpu.mem_write(eax + 0x16, struct.pack('<H', ebx & 65535))
            cpu.mem_write(eax + 0xb4, struct.pack('<I', word(stack + 12)))
            cleanup = 20
        elif address == 0x700310:
            descriptor = word(eax + 0xb4)
            x = struct.unpack('<h', cpu.mem_read(eax + 0xe, 2))[0]
            y = struct.unpack('<h', cpu.mem_read(eax + 0x16, 2))[0]
            assert bytes(cpu.mem_read(eax + 0x8e, 2)) == b'\0\1'
            assert bytes(cpu.mem_read(eax + 0x44, 1)) == bytes([mode])
            assert bytes(cpu.mem_read(eax + 0x91, 1)) == bytes([override])
            assert edx == 0x800000
            draws.append(((descriptor - 0x900000) // 64, x, y))
        cpu.reg_write(UC_X86_REG_EIP, word(stack))
        cpu.reg_write(UC_X86_REG_ESP, stack + 4 + cleanup)

    for address in (0x4ca000, 0x4abd70, 0x4adf20, 0x700300, 0x700310, 0x440b29):
        cpu.hook_add(UC_HOOK_CODE, boundary, begin=address, end=address)
    cpu.mem_write(0x806000, struct.pack('<3I', 0x700300, 0, 0x700310))
    rng = random.Random(0x440a20)
    bank = Bank()
    bank.ready = 1
    placements_total = 0
    for case in range(1024):
        mapping = FontMap(rng.getrandbits(32), 0)
        for glyph in range(256):
            mapping.glyphs[glyph] = rng.choice([-1, rng.randrange(128)])
        cpu.mem_write(0x541988, bytes(mapping))
        for index in range(128):
            width = rng.getrandbits(32)
            bank.glyphs[index].width = width
            bank.glyphs[index].height = 1
            bank.glyphs[index].rgba = 1
            pointer = 0x900000 + index * 64
            cpu.mem_write(pointer, struct.pack('<3I', 0, width, 1))
            cpu.mem_write(0x5410f8 + index * 4, struct.pack('<I', pointer))
        text = (bytes(range(1, 256)) if case % 128 == 0 else
                bytes(rng.randrange(1, 256) for _ in range(rng.randrange(65)))) + b'\0'
        x, y = rng.randrange(-32768, 32768), rng.randrange(-32768, 32768)
        mode, override, unscaled, screen_mode = rng.randrange(17), rng.randrange(3), rng.randrange(2), rng.randrange(17)
        style = bytearray(0x15c)
        style[0x44], style[0x91] = mode, override
        cpu.mem_write(0x801000, bytes(style))
        cpu.mem_write(0x544070, struct.pack('<I', 0x809000))
        cpu.mem_write(0x809220, bytes([unscaled, screen_mode]))
        cpu.mem_write(0x802000, text)
        draws.clear()
        original.call(0x440a20, eax=0x800000, edx=0, ebx=x & 65535, ecx=y & 65535, args=(0x802000, 0x801000))
        placements = (Placement * 256)()
        count, final = c.c_size_t(123), c.c_int16(456)
        assert native(c.byref(bank), c.byref(mapping), text, len(text), x, y,
                      mode, override, unscaled, screen_mode, placements, len(placements), c.byref(count), c.byref(final))
        assert count.value == len(draws) and final.value == terminal, case
        actual = [(p.descriptor, p.x, p.y) for p in placements[:count.value]]
        assert actual == draws, case
        assert [p.glyph for p in placements[:count.value]] == [g for g in text[:-1]
                if g != 32 and mapping.glyphs[g] != -1]
        placements_total += count.value
        before = bytes(placements), count.value, final.value
        assert not native(c.byref(bank), c.byref(mapping), b'A', 1, x, y,
                          mode, override, unscaled, screen_mode, placements, len(placements), c.byref(count), c.byref(final))
        assert (bytes(placements), count.value, final.value) == before
    report = {'status': 'passed', 'cases': 1024, 'placements': placements_total,
              'scope': 'Actual440a20, actual43f420/48ac00 lookup and4b14c0 measurement. Allocation, '
                       'object constructor/resource attach, virtual draw and destructor '
                       'are service hooks. Glyph handles, signed coordinates, inherited scale/override, flags8e/8f, '
                       'missing/space measured traversal and final signed-word position match. Full-width '
                       'random dimensions/spaces cover measurement narrowing and word wrap. '
                       'Actual rendered pixels and full application remain separate.'}
    (args.build_dir / 'font-scaled-run-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
