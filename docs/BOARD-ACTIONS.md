# Board actions

`board_actions.c` recovers five routines that act on the block grids of a board
(`+0x220` blocks, `+0x87c` companions, markers at `+0xb94`):

- `0x4330d0` tests whether the active piece's column, from its top row to its bottom row
  (`y + 0x47`), meets an occupied cell of another board's grid.
- `0x4371b0` and `0x437460` walk the markers equal to 1 in row order; the first marks them 2 and
  hands out the handlers `0x44e790` / `0x44e800`, the second leaves the markers and hands out
  `0x44d9d0` / `0x44dbb0`.
- `0x438470` starts a slide of an actor to a board cell: downward (handler `0x44e920`) or upward
  (`0x44ebe0`) depending on the target y.
- `0x433750` turns a block into a stone: the old block moves to the companion grid with handler
  `0x44cb50` and a new kind-5 block, spawned as in `0x430800`, takes its cell.

Allocation, name resolution and the random draw come from `VertrixFactoryServices`
(see `BLOCK-FACTORY.md`). `tools/verify_board_actions.py` runs each original routine 2,048 times
over random boards (the allocator and draw stubbed and replayed) and compares return values, every
object and the draws consumed. Evidence: `board-actions-verification.json`.
