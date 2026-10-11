#ifndef VERTRIX_LIFTED_WHOLE_27_H
#define VERTRIX_LIFTED_WHOLE_27_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F47E890_STACK = 188,
    LIFTED_F488C50_STACK = 192
};

/* Original 0x47e890. */
uint32_t lifted_f47e890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488c50. */
uint32_t lifted_f488c50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
