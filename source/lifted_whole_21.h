#ifndef VERTRIX_LIFTED_WHOLE_21_H
#define VERTRIX_LIFTED_WHOLE_21_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_BITS_FILL_STACK = 128,
    LIFTED_WINDOW_TABLES_STACK = 208,
    LIFTED_MIXER_VOLUME_COLUMN_STACK = 92,
    LIFTED_MIXER_PLAYBACK_TICK_STACK = 88,
    LIFTED_TEXT_TABLE_REFRESH_STACK = 148,
    LIFTED_QUAD_AVERAGE_STACK = 112,
    LIFTED_F41B310_STACK = 1060,
    LIFTED_F41C410_STACK = 572,
    LIFTED_F41CC30_STACK = 704,
    LIFTED_F41E780_STACK = 548,
    LIFTED_F41F9B0_STACK = 476,
    LIFTED_F424360_STACK = 668,
    LIFTED_AI_FALLBACK_STACK = 252,
    LIFTED_AI_CHAIN_SEARCH_STACK = 600,
    LIFTED_AI_BOMB_SEARCH_STACK = 268,
    LIFTED_AI_MODE_FLAGS_STACK = 76,
    LIFTED_AI_CHOICE_SCORES_STACK = 112,
    LIFTED_F429750_STACK = 140,
    LIFTED_ACTOR_SPAWN_MATCH_EFFECT_STACK = 152,
    LIFTED_ACTOR_SPAWN_MATCH_BURST_STACK = 184,
    LIFTED_EFFECTS_RELEASE_ALL_FULL_STACK = 80,
    LIFTED_F43EAB0_STACK = 384,
    LIFTED_F461610_STACK = 240,
    LIFTED_F461790_STACK = 252,
    LIFTED_OPTIONS_BUILD_STACK = 1132,
    LIFTED_LETTER_ROW_STACK = 236,
    LIFTED_LETTER_ROW_SECOND_STACK = 236,
    LIFTED_SLIDE_PAIR_STACK = 228,
    LIFTED_DELAY_ACTOR_SPAWN_STACK = 128,
    LIFTED_PAIR_FLAGS_STACK = 144,
    LIFTED_PAIR_FLAGS_473960_STACK = 144,
    LIFTED_PAIR_SCAN_STACK = 144,
    LIFTED_LIST_PUSH_CALL_STACK = 80,
    LIFTED_F477390_STACK = 224,
    LIFTED_F477B10_STACK = 236,
    LIFTED_SURFACE_BOUNDS_STACK = 124,
    LIFTED_F484B60_STACK = 752,
    LIFTED_FIND_SIZE_FIELD_STACK = 372,
    LIFTED_RENDER_PALETTE_WEIGHTED_PIXEL_STACK = 92,
    LIFTED_ACTOR_DOUBLE_ORBIT_POINT_STACK = 100,
    LIFTED_ACTOR_IMAGE_BOUNDS_STACK = 96,
    LIFTED_OBJECT_IS_IDLE_STACK = 96,
    LIFTED_SCALED_ROUND_STACK = 64,
    LIFTED_F4CD520_STACK = 92,
    LIFTED_RTL_RANGE_TABLE_FIND_STACK = 68,
    LIFTED_MESSAGE_DISPATCH_STACK = 132,
    LIFTED_F4D77D0_STACK = 432,
    LIFTED_F4DA3BA_STACK = 1400,
    LIFTED_RTL_FLAGS_CALL_STACK = 80,
    LIFTED_F4DF320_STACK = 248,
    LIFTED_F4E5B0C_STACK = 120
};

/* Original 0x4074a0. */
uint32_t lifted_bits_fill(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a590. */
uint32_t lifted_window_tables(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40dc80. */
uint32_t lifted_mixer_volume_column(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e030. */
uint32_t lifted_mixer_playback_tick(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415180. */
uint32_t lifted_text_table_refresh(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4179d0. */
uint32_t lifted_quad_average(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41b310. */
uint32_t lifted_f41b310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c410. */
uint32_t lifted_f41c410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41cc30. */
uint32_t lifted_f41cc30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41e780. */
uint32_t lifted_f41e780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41f9b0. */
uint32_t lifted_f41f9b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424360. */
uint32_t lifted_f424360(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x427e10. */
uint32_t lifted_ai_mode_flags(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x428e70. */
uint32_t lifted_ai_choice_scores(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429750. */
uint32_t lifted_f429750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430190. */
uint32_t lifted_actor_spawn_match_effect(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4302a0. */
uint32_t lifted_actor_spawn_match_burst(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d800. */
uint32_t lifted_effects_release_all_full(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43eab0. */
uint32_t lifted_f43eab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x461610. */
uint32_t lifted_f461610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x461790. */
uint32_t lifted_f461790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x461fc0. */
uint32_t lifted_options_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46f000. */
uint32_t lifted_letter_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46f220. */
uint32_t lifted_letter_row_second(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4711a0. */
uint32_t lifted_slide_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471340. */
uint32_t lifted_delay_actor_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4737d0. */
uint32_t lifted_pair_flags(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473960. */
uint32_t lifted_pair_flags_473960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473af0. */
uint32_t lifted_pair_scan(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475ab0. */
uint32_t lifted_list_push_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477390. */
uint32_t lifted_f477390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477b10. */
uint32_t lifted_f477b10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4792d0. */
uint32_t lifted_surface_bounds(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484b60. */
uint32_t lifted_f484b60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489610. */
uint32_t lifted_find_size_field(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x490340. */
uint32_t lifted_render_palette_weighted_pixel(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x4ad3c0. */
uint32_t lifted_actor_double_orbit_point(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b15e0. */
uint32_t lifted_actor_image_bounds(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c0b51. */
uint32_t lifted_object_is_idle(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5d60. */
uint32_t lifted_scaled_round(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd520. */
uint32_t lifted_f4cd520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d0b30. */
uint32_t lifted_rtl_range_table_find(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2020. */
uint32_t lifted_message_dispatch(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d77d0. */
uint32_t lifted_f4d77d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4da3ba. */
uint32_t lifted_f4da3ba(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db866. */
uint32_t lifted_rtl_flags_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df320. */
uint32_t lifted_f4df320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5b0c. */
uint32_t lifted_f4e5b0c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
