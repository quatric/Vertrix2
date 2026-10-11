#ifndef VERTRIX_LIFTED_WHOLE_29_H
#define VERTRIX_LIFTED_WHOLE_29_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F43E320_STACK = 128
};

/* Original 0x43e320. */
uint32_t lifted_f43e320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
