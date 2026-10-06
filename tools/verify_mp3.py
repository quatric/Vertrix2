""
    "Execute VF MP3 decoding with a host build of devkitPro libmad source."
    "" import argparse import ctypes import hashlib import json import shutil import subprocess from
        pathlib import Path

    class Audio(ctypes.Structure)
    : _fields_ =
          [
              ("samples", ctypes.c_void_p), ("allocation", ctypes.c_void_p),
              ("rate", ctypes.c_uint32), ("channels", ctypes.c_uint32), ("frames", ctypes.c_uint32),
              ("size", ctypes.c_uint32), ("padded", ctypes.c_uint32)
          ]

      def main()
    : parser = argparse.ArgumentParser(description = __doc__) parser
                   .add_argument("archive",
                                 type = Path) parser.add_argument("assets", type = Path) parser
                   .add_argument("decoder_source", type = Path,
                                 help = "devkitPro libogc checkout") parser
                   .add_argument("--build-dir", type = Path, required = True) parser.add_argument(
                       "--mad-header", type = Path,
                       default = Path("/opt/devkitpro/libogc/include/mad.h")) args =
          parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) decoder = build / "libmad";
shutil.copytree(args.decoder_source / "libmad", decoder, dirs_exist_ok = True) global_header =
    decoder /
    "global.h" global_header
        .write_text(global_header.read_text().replace("# define FPM_PPC",
                                                      "# define FPM_64BIT"))(build / "mad.h")
        .write_text(args.mad_header.read_text().replace("# define FPM_PPC",
                                                        "# define FPM_64BIT"))(build / "gctypes.h")
        .write_text("#include <stdint.h>\ntypedef int8_t s8; typedef uint8_t u8; typedef int16_t "
                    "s16; typedef uint16_t u16; typedef int32_t s32; typedef uint32_t u32; typedef "
                    "int64_t s64; typedef uint64_t u64;\n")(build / "gccore.h")
        .write_text("#include <stdint.h>\nvoid DCFlushRange(void *,uint32_t);\n")(build / "cache.c")
        .write_text(
            "#include <stdint.h>\nvoid DCFlushRange(void *p,uint32_t n) {(void)p; (void)n;}\n")
            source = Path(__file__).resolve().parents[1] / "source";library=build/"mp3.dylib"
    decoder_names=("bit","fixed","frame","huffman","layer12","layer3","stream","synth","timer")
    command=["cc","-shared","-fPIC","-O2","-fwrapv","-Wno-gnu-designator","-DHAVE_CONFIG_H",
             "-I"+str(build),"-I"+str(decoder),str(source/"wii_mp3.c"),str(source/"vf.c"),str(build/"cache.c"),
             *[str(decoder/(name+".c")) for name in decoder_names],"-o",str(library)]
    with (build/"compile.log").open("w") as log:
        subprocess.run(command,stdout=log,stderr=log,check=True)
    native=ctypes.CDLL(str(library));
native.vertrix_vf_open.argtypes = [ctypes.c_char_p] native.vertrix_vf_open.restype =
    ctypes.c_void_p;
native.vertrix_vf_close.argtypes = [ctypes.c_void_p] native.vertrix_wii_mp3_load.argtypes =
    [ ctypes.c_void_p, ctypes.c_char_p,
      ctypes.POINTER(Audio) ] native.vertrix_wii_mp3_free.argtypes = [ctypes.POINTER(Audio)] vf =
        native.vertrix_vf_open(str(args.archive.resolve()).encode());
assert vf rows = []
try:
        for
            path in sorted(args.assets.rglob("*.mp3")) : name = str(path.relative_to(args.assets));
audio = Audio() assert native.vertrix_wii_mp3_load(vf, name.encode(), ctypes.byref(audio)),
    name assert not audio.samples % 32 and
        audio.size == audio.frames * audio.channels * 2 assert audio.padded ==
            (audio.size + 31) // 32*32
            pcm = ctypes.string_at(audio.samples,
                                   audio.size) assert ctypes.string_at(audio.samples + audio.size,
                                                                       audio.padded - audio.size) ==
                  bytes(audio.padded - audio.size) rows.append({
                      "name" : name,
                      "sample_rate" : audio.rate,
                      "channels" : audio.channels,
                      "sample_frames" : audio.frames,
                      "byte_count" : audio.size,
                      "pcm_sha256" : hashlib.sha256(pcm).hexdigest()
                  }) saved = bytes(audio);
assert not native.vertrix_wii_mp3_load(vf, name.encode(), ctypes.byref(audio))
        assert bytes(audio) == saved native.vertrix_wii_mp3_free(ctypes.byref(audio));assert bytes(audio)==bytes(Audio())
            native.vertrix_wii_mp3_free(ctypes.byref(audio))
    finally:
        native.vertrix_vf_close(vf)
    assert len(rows)==63
    revision=subprocess.run(["git","-C",str(args.decoder_source),"rev-parse","HEAD"],capture_output=True,text=True,check=True).stdout.strip()
    report={"status":"passed","files":len(rows),"frames":sum(row["sample_frames"] for row in rows),"decoder_revision":revision,"rows":rows,
            "scope":"Actual decoding with devkitPro libmad source using FPM_64BIT host arithmetic and cache stub. No original-codec fidelity or Wii hardware validation."}
    (build/"mp3-verification.json").write_text(json.dumps(report,indent=2)+"\n")
    print(f"Decoded {len(rows)} original MP3 files ({report['frames']} sample frames)")

if __name__=="__main__":main()
