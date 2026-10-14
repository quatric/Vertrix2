#ifndef VERTRIX_LIFTED_WHOLE_21_H
#define VERTRIX_LIFTED_WHOLE_21_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_BITS_FILL_STACK = 128,
    LIFTED_WINDOW_TABLES_STACK = 208,
    LIFTED_F40C320_STACK = 88,
    LIFTED_FILE_READ_WORD_SWAPPED_STACK = 88,
    LIFTED_MIXER_VOLUME_COLUMN_STACK = 92,
    LIFTED_MIXER_PLAYBACK_TICK_STACK = 88,
    LIFTED_MIXER_NOTE_RELEASE_STACK = 68,
    LIFTED_DEVICE_LOCK_STACK = 80,
    LIFTED_DEVICE_MARK_DIRTY_STACK = 68,
    LIFTED_DEVICE_GET_LOCKED_STACK = 68,
    LIFTED_TABLE_LEVEL_FOR_STACK = 72,
    LIFTED_RECORD_STEP_STACK = 68,
    LIFTED_F412510_STACK = 68,
    LIFTED_RECORD_FIELD_STACK = 68,
    LIFTED_RECORD_STORE_CURRENT_STACK = 80,
    LIFTED_TEXT_TABLE_REFRESH_STACK = 148,
    LIFTED_GLOBAL_RESET_PAIR_FULL_STACK = 68,
    LIFTED_SESSION_LATCH_RELEASE_STACK = 68,
    LIFTED_GLOBAL_CLEAR_TABLES_FULL_STACK = 68,
    LIFTED_SESSION_REGISTERS_RESET_STACK = 68,
    LIFTED_SESSION_REGISTERS_RESET_OPEN_STACK = 72,
    LIFTED_SESSION_REGISTERS_RESET_SECONDARY_STACK = 68,
    LIFTED_QUAD_AVERAGE_STACK = 112,
    LIFTED_TABLE_BONUS_STACK = 68,
    LIFTED_F41B310_STACK = 1060,
    LIFTED_F41C410_STACK = 572,
    LIFTED_F41CC30_STACK = 704,
    LIFTED_F41E780_STACK = 548,
    LIFTED_F41F9B0_STACK = 476,
    LIFTED_F424360_STACK = 668,
    LIFTED_AI_ROW_REACH_STACK = 84,
    LIFTED_AI_FALLBACK_STACK = 252,
    LIFTED_AI_CHAIN_SEARCH_STACK = 600,
    LIFTED_AI_BOMB_SEARCH_STACK = 268,
    LIFTED_AI_MODE_FLAGS_STACK = 76,
    LIFTED_AI_CHOICE_SCORES_STACK = 112,
    LIFTED_F429750_STACK = 140,
    LIFTED_CHOICE_GRID_STORE_VALUES_STACK = 92,
    LIFTED_PIECE_RELEASE_CHILDREN_FULL_STACK = 72,
    LIFTED_PIECE_CHILDREN_PLACE_STACK = 88,
    LIFTED_PIECE_SET_OFFSET_X_FULL_STACK = 64,
    LIFTED_PIECE_SET_OFFSET_Y_FULL_STACK = 64,
    LIFTED_PLAYER_PREVIEW_TOGGLE_STACK = 72,
    LIFTED_PLAYER_PREVIEW_SET_MODE_STACK = 64,
    LIFTED_BOARD_PIECE_ALL_HANDLER_42EDF0_STACK = 76,
    LIFTED_BOARD_PIECE_STORE_NEGATED_ALWAYS_STACK = 72,
    LIFTED_BOARD_RELEASE_EXTRA_STACK = 80,
    LIFTED_ACTOR_SPAWN_MATCH_EFFECT_STACK = 152,
    LIFTED_ACTOR_SPAWN_MATCH_BURST_STACK = 184,
    LIFTED_F436100_STACK = 84,
    LIFTED_F439370_STACK = 92,
    LIFTED_EFFECTS_RELEASE_ALL_FULL_STACK = 80,
    LIFTED_F43E1A0_STACK = 160,
    LIFTED_F43EAB0_STACK = 384,
    LIFTED_OBJECT_START_HOLD_STACK = 84,
    LIFTED_TABLE_FILL_SLOT_STACK = 136,
    LIFTED_RESOURCE_PAIRED_FINISH_STACK = 212,
    LIFTED_F461610_STACK = 240,
    LIFTED_F461790_STACK = 252,
    LIFTED_OPTIONS_BUILD_STACK = 1132,
    LIFTED_LETTER_ROW_STACK = 236,
    LIFTED_LETTER_ROW_SECOND_STACK = 236,
    LIFTED_PANEL_SPAWN_STACK = 168,
    LIFTED_SLIDE_PAIR_STACK = 228,
    LIFTED_DELAY_ACTOR_SPAWN_STACK = 128,
    LIFTED_UI_SLIDE_FROM_BELOW_STACK = 68,
    LIFTED_SCENE_LOOKUP_PAIR_STACK = 92,
    LIFTED_OBJECT_FLIP_454_STACK = 72,
    LIFTED_OBJECT_FLIP_454_471E80_STACK = 72,
    LIFTED_OBJECT_GET_464_STACK = 64,
    LIFTED_OBJECT_GET_174_STACK = 64,
    LIFTED_OBJECT_GET_178_STACK = 64,
    LIFTED_POINT_LIST_WHEN_ONE_STACK = 68,
    LIFTED_PAIR_FLAGS_STACK = 144,
    LIFTED_PAIR_FLAGS_473960_STACK = 144,
    LIFTED_PAIR_SCAN_STACK = 144,
    LIFTED_LIST_PUSH_CALL_STACK = 80,
    LIFTED_OFFSET_CALL_STACK = 68,
    LIFTED_F477390_STACK = 224,
    LIFTED_F477B10_STACK = 236,
    LIFTED_SURFACE_WRITE_STACK = 72,
    LIFTED_SURFACE_BOUNDS_STACK = 124,
    LIFTED_OBJECT_DWORD_480070_STACK = 64,
    LIFTED_SCRATCH_PAIR_CALL_STACK = 88,
    LIFTED_F484B60_STACK = 752,
    LIFTED_FIND_SIZE_FIELD_STACK = 372,
    LIFTED_OBJECT_NOTIFY_FIELD_STACK = 76,
    LIFTED_OBJECT_NOTIFY_GLOBAL_STACK = 76,
    LIFTED_OBJECT_NOTIFY_FIELD_48C330_STACK = 76,
    LIFTED_COPY_DWORD_FULL_STACK = 64,
    LIFTED_OBJECT_CLEAR_WITH_ONES_STACK = 72,
    LIFTED_RENDER_PALETTE_WEIGHTED_PIXEL_STACK = 92,
    LIFTED_F4930C0_STACK = 100,
    LIFTED_F49B000_STACK = 112,
    LIFTED_F4A30A0_STACK = 112,
    LIFTED_F4A3540_STACK = 72,
    LIFTED_F4A3580_STACK = 72,
    LIFTED_F4A3660_STACK = 72,
    LIFTED_F4A3720_STACK = 72,
    LIFTED_F4A3770_STACK = 76,
    LIFTED_F4A3880_STACK = 72,
    LIFTED_F4A3970_STACK = 80,
    LIFTED_F4A3AC0_STACK = 76,
    LIFTED_F4A3B50_STACK = 84,
    LIFTED_F4A3CE0_STACK = 76,
    LIFTED_F4A3D70_STACK = 84,
    LIFTED_F4A3E20_STACK = 84,
    LIFTED_F4A3ED0_STACK = 84,
    LIFTED_F4A3F80_STACK = 76,
    LIFTED_F4A3FD0_STACK = 80,
    LIFTED_F4A4040_STACK = 80,
    LIFTED_F4A4170_STACK = 80,
    LIFTED_F4A42B0_STACK = 76,
    LIFTED_F4A43E0_STACK = 84,
    LIFTED_F4A4520_STACK = 84,
    LIFTED_F4A4660_STACK = 84,
    LIFTED_F4A47A0_STACK = 84,
    LIFTED_F4A48E0_STACK = 80,
    LIFTED_F4A49E0_STACK = 84,
    LIFTED_F4A4B10_STACK = 84,
    LIFTED_F4A4C40_STACK = 76,
    LIFTED_F4A4CD0_STACK = 84,
    LIFTED_F4A4E80_STACK = 80,
    LIFTED_F4A4F90_STACK = 84,
    LIFTED_F4A50C0_STACK = 84,
    LIFTED_F4A5180_STACK = 88,
    LIFTED_F4A5300_STACK = 84,
    LIFTED_F4A5420_STACK = 84,
    LIFTED_F4A54E0_STACK = 88,
    LIFTED_F4A5660_STACK = 84,
    LIFTED_F4A5780_STACK = 84,
    LIFTED_F4A5840_STACK = 88,
    LIFTED_F4A59C0_STACK = 76,
    LIFTED_F4A5AA0_STACK = 76,
    LIFTED_F4A5B00_STACK = 80,
    LIFTED_F4A5C20_STACK = 76,
    LIFTED_F4A5D20_STACK = 76,
    LIFTED_F4A5DB0_STACK = 80,
    LIFTED_F4A5EF0_STACK = 80,
    LIFTED_F4A6020_STACK = 80,
    LIFTED_F4A6170_STACK = 80,
    LIFTED_F4A62D0_STACK = 80,
    LIFTED_F4A6400_STACK = 80,
    LIFTED_F4A6550_STACK = 80,
    LIFTED_F4A66B0_STACK = 76,
    LIFTED_F4A67F0_STACK = 88,
    LIFTED_F4A6950_STACK = 88,
    LIFTED_F4A6AA0_STACK = 88,
    LIFTED_F4A6BF0_STACK = 84,
    LIFTED_F4A6D10_STACK = 84,
    LIFTED_F4A6E60_STACK = 92,
    LIFTED_F4A7050_STACK = 92,
    LIFTED_F4A7240_STACK = 84,
    LIFTED_F4A73B0_STACK = 88,
    LIFTED_F4A74B0_STACK = 92,
    LIFTED_F4A7690_STACK = 88,
    LIFTED_F4A7790_STACK = 92,
    LIFTED_F4A7940_STACK = 84,
    LIFTED_F4A7AF0_STACK = 84,
    LIFTED_F4A7C30_STACK = 96,
    LIFTED_F4A7D60_STACK = 96,
    LIFTED_F4A7F60_STACK = 84,
    LIFTED_F4A80E0_STACK = 96,
    LIFTED_F4A82C0_STACK = 76,
    LIFTED_F4A83C0_STACK = 72,
    LIFTED_F4A84B0_STACK = 80,
    LIFTED_F4A85C0_STACK = 76,
    LIFTED_F4A8760_STACK = 84,
    LIFTED_F4A88D0_STACK = 88,
    LIFTED_F4A8A30_STACK = 84,
    LIFTED_F4A8BE0_STACK = 88,
    LIFTED_F4A8D40_STACK = 84,
    LIFTED_F4A8EA0_STACK = 84,
    LIFTED_F4A8FF0_STACK = 84,
    LIFTED_F4A9250_STACK = 84,
    LIFTED_F4A9390_STACK = 80,
    LIFTED_F4A94F0_STACK = 76,
    LIFTED_F4A9640_STACK = 88,
    LIFTED_F4A97D0_STACK = 92,
    LIFTED_F4A99A0_STACK = 92,
    LIFTED_F4A9BA0_STACK = 84,
    LIFTED_F4A9D70_STACK = 76,
    LIFTED_F4A9DE0_STACK = 92,
    LIFTED_F4A9EE0_STACK = 80,
    LIFTED_F4AA030_STACK = 80,
    LIFTED_F4AA0B0_STACK = 92,
    LIFTED_F4AA1E0_STACK = 84,
    LIFTED_F4AA450_STACK = 88,
    LIFTED_F4AA660_STACK = 92,
    LIFTED_F4AA7F0_STACK = 88,
    LIFTED_F4AA950_STACK = 88,
    LIFTED_F4AAA40_STACK = 88,
    LIFTED_F4AABE0_STACK = 92,
    LIFTED_F4AAD90_STACK = 104,
    LIFTED_RENDER_ALPHA_IMAGE32_STACK = 108,
    LIFTED_F4AB4A0_STACK = 96,
    LIFTED_F4AB540_STACK = 96,
    LIFTED_F4AB5E0_STACK = 116,
    LIFTED_F4AB790_STACK = 96,
    LIFTED_F4AB830_STACK = 96,
    LIFTED_F4AB8D0_STACK = 116,
    LIFTED_F4ABA80_STACK = 100,
    LIFTED_F4ABB30_STACK = 100,
    LIFTED_F4ABBD0_STACK = 112,
    LIFTED_ACTOR_DOUBLE_ORBIT_POINT_STACK = 100,
    LIFTED_ACTOR_SET_WORDS_3A_FULL_STACK = 64,
    LIFTED_ACTOR_IMAGE_BOUNDS_STACK = 96,
    LIFTED_OBJECT_LIST_PRUNE_STACK = 100,
    LIFTED_OBJECT_GLYPH_LAYOUT_STACK = 76,
    LIFTED_LIST_ITEM_4B6FA0_STACK = 68,
    LIFTED_OBJECT_IS_IDLE_STACK = 96,
    LIFTED_EDX_TO_EAX_CALL_4C5BD0_STACK = 68,
    LIFTED_SCALED_ROUND_STACK = 64,
    LIFTED_F4CD520_STACK = 92,
    LIFTED_RTL_STRING_TAIL_STACK = 116,
    LIFTED_RTL_CLASS_ADDRESS_STACK = 64,
    LIFTED_RTL_RANGE_TABLE_FIND_STACK = 68,
    LIFTED_MESSAGE_DISPATCH_STACK = 132,
    LIFTED_F4D77D0_STACK = 432,
    LIFTED_RTL_SELECT_FLOAT_HELPERS_STACK = 68,
    LIFTED_RTL_PROBE_CALL_STACK = 92,
    LIFTED_F4DA3BA_STACK = 1400,
    LIFTED_RTL_FLAGS_CALL_STACK = 80,
    LIFTED_RTL_LOOKUP_CALL_STACK = 72,
    LIFTED_RTL_PAIR_CALL_STACK = 72,
    LIFTED_F4DDC40_STACK = 72,
    LIFTED_NODE_POOL_TAKE_QUAD_STACK = 92,
    LIFTED_F4DF320_STACK = 248,
    LIFTED_F4E14DC_STACK = 72,
    LIFTED_F4E5B0C_STACK = 120
};

/* Original 0x4074a0. */
uint32_t lifted_bits_fill(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a590. */
uint32_t lifted_window_tables(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c320. */
uint32_t lifted_f40c320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c360. */
uint32_t lifted_file_read_word_swapped(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40dc80. */
uint32_t lifted_mixer_volume_column(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e030. */
uint32_t lifted_mixer_playback_tick(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e640. */
uint32_t lifted_mixer_note_release(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ede0. */
uint32_t lifted_device_lock(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ee30. */
uint32_t lifted_device_mark_dirty(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ef40. */
uint32_t lifted_device_get_locked(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40f170. */
uint32_t lifted_table_level_for(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x412430. */
uint32_t lifted_record_step(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x412510. */
uint32_t lifted_f412510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4125e0. */
uint32_t lifted_record_field(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x412690. */
uint32_t lifted_record_store_current(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415180. */
uint32_t lifted_text_table_refresh(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415530. */
uint32_t lifted_global_reset_pair_full(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415550. */
uint32_t lifted_session_latch_release(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415b10. */
uint32_t lifted_global_clear_tables_full(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415b50. */
uint32_t lifted_session_registers_reset(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415b90. */
uint32_t lifted_session_registers_reset_open(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415bd0. */
uint32_t lifted_session_registers_reset_secondary(const VertrixCalls *calls,
                                                  const VertrixFactoryServices *services,
                                                  const VertrixGlobals *globals,
                                                  const LiftEntry *entry);

/* Original 0x4179d0. */
uint32_t lifted_quad_average(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417e20. */
uint32_t lifted_table_bonus(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4261b0. */
uint32_t lifted_ai_row_reach(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x429e80. */
uint32_t lifted_choice_grid_store_values(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a480. */
uint32_t lifted_piece_release_children_full(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a800. */
uint32_t lifted_piece_children_place(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a960. */
uint32_t lifted_piece_set_offset_x_full(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a970. */
uint32_t lifted_piece_set_offset_y_full(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b0f0. */
uint32_t lifted_player_preview_toggle(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b110. */
uint32_t lifted_player_preview_set_mode(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42edf0. */
uint32_t lifted_board_piece_all_handler_42edf0(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x42f2b0. */
uint32_t lifted_board_piece_store_negated_always(const VertrixCalls *calls,
                                                 const VertrixFactoryServices *services,
                                                 const VertrixGlobals *globals,
                                                 const LiftEntry *entry);

/* Original 0x430150. */
uint32_t lifted_board_release_extra(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430190. */
uint32_t lifted_actor_spawn_match_effect(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4302a0. */
uint32_t lifted_actor_spawn_match_burst(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436100. */
uint32_t lifted_f436100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x439370. */
uint32_t lifted_f439370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d800. */
uint32_t lifted_effects_release_all_full(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e1a0. */
uint32_t lifted_f43e1a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43eab0. */
uint32_t lifted_f43eab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450f80. */
uint32_t lifted_object_start_hold(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e750. */
uint32_t lifted_table_fill_slot(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f020. */
uint32_t lifted_resource_paired_finish(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
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

/* Original 0x471020. */
uint32_t lifted_panel_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4711a0. */
uint32_t lifted_slide_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471340. */
uint32_t lifted_delay_actor_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4717f0. */
uint32_t lifted_ui_slide_from_below(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471e10. */
uint32_t lifted_scene_lookup_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471e60. */
uint32_t lifted_object_flip_454(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471e80. */
uint32_t lifted_object_flip_454_471e80(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471eb0. */
uint32_t lifted_object_get_464(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471ec0. */
uint32_t lifted_object_get_174(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471ed0. */
uint32_t lifted_object_get_178(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473610. */
uint32_t lifted_point_list_when_one(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
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

/* Original 0x475d90. */
uint32_t lifted_offset_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477390. */
uint32_t lifted_f477390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477b10. */
uint32_t lifted_f477b10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478ed0. */
uint32_t lifted_surface_write(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4792d0. */
uint32_t lifted_surface_bounds(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480070. */
uint32_t lifted_object_dword_480070(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482610. */
uint32_t lifted_scratch_pair_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484b60. */
uint32_t lifted_f484b60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489610. */
uint32_t lifted_find_size_field(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c260. */
uint32_t lifted_object_notify_field(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c280. */
uint32_t lifted_object_notify_global(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c330. */
uint32_t lifted_object_notify_field_48c330(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c370. */
uint32_t lifted_copy_dword_full(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d500. */
uint32_t lifted_object_clear_with_ones(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x490340. */
uint32_t lifted_render_palette_weighted_pixel(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x4930c0. */
uint32_t lifted_f4930c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49b000. */
uint32_t lifted_f49b000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a30a0. */
uint32_t lifted_f4a30a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a3540. */
uint32_t lifted_f4a3540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a3580. */
uint32_t lifted_f4a3580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a3660. */
uint32_t lifted_f4a3660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a3720. */
uint32_t lifted_f4a3720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a3770. */
uint32_t lifted_f4a3770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a3880. */
uint32_t lifted_f4a3880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a3970. */
uint32_t lifted_f4a3970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a3ac0. */
uint32_t lifted_f4a3ac0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a3b50. */
uint32_t lifted_f4a3b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a3ce0. */
uint32_t lifted_f4a3ce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a3d70. */
uint32_t lifted_f4a3d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a3e20. */
uint32_t lifted_f4a3e20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a3ed0. */
uint32_t lifted_f4a3ed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a3f80. */
uint32_t lifted_f4a3f80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a3fd0. */
uint32_t lifted_f4a3fd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a4040. */
uint32_t lifted_f4a4040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a4170. */
uint32_t lifted_f4a4170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a42b0. */
uint32_t lifted_f4a42b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a43e0. */
uint32_t lifted_f4a43e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a4520. */
uint32_t lifted_f4a4520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a4660. */
uint32_t lifted_f4a4660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a47a0. */
uint32_t lifted_f4a47a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a48e0. */
uint32_t lifted_f4a48e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a49e0. */
uint32_t lifted_f4a49e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a4b10. */
uint32_t lifted_f4a4b10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a4c40. */
uint32_t lifted_f4a4c40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a4cd0. */
uint32_t lifted_f4a4cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a4e80. */
uint32_t lifted_f4a4e80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a4f90. */
uint32_t lifted_f4a4f90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a50c0. */
uint32_t lifted_f4a50c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a5180. */
uint32_t lifted_f4a5180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a5300. */
uint32_t lifted_f4a5300(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a5420. */
uint32_t lifted_f4a5420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a54e0. */
uint32_t lifted_f4a54e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a5660. */
uint32_t lifted_f4a5660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a5780. */
uint32_t lifted_f4a5780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a5840. */
uint32_t lifted_f4a5840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a59c0. */
uint32_t lifted_f4a59c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a5aa0. */
uint32_t lifted_f4a5aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a5b00. */
uint32_t lifted_f4a5b00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a5c20. */
uint32_t lifted_f4a5c20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a5d20. */
uint32_t lifted_f4a5d20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a5db0. */
uint32_t lifted_f4a5db0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a5ef0. */
uint32_t lifted_f4a5ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a6020. */
uint32_t lifted_f4a6020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a6170. */
uint32_t lifted_f4a6170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a62d0. */
uint32_t lifted_f4a62d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a6400. */
uint32_t lifted_f4a6400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a6550. */
uint32_t lifted_f4a6550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a66b0. */
uint32_t lifted_f4a66b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a67f0. */
uint32_t lifted_f4a67f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a6950. */
uint32_t lifted_f4a6950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a6aa0. */
uint32_t lifted_f4a6aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a6bf0. */
uint32_t lifted_f4a6bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a6d10. */
uint32_t lifted_f4a6d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a6e60. */
uint32_t lifted_f4a6e60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a7050. */
uint32_t lifted_f4a7050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a7240. */
uint32_t lifted_f4a7240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a73b0. */
uint32_t lifted_f4a73b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a74b0. */
uint32_t lifted_f4a74b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a7690. */
uint32_t lifted_f4a7690(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a7790. */
uint32_t lifted_f4a7790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a7940. */
uint32_t lifted_f4a7940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a7af0. */
uint32_t lifted_f4a7af0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a7c30. */
uint32_t lifted_f4a7c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a7d60. */
uint32_t lifted_f4a7d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a7f60. */
uint32_t lifted_f4a7f60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a80e0. */
uint32_t lifted_f4a80e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a82c0. */
uint32_t lifted_f4a82c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a83c0. */
uint32_t lifted_f4a83c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a84b0. */
uint32_t lifted_f4a84b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a85c0. */
uint32_t lifted_f4a85c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a8760. */
uint32_t lifted_f4a8760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a88d0. */
uint32_t lifted_f4a88d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a8a30. */
uint32_t lifted_f4a8a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a8be0. */
uint32_t lifted_f4a8be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a8d40. */
uint32_t lifted_f4a8d40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a8ea0. */
uint32_t lifted_f4a8ea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a8ff0. */
uint32_t lifted_f4a8ff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a9250. */
uint32_t lifted_f4a9250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a9390. */
uint32_t lifted_f4a9390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a94f0. */
uint32_t lifted_f4a94f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a9640. */
uint32_t lifted_f4a9640(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a97d0. */
uint32_t lifted_f4a97d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a99a0. */
uint32_t lifted_f4a99a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a9ba0. */
uint32_t lifted_f4a9ba0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a9d70. */
uint32_t lifted_f4a9d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a9de0. */
uint32_t lifted_f4a9de0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a9ee0. */
uint32_t lifted_f4a9ee0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aa030. */
uint32_t lifted_f4aa030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aa0b0. */
uint32_t lifted_f4aa0b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aa1e0. */
uint32_t lifted_f4aa1e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aa450. */
uint32_t lifted_f4aa450(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aa660. */
uint32_t lifted_f4aa660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aa7f0. */
uint32_t lifted_f4aa7f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aa950. */
uint32_t lifted_f4aa950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aaa40. */
uint32_t lifted_f4aaa40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aabe0. */
uint32_t lifted_f4aabe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aad90. */
uint32_t lifted_f4aad90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ab380. */
uint32_t lifted_render_alpha_image32(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ab4a0. */
uint32_t lifted_f4ab4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ab540. */
uint32_t lifted_f4ab540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ab5e0. */
uint32_t lifted_f4ab5e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ab790. */
uint32_t lifted_f4ab790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ab830. */
uint32_t lifted_f4ab830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ab8d0. */
uint32_t lifted_f4ab8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aba80. */
uint32_t lifted_f4aba80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4abb30. */
uint32_t lifted_f4abb30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4abbd0. */
uint32_t lifted_f4abbd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad3c0. */
uint32_t lifted_actor_double_orbit_point(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad520. */
uint32_t lifted_actor_set_words_3a_full(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b15e0. */
uint32_t lifted_actor_image_bounds(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5f50. */
uint32_t lifted_object_list_prune(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b69f0. */
uint32_t lifted_object_glyph_layout(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6fa0. */
uint32_t lifted_list_item_4b6fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c0b51. */
uint32_t lifted_object_is_idle(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5bd0. */
uint32_t lifted_edx_to_eax_call_4c5bd0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5d60. */
uint32_t lifted_scaled_round(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd520. */
uint32_t lifted_f4cd520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cdaf0. */
uint32_t lifted_rtl_string_tail(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cfa10. */
uint32_t lifted_rtl_class_address(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d82c6. */
uint32_t lifted_rtl_select_float_helpers(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d94a0. */
uint32_t lifted_rtl_probe_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4da3ba. */
uint32_t lifted_f4da3ba(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db866. */
uint32_t lifted_rtl_flags_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc160. */
uint32_t lifted_rtl_lookup_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd440. */
uint32_t lifted_rtl_pair_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ddc40. */
uint32_t lifted_f4ddc40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df070. */
uint32_t lifted_node_pool_take_quad(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df320. */
uint32_t lifted_f4df320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e14dc. */
uint32_t lifted_f4e14dc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5b0c. */
uint32_t lifted_f4e5b0c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
