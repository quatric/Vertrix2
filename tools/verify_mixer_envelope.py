"""Compare both original enabled-envelope advancement paths."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK

class Point(ctypes.Structure):
    _fields_ = [('tick', ctypes.c_uint16), ('value', ctypes.c_uint16)]
class State(ctypes.Structure):
    _fields_ = [(name, ctypes.c_uint32) for name in ('tick', 'value', 'point', 'slope')]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path);
parser.add_argument('--build-dir', type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      'source';
library = build / 'envelope.dylib' subprocess.run(
                      [
                          'cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC',
                          str(source / 'mixer.c'), '-o', str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
function = native.vertrix_mixer_envelope_step function.argtypes =
    [ ctypes.POINTER(Point), ctypes.c_size_t ] + [ctypes.c_uint8] * 6 +
    [ctypes.POINTER(State)] original = Original(args.executable);
rng = random.Random(0x40e070); cases = 40000
    for pan in (0, 1):
        start, stop = (0x40e122, 0x40e1a4) if pan else (0x40e070, 0x40e0f2)
        state_offset = 144 if pan else 128; points_offset = 192 if pan else 136
        metadata_offset = 240 if pan else 184
        for index in range(cases):
            data = bytearray(rng.randbytes(192)); instrument = bytearray(rng.randbytes(248))
            points = (Point * 12)(*[Point(rng.randrange(65536), rng.randrange(65536)) for _ in range(12)])
            point = index % 12;
count = index % 13;
flags = index % 256 sustain = point if index % 3 == 0 else rng.randrange(12) loop_end =
                                  point if index % 5 == 0 else rng.randrange(12);
loop_start = rng.randrange(12) active = index % 2;
data[0] = active tick = (0xffffffff, points[point].tick - 1, points[point].tick,
                         rng.getrandbits(32))[index % 4] & 0xffffffff state =
    State(tick, rng.getrandbits(32), point, rng.getrandbits(32)) struct.pack_into(
        '<4I', data, state_offset, state.tick, state.value, state.point, state.slope) instrument
    [points_offset:points_offset + 48] = bytes(points)
instrument [metadata_offset:metadata_offset + 5] =
    bytes((count, sustain, loop_start, loop_end, flags)) original.cpu.mem_write(BOARD, bytes(data));
original.cpu.mem_write(MASK, bytes(instrument)) original.call(start, eax = BOARD, ebx = MASK,
                                                              ecx = BOARD, stop = stop) expected =
    bytes(original.cpu.mem_read(BOARD, 192)) assert
    function(points, 12, count, flags, sustain, loop_start, loop_end, active,
             ctypes.byref(state)) actual = bytearray(data);
struct.pack_into('<4I', actual, state_offset, state.tick, state.value, state.point,
                 state.slope) assert bytes(actual) == expected,
    (pan, index)state = State(0, 123, 0, 45);
before =
    bytes(state) assert not function(None, 12, 12, 0, 0, 0, 0, 1, ctypes.byref(state))
        assert not function(points, 0, 12, 0, 0, 0, 0, 1, ctypes.byref(state)) assert
        bytes(state) == before points[0].tick =
        0 assert not function(points, 1, 12, 0, 0, 0, 0, 1, ctypes.byref(state)) and
        bytes(state) == before report = {
            'status' : 'passed',
            'volume_envelope_cases' : cases,
            'pan_envelope_cases' : cases,
            'scope' :
                'Original enabled volume 0x40e070..0x40e0f2 and pan 0x40e122..0x40e1a4 paths; whole channel comparisons with random point times/values, counter wrapping, sustain/loop and signed slope truncation. Excludes enable gating, final volume/pan scaling, fade and instrument vibrato.'
        }(build / 'mixer-envelope-verification.json')
                                            .write_text(json.dumps(report, indent = 2) + '\n')
                                                print(json.dumps(report, indent = 2)) if __name__
                                        == '__main__' : main()
