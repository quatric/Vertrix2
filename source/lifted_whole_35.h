#ifndef VERTRIX_LIFTED_WHOLE_35_H
#define VERTRIX_LIFTED_WHOLE_35_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F410F20_STACK = 160,
    LIFTED_F410FA0_STACK = 224
};

/* Original 0x410f20. */
uint32_t lifted_f410f20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x410fa0. */
uint32_t lifted_f410fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
