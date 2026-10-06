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

Not yet ported: 0x453150 (ids 4/5), 0x452e00 (id 1), 0x453b90.
