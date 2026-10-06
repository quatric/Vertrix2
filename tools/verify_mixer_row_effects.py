"""Compare original row transition following packed-event decode."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK


class State(ctypes.Structure):
    _fields_ = [('base', ctypes.c_uint32), ('output', ctypes.c_uint32)] + [(name, ctypes.c_uint8) for name in ('volume', 'effect', 'parameter', 'flags')]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'row-effects.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', str(source / 'mixer.c'), '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    function = native.vertrix_mixer_row_effects
    function.argtypes = [ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint8, ctypes.POINTER(State)]
    original = Original(args.executable)
    rng = random.Random(0x40e77f)
    cases = 40000
    for index in range(cases):
        data = bytearray(rng.randbytes(192))
        data[3] = (0, 4, 6, rng.randrange(256))[index % 4]
        data[4] = 0 if index % 3 == 0 else rng.randrange(1, 256)
        volume, effect, parameter = rng.randrange(256), (4, 6, rng.randrange(256))[index % 3], rng.randrange(256)
        state = State(* struct.unpack_from('<II', data, 36), data[2], data[3], data[4], data[1])
        original.cpu.mem_write(BOARD, bytes(data))
        original.cpu.mem_write(MASK, bytes((0x9f, 0, 0, volume, effect, parameter)))
        original.cpu.mem_write(0x530440, struct.pack('<I', MASK))
        original.call(0x40e770, eax=BOARD, stop=0x40e7ba)
        assert function(volume, effect, parameter, ctypes.byref(state))
        actual = bytearray(data)
        struct.pack_into('<II', actual, 36, state.base, state.output)
        actual[1: 5] = bytes((state.flags, state.volume, state.effect, state.parameter))
        assert bytes(actual) == bytes(original.cpu.mem_read(BOARD, 192)), index
        assert struct.unpack('<I', original.cpu.mem_read(0x530440, 4))[0] == MASK + 6
        assert not function(0, 0, 0, None)
    report = {'status': 'passed', 'row_effect_transition_cases': cases, 'scope': 'Original 0x40e770 through 0x40e7ba, including real packed-event decode and pitch restoration branches; whole channel comparison, vibrato/arpeggio transitions, zero/nonzero old parameters and arbitrary pitch/flags. Excludes later row instrument/note initialization and effect execution.'}
    (build / 'mixer-row-effects-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
