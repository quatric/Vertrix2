#ifndef VERTRIX_BOARD_ACTIONS_H
#define VERTRIX_BOARD_ACTIONS_H
#include "block_factory.h"
/* Board-level actions over the block grids. The board storage holds the grid of the falling
 * blocks at +0x220 (handles, 13 dwords per column), the grid of their shadow companions at +0x87c
 * and the marker bytes at +0xb94 (13 per column). Objects resolve through the supplied services. */

/* Original0x4330d0: whether any cell of the other board's grid (65 handles, 13 per column), in the
 * active piece's column and from its top row to its bottom row (y + 0x47), holds an object. Rows
 * above the board are skipped. Returns zero for a column or row outside the grid, which the
 * original would read past. */
int vertrix_board_piece_hits_grid(const void *board, size_t board_size,
                                  const VertrixFactoryServices *services,
                                  const uint32_t other_grid[65], uint32_t *hit);

/* Original0x4371b0: for every marker equal to 1, in row order: set it to 2, give the companion
 * object its handler 0x44e790 and the block object its handler 0x44e800. Returns 1 (also with no
 * markers); zero when an object does not resolve or a cell is unusable. */
int vertrix_board_start_marked(void *board, size_t board_size,
                               const VertrixFactoryServices *services);

/* Original0x437460: for every marker equal to 1, in row order and without changing the markers,
 * give the block object its handler 0x44d9d0 and the companion its handler 0x44dbb0. */
int vertrix_board_flag_marked(const void *board, size_t board_size,
                              const VertrixFactoryServices *services);

/* Original0x438470: start a slide of the actor to the board cell (cells_x, cells_y): the target
 * words +0x10 and +0x18 become the board origin plus 24 * cells, the current position is saved in
 * +8 and +0xa, and the actor receives the downward (target below the current y: handler
 * 0x44e920) or upward (target above: handler 0x44ebe0) motion parameters. Nothing more happens when
 * the target y equals the current one. Short storage is preserved and returns zero. */
int vertrix_actor_start_slide(const void *board, size_t board_size, void *actor, size_t actor_size,
                              int32_t cells_x, int32_t cells_y);

/* Original0x433750: turn the block at (column, row) into a stone. Applies only when the companion
 * slot is empty and the block exists and is not already a stone (kind byte +0x15c is not 5). The
 * block moves to the companion grid with handler 0x44cb50, period 5 and cleared counters, and a new
 * stone (block kind 5, spawned as 0x430800 does) takes its
 * place with the old block's +0xd0 and frame, handler 0x44cab0 and period 5. Returns 1 when
 * applied, 0 when not or on failure. */
int vertrix_board_make_stone(void *board, size_t board_size, int8_t column, int8_t row,
                             const VertrixFactoryServices *services);
#endif
