#ifndef VERTRIX_LIFTED_WHOLE_32_H
#define VERTRIX_LIFTED_WHOLE_32_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_ARRAY_LIST_BUILD_STACK = 128
};

/* Original 0x4875a0. */
uint32_t lifted_array_list_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);
#endif
