"""Full original4ade60 chain drawing comparison, using VF sprite fixtures."""
import ctypes as c
import random
import struct
from original import RETURN
from verify_render_geometry import Clip
from verify_sprite_clone import Frame, Image
from verify_render_rectangle import Surface
from verify_render_preparation import Preparation
from verify_ui_sprite_vf import Bank as SpriteBank
from verify_object_append import List
from unicorn.x86_const import UC_X86_REG_EIP

Resolve = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p),
                     c.POINTER(c.c_size_t), c.c_void_p)


def verify(native, original, samples, weights, tables):
    native.vertrix_sprite_chain_draw32.argtypes = [c.c_uint32, Resolve, c.c_void_p,
        c.POINTER(SpriteBank), c.POINTER(Surface), Clip, c.c_void_p, c.c_void_p,
        c.c_void_p, c.POINTER(Preparation), c.c_size_t, c.POINTER(c.c_size_t)]
    original.cpu.mem_map(0xb00000, 0x20000)
    frames = (Frame * len(samples))()
    backing = []
    for index, (width, height, raw, metadata) in enumerate(samples):
        pixels = (c.c_ubyte * len(raw)).from_buffer_copy(raw)
        backing.append(pixels)
        frames[index] = Frame(Image(width, height, pixels), len(samples),
                              (c.c_uint32 * 10)(*metadata))
        frames[index].metadata[0] = 0xb00000 + index * 4096
        original.cpu.mem_write(frames[index].metadata[0], bytes(raw))
        original.cpu.mem_write(0xb10000 + index * 40, bytes(frames[index].metadata))
    sprites = SpriteBank(frames, len(samples))
    original.cpu.mem_write(0x803000, struct.pack('<' + 'I' * len(samples),
        *[0xb10000 + i * 40 for i in range(len(samples))]))
    original.cpu.mem_write(0x5449fc, struct.pack('<6I', 0x803000, len(samples), 0, 0, 0, 0))
    target = bytearray(40)
    struct.pack_into('<3I', target, 0, 0x808000, 64, 64)
    target[12:14] = bytes((4, 4))
    struct.pack_into('<I', target, 20, 256)
    original.cpu.mem_write(0x802000, bytes(target))
    actors = {}
    visited = []
    @Resolve
    def resolve(handle, storage, size, context):
        visited.append(handle)
        if handle not in actors:
            return 0
        storage[0], size[0] = c.addressof(actors[handle]), len(actors[handle])
        return 1
    rng = random.Random(0x4ade60)
    nested_rng = random.Random(0x42b290)
    total = 0
    nested_total = 0
    from verify_actor_render_draw import BankBinding, BankMap
    binding = BankBinding(0x5449fc,c.pointer(sprites))
    bank_map = BankMap(c.pointer(binding),1)
    native.vertrix_ui_player_preview_draw32.argtypes = [c.c_void_p,c.c_size_t,Resolve,c.c_void_p,
        c.POINTER(BankMap),c.POINTER(Surface),Clip,c.c_void_p,c.c_void_p,c.c_void_p,
        c.POINTER(Preparation),c.c_size_t,c.POINTER(c.c_size_t)]
    for case in range(512):
        count = rng.randrange(13)
        actors.clear()
        selected = {}
        for index in range(count):
            handle = 0x800000 + index * 0x200
            actor = bytearray(0x15c)
            frame = rng.randrange(len(samples))
            selected[handle] = frame
            struct.pack_into('<H', actor, 14, rng.randrange(15, 45))
            struct.pack_into('<H', actor, 22, rng.randrange(15, 45))
            actor[0x44], actor[0x4e], actor[0x52], actor[0x8e] = rng.choice((8, 16)), 100, 13, 1
            if case % 2:
                actor[0x4e], actor[0x93], actor[0x95] = rng.choice((25, 50, 75)), 1, 0
            struct.pack_into('<3I', actor, 0xb0, 0x5449fc, 0xdeadbeef, frame)
            struct.pack_into('<I', actor, 0x108,
                             handle + 0x200 if index + 1 < count else 0)
            struct.pack_into('<I', actor, 0x134, frames[frame].metadata[0])
            struct.pack_into('<I', actor, 0x13c, 1)
            struct.pack_into('<I', actor, 0x144, 1)
            struct.pack_into('<I', actor, 0x150, rng.randrange(2))
            struct.pack_into('<I', actor, 0x158, 0x517af4)
            original.cpu.mem_write(handle, bytes(actor))
            actors[handle] = c.create_string_buffer(bytes(actor), len(actor))
        initial = rng.randbytes(16384)
        original.cpu.mem_write(0x808000, initial)
        original.call(0x4ade60, eax=0x800000 if count else 0, edx=0x802000)
        if original.cpu.reg_read(UC_X86_REG_EIP) != RETURN:
            original.cpu.emu_start(original.cpu.reg_read(UC_X86_REG_EIP), RETURN, count=100000000)
        assert original.cpu.reg_read(UC_X86_REG_EIP) == RETURN
        expected = bytes(original.cpu.mem_read(0x808000, len(initial)))
        destination = c.create_string_buffer(initial, len(initial))
        surface = Surface(c.addressof(destination), len(initial), 64, 64, 256, 4)
        prepared = Preparation()
        prepared.source_weights = c.addressof(weights.bytes[50])
        prepared.destination_weights = c.addressof(weights.bytes[50])
        prepared.source_words = c.addressof(weights.words[50])
        prepared.destination_words = c.addressof(weights.words[50])
        completed = c.c_size_t(999)
        visited.clear()
        assert native.vertrix_sprite_chain_draw32(0x800000 if count else 0, resolve, None,
            c.byref(sprites), c.byref(surface), Clip(0, 63, 0, 63), c.byref(weights), None,
            c.byref(tables), c.byref(prepared), 12, c.byref(completed)) == 1
        assert completed.value == count and visited == list(actors), case
        assert bytes(destination) == expected, ('chain pixels', case)
        for handle, storage in actors.items():
            expected_actor = bytearray(original.cpu.mem_read(handle, len(storage)))
            struct.pack_into('<I', expected_actor, 0xb4, selected[handle])
            assert bytes(storage) == bytes(expected_actor), ('chain actor', case, handle)
        total += count
        parent_raw = bytearray(nested_rng.randbytes(0x180))
        struct.pack_into('<I',parent_raw,0x158,0x514814)
        roots = [nested_rng.choice([0,*actors]) for _ in range(6)]
        struct.pack_into('<6I',parent_raw,0x15c,*roots)
        parent = c.create_string_buffer(bytes(parent_raw),len(parent_raw))
        original.cpu.mem_write(0x807000,bytes(parent_raw))
        original.cpu.mem_write(0x808000,initial)
        original.call(0x42b290,eax=0x807000,edx=0x802000)
        destination = c.create_string_buffer(initial,len(initial))
        surface.data = c.addressof(destination)
        visited.clear()
        expected_visits = []
        handles = list(actors)
        for root in roots:
            if root:
                expected_visits.extend(handles[handles.index(root):])
        assert native.vertrix_ui_player_preview_draw32(parent,len(parent_raw),resolve,None,
            c.byref(bank_map),c.byref(surface),Clip(0,63,0,63),c.byref(weights),None,
            c.byref(tables),c.byref(prepared),128,c.byref(completed))
        assert visited == expected_visits and completed.value == len(expected_visits),case
        assert bytes(destination) == bytes(original.cpu.mem_read(0x808000,len(initial))),case
        assert parent.raw == bytes(original.cpu.mem_read(0x807000,len(parent_raw))),case
        for handle,storage in actors.items():
            expected_actor = bytearray(original.cpu.mem_read(handle,len(storage)))
            struct.pack_into('<I',expected_actor,0xb4,selected[handle])
            assert storage.raw == bytes(expected_actor),(case,handle)
        nested_total += completed.value
#A cyclic chain must stop at the supplied budget, preserving completed draws.
    handle = next(iter(actors))
    native.vertrix_actor_storage_write(actors[handle], len(actors[handle]), 0x108, 4, handle)
    for _ in range(3):
        original.call(0x4ac8a0, eax=handle)
        original.call(0x4af8c0, eax=handle, edx=0x802000)
    visited.clear()
    assert native.vertrix_sprite_chain_draw32(handle, resolve, None, c.byref(sprites),
        c.byref(surface), Clip(0, 63, 0, 63), c.byref(weights), None, c.byref(tables),
        c.byref(prepared), 3, c.byref(completed)) == 0
    assert visited == [handle] * 3 and completed.value == 3
    assert bytes(destination) == bytes(original.cpu.mem_read(0x808000, len(initial)))
    native.vertrix_actor_storage_write(actors[handle], len(actors[handle]), 0x108, 4, 0xdeadbeef)
    original.call(0x4ac8a0, eax=handle)
    original.call(0x4af8c0, eax=handle, edx=0x802000)
    visited.clear()
    assert native.vertrix_sprite_chain_draw32(handle, resolve, None, c.byref(sprites),
        c.byref(surface), Clip(0, 63, 0, 63), c.byref(weights), None, c.byref(tables),
        c.byref(prepared), 12, c.byref(completed)) == 0
    assert visited == [handle, 0xdeadbeef] and completed.value == 1
    assert bytes(destination) == bytes(original.cpu.mem_read(0x808000, len(initial)))
    visited.clear()
    assert native.vertrix_sprite_chain_draw32(0, resolve, None, None, None,
        Clip(0, 0, 0, 0), None, None, None, None, 0, c.byref(completed)) == 1
    assert not visited and completed.value == 0
    for index, sample in enumerate(samples):
        assert bytes(backing[index]) == sample[2]
    scene_report = verify_scenes(native, original, frames, sprites, actors, resolve, visited,
                                weights, tables)
    from verify_ui_scene_render import verify as verify_animated
    animated_report = verify_animated(native, original, frames, sprites, actors, resolve,
                                      weights, tables)
    return {'complete_original_chain_cases': 512, 'chain_actors_checked': total,
            'complete_original_preview_parent_draw_cases':512,
            'nested_preview_actor_draws':nested_total,
            'preview_parent_scope':'Complete original42b290 without drawing hooks. '
                'VF pixels, parent/actor storage and nested companion-before-border '
                'visitation match with null/repeated roots and linked draw chains. '
                'Full player scene dispatch and gameplay remain unfinished.',
            'cyclic_chain_budget_cases': 1,
            'unresolved_next_after_completed_draw_cases': 1,
            'null_chain_without_destination_cases': 1,
            'chain_scope': 'Complete original4ade60 including real VF bank lookup, geometry '
                          'and drawing. Chains0..12, overlapping sprites, copy/fade, '
                          'scale8/16 and alpha override. No drawing hooks.',
            **scene_report, **animated_report}


def verify_scenes(native, original, frames, sprites, actors, resolve, visited, weights, tables):
    native.vertrix_sprite_scene_draw32.argtypes = [c.POINTER(List), Resolve, c.c_void_p,
        c.POINTER(SpriteBank), c.POINTER(Surface), Clip, c.c_void_p, c.c_void_p,
        c.c_void_p, c.POINTER(Preparation), c.c_size_t, c.POINTER(c.c_size_t)]
    rng = random.Random(0x4b6240)
    roots = 0
    for case in range(256):
        actors.clear()
        count = rng.randrange(13)
        positions = {}
        selected = {}
        next_handles = {}
        for index in range(count):
            handle = 0x800000 + index * 512
            actor = bytearray(0x15c)
            frame = rng.randrange(len(frames))
            y = rng.choice((-32768, -10, 16, 24, 24, 32, 32000, 32767))
            selected[handle], positions[handle] = frame, y
            struct.pack_into('<H', actor, 14, rng.randrange(16, 41))
            struct.pack_into('<H', actor, 22, y & 65535)
            actor[0x44], actor[0x4e], actor[0x52], actor[0x8e] = rng.choice((8, 16)), 100, 13, 1
            if rng.randrange(2):
                actor[0x4e], actor[0x93] = rng.choice((25, 50, 75)), 1
            struct.pack_into('<3I', actor, 0xb0, 0x5449fc, 0xdeadbeef, frame)
            next_handle = handle + 512 if index + 1 < count and rng.randrange(2) else 0
            next_handles[handle] = next_handle
            struct.pack_into('<I', actor, 0x108, next_handle)
            struct.pack_into('<I', actor, 0x134, frames[frame].metadata[0])
            struct.pack_into('<I', actor, 0x13c, 1)
            struct.pack_into('<I', actor, 0x144, 1)
            struct.pack_into('<I', actor, 0x150, rng.randrange(2))
            struct.pack_into('<I', actor, 0x158, 0x517af4)
            actors[handle] = c.create_string_buffer(bytes(actor), len(actor))
            original.cpu.mem_write(handle, bytes(actor))
        handles = list(actors)
        rng.shuffle(handles)
        if count and case % 3 == 0:
            handles.append(rng.choice(handles))
        initial = rng.randbytes(16384)
        original.cpu.mem_write(0x808000, initial)
        original.cpu.mem_write(0x806000, struct.pack('<4I', 0, 0x806100, len(handles), len(handles)))
        if handles:
            original.cpu.mem_write(0x806100, struct.pack('<' + 'I' * len(handles), *handles))
        original.call(0x4b6240, eax=0x806000, edx=0x802000)
        if original.cpu.reg_read(UC_X86_REG_EIP) != RETURN:
            original.cpu.emu_start(original.cpu.reg_read(UC_X86_REG_EIP), RETURN, count=100000000)
        assert original.cpu.reg_read(UC_X86_REG_EIP) == RETURN
        destination = c.create_string_buffer(initial, len(initial))
        surface = Surface(c.addressof(destination), len(initial), 64, 64, 256, 4)
        items = (c.c_uint32 * len(handles))(*handles)
        scene = List(items, len(handles), len(handles))
        prepared = Preparation()
        prepared.source_weights = c.addressof(weights.bytes[50])
        prepared.destination_weights = c.addressof(weights.bytes[50])
        prepared.source_words = c.addressof(weights.words[50])
        prepared.destination_words = c.addressof(weights.words[50])
        completed = c.c_size_t(999)
        visited.clear()
        assert native.vertrix_sprite_scene_draw32(c.byref(scene), resolve, None,
            c.byref(sprites), c.byref(surface), Clip(0, 63, 0, 63), c.byref(weights), None,
            c.byref(tables), c.byref(prepared), 12, c.byref(completed)) == 1
        ordered = sorted((h for h in handles if positions[h] < 32000), key=positions.get)
        expected_visits = list(handles)
        for head in ordered:
            while head:
                expected_visits.append(head)
                head = next_handles[head]
        assert visited == expected_visits and completed.value == len(ordered), ('scene order', case)
        assert bytes(destination) == bytes(original.cpu.mem_read(0x808000, 16384)), ('scene pixels', case)
        for handle, storage in actors.items():
            expected_actor = bytearray(original.cpu.mem_read(handle, len(storage)))
            descriptor = struct.unpack_from('<I', expected_actor, 0xb4)[0]
            if descriptor != 0xdeadbeef:
                struct.pack_into('<I', expected_actor, 0xb4, selected[handle])
            assert bytes(storage) == bytes(expected_actor), ('scene actor', case, handle)
        roots += len(ordered)
    empty = List(None, 0, 0)
    visited.clear()
    assert native.vertrix_sprite_scene_draw32(c.byref(empty), resolve, None, None, None,
        Clip(0, 0, 0, 0), None, None, None, None, 0, c.byref(completed)) == 1
    assert not visited and completed.value == 0
    invalid = List(items, 1025, 1025)
    before = bytes(destination), bytes(prepared)
    assert native.vertrix_sprite_scene_draw32(c.byref(invalid), resolve, None,
        c.byref(sprites), c.byref(surface), Clip(0, 63, 0, 63), c.byref(weights), None,
        c.byref(tables), c.byref(prepared), 12, c.byref(completed)) == 0
    assert not visited and completed.value == 0
    assert (bytes(destination), bytes(prepared)) == before
    assert actors
    handle = next(iter(actors))
    native.vertrix_actor_storage_write(actors[handle], len(actors[handle]), 0x16, 2, 24)
    native.vertrix_actor_storage_write(actors[handle], len(actors[handle]), 0x158, 4, 0)
    root = (c.c_uint32 * 1)(handle)
    unsupported = List(root, 1, 1)
    before_actor = bytes(actors[handle])
    assert native.vertrix_sprite_scene_draw32(c.byref(unsupported), resolve, None,
        c.byref(sprites), c.byref(surface), Clip(0, 63, 0, 63), c.byref(weights), None,
        c.byref(tables), c.byref(prepared), 12, c.byref(completed)) == 0
    assert completed.value == 0 and bytes(actors[handle]) == before_actor
    assert (bytes(destination), bytes(prepared)) == before
    return {'complete_original_sorted_scene_cases': 256, 'scene_roots_drawn': roots,
            'empty_scene_without_destination_cases': 1,
            'oversized_scene_preservation_cases': 1, 'unsupported_scene_class_preservation_cases': 1,
            'scene_scope': 'Complete original4b6240 executes base-class virtual draw '
                           'through4ae140 and4ade60, including real VF pixels. Signed Y, '
                           'equal-Y stability, duplicate roots, sentinel exclusion and linked '
                           'companions covered. No drawing hooks.'}
