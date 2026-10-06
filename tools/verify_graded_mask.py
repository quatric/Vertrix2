"""Verify graded PCX mask arithmetic using the original lookup initializer."""
import argparse
import ctypes
import json
import random
import subprocess
from pathlib import Path
from original import Original
from verify_image import NativeImage
from verify_pcx import Pcx


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("archive", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / "graded-mask.dylib"
    subprocess.run(["cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror", str(root / "source/image.c"), str(root / "source/vf.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_image_mask_graded.argtypes = [ctypes.POINTER(NativeImage), ctypes.POINTER(Pcx), ctypes.c_int32]
    native.vertrix_vf_open.argtypes = [ctypes.c_char_p]
    native.vertrix_vf_open.restype = ctypes.c_void_p
    native.vertrix_vf_close.argtypes = [ctypes.c_void_p]
    native.vertrix_vf_count.argtypes = [ctypes.c_void_p]
    native.vertrix_vf_name.argtypes = [ctypes.c_void_p, ctypes.c_uint32]
    native.vertrix_vf_name.restype = ctypes.c_char_p
    native.vertrix_image_pcx.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.POINTER(Pcx)]
    native.vertrix_pcx_free.argtypes = [ctypes.POINTER(Pcx)]
    oracle = Original(args.executable)
    rng = random.Random(0x4798B0)
    def compare(data, indices, offset):
        pixels = ctypes.create_string_buffer(data)
        values = ctypes.create_string_buffer(indices)
        image = NativeImage(len(indices), 1, ctypes.cast(pixels, ctypes.c_void_p))
        mask = Pcx(len(indices), 1, ctypes.cast(values, ctypes.c_void_p))
        assert native.vertrix_image_mask_graded(ctypes.byref(image), ctypes.byref(mask), offset)
        expected = b"".join(oracle.image_mask(data[start * 4: (start + 4096) * 4], indices[start: start + 4096], offset) for start in range(0, len(indices), 4096))
        assert pixels.raw[: len(data)] == expected, offset
    indices = b"".join(bytes([alpha]) * 256 for alpha in range(256))
    colors = bytes(channel for alpha in range(256) for value in range(256) for channel in (value, 255 - value, value ^ alpha, alpha))
    compare(colors, indices, 0)
    offsets = (- 2147483648, - 65537, - 65536, - 256, - 255, - 1, 0, 1, 254, 255, 65534, 65535, 65536, 2147483647)
    for offset in offsets:
        compare(rng.randbytes(1024), bytes(range(256)), offset)
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    assets = pixels = 0
    try:
        for index in range(native.vertrix_vf_count(archive)):
            name = native.vertrix_vf_name(archive, index)
            if not name.lower().endswith(b".pcx"):
                continue
            mask = Pcx()
            assert native.vertrix_image_pcx(archive, name, ctypes.byref(mask))
            try:
                count = mask.width * mask.height
                indices = ctypes.string_at(mask.indices, count)
                compare(rng.randbytes(count * 4), indices, offsets[assets % len(offsets)])
                pixels += count
                assets += 1
            finally:
                native.vertrix_pcx_free(ctypes.byref(mask))
    finally:
        native.vertrix_vf_close(archive)
    report = {"status": "passed", "channel_alpha_pairs_verified": 65536, "offsets_verified": list(offsets), "pcx_assets_verified": assets, "pcx_pixels_verified": pixels, "scope": "Original table initializer 0x4807ea..0x48087a and mask routine 0x4798b0 execute " "unchanged. Decoder/free boundaries supplied; runtime effect selection and " "rendering remain separate."}
    (args.build_dir / "graded-mask-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
if __name__ == "__main__":
    main()
