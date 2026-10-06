"""Compare main-dispatch speed/tempo, global volume and volume slide."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD


class State(ctypes.Structure):
    _fields_ = [(name, ctypes.c_uint32) for name in ('speed', 'tempo', 'volume', 'memory')] + [('flags', ctypes.c_uint8)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'global-effects.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', str(source / 'mixer.c'), '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    function = native.vertrix_mixer_global_effect
    function.argtypes = [ctypes.c_uint8, ctypes.c_uint8, ctypes.c_int32, ctypes.POINTER(State)]
    original = Original(args.executable)
    rng = random.Random(0x40d880)
    cases = 30000
    for effect in (15, 16, 17):
        for index in range(cases):
            channel = bytearray(rng.randbytes(192))
            channel[3] = effect
            parameter = index % 256
            channel[4] = parameter
            tick = (0, 1, - 1, rng.randrange(- 2147483648, 2147483648))[(index // 256) % 4]
            speed, tempo, volume, memory = [rng.getrandbits(32) for _ in range(4)]
            if index % 3 == 0:
                volume = rng.randrange(65)
            flags = rng.randrange(256)
            state = State(speed, tempo, volume, memory, flags)
            globals_before = bytearray(rng.randbytes(64))
            globals_before[0] = flags
            struct.pack_into('<i', globals_before, 8, tick)
            struct.pack_into('<4I', globals_before, 28, speed, tempo, volume, memory)
            original.cpu.mem_write(BOARD, bytes(channel))
            original.cpu.mem_write(0x531b44, bytes(globals_before))
            original.call(0x40dc50, eax=BOARD)
            assert function(effect, parameter, tick, ctypes.byref(state))
            actual = bytearray(globals_before)
            actual[0] = state.flags
            struct.pack_into('<4I', actual, 28, state.speed, state.tempo, state.volume, state.memory)
            assert bytes(actual) == bytes(original.cpu.mem_read(0x531b44, 64)), (effect, index)
            assert bytes(channel) == bytes(original.cpu.mem_read(BOARD, 192)), (effect, index)
    before = bytes(state)
    assert not function(14, 0, 0, ctypes.byref(state)) and bytes(state) == before
    assert not function(15, 0, 0, None)
    report = {'status': 'passed', 'speed_tempo_cases': cases, 'global_volume_cases': cases, 'global_slide_cases': cases, 'scope': 'Complete original main effect dispatcher 0x40dc50 for effects 15/16/17; whole global-state and channel comparisons, all parameters, zero/later signed ticks, memory preservation, clamps, dirty flags and wrapping. Excludes consuming pending tempo/volume changes and sequencing.'}
    (build / 'mixer-global-effects-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
