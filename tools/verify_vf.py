"""Verify direct VF reads against the independently extracted asset manifest."""
import argparse
import ctypes
import hashlib
import json
import struct
import subprocess
from pathlib import Path, PurePosixPath


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("archive", type=Path)
    parser.add_argument("manifest", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / "vf.dylib"
    subprocess.run(["cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror", str(root / "source/vf.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    handle = ctypes.c_void_p
    word = ctypes.c_uint32
    native.vertrix_vf_open.argtypes = [ctypes.c_char_p]
    native.vertrix_vf_open.restype = handle
    native.vertrix_vf_close.argtypes = [handle]
    native.vertrix_vf_count.argtypes = [handle]
    native.vertrix_vf_count.restype = word
    native.vertrix_vf_name.argtypes = [handle, word]
    native.vertrix_vf_name.restype = ctypes.c_char_p
    native.vertrix_vf_find.argtypes = [handle, ctypes.c_char_p, ctypes.POINTER(word)]
    native.vertrix_vf_size.argtypes = [handle, word, ctypes.POINTER(word)]
    native.vertrix_vf_read.argtypes = [handle, word, word, handle, ctypes.c_size_t]
    manifest = json.loads(args.manifest.read_text())
    archive_hash = hashlib.sha256(args.archive.read_bytes()).hexdigest()
    original = next(item for item in manifest["original"] if item["path"] == "Vertrix2.vf")
    assert archive_hash == original["sha256"]
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    checked_bytes = 0
    try:
        assert native.vertrix_vf_count(archive) == len(manifest["assets"])
        for i, item in enumerate(manifest["assets"]):
            name = str(PurePosixPath(native.vertrix_vf_name(archive, i).decode("cp1252").replace("\\", "/")))
            assert name == item["path"]
            index, size = word(), word()
#Original byte encoding; ASCII case folding only.
            lookup = bytes(c + 32 if 65 <= c <= 90 else c for c in name.replace("/", "\\").encode("cp1252"))
            assert native.vertrix_vf_find(archive, lookup, ctypes.byref(index)) and index.value == i
            assert native.vertrix_vf_size(archive, i, ctypes.byref(size)) and size.value == item["size"]
            data = ctypes.create_string_buffer(size.value)
            assert native.vertrix_vf_read(archive, i, 0, data, size.value)
            assert hashlib.sha256(data.raw).hexdigest() == item["sha256"]
            offset = size.value // 2
            partial = ctypes.create_string_buffer(size.value - offset)
            assert native.vertrix_vf_read(archive, i, offset, partial, len(partial))
            assert partial.raw == data.raw[offset:
                ]
            assert native.vertrix_vf_read(archive, i, size.value, None, 0)
            assert not native.vertrix_vf_read(archive, i, size.value, data, 1)
            checked_bytes += size.value
        assert not native.vertrix_vf_find(archive, b"missing/asset", ctypes.byref(index))
        assert not native.vertrix_vf_read(archive, len(manifest["assets"]), 0, None, 0)
    finally:
        native.vertrix_vf_close(archive)
#Malformed index / ranges, unsupported version, embedded NUL and truncation.
    fixtures = [b"", struct.pack("<II", 11, 0), struct.pack("<II", 10, 0xFFFFFFFF), struct.pack("<IIIII", 10, 1, 1, 0, 1) + b"a", struct.pack("<IIIII", 10, 1, 100, 21, 1) + b"a", struct.pack("<IIIII", 10, 1, 0, 21, 1) + b"\0", struct.pack("<IIIII", 10, 1, 0, 21, 100) + b"a"]
    for i, contents in enumerate(fixtures):
        path = args.build_dir / f"invalid-{i}.vf"
        path.write_bytes(contents)
        assert not native.vertrix_vf_open(str(path.resolve()).encode())
    report = {"status": "passed", "archive_sha256": archive_hash, "assets_verified": len(manifest["assets"]), "payload_bytes_verified": checked_bytes, "malformed_archives_rejected": len(fixtures), "scope": "Direct archive lookup/full/partial reads on host; Wii compilation separately"}
    (args.build_dir / "vf-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
if __name__ == "__main__":
    main()
