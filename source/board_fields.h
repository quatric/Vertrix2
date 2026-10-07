#ifndef VERTRIX_BOARD_FIELDS_H
#define VERTRIX_BOARD_FIELDS_H
#include "board_collections.h"
/* Small board and active-piece accessors over raw board storage (at least 0xb7c bytes). Object
 * handles are resolved through VertrixObjectStorage; unresolvable objects return zero. */

/* Original0x431380 (board +0xa60, field 0x168), 0x432000 (+0xa60, 0x17c), 0x431480 (+0xb70,
 * 0x170) and 0x431490 (+0xb78, 0x178): read a dword field of the object whose handle is stored at
 * the given board offset. */
/* Original variants 0x431380, 0x432000, 0x431480, 0x431490: object-field accessors. */
int vertrix_board_object_field(const void *board, size_t board_size, uint32_t pointer_offset,
                               uint32_t field_offset, VertrixObjectStorage resolve, void *context,
                               uint32_t *value);

/* Original0x431d80: store the dword at board +0xa68. */
int vertrix_board_set_a68(void *board, size_t board_size, uint32_t value);

/* Original0x4334a0: clear the byte at +0x838 and store value at +0x839. */
int vertrix_board_reset_counter(void *board, size_t board_size, uint8_t value);

/* Original0x4342f0: increment the byte at +0x838. */
int vertrix_board_bump_counter(void *board, size_t board_size);

/* Original0x432010: 1 when the active piece's signed y (word +0x16) is greater than the board's
 * y word minus 0x48. */
int vertrix_board_piece_below_top(const void *board, size_t board_size,
                                  VertrixObjectStorage resolve, void *context, uint32_t *below);

/* Original0x430090: 1 when the extra object at +0xce0 has handler token 0x44c860. */
int vertrix_board_extra_is_idle(const void *board, size_t board_size, VertrixObjectStorage resolve,
                                void *context, uint32_t *idle);
#endif
