"""Verify complete original trigger envelope reset, including preserved fields."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK

NAMES = ('vibrato_phase', 'tremolo_phase', 'fade_volume', 'fade_step',
         'volume_tick', 'volume_point', 'pan_tick', 'pan_point',
         'instrument_phase', 'instrument_amount', 'instrument_step')
OFFSETS = (64, 76, 120, 124, 128, 136, 144, 152, 160, 164, 168)
BYTES = (60, 112, 114, 115)
class State(ctypes.Structure):
    _fields_ = [(name, ctypes.c_uint32) for name in NAMES] + [
        (name, ctypes.c_uint8) for name in ('waveform', 'state_112', 'state_114', 'state_115')]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source =
    Path(__file__).resolve().parents[1] /
    'source' library = build / 'trigger-reset.dylib' subprocess.run(
                                   [
                                       'cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared',
                                       '-fPIC', str(source / 'mixer.c'), '-o', str(library)
                                   ],
                                   check = True) native =
                           ctypes.CDLL(str(library)) native.vertrix_mixer_trigger_reset.argtypes = [
                               ctypes.c_int, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint16,
                               ctypes.c_uint8, ctypes.c_uint8, ctypes.POINTER(State)
                           ] original = Original(args.executable);
rng = random.Random(0x40df20); cases = 40000
    for index in range(cases):
        data = bytearray(rng.randbytes(192)); instrument = bytearray(rng.randbytes(248))
        present = index % 2
        data[60] = (index // 2) % 256
        instrument[131] = 0 if index % 5 == 0 else rng.randrange(256)
        instrument[132] = 0 if index % 7 == 0 else rng.randrange(256)
        struct.pack_into('<I', data, 52, MASK if present else 0)
        state = State(*[struct.unpack_from('<I', data, offset)[0] for offset in OFFSETS],
                      *[data[offset] for offset in BYTES])
        original.cpu.mem_write(BOARD, bytes(data)); original.cpu.mem_write(MASK, bytes(instrument))
        original.call(0x40df20, eax=BOARD)
        expected = bytes(original.cpu.mem_read(BOARD, len(data)))
        assert native.vertrix_mixer_trigger_reset(present, instrument[188], instrument[244],
            struct.unpack_from('<H', instrument, 134)[0], instrument[131], instrument[132],
            ctypes.byref(state))
        actual = bytearray(data)
        for name, offset in zip(NAMES, OFFSETS):
            struct.pack_into('<I', actual, offset, getattr(state, name))
        for name, offset in zip(('waveform', 'state_112', 'state_114', 'state_115'), BYTES):
            actual[offset] = getattr(state, name)
        assert bytes(actual) == expected, index
    assert not native.vertrix_mixer_trigger_reset(1, 1, 1, 1, 1, 1, None)
    report = {'status': 'passed', 'trigger_reset_cases': cases,
        'scope': 'Complete original 0x40df20; whole 192-byte channel comparison, all waveform bytes, instrument presence, envelope flags, sweep/depth zero and nonzero. Excludes sample selection, envelope advancement and full note trigger.'}
    (build / 'mixer-trigger-reset-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))

if __name__ == '__main__':
    main()
