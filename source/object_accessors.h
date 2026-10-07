#ifndef VERTRIX_OBJECT_ACCESSORS_H
#define VERTRIX_OBJECT_ACCESSORS_H
#include <stddef.h>
#include <stdint.h>

/* Small field accessors of the actor and player objects, cleaned up from the lifted routines.
 * Each one returns 0 (and changes nothing) for storage too short for the field. */

/* Originals 0x4ac500 (offset 0xbc), 0x4ac370 (0xcc) and 0x4ac600 (0xdc): the dword at `offset`
 * grows by `elapsed`, the frame delta the original keeps in [0x5bd834]. */
int vertrix_actor_add_elapsed(void *actor, size_t size, uint32_t offset, uint32_t elapsed);

/* Original 0x4ac520: 1 when the clock at +0xbc has reached the period at +0xc0 (unsigned). */
int vertrix_actor_clock_reached(const void *actor, size_t size, uint32_t *reached);

/* Original 0x418830: the clock at +0xbc is set to the period at +0xc0. */
int vertrix_actor_clock_to_period(void *actor, size_t size);

/* Originals 0x4ac920 and 0x4ac940: the dword at +0x154 takes the dword at +0xec or +0xf0. */
int vertrix_actor_select_ec(void *actor, size_t size);
int vertrix_actor_select_f0(void *actor, size_t size);

/* Original 0x43a4f0: the bytes at +0x168, +0x169 and +0x16a take the low bytes of edx, ebx and
 * ecx. */
int vertrix_player_set_bytes_168(void *player, size_t size, uint32_t first, uint32_t second,
                                 uint32_t third);

/* Original 0x43b970: 1 when the dword at +0x4e8 is not zero. */
int vertrix_player_flag_4e8(const void *player, size_t size, uint32_t *set);

/* Original 0x43ba70: 1 when the bonus meter at +0x18c is 3 (full). */
int vertrix_player_bonus_meter_full(const void *player, size_t size, uint32_t *full);

/* Original 0x4320c0: 1 when the dword at +0xa60 is not zero. */
int vertrix_player_flag_a60(const void *player, size_t size, uint32_t *set);

/* Original 0x43bd40: 1 when the byte at +0x4c4 is 1. */
int vertrix_player_byte_4c4_is_one(const void *player, size_t size, uint32_t *is_one);

/* Original 0x47f8e0: the dword at +0x18 takes `value`. */
int vertrix_object_set_18(void *object, size_t size, uint32_t value);

/* Originals 0x4ac390 (counter +0xcc, limit +0xd0), 0x4ac620 (+0xdc, +0xe0) and the clock pair of
 * 0x4ac520 (+0xbc, +0xc0): 1 when the counter is at least the limit (unsigned). */
int vertrix_actor_counter_pair_reached(const void *actor, size_t size, uint32_t counter_offset,
                                       uint32_t limit_offset, uint32_t *reached);

/* Originals 0x4ac470 (offset 0xd0), 0x4ac7b0 (0xc0) and 0x4ac840 (0xe0): the dword at `offset`
 * becomes 12 * value (wrapping), the frame count converted to a period. */
int vertrix_actor_set_times_twelve(void *actor, size_t size, uint32_t offset, uint32_t value);

/* Originals 0x42ef60 (+0x99c, 5 bytes), 0x42ef80 (+0x9a1, 5), 0x42f7d0 (+0x9a6, 13), 0x42f7f0
 * (+0x9b3, 13), 0x42f810 (+0x9c0, 13) and 0x42f830 (+0x9cd, 13): `count` bytes from `start` take
 * the low byte of `value`. */
int vertrix_player_fill_bytes(void *player, size_t size, uint32_t start, uint32_t count,
                              uint32_t value);

/* Original 0x425de0: the first seven dwords of the object become 0xffffffff. */
int vertrix_object_clear_slots(void *object, size_t size);

/* Original 0x418150: -1, 0 or 1 as the first value is below, equal to or above the second
 * (unsigned). */
int32_t vertrix_compare_u32(uint32_t first, uint32_t second);
#endif
