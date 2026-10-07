#ifndef VERTRIX_ACTOR_CHAIN_VISIT_H
#define VERTRIX_ACTOR_CHAIN_VISIT_H
#include <stddef.h>
#include <stdint.h>
/* Supplied boundary for original 4877f0: bank handle and frame index to image handle. */
typedef uint32_t (*VertrixImageLookup)(uint32_t bank, uint32_t index, void *context);
/* Original4ac8a0: when actor dword b0 is nonzero store lookup(b0, b8) at b4. */
int vertrix_actor_lookup_image(void *actor, size_t size, VertrixImageLookup lookup, void *context);
/* Supplied boundaries for original 4ae3e0 (gate, given actor and dword144) and 4af560. */
typedef int (*VertrixActorGate)(uint32_t actor, uint32_t value, void *context);
typedef void (*VertrixActorPaint)(uint32_t actor, void *context);
/* Original 0x4af8c0: store arg in global 5bc010, then paint only when the gate result is nonzero.
 */
int vertrix_actor_chain_paint(uint32_t actor_handle, const void *actor, size_t size, uint32_t arg,
                              uint32_t *global_arg, VertrixActorGate gate, VertrixActorPaint paint,
                              void *context);
#endif
