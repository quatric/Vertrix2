"""Verify VF artwork against complete original45e490 execution."""
import argparse
import ctypes as c
import json
from pathlib import Path
import subprocess
import struct
from original import Original
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_ESP, UC_X86_REG_EIP
from verify_sprite_clone import Image, Frame
from verify_ui_sprite_vf import Bank
from verify_linked_alternating import Display
from verify_frame_resource import Resource


class Stencils(c.Structure):
    _fields_ = [('frame6', Frame), ('frame9', Frame)]


class Artwork(c.Structure):
    _fields_ = [('images', Image * 2), ('origin_x', c.c_uint32 * 2),
                ('origin_y', c.c_uint32 * 2), ('ready', c.c_uint)]


class DisplayAssets(c.Structure):
    _fields_ = [('artwork', Artwork), ('descriptors', c.c_uint32 * 2),
                ('resources', Resource * 2)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('archive', type=Path)
    parser.add_argument('--executable', type=Path, required=True)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'ui-artwork.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    *[str(source / name) for name in ['ui_artwork.c', 'ui_border_artwork.c', 'ui_sprite_bank.c',
                        'image_clone.c', 'image_mirror.c', 'image.c', 'vf.c',
                        'font_stencils.c', 'sprite_files.c', 'font_image.c', 'font_stencil.c',
                        'font_outline.c', 'ui_display.c', 'linked_alternating.c',
                        'block_resource.c', 'frame_resource.c', 'animation.c', 'timer.c',
                        'word_transition.c', 'dword_transition.c', 'ui_display_storage.c',
                        'ui_actor_storage.c', 'ui_actor_update.c', 'actor_storage.c',
                        'ui_display_layout.c', 'object_list.c', 'actor_lookup.c',
                        'ui_artwork_render.c', 'sprite_actor_image.c', 'sprite_actor_draw.c',
                        'actor_render_draw.c', 'actor_render_geometry.c', 'actor_render_style.c',
                        'actor_image_bounds.c', 'actor_image_clip.c', 'render_geometry.c', 'surface.c',
                        'render_dispatch.c', 'render_row.c', 'render_pixel.c', 'render_preparation.c',
                        'render_color.c', 'palette_map.c', 'palette_tables.c', 'palette_color.c',
                        'render_palette.c', 'render_weights.c', 'sprite_chain_draw.c',
                        'sprite_scene_draw.c', 'ui_scene_render.c', 'ui_scene_frame.c',
                        'ui_indicator_update.c', 'linked_indicator.c', 'byte_transition.c', 'ui_border_update.c', 'linked_burst.c', 'random.c', 'ui_actor_frame.c', 'ui_companion_update.c', 'linked_movement.c',
                        'frame_texture.c', 'texture.c']], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_ui_border_artwork_build.argtypes = [c.POINTER(Bank), c.POINTER(Bank),
        c.c_uint32, c.c_uint32, c.POINTER(Frame)]
    native.vertrix_sprite_free.argtypes = [c.POINTER(Frame)]
    native.vertrix_vf_open.argtypes = [c.c_char_p]
    native.vertrix_vf_open.restype = c.c_void_p
    native.vertrix_vf_close.argtypes = [c.c_void_p]
    native.vertrix_ui_artwork_load.argtypes = [c.c_void_p, c.c_char_p,
        c.POINTER(c.c_uint32), c.c_size_t, c.c_uint32, c.POINTER(Artwork)]
    native.vertrix_ui_artwork_free.argtypes = [c.POINTER(Artwork)]
    native.vertrix_ui_sprite_bank_load.argtypes = [c.c_void_p, c.c_char_p,
        c.POINTER(c.c_uint32), c.c_size_t, c.POINTER(Bank)]
    native.vertrix_ui_sprite_bank_free.argtypes = [c.POINTER(Bank)]
    native.vertrix_font_stencils_load.argtypes = [c.c_void_p, c.POINTER(c.c_uint32),
                                                c.POINTER(Stencils)]
    native.vertrix_font_stencils_free.argtypes = [c.POINTER(Stencils)]
    native.vertrix_font_image_stencil.argtypes = [c.POINTER(Image), c.POINTER(Image),
                                                 c.c_uint32, c.POINTER(Image)]
    native.vertrix_image_free.argtypes = [c.POINTER(Image)]
    native.vertrix_ui_display_assets_load.argtypes = [c.c_void_p, c.c_char_p,
        c.POINTER(c.c_uint32), c.c_size_t, c.c_uint32, c.POINTER(DisplayAssets)]
    native.vertrix_ui_display_assets_free.argtypes = [c.POINTER(DisplayAssets)]
    native.vertrix_ui_display_initialize_animation.argtypes = [c.POINTER(Display),
        c.c_size_t, c.POINTER(DisplayAssets)]
    native.vertrix_ui_display_update.argtypes = [c.POINTER(Display), c.c_int,
        c.c_uint32, c.c_uint32, c.c_int16, c.c_uint32, c.POINTER(DisplayAssets)]
    native.vertrix_ui_display_image.argtypes = [c.POINTER(Display), c.POINTER(DisplayAssets),
        c.POINTER(c.POINTER(Image)), c.POINTER(c.c_uint32), c.POINTER(c.c_uint32)]
    native.vertrix_ui_display_storage_construct.argtypes = [c.c_void_p, c.c_size_t,
        c.c_size_t, c.c_uint, c.c_int16, c.c_int16, c.POINTER(DisplayAssets)]
    native.vertrix_ui_display_storage_update.argtypes = [c.c_void_p, c.c_size_t,
        c.c_int, c.c_uint32, c.c_uint32, c.c_int16, c.c_uint32, c.POINTER(DisplayAssets)]
    native.vertrix_ui_display_storage_image.argtypes = [c.c_void_p, c.c_size_t,
        c.POINTER(DisplayAssets), c.POINTER(c.POINTER(Image)),
        c.POINTER(c.c_uint32), c.POINTER(c.c_uint32)]
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    retained = []
    pixels = 0
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_map(0x900000, 0x1000000)
    cpu.mem_map(0x2000000, 0x200000)
    cpu.mem_map(0x2200000, 0x100000)
    cpu.mem_map(0x2300000, 0x100000)
    heap = 0x900000
    generated_draw_cases = 0
    generated_frames = 0
    generated_visible_frames = generated_bank_switches = 0
    generated_texture_frames = 0

    def allocate(width, height, x, y, payload=None):
        nonlocal heap
        descriptor, pointer = heap, heap + 64
        heap = (pointer + width * height * 4 + 63) & ~63
        assert heap < 0x1900000
        cpu.mem_write(descriptor, struct.pack('<10I', pointer, width, height, x, y, 0, 0, 0, 0, 0x04010000))
        cpu.mem_write(pointer, payload if payload is not None else bytes(width * height * 4))
        return descriptor

    def resource(address, handles):
        nonlocal heap
        table = heap
        heap += (len(handles) * 4 + 63) & ~63
        cpu.mem_write(table, struct.pack('<' + 'I' * len(handles), *handles))
        cpu.mem_write(address, struct.pack('<6I', table, len(handles), 0, 0, 0, 0))

    def boundary(cpu, address, size, context):
        esp = cpu.reg_read(UC_X86_REG_ESP)
        cleanup = 4
        if address == 0x487640:
            assert cpu.reg_read(UC_X86_REG_EDX) == 1
            resource(cpu.reg_read(UC_X86_REG_EAX), [0])
        else:
            eax, edx, ebx, ecx = [cpu.reg_read(reg) for reg in
                (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX)]
            cpu.reg_write(UC_X86_REG_EAX, allocate(eax, edx, ebx, ecx))
            cleanup += 32
        cpu.reg_write(UC_X86_REG_EIP, struct.unpack('<I', cpu.mem_read(esp, 4))[0])
        cpu.reg_write(UC_X86_REG_ESP, esp + cleanup)

    for address in [0x487640, 0x483060]:
        cpu.hook_add(UC_HOOK_CODE, boundary, begin=address, end=address)
    for reverse in [False, True]:
        masks = (c.c_uint32 * 3)(*([0xff, 0xff00, 0xff0000] if reverse else
                                  [0xff0000, 0xff00, 0xff]))
        for first in [0, 9]:
            bank, stencils = Bank(), Stencils()
            assert native.vertrix_ui_sprite_bank_load(archive, b'sprite/damier.spr',
                                                      masks, first, c.byref(bank))
            assert native.vertrix_font_stencils_load(archive, masks, c.byref(stencils))
            for source_index in [0, 34]:
                heap = 0x900000
                handles = []
                for frame in bank.frames[:bank.count]:
                    handles.append(allocate(frame.image.width, frame.image.height,
                        frame.metadata[3], frame.metadata[4], c.string_at(frame.image.rgba,
                            frame.image.width * frame.image.height * 4)))
                resource(0x5449fc, handles)
                stencil = stencils.frame9.image
                stencil_handle = allocate(stencil.width, stencil.height, 0, 0,
                                           c.string_at(stencil.rgba, stencil.width * stencil.height * 4))
                resource(0x546538, [0] * 9 + [stencil_handle])
                cpu.mem_write(0x4fbfac, struct.pack('<I', source_index))
try : original
    .call(0x45e490) except RuntimeError
        : cpu.emu_start(cpu.reg_read(UC_X86_REG_EIP), 0x700000,
                        count = 100_000_000) assert cpu.reg_read(UC_X86_REG_EIP) ==
        0x700000 artwork =
        Artwork() assert native
            .vertrix_ui_artwork_load(archive, b 'sprite/damier.spr', masks, first, source_index,
                                     c.byref(artwork)) assert artwork.ready
        == 1 native.vertrix_ui_artwork_build.argtypes =
            [ c.POINTER(Bank), c.POINTER(Bank), c.c_uint32,
              c.POINTER(Artwork) ] stencil_frames = (Frame * 10)()
                stencil_frames[9] = stencils.frame9 stencil_bank = Bank(stencil_frames, 10) border =
                    Frame() assert native
                        .vertrix_ui_border_artwork_build(c.byref(bank), c.byref(stencil_bank), 20,
                                                         0x04010000, c.byref(border)) cpu
                        .mem_write(0x4fbf74, struct.pack('<I', 20))
    try : original.call(0x45e530)
                except RuntimeError:
                    cpu.emu_start(cpu.reg_read(UC_X86_REG_EIP), 0x700000, count=100_000_000)
                    assert cpu.reg_read(UC_X86_REG_EIP) == 0x700000
                border_table = struct.unpack('<I', cpu.mem_read(0x5466a4, 4))[0]
                border_descriptor = struct.unpack('<I', cpu.mem_read(border_table, 4))[0]
                border_words = struct.unpack('<10I', cpu.mem_read(border_descriptor, 40))
                assert tuple(border.metadata)[1:] == border_words[1:]
                assert (border.image.width, border.image.height) == border_words[1:3]
                assert c.string_at(border.image.rgba, border.image.width*border.image.height*4) == bytes(
                    cpu.mem_read(border_words[0], border_words[1]*border_words[2]*4))
                native.vertrix_sprite_free(c.byref(border))
                built = Artwork()
                assert native.vertrix_ui_artwork_build(c.byref(bank), c.byref(stencil_bank),
                                                       source_index, c.byref(built))
                for j in range(2):
                    a, b = artwork.images[j], built.images[j]
                    assert (a.width, a.height) == (b.width, b.height)
                    assert c.string_at(a.rgba, a.width*a.height*4) == c.string_at(b.rgba, b.width*b.height*4)
                    assert artwork.origin_x[j] == built.origin_x[j]
                    assert artwork.origin_y[j] == built.origin_y[j]
                native.vertrix_ui_artwork_free(c.byref(built))
                expected = []
                for i in range(2):
                    reference = Image()
                    frame = bank.frames[source_index]
                    assert native.vertrix_font_image_stencil(c.byref(frame.image),
                        c.byref(stencils.frame9.image), i == 0, c.byref(reference))
                    actual = artwork.images[i]
                    assert (actual.width, actual.height) == (reference.width, reference.height)
                    payload = c.string_at(reference.rgba, reference.width * reference.height * 4)
                    assert c.string_at(actual.rgba, len(payload)) == payload
                    table = struct.unpack('<I', cpu.mem_read([0x546618, 0x546634][i], 4))[0]
                    handle = struct.unpack('<I', cpu.mem_read(table, 4))[0]
                    pointer, width, height, x, y = struct.unpack('<5I', cpu.mem_read(handle, 20))
                    assert (actual.width, actual.height, artwork.origin_x[i], artwork.origin_y[i]) == (width, height, x, y)
                    assert payload == bytes(cpu.mem_read(pointer, width * height * 4))
                    assert artwork.origin_x[i] == (frame.metadata[3] + stencils.frame9.image.width // 2) & 0xffffffff
                    assert artwork.origin_y[i] == (frame.metadata[4] + stencils.frame9.image.height // 2) & 0xffffffff
                    expected.append(payload)
                    pixels += actual.width * actual.height
                    native.vertrix_image_free(c.byref(reference))
                from verify_ui_artwork_render import verify as verify_generated_draw
                generated_draw_cases += verify_generated_draw(native, original, artwork, generated_draw_cases)
                from verify_ui_artwork_frames import verify as verify_generated_frames
                frame_result = verify_generated_frames(native, original, artwork)
                generated_frames += frame_result['frames']
                generated_visible_frames += frame_result['visible_frames']
                generated_bank_switches += frame_result['bank_switches']
                generated_texture_frames += frame_result['texture_frames']
                before = bytes(artwork)
                assert not native.vertrix_ui_artwork_load(archive, b'sprite/damier.spr',
                                                          masks, first, source_index, c.byref(artwork))
                assert bytes(artwork) == before
                retained.append((artwork, expected))
            native.vertrix_ui_sprite_bank_free(c.byref(bank))
            native.vertrix_font_stencils_free(c.byref(stencils))
    invalid = Artwork()
    assert not native.vertrix_ui_artwork_load(archive, b'missing.spr', masks, 0, 34, c.byref(invalid))
    assert bytes(invalid) == bytes(Artwork())
    assert not native.vertrix_ui_artwork_load(archive, b'sprite/damier.spr', masks, 1, 34, c.byref(invalid))
    assert bytes(invalid) == bytes(Artwork())
    assert not native.vertrix_ui_artwork_load(archive, b'sprite/damier.spr', masks, 0, 0xffffffff, c.byref(invalid))
    assert bytes(invalid) == bytes(Artwork())
    assets = DisplayAssets()
    default_masks = (c.c_uint32 * 3)(0xff0000, 0xff00, 0xff)
    assert native.vertrix_ui_display_assets_load(archive, b'sprite/damier.spr', default_masks,
                                                0, 34, c.byref(assets))
    saved_assets = bytes(assets)
    assert not native.vertrix_ui_display_assets_load(archive, b'sprite/damier.spr', default_masks,
                                                    0, 34, c.byref(assets))
    assert bytes(assets) == saved_assets
    native.vertrix_vf_close(archive)
    state = Display()
    image = c.POINTER(Image)()
    x, y = c.c_uint32(123), c.c_uint32(456)
    assert not native.vertrix_ui_display_image(c.byref(state), c.byref(assets),
                                               c.byref(image), c.byref(x), c.byref(y))
    assert not image and (x.value, y.value) == (123, 456)
    for pair in range(12):
        state.primary.counter = 1234
        state.secondary.counter = 5678
        state.animation.timer.counter = 999
        state.animation.timer.period = 37
        state.origin_y, state.y = -75, 240
        assert native.vertrix_ui_display_initialize_animation(c.byref(state), pair, c.byref(assets))
        assert (state.primary.counter, state.secondary.counter, state.animation.timer.counter) == (1234, 5678, 0)
        assert (state.primary.period, state.secondary.period) == (10, 441 - pair * 40)
        assert (state.threshold, state.handler, state.phase, state.source, state.descriptor) == (pair + 1, 0x450a10, 0, 0, 0)
        assert (state.origin_y, state.y, state.animation.timer.period, state.animation.frame) == (-75, 240, 37, 0)
    before = bytes(state)
    assert not native.vertrix_ui_display_initialize_animation(c.byref(state), 12, c.byref(assets))
    assert bytes(state) == before
    for i in range(2):
        state.handler = 0x450a10 if i == 0 else 0x450aa0
        state.phase = 1 if i == 0 else 0
        state.y = state.target_y = 24
        state.primary.period = 1
        assert native.vertrix_ui_display_update(c.byref(state), 1, 1, 0, 120, 1, c.byref(assets))
        assert state.descriptor == i
        assert native.vertrix_ui_display_image(c.byref(state), c.byref(assets),
                                               c.byref(image), c.byref(x), c.byref(y))
        assert c.addressof(image.contents) == c.addressof(assets.artwork.images[i])
        assert (x.value, y.value) == (assets.artwork.origin_x[i], assets.artwork.origin_y[i])
        payload = retained[1][1][i]
        assert c.string_at(image.contents.rgba, len(payload)) == payload
    for pair in range(12):
        for side in range(2):
            storage = c.create_string_buffer(bytes([0xa5]) * 0x160, 0x160)
            assert native.vertrix_ui_display_storage_construct(storage, len(storage), pair,
                side, -123, 234, c.byref(assets))
            for i in range(2):
                raw = bytearray(storage.raw)
                struct.pack_into('<I', raw, 0x154, 0x450a10 if i == 0 else 0x450aa0)
                struct.pack_into('<I', raw, 0x7c, 1 if i == 0 else 0)
                struct.pack_into('<I', raw, 0xbc, 9)
                raw[0x18:0x1a] = raw[0x16:0x18]
                c.memmove(storage, bytes(raw), len(raw))
                assert native.vertrix_ui_display_storage_update(storage, len(storage), 1,
                    1, 0, 120, 1, c.byref(assets))
                assert native.vertrix_ui_display_storage_image(storage, len(storage), c.byref(assets),
                    c.byref(image), c.byref(x), c.byref(y))
                payload = retained[1][1][i]
                assert c.string_at(image.contents.rgba, len(payload)) == payload
                assert (x.value, y.value) == (assets.artwork.origin_x[i], assets.artwork.origin_y[i])
                assert struct.unpack_from('<I', storage.raw, 0xb0)[0] == [0x546618, 0x546634][i]
                assert storage.raw[0x56:0x58] == b'\xa5\xa5'
    raw = bytearray(storage.raw)
    struct.pack_into('<I', raw, 0xb4, 99)
    c.memmove(storage, bytes(raw), len(raw))
    before_image, before_origin = c.addressof(image.contents), (x.value, y.value)
    assert not native.vertrix_ui_display_storage_image(storage, len(storage), c.byref(assets),
        c.byref(image), c.byref(x), c.byref(y))
    assert (c.addressof(image.contents), (x.value, y.value)) == (before_image, before_origin)
    native.vertrix_ui_display_assets_free(c.byref(assets))
    before_storage = storage.raw
    assert not native.vertrix_ui_display_storage_update(storage, len(storage), 1,
        1, 0, 120, 1, c.byref(assets))
    assert storage.raw == before_storage
    assert not native.vertrix_ui_display_storage_image(storage, len(storage), c.byref(assets),
        c.byref(image), c.byref(x), c.byref(y))
    before = bytes(state)
    assert not native.vertrix_ui_display_update(c.byref(state), 1, 1, 0, 120, 1, c.byref(assets))
    assert bytes(state) == before
    assert not native.vertrix_ui_display_image(c.byref(state), c.byref(assets),
                                               c.byref(image), c.byref(x), c.byref(y))
    assert bytes(assets) == bytes(DisplayAssets())
    for artwork, expected in retained:
        for actual, payload in zip(artwork.images, expected):
            assert c.string_at(actual.rgba, len(payload)) == payload
        native.vertrix_ui_artwork_free(c.byref(artwork))
        assert bytes(artwork) == bytes(Artwork())
    report = {'status': 'passed', 'cases': len(retained), 'pixels': pixels,
              'scope': 'Complete original45e490 with actual4877f0 lookup,4831b0 stencil and487850 publication. '
                       'Hooks supply empty resource construction and image allocation only. Input pixels '
                       'come from separately verified VF bank decoding/configuration. Solid/hollow output '
                       'pixels, dimensions and origins match. Ownership after VF closure verified. '
                       'VF display assets bind solid/hollow images through actual recovered '
                       'animation attach branches and resolve pixels/origins after VF closure. '
                       'All24 portable actor-storage creations/updates resolve both VF images and '
                       'origins after archive closure, preserving untouched bytes. Invalid descriptor '
                       'and freed assets reject resolution/updates. Filename and first-source remain caller-selected.'}
    report['original_generated_artwork_mapped_draw_cases'] = generated_draw_cases
    report['original_border_builder_cases'] = 8
    report['constructed_generated_artwork_update_draw_frames'] = generated_frames
    report['constructed_generated_artwork_visible_frames'] = generated_visible_frames
    report['constructed_generated_artwork_bank_switches'] = generated_bank_switches
    report['generated_visible_frames_packed_for_wii'] = generated_texture_frames
    report['constructed_generated_scope'] = ('Original base constructor and complete UI position/setup '
        'fragments compare all24 actors. Complete4b6200 update and4b6240 draw match persistent '
        '640x480 frames using actual45e490-generated VF artwork and two supplied idle linked-state '
        'actors. Whole destination/actor storage/refresh compare; no update or drawing hooks. '
        'Final player implementation, scheduling, menus and Wii execution remain unfinished.')
    report['generated_draw_scope'] = ('Actual45e490-generated banks and descriptor metadata '
        'feed complete original4ac8a0/4af8c0 rendering comparisons. Native view borrows '
        'VF-generated solid/hollow pixels; clipping, anchors, displacement and scale8/16. '
        'Builder allocation boundaries are supplied as in artwork recovery; draw has no hooks.')
    (args.build_dir / 'ui-artwork-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
