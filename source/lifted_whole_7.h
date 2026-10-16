#ifndef VERTRIX_LIFTED_WHOLE_7_H
#define VERTRIX_LIFTED_WHOLE_7_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4EC0E0_STACK = 120,
    LIFTED_F4EC1EC_STACK = 80,
    LIFTED_F4EC650_STACK = 96,
    LIFTED_F4ECCB9_STACK = 288,
    LIFTED_F4EE025_STACK = 72,
    LIFTED_F4EE160_STACK = 80,
    LIFTED_F4EE750_STACK = 160
};

/* Original 0x4ec0e0. */
uint32_t lifted_f4ec0e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec1ec. */
uint32_t lifted_f4ec1ec(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec650. */
uint32_t lifted_f4ec650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eccb9. */
uint32_t lifted_f4eccb9(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee025. */
uint32_t lifted_f4ee025(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee160. */
uint32_t lifted_f4ee160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee750. */
uint32_t lifted_f4ee750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
