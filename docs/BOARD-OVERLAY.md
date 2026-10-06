# Board overlay actor

`0x42ff50` (`source/board_overlay.c`) builds the overlay actor of a board: base construct
(`0x4abd70`), initialise with zeros, `+0xd0`, period, resource `0x544d44` (class `0x15`) or
`0x544d60` (class `0x16`), box from the board origin words, style record from the table at board
dword `+0xce4` (`0x4123d0`), placed `0x138` below the board and stored at board `+0xce0`.
The period is the original table lookup `0x4f7cfc[dword 0x532bbc]`, supplied by the caller.

`tools/verify_board_overlay.py` runs the original 2,048 times (operator new stubbed) and compares
the whole board and every object. Evidence: `board-overlay-verification.json`.
