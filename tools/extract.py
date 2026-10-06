"""Extract and verify the supplied installer and its original asset container."""

import argparse
import hashlib
import io
import json
import struct
from pathlib import Path, PurePosixPath

import acefile

INSTALLER_SHA256 = "bfacbaced5ba069c2b7561a63ed0fd1462d846b46d037dfde6d8a2a59cf9ce16"


def safe_name(name):
    path = PurePosixPath(name.replace("\\", "/"))
    if path.is_absolute() or ".." in path.parts or ":" in name:
        raise ValueError(f"Unsafe archive name: {name!r}")
    return Path(*path.parts)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("installer", type=Path)
    parser.add_argument("destination", type=Path)
    args = parser.parse_args()
    data = args.installer.expanduser().read_bytes()
    if hashlib.sha256(data).hexdigest() != INSTALLER_SHA256:
        raise ValueError("Installer differs from the examined Vertrix 2 v2.0 package")
    signature = data.index(b"**ACE**")
    archive_data = bytearray(data[signature - 7 :])
    crc, size = struct.unpack_from("<HH", archive_data)
    if acefile.ace_crc16(archive_data[4 : 4 + size]) != crc:
        raise ValueError("Original archive header checksum failed")
#The SFX main header has an extra byte before its unused comment length.
#Disable only the comment flag in this in - memory copy.Payloads, file
#headers, and their original CRCs remain intact and are checked by acefile.
    flags = struct.unpack_from("<H", archive_data, 5)[0]
    struct.pack_into("<H", archive_data, 5, flags & ~2)
    struct.pack_into("<H", archive_data, 0, acefile.ace_crc16(archive_data[4 : 4 + size]))
    original = args.destination / "original"
    original.mkdir(parents=True, exist_ok=True)
    manifest = {"installer_sha256": INSTALLER_SHA256, "original": [], "assets": []}
    with acefile.open(io.BytesIO(archive_data)) as archive:
        for member in archive.getmembers():
            relative = safe_name(member.filename)
            contents = archive.read(member)
            output = original / relative
            output.parent.mkdir(parents=True, exist_ok=True)
            output.write_bytes(contents)
            manifest["original"].append({
                "path": relative.as_posix(), "size": len(contents),
                "sha256": hashlib.sha256(contents).hexdigest(),
            })
    container = (original / "Vertrix2.vf").read_bytes()
    version, count = struct.unpack_from("<II", container)
    if (version, count) != (10, 1525):
        raise ValueError(f"Unexpected asset container version/count: {version}, {count}")
    cursor = 8
    seen = set()
    for _ in range(count):
        size, offset, name_length = struct.unpack_from("<III", container, cursor)
        cursor += 12
        name = container[cursor : cursor + name_length].decode("cp1252")
        cursor += name_length
        relative = safe_name(name)
        if relative.as_posix().lower() in seen:
            raise ValueError(f"Duplicate asset path: {relative}")
        seen.add(relative.as_posix().lower())
        if offset + size > len(container):
            raise ValueError(f"Asset extends beyond the container: {relative}")
        contents = container[offset : offset + size]
        output = args.destination / "assets" / relative
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_bytes(contents)
        manifest["assets"].append({
            "path": relative.as_posix(), "size": size, "offset": offset,
            "sha256": hashlib.sha256(contents).hexdigest(),
        })
    if cursor != min(item["offset"] for item in manifest["assets"]):
        raise ValueError("Asset directory boundary does not match the first payload")
    args.destination.mkdir(parents=True, exist_ok=True)
    (args.destination / "extraction.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print(f"Verified {len(manifest['original'])} original files and {count} assets")


if __name__ == "__main__":
    main()
