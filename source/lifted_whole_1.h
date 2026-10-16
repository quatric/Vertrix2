#ifndef VERTRIX_LIFTED_WHOLE_1_H
#define VERTRIX_LIFTED_WHOLE_1_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_FONT_MAPS_INITIALIZE_STACK = 520,
    LIFTED_F444E00_STACK = 248,
    LIFTED_F445350_STACK = 272
};

/* Original 0x43fc50. */
uint32_t lifted_font_maps_initialize(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444e00. */
uint32_t lifted_f444e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445350. */
uint32_t lifted_f445350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
