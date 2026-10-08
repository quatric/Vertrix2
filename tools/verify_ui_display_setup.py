"""Verify both alternating-display initialization fragments with original x86."""
import argparse
import json
import random
import struct
import ctypes as c
import subprocess
from pathlib import Path
from original import Original, BOARD
from unicorn.x86_const import UC_X86_REG_EBP, UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EIP


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'ui-layout.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', * [str(source / name) for name in ['ui_display_layout.c', 'ui_actor_storage.c', 'actor_storage.c', 'block_factory.c', 'call_glue.c', 'actor_fields.c', 'board_cells.c']], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_ui_display_position.argtypes = [c.c_size_t, c.c_uint, c.c_int16, c.c_int16, c.POINTER(c.c_int16), c.POINTER(c.c_int16)]
    native.vertrix_ui_actor_storage_construct.argtypes = [c.c_void_p, c.c_size_t, c.c_size_t, c.c_uint, c.c_int16, c.c_int16, c.c_uint32]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x46e101)
    cases = 0
    for iteration in range(256):
        pair = iteration % 12
        for side, start, stop in [('left', 0x46e101, 0x46e16e), ('right', 0x46e290, 0x46e302)]:
            raw = bytearray(rng.randbytes(0x160))
            expected = bytearray(raw)
            descriptor = rng.getrandbits(32)
            cpu.mem_write(0x803000, struct.pack('<I', descriptor))
            cpu.mem_write(0x546618, struct.pack('<6I', 0x803000, 1, 0, 0, 0, 0))
            cpu.mem_write(0x709000, bytes(0x100))
            frame = 0x709080
            cpu.mem_write(frame - 0x20, struct.pack('<I', 441 - pair * 40))
            cpu.mem_write(frame - 0x34, struct.pack('<I', pair))
            cpu.mem_write(BOARD, bytes(raw))
            cpu.reg_write(UC_X86_REG_EBP, frame)
            cpu.reg_write(UC_X86_REG_ESI, BOARD)
            cpu.reg_write(UC_X86_REG_EDI, pair * 4)
            offset_x, offset_y = rng.randrange(- 32768, 32768), rng.randrange(- 32768, 32768)
            cpu.mem_write(0x533d70, struct.pack('<h', offset_x))
            cpu.mem_write(0x533d74, struct.pack('<h', offset_y))
            position_start = 0x46e0c8 if side == 'left' else 0x46e257
#Adjacent fragments change emulation stop boundaries.Invalidate
#cached blocks so a prior fragment cannot bypass the new stop.
            cpu.ctl_remove_cache(0x46e0c8, 0x46e303)
            try:
                original.call(position_start, stop=0x46e101 if side == 'left' else 0x46e290)
            except Exception as error:
                raise RuntimeError((iteration, side, hex(cpu.reg_read(UC_X86_REG_EIP)), hex(cpu.reg_read(UC_X86_REG_ESI)))) from error
            positioned = bytes(cpu.mem_read(BOARD, len(raw)))
            x, y = c.c_int16(), c.c_int16()
            assert native.vertrix_ui_display_position(pair, side == 'right', offset_x, offset_y, c.byref(x), c.byref(y))
            expected_position = bytearray(raw)
            for offset, value in [(8, x.value), (0xa, y.value), (0xc, 0), (0xe, x.value), (0x16, y.value), (0x1e, 0)]:
                struct.pack_into('<h', expected_position, offset, value)
            for offset in [0xb0, 0xb8, 0xb4, 0x154]:
                struct.pack_into('<I', expected_position, offset, 0)
            assert positioned == bytes(expected_position), (iteration, side, 'position')
            cpu.mem_write(BOARD, bytes(raw))
            cpu.ctl_remove_cache(0x46e0c8, 0x46e303)
            original.call(start, stop=stop)
            for offset, value in [(4, 0x17 if side == 'left' else 0x18), (0xc0, 10), (0xe0, 441 - pair * 40), (0x154, 0x450a10), (0x134, 0), (0x7c, 0), (0x58, pair + 1), (0xb0, 0x546618), (0xcc, 0), (0xb8, 0), (0xb4, descriptor)]:
                struct.pack_into('<I', expected, offset, value)
            expected[0x93], expected[0x95] = 1, 4
            assert bytes(expected) == bytes(cpu.mem_read(BOARD, len(raw))), (iteration, side)
            if side == 'left':
                assert struct.unpack('<I', cpu.mem_read(frame - 0x44, 4))[0] == pair + 1
            else:
                assert struct.unpack('<I', cpu.mem_read(frame - 0x34, 4))[0] == pair + 1
                assert cpu.reg_read(UC_X86_REG_EDI) == (pair + 1) * 4
            cpu.mem_write(BOARD, bytes(raw))
            original.call(0x4abd70)
            cpu.mem_write(frame - 0x34, struct.pack('<I', pair))
            cpu.reg_write(UC_X86_REG_ESI, BOARD)
            cpu.reg_write(UC_X86_REG_EDI, pair * 4)
            cpu.ctl_remove_cache(0x46e0c8, 0x46e303)
            original.call(position_start, stop=stop)
            storage = c.create_string_buffer(bytes(raw), len(raw))
            assert native.vertrix_ui_actor_storage_construct(storage, len(raw), pair, side == 'right', offset_x, offset_y, descriptor)
            assert storage.raw == bytes(cpu.mem_read(BOARD, len(raw))), (iteration, side, 'creation')
            cases += 1
    x, y = c.c_int16(123), c.c_int16(456)
    for pair, side in [(12, 0), (0, 2)]:
        assert not native.vertrix_ui_display_position(pair, side, 0, 0, c.byref(x), c.byref(y))
        assert (x.value, y.value) == (123, 456)
    prior = storage.raw
    for size, pair, side in [(0x15b, 0, 0), (0x160, 12, 0), (0x160, 0, 2)]:
        assert not native.vertrix_ui_actor_storage_construct(storage, size, pair, side, 0, 0, 0)
        assert storage.raw == prior
    report = {'status': 'passed', 'cases': cases, 'scope': 'Both complete post-position initialization fragments46e101..46e16e ' 'and46e290..46e302 execute without hooks. Whole object bytes match ' 'IDs, thresholds, periods, phase/source, flags, handler and real resource ' 'attachment/descriptor binding. Primary/secondary counters are preserved; ' 'animation counter resets. Both preceding coordinate setup fragments and ' 'actual4adf20 position setter also execute without hooks. Native layout matches ' 'original coordinates including wrapping; whole position-initialized object ' 'matches. Native full UI storage creation additionally matches actual4abd70 ' 'followed by position and setup, including untouched bytes. Allocation and ' 'list insertion remain external; this is not full application execution.'}
    args.output.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
