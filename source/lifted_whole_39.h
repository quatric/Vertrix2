#ifndef VERTRIX_LIFTED_WHOLE_39_H
#define VERTRIX_LIFTED_WHOLE_39_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4EA130_STACK = 64
};

/* Original 0x4ea130. */
uint32_t lifted_f4ea130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
