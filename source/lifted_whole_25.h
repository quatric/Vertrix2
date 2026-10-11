#ifndef VERTRIX_LIFTED_WHOLE_25_H
#define VERTRIX_LIFTED_WHOLE_25_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4B3DE0_STACK = 136,
    LIFTED_F4B3F30_STACK = 92
};

/* Original 0x4b3de0. */
uint32_t lifted_f4b3de0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3f30. */
uint32_t lifted_f4b3f30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
