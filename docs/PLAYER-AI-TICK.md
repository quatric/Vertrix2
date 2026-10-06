# Player AI Tick Routine (0x43b430)

## Overview

In `Vertrix2.exe`, `0x43b430` is the core per-tick AI driver for each player (`TPlayer` instance).
It manages the decision cycle and synthetic keypress injection for AI-controlled players.

## Routine: `0x43b430`

- **Signature**: `void __fastcall fcn_0043b430(void *player)`
- **Calling Convention**: Delphi fastcall (`eax = player`)

### Control Flow and State Machine

1. **AI Activation Check**:
   - Reads `dword ptr [player + 0x454]`.
   - If zero, AI is inactive; the function exits immediately.

2. **Phase 1: Initial Piece Evaluation & Planning**:
   - Reads `dword ptr [player + 0x178]`.
   - If equal to `1`:
     - Resolves the AI state object pointer at `player + 0x458`.
     - Calls `0x427850` (`compare_boards` / AI board state evaluator).
     - Resolves the active falling piece at `player + 0x140`.
     - Calls `0x42b090` (`preview_frames`) to retrieve candidate piece configurations into a 7-element table.
     - Calls `0x4290a0` (`vertrix_ai_choose_piece_rotation`) with the candidate table to pick the optimal rotation.
     - Sets the player phase `player + 0x178 = 0`.
     - Calls `0x4ac510` (`timer_reset`) on the AI timer object.
     - Calls `0x43b680` (`draw_delay_2`) to compute the reaction delay.
     - Calls `0x4ac7d0` (`timer_set_period`) with the delay.

3. **Phase 0: Execution & Key Injection**:
   - If `player + 0x178 == 0`:
     - Calls `0x4ac500` (`timer_update`) on the AI timer object.
     - Calls `0x4ac520` (`timer_check`) to query whether the timer period has elapsed.
     - If elapsed:
       - Checks `dword ptr [player + 0x16c]` (number of rotation steps remaining).
       - If `rotations > 0`:
         - Decrements `player + 0x16c`.
         - Reads `uint16_t key = *(uint16_t *)(player + 0x164)` (permute / rotate key code).
         - Injects key event (`0x4761d0` / `0x476280`).
       - If `rotations == 0`:
         - Checks if fast drop is allowed via `0x431490`.
         - Reads `uint16_t drop_key = *(uint16_t *)(player + 0x166)` (down / drop key code).
         - Injects drop key press.

## Verification

Differential verification against `Vertrix2.exe` via Unicorn x86 is in `tools/verify_player_ai_tick.py`:
- 4,096 randomized test iterations across active/inactive states, phase transitions, rotations remaining, timer expirations, and key injection paths.
- Verified exact matching of player memory layout, phase flags, timer updates, and returned actions.
- Results recorded in `docs/player-ai-tick-verification.json`.
