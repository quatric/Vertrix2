"""Verify recovered XM event decoding against the original executable."""
import argparse
import ctypes
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original,BOARD,BLOCKS

class Event(ctypes.Structure):
    _fields_=[(name,ctypes.c_uint8) for name in ("note","instrument","volume","effect","parameter")]

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable",type=Path);
parser.add_argument("music",
                    type = Path) parser.add_argument("--build-dir", type = Path,
                                                     required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "xm.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "xm.c"), str(source / "vf.c"), str(source / "audio.c"), "-o",
                          str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
native.vertrix_xm_event.argtypes = [
    ctypes.c_void_p, ctypes.c_size_t, ctypes.POINTER(ctypes.c_size_t), ctypes.POINTER(Event)
] original = Original(args.executable);rng=random.Random(0x40e690)
    def compare(data,count):
        assert len(data)<=32768
        storage=(ctypes.c_uint8*len(data)).from_buffer_copy(data) if data else None
        if data:original.cpu.mem_write(BLOCKS,data)
        original.cpu.mem_write(0x530440,struct.pack("<I",BLOCKS if data else 0))
        cursor=ctypes.c_size_t()
        for _ in range(count):
            original.cpu.mem_write(BOARD,bytes([0xA5])*8);original.call(0x40E690)
            expected=bytes(original.cpu.mem_read(BOARD,5))
            position=struct.unpack("<I",original.cpu.mem_read(0x530440,4))[0]
            event=Event(1,2,3,4,5)
            assert native.vertrix_xm_event(storage,len(data),ctypes.byref(cursor),ctypes.byref(event))
            assert bytes(event)==expected
            assert cursor.value==(position-BLOCKS if data else 0)
    for _ in range(20000):
        first=rng.randrange(256)
        data=bytes([first])+rng.randbytes(5)
        compare(data,1)
    compare(b"",1)
    truncated=0
    for flags in range(32):
        full=bytes([128|flags])+bytes(range(flags.bit_count()))
        for size in range(len(full)):
            cursor=ctypes.c_size_t();
event = Event(1, 2, 3, 4, 5);
saved = bytes(event)
    storage = (ctypes.c_uint8 * len(full))
                      .from_buffer_copy(full) assert not native
                      .vertrix_xm_event(storage, size, ctypes.byref(cursor), ctypes.byref(event))
                          assert cursor.value == 0 and
              bytes(event) == saved;truncated+=1
    files=patterns=cells=0
    for path in sorted(args.music.glob("*.xm")):
        data=path.read_bytes();channels,pattern_count=struct.unpack_from("<HH",data,68)
        offset=60+struct.unpack_from("<I",data,60)[0]
        for _ in range(pattern_count):
            header=struct.unpack_from("<I",data,offset)[0]
            assert data[offset+4]==0
            rows,size=struct.unpack_from("<HH",data,offset+5)
            compare(data[offset+header:offset+header+size],rows*channels)
            offset+=header+size;
patterns += 1;
cells += rows *channels files += 1 if files % 5 ==
                                 0
    : print(f "Verified {files} original XM files", flush = True) assert files == 29 and patterns ==
      967 and cells == 610816 report = {
    "status" : "passed",
    "xm_files" : files,
    "patterns" : patterns,
    "original_events" : cells,
    "random_events" : 20000,
    "truncated_events_rejected" : truncated,
    "scope" : "Original complete 0x40e690 event decoder; all original XM pattern events. No music "
              "tick, instrument playback or effects execution."
}(build / "xm-verification.json")
                                           .write_text(json.dumps(report, indent = 2) + "\n");
print(json.dumps(report, indent = 2))

        if __name__
    == "__main__" : main()
