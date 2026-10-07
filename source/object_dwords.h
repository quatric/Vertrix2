#ifndef VERTRIX_OBJECT_DWORDS_H
#define VERTRIX_OBJECT_DWORDS_H
#include "actor_gate.h"
#include "board_cells.h"
#include <stddef.h>
#include <stdint.h>
/* Generic field access for the many one-field routines of the library, list, score and effect
 * objects, plus the small compound routines built on them. Storage is raw object bytes; short or
 * null storage returns zero and preserves everything. Pointer fields are original addresses read
 * through the supplied VertrixMemoryRead boundary. */

/* Original variants 0x47e9a0, 0x480070, 0x4877e0, 0x48a2e0, 0x48aa80, 0x4b4500,
 * 0x4d5350: getters of dwords at offsets 0x1c4, 0x4c, 0x14, 8, 4, 0x174 and 0x98,
 * respectively. */
int vertrix_object_dword(const void *storage, size_t size, size_t offset, uint32_t *value);

/* Original variants 0x47ed60, 0x47ed70, 0x47ed80, 0x47ed90, 0x47f8e0, 0x481b20,
 * 0x484410, 0x4b65b0: edx stores at offsets 0x20, 0x24, 0x28, 0x2c and 0x18 for the first
 * five routines; the last three store constants at 0x28 = 0x516b14, 4 = 0x516c84
 * and 0x174 = 1, respectively. The class tokens are original addresses. */
int vertrix_object_set_dword(void *storage, size_t size, size_t offset, uint32_t value);

/* Original variants 0x48abe0, 0x4b35b0, 0x4b3c30, 0x4b4fa0: two-field setters at
 * offsets (0, 4), (0x170, 0x174), (0x184, 0x188) and (0x188, 0x18c), respectively. */
int vertrix_object_set_pair(void *storage, size_t size, size_t first_offset, size_t second_offset,
                            uint32_t first, uint32_t second);

/* Original variants 0x4879e0, 0x48d5f0: the count dword at +8 is zero. */
int vertrix_list_empty(const void *storage, size_t size, uint32_t *empty);

/* Original0x487770: when the dword at resource +0x14 is 1, the dword at
 * [resource + 8][index]; otherwise 0. The resource and table are original
 * addresses read through the boundary. Unreadable data also yields 0, which
 * the original cannot produce without faulting; entry 0 is ambiguous both
 * ways, exactly as in the original. */
uint32_t vertrix_resource_table_entry(uint32_t resource, uint32_t index, VertrixMemoryRead read,
                                      void *context);

/* Original0x4ac4a0: when the resource handle at +0xb0 is nonzero, refresh the
 * cached count at +0xd0 from the table entry selected by the index at +0xb8.
 * A null resource, or a resource whose flag is not 1, returns at once with no
 * effect (native 1; the original falls off with residue). Returns zero for
 * short storage or unreadable resource data. */
int vertrix_actor_refresh_count(void *actor, size_t size, VertrixMemoryRead read, void *context);

/* Original variants 0x487a20, 0x48d630, 0x4b6fa0, 0x4b79c0: item index of the list
 * whose pointer is the dword at +4 and count the dword at +8; zero past the end. */
int vertrix_list_item(const void *storage, size_t size, uint32_t index, VertrixMemoryRead read,
                      void *context, uint32_t *item);

/* Original variants 0x488030, 0x488040: item index of the table pointed to by the
 * dword at +0x18 or +0x1c, respectively, without bounds. */
int vertrix_table_item(const void *storage, size_t size, size_t pointer_offset, uint32_t index,
                       VertrixMemoryRead read, void *context, uint32_t *item);

/* Original0x4b2290: store zero in count dwords starting at the storage. */
int vertrix_object_zero_dwords(void *storage, size_t size, uint32_t count);

/* Original0x47ecf0: set the dword +0x30 to 1 when it is zero. */
int vertrix_object_arm_30(void *storage, size_t size);

/* Original0x482050: clear byte +0x208. */
int vertrix_object_clear_208(void *storage, size_t size);

/* Original0x482540: dword +8 = dword +0, word +0xc = 0. */
int vertrix_object_restart_range(void *storage, size_t size);

/* Original0x48a910: the dword +4 has reached the dword +8 (unsigned). */
int vertrix_range_done(const void *storage, size_t size, uint32_t *done);

/* Original0x48abf0: word at +8 + 2 * (index & 0xff) = value. */
int vertrix_object_set_indexed_word(void *storage, size_t size, uint32_t index, uint16_t value);

/* Range objects whose first dword points at a block of two dwords. Original0x48a8a0: +4 =
 * block[0], +8 = block[0] + block[1]. Original0x48aaf0: +4 = block[0] + offset. Original0x48aa70:
 * block[1]. Original0x48aad0: +4 - block[0], also the value the original stores in the global
 * 0x5bb250. */
/* Original0x48a8a0: +4 = block[0], +8 = block[0] + block[1]. */
int vertrix_range_start(void *storage, size_t size, VertrixMemoryRead read, void *context);
/* Original0x48aaf0: +4 = block[0] + offset. */
int vertrix_range_seek(void *storage, size_t size, uint32_t offset, VertrixMemoryRead read,
                       void *context);
/* Original0x48aa70: return block[1]. */
int vertrix_range_block_second(const void *storage, size_t size, VertrixMemoryRead read,
                               void *context, uint32_t *value);
/* Original0x48aad0: return +4 - block[0], also stored in global 0x5bb250. */
int vertrix_range_span(const void *storage, size_t size, VertrixMemoryRead read, void *context,
                       uint32_t *length);

/* Original0x4b6530: word +0x17a = 0, byte +0x178 = value. */
int vertrix_timer_reset(void *storage, size_t size, uint8_t value);
/* Original variants 0x4b6540, 0x4b6550: set the word at +0x17a or +0x17c, respectively. */
int vertrix_object_set_word(void *storage, size_t size, size_t offset, uint16_t value);
/* Original variants 0x4b6590, 0x4b65a0: read the word at +0x17c or +0x17a, respectively. */
int vertrix_object_word(const void *storage, size_t size, size_t offset, uint32_t *value);
/* Original0x4b6560: +0x174 is zero or signed word +0x17a is not above +0x17c. */
int vertrix_timer_running(const void *storage, size_t size, uint32_t *running);

/* Original0x4b6690: words +0x16a, +0x16c, +0x16e and +0x170 = a, b, c, d. */
int vertrix_object_set_four_words(void *storage, size_t size, uint16_t a, uint16_t b, uint16_t c,
                                  uint16_t d);

/* Original0x4d2700: dword +8 = 0, +0 = first, +4 = second. Original0x4d2d70: the dword +0x90 is
 * not 0, 0xe001 or 0xe002. */
int vertrix_object_reset_triple(void *storage, size_t size, uint32_t first, uint32_t second);
/* Original0x4d2d70: dword +0x90 is not 0, 0xe001 or 0xe002. */
int vertrix_object_status_active(const void *storage, size_t size, uint32_t *active);

/* Original0x4c5d60: (255 * (2 * a + 1) + b) / (2 * b) with wrapping 32-bit arithmetic and signed
 * division. A zero divisor and the overflowing quotient fault in the original and are rejected. */
int vertrix_scaled_round(int32_t a, int32_t b, int32_t *result);

/* Original0x4c0990: clear dwords +0xd8, +0x90 and +0x1a0 and, in the object whose handle is the
 * dword +0x1b8, the dwords +0xc, +0x10, +0x18 and +0xa4. Returns zero when the linked object does
 * not resolve; the object's own fields are then already cleared. */
int vertrix_object_release_links(void *storage, size_t size, VertrixObjectStorage resolve,
                                 void *context);

/* Original globals of 0x48a930, in order: 0x5bb22c (copied), 0x5bb230 (flag),
 * 0x5bb234 (wanted), 0x5bb238 (available). */
typedef struct
{
    uint32_t copied;
    uint32_t flag;
    uint32_t wanted;
    uint32_t available;
} VertrixRangeCopy;

/* Original0x48a930: copy bytes from the source range object to a flat
 * destination. The dword at source +4 is an absolute read pointer and the
 * dword at +8 the absolute end; wanted is factor_a * factor_b (wrapping) and
 * available is end minus pointer. The flag is 1 unless wanted exceeds
 * available; the count copied is the smaller side (zero copies nothing but
 * still reports the flag). The read pointer advances by the count. Source
 * bytes arrive through the boundary; the destination is a caller buffer.
 * Returns the flag; unreadable source bytes return zero without advancing.
 * (An earlier revision misread +4 as a buffer offset; the oracle showed
 * copies sourcing from absolute address zero.) */
uint32_t vertrix_range_copy(void *source, size_t source_size, void *dest, size_t dest_size,
                            uint32_t factor_a, uint32_t factor_b, VertrixMemoryRead read,
                            void *context, VertrixRangeCopy *cursor);

/* Original0x4121e0: save the dword at object +0x5bc, start the range, copy
 * 1 * 8 bytes to object +0x5b8, then copy [object + 0x5bc] * 12 bytes to the
 * object start (the second factor observes the first copy's output), and
 * restore the saved dword. The copy flags are data, not status (the original
 * ignores them); only short storage and failed range/object steps return
 * zero. */
int vertrix_range_save_copy(void *object, size_t object_size, void *range, size_t range_size,
                            VertrixMemoryRead read, void *context);

/* Supplied allocator boundary (mirrors the operator-new convention): returns
 * a nonzero handle token, zero on failure. */
typedef uint32_t (*VertrixBlockAllocate)(uint32_t size, void *context);

/* Original0x487640: store the value at object +4, allocate value * 4 bytes
 * (wrapping) zeroed, and store the handle at object +0. A null allocation
 * stores zero with no block work. Returns the handle, or zero when storage
 * is short, resolution fails, or the block is short. */
uint32_t vertrix_list_node_alloc(void *object, size_t size, uint32_t value,
                                 VertrixBlockAllocate allocate, VertrixObjectStorage resolve,
                                 void *context);
#endif
