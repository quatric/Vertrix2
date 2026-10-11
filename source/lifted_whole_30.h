#ifndef VERTRIX_LIFTED_WHOLE_30_H
#define VERTRIX_LIFTED_WHOLE_30_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F43E2A0_STACK = 100
};

/* Original 0x43e2a0. */
uint32_t lifted_f43e2a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
