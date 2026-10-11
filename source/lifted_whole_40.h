#ifndef VERTRIX_LIFTED_WHOLE_40_H
#define VERTRIX_LIFTED_WHOLE_40_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4056C0_STACK = 220,
    LIFTED_F409F00_STACK = 216,
    LIFTED_MIXER_EFFECT_SELECT_STACK = 76,
    LIFTED_RTL_SQUARE_ROOT_STACK = 96
};

/* Original 0x4056c0. */
uint32_t lifted_f4056c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x409f00. */
uint32_t lifted_f409f00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40dc50. */
uint32_t lifted_mixer_effect_select(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9b10. */
uint32_t lifted_rtl_square_root(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);
#endif
