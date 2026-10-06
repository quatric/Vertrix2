#ifndef VERTRIX_OBJECT_TAILS_H
#define VERTRIX_OBJECT_TAILS_H
#include "block_factory.h"
#include "call_glue.h"
#include "object_glue.h"
#include <stddef.h>
#include <stdint.h>

enum
{
    VERTRIX_TAIL_TEXT_LENGTH = 0x170,
    VERTRIX_TAIL_SLOT_ID = 0x15c,
    VERTRIX_TAIL_SLOT_ID_ALT = 0x172,
    VERTRIX_TAIL_TABLE_517644 = 0x517644,
    VERTRIX_TAIL_TABLE_FIELD = 0x14,
    VERTRIX_TAIL_SLOT_FLAG = 0x3b,
    VERTRIX_TAIL_BLOCK_BYTES = 16,
    VERTRIX_TAIL_BLOCK_DWORDS = 9,
    VERTRIX_TAIL_BLOCK_END = 0x30
};

/* Original 0x41de80: when 0x476480 on the point list 0x54d640 and 0x3b is not zero, 0x4762e0 on the
 * same, then the flag at 0x532a08 becomes one minus itself and that is returned; zero otherwise. */
uint32_t vertrix_slot_toggle(const VertrixCalls *calls, uint32_t *flag);

/* Original 0x476090: 0x475a20 on each of the 256 96-byte slots of the table at eax (edx counting
 * from one, ecx the table). Returns 256. */
uint32_t vertrix_slot_table_init(const VertrixCalls *calls, uint32_t table);

/* Original 0x482b30: 0x4b8170 on eax unless it is zero. Returns its eax, or zero. */
uint32_t vertrix_call_unless_zero(const VertrixCalls *calls, uint32_t eax);

/* Original 0x489f90: 0x4b78d0, then 0x517644 stored at +0x14 of the object it returns. */
uint32_t vertrix_object_table_517644(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t eax,
                                     uint32_t edx);

/* Original 0x4b4600 (step -1), 0x4b4610 (step +1) and 0x4b4620 (set minus one): adjust the dword at
 * +0x170 then 0x4b4690 on the object. Returns its eax. */
uint32_t vertrix_object_step_text_length(const VertrixCalls *calls, uint32_t object, void *storage,
                                         size_t size, uint32_t mode);

/* Original 0x4b5500 (word at +0x15c) and 0x4b6700 (word at +0x172): one when the word is not zero
 * and 0x476480 on the point list returns one, after 0x4762e0 on it. Zero otherwise. */
uint32_t vertrix_object_slot_present(const VertrixCalls *calls, const void *storage, size_t size,
                                     size_t field, uint32_t object);

/* Original 0x48d480: clear the sixteen bytes at +0 to +0xf and the nine dwords at +0x10 to +0x30.
 * Returns zero for short storage. */
int vertrix_object_clear_block(void *storage, size_t size);

/* Original 0x48a2f0 (to 0x4b7a80): tail call that hands eax and edx through. */
uint32_t vertrix_forward_a2f0(const VertrixCalls *calls, uint32_t eax, uint32_t edx);

/* Original 0x471e10: look up id 0x15 and then 0x16 in the list 0x54671c through 0x4b5eb0; for each
 * hit run 0x4123d0 on eax with zero and the hit as ebx. ebx is the caller's value for the first
 * lookup. Returns the eax of the last call. */
uint32_t vertrix_list_notify_pair(const VertrixCalls *calls, uint32_t eax, uint32_t ebx);

/* Original 0x4725f0: look up id 0x190 in the list 0x546744 through 0x4b5eb0 and clear the dword at
 * +0x94c of the hit. Returns the hit, zero for none. */
uint32_t vertrix_list_clear_hit(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                uint32_t ebx, uint32_t ecx);

/* Original 0x484a60: 0x481b20 on eax + 0x10, the table 0x516d34 stored at +0x60 of what it returns,
 * that is +0x70 of the object (its result less 0x10), which is returned. */
uint32_t vertrix_object_table_516d34(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t eax);

/* Original 0x48d330 (table 0x517a44 at +0x34 first) and 0x48d500 (ones at +0x20 and +0x2c after):
 * vertrix_object_clear_block on the object. Return the object, zero for short storage. */
uint32_t vertrix_object_clear_with_table(void *storage, size_t size, uint32_t object);
uint32_t vertrix_object_clear_with_ones(void *storage, size_t size, uint32_t object);

/* Original 0x4b4630: the dword at +0x170 becomes the text length minus one, then 0x4b4690 on the
 * object. Returns its eax. */
uint32_t vertrix_object_text_length_reset(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services, uint32_t object,
                                          void *storage, size_t size);

/* Original 0x4b5d40: as 0x4b5500, but a hit only calls 0x4762e0 when the dword at +0x160 is
 * zero. */
uint32_t vertrix_object_slot_present_unowned(const VertrixCalls *calls, const void *storage,
                                             size_t size, uint32_t object);

/* Original 0x4b6020: for each of the count items of the pointer array at +4 (count at +8) whose
 * dword at +0xb4 is set, 0x4830f0 on it, then the dword cleared. Returns the last eax. */
uint32_t vertrix_object_release_items(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services, const void *storage,
                                      size_t size);
#endif
