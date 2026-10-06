#ifndef VERTRIX_GAME_H
#define VERTRIX_GAME_H
#include <stdint.h>
#define COLS 5
#define ROWS 13
#define EMPTY 255
#define STONE 5
#define BOMB 6
typedef struct
{
    int n, weight;
    int8_t dx[7], dy[7];
} Figure;
extern const Figure figures[9];
/* Original 0x434ee0, the figure pass of match_board alone: returns 1 when any figure was found,
 * with the reward (figures not overlapping an earlier one). With commit nonzero the mask of
 * every figure cell is set and every accepted figure's cells are branded 7 in the board (the
 * original's ecx); with zero neither is written but found and reward are still computed.
 * Members must avoid 0xff, stone and bomb; colors compare sign-extended. The mask is only
 * ever set, never cleared. */
int vertrix_figure_pass(uint8_t board[COLS][ROWS], uint8_t mask[COLS][ROWS], int *reward,
                        int commit);
int match_board(uint8_t board[COLS][ROWS], uint8_t mask[COLS][ROWS], int threshold,
                int use_figures);
/* Original 0x4346b0: marks (1) every cell of a run longer than threshold in the six directions
 * without clearing the mask, adds the runs not yet marked to *reward and returns whether any
 * run was found. */
int vertrix_line_pass(const uint8_t board[COLS][ROWS], uint8_t mask[COLS][ROWS], int threshold,
                      int *reward);
int board_falling_mask(const uint8_t board[COLS][ROWS], uint8_t mask[COLS][ROWS]);
void board_collapse(uint8_t board[COLS][ROWS]);
/* Original placement after descent is blocked. Column must be 0..4.
 * discarded marks blocks outside the board; returns the original lock result. */
int board_lock(uint8_t board[COLS][ROWS], int32_t column, int32_t top, const uint8_t blocks[3],
               uint8_t discarded[3]);
void board_rise(uint8_t board[COLS][ROWS], uint8_t incoming[COLS], uint8_t evicted[COLS]);
/* Shift only rows with incoming blocks. Evicted reports blocks requiring
 * destruction; animation/destruction scheduling is handled separately. */
void board_shift(uint8_t board[COLS][ROWS], uint8_t incoming[ROWS], uint8_t evicted[ROWS],
                 int right);
void board_pixel_cell(int16_t origin_x, int16_t origin_y, int16_t pixel_x, int16_t pixel_y,
                      int32_t *column, int32_t *row);
void board_blast_mask(const uint8_t board[COLS][ROWS], uint8_t mask[COLS][ROWS], uint8_t pattern,
                      uint8_t radius);
void board_bomb_estimate(const uint8_t board[COLS][ROWS], uint8_t pattern, int *stones, int *total);
#endif
