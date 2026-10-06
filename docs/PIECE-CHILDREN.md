# Piece children

`piece_children.c` recovers routines on a piece object's three child blocks
(handles at `+0x15c`, `+0x160`, `+0x164`; a second list at `+0x170`):

- `0x42a980` and `0x43a5b0` (identical): read the three children's kind bytes.
- `0x43a410`: configure the three children from kinds (attach resource
  `0x544ac0 + kind * 28`, store the kind, handler `0x44c4c0`/`0x44c3e0`/
  `0x44c450`, clear `+0x58` and the timer counter).
- `0x43a5f0`: the same for the children whose stack flag is exactly 1, all with
  handler `0x44c4c0`.
- `0x42a800`: place both child lists below the piece (x plus signed byte
  `+0x16c`, y plus 24 per row plus signed byte `+0x16d`, 16-bit wrapping).
- `0x425ef0`: initialize a piece from a kind index using the dword tables at
  `0x4f8cec` and `0x4f8d38` (19 entries each). Larger indices read beyond the
  tables in the original; the native function returns 0 for them.
- `0x43a4f0`: store the three preview kinds in the piece bytes `+0x168..+0x16a`
  (low bytes of `edx`, `ebx`, `ecx`). The original has no return value and no
  bounds check; the native version preserves short storage and returns 0 there.
  Used by `0x43d260` after `0x43d180` generation.

The resource attach `0x4ac8d0` is a supplied boundary; handler setting and
counter clearing use the already recovered `0x4ac8f0` and `0x4ac510`.
`tools/verify_piece_children.py` runs each complete original 4,096 times over a
pool of random objects (children may alias the piece or each other) and compares
results, attach events and every object byte (`piece-children-verification.json`).
`tools/verify_piece_preview_kinds.py` runs `0x43a4f0` 4,096 times over random
piece storage and compares whole objects, plus a short-storage preservation
check (`piece-preview-kinds-verification.json`).
`0x43a160` (`vertrix_piece_child_slots_init`, in `verify_constructors.py` with
4,096 whole-object cases): construct with class `0x514b94`, zero three slot
dwords, and three consecutive `0xff` flag bytes at `+0x168..+0x16a`.
