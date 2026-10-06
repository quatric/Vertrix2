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

## 0x452e00 (dispatcher id 1): board match

Native: `vertrix_effect_board_match(services, player, entry_ebx)`. `entry_ebx` is the caller's ebx,
which the original forwards in its first boundary calls. 0x438cd0 (not portable: its result depends
on uninitialised stack, see `BOARD-MARKERS.md`) is a boundary call, as are 0x43ab60 and the
recovered board routines 0x4320c0, 0x4330d0, 0x431d80, 0x42ee20, 0x42eda0, 0x42ee80, 0x433040 and
0x43a560 (their results steer the flow, so the wiring supplies them). Flow: see the header comment
in `source/bonus_effects.h`. The sign-extended kinds of the opponent piece's three children go to
0x43a560.

Evidence: same verifier, 2048 more cases (equal boards, chain, pending-flag clear, plain paths
counted in the report) with all callees stubbed and logged with registers. Limit: registers a
stubbed callee would clobber in the original are not modelled (the stub leaves them), exactly as
for the other effects.

## 0x453b90 and 0x453c00

Natives `vertrix_effect_pair_sound` (0x43d3b0 steers; else sound 3 and two 0x43ccf0 calls with the
player's `+0x3f8`) and `vertrix_effect_copy_speed` (the opponent receives the player's `+0x3cc` at
`+0x424`, `+0x428` cleared, handler 0x453c90). Both take the caller's edx, which they forward.
2048 cases each in the same verifier.

## The sixteen state gates 0x4535d0..0x453a80

One native, `vertrix_effect_state_gate`, with the table `vertrix_state_gates` (handler, register
layout, expected state `+0x4c8`, callee). Opponent layout: 0x4535d0 (0x23, 0x43cf30), 0x4537b0
(0x2f, 0x43ceb0), 0x453800 (0x31, 0x43cef0), 0x453850 (0x24, 0x43cfb0), 0x4538a0 (0x28, 0x43cff0),
0x453990 (0x2d, 0x43d0b0), 0x4539e0 (0x2e, 0x43d0f0), 0x453a80 (0x2c, 0x43cda0). Self-board layout:
0x4536c0 (0x32), 0x453710 (0x33), 0x453760 (0x34), all 0x43ce70, and 0x453a30 (0x2b, 0x43cd60).
Self-sound layout (sound 6 instead of 0x43ac00): 0x453620 (0x22, 0x43cf70), 0x453670 (0x30,
0x43ce30), 0x4538f0 (0x29, 0x43d030), 0x453940 (0x2a, 0x43d070). A matching state calls 0x43acd0,
otherwise the callee runs; all end with slot 1 of the player's board and 0x43bbf0. 512 cases per
handler in the verifier, half with a matching state.

## Wiring note

The dispatcher 0x43c140 does not call an effect: it stores the effect address as the player's
actor handler with 0x4ac8f0 (`43cc74: edx = handler; eax = player; call 0x4ac8f0`). The effects run
later from the actor update, so their entry ebx/edx come from that caller, not from the dispatcher.

Not yet ported: the remaining effects behind 0x43c140 (0x452830, 0x452880, 0x4528e0, 0x452a30,
0x452b00, 0x452bb0, 0x452c60, 0x452d10, 0x452d70, 0x453460, 0x453f40 and everything from 0x454250).
