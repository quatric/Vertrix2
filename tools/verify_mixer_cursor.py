""
    "Compare recovered mixer cursor geometry with original sample attachment."
    "" import argparse import ctypes import json import random import struct import
        subprocess from pathlib import Path from original import Original,
    BOARD,
    BLOCKS

    class Cursor(ctypes.Structure)
    : _fields_ =
          [
              ("position", ctypes.c_uint32), ("start", ctypes.c_uint32), ("end", ctypes.c_uint32),
              ("flags", ctypes.c_uint8)
          ]

      def main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument("executable",
                                                                                  type = Path);
parser.add_argument("--build-dir", type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "mixer.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "mixer.c"), "-o", str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
native.vertrix_mixer_cursor.argtypes =
    [ ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint32,
      ctypes.c_uint8 ] native.vertrix_mixer_cursor.restype =
        Cursor native.vertrix_mixer_step.argtypes =
            [ ctypes.c_uint32, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint32) ] original =
                Original(args.executable);
rng = random.Random(0x40c9d0);cases=20000
    original.cpu.mem_write(0x52FC18,struct.pack("<I",32))
    for index in range(cases):
        count,start,end=rng.randrange(2**32),rng.randrange(2**32),rng.randrange(2**32)
        flags=rng.randrange(256);
slot = index % 32;
address = 0x52F918 + slot * 24 original.cpu.mem_write(BOARD, bytes(32));
original.cpu.mem_write(BOARD + 4, struct.pack("<4I", BLOCKS, count, start,
                                              end)) original.cpu.mem_write(BOARD + 0x16,
                                                                           bytes([flags]));
original.cpu.mem_write(address, rng.randbytes(24)) original.call(
    0x40C9D0, eax = slot, edx = BOARD) data = bytes(original.cpu.mem_read(address, 24));expected=struct.unpack_from("<I",data,4)[0],*struct.unpack_from("<II",data,12),data[22]
        result=native.vertrix_mixer_cursor(count,start,end,flags)
        assert (result.position,result.start,result.end,result.flags)==expected
    for _ in range(cases):
        frequency=rng.randrange(512,524289);rate=rng.randrange(1,2**32)
        original.cpu.mem_write(0x52FC20,struct.pack("<I",rate))
        original.call(0x40CB10,eax=0,edx=frequency)
        expected=struct.unpack("<I",original.cpu.mem_read(0x52F920,4))[0]
        result=ctypes.c_uint32()
        assert native.vertrix_mixer_step(frequency,rate,ctypes.byref(result))
        assert result.value==expected
    for frequency in (0,511,524289,0xffffffff):
        result=ctypes.c_uint32(123)
        assert not native.vertrix_mixer_step(frequency,48000,ctypes.byref(result))
        assert result.value==123
    result=ctypes.c_uint32(123)
    assert not native.vertrix_mixer_step(8363,0,ctypes.byref(result)) and result.value==123
    report={"status":"passed","cursor_cases":cases,"step_cases":cases,"scope":"Original successful attachment 0x40c9d0: cursor position, loop bounds and flags, including signed right shift and fixed-point wrapping. Also executes original 0x40cb10 playback step calculation. Source binding, slot validation and mixing excluded."}
    (build/"mixer-cursor-verification.json").write_text(json.dumps(report,indent=2)+"\n");
print(json.dumps(report, indent = 2))

        if __name__
    == "__main__" : main()
