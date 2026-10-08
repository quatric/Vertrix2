"""Report current naming coverage after validating generated source consistency."""
import argparse
import json
from pathlib import Path

from rename_lifted import plan_renames, read_json
from routine_names import readable_names
from dispatch_boundaries import NATIVE_UNVERIFIED_BOUNDARIES


def snapshot(root):
    paths = list((root / "source").rglob("*"))
    paths += list((root / "docs/lift").glob("*.json"))
    paths.append(root / "docs/names.json")
    result = {}
    for path in paths:
        if path.is_file():
            stat = path.stat()
            result[str(path)] = (stat.st_ino, stat.st_size, stat.st_mtime_ns)
    return result


def inventory(root):
    before = snapshot(root)
    staged, changes = plan_renames(root)
    canonical = readable_names(root / "docs/names.json")
    entries = {}
    for path in sorted((root / "docs/lift").glob("whole_*.json")):
        for name, metadata in read_json(path).items():
            entries[metadata["address"]] = name
    anonymous = {address: name for address, name in entries.items()
                 if name == f"f{address:x}"}
    pending = [hex(address) for address in sorted(anonymous) if address in canonical]
    line_counts = {"lifters": 0, "other_source": 0}
    for path in (root / "source").rglob("*"):
        if path.is_file():
            group = "lifters" if path.name.startswith(("lifted_", "lift_")) else "other_source"
            line_counts[group] += path.read_bytes().count(b"\n")
    line_counts["total"] = sum(line_counts.values())
    optional_path = root / "docs/lift/unverified.json"
    optional = read_json(optional_path) if optional_path.exists() else {}
    if before != snapshot(root):
        raise ValueError("Source or naming metadata changed during validation; retry the inventory")
    return {
        "scope": "Current working-tree naming coverage and generated-source consistency only; "
                 "the whole-chunk tier designation is not independent behavioral proof.",
        "name_map_entries": len(canonical),
        "verified_whole_chunk_entries": len(entries),
        "readable_whole_chunk_names": len(entries) - len(anonymous),
        "anonymous_whole_chunk_names": len(anonymous),
        "anonymous_entries_with_unapplied_canonical_names": pending,
        "optional_unverified_entries": len(optional),
        "optional_entries_kept_at_native_boundary": [
            hex(address) for address in sorted(NATIVE_UNVERIFIED_BOUNDARIES)
            if any(metadata["address"] == address for metadata in optional.values())
        ],
        "rename_dry_run": {"pending_routine_renames": len(changes),
                           "pending_files": len(staged)},
        "source_lines": line_counts,
        "line_count_convention": "All files under source, including comments and blank lines; "
                                 "lifters have filenames starting lifted_ or lift_; count LF bytes.",
        "full_native_recovery_reports": [
            "docs/actor-frame-switch-verification.json",
            "docs/ui-panel-dispatch-verification.json",
            "docs/input-verification.json",
            "docs/input-consume-verification.json",
            "docs/title-letter-step-verification.json",
            "docs/call-glue-verification.json",
            "docs/notice-verification.json",
            "docs/register-return-verification.json",
            "docs/copy-dword-verification.json",
            "docs/color-table-verification.json",
            "docs/constant-return-verification.json",
            "docs/actor-wrap-verification.json",
            "docs/table-loops-verification.json",
            "docs/object-accessors-verification.json",
            "docs/particle-init-verification.json",
            "docs/actor-fields-verification.json",
            "docs/global-scalars-verification.json",
            "docs/title-letter-digit-verification.json",
            "docs/object-scalar-returns-verification.json",
            "docs/particle-spawn-full-verification.json",
            "docs/title-letter-launch-verification.json",
            "docs/title-letter-verification.json",
            "docs/rtl-single-verification.json",
            "docs/rtl-single-negate-verification.json",
            "docs/rtl-double-add-verification.json",
            "docs/rtl-double-multiply-verification.json",
            "docs/host-rtl-double-verification.json",
            "docs/host-rtl-single-verification.json",
            "docs/rtl-single-multiply-verification.json",
            "docs/rtl-single-divide-verification.json",
            "docs/rtl-single-divide-hardware-verification.json",
            "docs/block-factory-full-verification.json",
            "docs/scalar-wrappers-verification.json",
            "docs/piece-offsets-verification.json",
        ],
        "dispatcher_report": "docs/dispatcher-integration-verification.json",
        "constant_dispatcher_report": "docs/constant-dispatch-verification.json",
        "remaining_work": "Recover anonymous routines and finish runtime integration. "
                          "Optional routines need independent behavioral verification.",
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument("--write", action="store_true",
                        help="Refresh docs/function-naming-inventory.json after validation")
    args = parser.parse_args()
    report = inventory(args.root)
    output = json.dumps(report, indent=2) + "\n"
    if args.write:
        (args.root / "docs/function-naming-inventory.json").write_text(output)
    print(output, end="")


if __name__ == "__main__":
    main()
