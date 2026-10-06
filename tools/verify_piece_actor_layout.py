"""Compare complete original active-piece actor layout without hooks."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from verify_linked_alternating import Resolve
from verify_frame_resource import Resource


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable',type=Path)
    parser.add_argument('--build-dir',type=Path,required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True,exist_ok=True)
    source = Path(__file__).resolve().parents[1]/'source'
    library = build/'piece-actor-layout.dylib'
    subprocess.run(['cc','-shared','-fPIC','-O2','-Wall','-Wextra','-Werror',
        str(source/'piece_actor_layout.c'),str(source/'actor_storage.c'),
        str(source/'piece_actor_update.c'),str(source/'timer.c'),
        str(source/'piece_child_update.c'),str(source/'frame_resource.c'),
        str(source/'dword_transition.c'),
        '-o',str(library)],check=True)
    native = c.CDLL(str(library))
    native.vertrix_piece_actor_layout.argtypes = [c.c_void_p,c.c_size_t,c.c_uint16,Resolve,c.c_void_p]
    native.vertrix_piece_actor_cycle.argtypes = [c.c_void_p,c.c_size_t,Resolve,c.c_void_p]
    native.vertrix_piece_actor_parent_construct.argtypes = [c.c_void_p,c.c_size_t]
    Update = c.CFUNCTYPE(c.c_int,c.c_void_p,c.c_size_t,c.c_uint32,c.c_void_p)
    native.vertrix_piece_actor_update.argtypes = [c.c_void_p,c.c_size_t,c.c_uint32,c.c_uint16,
                                                 Resolve,Update,c.c_void_p]
    native.vertrix_piece_actor_update_resource.argtypes = [c.c_void_p,c.c_size_t,c.c_uint32,
        c.c_uint16,Resolve,c.c_void_p,c.c_int,c.c_uint32,c.POINTER(Resource),c.c_size_t]
    original = Original(args.executable)
    cpu = original.cpu
    descriptors = (c.c_uint32*4)(*[0x806000+i*40 for i in range(4)])
    resource = Resource(0,4,descriptors,None,None)
    cpu.mem_write(0x804000,bytes(descriptors))
    cpu.mem_write(0x544bd8,struct.pack('<6I',0x804000,4,0,0,0,0))
    rng = random.Random(0x42af30)
    actors = {}
    visits = []
    updated = []
    clear = 0
    @Update
    def update(storage,size,elapsed,context):
        assert size >= 0x15c
        updated.append(storage)
        if clear:
            c.memmove(storage+0x120,struct.pack('<I',0),4)
        return 1
    @Resolve
    def resolve(handle,storage,size,context):
        visits.append(handle)
        if handle not in actors:
            return 0
        storage[0],size[0] = c.addressof(actors[handle]),len(actors[handle])
        return 1
    writes = 0
    for case in range(4096):
        constructor_raw = rng.randbytes(0x1a0)
        constructed = c.create_string_buffer(constructor_raw,len(constructor_raw))
        cpu.mem_write(0x800000,constructor_raw)
        original.call(0x42aab0,eax=0x800000,edx=rng.getrandbits(32))
        assert native.vertrix_piece_actor_parent_construct(constructed,len(constructor_raw))
        assert constructed.raw == bytes(cpu.mem_read(0x800000,len(constructor_raw))),case
        constructor_before = constructed.raw
        assert not native.vertrix_piece_actor_parent_construct(constructed,0x18b)
        assert constructed.raw == constructor_before
        actors.clear()
        for index in range(7):
            handle = 0x802000+index*0x200
            raw = bytearray(rng.randbytes(0x180))
            struct.pack_into('<I',raw,0x158,0x517af4)
            struct.pack_into('<I',raw,0x154,rng.choice([0x44c2a0,0x44c2b0,0x44c310,0x44c370]))
            struct.pack_into('<2I',raw,0x104,0,0)
            struct.pack_into('<I',raw,0xb0,rng.choice([0,0x544bd8]))
            struct.pack_into('<I',raw,0xb8,rng.randrange(4))
            struct.pack_into('<I',raw,0x58,rng.choice([0,60,rng.getrandbits(32)]))
            struct.pack_into('<2I',raw,0xbc,rng.getrandbits(32),rng.choice([0,1,24,0xffffffff]))
            actors[handle] = c.create_string_buffer(bytes(raw),len(raw))
            cpu.mem_write(handle,bytes(raw))
        parent_raw = bytearray(rng.randbytes(0x1a0))
        handles = [rng.choice([0,*actors]) for _ in range(7)]
        struct.pack_into('<7I',parent_raw,0x15c,*handles)
        struct.pack_into('<I',parent_raw,0x17c,rng.choice([0,0,1,rng.getrandbits(32)]))
        struct.pack_into('<2I',parent_raw,0x180,rng.choice([0,1,2]),rng.choice([0,1,2]))
        struct.pack_into('<2I',parent_raw,0xbc,rng.getrandbits(32),rng.choice([0,1,10,0xffffffff]))
        parent = c.create_string_buffer(bytes(parent_raw),len(parent_raw))
        cpu.mem_write(0x800000,bytes(parent_raw))
        spacing = rng.choice([0,24,65535,rng.randrange(65536)])
        cpu.mem_write(0x4f90ac,struct.pack('<H',spacing))
        original.call(0x42af30,eax=0x800000)
        visits.clear()
        assert native.vertrix_piece_actor_layout(parent,len(parent_raw),spacing,resolve,None)
        assert visits == [handle for handle in handles if handle],case
        assert parent.raw == bytes(cpu.mem_read(0x800000,len(parent_raw))),case
        for handle,actor in actors.items():
            assert actor.raw == bytes(cpu.mem_read(handle,len(actor))),(case,handle)
        writes += len(visits)
        before = parent.raw,[actor.raw for actor in actors.values()]
        assert not native.vertrix_piece_actor_layout(parent,0x177,spacing,resolve,None)
        assert (parent.raw,[actor.raw for actor in actors.values()]) == before
        elapsed = rng.choice([0,1,100,rng.getrandbits(32)])
        clear = case%2
        cpu.mem_write(0x5bd834,struct.pack('<I',elapsed))
        cpu.mem_write(0x5bb710,struct.pack('<I',clear))
        original.call(0x42ac40,eax=0x800000)
        visits.clear()
        updated.clear()
        assert native.vertrix_piece_actor_update_resource(parent,len(parent_raw),elapsed,spacing,
            resolve,None,clear,0x544bd8,c.byref(resource),1)
        expected_handles = [handle for handle in handles if handle]
        assert visits == expected_handles*3,case
        assert parent.raw == bytes(cpu.mem_read(0x800000,len(parent_raw))),case
        for handle,actor in actors.items():
            assert actor.raw == bytes(cpu.mem_read(handle,len(actor))),(case,handle)
        before = parent.raw,[actor.raw for actor in actors.values()]
        assert not native.vertrix_piece_actor_update(parent,0x187,elapsed,spacing,resolve,update,None)
        assert (parent.raw,[actor.raw for actor in actors.values()]) == before
        count = case%8
        c.memmove(c.addressof(parent)+0x188,struct.pack('<I',count),4)
        if count >= 2:
#Original dereferences only the old first / last actors after rotation.
            endpoints = [rng.choice(list(actors)) for _ in range(2)]
            c.memmove(c.addressof(parent)+0x15c,struct.pack('<I',endpoints[0]),4)
            c.memmove(c.addressof(parent)+0x158+count*4,struct.pack('<I',endpoints[1]),4)
        cpu.mem_write(0x800000,parent.raw)
        original.call(0x42af80,eax=0x800000)
        assert native.vertrix_piece_actor_cycle(parent,len(parent_raw),resolve,None)
        assert parent.raw == bytes(cpu.mem_read(0x800000,len(parent_raw))),case
        for handle,actor in actors.items():
            assert actor.raw == bytes(cpu.mem_read(handle,len(actor))),(case,handle)
        before = parent.raw,[actor.raw for actor in actors.values()]
        assert not native.vertrix_piece_actor_cycle(parent,0x18b,resolve,None)
        assert (parent.raw,[actor.raw for actor in actors.values()]) == before
        c.memmove(c.addressof(parent)+0x188,struct.pack('<I',8),4)
        failed_before = parent.raw,[actor.raw for actor in actors.values()]
        assert not native.vertrix_piece_actor_cycle(parent,len(parent_raw),resolve,None)
        assert (parent.raw,[actor.raw for actor in actors.values()]) == failed_before
        c.memmove(c.addressof(parent)+0x188,struct.pack('<I',2),4)
        c.memmove(c.addressof(parent)+0x15c,struct.pack('<I',0),4)
        failed_before = parent.raw,[actor.raw for actor in actors.values()]
        assert not native.vertrix_piece_actor_cycle(parent,len(parent_raw),resolve,None)
        assert (parent.raw,[actor.raw for actor in actors.values()]) == failed_before
    report = {'status':'passed','complete_original_layout_cases':4096,
              'actor_position_updates':writes,'failure_preservation_cases':4096,
              'complete_original_piece_update_cases':4096,
              'piece_update_failure_preservation_cases':4096,
              'complete_original_piece_cycle_cases':4096,
              'piece_cycle_failure_preservation_cases':12288,
              'complete_original_piece_parent_constructor_cases':4096,
              'piece_parent_constructor_failure_preservation_cases':4096,
              'scope':'Complete42af30 without hooks. Entire parent and child storage '
                      'matches seven-slot layout, null/repeated handles and word wrapping. '
                      'Caller supplies original row height and stable mutable resolution. '
                      'Complete42ac40 also matches timer-driven movement, all four piece child virtual '
                      'updates, mode-dependent effects and layout. '
                      'Complete42af80 also matches handle rotation and final callback assignments. '
                      'Other child callback classes, movement scheduling and full game remain unfinished.'}
    (build/'piece-actor-layout-verification.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report,indent=2))


if __name__ == '__main__':
    main()
