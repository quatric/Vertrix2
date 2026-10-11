#ifndef VERTRIX_LIFTED_WHOLE_18_H
#define VERTRIX_LIFTED_WHOLE_18_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F429BA0_STACK = 92
};

/* Original 0x429ba0. */
uint32_t lifted_f429ba0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
