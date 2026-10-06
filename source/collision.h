#ifndef VERTRIX_COLLISION_H
#define VERTRIX_COLLISION_H

#include "game.h"

/* Original downward probe. Valid piece column is 0..4; a probe that
 * reaches board storage must have a nonnegative row. */
int vertrix_down_clear(const uint8_t board[COLS][ROWS], int16_t origin_x, int16_t origin_y,
                       int16_t piece_x, int16_t piece_y);

/* Original side-shift pattern 0..2 at step zero. */
int vertrix_side_shift_contact(const uint8_t board[COLS][ROWS], uint32_t pattern, int16_t origin_x,
                               int16_t origin_y, int16_t piece_x, int16_t piece_y, int right);

/* Original side-contact decision, not permission to move. Current column
 * must be 0..4 and the active piece's bottom row at most 12. The row mask
 * is supplied by the original mode tables; zero rows ignore contact. */
int vertrix_side_contact(const uint8_t board[COLS][ROWS], const uint8_t row_mask[ROWS],
                         int16_t origin_x, int16_t origin_y, int16_t piece_x, int16_t piece_y,
                         int right);

#endif
