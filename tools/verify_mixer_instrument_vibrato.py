"""Compare complete original instrument vibrato paths."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EIP
from original import Original, BOARD, MASK, RETURN


class State(ctypes.Structure):
    _fields_ = [(name, ctypes.c_uint32) for name in ('phase', 'amount', 'step', 'period', 'output')] + [('active', ctypes.c_uint8), ('flags', ctypes.c_uint8)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'instrument-vibrato.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', str(source / 'mixer.c'), '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    function = native.vertrix_mixer_instrument_vibrato
    function.argtypes = [ctypes.c_int, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint8, ctypes.POINTER(State)]
    original = Original(args.executable)
    rng = random.Random(0x40e1db)
    def boundary(cpu, address, size, data):
        cpu.reg_write(UC_X86_REG_EIP, RETURN)
    hooks = [original.cpu.hook_add(UC_HOOK_CODE, boundary, begin=a, end=a) for a in (0x40e297, 0x40e566, 0x40e573)]
    cases = 60000
    try:
        for index in range(cases):
            data = bytearray(rng.randbytes(192))
            instrument = bytearray(rng.randbytes(248))
            present = index % 2
            waveform = (index // 2) % 256
            depth = 0 if index % 11 == 0 else rng.randrange(1, 256)
            rate = rng.randrange(256)
            instrument[130] = waveform
            instrument[132] = depth
            instrument[133] = rate
            struct.pack_into('<I', data, 52, MASK if present else 0)
            if index % 3 == 0:
                struct.pack_into('<III', data, 160, rng.getrandbits(32), rng.randrange(65536), rng.randrange(65536))
                struct.pack_into('<I', data, 40, rng.randrange(1, 0x7d00))
            if index % 7 == 0:
                struct.pack_into('<I', data, 168, 0)
            data[0] = (index // 512) % 256
            state = State(* struct.unpack_from('<III', data, 160), * struct.unpack_from('<II', data, 40), data[0], data[1])
            original.cpu.mem_write(BOARD, bytes(data))
            original.cpu.mem_write(MASK, bytes(instrument))
            original.call(0x40e1db, ebx=MASK if present else 0, ecx=BOARD)
            expected = bytes(original.cpu.mem_read(BOARD, 192))
            assert function(present, waveform, depth, rate, ctypes.byref(state))
            actual = bytearray(data)
            struct.pack_into('<III', actual, 160, state.phase, state.amount, state.step)
            struct.pack_into('<II', actual, 40, state.period, state.output)
            actual[0] = state.active
            actual[1] = state.flags
            assert bytes(actual) == expected, index
    finally:
        for hook in hooks:
            original.cpu.hook_del(hook)
    assert not function(1, 0, 1, 1, None)
    report = {'status': 'passed', 'instrument_vibrato_cases': cases, 'scope': 'Original 0x40e1db through each output epilogue; whole channel comparison, all waveform selectors, absent instruments, zero depth/step, signed wrapping and period clamps. Epilogue hooks only bypass register restores. Excludes sequencing and preceding envelope integration.'}
    (build / 'mixer-instrument-vibrato-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
