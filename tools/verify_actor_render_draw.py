"""Compare actor preparation followed by real original sprite drawing."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from verify_render_geometry import Clip
from verify_sprite_clone import Frame, Image
from verify_render_rectangle import Surface
from verify_render_preparation import Preparation
from verify_render_weights import Weights
from verify_palette_tables import Tables
from verify_render_color_bank import Bank
from verify_render_dispatch import FlagState
from verify_ui_sprite_vf import Bank as SpriteBank


class BankBinding(c.Structure):
    _fields_ = [('resource', c.c_uint32), ('sprites', c.POINTER(SpriteBank))]


class BankMap(c.Structure):
    _fields_ = [('bindings', c.POINTER(BankBinding)), ('count', c.c_size_t)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--archive', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'actor-render-draw.dylib'
    names = ('actor_render_draw', 'actor_render_geometry', 'actor_render_style', 'actor_image_bounds', 'actor_image_clip', 'actor_storage', 'render_geometry', 'surface', 'render_dispatch', 'render_row', 'render_pixel', 'render_preparation', 'render_color', 'palette_map', 'palette_tables', 'palette_color', 'render_palette', 'render_weights', 'image', 'vf', 'sprite_actor_image', 'sprite_actor_draw', 'sprite_chain_draw', 'sprite_scene_draw', 'ui_scene_render', 'ui_scene_frame', 'ui_actor_frame', 'ui_actor_update', 'ui_companion_update', 'actor_lookup', 'object_list', 'linked_movement', 'linked_alternating', 'block_resource', 'frame_resource', 'animation', 'timer', 'word_transition', 'dword_transition', 'ui_player_preview_draw', 'ui_indicator_update', 'linked_indicator', 'byte_transition', 'ui_border_update', 'linked_burst', 'random')
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-ffp-contract=off', '-Wall', '-Wextra', '-Werror', * [str(source / (name + '.c')) for name in names], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_actor_render_draw32.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(Frame), c.POINTER(Surface), Clip, c.c_void_p, c.c_void_p, c.c_void_p, c.POINTER(Preparation)]
    native.vertrix_sprite_actor_draw32.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(SpriteBank), c.POINTER(Surface), Clip, c.c_void_p, c.c_void_p, c.c_void_p, c.POINTER(Preparation)]
    native.vertrix_sprite_actor_draw_resource32.argtypes = [c.c_void_p, c.c_size_t, c.c_uint32, * native.vertrix_sprite_actor_draw32.argtypes[2:]]
    native.vertrix_sprite_actor_draw_mapped32.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(BankMap), * native.vertrix_sprite_actor_draw32.argtypes[3:]]
    native.vertrix_render_flags.argtypes = [FlagState, c.c_uint32]
    native.vertrix_render_flags.restype = c.c_uint32
    native.vertrix_vf_open.argtypes = [c.c_char_p]
    native.vertrix_vf_open.restype = c.c_void_p
    native.vertrix_vf_close.argtypes = [c.c_void_p]
    native.vertrix_image_sprite_processed.argtypes = [c.c_void_p, c.c_char_p, c.c_uint32, c.POINTER(c.c_uint32), c.POINTER(Frame)]
    native.vertrix_sprite_free.argtypes = [c.POINTER(Frame)]
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    masks = (c.c_uint32 * 3)(0xff0000, 0xff00, 0xff)
    samples = []
    for index in range(30):
        loaded = Frame()
        assert native.vertrix_image_sprite_processed(archive, b'sprite/damier.spr', index, masks, c.byref(loaded))
        if loaded.image.width <= 32 and loaded.image.height <= 32:
            samples.append((loaded.image.width, loaded.image.height, c.string_at(loaded.image.rgba, loaded.image.width * loaded.image.height * 4), tuple(loaded.metadata)))
        native.vertrix_sprite_free(c.byref(loaded))
    native.vertrix_vf_close(archive)
    assert samples
    weights = Weights()
    assert native.vertrix_render_weights_build(c.byref(weights))
    tables = Tables()
    native.vertrix_palette_tables_build.argtypes = [c.POINTER(Tables)]
    native.vertrix_palette_tables_free.argtypes = [c.POINTER(Tables)]
    assert native.vertrix_palette_tables_build(c.byref(tables))
    original = Original(args.executable)
    original.call(0x4b9050)
    original.cpu.mem_map(0x900000, 0x100000)
    original.cpu.mem_write(0x900000, struct.pack('<262144I', * tables.lookup[: 262144]))
    original.cpu.mem_map(0xa00000, 0x40000)
    original.cpu.mem_write(0xa00000, bytes(tables.hue[: 262144]))
    original.cpu.mem_write(0x5468b0, bytes(tables.channels))
    original.cpu.mem_write(0x558cf0, bytes(weights.bytes))
    original.cpu.mem_write(0x55f1f8, bytes(weights.words))
    original.cpu.mem_write(0x588600, bytes(weights.inverse_alpha))
    original.call(0x475400, stop=0x475443)
    original.cpu.mem_write(0x54b800, struct.pack('<2I', 0x900000, 0xa00000))
    original.cpu.mem_write(0x54c1d4, bytes(765 * 4))
    original.cpu.mem_write(0x54c1d4, struct.pack('<255I', * tables.auxiliary))
    original.cpu.mem_write(0x54c9cc, struct.pack('<255I', * ([100] * 255)))
    original.cpu.mem_write(0x54d1d0, struct.pack('<256I', 0x54c9cc, * [0x54c1d4 + i * 4 for i in range(255)]))
    rng = random.Random(0x4ae3e04af560)
    visible = 0
    effects = {}
    unsupported = 0
    overlapping_strides = 0
    truncated_targets = 0
    for case in range(8192):
        width, height = rng.randrange(1, 33), rng.randrange(1, 33)
        raw = bytearray(rng.randbytes(width * height * 4))
        for offset in range(3, len(raw), 4):
            raw[offset] = rng.choice((0, 255, rng.randrange(256)))
        pixels = (c.c_ubyte * len(raw)).from_buffer_copy(raw)
        frame = Frame(Image(width, height, pixels), 1)
        frame.metadata[0: 5] = [0x804000, width, height, rng.randrange(- 5, 6) & 65535, rng.randrange(- 5, 6) & 65535]
        frame.metadata[9] = (4 << 24) | (rng.randrange(2) << 16)
        if case >= 2048:
            width, height, raw, metadata = samples[case % len(samples)]
            pixels = (c.c_ubyte * len(raw)).from_buffer_copy(raw)
            frame = Frame(Image(width, height, pixels), 1, (c.c_uint32 * 10)(* metadata))
            frame.metadata[0] = 0x804000
            actor = bytearray(0x15c)
            struct.pack_into('<H', actor, 0xe, rng.randrange(- 20, 71) & 65535)
            struct.pack_into('<H', actor, 0x16, rng.randrange(- 20, 71) & 65535)
            struct.pack_into('<H', actor, 0x1e, rng.randrange(- 5, 6) & 65535)
            actor[0x44], actor[0x4e], actor[0x52], actor[0x8e] = rng.randrange(1, 17), 100, 13, 1
            if case >= 4096:
                actor[0x4e] = rng.choice((0, 25, 50, 75, 100))
            actor[0x52] = rng.choice((13, rng.randrange(13)))
            actor[0x8c], actor[0x93] = rng.randrange(2), 1
            actor[0x94] = rng.randrange(3)
            actor[0x95] = rng.choice((0, 1, 3, 4, 5, 6, 7, 8))
            actor[0x80] = rng.randrange(255)
            struct.pack_into('<H', actor, 0x48, rng.randrange(- 20, 1) & 65535)
            effects[str(actor[0x95])] = effects.get(str(actor[0x95]), 0) + 1
        bank = Bank()
        for i in range(13):
            bank.lookup[i] = sum(rng.randrange(101) << shift for shift in (0, 8, 16, 24))
            bank.colors[i] = rng.getrandbits(32)
        original.cpu.mem_write(0x54b808, bytes(bank.lookup))
        original.cpu.mem_write(0x54b83c, bytes(bank.colors))
        for address, payload in ((0x54d5d4, bytes(4)), (0x5bc008, bytes(4)), (0x54d5ec, bytes(4)), (0x54d5dc, bytes(6)), (0x54d5e8, bytes(3)), (0x54d5f0, bytes(1)), (0x54cdc8, struct.pack('<I', 0x54bb90)), (0x55f1f0, struct.pack('<2I', 0x558cf0 + 50 * 256, 0x558cf0 + 50 * 256)), (0x5785f8, struct.pack('<2I', 0x55f1f8 + 50 * 1024, 0x55f1f8 + 50 * 1024))):
            original.cpu.mem_write(address, payload)
        original.call(0x4754e0, eax=0)
        struct.pack_into('<I', actor, 0xb4, 0x801000)
        struct.pack_into('<I', actor, 0x134, 0x804000)
        struct.pack_into('<I', actor, 0x13c, 1)
        struct.pack_into('<I', actor, 0x144, 1)
        struct.pack_into('<I', actor, 0xb0, 0x5449fc)
        struct.pack_into('<I', actor, 0xb8, 1)
        struct.pack_into('<I', actor, 0x150, rng.randrange(2))
        resource_token = (0x5449fc, 0x546618, 0x546634)[case % 3]
        mapped_actor = bytearray(actor)
        struct.pack_into('<I', mapped_actor, 0xb0, resource_token)
        original.cpu.mem_write(0x800000, bytes(mapped_actor))
        original.cpu.mem_write(0x801000, bytes(frame.metadata))
        original.cpu.mem_write(0x804000, bytes(raw))
        initial = rng.randbytes(64 * 64 * 4)
        target = bytearray(40)
        struct.pack_into('<3I', target, 0, 0x808000, 64, 64)
        target[0xc], target[0xd] = 4, 4
        stride = 256 if case < 4096 else rng.choice((0, 4, 32, 128, 256))
        overlapping_strides += stride < 256
        struct.pack_into('<I', target, 0x14, stride)
#Original descriptors store both byte stride and trailing row bytes.
        struct.pack_into('<I', target, 0x18, (stride - 64 * 4) & 0xffffffff)
        original.cpu.mem_write(0x802000, bytes(target))
        original.cpu.mem_write(0x808000, initial)
        original.cpu.mem_write(0x5bc010, struct.pack('<I', 0x802000))
        original.cpu.mem_write(0x803000, struct.pack('<2I', 0x801100, 0x801000))
        for token in (0x5449fc, 0x546618, 0x546634):
            original.cpu.mem_write(token, struct.pack('<6I', 0x803000, 2, 0, 0, 0, 0))
        original.call(0x4ac8a0, eax=0x800000)
        assert struct.unpack('<I', original.cpu.mem_read(0x8000b4, 4))[0] == 0x801000
        expected_visible = original.call(0x4ae3e0, eax=0x800000, edx=1)
        original.call(0x4af8c0, eax=0x800000, edx=0x802000)
        if expected_visible == 1:
            visible += 1
        expected = bytes(original.cpu.mem_read(0x808000, len(initial)))
        destination = c.create_string_buffer(initial, len(initial))
        surface = Surface(c.addressof(destination), len(initial), 64, 64, stride, 4)
        storage = c.create_string_buffer(bytes(actor), len(actor))
        prepared = Preparation()
        prepared.source_weights = c.addressof(weights.bytes[50])
        prepared.destination_weights = c.addressof(weights.bytes[50])
        prepared.source_words = c.addressof(weights.words[50])
        prepared.destination_words = c.addressof(weights.words[50])
        previous_prepared = Preparation.from_buffer_copy(bytes(prepared))
        mapped_prepared = Preparation.from_buffer_copy(bytes(prepared))
        status = native.vertrix_actor_render_draw32(storage, len(actor), c.byref(frame), c.byref(surface), Clip(0, 63, 0, 63), c.byref(weights), c.byref(bank), c.byref(tables), c.byref(prepared))
        state = FlagState(actor[0x8c], 0 if actor[0x4e] == 100 else actor[0x93], actor[0x95], actor[0x4e], actor[0x52], 13, actor[0x94], struct.unpack_from('<H', actor, 0x48)[0])
        flags = native.vertrix_render_flags(state, 0)
        rule = native.vertrix_render_rule(flags)
        if expected_visible == 1 and rule == 92:
            assert status == - 1 and expected == initial, (case, status, flags)
            unsupported += 1
        else:
            assert status == expected_visible, (case, status, expected_visible, list(actor[0x44: 0x54]), list(actor[0x8c: 0x96]), hex(struct.unpack('<I', original.cpu.mem_read(0x5bb72c, 4))[0]))
        assert bytes(destination) == expected, (case, stride, list(actor[0x44: 0x54]), list(actor[0x8c: 0x96]), hex(flags), next((i, a, b) for i, (a, b) in enumerate(zip(bytes(destination), expected)) if a != b))
        assert bytes(pixels) == bytes(raw), case
        bound_destination = c.create_string_buffer(initial, len(initial))
        bound_surface = Surface(c.addressof(bound_destination), len(initial), 64, 64, stride, 4)
        frames = (Frame * 2)(Frame(), frame)
        sprites = SpriteBank(frames, 2)
        bound_actor = c.create_string_buffer(bytes(actor), len(actor))
        bound_status = native.vertrix_sprite_actor_draw32(bound_actor, len(actor), c.byref(sprites), c.byref(bound_surface), Clip(0, 63, 0, 63), c.byref(weights), c.byref(bank), c.byref(tables), c.byref(previous_prepared))
        assert bound_status == status and bytes(bound_destination) == expected, ('bank draw', case)
        expected_actor = bytearray(actor)
        struct.pack_into('<I', expected_actor, 0xb4, 1)
        assert bytes(bound_actor) == bytes(expected_actor), ('bank binding', case)
        assert bytes(previous_prepared) == bytes(prepared), ('bank preparation', case)
        mapped_storage = c.create_string_buffer(bytes(mapped_actor), len(mapped_actor))
        mapped_destination = c.create_string_buffer(initial, len(initial))
        mapped_surface = Surface(c.addressof(mapped_destination), len(initial), 64, 64, stride, 4)
        assert native.vertrix_sprite_actor_draw_resource32(mapped_storage, len(mapped_actor), resource_token, c.byref(sprites), c.byref(mapped_surface), Clip(0, 63, 0, 63), c.byref(weights), c.byref(bank), c.byref(tables), c.byref(mapped_prepared)) == status
        assert bytes(mapped_destination) == expected
        assert bytes(mapped_prepared) == bytes(prepared)
        expected_mapped = bytearray(original.cpu.mem_read(0x800000, len(mapped_actor)))
        struct.pack_into('<I', expected_mapped, 0xb4, 1)
        assert bytes(mapped_storage) == bytes(expected_mapped), ('mapped actor', case)
        bindings = (BankBinding * 3)(BankBinding(0x5449fc, None), BankBinding(0x546618, None), BankBinding(0x546634, None))
        bindings[case % 3].sprites = c.pointer(sprites)
        resource_map = BankMap(bindings, 3)
        c.memmove(mapped_storage, bytes(mapped_actor), len(mapped_actor))
        c.memmove(mapped_destination, initial, len(initial))
        mapped_prepared = Preparation()
        mapped_prepared.source_weights = c.addressof(weights.bytes[50])
        mapped_prepared.destination_weights = c.addressof(weights.bytes[50])
        mapped_prepared.source_words = c.addressof(weights.words[50])
        mapped_prepared.destination_words = c.addressof(weights.words[50])
        assert native.vertrix_sprite_actor_draw_mapped32(mapped_storage, len(mapped_actor), c.byref(resource_map), c.byref(mapped_surface), Clip(0, 63, 0, 63), c.byref(weights), c.byref(bank), c.byref(tables), c.byref(mapped_prepared)) == status
        assert bytes(mapped_storage) == bytes(expected_mapped)
        assert bytes(mapped_destination) == expected and bytes(mapped_prepared) == bytes(prepared)
        mapped_before = bytes(mapped_storage), bytes(mapped_destination), bytes(mapped_prepared)
        assert native.vertrix_sprite_actor_draw_resource32(mapped_storage, len(mapped_actor), resource_token ^ 1, c.byref(sprites), c.byref(mapped_surface), Clip(0, 63, 0, 63), c.byref(weights), c.byref(bank), c.byref(tables), c.byref(mapped_prepared)) == - 1
        assert (bytes(mapped_storage), bytes(mapped_destination), bytes(mapped_prepared)) == mapped_before
        resource_map.count = 0
        assert native.vertrix_sprite_actor_draw_mapped32(mapped_storage, len(mapped_actor), c.byref(resource_map), c.byref(mapped_surface), Clip(0, 63, 0, 63), c.byref(weights), c.byref(bank), c.byref(tables), c.byref(mapped_prepared)) == - 1
        assert (bytes(mapped_storage), bytes(mapped_destination), bytes(mapped_prepared)) == mapped_before
        invalid_actor = bytearray(expected_actor)
        struct.pack_into('<I', invalid_actor, 0xb8, 2)
        rejected_actor = c.create_string_buffer(bytes(invalid_actor), len(invalid_actor))
        before_binding = bytes(bound_destination), bytes(previous_prepared)
        assert native.vertrix_sprite_actor_draw32(rejected_actor, len(invalid_actor), c.byref(sprites), c.byref(bound_surface), Clip(0, 63, 0, 63), c.byref(weights), c.byref(bank), c.byref(tables), c.byref(previous_prepared)) == - 1
        assert bytes(rejected_actor) == bytes(invalid_actor)
        assert (bytes(bound_destination), bytes(previous_prepared)) == before_binding
        before = bytes(destination), bytes(prepared)
        assert native.vertrix_actor_render_draw32(storage, len(actor) - 1, c.byref(frame), c.byref(surface), Clip(0, 63, 0, 63), None, None, None, c.byref(prepared)) == - 1
        assert (bytes(destination), bytes(prepared)) == before
        if expected_visible == 1:
            surface.size = 0
            assert native.vertrix_actor_render_draw32(storage, len(actor), c.byref(frame), c.byref(surface), Clip(0, 63, 0, 63), c.byref(weights), c.byref(bank), c.byref(tables), c.byref(prepared)) == - 1
            assert (bytes(destination), bytes(prepared)) == before
            truncated_targets += 1
            from verify_sprite_chain_draw import verify as verify_chain
            chain_report = verify_chain(native, original, samples, weights, tables)
            native.vertrix_palette_tables_free(c.byref(tables))
    report = {'status': 'passed', 'complete_actor_geometry_and_draw_cases': 8192, 'original_vf_sprite_cases': 6144, 'vf_frames_used': len(samples), 'actor_effect_cases': effects, 'vf_bank_binding_and_draw_cases': 8192, 'explicit_resource_bank_draw_cases': 8192, 'actor_resource_map_draw_cases': 8192, 'missing_resource_map_preservation_cases': 8192, 'mismatched_resource_bank_preservation_cases': 8192, 'invalid_bank_frame_preservation_cases': 8192, 'unmatched_original_rule_preservation_cases': unsupported, 'nonstandard_overlapping_surface_stride_cases': overlapping_strides, 'truncated_destination_preservation_cases': truncated_targets, 'visible_cases': visible, 'source_preservation_cases': 8192, 'invalid_actor_preservation_cases': 8192, 'scope': 'Original 0x4ac8a0 frame binding then complete 0x4af8c0 executes ' 'with real 0x4ae3e0 geometry and 0x4af560 drawing, without draw hooks. ' 'Direct coordinates, scale1..16, clipping, anchors, displacement, ' 'opaque/binary source, alpha override, actor effects, fixed colors, ' 'palette shifts and cycling covered, including overlapping row strides. ' 'Unmatched original flag rules preserve pixels and native rejects them. ' 'Transforms, special clipping and full application remain unfinished.'}
    report.update(chain_report)
    (args.build_dir / 'actor-render-draw-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
