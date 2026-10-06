# Movement and collision recovery

Confirmed by original instructions and differential execution:

- Fast descent `0x00431390` is native as `vertrix_motion_fast`.
  Only piece state `+0x168 == 0` transitions to 1, selects the period
  table at `0x004f7d14`, writes the low-word step at `0x004f7d20`,
  and resets the motion counter. Nonzero states retain all fields.
  360 original-instruction comparisons passed over difficulties, initial
  counters/parameters, and states. The player handler calls this operation
  for its fourth action at `0x004511a3`.

Input-dispatch findings still awaiting native integration:

- `0x00450ff0` processes left, right, cycle, then fast descent in order.
  Player action identifiers are words at `+0x168`, `+0x16a`, `+0x16c`,
  and `+0x16e`. Readiness checks use `0x00476480` and compare action
  state with 1; consuming the action uses `0x00476320`.
- Handler gates include player `+0x4c5`, active-piece presence, and board
  `+0xbd8`. Successful movement in player mode `0x2b` also changes
  opponent input actions. Cycle invokes bottom recoloring only when piece
  `+0x17c == 1`, then calls a character-side method.
- Repeat timing, those opponent/character effects, action consumption, and
  the full handler state machine remain unfinished. These findings are
  instruction traces, not verification of a complete native input handler.
- Original horizontal piece moves `0x00431100` and `0x00431140` are
  native as `vertrix_move_horizontal`. They return zero without an active
  piece. Otherwise checks `0x004311c0` and `0x00431280` reject a wall
  or an occupied neighbor cell on any nonnegative row covered by the piece
  through Y+71. Allowed movement changes X by -24 or +24 with signed-word
  wrapping. These checks use ordinary occupancy, not board-effect masks.
  20,000 integrated comparisons execute the full original movement routines
  with their original occupancy checks, covering all columns, sub-cell
  coordinates, above-board rows, and absent pieces. The corpus keeps the
  bottom covered row within 0..12. Input repeat and rendering remain separate.
- `0x0042a8b0` cycles the three child pointers as `[first, second, third]`
  to `[second, third, first]`. Native `vertrix_piece_cycle` preserves that
  block-type order. `0x0042a8e0` redraws the bottom block from five normal
  colors; bottom stone 5 and bomb 6 are unchanged without consuming RNG.
  Native `vertrix_piece_bottom_color` preserves this behavior. 20,000
  operation/RNG-position comparisons passed, including sample-buffer wrap.
  The oracle executes the original sprite setter during recoloring; the
  native type operation still needs its graphics updates and input dispatch.
- Spawn selection in `0x00431d90` is native as `vertrix_spawn_position`.
  Original board `+0xa68` supplies the preferred column. If it is not 2
  and its top cell is occupied, it becomes 2. No fallback occupancy rejection
  occurs here. Constructor inputs are origin X plus column times 24, and
  origin Y minus 72, using the original signed-word wrapping. 20,490
  comparisons cover all columns, occupied fallback cells, signed extremes,
  and random origins. The oracle supplies object allocation/storage and skips
  preliminary construction, then stops before `0x0042a540`; selection and
  coordinate instructions execute unchanged. Full object initialization,
  its graphics children, and spawn-to-update scheduling remain unfinished.
- Native `vertrix_descent` combines downward clearance and locking as the
  original loop `0x0042fc2d` does. With a positive pixel budget it tests
  clearance before each one-pixel increment; exhausting the budget leaves
  the piece active without an extra lock check. A blocked probe invokes
  placement, clears the active piece, and writes the failure flag corresponding
  to board `+0xbd8`. 10,000 integrated comparisons execute the original loop
  slice through `0x0042fc56`, including its original probe and locking calls,
  with graphics destructors stubbed. They compare board contents, active state,
  Y coordinate, and failure flag. Empty/populated boards, all columns, above-board
  positions, and varied budgets are covered. The current corpus uses aligned X
  and board origin zero; it does not prove timing, input, rendering, or the
  rest of the piece-update routine.
- `0x00431c60` places the active piece after descent is blocked. Native
  `board_lock` writes its three block types in one column, marks out-of-board
  blocks for disposal, and preserves the return value: top row -3 or lower
  fails; otherwise it returns success, including pieces wholly below the board.
  The oracle checks 10,000 placements against original pointer-board writes,
  active-pointer clearing, destructor order, and placed-object fields:
  `+0x93=0`, `+0x4e=50`, `+0x48=0`. The native byte-board routine does not
  implement those graphics-object fields or destruction; runtime ownership
  and following resolution transitions remain unfinished.
- `0x00431b80` is ported as `vertrix_down_clear`. The piece update calls
  it at `0x0042fc2f`. It first compares piece Y plus 72 with the board
  origin using the original unsigned comparison. Otherwise it converts that
  bottom point to a cell: row 13 or greater blocks descent, and an occupied
  cell blocks descent. Valid storage-reaching probes have column 0..4 and
  nonnegative row. 20,000 comparisons cover occupied cells, empty cells,
  sub-cell positions, the upper boundary, and the bottom edge. This verifies
  the probe, not falling speed, locking, or subsequent state transitions.
- `0x0042f310` rises only columns with an incoming block at board `+0x988`.
  Native `board_rise` shifts those columns upward, inserts at row 12,
  clears consumed incoming entries, and reports the evicted top blocks in
  column order. 10,000 comparisons match original board transitions and
  destructor call order. Empty incoming columns remain unchanged. Graphics
  destructor effects and active-piece adjustment remain outside this routine.
- `0x0042f580` and `0x0042f620` shift occupied incoming rows right and
  left, respectively. Native `board_shift` preserves the block-type board,
  clears consumed incoming entries, and reports evicted types in row order.
  Empty incoming entries cause no shift. 20,000 comparisons passed for both
  directions, including isolated incoming rows, fully empty incoming rows,
  and fully populated incoming rows. The oracle replaces only graphics
  destructors with recorded calls; native eviction order matches that call
  order. Object ownership, destructor side effects, animation, and active-piece
  adjustment remain separate runtime work. Original incoming pointer arrays
  are at board `+0x9e8` (right shift) and `+0xa2c` (left shift).
- `0x00431ae0` converts signed 16-bit pixel coordinates to board cells.
  The board origin is stored at `+0x0e` and `+0x16`. Subtraction takes
  place in 32 bits; signed division by 24 truncates toward zero. No clamp
  occurs. Native `board_pixel_cell` matches 24,641 edge/random cases.
- `0x0042f030` (left) and `0x0042f120` (right) are ported as
  `vertrix_side_contact`. They scan the active piece's top through the point
  71 pixels below it, ignoring negative rows. A nonzero row-mask byte reports
  contact at the corresponding wall or an occupied neighboring cell.
  20,000 comparisons against original instructions passed with varied boards,
  explicit row masks, both walls, sub-cell positions, and above-board rows.
  Valid callers keep the current column in 0..4 and bottom row at most 12.
  This is contact detection; calling transitions determine movement response.
- `vertrix_side_shift_contact` uses the original first-step masks for patterns
  0..2 at `0x004f9ad8`. Its 60,000 comparisons execute the original routines
  with their unmodified table data. Pattern values are assigned to player
  `+0x3d0` at `0x0043c322`, `0x0043c4ba`, and `0x0043c4f2`.
  Instructions at `0x00453f7d` and `0x0045428d` copy that pattern into target-player
  `+0x42c` and reset step `+0x430` to zero. This concerns horizontal board
  shifts, not ordinary left/right piece controls.

Instruction-level findings to continue tracing, not yet native implementations:

- The board's active-piece pointer is `+0xa60`. `0x004320c0` checks it
  for nonzero. `0x00431d60` compares the board and active piece's signed
  vertical coordinates.
- `0x0042efa0` converts the active piece's upper coordinate and a point
  71 pixels below it, then reads a table at `0x004f9800`. Its incoming
  EDX/EBX parameters participate in the table index; callers must establish
  their meaning before porting this as a collision rule.
- Mode selection for `0x0042f030` and `0x0042f120` indexes data at
  `0x004f9ad8` with incoming EDX/EBX. The native decision takes an explicit
  13-byte row mask; later-step selection remains to be recovered. The oracle
  supplies those bytes at the table boundary while preserving the decision
  instructions. This is not a full-mode collision verification.
- `0x0042f410` subtracts 24 from the active piece's signed vertical
  coordinate. `0x0042f3d0` gates this through `0x0042efa0`.
- Player `+0x3b4` references its three-block preview. `0x0043d260`
  invokes recovered generation and writes its types through `0x0043a4f0`.
- `0x00452520` handles rising-board transitions, including `0x0042f410`
  and `0x0042f310`; it must not be mistaken for ordinary piece falling.

The collision tables, pixel animation updates, input repeat, movement rules,
locking, and spawning remain incomplete. Coordinate verification alone does
not establish their behavior.
