#ifndef VERTRIX_LIFTED_WHOLE_19_H
#define VERTRIX_LIFTED_WHOLE_19_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4B5EE0_STACK = 100
};

/* Original 0x4b5ee0. */
uint32_t lifted_f4b5ee0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
