#ifndef VERTRIX_LIFTED_WHOLE_44_H
#define VERTRIX_LIFTED_WHOLE_44_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_PALETTE_CUBE_STACK = 112,
    LIFTED_F491050_STACK = 80,
    LIFTED_F49A600_STACK = 88,
    LIFTED_F4A2650_STACK = 80,
    LIFTED_F4A26C0_STACK = 88,
    LIFTED_F4AA3C0_STACK = 88,
    LIFTED_F4DAE80_STACK = 72
};

/* Original 0x480ca0. */
uint32_t lifted_palette_cube(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x491050. */
uint32_t lifted_f491050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49a600. */
uint32_t lifted_f49a600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a2650. */
uint32_t lifted_f4a2650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a26c0. */
uint32_t lifted_f4a26c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aa3c0. */
uint32_t lifted_f4aa3c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dae80. */
uint32_t lifted_f4dae80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
