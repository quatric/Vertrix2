"""Compare main effect tremor and extra-fine pitch-slide paths."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD


class Tremor(ctypes.Structure):
    _fields_ = [('base', ctypes.c_uint32), ('output', ctypes.c_uint32)] + [(name, ctypes.c_uint8) for name in ('memory', 'on', 'remaining', 'flags')]


class Slide(ctypes.Structure):
    _fields_ = [('base', ctypes.c_uint32), ('output', ctypes.c_uint32)] + [(name, ctypes.c_uint8) for name in ('decrease', 'increase', 'flags')]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'tremor-extra-fine.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', str(source / 'mixer.c'), '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_tremor.argtypes = [ctypes.c_uint8, ctypes.c_int32, ctypes.POINTER(Tremor)]
    native.vertrix_mixer_extra_fine_slide.argtypes = [ctypes.c_uint8, ctypes.c_int32, ctypes.POINTER(Slide)]
    original = Original(args.executable)
    rng = random.Random(0x40db00)
    cases = 40000
    for effect in (29, 33):
        for index in range(cases):
            data = bytearray(rng.randbytes(192))
            parameter = index % 256
            data[3] = effect
            data[4] = parameter
            tick = (0, 1, - 1, rng.randrange(- 2147483648, 2147483648))[(index // 256) % 4]
            data[115] = (0, 1, 255, rng.randrange(256))[index % 4]
            if index % 3 == 0:
                struct.pack_into('<II', data, 16, rng.randrange(65), rng.randrange(65))
                struct.pack_into('<II', data, 36, rng.randrange(1, 0x7d00), rng.randrange(1, 0x7d00))
            original.cpu.mem_write(BOARD, bytes(data))
            original.cpu.mem_write(0x531b4c, struct.pack('<i', tick))
            original.call(0x40dc50, eax=BOARD)
            actual = bytearray(data)
            if effect == 29:
                state = Tremor(* struct.unpack_from('<II', data, 16), data[113], data[114], data[115], data[1])
                assert native.vertrix_mixer_tremor(parameter, tick, ctypes.byref(state))
                struct.pack_into('<II', actual, 16, state.base, state.output)
                actual[113: 116] = bytes((state.memory, state.on, state.remaining))
                actual[1] = state.flags
            else:
                state = Slide(* struct.unpack_from('<II', data, 36), data[108], data[109], data[1])
                assert native.vertrix_mixer_extra_fine_slide(parameter, tick, ctypes.byref(state))
                struct.pack_into('<II', actual, 36, state.base, state.output)
                actual[108: 110] = bytes((state.decrease, state.increase))
                actual[1] = state.flags
            assert bytes(actual) == bytes(original.cpu.mem_read(BOARD, 192)), (effect, index)
    assert not native.vertrix_mixer_tremor(0, 0, None)
    assert not native.vertrix_mixer_extra_fine_slide(0, 0, None)
    report = {'status': 'passed', 'tremor_cases': cases, 'extra_fine_slide_cases': cases, 'scope': 'Complete original main dispatcher 0x40dc50 effects 29/33, whole channel comparisons, every parameter byte, signed first/later ticks, tremor counter wrapping and arbitrary gate bytes, pitch memory and signed clamps. Excludes remaining effects and scheduling.'}
    (build / 'mixer-tremor-extra-fine-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
