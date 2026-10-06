#ifndef VERTRIX_CONTROLS_H
#define VERTRIX_CONTROLS_H

#include "descent.h"
#include "input.h"
#include "piece.h"
#include "timing.h"

typedef struct
{
    VertrixFallingPiece *piece;
    VertrixMotion *motion;
    VertrixRandom *random;
    VertrixInputAction *actions;
    uint16_t control[4];  /* Original player +0x168..0x16e: left/right/cycle/fast. */
    uint16_t opponent[2]; /* Opponent +0x160/+0x162, used by mode 0x2b. */
    uint32_t mode;
    uint32_t cycle_mode; /* Original active piece +0x17c. */
    int difficulty;
    int deferred;
    VertrixInputDeferredSink sink;
    void *sink_context;
} VertrixControlState;

/* Original active-piece input slice 0x451048..0x4511bb, including the
 * failed-move branches. refresh corresponds to the 0x43ad50 request flag.
 * Caller retains responsibility for the surrounding player/board state loop.
 * Returns 0 on invalid IDs or failed event delivery; processing must stop. */
int vertrix_controls_dispatch(const uint8_t board[COLS][ROWS], int16_t origin_x, int16_t origin_y,
                              VertrixControlState *state, uint8_t *refresh);

#endif
