"""Verify that the Wii library includes every recovered portable source file."""

import argparse
import json
import os
from pathlib import Path
import subprocess


def run(command, environment):
    return subprocess.check_output(command, env=environment, text=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--build-dir", type=Path, required=True)
    parser.add_argument("--devkitppc", type=Path, default=Path("/opt/devkitpro/devkitPPC"))
    arguments = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    build = arguments.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    environment = os.environ.copy()
    environment["TMPDIR"] = str(build)
    run(["make", "-s", "-C", str(root), f"BUILD={build}",
         f"DEVKITPPC={arguments.devkitppc}"], environment)
    prefix = arguments.devkitppc / "bin" / "powerpc-eabi-"
    archive = build / "libvertrix-recovered.a"
    expected = sorted(path.stem + ".o" for path in (root / "source").glob("*.c")
                      if not path.name.startswith("wii_"))
    members = run([str(prefix) + "ar", "t", str(archive)], environment).splitlines()
    if sorted(members) != expected:
        raise RuntimeError(f"Archive/source mismatch: missing={set(expected) - set(members)}, "
                           f"extra={set(members) - set(expected)}")
    combined = build / "recovered-link-check.o"
    run([str(prefix) + "gcc", "-r", "-nostdlib", "-Wl,--whole-archive", str(archive),
         "-Wl,--no-whole-archive", "-o", str(combined)], environment)
    undefined = sorted(line.split()[-1] for line in
                       run([str(prefix) + "nm", "-u", str(combined)], environment).splitlines())
    runtime = {"__divdi3", "__umoddi3", "calloc", "fclose", "fopen", "fread", "free",
               "fseek", "ftell", "malloc", "memcmp", "memcpy", "memmove", "memset"}
    unexpected = set(undefined) - runtime
    if unexpected:
        raise RuntimeError(f"Unresolved recovered dependencies: {sorted(unexpected)}")
    report = {"status": "passed", "portable_source_count": len(expected),
              "archive_members": sorted(members), "remaining_runtime_symbols": undefined,
              "scope": "All portable modules compile for PowerPC and combine without "
                       "unresolved recovered dependencies. Standard C/compiler runtime "
                       "dependencies remain for final application linking. This does not "
                       "prove a playable application or hardware execution."}
    (build / "wii-build-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({
key: value for key, value in report.items() if key != "archive_members"},
                     indent=2))


if __name__ == "__main__":
    main()
