""
    "Compare main-dispatch panning slide and full-byte timed release."
    "" import argparse,
    ctypes, json, random, struct, subprocess from pathlib import Path from original import Original,
    BOARD,
    MASK from verify_mixer_volume_slide import State as Volume

    class Pan(ctypes.Structure)
    : _fields_ = [ ('pan', ctypes.c_uint32), ('memory', ctypes.c_uint8), ('flags', ctypes.c_uint8) ]

      def main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument('executable',
                                                                                  type = Path);
parser.add_argument('--build-dir', type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      'source';
library = build / 'pan-release.dylib' subprocess.run(
                      [
                          'cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC',
                          str(source / 'mixer.c'), '-o', str(library)
                      ],
                      check = True) native =
              ctypes.CDLL(str(library)) native.vertrix_mixer_pan_slide.argtypes =
                  [ ctypes.c_uint8, ctypes.c_int32,
                    ctypes.POINTER(Pan) ] native.vertrix_mixer_timed_release.argtypes =
                      [
                          ctypes.c_uint8, ctypes.c_int32, ctypes.c_int, ctypes.c_uint8,
                          ctypes.POINTER(ctypes.c_uint8), ctypes.POINTER(Volume)
                      ] original = Original(args.executable);
rng = random.Random(0x40d9b0); cases = 40000
    for effect in (25,20):
        for index in range(cases):
            data = bytearray(rng.randbytes(192)); parameter = index % 256
            tick = (0,parameter,-1,rng.randrange(-2147483648,2147483648))[(index // 256) % 4]
            data[3] = effect; data[4] = parameter
            present = index % 2; envelope = rng.randrange(256)
            struct.pack_into('<I',data,52,MASK if present else 0)
            if index % 3 == 0: struct.pack_into('<I',data,28,rng.randrange(256))
            original.cpu.mem_write(BOARD,bytes(data)); original.cpu.mem_write(MASK+188,bytes([envelope]))
            original.cpu.mem_write(0x531b4c,struct.pack('<i',tick)); original.call(0x40dc50,eax=BOARD)
            actual = bytearray(data)
            if effect == 25:
                state = Pan(struct.unpack_from('<I',data,28)[0],data[105],data[1])
                assert native.vertrix_mixer_pan_slide(parameter,tick,ctypes.byref(state))
                struct.pack_into('<I',actual,28,state.pan); actual[105] = state.memory; actual[1] = state.flags
            else:
                state = Volume(*struct.unpack_from('<II',data,16),data[104],data[1]); active = ctypes.c_uint8(data[0])
                assert native.vertrix_mixer_timed_release(parameter,tick,present,envelope,ctypes.byref(active),ctypes.byref(state))
                struct.pack_into('<II',actual,16,state.base,state.output); actual[0] = active.value; actual[104] = state.memory; actual[1] = state.flags
            assert bytes(actual) == bytes(original.cpu.mem_read(BOARD,192)),(effect,index)
    assert not native.vertrix_mixer_pan_slide(0,0,None)
    assert not native.vertrix_mixer_timed_release(0,1,0,0,None,ctypes.byref(state))
    report = {'status':'passed','pan_slide_cases':cases,'timed_release_cases':cases,
        'scope':'Complete original main dispatcher 0x40dc50 effects 25/20, whole channel comparison, parameter memory and signed pan clamps/wrapping, full-byte release timing, instrument/envelope branches. Excludes scheduling and remaining main effects.'}
    (build / 'mixer-pan-release-verification.json').write_text(json.dumps(report,indent=2) + '\n'); print(json.dumps(report,indent=2))
if __name__ == '__main__': main()
