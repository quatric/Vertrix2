# Event Frame Draw Dispatchers (0x482e10, 0x482e80, 0x482f00)

## Overview

The font and glyph rendering pipeline uses a family of three dispatch routines to translate
an item / frame descriptor into a structured 28-byte event record, perform key mapping and field
scaling, and then invoke a drawing callback (direct blit, alpha blend, or scaled blend).

## Routines

### `0x482e10` — `vertrix_event_frame_draw_direct`
- **Inputs**:
  - `eax`: Pointer to item descriptor (min size `0x28` bytes; fields at `+0`, `+4`, `+8`, `+0x27`).
  - `edx`: Target surface or draw context handle.
  - `ebx`: Direct draw argument 0.
  - `ecx`: Direct draw argument 1.
- **Behavior**:
  1. Populates a 28-byte (`0x1c`) event structure:
     - `+0x00`: `item[0]`
     - `+0x04`: `item[4]`
     - `+0x08`: `item[8]`
     - `+0x0c`: `item[0x27]` (flags / key)
  2. Runs `vertrix_event_key_index` (`0x478cd0`) with `(item[0x27] << 3) & 0xff`, writing slot index to `+0x0d`.
  3. Computes `item[4] * item[0x27]`, writes to `+0x14`.
  4. Runs `vertrix_event_scale_fields` (`0x478da0`), writing difference to `+0x18` and nonzero flag to `+0x10`.
  5. Dispatches to draw callback `0x47ce10` with stack arguments `[ebx, ecx, item[4], item[8]]`.

### `0x482e80` — `vertrix_event_frame_draw_blend`
- **Inputs**: Same as direct blit, with an additional stack parameter `extra` (blend factor or palette mode).
- **Behavior**: Same event preparation and scaling as `0x482e10`, but dispatches to blend callback `0x47c930` with 5 stack arguments `[ebx, ecx, item[4], item[8], extra]`.

### `0x482f00` — `vertrix_event_frame_draw_scaled`
- **Inputs**: Item descriptor, registers `edx, ebx, ecx`, plus 5 stack arguments `[arg0..arg4]`.
- **Behavior**: Same event preparation, dispatches to scaled callback `0x47cb40` with `ebx = arg0`, `ecx = arg1`, and stack `[ebx_in, ecx_in, arg2, arg3, arg4]`.

## Verification

Verified by `tools/verify_event_frame_draw.py`:
- 4,096 cases tested per routine (12,288 total executions) against `Vertrix2.exe` via Unicorn x86.
- Register arguments (`edx, ebx, ecx`), stack parameters, and 28-byte event buffer compared.
- Short-buffer rejection tested for each function (`size < 0x28`).
- Evidence recorded in `docs/event-frame-draw-verification.json`.
