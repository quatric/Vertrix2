#ifndef VERTRIX_LIFTED_WHOLE_15_H
#define VERTRIX_LIFTED_WHOLE_15_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F42F910_STACK = 172,
    LIFTED_F42FB60_STACK = 304
};

/* Original 0x42f910. */
uint32_t lifted_f42f910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42fb60. */
uint32_t lifted_f42fb60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
