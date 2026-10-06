"""Compare owned list resize/growth with original4d8770 allocation decisions."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original, MASK
from verify_object_append import List
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ESP, UC_X86_REG_EIP


class Owned(c.Structure):
    _fields_ = [('list', List), ('growth_step', c.c_uint32)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'object-growth.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
        str(source / 'object_list_owned.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_owned_object_list_resize.argtypes = [c.POINTER(Owned), c.c_size_t]
    native.vertrix_owned_object_list_append.argtypes = [c.POINTER(Owned), c.c_uint32]
    native.vertrix_owned_object_list_free.argtypes = [c.POINTER(Owned)]
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_map(0x900000, 0x1000000)
    allocations = []
    def boundary(cpu, address, size, context):
        eax, edx, ebx = [cpu.reg_read(reg) for reg in (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX)]
        if address == 0x4c9ff0:
            allocations.append(eax)
            cpu.mem_write(0xa00000, b'\xa5' * eax)
            cpu.reg_write(UC_X86_REG_EAX, 0xa00000)
        elif address == 0x4eb5e0:
            cpu.mem_write(eax, bytes(cpu.mem_read(edx, ebx)))
        esp = cpu.reg_read(UC_X86_REG_ESP)
        cpu.reg_write(UC_X86_REG_EIP, struct.unpack('<I', cpu.mem_read(esp, 4))[0])
        cpu.reg_write(UC_X86_REG_ESP, esp + 4)
    for address in [0x4c9ff0, 0x4ca040, 0x4eb5e0]:
        cpu.hook_add(UC_HOOK_CODE, boundary, begin=address, end=address)
    rng = random.Random(0x4d8770)
    for case in range(512):
        count = [0, 1, 2, 31, 32, 8191, 8192, 16384][case % 8]
        step = [0, 1, 4, 32, 4096][case % 5]
        owned = Owned()
        owned.growth_step = step
        assert native.vertrix_owned_object_list_resize(c.byref(owned), count)
        raw = rng.randbytes(count * 4)
        if count:
            c.memmove(owned.list.items, raw, len(raw))
            cpu.mem_write(0x900000, raw)
        cpu.mem_write(MASK, struct.pack('<5I', 0, 0x900000 if count else 0, count, count, step))
        allocations.clear()
        requested = [0, count // 2, count, count + 1, count + 2048][(case // 5) % 5]
        original.call(0x4d8770, eax=MASK, edx=requested, ebx=0xffffffff)
        assert native.vertrix_owned_object_list_resize(c.byref(owned), requested)
        _, pointer, actual_count, capacity, actual_step = struct.unpack('<5I', cpu.mem_read(MASK, 20))
        assert (owned.list.count, owned.list.capacity, owned.growth_step) == (actual_count, capacity, actual_step), case
        assert actual_count == requested
        if requested:
            assert c.string_at(owned.list.items, requested * 4) == bytes(cpu.mem_read(pointer, requested * 4)), case
        if allocations:
            assert allocations == [capacity * 4], case
        native.vertrix_owned_object_list_free(c.byref(owned))
        assert bytes(owned) == bytes(Owned())
    owned = Owned()
    for handle in range(1, 2049):
        assert native.vertrix_owned_object_list_append(c.byref(owned), handle)
        assert owned.list.items[handle - 1] == handle
    assert list(owned.list.items[:owned.list.count]) == list(range(1, 2049))
    saved = bytes(owned)
    assert not native.vertrix_owned_object_list_append(c.byref(owned), 0)
    assert bytes(owned) == saved
    native.vertrix_owned_object_list_free(c.byref(owned))
    report = {'status': 'passed', 'cases': 512, 'native_append_sequence': 2048,
        'scope': 'Complete original4d8770 resize with allocation/free and CRT copy supplied. '
                 'Original allocation policy, count/capacity and all active slots match native '
                 'initial/shrink/grow/zero behavior including adaptive/fixed growth. Original '
                 'memset executes unchanged. Newly unused allocation tail is unspecified and '
                 'not compared. Native ordered append sequence and ownership disposal pass. '
                 'Full scene/application execution remains unfinished.'}
    (args.build_dir / 'object-growth-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
