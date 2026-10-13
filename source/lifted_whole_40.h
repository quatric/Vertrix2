#ifndef VERTRIX_LIFTED_WHOLE_40_H
#define VERTRIX_LIFTED_WHOLE_40_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_RTL_SQUARE_ROOT_STACK = 96
};

/* Original 0x4c9b10. */
uint32_t lifted_rtl_square_root(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);
#endif
