#ifndef VERTRIX_LIFTED_WHOLE_6_H
#define VERTRIX_LIFTED_WHOLE_6_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_RTL_SEGMENT_DISPATCH_STACK = 84,
    LIFTED_F4E628C_STACK = 80,
    LIFTED_F4E88BF_STACK = 76
};

/* Original 0x4dee73. */
uint32_t lifted_rtl_segment_dispatch(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e628c. */
uint32_t lifted_f4e628c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e88bf. */
uint32_t lifted_f4e88bf(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
