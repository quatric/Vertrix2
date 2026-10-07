#ifndef VERTRIX_OBJECT_SLOTS_H
#define VERTRIX_OBJECT_SLOTS_H
#include "board_cells.h"
/* Handle slot arrays embedded in object storage, and the small object initialisers around them.
 * Storage is raw object bytes; short or null storage returns zero and preserves everything. */

/* Original0x4b22c0 on an array in object storage: destroy (virtual destructor, flag 2) and clear
 * every set handle of count dwords at offset, in order. The destroy callback may change the storage
 * before the slot is cleared, as in the original. Returns zero when the array does not fit. */
int vertrix_object_release_slots(void *storage, size_t size, size_t offset, uint32_t count,
                                 VertrixBoardDestroy destroy, void *context);

/* Original0x42a480 (piece children at +0x15c) and 0x42a4a0 (second list at +0x170): release the
 * three child handles. Original0x43d800: release the 500 handles at +0x15c, then the 8 handles at
 * +0x92c. */
int vertrix_piece_release_children(void *storage, size_t size, int second_list,
                                   VertrixBoardDestroy destroy, void *context);
/* Original0x43d800: Release the 500 handles at +0x15c, then the eight handles at +0x92c. */
int vertrix_effects_release_all(void *storage, size_t size, VertrixBoardDestroy destroy,
                                void *context);

/* Original0x43e260: release the 450 handles at +0x15c, the 3 at +0x864 and the one at +0x870. */
int vertrix_arena_release_all(void *storage, size_t size, VertrixBoardDestroy destroy,
                              void *context);

/* Original0x42eba0: release the second child list (as 0x42a4a0) of the board's active piece, the
 * handle at board dword +0xa60. A board without a piece does nothing and succeeds. Returns zero
 * when the board is short or the piece does not resolve. */
int vertrix_board_release_piece_children(const void *board, size_t board_size,
                                         VertrixObjectStorage resolve, VertrixBoardDestroy destroy,
                                         void *context);

/* Original0x429670: construct a base actor (0x4abd70) and mark it: dword +0x158 = 0x5145a4, bytes
 * +0x94 = 0, +0x95 = 3, +0x15c = 0xff and dword +0x160 = 1. Returns zero for short storage. */
int vertrix_marker_actor_construct(void *storage, size_t size);

/* Original0x429660: the address four bytes into an object. */
uint32_t vertrix_object_address_plus_4(uint32_t object);

/* Original0x43d300: the list object whose handle is the dword +0x468 is not empty (its count dword
 * +8 is nonzero). Returns zero when an object does not resolve. */
int vertrix_object_list_filled(const void *storage, size_t size, VertrixObjectStorage resolve,
                               void *context, uint32_t *filled);

/* Original0x475da0: the three dwords +8, +0xc and +0x10 of the object. */
int vertrix_object_triple(const void *storage, size_t size, uint32_t values[3]);

/* Original0x476120 / 0x476140: clear / set the flag byte at the start of record (index & 0xffff)
 * of the 0x60-byte records that begin at the storage. */
int vertrix_record_clear_flag(void *storage, size_t size, uint32_t index);
/* Original0x476140: Set the flag byte of record (index & 0xffff), stride 0x60. */
int vertrix_record_set_flag(void *storage, size_t size, uint32_t index);

/* Original0x471bb0, 0x471d90 and 0x471dd0 (the actor lists at globals 0x546720, 0x546748 and
 * 0x546734): for each of count handles in order, copy the dword +0xec to the handler token +0x154
 * (0x4ac920). Returns zero when an object does not resolve; earlier objects stay changed. */
int vertrix_actors_handler_from_ec(const uint32_t *handles, uint32_t count,
                                   VertrixObjectStorage resolve, void *context);

/* Original0x471bf0: the same, skipping the actors whose dword +0x14c equals link. */
int vertrix_actors_handler_from_ec_unlinked(const uint32_t *handles, uint32_t count, uint32_t link,
                                            VertrixObjectStorage resolve, void *context);
#endif
