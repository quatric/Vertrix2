"""Plan or apply identifier-only renames to verified generated whole chunks.

No executable lifting, function regeneration or formatting occurs. Every input is
validated before writes; the default command reports a dry run.
"""
import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import re

from routine_names import readable_names

IDENTIFIER = re.compile(r"[A-Za-z_][A-Za-z_0-9]*\Z")
C_TOKEN = re.compile(
    r"(?P<trivia>\s+|/\*[\s\S]*?\*/|//[^\n]*)"
    r"|(?P<quoted>\"(?:\\[\s\S]|[^\"\\])*\"|'(?:\\[\s\S]|[^'\\])*')"
    r"|(?P<identifier>[A-Za-z_][A-Za-z_0-9]*)"
    r"|(?P<other>[^A-Za-z_\s\"'/]+|.)"
)
SIGNATURE = re.compile(r"\buint32_t\s+(lifted_\w+)\s*\([^;{}]*\)\s*([;{])")
ENUM = re.compile(r"\b(LIFTED_\w+_STACK)\s*=\s*(0x[0-9a-fA-F]+|[0-9]+)\b")
DISPATCH = re.compile(
    r"\{\s*(0x[0-9a-fA-F]+)\s*,\s*(lifted_\w+)\s*,\s*"
    r"([0-9]+)\s*,\s*([0-9]+)\s*\}"
)


def read_json(path):
    def unique_pairs(pairs):
        result = {}
        for key, value in pairs:
            if key in result:
                raise ValueError(f"Duplicate JSON key in {path}: {key}")
            result[key] = value
        return result
    return json.loads(path.read_text(), object_pairs_hook=unique_pairs)


def token_digest(text, substitutions=None):
    """Normalize exact identifier tokens, including stack enum identifiers."""
    substitutions = substitutions or {}
    digest = hashlib.sha256()
    for token in C_TOKEN.finditer(text):
        if token.lastgroup == "trivia":
            continue
        value = token.group()
        if token.lastgroup == "identifier":
            value = substitutions.get(value, value)
        digest.update(token.lastgroup.encode() + b":" + value.encode() + b"\0")
    return digest.digest()


def rename_tokens(text, substitutions):
    return C_TOKEN.sub(
        lambda token: substitutions.get(token.group(), token.group())
        if token.lastgroup == "identifier" else token.group(), text
    )


def identifiers(text):
    return Counter(token.group() for token in C_TOKEN.finditer(text)
                   if token.lastgroup == "identifier")


def executable_text(text):
    return C_TOKEN.sub(lambda token: " " if token.lastgroup in ("trivia", "quoted")
                       else token.group(), text)


def plan_renames(root):
    """Return staged file contents and the old/new short-name map without writing."""
    root = Path(root).resolve()
    readable = readable_names(root / "docs" / "names.json")
    metadata_paths = sorted((root / "docs" / "lift").glob("whole_*.json"))
    if not metadata_paths:
        raise ValueError("No verified whole-chunk metadata found")
    generated = {root / "source" / "lifted_dispatch.c"}
    chunks, originals, records = [], {}, {}
    for metadata_path in metadata_paths:
        chunk = metadata_path.stem
        metadata = read_json(metadata_path)
        if not isinstance(metadata, dict):
            raise ValueError(f"Invalid metadata object: {metadata_path}")
        header = root / "source" / f"lifted_{chunk}.h"
        body = root / "source" / f"lifted_{chunk}.c"
        if not header.is_file() or not body.is_file():
            raise ValueError(f"Missing generated source/header for {chunk}")
        generated.update((header, body))
        chunks.append((metadata_path, header, body, metadata))
        for old, meta in metadata.items():
            if not IDENTIFIER.fullmatch(old) or not isinstance(meta, dict):
                raise ValueError(f"Invalid routine metadata key: {old}")
            address = meta.get("address")
            if (not isinstance(address, int) or isinstance(address, bool)
                    or not isinstance(meta.get("stack"), int)
                    or not isinstance(meta.get("arguments"), int)):
                raise ValueError(f"Missing address/stack/arguments for {old}")
            if old in records or address in originals:
                raise ValueError(f"Duplicate routine identifier/address: {old}")
            records[old] = meta
            originals[address] = old
    actual_generated = set((root / "source").glob("lifted_whole_*.[ch]"))
    if actual_generated != generated - {root / "source" / "lifted_dispatch.c"}:
        raise ValueError("Generated whole files and metadata chunks differ")

    targets = {old: readable.get(meta["address"], f"f{meta['address']:x}")
               for old, meta in records.items()}
    if len(set(targets.values())) != len(targets):
        raise ValueError("Target routine names collide")
    enums = [f"LIFTED_{name.upper()}_STACK" for name in targets.values()]
    if len(set(enums)) != len(enums):
        raise ValueError("Target stack enum names collide")
    changes = {old: new for old, new in targets.items() if old != new}
    substitutions = {}
    for old, new in changes.items():
        substitutions[f"lifted_{old}"] = f"lifted_{new}"
        substitutions[f"LIFTED_{old.upper()}_STACK"] = f"LIFTED_{new.upper()}_STACK"
    if len(set(substitutions.values())) != len(substitutions):
        raise ValueError("Identifier substitution targets collide")

    texts = {path: path.read_text() for path in generated}
    validation_chunks = list(chunks)
    optional_path = root / "docs" / "lift" / "unverified.json"
    optional_metadata = {}
    if optional_path.exists():
        optional_metadata = read_json(optional_path)
        if not isinstance(optional_metadata, dict):
            raise ValueError("Invalid unverified metadata object")
        optional_addresses = set()
        for name, meta in optional_metadata.items():
            if (not IDENTIFIER.fullmatch(name) or not isinstance(meta, dict)
                    or any(not isinstance(meta.get(key), int) or isinstance(meta[key], bool)
                           or meta[key] < 0 for key in ("address", "stack", "arguments"))):
                raise ValueError(f"Invalid unverified routine metadata: {name}")
            if meta["address"] in optional_addresses or meta["address"] in originals:
                raise ValueError(f"Duplicate unverified routine address: {name}")
            optional_addresses.add(meta["address"])
        header = root / "source" / "lifted_unverified.h"
        body = root / "source" / "lifted_unverified.c"
        for path in (header, body):
            if not path.is_file():
                raise ValueError("Missing unverified source/header")
            texts[path] = path.read_text()
            if set(identifiers(texts[path])).intersection(substitutions):
                raise ValueError("Whole rename would change unverified identifiers")
        validation_chunks.append((optional_path, header, body, optional_metadata))
    for metadata_path, header, body, metadata in validation_chunks:
        expected = {f"lifted_{name}" for name in metadata}
        declarations = SIGNATURE.findall(executable_text(texts[header]))
        definitions = SIGNATURE.findall(executable_text(texts[body]))
        if (Counter(name for name, terminator in declarations if terminator == ";")
                != Counter({name: 1 for name in expected}) or
                Counter(name for name, terminator in definitions if terminator == "{")
                != Counter({name: 1 for name in expected})):
            raise ValueError(f"Prototype/definition metadata mismatch: {metadata_path.name}")
        header_signatures = {match.group(1): match.group()[:-1].strip()
                             for match in SIGNATURE.finditer(executable_text(texts[header]))}
        body_signatures = {match.group(1): match.group()[:-1].strip()
                           for match in SIGNATURE.finditer(executable_text(texts[body]))}
        if (len(declarations) != len(expected) or len(definitions) != len(expected)
                or header_signatures.keys() != body_signatures.keys()
                or any(token_digest(signature) != token_digest(body_signatures[name])
                       for name, signature in header_signatures.items())):
            raise ValueError(f"Prototype/definition signature mismatch: {metadata_path.name}")
        stack_values = ENUM.findall(executable_text(texts[header]))
        expected_enums = {f"LIFTED_{name.upper()}_STACK": meta["stack"]
                          for name, meta in metadata.items()}
        if (len(stack_values) != len(expected_enums) or
                {name: int(value, 0) for name, value in stack_values} != expected_enums):
            raise ValueError(f"Stack enum metadata mismatch: {metadata_path.name}")
        body_identifiers = identifiers(texts[body])
        for name, meta in metadata.items():
            enum = f"LIFTED_{name.upper()}_STACK"
            if body_identifiers[enum] < 2:
                raise ValueError(f"Missing stack identifiers for {name}")
        annotated = re.findall(r"/\*\s*Original\s+(0x[0-9a-fA-F]+)\.\s*\*/\s*"
                               r"uint32_t\s+lifted_(\w+)\s*\(", texts[header])
        if {name: int(address, 16) for address, name in annotated} != {
                name: meta["address"] for name, meta in metadata.items()}:
            raise ValueError(f"Original-address annotation mismatch: {metadata_path.name}")

    dispatch_path = root / "source" / "lifted_dispatch.c"
    dispatch_text = executable_text(texts[dispatch_path])
    tables = {}
    for match in re.finditer(r"\b(routines|unverified_routines)\s*\[\s*\]\s*=\s*\{([\s\S]*?)\}\s*;",
                             dispatch_text):
        if match.group(1) in tables:
            raise ValueError("Duplicate dispatcher table")
        tables[match.group(1)] = match.group(2)
    if optional_path.exists() or "unverified_routines" in tables:
        if set(tables) != {"routines", "unverified_routines"}:
            raise ValueError("Missing separate verified/unverified dispatcher tables")
        optional_rows = DISPATCH.findall(tables["unverified_routines"])
        optional_expected = {meta["address"]: (f"lifted_{name}", meta["stack"], meta["arguments"])
                             for name, meta in optional_metadata.items()}
        optional_actual = {int(address, 16): (name, int(stack), int(arguments))
                           for address, name, stack, arguments in optional_rows}
        if len(optional_rows) != len(optional_actual) or optional_actual != optional_expected:
            raise ValueError("Unverified dispatcher metadata mismatch")
        remainder = DISPATCH.sub("", tables["unverified_routines"])
        if not re.fullmatch(r"\s*\{\s*0\s*,\s*NULL\s*,\s*0\s*,\s*0\s*\}\s*,[\s,]*", remainder):
            raise ValueError("Invalid unverified dispatcher sentinel or row")
        # Optional rows must remain behind the generated, initially zero gate.
        if (not re.search(r"\bstatic\s+int\s+unverified_allowed\s*;", dispatch_text)
                or any(value.strip() != "allowed" for value in
                       re.findall(r"\bunverified_allowed\s*=(?!=)([^;]+);", dispatch_text))
                or not re.search(r"if\s*\(\s*found\s*==\s*NULL\s*&&\s*unverified_allowed\s*\)"
                                 r"\s*\{\s*found\s*=\s*bsearch\s*\([^;]*\bunverified_routines\s*\+\s*1\b",
                                 dispatch_text)):
            raise ValueError("Unverified dispatcher must be disabled by default and explicitly gated")
        if len(re.findall(r"\bbsearch\s*\([^;]*\bunverified_routines\b", dispatch_text)) != 1:
            raise ValueError("Unverified dispatcher lookup must occur only behind the gate")
        rows = DISPATCH.findall(tables["routines"])
        if not re.fullmatch(r"[\s,]*", DISPATCH.sub("", tables["routines"])):
            raise ValueError("Invalid verified dispatcher row")
        if len(DISPATCH.findall(dispatch_text)) != len(rows) + len(optional_rows):
            raise ValueError("Dispatcher rows outside validated tables")
    else:
        # Legacy fixtures and dispatchers have only the verified table.
        rows = DISPATCH.findall(dispatch_text)
    screen_addresses = {
        "hud_decor": 0x46b810, "title_screen": 0x465af0,
        "select_screen": 0x466d60, "game_screen": 0x46c9d0,
    }
    expected_rows = {meta["address"]: (f"lifted_{name}", meta["stack"], meta["arguments"])
                     for name, meta in records.items()}
    # gen_dispatch explicitly prefers these separately verified screen routines.
    for name, address in screen_addresses.items():
        screen_path = root / "docs" / "lift" / f"{name}.json"
        if not screen_path.exists():
            continue
        meta = read_json(screen_path)
        for suffix in ("c", "h"):
            screen_source = root / "source" / f"lifted_{name}.{suffix}"
            if not screen_source.is_file():
                raise ValueError(f"Missing screen override source: {name}")
            signatures = SIGNATURE.findall(executable_text(screen_source.read_text()))
            terminator = "{" if suffix == "c" else ";"
            if sum(symbol == f"lifted_{name}" and end == terminator
                   for symbol, end in signatures) != 1:
                raise ValueError(f"Invalid screen override signature: {name}")
        if meta.get("address") not in (None, address) or not all(
                isinstance(meta.get(key), int) for key in ("stack", "arguments")):
            raise ValueError(f"Invalid screen override metadata: {name}")
        if f"lifted_{name}" in substitutions:
            raise ValueError(f"Whole rename would overwrite reserved screen identifier: {name}")
        expected_rows[address] = (f"lifted_{name}", meta["stack"], meta["arguments"])
    actual_rows = {int(address, 16): (name, int(stack), int(arguments))
                   for address, name, stack, arguments in rows}
    if len(actual_rows) != len(rows) or actual_rows != expected_rows:
        missing = sorted(set(expected_rows) - set(actual_rows))
        extra = sorted(set(actual_rows) - set(expected_rows))
        mismatched = sorted(address for address in set(expected_rows).intersection(actual_rows)
                            if expected_rows[address] != actual_rows[address])
        raise ValueError(f"Dispatcher metadata mismatch: missing={missing}, extra={extra}, "
                         f"mismatched={mismatched}")
    occupied = set().union(*(set(identifiers(text)) for text in texts.values()))
    for old, new in substitutions.items():
        if new in occupied and new not in substitutions:
            raise ValueError(f"Target identifier already exists: {new}")

    # Only generated files may change. Explicit obsolete references elsewhere
    # are blockers, including literal identifier names in verification tools.
    for folder in (root / "source", root / "tools"):
        for path in folder.rglob("*"):
            if (not path.is_file() or path in generated or
                    path.suffix not in (".c", ".h", ".cpp", ".hpp", ".py")):
                continue
            found = set(re.findall(r"\b(?:lifted_\w+|LIFTED_\w+_STACK)\b", path.read_text()))
            obsolete = found.intersection(substitutions)
            if obsolete:
                raise ValueError(f"External obsolete identifiers in {path.relative_to(root)}: "
                                 + ", ".join(sorted(obsolete)))

    staged = {}
    for path, text in texts.items():
        if path not in generated:
            continue
        replacement = rename_tokens(text, substitutions)
        if token_digest(text, substitutions) != token_digest(replacement):
            raise ValueError(f"Non-identifier semantic change: {path}")
        if replacement != text:
            staged[path] = replacement
    for metadata_path, _, _, metadata in chunks:
        renamed = {targets[old]: meta for old, meta in metadata.items()}
        if list(renamed.values()) != list(metadata.values()):
            raise ValueError(f"Routine metadata values changed: {metadata_path}")
        if list(renamed) != list(metadata):
            staged[metadata_path] = json.dumps(renamed, indent=1) + "\n"
    return staged, changes


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--write", action="store_true", help="Apply the fully validated plan")
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    args = parser.parse_args()
    staged, changes = plan_renames(args.root)
    print(f"{len(changes)} routine renames across {len(staged)} files")
    for old, new in changes.items():
        print(f"{old} -> {new}")
    if args.write:
        # All validation and semantic comparison finished before the first write.
        for path, replacement in staged.items():
            path.write_text(replacement)
        print("Applied identifier-only renames")
    else:
        print("Dry run; use --write to apply")


if __name__ == "__main__":
    main()
