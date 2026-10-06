#ifndef VERTRIX_BOARD_FRAME_H
#define VERTRIX_BOARD_FRAME_H
#include "board_effects.h"
#include "scene_fall.h"

typedef struct
{
    VertrixBoardEffects effects;
    VertrixSceneFrame frame;
    VertrixScenePiece *piece;
    VertrixDescentState *descent;
    uint32_t elapsed;
    int paused;
    uint32_t frozen;
    uint32_t blink;
    uint32_t failed;
} VertrixBoardFrame;
/* Compose complete original board handler 0x42fb60: effects, active-piece
 * timer/descent/locking, then scene layout/list updates/reset. Actual object
 * virtual methods remain supplied by frame.visit. Callbacks may alter later
 * board fields before their stage. All storage is caller-owned; no allocation.
 * Invalid runtime state may follow partial progress. */
int vertrix_board_frame(VertrixBoardFrame *board);
#endif
