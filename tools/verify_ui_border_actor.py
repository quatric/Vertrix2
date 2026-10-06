"""Compare actual original border setup including all untouched actor bytes."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from unicorn.x86_const import UC_X86_REG_EBP, UC_X86_REG_ESI, UC_X86_REG_EDI


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = build/'ui-border-actor.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
        str(root/'source/ui_border_actor.c'), str(root/'source/actor_storage.c'),
        '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_ui_border_actor_construct.argtypes = [c.c_void_p,c.c_size_t,c.c_int16,c.c_int16,c.c_uint32]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x42b4d7)
    for case in range(2048):
        raw = rng.randbytes(0x180)
        storage = c.create_string_buffer(raw,len(raw))
        x, y = rng.randrange(-32768,32768), rng.randrange(-32768,32768)
        linked = rng.randrange(2**32)
        cpu.mem_write(0x800000,raw)
        original.call(0x4abd70,eax=0x800000,edx=0)
        ebp = 0x707000
        cpu.mem_write(ebp-0x1c,struct.pack('<I',0x805000))
#The y temporary overlaps the high half of the linked pointer.Only
#its signed high word participates in the original arithmetic shift.
        cpu.mem_write(ebp-0x18,struct.pack('<h',y))
        cpu.mem_write(ebp-0x26,struct.pack('<I',(x&65535)<<16))
        cpu.mem_write(0x805000,struct.pack('<I',linked))
        cpu.reg_write(UC_X86_REG_EBP,ebp)
        cpu.reg_write(UC_X86_REG_ESI,0x802000)
        original.call(0x42b4d7,eax=0x800000,stop=0x42b55b)
        assert native.vertrix_ui_border_actor_construct(storage,len(raw),x,y,linked)
        assert storage.raw == bytes(cpu.mem_read(0x800000,len(raw))), case
        before = storage.raw
        assert not native.vertrix_ui_border_actor_construct(storage,0x15b,x,y,linked)
        assert storage.raw == before
    assert not native.vertrix_ui_border_actor_construct(None,0x15c,0,0,0)
    native.vertrix_ui_border_actor_position.argtypes = [c.c_size_t,c.c_uint8,c.POINTER(c.c_int16),c.POINTER(c.c_int16)]
    for side in range(256):
        for
        index in range(3)
            : cpu.reg_write(UC_X86_REG_EBP, 0x707000) cpu.reg_write(UC_X86_REG_EDI, index) cpu
                  .mem_write(0x707000 - 0x14, bytes([side])) original.call(0x42b3ac,
                                                                           stop = 0x42b3d0)
                      expected_x =
            struct.unpack('<i', cpu.mem_read(0x707000 - 0x24, 4))[0] expected_y =
                struct.unpack('<i', cpu.mem_read(0x707000 - 0x18, 4))[0] x,
                      y = c.c_int16(),
                      c.c_int16() assert native.vertrix_ui_border_actor_position(
                          index, side, c.byref(x), c.byref(y)) assert(x.value, y.value) ==
                          (expected_x, expected_y)assert
                          not native.vertrix_ui_border_actor_position(3, side, c.byref(x),
                                                                      c.byref(y))
                              assert(x.value, y.value) == (expected_x, expected_y)report =
                          {
                              'status' : 'passed',
                              'original_border_setup_cases' : 2048,
                              'short_storage_preservation_cases' : 2048,
                              'original_position_selection_cases' : 768,
                              'scope' :
                                  'Original4abd70 constructor and complete42b4d7..42b55b setup execute without ' 'hooks. Entire extended actor storage compares across signed positions and ' 'linked identities. Parent attachment, surrounding position calculation, ' 'later image binding, update/draw and full gameplay remain separate.'
                          }(build / 'ui-border-actor-verification.json')
                              .write_text(json.dumps(report, indent = 2) + '\n')
                                  print(json.dumps(report, indent = 2))

                                      if __name__
                          == '__main__' : main()
