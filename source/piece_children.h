#ifndef VERTRIX_PIECE_CHILDREN_H
#define VERTRIX_PIECE_CHILDREN_H
#include "board_cells.h"
/* A falling piece holds three block child handles at +0x15c, +0x160 and +0x164 (and, in the
 * second list, at +0x170..). Each child stores its block kind in byte +0x15c. */
#define VERTRIX_PIECE_CHILD_COUNT 3
#define VERTRIX_KIND_TABLE_COUNT 19

/* Supplied boundary for the original resource attach 0x4ac8d0. The resource is an original
 * address token (0x544ac0 + kind * 28), never a native pointer. */
typedef void (*VertrixPieceAttach)(uint32_t actor, uint32_t resource, void *context);

/* Original0x42a980 and 0x43a5b0 (identical): read the kind bytes of the three children. Returns
 * zero for an unresolvable object, leaving the outputs that were already stored. */
int vertrix_piece_child_kinds(uint32_t piece, VertrixObjectStorage resolve, void *context,
                              uint8_t kinds[VERTRIX_PIECE_CHILD_COUNT]);

/* Original0x43a410: configure all three children from their kinds: attach the resource, store
 * the kind, set the handler (0x44c4c0, 0x44c3e0, 0x44c450 for children 0..2), clear the dword
 * +0x58 and the timer counter. Returns zero for an unresolvable object. */
int vertrix_piece_children_setup(uint32_t piece, const uint8_t kinds[VERTRIX_PIECE_CHILD_COUNT],
                                 VertrixPieceAttach attach, VertrixObjectStorage resolve,
                                 void *context);

/* Original0x43a5f0: as above for only the children whose flag is exactly 1, all with handler
 * 0x44c4c0. Returns zero for an unresolvable object. */
int vertrix_piece_children_setup_selected(uint32_t piece,
                                          const uint8_t kinds[VERTRIX_PIECE_CHILD_COUNT],
                                          const uint32_t selected[VERTRIX_PIECE_CHILD_COUNT],
                                          VertrixPieceAttach attach, VertrixObjectStorage resolve,
                                          void *context);

/* Original0x42a800: place the children of both lists (+0x15c and +0x170) below the piece: x is the
 * piece x (+0xe) plus the signed byte +0x16c, y is the piece y (+0x16) plus 24 per row plus the
 * signed byte +0x16d, with word wrapping. Returns zero for an unresolvable object. */
int vertrix_piece_children_place(uint32_t piece, VertrixObjectStorage resolve, void *context);

/* Original0x425ef0: initialize a piece from a kind index below 19: dword +0x15c from the first
 * table, +0x160 as its class (4 for 12, 3 above 7, 1 up to 3, else 2), +0x164 from the second
 * table and +0x180 = 0xffffffff. Larger indices read beyond the tables in the original and
 * return zero here, preserving the storage. */
int vertrix_piece_init_from_kind(void *storage, size_t size, uint8_t kind_index);

/* Original0x43a510: 0x43a410 with the three kinds taken from the low bytes of registers edx, ebx
 * and ecx (the original sign-extends them first, which the byte stores discard); identical to
 * vertrix_piece_children_setup. */
int vertrix_piece_children_setup_registers(uint32_t piece,
                                           const uint8_t kinds[VERTRIX_PIECE_CHILD_COUNT],
                                           VertrixPieceAttach attach, VertrixObjectStorage resolve,
                                           void *context);

/* Original0x43a560: remember the current kinds of the three children in the piece bytes
 * +0x168..+0x16a, then set the children up with the given kinds as 0x43a410 does. Nothing is
 * stored when an object does not resolve before the setup begins. */
int vertrix_piece_children_remember_and_setup(uint32_t piece,
                                              const uint8_t kinds[VERTRIX_PIECE_CHILD_COUNT],
                                              VertrixPieceAttach attach,
                                              VertrixObjectStorage resolve, void *context);

/* Original0x42b920: store the dword +0x168 and attach resource 0x544ba0 for 0, 0x544bbc for 1
 * (other values attach nothing). */
int vertrix_piece_set_variant(uint32_t piece, uint32_t variant, VertrixPieceAttach attach,
                              VertrixObjectStorage resolve, void *context);

/* Original0x43a520: set the children up with the kinds remembered in the piece bytes
 * +0x168..+0x16a (as 0x43a410) and then reset those three bytes to 0xff. */
int vertrix_piece_children_restore_and_clear(uint32_t piece, VertrixPieceAttach attach,
                                             VertrixObjectStorage resolve, void *context);

/* Original0x43a4f0: store the three preview kinds in the piece bytes +0x168..+0x16a.
 * The original writes the low bytes of edx, ebx and ecx directly with no return
 * value and no bounds check; the native version preserves short storage and
 * returns zero there. Used by 0x43d260 after 0x43d180 generation. */
int vertrix_piece_store_preview_kinds(void *preview, size_t size, uint8_t first, uint8_t second,
                                      uint8_t third);

/* Original0x42b9f0: when the dword +0x170 is zero, set it to 1, the period +0xc0 to period, the
 * word +0x1a to word and clear the counter +0xbc; period and word are the entries of the tables at
 * 0x4f7d14 and 0x4f7d20 selected by the dword at 0x532bbc, read at the boundary. A nonzero +0x170
 * leaves the storage unchanged. Short storage is preserved and returns zero. */
int vertrix_piece_arm_once(void *storage, size_t size, uint32_t period, uint16_t word);

/* Original0x42b950: when the word +0xe differs from the word +0xa8, copy +0xa8 into it and set
 * the variant (0x42b920) to 1 when the byte +0x16c is nonzero, else 0. Nothing happens when the
 * words are equal. */
int vertrix_piece_snap_to_left(uint32_t piece, VertrixPieceAttach attach,
                               VertrixObjectStorage resolve, void *context);
/* Original0x42b990: when the signed word +0xe differs from the signed word +0xaa minus origin (the
 * dword at 0x4f9098, read at the boundary), store the low 16 bits of word +0xaa minus origin in
 * +0xe and set the variant to 0 when the byte +0x16c is 1, else 1. */
int vertrix_piece_snap_to_origin(uint32_t piece, uint32_t origin, VertrixPieceAttach attach,
                                 VertrixObjectStorage resolve, void *context);

/* Original0x43a160: construct the actor (base fields 0x4abd70) with class
 * token 0x514b94, then zero three slot dwords at +0x15c/+0x160/+0x164 and
 * three consecutive flag bytes at +0x168..+0x16a (0xff; the inner edx
 * accumulates, so the bytes are adjacent, unlike the dwords). Short storage
 * preserves everything and returns zero. */
int vertrix_piece_child_slots_init(void *actor, size_t size);
#endif
