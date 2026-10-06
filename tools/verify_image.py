"""Verify direct VF bitmap decoding against Pillow pixel output."""
import argparse
import ctypes
import hashlib
import io
import json
import struct
import subprocess
from pathlib import Path
from PIL import Image


class NativeImage(ctypes.Structure):
    _fields_ = [("width", ctypes.c_uint32), ("height", ctypes.c_uint32), ("rgba", ctypes.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("archive", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / "image.dylib"
    subprocess.run(["cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror", str(root / "source/image.c"), str(root / "source/vf.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_vf_open.argtypes = [ctypes.c_char_p]
    native.vertrix_vf_open.restype = ctypes.c_void_p
    native.vertrix_vf_close.argtypes = [ctypes.c_void_p]
    native.vertrix_vf_count.argtypes = [ctypes.c_void_p]
    native.vertrix_vf_name.argtypes = [ctypes.c_void_p, ctypes.c_uint32]
    native.vertrix_vf_name.restype = ctypes.c_char_p
    native.vertrix_vf_size.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint32)]
    native.vertrix_vf_read.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_void_p, ctypes.c_size_t]
    native.vertrix_image_bmp.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.POINTER(NativeImage)]
    native.vertrix_image_free.argtypes = [ctypes.POINTER(NativeImage)]
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    verified, pixels = [], 0
    try:
        for index in range(native.vertrix_vf_count(archive)):
            name = native.vertrix_vf_name(archive, index)
            if not name.lower().endswith(b".bmp"):
                continue
            size = ctypes.c_uint32()
            assert native.vertrix_vf_size(archive, index, ctypes.byref(size))
            data = ctypes.create_string_buffer(size.value)
            assert native.vertrix_vf_read(archive, index, 0, data, size.value)
            reference = Image.open(io.BytesIO(data.raw)).convert("RGBA")
            image = NativeImage()
            assert native.vertrix_image_bmp(archive, name, ctypes.byref(image)), name
            try:
                assert (image.width, image.height) == reference.size
                actual = ctypes.string_at(image.rgba, image.width * image.height * 4)
                assert actual == reference.tobytes(), name
#Reject a nonempty destination without disturbing ownership.
                saved = bytes(image)
                assert not native.vertrix_image_bmp(archive, name, ctypes.byref(image))
                assert bytes(image) == saved
                pixels += image.width * image.height
                verified.append({"name": name.decode("cp1252"), "rgba_sha256": hashlib.sha256(actual).hexdigest()})
            finally:
                native.vertrix_image_free(ctypes.byref(image))
            assert not image.rgba and image.width == image.height == 0
            native.vertrix_image_free(ctypes.byref(image))
    finally:
        native.vertrix_vf_close(archive)
    def bitmap(width, height, top_down):
        stride = (width * 3 + 3) & ~ 3
        payload = bytes((i * 17 + 5) % 256 for i in range(stride * height))
        return struct.pack("<2sIHHI", b"BM", 54 + len(payload), 0, 0, 54) + struct.pack("<IiiHHIIiiII", 40, width, - height if top_down else height, 1, 24, 0, len(payload), 0, 0, 0, 0) + payload
    valid = [bitmap(w, h, top) for w in [1, 2, 3, 7] for h in [1, 2, 5] for top in [False, True]]
    base = bitmap(2, 2, False)
    invalid = [b"", b"ZZ" + base[2:], base[: - 1]]
    for offset, fmt, value in [(14, "I", 12), (18, "i", 0), (18, "i", - 1), (22, "i", 0), (22, "i", - 2147483648), (26, "H", 2), (28, "H", 8), (30, "I", 1), (10, "I", 53), (10, "I", 0xFFFFFFFF), (18, "i", 2147483647)]:
        data = bytearray(base)
        struct.pack_into("<" + fmt, data, offset, value)
        invalid.append(bytes(data))
    name = b"image.bmp"
    for i, contents in enumerate(valid + invalid):
        path = args.build_dir / f"bitmap-{i}.vf"
        path.write_bytes(struct.pack("<IIIII", 10, 1, len(contents), 20 + len(name), len(name)) + name + contents)
        archive = native.vertrix_vf_open(str(path.resolve()).encode())
        assert archive
        image = NativeImage()
        try:
            success = native.vertrix_image_bmp(archive, name, ctypes.byref(image))
            assert bool(success) == (i < len(valid)), i
            if success:
                reference = Image.open(io.BytesIO(contents)).convert("RGBA")
                assert ctypes.string_at(image.rgba, image.width * image.height * 4) == reference.tobytes()
            else:
                assert not image.rgba and image.width == image.height == 0
        finally:
            native.vertrix_image_free(ctypes.byref(image))
            native.vertrix_vf_close(archive)
    report = {"status": "passed", "original_bitmaps_verified": len(verified), "original_pixels_verified": pixels, "layout_fixtures_verified": len(valid), "invalid_bitmaps_rejected": len(invalid), "scope": "All original 24-bit BMP pixels read directly from VF, compared with Pillow; " "masks, JPG/PCX decoding and Wii texture/render integration remain separate", "images": verified}
    (args.build_dir / "image-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({key: value for key, value in report.items() if key != "images"}, indent=2))
if __name__ == "__main__":
    main()
