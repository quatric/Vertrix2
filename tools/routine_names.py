"""Shared deterministic names for independently callable recovered variants."""
import json
from pathlib import Path
import re

IDENTIFIER = re.compile(r"[A-Za-z_][A-Za-z_0-9]*\Z")


def readable_names(path):
    """First address keeps its base; later variants add their executable address.

    Reserve every real base name before choosing variant suffixes, so a generated
    variant cannot steal another routine's explicitly recovered base name.
    """
    path = Path(path)
    if not path.exists():
        return {}

    def unique_pairs(pairs):
        result = {}
        for key, value in pairs:
            if key in result:
                raise ValueError(f"Duplicate JSON key in {path}: {key}")
            result[key] = value
        return result

    raw = json.loads(path.read_text(), object_pairs_hook=unique_pairs)
    if not isinstance(raw, dict):
        raise ValueError("Routine names must be an address/name object")
    entries = {}
    for key, full in raw.items():
        if not isinstance(key, str) or not re.fullmatch(r"0x[0-9a-fA-F]+", key):
            raise ValueError(f"Invalid routine address: {key!r}")
        if not isinstance(full, str):
            raise ValueError(f"Invalid readable name at {key}")
        base = full[len("vertrix_"):] if full.startswith("vertrix_") else full
        if not IDENTIFIER.fullmatch(base):
            raise ValueError(f"Invalid C identifier at {key}: {base}")
        address = int(key, 16)
        if address in entries:
            raise ValueError(f"Duplicate normalized name address: {key}")
        entries[address] = base
    reserved = set(entries.values())
    result, owners, used = {}, set(), set()
    for address, base in sorted(entries.items()):
        if base not in owners:
            name = base
            owners.add(base)
        else:
            stem = f"{base}_{address:x}"
            name = stem
            counter = 2
            while name in reserved or name in used:
                name = f"{stem}_{counter}"
                counter += 1
        if name in used:
            raise ValueError(f"Routine output name collision: {name}")
        used.add(name)
        result[address] = name
    return result
