#ifndef VERTRIX_LIFTED_WHOLE_31_H
#define VERTRIX_LIFTED_WHOLE_31_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F412700_STACK = 784
};

/* Original 0x412700. */
uint32_t lifted_f412700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
