#ifndef VERTRIX_OBJECT_SCALARS_H
#define VERTRIX_OBJECT_SCALARS_H
#include "board_cells.h"
/* One-field accessors of library, piece and player objects, and of single global cells. Object
 * storage is raw bytes; short or null storage returns zero and preserves everything. Handles of
 * other objects resolve through VertrixObjectStorage. */

/* Original0x4126d0: flip the dword at +0x5cc + 4 * index between 1 and 0 (1 becomes 0, any other
 * value becomes 1). Original0x4126f0 reads it. */
int vertrix_object_toggle_flag(void *storage, size_t size, uint32_t index);
/* Original 0x4126f0: Read the indexed flag at +0x5cc + 4 * index. */
int vertrix_object_flag(const void *storage, size_t size, uint32_t index, uint32_t *value);

/* Original0x418820 (+0xc0 = value), 0x418840 (+0xbc = value), 0x418830 (+0xbc = +0xc0) and
 * 0x418870 (+0xbc = 0): the timer period and counter of a library object. */
int vertrix_object_set_period(void *storage, size_t size, uint32_t value);
/* Original 0x418840: Store the counter at +0xbc. */
int vertrix_object_set_counter(void *storage, size_t size, uint32_t value);
/* Original 0x418830: Copy the period +0xc0 to counter +0xbc. */
int vertrix_object_counter_to_period(void *storage, size_t size);
/* Original 0x418870: Clear counter +0xbc. */
int vertrix_object_clear_counter(void *storage, size_t size);

/* Original0x42a940 and 0x42a950: clear the signed byte +0x16c / +0x16d of a piece. */
int vertrix_piece_clear_offset_x(void *storage, size_t size);
/* Original 0x42a950: Clear signed byte +0x16d. */
int vertrix_piece_clear_offset_y(void *storage, size_t size);

/* Original0x42ba40: 1 when the signed word +0x16 is greater than the signed word +0xae. */
int vertrix_object_y_above_limit(const void *storage, size_t size, uint32_t *above);

/* Original0x43b860 / 0x43b870: set / get dword +0x4e0. Original0x43b970: dword +0x4e8 is
 * nonzero. Original0x43bad0 / 0x43bae0: set byte +0x4cd / +0x4cc. Original0x43bd40: byte +0x4c4
 * equals 1. Original0x43cde0: byte +0x4dc = 2 and dword +0x470 = 3. */
int vertrix_player_set_e0(void *storage, size_t size, uint32_t value);
/* Original 0x43b870: Read dword +0x4e0. */
int vertrix_player_e0(const void *storage, size_t size, uint32_t *value);
/* Original 0x43b970: Dword +0x4e8 is nonzero. */
int vertrix_player_has_e8(const void *storage, size_t size, uint32_t *flag);
/* Original 0x43bad0: Store byte +0x4cd. */
int vertrix_player_set_cd(void *storage, size_t size, uint8_t value);
/* Original 0x43bae0: Store byte +0x4cc. */
int vertrix_player_set_cc(void *storage, size_t size, uint8_t value);
/* Original 0x43bd40: Byte +0x4c4 equals one. */
int vertrix_player_c4_is_one(const void *storage, size_t size, uint32_t *flag);
/* Original 0x43cde0: Set byte +0x4dc to two and dword +0x470 to three. */
int vertrix_player_enter_state(void *storage, size_t size);

/* Original0x43cc90: byte +0x4cc of the object whose handle is at +0x3b0 is not 1. */
int vertrix_player_partner_not_cc_one(const void *storage, size_t size,
                                      VertrixObjectStorage resolve, void *context, uint32_t *flag);

/* Original0x415b30 / 0x415b40 (array cell = 1 for index) and 0x415d90 (the same for the index held
 * in the global at 0x53bb10), 0x415d60 (read that cell): the arrays are caller storage of count
 * dwords; indices outside them return zero. */
/* Original variants 0x415b30, 0x415b40, 0x415d90: set the selected global cell to one.
 * Complete callable variants verified in tools/verify_object_scalars.py. */
int vertrix_global_set_cell(uint32_t *cells, uint32_t count, uint32_t index);
/* Original 0x415d60: read the selected global cell; tools/verify_object_scalars.py. */
int vertrix_global_cell(const uint32_t *cells, uint32_t count, uint32_t index, uint32_t *value);

/* Original0x417f40 and 0x41a930 clear a global dword; 0x41d660 increments one. */
/* Original variants 0x417f40, 0x41a930: clear the selected global dword.
 * Complete callable variants verified in tools/verify_object_scalars.py. */
void vertrix_global_clear(uint32_t *cell);
/* Original 0x41d660: Increment the supplied global dword. */
void vertrix_global_increment(uint32_t *cell);

/* Original0x415b10: clear the first 19 dwords of both tables at 0x5344a4 and 0x5344f0. */
void vertrix_global_clear_tables(uint32_t first[19], uint32_t second[19]);

/* Original0x415d40: increment the index global at 0x53bb10; 1 while it has not reached 7. */
int vertrix_global_next_index(uint32_t *index);

/* Original0x415530: when the global at 0x532b40 equals 1, clear the globals at 0x532b44 and
 * 0x532b48. */
void vertrix_global_reset_pair(uint32_t mode, uint32_t *first, uint32_t *second);

/* Original0x418150: unsigned comparison of two dwords: -1, 0 or 1. */
int32_t vertrix_compare_unsigned(uint32_t left, uint32_t right);

/* Original0x425e00: number of the first seven dwords of the table that are not 0xffffffff. */
uint32_t vertrix_table_used_count(const uint32_t table[7]);

/* Original0x43bd60: 0 when byte +0x4cc of the object whose handle is at +0x3b0 is 1 or 4. */
int vertrix_player_partner_free(const void *storage, size_t size, VertrixObjectStorage resolve,
                                void *context, uint32_t *flag);
#endif
