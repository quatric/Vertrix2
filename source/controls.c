#include "controls.h"

static int opponent_move(VertrixControlState *state, int right)
{
    static const uint32_t payload[3] = {0, 0, 0};
    VertrixInputAction *action = &state->actions[state->opponent[right]];
    return vertrix_input_action_edge(action, payload, 1, 0, state->deferred, state->sink,
                                     state->sink_context) &&
           vertrix_input_action_edge(action, payload, 0, 0, state->deferred, state->sink,
                                     state->sink_context);
}

int vertrix_controls_dispatch(const uint8_t board[COLS][ROWS], int16_t origin_x, int16_t origin_y,
                              VertrixControlState *state, uint8_t *refresh)
{
    if (!state->piece->active || state->piece->failed)
    {
        return 1;
    }
    for (unsigned i = 0; i < 4; i++)
    {
        if (state->control[i] >= 256)
        {
            return 0;
        }
    }
    if (state->mode == 0x2b && (state->opponent[0] >= 256 || state->opponent[1] >= 256))
    {
        return 0;
    }
    for (int right = 0; right < 2; right++)
    {
        VertrixInputQueue *queue = &state->actions[state->control[right]].queue;
        if (vertrix_input_queue_ready(queue))
        {
            if (vertrix_move_horizontal(board, origin_x, origin_y, state->piece, right))
            {
                if (state->mode == 0x2b && !opponent_move(state, right))
                {
                    return 0;
                }
            }
            else
            {
                *refresh = 1;
            }
            vertrix_input_queue_acknowledge(queue);
        }
    }
    VertrixInputQueue *cycle = &state->actions[state->control[2]].queue;
    if (vertrix_input_queue_ready(cycle))
    {
        vertrix_piece_cycle(state->piece->blocks);
        if (state->cycle_mode == 1)
        {
            vertrix_piece_bottom_color(state->random, state->piece->blocks);
            *refresh = 1;
        }
        vertrix_input_queue_acknowledge(cycle);
    }
    VertrixInputQueue *fast = &state->actions[state->control[3]].queue;
    if (vertrix_input_queue_ready(fast))
    {
        vertrix_motion_fast(state->motion, state->difficulty);
        vertrix_input_queue_acknowledge(fast);
    }
    return 1;
}
