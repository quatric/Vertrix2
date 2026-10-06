# Game-screen HUD layout (recovered from the executable)

The game screen is built by one routine, `0x46c9d0` (to `0x46e6aa`), called from `0x46cb19` /
`0x46e6b6`. It creates the two players (class constructor `0x43a6f0`, which also builds the board
`0x42e870`, the computer-player object `0x425e20` and the helpers at `+0x468`/`+0x46c`) and then
about 34 HUD objects (allocations through `0x4ca000`; constructors `0x429880`, `0x43d3f0`, ...).
Every position and size comes from a table of 32-bit values at `0x4f8960..0x4f8c50` in the data
section, read by the code as an unaligned dword two bytes in and shifted right by 16 (so the
value is the table entry at address + 2). `docs/game-screen-constructor-annotated.txt` is the
disassembly of the routine with every table read resolved to its value.

Decoded so far:

| Object | Constructor | Table entries | Position / size |
| --- | --- | --- | --- |
| Player 1 bonus slot (id 3, side 1) | `0x429880` | `0x4f8abe`, `0x4f8ac2`, `0x4f8ac8`, `0x4f8acc` | x 3, y 274, 32 x 26 |
| Player 2 bonus slot (id 4, side 2) | `0x429880` | `0x4f8ace`, `0x4f8ad2`, `0x4f8ad8`, `0x4f8adc` | x 517, y 274, 32 x 26 |
| Object id 0xb (frame list at `0x4f8a10`..) | `0x43d3f0` | `0x4f8a10..0x4f8a1c` | x 59, y 34, 186 x 81 region |

The remaining objects (levels, speeds, name bar, next strips, tube bars, heads, bonus columns) read
the other entries of the same table; they are still to be decoded one by one from the annotated
listing. Nothing in the Wii HUD is placed by estimate once this table is decoded.

## Positions read from the table (640 x 480 frame)

Every number below is a value in the executable's table; the role column is only the object kind
the constructor creates (`[object] = id`), checked against the reference two-player screenshot.

| Object id | Position (x, y) | Size / second point | Notes |
| --- | --- | --- | --- |
| 3 (player 1 bonus slot) | 3, 274 | 32 x 26 | constructor `0x429880`, side 1 |
| 4 (player 2 bonus slot) | 517, 274 | 32 x 26 | side 2 |
| 0xb, 0xa, 0xc, ... (`0x43d3f0` objects) | origin (59, 34); points (186, 81), (247, 81), (334, 81), (395, 81), (239, 30), (401, 30), (186, 130), (334, 130) | | level / speed medallion positions of the two players (entries `0x4f8a10..0x4f8a5e`) |
| 7, 8 | 184, 9 and 332, 9 | 124 x 16 | the name and score fields of the top bar (one per player) |
| 5, 6 | 144, 69 and 478, 69 | 18 x 18 cells | next-piece strips |
| 0xf, 0x10 | 139, 136 and 473, 136 | 28 x 28 | tube caps under the next strips |
| 0x11, 0x12 | 310, 217 and 326, 217 | | objects at the centre gap between the boards |
| 0x17, 0x18 and the two 12 x 12 groups | (155, 251) and (471, 251) | | tube bars down the outer edges |

Entries still to be decoded: `0x4f8b2e..0x4f8c44` (two 14-entry rows of x positions 269..434 and
472, y 156..), the head positions and the bonus column cells.

## Frame pieces and their per-character look

`sprite/damier.spr` holds 47 frames (count word, then a 48-byte header and w x h RGBA per frame):
the HUD panels are drawn from them. Dimensions seen: 0: 140x384 (board panel with a divider bar),
2: 144x388, 3/5: 150x21, 4/6: 158x31 (top bars), 7: 26x62, 9: 18x206, 13: 34x76, 15: 59x34 (the
medallion), 16/17: 24x24, 24: 38x324 (tube), 28/30/31: 16x206 (tube bars), 41/42: 164x31 and
144x31, 43/44: 148x21 and 128x21, 45/46: 316x27 and 314x25 (the wide top bar), plus small bead and
circle frames (20..22 carry the LEVEL / SPEED text). The frames are grey metal and flat blue; the
brown wood of the reference screenshot is not in them.

`Filtre/<Character>.flt` (`FiltreFileName.ini`, one file per character, 20 entries) is the per
character look: 1472 bytes = an 8-byte header (`00 01 32 08`, then the item count 0x7a = 122)
followed by 122 items of 12 bytes (`01 type amount 00 s16 s16-ish 0d 02 ...`), two items per
entry (61 entries). The executable's filter class is `CXFiltre` (strings "Filtre", "Type",
"Rotation", "Valeur" in the editor routines near `0x420b31` and `0x42183d`), so each item is a
type / rotation / value triple applied to a frame. The loader and the effect that turns the grey
frames into the character's wood or metal are the next thing to recover.

## Filter items (`Filtre/*.flt`) and how they reach the frames

The file is read by `0x4121e0` into a 0x7b8-byte filter object (the global at `0x532928`, created
at `0x420111`): the 8-byte header goes to +0x5b8 (the count dword at +0x5bc is 0x7a) and the items,
12 bytes each, fill the start of the object (122 x 12 = 0x5b8). `0x4123d0(object, index, actor)`
copies one item into a sprite actor, which is how the screen constructor styles its frames:

| Item byte(s) | Actor field | Range the editor allows | Meaning (from the recovered renderer) |
| --- | --- | --- | --- |
| +0 | +0x93 | 0..1 | draw flag |
| +1 | +0x95 | 0..10 | effect (1 and 3 half blend, 4 saturating add, 5/6 subtract, 7/8 invert) |
| +2 | +0x4e | 0..100 | amount in percent |
| +4 (word) | +0x48 | up to +/-200 | palette offset |
| +6 | +0x52 | 0..13 | colour bank index |
| +7 | +0x94 | 0..2 | |
| +8 | +0x8c | 0..1 | cycle flag |
| +0xa (word) | +0x80 | 0..254 | |

So the per-character wood and metal look is a set of actor effect settings applied to the grey
`damier.spr` frames with the effect renderer already recovered (`actor_render_draw`, effects
1/3..8, colour banks, palette shifts). The board panel itself is styled directly in the
constructor (`0x46ced1`): offset 0xff9c (-100), amount 0x32 (50), draw flag 1, effect 4. The
filter data therefore replaces guessing: wiring the Wii HUD means preparing the renderer's
weights, colour bank and palette tables and drawing each frame through `actor_render_draw32`.

## Filter indices of the frame groups

The four-iteration loop at `0x46cd79..0x46ce80` (one group of damier frames of the level / speed
area, each iteration adding a frame to the chain through `0x4b5700` and styling it with
`0x4123d0`) takes its filter item from the table at `0x4fd608`:
(36, 110, 114, 118), (38, 112, 116, 120), (37, 111, 115, 119), (39, 113, 117, 121). The frame
indices come from the run-time table at `0x54682d` (zero in the file image, filled at start-up), so
the start-up routine that fills it is the next thing to read.

The four frame indices are the bytes at `0x4f9c06..0x4f9c09` (copied to `0x546830..0x546833` by the
routine ending at `0x45f6c0`): damier frames 4, 16, 17 and 18 (the 158 x 31 pill, the 24 x 24 blue
and grey squares and the 41 x 11 text frame). Each of the four iterations binds one of them to a
chain element covering the rectangle read from `0x4f8a10..`, styled by the filter items above.

## Host probe of the recovered effect renderer on a damier frame

`tools/hud_frame_probe.py.txt` (a scratch probe, kept as text because the older verifier modules it
would import are damaged; it declares the structures itself) draws processed `damier.spr` frames
through `vertrix_actor_render_draw32` onto Glouk's decor using filter items 36 / 110 / 114 / 118
from `Filtre/Glouk.flt`. The call dispatches (status 1) but changes only about 56 pixels:
frame 4 (158 x 31) is mostly alpha-0 pixels (3,166 of 4,898, value `f5 18 00 00`) with a grey
rim, and item 36 is effect 0, amount 0x32, offset 10, byte7 2. Nothing wood-coloured appears, so
the brown frames of the reference screenshot do not come from these items alone; the colour
bank / hue path (byte 6, byte 7 and the `0xf5 0x18` marker pixels) still needs its meaning
recovered before the frames can be reproduced.


## Recovered game-screen scene (supersedes the guesses above)

Corrections: the byte passed in `bl` to `0x4b5700` (4, 16, 17, 18 and 6) is not a damier frame
index. `0x4b5700` / `0x4b65d0` build the 0x194-byte text elements of the level and speed medallions
and the name / score fields (the rectangle arguments are the field bounds, for example
(186, 81)-(244, 114) and (184, 9)-(307, 24)); the filter items 36 / 110 / 114 / 118 and 40 / 41 style
those text elements. The earlier probe also drew every frame at one sixteenth of its size because
the actor's scale byte (+0x44) is 16 for 100 %, not 1; that, and not a missing colour bank, is why
the frames looked empty.

The damier pieces are created by the routine at `0x46b810` (called from `0x46b806` and `0x46c5de`),
which calls `0x471100(x, y, item, frame, filter, selected)` 120 times. Each call checks the item's
enable word (`0x4126f0`, filter object +0x5cc + 4 * item), allocates a 0x15c-byte actor, places it
with `0x4710d0` (+0xb8 = damier frame, +0x8e = 0, +0x8f = 1) and styles it with `0x4123d0`.
`tools/gen_hud_layout.py` executes the routine unchanged in the Unicorn oracle (only allocation, the
actor constructor and the chain insert are stubbed) and writes the creation (= draw) order,
position, damier frame and filter item of every piece to `source/hud_layout.c`. The frame bank is
`sprite/damier.spr` with the 0x45dd52 substitutions (1 = mirror of 0, 10 of 9, 12 of 11, 25 of 24,
29 of 28), loaded by `vertrix_ui_sprite_bank_load`.

`source/hud_draw.c` draws that list through `vertrix_actor_render_draw32` with the weights, palette
tables and colour bank of the recovered renderer (`vertrix_render_color_bank_build` with the
percentage row 100). Because the renderer works on 0x00RRGGBB dwords the Wii build swaps the red
and blue bytes of the decor around the call (`compose_hud` in `source/wii_game_art.c`) and draws the
whole HUD once when a character is loaded. Rendering the result with each character's own
`Filtre/*.flt` gives that character's look: Regis turns the grey metal copper through effects 9 / 10
and bank 2, Glouk stays stone grey.

Board geometry read from the executable: the player origin is set by `0x43aab0` from the words
`0x4f8a48/4c` = (186, 130) for player 1 and `0x4f8a50/54` = (334, 130) for player 2, and the clip
`0x42ff10` is origin .. origin + (0x77, 0x137) = 120 x 312 (5 columns x 13 rows of 24 pixels).
Score field (184, 9), level medallion (186, 81), speed medallion (247, 81) and the next strip
(cells centred at x 153, y 78 + 18 k) come from the same tables.

Confirmation that the builder is the in-game HUD: the match routine at `0x424360` loads the two
players' filter files (`0x4122f0`, names from the table at `0x534750`), stores the first in the
global `0x532928`, calls `0x46b800` (which runs `0x46b810`) and then the game constructor
`0x46c9d0` at `0x42459b`. Note that the second filter object is a separate file (player 2's
character); the Wii build draws all pieces with the selected character's file until versus exists.

## Scene flow notes (title / menus), partly recovered

The screens are states of a scene machine at `0x41b5e0`..`0x41d5b0`. Each state function rebuilds
the scene (`0x41c020` or the large builder `0x41c410`), installs the common per-frame handler
(`0x421f10` or `0x423960`) through `0x418840` and names the next state through `0x418820`:
`0x41c0c0 -> 0x41c390`, `0x41c0f0 -> 0x41b680`, `0x41c160 -> 0x41f080` (the `Story.jpg`
opponent page, text built by `0x46ea30`), `0x41c1d0/0x41c240/0x41c2b0 -> 0x41c6d0`,
`0x41c6d0/0x41c740 -> 0x41c7b0`, `0x41cc30 -> 0x41d0e0 / 0x41b5e0`, `0x41d410 -> 0x424230 ->
0x424360` (the match routine). `0x420040` / `0x420f10` allocate 0x7b8-byte filter objects (the
filter editor), and `0x46eda0` / `0x46f440` / `0x470960` build text tables, not menus.
`0x41c410` calls `0x465af0` and `0x466d60`; running `0x465af0` in the oracle creates 131 text
glyph actors plus four 0x15c actors at (64,142), (59,137), (585,142), (580,137) on the resource
at `0x544a18` (probably the left / right arrows), so it is a selection screen. Positions of the
glyph actors are set by routines the oracle run stubs; recovering them is still open.

### Builder `0x465af0` (run with the position setters 0x4b54d0 / 0x4b5400 / 0x4ac4e0 executed)

`tools/oracle_scene_trace.py.txt` (scratch tracer kept as text) executes a builder in the oracle with
only allocation, constructors and the chain insert stubbed. For `0x465af0` it yields: 34 text rows
of 640 x 1 at y = 1..34; two portrait boxes 106 x 116 at (121, 77) and (413, 77) (filter items with
colour banks 8 and 11); three bars 398 x 56 at x = 121, y = 241 / 310 / 379; and two grids of 20 x 20
cells, four columns at x = 6 / 34 / 62 / 90 (left) and 530 / 558 / 586 / 614 (right), rows every 28
pixels from y = 244. This is the screen with two opponents' portraits and bonus-slot grids, so it
is the pre-match / bonus selection page, not the main menu. The main menu is still to be found.

`0x41b130` is the start-up state: it initialises the video and sound services (`0x471a70..0x471b70`,
`0x4854a0`, `0x485520`), loads the options with `0x461360`, installs the scene handler `0x41b820`
and returns to the scene machine. `0x461360`, `0x4633b0` and `0x4651b0` are therefore configuration
loaders, which is why running them creates no actors. The first interactive scene is the handler
reached from `0x41b820`; reading that handler is the next step towards the title screen.

Correction to the `0x465af0` note: `0x41b820` re-initialises the video and sound services, then moves to
state `0x41c240`, whose next handler `0x41c6d0` runs the large builder `0x41c410`; that builder
calls `0x465af0` and `0x466d60` and the picture list names `Selectp.jpg` as the character-choice
image. The two 106 x 116 boxes and the two 4-column grids of 20 x 20 cells (28 slots per side, more
than the 18 characters plus specials) are therefore best read as the **character-select screen**
(a portrait for each player and a slot grid for each side), not a bonus page. The grid cells still
need their frames, which come from the `select.spr` sprites (89 x 105 and 34 x 30 frames).

## Tube-cell glow (0x4831b0)

`vertrix_font_stencil` (source/font_stencil.c, already verified in the font-bank work) reproduces the routine that builds the tube-cell
beads: each opaque pixel of the shape (damier frame 34) stamps the opaque-pixel mask of the
brush (Circle.spr frame 9) onto a canvas padded by half the brush on each side; counts become
opaque gray (clamped to 255); with flag 0 the canvas alpha under the shape is cleared.
Verified earlier against the original with the font-bank verifier. The cells themselves
(handler 0x450a10, resources 0x546618 lit / 0x546634 unlit) follow the level counter and are
drawn in the port (see "Tube in the port").

## Sound-effect triggers (oracle-free static trace)

Play path: `0x43c0e0(eax=player, edx=enum)` (skips enum `[0x4f81cc]`, player word 1 or 2) ->
`0x417260` / `0x417290` -> channel = first idle of the player's bank (`0x4174f0` / `0x417550`,
idle test `0x4828a0`) -> `0x482a60(channel, samples[enum], volume [0x532b9c])`.
Enum k is sample k (see RECOVERY.md). All 72 callers of `0x43c0e0` found by
`/Volumes/SSD/larsen/claude-tmp/sfxcalls.py` (scratch):
- bonus effects `0x450ff0..0x456033`: explosion(1), implosion(12), particules(11),
  laser down/up(5/6), push up(2), attention(3), phiit(9), little ploc(7), bip up(4)
- `0x43b720` (progress add/win check): excellent(13) when the limit `[0x532b34]` is reached
- `0x43b9c0` (counter at +0x180, starts at 12 = the twelve tube cells; step down by edx, when
  below 1 it refills by 12 and plays enum `[0x4f8190]` = 4 bip up)
- `0x44ee20`: alerte(8)
No call site plays big ploc (0) from board code, so landing and clearing blocks are silent
apart from these; the one-player port therefore has no per-event effects to add besides the
ones driven by the bonus system and the +0x180 gauge.

## Gauge, tube and bonus-timer findings (static trace)

- `+0x180` (starts 12) is the level counter already ported as `session->level_counter`:
  `0x43b9c0` subtracts the cleared-line reward (`0x432480` output) and, below 1, refills by 12
  and plays bip up; the callers are the clear handlers `0x4517c0`, `0x451920`, `0x451bxx`.
  `+0x184` counts successive matches (sounds at 3 and 6), `+0x188` sums rewards.
- Tube cells (`0x450a10`, built in `0x46e0f0..0x46e2d7`): cell `+4` = 0x17 (lookup id of the
  controller), `+0x58` = cell number 1..12, `+0x7c` = mode (0 / 1 toggled by `0x450c80`).
  A cell shows once the controller's `+0x64` reaches its number and the controller's `+0x58`
  decides which cell flashes lit (`0x546618`); otherwise the unlit sprite (`0x546634`).
- The bar `+0x4e0` of a player (get `0x43b870`, set `0x43b860`) is NOT the level gauge: it is
  `bonus.+0xbc * [0x4f89ac] / bonus.+0xc0`, a bonus-timer fill in pixels, eased toward by
  `0x450d40` (`+0x58` moves by the step toward the target, sets the clip rectangle
  `+0xa8..+0xae`). Bar geometry constants `[0x4f89a8]`, `[0x4f89ac]` are still to be read.
- Not yet recovered: the identity and writers of the controller `+0x64`; this needs the scene
  run in the oracle (as done for the HUD) rather than static reading.

## Tube cells = the level counter (resolved by static trace + ctor trace)

- Controller (built at `0x46df85`, handler `0x450750`): `+0x64` is the displayed level counter
  (starts 12), target `+0x70` = player `+0x180`. Each tick `+0x64` steps down by 1 while above
  the target; while the player's refill flag `+0x3ac` is set the target is 0 and when reached
  the counter jumps back to 12 (`0x4507e0`) and the flag clears.
- Cell k (1..12, `+0x58`) is lit while `+0x64 >= k`; when `+0x64 < k` its handler `0x450a10`
  starts the extinguish animation (`0x450aa0`: swap to the unlit sprite `0x546634`).
  So the gauge drains from the bottom cell (k = 12) upward.
- Cell positions (dwords at `0x4f8b88` x, `0x4f8bb8` y): x = 156 (P1) / 472 (P2),
  y = 269 + 15 (k - 1); size 12 x 12 (`0x4f8c48/4c`); each cell actor uses resource `0x546618`
  with draw flag 1 and effect 4 (`0x46e2dc`), plus a companion object from `0x471100`.
- Sprites: `0x546618` = `vertrix_font_stencil(damier frame [0x4fbfac], Circle.spr frame 9, solid 1)`,
  `0x546634` = same with flag 0 (`0x45e490`).
- Not yet reproduced: the colouring from effect 4 and the extinguish animation timing;
  these must be traced through the actor renderer before the cells are drawn in the port.

## Tube in the port

The unspent beads are the frame-32 rail pieces of the layout (items 52..63). The loop at 0x46dfea
adds, per bead k and per player (ids 0x17 and 0x18, tables 0x4f8b88.. / 0x4f8be8..), a companion
piece (damier frame 34, filter item 64 + k, handlers 0x450860..) and a glow cell (resource
0x546618, draw flag 1, effect 4, handlers 0x450a10..); both stay invisible (+0x134 = 0) until
the shown counter drops below k + 1. `source/gauge_tube.c` holds the twelve pairs and advances
them with the already verified handlers (`linked_movement`, `linked_alternating`); the controller
flag +0x58 is one in its phase 2 only. `tools/verify_gauge_tube.py` compares the pairs with the
original handlers frame by frame (1200 frames: drops, refill with flag, drop again): 0 mismatches.
`vertrix_hud_tube_draw` draws companion then cell per bead, the cell as the stencil sprite
(`vertrix_font_stencil` of damier frame 34 with Circle.spr frame 9; solid 1 for 0x546618, 0 for
0x546634) through the recovered actor renderer with the word +0x48 = the cell's effect. Rendered
frames match the reference screenshot: gray rail beads above, spent beads falling from y 252 and
settling pink/blue at the bottom. `vertrix_session_gauge` follows the controller (one step per
150 ms toward the level counter, after a wrap drain to 0, wait 1000 ms, jump to 12, wait 1000
ms) and then advances the tube. Frame pixels are little-endian dwords, so the stencil is run on
explicitly loaded LE dwords. The draw order against the head is not recovered.

## Title scene inputs (static findings, not yet a port)

`texte/PictureFileName.ini` rows 0..2 are the intro: `Main_Screen.jpg` (picture, 640 x 480),
`Main_Screen.pcx` (foreground mask: pixels that cover the stars) and `Intro_Stars.pcx` (sparse
dots marking where stars sit; they show only where the foreground mask is background). Row 3 is
`Selectp.jpg` (character choice). None of these images contains the menu: the 1PLAYER / 2PLAYERS /
OPTIONS / EXIT boxes in `vertrix_title_render` are a stand-in (their colours and positions are not
from the executable) until the title scene builder is traced through the oracle. Related sprites:
star.spr, bigstar.spr (stars), select.spr, mousea.spr / mousec.spr (cursors), Oeil1/2.spr.

Scene order found while tracing the title: `0x41b820` -> `0x41c240` -> `0x41c6d0` -> `0x41c410`
(the large builder with `0x465af0` / `0x466d60`, the `Selectp.jpg` screen) is the first
interactive scene after the logo states (`0x41a680..0x41a800`, pictures 5 and 6 of
PictureFileName.ini). `0x424360` is the match start (it runs `0x46c9d0`, `0x46b800`).
A separate 1PLAYER / 2PLAYERS / OPTIONS / EXIT page has not been found in this chain, so the
original may go from the intro straight to the character screen; the port's four-item menu
remains an unverified stand-in.

### Builder `0x466d60` (oracle, same tracer; select-screen objects, resource `0x544a18` = select.spr)

Per side the builder makes a portrait box (frame 16, effect 5, amount 50, handler `0x44a610`) at
(121, 77) left / (413, 77) right, a row of frame objects at y = 197 (left x = 121 frame 1, 157
frame 3, 193 frame 5; right x = 413 frame 7, 449 frame 9, 485 frame 11; centre x = 240 frame 13,
294 frame 15, 348 frame 17), two 0x16c-byte panels at (4, 242) and (528, 242) (handlers `0x44a570`
and `0x44a5c0`), nine 0x180-byte companions with handlers `0x44aec0..0x44b980` (effect 1,
amount 90), and two 0x160-byte objects at (148, 457) and (374, 457) (handlers `0x44bac0`,
`0x44bb30`). Positions and frames are exact, but the behaviour (which portrait shows, how the
cursor moves, how the choice is committed) lives in those handlers and has not been recovered, so
the select screen is not ported yet; the port still steps characters with the d-pad.

Select-screen handlers read so far: `0x44a570` / `0x44a5c0` redraw a panel (`0x4adfe0`) whenever
the chosen character changes, reading the globals `[0x532a68]` (player 1) and `[0x532a6c]`
(player 2); `0x44a610` is a decorative bob: every 100 + random ticks the object's `+0x48`
offset steps by one between -4 and 8 (random direction). `[0x532a80]` = 1 marks the two-player
selection. The cursor and commit logic starts at `0x44a720` (large, with `0x418110` and
`0x4b6700` checks) and is not recovered.

`0x44a720` (read statically) is the per-slot button handler of the select screen and the screen is
pointer driven: `0x4b66c0` hit-tests the pointer (`[0x558944]`, `[0x558946]`, 0x7d00 when
absent) against the slot, `0x476480(0x54d640, 0x74)` is the click state, hovering plays enum
`[0x4f818c]` (attention) through `0x417260` / `0x417290` (once per player when a slot is not yet
taken: flags `[eax*4 + 0x5344a4]` player 1 and `[eax*4 + 0x5344f0]` player 2, mode
`[0x532a80]`), a hovered or taken slot switches colour bank 1 or 13 with effect 0 or 1 (the
"taken" look), and a click installs `0x44ab50` / `0x44abe0` (selected: effect 3, amount 100,
scale 16, sound enum `[0x4f819c]`, and `[0x532a9c]` = 1 to commit). Mapping to the Wii: the
Wiimote pointer takes the place of the mouse; the commit state machine still needs the callees
`0x44ab00..0x44abe0` read before it can be ported.

Commit chain read from `0x44aa20..0x44acfe`: `0x44ab00` waits on the click state (`0x476480`
key 0x74) and returns to the idle button `0x44aa20`; the idle button blinks `+0x4a` between 0 and
0x23 (`0x44aa90`) with range 5; a click runs `0x44ab50` (effect 3, amount 100, scale 16, plays enum
`[0x4f819c]` = little ploc on channels 0 and 4) then `0x44abe0`, which steers the slot toward its
target with `0x4b65a0` / `0x4b6540` at speed 10 and, when `0x4b6560` reports arrival, goes to
`0x44ae80` (or `0x44acd0` when `[0x532a7c]` = 1: scale 0, amount 100, then a shrink to `+0x46` =
1) and calls `0x48c310` on `0x5bb254` once a one- or two-player selection is complete. The
remaining states from `0x44acd0` onward are unread.

Further commit states (`0x44acd0..0x44b050`, skim): the two blink states `0x44ad20` / `0x44add0`
alternate `+0x4a` = 0 / 0x23 and, when a `0x418110` check passes, write the selection-done flag
`[0x532a50]`; `0x44ae80` also writes it; the following state (`0x44aed0`) builds the object
for the chosen character `[0x532a68]` (`-1` = none), waits with the timers `+0xdc/+0xe0` and
hands the choice to `0x43abd0`. `[0x532a50]`, `[0x532a68]`, `[0x532a6c]`, `[0x532a7c]` and
`[0x532a80]` are therefore the select screen's output registers (done, player 1, player 2,
slot mode, two-player flag) that the match start `0x424360` consumes.

## Game options and the race rule (static trace)

The start-game states (`0x41bbe0..0x41bd80`) copy four option globals into the match: `[0x532b54]`
-> difficulty `[0x532bbc]` (choices 0, 1, 2 at `0x4f80e4`), `[0x532b58]` -> `[0x532bc0]` (ten choices
0..9 at `0x4f80f0`), `[0x532b5c]` -> `[0x532bc4]` (0 or 1 at `0x4f8118`) and `[0x532b60]` -> mode
`[0x532bc8]` (0 or 1 at `0x4f8120`). The OPTIONS page therefore is four radio groups with 3, 10, 2 and
2 choices (`0x416b30..0x416bb0` set each from its group with `0x415eb0`).
Mode 1 is the race: `0x43b720` adds to the player's progress `+0x178` every time the level counter
wraps (`0x43b9c0` calls it with 1 together with `0x43b800`, level + 1) and the limit `[0x532b34]`
is the constant 10 (`0x4157c5`); when the new progress reaches the limit in mode 1 the player's `+0x464`
is set to 1, `excellent` plays, `+0x474` = 1 and the win handler runs (`0x43ac00`, then the end
states `0x43bc90..0x43bd00`). The opponent object (`+0x3b0`) is only touched by the bonus effects
(`0x4522xx..0x4559xx`), so without bonuses a versus match is two independent boards racing to ten
wraps (mode 1) or until one board overflows.

## Full layout (corrected)

The earlier 120-piece layout came from an oracle run that crashed at the unstubbed constructor
0x4b6350 and box setter 0x4b65d0. With both stubbed (the setter takes three stack args, `ret 0xc`)
0x46b810 completes: 44 fixed pieces, the bonus slot grid (frames 16/17, one pair per bonus of each
player's character, [0x532a68] / [0x532a6c]), then 48 fixed pieces (rail beads, frame 32, among
them), plus two name boxes (built by 0x4b6350, not damier pieces; styled by items 32/33; (13,9)-(136,+24) and (503,9)-(626,+24)). `tools/gen_hud_layout.py` emits
this as prefix / per-character slot segments / tail; `vertrix_hud_draw` takes both characters.
The "Tube in the port" strips above are superseded: the rail beads are now ordinary layout pieces
and the spent-bead glow still has to be reworked from the controller state machines.

## Head placement (recovered, replaces the Doc-based assumption)

The constructor creates the two heads at `0x46e3f6..0x46e68c` as actors of the resource `0x544a34`
(frame = the player's character, `[0x532a68]` / `[0x532a6c]`, selected by `0x4ac710`), at the
table positions (62, 166) and (578, 166) (`0x4f8a56/5a` and `0x4f8a76/7a`), with amount 100, draw
flag 1 and the handler `0x45abd0`. Their clip boxes (`+0xa8..+0xae`: left, right, top, bottom) are
x 0..132, y 60..273 for the first and x 507..639, y 60..273 for the second (`0x4f8a60..68`,
`0x4f8a80..8c`; `[0x533d68]` is never written, so it is 0). The first head is therefore centred
on (62, 166) - which also matches the reference screenshot (Lee) - and clipped to its box; the port
used (106, 173) before. The mood animations (`0x45a0c0..0x45bf80`) are still not ported.
