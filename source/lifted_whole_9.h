#ifndef VERTRIX_LIFTED_WHOLE_9_H
#define VERTRIX_LIFTED_WHOLE_9_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4C6020_STACK = 148,
    LIFTED_F4EC68C_STACK = 96
};

/* Original 0x4c6020. */
uint32_t lifted_f4c6020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec68c. */
uint32_t lifted_f4ec68c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
