#ifndef VERTRIX_LIFTED_WHOLE_10_H
#define VERTRIX_LIFTED_WHOLE_10_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F405720_STACK = 516,
    LIFTED_F452960_STACK = 104,
    LIFTED_PALETTE_RGB_STACK = 292,
    LIFTED_PALETTE_COLOR_STACK = 256,
    LIFTED_SURFACE_FADE_STACK = 280,
    LIFTED_F483400_STACK = 144,
    LIFTED_F483790_STACK = 192,
    LIFTED_F485520_STACK = 84,
    LIFTED_F486DA0_STACK = 84,
    LIFTED_F486E00_STACK = 88,
    LIFTED_F488320_STACK = 540,
    LIFTED_F4AD810_STACK = 88,
    LIFTED_FLOAT_POWER_STACK = 168,
    LIFTED_F4C9E2F_STACK = 188,
    LIFTED_F4D06D0_STACK = 136,
    LIFTED_F4D1A50_STACK = 168,
    LIFTED_F4D1AE0_STACK = 188,
    LIFTED_F4D67E4_STACK = 68,
    LIFTED_F4D74D1_STACK = 72,
    LIFTED_F4E08C1_STACK = 96,
    LIFTED_F4E0C56_STACK = 212,
    LIFTED_F4E5710_STACK = 108,
    LIFTED_F4E5728_STACK = 108,
    LIFTED_F4E576C_STACK = 108,
    LIFTED_F4E5780_STACK = 108,
    LIFTED_F4E5794_STACK = 108,
    LIFTED_F4E57A4_STACK = 108,
    LIFTED_F4E57AC_STACK = 108,
    LIFTED_F4ECF33_STACK = 80,
    LIFTED_F4ECF49_STACK = 72
};

/* Original 0x405720. */
uint32_t lifted_f405720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452960. */
uint32_t lifted_f452960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x474560. */
uint32_t lifted_palette_rgb(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x474910. */
uint32_t lifted_palette_color(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47a040. */
uint32_t lifted_surface_fade(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x483400. */
uint32_t lifted_f483400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x483790. */
uint32_t lifted_f483790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x485520. */
uint32_t lifted_f485520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x486da0. */
uint32_t lifted_f486da0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x486e00. */
uint32_t lifted_f486e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488320. */
uint32_t lifted_f488320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad810. */
uint32_t lifted_f4ad810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9921. */
uint32_t lifted_float_power(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9e2f. */
uint32_t lifted_f4c9e2f(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d06d0. */
uint32_t lifted_f4d06d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1a50. */
uint32_t lifted_f4d1a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1ae0. */
uint32_t lifted_f4d1ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d67e4. */
uint32_t lifted_f4d67e4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d74d1. */
uint32_t lifted_f4d74d1(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e08c1. */
uint32_t lifted_f4e08c1(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0c56. */
uint32_t lifted_f4e0c56(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5710. */
uint32_t lifted_f4e5710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5728. */
uint32_t lifted_f4e5728(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e576c. */
uint32_t lifted_f4e576c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5780. */
uint32_t lifted_f4e5780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5794. */
uint32_t lifted_f4e5794(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e57a4. */
uint32_t lifted_f4e57a4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e57ac. */
uint32_t lifted_f4e57ac(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ecf33. */
uint32_t lifted_f4ecf33(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ecf49. */
uint32_t lifted_f4ecf49(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
