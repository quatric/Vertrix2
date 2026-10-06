"""Compare player-linked number selection and refresh with original handlers."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original, BOARD, MASK
from verify_object_find import ObjectList
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP


class Number(c.Structure):
    _fields_ = [(name, c.c_uint32) for name in ['id', 'value', 'mode', 'width', 'show_zero', 'handler']] + [('refresh_index', c.c_int16), ('refresh', c.c_uint32)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = a.build_dir.resolve() / 'number-player.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', * [str(source / name) for name in ['number_player.c', 'number_text.c', 'object_list.c']], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    callback = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_uint32), c.c_void_p)
    native.vertrix_number_player_update.argtypes = [c.POINTER(Number), c.POINTER(ObjectList), callback, callback, c.c_void_p, c.POINTER(c.c_uint32), c.c_size_t, c.POINTER(c.c_uint32), c.c_size_t, c.c_void_p, c.c_size_t]
    original = Original(a.executable)
    cpu = original.cpu
    captures = []
    def hook(cpu, address, size, context):
        if address != 0x4b58a0:
            return
        obj = cpu.reg_read(UC_X86_REG_EAX)
        value = cpu.reg_read(UC_X86_REG_EDX)
        captures.append((obj, value))
        cpu.mem_write(obj + 0x180, struct.pack('<I', value))
        esp = cpu.reg_read(UC_X86_REG_ESP)
        cpu.reg_write(UC_X86_REG_EIP, struct.unpack('<I', cpu.mem_read(esp, 4))[0])
        cpu.reg_write(UC_X86_REG_ESP, esp + 4)
    cpu.hook_add(UC_HOOK_CODE, hook)
    rng = random.Random(0x44fa70)
    for case in range(4096):
        handles = [0x804000 + 512 * i for i in range(8)]
        ids = [rng.randrange(4) for _ in handles]
        query = rng.choice(ids)
        values = [rng.getrandbits(32) for _ in handles]
        players = [rng.getrandbits(32) for _ in range(4)]
        alternate_players = [rng.getrandbits(32) for _ in range(4)]
        cpu.mem_write(MASK, struct.pack('<8I', * handles))
        cpu.mem_write(0x54671c, struct.pack('<3I', 0, MASK, 8))
        for handle, identity, value in zip(handles, ids, values):
            cpu.mem_write(handle, struct.pack('<I', identity))
            cpu.mem_write(handle + 0x180, struct.pack('<I', value))
        player_handles = [0x808000 + 512 * i for i in range(4)]
        cpu.mem_write(0x540f88, struct.pack('<4I', * player_handles))
        for handle, value in zip(player_handles, players):
            cpu.mem_write(handle + 0x17c, struct.pack('<I', value))
        for handle, value in zip(player_handles, alternate_players):
            cpu.mem_write(handle + 0x178, struct.pack('<I', value))
        raw = bytearray(rng.randbytes(0x194))
        index = rng.choice([- 1, 0, 1, 7])
        handler = [0x44fa70, 0x44faa0, 0x44fc00, 0x44fc30][case % 4]
        state = Number(query, rng.getrandbits(32), rng.choice([0, 1, 2]), rng.randrange(32), rng.randrange(2), handler, index, rng.getrandbits(32))
        offsets = [('id', 4, 'I'), ('value', 0x180, 'I'), ('mode', 0x184, 'I'), ('width', 0x188, 'I'), ('show_zero', 0x190, 'I'), ('handler', 0x154, 'I'), ('refresh_index', 0x148, 'h'), ('refresh', 0x120, 'I')]
        for name, offset, fmt in offsets:
            struct.pack_into('<' + fmt, raw, offset, getattr(state, name))
        cpu.mem_write(BOARD, bytes(raw))
        refresh = (c.c_uint32 * 8)(* [rng.getrandbits(32) for _ in range(8)])
        cpu.mem_write(0x5bb714, bytes(refresh))
        @ callback
        def identity(handle, output, context):
            output[0] = ids[handles.index(handle)]
            return 1
        @ callback
        def value(handle, output, context):
            output[0] = values[handles.index(handle)]
            return 1
        storage = (c.c_uint32 * 8)(* handles)
        listing = ObjectList(storage, 8, 8)
        selected_players = alternate_players if handler == 0x44fc30 else players
        player_values = (c.c_uint32 * 4)(* selected_players)
        text = c.create_string_buffer(64)
        captures.clear()
        original.call(handler, eax=BOARD)
        assert native.vertrix_number_player_update(c.byref(state), c.byref(listing), identity, value, None, player_values, 4, refresh, 8, text, len(text))
        assert captures == [(BOARD, state.value)]
        for name, offset, fmt in offsets:
            struct.pack_into('<' + fmt, raw, offset, getattr(state, name))
        assert bytes(raw) == bytes(cpu.mem_read(BOARD, len(raw))), case
        assert bytes(refresh) == bytes(cpu.mem_read(0x5bb714, 32))
    report = {'status': 'passed', 'cases': 4096, 'scope': 'Original 0x44fa70/0x44faa0/0x44fc00/0x44fc30, actual list lookup and refresh routines. ' 'Numeric/font setter is hooked to capture value and write field180; ' 'font binding and full player runtime remain unverified.'}
    (a.build_dir / 'number-player-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
