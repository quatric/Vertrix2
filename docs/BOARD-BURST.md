# Board burst (0x430660)

`vertrix_board_burst` (source/board_burst.c) is the spark effect the board plays at a cell: ten
actors with resource `0x54651c` and handler `0x444a80`, appended to the list embedded in the board
at `+0xcec`.

Order of the original: two draws (heading below 360, speed below 9 plus 2), then per spark: allocate
`0x15c` bytes, base construct (`0x4abd70`), initialize (`0x4adf20`, all zero), position words `+0xe`
and `+0x16` from the board origin plus 24 * cell + 12, `+0xd0` = 4 steps (`0x4ac470`), period 1
step (`0x4ac7b0`), a frame draw below 32, resource attach (`0x4ac8d0`), frame (`0x4ac710`), byte
`+0x94` = 1, frame binding (`0x4ac8a0`), bytes/words `+0x95`, `+0x48`, `+0x4e`, `+0x93`, `+0x44`,
`+0x70`, `+0x30`, `+0x32`, the heading `+0x24` and the speed `+0x28`, words `+0x2a..` (`0x4ad510`),
handler, and the list append (`0x4b5e70`).

The heading of spark i is `(draw + 36 * i) & 0xffff` modulo 360: the original adds 0x24 to `edi`
every iteration. The frame binding and the list append (the Delphi list growth `0x4d88a0`) stay
boundaries (`VertrixBurstHooks`); the oracle logs their calls.

Verification: tools/verify_board_burst.py, 4,000 complete original executions (operator new and the
draws replayed, the two boundaries logged); call logs, the board and every object compare. Evidence:
docs/board-burst-verification.json.

## Rings (0x430440)

`vertrix_board_rings` plays three rings of 18 sparks through the same builder: ring r draws a heading
below 360 (each spark adds 20), words `+0x30` = 12 - 4r and `+0x32` = 5 - r, `+0x28` = 0, handler
`0x444970`; rings 0 and 2 draw a frame below 32 per spark with resource `0x54651c`, ring 1 uses
frame 0 and resource `0x546500`. Verified together with the burst (4,000 complete original
executions across both).
