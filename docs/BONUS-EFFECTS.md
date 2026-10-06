# Bonus effects

## 0x453ad0 (dispatcher id 3): forced choice

Native: `vertrix_effect_forced_choice` in `source/bonus_effects.c`.

Picks a cell in the opponent's choice grid (`vertrix_choice_grid_pick_cell`, 0x429fe0). On a hit it
calls 0x43acd0, stores row/column at opponent +0x194/+0x198, calls 0x43bb60 and 0x4ac8f0 with
0x451f10, and sets the opponent board's +0xb80/+0xb84/+0xb88 to 1. Otherwise it calls 0x43ac00.
It then calls board virtual slot 1 and returns 0x43bbf0. 0x429fe0 leaves edx and ebx as leftovers
that the later boundary calls carry; the native side reproduces them.

Evidence: `tools/verify_bonus_effects.py` runs the complete original routine under Unicorn, 2048
cases (1549 forced choice, 499 none, 5 unresolved-object checks), comparing the boundary call log
with registers, the return value and every pool object. Report: `docs/bonus-effects-verification.json`.

## 0x453150 (dispatcher ids 4 and 5): block conversion

Native: `vertrix_effect_convert_blocks`. The player's `+0x3dc` (5 or 6) is the wanted block kind.
0x436a10 on both boards (snapshot of the slot kinds to `+0x1de`, markers at `+0xb94`) gives the
counts a (own) and b (opponent). Equal counts: 0x43acd0 on the player (ebx 1), slot 1 of the own
board, then 0x43bbf0. Otherwise 0x43ac00 (a > b unsigned) or 0x43acd0, sound 11 for the opponent
(0x43c0e0; 11 is the dword at 0x4f81ac), a and b to the player's `+0x43c`/`+0x440`, 0x436b40
(a markers on the own board, b on the opponent's), 0x4ac8f0 with 0x453280 for the player, 0x43bb60
on the opponent, the opponent board's `+0xb80/+0xb84/+0xb88` = 1, 0x4ac8f0 with 0x452050 for the
opponent, slot 1 of the own board; the result is that slot's.
0x436b40 leaves ebx and ecx behind (last old block and b; else a twice; else kind and 0) and the
boundary calls carry them, so `vertrix_boards_convert_counts_traced` reports the old block.

Evidence: same verifier, 2048 more cases (993 equal, 533 a > b, 522 a < b), real 0x436b40.

Not yet ported: 0x452e00 (id 1), 0x453b90.
