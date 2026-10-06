# Board kind snapshot and marker grids

`board_markers.c` recovers the routines that turn the board's object slots into
byte grids (5 columns of 13) and query them:

- `0x4327e0`: kind snapshot (board `+0x1de`): `0xff` for an empty slot, else the
  kind byte `+0x15c` of the slot's object. `0x432840` clears a 65-dword mask.
- `0x435e80`: marker grid (board `+0xb94`) by mode: empty cells are never
  marked; stones (5) only in mode 2; bombs (6) in modes 1 and 2; other kinds in
  modes 0, 1 and 2; other modes mark nothing.
- `0x435f30`: marker grid with only the first occupied cell of each column,
  when it is not a stone.
- `0x436030` / `0x436070`: number of markers equal to 1 / 2.
- `0x435fe0` (column order, kind 1), `0x4360b0` (row order, kind 1), `0x436100`
  (row order, kind 2): column and row of the n-th marker (zero-based); outputs
  stay untouched when there is no n-th marker.
- `0x436850` / `0x4372c0`: checkerboard marker (every even cell index holding a
  block; `0x436850` excludes stones).
- `0x436fe0` / `0x437240` (identical): markers on stones.
- `0x436a10`: markers where the kind, as a signed byte, equals the argument; the
  marker count is stored through the pointer argument via `0x436030`.
- `0x436aa0`: markers for powers 5 and 6: stones and empty cells never; bombs for
  5; other kinds for 5 and 6.
- `0x438830` / `0x4388a0`: in one column (stack argument), searching from the
  bottom row up, the n-th marker equal to 1 / 2; stores column and row and
  returns 1, else 0 with the outputs untouched.
- `0x438910`: 0 when the first argument is not below the second (signed);
  otherwise snapshots the kinds (`0x4327e0`, into board `+0x1de`) and returns 1
  when any column's bottom cell holds a block.
- `0x438d50`: like `0x438910` but reports 1 when any cell holds a block.
- `0x439140`: the first marker equal to 1 of one column from the bottom up (the
  same search as `vertrix_board_marker_in_column` with n = 0).
- `0x439370`: markers where the sign-extended kind byte (empty cells are -1)
  equals the dword the pointer argument refers to.

`0x438cd0` is not ported: it snapshots two boards into the same stack buffer
and compares it with an uninitialized one, so its result depends on stack
garbage rather than game state.

`tools/verify_board_markers.py` runs each complete original thousands of times
over random boards and object kinds. Evidence:
`board-markers-verification.json`.

`0x437b70` consumes one discarded draw below 48 per row and stamps dword
`+0x68 = 0x30` on every nonzero companion of the `+0x87c` grid. Covered by
`verify_board_markers.py` (4,096 cases with seeded RNG, whole board,
companions and RNG position compared).
