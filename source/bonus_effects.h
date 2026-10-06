#ifndef VERTRIX_BONUS_EFFECTS_H
#define VERTRIX_BONUS_EFFECTS_H
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
#endif
