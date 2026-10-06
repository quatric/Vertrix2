"""Check owned startup-bank/artwork integration and published pointer lifetimes."""
import argparse
import ctypes as c
import json
from pathlib import Path
import subprocess
from verify_sprite_load_set import LoadSet, Binding, Map
from verify_sprite_load_plan import Selection
from verify_ui_artwork import Artwork
from verify_ui_artwork_render import View
from verify_ui_sprite_vf import Bank
from verify_sprite_clone import Frame


class Resources(c.Structure):
    _fields_ = [('sprites', LoadSet), ('artwork', Artwork), ('view', View),
                ('border', Frame), ('border_bank', Bank),
                ('bindings', Binding*23), ('map', Map), ('ready', c.c_uint)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('archive', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = build / 'sprite-resources.dylib'
    sources = [p for p in sorted((root/'source').glob('*.c')) if not p.name.startswith('wii_')]
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    *map(str, sources), '-lm', '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_vf_open.argtypes = [c.c_char_p]
    native.vertrix_vf_open.restype = c.c_void_p
    native.vertrix_vf_close.argtypes = [c.c_void_p]
    native.vertrix_sprite_selection_init.argtypes = [c.POINTER(Selection)]
    native.vertrix_sprite_resources_load.argtypes = [c.c_void_p, c.POINTER(Selection),
        c.POINTER(c.c_uint32), c.c_uint32, c.POINTER(Resources)]
    native.vertrix_sprite_resources_free.argtypes = [c.POINTER(Resources)]
    native.vertrix_ui_artwork_load.argtypes = [c.c_void_p, c.c_char_p, c.POINTER(c.c_uint32),
        c.c_size_t, c.c_uint32, c.POINTER(Artwork)]
    native.vertrix_ui_artwork_free.argtypes = [c.POINTER(Artwork)]
    native.vertrix_ui_border_artwork_build.argtypes = [c.POINTER(Bank), c.POINTER(Bank),
        c.c_uint32, c.c_uint32, c.POINTER(Frame)]
    native.vertrix_sprite_free.argtypes = [c.POINTER(Frame)]
    pixels = 0
    for case in range(8):
        archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
        assert archive
        selection = Selection()
        assert native.vertrix_sprite_selection_init(c.byref(selection))
        selection.first_source = 9 if case&1 else 0
        selection.artwork_source = 0 if case&2 else 34
        masks = (c.c_uint32*3)(*((0xff0000,0xff00,0xff) if case&4 else (0xff,0xff00,0xff0000)))
        loaded = Resources()
        assert native.vertrix_sprite_resources_load(archive, c.byref(selection), masks,
                                                    0x04000000, c.byref(loaded))
        reference = Artwork()
        assert native.vertrix_ui_artwork_load(archive, b'sprite/damier.spr', masks,
            selection.first_source, selection.artwork_source, c.byref(reference))
        before = bytes(loaded)
        assert not native.vertrix_sprite_resources_load(archive, c.byref(selection), masks,
                                                        0x04000000, c.byref(loaded))
        assert bytes(loaded) == before
        native.vertrix_vf_close(archive)
        assert loaded.ready and loaded.map.count == 23
        assert loaded.bindings[22].token == 0x5466a4
        assert c.addressof(loaded.bindings[22].bank.contents) == c.addressof(loaded.border_bank)
        assert loaded.border_bank.count == 1
        assert c.addressof(loaded.border_bank.frames.contents) == c.addressof(loaded.border)
        border_reference = Frame()
        assert native.vertrix_ui_border_artwork_build(c.byref(loaded.sprites.banks[2]),
            c.byref(loaded.sprites.banks[16]), selection.border_source, 0x04000000,
            c.byref(border_reference))
        assert tuple(loaded.border.metadata) == tuple(border_reference.metadata)
        a, b = loaded.border.image, border_reference.image
        assert (a.width, a.height) == (b.width, b.height)
        assert c.string_at(a.rgba, a.width*a.height*4) == c.string_at(b.rgba, b.width*b.height*4)
        pixels += a.width*a.height
        native.vertrix_sprite_free(c.byref(border_reference))
        assert c.addressof(loaded.map.bindings.contents) == c.addressof(loaded.bindings)
        assert c.addressof(loaded.sprites.map.bindings.contents) == c.addressof(loaded.sprites.bindings)
        for index in range(20):
            assert c.addressof(loaded.bindings[index].bank.contents) == c.addressof(loaded.sprites.banks[index])
            assert c.addressof(loaded.sprites.bindings[index].bank.contents) == c.addressof(loaded.sprites.banks[index])
            assert loaded.bindings[index].token == loaded.sprites.bindings[index].token
        assert c.addressof(loaded.view.map.bindings.contents) == c.addressof(loaded.view.bindings)
        for index in range(2):
            a, b = loaded.artwork.images[index], reference.images[index]
            assert (a.width, a.height) == (b.width, b.height)
            assert c.string_at(a.rgba, a.width*a.height*4) == c.string_at(b.rgba, b.width*b.height*4)
            assert loaded.artwork.origin_x[index] == reference.origin_x[index]
            assert loaded.artwork.origin_y[index] == reference.origin_y[index]
            assert loaded.bindings[20+index].token == (0x546618 if index==0 else 0x546634)
            assert c.addressof(loaded.bindings[20+index].bank.contents) == c.addressof(loaded.view.banks[index])
            assert c.addressof(loaded.view.banks[index].frames.contents) == c.addressof(loaded.view.frames[index])
            assert c.addressof(loaded.view.bindings[index].sprites.contents) == c.addressof(loaded.view.banks[index])
            assert c.addressof(loaded.view.resources[index].frames.contents) == c.addressof(loaded.view.descriptors)+index*4
            assert c.addressof(loaded.view.frames[index].image.rgba.contents) == c.addressof(a.rgba.contents)
            pixels += a.width*a.height
        native.vertrix_ui_artwork_free(c.byref(reference))
        native.vertrix_sprite_resources_free(c.byref(loaded))
        assert bytes(loaded) == bytes(Resources())
        native.vertrix_sprite_resources_free(c.byref(loaded))
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    for case in range(5):
            selection = Selection() native.vertrix_sprite_selection_init(c.byref(selection))
                            loaded = Resources() format_word = 0x04000000 if case == 0:
            selection.artwork_source = 0xffffffff if case == 1:
            selection.settings[16] = 11 #Arrow bank lacks stencil frame9.if case == 2:
            selection.settings[18] = 22 #Missing last direct bank.if case == 3:
            format_word = 0x03000000 if case == 4:
            selection.border_source = 0xffffffff assert not native.vertrix_sprite_resources_load(
                                          archive, c.byref(selection), masks, format_word,
                                          c.byref(loaded)) assert
                                      bytes(loaded) ==
                                      bytes(Resources()) native.vertrix_vf_close(archive)
                                          report = {
                'status' : 'passed',
                'integrated_resource_sets' : 8,
                'published_bindings_checked' : 184,
                'generated_pixels_compared' : pixels,
                'failure_preservation_cases' : 5,
                'scope' :
                    'Selected20 VF banks plus solid/hollow and additional border artwork match the separately original-verified ' 'artwork path. All published internal pointers are rebased into the final live ' 'context and remain valid after archive closure. Occupied/invalid output rejection ' 'and repeated free checked. Full startup, actor creation, scene/gameplay and Wii ' 'execution remain separate.'
            }(build / 'sprite-resources-verification.json')
                                                       .write_text(json.dumps(report, indent = 2) +
                                                                   '\n')
                                                           print(json.dumps(report, indent = 2))

                                                               if __name__
                                                   == '__main__' : main()
