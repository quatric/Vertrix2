""
    "Compare original tempo setter arithmetic and validation."
    "" import argparse,
    ctypes, json, random, struct,
    subprocess from pathlib import Path from original import Original

        def
        main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument("executable",
                                                                                  type = Path);
parser.add_argument("--build-dir", type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "tempo.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "mixer.c"), "-o", str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
native.vertrix_mixer_tempo.argtypes =
    [ ctypes.c_uint32, ctypes.c_uint32, ctypes.c_int, ctypes.POINTER(ctypes.c_uint32) ] original =
        Original(args.executable);rng=random.Random(0x40cd40)
    fixtures=[(bpm,rate,stereo) for bpm in range(32,256) for rate in (11025,22050,32000,44100,48000) for stereo in (0,1)]
    fixtures += [(rng.randrange(32,256),rng.randrange(2**32),rng.randrange(2)) for _ in range(20000)]
    for bpm,rate,stereo in fixtures:
        original.cpu.mem_write(0x52FC20,struct.pack("<I",rate));original.cpu.mem_write(0x52FC1D,bytes([stereo]))
        assert original.call(0x40CD40,eax=bpm)==0
        expected=struct.unpack("<I",original.cpu.mem_read(0x52FC24,4))[0]
        result=ctypes.c_uint32()
        assert native.vertrix_mixer_tempo(bpm,rate,stereo,ctypes.byref(result))
        assert result.value==expected
    for bpm in (0,31,256,0xffffffff):
        original.cpu.mem_write(0x52FC24,struct.pack("<I",123))
        assert original.call(0x40CD40,eax=bpm)==2
        assert struct.unpack("<I",original.cpu.mem_read(0x52FC24,4))[0]==123
        result=ctypes.c_uint32(123)
        assert not native.vertrix_mixer_tempo(bpm,48000,1,ctypes.byref(result)) and result.value==123
    assert not native.vertrix_mixer_tempo(125,48000,1,None)
    report={"status":"passed","tempo_cases":len(fixtures),"scope":"Complete original 0x40cd40 setter, all valid BPM values at five audio rates in mono/stereo, plus 20000 full-width rates preserving wrapped arithmetic. Original and native invalid-BPM preservation checked. Excludes sequencer effects and audio delivery."}
    (build/"mixer-tempo-verification.json").write_text(json.dumps(report,indent=2)+"\n");
print(json.dumps(report, indent = 2)) if __name__ == "__main__" : main()
