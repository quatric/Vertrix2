# Vertrix 3, recompiled

Vertrix 3 runs here from its own Windows executable: `recomp.py` turns every function of
`Vertrix3.exe` into C, and a small runtime supplies the machine and the parts of Windows the game
uses. The same generated code runs on the build machine (software renderer, frames written as
PPM files) and on the Wii (GX renderer, Wii Remote, SD card).

Nothing of the game is in this repository: the build reads `Vertrix3.exe`
(sha256 `db625cfe…f7e9`), and the game reads its data from the original `VERTRIX3.VF`.

## Layout

| Path | What |
| --- | --- |
| `recomp.py` | x86 to C: function discovery, switch tables, flag liveness, x87 |
| `x87_check.py` | every x87 instruction form of the game, run under Unicorn and as generated C, compared |
| `runtime/` | the guest machine: memory (flat on the host, 64 KB pages on the Wii), the call dispatcher, heap, threads, the process and its threads |
| `win32/` | kernel32, user32, winmm, dinput8, advapi32, ole32 as the game calls them |
| `d3d/d3d9.c` | Direct3D 9: the objects, states and draws the game uses |
| `d3d/render_vertex.h` | the fixed-function vertex stage (transform, lighting, near clip, culling) |
| `d3d/render_soft.c` | the CPU rasterizer, the reference |
| `d3d/render_gx.c` | the same pipeline on the Wii's GX: TEV stages for the texture stages |
| `host/host_main.c` | the build-machine driver |
| `wii/wii_main.c` | the Wii driver: video, SD, controllers, ASND |

## How the recompiled code works

- Each x86 function becomes `void F_<address>(Cpu *c)`. Registers live in locals and are
  synchronised with the `Cpu` around calls; the stack is the guest's own, so `call` pushes the
  real return address and `ret` pops it.
- Direct calls are C calls; indirect calls and jumps go through `v3_call`, which finds the
  function or the host function (imports and COM methods live at `0xfff00000`, 16 bytes each).
- Flags are computed only where a later instruction reads them (backward liveness per
  function). Hand-written runtime helpers that hand flags across a call are found by
  `flag_readers` (a function that reads, before writing, flags its caller set) and
  `flag_returners` (a callee whose flags the caller uses).
- Switch tables are read from the image, bounded by the `cmp`/`and` before the jump; memcpy's
  tables are also indexed from below their base.
- The x87 stack is eight doubles with a top index, as the hardware's registers.
- MMX, SSE and 3DNow! paths are never taken: `cpuid` reports none, so D3DX and the C runtime
  pick their x87 code.

## The build machine

```
make -C vertrix3 V3_EXE=/path/to/Vertrix3.exe PYTHON=python3 host
build/v3/v3_host build/v3/gen/v3_image.bin GAME_DIR OUT_DIR [seconds] [frame_every] [-options]
```

`GAME_DIR` holds `VERTRIX3.VF` (and gets `Settings/`). Environment variables:

- `V3_SCRIPT="2 move 128 86; 2.5 button 0 1; 2.6 button 0 0"`: timed input (`key SCAN DOWN`,
  `move DX DY`, `button N DOWN`). The game's cursor moves two pixels per mouse unit, from the
  centre.
- `V3_TRACE=1` (every host call), `V3_TRACE_FRAME=N` (every host call of frame N, with each
  draw's vertices, matrices and texture), `V3_TRACE_D3D=1`, `V3_STATS=1` (each distinct render
  state combination once), `V3_WATCH=hex` (log each entry of a function), `V3_PEEK=addr,*ptr+off`
  (guest words every 300 frames), `V3_DUMP=FRAME:PATH` (the heap at a frame),
  `V3_NO_STENCIL=1` (draw without the stencil test, to compare).

A fault prints the guest address and the last function entries. When the run's time is up the
driver closes the game's window, as Alt+F4 would: the game leaves through its own exit and
saves `Settings/Vertrix3.cfg`.

The first launch asks to confirm the display mode (GO at the bottom right, within 13 seconds);
once the settings are saved, later launches skip it. The scripts above start with that click,
so run them without a `Settings/` folder.

## The Wii

```
make -C vertrix3 V3_EXE=/path/to/Vertrix3.exe PYTHON=python3 wii        # build/v3/vertrix3.dol
make -C vertrix3 BUILD=../build/v12 GAME=vertrix2-v12 V3_EXE=/path/to/Vertrix2.exe PYTHON=python3 wii
                                                                  # build/v12/vertrix2-v12.dol
make -C vertrix3 V3_EXE=... PYTHON=... wii-sync SYNC=/path/to/sd-root    # apps/vertrix3/
```

Copy the game's `VERTRIX3.VF` into `sd:/apps/vertrix3/`. Controls:

| Wii | Game |
| --- | --- |
| D-pad, Nunchuk or Classic stick | arrow keys: left, right, down; Up permutes |
| B | permute |
| A | click where the remote points (menus) |
| 1, 2 | Enter, Space |
| Plus, Minus | Escape |
| Home | back to the loader |

A USB keyboard and mouse work as themselves. The log is `sd:/apps/vertrix3/vertrix3.log` (and
Dolphin's OSReport log). On the first launch, point at GO and press A to keep the display mode;
Home then leaves through the game's own exit, which saves `sd:/apps/vertrix3/Settings/`, and
later launches go straight to the intro.

Debug builds for Dolphin, `WII_DEBUG='-DV3_WII_SHOTS=120 -DV3_WII_SCRIPT="\"…\"" -DV3_WII_ENV="\"V3_STATS=1\""'`:
frame dumps to `sd:/apps/vertrix3/shots/`, the timed input of `V3_SCRIPT` (in place of the
pointer; a step the game was too busy to take delays the ones after it), and the build machine's
diagnostic variables. The frame dumps read the EFB through a texture copy, so Dolphin needs
"Store EFB Copies to Texture Only" off (`[Hacks] EFBToTextureEnable = False` in `GFX.ini`).

### Memory

The guest heap is 32 MB of MEM2 (`V3_HEAP_SIZE`; a match peaks near 25 MB). GX keeps its own
RGBA8 copy of each texture; when memory runs out, the copies least recently drawn are dropped
and converted again from the game's own pixels on their next use.

### How GX draws Direct3D

The vertex stage runs on the CPU, shared with the reference renderer. GX receives each clipped
triangle's clip-space position as `(cx, cy, -cw)` with a projection that keeps x and y and
divides by w, so colors and texture coordinates interpolate with perspective. Direct3D's integer
pixel centres become a half-pixel viewport shift. The texture stages the game uses
(SELECTARG, MODULATE, ADD, SUBTRACT with TEXTURE, DIFFUSE, CURRENT and TFACTOR) map onto TEV;
the reverse-subtract blend premultiplies its source in a last TEV stage. Textures are converted
to RGBA8 tiles when the game unlocks them.

The stencil is used once: each well of the board screen is drawn into it, and the falling
pieces are drawn only where it is set, so a new piece slides in from under the well's top edge.
GX has no stencil, but the game never enables depth, so the depth buffer holds it. A stencil
value becomes a constant depth (the projection's z row, so it interpolates exactly), the stencil
clear writes that depth, REPLACE becomes a depth write, and the stencil function becomes the
depth function. Other stencil operations, and stencil with depth on, are logged once and drawn
unmasked.

Not modelled: fog, specular, points and lines (a whole run to a match enables none of them).
