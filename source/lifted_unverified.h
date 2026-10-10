#ifndef VERTRIX_LIFTED_UNVERIFIED_H
#define VERTRIX_LIFTED_UNVERIFIED_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_RETURN_UNCHANGED_STACK = 64,
    LIFTED_BITS_HEADER_STACK = 176,
    LIFTED_BITS_FILL_STACK = 128,
    LIFTED_WINDOW_TABLES_STACK = 208,
    LIFTED_F40C320_STACK = 88,
    LIFTED_FILE_READ_WORD_SWAPPED_STACK = 88,
    LIFTED_MIXER_CHANNEL_STACK = 116,
    LIFTED_MIXER_PITCH_STACK = 80,
    LIFTED_MIXER_VOLUME_COLUMN_STACK = 92,
    LIFTED_MIXER_PLAYBACK_TICK_STACK = 88,
    LIFTED_MIXER_NOTE_RELEASE_STACK = 68,
    LIFTED_MIXER_ROW_STACK = 92,
    LIFTED_MIXER_PUBLISH_STACK = 104,
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
    LIFTED_OBJECT_INVOKE_CALLBACK_STACK = 72,
    LIFTED_F4189F0_STACK = 76,
    LIFTED_F418A10_STACK = 136,
    LIFTED_GUARDED_CALL_4194B0_STACK = 68,
    LIFTED_F41B310_STACK = 1060,
    LIFTED_F41C410_STACK = 572,
    LIFTED_F41CC30_STACK = 704,
    LIFTED_F41E780_STACK = 548,
    LIFTED_F41F9B0_STACK = 476,
    LIFTED_F41FE10_STACK = 496,
    LIFTED_F4212A0_STACK = 508,
    LIFTED_F423960_STACK = 308,
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
    LIFTED_F43E2A0_STACK = 100,
    LIFTED_F43E320_STACK = 128,
    LIFTED_F43EAB0_STACK = 384,
    LIFTED_F441450_STACK = 164,
    LIFTED_TEXT_WIDTH_STACK = 76,
    LIFTED_F44B810_STACK = 224,
    LIFTED_OBJECT_START_HOLD_STACK = 84,
    LIFTED_F452520_STACK = 192,
    LIFTED_STATE_PAIR_453050_STACK = 144,
    LIFTED_F45D4D0_STACK = 160,
    LIFTED_RESOURCE_ONE_FRAME_45E720_STACK = 72,
    LIFTED_TABLE_FILL_SLOT_STACK = 136,
    LIFTED_RESOURCE_PAIRED_FINISH_STACK = 212,
    LIFTED_UI_PANELS_SLOT2_FULL_STACK = 92,
    LIFTED_F461610_STACK = 240,
    LIFTED_F461790_STACK = 252,
    LIFTED_OPTIONS_BUILD_STACK = 1132,
    LIFTED_LETTER_ROW_STACK = 236,
    LIFTED_LETTER_ROW_SECOND_STACK = 236,
    LIFTED_PANEL_SPAWN_STACK = 168,
    LIFTED_SLIDE_PAIR_STACK = 228,
    LIFTED_DELAY_ACTOR_SPAWN_STACK = 128,
    LIFTED_RETURN_UNCHANGED_4713C0_STACK = 64,
    LIFTED_UI_SLIDE_FROM_BELOW_STACK = 68,
    LIFTED_F471AB0_STACK = 72,
    LIFTED_F471AD0_STACK = 72,
    LIFTED_F471AE0_STACK = 72,
    LIFTED_F471AF0_STACK = 68,
    LIFTED_F471B30_STACK = 72,
    LIFTED_F471B50_STACK = 72,
    LIFTED_F471B60_STACK = 72,
    LIFTED_F471B70_STACK = 68,
    LIFTED_ACTOR_LIST_ALL_IDLE_STACK = 80,
    LIFTED_ACTOR_LIST_ALL_IDLE_471D50_STACK = 80,
    LIFTED_F471D90_STACK = 80,
    LIFTED_F471DD0_STACK = 80,
    LIFTED_SCENE_LOOKUP_PAIR_STACK = 92,
    LIFTED_OBJECT_FLIP_454_STACK = 72,
    LIFTED_OBJECT_FLIP_454_471E80_STACK = 72,
    LIFTED_OBJECT_GET_464_STACK = 64,
    LIFTED_OBJECT_GET_174_STACK = 64,
    LIFTED_OBJECT_GET_178_STACK = 64,
    LIFTED_RETURN_UNCHANGED_471EE0_STACK = 64,
    LIFTED_POINT_LIST_WHEN_ONE_STACK = 68,
    LIFTED_PAIR_FLAGS_STACK = 144,
    LIFTED_PAIR_FLAGS_473960_STACK = 144,
    LIFTED_PAIR_SCAN_STACK = 144,
    LIFTED_PALETTE_TABLES_BUILD_STACK = 540,
    LIFTED_F475660_STACK = 120,
    LIFTED_LIST_RESET_CALLS_STACK = 96,
    LIFTED_LIST_PUSH_CALL_STACK = 80,
    LIFTED_OFFSET_CALL_STACK = 68,
    LIFTED_SLOT_TABLE_RESET_STACK = 76,
    LIFTED_F476AA0_STACK = 380,
    LIFTED_F477390_STACK = 224,
    LIFTED_RETURN_UNCHANGED_477930_STACK = 64,
    LIFTED_F477B10_STACK = 236,
    LIFTED_SURFACE_WRITE_STACK = 72,
    LIFTED_SURFACE_BOUNDS_STACK = 124,
    LIFTED_F47E890_STACK = 188,
    LIFTED_OBJECT_DWORD_480070_STACK = 64,
    LIFTED_RENDER_WEIGHTS_BUILD_STACK = 124,
    LIFTED_PALETTE_CUBE_STACK = 112,
    LIFTED_RLE_ENCODED_LENGTH_STACK = 76,
    LIFTED_F482550_STACK = 128,
    LIFTED_SCRATCH_PAIR_CALL_STACK = 88,
    LIFTED_F484520_STACK = 68,
    LIFTED_F484B60_STACK = 752,
    LIFTED_F486E20_STACK = 140,
    LIFTED_ARRAY_LIST_BUILD_STACK = 128,
    LIFTED_F488C50_STACK = 192,
    LIFTED_FIND_SIZE_FIELD_STACK = 372,
    LIFTED_F48AC10_STACK = 288,
    LIFTED_OBJECT_NOTIFY_FIELD_STACK = 76,
    LIFTED_OBJECT_NOTIFY_GLOBAL_STACK = 76,
    LIFTED_OBJECT_NOTIFY_FIELD_48C330_STACK = 76,
    LIFTED_COPY_DWORD_FULL_STACK = 64,
    LIFTED_OBJECT_CLEAR_WITH_ONES_STACK = 72,
    LIFTED_F48D720_STACK = 68,
    LIFTED_RENDER_PALETTE_PIXEL_LAYOUT_STACK = 72,
    LIFTED_RENDER_PALETTE_PIXEL_LAYOUT_48D7F0_STACK = 72,
    LIFTED_F48D890_STACK = 68,
    LIFTED_F48D8C0_STACK = 76,
    LIFTED_F48D9A0_STACK = 76,
    LIFTED_F48DA80_STACK = 76,
    LIFTED_F48DB70_STACK = 72,
    LIFTED_RENDER_PALETTE_HALF_PIXEL_STACK = 80,
    LIFTED_F48DCD0_STACK = 72,
    LIFTED_F48DD00_STACK = 76,
    LIFTED_F48DD50_STACK = 72,
    LIFTED_F48DDA0_STACK = 72,
    LIFTED_F48DDF0_STACK = 68,
    LIFTED_F48DE10_STACK = 68,
    LIFTED_F48DE30_STACK = 76,
    LIFTED_F48DF10_STACK = 80,
    LIFTED_F48DFF0_STACK = 76,
    LIFTED_F48E0C0_STACK = 72,
    LIFTED_F48E190_STACK = 76,
    LIFTED_F48E280_STACK = 72,
    LIFTED_F48E370_STACK = 72,
    LIFTED_F48E460_STACK = 72,
    LIFTED_F48E520_STACK = 80,
    LIFTED_F48E5F0_STACK = 80,
    LIFTED_F48E6C0_STACK = 72,
    LIFTED_F48E700_STACK = 84,
    LIFTED_F48E850_STACK = 72,
    LIFTED_F48E900_STACK = 76,
    LIFTED_F48E9D0_STACK = 76,
    LIFTED_F48EA30_STACK = 80,
    LIFTED_F48EB40_STACK = 72,
    LIFTED_F48EC10_STACK = 72,
    LIFTED_F48EC70_STACK = 76,
    LIFTED_F48ED80_STACK = 72,
    LIFTED_F48EE50_STACK = 72,
    LIFTED_F48EEB0_STACK = 76,
    LIFTED_F48EFC0_STACK = 72,
    LIFTED_F48F070_STACK = 68,
    LIFTED_F48F0A0_STACK = 76,
    LIFTED_F48F190_STACK = 76,
    LIFTED_F48F230_STACK = 72,
    LIFTED_F48F260_STACK = 84,
    LIFTED_F48F360_STACK = 76,
    LIFTED_F48F430_STACK = 76,
    LIFTED_F48F520_STACK = 80,
    LIFTED_F48F620_STACK = 80,
    LIFTED_F48F6F0_STACK = 84,
    LIFTED_F48F800_STACK = 80,
    LIFTED_F48F910_STACK = 76,
    LIFTED_F48F9F0_STACK = 80,
    LIFTED_F48FAF0_STACK = 76,
    LIFTED_F48FBE0_STACK = 76,
    LIFTED_F48FCD0_STACK = 76,
    LIFTED_F48FDB0_STACK = 84,
    LIFTED_F48FE90_STACK = 92,
    LIFTED_F490010_STACK = 92,
    LIFTED_F4901A0_STACK = 76,
    LIFTED_F4902A0_STACK = 92,
    LIFTED_RENDER_PALETTE_WEIGHTED_PIXEL_STACK = 92,
    LIFTED_F4904C0_STACK = 92,
    LIFTED_F490560_STACK = 88,
    LIFTED_F4906A0_STACK = 84,
    LIFTED_F4907D0_STACK = 80,
    LIFTED_F4908C0_STACK = 92,
    LIFTED_F490980_STACK = 96,
    LIFTED_F490B30_STACK = 88,
    LIFTED_F490C60_STACK = 92,
    LIFTED_F490DC0_STACK = 76,
    LIFTED_F490E90_STACK = 72,
    LIFTED_F490F60_STACK = 80,
    LIFTED_F491050_STACK = 80,
    LIFTED_F4911D0_STACK = 80,
    LIFTED_F4912E0_STACK = 88,
    LIFTED_F4913E0_STACK = 84,
    LIFTED_F491530_STACK = 76,
    LIFTED_F491620_STACK = 80,
    LIFTED_F491720_STACK = 76,
    LIFTED_F491820_STACK = 76,
    LIFTED_F491920_STACK = 76,
    LIFTED_F491A00_STACK = 84,
    LIFTED_F491AF0_STACK = 76,
    LIFTED_F491BE0_STACK = 76,
    LIFTED_F491CE0_STACK = 80,
    LIFTED_F491E10_STACK = 88,
    LIFTED_F491F70_STACK = 92,
    LIFTED_F492120_STACK = 84,
    LIFTED_RENDER_BINARY_ROW32_STACK = 76,
    LIFTED_F4922F0_STACK = 92,
    LIFTED_RENDER_ROW32_STACK = 80,
    LIFTED_F492460_STACK = 92,
    LIFTED_RENDER_SAMPLE_BINARY_ROW32_STACK = 80,
    LIFTED_F4925D0_STACK = 92,
    LIFTED_RENDER_SAMPLE_ROW32_STACK = 84,
    LIFTED_F492770_STACK = 92,
    LIFTED_RENDER_IMAGE32_STACK = 80,
    LIFTED_RENDER_SAMPLE32_STACK = 88,
    LIFTED_F492980_STACK = 88,
    LIFTED_F492A70_STACK = 88,
    LIFTED_RENDER_RECTANGLE_PALETTE32_STACK = 92,
    LIFTED_RENDER_RECTANGLE_FIXED_PALETTE32_STACK = 84,
    LIFTED_RENDER_RECTANGLE_HALF32_STACK = 84,
    LIFTED_RENDER_RECTANGLE_INDEX_HALF32_STACK = 88,
    LIFTED_RENDER_RECTANGLE_HALF_PALETTE32_STACK = 84,
    LIFTED_F4930C0_STACK = 100,
    LIFTED_F4933E0_STACK = 72,
    LIFTED_F493420_STACK = 72,
    LIFTED_F493500_STACK = 72,
    LIFTED_F4935C0_STACK = 72,
    LIFTED_F493610_STACK = 76,
    LIFTED_F493720_STACK = 72,
    LIFTED_F493810_STACK = 80,
    LIFTED_F493970_STACK = 76,
    LIFTED_F493A00_STACK = 84,
    LIFTED_F493BA0_STACK = 76,
    LIFTED_F493C30_STACK = 84,
    LIFTED_F493CF0_STACK = 84,
    LIFTED_F493DB0_STACK = 84,
    LIFTED_F493E70_STACK = 76,
    LIFTED_F493EC0_STACK = 80,
    LIFTED_F493F40_STACK = 80,
    LIFTED_F494080_STACK = 80,
    LIFTED_F4941D0_STACK = 76,
    LIFTED_F494310_STACK = 84,
    LIFTED_F494450_STACK = 84,
    LIFTED_F4945A0_STACK = 84,
    LIFTED_F4946F0_STACK = 84,
    LIFTED_F494840_STACK = 80,
    LIFTED_F494940_STACK = 84,
    LIFTED_F494A80_STACK = 84,
    LIFTED_F494BC0_STACK = 76,
    LIFTED_F494C60_STACK = 84,
    LIFTED_F494E10_STACK = 80,
    LIFTED_F494F30_STACK = 84,
    LIFTED_F495060_STACK = 84,
    LIFTED_F495130_STACK = 88,
    LIFTED_F4952C0_STACK = 84,
    LIFTED_F4953F0_STACK = 84,
    LIFTED_F4954C0_STACK = 88,
    LIFTED_F495650_STACK = 84,
    LIFTED_F495780_STACK = 84,
    LIFTED_F495850_STACK = 88,
    LIFTED_F4959E0_STACK = 76,
    LIFTED_F495AC0_STACK = 76,
    LIFTED_F495B20_STACK = 80,
    LIFTED_F495C40_STACK = 76,
    LIFTED_F495D50_STACK = 76,
    LIFTED_F495DF0_STACK = 80,
    LIFTED_F495F40_STACK = 80,
    LIFTED_F496080_STACK = 80,
    LIFTED_F4961E0_STACK = 80,
    LIFTED_F496350_STACK = 80,
    LIFTED_F496480_STACK = 80,
    LIFTED_F4965E0_STACK = 80,
    LIFTED_F496750_STACK = 76,
    LIFTED_F4968A0_STACK = 88,
    LIFTED_F496A10_STACK = 88,
    LIFTED_F496B70_STACK = 88,
    LIFTED_F496CD0_STACK = 84,
    LIFTED_F496DF0_STACK = 84,
    LIFTED_F496F40_STACK = 92,
    LIFTED_F497140_STACK = 92,
    LIFTED_F497340_STACK = 84,
    LIFTED_F4974C0_STACK = 88,
    LIFTED_F4975D0_STACK = 92,
    LIFTED_F4977C0_STACK = 88,
    LIFTED_F4978D0_STACK = 92,
    LIFTED_F497A90_STACK = 84,
    LIFTED_F497C50_STACK = 84,
    LIFTED_F497DA0_STACK = 96,
    LIFTED_F497EE0_STACK = 96,
    LIFTED_F4980F0_STACK = 84,
    LIFTED_F498280_STACK = 96,
    LIFTED_F498470_STACK = 76,
    LIFTED_F498570_STACK = 72,
    LIFTED_F498660_STACK = 80,
    LIFTED_F498770_STACK = 76,
    LIFTED_F498910_STACK = 84,
    LIFTED_F498A80_STACK = 88,
    LIFTED_F498BF0_STACK = 84,
    LIFTED_F498DB0_STACK = 88,
    LIFTED_F498F20_STACK = 84,
    LIFTED_F499090_STACK = 84,
    LIFTED_F4991F0_STACK = 84,
    LIFTED_F499350_STACK = 80,
    LIFTED_F499460_STACK = 84,
    LIFTED_F4995A0_STACK = 80,
    LIFTED_F499700_STACK = 76,
    LIFTED_F499860_STACK = 88,
    LIFTED_F4999F0_STACK = 92,
    LIFTED_F499BC0_STACK = 92,
    LIFTED_F499DD0_STACK = 84,
    LIFTED_F499FB0_STACK = 76,
    LIFTED_F49A020_STACK = 92,
    LIFTED_F49A120_STACK = 80,
    LIFTED_F49A180_STACK = 92,
    LIFTED_F49A270_STACK = 80,
    LIFTED_F49A2F0_STACK = 92,
    LIFTED_F49A420_STACK = 84,
    LIFTED_F49A480_STACK = 92,
    LIFTED_F49A590_STACK = 80,
    LIFTED_F49A600_STACK = 88,
    LIFTED_F49A690_STACK = 88,
    LIFTED_F49A780_STACK = 88,
    LIFTED_F49A8A0_STACK = 92,
    LIFTED_F49AA40_STACK = 84,
    LIFTED_F49ABB0_STACK = 84,
    LIFTED_F49ACA0_STACK = 84,
    LIFTED_F49AE50_STACK = 88,
    LIFTED_F49B000_STACK = 112,
    LIFTED_F49B4A0_STACK = 72,
    LIFTED_F49B4E0_STACK = 72,
    LIFTED_F49B5C0_STACK = 72,
    LIFTED_F49B680_STACK = 72,
    LIFTED_F49B6D0_STACK = 76,
    LIFTED_F49B7E0_STACK = 72,
    LIFTED_F49B8D0_STACK = 80,
    LIFTED_F49BA30_STACK = 76,
    LIFTED_F49BAC0_STACK = 84,
    LIFTED_F49BC60_STACK = 76,
    LIFTED_F49BCF0_STACK = 84,
    LIFTED_F49BDB0_STACK = 84,
    LIFTED_F49BE70_STACK = 84,
    LIFTED_F49BF30_STACK = 76,
    LIFTED_F49BF80_STACK = 80,
    LIFTED_F49C000_STACK = 80,
    LIFTED_F49C140_STACK = 80,
    LIFTED_F49C290_STACK = 76,
    LIFTED_F49C3D0_STACK = 84,
    LIFTED_F49C510_STACK = 84,
    LIFTED_F49C660_STACK = 84,
    LIFTED_F49C7B0_STACK = 84,
    LIFTED_F49C900_STACK = 80,
    LIFTED_F49CA00_STACK = 84,
    LIFTED_F49CB40_STACK = 84,
    LIFTED_F49CC80_STACK = 76,
    LIFTED_F49CD20_STACK = 84,
    LIFTED_F49CED0_STACK = 80,
    LIFTED_F49CFF0_STACK = 84,
    LIFTED_F49D120_STACK = 84,
    LIFTED_F49D1F0_STACK = 88,
    LIFTED_F49D380_STACK = 84,
    LIFTED_F49D4B0_STACK = 84,
    LIFTED_F49D580_STACK = 88,
    LIFTED_F49D710_STACK = 84,
    LIFTED_F49D840_STACK = 84,
    LIFTED_F49D910_STACK = 88,
    LIFTED_F49DAA0_STACK = 76,
    LIFTED_F49DB80_STACK = 76,
    LIFTED_F49DBE0_STACK = 80,
    LIFTED_F49DD00_STACK = 76,
    LIFTED_F49DE10_STACK = 76,
    LIFTED_F49DEB0_STACK = 80,
    LIFTED_F49E000_STACK = 80,
    LIFTED_F49E140_STACK = 80,
    LIFTED_F49E2A0_STACK = 80,
    LIFTED_F49E410_STACK = 80,
    LIFTED_F49E540_STACK = 80,
    LIFTED_F49E6A0_STACK = 80,
    LIFTED_F49E810_STACK = 76,
    LIFTED_F49E960_STACK = 88,
    LIFTED_F49EAD0_STACK = 88,
    LIFTED_F49EC30_STACK = 88,
    LIFTED_F49ED90_STACK = 84,
    LIFTED_F49EEB0_STACK = 84,
    LIFTED_F49F000_STACK = 92,
    LIFTED_F49F200_STACK = 92,
    LIFTED_F49F400_STACK = 84,
    LIFTED_F49F580_STACK = 88,
    LIFTED_F49F690_STACK = 92,
    LIFTED_F49F880_STACK = 88,
    LIFTED_F49F990_STACK = 92,
    LIFTED_F49FB50_STACK = 84,
    LIFTED_F49FD10_STACK = 84,
    LIFTED_F49FE60_STACK = 96,
    LIFTED_F49FFA0_STACK = 96,
    LIFTED_F4A01B0_STACK = 84,
    LIFTED_F4A0340_STACK = 96,
    LIFTED_F4A0530_STACK = 76,
    LIFTED_F4A0630_STACK = 72,
    LIFTED_F4A0720_STACK = 80,
    LIFTED_F4A0830_STACK = 76,
    LIFTED_F4A09D0_STACK = 84,
    LIFTED_F4A0B40_STACK = 88,
    LIFTED_F4A0CB0_STACK = 84,
    LIFTED_F4A0E70_STACK = 88,
    LIFTED_F4A0FE0_STACK = 84,
    LIFTED_F4A1150_STACK = 84,
    LIFTED_F4A12B0_STACK = 84,
    LIFTED_F4A1410_STACK = 80,
    LIFTED_F4A1520_STACK = 84,
    LIFTED_F4A1660_STACK = 80,
    LIFTED_F4A17C0_STACK = 76,
    LIFTED_F4A1920_STACK = 88,
    LIFTED_F4A1AB0_STACK = 92,
    LIFTED_F4A1C80_STACK = 92,
    LIFTED_F4A1E90_STACK = 84,
    LIFTED_F4A2070_STACK = 76,
    LIFTED_F4A20E0_STACK = 92,
    LIFTED_F4A21E0_STACK = 80,
    LIFTED_F4A2240_STACK = 92,
    LIFTED_F4A2330_STACK = 80,
    LIFTED_F4A23B0_STACK = 92,
    LIFTED_F4A24E0_STACK = 84,
    LIFTED_F4A2540_STACK = 92,
    LIFTED_F4A2650_STACK = 80,
    LIFTED_F4A26C0_STACK = 88,
    LIFTED_F4A2750_STACK = 88,
    LIFTED_F4A2840_STACK = 88,
    LIFTED_F4A2960_STACK = 92,
    LIFTED_F4A2AF0_STACK = 88,
    LIFTED_F4A2C60_STACK = 84,
    LIFTED_F4A2D50_STACK = 88,
    LIFTED_F4A2EF0_STACK = 92,
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
    LIFTED_F4A9140_STACK = 80,
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
    LIFTED_F4A9F40_STACK = 92,
    LIFTED_F4AA030_STACK = 80,
    LIFTED_F4AA0B0_STACK = 92,
    LIFTED_F4AA1E0_STACK = 84,
    LIFTED_F4AA240_STACK = 92,
    LIFTED_F4AA350_STACK = 80,
    LIFTED_F4AA3C0_STACK = 88,
    LIFTED_F4AA450_STACK = 88,
    LIFTED_F4AA540_STACK = 88,
    LIFTED_F4AA660_STACK = 92,
    LIFTED_F4AA7F0_STACK = 88,
    LIFTED_F4AA950_STACK = 88,
    LIFTED_F4AAA40_STACK = 88,
    LIFTED_F4AABE0_STACK = 92,
    LIFTED_F4AAD90_STACK = 104,
    LIFTED_SURFACE_BINARY32_STACK = 92,
    LIFTED_F4AB310_STACK = 92,
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
    LIFTED_ACTOR_STORE_TIMES_TWELVE_4AC840_STACK = 68,
    LIFTED_ACTOR_DOUBLE_ORBIT_POINT_STACK = 100,
    LIFTED_ACTOR_SET_WORDS_3A_FULL_STACK = 64,
    LIFTED_F4ADF90_STACK = 68,
    LIFTED_F4AE0C0_STACK = 80,
    LIFTED_F4AE0F0_STACK = 72,
    LIFTED_ACTOR_CHAIN_PAINT_STACK = 76,
    LIFTED_ACTOR_IMAGE_BOUNDS_STACK = 96,
    LIFTED_F4B3380_STACK = 72,
    LIFTED_OBJECT_LIST_PRUNE_STACK = 100,
    LIFTED_F4B6240_STACK = 84,
    LIFTED_F4B68A0_STACK = 136,
    LIFTED_OBJECT_GLYPH_LAYOUT_STACK = 76,
    LIFTED_LIST_ITEM_4B6FA0_STACK = 68,
    LIFTED_F4B7610_STACK = 172,
    LIFTED_OBJECT_IS_IDLE_STACK = 96,
    LIFTED_EDX_TO_EAX_CALL_4C5BD0_STACK = 68,
    LIFTED_SCALED_ROUND_STACK = 64,
    LIFTED_F4CCF3B_STACK = 120,
    LIFTED_F4CD520_STACK = 92,
    LIFTED_F4CD8B0_STACK = 152,
    LIFTED_RTL_STRING_TAIL_STACK = 116,
    LIFTED_F4CE780_STACK = 108,
    LIFTED_RTL_CLASS_ADDRESS_STACK = 64,
    LIFTED_RTL_RANGE_TABLE_FIND_STACK = 68,
    LIFTED_MESSAGE_DISPATCH_STACK = 132,
    LIFTED_F4D77D0_STACK = 432,
    LIFTED_F4D7A10_STACK = 104,
    LIFTED_F4D7BB0_STACK = 100,
    LIFTED_RTL_SELECT_FLOAT_HELPERS_STACK = 68,
    LIFTED_F4D8AB0_STACK = 104,
    LIFTED_RTL_PROBE_CALL_STACK = 92,
    LIFTED_RTL_JUMP_CAPTURE_STACK = 72,
    LIFTED_F4DA3BA_STACK = 1400,
    LIFTED_F4DAAE8_STACK = 108,
    LIFTED_F4DAC40_STACK = 96,
    LIFTED_RTL_SIGN_OF_STACK = 64,
    LIFTED_FLOAT_SPLIT_STACK = 88,
    LIFTED_RTL_ABSOLUTE_DOUBLE_STACK = 64,
    LIFTED_FLOAT_EXP_STACK = 228,
    LIFTED_RTL_SCRATCH_TRIPLE_CALL_STACK = 96,
    LIFTED_RTL_FLAGS_CALL_STACK = 80,
    LIFTED_F4DBF80_STACK = 104,
    LIFTED_RTL_LOOKUP_CALL_STACK = 72,
    LIFTED_RTL_PAIR_CALL_STACK = 72,
    LIFTED_F4DDC40_STACK = 72,
    LIFTED_NODE_POOL_TAKE_QUAD_STACK = 92,
    LIFTED_F4DF320_STACK = 248,
    LIFTED_F4DFAC0_STACK = 92,
    LIFTED_F4DFB24_STACK = 168,
    LIFTED_F4E04EC_STACK = 64,
    LIFTED_F4E14DC_STACK = 72,
    LIFTED_RETURN_UNCHANGED_4E3697_STACK = 64,
    LIFTED_F4E509C_STACK = 92,
    LIFTED_F4E55D0_STACK = 64,
    LIFTED_F4E5B0C_STACK = 120,
    LIFTED_F4E6250_STACK = 156,
    LIFTED_F4E6B50_STACK = 76,
    LIFTED_F4E6BAC_STACK = 84,
    LIFTED_F4E6D16_STACK = 216,
    LIFTED_RETURN_ZERO_4E9D00_STACK = 64,
    LIFTED_RETURN_UNCHANGED_4EC8C0_STACK = 64
};

/* Original 0x404580. */
uint32_t lifted_return_unchanged(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x407280. */
uint32_t lifted_bits_header(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

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

/* Original 0x40c460. */
uint32_t lifted_mixer_channel(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ce20. */
uint32_t lifted_mixer_pitch(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x40e770. */
uint32_t lifted_mixer_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e8a0. */
uint32_t lifted_mixer_publish(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x418850. */
uint32_t lifted_object_invoke_callback(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4189f0. */
uint32_t lifted_f4189f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418a10. */
uint32_t lifted_f418a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4194b0. */
uint32_t lifted_guarded_call_4194b0(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
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

/* Original 0x41fe10. */
uint32_t lifted_f41fe10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4212a0. */
uint32_t lifted_f4212a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x423960. */
uint32_t lifted_f423960(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x43e2a0. */
uint32_t lifted_f43e2a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e320. */
uint32_t lifted_f43e320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43eab0. */
uint32_t lifted_f43eab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441450. */
uint32_t lifted_f441450(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x442b00. */
uint32_t lifted_text_width(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44b810. */
uint32_t lifted_f44b810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450f80. */
uint32_t lifted_object_start_hold(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452520. */
uint32_t lifted_f452520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453050. */
uint32_t lifted_state_pair_453050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d4d0. */
uint32_t lifted_f45d4d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e720. */
uint32_t lifted_resource_one_frame_45e720(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e750. */
uint32_t lifted_table_fill_slot(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f020. */
uint32_t lifted_resource_paired_finish(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45fab0. */
uint32_t lifted_ui_panels_slot2_full(const VertrixCalls *calls,
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

/* Original 0x4713c0. */
uint32_t lifted_return_unchanged_4713c0(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4717f0. */
uint32_t lifted_ui_slide_from_below(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471ab0. */
uint32_t lifted_f471ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471ad0. */
uint32_t lifted_f471ad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471ae0. */
uint32_t lifted_f471ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471af0. */
uint32_t lifted_f471af0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b30. */
uint32_t lifted_f471b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b50. */
uint32_t lifted_f471b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b60. */
uint32_t lifted_f471b60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b70. */
uint32_t lifted_f471b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471c90. */
uint32_t lifted_actor_list_all_idle(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471d50. */
uint32_t lifted_actor_list_all_idle_471d50(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471d90. */
uint32_t lifted_f471d90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471dd0. */
uint32_t lifted_f471dd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x471ee0. */
uint32_t lifted_return_unchanged_471ee0(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
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

/* Original 0x475090. */
uint32_t lifted_palette_tables_build(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475660. */
uint32_t lifted_f475660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475a80. */
uint32_t lifted_list_reset_calls(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475ab0. */
uint32_t lifted_list_push_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475d90. */
uint32_t lifted_offset_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4766f0. */
uint32_t lifted_slot_table_reset(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476aa0. */
uint32_t lifted_f476aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477390. */
uint32_t lifted_f477390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477930. */
uint32_t lifted_return_unchanged_477930(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
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

/* Original 0x47e890. */
uint32_t lifted_f47e890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480070. */
uint32_t lifted_object_dword_480070(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480730. */
uint32_t lifted_render_weights_build(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480ca0. */
uint32_t lifted_palette_cube(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481420. */
uint32_t lifted_rle_encoded_length(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482550. */
uint32_t lifted_f482550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482610. */
uint32_t lifted_scratch_pair_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484520. */
uint32_t lifted_f484520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484b60. */
uint32_t lifted_f484b60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x486e20. */
uint32_t lifted_f486e20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4875a0. */
uint32_t lifted_array_list_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488c50. */
uint32_t lifted_f488c50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489610. */
uint32_t lifted_find_size_field(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48ac10. */
uint32_t lifted_f48ac10(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x48d720. */
uint32_t lifted_f48d720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d740. */
uint32_t lifted_render_palette_pixel_layout(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d7f0. */
uint32_t lifted_render_palette_pixel_layout_48d7f0(const VertrixCalls *calls,
                                                   const VertrixFactoryServices *services,
                                                   const VertrixGlobals *globals,
                                                   const LiftEntry *entry);

/* Original 0x48d890. */
uint32_t lifted_f48d890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d8c0. */
uint32_t lifted_f48d8c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d9a0. */
uint32_t lifted_f48d9a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48da80. */
uint32_t lifted_f48da80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48db70. */
uint32_t lifted_f48db70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48dba0. */
uint32_t lifted_render_palette_half_pixel(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48dcd0. */
uint32_t lifted_f48dcd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48dd00. */
uint32_t lifted_f48dd00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48dd50. */
uint32_t lifted_f48dd50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48dda0. */
uint32_t lifted_f48dda0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48ddf0. */
uint32_t lifted_f48ddf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48de10. */
uint32_t lifted_f48de10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48de30. */
uint32_t lifted_f48de30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48df10. */
uint32_t lifted_f48df10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48dff0. */
uint32_t lifted_f48dff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48e0c0. */
uint32_t lifted_f48e0c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48e190. */
uint32_t lifted_f48e190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48e280. */
uint32_t lifted_f48e280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48e370. */
uint32_t lifted_f48e370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48e460. */
uint32_t lifted_f48e460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48e520. */
uint32_t lifted_f48e520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48e5f0. */
uint32_t lifted_f48e5f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48e6c0. */
uint32_t lifted_f48e6c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48e700. */
uint32_t lifted_f48e700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48e850. */
uint32_t lifted_f48e850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48e900. */
uint32_t lifted_f48e900(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48e9d0. */
uint32_t lifted_f48e9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48ea30. */
uint32_t lifted_f48ea30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48eb40. */
uint32_t lifted_f48eb40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48ec10. */
uint32_t lifted_f48ec10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48ec70. */
uint32_t lifted_f48ec70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48ed80. */
uint32_t lifted_f48ed80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48ee50. */
uint32_t lifted_f48ee50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48eeb0. */
uint32_t lifted_f48eeb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48efc0. */
uint32_t lifted_f48efc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48f070. */
uint32_t lifted_f48f070(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48f0a0. */
uint32_t lifted_f48f0a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48f190. */
uint32_t lifted_f48f190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48f230. */
uint32_t lifted_f48f230(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48f260. */
uint32_t lifted_f48f260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48f360. */
uint32_t lifted_f48f360(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48f430. */
uint32_t lifted_f48f430(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48f520. */
uint32_t lifted_f48f520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48f620. */
uint32_t lifted_f48f620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48f6f0. */
uint32_t lifted_f48f6f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48f800. */
uint32_t lifted_f48f800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48f910. */
uint32_t lifted_f48f910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48f9f0. */
uint32_t lifted_f48f9f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48faf0. */
uint32_t lifted_f48faf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48fbe0. */
uint32_t lifted_f48fbe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48fcd0. */
uint32_t lifted_f48fcd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48fdb0. */
uint32_t lifted_f48fdb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48fe90. */
uint32_t lifted_f48fe90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x490010. */
uint32_t lifted_f490010(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4901a0. */
uint32_t lifted_f4901a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4902a0. */
uint32_t lifted_f4902a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x490340. */
uint32_t lifted_render_palette_weighted_pixel(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x4904c0. */
uint32_t lifted_f4904c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x490560. */
uint32_t lifted_f490560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4906a0. */
uint32_t lifted_f4906a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4907d0. */
uint32_t lifted_f4907d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4908c0. */
uint32_t lifted_f4908c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x490980. */
uint32_t lifted_f490980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x490b30. */
uint32_t lifted_f490b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x490c60. */
uint32_t lifted_f490c60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x490dc0. */
uint32_t lifted_f490dc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x490e90. */
uint32_t lifted_f490e90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x490f60. */
uint32_t lifted_f490f60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x491050. */
uint32_t lifted_f491050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4911d0. */
uint32_t lifted_f4911d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4912e0. */
uint32_t lifted_f4912e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4913e0. */
uint32_t lifted_f4913e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x491530. */
uint32_t lifted_f491530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x491620. */
uint32_t lifted_f491620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x491720. */
uint32_t lifted_f491720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x491820. */
uint32_t lifted_f491820(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x491920. */
uint32_t lifted_f491920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x491a00. */
uint32_t lifted_f491a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x491af0. */
uint32_t lifted_f491af0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x491be0. */
uint32_t lifted_f491be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x491ce0. */
uint32_t lifted_f491ce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x491e10. */
uint32_t lifted_f491e10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x491f70. */
uint32_t lifted_f491f70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x492120. */
uint32_t lifted_f492120(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x492280. */
uint32_t lifted_render_binary_row32(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4922f0. */
uint32_t lifted_f4922f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x492400. */
uint32_t lifted_render_row32(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x492460. */
uint32_t lifted_f492460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x492550. */
uint32_t lifted_render_sample_binary_row32(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4925d0. */
uint32_t lifted_f4925d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x492710. */
uint32_t lifted_render_sample_row32(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x492770. */
uint32_t lifted_f492770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x492880. */
uint32_t lifted_render_image32(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4928f0. */
uint32_t lifted_render_sample32(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x492980. */
uint32_t lifted_f492980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x492a70. */
uint32_t lifted_f492a70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x492b90. */
uint32_t lifted_render_rectangle_palette32(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x492cc0. */
uint32_t lifted_render_rectangle_fixed_palette32(const VertrixCalls *calls,
                                                 const VertrixFactoryServices *services,
                                                 const VertrixGlobals *globals,
                                                 const LiftEntry *entry);

/* Original 0x492dc0. */
uint32_t lifted_render_rectangle_half32(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x492e40. */
uint32_t lifted_render_rectangle_index_half32(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x492f90. */
uint32_t lifted_render_rectangle_half_palette32(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x4930c0. */
uint32_t lifted_f4930c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4933e0. */
uint32_t lifted_f4933e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x493420. */
uint32_t lifted_f493420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x493500. */
uint32_t lifted_f493500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4935c0. */
uint32_t lifted_f4935c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x493610. */
uint32_t lifted_f493610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x493720. */
uint32_t lifted_f493720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x493810. */
uint32_t lifted_f493810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x493970. */
uint32_t lifted_f493970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x493a00. */
uint32_t lifted_f493a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x493ba0. */
uint32_t lifted_f493ba0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x493c30. */
uint32_t lifted_f493c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x493cf0. */
uint32_t lifted_f493cf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x493db0. */
uint32_t lifted_f493db0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x493e70. */
uint32_t lifted_f493e70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x493ec0. */
uint32_t lifted_f493ec0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x493f40. */
uint32_t lifted_f493f40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x494080. */
uint32_t lifted_f494080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4941d0. */
uint32_t lifted_f4941d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x494310. */
uint32_t lifted_f494310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x494450. */
uint32_t lifted_f494450(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4945a0. */
uint32_t lifted_f4945a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4946f0. */
uint32_t lifted_f4946f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x494840. */
uint32_t lifted_f494840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x494940. */
uint32_t lifted_f494940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x494a80. */
uint32_t lifted_f494a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x494bc0. */
uint32_t lifted_f494bc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x494c60. */
uint32_t lifted_f494c60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x494e10. */
uint32_t lifted_f494e10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x494f30. */
uint32_t lifted_f494f30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x495060. */
uint32_t lifted_f495060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x495130. */
uint32_t lifted_f495130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4952c0. */
uint32_t lifted_f4952c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4953f0. */
uint32_t lifted_f4953f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4954c0. */
uint32_t lifted_f4954c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x495650. */
uint32_t lifted_f495650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x495780. */
uint32_t lifted_f495780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x495850. */
uint32_t lifted_f495850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4959e0. */
uint32_t lifted_f4959e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x495ac0. */
uint32_t lifted_f495ac0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x495b20. */
uint32_t lifted_f495b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x495c40. */
uint32_t lifted_f495c40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x495d50. */
uint32_t lifted_f495d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x495df0. */
uint32_t lifted_f495df0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x495f40. */
uint32_t lifted_f495f40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x496080. */
uint32_t lifted_f496080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4961e0. */
uint32_t lifted_f4961e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x496350. */
uint32_t lifted_f496350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x496480. */
uint32_t lifted_f496480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4965e0. */
uint32_t lifted_f4965e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x496750. */
uint32_t lifted_f496750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4968a0. */
uint32_t lifted_f4968a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x496a10. */
uint32_t lifted_f496a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x496b70. */
uint32_t lifted_f496b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x496cd0. */
uint32_t lifted_f496cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x496df0. */
uint32_t lifted_f496df0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x496f40. */
uint32_t lifted_f496f40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x497140. */
uint32_t lifted_f497140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x497340. */
uint32_t lifted_f497340(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4974c0. */
uint32_t lifted_f4974c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4975d0. */
uint32_t lifted_f4975d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4977c0. */
uint32_t lifted_f4977c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4978d0. */
uint32_t lifted_f4978d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x497a90. */
uint32_t lifted_f497a90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x497c50. */
uint32_t lifted_f497c50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x497da0. */
uint32_t lifted_f497da0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x497ee0. */
uint32_t lifted_f497ee0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4980f0. */
uint32_t lifted_f4980f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x498280. */
uint32_t lifted_f498280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x498470. */
uint32_t lifted_f498470(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x498570. */
uint32_t lifted_f498570(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x498660. */
uint32_t lifted_f498660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x498770. */
uint32_t lifted_f498770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x498910. */
uint32_t lifted_f498910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x498a80. */
uint32_t lifted_f498a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x498bf0. */
uint32_t lifted_f498bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x498db0. */
uint32_t lifted_f498db0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x498f20. */
uint32_t lifted_f498f20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x499090. */
uint32_t lifted_f499090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4991f0. */
uint32_t lifted_f4991f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x499350. */
uint32_t lifted_f499350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x499460. */
uint32_t lifted_f499460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4995a0. */
uint32_t lifted_f4995a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x499700. */
uint32_t lifted_f499700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x499860. */
uint32_t lifted_f499860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4999f0. */
uint32_t lifted_f4999f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x499bc0. */
uint32_t lifted_f499bc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x499dd0. */
uint32_t lifted_f499dd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x499fb0. */
uint32_t lifted_f499fb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49a020. */
uint32_t lifted_f49a020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49a120. */
uint32_t lifted_f49a120(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49a180. */
uint32_t lifted_f49a180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49a270. */
uint32_t lifted_f49a270(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49a2f0. */
uint32_t lifted_f49a2f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49a420. */
uint32_t lifted_f49a420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49a480. */
uint32_t lifted_f49a480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49a590. */
uint32_t lifted_f49a590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49a600. */
uint32_t lifted_f49a600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49a690. */
uint32_t lifted_f49a690(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49a780. */
uint32_t lifted_f49a780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49a8a0. */
uint32_t lifted_f49a8a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49aa40. */
uint32_t lifted_f49aa40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49abb0. */
uint32_t lifted_f49abb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49aca0. */
uint32_t lifted_f49aca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49ae50. */
uint32_t lifted_f49ae50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49b000. */
uint32_t lifted_f49b000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49b4a0. */
uint32_t lifted_f49b4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49b4e0. */
uint32_t lifted_f49b4e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49b5c0. */
uint32_t lifted_f49b5c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49b680. */
uint32_t lifted_f49b680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49b6d0. */
uint32_t lifted_f49b6d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49b7e0. */
uint32_t lifted_f49b7e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49b8d0. */
uint32_t lifted_f49b8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49ba30. */
uint32_t lifted_f49ba30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49bac0. */
uint32_t lifted_f49bac0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49bc60. */
uint32_t lifted_f49bc60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49bcf0. */
uint32_t lifted_f49bcf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49bdb0. */
uint32_t lifted_f49bdb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49be70. */
uint32_t lifted_f49be70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49bf30. */
uint32_t lifted_f49bf30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49bf80. */
uint32_t lifted_f49bf80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49c000. */
uint32_t lifted_f49c000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49c140. */
uint32_t lifted_f49c140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49c290. */
uint32_t lifted_f49c290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49c3d0. */
uint32_t lifted_f49c3d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49c510. */
uint32_t lifted_f49c510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49c660. */
uint32_t lifted_f49c660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49c7b0. */
uint32_t lifted_f49c7b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49c900. */
uint32_t lifted_f49c900(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49ca00. */
uint32_t lifted_f49ca00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49cb40. */
uint32_t lifted_f49cb40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49cc80. */
uint32_t lifted_f49cc80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49cd20. */
uint32_t lifted_f49cd20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49ced0. */
uint32_t lifted_f49ced0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49cff0. */
uint32_t lifted_f49cff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49d120. */
uint32_t lifted_f49d120(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49d1f0. */
uint32_t lifted_f49d1f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49d380. */
uint32_t lifted_f49d380(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49d4b0. */
uint32_t lifted_f49d4b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49d580. */
uint32_t lifted_f49d580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49d710. */
uint32_t lifted_f49d710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49d840. */
uint32_t lifted_f49d840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49d910. */
uint32_t lifted_f49d910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49daa0. */
uint32_t lifted_f49daa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49db80. */
uint32_t lifted_f49db80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49dbe0. */
uint32_t lifted_f49dbe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49dd00. */
uint32_t lifted_f49dd00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49de10. */
uint32_t lifted_f49de10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49deb0. */
uint32_t lifted_f49deb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49e000. */
uint32_t lifted_f49e000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49e140. */
uint32_t lifted_f49e140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49e2a0. */
uint32_t lifted_f49e2a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49e410. */
uint32_t lifted_f49e410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49e540. */
uint32_t lifted_f49e540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49e6a0. */
uint32_t lifted_f49e6a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49e810. */
uint32_t lifted_f49e810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49e960. */
uint32_t lifted_f49e960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49ead0. */
uint32_t lifted_f49ead0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49ec30. */
uint32_t lifted_f49ec30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49ed90. */
uint32_t lifted_f49ed90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49eeb0. */
uint32_t lifted_f49eeb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49f000. */
uint32_t lifted_f49f000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49f200. */
uint32_t lifted_f49f200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49f400. */
uint32_t lifted_f49f400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49f580. */
uint32_t lifted_f49f580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49f690. */
uint32_t lifted_f49f690(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49f880. */
uint32_t lifted_f49f880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49f990. */
uint32_t lifted_f49f990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49fb50. */
uint32_t lifted_f49fb50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49fd10. */
uint32_t lifted_f49fd10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49fe60. */
uint32_t lifted_f49fe60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x49ffa0. */
uint32_t lifted_f49ffa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a01b0. */
uint32_t lifted_f4a01b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a0340. */
uint32_t lifted_f4a0340(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a0530. */
uint32_t lifted_f4a0530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a0630. */
uint32_t lifted_f4a0630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a0720. */
uint32_t lifted_f4a0720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a0830. */
uint32_t lifted_f4a0830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a09d0. */
uint32_t lifted_f4a09d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a0b40. */
uint32_t lifted_f4a0b40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a0cb0. */
uint32_t lifted_f4a0cb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a0e70. */
uint32_t lifted_f4a0e70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a0fe0. */
uint32_t lifted_f4a0fe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a1150. */
uint32_t lifted_f4a1150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a12b0. */
uint32_t lifted_f4a12b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a1410. */
uint32_t lifted_f4a1410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a1520. */
uint32_t lifted_f4a1520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a1660. */
uint32_t lifted_f4a1660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a17c0. */
uint32_t lifted_f4a17c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a1920. */
uint32_t lifted_f4a1920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a1ab0. */
uint32_t lifted_f4a1ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a1c80. */
uint32_t lifted_f4a1c80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a1e90. */
uint32_t lifted_f4a1e90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a2070. */
uint32_t lifted_f4a2070(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a20e0. */
uint32_t lifted_f4a20e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a21e0. */
uint32_t lifted_f4a21e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a2240. */
uint32_t lifted_f4a2240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a2330. */
uint32_t lifted_f4a2330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a23b0. */
uint32_t lifted_f4a23b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a24e0. */
uint32_t lifted_f4a24e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a2540. */
uint32_t lifted_f4a2540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a2650. */
uint32_t lifted_f4a2650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a26c0. */
uint32_t lifted_f4a26c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a2750. */
uint32_t lifted_f4a2750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a2840. */
uint32_t lifted_f4a2840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a2960. */
uint32_t lifted_f4a2960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a2af0. */
uint32_t lifted_f4a2af0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a2c60. */
uint32_t lifted_f4a2c60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a2d50. */
uint32_t lifted_f4a2d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4a2ef0. */
uint32_t lifted_f4a2ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4a9140. */
uint32_t lifted_f4a9140(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4a9f40. */
uint32_t lifted_f4a9f40(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4aa240. */
uint32_t lifted_f4aa240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aa350. */
uint32_t lifted_f4aa350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aa3c0. */
uint32_t lifted_f4aa3c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aa450. */
uint32_t lifted_f4aa450(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aa540. */
uint32_t lifted_f4aa540(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ab2a0. */
uint32_t lifted_surface_binary32(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ab310. */
uint32_t lifted_f4ab310(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ac840. */
uint32_t lifted_actor_store_times_twelve_4ac840(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x4ad3c0. */
uint32_t lifted_actor_double_orbit_point(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad520. */
uint32_t lifted_actor_set_words_3a_full(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4adf90. */
uint32_t lifted_f4adf90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ae0c0. */
uint32_t lifted_f4ae0c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ae0f0. */
uint32_t lifted_f4ae0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4af8c0. */
uint32_t lifted_actor_chain_paint(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b15e0. */
uint32_t lifted_actor_image_bounds(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3380. */
uint32_t lifted_f4b3380(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5f50. */
uint32_t lifted_object_list_prune(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6240. */
uint32_t lifted_f4b6240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b68a0. */
uint32_t lifted_f4b68a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b69f0. */
uint32_t lifted_object_glyph_layout(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6fa0. */
uint32_t lifted_list_item_4b6fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7610. */
uint32_t lifted_f4b7610(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ccf3b. */
uint32_t lifted_f4ccf3b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd520. */
uint32_t lifted_f4cd520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd8b0. */
uint32_t lifted_f4cd8b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cdaf0. */
uint32_t lifted_rtl_string_tail(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce780. */
uint32_t lifted_f4ce780(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d7a10. */
uint32_t lifted_f4d7a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7bb0. */
uint32_t lifted_f4d7bb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d82c6. */
uint32_t lifted_rtl_select_float_helpers(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8ab0. */
uint32_t lifted_f4d8ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d94a0. */
uint32_t lifted_rtl_probe_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9f06. */
uint32_t lifted_rtl_jump_capture(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4da3ba. */
uint32_t lifted_f4da3ba(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4daae8. */
uint32_t lifted_f4daae8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dac40. */
uint32_t lifted_f4dac40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dad19. */
uint32_t lifted_rtl_sign_of(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dae1e. */
uint32_t lifted_float_split(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dae62. */
uint32_t lifted_rtl_absolute_double(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4daed8. */
uint32_t lifted_float_exp(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db10a. */
uint32_t lifted_rtl_scratch_triple_call(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db866. */
uint32_t lifted_rtl_flags_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dbf80. */
uint32_t lifted_f4dbf80(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4dfac0. */
uint32_t lifted_f4dfac0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dfb24. */
uint32_t lifted_f4dfb24(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e04ec. */
uint32_t lifted_f4e04ec(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e14dc. */
uint32_t lifted_f4e14dc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3697. */
uint32_t lifted_return_unchanged_4e3697(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e509c. */
uint32_t lifted_f4e509c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e55d0. */
uint32_t lifted_f4e55d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5b0c. */
uint32_t lifted_f4e5b0c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6250. */
uint32_t lifted_f4e6250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6b50. */
uint32_t lifted_f4e6b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6bac. */
uint32_t lifted_f4e6bac(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6d16. */
uint32_t lifted_f4e6d16(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9d00. */
uint32_t lifted_return_zero_4e9d00(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec8c0. */
uint32_t lifted_return_unchanged_4ec8c0(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
