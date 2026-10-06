# Player slots

`player_slots.c` recovers small routines on the player object:

- `0x43d3b0` / `0x43d3d0`: the dword `+0x4c8` (mode) lies in `0x25..0x27` /
  `0x32..0x34` (the shared tail `0x43bd74` returns 0).
- `0x43aab0`: store the side byte `+0x190`, place the cursor child (handle at
  `+0x15c`) at (186, 130) for side 0 or (334, 130) otherwise (constants at
  `0x4f8a48..0x4f8a54`), link it to the player and copy the side to byte
  `+0x17c` of the object at `+0x450`.
- `0x43b810`: clamp the requested level to 0..9, store it at `+0x17c` and notify
  the cursor child (`0x431400`, supplied) when it changed.
- `0x43b1a0`: first-turn decision from the globals `0x532bc8`/`0x532b34` and the
  levels at `+0x178` of the player and its opponent (`+0x3b0`); a draw below 2
  (`0x4826c0`, supplied) decides when the levels call for it. The scratch
  globals `0x540f44..0x540f50` are modelled.
- `0x43bb40`: store the mode dword `+0x4c8, then refresh (`0x4726d0`, supplied).
- `0x43baf0`: store the flag byte `+0x4c4`, then refresh (`0x4726d0`, supplied).
- `0x43d260`: generate three block types with the player mode at `+0x4c8`
  (via `0x43d180`/`vertrix_piece`) and store them in the preview piece (handle
  at `+0x3b4`) through `0x43a4f0`. The original bounces the kinds through the
  scratch globals `0x540f84..86`; the native version uses stack storage and
  shares RNG position with `vertrix_piece`.
- `0x43b5b0`: draw delay parameter 0 from the kind at `+0x488`, the internal
  level at `+0x17c` and the supplied difficulty (original global `0x532bbc`),
  stored at `+0x458`. Only parameter 0 applies the internal-level adjustment.
- `0x43b660` / `0x43b680`: parameters 1 and 2 (shared helper `0x43b6a0` with
  row pairs 2,3 and 4,5; no level adjustment), stored at `+0x45c` / `+0x460`.
- `0x43b590`: all three delay draws in order. Table math matches
  `vertrix_delay`; draws use `vertrix_random_range` on the caller-supplied RNG
  (original states `0x598d48`). Out-of-range kind/difficulty and short storage
  preserve storage and return 0.
- `0x43ab30`: initialize the piece at `+0x450` from the kind byte at `+0x488`
  (via `0x425ef0`), then draw all three delays. Kinds at or above 19 read
  beyond the original tables and return 0 natively without touching either
  object; short storage or an unresolvable piece behaves the same.
- `0x43b980`: when the side handle at `+0x4e8` is nonzero, destroy it (resource
  method at `[side + 0x158]`, invoked with `edx = 2`; supplied boundary),
  clear the field and run the reset below. A null side returns at once (its
  return value is a native convention; the original leaves stale `eax`).
- `0x43ce00`: release as above, reset the mode dword to 0 (with refresh via
  `0x4726d0`, supplied), mark the reset state (`0x43cde0`), and regenerate the
  preview (`0x43d260`).
- `0x43b930`: release and reset as above, then allocate a `0x15c`-byte side
  object (`0x4ca000`, stubbed), construct it (`0x4abd70`) and set its period
  from the supplied step count (`0x4ac7b0`, period = 12 * steps; the steps
  arrive in `edx` from the difficulty table `0x4f9c14`).
- `0x43ce30`: allocate as above with live-table steps, mark the reset state,
  reset the mode to `0x30`, and overwrite the state dword with 4.
- `0x43ba80`: clear the dword at `+0x18c` to zero (no return contract).
- `0x43cd30`: when the mode dword is in group A (`0x25..0x27`), run the reset
  and refresh, returning 1; otherwise return 0. The trailing refresh observes
  the reset's return (1), not the player.
- `0x43cd60` / `0x43cda0`: allocate as above, reset the mode to `0x2b` / `0x2c`,
  and mark the reset state.
- `0x43ccf0`: release the side, store the supplied value at `+0x4e4` (no
  allocation), reset the mode to the value plus `0x25`, mark the reset state,
  clear `+0x18c` and `+0x3f4`, and refresh again. Callers pass 0 (mode `0x25`)
  or a side handle. The text disassembly misreports the store as `+0x4e8`;
  the mapped-image bytes show `+0x4e4`, confirmed differentially.
- `0x43bb00`: store the B01 byte, then refresh only when it is nonzero.
  Otherwise, when the mode is in group A, reset the opponent (handle at
  `+0x3b0`); then release and reset the player itself and refresh once more
  (observing the reset's return). The return value is a native convention.
- `0x43ba80`: clear the dword at `+0x18c` to zero (no return contract).
- `0x43bad0` / `0x43bae0`: store the flag bytes at `+0x4cd` / `+0x4cc` (the
  state bytes of the player_actions event machine). These duplicate
  `object_scalars.c` (`set_cd`/`set_cc`, same addresses, independently
  verified); either spelling may be used by future callers.
- Mode-setup family: allocate the side with live-table steps, reset the mode,
  mark the reset state, and finish per member — `0x43cf30`/`70`/`f0`,
  `0x43d030`/`70`/`b0`/`f0` (modes `0x23`/`0x22`/`0x28`/`0x29`/`0x2a`/`0x2d`/
  `0x2e`, preview tail), `0x43cfb0` (mode `0x24`, byte `+0x4dc = 3` tail),
  `0x43ceb0` (mode `0x2f`, state-dword 1 tail), `0x43ce70` (steps from table
  `0x4f9c38` indexed by `+0x3fc`, mode = index + `0x32`, no preview). The
  steps tables have one entry per difficulty and are read live in tests.

`tools/verify_player_slots.py` runs each complete original 4,096 times over a
pool of random objects and compares results, globals, notifications, replayed
draws and every object byte (`player-slots-verification.json`).
`tools/verify_player_mode_sets.py` runs `0x43bb40` and `0x43baf0` 4,096 times
each with the refresh stubbed and logged, plus short-storage preservation
checks (`player-mode-sets-verification.json`).
`tools/verify_preview_generate.py` runs `0x43d260` 4,104 times with seeded RNG
across all piece modes and buffer wrap, comparing preview kind bytes and RNG
position (`preview-generate-verification.json`). Test objects live at
`0x807000+` to stay clear of the oracle RNG sample buffer at `0x804000`.
`tools/verify_player_delays.py` runs `0x43b5b0`, `0x43b660`, `0x43b680` and
`0x43b590` 4,098 times each with seeded RNG across difficulties, kinds and
levels including buffer wrap (`player-delays-verification.json`).
`tools/verify_piece_setup.py` runs `0x43ab30` 4,096 times with seeded RNG
across difficulties, kinds and levels, comparing whole piece bytes, delay
fields and RNG position, plus invalid-kind and short-storage preservation
checks (`piece-setup-verification.json`).
`tools/verify_player_side.py` runs `0x43ba80`, `0x43b980`, `0x43ce00`, `0x43b930`,
`0x43ce30`, `0x43cd30`, `0x43cd60`, `0x43cda0`, `0x43ccf0` and `0x43bb00` 4,096
times each over null/present sides (and opponents) with stubbed allocator,
refresh and destructor, comparing player, opponent, side, preview and RNG
position (`player-side-verification.json`). Test objects live at `0x807000+`,
clear of the oracle RNG sample buffer at `0x804000`; the new side is always
chosen distinct from the old side so the destroy path cannot alias the fresh
object.
`tools/verify_player_stores.py` runs `0x43ba80`, `0x43bad0` and `0x43bae0`
4,096 times each over random player storage with whole-object compares, plus
short-storage preservation checks (`player-stores-verification.json`).
`tools/verify_player_modes.py` runs all ten mode-setup members 4,096 times
each over null/present sides and difficulties with stubbed allocator, refresh
and destructor, comparing player, side, preview and RNG position
(`player-modes-verification.json`).
