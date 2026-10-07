#ifndef VERTRIX_LIFTED_WHOLE_1_H
#define VERTRIX_LIFTED_WHOLE_1_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_BOARD_RINGS_STACK = 204,
    LIFTED_BOARD_BURST_STACK = 180,
    LIFTED_BLOCK_SPAWN_STACK = 96,
    LIFTED_F430850_STACK = 148,
    LIFTED_F431100_STACK = 80,
    LIFTED_F431140_STACK = 80,
    LIFTED_F431180_STACK = 72,
    LIFTED_F4311A0_STACK = 72,
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
    LIFTED_BOARD_PIECE_CHILD_KIND_STACK = 72,
    LIFTED_F431D60_STACK = 72,
    LIFTED_BOARD_SET_A68_STACK = 64,
    LIFTED_F431D90_STACK = 184,
    LIFTED_BOARD_PIECE_CHILD_KINDS_STACK = 68,
    LIFTED_BOARD_FLASH_CHILDREN_STACK = 72,
    LIFTED_BOARD_OBJECT_FIELD_432000_STACK = 64,
    LIFTED_BOARD_PIECE_BELOW_TOP_STACK = 68,
    LIFTED_BOARD_HAS_PIECE_STACK = 64,
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
    LIFTED_F4328E0_STACK = 96,
    LIFTED_BOARD_SWAP_SLOTS_STACK = 72,
    LIFTED_BOARD_BURST_OCCUPIED_STACK = 112,
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
    LIFTED_F436100_STACK = 84,
    LIFTED_F436850_STACK = 104,
    LIFTED_PIECE_REPLACE_CHILDREN_STACK = 140,
    LIFTED_F436A10_STACK = 104,
    LIFTED_F436AA0_STACK = 100,
    LIFTED_F436FE0_STACK = 100,
    LIFTED_F437240_STACK = 100,
    LIFTED_F4372C0_STACK = 104,
    LIFTED_BOARD_MARK_FILLED_STACK = 88,
    LIFTED_BOARD_STAMP_COMPANIONS_STACK = 96,
    LIFTED_BOARD_MARK_STONES_NOT_BOMBS_STACK = 100,
    LIFTED_BOARD_MARK_STONES_STACK = 100,
    LIFTED_ACTOR_START_SLIDE_STACK = 92,
    LIFTED_BOARD_PREPARE_SLOTS_STACK = 96,
    LIFTED_BOARD_MARKER_IN_COLUMN_STACK = 80,
    LIFTED_F4388A0_STACK = 80,
    LIFTED_BOARD_ANY_BOTTOM_STACK = 76,
    LIFTED_BOARD_SET_MOTION_STACK = 156,
    LIFTED_BOARD_ASSIGN_EFFECT_STACK = 116,
    LIFTED_BOARD_APPLY_PATTERN_STACK = 96,
    LIFTED_BOARD_ANY_BLOCK_STACK = 92,
    LIFTED_F438DD0_STACK = 156,
    LIFTED_F438EF0_STACK = 180,
    LIFTED_F439140_STACK = 76,
    LIFTED_BOARD_DESTROY_MARKED_STACK = 120,
    LIFTED_F439370_STACK = 92,
    LIFTED_F439510_STACK = 180,
    LIFTED_BOARD_CLEAR_MARKED_EXTRA_STACK = 112,
    LIFTED_BLOCK_CONSTRUCT_KIND_ONE_STACK = 68,
    LIFTED_PIECE_CHILD_SLOTS_INIT_STACK = 80,
    LIFTED_PIECE_FRAMES_BUILD_STACK = 148,
    LIFTED_PIECE_CHILDREN_SETUP_STACK = 112,
    LIFTED_PIECE_STORE_PREVIEW_KINDS_STACK = 64,
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
    LIFTED_PLAYER_SET_E0_STACK = 64,
    LIFTED_PLAYER_E0_STACK = 64,
    LIFTED_PLAYER_ALLOC_SIDE_STACK = 88,
    LIFTED_PLAYER_FLAG_4E8_STACK = 64,
    LIFTED_PLAYER_RELEASE_SIDE_STACK = 84,
    LIFTED_PLAYER_MATCH_REWARD_STACK = 96,
    LIFTED_PLAYER_BONUS_METER_FULL_STACK = 64,
    LIFTED_PLAYER_CLEAR_FIELD_18C_STACK = 64,
    LIFTED_PLAYER_ADD_SCORE_STACK = 72,
    LIFTED_PLAYER_SET_CD_STACK = 64,
    LIFTED_PLAYER_SET_CC_STACK = 64,
    LIFTED_PLAYER_SET_B00_AND_REFRESH_STACK = 68,
    LIFTED_PLAYER_CONDITIONAL_RESET_STACK = 92,
    LIFTED_PLAYER_SET_MODE_AND_REFRESH_STACK = 68,
    LIFTED_PLAYER_PUSH_EVENT_STACK = 132,
    LIFTED_PLAYER_ENTER_452070_STACK = 84,
    LIFTED_PLAYER_ENTER_452370_STACK = 80,
    LIFTED_PLAYER_ENTER_4523D0_STACK = 84,
    LIFTED_PLAYER_BYTE_4C4_IS_ONE_STACK = 64,
    LIFTED_PLAYER_PARTNER_FREE_STACK = 64,
    LIFTED_BOARD_VIEW_SETUP_FORWARD_STACK = 68,
    LIFTED_SFX_DISPATCH_EVENT_STACK = 80,
    LIFTED_SFX_DISPATCH_SECONDARY_STACK = 80,
    LIFTED_F43C140_STACK = 84,
    LIFTED_PLAYER_PARTNER_NOT_CC_ONE_STACK = 64,
    LIFTED_PLAYER_ENTER_4520B0_STACK = 80,
    LIFTED_PLAYER_ADOPT_SIDE_STACK = 88,
    LIFTED_PLAYER_GATED_RESET_STACK = 80,
    LIFTED_PLAYER_SETUP_SIDE_2B_STACK = 84,
    LIFTED_PLAYER_SETUP_SIDE_2C_STACK = 84,
    LIFTED_PLAYER_ENTER_STATE_STACK = 64,
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
    LIFTED_PLAYER_GENERATE_PREVIEW_STACK = 88,
    LIFTED_PLAYER_CREATE_OVERLAY_STACK = 80,
    LIFTED_OBJECT_LIST_FILLED_STACK = 68,
    LIFTED_OBJECT_VIRTUAL_SLOT6_STACK = 72,
    LIFTED_OBJECT_TABLE_STORE_STACK = 80,
    LIFTED_F43D370_STACK = 80,
    LIFTED_F43D3F0_STACK = 68,
    LIFTED_SLOT_OBJECT_CONSTRUCT_STACK = 136,
    LIFTED_EFFECTS_RELEASE_ALL_FULL_STACK = 80,
    LIFTED_PARTICLE_EMIT_STACK = 156,
    LIFTED_SPAWN_SPREAD_STACK = 108,
    LIFTED_OBJECT_POPULATE_STACK = 184,
    LIFTED_BOARD_PARTICLES_RESET_STACK = 140,
    LIFTED_ARENA_RELEASE_ALL_FULL_STACK = 84,
    LIFTED_BOARD_PARTICLES_SETUP_STACK = 264,
    LIFTED_PARTICLE_INIT_DRIFT_STACK = 96,
    LIFTED_PARTICLE_INIT_FALL_STACK = 100,
    LIFTED_SPAWN_PLACE_STACK = 136,
    LIFTED_RELEASE_TABLE_A_STACK = 80,
    LIFTED_FONT_GLYPH_STACK = 72,
    LIFTED_GLYPH_PRESENT_STACK = 68,
    LIFTED_F43F480_STACK = 124,
    LIFTED_KEY_BINDING_APPLY_STACK = 124,
    LIFTED_F43F630_STACK = 124,
    LIFTED_F43F710_STACK = 124,
    LIFTED_F43F7F0_STACK = 124,
    LIFTED_F43F8D0_STACK = 124,
    LIFTED_F43F9B0_STACK = 124,
    LIFTED_F43FA90_STACK = 124,
    LIFTED_F43FB70_STACK = 124,
    LIFTED_FONT_MAPS_INITIALIZE_STACK = 520,
    LIFTED_F440490_STACK = 136,
    LIFTED_F440A20_STACK = 224,
    LIFTED_F440D50_STACK = 244,
    LIFTED_FORWARD_4EA190_STACK = 68,
    LIFTED_CHAIN_OBJECT_CONSTRUCT_STACK = 136,
    LIFTED_RECORD_INIT_STACK = 88,
    LIFTED_RECORD_RELEASE_FULL_STACK = 104,
    LIFTED_RECORD_DRAW_STACK = 100,
    LIFTED_RELEASE_TABLE_B_STACK = 72,
    LIFTED_F4429A0_STACK = 92,
    LIFTED_TEXT_WIDTH_STACK = 76,
    LIFTED_F443260_STACK = 84,
    LIFTED_F443320_STACK = 112,
    LIFTED_F4433C0_STACK = 112,
    LIFTED_F443460_STACK = 124,
    LIFTED_F4434E0_STACK = 96,
    LIFTED_F443550_STACK = 132,
    LIFTED_F443890_STACK = 148,
    LIFTED_F443AB0_STACK = 96,
    LIFTED_F443D50_STACK = 96,
    LIFTED_F444020_STACK = 160,
    LIFTED_F444290_STACK = 132,
    LIFTED_F4443D0_STACK = 112,
    LIFTED_F444A30_STACK = 96,
    LIFTED_F445090_STACK = 136,
    LIFTED_F445130_STACK = 136,
    LIFTED_F445630_STACK = 136,
    LIFTED_F4456D0_STACK = 136,
    LIFTED_F445890_STACK = 104,
    LIFTED_F445A00_STACK = 116,
    LIFTED_F445A90_STACK = 112,
    LIFTED_F445B10_STACK = 112,
    LIFTED_F445D10_STACK = 104,
    LIFTED_F445E90_STACK = 104,
    LIFTED_F446730_STACK = 108,
    LIFTED_F4467C0_STACK = 108,
    LIFTED_F4469C0_STACK = 124,
    LIFTED_F446A80_STACK = 104,
    LIFTED_F446B10_STACK = 128,
    LIFTED_F446D70_STACK = 124,
    LIFTED_F446EC0_STACK = 128,
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
    LIFTED_F447E80_STACK = 136,
    LIFTED_F447F40_STACK = 104,
    LIFTED_F448140_STACK = 80,
    LIFTED_F448160_STACK = 68,
    LIFTED_F448180_STACK = 112,
    LIFTED_F448610_STACK = 100,
    LIFTED_F448670_STACK = 64,
    LIFTED_F448680_STACK = 64,
    LIFTED_F448690_STACK = 68,
    LIFTED_F4486D0_STACK = 68,
    LIFTED_F4486F0_STACK = 84,
    LIFTED_F448740_STACK = 84,
    LIFTED_F448790_STACK = 120,
    LIFTED_F448810_STACK = 176,
    LIFTED_F448C20_STACK = 116,
    LIFTED_F448CA0_STACK = 116,
    LIFTED_F448D30_STACK = 144,
    LIFTED_F448E00_STACK = 144,
    LIFTED_F448ED0_STACK = 144,
    LIFTED_F448FB0_STACK = 144,
    LIFTED_F4492F0_STACK = 100,
    LIFTED_ACTOR_FRAME_DECAY_STACK = 76,
    LIFTED_ACTOR_FRAME_SWITCH_STACK = 88,
    LIFTED_F4493D0_STACK = 108,
    LIFTED_F449460_STACK = 92,
    LIFTED_F4494C0_STACK = 92,
    LIFTED_F4495B0_STACK = 108,
    LIFTED_F449870_STACK = 96,
    LIFTED_F449A50_STACK = 92,
    LIFTED_F449B50_STACK = 108,
    LIFTED_F449E10_STACK = 96,
    LIFTED_F449FF0_STACK = 92,
    LIFTED_F44A340_STACK = 92,
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
    LIFTED_F44BEB0_STACK = 136,
    LIFTED_F44BF70_STACK = 264,
    LIFTED_F44C1A0_STACK = 140,
    LIFTED_F44C260_STACK = 84,
    LIFTED_PIECE_CHILD_UPDATE_STACK = 68,
    LIFTED_PIECE_CHILD_UPDATE_44C2B0_STACK = 104,
    LIFTED_PIECE_CHILD_UPDATE_44C310_STACK = 104,
    LIFTED_PIECE_CHILD_UPDATE_44C370_STACK = 104,
    LIFTED_F44C3D0_STACK = 68,
    LIFTED_F44C3E0_STACK = 108,
    LIFTED_F44C450_STACK = 108,
    LIFTED_F44C4C0_STACK = 108,
    LIFTED_F44C530_STACK = 108,
    LIFTED_F44C5A0_STACK = 104,
    LIFTED_F44C610_STACK = 104,
    LIFTED_F44C680_STACK = 104,
    LIFTED_F44C6E0_STACK = 104,
    LIFTED_F44C780_STACK = 108,
    LIFTED_F44C7F0_STACK = 108,
    LIFTED_BLOCK_UPDATE_STACK = 76,
    LIFTED_BLOCK_MOTION_UPDATE_STACK = 108,
    LIFTED_F44C8E0_STACK = 108,
    LIFTED_F44C940_STACK = 76,
    LIFTED_BLOCK_FADE_UPDATE_STACK = 108,
    LIFTED_BLOCK_PULSE_UPDATE_STACK = 108,
    LIFTED_F44CA40_STACK = 108,
    LIFTED_F44CAB0_STACK = 120,
    LIFTED_F44CB50_STACK = 120,
    LIFTED_BLOCK_BYTE_PULSE_UPDATE_STACK = 108,
    LIFTED_BLOCK_BYTE_PULSE_UPDATE_44CC60_STACK = 108,
    LIFTED_BLOCK_SCALE_UPDATE_STACK = 108,
    LIFTED_BLOCK_RETURN_UPDATE_STACK = 108,
    LIFTED_F44CF70_STACK = 108,
    LIFTED_F44CFD0_STACK = 108,
    LIFTED_F44D1E0_STACK = 108,
    LIFTED_F44D250_STACK = 108,
    LIFTED_F44D2C0_STACK = 108,
    LIFTED_F44D330_STACK = 108,
    LIFTED_F44D3A0_STACK = 108,
    LIFTED_BLOCK_BYTE_PULSE_UPDATE_44D410_STACK = 108,
    LIFTED_F44D480_STACK = 108,
    LIFTED_F44D4F0_STACK = 108,
    LIFTED_F44D560_STACK = 120,
    LIFTED_F44D5F0_STACK = 108,
    LIFTED_F44D660_STACK = 108,
    LIFTED_F44D6D0_STACK = 120,
    LIFTED_BLOCK_BYTE_PULSE_UPDATE_44D760_STACK = 108,
    LIFTED_F44D7D0_STACK = 108,
    LIFTED_F44D840_STACK = 108,
    LIFTED_BLOCK_MODE_PULSE_UPDATE_STACK = 116,
    LIFTED_F44D940_STACK = 116,
    LIFTED_F44D9D0_STACK = 120,
    LIFTED_BLOCK_HALF_PULSE_UPDATE_STACK = 120,
    LIFTED_F44DB10_STACK = 120,
    LIFTED_F44DBB0_STACK = 124,
    LIFTED_F44DC80_STACK = 108,
    LIFTED_F44DCF0_STACK = 128,
    LIFTED_BLOCK_SLIDE_UPDATE_STACK = 120,
    LIFTED_F44E2D0_STACK = 120,
    LIFTED_BLOCK_COLLAPSE_UPDATE_STACK = 120,
    LIFTED_F44E410_STACK = 116,
    LIFTED_BLOCK_VISIBILITY_UPDATE_STACK = 108,
    LIFTED_F44E510_STACK = 108,
    LIFTED_BLOCK_SWELL_UPDATE_STACK = 108,
    LIFTED_F44E600_STACK = 108,
    LIFTED_F44E670_STACK = 108,
    LIFTED_BLOCK_ACCELERATE_UPDATE_STACK = 124,
    LIFTED_BLOCK_MODE_AMOUNT_UPDATE_STACK = 108,
    LIFTED_F44E800_STACK = 120,
    LIFTED_BLOCK_PERIOD_UPDATE_STACK = 116,
    LIFTED_BLOCK_TRAVEL_UPDATE_STACK = 108,
    LIFTED_F44EC40_STACK = 120,
    LIFTED_F44F040_STACK = 108,
    LIFTED_F44F0B0_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F180_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F1E0_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F240_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F2B0_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F320_STACK = 108,
    LIFTED_BLOCK_CYCLE_UPDATE_STACK = 104,
    LIFTED_F44F3E0_STACK = 104,
    LIFTED_F44F430_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F4A0_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F500_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F560_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F5D0_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F630_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F690_STACK = 108,
    LIFTED_F44F700_STACK = 108,
    LIFTED_F44F770_STACK = 108,
    LIFTED_F44F7E0_STACK = 120,
    LIFTED_F44F880_STACK = 120,
    LIFTED_F44F920_STACK = 108,
    LIFTED_F44F990_STACK = 108,
    LIFTED_F44FA00_STACK = 108,
    LIFTED_NUMBER_PLAYER_UPDATE_STACK = 80,
    LIFTED_F44FAA0_STACK = 84,
    LIFTED_NUMBER_TRANSITION_UPDATE_STACK = 100,
    LIFTED_NUMBER_TRANSITION_UPDATE_44FB40_STACK = 104,
    LIFTED_NUMBER_TRANSITION_UPDATE_44FBB0_STACK = 96,
    LIFTED_F44FC00_STACK = 80,
    LIFTED_F44FC30_STACK = 84,
    LIFTED_NUMBER_TRANSITION_CONFIGURED_STACK = 104,
    LIFTED_NUMBER_TRANSITION_CONFIGURED_44FCF0_STACK = 104,
    LIFTED_NUMBER_TRANSITION_CONFIGURED_44FD60_STACK = 96,
    LIFTED_NUMBER_TRANSITION_CONFIGURED_44FDB0_STACK = 108,
    LIFTED_NUMBER_TRANSITION_CONFIGURED_44FE30_STACK = 96,
    LIFTED_PLAYER_INDICATOR_UPDATE_STACK = 84,
    LIFTED_PLAYER_INDICATOR_UPDATE_44FED0_STACK = 96,
    LIFTED_PLAYER_INDICATOR_UPDATE_44FF30_STACK = 88,
    LIFTED_PLAYER_INDICATOR_UPDATE_44FF60_STACK = 80,
    LIFTED_UI_INDICATOR_STORAGE_UPDATE_STACK = 88,
    LIFTED_UI_INDICATOR_STORAGE_UPDATE_44FFF0_STACK = 96,
    LIFTED_UI_INDICATOR_STORAGE_UPDATE_450040_STACK = 92,
    LIFTED_UI_INDICATOR_STORAGE_UPDATE_4500B0_STACK = 100,
    LIFTED_UI_INDICATOR_STORAGE_UPDATE_450100_STACK = 80,
    LIFTED_UI_BORDER_STORAGE_UPDATE_STACK = 92,
    LIFTED_UI_BORDER_STORAGE_UPDATE_4501A0_STACK = 96,
    LIFTED_UI_BORDER_STORAGE_UPDATE_450200_STACK = 96,
    LIFTED_UI_BORDER_STORAGE_UPDATE_450270_STACK = 108,
    LIFTED_UI_BORDER_STORAGE_UPDATE_450300_STACK = 80,
    LIFTED_BLOCK_FINISH_EFFECT_UPDATE_STACK = 108,
    LIFTED_BLOCK_FINISH_EFFECT_UPDATE_4503B0_STACK = 124,
    LIFTED_BLOCK_FINISH_EFFECT_UPDATE_450450_STACK = 120,
    LIFTED_BLOCK_FINISH_EFFECT_UPDATE_4504E0_STACK = 104,
    LIFTED_BLOCK_FINISH_EFFECT_UPDATE_450550_STACK = 108
};

/* Original 0x430440. */
uint32_t lifted_board_rings(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430660. */
uint32_t lifted_board_burst(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430800. */
uint32_t lifted_block_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4320c0. */
uint32_t lifted_board_has_piece(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4328e0. */
uint32_t lifted_f4328e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432ba0. */
uint32_t lifted_board_swap_slots(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x433040. */
uint32_t lifted_board_burst_occupied(const VertrixCalls *calls,
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

/* Original 0x436100. */
uint32_t lifted_f436100(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x437240. */
uint32_t lifted_f437240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4372c0. */
uint32_t lifted_f4372c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4375a0. */
uint32_t lifted_board_mark_filled(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x437b70. */
uint32_t lifted_board_stamp_companions(const VertrixCalls *calls,
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

/* Original 0x438d50. */
uint32_t lifted_board_any_block(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438dd0. */
uint32_t lifted_f438dd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438ef0. */
uint32_t lifted_f438ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x439140. */
uint32_t lifted_f439140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x439190. */
uint32_t lifted_board_destroy_marked(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x439370. */
uint32_t lifted_f439370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x439510. */
uint32_t lifted_f439510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4398c0. */
uint32_t lifted_board_clear_marked_extra(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a080. */
uint32_t lifted_block_construct_kind_one(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

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
uint32_t lifted_piece_store_preview_kinds(const VertrixCalls *calls,
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
uint32_t lifted_player_set_e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b870. */
uint32_t lifted_player_e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b930. */
uint32_t lifted_player_alloc_side(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b970. */
uint32_t lifted_player_flag_4e8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b980. */
uint32_t lifted_player_release_side(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b9c0. */
uint32_t lifted_player_match_reward(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ba70. */
uint32_t lifted_player_bonus_meter_full(const VertrixCalls *calls,
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
uint32_t lifted_player_set_cd(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bae0. */
uint32_t lifted_player_set_cc(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_player_byte_4c4_is_one(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bd60. */
uint32_t lifted_player_partner_free(const VertrixCalls *calls,
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
uint32_t lifted_player_partner_not_cc_one(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

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
uint32_t lifted_player_enter_state(const VertrixCalls *calls,
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

/* Original 0x43d800. */
uint32_t lifted_effects_release_all_full(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43dc80. */
uint32_t lifted_particle_emit(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43dea0. */
uint32_t lifted_spawn_spread(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43dff0. */
uint32_t lifted_object_populate(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e100. */
uint32_t lifted_board_particles_reset(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e260. */
uint32_t lifted_arena_release_all_full(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e4d0. */
uint32_t lifted_board_particles_setup(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e740. */
uint32_t lifted_particle_init_drift(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e840. */
uint32_t lifted_particle_init_fall(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e920. */
uint32_t lifted_spawn_place(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f3f0. */
uint32_t lifted_release_table_a(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f420. */
uint32_t lifted_font_glyph(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f460. */
uint32_t lifted_glyph_present(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f480. */
uint32_t lifted_f43f480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f550. */
uint32_t lifted_key_binding_apply(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f630. */
uint32_t lifted_f43f630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f710. */
uint32_t lifted_f43f710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f7f0. */
uint32_t lifted_f43f7f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f8d0. */
uint32_t lifted_f43f8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f9b0. */
uint32_t lifted_f43f9b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43fa90. */
uint32_t lifted_f43fa90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43fb70. */
uint32_t lifted_f43fb70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43fc50. */
uint32_t lifted_font_maps_initialize(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x440490. */
uint32_t lifted_f440490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x440a20. */
uint32_t lifted_f440a20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x440d50. */
uint32_t lifted_f440d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441120. */
uint32_t lifted_forward_4ea190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4413b0. */
uint32_t lifted_chain_object_construct(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441530. */
uint32_t lifted_record_init(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441a80. */
uint32_t lifted_record_release_full(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441b30. */
uint32_t lifted_record_draw(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x442110. */
uint32_t lifted_release_table_b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4429a0. */
uint32_t lifted_f4429a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x442b00. */
uint32_t lifted_text_width(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443260. */
uint32_t lifted_f443260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443320. */
uint32_t lifted_f443320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4433c0. */
uint32_t lifted_f4433c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443460. */
uint32_t lifted_f443460(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x444a30. */
uint32_t lifted_f444a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445090. */
uint32_t lifted_f445090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445130. */
uint32_t lifted_f445130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445630. */
uint32_t lifted_f445630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4456d0. */
uint32_t lifted_f4456d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445890. */
uint32_t lifted_f445890(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x445d10. */
uint32_t lifted_f445d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445e90. */
uint32_t lifted_f445e90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446730. */
uint32_t lifted_f446730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4467c0. */
uint32_t lifted_f4467c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x446d70. */
uint32_t lifted_f446d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446ec0. */
uint32_t lifted_f446ec0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x447e80. */
uint32_t lifted_f447e80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447f40. */
uint32_t lifted_f447f40(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4486f0. */
uint32_t lifted_f4486f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448740. */
uint32_t lifted_f448740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448790. */
uint32_t lifted_f448790(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_actor_frame_decay(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449390. */
uint32_t lifted_actor_frame_switch(const VertrixCalls *calls,
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

/* Original 0x449a50. */
uint32_t lifted_f449a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449b50. */
uint32_t lifted_f449b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449e10. */
uint32_t lifted_f449e10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449ff0. */
uint32_t lifted_f449ff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44a340. */
uint32_t lifted_f44a340(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x44c2b0. */
uint32_t lifted_piece_child_update_44c2b0(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c310. */
uint32_t lifted_piece_child_update_44c310(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c370. */
uint32_t lifted_piece_child_update_44c370(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c3d0. */
uint32_t lifted_f44c3d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c3e0. */
uint32_t lifted_f44c3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c450. */
uint32_t lifted_f44c450(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c4c0. */
uint32_t lifted_f44c4c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c530. */
uint32_t lifted_f44c530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c5a0. */
uint32_t lifted_f44c5a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c610. */
uint32_t lifted_f44c610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c680. */
uint32_t lifted_f44c680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c6e0. */
uint32_t lifted_f44c6e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c780. */
uint32_t lifted_f44c780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c7f0. */
uint32_t lifted_f44c7f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c860. */
uint32_t lifted_block_update(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c880. */
uint32_t lifted_block_motion_update(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c8e0. */
uint32_t lifted_f44c8e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c940. */
uint32_t lifted_f44c940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c960. */
uint32_t lifted_block_fade_update(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c9d0. */
uint32_t lifted_block_pulse_update(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ca40. */
uint32_t lifted_f44ca40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44cab0. */
uint32_t lifted_f44cab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44cb50. */
uint32_t lifted_f44cb50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44cbf0. */
uint32_t lifted_block_byte_pulse_update(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44cc60. */
uint32_t lifted_block_byte_pulse_update_44cc60(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x44ce80. */
uint32_t lifted_block_scale_update(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44cf00. */
uint32_t lifted_block_return_update(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44cf70. */
uint32_t lifted_f44cf70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44cfd0. */
uint32_t lifted_f44cfd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d1e0. */
uint32_t lifted_f44d1e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d250. */
uint32_t lifted_f44d250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d2c0. */
uint32_t lifted_f44d2c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d330. */
uint32_t lifted_f44d330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d3a0. */
uint32_t lifted_f44d3a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d410. */
uint32_t lifted_block_byte_pulse_update_44d410(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x44d480. */
uint32_t lifted_f44d480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d4f0. */
uint32_t lifted_f44d4f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d560. */
uint32_t lifted_f44d560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d5f0. */
uint32_t lifted_f44d5f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d660. */
uint32_t lifted_f44d660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d6d0. */
uint32_t lifted_f44d6d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d760. */
uint32_t lifted_block_byte_pulse_update_44d760(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x44d7d0. */
uint32_t lifted_f44d7d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d840. */
uint32_t lifted_f44d840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d8b0. */
uint32_t lifted_block_mode_pulse_update(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d940. */
uint32_t lifted_f44d940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d9d0. */
uint32_t lifted_f44d9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44da70. */
uint32_t lifted_block_half_pulse_update(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44db10. */
uint32_t lifted_f44db10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44dbb0. */
uint32_t lifted_f44dbb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44dc80. */
uint32_t lifted_f44dc80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44dcf0. */
uint32_t lifted_f44dcf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e250. */
uint32_t lifted_block_slide_update(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e2d0. */
uint32_t lifted_f44e2d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e380. */
uint32_t lifted_block_collapse_update(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e410. */
uint32_t lifted_f44e410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e4a0. */
uint32_t lifted_block_visibility_update(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e510. */
uint32_t lifted_f44e510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e590. */
uint32_t lifted_block_swell_update(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e600. */
uint32_t lifted_f44e600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e670. */
uint32_t lifted_f44e670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e6e0. */
uint32_t lifted_block_accelerate_update(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e790. */
uint32_t lifted_block_mode_amount_update(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e800. */
uint32_t lifted_f44e800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e890. */
uint32_t lifted_block_period_update(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ebe0. */
uint32_t lifted_block_travel_update(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ec40. */
uint32_t lifted_f44ec40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f040. */
uint32_t lifted_f44f040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f0b0. */
uint32_t lifted_f44f0b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f120. */
uint32_t lifted_block_effect_update(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f180. */
uint32_t lifted_block_effect_update_44f180(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f1e0. */
uint32_t lifted_block_effect_update_44f1e0(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f240. */
uint32_t lifted_block_effect_update_44f240(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f2b0. */
uint32_t lifted_block_effect_update_44f2b0(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f320. */
uint32_t lifted_block_effect_update_44f320(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f390. */
uint32_t lifted_block_cycle_update(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f3e0. */
uint32_t lifted_f44f3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f430. */
uint32_t lifted_f44f430(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f4a0. */
uint32_t lifted_block_effect_update_44f4a0(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f500. */
uint32_t lifted_block_effect_update_44f500(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f560. */
uint32_t lifted_block_effect_update_44f560(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f5d0. */
uint32_t lifted_block_effect_update_44f5d0(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f630. */
uint32_t lifted_block_effect_update_44f630(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f690. */
uint32_t lifted_block_effect_update_44f690(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f700. */
uint32_t lifted_f44f700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f770. */
uint32_t lifted_f44f770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f7e0. */
uint32_t lifted_f44f7e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f880. */
uint32_t lifted_f44f880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f920. */
uint32_t lifted_f44f920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f990. */
uint32_t lifted_f44f990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fa00. */
uint32_t lifted_f44fa00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fa70. */
uint32_t lifted_number_player_update(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44faa0. */
uint32_t lifted_f44faa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fad0. */
uint32_t lifted_number_transition_update(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fb40. */
uint32_t lifted_number_transition_update_44fb40(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x44fbb0. */
uint32_t lifted_number_transition_update_44fbb0(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x44fc00. */
uint32_t lifted_f44fc00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fc30. */
uint32_t lifted_f44fc30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fc60. */
uint32_t lifted_number_transition_configured(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fcf0. */
uint32_t lifted_number_transition_configured_44fcf0(const VertrixCalls *calls,
                                                    const VertrixFactoryServices *services,
                                                    const VertrixGlobals *globals,
                                                    const LiftEntry *entry);

/* Original 0x44fd60. */
uint32_t lifted_number_transition_configured_44fd60(const VertrixCalls *calls,
                                                    const VertrixFactoryServices *services,
                                                    const VertrixGlobals *globals,
                                                    const LiftEntry *entry);

/* Original 0x44fdb0. */
uint32_t lifted_number_transition_configured_44fdb0(const VertrixCalls *calls,
                                                    const VertrixFactoryServices *services,
                                                    const VertrixGlobals *globals,
                                                    const LiftEntry *entry);

/* Original 0x44fe30. */
uint32_t lifted_number_transition_configured_44fe30(const VertrixCalls *calls,
                                                    const VertrixFactoryServices *services,
                                                    const VertrixGlobals *globals,
                                                    const LiftEntry *entry);

/* Original 0x44fe80. */
uint32_t lifted_player_indicator_update(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fed0. */
uint32_t lifted_player_indicator_update_44fed0(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x44ff30. */
uint32_t lifted_player_indicator_update_44ff30(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x44ff60. */
uint32_t lifted_player_indicator_update_44ff60(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x44ff90. */
uint32_t lifted_ui_indicator_storage_update(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fff0. */
uint32_t lifted_ui_indicator_storage_update_44fff0(const VertrixCalls *calls,
                                                   const VertrixFactoryServices *services,
                                                   const VertrixGlobals *globals,
                                                   const LiftEntry *entry);

/* Original 0x450040. */
uint32_t lifted_ui_indicator_storage_update_450040(const VertrixCalls *calls,
                                                   const VertrixFactoryServices *services,
                                                   const VertrixGlobals *globals,
                                                   const LiftEntry *entry);

/* Original 0x4500b0. */
uint32_t lifted_ui_indicator_storage_update_4500b0(const VertrixCalls *calls,
                                                   const VertrixFactoryServices *services,
                                                   const VertrixGlobals *globals,
                                                   const LiftEntry *entry);

/* Original 0x450100. */
uint32_t lifted_ui_indicator_storage_update_450100(const VertrixCalls *calls,
                                                   const VertrixFactoryServices *services,
                                                   const VertrixGlobals *globals,
                                                   const LiftEntry *entry);

/* Original 0x450130. */
uint32_t lifted_ui_border_storage_update(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4501a0. */
uint32_t lifted_ui_border_storage_update_4501a0(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x450200. */
uint32_t lifted_ui_border_storage_update_450200(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x450270. */
uint32_t lifted_ui_border_storage_update_450270(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x450300. */
uint32_t lifted_ui_border_storage_update_450300(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x450330. */
uint32_t lifted_block_finish_effect_update(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4503b0. */
uint32_t lifted_block_finish_effect_update_4503b0(const VertrixCalls *calls,
                                                  const VertrixFactoryServices *services,
                                                  const VertrixGlobals *globals,
                                                  const LiftEntry *entry);

/* Original 0x450450. */
uint32_t lifted_block_finish_effect_update_450450(const VertrixCalls *calls,
                                                  const VertrixFactoryServices *services,
                                                  const VertrixGlobals *globals,
                                                  const LiftEntry *entry);

/* Original 0x4504e0. */
uint32_t lifted_block_finish_effect_update_4504e0(const VertrixCalls *calls,
                                                  const VertrixFactoryServices *services,
                                                  const VertrixGlobals *globals,
                                                  const LiftEntry *entry);

/* Original 0x450550. */
uint32_t lifted_block_finish_effect_update_450550(const VertrixCalls *calls,
                                                  const VertrixFactoryServices *services,
                                                  const VertrixGlobals *globals,
                                                  const LiftEntry *entry);
#endif
