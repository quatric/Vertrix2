#ifndef VERTRIX_LIFTED_WHOLE_12_H
#define VERTRIX_LIFTED_WHOLE_12_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4CAE30_STACK = 200,
    LIFTED_F4EC970_STACK = 152
};

/* Original 0x4cae30. */
uint32_t lifted_f4cae30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec970. */
uint32_t lifted_f4ec970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
