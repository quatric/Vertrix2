#include "board_frame.h"

int vertrix_board_frame(VertrixBoardFrame *board)
{
    if (!board || !board->frame.scene || !board->frame.list || !board->frame.resolve ||
        !board->frame.visit)
    {
        return 0;
    }
    if (!vertrix_board_effects_tick(&board->effects, board->elapsed, board->frame.visit,
                                    board->frame.context))
    {
        return 0;
    }
    if (board->frame.scene->active &&
        !vertrix_scene_fall_tick(board->frame.scene, board->piece, board->descent,
                                 board->frame.origin_x, board->frame.origin_y, board->elapsed,
                                 board->paused, board->frozen, board->blink, board->frame.resolve,
                                 board->frame.visit, board->frame.context, &board->failed))
    {
        return 0;
    }
    return vertrix_scene_frame(&board->frame);
}
