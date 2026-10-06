# Object label placement `0x4b3210`

`source/object_label.c` (`vertrix_object_place_label`), oracle `tools/verify_object_label.py`,
evidence `docs/object-label-verification.json` (4,096 complete original executions, all eight
parent/flag branch combinations seen).

The routine stores the parent handle at `+0x160`, the offsets at `+0x164`/`+0x166` and the flags
at `+0x168`/`+0x16c`. It builds an AnsiString temporary (`0x4ca070`), assigns the parent's text
dword `+0x15c` through `0x4ca370` when the parent is non-zero, then calls `0x4b65d0` on the parent
with the sign-extended glyph byte `+0x160` and the corner words, and releases the temporary
(`0x4ca210`). The register values of every call, including the stale `ebx`/`ecx` the original
leaves behind, compare. The original returns the saved exception chain head, which no caller uses.

String runtime `0x4ca060`/`0x4ca070`/`0x4ca210`/`0x4ca370` stays a call boundary: `0x4ca060`
returns the constant `0x50081c`, `0x4ca070` points the variable at it, `0x4ca370` is a `strlen`
import followed by `0x4ca2e0`. Remaining for `0x45fb00`: `0x4b54d0`, `0x4b5550`, `0x4b65d0`.
