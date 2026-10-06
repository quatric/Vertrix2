""
    "Compare recovered tracker sample delta decoding with original instructions."
    "" import argparse import ctypes import json import random import struct import
        subprocess from pathlib import Path from original import Original,
    BOARD,
    BLOCKS

        def
        main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument("executable",
                                                                                  type = Path);
parser.add_argument("--build-dir", type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "delta.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "audio.c"), str(source / "vf.c"), "-o", str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
native.vertrix_audio_delta_decode.argtypes =
    [ ctypes.c_void_p, ctypes.c_size_t, ctypes.c_int ] original = Original(args.executable);
rng = random.Random(0x411280);cases=20000
    for index in range(cases):
        count=rng.randrange(257);
flags = rng.randrange(256);
data = rng.randbytes(count) + bytes([0xA5]) * 4 original.cpu.mem_write(BOARD, bytes(32));
original.cpu.mem_write(BOARD,
                       struct.pack("<I", BLOCKS)) original.cpu.mem_write(BOARD + 8,
                                                                         struct.pack("<I", count));
original.cpu.mem_write(BOARD + 0x16, bytes([flags])) original.cpu.mem_write(BLOCKS, data);
original.call(0x411280)
    expected = bytes(original.cpu.mem_read(BLOCKS, len(data))) samples =
    (ctypes.c_uint8 * len(data))
        .from_buffer_copy(data) assert native.vertrix_audio_delta_decode(samples, count,
                                                                         flags & 1) assert
    bytes(samples) == expected,
    (count, flags)assert native.vertrix_audio_delta_decode(None, 0, 1) assert
    not native.vertrix_audio_delta_decode(None, 1, 0) report = {
        "status" : "passed",
        "cases" : cases,
        "scope" : "Original 0x411280 full delta decoder, 8/16-bit modes, odd counts, zero counts, "
                  "upper flags and trailing storage guards. Does not recover XM playback."
    }(build / "audio-delta-verification.json")
                                                                   .write_text(
                                                                       json.dumps(report,
                                                                                  indent = 2) +
                                                                       "\n");
print(json.dumps(report, indent = 2))

        if __name__
    == "__main__" : main()
