"""Execute original sprite color-order processing against native RGBA images."""
import argparse
import ctypes
import itertools
import json
import random
import subprocess
from pathlib import Path
from original import Original
from verify_image import NativeImage
from verify_sprite import SpriteFrame


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("archive", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / "color-order.dylib"
    subprocess.run(["rtk", "proxy", "cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror",
                    str(root / "source/image.c"), str(root / "source/vf.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_image_color_order.argtypes = [ctypes.POINTER(NativeImage), ctypes.POINTER(ctypes.c_uint32)]
    native.vertrix_vf_open.argtypes = [ctypes.c_char_p]
    native.vertrix_vf_open.restype = ctypes.c_void_p
    native.vertrix_vf_close.argtypes = [ctypes.c_void_p]
    native.vertrix_vf_count.argtypes = [ctypes.c_void_p]
    native.vertrix_vf_name.argtypes = [ctypes.c_void_p, ctypes.c_uint32]
    native.vertrix_vf_name.restype = ctypes.c_char_p
    native.vertrix_image_sprite.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_uint32, ctypes.POINTER(SpriteFrame)]
    native.vertrix_sprite_free.argtypes = [ctypes.POINTER(SpriteFrame)]
    native.vertrix_image_sprite_processed.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_uint32,
                                                     ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(SpriteFrame)]
    oracle = Original(args.executable)

    def expected(data, masks):
        return b"".join(oracle.image_color_order(data[start:start + 16384], masks)
                        for start in range(0, len(data), 16384))

    rng = random.Random(0x483ED0)
    data = rng.randbytes(4096)
    layouts = list(itertools.permutations((0xFF0000, 0xFF00, 0xFF)))
    layouts += list(itertools.permutations((0xF800, 0x7E0, 0x1F)))
    for masks in layouts:
        buffer = ctypes.create_string_buffer(data)
        image = NativeImage(len(data) // 4, 1, ctypes.cast(buffer, ctypes.c_void_p))
        assert native.vertrix_image_color_order(ctypes.byref(image), (ctypes.c_uint32 * 3)(*masks))
        assert buffer.raw[:len(data)] == expected(data, masks), masks

    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    frames, pixels = 0, 0
    masks = (0xFF0000, 0xFF00, 0xFF)
    try:
        for index in range(native.vertrix_vf_count(archive)):
            name = native.vertrix_vf_name(archive, index)
            if not name.lower().endswith(b".spr"):
                continue
            frame_index = 0
            while True:
                frame = SpriteFrame()
                assert native.vertrix_image_sprite(archive, name, frame_index, ctypes.byref(frame))
                try:
                    count = frame.image.width * frame.image.height
                    original = ctypes.string_at(frame.image.rgba, count * 4)
                    assert native.vertrix_image_color_order(ctypes.byref(frame.image), (ctypes.c_uint32 * 3)(*masks))
                    assert ctypes.string_at(frame.image.rgba, count * 4) == expected(original, masks)
                    processed = SpriteFrame()
                    assert native.vertrix_image_sprite_processed(archive, name, frame_index,
                                                                 (ctypes.c_uint32 * 3)(*masks), ctypes.byref(processed))
                    try:
                        normalized = b"".join(oracle.image_binary_alpha(original[start:start + 16384])
                                               for start in range(0, len(original), 16384))
                        assert ctypes.string_at(processed.image.rgba, count * 4) == expected(normalized, masks)
                        assert processed.frame_count == frame.frame_count
                        assert tuple(processed.metadata) == tuple(frame.metadata)
                    finally:
                        native.vertrix_sprite_free(ctypes.byref(processed))
                    frames += 1
                    pixels += count
                    frame_count = frame.frame_count
                finally:
                    native.vertrix_sprite_free(ctypes.byref(frame))
                frame_index += 1
                if frame_index == frame_count:
                    break
    finally:
        native.vertrix_vf_close(archive)
    for invalid in ((0, 0xFF00, 0xFF), (0xFF, 0xFF, 0xFF0000)):
        buffer = ctypes.create_string_buffer(data)
        image = NativeImage(len(data) // 4, 1, ctypes.cast(buffer, ctypes.c_void_p))
        assert not native.vertrix_image_color_order(ctypes.byref(image), (ctypes.c_uint32 * 3)(*invalid))
        assert buffer.raw[:len(data)] == data
    report = {"status": "passed", "destination_layouts_verified": len(layouts),
              "random_pixels_verified": len(layouts) * len(data) // 4,
              "original_sprite_frames_verified": frames, "original_sprite_pixels_verified": pixels,
              "processed_vf_sprite_frames_verified": frames,
              "scope": "Original full 0x483ed0 and its format constructor/conversion execute unchanged; fixed four-byte source, nonzero masks with distinct trailing bit positions. Screen format selection and renderer blending remain separate."}
    (args.build_dir / "color-order-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
