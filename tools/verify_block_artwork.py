"""Verify VF artwork ownership and runtime frame descriptor binding."""
import argparse
import ctypes as c
import json
import subprocess
from pathlib import Path
from verify_block_frames import BlockSet
from verify_frame_resource import Resource
from verify_image import NativeImage
from verify_animation import Animation
from verify_timer import Timer


class Artwork(c.Structure):
    _fields_ = [('set', BlockSet), ('descriptors', (c.c_uint32 * 8) * 7), ('resources', Resource * 7), ('ready', c.c_uint)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('archive', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / 'artwork.dylib'
    names = ['block_artwork.c', 'block_resource.c', 'frame_resource.c', 'animation.c', 'timer.c', 'assets.c', 'image.c', 'vf.c']
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror', * [str(root / 'source' / name) for name in names], '-o', str(library)], check=True)
    n = c.CDLL(str(library))
    n.vertrix_vf_open.argtypes = [c.c_char_p]
    n.vertrix_vf_open.restype = c.c_void_p
    n.vertrix_vf_close.argtypes = [c.c_void_p]
    n.vertrix_block_artwork_load.argtypes = [c.c_void_p, c.c_uint32, c.POINTER(c.c_uint32), c.POINTER(Artwork)]
    n.vertrix_block_artwork_free.argtypes = [c.POINTER(Artwork)]
    n.vertrix_block_artwork_image.argtypes = [c.POINTER(Artwork), c.c_uint32]
    n.vertrix_block_artwork_image.restype = c.POINTER(NativeImage)
    n.vertrix_asset_block_set.argtypes = [c.c_void_p, c.c_uint32, c.POINTER(c.c_uint32), c.POINTER(BlockSet)]
    n.vertrix_block_set_free.argtypes = [c.POINTER(BlockSet)]
    n.vertrix_block_resource_update.argtypes = [c.POINTER(Animation), c.POINTER(Resource), c.c_size_t, c.c_uint32, c.POINTER(c.c_uint32)]
    masks = (c.c_uint32 * 3)(0xff0000, 0xff00, 0xff)
    comparisons = 0
    for character in range(18):
        archive = n.vertrix_vf_open(str(args.archive.resolve()).encode())
        assert archive
        artwork, reference = Artwork(), BlockSet()
        try:
            assert n.vertrix_block_artwork_load(archive, character, masks, c.byref(artwork))
            assert n.vertrix_asset_block_set(archive, character, masks, c.byref(reference))
            before = bytes(artwork)
            assert not n.vertrix_block_artwork_load(archive, character, masks, c.byref(artwork))
            assert bytes(artwork) == before
        finally:
            n.vertrix_vf_close(archive)
    try:
        for color in range(7):
            animation = Animation(Timer(0, 1), 7, 8)
            descriptor = c.c_uint32()
            for frame in range(8):
                assert n.vertrix_block_resource_update(c.byref(animation), c.byref(artwork.resources[color]), 1, 1, c.byref(descriptor))
                assert animation.frame == frame
                image = n.vertrix_block_artwork_image(c.byref(artwork), descriptor.value)
                assert image and c.addressof(image.contents) == c.addressof(artwork.set.frames[color][frame])
                expected = reference.frames[color][frame]
                assert (image.contents.width, image.contents.height) == (24, 24)
                assert c.string_at(image.contents.rgba, 2304) == c.string_at(expected.rgba, 2304)
                comparisons += 1
            assert bytes(artwork.set.delays) == bytes(reference.delays)
            assert not n.vertrix_block_artwork_image(c.byref(artwork), 0)
            assert not n.vertrix_block_artwork_image(c.byref(artwork), 57)
    finally:
        n.vertrix_block_set_free(c.byref(reference))
        n.vertrix_block_artwork_free(c.byref(artwork))
        assert bytes(artwork) == bytes(c.sizeof(artwork))
        n.vertrix_block_artwork_free(c.byref(artwork))
    report = {'status': 'passed', 'characters': 18, 'bound_frames': comparisons, 'scope': 'Original VF character sets bound to native runtime resources; all ' 'frames match the separately verified asset loader after archive closure. ' 'Animation periods in this binding harness are fixtures, not gameplay defaults. ' 'No complete actor lifecycle, renderer integration or playable game is claimed.'}
    (args.build_dir / 'block-artwork-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
