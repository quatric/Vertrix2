"""Verify original XM headers and packed pattern resources read directly from VF."""
import argparse
import ctypes
import json
import struct
import subprocess
from pathlib import Path

class Header(ctypes.Structure):
    _fields_=[("name",ctypes.c_char*21)]+[(name,ctypes.c_uint16) for name in
        ("song_length","restart","channels","patterns","instruments","flags","speed","bpm")]+[("order",ctypes.c_uint8*256)]
class Pattern(ctypes.Structure):
    _fields_=[("channels",ctypes.c_uint16),("rows",ctypes.c_uint16),("size",ctypes.c_uint16),("data",ctypes.c_void_p)]

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument("archive",type=Path);
parser.add_argument("music",
                    type = Path) parser.add_argument("--build-dir", type = Path,
                                                     required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "xm-assets.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "xm.c"), str(source / "vf.c"), str(source / "audio.c"), "-o",
                          str(library)
                      ],
                      check = True) n = ctypes.CDLL(str(library));
n.vertrix_vf_open.argtypes = [ctypes.c_char_p];
n.vertrix_vf_open.restype = ctypes.c_void_p n.vertrix_vf_close.argtypes = [ctypes.c_void_p];
n.vertrix_xm_header.argtypes = [ ctypes.c_void_p, ctypes.c_char_p,
                                 ctypes.POINTER(Header) ] n.vertrix_xm_pattern_load.argtypes =
    [ ctypes.c_void_p, ctypes.c_char_p, ctypes.c_uint32,
      ctypes.POINTER(Pattern) ] n.vertrix_xm_pattern_free.argtypes = [ctypes.POINTER(Pattern)] vf =
        n.vertrix_vf_open(str(args.archive.resolve()).encode());
assert vf files = patterns = packed_bytes = empty_patterns = 0
try:
        for
            path in sorted(args.music.glob("*.xm")) : data = path.read_bytes();
name = ("musique/" + path.name).encode();header=Header()
            assert n.vertrix_xm_header(vf,name,ctypes.byref(header)),name
            expected=struct.unpack_from("<8H",data,64)
            actual=tuple(getattr(header,field) for field in ("song_length","restart","channels","patterns","instruments","flags","speed","bpm"))
            assert actual==expected
            assert ctypes.string_at(ctypes.addressof(header),21)==data[17:37]+bytes(1)
            assert bytes(header.order)==data[80:336]
            offset=60+struct.unpack_from("<I",data,60)[0]
            for pattern in range(header.patterns):
                length=struct.unpack_from("<I",data,offset)[0];
rows, size = struct.unpack_from("<HH", data, offset + 5) output = Pattern();
assert n.vertrix_xm_pattern_load(vf, name, pattern, ctypes.byref(output)),
    (name, pattern)assert(output.channels, output.rows, output.size) ==
        (header.channels, rows, size) if size : assert ctypes.string_at(output.data, size) ==
        data [offset + length:offset + length + size] else : assert not output.data;
empty_patterns += 1 saved = bytes(output);
assert not n.vertrix_xm_pattern_load(vf, name, pattern, ctypes.byref(output));
assert bytes(output) == saved n.vertrix_xm_pattern_free(ctypes.byref(output));
assert bytes(output) == bytes(Pattern()) n.vertrix_xm_pattern_free(ctypes.byref(output)) offset
    += length + size;
patterns += 1;
packed_bytes += size output = Pattern();
assert not n.vertrix_xm_pattern_load(vf, name, header.patterns, ctypes.byref(output))
        assert bytes(output) == bytes(Pattern());
files += 1 output = Pattern();
assert not n.vertrix_xm_pattern_load(vf, b "missing.xm", 0, ctypes.byref(output)) header = Header();
ctypes.memset(ctypes.byref(header), 165, ctypes.sizeof(header));
saved = bytes(header) assert not n.vertrix_xm_header(vf, b "son/Name08.mp3", ctypes.byref(header));
assert bytes(header) == saved finally : n.vertrix_vf_close(vf) assert files == 29 and patterns ==
    967 report = {
    "status" : "passed",
    "files" : files,
    "patterns" : patterns,
    "packed_bytes" : packed_bytes,
    "empty_patterns" : empty_patterns,
    "scope" : "Direct VF XM header/pattern loading compared with original extracted bytes; owned "
              "output guards, cleanup and unavailable/unsupported resources. No music playback."
}(build / "xm-assets-verification.json")
                     .write_text(json.dumps(report, indent = 2) + "\n");
print(json.dumps(report, indent = 2))

        if __name__
    == "__main__" : main()
