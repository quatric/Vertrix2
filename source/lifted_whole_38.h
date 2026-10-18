#ifndef VERTRIX_LIFTED_WHOLE_38_H
#define VERTRIX_LIFTED_WHOLE_38_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4CEAA0_STACK = 700
};

/* Original 0x4ceaa0. */
uint32_t lifted_f4ceaa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
