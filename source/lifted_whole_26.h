#ifndef VERTRIX_LIFTED_WHOLE_26_H
#define VERTRIX_LIFTED_WHOLE_26_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F476AA0_STACK = 380,
    LIFTED_F4DAAE8_STACK = 108
};

/* Original 0x476aa0. */
uint32_t lifted_f476aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4daae8. */
uint32_t lifted_f4daae8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
