"""Verify original block sheet resource/frame ordering and VF pixel slicing."""
import argparse
import ctypes
import json
import subprocess
from pathlib import Path
from original import Original
from verify_assets import BlockFiles
from verify_image import NativeImage
from verify_spawn import AnimationRange

class BlockSet(ctypes.Structure):
    _fields_ = [("frames", (NativeImage * 8) * 7), ("delays", AnimationRange * 7)]

class Texture(ctypes.Structure):
    _fields_ = [("width", ctypes.c_uint32), ("height", ctypes.c_uint32),
               ("storage_width", ctypes.c_uint32), ("storage_height", ctypes.c_uint32),
               ("size", ctypes.c_size_t), ("data", ctypes.c_void_p), ("allocation", ctypes.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("archive", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / "block-frames.dylib"
    subprocess.run(["rtk", "proxy", "cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror",
                    *(str(root / "source" / name) for name in ("image.c", "assets.c", "vf.c", "texture.c")),
                    "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_vf_open.argtypes = [ctypes.c_char_p]
    native.vertrix_vf_open.restype = ctypes.c_void_p
    native.vertrix_vf_close.argtypes = [ctypes.c_void_p]
    native.vertrix_asset_block_files.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(BlockFiles)]
    native.vertrix_image_bmp_masked.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p, ctypes.POINTER(NativeImage)]
    native.vertrix_image_block_frame.argtypes = [ctypes.POINTER(NativeImage), ctypes.c_uint32,
                                               ctypes.c_uint32, ctypes.POINTER(NativeImage)]
    native.vertrix_image_free.argtypes = [ctypes.POINTER(NativeImage)]
    native.vertrix_asset_block_set.argtypes = [ctypes.c_void_p, ctypes.c_uint32,
                                              ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(BlockSet)]
    native.vertrix_block_set_free.argtypes = [ctypes.POINTER(BlockSet)]
    native.vertrix_asset_animation_ranges.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(AnimationRange)]
    native.vertrix_texture_rgba8.argtypes = [ctypes.POINTER(NativeImage), ctypes.POINTER(Texture)]
    native.vertrix_texture_free.argtypes = [ctypes.POINTER(Texture)]
    def verify_texture(image):
        texture = Texture()
        assert native.vertrix_texture_rgba8(ctypes.byref(image), ctypes.byref(texture))
try : assert texture.data % 32 == 0
            raw = ctypes.string_at(texture.data, texture.size)
            source = ctypes.string_at(image.rgba, image.width * image.height * 4)
            for y in range(texture.storage_height):
                for x in range(texture.storage_width):
                    block = ((y // 4) * (texture.storage_width // 4) + x // 4) * 64
                    offset = block + ((y % 4) * 4 + x % 4) * 2
                    decoded = bytes((raw[offset + 1], raw[offset + 32], raw[offset + 33], raw[offset]))
                    expected = source[(y * image.width + x) * 4:(y * image.width + x + 1) * 4] if x < image.width and y < image.height else bytes(4)
                    assert decoded == expected
        finally:
            native.vertrix_texture_free(ctypes.byref(texture))
        assert bytes(texture) == bytes(ctypes.sizeof(texture))
    for width, height in ((1, 1), (3, 5), (4, 4), (8, 9), (17, 13)):
        buffer = ctypes.create_string_buffer(bytes(i % 256 for i in range(width * height * 4)))
        verify_texture(NativeImage(width, height, ctypes.cast(buffer, ctypes.c_void_p)))
    oracle = Original(args.executable)
    layout = {}
    for column in range(7):
        records = oracle.block_frame_layout(column)
        assert len(records) == 8
        for color, frame, x, y in records:
            assert (color, frame) not in layout
            layout[color, frame] = (x, y)
    assert len(layout) == 56
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    frames = pixels = 0
    try:
        for character in range(18):
            files, sheet = BlockFiles(), NativeImage()
            assert native.vertrix_asset_block_files(archive, character, ctypes.byref(files))
            assert native.vertrix_image_bmp_masked(archive, files.artwork, files.mask, ctypes.byref(sheet))
            resources = BlockSet()
            masks = (ctypes.c_uint32 * 3)(0xFF0000, 0xFF00, 0xFF)
            assert native.vertrix_asset_block_set(archive, character, masks, ctypes.byref(resources))
            delays = (AnimationRange * 7)()
            assert native.vertrix_asset_animation_ranges(archive, character, delays)
            assert bytes(resources.delays) == bytes(delays)
            try:
                data = ctypes.string_at(sheet.rgba, sheet.width * sheet.height * 4)
                for (color, frame), (x, y) in layout.items():
                    image = NativeImage()
                    assert native.vertrix_image_block_frame(ctypes.byref(sheet), color, frame, ctypes.byref(image))
                    try:
                        expected = b"".join(data[((y + row) * sheet.width + x) * 4:
                                                 ((y + row) * sheet.width + x + 24) * 4]
                                            for row in range(24))
                        assert (image.width, image.height) == (24, 24)
                        assert ctypes.string_at(image.rgba, 24 * 24 * 4) == expected
                        loaded = resources.frames[color][frame]
                        assert (loaded.width, loaded.height) == (24, 24)
                        assert ctypes.string_at(loaded.rgba, 24 * 24 * 4) == expected
                        verify_texture(loaded)
                        frames += 1
                        pixels += 24 * 24
                    finally:
                        native.vertrix_image_free(ctypes.byref(image))
                for color, frame in ((7, 0), (0, 8), (0xFFFFFFFF, 0)):
                    image = NativeImage()
                    assert not native.vertrix_image_block_frame(ctypes.byref(sheet), color, frame, ctypes.byref(image))
                    assert not image.rgba
            finally:
                native.vertrix_image_free(ctypes.byref(sheet))
                native.vertrix_block_set_free(ctypes.byref(resources))
                assert bytes(resources) == bytes(ctypes.sizeof(resources))
        for character in (18, 19, 20):
            resources = BlockSet()
            resources.delays[0].first = 123
            saved = bytes(resources)
            assert not native.vertrix_asset_block_set(archive, character, masks, ctypes.byref(resources))
            assert bytes(resources) == saved
        invalid_masks = (ctypes.c_uint32 * 3)(0, 0xFF00, 0xFF)
        assert not native.vertrix_asset_block_set(archive, 0, invalid_masks, ctypes.byref(resources))
        assert bytes(resources) == saved
    finally:
        native.vertrix_vf_close(archive)
    report = {"status": "passed", "original_frame_layouts_verified": len(layout),
              "character_sheets_verified": 18, "frames_verified": frames, "pixels_verified": pixels,
              "integrated_character_sets_verified": 18,
              "gx_texture_frames_verified": frames, "gx_padding_layouts_verified": 5,
              "scope": "Original 0x45f0c0 resource/frame/coordinate selection executes with allocation, copy and color-conversion boundaries intercepted. Native crops match these rectangles in directly loaded VF sheets. Renderer remains separate."}
    (args.build_dir / "block-frames-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
