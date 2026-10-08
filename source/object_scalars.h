#ifndef VERTRIX_OBJECT_SCALARS_H
#define VERTRIX_OBJECT_SCALARS_H
#include "actor_gate.h"
#include "board_cells.h"
/* One-field accessors of library, piece and player objects, and of single global cells. Object
 * storage is raw bytes; short or null storage returns zero and preserves everything. Handles of
 * other objects resolve through VertrixObjectStorage. */

/* Original fragment 0x4126d0: flip the dword at +0x5cc + 4 * index between 1 and 0 (1 becomes 0,
 * any other value becomes 1). Original fragment 0x4126f0 reads it. */
int vertrix_object_toggle_flag(void *storage, size_t size, uint32_t index);
/* Original fragment 0x4126f0: Read the indexed flag at +0x5cc + 4 * index. */
int vertrix_object_flag(const void *storage, size_t size, uint32_t index, uint32_t *value);

/* Original fragment 0x418820 (+0xc0 = value), 0x418840 (+0xbc = value), 0x418830 (+0xbc = +0xc0)
 * and 0x418870 (+0xbc = 0): the timer period and counter of a library object. */
int vertrix_object_set_period(void *storage, size_t size, uint32_t value);
/* Original fragment 0x418840: Store the counter at +0xbc. */
int vertrix_object_set_counter(void *storage, size_t size, uint32_t value);
/* Original fragment 0x418830: Copy the period +0xc0 to counter +0xbc. */
int vertrix_object_counter_to_period(void *storage, size_t size);
/* Original fragment 0x418870: Clear counter +0xbc. */
int vertrix_object_clear_counter(void *storage, size_t size);

/* Original fragment 0x42a940 and 0x42a950: clear the signed byte +0x16c / +0x16d of a piece. */
int vertrix_piece_clear_offset_x(void *storage, size_t size);
/* Original fragment 0x42a950: Clear signed byte +0x16d. */
int vertrix_piece_clear_offset_y(void *storage, size_t size);

/* Original fragment 0x42ba40: 1 when the signed word +0x16 is greater than the signed word +0xae.
 */
int vertrix_object_y_above_limit(const void *storage, size_t size, uint32_t *above);

/* Original fragment 0x43b860 / 0x43b870: set / get dword +0x4e0. Original fragment 0x43b970: dword
 * +0x4e8 is nonzero. Original fragment 0x43bad0 / 0x43bae0: set byte +0x4cd / +0x4cc. Original
 * fragment 0x43bd40: byte +0x4c4 equals 1. Original fragment 0x43cde0: byte +0x4dc = 2 and dword
 * +0x470 = 3. */
int vertrix_player_set_e0(void *storage, size_t size, uint32_t value);
/* Original fragment 0x43b870: Read dword +0x4e0. */
int vertrix_player_e0(const void *storage, size_t size, uint32_t *value);
/* Original fragment 0x43b970: Dword +0x4e8 is nonzero. */
int vertrix_player_has_e8(const void *storage, size_t size, uint32_t *flag);
/* Original fragment 0x43bad0: Store byte +0x4cd. */
int vertrix_player_set_cd(void *storage, size_t size, uint8_t value);
/* Original fragment 0x43bae0: Store byte +0x4cc. */
int vertrix_player_set_cc(void *storage, size_t size, uint8_t value);
/* Original fragment 0x43bd40: Byte +0x4c4 equals one. */
int vertrix_player_c4_is_one(const void *storage, size_t size, uint32_t *flag);
/* Original fragment 0x43cde0: Set byte +0x4dc to two and dword +0x470 to three. */
int vertrix_player_enter_state(void *storage, size_t size);

/* Original fragment 0x43cc90: byte +0x4cc of the object whose handle is at +0x3b0 is not 1. */
int vertrix_player_partner_not_cc_one(const void *storage, size_t size,
                                      VertrixObjectStorage resolve, void *context, uint32_t *flag);

/* Original fragment 0x415b30 / 0x415b40 (array cell = 1 for index) and 0x415d90 (the same for the
 * index held in the global at 0x53bb10), 0x415d60 (read that cell): the arrays are caller storage
 * of count dwords; indices outside them return zero. */
/* Original fragment variants 0x415b30, 0x415b40, 0x415d90: set the selected global cell to one.
 * Projected convenience variants verified in tools/verify_object_scalars.py. */
int vertrix_global_set_cell(uint32_t *cells, uint32_t count, uint32_t index);
/* Original fragment 0x415d60: read the selected global cell; tools/verify_object_scalars.py. */
int vertrix_global_cell(const uint32_t *cells, uint32_t count, uint32_t index, uint32_t *value);

/* Original fragment 0x417f40 and 0x41a930 clear a global dword; 0x41d660 increments one. */
/* Original fragment variants 0x417f40, 0x41a930: clear the selected global dword.
 * Projected convenience variants verified in tools/verify_object_scalars.py. */
void vertrix_global_clear(uint32_t *cell);
/* Original fragment 0x41d660: Increment the supplied global dword. */
void vertrix_global_increment(uint32_t *cell);

/* Original fragment 0x415b10: clear the first 19 dwords of both tables at 0x5344a4 and 0x5344f0. */
void vertrix_global_clear_tables(uint32_t first[19], uint32_t second[19]);

/* Original fragment 0x415d40: increment the index global at 0x53bb10; 1 while it has not reached 7.
 */
int vertrix_global_next_index(uint32_t *index);

/* Original fragment 0x415530: when the global at 0x532b40 equals 1, clear the globals at 0x532b44
 * and 0x532b48. */
void vertrix_global_reset_pair(uint32_t mode, uint32_t *first, uint32_t *second);

/* Original0x418150: unsigned comparison of two dwords: -1, 0 or 1. */
int32_t vertrix_compare_unsigned(uint32_t left, uint32_t right);

/* Original0x425e00: number of the first seven dwords of the table that are not 0xffffffff. */
uint32_t vertrix_table_used_count(const uint32_t table[7]);

/* Original fragment 0x43bd60: 0 when byte +0x4cc of the object whose handle is at +0x3b0 is 1 or 4.
 */
int vertrix_player_partner_free(const void *storage, size_t size, VertrixObjectStorage resolve,
                                void *context, uint32_t *flag);
/* Full global APIs use 32-bit wrapping indexed addresses, with no native array bounds
 * projection. Read/write boundaries report availability; late failure retains earlier writes
 * and leaves result untouched. Null required boundaries/result fail before effects. */
/* Original 0x415b30: Set indexed 0x5344a4 to one; return caller EAX. */
int vertrix_global_set_first_cell_full(uint32_t eax, VertrixMemoryRead read,
                                       VertrixMemoryWrite write, void *context, uint32_t *result);

/* Original 0x415b40: Set indexed 0x5344f0 to one; return caller EAX. */
int vertrix_global_set_second_cell_full(uint32_t eax, VertrixMemoryRead read,
                                        VertrixMemoryWrite write, void *context, uint32_t *result);

/* Original 0x415d90: Read index 0x53bb10, set indexed 0x53baf4 to one and return index. */
int vertrix_global_set_current_cell_full(uint32_t eax, VertrixMemoryRead read,
                                         VertrixMemoryWrite write, void *context, uint32_t *result);

/* Original 0x415d60: Read index 0x53bb10 and return indexed 0x53bad8. */
int vertrix_global_read_current_cell_full(uint32_t eax, VertrixMemoryRead read,
                                          VertrixMemoryWrite write, void *context,
                                          uint32_t *result);

/* Original 0x41a930: Clear 0x54004c and preserve caller EAX. */
int vertrix_global_clear_full(uint32_t eax, VertrixMemoryRead read, VertrixMemoryWrite write,
                              void *context, uint32_t *result);

/* Original 0x41d660: Increment 0x5329f8 with dword wrapping; preserve caller EAX. */
int vertrix_global_increment_full(uint32_t eax, VertrixMemoryRead read, VertrixMemoryWrite write,
                                  void *context, uint32_t *result);

/* Original 0x415b10: Clear 19 pairs at 0x5344a4/0x5344f0, interleaved in ascending order; return
 * 0x4c. */
int vertrix_global_clear_tables_full(uint32_t eax, VertrixMemoryRead read, VertrixMemoryWrite write,
                                     void *context, uint32_t *result);

/* Original 0x415d40: Increment 0x53bb10; return one unless the new value equals seven. */
int vertrix_global_next_index_full(uint32_t eax, VertrixMemoryRead read, VertrixMemoryWrite write,
                                   void *context, uint32_t *result);

/* Original 0x415530: When 0x532b40 equals one, clear 0x532b48 then 0x532b44; preserve caller EAX.
 */
int vertrix_global_reset_pair_full(uint32_t eax, VertrixMemoryRead read, VertrixMemoryWrite write,
                                   void *context, uint32_t *result);

/* Complete object APIs below preserve original normal-return values. Bounded storage APIs
 * return zero for short/null storage without writes. */

/* Original 0x418820: write dword to +0xc0; return the original object token. */
uint32_t vertrix_object_set_period_full(void *storage, size_t size, uint32_t object,
                                        uint32_t value);

/* Original 0x418840: write dword to +0xbc; return the original object token. */
uint32_t vertrix_object_set_counter_full(void *storage, size_t size, uint32_t object,
                                         uint32_t value);

/* Original 0x418870: clear +0xbc; return the original object token. */
uint32_t vertrix_object_clear_counter_full(void *storage, size_t size, uint32_t object);

/* Original 0x42a940: clear +0x16c; return the original object token. */
uint32_t vertrix_piece_clear_offset_x_full(void *storage, size_t size, uint32_t object);

/* Original 0x42a950: clear +0x16d; return the original object token. */
uint32_t vertrix_piece_clear_offset_y_full(void *storage, size_t size, uint32_t object);

/* Original 0x42ba40: return one when signed word +0x16 exceeds signed word +0xae, else zero. */
uint32_t vertrix_object_y_above_limit_full(const void *storage, size_t size);

/* Original 0x43b860: write dword to +0x4e0; return the original object token. */
uint32_t vertrix_player_set_e0_full(void *storage, size_t size, uint32_t object, uint32_t value);

/* Original 0x43b870: return dword +0x4e0. */
uint32_t vertrix_player_e0_full(const void *storage, size_t size);

/* Original 0x43bad0: write low byte to +0x4cd; return the original object token. */
uint32_t vertrix_player_set_cd_full(void *storage, size_t size, uint32_t object, uint32_t value);

/* Original 0x43bae0: write low byte to +0x4cc; return the original object token. */
uint32_t vertrix_player_set_cc_full(void *storage, size_t size, uint32_t object, uint32_t value);

/* Original 0x43cde0: write byte +0x4dc=2, then dword +0x470=3; return the original object token. */
uint32_t vertrix_player_enter_state_full(void *storage, size_t size, uint32_t object);

/* Full address-boundary APIs report availability separately from original eax in result.
 * Required boundaries/result must exist before effects. Late boundary failure preserves
 * earlier writes and leaves result untouched. All guest address arithmetic wraps in 32 bits. */
/* Original 0x4126d0: read indexed +0x5cc, write zero if it was one, otherwise one;
 * return object + index*4, excluding the +0x5cc field displacement. */
int vertrix_object_toggle_flag_full(uint32_t object, uint32_t index, VertrixMemoryRead read,
                                    VertrixMemoryWrite write, void *context, uint32_t *result);
/* Original 0x4126f0: return the indexed dword at object + index*4 +0x5cc. */
int vertrix_object_flag_full(uint32_t object, uint32_t index, VertrixMemoryRead read, void *context,
                             uint32_t *result);
/* Original 0x43cc90: read partner handle at object+0x3b0, then its byte +0x4cc;
 * return one unless that byte equals one. */
int vertrix_player_partner_not_cc_one_full(uint32_t object, VertrixMemoryRead read, void *context,
                                           uint32_t *result);
/* Original 0x43bd60: read partner handle at object+0x3b0, then its byte +0x4cc;
 * return zero when that byte is one or four, otherwise one. */
int vertrix_player_partner_free_full(uint32_t object, VertrixMemoryRead read, void *context,
                                     uint32_t *result);
#endif
