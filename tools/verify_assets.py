"""Verify original animation-delay ranges read directly from the VF archive."""
import argparse
import ctypes
import hashlib
import json
import struct
import subprocess
from pathlib import Path
from original import Original
from verify_spawn import AnimationRange


class BlockFiles(ctypes.Structure):
    _fields_ = [("artwork", ctypes.c_char * 128), ("mask", ctypes.c_char * 128)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("archive", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / "assets.dylib"
    subprocess.run(["cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror", str(root / "source/assets.c"), str(root / "source/image.c"), str(root / "source/vf.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_vf_open.argtypes = [ctypes.c_char_p]
    native.vertrix_vf_open.restype = ctypes.c_void_p
    native.vertrix_vf_close.argtypes = [ctypes.c_void_p]
    native.vertrix_vf_find.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.POINTER(ctypes.c_uint32)]
    native.vertrix_vf_size.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint32)]
    native.vertrix_vf_read.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_void_p, ctypes.c_size_t]
    native.vertrix_asset_animation_ranges.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(AnimationRange)]
    native.vertrix_asset_block_files.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(BlockFiles)]
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    oracle = Original(args.executable)
    try:
        index, size = ctypes.c_uint32(), ctypes.c_uint32()
        assert native.vertrix_vf_find(archive, b"texte/BlocsSpeed.ini", ctypes.byref(index))
        assert native.vertrix_vf_size(archive, index, ctypes.byref(size))
        data = ctypes.create_string_buffer(size.value)
        assert native.vertrix_vf_read(archive, index, 0, data, size.value)
        rows = []
        for line in data.raw.decode("cp1252").splitlines():
            line = line.strip()
            if line and not line.startswith("/"):
                rows.append(tuple(int(value.strip()) for value in line.split("/")[0].split("\\")[: 14]))
        assert len(rows) == 20 and all(len(row) == 14 for row in rows)
        output = (AnimationRange * 7)()
        for character in range(20):
            assert native.vertrix_asset_animation_ranges(archive, character, output)
            actual = tuple((value.first, value.last) for value in output)
            assert actual == oracle.asset_animation_ranges(rows, character)
        saved = bytes(output)
        assert not native.vertrix_asset_animation_ranges(archive, 20, output)
        assert bytes(output) == saved
        digest = hashlib.sha256(data.raw).hexdigest()
        assert native.vertrix_vf_find(archive, b"texte/BlocsFileName.ini", ctypes.byref(index))
        assert native.vertrix_vf_size(archive, index, ctypes.byref(size))
        names = ctypes.create_string_buffer(size.value)
        assert native.vertrix_vf_read(archive, index, 0, names, size.value)
        configured = [line.strip().split(b"\\")[: 2] for line in names.raw.splitlines() if line.strip() and not line.strip().startswith(b"/")]
        assert len(configured) == 20
        available = missing = 0
        files = BlockFiles()
        for character, pair in enumerate(configured):
            assert native.vertrix_asset_block_files(archive, character, ctypes.byref(files))
            assert (files.artwork, files.mask) == tuple(b"image/Blocs/" + name for name in pair)
            present = all(native.vertrix_vf_find(archive, name, ctypes.byref(index)) for name in (files.artwork, files.mask))
            available += present
            missing += not present
        assert (available, missing) == (18, 2)
        saved_files = bytes(files)
        assert not native.vertrix_asset_block_files(archive, 20, ctypes.byref(files))
        assert bytes(files) == saved_files
    finally:
        native.vertrix_vf_close(archive)
    name = b"texte/BlocsSpeed.ini"
    row = b"72\\240\\" * 7 + b" / test\r\n"
    valid = b"/ comment\r\n" + row * 20
    malformed = [b"", row * 19, row * 21, valid.replace(b"72", b"x", 1), valid.replace(b"72", b"4294967296", 1), valid.replace(b"72\\240", b"240\\72", 1), valid.replace(b"72\\240", b"0\\65535", 1), valid.replace(b"72\\240\\", b"72\\240", 1)]
    for i, payload in enumerate(malformed + [valid]):
        path = args.build_dir / f"ranges-{i}.vf"
        path.write_bytes(struct.pack("<IIIII", 10, 1, len(payload), 20 + len(name), len(name)) + name + payload)
        archive = native.vertrix_vf_open(str(path.resolve()).encode())
        assert archive
        ctypes.memset(output, 0xA5, ctypes.sizeof(output))
        saved = bytes(output)
    try:
        success = native.vertrix_asset_animation_ranges(archive, 0, output)
        assert bool(success) == (i == len(malformed))
        if not success:
            assert bytes(output) == saved
    finally:
        native.vertrix_vf_close(archive)
    report = {"status": "passed", "asset_sha256": digest, "characters_verified": 20, "block_filename_rows_verified": 20, "available_block_pairs": available, "configured_missing_block_pairs": missing, "original_range_comparisons": 140, "malformed_assets_rejected": len(malformed), "scope": "Direct VF text loading and all original color-delay mappings; original text parser " "is not emulated, graphics decoding and runtime rendering remain separate"}
    (args.build_dir / "assets-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
if __name__ == "__main__":
    main()
