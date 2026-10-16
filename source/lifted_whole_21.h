#ifndef VERTRIX_LIFTED_WHOLE_21_H
#define VERTRIX_LIFTED_WHOLE_21_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_WINDOW_TABLES_STACK = 208,
    LIFTED_MIXER_PLAYBACK_TICK_STACK = 88,
    LIFTED_F41CC30_STACK = 704,
    LIFTED_F41E780_STACK = 548,
    LIFTED_AI_FALLBACK_STACK = 252,
    LIFTED_AI_CHAIN_SEARCH_STACK = 600,
    LIFTED_AI_BOMB_SEARCH_STACK = 268,
    LIFTED_EFFECTS_RELEASE_ALL_FULL_STACK = 80,
    LIFTED_DELAY_ACTOR_SPAWN_STACK = 128,
    LIFTED_SURFACE_BOUNDS_STACK = 124,
    LIFTED_F484B60_STACK = 752,
    LIFTED_OBJECT_IS_IDLE_STACK = 96,
    LIFTED_SCALED_ROUND_STACK = 64,
    LIFTED_RTL_RANGE_TABLE_FIND_STACK = 68,
    LIFTED_F4DA3BA_STACK = 1400,
    LIFTED_F4DF320_STACK = 248
};

/* Original 0x40a590. */
uint32_t lifted_window_tables(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e030. */
uint32_t lifted_mixer_playback_tick(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41cc30. */
uint32_t lifted_f41cc30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41e780. */
uint32_t lifted_f41e780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x426240. */
uint32_t lifted_ai_fallback(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4269e0. */
uint32_t lifted_ai_chain_search(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x427380. */
uint32_t lifted_ai_bomb_search(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d800. */
uint32_t lifted_effects_release_all_full(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471340. */
uint32_t lifted_delay_actor_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4792d0. */
uint32_t lifted_surface_bounds(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484b60. */
uint32_t lifted_f484b60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c0b51. */
uint32_t lifted_object_is_idle(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5d60. */
uint32_t lifted_scaled_round(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
