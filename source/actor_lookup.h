#ifndef VERTRIX_ACTOR_LOOKUP_H
#define VERTRIX_ACTOR_LOOKUP_H
#include "actor_storage.h"
#include "object_list.h"
/* Resolve stable live storage for the duration of lookup/update. */
typedef int (*VertrixActorStorageResolve)(uint32_t handle, const void **storage, size_t *size,
                                          void *context);
/* Original4b5eb0: field4 selects first listed field0 match, reading linked58/64.
 * Missing match succeeds with present0/value0/state0. Invalid resolution leaves
 * all outputs unchanged. This helper does not mutate actors or lists. */
int vertrix_actor_linked_values(const void *storage, size_t size, const VertrixObjectList *list,
                                VertrixActorStorageResolve resolve, void *context, int *present,
                                uint32_t *value, uint32_t *state);
#endif
