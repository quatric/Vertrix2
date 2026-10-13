#ifndef VERTRIX_LIFTED_WHOLE_31_H
#define VERTRIX_LIFTED_WHOLE_31_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F412700_STACK = 784,
    LIFTED_F4185F0_STACK = 188
};

/* Original 0x412700. */
uint32_t lifted_f412700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4185f0. */
uint32_t lifted_f4185f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
