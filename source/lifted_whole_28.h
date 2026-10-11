#ifndef VERTRIX_LIFTED_WHOLE_28_H
#define VERTRIX_LIFTED_WHOLE_28_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_RENDER_WEIGHTS_BUILD_STACK = 124
};

/* Original 0x480730. */
uint32_t lifted_render_weights_build(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);
#endif
