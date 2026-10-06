"""Compare original sprite-load alpha normalization with native pixels."""
import argparse
import ctypes
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
    library = args.build_dir.resolve() / "alpha.dylib"
    subprocess.run(["rtk", "proxy", "cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror",
                    str(root / "source/image.c"), str(root / "source/vf.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_image_binary_alpha.argtypes = [ctypes.POINTER(NativeImage)]
    native.vertrix_vf_open.argtypes = [ctypes.c_char_p]
    native.vertrix_vf_open.restype = ctypes.c_void_p
    native.vertrix_vf_close.argtypes = [ctypes.c_void_p]
    native.vertrix_vf_count.argtypes = [ctypes.c_void_p]
    native.vertrix_vf_name.argtypes = [ctypes.c_void_p, ctypes.c_uint32]
    native.vertrix_vf_name.restype = ctypes.c_char_p
    native.vertrix_image_sprite.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_uint32, ctypes.POINTER(SpriteFrame)]
    native.vertrix_sprite_free.argtypes = [ctypes.POINTER(SpriteFrame)]
    oracle = Original(args.executable)
    def expected(data):
        return b"".join(oracle.image_binary_alpha(data[start:start + 16384])
                        for start in range(0, len(data), 16384))
    rng = random.Random(0x483750)
    fixtures = [b"".join(bytes([alpha ^ 255, (alpha * 13) % 256, alpha, alpha]) for alpha in range(256))]
    fixtures += [rng.randbytes(16384) for _ in range(32)]
    for data in fixtures:
        buffer = ctypes.create_string_buffer(data)
        image = NativeImage(len(data) // 4, 1, ctypes.cast(buffer, ctypes.c_void_p))
        assert native.vertrix_image_binary_alpha(ctypes.byref(image))
        assert buffer.raw[:len(data)] == expected(data)
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    frames, pixels = 0, 0
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
                    assert native.vertrix_image_binary_alpha(ctypes.byref(frame.image))
                    actual = ctypes.string_at(frame.image.rgba, count * 4)
                    assert actual == expected(original)
                    assert all(actual[i:i + 3] == original[i:i + 3] for i in range(0, len(actual), 4))
                    pixels += count
                    frames += 1
                    frame_count = frame.frame_count
                finally:
                    native.vertrix_sprite_free(ctypes.byref(frame))
                frame_index += 1
                if frame_index == frame_count:
                    break
    finally:
        native.vertrix_vf_close(archive)
    empty = NativeImage()
    assert not native.vertrix_image_binary_alpha(ctypes.byref(empty))
    report = {"status": "passed", "alpha_values_verified": 256, "random_pixels_verified": 32 * 4096,
              "original_sprite_frames_verified": frames, "original_sprite_pixels_verified": pixels,
              "scope": "Original 0x483750 executes unchanged for all pixels; color-format conversion, PCX mask attachment, blending and Wii rendering remain separate"}
    (args.build_dir / "alpha-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))

if __name__ == "__main__":
    main()
