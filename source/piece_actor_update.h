#ifndef VERTRIX_PIECE_ACTOR_UPDATE_H
#define VERTRIX_PIECE_ACTOR_UPDATE_H
#include "frame_resource.h"
#include "piece_actor_layout.h"
typedef int (*VertrixPieceActorUpdate)(void *actor, size_t size, uint32_t elapsed, void *context);
/* Original 0x42ac40: advance parent timer, move if due and17c is zero, update
 * seven children, set their effect48, then apply42af30 layout. Child virtual
 * dispatch remains explicit because those actors can have different classes.
 * Parent count/handles may change during callbacks; read them as reached.
 * Invalid initial storage fails before mutation; later failures retain earlier
 * timer/movement/child/effect changes. Caller supplies original4f90ac height. */
int vertrix_piece_actor_update(void *parent, size_t parent_size, uint32_t elapsed,
                               uint16_t row_height, VertrixActorStorageMutableResolve resolve,
                               VertrixPieceActorUpdate update, void *context);
/* Same parent update with recovered piece-child virtual dispatch and explicit
 * shared piece resource graph. Zero child resources retain null-bind behavior.
 * Resource storage and resolved actor ownership stay with the caller. */
int vertrix_piece_actor_update_resource(void *parent, size_t parent_size, uint32_t elapsed,
                                        uint16_t row_height,
                                        VertrixActorStorageMutableResolve resolve, void *context,
                                        int clear_refresh, uint32_t resource_token,
                                        const VertrixFrameResource *resource, size_t budget);
#endif
