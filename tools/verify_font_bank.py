"""Compare complete owned VF font bank with original loading/transform execution."""
import argparse
import ctypes as c
import io
import json
import struct
import subprocess
from pathlib import Path
from PIL import Image
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP
from original import Original
from verify_image import NativeImage


class Bank(c.Structure):
    _fields_ = [('glyphs', NativeImage * 548), ('origin_x', c.c_uint32 * 548),
                ('origin_y', c.c_uint32 * 548), ('ready', c.c_uint)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('archive', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / 'bank.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    *[str(root / 'source' / name) for name in ('font_bank.c', 'font_stencils.c', 'sprite_files.c',
                       'font_sheet.c', 'font_cell.c', 'font_image.c', 'font_outline.c',
                       'font_stencil.c', 'image_crop.c', 'image_key.c', 'image.c', 'vf.c')],
                    '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_vf_open.argtypes = [c.c_char_p]
    native.vertrix_vf_open.restype = c.c_void_p
    native.vertrix_vf_close.argtypes = [c.c_void_p]
    native.vertrix_vf_find.argtypes = [c.c_void_p, c.c_char_p, c.POINTER(c.c_uint32)]
    native.vertrix_vf_size.argtypes = [c.c_void_p, c.c_uint32, c.POINTER(c.c_uint32)]
    native.vertrix_vf_read.argtypes = [c.c_void_p, c.c_uint32, c.c_uint32, c.c_void_p, c.c_size_t]
    native.vertrix_font_bank_load.argtypes = [c.c_void_p, c.POINTER(c.c_uint32), c.POINTER(Bank)]
    native.vertrix_font_bank_free.argtypes = [c.POINTER(Bank)]
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive

    def read(name):
        index, size = c.c_uint32(), c.c_uint32()
        assert native.vertrix_vf_find(archive, name.encode(), c.byref(index))
        assert native.vertrix_vf_size(archive, index, c.byref(size))
        data = c.create_string_buffer(size.value)
        assert native.vertrix_vf_read(archive, index, 0, data, size.value)
        return data.raw

    operations = json.loads((root / 'docs/font-load-plan.json').read_text())['operations']
    sheets = {op['eax']: op for op in operations if op['address'] == '0x43f200'}
    original = Original(args.executable)
    original.cpu.mem_map(0x900000, 0x1000000)
    heap = 0x900000

    def allocate(width, height, x, y, raw=None):
        nonlocal heap
        descriptor = heap
        pointer = descriptor + 64
        heap = (pointer + width * height * 4 + 63) & ~63
        assert heap < 0x1900000
        original.cpu.mem_write(descriptor, struct.pack('<10I', pointer, width, height, x, y, 0, 0, 0, 0, 0x04010000))
        original.cpu.mem_write(pointer, raw if raw is not None else bytes(width * height * 4))
        return descriptor

    blob = read('sprite/Circle.spr')
    cursor = 2
    stencil_handles = {}
    for frame in range(struct.unpack_from('<H', blob)[0]):
        header = blob[cursor:cursor + 48]
        width, height = struct.unpack_from('<2I', header, 12)
        cursor += 48
        payload = blob[cursor:cursor + width * height * 4]
        cursor += len(payload)
        if frame in (6, 9):
            raw = bytearray(payload)
            raw[0::4], raw[2::4] = payload[2::4], payload[0::4]
            raw[3::4] = bytes(255 if alpha == 0 else 0 for alpha in payload[3::4])
            stencil_handles[frame] = allocate(width, height, 0, 0, bytes(raw))

    def boundary(cpu, address, size, context):
        stack = cpu.reg_read(UC_X86_REG_ESP)
        eax, edx, ebx, ecx = [cpu.reg_read(r) for r in
                            (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX)]
        cleanup = 4
        if address == 0x43f200:
            operation = sheets[eax]
            image = Image.open(io.BytesIO(read(operation['vf_image']))).convert('RGBA')
            raw = bytearray(image.tobytes())
            key = bytes(raw[:4])
            for i in range(0, len(raw), 4):
                raw[i + 3] = 0 if bytes(raw[i:i + 4]) == key else 255
            image = Image.frombytes('RGBA', image.size, bytes(raw))
            columns, rows = image.width // (ebx + 1), image.height // (ecx + 1)
            for index in range(columns * rows):
                x, y = 1 + (index % columns) * (ebx + 1), 1 + (index // columns) * (ecx + 1)
                cropped = image.crop((x, y, x + ebx, y + ecx)).tobytes()
                handle = allocate(ebx, ecx, 0, 0, cropped)
                cpu.mem_write(0x5410f8 + (edx + index) * 4, struct.pack('<I', handle))
            cleanup += 4
        elif address == 0x4877f0:
            cpu.reg_write(UC_X86_REG_EAX, stencil_handles[edx])
        elif address == 0x483060:
            cpu.reg_write(UC_X86_REG_EAX, allocate(eax, edx, ebx, ecx))
            cleanup += 32
        elif address == 0x483110:
            pointer, width, height, x, y = struct.unpack('<5I', cpu.mem_read(eax, 20))
            raw = bytes(cpu.mem_read(pointer, width * height * 4))
            cpu.reg_write(UC_X86_REG_EAX, allocate(width, height, x, y, raw))
        destination = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
        cpu.reg_write(UC_X86_REG_ESP, stack + cleanup)
        cpu.reg_write(UC_X86_REG_EIP, destination)

    for address in (0x43fc50, 0x43f200, 0x4877f0, 0x483060, 0x483110, 0x418270):
        original.cpu.hook_add(UC_HOOK_CODE, boundary, begin=address, end=address)
    try:
        original.call(0x43eab0)
    except RuntimeError:
        original.cpu.emu_start(original.cpu.reg_read(UC_X86_REG_EIP), 0x700000, count=100_000_000)
        assert original.cpu.reg_read(UC_X86_REG_EIP) == 0x700000
    assert struct.unpack('<I', original.cpu.mem_read(0x54406c, 4))[0] == 548
    masks = (c.c_uint32 * 3)(0xff0000, 0xff00, 0xff)
    bank = Bank()
    assert native.vertrix_font_bank_load(archive, masks, c.byref(bank))
    assert bank.ready == 1
    references = []
    pixels = 0
    for index in range(548):
        handle = struct.unpack('<I', original.cpu.mem_read(0x5410f8 + index * 4, 4))[0]
        pointer, width, height, x, y = struct.unpack('<5I', original.cpu.mem_read(handle, 20))
        reference = bytes(original.cpu.mem_read(pointer, width * height * 4))
        glyph = bank.glyphs[index]
        assert (glyph.width, glyph.height, bank.origin_x[index], bank.origin_y[index]) == (width, height, x, y), index
        assert c.string_at(glyph.rgba, len(reference)) == reference, index
        references.append(reference)
        pixels += width * height
    saved = bytes(bank)
    assert not native.vertrix_font_bank_load(archive, masks, c.byref(bank))
    assert bytes(bank) == saved
    invalid = Bank()
    bad_masks = (c.c_uint32 * 3)(0, 0, 0)
    assert not native.vertrix_font_bank_load(archive, bad_masks, c.byref(invalid))
    assert bytes(invalid) == bytes(Bank())
    native.vertrix_vf_close(archive)
    for index, reference in enumerate(references):
        assert c.string_at(bank.glyphs[index].rgba, len(reference)) == reference
    native.vertrix_font_bank_free(c.byref(bank))
    assert bytes(bank) == bytes(Bank())
    report = {'status': 'passed', 'glyphs': 548, 'derived_glyphs': 82, 'pixels': pixels,
              'scope': 'Actual43eab0 with actual43f110/43f190 and4831b0/483400 transforms, '
                       'including source84..93 mutation through three outline passes. '
                       'Hooks supply independently decoded VF base sheets/stencils, resource '
                       'allocation/clone, progress and separately verified map initialization. '
                       'All final glyph pixels, dimensions, descriptor origins and owned '
                       'lifetime match. Original filenames fixed; alternate configurations '
                       'and text rendering remain separate. OriginalRGBA color order tested.'}
    (args.build_dir / 'font-bank-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
