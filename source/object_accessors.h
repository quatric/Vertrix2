#ifndef VERTRIX_OBJECT_ACCESSORS_H
#define VERTRIX_OBJECT_ACCESSORS_H
#include <stddef.h>
#include <stdint.h>

/* Small field accessors of the actor and player objects, cleaned up from the lifted routines.
 * Each one returns 0 (and changes nothing) for storage too short for the field. */

/* Original fragments 0x4ac500, 0x4ac370, 0x4ac600: the dword at offset 0xbc, 0xcc or
 * 0xdc, respectively, grows by elapsed, the frame delta kept in global 0x5bd834. */
int vertrix_actor_add_elapsed(void *actor, size_t size, uint32_t offset, uint32_t elapsed);

/* Original fragment 0x4ac520: 1 when the clock at +0xbc has reached the period at +0xc0 (unsigned).
 */
int vertrix_actor_clock_reached(const void *actor, size_t size, uint32_t *reached);

/* Original fragment 0x418830: the clock at +0xbc is set to the period at +0xc0. */
int vertrix_actor_clock_to_period(void *actor, size_t size);

/* Original fragment 0x4ac920: the dword at +0x154 takes the dword at +0xec. */
int vertrix_actor_select_ec(void *actor, size_t size);
/* Original fragment 0x4ac940: the dword at +0x154 takes the dword at +0xf0. */
int vertrix_actor_select_f0(void *actor, size_t size);

/* Original fragment 0x43a4f0: the bytes at +0x168, +0x169 and +0x16a take the low bytes of edx, ebx
 * and ecx. */
int vertrix_player_set_bytes_168(void *player, size_t size, uint32_t first, uint32_t second,
                                 uint32_t third);

/* Original fragment 0x43b970: 1 when the dword at +0x4e8 is not zero. */
int vertrix_player_flag_4e8(const void *player, size_t size, uint32_t *set);

/* Original fragment 0x43ba70: 1 when the bonus meter at +0x18c is 3 (full). */
int vertrix_player_bonus_meter_full(const void *player, size_t size, uint32_t *full);

/* Original fragment 0x4320c0: 1 when the dword at +0xa60 is not zero. */
int vertrix_player_flag_a60(const void *player, size_t size, uint32_t *set);

/* Original fragment 0x43bd40: 1 when the byte at +0x4c4 is 1. */
int vertrix_player_byte_4c4_is_one(const void *player, size_t size, uint32_t *is_one);

/* Original fragment 0x47f8e0: the dword at +0x18 takes `value`. */
int vertrix_object_set_18(void *object, size_t size, uint32_t value);

/* Original fragments 0x4ac390, 0x4ac620, 0x4ac520: counter/limit offsets (0xcc, 0xd0),
 * (0xdc, 0xe0) and (0xbc, 0xc0), respectively; 1 when the counter is at least the limit
 * (unsigned). */
int vertrix_actor_counter_pair_reached(const void *actor, size_t size, uint32_t counter_offset,
                                       uint32_t limit_offset, uint32_t *reached);

/* Original fragments 0x4ac470, 0x4ac7b0, 0x4ac840: the dword at offset 0xd0, 0xc0 or
 * 0xe0, respectively, becomes 12 * value (wrapping), the frame count converted to a period. */
int vertrix_actor_set_times_twelve(void *actor, size_t size, uint32_t offset, uint32_t value);

/* Original fragments 0x42ef60, 0x42ef80, 0x42f7d0, 0x42f7f0, 0x42f810, 0x42f830:
 * byte ranges (start, count) are (0x99c, 5), (0x9a1, 5), (0x9a6, 13), (0x9b3, 13),
 * (0x9c0, 13) and (0x9cd, 13), respectively; fill with the low byte of value. */
int vertrix_player_fill_bytes(void *player, size_t size, uint32_t start, uint32_t count,
                              uint32_t value);

/* Original fragment 0x425de0: the first seven dwords of the object become 0xffffffff. */
int vertrix_object_clear_slots(void *object, size_t size);

/* Original 0x418150: -1, 0 or 1 as the first value is below, equal to or above the second
 * (unsigned). */
int32_t vertrix_compare_u32(uint32_t first, uint32_t second);
/* The APIs below preserve the complete original eax. Identity tokens are supplied explicitly,
 * independently of native storage pointers. Invalid storage returns zero without writes. */

/* Original variants 0x4ac500, 0x4ac370, 0x4ac600: offsets 0xbc/0xcc/0xdc. Add the supplied
 * original frame delta and return the unchanged actor token. */
uint32_t vertrix_actor_advance_elapsed(void *actor, size_t size, uint32_t object, uint32_t offset,
                                       uint32_t elapsed);
/* Original 0x418830: copy period +0xc0 to clock +0xbc and return the actor token. */
uint32_t vertrix_actor_sync_clock_period(void *actor, size_t size, uint32_t object);
/* Original variants 0x4ac920, 0x4ac940: copy source +0xec/+0xf0 to handler +0x154 and return
 * the actor token. */
uint32_t vertrix_actor_choose_handler(void *actor, size_t size, uint32_t object,
                                      uint32_t source_offset);
/* Original 0x43a4f0: store three low bytes at +0x168..+0x16a and return the player token. */
uint32_t vertrix_player_write_bytes_168(void *player, size_t size, uint32_t object, uint32_t first,
                                        uint32_t second, uint32_t third);
/* Original 0x43b970: exact eax is 1 when dword +0x4e8 is nonzero, otherwise 0. */
uint32_t vertrix_player_test_4e8(const void *player, size_t size);
/* Original 0x43ba70: exact eax is 1 when dword +0x18c is 3, otherwise 0. */
uint32_t vertrix_player_test_bonus_full(const void *player, size_t size);
/* Original 0x4320c0: exact eax is 1 when dword +0xa60 is nonzero, otherwise 0. */
uint32_t vertrix_player_test_a60(const void *player, size_t size);
/* Original 0x43bd40: exact eax is 1 when byte +0x4c4 is 1, otherwise 0. */
uint32_t vertrix_player_test_4c4(const void *player, size_t size);
/* Original 0x47f8e0: store value at +0x18 and return the object token. */
uint32_t vertrix_object_write_18(void *storage, size_t size, uint32_t object, uint32_t value);
/* Original variants 0x4ac390, 0x4ac620, 0x4ac520: pairs (0xcc,0xd0)/(0xdc,0xe0)/(0xbc,0xc0).
 * Exact eax is the unsigned counter-at-least-limit predicate, 0 or 1. */
uint32_t vertrix_actor_test_counter_pair(const void *actor, size_t size, uint32_t counter_offset,
                                         uint32_t limit_offset);
/* Original variants 0x4ac470, 0x4ac7b0, 0x4ac840: store 12 * value at +0xd0/+0xc0/+0xe0 and
 * return the stored product, wrapping to 32 bits. */
uint32_t vertrix_actor_store_times_twelve(void *actor, size_t size, uint32_t offset,
                                          uint32_t value);
/* Original variants 0x42ef60, 0x42ef80, 0x42f7d0, 0x42f7f0, 0x42f810, 0x42f830:
 * (start,count) = (0x99c,5)/(0x9a1,5)/(0x9a6,13)/(0x9b3,13)/(0x9c0,13)/(0x9cd,13).
 * Fill with the low byte of value; original eax returns object + count, not the field end. */
uint32_t vertrix_player_fill_byte_range(void *player, size_t size, uint32_t object, uint32_t start,
                                        uint32_t count, uint32_t value);
/* Original 0x425de0: clear seven dwords to 0xffffffff and return object + 0x1c (wrapping). */
uint32_t vertrix_object_reset_slots(void *storage, size_t size, uint32_t object);
#endif
