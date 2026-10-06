# Choice grid

`choice_grid.c` recovers the routines of a seven row by four column grid object
(object handles at `+0x15c`, dword values at `+0x1cc`, byte tables at `+0x23c`
and `+0x258`; a value of 1 marks an enabled cell):

- `0x429d50`: apply the cell values to every cell object (power `+0x4e`, flags
  `+0x93`/`+0x15c`, clear `+0x15d`, handler `0x456ca0` through the recovered
  `0x4ac8f0`).
- `0x429df0`: load 28 values and set each object's `+0x15c` from them.
- `0x429e80`: store the 28 values into a destination array at a start index.
- `0x429ee0`: pick rows that hold an enabled cell, shuffled with ten passes of
  random draws, copying up to a byte limit; `0x42a080` does the same for the
  columns of one row and then draws one column.
- `0x42a140`, `0x42a190`, `0x42a1b0`, `0x42a170`: mark an available cell,
  test availability, test for any marked cell, and read both table bytes.

The random draw `0x4826c0` is a supplied boundary. `tools/verify_choice_grid.py`
runs each complete original 4,096 times with random grids and a pool of random
objects, replays the original's draws into the native code and compares results,
outputs, the grid and every object byte-for-byte (evidence in
`choice-grid-verification.json`). Unrecovered: the layout (`0x42a200`),
constructors and destructors.
