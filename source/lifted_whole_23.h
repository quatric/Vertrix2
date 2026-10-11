#ifndef VERTRIX_LIFTED_WHOLE_23_H
#define VERTRIX_LIFTED_WHOLE_23_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F44B810_STACK = 224
};

/* Original 0x44b810. */
uint32_t lifted_f44b810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
