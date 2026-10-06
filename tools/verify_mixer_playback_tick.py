"""Compare full original per-tick instrument playback update across sequences."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK
from verify_mixer_envelope import Point, State as EnvelopeState
from verify_mixer_instrument_vibrato import State as Vibrato

class Envelope(ctypes.Structure):
    _fields_ = [('points', ctypes.POINTER(Point)), ('storage', ctypes.c_size_t)] + [
        (name, ctypes.c_uint8) for name in ('count', 'flags', 'sustain', 'start', 'end')]
class Instrument(ctypes.Structure):
    _fields_ = [('volume', Envelope), ('pan', Envelope)] + [
        (name, ctypes.c_uint8) for name in ('waveform', 'depth', 'rate')]
class State(ctypes.Structure):
    _fields_ = [(name, ctypes.c_uint32) for name in ('base_volume', 'output_volume', 'base_pan',
        'output_pan', 'fade_volume', 'fade_step')] + [('volume', EnvelopeState), ('pan', EnvelopeState), ('vibrato', Vibrato)]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path);
parser.add_argument('--build-dir', type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      'source';
library = build / 'playback-tick.dylib' subprocess.run(
                      [
                          'cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC',
                          str(source / 'mixer.c'), '-o', str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
function = native.vertrix_mixer_playback_tick function.argtypes =
    [ ctypes.POINTER(Instrument), ctypes.POINTER(State) ] original = Original(args.executable);
rng = random.Random(0x40e030);
runs = 12000; ticks = 4
    for index in range(runs):
        data = bytearray(rng.randbytes(192));
instrument = bytearray(rng.randbytes(248)) present = index % 2; data[0] = (index // 2) % 256
        struct.pack_into('<I', data, 52, MASK if present else 0)
        arrays = []; envelopes = []
        for point_offset, meta_offset, state_offset in ((136,184,128), (192,240,144)):
            points = (Point * 12)(*[Point(rng.randrange(65536), rng.randrange(65536)) for _ in range(12)])
            arrays.append(points); instrument[point_offset:point_offset + 48] = bytes(points)
            count, flags, sustain, start, end = rng.randrange(13), rng.randrange(256), rng.randrange(12), rng.randrange(12), rng.randrange(12)
            instrument[meta_offset:meta_offset + 5] = bytes((count, sustain, start, end, flags))
            envelopes.append(Envelope(points, 12, count, flags, sustain, start, end))
            point = rng.randrange(12)
            tick = (0xffffffff, points[point].tick - 1, rng.getrandbits(32))[index % 3] & 0xffffffff
            struct.pack_into('<4I', data, state_offset, tick, rng.getrandbits(32), point, rng.getrandbits(32))
        instrument[132] = 0 if index % 5 == 0 else rng.randrange(256)
        context = Instrument(*envelopes, instrument[130], instrument[132], instrument[133])
        if index % 3 == 0:
            struct.pack_into('<4I', data, 20, rng.randrange(65), 0, rng.randrange(256), 0)
            struct.pack_into('<II', data, 120, 0x7fff, rng.randrange(65536))
        state = State(*struct.unpack_from('<4I', data, 20), *struct.unpack_from('<II', data, 120),
            EnvelopeState(*struct.unpack_from('<4I', data, 128)), EnvelopeState(*struct.unpack_from('<4I', data, 144)),
            Vibrato(*struct.unpack_from('<III', data, 160), *struct.unpack_from('<II', data, 40), data[0], data[1]))
        original.cpu.mem_write(BOARD, bytes(data)); original.cpu.mem_write(MASK, bytes(instrument))
        for tick_index in range(ticks):
            original.call(0x40e030, eax=BOARD)
            expected = bytes(original.cpu.mem_read(BOARD, 192))
            assert function(ctypes.byref(context) if present else None, ctypes.byref(state))
            actual = bytearray(data)
            struct.pack_into('<4I', actual, 20, state.base_volume, state.output_volume, state.base_pan, state.output_pan)
            struct.pack_into('<II', actual, 120, state.fade_volume, state.fade_step)
            for offset, env in ((128,state.volume), (144,state.pan)):
                struct.pack_into('<4I', actual, offset, env.tick, env.value, env.point, env.slope)
            vib = state.vibrato; struct.pack_into('<III', actual, 160, vib.phase, vib.amount, vib.step)
            struct.pack_into('<II', actual, 40, vib.period, vib.output); actual[0] = vib.active; actual[1] = vib.flags
            assert bytes(actual) == expected, (index, tick_index)
            data = actual
    context.pan.flags = 1; context.pan.points = None
    before = bytes(state)
    assert not function(ctypes.byref(context), ctypes.byref(state)) and bytes(state) == before
    assert not function(None, None)
    report = {'status':'passed', 'sequences':runs, 'ticks_per_sequence':ticks, 'playback_tick_cases':runs * ticks,
        'scope':'Complete original 0x40e030, whole 192-byte channels across consecutive ticks, absent instruments, both envelope gates, release fade, volume/pan scaling and instrument vibrato. Native invalid storage rejects atomically. Excludes row/tick scheduling and audio delivery.'}
    (build / 'mixer-playback-tick-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__': main()
