#ifndef VERTRIX_LIFTED_WHOLE_3_H
#define VERTRIX_LIFTED_WHOLE_3_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F45C9A0_STACK = 248,
    LIFTED_F4627A0_STACK = 1572,
    LIFTED_F4633B0_STACK = 3240,
    LIFTED_F4651B0_STACK = 708,
    LIFTED_F466D60_STACK = 2768,
    LIFTED_F469480_STACK = 984,
    LIFTED_F46A410_STACK = 644,
    LIFTED_HUD_BUILD_STACK = 1096,
    LIFTED_F46C9D0_STACK = 2064,
    LIFTED_LETTER_MENU_STACK = 480,
    LIFTED_F46F440_STACK = 1140,
    LIFTED_SURFACE_FLIP_VERTICAL_STACK = 112,
    LIFTED_SURFACE_BLIT_STACK = 104,
    LIFTED_F47E680_STACK = 188,
    LIFTED_F47EAB0_STACK = 96
};

/* Original 0x45c9a0. */
uint32_t lifted_f45c9a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4627a0. */
uint32_t lifted_f4627a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4633b0. */
uint32_t lifted_f4633b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4651b0. */
uint32_t lifted_f4651b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x466d60. */
uint32_t lifted_f466d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x469480. */
uint32_t lifted_f469480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46a410. */
uint32_t lifted_f46a410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46b810. */
uint32_t lifted_hud_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46c9d0. */
uint32_t lifted_f46c9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46ea30. */
uint32_t lifted_letter_menu(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46f440. */
uint32_t lifted_f46f440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479b50. */
uint32_t lifted_surface_flip_vertical(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ce10. */
uint32_t lifted_surface_blit(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e680. */
uint32_t lifted_f47e680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47eab0. */
uint32_t lifted_f47eab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
