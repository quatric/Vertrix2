"""Compare consecutive recovered update/draw frames with complete originals."""
import ctypes as c
import random
import struct
from original import RETURN
from verify_frame_resource import Resource
from verify_object_append import List
from verify_render_geometry import Clip
from verify_render_preparation import Preparation
from verify_render_rectangle import Surface
from verify_ui_sprite_vf import Bank as SpriteBank
from unicorn.x86_const import UC_X86_REG_EIP


class Options(c.Structure):
    _fields_ = [('clear', c.c_int), ('start_y', c.c_int16), ('elapsed', c.c_uint32),
                ('refresh', c.POINTER(c.c_uint32)), ('refresh_count', c.c_size_t),
                ('one', c.POINTER(Resource)), ('other', c.POINTER(Resource)),
                ('budget', c.c_size_t)]


def verify(native, original, frames, sprites, actors, resolve, weights, tables):
    from verify_sprite_chain_draw import Resolve
    from verify_actor_render_draw import BankBinding, BankMap
    from verify_sprite_clone import Frame
    native.vertrix_ui_scene_frame_render.argtypes = [c.POINTER(List), Resolve, c.c_void_p,
        c.POINTER(Options), c.POINTER(SpriteBank), c.POINTER(Surface), Clip, c.c_void_p,
        c.c_void_p, c.c_void_p, c.POINTER(Preparation), c.c_size_t, c.POINTER(c.c_size_t)]
    native.vertrix_ui_scene_frame_render_mapped.argtypes = [c.POINTER(List), Resolve, c.c_void_p,
        c.POINTER(Options), c.POINTER(BankMap), *native.vertrix_ui_scene_frame_render.argtypes[5:]]
    handlers = [0, 0x450860, 0x4508c0, 0x450920, 0x450960, 0x4509a0, 0x4509d0]
    alternating = [0x450a10, 0x450aa0, 0x450b30, 0x450b90, 0x450bf0, 0x450c70]
    reversed_frames = (Frame * len(frames))(*reversed(frames))
    rotated_frames = (Frame * len(frames))(*list(frames)[1:], frames[0])
    banks = [sprites, SpriteBank(reversed_frames, len(frames)), SpriteBank(rotated_frames, len(frames))]
    tokens = (0x5449fc, 0x546618, 0x546634)
    bindings = (BankBinding * 3)(*[BankBinding(t, c.pointer(b)) for t, b in zip(tokens, banks)])
    bank_map = BankMap(bindings, 3)
    for bank_index, token in enumerate(tokens):
        order = list(range(len(frames)))
        if bank_index == 1:
            order.reverse()
        elif bank_index == 2:
            order = order[1:] + order[:1]
        original.cpu.mem_write(0x803000 + bank_index * 256,
            struct.pack('<' + 'I' * len(order), *[0xb10000 + i * 40 for i in order]))
        original.cpu.mem_write(token,
            struct.pack('<6I', 0x803000 + bank_index * 256, len(order), 0, 0, 0, 0))
    descriptors = (c.c_uint32 * len(frames))(*range(len(frames)))
    resources = [Resource(0, len(frames), descriptors, None, None),
                 Resource(0, len(frames), descriptors, None, None)]
    rng = random.Random(0x4b62004b6240)
    updates = roots = 0
#Six refresh words precede the renderer's kernel pointer at0x5bb72c.
    refresh = (c.c_uint32 * 6)()
    mapped_updates = mapped_roots = switches = 0
    for scene_case in range(128):
        mapped = scene_case >= 64
        actors.clear()
        count = rng.randrange(1, 13)
        selected = {}
        for index in range(count):
            handle = 0x800000 + index * 512
            frame = rng.randrange(len(frames))
            selected[handle] = frame
            actor = bytearray(0x15c)
            struct.pack_into('<2I', actor, 0, rng.randrange(4), rng.randrange(4))
            struct.pack_into('<H', actor, 10, rng.randrange(16, 41))
            struct.pack_into('<H', actor, 14, rng.randrange(16, 41))
            struct.pack_into('<3H', actor, 22, rng.randrange(16, 41), rng.randrange(16, 41), 1)
            actor[0x44], actor[0x4e], actor[0x52], actor[0x8e] = rng.choice((8, 16)), 100, 13, 1
            struct.pack_into('<I', actor, 0x58, rng.randrange(13))
            struct.pack_into('<I', actor, 0x64, rng.randrange(13))
            handler = rng.choice(handlers + alternating if mapped else handlers)
            token = rng.choice(tokens[1:] if handler in alternating else tokens) if mapped else tokens[0]
            struct.pack_into('<3I', actor, 0xb0, token, 0xdeadbeef, frame)
            if handler in alternating:
                struct.pack_into('<3h', actor, 0x48, rng.randrange(-40, 6), 5, 1)
                struct.pack_into('<3I', actor, 0x70, 0, 1, 1)
                struct.pack_into('<I', actor, 0x7c, rng.randrange(2))
                struct.pack_into('<2I', actor, 0xcc, 0, 10)
            for offset in (0xbc, 0xdc):
                struct.pack_into('<2I', actor, offset, rng.randrange(101), rng.choice((1, 10, 50)))
            struct.pack_into('<I', actor, 0x120, rng.randrange(2))
            struct.pack_into('<I', actor, 0x134, rng.randrange(2))
            struct.pack_into('<I', actor, 0x13c, 1)
            struct.pack_into('<I', actor, 0x144, 1)
            struct.pack_into('<h', actor, 0x148, rng.choice((-1, 0, 1, 5)))
            struct.pack_into('<I', actor, 0x150, rng.randrange(2))
            struct.pack_into('<2I', actor, 0x154, handler, 0x517af4)
            actors[handle] = c.create_string_buffer(bytes(actor), len(actor))
            original.cpu.mem_write(handle, bytes(actor))
        handles = list(actors)
        rng.shuffle(handles)
        items = (c.c_uint32 * count)(*handles)
        listed = List(items, count, count)
        original.cpu.mem_write(0x806000, struct.pack('<4I', 0, 0x806100, count, count))
        original.cpu.mem_write(0x806100, bytes(items))
        original.cpu.mem_write(0x54671c, struct.pack('<3I', 0, 0x806100, count))
        for index in range(6):
            refresh[index] = rng.getrandbits(32)
        original.cpu.mem_write(0x5bb714, bytes(refresh))
        prepared = Preparation()
        prepared.source_weights = c.addressof(weights.bytes[50])
        prepared.destination_weights = c.addressof(weights.bytes[50])
        prepared.source_words = c.addressof(weights.words[50])
        prepared.destination_words = c.addressof(weights.words[50])
        for frame_index in range(8):
            options = Options(frame_index % 2, rng.randrange(-10, 21), rng.randrange(101),
                              refresh, 6, c.pointer(resources[0]) if mapped else None,
                              c.pointer(resources[1]) if mapped else None, 1)
            original.cpu.mem_write(0x5bb710, struct.pack('<I', options.clear))
            original.cpu.mem_write(0x533d78, struct.pack('<h', options.start_y))
            original.cpu.mem_write(0x5bd834, struct.pack('<I', options.elapsed))
            initial = rng.randbytes(16384)
            original.cpu.mem_write(0x808000, initial)
            original.call(0x4b6200, eax=0x806000)
            assert original.cpu.reg_read(UC_X86_REG_EIP) == RETURN
            original.call(0x4b6240, eax=0x806000, edx=0x802000)
            if original.cpu.reg_read(UC_X86_REG_EIP) != RETURN:
                original.cpu.emu_start(original.cpu.reg_read(UC_X86_REG_EIP), RETURN, count=100000000)
            assert original.cpu.reg_read(UC_X86_REG_EIP) == RETURN
            destination = c.create_string_buffer(initial, len(initial))
            surface = Surface(c.addressof(destination), len(initial), 64, 64, 256, 4)
            completed = c.c_size_t(999)
            previous_tokens = {h: struct.unpack_from('<I', bytes(s), 0xb0)[0] for h, s in actors.items()}
            render = (native.vertrix_ui_scene_frame_render_mapped if mapped else
                      native.vertrix_ui_scene_frame_render)
            assert render(c.byref(listed), resolve, None,
                c.byref(options), c.byref(bank_map) if mapped else c.byref(sprites), c.byref(surface), Clip(0, 63, 0, 63),
                c.byref(weights), None, c.byref(tables), c.byref(prepared), 12,
                c.byref(completed)) == 1
            assert completed.value == count
            assert bytes(destination) == bytes(original.cpu.mem_read(0x808000, 16384)), (
                'animated frame pixels', scene_case, frame_index)
            assert bytes(refresh) == bytes(original.cpu.mem_read(0x5bb714, 24)), (
                'animated frame refresh', scene_case, frame_index)
            for handle, storage in actors.items():
                expected = bytearray(original.cpu.mem_read(handle, len(storage)))
                struct.pack_into('<I', expected, 0xb4, struct.unpack_from('<I', expected, 0xb8)[0])
                assert bytes(storage) == bytes(expected), ('animated frame actor', scene_case,
                                                         frame_index, handle)
                switches += previous_tokens[handle] != struct.unpack_from('<I', bytes(storage), 0xb0)[0]
            assert bytes(items) == bytes(original.cpu.mem_read(0x806100, count * 4))
            updates += count
            roots += completed.value
            if mapped:
                mapped_updates += count
                mapped_roots += completed.value
    native.vertrix_sprite_chain_draw_mapped32.argtypes = [c.c_uint32, Resolve, c.c_void_p,
        c.POINTER(BankMap), c.POINTER(Surface), Clip, c.c_void_p, c.c_void_p,
        c.c_void_p, c.POINTER(Preparation), c.c_size_t, c.POINTER(c.c_size_t)]
    for chain_case in range(64):
        rng.shuffle(handles)
        for index, handle in enumerate(handles):
            next_handle = handles[index + 1] if index + 1 < len(handles) else 0
            token = tokens[(chain_case + index) % 3]
            for offset, width, value in ((0x108, 4, next_handle), (0xb0, 4, token),
                                         (0x134, 4, 1), (0xe, 2, 22 + index), (0x16, 2, 22 + index)):
                native.vertrix_actor_storage_write(actors[handle], len(actors[handle]), offset, width, value)
                original.cpu.mem_write(handle + offset, value.to_bytes(width, 'little'))
        initial = rng.randbytes(16384)
        original.cpu.mem_write(0x808000, initial)
        original.call(0x4ade60, eax=handles[0], edx=0x802000)
        if original.cpu.reg_read(UC_X86_REG_EIP) != RETURN:
            original.cpu.emu_start(original.cpu.reg_read(UC_X86_REG_EIP), RETURN, count=100000000)
        assert original.cpu.reg_read(UC_X86_REG_EIP) == RETURN
        chain_destination = c.create_string_buffer(initial, len(initial))
        chain_surface = Surface(c.addressof(chain_destination), len(initial), 64, 64, 256, 4)
        assert native.vertrix_sprite_chain_draw_mapped32(handles[0], resolve, None,
            c.byref(bank_map), c.byref(chain_surface), Clip(0, 63, 0, 63), c.byref(weights),
            None, c.byref(tables), c.byref(prepared), 12, c.byref(completed)) == 1
        assert completed.value == len(handles)
        assert bytes(chain_destination) == bytes(original.cpu.mem_read(0x808000, 16384))
        for handle, storage in actors.items():
            expected = bytearray(original.cpu.mem_read(handle, len(storage)))
            struct.pack_into('<I', expected, 0xb4, struct.unpack_from('<I', expected, 0xb8)[0])
            assert bytes(storage) == bytes(expected), ('mixed bank chain actor', chain_case, handle)
#Restore independent roots for the update failure checks.
    for handle in handles:
        native.vertrix_actor_storage_write(actors[handle], len(actors[handle]), 0x108, 4, 0)
        original.cpu.mem_write(handle + 0x108, bytes(4))
#Alternating handlers require either of their two animation resources.
        native.vertrix_actor_storage_write(actors[handle], len(actors[handle]), 0xb0, 4, 0x546618)
        original.cpu.mem_write(handle + 0xb0, struct.pack('<I', 0x546618))
#Drawing failure must retain the updates that completed before it.
    options = Options(1, 0, 100, refresh, 6, c.pointer(resources[0]), c.pointer(resources[1]), 1)
    original.cpu.mem_write(0x5bb710, struct.pack('<I', options.clear))
    original.cpu.mem_write(0x533d78, struct.pack('<h', options.start_y))
    original.cpu.mem_write(0x5bd834, struct.pack('<I', options.elapsed))
    original.call(0x4b6200, eax=0x806000)
    before_destination = bytes(destination)
    assert native.vertrix_ui_scene_frame_render_mapped(c.byref(listed), resolve, None,
        c.byref(options), c.byref(bank_map), None, Clip(0, 63, 0, 63), c.byref(weights),
        None, c.byref(tables), c.byref(prepared), 12, c.byref(completed)) == 0
    assert completed.value == 0 and bytes(destination) == before_destination
    assert bytes(refresh) == bytes(original.cpu.mem_read(0x5bb714, 24))
    for handle, storage in actors.items():
        expected = bytearray(original.cpu.mem_read(handle, len(storage)))
        struct.pack_into('<I', expected, 0xb4, struct.unpack_from('<I', expected, 0xb8)[0])
        assert bytes(storage) == bytes(expected), ('update retained after draw failure', handle)
#An unsupported first update must prevent drawing and preserve its storage.
    handle = items[0]
    native.vertrix_actor_storage_write(actors[handle], len(actors[handle]), 0x154, 4, 0xdeadbeef)
    before = {h: bytes(s) for h, s in actors.items()}, bytes(refresh), bytes(prepared)
    assert native.vertrix_ui_scene_frame_render_mapped(c.byref(listed), resolve, None,
        c.byref(options), c.byref(bank_map), c.byref(surface), Clip(0, 63, 0, 63),
        c.byref(weights), None, c.byref(tables), c.byref(prepared), 12,
        c.byref(completed)) == 0
    assert completed.value == 0 and bytes(destination) == before_destination
    assert ({
h: bytes(s) for h, s in actors.items()}, bytes(refresh), bytes(prepared)) == before
    return {'complete_update_then_draw_frames': 1024, 'consecutive_frames_per_scene': 8,
            'animated_scene_count': 128, 'animated_actor_updates': updates,
            'animated_root_draws': roots,
            'mapped_consecutive_frames': 512, 'mapped_actor_updates': mapped_updates,
            'mapped_root_draws': mapped_roots, 'verified_resource_bank_switches': switches,
            'mixed_resource_bank_chain_cases': 64,
            'draw_failure_after_complete_updates_cases': 1,
            'update_failure_prevents_drawing_cases': 1,
            'animated_scope': 'Real original4b6200 then4b6240 across persistent consecutive '
                              'actor states. Distinct reordered VF sprite banks, all twelve interface handlers plus '
                              'idle, linked identity lookup, timers, refresh flags, visibility, '
                              'scaling and sorted drawing with actual bank switches. No update/draw hooks. '
                              'Final asset-bank construction, child update chains and full application unfinished.'}
