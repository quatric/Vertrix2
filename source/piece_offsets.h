#ifndef VERTRIX_PIECE_OFFSETS_H
#define VERTRIX_PIECE_OFFSETS_H
#include <stddef.h>
#include <stdint.h>

/* Piece +0x16c/+0x16d are signed X/Y offsets added to child positions by 0x42a800.
 * Board +0xa64/+0xa65 are pending active-piece offsets, sign-extended and forwarded
 * to the piece setters by 0x42fc60..0x42fc7f. Setters store EDX's low byte and return
 * the original object token through result; the C return reports storage success.
 * Null/short backing or null result fails without changing storage or result. */
/* Original 0x42a960: set the piece child-position X offset. */
int vertrix_piece_set_offset_x_full(void *storage, size_t size, uint32_t token, uint32_t edx,
                                    uint32_t *result);
/* Original 0x42a970: set the piece child-position Y offset. */
int vertrix_piece_set_offset_y_full(void *storage, size_t size, uint32_t token, uint32_t edx,
                                    uint32_t *result);
/* Original 0x42f890: set the board's pending active-piece X offset. */
int vertrix_board_piece_set_offset_x_full(void *storage, size_t size, uint32_t token, uint32_t edx,
                                          uint32_t *result);
/* Original 0x42f8a0: set the board's pending active-piece Y offset. */
int vertrix_board_piece_set_offset_y_full(void *storage, size_t size, uint32_t token, uint32_t edx,
                                          uint32_t *result);
#endif
