#ifndef VERTRIX_LIFTED_WHOLE_15_H
#define VERTRIX_LIFTED_WHOLE_15_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F425F60_STACK = 252,
    LIFTED_F42F910_STACK = 172,
    LIFTED_F42FB60_STACK = 304,
    LIFTED_F487890_STACK = 136
};

/* Original 0x425f60. */
uint32_t lifted_f425f60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f910. */
uint32_t lifted_f42f910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42fb60. */
uint32_t lifted_f42fb60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487890. */
uint32_t lifted_f487890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
