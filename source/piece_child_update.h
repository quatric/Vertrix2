#ifndef VERTRIX_PIECE_CHILD_UPDATE_H
#define VERTRIX_PIECE_CHILD_UPDATE_H
#include "actor_storage.h"
#include "frame_resource.h"
typedef struct
{
    int16_t x_min, x_max, y_min, y_max;
} VertrixPieceChildBounds;
/* Original base constructor and42ae11..42aea5 child setup. Attach544bd8,
 * set supplied frame and clipping words, timer24/animation period12, clipping
 * mode3, and callback44c2b0 for the last child or44c2a0 otherwise. Allocation
 * and parent handle publication are separate. Invalid storage/bounds preserve
 * destination; untouched bytes remain unchanged. */
int vertrix_piece_child_construct(void *storage, size_t size, uint32_t frame,
                                  const VertrixPieceChildBounds *bounds, int last_child);
/* Original44c2a0/44c2b0/44c310/44c370. Explicit resolved resource token and
 * borrowed graph supply original4ac8a0 binding. Zero actorb0 skips binding.
 * Valid callbacks update primary timer and signed value58 transitions. Invalid
 * storage/handler/resource binding preserves the actor. Base virtual refresh
 * and interaction/child-chain processing remain separate. */
int vertrix_piece_child_update(void *storage, size_t size, uint32_t elapsed,
                               uint32_t resource_token, const VertrixFrameResource *resource,
                               size_t budget);
/* Complete4ae150/4ade20 base virtual update for these callbacks, excluding
 * interaction104 and child-update chain108. Validate base class517af4 and
 * apply original conditional refresh clearing before the callback. */
int vertrix_piece_child_frame_update(void *storage, size_t size, uint32_t elapsed,
                                     int clear_refresh, uint32_t resource_token,
                                     const VertrixFrameResource *resource, size_t budget);
#endif
