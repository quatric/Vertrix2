"""Compare complete original preview mode and frame access helpers."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from unicorn.x86_const import UC_X86_REG_EAX
from verify_linked_alternating import Resolve


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable',type=Path)
    parser.add_argument('--build-dir',type=Path,required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True,exist_ok=True)
    source = Path(__file__).resolve().parents[1]/'source'
    library = build/'player-preview-state.dylib'
    subprocess.run(['cc','-shared','-fPIC','-O2','-Wall','-Wextra','-Werror',
        str(source/'player_preview_state.c'),str(source/'actor_storage.c'),
        str(source/'player_preview_motion.c'),str(source/'timing.c'),
        '-o',str(library)],check=True)
    native = c.CDLL(str(library))
    native.vertrix_player_preview_mode.argtypes = [c.c_void_p,c.c_size_t,c.POINTER(c.c_uint32)]
    native.vertrix_player_preview_toggle.argtypes = [c.c_void_p,c.c_size_t]
    native.vertrix_player_preview_set_mode.argtypes = [c.c_void_p,c.c_size_t,c.c_uint32]
    native.vertrix_player_preview_frame.argtypes = [c.c_void_p,c.c_size_t,Resolve,c.c_void_p,
                                                   c.POINTER(c.c_uint32)]
    native.vertrix_player_preview_frames.argtypes = [c.c_void_p,c.c_size_t,Resolve,c.c_void_p,
                                                    c.POINTER(c.c_uint32),c.c_size_t]
    native.vertrix_player_preview_motion_start.argtypes = [c.c_void_p,c.c_size_t,c.c_int]
    native.vertrix_player_preview_below_limit.argtypes = [c.c_void_p,c.c_size_t,c.POINTER(c.c_int)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x42b110)
    actors = {}
    @Resolve
    def resolve(handle,storage,size,context):
        if handle not in actors:
            return 0
        storage[0],size[0] = c.addressof(actors[handle]),len(actors[handle])
        return 1
    for case in range(4096):
        raw = bytearray(rng.randbytes(0x1a0))
        previous,mode = rng.choice([0,1,rng.getrandbits(32)]),rng.choice([0,1,rng.getrandbits(32)])
        struct.pack_into('<I',raw,0x180,previous)
        storage = c.create_string_buffer(bytes(raw),len(raw))
        cpu.mem_write(0x800000,bytes(raw))
        original.call(0x42b110,eax=0x800000,edx=mode)
        assert native.vertrix_player_preview_set_mode(storage,len(raw),mode)
        assert storage.raw == bytes(cpu.mem_read(0x800000,len(raw))),case
        original.call(0x42b0f0,eax=0x800000)
        assert native.vertrix_player_preview_toggle(storage,len(raw))
        assert storage.raw == bytes(cpu.mem_read(0x800000,len(raw))),case
        original.call(0x42b0e0,eax=0x800000)
        output = c.c_uint32(0xdeadbeef)
        assert native.vertrix_player_preview_mode(storage,len(raw),c.byref(output))
        assert output.value == cpu.reg_read(UC_X86_REG_EAX)
        count = 1+case%3
        parent = bytearray(storage.raw)
        struct.pack_into('<I',parent,0x188,count)
        for index in range(3):
            handle = 0x802000+index*0x200
            struct.pack_into('<I',parent,0x15c+index*4,handle)
            actor = rng.randbytes(0x15c)
            actors[handle] = c.create_string_buffer(actor,len(actor))
            cpu.mem_write(handle,actor)
        cpu.mem_write(0x800000,bytes(parent))
        storage = c.create_string_buffer(bytes(parent),len(parent))
        original.call(0x42b070,eax=0x800000)
        assert native.vertrix_player_preview_frame(storage,len(parent),resolve,None,c.byref(output))
        assert output.value == cpu.reg_read(UC_X86_REG_EAX)
        before = storage.raw
        assert not native.vertrix_player_preview_set_mode(storage,0x187,mode)
        assert not native.vertrix_player_preview_toggle(storage,0x187)
        assert storage.raw == before
        expected = output.value
        assert not native.vertrix_player_preview_frame(storage,0x18b,resolve,None,c.byref(output))
        assert output.value == expected
        snapshot_count = case%4
        c.memmove(c.addressof(storage)+0x188,struct.pack('<I',snapshot_count),4)
        cpu.mem_write(0x800000,storage.raw)
        values = [rng.getrandbits(32) for _ in range(9)]
        frames = (c.c_uint32*9)(*values)
        cpu.mem_write(0x806000,bytes(frames))
        original.call(0x42b090,eax=0x800000,edx=0x806000)
        assert native.vertrix_player_preview_frames(storage,len(parent),resolve,None,frames,9)
        assert bytes(frames) == bytes(cpu.mem_read(0x806000,len(bytes(frames)))),case
        frame_before = bytes(frames)
        assert not native.vertrix_player_preview_frames(storage,len(parent),resolve,None,frames,6)
        assert bytes(frames) == frame_before
        c.memmove(c.addressof(storage)+0x188,struct.pack('<I',4),4)
        assert not native.vertrix_player_preview_frames(storage,len(parent),resolve,None,frames,9)
        assert bytes(frames) == frame_before
        c.memmove(c.addressof(storage)+0x188,struct.pack('<I',3),4)
        missing = actors.pop(0x802400)
        assert not native.vertrix_player_preview_frames(storage,len(parent),resolve,None,frames,9)
        assert bytes(frames) == frame_before
        actors[0x802400] = missing
        state = rng.choice([0,0,rng.getrandbits(32)])
        c.memmove(c.addressof(storage)+0x178,struct.pack('<I',state),4)
        cpu.mem_write(0x800000,storage.raw)
        cpu.mem_write(0x532bbc,struct.pack('<I',case%3))
        original.call(0x42b000,eax=0x800000)
        assert native.vertrix_player_preview_motion_start(storage,len(parent),case%3)
        assert storage.raw == bytes(cpu.mem_read(0x800000,len(parent))),case
        original.call(0x42b050,eax=0x800000)
        below = c.c_int(99)
        assert native.vertrix_player_preview_below_limit(storage,len(parent),c.byref(below))
        assert below.value == cpu.reg_read(UC_X86_REG_EAX),case
        motion_before = storage.raw
        assert not native.vertrix_player_preview_motion_start(storage,0x17b,0)
        assert storage.raw == motion_before
        assert not native.vertrix_player_preview_below_limit(storage,0xaf,c.byref(below))
        assert below.value == cpu.reg_read(UC_X86_REG_EAX)
    report = {'status':
            'passed', 'original_helper_calls' : 28672, 'failure_preservation_cases' : 12288,
                'original_preview_snapshot_cases' : 4096,
                'snapshot_failure_preservation_cases' : 12288, 'original_motion_start_cases' : 4096,
                'original_signed_limit_cases' : 4096, 'motion_failure_preservation_cases' : 8192,
                'scope'
                : 'Complete42b000/42b050/42b070/42b090/42b0e0/42b0f0/42b110 without hooks. Entire player bytes ' 'match mode and wrapping toggle operations; selected preview frame matches ' 'for valid counts1..3. Seven-DWORD snapshots match counts0..3 with ' 'extra destination entries preserved. Caller supplies identity resolution. Full player ' 'construction, game-loop integration and Wii execution remain unfinished.'
            }
            (build / 'player-preview-state-verification.json')
                    .write_text(json.dumps(report, indent = 2) + '\n')
                        print(json.dumps(report, indent = 2))

                            if __name__ == '__main__' : main()
