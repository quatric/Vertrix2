#ifndef VERTRIX_LIFTED_WHOLE_44_H
#define VERTRIX_LIFTED_WHOLE_44_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_PALETTE_CUBE_STACK = 112
};

/* Original 0x480ca0. */
uint32_t lifted_palette_cube(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

#endif
