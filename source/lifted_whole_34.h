#ifndef VERTRIX_LIFTED_WHOLE_34_H
#define VERTRIX_LIFTED_WHOLE_34_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F40B6E0_STACK = 332
};

/* Original 0x40b6e0. */
uint32_t lifted_f40b6e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
