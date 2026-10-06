#include "descent.h"
#include "collision.h"

/* Original 0x00431100 / 0x00431140, using occupancy-only checks
 * 0x004311c0 / 0x00431280 rather than the board-effect row masks. */
int vertrix_move_horizontal(const uint8_t board[COLS][ROWS], int16_t origin_x, int16_t origin_y,
                            VertrixFallingPiece *piece, int right)
{
    static const uint8_t all_rows[ROWS] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int32_t column, row;
    board_pixel_cell(origin_x, origin_y, piece->x, piece->y, &column, &row);
    int32_t neighbor = column + (right ? 1 : -1);
    if (neighbor < 0 || neighbor >= COLS)
    {
        return 0;
    }
    if (!piece->active ||
        vertrix_side_contact(board, all_rows, origin_x, origin_y, piece->x, piece->y, right))
    {
        return 0;
    }
    uint16_t bits = (uint16_t)((uint16_t)piece->x + (right ? 24 : -24));
    piece->x = (int16_t)(bits < 32768 ? bits : (int32_t)bits - 65536);
    return 1;
}

/* Original 0x0042fc2d..0x0042fc56, with clear branch at 0x0042fe81.
 * Check before moving each pixel; budget exhaustion does not lock early. */
void vertrix_descent(uint8_t board[COLS][ROWS], int16_t origin_x, int16_t origin_y,
                     VertrixFallingPiece *piece, uint32_t pixels)
{
    while (piece->active && pixels)
    {
        if (!vertrix_down_clear(board, origin_x, origin_y, piece->x, piece->y))
        {
            int32_t column, row;
            uint8_t discarded[3];
            board_pixel_cell(origin_x, origin_y, piece->x, piece->y, &column, &row);
            piece->failed = !board_lock(board, column, row, piece->blocks, discarded);
            piece->active = 0;
            return;
        }
        uint16_t bits = (uint16_t)((uint16_t)piece->y + 1);
        piece->y = (int16_t)(bits < 32768 ? bits : (int32_t)bits - 65536);
        pixels--;
    }
}

static void descent_frozen(VertrixDescentState *state, uint32_t frozen)
{
    if ((frozen == 1 && state->frozen == 0) || (frozen != 1 && state->frozen == 1))
    {
        state->flash = frozen == 1 ? 1 : 0;
        uint16_t effect = frozen != 1 && state->cycle_mode == 1 ? 20 : 0;
        for (unsigned i = 0; i < 3; i++)
        {
            state->block_effect[i] = effect;
        }
    }
    state->frozen = frozen;
}

uint32_t vertrix_descent_budget(VertrixDescentState *state, uint32_t elapsed, int paused,
                                uint32_t frozen, uint32_t blink)
{
    state->motion.counter += elapsed;
    if (paused || frozen)
    {
        if (blink == 1)
        {
            descent_frozen(state, 1);
            vertrix_timer_advance(&state->blink, elapsed);
            if (vertrix_timer_due(&state->blink))
            {
                state->blink.counter = 0;
                uint16_t effect = state->flash ? 0 : 0xff38;
                for (unsigned i = 0; i < 3; i++)
                {
                    state->block_effect[i] = effect;
                }
                state->flash = 1u - state->flash;
            }
        }
        state->motion.counter = 0;
        return 0;
    }
    descent_frozen(state, 0);
    state->blink.counter = 0;
    VertrixTimer timer = {state->motion.counter, state->motion.period};
    uint32_t scale =
        state->motion.step < 32768 ? state->motion.step : (uint32_t)state->motion.step - 65536u;
    uint32_t pixels = vertrix_timer_scaled(&timer, scale);
    if (pixels)
    {
        state->motion.counter = 0;
    }
    return pixels;
}

void vertrix_descent_tick(uint8_t board[COLS][ROWS], int16_t origin_x, int16_t origin_y,
                          VertrixFallingPiece *piece, VertrixDescentState *state, uint32_t elapsed,
                          int paused, uint32_t frozen, uint32_t blink)
{
    if (!piece->active)
    {
        return;
    }
    uint32_t pixels = vertrix_descent_budget(state, elapsed, paused, frozen, blink);
    if (pixels)
    {
        vertrix_descent(board, origin_x, origin_y, piece, pixels);
    }
}
