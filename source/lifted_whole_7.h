#ifndef VERTRIX_LIFTED_WHOLE_7_H
#define VERTRIX_LIFTED_WHOLE_7_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4ECCB9_STACK = 288
};

/* Original 0x4eccb9. */
uint32_t lifted_f4eccb9(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
