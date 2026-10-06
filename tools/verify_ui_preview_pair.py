"""Compare final preview pair setup and descriptor binding with original x86."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from verify_sprite import SpriteFrame
from verify_ui_sprite_vf import Bank
from unicorn.x86_const import UC_X86_REG_EBP, UC_X86_REG_ESI, UC_X86_REG_EDI
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EIP, UC_X86_REG_ESP
from unicorn import UC_HOOK_CODE


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = build/'ui-preview-pair.dylib'
    names = ['ui_preview_pair.c','ui_border_actor.c','ui_companion_actor.c',
             'sprite_actor_image.c','actor_storage.c','ui_player_previews.c']
    subprocess.run(['cc','-shared','-fPIC','-O2','-Wall','-Wextra','-Werror',
                    *[str(root/'source'/name) for name in names],'-o',str(library)],check=True)
    native = c.CDLL(str(library))
    construct = native.vertrix_ui_preview_pair_construct
    construct.argtypes = [c.c_void_p,c.c_size_t,c.c_void_p,c.c_size_t,c.c_size_t,
                         c.c_uint8,c.c_uint32,c.c_uint32,c.POINTER(Bank),c.POINTER(Bank)]
    frames = (SpriteFrame*34)()
    pixels = (c.c_ubyte*4)(1,2,3,255)
    for frame in frames:
        frame.image.rgba = c.addressof(pixels)
        frame.image.width = frame.image.height = 1
    bank_frames = c.cast(frames, Bank._fields_[0][1])
    interface, border_bank = Bank(bank_frames,34), Bank(bank_frames,1)
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_map(0x811000,0x3000)
    cpu.mem_write(0x811000,struct.pack('<34I',*[0x812000+i*40 for i in range(34)]))
    cpu.mem_write(0x5449fc,struct.pack('<6I',0x811000,34,0,0,0,0))
    cpu.mem_write(0x5466a4,struct.pack('<6I',0x811000,1,0,0,0,0))
    rng = random.Random(0x42b586)
    parent_construct = native.vertrix_ui_player_preview_parent_construct
    parent_construct.argtypes = [c.c_void_p,c.c_size_t]
    for case in range(2048):
        raw = rng.randbytes(0x1a0)
        parent = c.create_string_buffer(raw,len(raw))
        cpu.mem_write(0x800000,raw)
        original.call(0x42b150,eax=0x800000,edx=rng.getrandbits(32))
        assert parent_construct(parent,len(raw))
        assert parent.raw == bytes(cpu.mem_read(0x800000,len(raw))),case
        before = parent.raw
        assert not parent_construct(parent,0x173)
        assert parent.raw == before
    assert not parent_construct(None,0x174)
    for case in range(2048):
        raws = [rng.randbytes(0x180),rng.randbytes(0x180)]
        actors = [c.create_string_buffer(raw,len(raw)) for raw in raws]
        index, side = case%3, case%256
        source, linked = rng.randrange(32), rng.getrandbits(32)
        x = ([143,133,153] if side == 0 else [477,467,487])[index]
        y = [129,147,147][index]
        for address, raw in zip([0x800000,0x801000],raws):
            cpu.mem_write(address,raw)
            original.call(0x4abd70,eax=address,edx=0)
        ebp = 0x707000
        cpu.mem_write(ebp-0x1c,struct.pack('<I',0x805000))
        cpu.mem_write(ebp-0x18,struct.pack('<h',y))
        cpu.mem_write(ebp-0x26,struct.pack('<I',(x&65535)<<16))
        cpu.mem_write(0x805000,struct.pack('<I',linked))
        cpu.mem_write(0x4fbf74,struct.pack('<I',source))
        cpu.reg_write(UC_X86_REG_EBP,ebp)
        cpu.reg_write(UC_X86_REG_ESI,0x802000)
        cpu.reg_write(UC_X86_REG_EDI,index)
        original.call(0x42b3f3,eax=0x800000,stop=0x42b4b4)
        original.call(0x42b4d7,eax=0x801000,stop=0x42b586)
        assert construct(actors[0],0x180,actors[1],0x180,index,side,linked,source,
                         c.byref(interface),c.byref(border_bank))
        for actor,address,descriptor in zip(actors,[0x800000,0x801000],[source+index,0]):
            expected = bytearray(cpu.mem_read(address,0x180))
            assert struct.unpack_from('<I',expected,0xb4)[0] == 0x812000+descriptor*40
            struct.pack_into('<I',expected,0xb4,descriptor)
            assert actor.raw == bytes(expected), case
        before = [actor.raw for actor in actors]
        assert not construct(actors[0],0x180,actors[1],0x180,index,side,linked,34,
                             c.byref(interface),c.byref(border_bank))
        assert not construct(actors[0],0x180,actors[1],0x180,index,side,linked,source,
                             c.byref(interface),None)
        assert not construct(actors[0],0x180,actors[0],0x180,index,side,linked,source,
                             c.byref(interface),c.byref(border_bank))
        assert [actor.raw for actor in actors] == before
    player_construct = native.vertrix_ui_player_previews_construct
    player_construct.argtypes = [c.c_void_p,c.c_size_t,c.c_void_p,c.c_size_t,
        c.POINTER(c.c_uint32),c.c_uint8,c.c_uint32,c.POINTER(Bank),c.POINTER(Bank)]
    cpu.mem_map(0x900000,0x3000)
    addresses = [0x900000 + i*0x200 for i in range(6)]
    allocated = []
    def allocate(cpu, address, size, context):
            assert cpu.reg_read(UC_X86_REG_EAX) ==
                0x15c result = addresses[len(allocated)] allocated.append(
                result) stack = cpu.reg_read(UC_X86_REG_ESP) destination =
                struct.unpack('<I',
                              cpu.mem_read(stack, 4))[0] cpu.reg_write(UC_X86_REG_EAX, result) cpu
                    .reg_write(UC_X86_REG_ESP, stack + 4) cpu.reg_write(UC_X86_REG_EIP,
                                                                        destination) hook =
                    cpu.hook_add(UC_HOOK_CODE, allocate, begin = 0x4ca000, end = 0x4ca000)
            try:
        for
        case in range(512):
            allocated.clear()
            parent_raw = rng.randbytes(0x180)
            actor_raw = rng.randbytes(6*0x15c)
            parent = c.create_string_buffer(parent_raw,len(parent_raw))
            actors = c.create_string_buffer(actor_raw,len(actor_raw))
            for i,address in enumerate(addresses):
                cpu.mem_write(address,actor_raw[i*0x15c:(i+1)*0x15c])
            cpu.mem_write(0x800000,parent_raw)
            original.call(0x42b150,eax=0x800000,edx=0)
            assert parent_construct(parent,len(parent_raw))
            identity = rng.getrandbits(32)
            cpu.mem_write(0x800000,struct.pack('<I',identity))
            c.memmove(parent,struct.pack('<I',identity),4)
            source, side = rng.randrange(32),case%256
            cpu.mem_write(0x4fbf74,struct.pack('<I',source))
            original.call(0x42b370,eax=0x800000,edx=side)
            assert allocated == addresses
            handles = (c.c_uint32*6)(*addresses)
            assert player_construct(parent,len(parent_raw),actors,len(actor_raw),handles,side,
                                    source,c.byref(interface),c.byref(border_bank))
            assert parent.raw == bytes(cpu.mem_read(0x800000,len(parent_raw))),case
            for i,address in enumerate(addresses):
                descriptor =
                    source + i // 2 if i%2 == 0 else 0
                                 expected =
                        bytearray(cpu.mem_read(address, 0x15c))
                            assert struct.unpack_from('<I', expected, 0xb4)[0] ==
                        0x812000 +
                            descriptor *
                                40 struct.pack_into('<I', expected, 0xb4,
                                                    descriptor) assert actors.raw
                                [i * 0x15c:(i + 1) * 0x15c] ==
                        expected,
                (case, i)before = parent.raw,
                actors.raw
#The third companion binding fails after two valid staged pairs.
                    limited = Bank(bank_frames, source + 2) assert
                              not player_construct(parent, len(parent_raw), actors, len(actor_raw),
                                                   handles, side, source, c.byref(limited),
                                                   c.byref(border_bank))
                                  assert(parent.raw, actors.raw) == before
                              handles[5] = handles[0] assert
                                           not player_construct(parent, len(parent_raw), actors,
                                                                len(actor_raw), handles, side,
                                                                source, c.byref(interface),
                                                                c.byref(border_bank))
                                               assert(parent.raw, actors.raw) == before finally
                    : cpu.hook_del(hook) report = {
                    'status' : 'passed',
                    'original_pair_cases' : 2048,
                    'actors_compared' : 4096,
                    'failure_preservation_cases' : 6144,
                    'complete_original_preview_parent_constructor_cases' : 2048,
                    'parent_constructor_failure_preservation_cases' : 2048,
                    'complete_original_player_preview_cases' : 512,
                    'complete_original_player_preview_actors' : 3072,
                    'player_failure_preservation_cases' : 1024,
                    'scope' :
                        'Original constructors and complete companion/border setup fragments ' 'execute without hooks, including actual4877f0 binding and final callbacks. ' 'Original descriptor pointers normalize to verified bank-local indices. ' 'Entire extended actors match. Complete42b370 construction also matches ' 'all six actors and all parent bytes with only heap allocation supplied. ' 'Direct resource fixtures; native ownership, scene registration and ' 'full gameplay remain separate.'
                }(build / 'ui-preview-pair-verification.json')
                                                      .write_text(json.dumps(report, indent = 2) +
                                                                  '\n')
                                                          print(json.dumps(report, indent = 2))

                                                              if __name__
                                                  == '__main__' : main()
