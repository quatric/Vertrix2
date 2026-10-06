"""Original interface setup, generated VF banks and consecutive rendered frames."""
import ctypes as c
import struct
from original import RETURN
from verify_ui_artwork_render import View
from verify_actor_render_draw import BankMap
from verify_sprite_chain_draw import Resolve
from verify_ui_scene_render import Options
from verify_object_append import List
from verify_render_geometry import Clip
from verify_render_rectangle import Surface
from verify_render_preparation import Preparation
from verify_render_weights import Weights
from verify_palette_tables import Tables
from verify_wii_frame_texture import Texture, check_pixels
from unicorn.x86_const import UC_X86_REG_EBP, UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EIP


def verify(native, original, artwork):
    native.vertrix_ui_artwork_actor_construct.argtypes = [c.c_void_p, c.c_size_t, c.c_size_t,
        c.c_uint, c.c_int16, c.c_int16, c.POINTER(View)]
    native.vertrix_ui_scene_frame_render_mapped.argtypes = [c.POINTER(List), Resolve, c.c_void_p,
        c.POINTER(Options), c.POINTER(BankMap), c.POINTER(Surface), Clip, c.c_void_p,
        c.c_void_p, c.POINTER(Tables), c.POINTER(Preparation), c.c_size_t, c.POINTER(c.c_size_t)]
    native.vertrix_frame_texture_init.argtypes = [c.POINTER(Surface), c.POINTER(c.c_uint32), c.POINTER(Texture)]
    native.vertrix_frame_texture_update.argtypes = native.vertrix_frame_texture_init.argtypes
    native.vertrix_texture_free.argtypes = [c.POINTER(Texture)]
    view = View()
    assert native.vertrix_ui_artwork_render_view(c.byref(artwork), 0x04010000, c.byref(view))
    tables, weights = Tables(), Weights()
    native.vertrix_palette_tables_build.argtypes = [c.POINTER(Tables)]
    native.vertrix_palette_tables_free.argtypes = [c.POINTER(Tables)]
    assert native.vertrix_palette_tables_build(c.byref(tables))
    assert native.vertrix_render_weights_build(c.byref(weights))
    original.cpu.mem_write(0x2300000, struct.pack('<262144I', *tables.lookup[:262144]))
    original.cpu.mem_write(0x54b800, struct.pack('<I', 0x2300000))
    original.cpu.mem_write(0x5468b0, bytes(tables.channels))
    original.cpu.mem_write(0x558cf0, bytes(weights.bytes))
    original.cpu.mem_write(0x55f1f8, bytes(weights.words))
    original.call(0x475400, stop=0x475443)
    actors = {}
    @Resolve
    def resolve(handle, storage, size, context):
        if handle not in actors:
            return 0
        storage[0], size[0] = c.addressof(actors[handle]), len(actors[handle])
        return 1
    solid_table = struct.unpack('<I', original.cpu.mem_read(0x546618, 4))[0]
    solid_descriptor = struct.unpack('<I', original.cpu.mem_read(solid_table, 4))[0]
    for index in range(26):
        handle = 0x2200000 + index * 512
        original.cpu.mem_write(handle, bytes(0x15c))
        storage = c.create_string_buffer(bytes(0x15c), 0x15c)
        if index < 24:
            pair, side = index // 2, index % 2
            original.call(0x4abd70, eax=handle)
            frame = 0x709080
            original.cpu.mem_write(frame - 0x20, struct.pack('<I', 441 - pair * 40))
            original.cpu.mem_write(frame - 0x34, struct.pack('<I', pair))
            original.cpu.mem_write(0x533d70, bytes(2))
            original.cpu.mem_write(0x533d74, bytes(2))
            original.cpu.reg_write(UC_X86_REG_EBP, frame)
            original.cpu.reg_write(UC_X86_REG_ESI, handle)
            original.cpu.reg_write(UC_X86_REG_EDI, pair * 4)
            original.cpu.ctl_remove_cache(0x46e0c8, 0x46e303)
            original.call(0x46e0c8 if side == 0 else 0x46e257,
                          stop=0x46e16e if side == 0 else 0x46e302)
            assert native.vertrix_ui_artwork_actor_construct(storage, len(storage), pair,
                side, 0, 0, c.byref(view))
        else:
            original.call(0x4abd70, eax=handle)
            assert native.vertrix_actor_storage_construct(storage, len(storage))
            for offset, value in ((0, 0x17 + index - 24), (0x58, 1), (0x64, 0),
                                  (0x134, 0), (0xb0, 0x546618), (0xb4, solid_descriptor)):
                original.cpu.mem_write(handle + offset, struct.pack('<I', value))
                native.vertrix_actor_storage_write(storage, len(storage), offset, 4,
                                                   0 if offset == 0xb4 else value)
        expected = bytearray(original.cpu.mem_read(handle, len(storage)))
        struct.pack_into('<I', expected, 0xb4, 0)
        assert bytes(storage) == bytes(expected), ('constructed actor', index)
        actors[handle] = storage
    handles = (c.c_uint32 * 26)(*actors)
    listed = List(handles, 26, 26)
    original.cpu.mem_write(0x806000, struct.pack('<4I', 0, 0x806100, 26, 26))
    original.cpu.mem_write(0x806100, bytes(handles))
    original.cpu.mem_write(0x54671c, struct.pack('<3I', 0, 0x806100, 26))
    target = bytearray(40)
    struct.pack_into('<3I', target, 0, 0x2000000, 640, 480)
    target[12:14] = bytes((4, 4))
    struct.pack_into('<I', target, 20, 2560)
    original.cpu.mem_write(0x802000, bytes(target))
    refresh = (c.c_uint32 * 6)()
    original.cpu.mem_write(0x5bb714, bytes(refresh))
    prepared = Preparation()
    options = Options(1, 30, 500, refresh, 6, c.pointer(view.resources[0]),
                      c.pointer(view.resources[1]), 1)
    original.cpu.mem_write(0x5bb710, struct.pack('<I', 1))
    original.cpu.mem_write(0x533d78, struct.pack('<h', options.start_y))
    original.cpu.mem_write(0x5bd834, struct.pack('<I', options.elapsed))
    background = bytes((32, 48, 64, 255)) * (640 * 480)
    visible_frames = switches = 0
    packed_frames = 0
    texture = Texture()
    masks = (c.c_uint32 * 3)(0xff, 0xff00, 0xff0000)
    for step in range(16):
        previous_tokens = {h: struct.unpack_from('<I', bytes(s), 0xb0)[0] for h, s in actors.items()}
        original.cpu.mem_write(0x2000000, background)
        original.call(0x4b6200, eax=0x806000)
        assert original.cpu.reg_read(UC_X86_REG_EIP) == RETURN
try : original.call(0x4b6240, eax=0x806000, edx=0x802000)
        except RuntimeError as error:
            if 'did not reach its return boundary' not in str(error):
                raise
        if original.cpu.reg_read(UC_X86_REG_EIP) != RETURN:
            original.cpu.emu_start(original.cpu.reg_read(UC_X86_REG_EIP), RETURN, count=100000000)
        assert original.cpu.reg_read(UC_X86_REG_EIP) == RETURN
        destination = c.create_string_buffer(background, len(background))
        surface = Surface(c.addressof(destination), len(background), 640, 480, 2560, 4)
        completed = c.c_size_t()
        assert native.vertrix_ui_scene_frame_render_mapped(c.byref(listed), resolve, None,
            c.byref(options), c.byref(view.map), c.byref(surface), Clip(0, 639, 0, 479),
            c.byref(weights), None, c.byref(tables), c.byref(prepared), 1, c.byref(completed))
        assert completed.value == 26
        assert bytes(destination) == bytes(original.cpu.mem_read(0x2000000, len(background))), ('generated frame', step)
        visible_frames += bytes(destination) != background
        if bytes(destination) != background and packed_frames < 2:
            if packed_frames == 0:
                assert native.vertrix_frame_texture_init(c.byref(surface), masks, c.byref(texture))
                texture_pointer = texture.data
            else:
                assert native.vertrix_frame_texture_update(c.byref(surface), masks, c.byref(texture))
                assert texture.data == texture_pointer
            check_pixels(texture, bytes(destination), surface.stride, (0, 1, 2, 3))
            packed_frames += 1
        assert bytes(refresh) == bytes(original.cpu.mem_read(0x5bb714, 24))
        for handle, storage in actors.items():
            expected = bytearray(original.cpu.mem_read(handle, len(storage)))
            struct.pack_into('<I', expected, 0xb4, 0)
            assert bytes(storage) == bytes(expected), ('generated frame actor', step, handle)
            switches += previous_tokens[handle] != struct.unpack_from('<I', bytes(storage), 0xb0)[0]
    native.vertrix_palette_tables_free(c.byref(tables))
    native.vertrix_texture_free(c.byref(texture))
    invalid_storage = c.create_string_buffer(bytes(0x15c), 0x15c)
    before = bytes(invalid_storage)
    assert not native.vertrix_ui_artwork_actor_construct(invalid_storage, len(invalid_storage),
        12, 0, 0, 0, c.byref(view))
    assert bytes(invalid_storage) == before
    assert visible_frames and switches and packed_frames == 2
    return
    {
        'frames' : 16, 'visible_frames' : visible_frames,
                                          'bank_switches' : switches,
                                                            'texture_frames' : packed_frames
    }
