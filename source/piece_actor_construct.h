#ifndef VERTRIX_PIECE_ACTOR_CONSTRUCT_H
#define VERTRIX_PIECE_ACTOR_CONSTRUCT_H
#include "board_cells.h"
#include "piece_child_update.h"
typedef struct
{
    uint32_t left_x, left_y, right_x, right_y, width, height;
    uint16_t row_height;
} VertrixPiecePlacement;
/* Original0x42acf0: construction with explicit snapshots of placement globals
 * 0x4f89e8..0x4f89fc and 0x4f90ac. Preserve original
 * low-word wrapping, including runtime changes to placement and dimensions. */
int vertrix_piece_actor_construct_placed(void *parent, size_t parent_size, void *children,
                                         size_t children_size, const uint32_t frames[7],
                                         const uint32_t handles[7], uint8_t side, int difficulty,
                                         int level, const VertrixPiecePlacement *placement);
/* Original fragment 0x42acf0 using original initial placement globals: left138/right488,
 * baseline248, clip width14/height202. Count non-ffffffff values in seven
 * entries, then use the first count entries exactly as the original does.
 * Caller owns contiguous base child storage and distinct nonzero handles.
 * Supply original4f90ac row height, difficulty0..2 and level0..9. Parent must
 * already be constructed. Invalid inputs preserve all caller storage.
 * Runtime changes to placement globals and heap ownership remain separate. */
int vertrix_piece_actor_construct(void *parent, size_t parent_size, void *children,
                                  size_t children_size, const uint32_t frames[7],
                                  const uint32_t handles[7], uint8_t side, int difficulty,
                                  int level, uint16_t row_height);
/* Original 0x429880: construct a slotted actor (base fields 0x4abd70) with class
 * token 0x514624, flag byte +0x274 = 0xff and dword +0x278 = 1, then clear
 * seven rows: four dwords at +0x15c and four at +0x1cc per 16-byte row stride,
 * plus flag bytes spanning +0x23c..+0x257 and +0x258..+0x273 (the inner edx
 * accumulates across the row: the back-edge targets the store, not the
 * reload). Needs 0x274 bytes. Invalid inputs preserve storage. */
int vertrix_piece_actor_construct_slots(void *actor, size_t actor_size);
/* Original 0x42b5c0: construct a piece actor (base fields 0x4abd70) with class
 * token 0x514894 and cleared child slots (+0x170 second list and +0x15c,
 * +0x160, +0x164 handles). Needs 0x174 bytes; the board caller allocates
 * exactly that. Invalid inputs preserve storage. */
int vertrix_piece_actor_construct_empty(void *actor, size_t actor_size);

/* Supplied boundary for the original operator new 0x4ca000. Returns the actor
 * handle, or zero on allocation failure. */
typedef uint32_t (*VertrixPieceAllocate)(uint32_t size, void *context);

/* Supplied boundary for the original piece finish 0x42b6b0. The actor is the
 * allocated handle (zero when allocation failed); the kind is the
 * sign-extended low byte of the caller's edx. */
typedef void (*VertrixPieceFinish)(uint32_t actor, int32_t kind, void *context);

/* Original0x4320d0: when the actor slot dword at +0xb70 is already set, do
 * nothing. Otherwise allocate 0x174 bytes, construct the empty piece actor
 * in them (skipped when allocation fails), store the handle (possibly zero)
 * in the slot, and run the finish with the sign-extended kind. Returns 1
 * when stored or already occupied, 0 for short storage, an unresolvable
 * allocation, or a failed construction (storage preserved). */
int vertrix_piece_actor_spawn(void *board, size_t size, int32_t kind, VertrixPieceAllocate allocate,
                              VertrixPieceFinish finish, VertrixObjectStorage resolve,
                              void *context);
#endif
