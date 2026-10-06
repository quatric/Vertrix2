#ifndef VERTRIX_BONUS_EFFECTS_H
#define VERTRIX_BONUS_EFFECTS_H
#include "block_factory.h"
#include "board_cells.h"
#include "call_glue.h"
#include "choice_grid.h"
#include "virtual_call.h"

/* Services of the bonus effect handlers behind the dispatcher 0x43c140. Objects are original
 * address tokens resolved to storage by resolve; every callee that is not recovered here goes
 * through calls with the registers it receives in the original (the entry ebp is the token frame,
 * as in vertrix_board_view_setup); virtual calls name a slot (vtable offset / 4) of an object
 * handle; draw is the original random draw 0x4826c0. */
typedef struct
{
    const VertrixCalls *calls;
    VertrixObjectStorage resolve;
    void *resolve_context;
    VertrixVirtualCall virtual_call;
    void *virtual_context;
    VertrixChoiceDraw draw;
    void *draw_context;
    const VertrixFactoryServices *factory;
} VertrixEffectServices;

/* Original 0x453ad0 (eax = player, the effect behind dispatcher id 3): reads the opponent
 * (+0x3b0), the player's board (+0x15c), the opponent's board (+0x15c) and the opponent's choice
 * grid object (+0x3b8). A cell drawn from the grid (0x429fe0, recovered as
 * vertrix_choice_grid_pick_cell) makes the opponent take it: 0x43acd0 on the player, the row and
 * column stored as dwords at the opponent's +0x194 and +0x198, 0x43bb60 and 0x4ac8f0 on the
 * opponent with the handler token 0x451f10, and the dwords +0xb80, +0xb84 and +0xb88 of the
 * opponent's board set to one. Without a cell only 0x43ac00 runs on the player. Both paths then
 * call slot 1 of the player's board and end with 0x43bbf0 on the player. Returns the result of
 * 0x43bbf0, zero when an object does not resolve (nothing is done after that point). */
uint32_t vertrix_effect_forced_choice(const VertrixEffectServices *services, uint32_t player,
                                      uint32_t frame);

/* Original 0x453150 (eax = player, the effect behind dispatcher ids 4 and 5; the player's +0x3dc
 * is the wanted block kind, 5 or 6): marks the blocks of that kind on the player's board and on
 * the opponent's (0x436a10, which also snapshots the kinds) and counts them as a and b. Equal
 * counts only call 0x43acd0 on the player. Otherwise 0x43ac00 (a > b, unsigned) or 0x43acd0 runs
 * on the player, the sound 11 plays for the opponent (0x43c0e0), a and b are stored at the
 * player's +0x43c and +0x440, a markers of the player's board and b of the opponent's are
 * converted (0x436b40, vertrix_boards_convert_counts_traced), 0x4ac8f0 takes the handler token
 * 0x453280 for the player, 0x43bb60 runs on the opponent, the opponent board's +0xb80, +0xb84
 * and +0xb88 become one and 0x4ac8f0 takes 0x452050 for the opponent. Slot 1 of the player's
 * board is then called. With equal counts the result is 0x43bbf0 on the player, otherwise the
 * result of that slot. Zero when an object does not resolve. frame is the entry ebp token. */
uint32_t vertrix_effect_convert_blocks(const VertrixEffectServices *services, uint32_t player,
                                       uint32_t frame);

/* Original 0x452e00 (eax = player, the effect behind dispatcher id 1). Everything not recovered
 * here, and the recovered board routines whose results steer the flow, are boundary calls with the
 * registers the original holds; entry_ebx is the caller's ebx, which the original passes on to its
 * first calls. With the opponent's +0x3b0 board and the player's board (+0x15c each) 0x438cd0
 * decides: non-zero only calls 0x43acd0 (ecx 1) and slot 1 of the player's board, then returns
 * 0x43bbf0. Otherwise 0x43ab60 chooses 0x43ac00 (result 1) or 0x43acd0 on the player; sound 11
 * goes to the opponent (0x43c0e0); when 0x4320c0 on the opponent's board and 0x4330d0 (opponent's
 * board, player's board) both return 1 and the opponent's +0x170 is 1, the kinds of the three
 * children of the opponent board's active piece (+0xa60) go, sign-extended, to 0x43a560 with the
 * opponent's +0x3b4 and +0x170 is cleared; then 0x431d80 and 0x42ee20 follow on the opponent's
 * board, 0x42eda0 (0x44f040) and 0x42ee80 (5) on both boards, 0x433040, 0x43bb60 on the opponent,
 * its board's +0xb80, +0xb84 and +0xb88 are set to one, and 0x4ac8f0 takes 0x452050 for the
 * opponent and 0x452fc0 for the player. Slot 1 of the player's board is called last and its result
 * returned. Zero when an object does not resolve. */
uint32_t vertrix_effect_board_match(const VertrixEffectServices *services, uint32_t player,
                                    uint32_t entry_ebx);
#endif
