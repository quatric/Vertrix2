#ifndef VERTRIX_LIFTED_WHOLE_36_H
#define VERTRIX_LIFTED_WHOLE_36_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4DAE94_STACK = 72
};

/* Original 0x4dae94. */
uint32_t lifted_f4dae94(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
