# Sound Effects Channel Allocation and Event Dispatch (0x4174f0, 0x417550, 0x43c0e0, 0x43c110)

## Overview

The game audio engine uses an 8-channel sound mixer with dedicated voice partitions per player:
- **Player 1**: Channels 0, 1, 2, 3 (panned left)
- **Player 2**: Channels 4, 5, 6, 7 (panned right)

Audio events across the game loop (chains, alerts, bonus triggers, locks, line clears) route through
the event dispatchers `0x43c0e0` and `0x43c110`.

## Routines

### `0x4174f0` — `vertrix_sfx_allocate_channel_p1`
- Iterates over channels 0..3 checking channel availability via `0x4828a0`.
- Returns the first free channel index.
- If all 4 channels are busy, returns channel 0 as fallback.

### `0x417550` — `vertrix_sfx_allocate_channel_p2`
- Iterates over channels 4..7 checking availability via `0x4828a0`.
- Returns the first free channel index.
- If all 4 channels are busy, returns channel 4 as fallback.

### `0x43c0e0` — `vertrix_sfx_dispatch_event`
- **Inputs**:
  - `eax`: Player storage object (side 1 or 2 at `dword ptr [player + 0]`).
  - `edx`: Effect enumeration / index.
- **Behavior**:
  - Compares `effect` against sentinel `0xf4240` (1,000,000, meaning "no sound"). If equal, returns immediately.
  - If player side is 1: invokes Player 1 voice playback `0x417260`.
  - If player side is 2: invokes Player 2 voice playback `0x417290`.
  - Ignores other side values or undersized storage (`size < 4`).

### `0x43c110` — `vertrix_sfx_dispatch_secondary`
- Same sentinel check and side routing, dispatching to alternative playback handlers `0x4172c0` and `0x4173d0`.

## Verification

Verified by `tools/verify_sfx_dispatch.py`:
- Exhaustive verification of all 16 busy/free channel bit patterns for both Player 1 (`0x4174f0`) and Player 2 (`0x417550`).
- 4,096 cases testing `0x43c0e0` and `0x43c110` with varied effect IDs, sides, and sentinel values against `Vertrix2.exe` Unicorn x86 (8,224 complete original executions).
- Evidence recorded in `docs/sfx-dispatch-verification.json`.
