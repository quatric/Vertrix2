#ifndef VERTRIX_BOARD_PIECE_H
#define VERTRIX_BOARD_PIECE_H
#include "piece_children.h"
/* Board-level queries and updates of the active piece (handle at board +0xa60). Board storage is
 * raw board bytes of at least 0xa64 bytes; the piece is resolved through VertrixObjectStorage.
 * All routines return zero when storage is short or an object does not resolve. */

/* Original0x4320c0: report whether the board holds an active piece. */
int vertrix_board_has_piece(const void *board, size_t board_size, uint32_t *has_piece);

/* Original0x42f2e0: store the board byte at +0x58 in all 65 bytes at +0x19d..+0x1dd. */
int vertrix_board_fill_cells(void *board, size_t board_size);

/* Original0x431fa0: read the kind bytes of the three children of the active piece (0x42a980). */
int vertrix_board_piece_child_kinds(const void *board, size_t board_size,
                                    VertrixObjectStorage resolve, void *context,
                                    uint8_t kinds[VERTRIX_PIECE_CHILD_COUNT]);

/* Original0x431fb0: put the three children of the active piece into their flashing state (byte
 * +0x93 = 1, +0x95 = 0, +0x4e = 0x32, word +0x48 = 0x14) and set the piece dword +0x17c to 1. */
int vertrix_board_flash_children(const void *board, size_t board_size, VertrixObjectStorage resolve,
                                 void *context);

/* Original0x432040 (right = 1, column >= 5) and 0x432080 (right = 0, column <= 0): compare the
 * active piece's board column, (piece x - board x) / 24 with signed 16-bit positions, with the
 * edge of the five-column board. */
int vertrix_board_piece_past_edge(const void *board, size_t board_size,
                                  VertrixObjectStorage resolve, void *context, int right,
                                  uint32_t *past);

/* Original0x431340: the board column of the active piece. */
int vertrix_board_piece_column(const void *board, size_t board_size, VertrixObjectStorage resolve,
                               void *context, int32_t *column);

/* Original0x431b20: board column and rows of the active piece. The top row uses the piece y and
 * the bottom row y + 0x47 truncated to a signed 16-bit position; the column is the same for both.
 */
int vertrix_board_piece_span(const void *board, size_t board_size, VertrixObjectStorage resolve,
                             void *context, int32_t *column, int32_t *top, int32_t *bottom);

/* Original0x431c10: kind byte (sign-extended) of the child at index, or -1 without a piece. */
int vertrix_board_piece_child_kind(const void *board, size_t board_size,
                                   VertrixObjectStorage resolve, void *context, uint32_t index,
                                   int32_t *kind);
#endif
