#ifndef VERTRIX_LIFTED_WHOLE_42_H
#define VERTRIX_LIFTED_WHOLE_42_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F405680_STACK = 336
};

/* Original 0x405680. */
uint32_t lifted_f405680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
