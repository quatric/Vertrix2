# Vertrix 2 v2.0: full Wii port in progress

The objective is the entire original game, preserving its behavior. This is not
yet a playable Wii release. The handwritten recreation was removed from the
deliverable source tree. No guessed game loop, AI, speeds, or bonus effects are
used as substitutes for the original implementation.

## Original package

The supplied installer contains an ACE self-extracting archive. Its game
executable is an unpacked 32-bit Windows PE with image base `0x00400000` and
entry point `0x004eb454`. It imports DirectDraw, DirectInput8, WinMM, Windows
registry/window APIs, and other platform functions. The asset file contains
1,525 entries, including the original artwork, masks, music, voices, animation
definitions, and text. The original CHM manual is also available.

`tools/extract.py` verifies the installer fingerprint, extracts the original
files with payload CRC verification, decodes the asset directory, and writes
SHA-256 manifests. The original installer is not modified.

## Recovered native routines

| Original address | Behavior | Current native implementation |
| --- | --- | --- |
| `0x004328e0` | Identify occupied cells above holes | `board_falling_mask` |
| `0x00432980` | Collapse the byte board used by AI | `board_collapse` |
| `0x00433e20` through `0x00433f43` | Construct live blast area before FX creation | `board_blast_mask` |
| `0x00434300` | AI estimate of stones and blocks in a bomb pattern | `board_bomb_estimate` |
| `0x004346b0` | Line/column/diagonal masks and rewards | Line pass in `match_board` |
| `0x00434ee0` | Nine special figures, precedence, masks, and rewards | Figure pass in `match_board` |
| `0x00432480` | Figure/line orchestration with a preserved board copy | Combined behavior in `match_board` |
| `0x00417c80`, `0x004178d0` | Original character bonus lookup | 532 recovered table entries |
| Data at `0x004f8d38` | Character speed indices | 19 recovered entries |
| `0x00482640`, `0x004826c0`, `0x00482770` | Seeded repeating random buffer and range draws | `random.c` |
| `0x00482550` | Clock-reseeded refill, initially and every 500 samples | `vertrix_random_clock` |
| `0x0043b5b0`, `0x0043b660`, `0x0043b680` | Player delay parameter draws | `timing.c` |
| Data at `0x004f8d84` | Difficulty delay parameters | 180 recovered entries |
| `0x0043d130`, `0x0043d180` | Three-block types and mode-dependent random consumption | `vertrix_piece` |
| `0x00431ae0` | Signed pixel-to-board coordinate conversion | `board_pixel_cell` |
| `0x0042f030`, `0x0042f120` | Side-contact decision with supplied original row mask | `vertrix_side_contact` |
| `0x0042f580`, `0x0042f620` | Horizontal board row insertion and eviction | `board_shift` |
| `0x0042f310` | Rising column insertion and eviction | `board_rise` |
| `0x00431b80` | Active-piece downward clearance probe | `vertrix_down_clear` |
| `0x00431c60` | Lock block types and discard out-of-board blocks | `board_lock` |
| `0x0043ba90` | Difficulty score multiplier, wrapping arithmetic and cap | `vertrix_score_add` |
| `0x00431400` | Level-dependent active-piece motion parameter update | `vertrix_motion_level` |
| `0x004ac500` family, `0x004ac600` family | Integer elapsed accumulators and cycle consumption | `timer.c` |
| `0x004b7d10` | Clock sample to bounded elapsed interval | `vertrix_frame_sample` |
| `0x0042fc2d` loop, clear branch `0x0042fe81` | Integrated pixel descent and locking | `vertrix_descent` |
| `0x00431d90` through constructor boundary `0x00431e28` | Spawn-column selection and position inputs | `vertrix_spawn_position` |
| `0x0042a8b0`, `0x0042a8e0` | Cycle piece blocks and replace bottom normal color | `piece.c` |
| `0x00431100`, `0x00431140` | Occupancy-checked horizontal piece movement | `vertrix_move_horizontal` |
| `0x00431390` | One-time fast-descent motion state transition | `vertrix_motion_fast` |

The board is column-major, five columns by thirteen rows. Normal types are
`0..4`, stone is `5`, bomb is `6`, and empty is `255`. Live blast radius uses
strict comparisons. Pattern 4 includes additional vertical arms in neighboring
columns. The AI estimator uses full rows/columns independently of that radius;
this distinction is preserved.

The differential verifier executes original x86 machine instructions through
Unicorn on the development host. It does not emulate the Windows game on Wii.
For the live blast it stops at the verified mask boundary before platform FX
creation. Those later effects, their timing, and resulting game transitions
are not yet recovered by this implementation.

Both random modes contain 4,097 samples, with three original CRT draws per
sample. The clock mode obtains time once at refill entry and again after every
500 samples, then refills when consumption reaches the buffer end. A platform
callback supplies the original time value in seconds. This verifies the refill
and consumption behavior; game startup and clock integration remain separate
work. The oracle replaces the Windows thread-local storage provider with a
single-thread storage shim and supplies controlled values at the original
time() boundary; the original random arithmetic executes unchanged. Delay verification covers
player fields `+0x458`, `+0x45c`, and `+0x460`, not their game-loop scheduling.

Piece generation reads the original player mode field `+0x4c8`. Mode `0x22`
draws six values and converts value 5 to bomb type 6; `0x28` retains it as
stone type 5. Mode `0x29` repeats the second color as the third, `0x2a`
repeats the first color three times, `0x2d` draws three colors before replacing
the third with a stone, and `0x2e` rejects repeated colors until all three
are distinct. Other modes draw three independent colors. These mode numbers
are preserved as player-field values; they are not assumed to be bonus IDs.
Spawn, rendering, movement, and collision remain unrecovered.

## Verification and build

Install `tools/requirements.txt` in a development virtual environment. Run:

```sh
python tools/extract.py /path/to/Vertrix2-v2.0-Install.exe /path/to/scratch/extracted
python tools/verify_board.py /path/to/extracted/original/Vertrix2.exe \
    --build-dir /path/to/scratch/verification --cases 1000
python tools/verify_random.py /path/to/extracted/original/Vertrix2.exe \
    --build-dir /path/to/scratch/random-verification
python tools/verify_timing.py /path/to/extracted/original/Vertrix2.exe \
    --build-dir /path/to/scratch/timing-verification
python tools/verify_piece.py /path/to/extracted/original/Vertrix2.exe \
    --build-dir /path/to/scratch/piece-verification
python tools/verify_coordinates.py /path/to/extracted/original/Vertrix2.exe \
    --build-dir /path/to/scratch/coordinate-verification
python tools/verify_shift.py /path/to/extracted/original/Vertrix2.exe \
    --build-dir /path/to/scratch/shift-verification
python tools/verify_score.py /path/to/extracted/original/Vertrix2.exe \
    --build-dir /path/to/scratch/score-verification
python tools/verify_timer.py /path/to/extracted/original/Vertrix2.exe \
    --build-dir /path/to/scratch/timer-verification
python tools/verify_descent.py /path/to/extracted/original/Vertrix2.exe \
    --build-dir /path/to/scratch/descent-verification
python tools/verify_spawn.py /path/to/extracted/original/Vertrix2.exe \
    --build-dir /path/to/scratch/spawn-verification
make BUILD=/path/to/scratch/wii-build
make check-format
```

These checks prove the specified recovered board routines on the test corpus
and that they compile for Wii PowerPC. They do not prove full-game fidelity or
hardware execution. The build produces a recovered native library, not a
Homebrew Channel application.

The recorded corpus passed 38,000 board comparisons, 24,582 random sample
comparisons, 60,000 random range/position comparisons, and 10,260 delay
draw/position comparisons. All 532 native character power entries matched.
Clock mode additionally passed 36,873 sample comparisons and 39,000
range/position comparisons, including changing clocks and buffer refills.
Piece generation passed 40,376 block-triple and RNG-position comparisons,
including mode transitions and buffer wrap.
Coordinate conversion passed 24,641 comparisons, including signed extremes
and positions outside the board. Further movement findings are recorded in
`MOVEMENT-RECOVERY.md`. Left/right contact decisions passed 20,000 comparisons
with supplied masks; mode-mask selection and movement responses remain incomplete.
The recovered source modules compile for Wii PowerPC with warnings
treated as errors. Formatting is enforced by `.clang-format` and
`make check-format`.

## Remaining full-game recovery

- Original player state, piece spawning, movement, collision, falling timing,
  locking, resolution transitions, three-second win conditions, and scoring.
- All 93 bonus implementations, activation selection, timed states, and their
  interactions. Lookup tables are recovered; effect behavior is not complete.
- Original AI decisions and difficulty behavior; its byte-board collapse and
  bomb estimator are recovered components only.
- Original menu flows, practice, local multiplayer, tournament, round rules,
  character/story sequences, endings, settings, saves, and network modes.
- Sprite/animation decoding, original composition, music playback, voices,
  sound effects, and Wii platform replacements for Windows services.
- An installable Wii application, emulator end-to-end comparisons, and real
  controller/hardware validation.

The original graphics and music credits remain those of the original game.
No ownership of the extracted game material is asserted by this project.

## Runtime asset format

The native `vf.c` loader reads the unchanged original `Vertrix2.vf` directly;
runtime assets will not require unpacked folders. All 1,525 payload hashes
match the independently extracted manifest. See `ASSETS.md` for the API,
intended SD layout, verification, and remaining runtime integration.

## Held input repeat scheduling

`source/input.c` recovers start (`0x475ad0`), stop (`0x475af0`) and
repeat scheduling (`0x475e50`, timer helpers `0x475de0`–`0x475e30`).
Only enable byte exactly 1 and a nonzero repeat delay advance the counter.
Addition wraps unsigned 32 bits. At the initial threshold, event count is
counter divided by the current period (zero period uses divisor 1).
The counter resets to zero, discarding any remainder, and the period becomes
the repeat delay, even if no events were generated. Start stores the supplied
three-word payload and selects the initial delay; stop only clears enable.
The native API returns the number of events to enqueue, each carrying that
stored payload. It does not impose guessed Wii repeat settings.

6,420 comparisons execute the original arithmetic and start/stop routines.
The oracle intercepts only `0x475b20` queue insertion, recording the count and
three payload words instead of allocating original Windows objects.
Checks include wraparound, zero periods, exact enable-byte semantics and
payload/state preservation. Controller polling, bindings and full gameplay
dispatch remain unfinished.

```sh
python tools/verify_input.py /path/to/Vertrix2.exe --build-dir /path/to/scratch/input
```

## Input action queues

`source/input.c` now preserves FIFO action consumption (`0x475c30`), state
copy (`0x4757e0`), readiness (`0x475d70`), acknowledgment (`0x476320`) and
both update policies (`0x475cd0`, `0x475d20`). An acknowledgment resets current
state and all three payload words without popping a queued event. Explicit
consumption resets current first, even when the queue is empty.

Mode 0 consumes at most one event per update, including when a press is
already pending. Mode 1 keeps state 1 pending until acknowledged; the single
update policy consumes at most one event, whereas the drain policy skips
other states until reaching a press or exhausting the queue. Other modes
leave current and pending events unchanged. Nonzero global `0x553648`
suppresses only the single policy, after original repeat generation. Thus
callers must schedule repeats before queue update. These are separate
policies, not an assumed pair of frame phases: the original frame poll
calls `0x476400` / `0x475cd0` at `0x41dee3`; input processing also calls
`0x476440` / `0x475d20` at `0x4736ee` and `0x473bb8`.

126,482 queue-operation comparisons cover mixed presses/releases/arbitrary
state bytes, all update modes, deferred gating, acknowledgment, empty queues,
three-word payloads and FIFO order across successive operations. The oracle
executes original pool-list removal (`0x4d8540`, `0x4d84f0`), state copying,
readiness and update branches. Only event destruction and empty-pool storage
release (`0x4d83c0`) are replaced. The native queue uses ordinary allocation
and reports allocation failure rather than reproducing the original pool.
Clear/reuse lifecycle checks exercise native storage cleanup separately.

This recovers an input subsystem, not a playable Wii application. Controller
bindings, deferred event storage/dispatch and integration into the recovered
game state still require work. Report: `docs/input-verification.json`.

## Integrated input actions

`VertrixInputAction` combines the recovered queue and repeat scheduler.
Guarded press (`0x4761d0`) emits state 1 and starts repeats only when the
repeat-enable byte is exactly zero; duplicate presses while enabled do
nothing. Guarded release (`0x476280`) emits state 2 and stops repeats when
that byte is nonzero. The forced variants (`0x476360`, `0x4763c0`) emit without
those guards and start/stop the repeat scheduler respectively.

With global `0x553648` nonzero, presses go to deferred delivery with the
original stored action ID and all three payload words (`0x475b20` routes to
`0x475b80`). A guarded deferred press leaves repeats unchanged, and a guarded
deferred release does nothing. A forced deferred press still starts repeats;
a forced deferred release stops them without emitting a release. Repeat
updates generate all due press events before applying the queue update policy,
including when deferred mode suppresses the single queue update.

80,000 sequential integrated comparisons run the original four edge wrappers,
repeat scheduler, queue removal/copy, acknowledgment and update policies.
They compare complete repeat state, current action, every pending FIFO event,
and cumulative deferred action IDs/payloads. Event allocation/enqueueing and
storage destruction are supplied by the oracle boundary; native pool replacement
and deferred callback delivery are covered through observed sequences.
These supplement the 6,420 arithmetic and 126,482 queue-operation comparisons.

Deferred delivery uses a callback so the future platform can retain its global
queue and routing semantics. The callback must synchronously copy the payload.
Native allocation/delivery failure returns zero; callers must stop processing
rather than retry a partially advanced action. No Wii bindings or scheduling
parameters are guessed by the library. The original input object constructor
`0x475840` uses global `0x553644` for both delays; initialization/configuration
of that global and controller bindings remain to be recovered.

## Applying configured input delays

`vertrix_input_configure` recovers the ordered control-settings application
at `0x425b8d` through `0x425d26`. The first eight IDs come from settings globals
`0x532b6c` through `0x532b7a`, and the ninth from `0x532b7c`. The ninth is put
in mode 1. Both initial and repeat delays of controls 0–2 use player delay
`0x532b80`; controls 4–6 use `0x532b84`; controls 3 and 7 use global default
`0x553644`. Setter wrappers are `0x476500` (initial) and `0x4764d0` (repeat).
Only these fields change: ongoing counters, periods, payloads and queued
inputs stay intact. Binding aliases receive the original ordered overwrites.

500 complete 256-entry configuration comparisons execute this original
instruction range, without replacing any calls, using varied settings and
deliberately repeated control IDs. An additional native bounds check rejects
IDs outside the 256-entry table before mutation; the original valid-input
behavior is preserved without reproducing its unchecked memory access.

The preceding setup at `0x425ae0` clears input state, configures mode-1 keys
and rebuilds mappings through `0x473490`; it is outside this helper's scope.
Settings parsing, actual default-value initialization and Wii binding
translation still need recovery and integration. This change applies supplied
original settings and does not choose replacement timings.

## Active-piece control dispatch

`source/controls.c` connects recovered input actions, horizontal movement,
piece cycling, bottom-color RNG and fast-drop parameters. It follows player
handler `0x450ff0` from `0x451048` to `0x4511bb`, including the failed-movement
branches `0x4512f3` and `0x4512ff`. Controls use original player words
`+0x168/+0x16a/+0x16c/+0x16e` and execute left, right, cycle, then fast drop.
Every ready action is acknowledged, including failed moves. Aliased action
IDs therefore retain the original ordering effects.

Successful horizontal movement in player mode `0x2b` generates a guarded
press then release for the opponent's `+0x160` or `+0x162` action. These use
the recovered repeat gating and deferred routing. Failed movement requests
the original refresh flag (`0x43ad50`, target object `+0x178 = 1`). Cycling
uses `0x431180` / `0x42a8b0`; active piece `+0x17c == 1` additionally invokes
`0x4311a0` / `0x42a8e0` and requests refresh, even if stone/bomb prevents a
color change. Fast input invokes `0x431390` and acknowledges regardless of
whether the motion state permits a parameter change. The caller supplies
the original difficulty (0–2), mode fields and action IDs.

5,000 integrated comparisons execute the original handler prologue and
entire input slice, stopping before virtual board update at `0x4511bb`.
Movement, cycling, sprite color setter, random draw, motion changes,
acknowledgments, refresh assignment and opponent edge wrappers execute their
original instructions. Only the preceding `0x43ad70` display/preview update
and event allocation/enqueue boundaries are substituted. Comparisons cover
blocked/clear boards, subcell positions, walls, simultaneous and aliased
controls, stone/bomb blocks, special modes, deferred delivery, failed boards,
all difficulties and varied repeat/motion state bytes. They compare piece X,
all colors, motion parameters, complete affected input/repeat state, generated
opponent events, refresh requests and RNG position across four seeded streams.

The surrounding player state machine, initial spawn, board virtual update,
preview scheduling, animation and rendering remain unfinished. This component
is part of the full port, not a playable or complete game. Verification report:
`docs/controls-verification.json`.

```sh
python tools/verify_controls.py /path/to/Vertrix2.exe --build-dir /path/to/scratch/controls
```

## Timed active-piece descent and frozen blinking

`vertrix_descent_tick` connects elapsed-time arithmetic to the original pixel
movement and locking loop. It recovers the active-piece path `0x42fbba` through
`0x42fc56`, including the alternate branch `0x42fe9e` through `0x42fef1`.
The preceding board-effect/preview update and following sprite/board virtual
updates remain outside this function.

The primary counter (piece `+0xbc`) always adds global elapsed `0x5bd834`
with unsigned wrapping. Normal falling clears the secondary counter `+0xdc`,
calculates wrapped `counter * signed16(step) / (period or 1)` through `0x4ac590`,
and resets the primary counter only if that produces a positive pixel budget.
The budget enters the recovered collision-before-movement loop, including
locking and board failure assignment. Subpixel time accumulates until a
positive budget is available; no remainder survives a positive-budget update.

Nonzero player `+0x4cc` or board `+0xb80` selects the frozen path and always
clears the movement counter. Board `+0xb90 == 1` additionally selects frozen
appearance via `0x42aa20`, advances the secondary timer and, when due, resets
that timer to zero and invokes `0x42a9d0`. That routine writes original child
`+0x48` effect words (0 or `0xff38`) and wraps `flash = 1 - flash`. The recovered
state retains piece `+0x180/+0x184`, cycle mode `+0x17c` and child effect values;
returning from frozen appearance restores effect 20 for cycle mode 1 or zero
otherwise. Effect values only describe live children; locking transfers or
releases those objects separately.

6,000 timed-update comparisons execute the original timer helpers, appearance
transitions, blinking routine, pixel loop and lock routine. They cover zero
periods, signed step-word boundaries, unsigned overflow, fractional budgets,
paused/frozen flags, exact blink-mode checks, unusual appearance state values,
clear/occupied boards and lock/failure outcomes. The fixture uses a valid board
origin so fully-above-board probes stay within the recovered collision routine's
storage domain. A zero-origin negative-pixel fixture was rejected because it
would probe outside that domain. The previous 10,000 integrated descent and
20,000 horizontal movement comparisons also pass.

```sh
python tools/verify_descent.py /path/to/Vertrix2.exe --build-dir /path/to/scratch/descent
```

The original frame orchestration, sprite updates, board effects and resolution
state machine still require recovery. This is not a complete Wii application.

## Active-piece spawn initialization

`vertrix_spawn_initialize` now connects the original spawn-position logic to
native piece, descent timer and animation state. Original routine `0x431d90`
executes piece constructor `0x42a310`, block constructor/setup `0x42a540`, and
then reapplies the supplied block colors. The native initialization sets the
same recovered fields while replacing pointer ownership with explicit state.

There are twelve random draws per spawn. Temporary colors 0, 1 and 2 each
consume one animation-delay draw through `0x415470` and one modulo-10 animation-speed
draw. The final supplied colors consume the same two draws each. Animation-delay ranges
come from the original loaded `0x53bcd0` table; the native caller supplies those
ranges rather than assuming sprite counts. Delay selection is first plus
modulo(last-first+1). The primary timer periods are `12 * (modulo(10)+1)` through
`0x4ac7b0`; counters start at zero. The discarded temporary draws are preserved
so subsequent gameplay retains the original RNG position.

The active-piece primary period and signed-word step use the recovered
3-by-10 difficulty/level tables; counters and motion state are zero. Secondary
blink period is 400; frozen, flash, cycle-mode and child-effect values are
zero. Board blink mode becomes 1. Preferred spawn column returns to 2 after
construction. If the selected column is 2 and its top cell is occupied,
the board failure flag becomes 1; otherwise its previous value is retained.
The piece still exists in that failure case, as in the original.

4,800 comparisons execute the full original spawn routine and constructors,
including all animation-delay selection, timer setters and RNG instructions. The oracle
provides single-thread SEH storage and replaces only heap allocation with
reserved scratch memory. Allocations start with nonzero bytes to verify that
initialization does not rely on zeroed allocation. Checks compare coordinates,
all colors, both timers, motion/special-mode fields, child effect values,
animation/primary timer parameters, failure/preferred-column state, blink mode and
RNG position. Four seeded sequences cross the 4,097-sample buffer boundary.
The previous 20,490 spawn-position comparisons also pass.

```sh
python tools/verify_spawn.py /path/to/Vertrix2.exe --build-dir /path/to/scratch/spawn
```

Clipping/resource ownership, original graphics decoding,
sprite updates, preview and player state-machine integration remain unfinished.
This initializes the recovered native fields, not a finished Wii game.

## Direct archive loading of block animation delays

`source/assets.c` now reads the original `texte/BlocsSpeed.ini` payload directly
through the VF loader. The file contains 20 character/decor rows and 14
minimum/maximum delay columns. Original initialization (`0x414251` through
`0x414293`) reads this file into the column-major table `0x5336ac`.
`0x415330` / `0x415350` selects one character's seven color ranges into
`0x53bcd0`. Native loading preserves the important column order: colors 0–4
use pairs 0–9; bomb (native 6) uses pair 10–11; stone (native 5) uses 12–13.

These values are animation delays in milliseconds. The earlier recovery
labeled the `0x415470` random result as a frame choice; the archive's field
meaning and counter/period setters show it initializes child timer period
`+0xd0`, whose counter is `+0xcc`. The native API and spawn details have been
corrected to represent both this animation timer and primary timer `+0xbc/+0xc0`.
The recovered arithmetic and twelve-draw spawn RNG sequence are unchanged.

Validation loads all 20 rows from the untouched VF and compares all 140 color
ranges with original `0x415330` execution. The table supplied to that routine
comes from independently parsed archive bytes; original string-parser behavior
is not claimed as emulated. Eight malformed text fixtures are rejected without
changing the caller's output. The native parser accepts this original file's
comments, decimal fields, backslash delimiters and CRLF layout; it is not a
substitute for recovery of the game's general settings parser.

```sh
python tools/verify_assets.py /path/to/Vertrix2.exe /path/to/Vertrix2.vf \
    --build-dir /path/to/scratch/assets
```

The ranges can now be passed to `vertrix_spawn_initialize` without extracted
asset folders. Image/mask decoding, frame layout, renderer and Wii startup
integration remain unfinished. Report: `docs/assets-verification.json`.

## Original sprite animation playback

`source/animation.c` recovers forward-loop (`0x4ac1f0`), forward-once
(`0x4ac250`), reverse-once (`0x4ac2b0`) and reverse-loop (`0x4ac310`) playback.
Animation uses object counter `+0xcc`, period `+0xd0`, frame index `+0xb8`, and
resource frame count obtained through `0x487860` (resource `+4`). The normal
spawned-block handler `0x44c860` invokes forward-loop playback.

Elapsed time adds with unsigned wrapping. Once due, whole steps are computed
using period or divisor 1 and removed from the accumulator, preserving the
fractional remainder. Looping playback wraps at the original frame endpoints;
the native implementation computes the equivalent result without an unbounded
per-step loop. One-shot playback stops on an attempted step past the endpoint,
not simply on reaching it: landing exactly on the endpoint still reports
playing until a later due step tries to advance beyond it. All accumulated
whole steps are consumed before the one-shot stops. Completion is not latched
inside this function, matching the original; its caller chooses the next state.

108,244 comparisons execute the original four routines and timer/frame
helpers without substitutions. Another 20,000 sequential updates cover mode
changes and partial accumulated timing. Checks include forward/reverse bounds,
one-frame resources, zero periods, unsigned clock wraparound and large valid
frame indices. Native invalid-state checks reject zero frame counts, out-of-
range indices and unknown modes without changing state; original valid
resource behavior remains preserved. Report: `docs/animation-verification.json`.

```sh
python tools/verify_animation.py /path/to/Vertrix2.exe --build-dir /path/to/scratch/animation
```

Resource decoding must still provide real frame counts, and the renderer and
full game scheduler remain unfinished. This does not create a playable app.

## Alternating block byte intensity

Recovered complete handlers 0x44cbf0 and 0x44cc60 in block_byte_pulse.c. Both advance looping animation and the primary timer, set field 0x93, and bind the selected frame. Due ticks set the byte target to 100 or 0 with step 5, preserving original 32-bit wrapped arithmetic and byte narrowing. Arrival switches to the opposite handler. Invalid inputs preserve outputs.

verify_block_byte_pulse.py executes original handlers without routine hooks and compares whole block memory across 1,024 cases, including 682 linked-resource cases. Evidence: block-byte-pulse-verification.json. Full actor dispatch, VF binding and the playable application remain incomplete.

## Block effect return phases

Recovered complete 0x44cf00 and 0x44cf70 handlers in block_return.c. Both set field 0x95 to one, advance looping animation and the primary timer, then apply original signed-word effect transition 0x4ad530 when due. Arrival in the first phase selects 0x44cf70 and sets target zero and step ten. Arrival in the second phase selects normal handler 0x44c860. These handlers do not remove the object. Frame binding runs in all paths. Invalid input preserves outputs.

verify_block_return.py compares whole original objects without routine hooks across 1,024 cases, including 682 direct-to-linked resource transitions. Evidence: block-return-verification.json. Actual actor resource ownership, dispatch and full gameplay integration remain incomplete.

## Block scale transition phases

Recovered complete 0x44ce80 and 0x44cfd0 in block_scale.c, including animation, primary timer, signed dword transition 0x4ad6e0 and descriptor binding. Both set field 0x95 to one. Arrival in 0x44ce80 sets amount to 100, signed effect to zero, target to 50 and step to ten, then selects 0x44cf00. Arrival in 0x44cfd0 selects 0x44d030. Arithmetic preserves 32-bit wrap and signed clamping. Neither handler destroys the object.

verify_block_scale.py compares whole object storage against the actual original routines without hooks: 1,024 cases, 682 linked-resource cases. See block-scale-verification.json. Resource graph construction, actor dispatch and the playable game remain unfinished.

## Three-phase block effect chain

block_chain.c recovers complete 0x44d1e0, 0x44d250 and 0x44d2c0. Due ticks in the first two handlers set signed effect targets 100 and zero, with steps ten and twenty respectively. Arrival advances to the next handler. The third sets field 0x93 and fades the byte amount to zero with step eight, then selects normal 0x44c860. Field 0x95 is preserved. All phases advance looping animation, primary timer and descriptor binding. No destructor runs.

verify_block_chain.py executes original handlers without routine hooks and compares whole object storage in 1,024 cases, including 682 linked resource cases. Evidence: block-chain-verification.json. Full actor dispatch, VF ownership and gameplay application integration remain unfinished.

## Native linked frame resource traversal

frame_resource.c implements original 0x4877f0: kind one selects a child resource and mapped index repeatedly; all other kinds select a direct descriptor. Runtime resources use native pointers, retain no Windows addresses and allocate nothing during lookup. Caller-provided counts and traversal budget reject invalid storage, out-of-range indices and cyclic graphs without changing the descriptor output. These checks apply to malformed inputs; valid traversal preserves original selection.

verify_frame_resource.py runs original 0x4877f0 without hooks, comparing 4,419 descriptor lookups through 256 resource graphs up to eight levels deep. See frame-resource-verification.json. Resource construction, VF-backed ownership and actor update integration remain unfinished.

## Normal block update with live resources

block_resource.c composes original normal update 0x44c860, looping animation 0x4ac1f0 and frame binding 0x4ac8a0/0x4877f0 using native live resource nodes. No flattened frame list or per-update allocation is required. Resources are borrowed, and top resource count must match animation count. Animation and descriptor publish only after successful traversal.

verify_block_resource.py compares whole original objects without hooks across 1,024 cases, including 682 linked cases. See block-resource-verification.json. Resource construction from VF assets, ownership and all actor dispatch remain to be integrated into the full application.

## Resource attachment and deferred binding

block_resource.c now implements 0x4ac8d0 attachment and 0x4ac8a0 binding separately. Attachment clears animation counter and frame, retains period and descriptor, and changes the borrowed resource pointer. Native frame_count caches attached resource count, or zero after detach; the original obtains count from the resource. Binding with a null resource retains the existing descriptor. Valid non-null binding follows the original linked lookup.

The extended verify_block_resource.py compares whole original object storage through 1,024 attachment/binding pairs, including null detachment, alongside the 1,024 normal-update cases. No original routine hooks are used. Full actor construction and game integration remain unfinished.

## Resource last-frame selection

block_resource.c implements original 0x4ac720: obtain resource count and select count minus one with unsigned wrapping. Counter, period and descriptor remain unchanged. Empty resource count deliberately yields UINT32_MAX; subsequent update/binding validation remains separate. Native frame_count caches the original resource count. Extended verify_block_resource.py compares whole original object state across 1,024 endpoint cases including zero, one and UINT32_MAX counts without routine hooks. The same run retains normal update and attachment/binding verification. Full actor initialization and gameplay integration remain unfinished.

## Additional dword scale phases

block_scale.c now includes original 0x44d330 and 0x44d3a0. Both advance animation and primary timer, preserve field 0x95 and bind the selected descriptor. Due ticks target 100 with steps ten and twenty respectively using 0x4ad6e0 arithmetic. The first resets current to zero on arrival before selecting 0x44d3a0; the second selects 0x44d410 without resetting current.

Extended verify_block_scale.py executes all four recovered handlers without hooks across 2,048 cases and compares whole object storage, including 1,365 linked resource cases. Evidence replaces block-scale-verification.json. Full actor dispatch and gameplay integration remain incomplete.

## Scale sequence final fade

block_byte_pulse.c includes complete 0x44d410: set field 0x93, advance looping animation and primary timer, target byte amount 100 with step eight when due, then select normal 0x44c860 on arrival. Descriptor binding always runs. The extended leaf verifier compares 2,048 whole objects, including 1,365 linked cases.

verify_scale_chain.py additionally compares 256 successive three-phase sequences against the actual original handlers without hooks, covering 2,712 whole-object updates. All finish through 0x44d330 -> 0x44d3a0 -> 0x44d410 -> 0x44c860. Random periods and frame intervals are harness fixtures rather than gameplay defaults. Evidence: scale-chain-verification.json. Full actor runtime and playable integration remain unfinished.

## Negative signed block effect phases

block_chain.c includes original 0x44d480 and 0x44d4f0. Due ticks set signed effect target minus 100 or zero with step twenty. Arrival advances from 0x44d480 to 0x44d4f0, then to 0x44d560. Animation, primary timer and frame binding match existing phases; both flag bytes are preserved. The final 0x44d560 phase is recovered separately in block_finish.c.

Extended verify_block_chain.py compares five recovered handlers without hooks across 2,048 whole object cases, including 1,365 linked resources. Evidence: block-chain-verification.json. Actor integration and full gameplay remain incomplete.

## Paired fade and mode completion

block_finish.c recovers complete 0x44d560. Every update clears field 0x93 and advances looping animation and primary timer. Due ticks target byte amount zero with step eight and scale mode zero with step one, using the same consumed cycle count for both transitions. Each preserves original wrapped 32-bit intermediate arithmetic and byte narrowing. Only completion of both selects normal handler 0x44c860. Descriptor binding always runs.

verify_block_finish.py compares whole original object storage without hooks in 1,024 cases, including 682 linked resources and wide timer counters. Evidence: block-finish-verification.json. Full actor dispatch and playable integration remain unfinished.

## Paired scale restoration phase

block_finish.c includes complete original 0x44d6d0. Every update sets field 0x93 to one and amount to 80, including frames before the primary timer is due. Due ticks set amount target 80 with step eight and mode target 16 with step one. Both transitions use the same cycle count; arrival selects 0x44d760. The generalized byte transition preserves signed wrapped intermediate comparisons and narrowing for both directions.

Extended verify_block_finish.py compares both handlers without hooks across 2,048 whole object cases including 1,365 linked resources. Existing fade-to-zero behavior remains verified. Evidence: block-finish-verification.json. Full actor dispatch and playable integration remain unfinished.

## Restoration fade and signed return

Recovered complete 0x44d760 in block_byte_pulse.c: field 0x93 is one, due ticks target amount 100 with step eight, arrival selects 0x44d7d0. block_chain.c includes 0x44d7d0 and 0x44d840: signed effect targets 50 and zero with steps ten and twenty; arrivals select 0x44d840 and normal 0x44c860. Both preserve flag bytes, advance looping animation and primary timer, and bind descriptors.

Byte-phase verification covers 2,048 whole objects; signed-chain verification covers 3,072, including 2,048 linked resources. Original routines run without hooks. Evidence: block-byte-pulse-verification.json and block-chain-verification.json. Full actor dispatch and playable integration remain unfinished.

## Negative dword restoration lead-in

block_scale.c implements original 0x44d5f0 and 0x44d660. Due ticks set signed dword targets minus 100 and zero with step twenty, using 0x4ad6e0 wrapped arithmetic. Arrival advances through 0x44d660 to paired restoration 0x44d6d0. These handlers preserve field 0x95 and all other unrelated object fields; animation, primary timer and descriptor binding continue in both phases.

Extended verify_block_scale.py compares all six recovered dword handlers without hooks in 3,072 whole object cases, including 2,048 linked resource cases. Evidence replaces block-scale-verification.json. Full actor dispatch, renderer integration and playable game remain incomplete.

## Age-limited scale-mode oscillation

block_mode_pulse.c recovers complete 0x44d8b0 and 0x44d940. Field 0x95 becomes three every update; looping animation and primary timer advance normally. Due ticks add consumed cycles to the wrapping dword age, target mode zero or 16 with step one, and switch phases on arrival. Signed age >=30 overrides the phase switch and selects normal 0x44c860. Negative ages after overflow do not satisfy that limit. Descriptor binding always runs.

verify_block_mode_pulse.py compares whole original objects without hooks across 1,024 cases, including 682 linked resources. Evidence: block-mode-pulse-verification.json. Full actor dispatch and playable integration remain incomplete.

## Triple scale, signed effect and fade transition

block_triple.c recovers complete original 0x44d9d0. Every update sets field 0x95 to three, advances looping animation and primary timer, and binds a descriptor. Due ticks use the same consumed cycle count for mode target 16/step one, signed effect target 50/step twenty, and amount target zero/step eight. Amount completion alone selects normal 0x44c860; incomplete mode or signed effect does not prevent return. Field 0x93 is preserved. Wrapped intermediate arithmetic and byte/word narrowing remain faithful.

verify_block_triple.py compares whole original objects without routine hooks across 1,024 cases, including 682 linked resource cases. Evidence: block-triple-verification.json. Full actor runtime and playable integration remain unfinished.

## Age-limited mode oscillation with amount 50

block_half_pulse.c recovers complete 0x44da70 and 0x44db10. Due ticks move byte amount toward 50 with step ten, add consumed cycles to wrapping dword age, and move mode toward 16 or zero with step one. Mode completion switches phases independently of amount completion. Signed age >=30 overrides switching and selects normal 0x44c860. Field 0x95 becomes three every update. Animation, primary timer and descriptor binding retain original behavior.

verify_block_half_pulse.py compares whole original object storage without hooks across 1,024 cases, including 682 linked resources and wide timer/age values. Evidence: block-half-pulse-verification.json. Full actor runtime and playable integration remain unfinished.

## Staged signed-effect fade

block_staged.c recovers complete 0x44dbb0. Field 0x95 becomes four every update. Due ticks target mode 16/step one, signed effect 50/step five, and amount zero/step four. Stage byte +0x52 becomes one at signed effect >=15, two at >=30, and three at exactly 50; values below 15 preserve the previous byte. Only amount completion selects 0x44dc80. Original animation, timer and descriptor binding remain intact.

verify_block_staged.py compares whole original objects without hooks across 1,024 cases including 682 linked resources. Explicit boundary fixtures cover negative effects and values 14,15,29,30,49,50 with zero consumed cycles. Evidence: block-staged-verification.json. Full actor runtime and playable integration remain unfinished.

## Staged effect return sequence

block_chain.c includes original 0x44dc80: due ticks target signed effect zero with step twenty, arrival selects normal 0x44c860. Both flags and the stage byte remain unchanged. Animation, primary timer and descriptor binding match the original. The expanded leaf verifier checks eight handlers across 3,072 whole object cases.

verify_staged_chain.py compares 256 complete 0x44dbb0 -> 0x44dc80 -> 0x44c860 sequences against actual original routines without hooks, covering 2,142 successive whole-object updates. Timer periods and intervals are fixtures. Evidence: staged-chain-verification.json. Full actor runtime and playable integration remain unfinished.

## Threshold-gated moving departure effect

block_departure.c recovers complete 0x44dcf0. Field 0x95 becomes three; due ticks add cycles to wrapping age. Only signed age strictly greater than signed threshold resets age, increments the vertical step with word wrapping, targets signed effect minus 200/step thirty and mode zero/step one, then moves both coordinates by cycles times step. Mode completion selects normal but movement still runs. The original 24-pixel bounds then select normal when outside object clipping limits. Animation, timer consumption and binding run even while threshold gating suppresses movement.

verify_block_departure.py compares whole original objects without hooks across 1,024 cases including 682 linked resources. Explicit fixtures cover strict threshold equality and clipping boundaries with no motion delta. Evidence: block-departure-verification.json. Full actor runtime and playable integration remain unfinished.

## Original per-cycle rotation

rotation.c recovers 0x4ad060, needed by 0x44de20. Each cycle adds signed-word step with 16-bit wrapping, then normalizes angles outside 0..359. A negative wrapped angle adds 360, narrows unsigned to a word, then takes remainder 360. Thus extreme steps cannot be replaced by one ordinary modulo expression. Trace records whether any normalization occurred and the consumed iterations. Zero step or zero cycles retains the previous global iteration count and returns unwrapped one. Native callers supply shared trace state corresponding to original globals 0x5bb5f4/0x5bb5f8.

verify_rotation.py executes the original without hooks and compares complete object storage, return value and trace globals in 1,024 cases, including signed-word extremes. Evidence: rotation-verification.json. Coordinate lookup and the enclosing actor handler remain unfinished, as does full playable integration.

## VF fixed-point rotation coordinates

Original initializer 0x484550 requests Sin.tab and Cos.tab, each 0x5a0 bytes. rotation_tables.c loads the original 360-entry little-endian tables directly from VF table/Sin.tab and table/Cos.tab. Tables own inline storage and remain valid after archive closure. Coordinate function recovers 0x4ad1c0 and 0x4849e0: wrapped 32-bit radius shift, signed 64-bit product, original intermediate narrowing and signed-word coordinate output. No regenerated trigonometric values are used.

verify_rotation_tables.py compares all 720 values against extraction references and 2,048 coordinate calculations against original instructions without hooks, including signed radius extremes. Original tables are populated in oracle memory; the file I/O initializer itself is not executed. Evidence: rotation-tables-verification.json. The enclosing actor handler and full playable integration remain unfinished.

## Shared signed-word transition primitive

word_transition.c recovers common arithmetic of original horizontal 0x4aca60, vertical 0x4acab0 and signed effect 0x4ad530. It preserves wrapped multiplication and addition/subtraction, signed intermediate clamps, word narrowing and completion comparison after narrowing. block_motion.c now calls this primitive so future rotation movement can use the same implementation.

verify_word_transition.py executes all three original routines without hooks across 3,072 whole-object cases, including full-width cycle counts and signed step extremes. Affected motion, pulse, return and chain leaf verifiers pass; scale and staged sequence verifiers also pass after the change. Evidence: word-transition-verification.json. The enclosing rotating actor and full playable game remain unfinished.

## Shared signed-dword transition primitive

dword_transition.c recovers common arithmetic of original 0x4ad6e0 and 0x4acc70: unsigned wrapped distance multiplication and addition/subtraction, signed clamps, and exact completion return. block_scale.c now uses this primitive, which can also serve the rotating effect.

verify_dword_transition.py compares both original routines without hooks across 3,072 complete object cases, including full-width cycles and signed step extremes. All six scale handlers and 256 complete scale-to-fade sequences remain verified after the change. Evidence: dword-transition-verification.json. The enclosing rotating actor and full playable game remain unfinished.

## Shared byte transition primitive

byte_transition.c recovers mode 0x4acc10 and amount 0x4ad580: unsigned byte endpoints, signed-word step, wrapped distance and arithmetic, signed intermediate clamps, byte narrowing and completion after narrowing. block_fade.c now calls this common primitive, also available to the rotating effect.

verify_byte_transition.py compares both original routines without hooks across 3,072 whole-object cases with full-width cycles and signed step extremes. Existing fade, chain and staged sequence verification passes after the change. Evidence: byte-transition-verification.json. The rotating actor and full playable game remain unfinished.

## Complete first rotating block phase

block_orbit.c recovers complete 0x44de20 using verified primitives. Due ticks rotate the angle, read exact VF table coordinates with radii 48 and five, derive the byte mode target from 11 plus vertical offset, measure the OLD bound descriptor or fallback, and set movement targets around the original origin. X, Y and mode completion initializes the 0x44dfb0 handoff fields. The subsequent signed-dword transition can override that handler with normal 0x44c860 while retaining initialized fields. Context supplies resolved old descriptor dimensions and original screen override state. Rotation trace remains shared.

verify_block_orbit.py executes the complete original without routine hooks across 1,024 whole-object cases, including 682 linked resources and 64 focused handoff/override fixtures. It initializes original measurement tables and populates original VF rotation tables in oracle memory. Whole object state and shared rotation trace match. Evidence: block-orbit-verification.json. Native frame descriptors are supplied in resolved order; full actor ownership, the following rotating phase, renderer and playable application remain unfinished.

## Second rotating block phase (0x44dfb0)

Recovered the complete second phase alongside 0x44de20. It updates effect stage, vertical origin, rotation radius and measured position, preserving the original unsigned division for scale. Vertical or dword transition completion restores 0x44c860. Both phases match 2,048 whole original objects, including 1,365 linked-resource cases and 64 focused handoffs; rotation globals also match. Evidence: block-orbit-verification.json. Actor lifecycle and playable application integration remain unfinished.

## Consecutive rotating-effect phases

verify_orbit_chain.py compares 256 complete 0x44de20 -> 0x44dfb0 -> 0x44c860 sequences against the executable without routine hooks. All 2,894 whole-object updates and shared rotation globals match. Descriptor binding runs on every frame with valid 24-by-24 descriptors. Timer periods, starting positions, radius targets and intervals are test fixtures, not recovered gameplay initialization. Evidence: orbit-chain-verification.json. Full actor construction and application integration remain incomplete.

## Fade-to-slide handlers (0x44e250/0x44e2d0)

block_slide.c recovers the existing-target amount/effect transitions and their handoff to horizontal sliding. The slide recomputes effect and step from the absolute word distance, preserving signed narrowing and unsigned divisions. Its completed horizontal transition restores 0x44c860. Both complete handlers match 2,048 whole original objects with 1,365 linked resources, without routine hooks. Evidence: block-slide-verification.json. Actor initialization and playable application integration remain incomplete.

## Collapse phases (0x44e380/0x44e410)

block_collapse.c recovers effect 50/step20 followed by effect -200/step10, with mode 0/step1 in both phases. In the first phase, effect completion selects 0x44e410 but later mode completion overrides it with 0x44c860. The second phase sets fields 93/94/95 to 1/0/0 even before a timer tick; only mode completion ends it. Complete objects match 2,048 original executions, including 1,365 linked-resource cases. Evidence: block-collapse-verification.json. Actor construction and playable application integration remain incomplete.

## Amount visibility handlers (0x44e4a0/0x44e510)

block_visibility.c recovers amount 100/step2 and amount 0/step8. Both set field93 before testing the timer; 0x44e510 also clears fields94/95. Completion restores 0x44c860, and only 0x44e4a0 clears field93 on completion. Complete objects match 2,048 original executions including 1,365 linked resources without routine hooks. Evidence: block-visibility-verification.json. Actor initialization and playable application integration remain unfinished.

## Three swell phases (0x44e590/0x44e600/0x44e670)

block_swell.c recovers mode16/step1, effect50/step5, then effect0/step10, with handoffs to the next phase and finally 0x44c860. The first phase writes amount100 and field93=0 on every frame before the timer test; subsequent phases preserve them. All 3,072 whole original objects match without routine hooks, including 2,048 linked-resource cases. Evidence: block-swell-verification.json. Full actor creation and playable integration remain incomplete.

## Animation acceleration (0x44e6e0)

block_accelerate.c first advances animation using the previous period, then divides that period as signed by12. Quotients above1 decrease by primary cycles with signed wrapping and clamp to1, writing 12 times the result as the new period. Quotients at or below1 leave the actual period unchanged. Effect50/step2 completion restores 0x44c860 only when the local speed is1. All 2,048 complete original objects match including 1,365 linked-resource cases and periods0..256. Evidence: block-accelerate-verification.json. Full actor construction and playable application integration remain incomplete.

## Mode and amount handlers (0x44e790/0x44e800)

block_mode_amount.c recovers mode0/step1 completion to normal, and amount100/step6 followed by mode16/step1 with both-completion required before 0x44e890. No flags change. All 2,048 complete original objects match including 1,365 linked-resource cases without routine hooks. Evidence: block-mode-amount-verification.json. The next handler 0x44e890 and full actor/application integration remain unfinished.

## Animation period target (0x44e890)

block_period.c advances animation before evaluating the signed period/12 quotient. A quotient below the signed target at58 adds primary cycles with wrapping and signed clamping, then writes12 times the result. At or above target, it completes without rewriting the animation period. Completion restores0x44c860. All2,048 whole original objects match, including1,365 linked-resource cases and arbitrary signed targets. Evidence: block-period-verification.json. Full actor creation and playable application integration remain unfinished.

## Centered mode and movement (0x44e920/0x44e9f0)

block_orbit.c now dispatches these two additional phases. The first transitions existing mode targets, derives effect as4*(mode-16), and selects0x44e9f0 on arrival. Both center using logical unsigned(24-measurement)/2. The second moves origin words through existing x/y transitions, recenters, and restores0x44c860 with mode target16/step1 only when both arrive. No flags change. All2,048 whole original objects match including1,365 linked resources without hooks. Mode targets0..16 and nonnegative steps are valid-dimension fixtures; invalid resulting modes are rejected transactionally. Evidence: block-centered-verification.json. Full actor/application integration remains incomplete.

## Centered completion (0x44eaf0)

Recovered the existing-target mode transition, recentering and effect4*(mode-16). Mode completion restores0x44c860, clears field93, sets amount50 and field95=1; measurement and effect derivation still run afterward. All2,048 whole original objects match including1,365 linked resources with valid mode targets0..16/nonnegative step fixtures. Evidence: block-centered-finish-verification.json. Full actor and playable application integration remain unfinished.

## Dword-to-origin travel (0x44ebe0/0x44ec40)

block_travel.c recovers existing dword transition completion to0x44ec40, then x/y transitions starting from stored origin words. Both displayed and stored coordinates update; both axes must finish to restore0x44c860. No flags or mode initialization changes. All2,048 whole original objects match including1,365 linked resources without routine hooks. Evidence: block-travel-verification.json. Full actor creation and playable application integration remain unfinished.

## Secondary rotation-step transitions

Extended executable comparison of word_transition.c to 0x4ad5e0 (current2a, target30, step32) and 0x4ad630 (current3a, target40, step42). These noncontiguous fields use exactly the existing signed arithmetic, 32-bit wrapping, word narrowing and completion check. All 5,120 complete-object/return comparisons pass across the five routines, including full-width cycle counts and signed extremes. Evidence: word-transition-verification.json. Traced 0x44ece0: animation first, secondary timer dc/e0 then primary bc/c0, rotation-step transition and angle advance using secondary cycles, fade using primary cycles, measurement and circular placement each frame. Enclosing effect integration remains unfinished; the helper proof does not verify that handler.

## Dual-timer rotating fade (0x44ece0)

block_spin.c recovers the complete effect. The secondary timer dc/e0 changes radius2a toward30 using step32; radius is distinct from rotation speed28. This corrects the earlier description of4ad5e0 as a rotation-step transition. Radius transitions precede angle advancement; primary timerbc/c0 independently fades amount toward0/step8. Both transitions execute even with zero cycles. Completion requires both arrivals, then scale, measurement, circular coordinates and frame binding still execute. All2,048 whole original objects and rotation globals match, including1,365 linked-resource cases; radii/targets0..100 are valid-mode fixtures. Evidence: block-spin-verification.json. Full actor creation and playable application integration remain unfinished.

## Companion rotating reveal (0x44ee20)

Extended block_spin.c to the original reveal variant. It shares independent timers, radius transition, angle, scale and placement, but targets amount100/step8 and clears field93 only after both radius and amount complete. All4,096 whole original objects and shared rotation globals match, including2,730 linked-resource cases and64 explicit completions with neither timer due. Evidence: block-spin-verification.json. This confirms transitions run even with zero cycles; no full actor/application runtime is claimed.

## Additional fade and swell dispatch

Added original0x44ef60/0x44efd0 to block_visibility.c: amount0/100 at step8, field93=1 before every tick, other flags preserved and completion to0x44c860. Four fade handlers match4,096 whole original objects including2,730 linked resources. Added0x44f040/0x44f0b0 to block_swell.c: effect50/step10 then0/step20, preserving mode/amount/flags, ending at0x44c860. Five swell handlers match5,120 whole original objects including3,413 linked resources. Evidence: block-visibility-verification.json and block-swell-verification.json. Full actor/application runtime remains unfinished.

## Existing-step effect handlers

block_effect.c recovers0x44f120/180/1e0/240/2b0. All preserve effect step4c. First pair sets targets100/-100 before transitions and alternates handlers;1e0 sets0 and completes to normal. Second pair clears field94 every frame, uses existing targets, and on arrival alternates handlers while setting the next target0/-100. All5,120 whole original objects match, including3,413 linked-resource cases without hooks. Evidence: block-effect-verification.json. Full actor creation and playable application integration remain unfinished.

## Effect stage completion (0x44f320)

Extended block_effect.c with target0 using existing step; arrival sets stage52=13 and restores0x44c860. Six complete handlers now match6,144 whole original objects including4,096 linked resources. Evidence: block-effect-verification.json. Also traced upcoming0x44f390/0x44f3e0: field94 cleared before ticks; forward/backward signed cyclic dword80 using step88, modulus255 and separate iteration/wrap globals. These cyclic handlers remain unimplemented. Full actor/application integration remains unfinished.

## Forward/backward cyclic effects (0x44f390/0x44f3e0)

block_cycle.c recovers each per-cycle wrapped32-bit add/subtract of current80 by step88, with original signed comparisons and signed remainder255 after boundary adjustment. Separate caller-owned traces represent globals5bb5cc/5bb5d0 and5bb5d4/5bb5d8. Field94 clears every frame; traces reset only when primary timer is due, including zero-cycle calls. All2,048 complete original objects and trace globals match including1,365 linked resources and arbitrary signed current/step. Cycle counts are bounded test fixtures; code preserves the original per-cycle loop. Evidence: block-cycle-verification.json. Full actor/application integration remains unfinished.

## Cyclic effect return (0x44f430)

Extended block_cycle.c with the original return handler using dword transition4acc70 to target0 at84, preserving existing step88. Arrival clears current80 and field8c and restores0x44c860. It preserves field94 and both cyclic traces, unlike the loop handlers. All3,072 complete original objects match including2,048 linked resources; existing forward/backward trace checks still pass. Evidence: block-cycle-verification.json. Full actor construction and playable application integration remain unfinished.

## Additional existing-step effect groups

Recovered0x44f4a0/500/560 and0x44f5d0/630/690. Each pair alternates100/-100 targets and its own handler addresses, preserving the step. The third handler sets target0 and stage13 on completion to normal. Distinct addresses stay distinct in runtime dispatch. All12 handlers match12,288 whole original objects including8,192 linked resources without hooks. Evidence: block-effect-verification.json. Full actor/application integration remains unfinished.

## Combined fade/distortion and cleanup phases

Added0x44f7e0 (amount0/step8,effect-100/step8) and0x44f880 (amount100/step4,effect100/step4), both requiring paired completion. Both set flags93=1/95=3 every frame; reveal completion changes95=1 and handler44f920. Combined proof4,096 whole objects passes. Added44f700(effect100/step10)->44f770(effect0/step10)->normal, plus44f920(effect0/step20)->normal. Eight swell handlers match8,192 whole objects. Evidence: block-combined-verification.json and block-swell-verification.json. Full actor/application integration remains unfinished.

## Alternating mode handlers (0x44f990/0x44fa00)

Extended block_mode_amount.c with mode16/step1 and mode0/step1 alternating original handler addresses. They preserve amount fields and all flags. All4,096 complete original objects match across four handlers including2,730 linked resources without hooks. Evidence: block-mode-amount-verification.json. Subsequent0x44fa70/0x44faa0/0x44fad0/0x44fb40 access player objects; their integration remains unfinished alongside full actor/application runtime.

## Player-linked object lookup (0x4b5eb0)

Added vertrix_object_list_find for first-match field0 identity lookup, preserving live ordered reads and stopping at the first duplicate ID. Missing/empty lists return handle0. Native resolver failures and invalid storage preserve the result. All2,048 original calls match including1,342 hits; callback read order and original/native list storage remain unchanged. Evidence: object-find-verification.json. This enables forthcoming player-linked handlers; the complex resource selection4b58a0 and enclosing player integration remain unfinished.

## Player-linked numeric text (0x4b58a0)

number_text.c recovers unsigned decimal selection: mode184=1 pads with zeros to width188; other modes print ordinary decimal. When value180=0 and show_zero190=0, text becomes empty even after padding. Caller-owned output rejects insufficient capacity transactionally. Original control flow matches1,024 cases with explicit hooks for string services and final4b65d0 font binding; this proof does not verify those services or rendering. Evidence: number-text-verification.json. Earlier sprite-resource description of4b58a0 is corrected: it is a numeric text setter. Font binding and full player/application integration remain unfinished.

## Player-linked numeric handlers (0x44fa70/0x44faa0)

number_player.c integrates ordered object-ID lookup and numeric formatting.0x44fa70 reads the first matching object field180;0x44faa0 reads indexed player field17c, marks local refresh120 when index148=-1 or shared refresh5bb714 otherwise, then clears handler154. All2,048 whole original objects and shared refresh arrays match with actual lookup/refresh routines; numeric/font setter4b58a0 is hooked to capture values and update180, and separately verified numeric formatting is native. Evidence: number-player-verification.json. Font binding/rendering and full player/application runtime remain unfinished.

## Original font positioning (0x440990)

text_layout.c recovers signed-word bounds/dimensions, horizontal offset(right-left+2-width)/2 and vertical offset(bottom-top+1-height)/2 truncated toward zero and narrowed before testing negativity. Oversized text can return before origins are added; reversed/equal bounds skip their centering. All4,096 original executions match whole output buffers without hooks. Evidence: text-layout-verification.json. Traced4b65d0: copy text/style/bounds, call4408e0 for font measurement/layout, store x/y and fallback width/height. Font measurement440610, VF font binding and playable application integration remain unfinished.

## Font measurement (0x440610)

font_measure.c recovers per-glyph original resource measurement, one trailing pixel per recognized glyph/space, unsigned maximum height, missing-glyph skipping and empty-text height from space fallback dimensions. Caller supplies bounded NUL text and glyph dimensions; no glyph map is invented. All1,024 original control-flow executions and actual4b14c0 measurements match; glyph lookup/allocation/constructor/attach/destructor and empty-string comparison are explicit service hooks. Evidence: font-measure-verification.json. VF font mapping, binding/rendering and full application runtime remain unfinished.

## Font glyph lookup (0x43f420/0x48ac00)

font_map.c recovers256 signed-word glyph indices plus space dimensions. Missing index-1 returns resource0 and updates the selected index; nonnegative indices select shared resource handles. Invalid native indices preserve outputs. All8,192 original lookups pass across20 slots and every byte code, including4,063 missing entries. Fixtures supply maps/resources; this does not prove actual font initialization. Traced initializer43fc50..44046b and20 map blocks of stride20c: map0 uses A-Z indices48..73 and digits74..83; later maps use resource-clone helpers requiring further recovery. Evidence: font-map-verification.json. Original map initialization, VF glyph loading and playable integration remain unfinished.

### Original font-map initialization

Recovered 0x43fc50 initializes 19 maps, preserving unspecified glyphs. Letters, digits, punctuation and special GO/VS glyphs now match the original. Space dimensions for slots7–9 use original resource indices6/9 with even rounding and unsigned wrap. The helpers at0x43f480 and subsequent punctuation helpers write map indices; earlier resource-clone descriptions were inaccurate. Verification compared 5,120 full maps against the executable, hooking only resource lookup0x4877f0. VF font-resource construction and text rendering are still unfinished. Wii compilation and formatting checks passed.

## Font resource loading plan (0x43eab0)

Recorded39 loading/transform calls producing548 resource slots. Actual original control flow verifies destination indices, source indices, cell dimensions, counts and transform arguments with explicit service hooks. Sheet identifiers22–53 correspond to the original PictureFileName.ini rows under image/systeme. 0x43f200 divides sheet width/height by cell dimensions plus one, begins each cell at coordinate1, and advances through row-major cells with one-pixel gutters. Resource cropping and transform pixels remain to be recovered and verified. Evidence: font-load-plan.json and tools/recover_font_load_plan.py.

## Font outline pixels (0x483400)

font_outline.c implements the EBX=1 transform used by43f190: copy RGB to output with alpha0, identify source alpha edges against four neighbors (eight only when diagonal=1), mark output edge alpha255, then clear those alpha bytes in the source. Repeated passes accumulate removed edge pixels. Boundaries are always edges; transparent RGB is preserved. 1,024 original executions compare154,478 pixels across both modified source and output. Only resource clone/allocation483110 is hooked. Native invalid capacity preserves both buffers. The EBX=0 ownership branch, descriptor allocation and complete VF font binding remain separate. Wii compilation and formatting checks passed. Evidence: font-outline-verification.json.

## Font stencil pixels (0x4831b0)

font_stencil.c recovers alpha-only overlap counts, zero-transparent background, grayscale saturation255 and optional clearing of center alpha when solid=0. Output dimensions add twice floor(stencil size/2); original descriptor origins add the same half sizes with32-bit wrap. 1,024 actual executions compare191,833 output pixels, unmodified source and descriptor geometry; only zeroed resource allocation483060 is hooked. Dense20x20 fixtures verify counts above255 and resume the same oracle state past its standard instruction budget. Native pixel buffers reject invalid capacity before mutation. Original descriptor allocation and complete VF font loading remain unfinished. Wii compilation and formatting checks passed. Evidence: font-stencil-verification.json.

## Font sheet cell traversal (0x43f200)

font_cell.c reproduces row-major bordered cell geometry: columns=sheetWidth/(cellWidth+1), rows=sheetHeight/(cellHeight+1), x/y begin at1 and advance by respective cell dimension+1. The caller stack progress count does not constrain slicing. 256 actual original control-flow executions yield4,220 matching crop rectangles, counts and order, with empty grids, partial borders and arbitrary progress counts. File/string/image/crop/color/destruction services are explicit hooks; this proves geometry rather than crop pixels or VF loading. Native invalid dimensions/index preserve output. Wii compilation and formatting checks passed. Evidence: font-cell-verification.json. Original crop allocator482f80 constructs40-byte descriptors and calls47ce10 for copying, requiring further integration.

## Font crop pixels (0x482f80/0x47ce10)

image_crop.c allocates native-owned glyph images and copies four-byte pixels without alpha processing. All1,024 original47ce10 regular row-copy executions match75,369 pixels, including transparent RGB, with source unchanged and no hooks. Native rectangles must be narrower than the sheet, matching bordered font use; full-width fast path remains outside the implementation/proof. Invalid crop/storage/output rejects before mutation. Original482f80 metadata allocation and full VF font resource integration remain separate. Wii compilation and formatting checks passed. Evidence: font-crop-verification.json.

## VF font-sheet transparency (0x4799f0/0x43f200)

image_key.c compares complete little-endian32-bit pixels to key, including incoming alpha; matches clear alpha, others set255, RGB remains unchanged. Direct VF BMP helper takes top-left pixel as key, matching missing-mask branch in43f200. 1,024 random original executions pass without hooks. All29 original VF font BMP sheets load and196,664 pixels match original4799f0 processing; native-owned buffers remain valid after archive close. Original mask-present branch/configuration parser and complete glyph-resource binding/rendering remain separate. Wii compilation and formatting checks passed. Evidence: image-key-verification.json.

## VF base font glyph assembly

font_sheet.c composes BMP loading, configured mask when present or top-left key fallback, original bordered cell traversal and native-owned crop allocation. All29 original font BMP sheets produce466 base glyphs, matching170,904 pixels and all dimensions/order against actual4799f0 and47ce10 without hooks. After archive close all owned glyph buffers remain valid; missing artwork preserves empty output and occupied destinations are rejected. The mask-present branch is implemented via previously recovered image masking but not exercised by original font fixtures. Final color ordering483ed0,82 derived glyphs, configured filename parsing, complete resource bank and text rendering remain unfinished. Wii compilation and formatting checks passed. Evidence: font-sheet-verification.json.

## Owned font transform images

font_image.c connects recovered4831b0 stencil and483400 outline kernels to native-owned VertrixImage buffers. Explicit LE byte translation avoids host/Wii endian casts. Source/output dimensions and allocation are checked before transformation; outline publishes source mutation only after all allocations succeed. 1,024 adapter cases compare118,832 pixels to separately oracle-verified kernels and verify source mutation/preservation, occupied-output rejection and freeing. This is integration evidence rather than new x86 proof. Complete82 derived glyph bank construction, original descriptor origins and font rendering remain unfinished. Wii compilation and formatting checks passed. Evidence: font-image-verification.json.

## Original VF font stencils

45e119..45e145 reads static sprite index513c5d=17 from filename array533650 under sprite prefix4fc188, then loads546538. Original VF SpriteFileName.ini row17 is Circle.spr. Font43f110 and map initializer resolve frames6 and9. font_stencils.c now owns processed VF frames6(15x15) and9(21x21). Independent sequential SPR parsing verifies pixels, binary alpha, all metadata, two RGB orders, occupied-output rejection, invalid masks and lifetime after archive close. Native code uses the verified original filename; alternate sprite filename configurations are not resolved here. Original resource graph loading, complete82 derived glyph bank and rendering remain unfinished. Wii compilation and formatting checks passed. Evidence: font-stencils-verification.json.

## Complete original VF font glyph bank

font_bank.c implements39 original43eab0 operations and owns548 images with original descriptor origins:466 base glyphs plus82 derived glyphs. Base images use original color-order processing; stencil transforms use Circle.spr frames6/9, and final outlines run in original538,528,518 order while mutating source84..93. The complete original43eab0/43f110/43f190/4831b0/483400 execution matches310,592 final pixels and all dimensions/origins. Hooks provide independently decoded VF base sheets/stencils, allocation/clone/progress and skip separately verified map initialization. Buffer lifetime after archive close, occupied output and invalid masks are checked. OriginalRGBA order is verified. Native filenames follow verified original tables; alternate filename configurations, font-map binding, renderer and playable application remain unfinished. Wii compilation and formatting checks passed. Evidence: font-bank-verification.json.

## Real VF glyph mapping and measurement

font_map_construct reproduces48ab10: clear space dimensions, set glyph indices0..254 to-1, preserve glyph255. All1,024 random original constructor objects match. font_binding.c borrows actual font-bank images through signed map indices and composes440610 measurement with low-word descriptor/space dimensions. All19 original initialized maps match;1,216 text measurements against actual440610,43f420/48ac00 and4b14c0 match, including every nonzero byte code and scaling/screen flags. Real VF glyphs remain valid after archive close. Resource allocation/constructor/attach/destructor/empty comparison and stencil lookup are explicit hooks. Native invalid text preserves outputs. Rendering and playable application integration remain unfinished. Wii compilation and formatting checks passed. Evidence: font-binding-verification.json.

## Unscaled text draw traversal (0x440490)

font_run.c produces original descriptor indices and signed-word draw anchors. Spaces add full32-bit font space width then increment; glyph widths add only to low16 bits before full32-bit increment. Missing glyphs neither draw nor advance. Complete text/resources/capacity validation precedes output writes. All1,024 original440490 executions and actual43f420/48ac00 lookups match17,612 placements, final positions and native glyph ordering; service hooks cover allocation/constructor/attach/virtual draw/destructor. Original per-glyph flags8e=0,8f=1 are asserted before hooked virtual draw. Rendering pixels, descriptor-origin positioning and full application integration remain unfinished. Wii compilation and formatting checks passed. Evidence: font-run-verification.json.

## Glyph origin positioning and pixel drawing

font_draw.c composes font-bank image buffers, original low-word anchor-minus-origin positioning, full-target clipping and binary-alpha rendering for unscaled fonts in a zero-origin viewport. 2,048 actual4ae6fa..4ae747 origin executions match without hooks, including full32-bit origins narrowed to words. 1,024 independently checked drawing fixtures verify alpha0/1/128/255, varied source/destination RGB, clipping and unmodified source. Pixel adapter delegates previously oracle-verified sprite clipping/binary rendering; these new integration fixtures do not prove complete original sprite preparation or nonzero viewport offsets. Text run composition and playable application integration remain unfinished. Wii compilation and formatting checks passed. Evidence: font-draw-verification.json.

## Complete unscaled VF text composition

vertrix_font_draw_text connects440490 placement traversal with original descriptor origins and binary-alpha glyph rendering in a zero-origin32-bit viewport. It validates bounded text, target storage and all glyph source rectangles before drawing; all allocations precede pixel writes. 304 complete VF text draws across19 styles independently match pixels, dimensions/order/position arithmetic, row padding and clipping. Invalid text or late invalid map entries preserve target and output counters. This integration uses separately oracle-verified components; whole original virtual sprite preparation, scaled text, nonzero viewport offsets and application integration remain outside this proof. Diagnostic preview original-vf-fonts.png renders all19 styles directly from original VF glyphs. Wii compilation and formatting checks passed. Evidence: font-text-verification.json.

## Styled text traversal (0x440a20)

vertrix_font_run_scaled reproduces measured glyph/space widths and signed-word advancement. Effective scale uses parent mode44 and screen override91. Missing glyphs skip, recognized glyphs retain original positions and order even at measured width0. 1,024 actual440a20 executions with actual43f420/48ac00 and4b14c0 match17,330 placements and final signed-word positions across all scale modes, screen overrides, full32-bit source dimensions and spaces. Original per-child mode/override and8e/8f flags are checked; allocation/constructor/attach/virtual draw/destructor are hooks. Native scaled pixel drawing and full transfer of parent effects/clipping/cyclic style fields remain unfinished. Wii compilation and formatting checks passed. Evidence: font-scaled-run-verification.json.

## Styled glyph parent transfer (0x440b93..0x440c46)

font_style.c copies clip mode8e, amount4e, effect48, stage52, flags94/95/93, mode44, screen override91, cycle80/cycle flag8c and four clip words a8..ae while forcing binary8f=1. All2,048 actual original fragment executions match16 fields and untouched child bytes without hooks. Parent stays unchanged; in-place and invalid-input behavior are checked. Traced scaled sprite preparation4aed56..4aee28: original lookup-table measured width/height scale signed descriptor anchors by measured/source dimensions with signed division and low-word narrowing before returning to4ae6da; existing resource-bounds recovery follows this arithmetic. Styled pixel composition and application integration remain unfinished. Wii compilation and formatting checks passed. Evidence: font-style-verification.json.

## Scaled font origin and binary pixels

font_draw.c now measures scaled glyph bounds, scales descriptor anchors with signed measured/source division and low-word narrowing, then composes binary sampled drawing for modes0..16 in a zero-origin viewport. Mode0/zero measured dimensions skip pixels, mode16 uses unscaled binary copy. All2,048 actual4aed56..4aee28 fragment executions match dimensions/anchors without hooks. 512 image integration cases match pixels using actual original4b15e0 bounds and4b9050 sample tables across all scales, clipping and varied nonzero alpha. Previously recovered renderer components provide native sampling. Parent effects/custom clips, complete styled text drawing and playable application remain unfinished. Wii compilation and formatting checks passed. Evidence: font-scaled-draw-verification.json.

## Complete basic scaled VF text composition

`vertrix_font_draw_text_scaled` connects the recovered 0x440a20 traversal with scaled glyph bounds and binary sampling. It validates text, target storage and every glyph before writing pixels. All 969 complete text draws across 19 original VF fonts, 17 scale modes and three override configurations match independent pixel expectations derived from original measurement, bounds and sampling tables. Checks include spacing, descriptor origins, clipping, row padding and final positions; invalid bounded text preserves pixels and output counters. The component routines have separate original execution proofs. Wii compilation and formatting checks passed. Evidence: font-scaled-text-verification.json. Parent effects, custom clipping, viewport offsets and playable application integration remain unfinished.

## Complete recovered library build coverage

The previous manually maintained Makefile list omitted the font-bank pipeline and image crop/key helpers. Default builds now include every portable C module, with `wii_*.c` adapters retaining their separate libogc targets. `tools/verify_wii_build.py --build-dir /path/to/scratch/wii-build` checks archive members against the actual source files and combines the entire archive into a PowerPC relocatable object. All 86 modules compile and link without unresolved recovered dependencies; only standard C/compiler runtime symbols remain. Evidence: wii-build-verification.json. This corrects build coverage; it does not establish a bootable or playable application or hardware behavior.

## Additional player display updates (0x44fc00/0x44fc30)

Extended number_player.c to preserve these two original handlers. 0x44fc00 looks up the first matching object ID and copies its field0x180 without clearing the handler. 0x44fc30 reads indexed player field0x178, formats it, performs the original local/shared refresh and clears the handler. The caller supplies the player field selected by the handler; existing 0x44faa0 still uses field0x17c. All 4,096 whole-object comparisons across four numeric handlers pass with actual original list lookup and refresh routines. The numeric/font setter is intercepted to capture its argument and update field0x180; numeric formatting has separate original evidence. Full player scheduling and text-object binding remain unfinished. Evidence: number-player-verification.json. Wii compilation, recovered dependency linking and formatting checks pass.

## Player-value display transition (0x44fad0/0x44fb40/0x44fbb0)

number_transition.c preserves all three phases. The waiting phase clears source field0x134, compares the linked numeric value with indexed player field0x17c, and on a mismatch sets source1/effect-100, resets the timer and enters44fb40. Timed phases consume cycles and transition effect toward50 then-100 with step2. First arrival schedules44faa0 on the linked numeric object before entering44fbb0; second arrival returns to44fad0. The caller supplies the first matching live numeric object, whose list identity is field0 and player index is field4. All 6,144 complete original executions without hooks match both whole objects, including3,102 phase changes, zero periods, timer overflow and signed effect extremes. Evidence: number-transition-verification.json. All87 portable modules compile and combine for Wii without unresolved recovered dependencies; formatting passes. Full player scheduling and playable application remain unfinished.

## Field0x178 display transition and configuration branch

The configured entry point additionally preserves44fc60/44fcf0/44fd60 and the repeating44fdb0/44fe30 pair. Field0x178 supplies these comparisons. Config532bc8 equal1 and config532b34 equal the player value selects44fe30 directly from44fc60. The ordinary path uses step2 and schedules44fc30; the repeating pair uses step4 and schedules44fc30 only when the linked numeric value differs at arrival. All16,384 complete original executions across eight handlers match both whole objects without hooks. Fixtures keep object list ID independent of player index and put different values in player fields178/17c. Timer overflow, zero periods, configuration selection and source/handler changes are covered. Evidence: number-transition-verification.json. Wii compilation, internal linking and formatting pass; complete player scheduling remains unfinished.

## Player-state indicator (0x44fe80/0x44fed0/0x44ff30/0x44ff60)

player_indicator.c preserves the four phases. Waiting copies indexed player field18c into object64 and clears58; exact state3 resets the primary timer and enters44fed0. Primary expiry resets both timers, sets58=1/64=0, requests43c0e0 with original4f81a0 and enters44ff30. Secondary expiry resets its counter and enters44ff60, which waits until state differs from3 before returning to44fe80. No due phase consumes cycles: the original resets counters to zero. The native output reports the audio request for caller routing. All8,192 whole-object comparisons pass with actual43ba70 and timer helpers; only43c0e0 audio is intercepted, with1,548 matching requests. Evidence: player-indicator-verification.json. All88 portable modules compile and combine for Wii; formatting passes. Player/audio/application integration and playable hardware verification remain unfinished.

## Linked threshold indicator (0x44ff90..0x450100)

linked_indicator.c preserves44ff90/44fff0/450040/4500b0/450100. A present linked object's signed field64 reaching signed threshold58 starts reveal: stage13, timer reset, amount0/target100/step3/source1. Timer cycles advance amount through4ad580. Revealed state fades with step1 when linked58 equals1, otherwise step3 when signed linked64 falls below threshold. Completion clears source134 and waits until linked58 equals0 before returning to the initial handler. Missing linked objects leave waiting phases unchanged. All10,240 complete original executions without hooks match whole objects, including3,360 handler changes and unchanged linked storage. Original lookup, timers and byte-transition instructions execute. Evidence: linked-indicator-verification.json. All89 portable modules compile/link for Wii and formatting passes. Full actor/player/application scheduling remains unfinished.

## Linked repeated burst (0x450130..0x450300)

linked_burst.c preserves450130/4501a0/450200/450270/450300. Linked field58 equal1 starts three repetitions with source1/effect-40/target0 and step2+shared RNG modulo3. Arrival sets dword70=0/74=1/78=1 and enters the timed dword transition. Its arrival sets target-100, scales the existing signed step by5/2 with truncation toward zero and low-word narrowing, and resets effect0. Next arrival decrements repetitions with wrapping; nonzero repeats draw the next random speed without resetting the timer. Zero clears source and waits for linked58 equal0. All10,240 complete original executions without hooks match whole effect state, unchanged linked storage and RNG cursor, including3,104 handler changes and1,107 random draws. These fixtures do not cross RNG refill; separate RNG verification covers refill. Evidence: linked-burst-verification.json. All90 portable modules compile/link for Wii; formatting passes. Full runtime/player/application integration remains unfinished.

## Animated finish effects (0x450330/0x4503b0/0x450450)

block_finish_effect.c preserves forward animation, primary timer and descriptor binding for all three handlers. 450330 forces93=0/amount50/95=3, transitions effect toward200 with step8, then sets93=1/amount100 and enters4503b0. That phase forces93=1/95=3 and requires amount0/step4 plus effect0/step8 completion before clearing handler and setting byte15d=2. 450450 uses amount0/step2 plus effect0/step1; paired arrival clears handler and sets93=1/amount0. All6,144 whole original executions without hooks match, including4,096 one/two-level linked resource cases, unchanged unrelated fields and invalid native capacity preservation. Evidence: block-finish-effect-verification.json. All91 portable modules compile/link for Wii; formatting passes. Complete actor ownership, player/application scheduling and playable hardware verification remain unfinished.

## Non-animating finish chain (0x4504e0/0x450550/0x4505c0)

Extended block_finish_effect.c with three original handlers that leave frame and animation timer unchanged while binding the current descriptor. Primary timer cycles drive effect100/step3, then-100/step4, then-200/step10. First arrival sets95=4/amount50; final arrival clears handler and sets byte15d=2. Expanded verification matches12,288 whole original objects across six handlers, including8,192 linked resource cases, without routine hooks. Evidence: block-finish-effect-verification.json. Wii compilation, internal linking and formatting pass. Full actor/player/application scheduling remains unfinished.

## Alternate finish chain (0x450630/0x4506a0)

Added the distinct two-phase chain: effect100/step3 then effect0/step4. First arrival sets95=4/amount50 and selects4506a0; final arrival clears handler and sets state15d=2. Animation timer/frame remain unchanged; current descriptor is bound each update. The eight-handler verifier now matches16,384 whole original objects, including10,922 linked resources, without hooks. Evidence: block-finish-effect-verification.json. Wii compilation, internal linking and formatting pass. Full application and object lifecycle integration remain unfinished.

## Animation-only handler dispatch (0x450710/0x450730)

block_update.c now accepts original animation-only handler identities:44c860/450710 advance forward-loop animation;450730 advances reverse-loop animation. Descriptor binding follows animation in every case, including linked resource indices. The existing normal-block entry point retains44c860 behavior. All3,072 whole original executions across three handlers match without hooks, including2,048 linked resource cases. Evidence: block-update-verification.json. The16,384-case finish-handler regression also passes following this shared routine change. Wii compilation, internal linking and formatting pass; full actor/runtime/application integration remains unfinished.

## Player countdown and trigger (0x450750/0x4507e0)

player_indicator.c now preserves450750/4507e0. Waiting clears value58, selects target70 from player180 or zero when player3ac equals1, advances the secondary timer and decrements signed state64 once on expiry when it exceeds target. The timer resets rather than consuming elapsed cycles. Matching target with player3ac equal1 clears that flag, resets the primary timer and selects4507e0. Primary expiry resets its counter, sets58=1/64=12/70=12 and hands off to450830. All8,192 complete original executions without hooks match whole objects and player flag, including signed extremes and timer wrap. Evidence: player-countdown-verification.json. Wii compilation, internal linking and formatting pass;450830 and full player/application scheduling remain unfinished.

## Countdown return phase (0x450830)

The countdown now includes450830: advance primary timer, wait for unsigned expiry, reset the counter to zero and return to450750. Value/state/target and player flag stay unchanged during this phase. All12,288 complete original executions across all three countdown phases match whole objects and player flag without hooks. Evidence: player-countdown-verification.json. Wii compilation, internal linking and formatting pass. The countdown cycle is recovered; full player/application scheduling remains unfinished.

## Linked movement lifecycle instruction evidence (0x450860..0x4509d0)

`tools/recover_linked_movement.py` verifies the original executable hash and decodes complete bounded bodies for six handlers, checking every byte and final return. The resulting linked-movement-instructions.json records146 instructions and their original call dependencies. This is static evidence; native implementation and runtime verification are still required.

450860 resolves list54671c by object field4. A present linked object's signed field64 below the local signed threshold58 sets local Y16 from global word533d78, targetY18 from originA, stepY1a=1, source134=1, resets primary timer and selects4508c0. That phase consumes primary cycles through4acab0; arrival resets primary timer, sets field124=1, requests4adfe0 local/shared refresh and selects450920. Linked field58 equal1 then resets secondary timer and selects450960. Secondary expiry clears source134, requests refresh, selects4509a0 and resets the secondary counter. The next secondary expiry resets primary counter and selects4509d0. A present linked object's field58 equal0 clears field124 and returns to450860. Missing linked objects preserve waiting phases. Implementing this chain requires both timers, signed-word movement, original ordered lookup, source visibility and indexed refresh storage; none of these phase relationships should be replaced with guessed timing.

## Native linked movement lifecycle verification

linked_movement.c now implements all six documented phases, preserving signed comparisons, timer reset versus consumption, movement, source visibility, active124 and local/shared refresh. Caller resolves the first matching live linked object. All12,288 complete original executions without hooks match whole effect state, unchanged linked storage and shared refresh words, including5,574 handler changes. Evidence: linked-movement-verification.json. All92 portable modules compile and combine for Wii with no unresolved recovered dependencies; formatting passes. Full actor ownership, scheduler, rendering and playable application remain unfinished.

## Alternating linked display instruction evidence (0x450a10..0x450c70)

The recovery tool's `--chain alternating` captures complete bounded instruction bodies for six additional handlers in linked-alternating-instructions.json, with executable hash verification and full byte coverage. Native implementation and runtime proof remain pending.

450a10 resolves the linked object. If local7c equals1, it waits for linked58 equal1, binds resource546618/frame0, resolves its descriptor, resets the secondary timer and enters450b30. Other7c values wait for signed linked64 below signed local58, reset primary timer and initialize Y from533d78 toward originA with step1 before selecting450aa0. Movement arrival binds resource546634/frame0, resolves the descriptor, enables source134, initializes effect-40/target5/step4, resets primary timer and selects450b90. The secondary-timed450b30 enables source and initializes the same effect with step1 before selecting450b90. Effect arrival initializes70=0/74=1/78=1 and selects450bf0. Its timed dword-transition arrival initializes effect5/target-60, with step2 for7c equal1 and step1 otherwise, and selects450c70. Final effect arrival clears source134, stores wrapping `1 - field7c`, and returns to450a10. Resource bindings and distinct frame initialization are part of fidelity; they still require integration with real VF resources.

## Native alternating linked display verification

linked_alternating.c now implements all six phases using recovered resource attach/bind helpers. Switches reset animation counter/frame and retain period, resolve frame0, and publish the borrowed resource plus descriptor. All12,288 complete original executions without hooks match whole display state and unchanged linked storage, including5,706 handler changes and1,218 resource switches. Cases cover signed movement/effect arithmetic, dword delay, missing linked objects and wrapping phase values. Fixtures use direct resources; resource graph traversal has separate original proof. Evidence: linked-alternating-verification.json. All93 portable modules compile/link for Wii and formatting passes. Actual VF bindings, full object scheduling and playable application remain unfinished.

## Alternating display artwork source recovery (0x45e490)

The original builder creates one-frame resources546618 and546634 through487640. It resolves stencil546538 frame9 (the already recovered Circle.spr bank), then source5449fc frame selected by dword4fbfac (initialized34) twice, calling4831b0 with EBX solid1/0 respectively and publishing through487850. These are generated stencil images, not direct standalone VF entries. The complete builder instruction evidence is linked-alternating-artwork-instructions.json, reproduced with `--chain artwork`. Source bank5449fc is loaded at45dd48 through4873d0;45dd21..45dd3d selects its filename using runtime byte53bd09 into SpriteFileName.ini table533650 and prefix4fc188. The default/character-selected value of53bd09 remains unproven, so no filename is hardcoded here. Its subsequently configured frames and stencil descriptor origins must also be preserved in native asset integration. Existing stencil pixel and owned image adapters have separate original verification; this static trace does not prove the full artwork builder or filename selection.

## Sprite frame horizontal mirroring (0x483ce0)

image_mirror.c preserves the original four-byte pixel branch without changing descriptor origins, dimensions or channel order. All2,048 actual complete original executions without hooks match2,201,989 pixels; double mirroring restores original storage. Evidence: image-mirror-verification.json. Post-load bank mutation487790 clones a selected source frame into a destination, then4877d0 calls this mirror routine. Initialized default destination constants are1,10,12,29,25; corresponding sources after the first replacement are9,11,28,24. First source index comes from runtime dword5466c4. Consequently bank frame1 used by45e490 is replaced/mirrored before stencil creation and cannot be taken directly from VF unchanged. Source index and selector initialization remain under recovery. All94 portable modules compile/link for Wii and formatting passes. Full configured bank and playable application remain unfinished.

## Owned sprite descriptor clone (0x483110)

image_clone.c creates independently owned four-byte pixel storage and retains all serialized frame metadata and bank count. Actual original483110 copies the40-byte descriptor and full pixel buffer; only the calloc boundary is supplied. All2,048 cases match2,163,444 pixels and descriptor bytes apart from the independently allocated pointer, represented natively by image.rgba. Native ownership, unmodified source and occupied-output rejection are checked. Evidence: sprite-clone-verification.json. This supplies the clone primitive required by487790; complete destination replacement and configured bank composition remain unfinished. All95 portable modules compile/link for Wii and formatting passes.

## Owned mirrored sprite replacement composition

vertrix_sprite_replace_mirrored composes clone and horizontal mirror, releases the previous destination and publishes the replacement while preserving source pixels/metadata. Validation and allocations precede replacement; aliased source/destination storage is rejected. All2,048 occupied-destination integration fixtures match actual original483110 followed by483ce0, including descriptor bytes excluding the allocated pointer. Evidence: sprite-clone-verification.json. This proves composition of recovered leaves, not the full indexed487790/4877d0 bank operations or complete configured artwork loader. Wii compilation, internal linking and formatting pass; full application remains unfinished.

## Indexed direct-bank mirrored replacement verification

vertrix_sprite_bank_replace_mirrored now selects source/destination from direct owned frame storage with bounds checking. All2,048 actual complete487790 then4877d0 executions match bank selection, original source preservation, cloned descriptor/pixels and mirroring across2,072,433 pixels. Actual483110/483ce0 and4877f0 lookup execute. Allocation and old descriptor disposal are supplied boundaries; the disposal target and updated original pointer table are asserted. Native invalid destination indices preserve the bank. Evidence: sprite-clone-verification.json. Wii compilation, internal linking and formatting pass. Linked-bank mutation, configured sprite identity and complete artwork/application integration remain unfinished.

## Five UI bank substitutions (0x45dd52..0x45de10)

vertrix_sprite_bank_configure_ui composes all five original default clone/mirror substitutions: explicit runtime source5466c4 to frame1,9->10,11->12,28->29 and24->25. All replacements allocate before publication, preserving the bank on validation/allocation failure. Actual original fragment executes its real initialized configuration constants and helpers; only allocation and discarded descriptor disposal are supplied. All256 banks/8,960 frames match143,807 pixels and descriptor fields excluding allocated pointer, including first source indices that overlap later destinations. Invalid bank capacity preserves native storage. Evidence: ui-sprite-bank-verification.json. Wii compilation, internal linking and formatting pass. Runtime source index/filename selector initialization, full VF artwork composition and playable application remain unfinished.

## Direct VF configured UI sprite bank

ui_sprite_bank.c loads a caller-selected sprite bank directly from original VF, owns all processed frames and applies the separately original-verified five substitutions. Filename and first source index remain explicit runtime inputs. Ten configurations of actual damier.spr, each47 frames, independently match2,397,534 pixels and serialized metadata through sequential SPR parsing, binary alpha, both color orders and mirroring. All pixels remain valid after VF closure; occupied outputs and invalid first-source rejection preserve storage. Evidence: ui-sprite-vf-verification.json. This validates caller-selected artwork loading, not startup selection. All96 portable modules compile/link for Wii and formatting passes. Generated stencil resources, final selector integration and playable application remain unfinished.


The complete45e490 execution comparison in tools/verify_ui_artwork.py corrects the earlier argument interpretation:4877f0 uses EDX as the frame index and preserves EBX. Both generated artwork images now match original dimensions, origins and pixels; allocator and empty resource construction are supplied, while lookup, stencil and publication execute unchanged. The native VF wrapper retains owned images after archive closure. Runtime filename/first-source selection and full application integration remain unfinished. See docs/UI-ARTWORK.md.

Kernel0x491af0 now preserves source palette row while cycling destination hue. All256 complete original executions match, bringing supported pixel kernels to81 with20,736 comparisons. Formatting and124 portable PowerPC modules pass. Full rendering traversal and playable application remain unfinished. See RENDER-PIXEL.md and render-pixel-verification.json.

Recovered complete pixel kernels0x491be0 and0x491ce0: source hue/destination row and source hue/weighted row cycling. All512 comparisons match actual original bodies, plus601 signed cycling row cases across all mapped slots. Total83 supported kernels/21,248 standard cases;2,304 unsupported cases preserve output. All124 portable modules compile and combine for PowerPC; formatting passes. Full pixel traversal, actor drawing and playable application remain unfinished. See RENDER-PIXEL.md and render-pixel-verification.json.

Recovered0x491e10 weighted RGB cycling and0x491f70 weighted cycled palette indices. All512 full original kernel comparisons pass; the complete pixel suite now covers85 kernels/21,760 standard comparisons and1,202 signed weighted row cases. All1,792 unsupported rule cases preserve output. Formatting and124 portable PowerPC modules pass. Full pixel traversal, actor/application integration and playable Wii verification remain unfinished.

Recovered complete0x492120 cycled RGB then weighted destination blend. All256 complete original executions match, bringing the pixel suite to86 kernels/22,016 standard cases plus1,202 signed row cases. All1,536 unsupported cases preserve output. Formatting and124 portable PowerPC modules pass. Six32-bit table entries, full traversal, actor integration and playable application remain unfinished.

Recovered0x48d8c0 source-row fixed-index average:256 complete original comparisons pass. Total87 pixel kernels/22,272 standard cases plus1,202 signed row cases. The five remaining32-bit table entries are whole destination rectangle routines, requiring separate traversal recovery. All1,280 rejected pixel API cases preserve output. Formatting and124 portable PowerPC modules pass. Full traversal, actor/application integration and playable hardware execution remain unfinished.

Recovered destination rectangle0x492dc0 in render_rectangle.c. The native operation validates whole backing, uses explicit little-endian pixels and preserves forward traversal including overlapping rows. All4,096 complete original runs match35,745 modified pixels and unchanged surrounding bytes, with original final cursors/counters asserted. All4,096 invalid-bound cases preserve storage. Evidence: render-rectangle-verification.json. Formatting and125 portable PowerPC modules pass. Remaining rectangle operations, dispatch integration, actor drawing and playable application remain unfinished.

Recovered0x492b90 destination palette rectangle traversal. All4,096 complete original executions match whole backing and final cursor/counter behavior through random shifted tables and overlapping rows. Existing0x492dc0 comparisons also pass. Native palette conversion stages backing to preserve destination on invalid references. Formatting and125 portable PowerPC modules pass. Three rectangle effects and final dispatch/actor/application integration remain unfinished. See RENDER-RECTANGLE.md.

Recovered complete0x492cc0 fixed palette rectangle conversion. All4,096 original executions match, including valid cross-row indices up to255 and whole backing/final cursors/counters. Existing rectangle checks pass for a total12,288 original executions. Formatting and125 portable PowerPC modules pass. Rectangle effects0x492e40/0x492f90, final dispatch, actor drawing and playable Wii application remain unfinished. See RENDER-RECTANGLE.md and render-rectangle-verification.json.

Recovered final destination rectangle leaves0x492e40 and0x492f90, preserving index blending versus RGB blending order. All five rectangle modes match20,480 direct original executions; flag-selected rectangle integration matches another20,480 bodies. Unsupported selections and invalid backing preserve destination. Formatting and125 portable PowerPC modules pass. Full actor preparation, scene drawing and playable application/hardware verification remain unfinished. Evidence: RENDER-RECTANGLE.md and render-rectangle-verification.json.

Recovered binary row0x492280 integration with87 pixel kernels in render_row.c. All22,272 complete original rows match whole backing, source/destination cursors and remaining count, including alpha skipping and unaligned aliasing. All22,272 invalid-offset cases preserve storage. Single-pixel and signed-row checks also pass. Formatting and126 portable PowerPC modules pass. Full scaled/vertical traversal, actor preparation and playable Wii application remain unfinished. See RENDER-PIXEL.md and render-pixel-verification.json.

Recovered sampled binary row0x492550 over all87 pixel kernels. All22,272 complete original executions match whole backing and final source/destination/table cursors/count; all22,272 short-table cases preserve destination. Existing unscaled row and pixel tests pass. Formatting and126 portable PowerPC modules pass. Vertical traversal, actor drawing and playable Wii application remain unfinished. See RENDER-PIXEL.md and render-pixel-verification.json.

Recovered0x492710 opaque sampled row integration with87 pixel kernels. All22,272 complete original executions match; transparent sampled/unscaled rows and individual pixels remain passing. Formatting and126 portable PowerPC modules pass. Vertical traversal, actor preparation, scene drawing and playable Wii verification remain unfinished. See RENDER-PIXEL.md and render-pixel-verification.json.

Recovered0x4928f0 vertical integration with87 pixel kernels and sampled opaque/binary rows. All22,272 full original images match backing and final cursors/count; all22,272 short vertical table cases preserve output. Image path uses one staging allocation rather than allocating per row. Existing pixel/row checks pass; formatting and126 portable PowerPC modules pass. General transform traversal, actor preparation and playable Wii application remain unfinished. Evidence: RENDER-PIXEL.md and render-pixel-verification.json.

Recovered0x492400 opaque native row and0x492880 native image traversal over87 pixel effects. Each passes22,272 complete original comparisons, including aliasing and alpha behavior. Invalid native image source offsets preserve storage in22,272 cases. Existing sampled image/row and pixel comparisons pass. Formatting and126 portable PowerPC modules pass. Actor preparation, general transforms and playable Wii application remain unfinished. Evidence: RENDER-PIXEL.md and render-pixel-verification.json.

Recovered row/image traversal binding from original0x4af707..0x4af77d and tables0x4ff684/0x4ff6c4. All20,000 original selector-fragment executions match both address identifiers across four target formats and exact-byte traversal flags. All20,000 invalid target formats preserve native output. Address identifiers never serve as callable native pointers. Formatting and126 portable PowerPC modules pass. This bridges recovered selection to traversal identities; fast/alpha overrides, general transforms, actor preparation and playable application remain unfinished. Evidence: render-dispatch-verification.json.

Recovered original0x4af786..0x4af86d fast/alpha/prepared operation selection in render_dispatch.c. All1,536 original fragment executions match selected invocation address and whether preparation is called, across four formats, eight traversal indices, four groups, rules0/1/46/91 and alpha overrides0/1/ffffffff. Another1,536 invalid-rule cases preserve output. Preparation/drawing calls are supplied boundaries; no full-body claim is made. Formatting and126 portable PowerPC modules pass. Full actor preparation, general transforms and playable application remain unfinished. Evidence: render-operation-verification.json.

Recovered original0x4ab380 premultiplied-alpha shared-backing image path. All4,096 complete original executions match, including aliasing, arbitrary RGB/alpha, overlapping rows and empty images. Existing pixel and traversal comparisons pass. Formatting and126 portable PowerPC modules pass. General transforms, actor preparation and playable Wii application remain unfinished. Evidence: RENDER-PIXEL.md and render-pixel-verification.json.

Integrated bound32-bit image renderer with original operation selection. All22,272 original selector-plus-complete-drawing executions match backing across87 pixel kernels, native/scaled paths and alpha overrides. Preparation is supplied;22,272 unsupported transform requests preserve destination. Formatting and126 portable PowerPC modules pass. Full actor clipping/preparation, general transforms, borders, presentation and playable Wii application remain unfinished. Evidence: RENDER-PIXEL.md and render-pixel-verification.json.

Integrated complete prepared32-bit renderer: gate, flags, operation selection, conditional preparation and drawing. All2,048 complete original4af560 executions match whole backing with real4ae250 and drawing bodies; no preparation/drawing boundaries are replaced in these cases. Supplied geometry/tables and disabled borders/callbacks define scope. Failed backing preserves both pixels and native preparation. Formatting and126 portable PowerPC modules pass. Actor geometry, transforms, borders/presentation and playable Wii application remain unfinished. Evidence: RENDER-PIXEL.md and render-pixel-verification.json.

Recovered direct actor geometry composition in actor_render_geometry.c. All4,096 complete original4ae3e0 executions match visibility, visible dimensions, source offsets and target pixel pointer (2,593 visible), through scale1..16, descriptor anchors, actor1e displacement, direct-mode ignored91 override and target clipping mode1. All4,096 truncated actor storage cases preserve output. Formatting and127 portable PowerPC modules pass. Drawing integration, other clip modes, screen-relative actor paths and playable application remain unfinished. Evidence: actor-render-geometry-verification.json.

Recovered Player piece create/release 0x432160, 0x4321b0 and 0x432110 in player_piece.c. 2,048 complete original executions match whole player/parent/child storage with allocation and the virtual destructor as supplied boundaries. Destructor bodies, preview construction 0x4320d0/0x42b6b0 and game-loop integration remain unfinished. See PLAYER-PIECE.md and player-piece-verification.json.

Recovered piece parent destructor 0x42ab10 and base actor destructor 0x4ac130 in piece_actor_destroy.c. 8,192 complete original executions match whole parent storage and child destruction/free event order. Flag 4 virtual-base cleanup, child destructor bodies and vtable slot 2 (0x42abf0) remain unfinished. See PIECE-ACTOR-DESTROY.md.

Recovered piece vtable slot-2 forwarders 0x42abf0 and 0x42ac30. 8,192 complete original executions match call order, identity and argument with slot-2 targets supplied. See PIECE-ACTOR-DESTROY.md.

Recovered base-actor refresh state and slot methods 0x4ac1c0, 0x4ac1e0, 0x4adf70, 0x4adfa0, 0x4adfb0, 0x4adfe0, 0x4adf90, 0x4ae0f0 and 0x4ae0c0 in actor_refresh.c. 36,864 complete original executions match whole actor storage and 0x5bb710 state. Remaining base slots 0x4ae010 and 0x4ae140 unfinished. See ACTOR-REFRESH.md.

Recovered base actor draw slot 0x4ae010 and chain walk 0x4ade60 (base slot 2 0x4ae140) in actor_draw_slot.c. 8,192 draw and 4,096 chain complete original executions match call order and arguments with 0x47ce10, 0x4ac8a0 and 0x4af8c0 supplied; actor storage and 0x5bb710 state compare whole. Boundary bodies, scene/game-loop integration and the playable application remain unfinished. See ACTOR-DRAW-SLOT.md.

Recovered chain visit routines 0x4ac8a0 and 0x4af8c0 in actor_chain_visit.c. 4,096 complete original executions each match call order, registers, whole actor storage and global 0x5bc010 with 0x4877f0, 0x4ae3e0 and 0x4af560 supplied. Gate 0x4ae3e0 and scene/game-loop integration remain unfinished. See ACTOR-CHAIN-VISIT.md.

Recovered clipping gate 0x4ae3e0 (0x4ae3e0..0x4af212) in actor_gate.c with inline 0x4ae110 and 0x478eb0. 18,083 complete original executions match the eax result, whole 0x5bb680..0x5bc01f globals and whole actor storage (2,678 drawable, 797 mask-row, 11,847 table-scaled); 1,917 original faults are rejected natively. Original memory is read through a callback. Drawing 0x4af560, scene/game-loop integration and the playable application remain unfinished. See ACTOR-GATE.md.

Recovered board marking 0x42f210, 0x42f440 and 0x42f4b0 and column fall 0x42f760 (with its virtual destructor supplied) in board_cells.c. 4,096 complete original executions each match every modeled scene collection and cell array plus destruction order. Callers, the remaining board routines and the game loop remain unfinished. See BOARD-CELLS.md.

Recovered one-field actor setters 0x4ac510, 0x4ac7b0, 0x4ac7d0 and 0x4ac8f0 in actor_fields.c (4,096 complete original executions each, whole actor storage). Added board routines 0x42eb60, 0x430150, 0x42ee20 and 0x42ee80 to board_cells.c (4,096 executions each over whole scene collections, resolved object storage and destruction order). See ACTOR-FIELDS.md and BOARD-CELLS.md.

Added board routines 0x4300b0, 0x430100, 0x432200, 0x432280, 0x4322f0, 0x4334b0 and 0x432ba0 to board_cells.c. 4,096 (8,192 for the placement pair) complete original executions each match whole scene collections, resolved object storage, scan results and destruction order. See BOARD-CELLS.md.

Recovered board collection wrappers 0x42ebc0..0x42ec60, 0x42ec80..0x42ed20, 0x42ed40, 0x42ed70, 0x42eda0, 0x42edc0 and 0x42edf0 with list helpers 0x4b22c0, 0x4b2300 and 0x4b2340 in board_collections.c. 2,048 cases per wrapper (12,288 each for the clear and all-handler families) match whole scene collections, every object and destruction order. See BOARD-COLLECTIONS.md.

Recovered board kind snapshot and marker routines 0x4327e0, 0x432840, 0x435e80, 0x435f30, 0x435fe0, 0x436030, 0x436070, 0x4360b0 and 0x436100 in board_markers.c. 4,096 to 12,288 complete original executions each match snapshots, marker grids, counts and found cells. See BOARD-MARKERS.md.

Added marker builders 0x436850, 0x4372c0, 0x436fe0, 0x437240, 0x436a10 and 0x436aa0 to board_markers.c and setters 0x4ac380, 0x4ac490 and 0x4ac710 to actor_fields.c, each with 4,096+ complete original executions. See BOARD-MARKERS.md and ACTOR-FIELDS.md.

Added 0x42ff10 (board clip rectangle for an actor) to board_cells.c; 4,096 complete original executions match the whole actor.

Added 0x438830, 0x4388a0 and 0x438910 to board_markers.c and 0x4387b0 to board_collections.c; 2,048 to 8,192 complete original executions each match results, outputs, snapshots and every object. See BOARD-MARKERS.md and BOARD-COLLECTIONS.md.

Added 0x438d50 and 0x439140 to board_markers.c and 0x438c60 to board_collections.c (4,096 and 2,048 complete original executions). 0x438cd0 is documented as not portable: it compares against an uninitialized stack buffer. See BOARD-MARKERS.md and BOARD-COLLECTIONS.md.

Added 0x439370 to board_markers.c and 0x4398c0, 0x439190 and 0x438b90 to board_collections.c (2,048 to 14,336 complete original executions each; whole scene, every object and destruction order). See BOARD-MARKERS.md and BOARD-COLLECTIONS.md.

board_fields: 0x431380, 0x432000, 0x431480, 0x431490, 0x431d80, 0x4334a0, 0x4342f0, 0x432010, 0x430090 plus actor 0x4ac470/0x4ac900 verified against the oracle (docs/BOARD-FIELDS.md).

Added event_stack.c (0x482060, 0x482110, 0x482210, 0x482300): nine-record event stack push/pop/replace-top/empty; 4,096 complete original executions each over the whole object and every output pointer. See EVENT-STACK.md.

Recovered UI slide setup routines 0x4717f0, 0x4719a0, 0x471820 and 0x457890 in ui_slide_setup.c (4,096 complete original executions each, whole actor storage; 0x457890 runs the real 0x4b14c0). See UI-SLIDE-SETUP.md.

Added choice_grid.c: 0x429d50, 0x429df0, 0x429e80, 0x429ee0, 0x42a080, 0x42a140, 0x42a170, 0x42a190 and 0x42a1b0 (seven by four grid object; 4,096 complete original executions each, with the random draw 0x4826c0 stubbed and replayed). See CHOICE-GRID.md.

Added color_conversion.c (0x480890, 0x480ca0, 0x481d90): 6-bit palette expansion, 8x8x4 colour cube and pixel layout conversion; 4,096 to 16,384 complete original executions each. See COLOR-CONVERSION.md.

Recovered panel broadcasts 0x45f9f0, 0x45fa70, 0x45fab0 and 0x472d50 in ui_panel_dispatch.c with the vtable calls as a supplied boundary (2,048 complete original executions each, every call and the cleared global compare). See UI-PANEL-DISPATCH.md.

Added piece_children.c: 0x42a980/0x43a5b0, 0x43a410, 0x43a5f0, 0x42a800 and 0x425ef0 (piece child kinds, setup, placement and kind-table init; 4,096 complete original executions each, resource attach 0x4ac8d0 stubbed). See PIECE-CHILDREN.md.

Added actor_value_steps.c (0x4ac980, 0x4acb00, 0x4ad750, 0x4ac3b0, 0x4ac7e0, 0x4ac810, 0x4ac760, 0x4ac780): clamped stepping, progress quotient, random period/d0 draws and frame-count tests; 4,096 complete original executions each (draws stubbed and replayed). See ACTOR-VALUE-STEPS.md.

Recovered sound wrapper state routines 0x4756d0, 0x475790, 0x4768e0, 0x476d20, 0x4779c0, 0x477910, 0x476650, 0x476c80, 0x476cc0, 0x477320, 0x477d10, 0x476a00, 0x4772f0 and 0x477af0 in sound_object.c with interface calls and the 0x476aa0/0x477390/0x477b10 builders as supplied boundaries (4,096 complete original executions each, whole object, every call and return). See SOUND-OBJECT.md.

Added release_tables.c: 0x43f3f0 and 0x442110 (shutdown release loops over handle tables; 2,048 complete original executions each, releases stubbed). See RELEASE-TABLES.md.

Added fixed_point.c (0x4849e0, 0x4849f0, 0x484630, 0x484680, 0x4845d0, 0x484700): 16.16 multiply/divide, iterative integer root, point distance, angle-table lookup and point heading; 8,192 complete original executions each (faulting divisions matched as invalid). See FIXED-POINT.md.

Recovered pure value routines 0x4776a0 (limited decimal text), 0x478b70, 0x478da0, 0x478480 and 0x479a40 in object_value_helpers.c (8,192 complete original executions each, whole objects and text buffers). See OBJECT-VALUE-HELPERS.md.

Added resource_record.c: 0x441530, 0x441a80, 0x441b30 and 0x442b00 (resource record init/release/draw and text width; 4,096 complete original executions each, release and draw stubbed). See RESOURCE-RECORD.md.

Recovered sound cue wrappers 0x476fb0, 0x476fe0, 0x477010..0x477160, 0x4784d0, 0x478520, 0x478570..0x4787a0 and 0x476720 in sound_cues.c with the 0x4761d0/0x476280 start/stop routines as a supplied boundary (2,048 to 16,384 complete original executions, every call compared). See SOUND-CUES.md.

Added actor_angle.c (0x4ad110, 0x4ace40, 0x4ad1c0, 0x4ad210, 0x4ad260): angle spin and turn with 360-degree wrapping and table-scaled polar offsets/orbit points; 2,800 to 4,096 complete original executions each over whole actors. See ACTOR-ANGLE.md.

Added actor_frame_switch.c: 0x449360 and 0x449390 (frame decay and frame switch over the recovered word transition and refresh state; 8,192 complete original executions each, attach/frame/bind stubbed). 0x449460 documented as not portable (uses edx left by 0x4ac8a0). See ACTOR-FRAME-SWITCH.md.

Recovered actor list idle scans 0x471c40, 0x471c90, 0x471cd0, 0x471d10, 0x471d50 and 0x472360 in actor_list_idle.c (4,096 complete original executions each over handle arrays of 0 to 12 actors). See ACTOR-LIST-IDLE.md.

Added stream_read.c (0x48a930, 0x48a9d0, 0x48aa90): memory stream bounded read, partial read and skip; 4,096 complete original executions each (stream object, destination and results). See STREAM-READ.md.

Added player_slots.c: 0x43d3b0, 0x43d3d0, 0x43aab0, 0x43b810 and 0x43b1a0 (player mode groups, side placement, level clamp and first-turn decision; 4,096 complete original executions each). See PLAYER-SLOTS.md.

Added mode_colors.c: 0x43bd90 (effect mode to primary/secondary color chooser; 8,192 complete original executions over all 256 modes). See MODE-COLORS.md.

Added engine_helpers.c (0x482480, 0x487870, 0x482750, 0x481420, 0x4ae170): random/table object constructors, inclusive random range, run-length encoded size and cell cursor clamp; 4,096 to 17,900 complete original executions each. See ENGINE-HELPERS.md.

Recovered software surface operations 0x479450, 0x479d70, 0x479b50, 0x47e200 and 0x47cd60 in surface_pixel_ops.c (4,096 complete original executions each; all pixel bytes and output compare, out-of-storage requests rejected). See SURFACE-PIXEL-OPS.md.

Recovered display object helpers 0x47f160, 0x47f320, 0x47f370, 0x47f410, 0x47ea20, 0x47fe20, 0x47fe50 and 0x47fe80 in display_object.c (4,096 complete original executions each over guest node chains and vtable stubs). See DISPLAY-OBJECT.md.

Added ai_features.c: 0x4261b0, 0x427c10, 0x427e10 and 0x428e70 (row reach, feature bytes, mode flags and choice grid scores; 8,192 complete original executions each). See AI-FEATURES.md.

Recovered surface bounding box 0x4792d0 in surface_bounds.c (4,096 complete original executions, including the whole-image quirk for an image whose leftmost nonzero column is the last). See SURFACE-BOUNDS.md.

Added range 0x401000..0x41ffff batch: table_queries.c (0x417930/970/cf0/d10/d40/d70/df0/da0/e20/fc0, 0x418000/050/0a0, 0x417840, 0x40f170, 0x415c00/c30, 0x415e40/e80, 0x4153e0, 0x417e60/ed0), session_registers.c (0x415550/b50/b90/bd0), device_flags.c (0x40ee30/e60/ea0/ef00/ef40/ede0), handle_registry.c (0x40a860/890/ab20/ab60/aba0/aca0/ad50), bit_reader.c (0x4046e0/404610/404680/4060e0), file_reads.c (0x40c220/260/2a0/2e0/320/360), record_slots.c (0x412650/690/4120a0/4125e0/412430/412510), link_queue.c (0x405e00/405ea0), anchor_offsets.c (0x414a90/414b10), frame_counter.c (0x41d670), pitch_curve.c (0x410150), slot_deal.c (0x415c60) and mpeg_header.c (0x404480); each has tools/verify_NAME.py running the complete original in Unicorn over 4,096+ cases with only unrecovered callees stubbed. See TABLE-QUERIES.md, SESSION-REGISTERS.md, DEVICE-FLAGS.md, HANDLE-REGISTRY.md, BIT-READER.md, FILE-READS.md, RECORD-SLOTS.md, LINK-QUEUE.md, ANCHOR-OFFSETS.md, FRAME-COUNTER.md, PITCH-CURVE.md, SLOT-DEAL.md and MPEG-HEADER.md.

Added ai_scoring.c: 0x428110 and 0x428610 (board pressure comparison and record list scoring; 8,192 complete original executions each). See AI-SCORING.md.

Added particle_spawn.c: 0x43dea0, 0x43e740, 0x43e840 and 0x43e920 (background particle initializers over the recovered actor setters; 4,096 complete original executions each, random draw and image lookup stubbed). See PARTICLE-SPAWN.md.

board_piece: 0x4320c0, 0x42f2e0, 0x431fa0, 0x431fb0, 0x432040, 0x432080 verified against the oracle (docs/BOARD-PIECE.md).

board_piece (cont.): 0x431340, 0x431b20, 0x431c10 verified against the oracle (docs/BOARD-PIECE.md).

object_scalars: 0x4126d0, 0x4126f0, 0x415b30, 0x415b40, 0x415d60, 0x415d90, 0x417f40, 0x418820, 0x418830, 0x418840, 0x418870, 0x41a930, 0x41d660, 0x42a940, 0x42a950, 0x42ba40, 0x43b860, 0x43b870, 0x43b970, 0x43bad0, 0x43bae0, 0x43bd40, 0x43cc90, 0x43cde0 verified against the oracle (docs/OBJECT-SCALARS.md).

object_scalars (cont.): 0x415b10, 0x415530, 0x415d40, 0x418150, 0x425e00, 0x43bd60; piece_children: 0x43a510, 0x43a560, 0x42b920 verified against the oracle.

board_markers (cont.): 0x4375a0 (mark filled), 0x4328a0 (any falling), 0x432820 (first-grid snapshot); piece_children (cont.): 0x43a520, 0x42b9f0 verified against the oracle.

field_accessors: 0x471e60, 0x471e80, 0x471ea0, 0x471eb0, 0x471ec0, 0x471ed0, 0x45f1e0, 0x4757b0, 0x475800, 0x475810, 0x475820, 0x475830, 0x4759d0, 0x475b00, 0x475dd0, 0x475df0, 0x475e10, 0x475e40, 0x477240, 0x477870, 0x477e10, 0x478460, 0x479b30, 0x47e990 verified against the oracle (docs/FIELD-ACCESSORS.md).

actor_fields (cont.): 0x4ac370, 0x4ac390, 0x4ac4e0, 0x4ac4f0, 0x4ac520, 0x4ac540, 0x4ac640, 0x4ac700, 0x4ac740, 0x4ac750, 0x4ac7a0, 0x4ac840, 0x4ac860, 0x4ac910, 0x4ac920, 0x4ac930, 0x4ac940, 0x4ac950, 0x4ac960, 0x4ad510, 0x4ad520, 0x4b54d0 verified against the oracle (docs/ACTOR-FIELDS.md).

object_dwords: generic object field routines 0x47e9a0..0x4d5350 (60 small routines, see docs/OBJECT-DWORDS.md) verified against the oracle.

object_slots: 0x42a480, 0x42a4a0, 0x43d800, 0x429660, 0x429670, 0x43d300, 0x475da0, 0x476120, 0x476140 verified against the oracle (docs/OBJECT-SLOTS.md).

object_slots (cont.): 0x471bb0, 0x471bf0, 0x471d90, 0x471dd0; piece_children (cont.): 0x42b950, 0x42b990 verified against the oracle.

block_factory: 0x4ac8d0, 0x4adf20, 0x42bb00, 0x42bbd0, 0x430800 verified against the oracle (docs/BLOCK-FACTORY.md); the allocator, resolver and random draw are supplied services.

key_maps: 0x43f550, 0x43f630, 0x43f710, 0x43f7f0, 0x43f8d0, 0x43f9b0, 0x43fa90, 0x43fb70 verified against the oracle (docs/KEY-MAPS.md).

board_actions: 0x4330d0, 0x4371b0, 0x437460, 0x438470, 0x433750 verified against the oracle (docs/BOARD-ACTIONS.md).

player_actions: 0x43bb60, 0x43b7c0 verified against the oracle (docs/PLAYER-ACTIONS.md).

board_markers (cont.): 0x432b10 (mark falling cells) verified against the oracle.
board_conversions: 0x436720, 0x437060, 0x437350 verified against the oracle.
choice_grid (cont.): 0x429fe0 (pick row then column) verified against the oracle.
board_overlay: 0x42ff50 verified against the oracle.
score_text: 0x417790 verified against the oracle.
table_queries (cont.): 0x415eb0 and 0x415ed0 verified against the oracle.
board_piece_moves: 0x42efa0, 0x42f030, 0x42f120, 0x42f280, 0x42f2b0, 0x42f520, 0x42f550, 0x42f6e0, 0x42f720 verified against the oracle.
player_actions (cont.): 0x43bc90, 0x43bce0, 0x43ccb0, 0x43bd00; object_slots (cont.): 0x43e260, 0x42eba0 verified against the oracle.
board_overlay (cont.): 0x43d2b0 verified against the oracle.
- player_actions (cont.): 0x43b6a0 vertrix_player_draw_table_value, verified over 4096 cases in the oracle (docs/player-actions-verification.json).
- player_slots (cont.): 0x43cef0 vertrix_player_setup_side_31 (mode 0x31) added to the mode-setup family; 206 complete original executions (docs/player-modes-verification.json).
- board_markers (cont.): 0x4383f0 vertrix_board_mark_stones (marker 0 empty, 1 stone, 2 other), 4,096 complete original executions (docs/board-markers-verification.json).
record_stream: 0x4293e0 vertrix_saved_block_load (saved block read from a range stream, bytes at +0x70 complemented, state 1 becomes 2); 4,096 complete original executions (docs/record-stream-verification.json).
record_stream (cont.): 0x4121e0 vertrix_record_table_load (record table and count read from a range stream, +0x5bc restored); 4,096 complete original executions.
board_conversions (cont.): 0x437be0 vertrix_board_scatter_marked; 2,048 complete original executions (docs/board-conversions-verification.json).
board_conversions (cont.): 0x437b70 vertrix_board_prime_companions, 0x437d70 vertrix_board_split_marked; 2,048 complete original executions each (docs/board-conversions-verification.json).
board_conversions (cont.): 0x4368e0 vertrix_piece_replace_children, 0x436b40 vertrix_boards_convert_counts; 2,048 complete original executions each.
board_conversions (cont.): 0x436d80 vertrix_boards_convert_random; 2,048 complete original executions.
board_conversions (cont.): 0x438540 vertrix_board_collapse_marked; 2,048 complete original executions (moving, settled and no-marker cases).
board_conversions (cont.): 0x439260 vertrix_board_pick_kinds; 2,048 complete original executions.
board_markers (cont.): 0x437f60 vertrix_board_mark_stones_not_bombs (4,096 executions). board_conversions (cont.): 0x437fe0 vertrix_board_spin_marked (2,048 executions).
board_conversions (cont.): 0x4378c0 vertrix_board_swirl_marked; 2,048 complete original executions.
board_conversions (cont.): 0x438960 vertrix_board_set_motion; 2,048 complete original executions.
settings_defaults: 0x4290c0 vertrix_settings_defaults; 2,048 complete original executions (docs/SETTINGS-DEFAULTS.md).
surface_blit: 0x47ce10 vertrix_surface_blit (format converting rectangle copy, fast and pitched paths); 8,192 complete original executions over every format pair (docs/SURFACE-BLIT.md).
surface_blit (cont.): 0x41a2f0 vertrix_surface_blit_progress, 0x41ab90 vertrix_surface_blit_region; 2,048 complete original executions each.
surface_blit (cont.): 0x441b30 vertrix_surface_blit_whole; 2,048 complete original executions.
- 0x47a040 `vertrix_surface_fade` (neighbour-mean table blend for 2/4-byte surfaces; source/surface_blit.c, tools/verify_surface_fade.py, docs/surface-fade-verification.json): 4000 complete original executions match.
- 0x4316c0 `vertrix_board_place_stones` (release the +0x988 collection, then five stones of kind 5 with handler 0x44f700; source/board_conversions.c, tools/verify_board_stones.py, docs/board-stones-verification.json): 4000 complete original executions match, destroy events included.
- 0x431780 and 0x431930 `vertrix_board_deal_first_row` / `vertrix_board_deal_second_row` (clear the 13 entry collection, deal a row of 0x4f9ad8 pattern bytes; source/board_conversions.c, tools/verify_board_rows.py, docs/board-rows-verification.json): 4000 complete original executions match, destroy events included. The spawn index is the sign extended byte.
- 0x430660 `vertrix_board_burst` (ten sparks, heading step 36; source/board_burst.c, tools/verify_board_burst.py, docs/BOARD-BURST.md, docs/board-burst-verification.json): 4000 complete original executions match; frame binding 0x4ac8a0 and list append 0x4b5e70 are logged boundaries.
- 0x430440 `vertrix_board_rings` (three rings of 18 sparks; same file, verifier and evidence as 0x430660): 4000 complete original executions across both routines match.
- 0x433550 `vertrix_board_marker_reach` (smallest distance with no kind 6 neighbour in the directions of mode byte +0x839; source/board_conversions.c, tools/verify_board_reach.py, docs/board-reach-verification.json): 4000 complete original executions match.
- 0x433180 `vertrix_board_tile_cell` (edge tile bytes from the eight neighbour flags and four 8 byte tables; source/board_tiles.c, tools/verify_board_tiles.py, docs/board-tiles-verification.json): 4000 complete original executions match, scratch globals 0x5407f9..0x540804 included.
- 0x436150 `vertrix_board_swap_marked` (swap the kinds of two drawn marked blocks; source/board_conversions.c, tools/verify_board_swap.py, docs/board-swap-verification.json): 4000 complete original executions match.
- 0x43e740 and 0x43e840 `vertrix_particle_init_drift` / `vertrix_particle_init_fall` (source/particle_init.c, tools/verify_particle_init.py, docs/particle-init-verification.json): 4000 complete original executions match, scratch globals 0x541014.. and 0x54101c.. included; frame binding 0x4ac8a0 is a logged boundary.
- 0x43e4d0 `vertrix_board_particles_setup` (picture scan for 30 spots, three plumes, 450 drifting particles and one falling particle; source/particle_init.c, tools/verify_particle_setup.py, docs/particle-setup-verification.json): 600 complete original executions match (operator new, draws, picture loader 0x4816f0, release 0x478d80 and frame binding 0x4ac8a0 as logged boundaries; pixel reader 0x478f10 ran for real).
- 0x46e8b0 `vertrix_marquee_build` (sixteen strip cells appended to the list at 0x54671c; source/particle_init.c, tools/verify_marquee.py, docs/marquee-verification.json): 4000 complete original executions match; frame binding and list append are logged boundaries.
- 0x4ad790 (and 0x4ad6e0) `vertrix_actor_dword_transition` (dword transition of current/target/step at +0x70/+0x74/+0x78 or +0x58/+0x5c/+0x60; source/dword_transition.c, tools/verify_actor_dword_transition.py, docs/actor-dword-transition-verification.json): 8192 complete original executions match.
- 0x4ad3c0 `vertrix_actor_double_orbit_point` (two chained polar offsets with the radius words +0x3a and +0x2a; source/actor_angle.c, tools/verify_actor_double_orbit.py, docs/actor-double-orbit-verification.json): 8192 complete original executions match, scratch globals 0x5bb620.. included.
- 0x4ad440 `vertrix_actor_chain_orbit_point` (three chained polar offsets through the overlapping scratch globals 0x5bb62c..; same file, verifier and evidence as 0x4ad3c0): 4096 complete original executions match.
- 0x4ac5b0 and 0x4ac6b0 `vertrix_actor_counter_wrap` / `vertrix_actor_progress_wrap` (remainder of the counter by the period / of the progress by the total; source/actor_fields.c, tools/verify_actor_wrap.py, docs/actor-wrap-verification.json): 8192 complete original executions match.
- 0x4731a0 `vertrix_icons_build` (two icon actors appended to the list at 0x546730; source/particle_init.c, tools/verify_icons.py, docs/icons-verification.json): 4000 complete original executions match; frame binding and list append are logged boundaries.
- 0x43a310 `vertrix_piece_frames_build` (three frame blocks of a piece appended to the list at +0x15c; source/particle_init.c, tools/verify_piece_frames.py, docs/piece-frames-verification.json): 4000 complete original executions match; allocation, draw and frame binding are logged boundaries.
- 0x4182f0, 0x418550, 0x418570, 0x416c10, 0x4735e0, 0x473610, 0x45e690, 0x45e720, 0x45e990, 0x45f0a0, 0x425d30, 0x43f460 and 0x441120 (thin call-through wrappers on an injected `VertrixCalls` boundary; source/call_glue.c, tools/verify_call_glue.py, docs/call-glue-verification.json): 4000 complete original executions each match, with every callee call and return value logged.
- 0x471a70, 0x471a80, 0x471b00, 0x471b80, 0x472350, 0x475d90, 0x47ed50, 0x47f8d0, 0x476010, 0x476260, 0x478bd0, 0x482740, 0x482a40, 0x4872b0, 0x48c370 and 0x48d6b0 (second batch of call-through wrappers; source/call_glue.c, tools/verify_call_glue.py, docs/call-glue-verification.json): 4000 complete original executions each match; 0x476260 passes two stack arguments that its callee 0x475b80 pops with `ret 8`.
- 0x4b4510, 0x4b4c90, 0x4b4cd0, 0x4b5c60, 0x4b66c0, 0x4b6890, 0x4b69f0, 0x4b6a10 and 0x4b6f70 (object accessor wrappers over resolved storage; source/object_glue.c, source/call_glue.c, tools/verify_object_glue.py, docs/object-glue-verification.json): 4000 complete original executions each match, including the global 0x5bd828 and every pool object.
- 0x46b800, 0x473cd0, 0x475a80, 0x475ab0, 0x4764a0, 0x476590 and 0x478b40 (third batch of call-through wrappers; source/call_glue.c, tools/verify_call_glue.py) and 0x47ecd0 and 0x47f190 (object chain and match wrappers; source/object_glue.c, tools/verify_object_glue.py): 4000 complete original executions each match.
- 0x47f9b0, 0x482bb0, 0x489760, 0x47fbb0, 0x40c1e0, 0x40c1f0, 0x40c210, 0x40ae80, 0x40ab10, 0x487a10 and 0x48d620 (fourth batch of call-through wrappers; source/call_glue.c, tools/verify_call_glue.py), 0x482720, 0x487280, 0x487710, 0x4872c0, 0x48c9b0, 0x4879f0 and 0x48d600 (object allocation wrappers; source/object_glue.c, tools/verify_object_glue.py) and 0x4885a0 and 0x488940 (path separator scans; source/path_text.c, tools/verify_path_text.py, docs/path-text-verification.json): 4000 complete original executions each match. 0x4895b0, 0x4895e0 and 0x489610 (find-data buffers on the host stack) and 0x482610 (stack temporary) are not ported.
- 0x4c5bc0, 0x4c5bd0, 0x4c5be0, 0x4c5bf0, 0x4c5c10, 0x45e8d0, 0x45ea60, 0x45e950, 0x4766f0, 0x4b8170, 0x4b7da0 and 0x47f260 (fifth batch of call-through wrappers; source/call_glue.c, tools/verify_call_glue.py; 0x4766f0 loops the recovered 0x475a80 body), and 0x48c260, 0x48c280, 0x48c2b0, 0x48c2e0, 0x48c310, 0x48c330 (notify wrappers over 0x48c9b0), 0x4b4cb0, 0x4b78d0, 0x48d520, 0x4b7a80, 0x4b4660, 0x4b4690, 0x4c3fa0, 0x47f070 (source/object_glue.c, tools/verify_object_glue.py): 4000 complete original executions each match.
- 0x457810, 0x450f80 and 0x452250 (object event handlers on the injected call boundary; source/object_events.c, tools/verify_object_events.py, docs/object-events-verification.json): 4000 complete original executions each match, with the draw 0x4826c0 replayed.
- 0x4760f0, 0x479df0 (call_glue), 0x475a20, 0x4762e0 and 0x478c90 (object_glue): sweep, neighbour, list-initialisation, slot-selection and literal-copy wrappers; 4000 complete original executions each match (tools/verify_call_glue.py, tools/verify_object_glue.py).
- 0x41de80, 0x476090, 0x482b30, 0x489f90, 0x4b4600, 0x4b4610, 0x4b4620, 0x4b5500, 0x4b6700, 0x48d480 and 0x48a2f0 (object tail wrappers; source/object_tails.c, tools/verify_object_tails.py, docs/object-tails-verification.json) and 0x4b79a0 (same wrapper as 0x4b6f70, tools/verify_object_glue.py): 4000 complete original executions each match.
- 0x4765b0, 0x4760c0 and 0x4766b0 (fixed-code, index-sweep and table-switch wrappers; source/call_glue.c, tools/verify_call_glue.py): 4000 complete original executions each match.
- 0x45e590, 0x45e6b0 and 0x45ec50 (resource table loops on the injected call boundary, previously listed as not portable for want of the callees; source/table_loops.c, tools/verify_table_loops.py, docs/table-loops-verification.json): 4000 complete original executions each match, every callee call logged.
- 0x45ed10, 0x45ee30, 0x45f020, 0x45f140, 0x45f1f0 and 0x45f250 (the remaining resource table loops of the 0x45e590 family; source/table_loops.c, tools/verify_table_loops.py): 4000 complete original executions each match, every callee call logged.
- 0x471e10 and 0x4725f0 (lookups through 0x4b5eb0 with 0x4123d0 and a field clear, previously unported for want of 0x4123d0; source/object_tails.c, tools/verify_object_tails.py): 4000 complete original executions each match.
- 0x42e870 (board constructor), 0x43d6a0 and 0x4413b0 (object constructors without the exception frame, which leaves no state; source/object_construct.c, tools/verify_object_construct.py, docs/object-construct-verification.json): 4000 complete original executions each match, every callee call logged.
- 0x4b7080, 0x4b7120, 0x4b71c0, 0x4b7260, 0x4b7300, 0x4b73a0 and 0x4b7420 (checked list text readers; source/list_text.c, tools/verify_list_text.py, docs/list-text-verification.json): 4000 complete original executions each match, exception frame included, with 0x4cdfb0 stubbed as a cdecl call (oracle_kit.Stubs.add gained a cdecl flag; VertrixCallSite gained stack_third).
- 0x4b3740, 0x4b37e0, 0x4b3880 and 0x4b3940 (list box previous/next choice steppers over the string compare 0x4ccfe0; source/list_text.c, tools/verify_list_text.py): 4000 complete original executions each match, exception frame included.
- 0x4177b0 (high score table insertion; source/score_table.c, tools/verify_score_table.py, docs/score-table-verification.json): 4000 complete original executions match, every rank 0..4 and the not-ranked result seen, with the name slot moves 0x4ca310 and 0x4ca370 logged.
- 0x4179d0 (four-lookup average over 0x417970; source/score_table.c, tools/verify_score_table.py): 4000 complete original executions match, outputs in guest memory compared.
- 0x484a60, 0x48d330, 0x48d500, 0x4b4630, 0x4b5d40 and 0x4b6020 (object_tails: table, clear, text-length and item-release wrappers) and 0x415e10 (call_glue: clear-each loop over 0x482b30): 4000 complete original executions each match (tools/verify_object_tails.py, tools/verify_call_glue.py). vertrix_object_text_length is now public in object_glue.c.
- 0x472570 (special actor spawn: operator new, 0x4abd70, the recovered 0x4adf20 placement and four logged calls; source/object_construct.c, tools/verify_object_construct.py): 4000 complete original executions match, allocation replayed through the services.
- 0x4365c0 and 0x436440 (board cell replacement: retire the block, spawn its replacement, finish both; source/board_cell_replace.c, tools/verify_board_cell_replace.py, docs/board-cell-replace-verification.json): 4000 complete original executions each match, every callee call logged; the callee outputs through the ebx and ecx locals travel in VertrixCallSite.out_ebx and out_ecx and the routine frame is a token.
- 0x433040 (burst on every occupied cell of two boards; source/board_cell_replace.c, tools/verify_board_cell_replace.py): 4000 complete original executions match, every 0x430660 call logged.
- 0x43bbf0 (board view setup through 0x482110 with eleven stack arguments; source/board_cell_replace.c, tools/verify_board_cell_replace.py; VertrixCallSite gained stack_rest and out_value, vertrix_calln added): 4000 complete original executions match, all eleven stack arguments logged.
- 0x43dc80 (particle emission with the three resource branches; source/particle_emit.c, tools/verify_particle_emit.py, docs/particle-emit-verification.json): 4000 complete original executions match across all emitter modes, every callee call and draw logged.
- 0x441e30 colour table builder (`source/color_table.c`): verified against the original in `docs/color-table-verification.json`.
- 0x419490, 0x4194b0, 0x45ecd0 (`vertrix_guarded_call`, `vertrix_resource_pair_call` in `source/call_glue.c`): verified in `docs/call-glue-verification.json`.

- 0x40afc0 (`vertrix_mode_switch_call`): verified in `docs/call-glue-verification.json`; the callee's edx is restored, so no edx output is needed.
- 0x4895b0, 0x4895e0, 0x489610 (`vertrix_find_*` in `source/call_glue.c`): verified in `docs/call-glue-verification.json`; the find-data local is a frame token.
- 0x4b4270 (`vertrix_object_contains_point` in `source/object_bounds.c`): verified in `docs/object-bounds-verification.json`.
- 0x4874f0, 0x4876c0, 0x487660 (`source/array_list.c`): verified in `docs/array-list-verification.json`.
- 0x482610 (`vertrix_scratch_pair_call` in `source/call_glue.c`): verified in `docs/call-glue-verification.json`.
- 0x4b4fb0 (`vertrix_object_label_format` in `source/list_text.c`): verified in `docs/list-text-verification.json`; the returned eax is the restored exception chain and is not ported.
- 0x478bf0 (`vertrix_offset_pair_call` in `source/call_glue.c`): verified in `docs/call-glue-verification.json`.
- 0x45d820 (`vertrix_object_step_toggle` in `source/object_glue.c`): verified in `docs/object-glue-verification.json`.
- 0x472d00, 0x476530, 0x4777c0 (`vertrix_slot_create_call`, `vertrix_slot_search_call`, `vertrix_text_append_call` in `source/call_glue.c`): verified in `docs/call-glue-verification.json`.
- 0x40ed70 (`vertrix_flagged_table_call` in `source/call_glue.c`): verified in `docs/call-glue-verification.json`.
- 0x417f40 (`vertrix_matcher_reset`) and 0x417f50 (`vertrix_matcher_feed`) in `source/call_glue.c`: verified in `docs/call-glue-verification.json`.
- 0x4b5420 (`vertrix_object_destroy_call` in `source/object_glue.c`): verified in `docs/object-glue-verification.json`.
- 0x4408e0 (`vertrix_corner_transform_call` in `source/call_glue.c`): verified in `docs/call-glue-verification.json`; the original's eax is the restored exception chain and is not ported.
- 0x4ac560, 0x4aca00, 0x40ba00 (`vertrix_object_scale_call`, `vertrix_step_toward_call`, `vertrix_curve_table_build` in `source/call_glue.c`): verified in `docs/call-glue-verification.json`. They keep a value in the x87 stack between runtime calls; the recovery models each call by its registers and, like the oracle stubs, assumes the callees preserve edx, ebx and ecx.

## Remaining functions (not ported as C)

- 0x4c8000 and up (about 120 entries): Delphi runtime library (string, exception, FPU, heap). On the Wii these are replaced by newlib and the C runtime; a literal port would not be behaviour-preserving on a different ABI.
- Host-pointer / stack-local buffers (0x4b4fb0, 0x477610, 0x414b90): need the call boundary extended with edx outputs and buffer modelling before they can be verified.

## Delphi runtime wrappers

`source/rtl_glue.c` ports the runtime wrappers 0x4cbe80, 0x4cba60, 0x4dec60, 0x4dd170, 0x4d16b0, 0x4c9daf, 0x4c9dd6, 0x4c9e00, 0x4dd440, 0x4ddc40, 0x4c98f0, 0x4d4990, 0x4cd836, 0x4ca180, 0x4ca1e0, 0x4cba70, 0x4c9840, 0x4cb460, 0x4cbf10, 0x4ccb9f, 0x4cd0a4 and 0x4cd9f0, verified in `docs/rtl-glue-verification.json`. The runtime internals they call stay behind the call boundary.

## Array list table wrappers

`source/table_release.c` ports 0x45e670, 0x45e740, 0x45e810, 0x45e820, 0x45ed40, 0x45e830, 0x45e8f0, 0x45ea80, 0x45e910, 0x45e750 and 0x45e7b0, which release or visit the global array list objects through 0x4874f0 and 0x4876c0. Verified in `docs/table-release-verification.json`.

- 0x48a380 (`vertrix_stream_skip_line`), 0x48a620 (`vertrix_object_unknown_init`) and 0x48a8c0 (`vertrix_object_unknown_reset`) in `source/object_glue.c`: verified in `docs/object-glue-verification.json`.

- 0x4ad720 (`vertrix_object_step_field`) and 0x481f30 (`vertrix_object_create_with_class`) in `source/object_glue.c`: verified in `docs/object-glue-verification.json`.
- 0x4cfa10, 0x4d67b2, 0x4ce9fd, 0x4d4060, 0x4cf8e0 and 0x489470 in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4ca630, 0x4cdad0 and 0x4d3020 in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4d8082 (`vertrix_rtl_sign_compare`) in `source/rtl_glue.c`: pure, verified unstubbed in `docs/rtl-glue-verification.json`.
- 0x4d9510, 0x4d9530, 0x4dde50 (`vertrix_rtl_static_init_call`) and 0x4dad2e in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4dabe0, 0x4dacf8 (`vertrix_rtl_stack_pair_call`) and 0x4dad19 (`vertrix_rtl_sign_of`) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4db866 (`vertrix_rtl_flags_call`) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4db10a (`vertrix_rtl_scratch_triple_call`) and 0x4da66e (`vertrix_rtl_zero_call3`, eax not compared: restored exception chain) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4dd360 and 0x4d9280 (`vertrix_rtl_construct_list`, `_flag`) in `source/rtl_glue.c`: run unstubbed and compared byte for byte, in `docs/rtl-glue-verification.json`.
- 0x4d82c6 (`vertrix_rtl_select_float_helpers`) in `source/rtl_glue.c`: run unstubbed and the 0x503ea0 table compared, in `docs/rtl-glue-verification.json`.
- 0x4d8340, 0x4d8ab0 (`vertrix_rtl_construct_chunk_list`), 0x4ddc60 (`vertrix_rtl_release_list_head`) and 0x4cf980 (`vertrix_rtl_release_string_member`) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4dc160 (`vertrix_rtl_lookup_call`) and 0x4dfa7c (`vertrix_rtl_distribute_slack`, six dwords from +0x20) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4deec0 (`vertrix_rtl_construct_table`) and 0x4d94a0 (`vertrix_rtl_probe_call`, three stack arguments logged) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4d6775 (`vertrix_rtl_integer_to_double`) and 0x4d67f0 (`vertrix_rtl_float_to_integer`) in `source/rtl_glue.c`: pure, run unstubbed and compared in `docs/rtl-glue-verification.json`.
- 0x4ca3f0 (`vertrix_rtl_string_append_pair`) and 0x4cda90 (`vertrix_rtl_string_fill`) in `source/rtl_glue.c`: the variable is a pool handle read and written through the services; verified in `docs/rtl-glue-verification.json`.
- 0x4ca240 (`vertrix_rtl_string_copy_pair`) and 0x4ca670 (`vertrix_rtl_string_unique_size`, header 12 bytes before the text, 0x4ca150 gets the old header as its stack argument) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4ca6f0 (`vertrix_rtl_string_set_length`) in `source/rtl_glue.c`: runs the recovered 0x4ca670 inside, its own callees stubbed; verified in `docs/rtl-glue-verification.json`.
- 0x4cf320 and 0x4cf3a0 (`vertrix_rtl_construct_buffer_stream`) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4ca1a0 (`vertrix_rtl_string_make_unique`), 0x4d3120 (`vertrix_rtl_class_chain_contains`, acyclic chain of pool objects) and 0x4d8580 (`vertrix_rtl_wide_length`) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4d4390 (`vertrix_rtl_ancestor_search`) in `source/rtl_glue.c`: the 0x4d1890 chain is replayed with its stack argument logged; verified in `docs/rtl-glue-verification.json`.
- 0x4df140 (`vertrix_rtl_table_lookup_value`) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4d9930 (`vertrix_rtl_forward_pair`) in `source/rtl_glue.c`: both callees' stack arguments logged; verified in `docs/rtl-glue-verification.json`.
- 0x4ccee0 (`vertrix_rtl_link_owner`) in `source/rtl_glue.c`: the original runs the real 0x4df140 inside with only 0x4df0f0 stubbed; verified in `docs/rtl-glue-verification.json`.
- 0x4d0b30 (`vertrix_rtl_range_table_find`) in `source/rtl_glue.c`: run unstubbed over random tables and compared in `docs/rtl-glue-verification.json`.
- 0x4db6d9 (`vertrix_rtl_bracket_call`) and 0x418760 (`vertrix_rtl_construct_derived_stream`) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4decd0 (`vertrix_rtl_construct_event_table`) in `source/rtl_glue.c`: the real 0x4deec0 runs inside, 0x4def50 stubbed; verified in `docs/rtl-glue-verification.json`.
- 0x4d8620 (`vertrix_rtl_store_in_slot`) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4cd544 and 0x4cd520 (`vertrix_rtl_vararg_call`) in `source/rtl_glue.c`: 0x4cd520 runs the real 0x4cd544 with only 0x4cd56c stubbed; verified in `docs/rtl-glue-verification.json`.
- 0x4d66cd (`vertrix_rtl_test_and_set`) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4cda10 and 0x4cda12 (`vertrix_rtl_local_chain_call`) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4ca430 (`vertrix_rtl_string_concat`) in `source/rtl_glue.c`: the real 0x4ca3f0 runs inside with its callees stubbed; verified in `docs/rtl-glue-verification.json`.
- 0x4db1fd (`vertrix_rtl_split_exponent`, frexp) in `source/rtl_glue.c`: pure, run unstubbed and compared in `docs/rtl-glue-verification.json`.
- 0x4d6710 (`vertrix_rtl_parse_integer`) in `source/rtl_glue.c`: the class table at 0x507d58 reduces to white space 9..13 and 0x20 and digits 0..9; pure, compared in `docs/rtl-glue-verification.json`.
- 0x4daab0 (`vertrix_rtl_copy_terminated`) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4cdfe0 (`vertrix_rtl_string_trim_end`) and 0x4ce030 (`vertrix_rtl_string_trim_start`) in `source/rtl_glue.c`: the real 0x4ca1a0 runs inside, the character tests are replayed; verified in `docs/rtl-glue-verification.json`.
- 0x4dee73 (`vertrix_rtl_segment_dispatch`; the ds selector read from the emulator is passed in) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x4dae4a (`vertrix_rtl_negate_double`) and 0x4dae62 (`vertrix_rtl_absolute_double`) in `source/rtl_glue.c`: pure, compared in `docs/rtl-glue-verification.json`.
- 0x4b3c40 (`vertrix_object_label_format_alternate`) in `source/list_text.c`: shares the 0x4b4fb0 formatter with the value at +0x18c and format 0x51108e; verified in `docs/list-text-verification.json`.
- 0x4b7710 (`vertrix_list_text_indexed`) in `source/list_text.c`: verified in `docs/list-text-verification.json`.
- 0x4b76d0 (`vertrix_list_resize_call`) and 0x4b7830 (`vertrix_list_release_entries`, ecx is 0x51864c for an empty array; eax not compared) in `source/list_text.c`: verified in `docs/list-text-verification.json`.
- 0x4df81c (`vertrix_rtl_parse_format_flags`) and 0x4cdaf0 (`vertrix_rtl_string_tail`, the real 0x4ca240 runs inside) in `source/rtl_glue.c`: verified in `docs/rtl-glue-verification.json`.
- 0x45e850 and 0x45e9e0 (`vertrix_table_fill_indexed`) in `source/table_release.c`: the fill of 0x45e7b0 on the list at base + 28 * row; verified in `docs/table-release-verification.json`.
- 0x48a310 (`vertrix_stream_skip_blank`) in `source/object_glue.c`: the real 0x48a380 runs inside; the edx the original leaves after it is tracked; verified in `docs/object-glue-verification.json`.
- 0x477d70 (`vertrix_object_center_setup`) in `source/object_glue.c` (`docs/object-glue-verification.json`) and 0x48d3e0 (`vertrix_record_copy`, 0x34 bytes) in `source/rtl_glue.c` (`docs/rtl-glue-verification.json`): verified.
- 0x4b2400 (`vertrix_object_construct_labeled`) in `source/object_glue.c`: verified in `docs/object-glue-verification.json` (verifier object size raised to 0x400 for the +0x304 field).
- 0x4b6350 (`vertrix_object_construct_labeled_box`) in `source/object_glue.c`: shares the table-driven constructor with 0x4b2400; verified in `docs/object-glue-verification.json`.
- 0x4b5dc0, 0x481fb0 and 0x429350 (`vertrix_object_destroy_a`, `_b`, `_c`) in `source/object_glue.c`: Delphi destructors with the flags in edx; verified in `docs/object-glue-verification.json`.
- 0x4b79e0 (`vertrix_list_text_lookup`, the real 0x4b7710 runs inside) in `source/list_text.c` (`docs/list-text-verification.json`) and 0x4b8fbc (`vertrix_record_prefix_sum`) in `source/rtl_glue.c` (`docs/rtl-glue-verification.json`): verified.
- 0x4b6460 and 0x488b90 (`vertrix_object_destroy_d`, `_e`) in `source/object_glue.c`: verified in `docs/object-glue-verification.json`.
- 0x48a300 (`vertrix_list_text_lookup_slot`) in `source/list_text.c` and 0x477ed0 (`vertrix_object_reset_center`, the real 0x477d70 runs inside) in `source/object_glue.c`: verified in `docs/list-text-verification.json` and `docs/object-glue-verification.json`.
- 0x481480 (`vertrix_rle_decode`, PCX-style run-length decoder; eax not compared) in `source/rtl_glue.c`: verified over planned streams including the error path in `docs/rtl-glue-verification.json`.
- 0x481580 (`vertrix_rle_decode_bitmap`) in `source/rtl_glue.c`: verified over planned streams in `docs/rtl-glue-verification.json`.
- 0x4896f0, 0x489ba0 and 0x489640 (`vertrix_path_split_a`, `_b`, `_c`) in `source/rtl_glue.c`: the copy into the global buffers and every 0x4daae8 / 0x4ca370 / 0x4ca600 call compare in `docs/rtl-glue-verification.json`.
- 0x4875a0 (`vertrix_array_list_build`) in `source/array_list.c`: verified in `docs/array-list-verification.json`.
- 0x45e260 (`vertrix_table_release_everything`) in `source/table_release.c`: verified in `docs/table-release-verification.json`.
- 0x45e440 and 0x45e630 ported as vertrix_table_build_pair and vertrix_table_build_by_flag (table_release.c), verified in verify_table_release.py.
- 0x43bd80 ported as vertrix_board_view_setup_forward (board_cell_replace.c), verified in verify_board_cell_replace.py.
- 0x4d2390 ported as vertrix_rtl_scope_refresh (rtl_glue.c), verified in verify_rtl_glue.py.
- 0x4d3f70 ported as vertrix_object_destroy_f (object_glue.c), verified in verify_object_glue.py.
- 0x477e30 ported as vertrix_object_center_place (object_glue.c), verified in verify_object_glue.py.
- 0x478c40 ported as vertrix_offset_pair_clamp_call (call_glue.c), verified in verify_call_glue.py.
- 0x424760 ported as vertrix_object_center_titled (object_glue.c), verified in verify_object_glue.py.
- 0x488b10 ported as vertrix_object_construct_e (object_glue.c), verified in verify_object_glue.py.
- 0x475ec0 ported as vertrix_object_construct_f (object_glue.c), verified in verify_object_glue.py (the 0x6200-byte table object is a mapped test buffer at 0x900000).
- 0x45afe0 and 0x45cff0 ported as vertrix_actor_refresh (source/actor_refresh.c, tools/verify_actor_refresh.py, docs/actor-refresh-verification.json): 1000 complete original executions each match.
- 0x472470, 0x4724f0 and 0x472570 ported as vertrix_actor_spawn with a VertrixSpawnSpec per routine (source/actor_spawn.c, tools/verify_actor_spawn.py, docs/actor-spawn-verification.json): 300 complete original executions each match. The original writes through a null actor when 0x4ca000 returns zero; the native returns zero there.
- 0x473630, 0x4737d0 and 0x473960 ported as vertrix_pair_words and vertrix_pair_flags (source/pair_sync.c, tools/verify_pair_sync.py, docs/pair-sync-verification.json): 400 complete original executions each match. The globals read by the originals (gates, flag bytes, 0x5bd834, the two object pointers) are parameters.
- 0x473af0 ported as vertrix_pair_scan (source/pair_sync.c, verify_pair_sync.py): 400 complete original executions match; the eight probe bytes the original stores to 0x5bb594..0x5bb59b are returned through an array.
- 0x45cdc0 ported as vertrix_actor_refresh_if_active (actor_refresh.c) and 0x487b00 as vertrix_object_construct_g (object_glue.c), verified in their verifiers.
- 0x478dd0 ported as vertrix_object_describe (list_text.c), verified in verify_list_text.py.
- 0x47faf0 ported as vertrix_object_set_text (object_glue.c), verified in verify_object_glue.py with texts of 0..0x180 bytes.
- 0x4c98d0 ported as vertrix_rtl_copy_blocks (rtl_glue.c), verified unstubbed in verify_rtl_glue.py.
- 0x41d5b0 ported as vertrix_gate_dispatch_call (call_glue.c), verified in verify_call_glue.py (the original's eax is the restored exception chain and is not compared; the stored global 0x532ab4 is).
- 0x416010 ported as vertrix_notice_call (call_glue.c, tools/verify_notice.py, docs/notice-verification.json): 500 complete original executions match; it has its own verifier because 0x47f9b0 runs unstubbed in verify_call_glue.py.
- 0x4db8c0 ported as vertrix_rtl_read_into (rtl_glue.c, tools/verify_read_into.py, docs/read-into-verification.json): 1000 complete original executions match; own verifier because 0x4ca670 has an entry test in verify_rtl_glue.py.
- 0x4df884, 0x4df8a8 and 0x4df914 ported as vertrix_rtl_length_limit, vertrix_rtl_wide_byte_count and vertrix_rtl_pad_zeros (rtl_glue.c, tools/verify_far_strings.py, docs/far-strings-verification.json): 1000 complete original executions each match. The routines load es from a selector argument or from ds, so the verifier installs a flat GDT descriptor (selector 0x10) for ds, es and ss.
- 0x4d80a6 and 0x4d809c ported as vertrix_float_add and vertrix_float_subtract (rtl_glue.c, tools/verify_float_dispatch.py, docs/float-dispatch-verification.json): 1500 complete original executions each match; the jump through the pointer at 0x503ea0 is a call to the helper address passed in.
- 0x4c9b10 ported as vertrix_rtl_square_root (rtl_glue.c, tools/verify_sqrt.py, docs/sqrt-verification.json): bit exact over thousands of runs, including the rare cases where the x87 fsqrt double rounding differs from the correctly rounded root. 0x4db896 ported as vertrix_rtl_natural_log (tools/verify_ln.py, docs/ln-verification.json): within one unit in the last place of fyl2x (96% bit exact); zero is not tested because the emulator's fyl2x of zero differs from the hardware.
- 0x4d8b80 ported as vertrix_object_destroy_g (object_glue.c), verified in verify_object_glue.py.
- 0x4ca3a0 ported as vertrix_rtl_wide_assign (rtl_glue.c, tools/verify_wide_assign.py, docs/wide-assign-verification.json): 1000 complete original executions match.
- 0x48a670 ported as vertrix_object_destroy_h (object_glue.c), composing vertrix_object_unknown_reset, verified in verify_object_glue.py.
- 0x47f280 ported as vertrix_object_pick_entry (object_glue.c, tools/verify_pick_entry.py, docs/pick-entry-verification.json): 400 complete original executions match; the 16 byte local that 0x47fbb0 fills through esi is the scratch argument, written by the verifier's callee hook. Own verifier because 0x47fbb0 runs unstubbed in verify_object_glue.py.
- 0x416a80 ported as vertrix_object_load_script (list_text.c), verified in verify_list_text.py (the original's eax is the restored exception chain and is not compared).
- 0x4c0b51 ported as vertrix_object_is_idle (object_glue.c), verified unstubbed in verify_object_glue.py with both outcomes exercised.
- 0x427ae0 ported as vertrix_object_compare_regions (object_glue.c, tools/verify_regions.py, docs/regions-verification.json): 800 complete original executions match. The two 0x41 byte copies the original makes to its own locals are returned in two buffers and compared with the original's stack. Own verifier because 0x432820, 0x428110 and 0x428610 run unstubbed in verify_object_glue.py.
- 0x40ef90 ported as vertrix_object_free_tree (object_glue.c, tools/verify_free_tree.py, docs/free-tree-verification.json): 1000 complete original executions match, the register arguments of every release call included.
- 0x40f910 ported as vertrix_object_attach_item (object_glue.c, tools/verify_attach_item.py, docs/attach-item-verification.json): 1500 complete original executions match.
- 0x418170 ported as vertrix_clock_text (list_text.c), verified in verify_list_text.py.
- 0x43ab80 ported as vertrix_object_region_verdict (object_glue.c), run with 0x427ae0 executing inside it in tools/verify_regions.py: 1200 complete original executions match, all three verdicts exercised.
- 0x440ca0 ported as vertrix_object_corner_call (object_glue.c, tools/verify_corner_call.py, docs/corner-call-verification.json): 1000 complete original executions match; the unaligned stack reads of the original are the low words of its arguments, and the two result dwords of 0x4408e0 are carried in out_ebx and out_ecx of the call site.
- 0x4ab200 ported as vertrix_surface_mask32 (source/surface_mask.c, tools/verify_surface_mask.py, docs/surface-mask-verification.json): 1500 complete original executions match, with zero and wrapped 16 bit counts; the globals the original reads (surface width, source pixel pointer and skip) are arguments.
- 0x43dff0 ported as vertrix_object_populate (object_glue.c, tools/verify_populate.py, docs/populate-verification.json): 120 complete original executions (each 508 allocations) match, register arguments included.
- 0x48a560 vertrix_list_parse_values (source/list_text.c): verified in tools/verify_parse_values.py, docs/parse-values-verification.json.
- 0x48a4a0 vertrix_list_parse_texts (source/list_text.c): verified in tools/verify_parse_texts.py, docs/parse-texts-verification.json.
- 0x489d00 vertrix_rtl_text_equal (source/rtl_glue.c): verified in tools/verify_text_equal.py, docs/text-equal-verification.json.
- 0x487fd0 vertrix_list_find_name (source/list_text.c): verified in tools/verify_find_name.py, docs/find-name-verification.json.
- 0x4d8490, 0x4d8c20, 0x4df070 vertrix_node_pool_take_pair/_initialised/_quad (source/node_pool.c): verified in tools/verify_node_pool.py, docs/node-pool-verification.json.
- 0x4df160 vertrix_map_find_or_add (source/node_pool.c): verified in tools/verify_map_find.py, docs/map-find-verification.json.
- 0x4df220 vertrix_map_iterate (source/node_pool.c): verified in tools/verify_map_iterate.py, docs/map-iterate-verification.json.
- 0x4db250 vertrix_float_remainder (source/rtl_glue.c): verified in tools/verify_float_remainder.py, docs/float-remainder-verification.json.
- 0x4b4af0 vertrix_object_text_rebuild (source/list_text.c): verified in tools/verify_text_rebuild.py, docs/text-rebuild-verification.json.
- 0x4b4790 vertrix_object_text_insert (source/list_text.c): verified in tools/verify_text_insert.py, docs/text-insert-verification.json.
- 0x4b4950 vertrix_object_text_remove (source/list_text.c): verified in tools/verify_text_remove.py, docs/text-remove-verification.json.
- 0x4b6930 vertrix_object_text_value (source/list_text.c): verified in tools/verify_text_value.py, docs/text-value-verification.json.
- 0x4b46e0, 0x4b4700, 0x4b4780 vertrix_object_text_row/_nearest/_seek (source/list_text.c): verified in tools/verify_text_seek.py, docs/text-seek-verification.json.
- 0x4b45f0, 0x4b4600, 0x4b4610, 0x4b4620, 0x4b4630, 0x4b4660, 0x4b4690 vertrix_object_cursor_* (source/list_text.c): verified in tools/verify_text_seek.py, docs/text-seek-verification.json.
- 0x4d9f06 vertrix_rtl_jump_capture (source/rtl_glue.c): verified in tools/verify_jump_capture.py, docs/jump-capture-verification.json.
- 0x4c9860 vertrix_rtl_copy_rows (source/rtl_glue.c): verified in tools/verify_copy_rows.py, docs/copy-rows-verification.json.
- 0x415180 vertrix_text_table_refresh (source/text_table.c): verified in tools/verify_text_table.py, docs/text-table-verification.json.
- 0x4074a0 vertrix_bits_fill (source/bits_fill.c): verified in tools/verify_bits_fill.py, docs/bits-fill-verification.json.
- 0x407280 vertrix_bits_header (source/bits_fill.c): verified in tools/verify_bits_header.py, docs/bits-header-verification.json.
- 0x40a590 vertrix_window_tables (source/window_tables.c): verified in tools/verify_window_tables.py, docs/window-tables-verification.json.
- 0x40f1a0 vertrix_event_pack (source/event_pack.c): verified in tools/verify_event_pack.py, docs/event-pack-verification.json.
- 0x441f20 vertrix_pattern_tables (source/pattern_tables.c): verified in tools/verify_pattern_tables.py, docs/pattern-tables-verification.json.
- 0x479e50 vertrix_circle_points (source/circle_points.c): verified in tools/verify_circle_points.py, docs/circle-points-verification.json.
- 0x473cf0 vertrix_bitmap_load (source/bitmap_load.c): verified in tools/verify_bitmap_load.py, docs/bitmap-load-verification.json.
- 0x488d80 vertrix_object_kind_text (source/list_text.c): verified in tools/verify_kind_text.py, docs/kind-text-verification.json.
- 0x46f000 vertrix_letter_row (source/letter_row.c): verified in tools/verify_letter_row.py, docs/letter-row-verification.json.
- 0x46f220 vertrix_letter_row_second: verified with tools/verify_letter_row.py (docs/letter_row-verification.json).
- 0x46eda0 vertrix_letter_grid: verified with tools/verify_letter_grid.py (docs/letter-grid-verification.json).
- 0x46ea30 vertrix_letter_menu: verified with tools/verify_letter_menu.py (docs/letter-menu-verification.json).
- 0x4713d0 and 0x4715a0 vertrix_title_letter_first/_second: verified with tools/verify_title_letter.py (docs/title-letter-verification.json).
- 0x478f50 vertrix_surface_fill: verified with tools/verify_surface_fill.py (docs/surface-fill-verification.json).
- 0x4270a0 vertrix_ai_search: verified with tools/verify_ai_search.py (docs/ai-search-verification.json).
- 0x429bf0 vertrix_slot_objects_make: verified with tools/verify_slot_objects.py (docs/slot-objects-verification.json).
- 0x41ac70 and 0x4856a0 vertrix_surface_clear_second/_pair_make: verified with tools/verify_surface_clear.py (docs/surface-clear-verification.json).
- 0x4b7e80 vertrix_wave_load: verified with tools/verify_wave_load.py (docs/wave-load-verification.json).
- 0x40f360 vertrix_module_load: verified with tools/verify_module_load.py (docs/module-load-verification.json).
- 0x4b25b0 vertrix_text_wrap: verified with tools/verify_text_wrap.py (docs/text-wrap-verification.json).
- 0x4d2020 vertrix_message_dispatch: verified with tools/verify_message_dispatch.py (docs/message-dispatch-verification.json).
- 0x4df6c8 vertrix_format_spec: verified with tools/verify_format_spec.py (docs/format-spec-verification.json); the real 0x4df81c runs inside.
- 0x4dae1e vertrix_float_split: verified with tools/verify_float_split.py (docs/float-split-verification.json).
- 0x4daed8 vertrix_float_exp: verified with tools/verify_float_exp.py (docs/float-exp-verification.json).
- 0x4c9921 vertrix_float_power: verified with tools/verify_float_power.py (docs/float-power-verification.json).
- `0x4da6b6` exception chain step: `source/exception_chain.c`, verified by `tools/verify_exception_chain.py` (4096 complete original executions, callee registers, locals and record compared); evidence `docs/exception-chain-verification.json`.
- `source/game_session.c`, `source/game_render.c`, `tools/wii_game.c`: playable single board for the Wii built from the recovered routines (`make wii-game`, `wii-game/`, `docs/WII-GAME.md`); verified by running in Dolphin, not on hardware.
- `source/wii_game_art.c`, `source/game_art.h`, reworked `source/game_render.c`: the board screen now uses the original decor (JPEG), masked head, panel layout and fonts; see `docs/WII-GAME.md`.
- `source/wii_input.c`: merged Wii Remote / Classic / GameCube input with the original key bindings and no auto-repeat (key delay NONE).
- `vertrix_title_render` and the title menu in `tools/wii_game.c`: original title decor and menu layout; 1PLAYER and EXIT work, 2PLAYERS and OPTIONS do not yet.
- `tools/wii_game.c`: original XM music (Intro on the title, Doc on the board) through the recovered sequencer and `wii_music.c`; sound effects not wired.
- `0x434ee0` figure pass: `vertrix_figure_pass` in `source/match.c`, verified by `tools/verify_figure_pass.py` (16,000 complete original executions: eax, reward word, mask). This found and fixed a bug in the earlier `match_board`: the original checks the fifth figure shape before the fourth, which changes which overlapping weight-four figure earns its reward (about 0.3% of dense boards; the mask was always identical). Evidence: `docs/figure-pass-verification.json`.
- `0x4270a0` computer-player figure search: `vertrix_ai_search_native` in `source/ai_player.c` (scoring call `0x434ee0` done natively with `vertrix_figure_pass`), verified by `tools/verify_ai_player.py` against the complete original with every callee executing for real (4,096 runs, 830 finding a figure). Evidence: `docs/ai-player-verification.json`.
- 0x426240 (computer player's fallback column/rotation search): recovered in source/ai_player.c as vertrix_ai_fallback; 4,096 complete original executions (draws from 0x4826c0 stubbed and replayed with divisors checked) match the column, rotation and remembered column (docs/ai-fallback-verification.json).
- 0x4346b0 (line pass) split out of match_board as vertrix_line_pass (8,000 complete original executions, docs/line-pass-verification.json); 0x432980 byte-board collapse checked against board_collapse (8,000, docs/board-collapse-bytes-verification.json); 0x4269e0 (computer player's chain search) recovered as vertrix_ai_chain_search in source/ai_player.c (3,000 complete original executions, docs/ai-chain-verification.json).
- 0x427380 (computer player's bomb search, with the 0x434300/0x4344e0 blast estimates done natively; pattern 5 and above blast nothing) recovered as vertrix_ai_bomb_search in source/ai_player.c; 3,000 complete original executions (docs/ai-bomb-verification.json).
- Computer player planner 0x425f60 and steering 0x43ae20..0x43b194 read from the executable and written as vertrix_ai_plan / vertrix_ai_steer (source/ai_player.c). The four searches it calls are each verified against the original (figure 0x4270a0, chain 0x4269e0, bomb 0x427380, fallback 0x426240); the composition and the key choice are not run as a whole in the oracle. Keys: player +0x160 left, +0x162 right, +0x164 permute, +0x166 down; 0x431380 is the fast-drop flag. Not yet recovered: the reaction timer (0x43b5b0 / 0x4ac7d0, table 0x544f90), the opponent board and what its clears do to the player's board.
- 0x43b5b0 (computer player's reaction time; tables 0x4f8d38/0x4f8d84/0x4f8dac for the three difficulties) recovered as vertrix_ai_reaction_time in source/ai_timing.c; 2,000 complete original executions (docs/ai-timing-verification.json).
- wii_game: all 18 characters of HeadFileName.ini load their own decor, head, blocks and music (title Left/Right steps through them, a stand-in for the unrecovered character screen). Checked in Dolphin for the first six; base head file names differ per character (trailing underscore, head_bill, _-001 frames).
- Heads are drawn by their HeadFileName.ini centre (anchor taken from Doc's known placement, an assumption); checked in Dolphin across the first 11 characters.
- Sound effects (not recovered): the effect files and names are in SfxFileName.ini/SfxInfo.ini (FX01..FX19, NAME/LAUGH/DOO per character); the loader of SfxInfo.ini is 0x413bd0 (fills globals from 0x532d8c); the options screen builder (0x461fc0, strings "VOL. SFX", "TEST SFX", "SWITCH SFX") only lays out labels. 0x4761d0/0x476280 act on the input table at 0x54d640 (key/joystick state, 0x7d00 is the axis centre), not on audio, and 0x4b2380/0x4b23c0 are virtual-dispatch loops. The routine that plays an effect on lock, clear or chain, and the event-to-effect index mapping, are still to be found; no mapping is guessed in the Wii build.
- Reference screenshot from the user (two-player game, Regis against Glouk, Glouk's decor, 4:3): a wooden title bar across the top with each player's name and an eight-digit score; a LEVEL / SPEED medallion pair above each board (mirrored for the right player); a three-block next-piece strip beside each board's outer edge with a brown tube cap under it; a framed tube bar (progress gauge) down the outer edge; bonus icon columns on both outer sides (icons come from image/systeme/Bonus.bmp, bonus-slot squares as grey boxes); each player's head on the outer side; the two boards in the middle, 5 x 13 cells, translucent with a brown frame. Board position agrees with the single-player layout already used (x about 183, y about 131 on a 640 x 480 frame). The one-player arrangement of the other elements is not known from this image.
- docs/HUD-LAYOUT.md and docs/game-screen-constructor-annotated.txt: the game-screen constructor 0x46c9d0 and its layout table at 0x4f8960..0x4f8c50 located; first objects decoded.
- game_render: the next-piece strip is drawn where the executable's table puts it (x 144, y 69, 18 x 18 cells, scaled from the 24 x 24 blocks); first HUD element moved from a guess to a decoded position. Checked in Dolphin.
- Filter items decoded: 0x4121e0 loads Filtre/*.flt, 0x4123d0 applies an item to an actor's effect fields (docs/HUD-LAYOUT.md).

Recovered the game-screen HUD scene: the original builder 0x46b810 is executed unchanged in the oracle (tools/gen_hud_layout.py) and yields the 120 damier pieces with position, frame (+0xb8) and filter item in draw order (source/hud_layout.c). source/hud_draw.c draws them through the recovered actor renderer with each character's Filtre file, composed into the decor at load (source/wii_game_art.c). Board origin (186,130)/(334,130) and the 120x312 clip come from 0x43aab0/0x42ff10. Host render checked against the Dolphin build for Regis and Glouk. Not verified against a reference screenshot: the original draw order of dynamic text over the pieces, the exact name text and the speed medallion value.
- `0x429000` / `0x4290a0` AI candidate slot selection and rotation count store: recovered in `source/ai_piece_choice.c` (`vertrix_ai_find_best_slot` / `vertrix_ai_choose_piece_rotation`), verified by `tools/verify_ai_piece_choice.py` against `Vertrix2.exe` Unicorn x86 across 4,096 complete original executions. Preserves signed `int8_t` score comparisons, tie-breaking via static block-kind priority table at `0x4f9318`, and randomized draw fallback `0x4826c0` (`random(2)`). Evidence: `docs/ai-piece-choice-verification.json`, notes: `docs/AI-PIECE-CHOICE.md`.
- `0x482e10` / `0x482e80` / `0x482f00` event frame draw dispatchers: recovered in `source/event_frame_draw.c` (`vertrix_event_frame_draw_direct`, `vertrix_event_frame_draw_blend`, `vertrix_event_frame_draw_scaled`), verified by `tools/verify_event_frame_draw.py` across 12,288 complete original executions against `Vertrix2.exe` Unicorn x86. Prepares 28-byte event record from item descriptor (+0, +4, +8, +0x27), invokes key-index mapper `0x478cd0` and field scaler `0x478da0`, and dispatches to draw callback `0x47ce10`, blend callback `0x47c930`, or scaled callback `0x47cb40`. Evidence: `docs/event-frame-draw-verification.json`, notes: `docs/EVENT-FRAME-DRAW.md`.
- `0x4174f0` / `0x417550` / `0x43c0e0` / `0x43c110` SFX channel allocation and event dispatch: recovered in `source/sfx_dispatch.c` (`vertrix_sfx_allocate_channel_p1`, `vertrix_sfx_allocate_channel_p2`, `vertrix_sfx_dispatch_event`, `vertrix_sfx_dispatch_secondary`), verified by `tools/verify_sfx_dispatch.py` across 8,224 complete original executions against `Vertrix2.exe` Unicorn x86. Dedicated 4-channel voice partitions (channels 0..3 for Player 1, 4..7 for Player 2), sentinel `0xf4240` filtering, and side routing to voice handlers (`0x417260`/`0x417290`). Evidence: `docs/sfx-dispatch-verification.json`, notes: `docs/SFX-DISPATCH.md`.
- `0x43b430` player AI tick routine: recovered in `source/player_ai_tick.c` (`vertrix_player_ai_tick`), verified by `tools/verify_player_ai_tick.py` across 4,096 complete original executions against `Vertrix2.exe` Unicorn x86. Coordinates AI phase evaluation (`0x427850`, `0x42b090`, `0x4290a0`, `0x4ac510`, `0x43b680`, `0x4ac7d0`), timer step checking (`0x4ac500`/`0x4ac520`), rotation decrements, permute key generation (`player + 0x164`), and drop key injection (`player + 0x166`). Evidence: `docs/player-ai-tick-verification.json`, notes: `docs/PLAYER-AI-TICK.md`.

- `0x410270` S3M pattern converter: recovered in `source/s3m_pattern.c` (`vertrix_s3m_pattern`), verified by `tools/verify_s3m_pattern.py` across 4,096 complete original executions against `Vertrix2.exe` Unicorn x86. Converts the packed S3M rows into XM-style packed rows: channel map `0x5324dc`, note/volume conversion, effect memory for `"DEFGKLQ"` (`0x50c80c` through `0x4ec1d0`), letter translation tables `0x4101d8` / `0x410244`, row buffer `0x53207c` and parameter memory `0x53211c`. Served from the lifted dispatcher as a native port (the batch lift of 0x410270 failed verification); half of the cases exercise the globals reader / 0xf0000000 store path the lifted host uses. The old handoff's "file-loader / sample block allocator" label was wrong. Evidence: `docs/s3m-pattern-verification.json`, notes: `docs/S3M-PATTERN.md`.
