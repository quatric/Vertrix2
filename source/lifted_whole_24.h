#ifndef VERTRIX_LIFTED_WHOLE_24_H
#define VERTRIX_LIFTED_WHOLE_24_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4B41F0_STACK = 92
};

/* Original 0x4b41f0. */
uint32_t lifted_f4b41f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
