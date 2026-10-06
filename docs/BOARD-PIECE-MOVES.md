# Board piece moves

`source/board_piece_moves.c`: placement tests and moves of the active piece.

- `0x42efa0` tests the fit table `0x4f9800[30 * shape + 5 * rotation + column]`.
- `0x42f030` / `0x42f120` scan the piece's rows against the touch table
  `0x4f9ad8[13 * (shape + rotation) + row]` at the left / right neighbour column (edge or occupied
  block cell).
- `0x42f280`, `0x42f2b0`, `0x42f520`, `0x42f550`, `0x42f6e0`, `0x42f720` are the wrappers that store
  board bytes `+0xa64`/`+0xa65` or shift the piece by 24 pixels. Shape and rotation are the values
  the original callers leave in `edx` and `ebx`, so they are parameters here.

Shape tables stay in original memory and are read through `VertrixMemoryRead`.
`tools/verify_board_piece_moves.py` runs all nine routines 2,048 times in the original and
compares return values and whole boards and pieces. Evidence: `board-piece-moves-verification.json`.
