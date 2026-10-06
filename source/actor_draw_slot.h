#ifndef VERTRIX_ACTOR_DRAW_SLOT_H
#define VERTRIX_ACTOR_DRAW_SLOT_H
#include "actor_refresh_state.h"
/* Supplied boundary for original 47ce10: surface/handle, selector, x, y and two
 * resource words. Handles are identity tokens, never native pointers. */
typedef int (*VertrixActorDraw)(uint32_t handle, uint32_t selector, int32_t x, int32_t y,
                                uint32_t resource_a, uint32_t resource_b, void *context);
/* Original4ae010 (base vtable slot 3). Draws only when dword124 is one, the
 * refresh value is one and equals dword138 with nonzero resources at 12c/130.
 * x and y are the signed words at 128 and 12a. When dword140 is one the same
 * rectangle is drawn again for the companion handle/selector read from
 * companion storage at 274/278. Invalid storage preserves both outputs. */
int vertrix_actor_draw_slot(const VertrixActorRefresh *state, const void *actor, size_t size,
                            uint32_t surface, uint32_t selector, const void *companion,
                            size_t companion_size, VertrixActorDraw draw, void *context);
/* Supplied boundaries for original 4ac8a0 and 4af8c0 and the next link at
 * node+0x108. */
typedef int (*VertrixChainVisit)(uint32_t node, uint32_t arg, void *context);
typedef int (*VertrixChainNext)(uint32_t node, uint32_t *next, void *context);
/* Original4ade60 (also base slot 2 0x4ae140): for each node from the first until
 * a zero link, call visit twice (4ac8a0 then 4af8c0 with arg) then follow next.
 * Native walks reject chains longer than 4096. */
int vertrix_actor_chain_walk(uint32_t first, uint32_t arg, VertrixChainVisit visit_a,
                             VertrixChainVisit visit_b, VertrixChainNext next, void *context);
#endif
