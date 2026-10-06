"""Compare complete original475090 table builder with portable owned tables."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path
import struct
import subprocess
from original import Original
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EIP, UC_X86_REG_ESP


class Tables(c.Structure):
    _fields_ = [('lookup', c.POINTER(c.c_uint32)), ('hue', c.POINTER(c.c_uint8)), ('channels', c.c_uint8 * 20301), ('auxiliary', c.c_uint32 * 255)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'palette-tables.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-ffp-contract=off', '-Wall', '-Wextra', '-Werror', str(source / 'palette_color.c'), str(source / 'palette_tables.c'), str(source / 'render_palette.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_palette_tables_build.argtypes = [c.POINTER(Tables)]
    native.vertrix_palette_tables_free.argtypes = [c.POINTER(Tables)]
    native.vertrix_palette_tables_pixel.argtypes = [c.POINTER(Tables), c.c_uint32, c.c_int, c.POINTER(c.c_uint16), c.POINTER(c.c_uint32)]
    tables = Tables()
    assert native.vertrix_palette_tables_build(c.byref(tables)) == 1
    before = bytes(tables)
    assert native.vertrix_palette_tables_build(c.byref(tables)) == 0
    assert bytes(tables) == before
    original = Original(args.executable)
    original.cpu.mem_map(0x900000, 0x200000)
    allocations = []
    next_address = 0x900000
    def allocate(cpu, address, size, data):
        nonlocal next_address
        amount = cpu.reg_read(UC_X86_REG_EAX) * cpu.reg_read(UC_X86_REG_EDX)
        result = next_address
        next_address += (amount + 4095) & ~ 4095
        assert next_address <= 0xb00000
        cpu.mem_write(result, bytes(amount))
        allocations.append((result, amount))
        stack = cpu.reg_read(UC_X86_REG_ESP)
        target = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
        cpu.reg_write(UC_X86_REG_EAX, result)
        cpu.reg_write(UC_X86_REG_ESP, stack + 4)
        cpu.reg_write(UC_X86_REG_EIP, target)
    original.cpu.hook_add(UC_HOOK_CODE, allocate, begin=0x4ec160, end=0x4ec160)
    try:
        original.call(0x475090)
    except RuntimeError:
        for chunk in range(100):
            original.cpu.emu_start(original.cpu.reg_read(UC_X86_REG_EIP), 0x700000, count=100_000_000)
            if original.cpu.reg_read(UC_X86_REG_EIP) == 0x700000:
                break
        assert original.cpu.reg_read(UC_X86_REG_EIP) == 0x700000
    assert [amount for _, amount in allocations] == [1048576, 262144]
    lookup_address = struct.unpack('<I', original.cpu.mem_read(0x54b800, 4))[0]
    hue_address = struct.unpack('<I', original.cpu.mem_read(0x54b804, 4))[0]
    expected_lookup = bytes(original.cpu.mem_read(lookup_address, 1048576))
    native_lookup = struct.pack('<262144I', * tables.lookup[: 262144])
    assert native_lookup == expected_lookup
    assert c.string_at(tables.hue, 262144) == bytes(original.cpu.mem_read(hue_address, 262144))
    assert bytes(tables.channels) == bytes(original.cpu.mem_read(0x5468b0, 20301))
    assert struct.pack('<255I', * tables.auxiliary) == bytes(original.cpu.mem_read(0x54c1d4, 1020))
    rng = random.Random(0x475495)
    original.cpu.mem_write(0x5bb764, struct.pack('<I', 0x804000))
    original.cpu.mem_write(0x5bb768, struct.pack('<I', 0x804004))
    for case in range(8192):
        pixel = rng.getrandbits(32)
        channels = (c.c_uint16 * 3)(* [rng.randrange(101) for _ in range(3)])
        fixed = case % 2
        original.cpu.mem_write(0x804000, struct.pack('<2I', pixel, 0xdeadbeef))
        original.cpu.mem_write(0x54d5dc, bytes(channels))
        original.call(0x48d7f0 if fixed else 0x48d740)
        expected = struct.unpack('<I', original.cpu.mem_read(0x804004, 4))[0]
        output = c.c_uint32(0xdeadbeef)
        assert native.vertrix_palette_tables_pixel(c.byref(tables), pixel, fixed, channels, c.byref(output)) == 1
        assert output.value == expected, (case, pixel, output.value, expected)
    native.vertrix_palette_tables_free(c.byref(tables))
    assert bytes(tables) == bytes(c.sizeof(tables))
    report = {'status': 'passed', 'lookup_entries': 262144, 'hue_bytes': 262144, 'channel_bytes': 20301, 'auxiliary_entries': 255, 'bound_pixel_cases': 8192, 'scope': 'Complete original475090 executes with only calloc replaced. ' 'All conversion, nearest matching, table loops and software math remain original. ' 'Native owned tables match all outputs and8192 pixel cases using ' 'the original builder default pointer selection. Other global pointer-table selection, ' 'complete rendering and playable application remain unfinished.'}
    (args.build_dir / 'palette-tables-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
