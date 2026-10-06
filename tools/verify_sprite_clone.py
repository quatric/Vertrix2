"""Compare original483110 descriptor/pixel copying with allocation supplied."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original, BOARD, MASK
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP


class Image(c.Structure):
    _fields_ = [('width', c.c_uint32), ('height', c.c_uint32), ('rgba', c.POINTER(c.c_ubyte))]


class Frame(c.Structure):
    _fields_ = [('image', Image), ('frame_count', c.c_uint32), ('metadata', c.c_uint32 * 10)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = a.build_dir.resolve() / 'sprite-clone.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    *[str(source / name) for name in ['image_clone.c', 'image_mirror.c', 'image.c', 'vf.c']],
                    '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_sprite_clone.argtypes = [c.POINTER(Frame), c.POINTER(Frame)]
    native.vertrix_sprite_replace_mirrored.argtypes = [c.POINTER(Frame), c.POINTER(Frame)]
    native.vertrix_sprite_bank_replace_mirrored.argtypes = [c.POINTER(Frame), c.c_size_t,
                                                           c.c_size_t, c.c_size_t]
    native.vertrix_sprite_free.argtypes = [c.POINTER(Frame)]
    original = Original(a.executable)
    cpu = original.cpu
    allocations = []
    discarded = []
    def allocate(cpu, address, size, context):
        count = cpu.reg_read(UC_X86_REG_EAX) * cpu.reg_read(UC_X86_REG_EDX)
        target = 0x802000 if not allocations else 0x809000
        allocations.append(count)
        cpu.mem_write(target, bytes(count))
        esp = cpu.reg_read(UC_X86_REG_ESP)
        cpu.reg_write(UC_X86_REG_EAX, target)
        cpu.reg_write(UC_X86_REG_EIP, struct.unpack('<I', cpu.mem_read(esp, 4))[0])
        cpu.reg_write(UC_X86_REG_ESP, esp + 4)
    cpu.hook_add(UC_HOOK_CODE, allocate, begin=0x4ec160, end=0x4ec160)
    def discard(cpu, address, size, context):
        discarded.append(cpu.reg_read(UC_X86_REG_EAX))
        esp = cpu.reg_read(UC_X86_REG_ESP)
        cpu.reg_write(UC_X86_REG_EIP, struct.unpack('<I', cpu.mem_read(esp, 4))[0])
        cpu.reg_write(UC_X86_REG_ESP, esp + 4)
    cpu.hook_add(UC_HOOK_CODE, discard, begin=0x4830f0, end=0x4830f0)
    rng = random.Random(0x483110)
    pixels = 0
    for case in range(2048):
        width, height = rng.randrange(1, 65), rng.randrange(1, 65)
        raw = rng.randbytes(width * height * 4)
        descriptor = bytearray(rng.randbytes(40))
        struct.pack_into('<3I', descriptor, 0, 0x804000, width, height)
        descriptor[39] = 4
        cpu.mem_write(BOARD, bytes(descriptor))
        cpu.mem_write(0x804000, raw)
        cpu.mem_write(0x802100, rng.randbytes(40))
        cpu.mem_write(0x803000, struct.pack('<2I', BOARD, 0x802100))
        cpu.mem_write(MASK, struct.pack('<6I', 0x803000, 2, 0, 0, 0, 0))
        allocations.clear()
        discarded.clear()
        original.call(0x487790, eax=MASK, edx=1, ebx=0)
        assert discarded == [0x802100]
        assert struct.unpack('<2I', cpu.mem_read(0x803000, 8)) == (BOARD, 0x802000)
        assert allocations == [40, len(raw)]
        expected = bytearray(descriptor)
        struct.pack_into('<I', expected, 0, 0x809000)
        assert bytes(expected) == bytes(cpu.mem_read(0x802000, 40)), case
        assert raw == bytes(cpu.mem_read(0x809000, len(raw))), case
        assert bytes(descriptor) == bytes(cpu.mem_read(BOARD, 40))
        storage = (c.c_ubyte * len(raw)).from_buffer_copy(raw)
        frame = Frame(Image(width, height, storage), rng.randrange(1, 100),
                      (c.c_uint32 * 10)(*struct.unpack('<10I', descriptor)))
        prior = bytes(frame)
        cloned = Frame()
        assert native.vertrix_sprite_clone(c.byref(frame), c.byref(cloned))
        assert bytes(frame) == prior and bytes(storage) == raw
        assert bytes(cloned.metadata)[4:] == bytes(expected)[4:]
        assert cloned.metadata[0] == frame.metadata[0]
        assert cloned.frame_count == frame.frame_count
        assert c.string_at(cloned.image.rgba, len(raw)) == raw
        assert c.addressof(cloned.image.rgba.contents) != c.addressof(storage)
        before = c.string_at(cloned.image.rgba, len(raw))
        assert not native.vertrix_sprite_clone(c.byref(frame), c.byref(cloned))
        assert c.string_at(cloned.image.rgba, len(raw)) == before
        original.call(0x4877d0, eax=MASK, edx=1)
        bank = (Frame * 2)(frame, cloned)
        assert native.vertrix_sprite_bank_replace_mirrored(bank, 2, 0, 1)
        cloned = bank[1]
        assert bytes(bank[0]) == prior
        before_bank = bytes(bank)
        assert not native.vertrix_sprite_bank_replace_mirrored(bank, 2, 0, 2)
        assert bytes(bank) == before_bank
        assert c.string_at(cloned.image.rgba, len(raw)) == bytes(cpu.mem_read(0x809000, len(raw)))
        assert bytes(cloned.metadata)[4:] == bytes(cpu.mem_read(0x802004, 36))
        assert bytes(frame) == prior and bytes(storage) == raw
        assert not native.vertrix_sprite_replace_mirrored(c.byref(frame), c.byref(frame))
        native.vertrix_sprite_free(c.byref(cloned))
        pixels += width * height
    report = {'status': 'passed', 'cases': 2048, 'pixels': pixels,
              'scope': 'Complete original487790 clone replacement then4877d0 mirror execute, '
                       'including actual483110/483ce0 and resource lookup. Only calloc and '
                       'discarded old descriptor disposal are supplied. Native owns independent pixels '
                       'and retains serialized metadata/frame count. Original pointer field is '
                       'represented by native image.rgba. Mirrored replacement composition matches '
                       'actual cloned descriptor483ce0 execution with an occupied native destination. '
                       'Indexed direct-bank mutation matches; linked banks and full application remain unfinished.'}
    (a.build_dir / 'sprite-clone-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
