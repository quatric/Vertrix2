#ifndef VERTRIX_PIECE_OFFSET_CLEAR_H
#define VERTRIX_PIECE_OFFSET_CLEAR_H
#include <stddef.h>
#include <stdint.h>
/* Board pending active-piece offsets are signed X/Y bytes +0xa64/+0xa65,
 * forwarded by 0x42fc60/0x42fc70 to piece child-position offsets +0x16c/+0x16d.
 * These complete clear wrappers preserve all incoming registers, including EDX;
 * original EAX is the supplied token, returned through result. Native status
 * reports valid backing/output. Null/short backing or output rejects unchanged. */
/* Original 0x42f870: clear the board's pending active-piece X offset. */
int vertrix_board_piece_clear_offset_x_full(void *storage, size_t size, uint32_t token,
                                            uint32_t *result);
/* Original 0x42f880: clear the board's pending active-piece Y offset. */
int vertrix_board_piece_clear_offset_y_full(void *storage, size_t size, uint32_t token,
                                            uint32_t *result);
/* The adjacent board initializers clear/fill 65 cell-value bytes +0x19d..+0x1dd,
 * column-major with 13 rows per column. This is the plane filled from board +0x58
 * by 0x42f2e0. EAX returns token+65 with 32-bit wrapping. */
/* Original 0x42f860: clear cell values and preserve incoming EDX/EBX/ECX/ESI/EDI/EBP. */
int vertrix_board_cell_values_clear_full(void *storage, size_t size, uint32_t token,
                                         uint32_t *result);
/* Original 0x42f8e0: fill cell values with incoming EDX's low byte. Original EAX
 * and EDX both return token+65; other registers are preserved. Null/short storage
 * or missing either output rejects without changing storage or outputs. */
int vertrix_board_cell_values_fill_full(void *storage, size_t size, uint32_t token, uint32_t edx,
                                        uint32_t *eax_result, uint32_t *edx_result);
#endif
