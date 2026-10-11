#ifndef VERTRIX_LIFTED_WHOLE_22_H
#define VERTRIX_LIFTED_WHOLE_22_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_RTL_LENGTH_LIMIT_STACK = 80
};

/* Original 0x4df884. */
uint32_t lifted_rtl_length_limit(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);
#endif
