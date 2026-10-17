#ifndef VERTRIX_LIFTED_WHOLE_21_H
#define VERTRIX_LIFTED_WHOLE_21_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_MIXER_PLAYBACK_TICK_STACK = 88,
    LIFTED_SURFACE_BOUNDS_STACK = 124,
    LIFTED_RTL_RANGE_TABLE_FIND_STACK = 68,
    LIFTED_F4DA3BA_STACK = 1400,
    LIFTED_F4DF320_STACK = 248
};

/* Original 0x40e030. */
uint32_t lifted_mixer_playback_tick(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4792d0. */
uint32_t lifted_surface_bounds(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d0b30. */
uint32_t lifted_rtl_range_table_find(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4da3ba. */
uint32_t lifted_f4da3ba(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df320. */
uint32_t lifted_f4df320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
