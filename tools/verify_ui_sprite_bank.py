"""Compare original45dd52..45de10 UI sprite substitutions with native bank."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from verify_sprite_clone import Frame, Image
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = a.build_dir.resolve() / 'ui-sprite-bank.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    *[str(source / name) for name in ['image_clone.c', 'image_mirror.c', 'image.c', 'vf.c']],
                    '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_sprite_clone.argtypes = [c.POINTER(Frame), c.POINTER(Frame)]
    native.vertrix_sprite_free.argtypes = [c.POINTER(Frame)]
    native.vertrix_sprite_bank_configure_ui.argtypes = [c.POINTER(Frame), c.c_size_t, c.c_size_t]
    original = Original(a.executable)
    cpu = original.cpu
    cpu.mem_map(0x900000, 0x400000)
    heap = 0xa00000
    discarded = []
    def boundary(cpu, address, size, context):
        nonlocal heap
        if address == 0x4ec160:
            count = cpu.reg_read(UC_X86_REG_EAX) * cpu.reg_read(UC_X86_REG_EDX)
            target = heap
            heap += (count + 15) & ~15
            cpu.mem_write(target, bytes(count))
            cpu.reg_write(UC_X86_REG_EAX, target)
        else:
            discarded.append(cpu.reg_read(UC_X86_REG_EAX))
        esp = cpu.reg_read(UC_X86_REG_ESP)
        cpu.reg_write(UC_X86_REG_EIP, struct.unpack('<I', cpu.mem_read(esp, 4))[0])
        cpu.reg_write(UC_X86_REG_ESP, esp + 4)
    for address in [0x4ec160, 0x4830f0]:
        cpu.hook_add(UC_HOOK_CODE, boundary, begin=address, end=address)
    rng = random.Random(0x45dd52)
    pixels = 0
    for case in range(256):
        heap = 0xa00000
        discarded.clear()
        count = 35
        bank = (Frame * count)()
        descriptors = []
        for index in range(count):
            width, height = rng.randrange(1, 8), rng.randrange(1, 8)
            raw = rng.randbytes(width * height * 4)
            descriptor = bytearray(rng.randbytes(40))
            pointer = 0x910000 + 256 * index
            struct.pack_into('<3I', descriptor, 0, pointer, width, height)
            descriptor[39] = 4
            address = 0x900000 + 64 * index
            descriptors.append(address)
            cpu.mem_write(address, bytes(descriptor))
            cpu.mem_write(pointer, raw)
            storage = (c.c_ubyte * len(raw)).from_buffer_copy(raw)
            frame = Frame(Image(width, height, storage), count,
                          (c.c_uint32 * 10)(*struct.unpack('<10I', descriptor)))
            assert native.vertrix_sprite_clone(c.byref(frame), c.byref(bank[index]))
        cpu.mem_write(0x902000, struct.pack('<35I', *descriptors))
        cpu.mem_write(0x5449fc, struct.pack('<6I', 0x902000, count, 0, 0, 0, 0))
        first = rng.choice([index for index in range(count) if index != 1])
        cpu.mem_write(0x5466c4, struct.pack('<I', first))
        original.call(0x45dd52, stop=0x45de10)
        assert native.vertrix_sprite_bank_configure_ui(bank, count, first)
        assert discarded == [descriptors[index] for index in [1, 10, 12, 29, 25]]
        pointers = struct.unpack('<35I', cpu.mem_read(0x902000, 140))
        for index, pointer in enumerate(pointers):
            descriptor = bytes(cpu.mem_read(pointer, 40))
            data, width, height = struct.unpack_from('<3I', descriptor)
            assert bank[index].image.width == width and bank[index].image.height == height
            assert bytes(bank[index].metadata)[4:] == descriptor[4:], (case, index)
            assert c.string_at(bank[index].image.rgba, width * height * 4) == bytes(
                cpu.mem_read(data, width * height * 4)), (case, index)
            pixels += width * height
        before = bytes(bank)
        assert not native.vertrix_sprite_bank_configure_ui(bank, 29, first)
        assert bytes(bank) == before
        for frame in bank:
            native.vertrix_sprite_free(c.byref(frame))
    report = {'status': 'passed', 'banks': 256, 'frames': 8960, 'pixels': pixels,
              'scope': 'Actual45dd52..45de10 executes all five clone/mirror substitutions with '
                       'original helpers and initialized configuration constants. Only allocation '
                       'and old descriptor disposal supplied. All bank frames/descriptors match. '
                       'First source index supplied explicitly; full VF selector/startup remains unfinished.'}
    (a.build_dir / 'ui-sprite-bank-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
