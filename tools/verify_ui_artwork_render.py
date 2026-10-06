"""Draw actual generated UI artwork against the original mapped banks."""
import ctypes as c
import random
import struct
from original import RETURN
from verify_sprite_clone import Frame
from verify_ui_sprite_vf import Bank
from verify_actor_render_draw import BankBinding, BankMap
from verify_frame_resource import Resource
from verify_render_rectangle import Surface
from verify_render_geometry import Clip
from verify_render_preparation import Preparation
from unicorn.x86_const import UC_X86_REG_EIP


class View(c.Structure):
    _fields_ = [('frames', Frame * 2), ('banks', Bank * 2), ('bindings', BankBinding * 2), ('map', BankMap), ('descriptors', c.c_uint32 * 2), ('resources', Resource * 2), ('ready', c.c_uint)]


def verify(native, original, artwork, case_seed):
    native.vertrix_ui_artwork_render_view.argtypes = [c.c_void_p, c.c_uint32, c.POINTER(View)]
    native.vertrix_sprite_actor_draw_mapped32.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(BankMap), c.POINTER(Surface), Clip, c.c_void_p, c.c_void_p, c.c_void_p, c.POINTER(Preparation)]
    view = View()
    descriptors = []
    for token in (0x546618, 0x546634):
        table = struct.unpack('<I', original.cpu.mem_read(token, 4))[0]
        descriptors.append(struct.unpack('<I', original.cpu.mem_read(table, 4))[0])
    formats = [struct.unpack('<I', original.cpu.mem_read(d + 36, 4))[0] for d in descriptors]
    assert formats[0] == formats[1]
    assert native.vertrix_ui_artwork_render_view(c.byref(artwork), formats[0], c.byref(view))
    for index in range(2):
        assert bytes(view.frames[index].metadata)[4:
            ] == bytes(original.cpu.mem_read(descriptors[index] + 4, 36))
        assert c.addressof(view.frames[index].image.rgba.contents) == c.addressof(artwork.images[index].rgba.contents)
        assert view.resources[index].count == 1 and view.resources[index].frames[0] == 0
    before = bytes(view)
    assert not native.vertrix_ui_artwork_render_view(c.byref(artwork), formats[0], c.byref(view))
    assert bytes(view) == before
    invalid = View()
    assert not native.vertrix_ui_artwork_render_view(c.byref(artwork), 0x02010000, c.byref(invalid))
    assert bytes(invalid) == bytes(View())
    original.call(0x4b9050)
    rng = random.Random(0x45e490 + case_seed)
    for case in range(128):
        actor = bytearray(0x15c)
        struct.pack_into('<H', actor, 14, rng.randrange(- 10, 151) & 65535)
        struct.pack_into('<H', actor, 22, rng.randrange(- 10, 151) & 65535)
        struct.pack_into('<H', actor, 30, rng.randrange(- 5, 6) & 65535)
        actor[0x44], actor[0x4e], actor[0x52], actor[0x8e] = rng.choice((8, 16)), 100, 13, 1
        struct.pack_into('<I', actor, 0xb0, (0x546618, 0x546634)[case % 2])
        struct.pack_into('<I', actor, 0xb4, 0xdeadbeef)
        struct.pack_into('<I', actor, 0x134, 1)
        struct.pack_into('<I', actor, 0x13c, 1)
        struct.pack_into('<I', actor, 0x144, 1)
#Binary default path avoids borrowing uninitialized alpha tables.
        struct.pack_into('<I', actor, 0x150, 0)
        target = bytearray(40)
        struct.pack_into('<3I', target, 0, 0x2000000, 128, 128)
        target[12: 14] = bytes((4, 4))
        struct.pack_into('<I', target, 20, 512)
        initial = rng.randbytes(128 * 128 * 4)
        original.cpu.mem_write(0x800000, bytes(actor))
        original.cpu.mem_write(0x802000, bytes(target))
        original.cpu.mem_write(0x2000000, initial)
        original.call(0x4ac8a0, eax=0x800000)
        original.call(0x4af8c0, eax=0x800000, edx=0x802000)
        if original.cpu.reg_read(UC_X86_REG_EIP) != RETURN:
            original.cpu.emu_start(original.cpu.reg_read(UC_X86_REG_EIP), RETURN, count=100000000)
            assert original.cpu.reg_read(UC_X86_REG_EIP) == RETURN
        destination = c.create_string_buffer(initial, len(initial))
        surface = Surface(c.addressof(destination), len(initial), 128, 128, 512, 4)
        storage = c.create_string_buffer(bytes(actor), len(actor))
        prepared = Preparation()
        result = native.vertrix_sprite_actor_draw_mapped32(storage, len(actor), c.byref(view.map), c.byref(surface), Clip(0, 127, 0, 127), None, None, None, c.byref(prepared))
        assert result in (0, 1), (case_seed, case, result)
        assert bytes(destination) == bytes(original.cpu.mem_read(0x2000000, len(initial))), (case_seed, case)
        expected_actor = bytearray(original.cpu.mem_read(0x800000, len(actor)))
        struct.pack_into('<I', expected_actor, 0xb4, 0)
        assert bytes(storage) == bytes(expected_actor)
    return 128
