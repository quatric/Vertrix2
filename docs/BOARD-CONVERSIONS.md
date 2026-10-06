# Board conversions

Recovered from `Vertrix2.exe`; `source/board_conversions.c`.

- `0x436720` retires each marked block (marker 1, row order, marker set to 2) to the companion
  grid with handler `0x44d480` and puts a freshly spawned block of the given kind in its place
  (handler `0x44d5f0`), inheriting the old `+0xd0` and frame.
- `0x437060` does the same without touching the markers (handlers `0x44e6e0`/`0x44c860`); the new
  block's `+0x58` is the old `+0xd0` divided by 12. Only modes 6 and -2 are defined; other modes
  read an uninitialised local in the original and are rejected.
- `0x437350` gives each marked block handler `0x44d8b0` and puts a block of the same kind in the
  companion cell (handler `0x44da70`).

`tools/verify_board_conversions.py` runs each original routine 2,048 times (operator new and the
draw stubbed and replayed) and compares return values, whole boards and objects and the draws
consumed. Evidence: `board-conversions-verification.json`.

## 0x437be0 scatter

vertrix_board_scatter_marked: every marked block moves to the companion grid and flies from the board origin offset by (0x3c, 0x9c); it stores distance, origin, heading modulo 360 and a draw of 8 plus 3, the handler 0x44e120 and fixed dwords. The callees 0x484680, 0x484700 (fixed_point.c), 0x4ad510, 0x4ac8f0, 0x4ac7b0, 0x4ac510, 0x4ac380 are the recovered ones. 2,048 complete original executions with a random angle table compare whole boards, objects and draws.

## 0x437b70 and 0x437d70

vertrix_board_prime_companions sets +0x68 = 0x30 on every companion block after one discarded draw per row. vertrix_board_split_marked splits each marked block in two halves flying apart (handler 0x44e250, targets at board x - 24 and x + 125, distance words |target - x| * 100 / 60). Both verified over 2,048 complete original executions each.

## 0x4368e0 and 0x436b40

vertrix_piece_replace_children replaces the three children of the active piece (saving the old ones at +0x170); vertrix_boards_convert_counts converts the first N pending markers of two boards (marking each 2) with drawn kinds. Verified over 2,048 complete original executions each.

## 0x436d80

vertrix_boards_convert_random converts a drawn pending marker per round on two boards (handler 0x44e510 for the old block, 0x44e590 and +0x44 = 0 for the new one). Verified over 2,048 complete original executions.

## 0x438540

vertrix_board_collapse_marked moves every block to the companion grid, brings the blocks of the markers 2 then 1 of each column back from row 12 upward with start_slide, and reports whether any block is still sliding (otherwise every block gets +0x93 = 0, +0x95 = 1, +0x4e = 0x32). Verified over 2,048 complete original executions covering the moving, settled (blocks standing on their targets) and missing-marker cases.

## 0x439260

vertrix_board_pick_kinds counts the cells of kinds 0..4, lists the kinds present, shuffles the list with one draw per entry and returns min(length, 3) with the first five entries (entries past the length are stale stack words in the original and are not compared). 2,048 complete original executions.

## 0x437fe0

vertrix_board_spin_marked: every marker 1 (then every marker 2) block is retired with a spin (word +0x24) and replaced by a new block at the same position; the replacement kind is drawn below 5 for the markers 1 and is always the stone (kind 5, no draw) for the markers 2. 2,048 complete original executions including heavy pool aliasing.

## 0x4378c0

vertrix_board_swirl_marked retires every marker 1 block with handler 0x44de20 and an angle of 72 * column, then adds one drawn offset per row (cut to 16 bits, modulo 360) to the angle of every companion block of the row. The averaging and largest-distance loops of the original have no effect and are not ported. 2,048 complete original executions.

## 0x438960

vertrix_board_set_motion gives every block of the grid the motion of a mode (0 to 4; period 4 steps, handler pairs by a parity that alternates over all 65 cells, mode 2 drawing an extra delay and a handler). 2,048 complete original executions over modes 0-4 and out-of-range modes.
