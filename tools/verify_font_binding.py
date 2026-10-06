"""Compare original font measurement using actual maps and owned original VF glyphs."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP
from original import Original, BOARD, MASK
from verify_font_bank import Bank
from verify_font_map import FontMap


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('archive', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / 'binding.dylib'
    names = ['font_binding.c', 'font_map.c', 'font_measure.c', 'font_bank.c',
             'font_stencils.c', 'sprite_files.c', 'font_sheet.c', 'font_cell.c', 'font_image.c',
             'font_outline.c', 'font_stencil.c', 'image_crop.c', 'image_key.c',
             'image.c', 'vf.c', 'render_geometry.c', 'surface.c', 'render_dispatch.c']
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    *[str(root / 'source' / name) for name in names], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_vf_open.argtypes = [c.c_char_p]
    native.vertrix_vf_open.restype = c.c_void_p
    native.vertrix_vf_close.argtypes = [c.c_void_p]
    native.vertrix_font_bank_load.argtypes = [c.c_void_p, c.POINTER(c.c_uint32), c.POINTER(Bank)]
    native.vertrix_font_bank_free.argtypes = [c.POINTER(Bank)]
    native.vertrix_font_map_construct.argtypes = [c.POINTER(FontMap)]
    native.vertrix_font_maps_initialize.argtypes = [c.POINTER(FontMap), c.c_size_t] + [c.c_uint32] * 4
    native.vertrix_font_bank_measure.argtypes = [c.POINTER(Bank), c.POINTER(FontMap), c.c_void_p,
        c.c_size_t, c.c_uint8, c.c_uint8, c.c_uint8, c.POINTER(c.c_uint32), c.POINTER(c.c_uint32)]
    original = Original(args.executable)
    original.call(0x4b9050)
    cpu = original.cpu
    rng = random.Random(0x48ab10440610)
    for case in range(1024):
        raw = rng.randbytes(520)
        mapping = FontMap.from_buffer_copy(raw)
        cpu.mem_write(0x804000, raw + rng.randbytes(4))
        original.call(0x48ab10, eax=0x804000)
        assert native.vertrix_font_map_construct(c.byref(mapping))
        assert bytes(mapping) == bytes(cpu.mem_read(0x804000, 520))
        assert bytes(cpu.mem_read(0x804208, 4)) == struct.pack('<I', 0x5176b4)
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    bank = Bank()
    masks = (c.c_uint32 * 3)(0xff0000, 0xff00, 0xff)
    assert native.vertrix_font_bank_load(archive, masks, c.byref(bank))
    native.vertrix_vf_close(archive)
    maps = (FontMap * 19)()
    for font in range(19):
        assert native.vertrix_font_map_construct(c.byref(maps[font]))
        cpu.mem_write(0x541988 + font * 524, bytes(524))
        original.call(0x48ab10, eax=0x541988 + font * 524)
    cpu.mem_write(0x805000, struct.pack('<3I', 0, 15, 15))
    cpu.mem_write(0x805040, struct.pack('<3I', 0, 21, 21))
    cpu.mem_map(0x900000, 0x10000)
    for index, image in enumerate(bank.glyphs):
        pointer = 0x900000 + index * 64
        cpu.mem_write(pointer, struct.pack('<3I', 0, image.width, image.height) + bytes(28))
        cpu.mem_write(0x5410f8 + index * 4, struct.pack('<I', pointer))

    def word(address):
        return struct.unpack('<I', cpu.mem_read(address, 4))[0]

    def boundary(cpu, address, size, context):
        eax, edx, stack = [cpu.reg_read(r) for r in (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP)]
        cleanup = 0
        if address == 0x4877f0:
            cpu.reg_write(UC_X86_REG_EAX, 0x805000 if edx == 6 else 0x805040)
        elif address == 0x4ccfe0:
            cpu.reg_write(UC_X86_REG_EAX, int(cpu.mem_read(eax, 1) != b'\0'))
        elif address == 0x4ca000:
            cpu.reg_write(UC_X86_REG_EAX, 0x804000)
        elif address == 0x4abd70:
            cpu.mem_write(eax, bytes(0x15c))
            cpu.mem_write(eax + 0x158, struct.pack('<I', 0x806000))
        elif address == 0x4adf20:
            cpu.mem_write(eax + 0xb4, struct.pack('<I', word(stack + 12)))
            cleanup = 20
        cpu.reg_write(UC_X86_REG_EIP, word(stack))
        cpu.reg_write(UC_X86_REG_ESP, stack + 4 + cleanup)

    for address in (0x4877f0, 0x4ccfe0, 0x4ca000, 0x4abd70, 0x4adf20, 0x700300):
        cpu.hook_add(UC_HOOK_CODE, boundary, begin=address, end=address)
    cpu.mem_write(0x806000, struct.pack('<I', 0x700300))
    original.call(0x43fc50)
    assert native.vertrix_font_maps_initialize(maps, 19, 15, 15, 21, 21)
    for font in range(19):
        assert bytes(maps[font]) == bytes(cpu.mem_read(0x541988 + font * 524, 520))
    cases = 0
    for font in range(19):
        for sample in range(64):
            text = (bytes(range(1, 256)) if sample == 0 else
                    bytes(rng.randrange(1, 256) for _ in range(rng.randrange(65)))) + b'\0'
            mode, unscaled, screen_mode = rng.randrange(17), rng.randrange(2), rng.randrange(17)
            cpu.mem_write(0x802000, text)
            cpu.mem_write(0x544070, struct.pack('<I', 0x809000))
            cpu.mem_write(0x809220, bytes([unscaled, screen_mode]))
            original.call(0x440610, eax=font, edx=0x802000, ebx=mode, ecx=BOARD, args=(MASK,))
            width, height = c.c_uint32(123), c.c_uint32(456)
            assert native.vertrix_font_bank_measure(c.byref(bank), c.byref(maps[font]), text,
                len(text), mode, unscaled, screen_mode, c.byref(width), c.byref(height))
            assert (width.value, height.value) == (word(BOARD), word(MASK)), (font, sample)
            cases += 1
    before = width.value, height.value
    assert not native.vertrix_font_bank_measure(c.byref(bank), c.byref(maps[0]), b'A', 1,
        16, 0, 16, c.byref(width), c.byref(height))
    assert (width.value, height.value) == before
    native.vertrix_font_bank_free(c.byref(bank))
    report = {'status': 'passed', 'constructor_cases': 1024, 'fonts': 19, 'measurements': cases,
              'scope': 'Actual48ab10 constructor matches all fields including preserved255. '
                       'Actual43fc50 mapping and440610 measurement with actual43f420/48ac00 '
                       'glyph lookup and4b14c0 dimensions match real owned VF bank. '
                       'Resource lookup for stencil dimensions and allocation/constructor/attach/'
                       'destructor/empty comparison remain hooks. Rendering/application integration '
                       'remain unfinished.'}
    (args.build_dir / 'font-binding-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
