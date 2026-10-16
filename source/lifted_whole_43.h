#ifndef VERTRIX_LIFTED_WHOLE_43_H
#define VERTRIX_LIFTED_WHOLE_43_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_SEQUENCE_EXTENDED_EFFECT_STACK = 92
};

/* Original 0x40d540. */
uint32_t lifted_sequence_extended_effect(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

#endif
