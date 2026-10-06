"""Compare complete original471100 companion creation with native actor bytes."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original, BOARD
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_EBP, UC_X86_REG_EDI


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'sprite-actor.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
        *[str(source / name) for name in ['sprite_actor_storage.c', 'actor_storage.c',
                                         'actor_style_storage.c', 'ui_companion_storage.c',
                                         'ui_display_layout.c']], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_sprite_actor_storage_construct.argtypes = [c.c_void_p, c.c_size_t,
        c.c_int16, c.c_int16, c.c_uint32, c.c_void_p, c.c_size_t, c.c_uint32, c.c_uint32]
    native.vertrix_ui_companion_storage_construct.argtypes = [c.c_void_p, c.c_size_t,
        c.c_size_t, c.c_uint, c.c_int16, c.c_int16, c.c_uint32, c.c_void_p, c.c_size_t,
        c.c_uint32, c.c_uint32, c.c_uint32]
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_map(0x900000, 0x1000)
    allocations = []
    def allocate(cpu, address, size, context):
        allocations.append(cpu.reg_read(UC_X86_REG_EAX))
        esp = cpu.reg_read(UC_X86_REG_ESP)
        cpu.reg_write(UC_X86_REG_EAX, BOARD)
        cpu.reg_write(UC_X86_REG_EIP, struct.unpack('<I', cpu.mem_read(esp, 4))[0])
        cpu.reg_write(UC_X86_REG_ESP, esp + 4)
    cpu.hook_add(UC_HOOK_CODE, allocate, begin=0x4ca000, end=0x4ca000)
    rng = random.Random(0x471100)
    created = 0
    for case in range(2048):
        index = rng.randrange(128)
        sentinel = index if case % 3 == 0 else 0xffffffff
        configuration = bytearray(rng.randbytes(2048))
        enabled = rng.choice([0, 1, 1, 2, 0xffffffff])
        struct.pack_into('<I', configuration, 0x5cc + index * 4, enabled)
        raw = rng.randbytes(0x160)
        cpu.mem_write(BOARD, raw)
        cpu.mem_write(0x900000, bytes(configuration))
        cpu.mem_write(0x803000, struct.pack('<I', 0xabcdef01))
        cpu.mem_write(0x54671c, struct.pack('<5I', 0, 0x803000, 0, 1, 0))
        allocations.clear()
        x, y = rng.randrange(-32768, 32768), rng.randrange(-32768, 32768)
        frame = rng.getrandbits(32)
        result = original.call(0x471100, eax=x & 0xffffffff, edx=y & 0xffffffff,
                               ebx=frame, ecx=index, args=(sentinel, 0x900000))
        storage = c.create_string_buffer(raw, len(raw))
        config = c.create_string_buffer(bytes(configuration), len(configuration))
        success = native.vertrix_sprite_actor_storage_construct(storage, len(raw), x, y,
                    frame, config, len(configuration), index, sentinel)
        assert success == (enabled == 1), case
        assert result == (BOARD if success else 0), case
        assert allocations == ([0x15c] if success else []), case
        assert storage.raw == bytes(cpu.mem_read(BOARD, len(raw))), case
        assert struct.unpack('<I', cpu.mem_read(0x546724, 4))[0] == int(bool(success))
        assert struct.unpack('<I', cpu.mem_read(0x803000, 4))[0] == (BOARD if success else 0xabcdef01)
        created += bool(success)
    before = storage.raw
    assert not native.vertrix_sprite_actor_storage_construct(storage, 0x15b, 0, 0,
        0, config, len(config), 0, 0)
    assert not native.vertrix_sprite_actor_storage_construct(storage, len(storage), 0, 0,
        0, config, len(config), 0xffffffff, 0)
    assert storage.raw == before
    for case in range(512):
        pair, side = case % 12, (case // 12) % 2
        index = 64 + pair
        configuration = bytearray(rng.randbytes(2048))
        struct.pack_into('<I', configuration, 0x5cc + index * 4, 1)
        offset_x, offset_y = rng.randrange(-32768, 32768), rng.randrange(-32768, 32768)
        x = ((offset_x + [156, 472][side] + 32768) % 65536) - 32768
        y = ((offset_y + 269 + pair * 15 + 32768) % 65536) - 32768
        parameter_one, parameter_other, frame = [rng.getrandbits(32) for _ in range(3)]
        raw = rng.randbytes(0x160)
        cpu.mem_write(BOARD, raw)
        cpu.mem_write(0x900000, bytes(configuration))
        cpu.mem_write(0x54671c, struct.pack('<5I', 0, 0x803000, 0, 1, 0))
        assert original.call(0x471100, eax=x & 0xffffffff, edx=y & 0xffffffff,
            ebx=frame, ecx=index, args=(0xffffffff, 0x900000)) == BOARD
        cpu.mem_write(0x533d70, struct.pack('<h', offset_x))
        cpu.mem_write(0x533d74, struct.pack('<h', offset_y))
        cpu.mem_write(0x4f8c48, struct.pack('<2I', parameter_one, parameter_other))
        cpu.mem_write(0x709000, bytes(0x100))
        cpu.mem_write(0x709080 - 0x34, struct.pack('<I', pair))
        cpu.mem_write(0x709080 - 0x44, struct.pack('<I', pair + 1))
        cpu.reg_write(UC_X86_REG_EBP, 0x709080)
        cpu.reg_write(UC_X86_REG_EDI, pair * 4)
        start, stop = [(0x46e022, 0x46e0a3), (0x46e1b2, 0x46e232)][side]
        original.call(start, eax=BOARD, stop=stop)
        storage = c.create_string_buffer(raw, len(raw))
        config = c.create_string_buffer(bytes(configuration), len(configuration))
        assert native.vertrix_ui_companion_storage_construct(storage, len(raw), pair, side,
            offset_x, offset_y, frame, config, len(config), 0xffffffff, parameter_one, parameter_other)
        assert storage.raw == bytes(cpu.mem_read(BOARD, len(raw))), (case, side, 'companion')
    report = {'status':
        'passed', 'cases' : 2048, 'created' : created,
                                              'companion_setup_cases' : 512,
                                              'scope'
            : 'Complete original471100 executes availability lookup,4abd70 constructor, ' '4710d0/4adf20 positioning,4123d0 styling, sentinel flag and4b5e70 list ' 'registration unchanged. Only allocation4ca000 is supplied with prior storage. ' 'Whole native actor bytes and enabled/disabled results match, including ' 'untouched bytes; original registration count/order is checked. Native ' 'allocation/registration remain external. Additionally512 complete companion ' 'constructor-plus-setup cases match original46e022/46e1b2 including parameters, ' 'thresholds, timing and movement handler. Full VF companion/scene integration remains unfinished.'
        }
        (args.build_dir / 'sprite-actor-storage-verification.json')
                .write_text(json.dumps(report, indent = 2) + '\n')
                    print(json.dumps(report, indent = 2))

                        if __name__ == '__main__' : main()
