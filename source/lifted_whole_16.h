#ifndef VERTRIX_LIFTED_WHOLE_16_H
#define VERTRIX_LIFTED_WHOLE_16_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F432480_STACK = 228
};

/* Original 0x432480. */
uint32_t lifted_f432480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
