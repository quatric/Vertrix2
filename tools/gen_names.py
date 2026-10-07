"""Generate proven address/name pairs from recovered header annotations.

Only a standalone Original annotation and its following declaration provide evidence.
Markdown prose may mention callees or data and is deliberately not a naming source.
For grouped annotations, only the first address is paired with the first prototype;
parameterized helpers and shared implementations make positional alias inference unsafe.
Only explicit Original variants annotations associate every listed address with one declaration.
"""
import json
import re
import sys
from pathlib import Path

BLOCK_COMMENT = re.compile(r"/\*[\s\S]*?\*/")
ANNOTATION = re.compile(
    r"/\*\s*Original(?:s|\s+routines?|\s+handlers?|\s+variants)?\s*0x([0-9a-f]+)\b", re.I
)
# Excluded fragment/composition and malformed annotations still end preceding evidence.
ANNOTATION_BOUNDARY = re.compile(r"/\*\s*Original(?:s)?(?=\b|0x|[0-9])", re.I)
VARIANTS = re.compile(
    r"/\*\s*Original\s+variants\s+"
    r"(0x[0-9a-f]+(?:\s*(?:,|and|/)\s*0x[0-9a-f]+)*)\s*:", re.I
)
VARIANT_MARKER = re.compile(r"/\*\s*Original\s+variants\b", re.I)
PROTOTYPE = re.compile(
    r"(?:static\s+inline\s+)?[A-Za-z_][\w\s*]*?\b(vertrix_\w+)\s*\("
)


def following_name(text):
    """Inspect declarations, skipping only comments, directives and type scaffolding."""
    text = BLOCK_COMMENT.sub(" ", text)
    text = re.sub(r"//[^\n]*", " ", text)
    text = re.sub(r"^[ \t]*#[^\n]*(?:\\\n[^\n]*)*", " ", text, flags=re.M)
    while text.strip():
        text = text.lstrip()
        found = None if re.match(r"typedef\b", text) else PROTOTYPE.match(text)
        if found:
            return found.group(1)
        if not re.match(r"(?:typedef|enum|struct|union)\b", text):
            return None
        # A typedef may contain semicolons inside its struct/union body.
        depth = 0
        for index, char in enumerate(text):
            if char == "{":
                depth += 1
            elif char == "}":
                depth -= 1
                if depth < 0:
                    return None
            elif char == ";" and depth == 0:
                text = text[index + 1:]
                break
        else:
            return None
    return None


def header_pairs(text):
    comments = list(BLOCK_COMMENT.finditer(text))
    annotations = [m for m in comments if ANNOTATION_BOUNDARY.match(m.group())]
    for index, annotation in enumerate(annotations):
        if not ANNOTATION.match(annotation.group()):
            continue
        # Callback/member comments are not annotations for a later declaration.
        line_start = text.rfind("\n", 0, annotation.start()) + 1
        if text[line_start:annotation.start()].strip():
            continue
        boundary = annotations[index + 1].start() if index + 1 < len(annotations) else len(text)
        name = following_name(text[annotation.end():boundary])
        if name:
            variant_text = re.sub(r"\n[ \t]*\*[ \t]?", "\n", annotation.group())
            variants = VARIANTS.match(variant_text)
            if VARIANT_MARKER.match(annotation.group()):
                if variants is None:
                    raise ValueError("Original variants annotation requires an explicit address list and colon")
                addresses = [int(value, 16) for value in re.findall(r"0x([0-9a-f]+)", variants.group(1), re.I)]
                if len(addresses) != len(set(addresses)):
                    raise ValueError("Original variants annotation repeats an address")
            else:
                addresses = [int(ANNOTATION.match(annotation.group()).group(1), 16)]
            for address in addresses:
                yield address, name


def collect_names(source):
    candidates = {}
    for header in sorted(source.glob("*.h")):
        if header.name.startswith(("lifted_", "lift_")):
            continue
        for address, name in header_pairs(header.read_text()):
            candidates.setdefault(address, set()).add(name)
    conflicts = {address: values for address, values in candidates.items() if len(values) > 1}
    names = {address: next(iter(values)) for address, values in candidates.items() if len(values) == 1}
    return names, conflicts


def resolve_aliases(names, conflicts, registry, root):
    """Apply reviewed canonical names only while their evidence still matches."""
    if not isinstance(registry, dict):
        raise ValueError("Canonical name registry must be an object")
    resolved = dict(names)
    unresolved = dict(conflicts)
    root = root.resolve()
    seen = set()
    for key, entry in registry.items():
        if not isinstance(key, str) or not re.fullmatch(r"0x[0-9a-fA-F]+", key):
            raise ValueError(f"Invalid registry address: {key!r}")
        address = int(key, 16)
        if address in seen:
            raise ValueError(f"Duplicate registry address: {key}")
        seen.add(address)
        candidates = conflicts.get(address)
        if candidates is None:
            raise ValueError(f"Stale registry entry: {key} has no header conflict")
        if not isinstance(entry, dict):
            raise ValueError(f"Invalid registry entry: {key}")
        chosen = entry.get("name")
        aliases = entry.get("aliases")
        if not isinstance(chosen, str) or chosen not in candidates:
            raise ValueError(f"Canonical name for {key} is not a header candidate")
        if (not isinstance(aliases, list) or not all(isinstance(value, str) for value in aliases)
                or len(aliases) != len(set(aliases)) or set(aliases) != candidates):
            raise ValueError(f"Registry aliases for {key} do not match header candidates")
        reason = entry.get("reason")
        if not isinstance(reason, str) or not reason.strip():
            raise ValueError(f"Missing canonical-name reason for {key}")
        evidence = entry.get("evidence")
        if not isinstance(evidence, list) or not evidence:
            raise ValueError(f"Missing canonical-name evidence for {key}")
        for reference in evidence:
            if not isinstance(reference, str) or not reference.strip():
                raise ValueError(f"Invalid evidence path for {key}")
            path = Path(reference)
            if path.is_absolute():
                raise ValueError(f"Evidence path for {key} must be relative")
            path = (root / path).resolve()
            if not path.is_relative_to(root) or not path.is_file():
                raise ValueError(f"Evidence path for {key} must name an existing root-contained file")
        resolved[address] = chosen
        del unresolved[address]
    return resolved, unresolved


def main():
    root = Path(__file__).resolve().parents[1]
    names, conflicts = collect_names(root / "source")
    registry_path = root / "docs" / "function-name-aliases.json"
    if registry_path.exists():
        names, conflicts = resolve_aliases(names, conflicts, json.loads(registry_path.read_text()), root)
    for address, values in sorted(conflicts.items()):
        print(f"Excluded conflicting annotation 0x{address:x}: {', '.join(sorted(values))}", file=sys.stderr)
    (root / "docs" / "names.json").write_text(
        json.dumps({f"0x{address:x}": name for address, name in sorted(names.items())}, indent=1) + "\n"
    )
    print(len(names), "names")


if __name__ == "__main__":
    main()
