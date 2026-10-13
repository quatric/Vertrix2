#ifndef VERTRIX_LIFTED_WHOLE_44_H
#define VERTRIX_LIFTED_WHOLE_44_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_PALETTE_CUBE_STACK = 112,
    LIFTED_F491050_STACK = 80,
    LIFTED_F4DAE80_STACK = 72
};

/* Original 0x480ca0. */
uint32_t lifted_palette_cube(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x491050. */
uint32_t lifted_f491050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dae80. */
uint32_t lifted_f4dae80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
