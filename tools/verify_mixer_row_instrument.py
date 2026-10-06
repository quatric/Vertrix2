"""Verify original row instrument selection and sample defaults."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EIP
from original import Original, BOARD, MASK, BLOCKS, RETURN


class Instrument(ctypes.Structure):
    _fields_ = [('selected', ctypes.c_uint32), ('number', ctypes.c_uint8)]


class Defaults(ctypes.Structure):
    _fields_ = [(name, ctypes.c_uint32) for name in ('base', 'output', 'pan')] + [('flags', ctypes.c_uint8)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'row-instrument.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', str(source / 'mixer.c'), '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_row_instrument.argtypes = [ctypes.c_uint8, ctypes.c_uint16, ctypes.POINTER(Instrument)]
    native.vertrix_mixer_row_defaults.argtypes = [ctypes.c_uint8, ctypes.c_int, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint8, ctypes.POINTER(Defaults)]
    original = Original(args.executable)
    rng = random.Random(0x40e7ba)
    cases = 40000
    for index in range(cases):
        data = bytearray(rng.randbytes(192))
        incoming = index % 256
        count = rng.randrange(256) if index % 2 else rng.randrange(65536)
        old = rng.randrange(256)
        struct.pack_into('<I', data, 52, 0 if old == 0 else BLOCKS + (old - 1) * 252)
        state = Instrument(old, data[5])
        original.cpu.mem_write(BOARD, bytes(data))
        original.cpu.mem_write(0x531b81, bytes([incoming]))
        original.cpu.mem_write(0x53043c, struct.pack('<I', MASK))
        original.cpu.mem_write(MASK + 42, struct.pack('<H', count))
        original.cpu.mem_write(MASK + 340, struct.pack('<I', BLOCKS))
        original.call(0x40e7ba, edx=BOARD, stop=0x40e7f8)
        assert native.vertrix_mixer_row_instrument(incoming, count, ctypes.byref(state))
        actual = bytearray(data)
        actual[5] = state.number
        struct.pack_into('<I', actual, 52, 0 if state.selected == 0 else BLOCKS + (state.selected - 1) * 252)
        assert bytes(actual) == bytes(original.cpu.mem_read(BOARD, 192)), index
    def boundary(cpu, address, size, data):
        cpu.reg_write(UC_X86_REG_EIP, RETURN)
    hooks = [original.cpu.hook_add(UC_HOOK_CODE, boundary, begin=a, end=a) for a in (0x40e857, 0x40e899)]
    try:
        for index in range(cases):
            data = bytearray(rng.randbytes(192))
            incoming = index % 256
            present = (index // 256) % 2
            volume, pan, module = rng.randrange(256), rng.randrange(256), rng.randrange(256)
            struct.pack_into('<I', data, 56, MASK if present else 0)
            state = Defaults(* struct.unpack_from('<II', data, 16), struct.unpack_from('<I', data, 28)[0], data[1])
            original.cpu.mem_write(BOARD, bytes(data))
            original.cpu.mem_write(0x531b81, bytes([incoming]))
            original.cpu.mem_write(0x531b47, bytes([module]))
            original.cpu.mem_write(MASK + 32, bytes([volume, pan]))
            original.call(0x40e82c, edx=BOARD)
            assert native.vertrix_mixer_row_defaults(incoming, present, volume, pan, module, ctypes.byref(state))
            actual = bytearray(data)
            actual[1] = state.flags
            struct.pack_into('<II', actual, 16, state.base, state.output)
            struct.pack_into('<I', actual, 28, state.pan)
            assert bytes(actual) == bytes(original.cpu.mem_read(BOARD, 192)), index
    finally:
        for hook in hooks:
            original.cpu.hook_del(hook)
    assert not native.vertrix_mixer_row_instrument(1, 1, None)
    assert not native.vertrix_mixer_row_defaults(1, 1, 64, 128, 0, None)
    report = {'status': 'passed', 'instrument_selection_cases': cases, 'sample_default_cases': cases, 'scope': 'Original 0x40e7ba..0x40e7f8 selection and 0x40e82c..0x40e89d defaults. Whole channel comparisons with one-based handles translated to original instrument addresses; note/sample initialization remains separate. Defaults hooks only bypass final register restores.'}
    (build / 'mixer-row-instrument-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
