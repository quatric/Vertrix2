#ifndef VERTRIX_ACTOR_REFRESH_STATE_H
#define VERTRIX_ACTOR_REFRESH_STATE_H
#include <stddef.h>
#include <stdint.h>

#include "actor_storage.h"

enum
{
    VERTRIX_ACTOR_REFRESH_COUNT = 6
};

/* Shared refresh state: the gate dword at 0x5bb710 followed by the six refresh words at
 * 0x5bb714..0x5bb728. */
typedef struct VertrixActorRefresh
{
    uint32_t gate;
    uint32_t refresh[VERTRIX_ACTOR_REFRESH_COUNT];
} VertrixActorRefresh;

/* Original 0x4adfb0: the refresh value of an actor. The signed word at +0x148 selects one of the
 * six refresh words; 0xffff selects the dword at +0x120. Returns zero for short storage or an
 * index outside 0..5. */
int vertrix_actor_refresh_value(const VertrixActorRefresh *state, const void *actor, size_t size,
                                uint32_t *value);

/* Original 0x4adfe0: set the refresh value selected as above to one (the dword at +0x120 for
 * 0xffff). Returns zero for short storage or an index outside 0..5. */
int vertrix_actor_refresh_arm(VertrixActorRefresh *state, void *actor, size_t size);

#endif
