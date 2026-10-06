# Board marking, column fall and object setup

`board_cells.c` recovers nineteen original board routines over the scene storage
(`VertrixScene`, see SCENE-RECOVERY.md). Slot handles are only tested for zero.

- `0x42f210`: fills the column array at `+0x9a1` with the negated board byte
  `+0x58` and, for every column whose slot at `+0x988` is set, the 13 cells of
  the grid at `+0x19d` (`cell_b`).
- `0x42f440` / `0x42f4b0`: fill row array 0 (`+0x9a6`) / row array 2 (`+0x9c0`)
  with the board byte and, for every row whose slot at `+0x9e8` / `+0xa2c` is
  set, store it in that row of all five columns of the grid at `+0x15c`
  (`cell_a`).
- `0x42f760`: for each of the five columns of the slot grid at `+0x220`
  (13 slots per column, stride `0x34`), destroys the bottom slot's object with
  the virtual destructor (vtable slot 0, flag 2) when it is set and clears it,
  then moves every slot down one row and empties the top slot.
- `0x42eb60` / `0x430150`: destroy the active piece (`+0xa60`) / extra object
  (`+0xce0`) with the virtual destructor (flag 2) when set, then clear the slot.
- `0x42ee20`: when a piece is active, for each of its three child handles at
  piece `+0x15c` that is set: period 5 steps (`0x4ac7b0`), byte `+0x4e` = 0x64,
  counter cleared (`0x4ac510`) and handler `0x44c960` (`0x4ac8f0`).
- `0x42ee80`: for every set slot of the grid at `+0x220`, period = steps * 12 and
  counter cleared.
- `0x4300b0` / `0x430100`: position the extra object: word `+0x18` = board
  `+0x16` + `0x108` / `0x138`, word `+0x1a` = the `0x4f7d08` table entry chosen by
  the dword at `0x532bbc`, handler `0x44c880` / `0x44c8e0`.
- `0x432200`: destroy and clear every slot of the grid at `+0x220` whose object
  has type byte `+0x15d` equal to 2.
- `0x432280`, `0x4322f0`, `0x4334b0`: report whether any object of the grid at
  `+0x220` has byte `+0x15d` = 1 / byte `+0x15c` = 6, or any object of the
  collection at `+0x324` has byte `+0x15d` = 1; scans stop at the first match.
- `0x432ba0`: swap two entries of 13-entry columns (the original passes both grid
  bases; the same grid in its caller `0x432a30`).
- `0x42ff10`: give an actor the board's clip rectangle: byte `+0x8e` = 3 and
  words `+0xa8`, `+0xaa`, `+0xac`, `+0xae` = x, x + 0x77, y, y + 0x137 (board
  words `+0x0e`, `+0x16`); this is clip kind 3 of the gate (ACTOR-GATE.md).

The one-field actor setters they use are in `actor_fields.c` (ACTOR-FIELDS.md).
The destructor is a supplied boundary (`VertrixBoardDestroy`).
`tools/verify_board_cells.py` runs each complete original 4,096 times over
random board storage and compares every modeled collection and cell array,
the resolved object storage, and the destruction order and arguments. Evidence:
`board-cells-verification.json`.
