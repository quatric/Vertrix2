#ifndef VERTRIX_LIFTED_WHOLE_33_H
#define VERTRIX_LIFTED_WHOLE_33_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F48B2F0_STACK = 26668
};

/* Original 0x48b2f0. */
uint32_t lifted_f48b2f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
