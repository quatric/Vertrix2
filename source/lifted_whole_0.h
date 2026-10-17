#ifndef VERTRIX_LIFTED_WHOLE_0_H
#define VERTRIX_LIFTED_WHOLE_0_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F407020_STACK = 184,
    LIFTED_F4193B0_STACK = 168
};

/* Original 0x407020. */
uint32_t lifted_f407020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4193b0. */
uint32_t lifted_f4193b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
