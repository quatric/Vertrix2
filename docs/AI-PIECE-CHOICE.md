# AI Piece Choice and Rotation Selection (0x429000, 0x4290a0)

## Overview

The computer player / AI selects which rotation or slot of the active falling piece to choose
through the routine pair `0x429000` (candidate slot evaluation and max selection) and
`0x4290a0` (storage read, evaluation, and rotation count assignment).

## Routines

### `0x429000` — `vertrix_ai_find_best_slot`
- **Inputs**:
  - `eax` / `edx`: Pointer to an array of up to seven active slot/piece indices (`uint32_t table[7]`),
    terminated by `0xffffffff` (`-1`).
  - `ebx`: Pointer to an array of byte scores (`player + 0x210`), indexed by the candidate indices.
- **Algorithm**:
  1. Counts active candidates via `0x425e00` (`vertrix_table_used_count`).
  2. If `count == 1`, returns 0.
  3. If `count == 0`, returns 1.
  4. Reads `scores[table[i]]` and static priority `table_4f9318[table[i]]`.
  5. Scans candidate `1..count-1` against `best`:
     - Compares scores using signed `int8_t` (Delphi `Shortint`) arithmetic (`jle`/`jg`).
     - On tied scores, breaks tie using signed comparison of static priority values from `0x4f9318`.
     - On tied priority, draws a random bit from `0x4826c0` (`random(2)`). If 1, the new candidate wins.
  6. Return value: `best + 1`. If `best + 1 == count`, wraps to 0 (`(best + 1) ^ count = 0`).

### `0x4290a0` — `vertrix_ai_choose_piece_rotation`
- **Inputs**:
  - `eax`: Player / AI storage object.
  - `edx`: Pointer to `table[7]`.
- **Behavior**:
  - Passes `&player[0x210]` as the scores buffer to `0x429000`.
  - Writes the returned rotation count into `dword ptr [player + 0x16c]`.
  - Returns the chosen rotation count in `eax`.
  - `0x43b430` decrements `player + 0x16c` each tick and emits permute key presses until zero.

## Verification

Verified by `tools/verify_ai_piece_choice.py`:
- 4,096 complete original executions against `Vertrix2.exe` via Unicorn x86.
- Tested all candidate counts 0..7, random indices, scores, and tied priorities.
- Whole-object memory comparison of player buffer before and after `0x4290a0`.
- Short-buffer protection validated.
- Evidence recorded in `docs/ai-piece-choice-verification.json`.
