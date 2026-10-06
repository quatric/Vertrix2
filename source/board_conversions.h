#ifndef VERTRIX_BOARD_CONVERSIONS_H
#define VERTRIX_BOARD_CONVERSIONS_H
#include "block_factory.h"
#include "board_actions.h"
#include "fixed_point.h"
/* Conversions of the marked cells of a board (markers equal to 1, at +0xb94): each marked block
 * is retired and replaced by a freshly spawned block. The grids, markers and services are those
 * of board_actions.h. All three return 1 on success (also without markers) and 0 on failure. */

/* Original0x436720: for every marked cell, in row order: mark it 2, move its block to the
 * companion grid with handler 0x44d480, then put a new block of kind index in its place with the
 * old block's +0xd0 and frame and handler 0x44d5f0. */
int vertrix_board_replace_marked(void *board, size_t board_size, uint32_t index,
                                 const VertrixFactoryServices *services);

/* Original0x437060: for every marked cell, in row order and without changing the markers: move the
 * block to the companion grid (handler 0x44e6e0) and put a new block in its place (handler
 * 0x44c860) whose +0x58 is the old +0xd0 divided by 12. mode 6 spawns kind 6; mode -2 spawns the
 * kind of a draw below 5 (one draw per cell). Other modes read an uninitialised stack variable
 * in the original and are rejected. */
int vertrix_board_replace_marked_scaled(void *board, size_t board_size, int32_t mode,
                                        const VertrixFactoryServices *services);

/* Original0x437350: for every marked cell, in row order and without changing the markers: give
 * the block its handler 0x44d8b0 and put a block of the same kind in the companion cell
 * (handler 0x44da70, +0xd0 = 12). */
int vertrix_board_mirror_marked(void *board, size_t board_size,
                                const VertrixFactoryServices *services);

/* Original0x437be0: for every marked cell, in marker order: move its block to the companion grid
 * and make it fly from the board origin offset by (0x3c, 0x9c): the block stores the distance to
 * that point in word +0x2a and the point in words +0x2c and +0x2e, the heading to it modulo 360 in
 * word +0x24 and a draw below 8 plus 3 in word +0x28, takes the handler 0x44e120, power 0x64, +0x93
 * = 1, dwords +0x58..+0x6c = 0, 300, 1, 0, 1, 1, a period of 2 steps and cleared timers. The angle
 * table is that of fixed_point.h. Returns 1 on success, and 0 without markers or on failure
 * (including the faults the original has for coincident points). */
int vertrix_board_scatter_marked(void *board, size_t board_size,
                                 const uint16_t angle_table[VERTRIX_RATIO_TABLE_SIZE],
                                 const VertrixFactoryServices *services);

/* Original0x437b70: for each of the 13 rows draw once below 48 (the value is not used, but the
 * draw advances the generator), then give the block of every occupied companion cell of the row
 * the dword +0x68 = 0x30. Returns 1 on success and 0 when an object cannot be resolved. */
int vertrix_board_prime_companions(void *board, size_t board_size,
                                   const VertrixFactoryServices *services);

/* Original0x437d70: for every marked cell, in row order, move its block to the companion grid and
 * split it in two halves that fly apart. The old block takes the handler 0x44e250, power 0x64,
 * +0x4f = 0x32, word +0x50 = 0x14, word +0x10 = the board x word minus 24 and word +0x12 = a draw
 * below 3 plus 1; a new block of the same kind (spawned as 0x430800 does) takes the old x, y,
 * +0xd0 and frame, the board x word plus 125 as word +0x10 and the old +0x12. Both get a
 * period of two steps, +0x93 = 1, cleared timers, word +0x4c = 10 and in word +0x4a the distance
 * of their words +0x10 and x times 100, divided by 60. Returns 1 on success, and 0 without markers
 * or on failure. */
int vertrix_board_split_marked(void *board, size_t board_size,
                               const VertrixFactoryServices *services);

/* Original0x4368e0: replace the three child blocks of the active piece (handle at board +0xa60,
 * children at +0x15c, +0x160 and +0x164 of the piece) by new blocks of the given kinds, spawned as
 * 0x430800 does. The old child is saved at +0x170.. of the piece; it takes the handler 0x44f7e0,
 * power 0x64, a period of 5 steps and one step of +0xd0, and the new one its +0xd0, frame and
 * the handler 0x44f880. Empty children are only saved. Returns 1 on success, 0 on failure. */
int vertrix_piece_replace_children(void *board, size_t board_size, const uint32_t kinds[3],
                                   const VertrixFactoryServices *services);

/* Original0x436b40: for the first count_first pending markers of the first board and the first
 * count_second of the second board (each marker is marked 2 as it is taken), move the block to the
 * companion grid with handler 0x44e380, power 0x64 and a period of 5 steps, and put a new block of
 * a drawn kind (below 5) in its place with the old +0xd0 and frame and handler 0x44e4a0. Returns 1
 * on success, and 0 when fewer markers than requested exist or on failure. */
int vertrix_boards_convert_counts(void *first, size_t first_size, void *second, size_t second_size,
                                  uint32_t count_first, uint32_t count_second,
                                  const VertrixFactoryServices *services);

/* 0x436b40 as above, additionally reporting through last_second_old (when not NULL) the old block
 * of the last conversion on the second board, which the original leaves in ebx. */
int vertrix_boards_convert_counts_traced(void *first, size_t first_size, void *second,
                                         size_t second_size, uint32_t count_first,
                                         uint32_t count_second,
                                         const VertrixFactoryServices *services,
                                         uint32_t *last_second_old);

/* Original0x436d80: count_first times on the first board and then count_second times on the
 * second, when a pending marker exists: draw one of the pending markers (a draw below their count),
 * mark it 2, move its block to the companion grid with handler 0x44e510, power 0x64 and a period of
 * 5 steps, and put a new block of the given kind in its place with the old +0xd0 and frame, handler
 * 0x44e590 and +0x44 = 0. Rounds without pending markers do nothing. Returns 1 on success and 0 on
 * failure. */
int vertrix_boards_convert_random(void *first, size_t first_size, void *second, size_t second_size,
                                  uint32_t kind, uint32_t count_first, uint32_t count_second,
                                  const VertrixFactoryServices *services);

/* Original0x438540: with markers 1 and 2 both present, move every block of the board to the
 * companion grid, then for each column bring the blocks of the markers 2 and then 1 (bottom first)
 * back to the block grid from row 12 upward, each sliding to its new cell as 0x438470 does. When
 * no block of the block grid has a start position (+8, +0xa) different from its target (+0x10,
 * +0x18) every block gets +0x93 = 0, +0x95 = 1 and +0x4e = 0x32. *moving receives the original
 * result: 1 when some block is sliding and 0 otherwise (also without both markers). Returns 1 on
 * success and 0 on failure. */
int vertrix_board_collapse_marked(void *board, size_t board_size,
                                  const VertrixFactoryServices *services, uint32_t *moving);

/* Original0x439260: snapshot the kinds of the 65 slots into the board (as 0x4327e0 does, at
 * +0x1de), count the cells of kinds 0..4 (empty cells, stones and bombs are ignored), list the
 * kinds that occur in ascending order, shuffle the list (one draw below the list length per entry,
 * swapping the entry with the drawn one; only for more than one kind) and report the smaller of the
 * length and 3 in *count with the list's first five entries in out (entries past the list length
 * are stale stack words in the original and are zero here). Returns 1 on success and 0 on
 * failure. */
int vertrix_board_pick_kinds(void *board, size_t board_size, const VertrixFactoryServices *services,
                             uint32_t out[5], uint32_t *count);

/* Original0x437fe0: for every marker 1 and then for every marker 2, in row order and without
 * changing the markers: draw a spin below 8 (its value plus 4, less 7 when above 7, goes to the old
 * block's word +0x24 and the draw itself to the new one's), move the block to the companion grid
 * (handler 0x44cfd0, power 0x64, a period of a draw below 4 plus 4 steps, +0x93 = 1, +0x44 = 0x10,
 * dwords +0x58..+0x6c = 0, 4, 1, 0, 2, 1, words +0x8/+0xa = its position) and put a new block of
 * a drawn kind (below 5; a stone for the markers 2, without a draw) in its place at the same
 * position with the old +0xd0, period and frame, handler 0x44ccd0, power 0x32, +0x45 = 0x10 and the
 * same dwords. *result receives the original result: 1 when any marker existed and 0
 * otherwise. Returns 1 on success and 0 on failure. */
int vertrix_board_spin_marked(void *board, size_t board_size,
                              const VertrixFactoryServices *services, uint32_t *result);

/* Original0x4378c0: with at least one marker 1, move every such block, in row order, to the
 * companion grid with handler 0x44de20, power 0x64, a period of 2 steps, +0x93 = 1, the angle word
 * +0x24 = 72 * column (the original also averages the block positions and measures their largest
 * distance, but never uses the results), word +0x28 = 8, dwords +0x58 = 0, +0x5c = 300, +0x60 = 1,
 * words +0x18 = 0, +0x46 = 1, +0x12 = +0x1a = 5, +0x4f = 0, +0x50 = 1, +0x8 = the board x word plus
 * 60, +0xa = its own y word plus 12 and cleared timers. Then, for each of the 13 rows, draw an
 * offset below 360 and add it to the angle word of every companion block of the row (the sum is
 * cut to 16 bits, then taken modulo 360). Returns 1 when the markers existed and 0 otherwise or on
 * failure. */
int vertrix_board_swirl_marked(void *board, size_t board_size,
                               const VertrixFactoryServices *services);

/* Original0x438960: give every block of the block grid, in row order (parity alternating over all
 * 65 cells, empty ones included, starting even), the motion of a mode: period 4 steps and cleared
 * counter, then
 *  mode 0: word +0x4c = 10, +0x48 = 0, +0x4a = 100 (even) or -100 (odd), handler 0x44f120 /
 * 0x44f180; mode 1: word +0x4c = 8, +0x48 = 0, +0x4a = -100, handler 0x44f240; mode 2: dwords +0x80
 * = +0x84 = 0, +0x88 = a draw below 5 plus 2, byte +0x8c = 1, handler 0x44f390 or (after a second
 * draw below 2 that is not zero) 0x44f3e0; mode 3 and 4: byte +0x94 = 0, byte +0x52 = 0 / 1, word
 * +0x4c = 10, +0x48 = 0, +0x4a = 100 (even) or -100 (odd), handler 0x44f4a0 / 0x44f500 (mode 3) or
 * 0x44f5d0 / 0x44f630 (mode 4). Other modes change nothing. Returns 1 on success and 0 on failure.
 */
int vertrix_board_set_motion(void *board, size_t board_size, uint8_t mode,
                             const VertrixFactoryServices *services);

/* Original0x4316c0: release the five objects of the collection at board +0x988 (destroy with flag
 * 2 in order, slots cleared; 0x42ec00), then, only when low < high (signed), snapshot the slot
 * kinds into +0x1de (as 0x4327e0), set the five bytes +0x980..+0x984 to 5 and fill the collection
 * with five new blocks of kind 5 (spawned as 0x430800 does), each with handler 0x44f700 and period
 * 4 steps. *placed is 1 when the blocks were created and 0 when low >= high. Returns zero on
 * failure (an unresolvable object or a failed spawn). */
int vertrix_board_place_stones(void *board, size_t board_size, int32_t low, int32_t high,
                               const VertrixFactoryServices *services, VertrixBoardDestroy destroy,
                               void *destroy_context, uint32_t *placed);

/* The board data of the row dealing routines 0x431780 and 0x431930: the 13 byte rows of the table
 * at 0x4f9ad8 (row 13 * (a + b) .. + 12 is read, so pattern_rows must hold 13 * (a + b + 1) bytes)
 * and the period steps (the byte at 0x4f9ad0). */
typedef struct
{
    const uint8_t *pattern;
    size_t pattern_size;
    uint8_t period_steps;
} VertrixDealTable;

/* Original0x431780 (first row, collection +0x9e8, bytes +0x9da, kinds of the first column) and
 * Original0x431930 (second row, collection +0xa2c, bytes +0xa1c, kinds of the second column
 * +0x212): clear the 13 entry collection (destroy flag 2), then deal one row. A row is dealt only
 * when b < 1 (signed) and the any-nonzero flag of the pattern group a (0x417df0) is greater than
 * b unsigned, that is, b == 0 and the group has a nonzero entry. The kinds are snapshotted as
 * 0x4327e0 does; for every of the 13 positions the pattern byte 2 stores 5, 1 draws a value below 5
 * (redrawn while it equals the previous position's value or the kind of the position) and 0
 * stores 0xff. Nothing counted (no 1 or 2) returns 0; otherwise every position that is not 0xff
 * gets a block of that kind (spawned as 0x430800 does) with handler 0x44f700 and the period steps
 * of the table. *dealt is 1 when a row was dealt. Returns 0 on failure. */
int vertrix_board_deal_first_row(void *board, size_t board_size, int32_t a, int32_t b,
                                 const VertrixDealTable *table,
                                 const VertrixFactoryServices *services,
                                 VertrixBoardDestroy destroy, void *destroy_context,
                                 uint32_t *dealt);
int vertrix_board_deal_second_row(void *board, size_t board_size, int32_t a, int32_t b,
                                  const VertrixDealTable *table,
                                  const VertrixFactoryServices *services,
                                  VertrixBoardDestroy destroy, void *destroy_context,
                                  uint32_t *dealt);

/* Original0x433550: snapshot the slot kinds into +0x1de (as 0x4327e0) and find the smallest
 * distance k >= 1 at which no cell of kind 6 has a cell on the board at distance k in the
 * directions selected by the mode byte +0x839: 1, 3 and 4 look left and right (columns 0..4), 2, 3
 * and 4 look up and down (rows 0..12) and 4 also looks up and down from every column that has a
 * neighbouring column (column > 0 and column < 4 each add the vertical check). *reach is k, the
 * original's result. Returns zero for an unresolvable object or short storage. */
int vertrix_board_marker_reach(void *board, size_t board_size,
                               const VertrixFactoryServices *services, uint32_t *reach);

/* Original0x436150: with at least two markers equal to 1, draw two of them (the first draw below
 * the count over the markers in row order, the second below the count minus one over those left
 * after the first became 2), mark both 2 and swap the kinds of their blocks: each block moves to
 * the companion grid with handler 0x44d1e0, power 0x64 and period 5, and a new block of the other
 * block's kind (spawned as 0x430800 does) takes its cell with the old block's +0xd0 and frame,
 * period 5 and cleared counters; its handler is 0x44c860 when kind_class[old kind] equals
 * kind_class[new kind] (the table at 0x53bcc8) and 0x44d330 otherwise. *swapped is 1 when done.
 * Returns zero on failure. */
int vertrix_board_swap_marked(void *board, size_t board_size, const uint8_t *kind_class,
                              size_t kind_class_size, const VertrixFactoryServices *services,
                              uint32_t *swapped);
#endif
