#ifndef VERTRIX_LIFTED_WHOLE_3_H
#define VERTRIX_LIFTED_WHOLE_3_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_SURFACE_FLIP_VERTICAL_STACK = 112,
    LIFTED_SURFACE_BLIT_STACK = 104,
    LIFTED_F47EAB0_STACK = 96
};

/* Original 0x479b50. */
uint32_t lifted_surface_flip_vertical(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ce10. */
uint32_t lifted_surface_blit(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47eab0. */
uint32_t lifted_f47eab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
