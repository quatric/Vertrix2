#ifndef VERTRIX_LIFTED_WHOLE_43_H
#define VERTRIX_LIFTED_WHOLE_43_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F40CAA0_STACK = 68,
    LIFTED_MIXER_SET_EFFECT_40D490_STACK = 68,
    LIFTED_SEQUENCE_EXTENDED_EFFECT_STACK = 92,
    LIFTED_MIXER_GLOBAL_EFFECT_STACK = 68
};

/* Original 0x40caa0. */
uint32_t lifted_f40caa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40d490. */
uint32_t lifted_mixer_set_effect_40d490(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40d540. */
uint32_t lifted_sequence_extended_effect(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40d880. */
uint32_t lifted_mixer_global_effect(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);
#endif
