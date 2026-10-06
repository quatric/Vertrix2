# Board active-piece routines

`board_piece.c` recovers `0x4320c0` (board has an active piece at `+0xa60`), `0x42f2e0`
(fill the 65 bytes at `+0x19d` with the board byte `+0x58`), `0x431fa0` (child kinds of the
active piece, via `0x42a980`), `0x431fb0` (put the three children into their flashing state and
set piece `+0x17c`) and `0x432040` / `0x432080` (piece column at or past the right / left edge,
using the signed 16-bit division by 24 of `0x431ae0`).

`0x431340` returns the piece column, `0x431b20` the column plus top and bottom rows (bottom uses
y + 0x47 truncated to 16 bits) and `0x431c10` the sign-extended kind byte of child *n* (-1 without a
piece).

Piece and child handles resolve through `VertrixObjectStorage`. `0x431fa0` forwards the caller's
`edx`, `ebx`, `ecx` output pointers, so the native form returns the three kinds in an array.
`tools/verify_board_piece.py` runs each original routine up to 4,096 times over a pool of
random objects and compares return values and every object. Evidence:
`board-piece-verification.json`.
