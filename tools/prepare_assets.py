"""Prepare the on-disk layout the verifiers expect from the shipped Vertrix2.vf.zip.

The verifiers locate the original executable and the extracted assets relative to each other
(`<root>/original/Vertrix2.exe`, `<root>/original/Vertrix2.vf`, `<root>/assets/...`) and one of them
reads an extraction manifest. `tools/extract.py` produces this from the original ACE installer;
this script produces the same layout from the files that ship in the repository, so no installer
(or `acefile`) is needed. The manifest is derived from the container itself, so it checks the
container against its own directory, not against an independent extraction.
"""
import argparse
import hashlib
import json
import shutil
import struct
import zipfile
from pathlib import Path, PurePosixPath


def safe_name(name):
    path = PurePosixPath(name.replace("\\", "/"))
    if path.is_absolute() or ".." in path.parts or ":" in name:
        raise ValueError(f"Unsafe archive name: {name!r}")
    return Path(*path.parts)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("destination", type=Path)
    parser.add_argument("--repository", type=Path, default=Path(__file__).resolve().parents[1])
    args = parser.parse_args()
    original = args.destination / "original"
    original.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(args.repository / "Vertrix2.exe", original / "Vertrix2.exe")
    with zipfile.ZipFile(args.repository / "Vertrix2.vf.zip") as archive:
        container = archive.read("Vertrix2.vf")
    (original / "Vertrix2.vf").write_bytes(container)
    version, count = struct.unpack_from("<II", container)
    if (version, count) != (10, 1525):
        raise ValueError(f"Unexpected asset container version/count: {version}, {count}")
    manifest = {
        "original": [{
            "path": "Vertrix2.vf",
            "size": len(container),
            "sha256": hashlib.sha256(container).hexdigest(),
        }],
        "assets": [],
    }
    cursor = 8
    for _ in range(count):
        size, offset, name_length = struct.unpack_from("<III", container, cursor)
        cursor += 12
        name = container[cursor:cursor + name_length].decode("cp1252")
        cursor += name_length
        relative = safe_name(name)
        if offset + size > len(container):
            raise ValueError(f"Asset extends beyond the container: {relative}")
        contents = container[offset:offset + size]
        output = args.destination / "assets" / relative
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_bytes(contents)
        manifest["assets"].append({
            "path": relative.as_posix(),
            "size": size,
            "offset": offset,
            "sha256": hashlib.sha256(contents).hexdigest(),
        })
    (args.destination / "extraction.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print(f"Prepared {count} assets in {args.destination}")


if __name__ == "__main__":
    main()
