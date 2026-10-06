""
    "Verify original released-note fade and envelope output scaling."
    "" import argparse,
    ctypes, json, random, struct, subprocess from pathlib import Path from original import Original,
    BOARD,
    MASK

    class Fade(ctypes.Structure)
    : _fields_ =
          [ ('volume', ctypes.c_uint32), ('step', ctypes.c_uint32), ('flags', ctypes.c_uint8) ]

      def main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument('executable',
                                                                                  type = Path);
parser.add_argument('--build-dir', type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      'source';
library =
    build / 'envelope-output.dylib' subprocess.run(
                [
                    'cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC',
                    str(source / 'mixer.c'), '-o', str(library)
                ],
                check = True) native = ctypes.CDLL(str(library))
                                           native.vertrix_mixer_fade_step.argtypes =
        [ ctypes.c_int, ctypes.c_uint8,
          ctypes.POINTER(Fade) ] native.vertrix_mixer_envelope_volume.argtypes =
            [ctypes.c_uint32] * 3 +
            [ ctypes.c_int, ctypes.POINTER(ctypes.c_uint32),
              ctypes.POINTER(ctypes.c_uint8) ] native.vertrix_mixer_envelope_pan.argtypes =
                [ctypes.c_uint32] * 2 + [
                    ctypes.c_int, ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_uint8)
                ] original = Original(args.executable);
rng = random.Random(0x40e0f2); cases = 25000
    for mode in range(5):
        for index in range(cases):
            data = bytearray(rng.randbytes(192));
flags = ctypes.c_uint8(data[1]) output = ctypes.c_uint32(rng.getrandbits(32)) base =
    rng.getrandbits(32) if index % 2 else rng.randrange(256) envelope =
        rng.getrandbits(32) if index % 2 else rng.randrange(0x4001) fade =
            rng.getrandbits(32) if index % 2 else rng.randrange(0x8000) if index % 7 == 0 : fade =
                0x7fff actual = bytearray(data) if mode == 0 : present = index % 2; active = (index // 2) % 256
                data[0] = active; struct.pack_into('<I', data, 52, MASK if present else 0)
                step = rng.getrandbits(32)
                struct.pack_into('<II', data, 120, fade, step); actual = bytearray(data)
                state = Fade(fade, step, flags.value)
                original.cpu.mem_write(BOARD, bytes(data))
                original.call(0x40e038, eax=BOARD, ecx=BOARD, stop=0x40e05b)
                assert native.vertrix_mixer_fade_step(present, active, ctypes.byref(state))
                struct.pack_into('<II', actual, 120, state.volume, state.step); actual[1] = state.flags
            elif mode in (1, 2):
                enabled = mode == 1
                struct.pack_into('<II', data, 20, base, output.value)
                struct.pack_into('<I', data, 120, fade); struct.pack_into('<I', data, 132, envelope)
                actual = bytearray(data); original.cpu.mem_write(BOARD, bytes(data))
                original.call(0x40e0f2 if enabled else 0x40e3c3, ecx=BOARD, stop=0x40e10d)
                assert native.vertrix_mixer_envelope_volume(base, fade, envelope, enabled, ctypes.byref(output), ctypes.byref(flags))
                struct.pack_into('<I', actual, 24, output.value); actual[1] = flags.value
            else:
                enabled = mode == 3
                struct.pack_into('<II', data, 28, base, output.value); struct.pack_into('<I', data, 148, envelope)
                actual = bytearray(data); original.cpu.mem_write(BOARD, bytes(data))
                original.call(0x40e1a4 if enabled else 0x40e4ff, ecx=BOARD, stop=0x40e1db)
                assert native.vertrix_mixer_envelope_pan(base, envelope, enabled, ctypes.byref(output), ctypes.byref(flags))
                struct.pack_into('<I', actual, 32, output.value); actual[1] = flags.value
            assert bytes(actual) == bytes(original.cpu.mem_read(BOARD, 192)), (mode, index)
    before = output.value, flags.value
    assert not native.vertrix_mixer_envelope_volume(1, 1, 1, 1, None, ctypes.byref(flags))
    assert not native.vertrix_mixer_envelope_pan(1, 1, 1, ctypes.byref(output), None)
    assert (output.value, flags.value) == before
    assert not native.vertrix_mixer_fade_step(1, 0, None)
    report = {'status':'passed', 'fade_cases':cases, 'volume_cases':cases * 2, 'pan_cases':cases * 2,
        'scope':'Original fade 0x40e038..0x40e05b, enabled/disabled output volume and pan branches, whole channel comparisons with realistic and full-width wrapping inputs. Excludes instrument vibrato, envelope enable gating and full sequencing.'}
    (build / 'mixer-envelope-output-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__': main()
