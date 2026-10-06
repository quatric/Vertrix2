""
    "Compare VF-backed XM samples with independent original resource parsing."
    "" import argparse import ctypes import json import struct import
        subprocess from pathlib import Path

    class Sample(ctypes.Structure)
    : _fields_ =
          [
              ("name", ctypes.c_char * 23), ("size", ctypes.c_uint32),
              ("loop_start", ctypes.c_uint32), ("loop_length", ctypes.c_uint32),
              ("loop_end", ctypes.c_uint32), ("base_frequency", ctypes.c_uint16),
              ("volume", ctypes.c_uint8), ("finetune", ctypes.c_int8), ("type", ctypes.c_uint8),
              ("panning", ctypes.c_uint8), ("relative", ctypes.c_int8),
              ("native_flags", ctypes.c_uint8), ("samples", ctypes.c_void_p),
              ("ready", ctypes.c_uint)
          ]

      def decode(data, sixteen)
    : decoded = bytearray(data);previous=0
    if sixteen:
        for offset in range(0,len(data)-1,2):
            previous=(previous+int.from_bytes(data[offset:offset+2],"little"))&65535
            decoded[offset:offset+2]=previous.to_bytes(2,"little")
    else:
        for offset,value in enumerate(data):
            previous=(previous+value)&255;
decoded[offset] = previous return bytes(decoded)

    def
    main()
    : parser = argparse.ArgumentParser(description = __doc__)
                   parser.add_argument("archive", type = Path);
parser.add_argument("music",
                    type = Path) parser.add_argument("--build-dir", type = Path,
                                                     required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "xm-samples.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "xm.c"), str(source / "audio.c"), str(source / "vf.c"), "-o",
                          str(library)
                      ],
                      check = True) n = ctypes.CDLL(str(library));
n.vertrix_vf_open.argtypes = [ctypes.c_char_p];
n.vertrix_vf_open.restype = ctypes.c_void_p n.vertrix_vf_close.argtypes =
    [ctypes.c_void_p] n.vertrix_xm_sample_load.argtypes =
        [
            ctypes.c_void_p, ctypes.c_char_p, ctypes.c_uint32, ctypes.c_uint32,
            ctypes.POINTER(Sample)
        ] n.vertrix_xm_sample_free.argtypes = [ctypes.POINTER(Sample)] vf =
            n.vertrix_vf_open(str(args.archive.resolve()).encode());
assert vf files = instruments = samples = total_bytes = empty = sixteen = 0
try:
        for
            path in sorted(args.music.glob("*.xm")) : data = path.read_bytes();
name = ("musique/" + path.name).encode();offset=60+struct.unpack_from("<I",data,60)[0]
            patterns,instrument_count=struct.unpack_from("<HH",data,70)
            for _ in range(patterns):
                header=struct.unpack_from("<I",data,offset)[0];packed=struct.unpack_from("<H",data,offset+7)[0]
                offset+=header+packed
            for instrument in range(instrument_count):
                length=struct.unpack_from("<I",data,offset)[0];
count = struct.unpack_from("<H", data, offset + 27)[0] header_size =
    struct.unpack_from("<I", data, offset + 29)[0] if count else 0 offset += length;payload=offset+header_size*count
                for sample in range(count):
                    h=data[offset+sample*header_size:offset+sample*header_size+40]
                    size,loop_start,loop_length=struct.unpack_from("<III",h)
                    expected=decode(data[payload:payload+size],h[14]&16);
payload += size output = Sample();
assert n.vertrix_xm_sample_load(vf, name, instrument, sample, ctypes.byref(output)),
    (name, instrument, sample)assert output.ready and output.size == size and output.loop_start
                == loop_start and output.loop_length == loop_length assert output.loop_end ==
                (loop_start + loop_length) &
            0xffffffff and
        output.base_frequency == 8363 assert output.volume == h[12] and
        output.finetune == int.from_bytes(h [13:14], "little", signed = True) assert output.type
            == h[14] and
        output.panning == h[15] and
        output.relative == int.from_bytes(h [16:17], "little", signed = True) flags =
        (1 if h[14] & 16 else 0) | (16 if h[14] & 1 else 0) |
        (32 if h[14] & 2 else 0) assert output.native_flags
            == flags assert ctypes.string_at(ctypes.addressof(output), 23) ==
            h [18:40] + bytes(1) if size : prepared = bytearray(expected) + bytes(4) if flags & 16
    : assert loop_start <= size and output.loop_end <= size guard = prepared
    [loop_start:loop_start + 4] prepared
    [output.loop_end:output.loop_end + 4] = guard assert ctypes.string_at(output.samples,
                                                                          size + 4) == prepared else
    : assert not output.samples;
empty += 1 saved = bytes(output);
assert not n.vertrix_xm_sample_load(vf, name, instrument, sample, ctypes.byref(output));
assert bytes(output) == saved n.vertrix_xm_sample_free(ctypes.byref(output));
assert bytes(output) == bytes(Sample()) n.vertrix_xm_sample_free(ctypes.byref(output)) total_bytes
    += size;
samples += 1;
sixteen += bool(h[14] & 16) output = Sample();
assert not n.vertrix_xm_sample_load(vf, name, instrument, count, ctypes.byref(output))
        assert bytes(output) == bytes(Sample());
offset = payload;
instruments += 1 files += 1 finally : n.vertrix_vf_close(vf) assert files ==
                          29 report = {
    "status" : "passed",
    "files" : files,
    "instruments" : instruments,
    "samples" : samples,
    "sample_bytes" : total_bytes,
    "empty_samples" : empty,
    "sixteen_bit_samples" : sixteen,
    "scope" : "Direct VF XM sample metadata and delta-decoded bytes compared with independent "
              "original resource parsing; includes software-mixer interpolation guards; "
              "instruments/envelopes and playback excluded."
}(build / "xm-samples-verification.json")
                                          .write_text(json.dumps(report, indent = 2) + "\n");
print(json.dumps(report, indent = 2))

        if __name__
    == "__main__" : main()
