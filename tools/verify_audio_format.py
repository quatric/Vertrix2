""
    "Compare original output-format builder instructions against recovered C."
    "" import argparse import ctypes import json import random import struct import
        subprocess from pathlib import Path from unicorn.x86_const import UC_X86_REG_ESI,
    UC_X86_REG_EBP, UC_X86_REG_EDI from original import Original,
    BOARD

    class Format(ctypes.Structure)
    : _fields_ =
          [
              ("format", ctypes.c_uint16), ("channels", ctypes.c_uint16), ("rate", ctypes.c_uint32),
              ("byte_rate", ctypes.c_uint32), ("align", ctypes.c_uint16), ("bits", ctypes.c_uint16)
          ]

      def main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument("executable",
                                                                                  type = Path);
parser.add_argument("--build-dir", type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "audio-format.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "audio.c"), str(source / "vf.c"), "-o", str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
native.vertrix_audio_output_format.argtypes =
    [ ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint16 ] native.vertrix_audio_output_format.restype =
        Format native.vertrix_audio_buffer_bytes.argtypes =
            [ ctypes.c_uint8, ctypes.c_uint8,
              ctypes.c_uint16 ] native.vertrix_audio_buffer_bytes.restype =
                ctypes.c_uint32 original = Original(args.executable);
rng = random.Random(0x4110);
cases = 20000;frame=0x707000
    for index in range(cases):
        flag4,flag5,rate=rng.randrange(256),rng.randrange(256),rng.randrange(65536)
        if index<16:flag4,flag5,rate=index%2,(index//2)%2,(0,11025,22050,65535)[index//4]
        original.cpu.mem_write(BOARD+4,struct.pack("<BBH",flag4,flag5,rate))
        original.cpu.mem_write(frame-36,bytes(20));original.cpu.reg_write(UC_X86_REG_ESI,BOARD)
        original.cpu.reg_write(UC_X86_REG_EBP,frame)
        original.call(0x410FFD,stop=0x41106A)
        expected=struct.unpack("<HHIIHH",original.cpu.mem_read(frame-36,16))
        result=native.vertrix_audio_output_format(flag4,flag5,rate)
        assert (result.format,result.channels,result.rate,result.byte_rate,result.align,result.bits)==expected
        original.cpu.reg_write(UC_X86_REG_ESI,BOARD)
        original.call(0x41108A,stop=0x4110B3)
        expected_bytes=original.cpu.reg_read(UC_X86_REG_EDI)
        assert native.vertrix_audio_buffer_bytes(flag4,flag5,rate)==expected_bytes
    report={"status":"passed","format_cases":cases,"buffer_size_cases":cases,"scope":"Original 0x410ffd..0x41106a output format builder, including 8-bit branch 0x41110d. Also executes buffer sizing 0x41108a..0x4110b3 and stereo branch 0x41111e. Device capability negotiation and playback excluded."}
    (build/"audio-format-verification.json").write_text(json.dumps(report,indent=2)+"\n");print(json.dumps(report,indent=2))

if __name__=="__main__":main()
