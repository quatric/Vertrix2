#ifndef VERTRIX_LIFTED_WHOLE_10_H
#define VERTRIX_LIFTED_WHOLE_10_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_PALETTE_RGB_STACK = 292,
    LIFTED_PALETTE_COLOR_STACK = 256,
    LIFTED_F4D1AE0_STACK = 188,
    LIFTED_F4E0C56_STACK = 212
};

/* Original 0x474560. */
uint32_t lifted_palette_rgb(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x474910. */
uint32_t lifted_palette_color(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1ae0. */
uint32_t lifted_f4d1ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0c56. */
uint32_t lifted_f4e0c56(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
