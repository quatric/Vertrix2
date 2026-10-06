# What is still not a 1:1 port, with the evidence found so far

Everything here is open. Pointers are original addresses; nothing below is guessed behaviour.

## Heads (animated idle; moods and bonus animations open)
`source/head_anim.c` plays the original head animations: `Head_<name>.ini` rows (row 0 the still
head, row n + 1 the frame n of the `.ani` files, checked for all 19 characters: the largest frame
is always rows - 2), `HeadAnimFileName.ini` (per character: `.ani` name and type), `Anim/*.ani`
(frame \ delay ms). The idle player follows the handlers `0x45aa70` / `0x45aab0`: wait 2000 + a
draw below 10000 ms, then, when no animation is running, a random animation of the player's mood
(types 3 sad, 4 neutral, 5 happy; type 0 when none), frames shown for their delay, then the
still head. The mood of `0x43ab80` is sad when the board is lost, happy when the opponent's is;
for a living pair the original compares both boards (`0x427ae0` = `ai_compare_boards`,
`ai_features` and `ai_record_score` over a record list in the AI object at `+0x1c5`, whose
contents are not yet recovered), so a living pair stays neutral here. Open: the good / bad bonus
animations (types 1, 2, with dialogue) that the 93 bonus effects start, and the original's global
random table (0x598d30) instead of the head's own generator.

## Game screen objects beyond `0x46b810`
The constructor `0x46c9d0` also builds, per `docs/game-screen-constructor-annotated.txt`: the two
player objects (`0x43a6f0`), bonus slot objects 3/4 (`0x429880`), text elements (`0x4b5700`,
`0x4b65d0`: level, speed, name, score), next-piece strips 5/6 (`0x43a160`, 478/144, 69), the bonus
icon columns and counters, the centre objects 0x11/0x12, and the bonus timer bar (`0x450d40`).
`game_render.c` still draws name, score, level and next from hand-placed coordinates for player 1
only.

## Versus
`2PLAYERS` now starts a match against the computer: `source/ai_controller.c` drives a second
`vertrix_session` with the recovered planner (`ai_plan`, `ai_steer`, `ai_reaction_time`). The
skill (`+0x488`) is the opponent's character index (`[0x532a6c]`, stored by 0x46cb5f), its planner
level comes from the rating table `0x4f8cec` by `0x425ef0` (12 -> 4, >7 -> 3, <=3 -> 1, else 2).
The driver follows 0x43ad70/0x43ae20 (plan once per piece, reaction-time timer, one steering tick
per period). The stage (decor, HUD filter) is the opponent's, as in the reference screenshot
(Lee vs Bill on Bill's stage, so the blue filter 12 is correct and there is no colour mismatch).
Open: the attack/bonus effects between the two boards (`+0x3b0`, effects `0x4522xx..0x4559xx`),
the opponent choice (the select screen), the AI session's own random source (the original draws
from the global table 0x598d48), the race rule `[0x532bc8] == 1` winning at `[0x532b34]` (10).

## Scenes and options
Real title scene, character select (`0x466d60`, pointer driven; outputs `0x532a50`, `0x532a68`,
`0x532a6c`, `0x532a7c`, `0x532a80`), story page (`0x46ea30`), OPTIONS (four radio groups of
3/10/2/2 choices), sound effects (72 callers of `0x43c0e0`; see `docs/HUD-LAYOUT.md`).

## Done and verified this round
Full HUD layout (`tools/gen_hud_layout.py`), level tube (`tools/verify_gauge_tube.py`).

## Bonus and attack system: what the static trace shows so far
- Post-lock handlers `0x4517c0` and `0x451970` run the match `0x432480`. With no match: if the
  player's bonus meter (`+0x18c`) is 3 (`0x43ba70`) the bonus starts (`0x451a60`: state 2 via
  `0x43bae0`, meter cleared by `0x43ba80`), otherwise the normal spawn `0x450ff0` follows (state 0).
- The meter is filled by the match reward in `0x43b9c0` (`+0x18c += reward`, capped at 3, kept at 0
  while `+0x44c == 1`); the HUD object `0x44fe80..0x450200` follows it and plays `FX09` ("alerte",
  enum 8, `[0x4f81a0]`) when it fills (`0x44ff07`).
- With a match: `+0x184` counts the chain steps, `+0x188` sums their rewards, `FX03`/`FX01`
  (`[0x4f81b4]` is 13, `excellent`) plays on a third step (`0x451a26`). After the chain,
  `0x452250` hands `+0x188` to the opponent (`+0x3f0`, state 4) when it is alive (`+0x4c5`): the
  attack. Its receiving states are `0x4522c0..0x45247x` (opponent `+0x428`, speed table `0x4f7c24`).
- The 93 effects hang off `0x450ff0..0x456033`; each is an actor animation, so each needs its own
  oracle run, like the HUD builder.
- `0x43b720` is the progress update (`+0x178 += n`, floor 0) and ends a race match at `[0x532b34]`.

## Defaults and the race rule (resolved from the executable)
`0x429660` returns the settings object plus 4, so the match options `[0x532b4c..0x532b60]` are
the default dwords at settings `+0x4..+0x14` (`settings_defaults.c`): 20, 1, 5, 0, 1. Difficulty
`[0x532b54]` is 1, the speed choice `[0x532b58]` is 5 and the mode choice `[0x532b60]` is 1, the
race. The match start `0x41bbc3` copies them to `[0x532bbc]`, `[0x532bc0]`, `[0x532bc4]` and
`[0x532bc8]`, and the player constructor stores `[0x532bc0]` in `+0x17c`. The session therefore
starts at speed 5, and `0x43b720` ends the race when the progress reaches the limit 10
(`VERTRIX_PHASE_WON`, `excellent` played). Settings the player saved change these values; the
options page that edits them is not ported.

## Menus (texts and options recovered, layout still a stand-in)
`source/menu.c` follows the string table of the executable (file `0x10c8a0..0x10cb3c`): title
1PLAYER / 2PLAYERS / OPTIONS / EXIT; 1PLAYER: TOURNAMENT / PRACTICE / RETURN; 2PLAYERS:
TOURNAMENT / PRACTICE / NETWORK / RETURN; OPTIONS: GAME / SOUND / KEYS / HIGHS / RETURN; GAME:
DIFFICULTY (EASY NORMAL HARD), START SPEED (0..9), ALL BONUS (NO YES), LEVEL LIMIT (NO YES),
COLOR LEVEL (16 32); SOUND: VOL. MUSIC, VOL. SFX, TEST MUSIC, TEST SFX; the in-game page has
RETURN TO GAME / SWITCH MUSIC / SWITCH SFX / RESTART MUSIC / QUIT THE MATCH, and the select page
PLAYERS SELECTION / CPU / BRAIN / SPEED / GO / EXIT / PLAY. The game page's rows are the four
radio groups of `0x416b30..0x416bb0` (the defaults 1, 5, 0, 1) and set the match: difficulty, the
start speed and, with LEVEL LIMIT, the race to 10. Not ported: TOURNAMENT (story), NETWORK, KEYS,
HIGHS, the in-game page, the volume step (4 is a platform choice), the box layout and the menu
backgrounds of the original.

2PLAYERS > PRACTICE opens the select page (rows from the original strings CPU / SPEED / GO / EXIT):
CPU picks the computer opponent's character, SPEED the start speed, GO starts the match with that
opponent's stage. The original page (`0x466d60`, pointer driven, with BRAIN for a human second
player and PLAYERS SELECTION as its title) is not ported; a human second player is not supported.

The in-game page (strings RETURN TO GAME / SWITCH MUSIC / SWITCH SFX / RESTART MUSIC / QUIT THE MATCH)
opens with the + button over the paused match: it resumes, mutes the music or effects, restarts
the track or returns to the title. Its original layout is not recovered (same stand-in boxes); the
effects volume follows the OPTIONS > SOUND value (48 by default, the original's `+0x30`).

Sounds: `wii_sfx.c` now also decodes the MP3 effects (libmad, whole file to 16 bit at load), which
covers every `.mp3` row of SfxFileName.ini (FX09, FX15..FX19, NAME, LAUGH, DOO). `FX19`
("Wouin Wouin", enum 75, `[0x4f81c8]`) plays when a board is lost (`0x451370`, after
`0x43acd0`). Still unwired: FX09 alerte (the bonus meter), FX15..FX18 (One, Two, Three, Fight!),
the NAME / LAUGH / DOO voices (played through the `0x43c110` / `0x43d330` head paths), and the
bonus sounds of `0x4522xx..0x4559xx`.

Bonus meter: `session->meter` is the player's `+0x18c` (0..3, filled by the reward in `0x43b9c0`
and emptied by `0x43ba80` when a lock without a match finds it full, where the original starts
the bonus: that effect is not ported). The meter object plays `FX09` ("alerte") 500 ms after it
reads 3 (its handlers `0x44fe80..0x44ff60`, periods 500 from `0x46d678`).

## The attack (first version, unverified timing)
Read from the executable: the sum of the chain's rewards (`+0x188`, cleared when the next piece
starts, `0x450ff0`) becomes the sender's `+0x3f0` (`0x452250`); `0x4522c0 .. 0x4527xx` runs the
two boards through a synchronised state machine and, for every unit of `+0x3f0`, `0x4316c0`
places a row of five stones (kind 5, handler `0x44f700`, the sound is enum 2, push up) on the
other board, where they fall onto the stacks. `vertrix_session_receive` / `land_stones` give the
same outcome in versus: when a chain ends its total is sent and the rows land after the
receiver's next lock, before its next piece; a column that cannot take a stone loses the board.
Not verified: whether the original scales the total, whether stones are cleared by matches next
to them (the AI-vs-AI headless runs end in 13..21 s, which suggests it does), the exact moment
the rows land and the two-board synchronisation. The 93 bonus effects, which use the same
opponent link (`+0x3b0`), remain.

## Stones and matches (checked)

`0x432480` snapshots the board kinds (0x4327e0) and runs the figure pass 0x434ee0 and the line pass
0x4346b0 over them, then gives every cell with mask 1 the clear handler 0x450330 (0x43272x). Only
matched cells are touched; no adjacent-clear step exists in this routine. `source/match.c` was
verified against those passes and excludes kind >= 5, so stones stay until a bonus effect removes
them. The attack in `game_session.c` therefore needs no stone clearing.

## Speed bonuses (primitives)

`vertrix_session_set_speed` / `add_speed` / `exchange_speeds` in `game_session.c` follow 0x43b810
(clamp 0..9, negative gives 0), 0x43b800 (add) and 0x452d70 (the two boards swap speeds through
0x43b810). They are not yet triggered: that needs the bonus piece (0x451a60, kind byte +0x190, effect
ids in `docs/bonus-descriptions.json`) and the amounts the handlers 0x452830/0x452880 read from
player +0x3bc/+0x3c0.

Effect dispatcher `0x43c140` (id in dl, parameter in bl): 1 -> 0x452e00, 2 -> 0x452d70 (exchange
speeds), 3 -> 0x453ad0, 4/5 -> 0x453150 with player +0x3dc = 5/6, 6 -> 0x452880 (opponent speed
+bl), 0x18 -> 0x452830 (own speed -bl). `vertrix_session_apply_speed_effect` covers ids 2, 6, 0x18.

## Bonus start chain (read, not ported)

`0x451a60` -> `0x4320d0` builds the bonus sprite object at board +0xb70 (`0x42b6b0`: character
animation table at 0x4f7d50 stride 0x28 per `[0x532bbc]`, handler 0x450710, slides until y > +0xae,
tested by `0x42ba40`). Its handler `0x451aa0` waits for that, then `0x432110` frees it and the
chosen mode `[board+0xb74]` decides: 1 -> `0x43b9c0` then spawn, 0 -> handler `0x451c00`
(`0x429ee0` picks, `0x432160` shows the effect, handler `0x451c80`), else spawn (0x450ff0).
Effects then run through the dispatcher `0x43c140`. The effect choice reads the per-character
tables in `docs/character-powers.json`.

## Plain-match sound `[0x532d88]` (traced, unresolved)

Every one of the ten references in the disassembly is a read (0x4148a6, 0x4148f4, 0x414942, 0x417082,
0x451915, 0x451a39, 0x45ca8e..). The dword sits directly after the 19-dword array at 0x532d3c
(0x532d3c + 0x4c), whose initialiser is the string load at 0x41489b. In the exe image it holds
0x534c70 (a pointer), not a sound enum, so it is filled at run time before the match handlers read it
(0x451915 passes it to 0x43c0e0 as the sound id, and 0x417260 indexes the table at 0x533164 with
it). The filler is not among the direct stores; find it by running the startup path in the oracle
rather than by guessing.

## Voices FX15..FX18 (traced)

Enum 14/15/16 (One/Two/Three, table 0x4f81b8..0x4f81c0) are played only at 0x459cdb/0x459d33 by the
countdown object (index = 0x4f81b8 value + object +0x58 - 1; 0x417260 for one mode, 0x417290 for the
other, chosen by object +4 == 1). Enum 17 (Fight, 0x4f81c4) is played at 0x45a352 by a sibling object
(0x45a3e0 handler) and at 0x4154ec, which is a key-triggered test (key id [0x532b90] = 0x3c in the
input table 0x54d640, once per run through [0x532b40]), not a match event. So no sound belongs to the
board start itself; they follow the countdown/continue object (0x4713d0, 0x459be0), still to port.

## Game-over number object (0x4713d0 / 0x4715a0, read)

Built at game over (0x451370 plays FX19 first). The object formats the player index with "%lu"
(0x50e62c; 0x4715a0 uses 0x50e630), picks the glyph frame with 0x43f420 (digit char, [0x4f9c02]>>24),
sets +4 = 2 for player 1 and 1 otherwise, places it at ([0x4f8a48] + 0x3c, [0x4f8a4c] + 0x9c) for
player 1 or ([0x4f8a50], [0x4f8a54]) for the other, and starts handler 0x459be0 with +0x58 = 3 (count),
+0x30 = 0x3c, +0x28 = 0x14, +0x32 = 1. Handler chain 0x459be0 -> 0x459d60 -> 0x459e00 -> 0x459ec0
moves and scales the sprite with the generic object engine (0x4ac500/0x4ac520/0x4ac540/0x4ad060/
0x4ad260/0x4ad530/0x4b14c0) and plays One/Two/Three by the counter (0x459cdb). Porting it needs that
engine's field map (+0x24, +0x28, +0x2a, +0x2c, +0x2e, +0x30, +0x32, +0x44, +0x48..+0x4c), which no
existing module covers.

Correction to the two sections above: the constructors 0x4713d0 and 0x4715a0 are already recovered
as `vertrix_title_letter_first` / `_second` (`source/title_letter.c`, evidence
`docs/title-letter-verification.json`). What is not recovered are their handlers 0x459be0, 0x459d60,
0x459e00 and 0x459ec0 (and 0x45a2xx, 0x45a3e0), which animate the letter and play the voice.

## Letter handlers 0x459be0, 0x459d60, 0x459e00 (ported)

`vertrix_title_letter_count`, `_settle` and `_restart` (`source/title_letter_step.c`) are the first
three letter handlers, composed of recovered primitives. 4,096 complete original executions each
match the first 0x160 bytes of the actor, handler token included (`tools/verify_title_letter_step.py`,
evidence `docs/title-letter-step-verification.json`); only the two sound players are observed. The
python tools run with `work/tools-env/bin/python3`.

`vertrix_title_letter_digit` is handler 0x459ec0 (the digit step): 4,096 complete original executions
(`tools/verify_title_letter_digit.py`, evidence `docs/title-letter-digit-verification.json`), with
the string runtime, glyph map 0x43f420, bank lookup 0x4877f0 and 0x450f80 stubbed and their calls
compared with the native service calls. It covers the not-due, level, moving (glyph set, back to
0x459be0), arrived (flag [0x532a3c], handler 0) and bank-bound paths.

`vertrix_title_letter_fight_count`, `_fight_settle` and `_fight_restart` are 0x45a290, 0x45a3e0 and
0x45a440 (the letters of the second title word: park and play the fight pair 0x4171e0/0x417220,
settle, then redraw angle and speed with two draws of 0x4826c0); 4,096 executions each in the same
verifier.

`vertrix_title_letter_launch` (0x45a0c0: launch toward the screen centre with distance 0x484680 and
heading 0x484700, two plays of the sound entry), `vertrix_title_letter_fly_out` (0x45a1c0) and
`vertrix_title_letter_fight_fly` (0x45a4f0; handler zero and flag 0x532a40) are verified by
`tools/verify_title_letter_launch.py` (2,048 complete original executions each, evidence
`docs/title-letter-launch-verification.json`).

The third family is ported too: `vertrix_title_letter_wave_count` (0x45a620), `vertrix_title_letter_wave`
(0x45a750 and 0x45a830, driven by the global at 0x532bd0) and `vertrix_title_letter_wave_fly` (0x45a910),
verified in the two scripts above.

Open: the object creation glue that starts these letters (0x46f000/0x46f220 are recovered as
`letter_row`; 0x46eda0/0x46ea30 as the grid and menu) and the wiring into a title scene. Note:
`actor_fields.c` and `actor_value_steps.c` both define `vertrix_actor_progress_quotient`, so they
cannot be linked into one library; the letter code uses `dword_transition.c` for 0x4ad750 for that
reason.

## Bonus selection (traced)

- The bonus is a choice, not a random roll. After a full meter (0x451a60) the board shows a selector
  (board +0xb78, built by 0x42acf0/0x432160); the keys at player +0x16c / +0x16e move it
  (0x42af80 / 0x42b000) and handler 0x451c80 runs the AI tick 0x43b430 while it waits. When the
  selector is done (0x42b050) it is freed (0x4321b0) and the chosen row is in board +0xb7c.
- The grid is 7 rows by 4 columns of the character's powers. The constructor (0x429c07..) reads
  `0x4178d0(character, slot)` and `0x417930`, which index byte tables in the exe: the effect id at
  0x4f9320 and its parameter at 0x4f9538, `character * 28 + slot`, 0 when the slot is empty. Slot `s`
  is row `s / 4`, column `s % 4`; `docs/character-powers.json` lists the description id of each slot.
- The column inside the chosen row is drawn by 0x42a080 (recovered in `choice_grid.c`, random among
  the enabled cells); the result goes to player +0x194 (row) and +0x198 (column), handler 0x451f10
  applies it: 0x42a170 gives (id, parameter) and 0x43c140 dispatches: 1 exchange boards (0x452e00),
  2 exchange speeds (0x452d70), 3 exchange gray blocks (0x453ad0), 4 and 5 (0x453150 with +0x3dc = 5
  or 6), 6 opponent speed + parameter (0x452880), 7 mix with parameter 1..3, 8 freeze with parameter
  1..3, 9, 12 (0x4528e0), 0x18 own speed - parameter (0x452830). Description ids map as
  0 -> id 1, 1 -> id 2, 2 -> id 3, 3 -> id 4, 5/6 -> id 6 (1/2), 7..9 -> id 7 (1..3),
  10..12 -> id 8 (1..3), 15 -> id 9, 18 -> id 12.
- `vertrix_session_apply_speed_effect` (ids 2, 6, 0x18) is the only part applied to the session so far.

## Mix bonus (dispatcher id 7, ported to the session, not yet reachable)

`vertrix_session_start_mix(session, parameter)` and the `VERTRIX_PHASE_MIXING` step in
`game_session.c` follow 0x4547b0 / 0x454830 / 0x4548e0: parameter 1..3 gives the mode 0..2 of the
marker grid 0x435e80 (empty never; stone only in mode 2; bomb in modes 1 and 2; normal kinds in all),
and every 180 ms (0x4ac7b0 gives 12 * 15, the table 0x4f7c54 holds 15 for every difficulty) one pair is
drawn as in 0x436150 (first draw below the count of waiting markers, second below the count minus one,
both taken in row order, 0x4360b0), marked as swapped and the two kinds exchanged, with enum 4 played
per swap (0x4f8190). The run ends when fewer than two waiting markers are left. The recovered
pieces it is built from (0x435e80, 0x4360b0, 0x436150) were verified against the original on object
boards; this session-level composition is checked on the host for conservation of kinds, the swap count
and untouched unmarked cells (`/Volumes/SSD/larsen/claude-tmp/mix/t.c` style test), not against the
original. Simplifications: the original stops the target's play (0x43bb60 state 4) and resumes it
through 0x43bbf0 after a one-frame handler 0x454970; here the phase simply returns to PLAYING, and the
draws come from the target session's generator instead of the one global generator.
Still missing: the roulette that selects the effect (see above), so nothing starts a mix yet.

## Freeze bonus (dispatcher id 8, ported to the session, not yet reachable)

`vertrix_session_start_freeze(session, parameter)` and `VERTRIX_PHASE_FROZEN` follow 0x454560 /
0x454600: the type is parameter - 1 (0x43c2b0), the timer object is set by 0x43b930 to 12 times the
dword at 0x4f7c90 + 4 * (difficulty * 5 + type) (700, 800, 900 for types 0..2 at every difficulty,
so 8.4, 9.6 and 10.8 seconds; the unit is the millisecond clock of 0x4b7d10), and 0x43b970 ends the
freeze when the timer object is gone. The ice overlay (0x438960 / 0x438c60 / 0x438b90), the sound
[0x4f8194] and the original's player states (0x43bb60 state 4, 0x43baf0) are not reproduced.

## Level, random speed and the effect dispatcher (session level)

`vertrix_session_lower_level` (id 9, 0x452d10 through 0x43b720: the level falls by the parameter, floor
zero, enum 5 when it changed), `vertrix_session_random_speed` (id 12 and the mad speed mode, 0x4528e0
through 0x43b7c0: a draw of 0..9 from 0x482750 repeated until it differs from the current speed, enum
5 or 6 by direction) and `vertrix_session_apply_effect(self, target, id, parameter)` for the ids 2, 6,
7, 8, 9, 12 and 0x18 are in `game_session.c`. Sound events follow the original table 0x4f8180: enum 5
= FX06 laser down (0x4f8194), enum 6 = FX07 laser up (0x4f8198), enum 11 = FX12 particles (0x4f81ac,
played by exchange speeds when the speeds differed), enum 12 = FX13 (0x4f81b0, the launch of the
letters 0x45a0c0). `tools/wii_game.c` plays FX06 and FX07 for the new events of the own session.
Nothing calls `vertrix_session_apply_effect` yet because the selection is not ported.

## Column insertion bonuses (ids 13 and 20, read, not ported)

Handler 0x453f40 (or 0x454250 when the caster's byte +0x190 is not zero) starts them: the target gets
+0x42c = type (0x3d0: 0 for id 13, 1 and 2 for id 20) and +0x430 = 0. Each tick of 0x454090 slides the
new column in (progress +0x58 up to 0x18 pixels), then 0x42f580 pushes every row that has an incoming
block one cell to the right (the rightmost cell of such a row is evicted; `board_shift` is the verified
object-level routine) and 0x431780 deals the column once (b == 0): the pattern row `type` of the table
at 0x4f9ad8 (13 bytes, row 0 = random kinds, row 1 = stone / random alternating, row 2 = all stones).
A byte 1 draws below 5 and is redrawn while it equals the value above it in the new column or the kind
at the left edge of the same row; 2 stores a stone; 0 leaves the cell empty. Sound [0x4f8188] (enum 2,
FX03 push up) plays when the column is dealt. Open: what the original does to a falling piece while
the board is pushed (0x432040, 0x43a560 and the +0x170 flag are involved), which decides whether the
effect can be applied to the simplified session board.

Update: the column bonuses are in the session (`vertrix_session_start_column`, `VERTRIX_PHASE_INSERTING`,
ids 13 and 20 in `vertrix_session_apply_effect`). Read from 0x453fd0 / 0x454090 / 0x42f6e0: the column is
dealt at once (0x431780 with b = 0; sound enum 2), slides in for 12 ticks of 48 ms (period 12 * 4 from
0x4f7c3c, 2 pixels per tick from 0x4f7c48, 24 pixels in all), and at the end 0x42f6e0 steps the falling
piece one column right when the touch table allows it (the session uses its own horizontal move test),
then 0x42f580 pushes every row that has a dealt block one cell right (the rightmost cell of the row is
lost). Checked on the host (shape, rules for the draws, the shift, the timing); the piece handling after
the shift (0x432040, 0x43a560, 0x42eb60) is not reproduced.

## Bottom-row bonuses (ids 14 to 16, 19, 21, 22; ported, host-tested only)

`vertrix_session_start_rows` follows 0x453c00 (stores the group in +0x424, step 0 in +0x428),
0x453c90, 0x453d50 and the row dealer 0x4314a0 over the pattern table 0x4f9800 (24 groups of six
rows of five cells, embedded as `ROW_PATTERN`). Group per dispatcher id and parameter, read from
0x43c140: 14/15/16 give 0 to 8, 19 gives 9 to 11, 21 gives 12 to 17, 22 gives 18, 19, 20, 22, 21,
23 for the parameters 1 to 6 (the order of 4 and 5 is as in the exe).

- A row is dealt when the step is below six and the group has more non-empty rows than the step.
  Pattern 2 is a stone; 1 draws below five and redraws while equal to the left cell (the previous
  dealt cell, or the bottom cell of the left column when that is empty; 0xff in column 0), the right
  bottom cell (only when the next pattern byte is 0 and the column is below 4) or its own bottom
  cell. The push sound (enum 2, `[0x4f8188]`) plays for every dealt row.
- The row rises 2 px per tick (0x4f7c18) of 12 * 0x4f7c0c[difficulty] ms (4, 4, 4, 2, 2, 2). At 24
  px 0x42f310 shifts every column that received a cell up one cell (the top block is lost; columns
  without a cell stay), the falling piece goes up a cell when its column received a cell
  (0x42f3d0 through 0x42efa0), then the next row is dealt; no row left ends the effect.
- The column slide of ids 13 and 20 now takes the same per-difficulty tick and pixel tables
  (0x4f7c3c, 0x4f7c48: 4, 4, 4, 2, 2, 2 and 2, 2, 2, 15, 15, 15), it was fixed at 576 ms before.
- Not ported: the re-spawn of a piece that has not yet entered the board (0x432010, 0x431340,
  0x42eb60), 0x43a560 on the next piece, the per-column spawn delays from 0x4f97f8 (visual), and
  drawing the rise offset (`rise_offset`). Ids 13 and 20 were also added to the dispatcher.

## Timed power states (dispatcher ids 34 to 52; partly ported, host-tested only)

Each id installs a one-shot handler (0x453620 to 0x453b90): if the holder's `+0x4c8` already
equals the state it only runs 0x43acd0, otherwise 0x43ac00 (face), optionally the laser up sound
`[0x4f8198]` (0x43c0e0) and the starter 0x43cd60 to 0x43d0f0 on the holder. The state is the id
minus 34 plus 0x22. Holder: the player for 34, 41, 42, 43, 48, 50, 51, 52, the opponent for 35, 36,
40, 44 to 47, 49; the sound plays for 34, 41, 42, 48 only. Ids 37 to 39 (0x453b90, starter 0x43ccf0,
states 0x25 to 0x27 without a timer, `[0x4e4]` the index) are not ported.

A starter stops the timer (0x43b980 / 0x43ce00), starts the timer actor `+0x4e8` of 12 times the
steps (0x4f9c14: 4000, 0x4f9c20: 3000, 0x4f9c2c: 1000, 0x4f9c38[[0x3fc]]: 1000, 2000, 3000 for
0x32 to 0x34), stores the state (0x43bb40), sets `+0x4dc` = 2 and `+0x470` = 3 (0x43cde0; 3 for
0x24, 4 for 0x30, 1 for 0x2f) and for 0x22, 0x23, 0x28, 0x29, 0x2a, 0x2d, 0x2e regenerates the
preview (0x43d260). 0x43b8a0 steps the timer; when reached 0x43ce00 ends the state (state 0,
threshold 2, preview again). Ported: preview/spawn generation modes (piece.c, already verified),
the match threshold of 0x24 (ends at the first reward with the laser down sound, 0x451871), the
random speed at every spawn of 0x31 (0x451289 calls 0x43b7c0). Not ported: 0x23 (lock handler
0x4513f0 and `+0x44c`), 0x2b (0x45106f, sound objects on moves), 0x2c (0x431fb0 marks the piece
blocks, +0x93, +0x95, +0x4e, +0x48 and sets piece `+0x17c`), 0x2f, 0x30 and 0x32 to 0x34 (their
consumers were not found yet; `+0x470` is read by 0x451c07 with `+0x46c`), the HUD icon
(0x44c5a0, table 0x53bb10) and the remaining-time display (0x43b860, 0x4f89ac = 220).
