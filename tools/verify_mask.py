"""Verify the original binary PCX mask operation and direct VF composition."""
import argparse, ctypes, json, random, subprocess
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
    library = args.build_dir.resolve() / "mask.dylib"
    subprocess.run(["cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror", str(root / "source/image.c"), str(root / "source/vf.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_image_mask.argtypes = [ctypes.POINTER(NativeImage), ctypes.POINTER(Pcx)]
    native.vertrix_vf_open.argtypes = [ctypes.c_char_p]
    native.vertrix_vf_open.restype = ctypes.c_void_p
    native.vertrix_vf_close.argtypes = [ctypes.c_void_p]
    native.vertrix_vf_count.argtypes = [ctypes.c_void_p]
    native.vertrix_vf_name.argtypes = [ctypes.c_void_p, ctypes.c_uint32]
    native.vertrix_vf_name.restype = ctypes.c_char_p
    native.vertrix_image_pcx.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.POINTER(Pcx)]
    native.vertrix_pcx_free.argtypes = [ctypes.POINTER(Pcx)]
    native.vertrix_image_bmp.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.POINTER(NativeImage)]
    native.vertrix_image_bmp_masked.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p, ctypes.POINTER(NativeImage)]
    native.vertrix_image_free.argtypes = [ctypes.POINTER(NativeImage)]
    oracle = Original(args.executable)
    rng = random.Random(0x4797F0)
    def expected(data, indices):
        return b"".join(oracle.image_mask(data[start * 4: (start + 4096) * 4], indices[start: start + 4096]) for start in range(0, len(indices), 4096))
    def compare(indices):
        data = rng.randbytes(len(indices) * 4)
        pixels = ctypes.create_string_buffer(data)
        values = ctypes.create_string_buffer(indices)
        image = NativeImage(len(indices), 1, ctypes.cast(pixels, ctypes.c_void_p))
        mask = Pcx(len(indices), 1, ctypes.cast(values, ctypes.c_void_p))
        assert native.vertrix_image_mask(ctypes.byref(image), ctypes.byref(mask))
        assert pixels.raw[: len(data)] == expected(data, indices)
        return len(indices)
    compare(bytes(range(256)))
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    assets = pixels = pairs = pair_pixels = 0
    try:
        names = [native.vertrix_vf_name(archive, i) for i in range(native.vertrix_vf_count(archive))]
        lookup = {name.lower(): name for name in names}
        for name in names:
            if not name.lower().endswith(b".pcx"):
                continue
            mask = Pcx()
            assert native.vertrix_image_pcx(archive, name, ctypes.byref(mask))
            try:
                count = mask.width * mask.height
                indices = ctypes.string_at(mask.indices, count)
                pixels += compare(indices)
                assets += 1
                artwork = lookup.get(name.lower()[:-4] + b".bmp")
                if artwork:
                    source, combined = NativeImage(), NativeImage()
                    assert native.vertrix_image_bmp(archive, artwork, ctypes.byref(source))
                    try:
                        if (source.width, source.height) != (mask.width, mask.height):
                            assert not native.vertrix_image_bmp_masked(
                                archive, artwork, name, ctypes.byref(combined))
                            continue
                        assert native.vertrix_image_bmp_masked(archive, artwork, name,
                                                               ctypes.byref(combined))
                        data = ctypes.string_at(source.rgba, count * 4)
                        assert ctypes.string_at(combined.rgba, count * 4) == expected(data, indices)
                        pairs += 1
                        pair_pixels += count
                    finally:
                        native.vertrix_image_free(ctypes.byref(source))
                        native.vertrix_image_free(ctypes.byref(combined))
            finally:
                native.vertrix_pcx_free(ctypes.byref(mask))
    finally:
        native.vertrix_vf_close(archive)
    report = {"status": "passed", "mask_values_verified": 256, "pcx_assets_verified": assets, "pcx_pixels_verified": pixels, "matching_bmp_pcx_pairs_verified": pairs, "composed_artwork_pixels_verified": pair_pixels, "scope": "Original 0x4797f0 mask instructions execute unchanged; PCX decode and free " "boundaries supplied by oracle. Binary mask path only; graded effects and " "renderer remain separate."}
    (args.build_dir / "mask-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
if __name__ == "__main__":
    main()
