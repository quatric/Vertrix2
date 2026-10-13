#ifndef VERTRIX_LIFTED_WHOLE_1_H
#define VERTRIX_LIFTED_WHOLE_1_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_BOARD_READY_PREVIEWS_STACK = 92,
    LIFTED_BOARD_RESTART_SLOTS_STACK = 100,
    LIFTED_F42EEE0_STACK = 72,
    LIFTED_F42EF00_STACK = 72,
    LIFTED_F42EF10_STACK = 72,
    LIFTED_F42EF20_STACK = 72,
    LIFTED_F42EF30_STACK = 72,
    LIFTED_F42EF40_STACK = 72,
    LIFTED_F42EF50_STACK = 72,
    LIFTED_PLAYER_FILL_BYTE_RANGE_STACK = 68,
    LIFTED_PLAYER_FILL_BYTE_RANGE_42EF80_STACK = 68,
    LIFTED_BOARD_PIECE_SHAPE_FITS_STACK = 124,
    LIFTED_BOARD_PIECE_TOUCHES_SIDE_STACK = 124,
    LIFTED_BOARD_PIECE_TOUCHES_SIDE_42F120_STACK = 124,
    LIFTED_BOARD_MARK_COLUMNS_STACK = 96,
    LIFTED_BOARD_PIECE_STORE_NEGATED_STACK = 76,
    LIFTED_BOARD_FILL_CELLS_STACK = 84,
    LIFTED_F42F310_STACK = 100,
    LIFTED_F42F3D0_STACK = 76,
    LIFTED_F42F410_STACK = 72,
    LIFTED_BOARD_MARK_ROWS_FIRST_STACK = 100,
    LIFTED_BOARD_MARK_ROWS_SECOND_STACK = 100,
    LIFTED_BOARD_PIECE_STORE_TOUCH_STACK = 76,
    LIFTED_BOARD_PIECE_STORE_TOUCH_42F550_STACK = 76,
    LIFTED_F42F580_STACK = 96,
    LIFTED_F42F620_STACK = 104,
    LIFTED_BOARD_PIECE_SHIFT_STACK = 76,
    LIFTED_BOARD_PIECE_SHIFT_42F720_STACK = 76,
    LIFTED_BOARD_DROP_COLUMNS_STACK = 88,
    LIFTED_PLAYER_FILL_BYTE_RANGE_42F7D0_STACK = 68,
    LIFTED_PLAYER_FILL_BYTE_RANGE_42F7F0_STACK = 68,
    LIFTED_PLAYER_FILL_BYTE_RANGE_42F810_STACK = 68,
    LIFTED_PLAYER_FILL_BYTE_RANGE_42F830_STACK = 68,
    LIFTED_F42F850_STACK = 72,
    LIFTED_BOARD_CELL_VALUES_CLEAR_FULL_STACK = 72,
    LIFTED_BOARD_PIECE_CLEAR_OFFSET_X_FULL_STACK = 72,
    LIFTED_BOARD_PIECE_CLEAR_OFFSET_Y_FULL_STACK = 72,
    LIFTED_BOARD_PIECE_SET_OFFSET_X_FULL_STACK = 64,
    LIFTED_BOARD_PIECE_SET_OFFSET_Y_FULL_STACK = 64,
    LIFTED_F42F8B0_STACK = 80,
    LIFTED_BOARD_CELL_VALUES_FILL_FULL_STACK = 80,
    LIFTED_BOARD_SET_ACTOR_CLIP_STACK = 76,
    LIFTED_BOARD_CREATE_OVERLAY_STACK = 164,
    LIFTED_BOARD_EXTRA_IS_IDLE_STACK = 68,
    LIFTED_BOARD_PLACE_EXTRA_STACK = 76,
    LIFTED_BOARD_PLACE_EXTRA_430100_STACK = 76,
    LIFTED_BOARD_RINGS_STACK = 204,
    LIFTED_BOARD_BURST_STACK = 180,
    LIFTED_BLOCK_SPAWN_FULL_STACK = 96,
    LIFTED_F430850_STACK = 148,
    LIFTED_F431100_STACK = 80,
    LIFTED_F431140_STACK = 80,
    LIFTED_F431180_STACK = 72,
    LIFTED_F4311A0_STACK = 72,
    LIFTED_F4311C0_STACK = 128,
    LIFTED_F431280_STACK = 128,
    LIFTED_BOARD_PIECE_COLUMN_STACK = 96,
    LIFTED_BOARD_OBJECT_FIELD_STACK = 64,
    LIFTED_F431390_STACK = 84,
    LIFTED_PLAYER_LEVEL_SIDE_STACK = 88,
    LIFTED_BOARD_OBJECT_FIELD_431480_STACK = 64,
    LIFTED_BOARD_OBJECT_FIELD_431490_STACK = 64,
    LIFTED_F4314A0_STACK = 160,
    LIFTED_BOARD_PLACE_STONES_STACK = 104,
    LIFTED_BOARD_DEAL_FIRST_ROW_STACK = 140,
    LIFTED_BOARD_DEAL_SECOND_ROW_STACK = 140,
    LIFTED_F431AE0_STACK = 72,
    LIFTED_BOARD_PIECE_SPAN_STACK = 104,
    LIFTED_F431B80_STACK = 104,
    LIFTED_BOARD_PIECE_CHILD_KIND_STACK = 72,
    LIFTED_F431D60_STACK = 72,
    LIFTED_BOARD_SET_A68_STACK = 64,
    LIFTED_F431D90_STACK = 184,
    LIFTED_BOARD_PIECE_CHILD_KINDS_STACK = 68,
    LIFTED_BOARD_FLASH_CHILDREN_STACK = 72,
    LIFTED_BOARD_OBJECT_FIELD_432000_STACK = 64,
    LIFTED_BOARD_PIECE_BELOW_TOP_STACK = 68,
    LIFTED_BOARD_PIECE_PAST_EDGE_STACK = 100,
    LIFTED_BOARD_PIECE_PAST_EDGE_432080_STACK = 100,
    LIFTED_PLAYER_TEST_A60_STACK = 64,
    LIFTED_PIECE_ACTOR_SPAWN_STACK = 80,
    LIFTED_PLAYER_PREVIEW_RELEASE_STACK = 80,
    LIFTED_PLAYER_PIECE_CREATE_STACK = 92,
    LIFTED_PLAYER_PIECE_RELEASE_STACK = 84,
    LIFTED_BOARD_PURGE_TYPE_TWO_STACK = 100,
    LIFTED_BOARD_HAS_TYPE_ONE_STACK = 92,
    LIFTED_BOARD_HAS_KIND_SIX_STACK = 92,
    LIFTED_F4323D0_STACK = 112,
    LIFTED_F432820_STACK = 76,
    LIFTED_BOARD_CLEAR_MASK_STACK = 84,
    LIFTED_BOARD_ANY_FALLING_STACK = 348,
    LIFTED_F4328E0_STACK = 96,
    LIFTED_F432980_STACK = 368,
    LIFTED_F432A30_STACK = 392,
    LIFTED_BOARD_MARK_FALLING_CELLS_STACK = 364,
    LIFTED_BOARD_SWAP_SLOTS_STACK = 72,
    LIFTED_BOARD_BURST_OCCUPIED_STACK = 112,
    LIFTED_BOARD_PIECE_HITS_GRID_STACK = 128,
    LIFTED_BOARD_RESET_COUNTER_STACK = 64,
    LIFTED_BOARD_HAS_TYPE_ONE_EXTRA_STACK = 104,
    LIFTED_BOARD_MARKER_REACH_STACK = 116,
    LIFTED_BOARD_MAKE_STONE_STACK = 116,
    LIFTED_F433840_STACK = 272,
    LIFTED_F433E20_STACK = 216,
    LIFTED_BOARD_BUMP_COUNTER_STACK = 64,
    LIFTED_F435E80_STACK = 100,
    LIFTED_F435F30_STACK = 100,
    LIFTED_BOARD_MARKER_NTH_BY_COLUMN_STACK = 84,
    LIFTED_BOARD_MARKER_COUNT_STACK = 88,
    LIFTED_F436070_STACK = 88,
    LIFTED_F4360B0_STACK = 84,
    LIFTED_BOARD_SWAP_MARKED_STACK = 220,
    LIFTED_BOARD_REPLACE_RANDOM_CELL_STACK = 152,
    LIFTED_BOARD_REPLACE_CELL_STACK = 148,
    LIFTED_BOARD_REPLACE_MARKED_STACK = 152,
    LIFTED_F436850_STACK = 104,
    LIFTED_PIECE_REPLACE_CHILDREN_STACK = 140,
    LIFTED_F436A10_STACK = 104,
    LIFTED_F436AA0_STACK = 100,
    LIFTED_F436FE0_STACK = 100,
    LIFTED_BOARD_START_MARKED_STACK = 112,
    LIFTED_F437240_STACK = 100,
    LIFTED_F4372C0_STACK = 104,
    LIFTED_BOARD_MIRROR_MARKED_STACK = 156,
    LIFTED_BOARD_FLAG_MARKED_STACK = 116,
    LIFTED_F4374E0_STACK = 116,
    LIFTED_BOARD_MARK_FILLED_STACK = 88,
    LIFTED_BOARD_STAMP_COMPANIONS_STACK = 96,
    LIFTED_BOARD_SCATTER_MARKED_STACK = 168,
    LIFTED_BOARD_SPLIT_MARKED_STACK = 160,
    LIFTED_BOARD_MARK_STONES_NOT_BOMBS_STACK = 100,
    LIFTED_BOARD_MARK_STONES_STACK = 100,
    LIFTED_ACTOR_START_SLIDE_STACK = 92,
    LIFTED_BOARD_COLLAPSE_MARKED_STACK = 168,
    LIFTED_BOARD_PREPARE_SLOTS_STACK = 96,
    LIFTED_BOARD_MARKER_IN_COLUMN_STACK = 80,
    LIFTED_F4388A0_STACK = 80,
    LIFTED_BOARD_ANY_BOTTOM_STACK = 76,
    LIFTED_BOARD_SET_MOTION_STACK = 156,
    LIFTED_BOARD_ASSIGN_EFFECT_STACK = 116,
    LIFTED_BOARD_APPLY_PATTERN_STACK = 96,
    LIFTED_F438CD0_STACK = 220,
    LIFTED_BOARD_ANY_BLOCK_STACK = 92,
    LIFTED_F438DD0_STACK = 156,
    LIFTED_F438EF0_STACK = 180,
    LIFTED_F439080_STACK = 108,
    LIFTED_F439140_STACK = 76,
    LIFTED_BOARD_DESTROY_MARKED_STACK = 120,
    LIFTED_F439510_STACK = 180,
    LIFTED_BOARD_CLEAR_MARKED_EXTRA_STACK = 112,
    LIFTED_BLOCK_CONSTRUCT_KIND_ONE_FULL_STACK = 68,
    LIFTED_PIECE_CHILD_SLOTS_INIT_STACK = 80,
    LIFTED_PIECE_FRAMES_BUILD_STACK = 148,
    LIFTED_PIECE_CHILDREN_SETUP_STACK = 112,
    LIFTED_PLAYER_WRITE_BYTES_168_STACK = 64,
    LIFTED_PIECE_CHILDREN_SETUP_REGISTERS_STACK = 68,
    LIFTED_PIECE_CHILDREN_RESTORE_AND_CLEAR_STACK = 84,
    LIFTED_PIECE_CHILDREN_REMEMBER_AND_SETUP_STACK = 72,
    LIFTED_F43A5B0_STACK = 72,
    LIFTED_PIECE_CHILDREN_SETUP_SELECTED_STACK = 112,
    LIFTED_F43A6F0_STACK = 168,
    LIFTED_PLAYER_SET_SIDE_STACK = 68,
    LIFTED_PLAYER_INIT_PIECE_AND_DELAYS_STACK = 80,
    LIFTED_F43AB60_STACK = 76,
    LIFTED_OBJECT_REGION_VERDICT_STACK = 76,
    LIFTED_F43ABD0_STACK = 72,
    LIFTED_OBJECT_CHAIN_SELECT_STACK = 104,
    LIFTED_OBJECT_CHAIN_SELECT_PAIR_STACK = 96,
    LIFTED_PLAYER_RESET_PIECE_PROGRESS_STACK = 64,
    LIFTED_F43AD70_STACK = 328,
    LIFTED_F43B260_STACK = 172,
    LIFTED_PLAYER_AI_TICK_STACK = 160,
    LIFTED_PLAYER_DRAW_ALL_DELAYS_STACK = 80,
    LIFTED_AI_REACTION_TIME_STACK = 80,
    LIFTED_PLAYER_DRAW_DELAY_1_STACK = 80,
    LIFTED_PLAYER_DRAW_DELAY_2_STACK = 80,
    LIFTED_PLAYER_DRAW_TABLE_VALUE_STACK = 76,
    LIFTED_PLAYER_PROGRESS_UPDATE_STACK = 100,
    LIFTED_PLAYER_RANDOMIZE_LEVEL_STACK = 88,
    LIFTED_PLAYER_BUMP_LEVEL_STACK = 68,
    LIFTED_PLAYER_SET_LEVEL_STACK = 76,
    LIFTED_PLAYER_SET_E0_FULL_STACK = 64,
    LIFTED_PLAYER_E0_FULL_STACK = 64,
    LIFTED_PLAYER_ALLOC_SIDE_STACK = 88,
    LIFTED_PLAYER_TEST_4E8_STACK = 64,
    LIFTED_PLAYER_RELEASE_SIDE_STACK = 84,
    LIFTED_PLAYER_MATCH_REWARD_STACK = 96,
    LIFTED_PLAYER_CLEAR_FIELD_18C_STACK = 64,
    LIFTED_PLAYER_ADD_SCORE_STACK = 72,
    LIFTED_PLAYER_SET_CD_FULL_STACK = 64,
    LIFTED_PLAYER_SET_CC_FULL_STACK = 64,
    LIFTED_PLAYER_SET_B00_AND_REFRESH_STACK = 68,
    LIFTED_PLAYER_CONDITIONAL_RESET_STACK = 92,
    LIFTED_PLAYER_SET_MODE_AND_REFRESH_STACK = 68,
    LIFTED_PLAYER_PUSH_EVENT_STACK = 132,
    LIFTED_BOARD_VIEW_SETUP_STACK = 148,
    LIFTED_PLAYER_ENTER_452070_STACK = 84,
    LIFTED_PLAYER_ENTER_452370_STACK = 80,
    LIFTED_PLAYER_ENTER_4523D0_STACK = 84,
    LIFTED_PLAYER_TEST_4C4_STACK = 64,
    LIFTED_PLAYER_PARTNER_FREE_FULL_STACK = 64,
    LIFTED_BOARD_VIEW_SETUP_FORWARD_STACK = 68,
    LIFTED_SFX_DISPATCH_EVENT_STACK = 80,
    LIFTED_SFX_DISPATCH_SECONDARY_STACK = 80,
    LIFTED_F43C140_STACK = 84,
    LIFTED_PLAYER_PARTNER_NOT_CC_ONE_FULL_STACK = 64,
    LIFTED_PLAYER_ENTER_4520B0_STACK = 80,
    LIFTED_PLAYER_ADOPT_SIDE_STACK = 88,
    LIFTED_PLAYER_GATED_RESET_STACK = 80,
    LIFTED_PLAYER_SETUP_SIDE_2B_STACK = 84,
    LIFTED_PLAYER_SETUP_SIDE_2C_STACK = 84,
    LIFTED_PLAYER_ENTER_STATE_FULL_STACK = 64,
    LIFTED_PLAYER_RESET_SIDE_STACK = 88,
    LIFTED_PLAYER_SETUP_SIDE_STACK = 84,
    LIFTED_PLAYER_SETUP_INDEXED_STACK = 84,
    LIFTED_PLAYER_SETUP_SIDE_2F_STACK = 84,
    LIFTED_PLAYER_SETUP_SIDE_31_STACK = 84,
    LIFTED_PLAYER_SETUP_SIDE_23_STACK = 88,
    LIFTED_PLAYER_SETUP_SIDE_22_STACK = 88,
    LIFTED_PLAYER_SETUP_SIDE_24_STACK = 84,
    LIFTED_PLAYER_SETUP_SIDE_28_STACK = 88,
    LIFTED_PLAYER_SETUP_SIDE_29_STACK = 88,
    LIFTED_PLAYER_SETUP_SIDE_2A_STACK = 88,
    LIFTED_PLAYER_SETUP_SIDE_2D_STACK = 88,
    LIFTED_PLAYER_SETUP_SIDE_2E_STACK = 88,
    LIFTED_F43D130_STACK = 76,
    LIFTED_PIECE_STACK = 116,
    LIFTED_PLAYER_GENERATE_PREVIEW_STACK = 88,
    LIFTED_PLAYER_CREATE_OVERLAY_STACK = 80,
    LIFTED_OBJECT_LIST_FILLED_STACK = 68,
    LIFTED_OBJECT_VIRTUAL_SLOT6_STACK = 72,
    LIFTED_OBJECT_TABLE_STORE_STACK = 80,
    LIFTED_F43D370_STACK = 80,
    LIFTED_F43D3F0_STACK = 68,
    LIFTED_SLOT_OBJECT_CONSTRUCT_STACK = 136,
    LIFTED_PARTICLE_EMIT_STACK = 156,
    LIFTED_SPAWN_SPREAD_FULL_STACK = 108,
    LIFTED_OBJECT_POPULATE_STACK = 184,
    LIFTED_ARENA_RELEASE_ALL_FULL_STACK = 84,
    LIFTED_BOARD_PARTICLES_SETUP_STACK = 264,
    LIFTED_SPAWN_PLACE_FULL_STACK = 136,
    LIFTED_F43F200_STACK = 752,
    LIFTED_RELEASE_TABLE_A_STACK = 80,
    LIFTED_GLYPH_PRESENT_STACK = 68,
    LIFTED_FONT_MAPS_INITIALIZE_STACK = 520,
    LIFTED_F440490_STACK = 136,
    LIFTED_F440D50_STACK = 244,
    LIFTED_F440FC0_STACK = 176,
    LIFTED_FORWARD_4EA190_STACK = 68,
    LIFTED_F441600_STACK = 496,
    LIFTED_RECORD_DRAW_STACK = 100,
    LIFTED_F441B70_STACK = 408,
    LIFTED_COLOR_TABLE_BUILD_FULL_STACK = 184,
    LIFTED_RELEASE_TABLE_B_STACK = 72,
    LIFTED_F4429A0_STACK = 92,
    LIFTED_F443320_STACK = 112,
    LIFTED_F4433C0_STACK = 112,
    LIFTED_F4434E0_STACK = 96,
    LIFTED_F443550_STACK = 132,
    LIFTED_F443890_STACK = 148,
    LIFTED_F443AB0_STACK = 96,
    LIFTED_F443D50_STACK = 96,
    LIFTED_F444020_STACK = 160,
    LIFTED_F444290_STACK = 132,
    LIFTED_F4443D0_STACK = 112,
    LIFTED_F444850_STACK = 136,
    LIFTED_F444970_STACK = 124,
    LIFTED_F444A30_STACK = 96,
    LIFTED_F444A80_STACK = 128,
    LIFTED_F444B50_STACK = 124,
    LIFTED_F444C80_STACK = 184,
    LIFTED_F444E00_STACK = 248,
    LIFTED_F445090_STACK = 136,
    LIFTED_F445130_STACK = 136,
    LIFTED_F4451D0_STACK = 184,
    LIFTED_F445350_STACK = 272,
    LIFTED_F445630_STACK = 136,
    LIFTED_F4456D0_STACK = 136,
    LIFTED_F445770_STACK = 152,
    LIFTED_F445890_STACK = 104,
    LIFTED_F445900_STACK = 132,
    LIFTED_F445A00_STACK = 116,
    LIFTED_F445A90_STACK = 112,
    LIFTED_F445B10_STACK = 112,
    LIFTED_F445B90_STACK = 180,
    LIFTED_F445D10_STACK = 104,
    LIFTED_F445D80_STACK = 144,
    LIFTED_F445E90_STACK = 104,
    LIFTED_F446440_STACK = 128,
    LIFTED_F4465A0_STACK = 148,
    LIFTED_F446730_STACK = 108,
    LIFTED_F4467C0_STACK = 108,
    LIFTED_F446850_STACK = 172,
    LIFTED_F4469C0_STACK = 124,
    LIFTED_F446A80_STACK = 104,
    LIFTED_F446B10_STACK = 128,
    LIFTED_F446C10_STACK = 164,
    LIFTED_F446D70_STACK = 124,
    LIFTED_F446EC0_STACK = 128,
    LIFTED_F446FE0_STACK = 164,
    LIFTED_F447140_STACK = 124,
    LIFTED_F447290_STACK = 128,
    LIFTED_F4473B0_STACK = 176,
    LIFTED_F447560_STACK = 104,
    LIFTED_F447600_STACK = 140,
    LIFTED_F4476B0_STACK = 88,
    LIFTED_F447740_STACK = 96,
    LIFTED_F447830_STACK = 104,
    LIFTED_F4478F0_STACK = 144,
    LIFTED_F4479F0_STACK = 96,
    LIFTED_F447A50_STACK = 96,
    LIFTED_F447AA0_STACK = 96,
    LIFTED_F447BC0_STACK = 132,
    LIFTED_F447C60_STACK = 160,
    LIFTED_F447D70_STACK = 160,
    LIFTED_F447E80_STACK = 136,
    LIFTED_F447F40_STACK = 104,
    LIFTED_F448010_STACK = 204,
    LIFTED_F448140_STACK = 80,
    LIFTED_F448160_STACK = 68,
    LIFTED_F448180_STACK = 112,
    LIFTED_F448260_STACK = 152,
    LIFTED_F4483D0_STACK = 148,
    LIFTED_F4484F0_STACK = 148,
    LIFTED_F448610_STACK = 100,
    LIFTED_F448670_STACK = 64,
    LIFTED_F448680_STACK = 64,
    LIFTED_F448690_STACK = 68,
    LIFTED_F4486D0_STACK = 68,
    LIFTED_F448740_STACK = 84,
    LIFTED_F448810_STACK = 176,
    LIFTED_F448C20_STACK = 116,
    LIFTED_F448CA0_STACK = 116,
    LIFTED_F448D30_STACK = 144,
    LIFTED_F448E00_STACK = 144,
    LIFTED_F448ED0_STACK = 144,
    LIFTED_F448FB0_STACK = 144,
    LIFTED_F4492F0_STACK = 100,
    LIFTED_ACTOR_FRAME_DECAY_FULL_STACK = 76,
    LIFTED_ACTOR_FRAME_SWITCH_FULL_STACK = 88,
    LIFTED_F4493D0_STACK = 108,
    LIFTED_F449460_STACK = 92,
    LIFTED_F4494C0_STACK = 92,
    LIFTED_F4495B0_STACK = 108,
    LIFTED_F449870_STACK = 96,
    LIFTED_F4498E0_STACK = 180,
    LIFTED_F449A50_STACK = 92,
    LIFTED_F449B50_STACK = 108,
    LIFTED_F449E10_STACK = 96,
    LIFTED_F449E80_STACK = 176,
    LIFTED_F449FF0_STACK = 92,
    LIFTED_F44A040_STACK = 128,
    LIFTED_F44A170_STACK = 128,
    LIFTED_F44A2A0_STACK = 128,
    LIFTED_F44A340_STACK = 92,
    LIFTED_F44A3A0_STACK = 176,
    LIFTED_F44A520_STACK = 92,
    LIFTED_F44A570_STACK = 88,
    LIFTED_F44A5C0_STACK = 88,
    LIFTED_F44A610_STACK = 112,
    LIFTED_F44A6D0_STACK = 96,
    LIFTED_F44A720_STACK = 200,
    LIFTED_F44AA20_STACK = 108,
    LIFTED_F44AA90_STACK = 108,
    LIFTED_F44AB00_STACK = 92,
    LIFTED_F44AB50_STACK = 100,
    LIFTED_F44ABE0_STACK = 148,
    LIFTED_F44ACD0_STACK = 96,
    LIFTED_F44AD20_STACK = 112,
    LIFTED_F44ADD0_STACK = 112,
    LIFTED_F44AE80_STACK = 84,
    LIFTED_F44BAC0_STACK = 92,
    LIFTED_F44BB30_STACK = 92,
    LIFTED_F44BBA0_STACK = 136,
    LIFTED_F44BC50_STACK = 236,
    LIFTED_F44BEB0_STACK = 136,
    LIFTED_F44BF70_STACK = 264,
    LIFTED_F44C1A0_STACK = 140,
    LIFTED_F44C260_STACK = 84,
    LIFTED_PIECE_CHILD_UPDATE_STACK = 68
};

/* Original 0x42ee20. */
uint32_t lifted_board_ready_previews(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ee80. */
uint32_t lifted_board_restart_slots(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42eee0. */
uint32_t lifted_f42eee0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef00. */
uint32_t lifted_f42ef00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef10. */
uint32_t lifted_f42ef10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef20. */
uint32_t lifted_f42ef20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef30. */
uint32_t lifted_f42ef30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef40. */
uint32_t lifted_f42ef40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef50. */
uint32_t lifted_f42ef50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef60. */
uint32_t lifted_player_fill_byte_range(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef80. */
uint32_t lifted_player_fill_byte_range_42ef80(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x42efa0. */
uint32_t lifted_board_piece_shape_fits(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f030. */
uint32_t lifted_board_piece_touches_side(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f120. */
uint32_t lifted_board_piece_touches_side_42f120(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x42f210. */
uint32_t lifted_board_mark_columns(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f280. */
uint32_t lifted_board_piece_store_negated(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f2e0. */
uint32_t lifted_board_fill_cells(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f310. */
uint32_t lifted_f42f310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f3d0. */
uint32_t lifted_f42f3d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f410. */
uint32_t lifted_f42f410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f440. */
uint32_t lifted_board_mark_rows_first(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f4b0. */
uint32_t lifted_board_mark_rows_second(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f520. */
uint32_t lifted_board_piece_store_touch(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f550. */
uint32_t lifted_board_piece_store_touch_42f550(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x42f580. */
uint32_t lifted_f42f580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f620. */
uint32_t lifted_f42f620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f6e0. */
uint32_t lifted_board_piece_shift(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f720. */
uint32_t lifted_board_piece_shift_42f720(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f760. */
uint32_t lifted_board_drop_columns(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f7d0. */
uint32_t lifted_player_fill_byte_range_42f7d0(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x42f7f0. */
uint32_t lifted_player_fill_byte_range_42f7f0(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x42f810. */
uint32_t lifted_player_fill_byte_range_42f810(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x42f830. */
uint32_t lifted_player_fill_byte_range_42f830(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x42f850. */
uint32_t lifted_f42f850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f860. */
uint32_t lifted_board_cell_values_clear_full(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f870. */
uint32_t lifted_board_piece_clear_offset_x_full(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x42f880. */
uint32_t lifted_board_piece_clear_offset_y_full(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x42f890. */
uint32_t lifted_board_piece_set_offset_x_full(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x42f8a0. */
uint32_t lifted_board_piece_set_offset_y_full(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x42f8b0. */
uint32_t lifted_f42f8b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f8e0. */
uint32_t lifted_board_cell_values_fill_full(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ff10. */
uint32_t lifted_board_set_actor_clip(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ff50. */
uint32_t lifted_board_create_overlay(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430090. */
uint32_t lifted_board_extra_is_idle(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4300b0. */
uint32_t lifted_board_place_extra(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430100. */
uint32_t lifted_board_place_extra_430100(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430440. */
uint32_t lifted_board_rings(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430660. */
uint32_t lifted_board_burst(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430800. */
uint32_t lifted_block_spawn_full(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430850. */
uint32_t lifted_f430850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431100. */
uint32_t lifted_f431100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431140. */
uint32_t lifted_f431140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431180. */
uint32_t lifted_f431180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4311a0. */
uint32_t lifted_f4311a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4311c0. */
uint32_t lifted_f4311c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431280. */
uint32_t lifted_f431280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431340. */
uint32_t lifted_board_piece_column(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431380. */
uint32_t lifted_board_object_field(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431390. */
uint32_t lifted_f431390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431400. */
uint32_t lifted_player_level_side(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431480. */
uint32_t lifted_board_object_field_431480(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431490. */
uint32_t lifted_board_object_field_431490(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4314a0. */
uint32_t lifted_f4314a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4316c0. */
uint32_t lifted_board_place_stones(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431780. */
uint32_t lifted_board_deal_first_row(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431930. */
uint32_t lifted_board_deal_second_row(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431ae0. */
uint32_t lifted_f431ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431b20. */
uint32_t lifted_board_piece_span(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431b80. */
uint32_t lifted_f431b80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431c10. */
uint32_t lifted_board_piece_child_kind(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431d60. */
uint32_t lifted_f431d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431d80. */
uint32_t lifted_board_set_a68(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431d90. */
uint32_t lifted_f431d90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431fa0. */
uint32_t lifted_board_piece_child_kinds(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431fb0. */
uint32_t lifted_board_flash_children(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432000. */
uint32_t lifted_board_object_field_432000(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432010. */
uint32_t lifted_board_piece_below_top(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432040. */
uint32_t lifted_board_piece_past_edge(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432080. */
uint32_t lifted_board_piece_past_edge_432080(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4320c0. */
uint32_t lifted_player_test_a60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4320d0. */
uint32_t lifted_piece_actor_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432110. */
uint32_t lifted_player_preview_release(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432160. */
uint32_t lifted_player_piece_create(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4321b0. */
uint32_t lifted_player_piece_release(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432200. */
uint32_t lifted_board_purge_type_two(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432280. */
uint32_t lifted_board_has_type_one(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4322f0. */
uint32_t lifted_board_has_kind_six(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4323d0. */
uint32_t lifted_f4323d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432820. */
uint32_t lifted_f432820(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432840. */
uint32_t lifted_board_clear_mask(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4328a0. */
uint32_t lifted_board_any_falling(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4328e0. */
uint32_t lifted_f4328e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432980. */
uint32_t lifted_f432980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432a30. */
uint32_t lifted_f432a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432b10. */
uint32_t lifted_board_mark_falling_cells(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432ba0. */
uint32_t lifted_board_swap_slots(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x433040. */
uint32_t lifted_board_burst_occupied(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4330d0. */
uint32_t lifted_board_piece_hits_grid(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4334a0. */
uint32_t lifted_board_reset_counter(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4334b0. */
uint32_t lifted_board_has_type_one_extra(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x433550. */
uint32_t lifted_board_marker_reach(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x433750. */
uint32_t lifted_board_make_stone(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x433840. */
uint32_t lifted_f433840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x433e20. */
uint32_t lifted_f433e20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4342f0. */
uint32_t lifted_board_bump_counter(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x435e80. */
uint32_t lifted_f435e80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x435f30. */
uint32_t lifted_f435f30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x435fe0. */
uint32_t lifted_board_marker_nth_by_column(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436030. */
uint32_t lifted_board_marker_count(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436070. */
uint32_t lifted_f436070(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4360b0. */
uint32_t lifted_f4360b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436150. */
uint32_t lifted_board_swap_marked(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436440. */
uint32_t lifted_board_replace_random_cell(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4365c0. */
uint32_t lifted_board_replace_cell(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436720. */
uint32_t lifted_board_replace_marked(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436850. */
uint32_t lifted_f436850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4368e0. */
uint32_t lifted_piece_replace_children(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436a10. */
uint32_t lifted_f436a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436aa0. */
uint32_t lifted_f436aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436fe0. */
uint32_t lifted_f436fe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4371b0. */
uint32_t lifted_board_start_marked(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x437240. */
uint32_t lifted_f437240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4372c0. */
uint32_t lifted_f4372c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x437350. */
uint32_t lifted_board_mirror_marked(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x437460. */
uint32_t lifted_board_flag_marked(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4374e0. */
uint32_t lifted_f4374e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4375a0. */
uint32_t lifted_board_mark_filled(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x437b70. */
uint32_t lifted_board_stamp_companions(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x437be0. */
uint32_t lifted_board_scatter_marked(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x437d70. */
uint32_t lifted_board_split_marked(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x437f60. */
uint32_t lifted_board_mark_stones_not_bombs(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4383f0. */
uint32_t lifted_board_mark_stones(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438470. */
uint32_t lifted_actor_start_slide(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438540. */
uint32_t lifted_board_collapse_marked(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4387b0. */
uint32_t lifted_board_prepare_slots(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438830. */
uint32_t lifted_board_marker_in_column(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4388a0. */
uint32_t lifted_f4388a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438910. */
uint32_t lifted_board_any_bottom(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438960. */
uint32_t lifted_board_set_motion(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438b90. */
uint32_t lifted_board_assign_effect(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438c60. */
uint32_t lifted_board_apply_pattern(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438cd0. */
uint32_t lifted_f438cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438d50. */
uint32_t lifted_board_any_block(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438dd0. */
uint32_t lifted_f438dd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438ef0. */
uint32_t lifted_f438ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x439080. */
uint32_t lifted_f439080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x439140. */
uint32_t lifted_f439140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x439190. */
uint32_t lifted_board_destroy_marked(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x439510. */
uint32_t lifted_f439510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4398c0. */
uint32_t lifted_board_clear_marked_extra(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a080. */
uint32_t lifted_block_construct_kind_one_full(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x43a160. */
uint32_t lifted_piece_child_slots_init(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a310. */
uint32_t lifted_piece_frames_build(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a410. */
uint32_t lifted_piece_children_setup(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a4f0. */
uint32_t lifted_player_write_bytes_168(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a510. */
uint32_t lifted_piece_children_setup_registers(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x43a520. */
uint32_t lifted_piece_children_restore_and_clear(const VertrixCalls *calls,
                                                 const VertrixFactoryServices *services,
                                                 const VertrixGlobals *globals,
                                                 const LiftEntry *entry);

/* Original 0x43a560. */
uint32_t lifted_piece_children_remember_and_setup(const VertrixCalls *calls,
                                                  const VertrixFactoryServices *services,
                                                  const VertrixGlobals *globals,
                                                  const LiftEntry *entry);

/* Original 0x43a5b0. */
uint32_t lifted_f43a5b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a5f0. */
uint32_t lifted_piece_children_setup_selected(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x43a6f0. */
uint32_t lifted_f43a6f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43aab0. */
uint32_t lifted_player_set_side(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ab30. */
uint32_t lifted_player_init_piece_and_delays(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ab60. */
uint32_t lifted_f43ab60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ab80. */
uint32_t lifted_object_region_verdict(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43abd0. */
uint32_t lifted_f43abd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ac00. */
uint32_t lifted_object_chain_select(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43acd0. */
uint32_t lifted_object_chain_select_pair(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ad50. */
uint32_t lifted_player_reset_piece_progress(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ad70. */
uint32_t lifted_f43ad70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b260. */
uint32_t lifted_f43b260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b430. */
uint32_t lifted_player_ai_tick(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b590. */
uint32_t lifted_player_draw_all_delays(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b5b0. */
uint32_t lifted_ai_reaction_time(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b660. */
uint32_t lifted_player_draw_delay_1(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b680. */
uint32_t lifted_player_draw_delay_2(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b6a0. */
uint32_t lifted_player_draw_table_value(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b720. */
uint32_t lifted_player_progress_update(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b7c0. */
uint32_t lifted_player_randomize_level(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b800. */
uint32_t lifted_player_bump_level(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b810. */
uint32_t lifted_player_set_level(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b860. */
uint32_t lifted_player_set_e0_full(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b870. */
uint32_t lifted_player_e0_full(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b930. */
uint32_t lifted_player_alloc_side(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b970. */
uint32_t lifted_player_test_4e8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b980. */
uint32_t lifted_player_release_side(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b9c0. */
uint32_t lifted_player_match_reward(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ba80. */
uint32_t lifted_player_clear_field_18c(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ba90. */
uint32_t lifted_player_add_score(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bad0. */
uint32_t lifted_player_set_cd_full(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bae0. */
uint32_t lifted_player_set_cc_full(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43baf0. */
uint32_t lifted_player_set_b00_and_refresh(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bb00. */
uint32_t lifted_player_conditional_reset(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bb40. */
uint32_t lifted_player_set_mode_and_refresh(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bb60. */
uint32_t lifted_player_push_event(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bbf0. */
uint32_t lifted_board_view_setup(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bc90. */
uint32_t lifted_player_enter_452070(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bce0. */
uint32_t lifted_player_enter_452370(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bd00. */
uint32_t lifted_player_enter_4523d0(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bd40. */
uint32_t lifted_player_test_4c4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bd60. */
uint32_t lifted_player_partner_free_full(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bd80. */
uint32_t lifted_board_view_setup_forward(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43c0e0. */
uint32_t lifted_sfx_dispatch_event(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43c110. */
uint32_t lifted_sfx_dispatch_secondary(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43c140. */
uint32_t lifted_f43c140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cc90. */
uint32_t lifted_player_partner_not_cc_one_full(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x43ccb0. */
uint32_t lifted_player_enter_4520b0(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ccf0. */
uint32_t lifted_player_adopt_side(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cd30. */
uint32_t lifted_player_gated_reset(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cd60. */
uint32_t lifted_player_setup_side_2b(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cda0. */
uint32_t lifted_player_setup_side_2c(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cde0. */
uint32_t lifted_player_enter_state_full(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ce00. */
uint32_t lifted_player_reset_side(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ce30. */
uint32_t lifted_player_setup_side(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ce70. */
uint32_t lifted_player_setup_indexed(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ceb0. */
uint32_t lifted_player_setup_side_2f(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cef0. */
uint32_t lifted_player_setup_side_31(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cf30. */
uint32_t lifted_player_setup_side_23(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cf70. */
uint32_t lifted_player_setup_side_22(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cfb0. */
uint32_t lifted_player_setup_side_24(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cff0. */
uint32_t lifted_player_setup_side_28(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d030. */
uint32_t lifted_player_setup_side_29(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d070. */
uint32_t lifted_player_setup_side_2a(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d0b0. */
uint32_t lifted_player_setup_side_2d(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d0f0. */
uint32_t lifted_player_setup_side_2e(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d130. */
uint32_t lifted_f43d130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d180. */
uint32_t lifted_piece(const VertrixCalls *calls, const VertrixFactoryServices *services,
                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d260. */
uint32_t lifted_player_generate_preview(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d2b0. */
uint32_t lifted_player_create_overlay(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d300. */
uint32_t lifted_object_list_filled(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d320. */
uint32_t lifted_object_virtual_slot6(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d330. */
uint32_t lifted_object_table_store(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d370. */
uint32_t lifted_f43d370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d3f0. */
uint32_t lifted_f43d3f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d6a0. */
uint32_t lifted_slot_object_construct(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43dc80. */
uint32_t lifted_particle_emit(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43dea0. */
uint32_t lifted_spawn_spread_full(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43dff0. */
uint32_t lifted_object_populate(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e260. */
uint32_t lifted_arena_release_all_full(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e4d0. */
uint32_t lifted_board_particles_setup(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e920. */
uint32_t lifted_spawn_place_full(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f200. */
uint32_t lifted_f43f200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f3f0. */
uint32_t lifted_release_table_a(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f460. */
uint32_t lifted_glyph_present(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43fc50. */
uint32_t lifted_font_maps_initialize(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x440490. */
uint32_t lifted_f440490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x440d50. */
uint32_t lifted_f440d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x440fc0. */
uint32_t lifted_f440fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441120. */
uint32_t lifted_forward_4ea190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441600. */
uint32_t lifted_f441600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441b30. */
uint32_t lifted_record_draw(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441b70. */
uint32_t lifted_f441b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441e30. */
uint32_t lifted_color_table_build_full(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x442110. */
uint32_t lifted_release_table_b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4429a0. */
uint32_t lifted_f4429a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443320. */
uint32_t lifted_f443320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4433c0. */
uint32_t lifted_f4433c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4434e0. */
uint32_t lifted_f4434e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443550. */
uint32_t lifted_f443550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443890. */
uint32_t lifted_f443890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443ab0. */
uint32_t lifted_f443ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443d50. */
uint32_t lifted_f443d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444020. */
uint32_t lifted_f444020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444290. */
uint32_t lifted_f444290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4443d0. */
uint32_t lifted_f4443d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444850. */
uint32_t lifted_f444850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444970. */
uint32_t lifted_f444970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444a30. */
uint32_t lifted_f444a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444a80. */
uint32_t lifted_f444a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444b50. */
uint32_t lifted_f444b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444c80. */
uint32_t lifted_f444c80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444e00. */
uint32_t lifted_f444e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445090. */
uint32_t lifted_f445090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445130. */
uint32_t lifted_f445130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4451d0. */
uint32_t lifted_f4451d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445350. */
uint32_t lifted_f445350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445630. */
uint32_t lifted_f445630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4456d0. */
uint32_t lifted_f4456d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445770. */
uint32_t lifted_f445770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445890. */
uint32_t lifted_f445890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445900. */
uint32_t lifted_f445900(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445a00. */
uint32_t lifted_f445a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445a90. */
uint32_t lifted_f445a90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445b10. */
uint32_t lifted_f445b10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445b90. */
uint32_t lifted_f445b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445d10. */
uint32_t lifted_f445d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445d80. */
uint32_t lifted_f445d80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445e90. */
uint32_t lifted_f445e90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446440. */
uint32_t lifted_f446440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4465a0. */
uint32_t lifted_f4465a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446730. */
uint32_t lifted_f446730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4467c0. */
uint32_t lifted_f4467c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446850. */
uint32_t lifted_f446850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4469c0. */
uint32_t lifted_f4469c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446a80. */
uint32_t lifted_f446a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446b10. */
uint32_t lifted_f446b10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446c10. */
uint32_t lifted_f446c10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446d70. */
uint32_t lifted_f446d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446ec0. */
uint32_t lifted_f446ec0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446fe0. */
uint32_t lifted_f446fe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447140. */
uint32_t lifted_f447140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447290. */
uint32_t lifted_f447290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4473b0. */
uint32_t lifted_f4473b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447560. */
uint32_t lifted_f447560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447600. */
uint32_t lifted_f447600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4476b0. */
uint32_t lifted_f4476b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447740. */
uint32_t lifted_f447740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447830. */
uint32_t lifted_f447830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4478f0. */
uint32_t lifted_f4478f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4479f0. */
uint32_t lifted_f4479f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447a50. */
uint32_t lifted_f447a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447aa0. */
uint32_t lifted_f447aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447bc0. */
uint32_t lifted_f447bc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447c60. */
uint32_t lifted_f447c60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447d70. */
uint32_t lifted_f447d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447e80. */
uint32_t lifted_f447e80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447f40. */
uint32_t lifted_f447f40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448010. */
uint32_t lifted_f448010(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448140. */
uint32_t lifted_f448140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448160. */
uint32_t lifted_f448160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448180. */
uint32_t lifted_f448180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448260. */
uint32_t lifted_f448260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4483d0. */
uint32_t lifted_f4483d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4484f0. */
uint32_t lifted_f4484f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448610. */
uint32_t lifted_f448610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448670. */
uint32_t lifted_f448670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448680. */
uint32_t lifted_f448680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448690. */
uint32_t lifted_f448690(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4486d0. */
uint32_t lifted_f4486d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448740. */
uint32_t lifted_f448740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448810. */
uint32_t lifted_f448810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448c20. */
uint32_t lifted_f448c20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448ca0. */
uint32_t lifted_f448ca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448d30. */
uint32_t lifted_f448d30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448e00. */
uint32_t lifted_f448e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448ed0. */
uint32_t lifted_f448ed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448fb0. */
uint32_t lifted_f448fb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4492f0. */
uint32_t lifted_f4492f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449360. */
uint32_t lifted_actor_frame_decay_full(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449390. */
uint32_t lifted_actor_frame_switch_full(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4493d0. */
uint32_t lifted_f4493d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449460. */
uint32_t lifted_f449460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4494c0. */
uint32_t lifted_f4494c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4495b0. */
uint32_t lifted_f4495b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449870. */
uint32_t lifted_f449870(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4498e0. */
uint32_t lifted_f4498e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449a50. */
uint32_t lifted_f449a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449b50. */
uint32_t lifted_f449b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449e10. */
uint32_t lifted_f449e10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449e80. */
uint32_t lifted_f449e80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449ff0. */
uint32_t lifted_f449ff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44a040. */
uint32_t lifted_f44a040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44a170. */
uint32_t lifted_f44a170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44a2a0. */
uint32_t lifted_f44a2a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44a340. */
uint32_t lifted_f44a340(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44a3a0. */
uint32_t lifted_f44a3a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44a520. */
uint32_t lifted_f44a520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44a570. */
uint32_t lifted_f44a570(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44a5c0. */
uint32_t lifted_f44a5c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44a610. */
uint32_t lifted_f44a610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44a6d0. */
uint32_t lifted_f44a6d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44a720. */
uint32_t lifted_f44a720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44aa20. */
uint32_t lifted_f44aa20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44aa90. */
uint32_t lifted_f44aa90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ab00. */
uint32_t lifted_f44ab00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ab50. */
uint32_t lifted_f44ab50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44abe0. */
uint32_t lifted_f44abe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44acd0. */
uint32_t lifted_f44acd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ad20. */
uint32_t lifted_f44ad20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44add0. */
uint32_t lifted_f44add0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ae80. */
uint32_t lifted_f44ae80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44bac0. */
uint32_t lifted_f44bac0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44bb30. */
uint32_t lifted_f44bb30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44bba0. */
uint32_t lifted_f44bba0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44bc50. */
uint32_t lifted_f44bc50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44beb0. */
uint32_t lifted_f44beb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44bf70. */
uint32_t lifted_f44bf70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c1a0. */
uint32_t lifted_f44c1a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c260. */
uint32_t lifted_f44c260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c2a0. */
uint32_t lifted_piece_child_update(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);
#endif
