#ifndef VERTRIX_LIFTED_WHOLE_13_H
#define VERTRIX_LIFTED_WHOLE_13_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4D2710_STACK = 300,
    LIFTED_F4DFB24_STACK = 168
};

/* Original 0x4d2710. */
uint32_t lifted_f4d2710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dfb24. */
uint32_t lifted_f4dfb24(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
