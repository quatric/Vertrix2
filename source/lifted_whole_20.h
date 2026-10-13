#ifndef VERTRIX_LIFTED_WHOLE_20_H
#define VERTRIX_LIFTED_WHOLE_20_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_PIECE_ACTOR_DESTROY_FULL_STACK = 164,
    LIFTED_PIECE_ACTOR_FORWARD_SLOT2_STACK = 84,
    LIFTED_PIECE_ACTOR_UPDATE_STACK = 108
};

/* Original 0x42ab10. */
uint32_t lifted_piece_actor_destroy_full(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42abf0. */
uint32_t lifted_piece_actor_forward_slot2(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ac40. */
uint32_t lifted_piece_actor_update(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

#endif
