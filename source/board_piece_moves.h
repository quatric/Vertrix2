#ifndef VERTRIX_BOARD_PIECE_MOVES_H
#define VERTRIX_BOARD_PIECE_MOVES_H
#include "actor_gate.h"
#include "board_piece.h"
/* Placement tests and moves of the active piece for a piece shape and rotation. The shape tables
 * (bytes at 0x4f9800 and 0x4f9ad8) are original memory read through VertrixMemoryRead; shape and
 * rotation are the values the original callers leave in registers edx and ebx. All routines return
 * zero when board storage is short, the piece or a table byte cannot be read, or a board cell
 * lies outside the stored board; the results are stored only on success. */

typedef struct
{
    VertrixObjectStorage resolve;
    VertrixMemoryRead read;
    void *context;
} VertrixPieceServices;

/* Original0x42efa0: nonzero table byte 0x4f9800[30 * shape + 5 * rotation + column]. */
int vertrix_board_piece_shape_fits(const void *board, size_t board_size, uint32_t shape,
                                   uint32_t rotation, const VertrixPieceServices *services,
                                   uint32_t *fits);

/* Original0x42f030 (side = -1, left) and 0x42f120 (side = 1, right): 1 when some row of the
 * piece, from top to bottom, has a nonzero byte 0x4f9ad8[13 * (shape + rotation) + row] next to
 * the piece's column: at the board edge (column 0 left, column 4 right) or beside an occupied
 * cell of the block grid (+0x220). */
/* Original variants 0x42f030, 0x42f120: left and right occupied-side queries. */
int vertrix_board_piece_touches_side(const void *board, size_t board_size, uint32_t shape,
                                     uint32_t rotation, int side,
                                     const VertrixPieceServices *services, uint32_t *touches);

/* Original0x42f280: with a piece whose shape fits, store the negated board byte +0x58 at +0xa65.
 * Without the fit nothing changes. */
int vertrix_board_piece_store_negated(void *board, size_t board_size, uint32_t shape,
                                      uint32_t rotation, const VertrixPieceServices *services);

/* Original0x42f2b0: the same store of byte +0xa65 whenever a piece is held, without the test. */
int vertrix_board_piece_store_negated_always(void *board, size_t board_size,
                                             const VertrixPieceServices *services);

/* Original0x42f520 (side = -1) and 0x42f550 (side = 1): when the piece touches that side, store
 * the board byte +0x58 at +0xa64. */
/* Original variants 0x42f520, 0x42f550: left and right touch stores. */
int vertrix_board_piece_store_touch(void *board, size_t board_size, uint32_t shape,
                                    uint32_t rotation, int side,
                                    const VertrixPieceServices *services);

/* Original0x42f6e0 (side = -1, 0x18 added to the piece x word +0xe) and 0x42f720 (side = 1,
 * subtracted): when the piece touches that side, move it by one column. */
/* Original variants 0x42f6e0, 0x42f720: left and right piece shifts. */
int vertrix_board_piece_shift(const void *board, size_t board_size, uint32_t shape,
                              uint32_t rotation, int side, const VertrixPieceServices *services);
#endif
