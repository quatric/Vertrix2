#ifndef VERTRIX_DESCENT_H
#define VERTRIX_DESCENT_H

#include "game.h"
#include "timer.h"
#include "timing.h"

typedef struct
{
    int16_t x;
    int16_t y;
    uint8_t blocks[3];
    uint8_t active;
    uint8_t failed;
} VertrixFallingPiece;

/* Original horizontal move: one cell when every covered row is clear. */
int vertrix_move_horizontal(const uint8_t board[COLS][ROWS], int16_t origin_x, int16_t origin_y,
                            VertrixFallingPiece *piece, int right);

/* Original descent-loop slice with a positive pixel budget. */
void vertrix_descent(uint8_t board[COLS][ROWS], int16_t origin_x, int16_t origin_y,
                     VertrixFallingPiece *piece, uint32_t pixels);

typedef struct
{
    VertrixMotion motion;
    VertrixTimer blink;
    uint32_t frozen;
    uint32_t flash;
    uint32_t cycle_mode;
    uint16_t block_effect[3];
} VertrixDescentState;

/* Original active-piece timer/frozen preparation, before pixel traversal.
 * Requires a live active piece and valid state. Updates child effect values;
 * caller publishes them before moving/locking. Returns original pixel budget. */
uint32_t vertrix_descent_budget(VertrixDescentState *state, uint32_t elapsed, int paused,
                                uint32_t frozen, uint32_t blink);

/* Active-piece update 0x42fbc8..0x42fc56, including frozen branch.
 * paused: player +0x4cc != 0; frozen: board +0xb80 != 0;
 * blink: board +0xb90 (only value 1 enables the blinking timer).
 * Block effects are original child +0x48 values, meaningful while active. */
void vertrix_descent_tick(uint8_t board[COLS][ROWS], int16_t origin_x, int16_t origin_y,
                          VertrixFallingPiece *piece, VertrixDescentState *state, uint32_t elapsed,
                          int paused, uint32_t frozen, uint32_t blink);

#endif
