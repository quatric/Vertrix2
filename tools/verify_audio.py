""
    "Compare direct VF PCM loading with independently decoded original WAVs."
    "" import
        argparse import ctypes import json import subprocess import wave from pathlib import Path

    class Pcm8(ctypes.Structure)
    : _fields_ =
          [
              ("sample_rate", ctypes.c_uint32), ("sample_count", ctypes.c_uint32),
              ("samples", ctypes.c_void_p)
          ]

      def main()
    : parser = argparse.ArgumentParser(
                           description = __doc__) parser.add_argument("archive", type = Path) parser
                   .add_argument("extracted_assets", type = Path) parser.add_argument(
                       "--build-dir", type = Path, required = True) args =
          parser.parse_args() build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source =
    Path(__file__).resolve().parents[1] / "source" library =
        build / "audio.dylib" subprocess.run(
                    [
                        "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                        str(source / "audio.c"), str(source / "vf.c"), "-o", str(library)
                    ],
                    check = True) native =
            ctypes.CDLL(str(library)) native.vertrix_vf_open.argtypes = [ctypes.c_char_p];
native.vertrix_vf_open.restype = ctypes.c_void_p native.vertrix_vf_close.argtypes =
    [ctypes.c_void_p] native.vertrix_audio_pcm8.argtypes =
        [ ctypes.c_void_p, ctypes.c_char_p,
          ctypes.POINTER(Pcm8) ] native.vertrix_pcm8_free.argtypes =
            [ctypes.POINTER(Pcm8)] archive =
                native.vertrix_vf_open(str(args.archive.resolve()).encode());
assert archive files = samples = unsupported = 0;
rates = set()
try:
        for
            path in args.extracted_assets.rglob("*")
                : if not path.is_file() or
                path.suffix.lower() not in(".wav", ".mp3")
                : continue name = str(path.relative_to(args.extracted_assets)).encode() output =
                Pcm8() if path.suffix.lower() == ".mp3"
                : assert not native
                      .vertrix_audio_pcm8(archive, name, ctypes.byref(output)) assert
                  not output.samples and not output.sample_rate and not output.sample_count
                  unsupported += 1;
continue with wave.open(str(path)) as wav : assert wav.getnchannels() == 1 and wav.getsampwidth() ==
                                                                                   1 rate =
    wav.getframerate();
data = wav.readframes(wav.getnframes())
           assert native.vertrix_audio_pcm8(archive, name, ctypes.byref(output)),
    name assert output.sample_rate == rate and output.sample_count ==
        len(data) assert ctypes.string_at(output.samples, output.sample_count) == data saved =
        bytes(output) assert
        not native.vertrix_audio_pcm8(archive, name, ctypes.byref(output)) assert
        bytes(output) == saved native.vertrix_pcm8_free(ctypes.byref(output));
assert bytes(output) == bytes(Pcm8()) native.vertrix_pcm8_free(ctypes.byref(output)) files += 1;
samples += len(data);
rates.add(rate) output = Pcm8() assert not native.vertrix_audio_pcm8(archive, b "missing.wav",
                                                                     ctypes.byref(output)) assert
                         bytes(output) ==
                         bytes(Pcm8()) finally : native.vertrix_vf_close(archive) assert files ==
                         13 and unsupported ==
                         63 report = {
    "status" : "passed",
    "wav_files" : files,
    "samples" : samples,
    "sample_rates" : sorted(rates),
    "unsupported_mp3_files_rejected" : unsupported,
    "scope" : "VF-backed original PCM samples compared with Python wave decoding. No playback, "
              "mixing, resampling or MP3 decoding."
}(build / "audio-verification.json")
                                         .write_text(json.dumps(report, indent = 2) + "\n")
                                             print(json.dumps(report, indent = 2))

                                                 if __name__
                                     == "__main__" : main()
