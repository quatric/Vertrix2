#ifndef VERTRIX_LIFTED_WHOLE_0_H
#define VERTRIX_LIFTED_WHOLE_0_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_MIXER_OUTPUT_STACK = 92,
    LIFTED_MIXER_OUTPUT_401054_STACK = 92,
    LIFTED_MPEG_HEADER_DECODE_STACK = 80,
    LIFTED_F404580_STACK = 64,
    LIFTED_BIT_READER_BITS24_STACK = 76,
    LIFTED_BIT_READER_BITS16_STACK = 76,
    LIFTED_QUEUE_PUSH_STACK = 100,
    LIFTED_QUEUE_POP_STACK = 88,
    LIFTED_F405EE0_STACK = 80,
    LIFTED_F405F30_STACK = 88,
    LIFTED_F405F70_STACK = 108,
    LIFTED_F406170_STACK = 852,
    LIFTED_F407020_STACK = 184,
    LIFTED_BITS_HEADER_STACK = 176,
    LIFTED_BITS_FILL_STACK = 128,
    LIFTED_F407720_STACK = 100,
    LIFTED_F407830_STACK = 392,
    LIFTED_F4083A0_STACK = 212,
    LIFTED_F4088E0_STACK = 1176,
    LIFTED_WINDOW_TABLES_STACK = 208,
    LIFTED_F40A800_STACK = 88,
    LIFTED_TEXT_FOR_CODE_STACK = 76,
    LIFTED_REGISTRY_ADD_STACK = 72,
    LIFTED_F40A8F0_STACK = 88,
    LIFTED_F40A950_STACK = 92,
    LIFTED_F40A9D0_STACK = 124,
    LIFTED_F40AAE0_STACK = 76,
    LIFTED_FORWARD_REGISTERS_STACK = 68,
    LIFTED_HANDLES_INIT_STACK = 84,
    LIFTED_HANDLES_SHUTDOWN_STACK = 84,
    LIFTED_F40AC00_STACK = 68,
    LIFTED_F40AC10_STACK = 68,
    LIFTED_F40AC20_STACK = 68,
    LIFTED_F40AC30_STACK = 68,
    LIFTED_F40AC50_STACK = 84,
    LIFTED_CLOSE_CELL_STACK = 84,
    LIFTED_F40ACD0_STACK = 68,
    LIFTED_HANDLES_RELEASE_STACK = 68,
    LIFTED_F40ADB0_STACK = 68,
    LIFTED_F40ADC0_STACK = 68,
    LIFTED_F40ADD0_STACK = 68,
    LIFTED_F40ADE0_STACK = 68,
    LIFTED_F40ADF0_STACK = 68,
    LIFTED_F40AE00_STACK = 68,
    LIFTED_F40AE10_STACK = 68,
    LIFTED_F40AE60_STACK = 68,
    LIFTED_MODULE_RESET_CALLS_STACK = 84,
    LIFTED_F40AED0_STACK = 92,
    LIFTED_F40AF30_STACK = 132,
    LIFTED_F40AF90_STACK = 96,
    LIFTED_F40B040_STACK = 116,
    LIFTED_F40B080_STACK = 88,
    LIFTED_F40B620_STACK = 116,
    LIFTED_F40B660_STACK = 88,
    LIFTED_CURVE_TABLE_BUILD_STACK = 120,
    LIFTED_F40C1C0_STACK = 72,
    LIFTED_GLOBAL_DISCARD_CALL_STACK = 68,
    LIFTED_GLOBAL_PAIR_CALL_STACK = 76,
    LIFTED_GLOBAL_CALL_STACK = 68,
    LIFTED_FILE_READ_EXACT_STACK = 88,
    LIFTED_FILE_READ_BYTE_STACK = 88,
    LIFTED_FILE_READ_WORD_STACK = 88,
    LIFTED_FILE_READ_DWORD_STACK = 88,
    LIFTED_F40C320_STACK = 88,
    LIFTED_FILE_READ_WORD_SWAPPED_STACK = 88,
    LIFTED_F40C430_STACK = 100,
    LIFTED_MIXER_CHANNEL_STACK = 116,
    LIFTED_MIXER_PITCH_STACK = 80,
    LIFTED_MIXER_NOTE_PERIOD_STACK = 72,
    LIFTED_MIXER_PORTAMENTO_STACK = 88,
    LIFTED_MIXER_VIBRATO_STACK = 80,
    LIFTED_MIXER_VOLUME_SLIDE_STACK = 76,
    LIFTED_MIXER_VOLUME_COLUMN_STACK = 92,
    LIFTED_MIXER_TRIGGER_RESET_STACK = 76,
    LIFTED_MIXER_PLAYBACK_TICK_STACK = 88,
    LIFTED_MIXER_SELECT_SAMPLE_STACK = 80,
    LIFTED_MIXER_NOTE_RELEASE_STACK = 68,
    LIFTED_F40E670_STACK = 76,
    LIFTED_MIXER_ROW_STACK = 92,
    LIFTED_MIXER_PUBLISH_STACK = 104,
    LIFTED_FLAGGED_TABLE_CALL_STACK = 92,
    LIFTED_DEVICE_LOCK_STACK = 80,
    LIFTED_DEVICE_MARK_DIRTY_STACK = 68,
    LIFTED_DEVICE_SET_LIMIT_STACK = 72,
    LIFTED_DEVICE_SET_PAIR_STACK = 68,
    LIFTED_DEVICE_GET_VALUES_STACK = 68,
    LIFTED_DEVICE_GET_LOCKED_STACK = 68,
    LIFTED_OBJECT_FREE_TREE_STACK = 116,
    LIFTED_TABLE_LEVEL_FOR_STACK = 72,
    LIFTED_OBJECT_ATTACH_ITEM_STACK = 100,
    LIFTED_F40F9E0_STACK = 308,
    LIFTED_PITCH_CURVE_STACK = 72,
    LIFTED_F4108A0_STACK = 416,
    LIFTED_F411280_STACK = 80,
    LIFTED_F4112D0_STACK = 468,
    LIFTED_F411C70_STACK = 164,
    LIFTED_RECORD_TABLE_INIT_STACK = 72,
    LIFTED_RECORD_TABLE_LOAD_STACK = 100,
    LIFTED_F412240_STACK = 136,
    LIFTED_F412390_STACK = 88,
    LIFTED_ACTOR_STORAGE_STYLE_STACK = 68,
    LIFTED_RECORD_STEP_STACK = 68,
    LIFTED_F412510_STACK = 68,
    LIFTED_RECORD_FIELD_STACK = 68,
    LIFTED_RECORD_STORE_CURRENT_STACK = 80,
    LIFTED_OBJECT_FLAG_STACK = 64,
    LIFTED_ANCHOR_OFFSETS_UPDATE_STACK = 92,
    LIFTED_ANCHOR_OFFSETS_UPDATE_414B10_STACK = 92,
    LIFTED_TEXT_TABLE_REFRESH_STACK = 148,
    LIFTED_F415330_STACK = 80,
    LIFTED_F415350_STACK = 72,
    LIFTED_TABLE_PAIR_SELECT_STACK = 68,
    LIFTED_F415470_STACK = 76,
    LIFTED_GLOBAL_RESET_PAIR_STACK = 68,
    LIFTED_SESSION_LATCH_RELEASE_STACK = 68,
    LIFTED_GLOBAL_CLEAR_TABLES_STACK = 68,
    LIFTED_GLOBAL_SET_CELL_STACK = 64,
    LIFTED_GLOBAL_SET_CELL_415B40_STACK = 64,
    LIFTED_SESSION_REGISTERS_RESET_STACK = 68,
    LIFTED_SESSION_REGISTERS_RESET_OPEN_STACK = 72,
    LIFTED_SESSION_REGISTERS_RESET_SECONDARY_STACK = 68,
    LIFTED_TABLE_ALL_FILLED_STACK = 72,
    LIFTED_TABLE_ALL_FILLED_415C30_STACK = 72,
    LIFTED_GLOBAL_CELL_STACK = 64,
    LIFTED_GLOBAL_SET_CELL_415D90_STACK = 64,
    LIFTED_CLEAR_EACH_CALL_STACK = 76,
    LIFTED_TABLE_FIND_MATCHING_STACK = 88,
    LIFTED_TABLE_FIND_EQUAL_STACK = 72,
    LIFTED_TABLE_VALUE_MATCHING_STACK = 72,
    LIFTED_TABLE_VALUE_EQUAL_STACK = 72,
    LIFTED_F415EF0_STACK = 80,
    LIFTED_F415F10_STACK = 80,
    LIFTED_F415F30_STACK = 80,
    LIFTED_F415F50_STACK = 80,
    LIFTED_F415F70_STACK = 80,
    LIFTED_F415F90_STACK = 80,
    LIFTED_F415FB0_STACK = 72,
    LIFTED_F415FC0_STACK = 72,
    LIFTED_F415FD0_STACK = 72,
    LIFTED_F415FE0_STACK = 72,
    LIFTED_F416970_STACK = 72,
    LIFTED_F416B30_STACK = 80,
    LIFTED_F416B50_STACK = 80,
    LIFTED_F416B70_STACK = 80,
    LIFTED_F416B90_STACK = 80,
    LIFTED_F416BB0_STACK = 80,
    LIFTED_F416BD0_STACK = 80,
    LIFTED_F416BF0_STACK = 80,
    LIFTED_POINT_LIST_ADD_STACK = 76,
    LIFTED_F417030_STACK = 80,
    LIFTED_F4170F0_STACK = 80,
    LIFTED_F417130_STACK = 80,
    LIFTED_F4171E0_STACK = 84,
    LIFTED_F417220_STACK = 84,
    LIFTED_F417260_STACK = 80,
    LIFTED_F417290_STACK = 80,
    LIFTED_F4172C0_STACK = 120,
    LIFTED_F417350_STACK = 104,
    LIFTED_F4173D0_STACK = 120,
    LIFTED_F417460_STACK = 104,
    LIFTED_SFX_ALLOCATE_CHANNEL_P1_STACK = 84,
    LIFTED_SFX_ALLOCATE_CHANNEL_P2_STACK = 84,
    LIFTED_F4175B0_STACK = 84,
    LIFTED_F417620_STACK = 84,
    LIFTED_SCORE_TEXT_STACK = 80,
    LIFTED_TABLE_LAST_CHANGE_STACK = 76,
    LIFTED_F417880_STACK = 72,
    LIFTED_F417890_STACK = 72,
    LIFTED_F4178A0_STACK = 72,
    LIFTED_F4178B0_STACK = 72,
    LIFTED_F4178C0_STACK = 72,
    LIFTED_F4178D0_STACK = 72,
    LIFTED_TABLE_BYTE_PAIR_STACK = 68,
    LIFTED_TABLE_PAIR_LINK_STACK = 72,
    LIFTED_QUAD_AVERAGE_STACK = 112,
    LIFTED_F417C80_STACK = 84,
    LIFTED_TABLE_GRID_VALUE_STACK = 68,
    LIFTED_F417D10_STACK = 68,
    LIFTED_F417D40_STACK = 68,
    LIFTED_F417D70_STACK = 68,
    LIFTED_TABLE_GROUPS_USED_STACK = 88,
    LIFTED_TABLE_ROW_USED_STACK = 76,
    LIFTED_TABLE_BONUS_STACK = 68,
    LIFTED_TABLE_RANDOM_EMPTY_STACK = 164,
    LIFTED_TABLE_RANDOM_EMPTY_417ED0_STACK = 164,
    LIFTED_MATCHER_RESET_STACK = 68,
    LIFTED_TABLE_COLUMN_COUNT_STACK = 84,
    LIFTED_TABLE_COLUMN_NTH_STACK = 80,
    LIFTED_TABLE_COLUMN_OPEN_STACK = 88,
    LIFTED_TABLE_COLUMN_OPEN_NTH_STACK = 84,
    LIFTED_F418100_STACK = 68,
    LIFTED_F418110_STACK = 84,
    LIFTED_F418130_STACK = 84,
    LIFTED_COMPARE_UNSIGNED_STACK = 64,
    LIFTED_F4182C0_STACK = 92,
    LIFTED_RESOURCE_ENTRY_CALL_STACK = 72,
    LIFTED_RESOURCE_ENTRY_CALL_418550_STACK = 72,
    LIFTED_RESOURCE_ENTRY_CALL_418570_STACK = 72,
    LIFTED_RTL_CONSTRUCT_DERIVED_STREAM_STACK = 68,
    LIFTED_OBJECT_SET_PERIOD_STACK = 64,
    LIFTED_ACTOR_CLOCK_TO_PERIOD_STACK = 68,
    LIFTED_OBJECT_SET_COUNTER_STACK = 64,
    LIFTED_OBJECT_INVOKE_CALLBACK_STACK = 72,
    LIFTED_OBJECT_CLEAR_COUNTER_STACK = 64,
    LIFTED_F418970_STACK = 120,
    LIFTED_F418AE0_STACK = 76,
    LIFTED_F418CE0_STACK = 100,
    LIFTED_F4192A0_STACK = 172,
    LIFTED_F4193B0_STACK = 168,
    LIFTED_GUARDED_CALL_STACK = 68,
    LIFTED_GUARDED_CALL_4194B0_STACK = 68,
    LIFTED_F419EF0_STACK = 116,
    LIFTED_F419F60_STACK = 68,
    LIFTED_F41A010_STACK = 104,
    LIFTED_F41A240_STACK = 104,
    LIFTED_F41A2B0_STACK = 92,
    LIFTED_SURFACE_BLIT_PROGRESS_STACK = 92,
    LIFTED_F41A4E0_STACK = 96,
    LIFTED_F41A520_STACK = 76,
    LIFTED_F41A680_STACK = 96,
    LIFTED_F41A6C0_STACK = 96,
    LIFTED_F41A700_STACK = 128,
    LIFTED_F41A800_STACK = 148,
    LIFTED_GLOBAL_CLEAR_STACK = 68,
    LIFTED_F41A940_STACK = 72,
    LIFTED_F41A960_STACK = 104,
    LIFTED_F41A9A0_STACK = 100,
    LIFTED_F41AA20_STACK = 104,
    LIFTED_F41AAA0_STACK = 104,
    LIFTED_F41AAF0_STACK = 68,
    LIFTED_F41AB00_STACK = 76,
    LIFTED_F41AB30_STACK = 76,
    LIFTED_F41AB60_STACK = 76,
    LIFTED_SURFACE_BLIT_REGION_STACK = 96,
    LIFTED_F41ABE0_STACK = 76,
    LIFTED_F41AC00_STACK = 76,
    LIFTED_F41AC20_STACK = 76,
    LIFTED_F41AC40_STACK = 80,
    LIFTED_SURFACE_CLEAR_SECOND_STACK = 72,
    LIFTED_F41AC80_STACK = 84,
    LIFTED_F41ACA0_STACK = 80,
    LIFTED_F41B5E0_STACK = 124,
    LIFTED_F41B680_STACK = 120,
    LIFTED_F41C020_STACK = 124,
    LIFTED_F41C080_STACK = 96,
    LIFTED_F41C0C0_STACK = 84,
    LIFTED_F41C0F0_STACK = 120,
    LIFTED_F41C160_STACK = 120,
    LIFTED_F41C1D0_STACK = 120,
    LIFTED_F41C240_STACK = 120,
    LIFTED_F41C2B0_STACK = 120,
    LIFTED_F41C390_STACK = 116,
    LIFTED_F41C400_STACK = 68,
    LIFTED_F41C6D0_STACK = 120,
    LIFTED_F41C740_STACK = 120,
    LIFTED_F41C9E0_STACK = 176,
    LIFTED_F41CBB0_STACK = 136,
    LIFTED_F41D410_STACK = 108,
    LIFTED_F41D470_STACK = 156,
    LIFTED_F41D510_STACK = 152,
    LIFTED_GATE_DISPATCH_CALL_STACK = 120,
    LIFTED_F41D640_STACK = 72,
    LIFTED_FRAME_COUNTER_UPDATE_STACK = 72,
    LIFTED_F41DD60_STACK = 120,
    LIFTED_F41DDF0_STACK = 120,
    LIFTED_F41DEC0_STACK = 96,
    LIFTED_F41DF00_STACK = 96,
    LIFTED_F41EDE0_STACK = 204,
    LIFTED_F41EFE0_STACK = 152,
    LIFTED_F41F460_STACK = 156,
    LIFTED_F41F910_STACK = 156,
    LIFTED_F41FC70_STACK = 156,
    LIFTED_F421E80_STACK = 144,
    LIFTED_F423D70_STACK = 92,
    LIFTED_F424160_STACK = 68,
    LIFTED_F424180_STACK = 104,
    LIFTED_F4241D0_STACK = 64,
    LIFTED_F4241E0_STACK = 64,
    LIFTED_F4241F0_STACK = 64,
    LIFTED_F424200_STACK = 64,
    LIFTED_OBJECT_CENTER_TITLED_STACK = 84,
    LIFTED_F424790_STACK = 160,
    LIFTED_F424890_STACK = 160,
    LIFTED_F425260_STACK = 184,
    LIFTED_F4253B0_STACK = 164,
    LIFTED_F4259D0_STACK = 144,
    LIFTED_F425A50_STACK = 144,
    LIFTED_F425AE0_STACK = 196,
    LIFTED_OBJECT_SET_TABLE_STACK = 72,
    LIFTED_OBJECT_CLEAR_SLOTS_STACK = 68,
    LIFTED_TABLE_USED_COUNT_STACK = 72,
    LIFTED_PLAYER_PIECE_INITIALIZE_STACK = 68,
    LIFTED_PIECE_INIT_FROM_KIND_STACK = 68,
    LIFTED_F425F40_STACK = 64,
    LIFTED_AI_ROW_REACH_STACK = 84,
    LIFTED_AI_BOMB_SEARCH_STACK = 268,
    LIFTED_AI_FEATURES_STACK = 76,
    LIFTED_AI_MODE_FLAGS_STACK = 76,
    LIFTED_AI_COMPARE_BOARDS_STACK = 184,
    LIFTED_AI_CHOICE_SCORES_STACK = 112,
    LIFTED_AI_FIND_BEST_SLOT_STACK = 104,
    LIFTED_AI_CHOOSE_PIECE_ROTATION_STACK = 76,
    LIFTED_SETTINGS_DEFAULTS_STACK = 116,
    LIFTED_OBJECT_DESTROY_C_STACK = 136,
    LIFTED_SAVED_BLOCK_LOAD_STACK = 96,
    LIFTED_F429460_STACK = 148,
    LIFTED_F429600_STACK = 88,
    LIFTED_OBJECT_ADDRESS_PLUS_4_STACK = 64,
    LIFTED_MARKER_ACTOR_CONSTRUCT_STACK = 68,
    LIFTED_PIECE_ACTOR_CONSTRUCT_SLOTS_STACK = 96,
    LIFTED_CHOICE_GRID_APPLY_STACK = 100,
    LIFTED_CHOICE_GRID_LOAD_VALUES_STACK = 96,
    LIFTED_CHOICE_GRID_STORE_VALUES_STACK = 92,
    LIFTED_CHOICE_GRID_PICK_ROWS_STACK = 112,
    LIFTED_CHOICE_GRID_PICK_CELL_STACK = 112,
    LIFTED_CHOICE_GRID_PICK_COLUMN_STACK = 100,
    LIFTED_CHOICE_GRID_MARK_STACK = 64,
    LIFTED_CHOICE_GRID_CELL_BYTES_STACK = 64,
    LIFTED_CHOICE_GRID_AVAILABLE_STACK = 64,
    LIFTED_CHOICE_GRID_ANY_MARKED_STACK = 84,
    LIFTED_F42A310_STACK = 144,
    LIFTED_PIECE_RELEASE_CHILDREN_STACK = 72,
    LIFTED_F42A4A0_STACK = 72,
    LIFTED_F42A540_STACK = 276,
    LIFTED_PIECE_CHILDREN_PLACE_STACK = 88,
    LIFTED_F42A8B0_STACK = 72,
    LIFTED_F42A8E0_STACK = 84,
    LIFTED_PIECE_CLEAR_OFFSET_X_STACK = 64,
    LIFTED_PIECE_CLEAR_OFFSET_Y_STACK = 64,
    LIFTED_F42A960_STACK = 64,
    LIFTED_F42A970_STACK = 64,
    LIFTED_PIECE_CHILD_KINDS_STACK = 72,
    LIFTED_F42A9D0_STACK = 80,
    LIFTED_F42AA20_STACK = 80,
    LIFTED_PIECE_ACTOR_PARENT_CONSTRUCT_STACK = 76,
    LIFTED_PIECE_ACTOR_CONSTRUCT_PLACED_STACK = 180,
    LIFTED_PIECE_ACTOR_LAYOUT_STACK = 80,
    LIFTED_PIECE_ACTOR_CYCLE_STACK = 88,
    LIFTED_PLAYER_PREVIEW_MOTION_START_STACK = 80,
    LIFTED_PLAYER_PREVIEW_BELOW_LIMIT_STACK = 68,
    LIFTED_PLAYER_PREVIEW_FRAME_STACK = 68,
    LIFTED_PLAYER_PREVIEW_TOGGLE_STACK = 72,
    LIFTED_PLAYER_PREVIEW_SET_MODE_STACK = 64,
    LIFTED_UI_PLAYER_PREVIEW_PARENT_CONSTRUCT_STACK = 76,
    LIFTED_F42B290_STACK = 96,
    LIFTED_UI_PLAYER_PREVIEWS_CONSTRUCT_STACK = 232,
    LIFTED_PIECE_ACTOR_CONSTRUCT_EMPTY_STACK = 68,
    LIFTED_F42B6B0_STACK = 176,
    LIFTED_PIECE_SET_VARIANT_STACK = 72,
    LIFTED_PIECE_SNAP_TO_LEFT_STACK = 80,
    LIFTED_PIECE_SNAP_TO_ORIGIN_STACK = 84,
    LIFTED_PIECE_ARM_ONCE_STACK = 80,
    LIFTED_OBJECT_Y_ABOVE_LIMIT_STACK = 68,
    LIFTED_F42BA70_STACK = 72,
    LIFTED_F42BAB0_STACK = 64,
    LIFTED_BLOCK_CONSTRUCT_STACK = 68,
    LIFTED_BLOCK_CREATE_STACK = 128,
    LIFTED_BOARD_CONSTRUCT_STACK = 200,
    LIFTED_BOARD_RELEASE_ACTIVE_STACK = 80,
    LIFTED_BOARD_RELEASE_PIECE_CHILDREN_STACK = 72,
    LIFTED_BOARD_CLEAR_COLLECTION_STACK = 72,
    LIFTED_BOARD_CLEAR_COLLECTION_42EBE0_STACK = 72,
    LIFTED_BOARD_CLEAR_COLLECTION_42EC00_STACK = 72,
    LIFTED_BOARD_CLEAR_COLLECTION_42EC20_STACK = 72,
    LIFTED_BOARD_CLEAR_COLLECTION_42EC40_STACK = 72,
    LIFTED_BOARD_CLEAR_COLLECTION_42EC60_STACK = 72,
    LIFTED_BOARD_COLLECTION_ALL_HANDLER_STACK = 72,
    LIFTED_BOARD_COLLECTION_ALL_HANDLER_42ECA0_STACK = 72,
    LIFTED_BOARD_COLLECTION_ALL_HANDLER_42ECC0_STACK = 72,
    LIFTED_BOARD_PIECE_ALL_HANDLER_STACK = 76,
    LIFTED_BOARD_PIECE_ALL_HANDLER_42ED70_STACK = 76,
    LIFTED_BOARD_COLLECTION_SET_HANDLER_STACK = 72,
    LIFTED_BOARD_PIECE_ALL_HANDLER_42EDF0_STACK = 76,
    LIFTED_BOARD_READY_PREVIEWS_STACK = 92,
    LIFTED_BOARD_RESTART_SLOTS_STACK = 100,
    LIFTED_F42EEE0_STACK = 72,
    LIFTED_F42EF00_STACK = 72,
    LIFTED_F42EF10_STACK = 72,
    LIFTED_F42EF20_STACK = 72,
    LIFTED_F42EF30_STACK = 72,
    LIFTED_F42EF40_STACK = 72,
    LIFTED_F42EF50_STACK = 72,
    LIFTED_PLAYER_FILL_BYTES_STACK = 68,
    LIFTED_PLAYER_FILL_BYTES_42EF80_STACK = 68,
    LIFTED_BOARD_MARK_COLUMNS_STACK = 96,
    LIFTED_BOARD_PIECE_STORE_NEGATED_STACK = 76,
    LIFTED_BOARD_PIECE_STORE_NEGATED_ALWAYS_STACK = 72,
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
    LIFTED_PLAYER_FILL_BYTES_42F7D0_STACK = 68,
    LIFTED_PLAYER_FILL_BYTES_42F7F0_STACK = 68,
    LIFTED_PLAYER_FILL_BYTES_42F810_STACK = 68,
    LIFTED_PLAYER_FILL_BYTES_42F830_STACK = 68,
    LIFTED_F42F850_STACK = 72,
    LIFTED_F42F860_STACK = 72,
    LIFTED_F42F870_STACK = 72,
    LIFTED_F42F880_STACK = 72,
    LIFTED_F42F890_STACK = 64,
    LIFTED_F42F8A0_STACK = 64,
    LIFTED_F42F8B0_STACK = 80,
    LIFTED_F42F8E0_STACK = 80,
    LIFTED_BOARD_SET_ACTOR_CLIP_STACK = 76,
    LIFTED_BOARD_CREATE_OVERLAY_STACK = 164,
    LIFTED_BOARD_EXTRA_IS_IDLE_STACK = 68,
    LIFTED_BOARD_PLACE_EXTRA_STACK = 76,
    LIFTED_BOARD_PLACE_EXTRA_430100_STACK = 76,
    LIFTED_BOARD_RELEASE_EXTRA_STACK = 80,
    LIFTED_ACTOR_SPAWN_MATCH_EFFECT_STACK = 152,
    LIFTED_ACTOR_SPAWN_MATCH_BURST_STACK = 184
};

/* Original 0x401010. */
uint32_t lifted_mixer_output(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x401054. */
uint32_t lifted_mixer_output_401054(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x404480. */
uint32_t lifted_mpeg_header_decode(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x404580. */
uint32_t lifted_f404580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x404610. */
uint32_t lifted_bit_reader_bits24(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x404680. */
uint32_t lifted_bit_reader_bits16(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x405e00. */
uint32_t lifted_queue_push(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x405ea0. */
uint32_t lifted_queue_pop(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x405ee0. */
uint32_t lifted_f405ee0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x405f30. */
uint32_t lifted_f405f30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x405f70. */
uint32_t lifted_f405f70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x406170. */
uint32_t lifted_f406170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x407020. */
uint32_t lifted_f407020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x407280. */
uint32_t lifted_bits_header(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4074a0. */
uint32_t lifted_bits_fill(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x407720. */
uint32_t lifted_f407720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x407830. */
uint32_t lifted_f407830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4083a0. */
uint32_t lifted_f4083a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4088e0. */
uint32_t lifted_f4088e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a590. */
uint32_t lifted_window_tables(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a800. */
uint32_t lifted_f40a800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a860. */
uint32_t lifted_text_for_code(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a890. */
uint32_t lifted_registry_add(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a8f0. */
uint32_t lifted_f40a8f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a950. */
uint32_t lifted_f40a950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a9d0. */
uint32_t lifted_f40a9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40aae0. */
uint32_t lifted_f40aae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ab10. */
uint32_t lifted_forward_registers(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ab60. */
uint32_t lifted_handles_init(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40aba0. */
uint32_t lifted_handles_shutdown(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ac00. */
uint32_t lifted_f40ac00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ac10. */
uint32_t lifted_f40ac10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ac20. */
uint32_t lifted_f40ac20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ac30. */
uint32_t lifted_f40ac30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ac50. */
uint32_t lifted_f40ac50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40aca0. */
uint32_t lifted_close_cell(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40acd0. */
uint32_t lifted_f40acd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ad50. */
uint32_t lifted_handles_release(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40adb0. */
uint32_t lifted_f40adb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40adc0. */
uint32_t lifted_f40adc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40add0. */
uint32_t lifted_f40add0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ade0. */
uint32_t lifted_f40ade0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40adf0. */
uint32_t lifted_f40adf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ae00. */
uint32_t lifted_f40ae00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ae10. */
uint32_t lifted_f40ae10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ae60. */
uint32_t lifted_f40ae60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ae80. */
uint32_t lifted_module_reset_calls(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40aed0. */
uint32_t lifted_f40aed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40af30. */
uint32_t lifted_f40af30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40af90. */
uint32_t lifted_f40af90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40b040. */
uint32_t lifted_f40b040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40b080. */
uint32_t lifted_f40b080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40b620. */
uint32_t lifted_f40b620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40b660. */
uint32_t lifted_f40b660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ba00. */
uint32_t lifted_curve_table_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c1c0. */
uint32_t lifted_f40c1c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c1e0. */
uint32_t lifted_global_discard_call(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c1f0. */
uint32_t lifted_global_pair_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c210. */
uint32_t lifted_global_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c220. */
uint32_t lifted_file_read_exact(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c260. */
uint32_t lifted_file_read_byte(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c2a0. */
uint32_t lifted_file_read_word(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c2e0. */
uint32_t lifted_file_read_dword(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c320. */
uint32_t lifted_f40c320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c360. */
uint32_t lifted_file_read_word_swapped(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c430. */
uint32_t lifted_f40c430(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c460. */
uint32_t lifted_mixer_channel(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ce20. */
uint32_t lifted_mixer_pitch(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ce80. */
uint32_t lifted_mixer_note_period(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40cff0. */
uint32_t lifted_mixer_portamento(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40d090. */
uint32_t lifted_mixer_vibrato(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40d250. */
uint32_t lifted_mixer_volume_slide(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40dc80. */
uint32_t lifted_mixer_volume_column(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40df20. */
uint32_t lifted_mixer_trigger_reset(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e030. */
uint32_t lifted_mixer_playback_tick(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e580. */
uint32_t lifted_mixer_select_sample(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e640. */
uint32_t lifted_mixer_note_release(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e670. */
uint32_t lifted_f40e670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e770. */
uint32_t lifted_mixer_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e8a0. */
uint32_t lifted_mixer_publish(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ed70. */
uint32_t lifted_flagged_table_call(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ede0. */
uint32_t lifted_device_lock(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ee30. */
uint32_t lifted_device_mark_dirty(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ee60. */
uint32_t lifted_device_set_limit(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40eea0. */
uint32_t lifted_device_set_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ef00. */
uint32_t lifted_device_get_values(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ef40. */
uint32_t lifted_device_get_locked(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ef90. */
uint32_t lifted_object_free_tree(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40f170. */
uint32_t lifted_table_level_for(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40f910. */
uint32_t lifted_object_attach_item(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40f9e0. */
uint32_t lifted_f40f9e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x410150. */
uint32_t lifted_pitch_curve(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4108a0. */
uint32_t lifted_f4108a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x411280. */
uint32_t lifted_f411280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4112d0. */
uint32_t lifted_f4112d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x411c70. */
uint32_t lifted_f411c70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4120a0. */
uint32_t lifted_record_table_init(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4121e0. */
uint32_t lifted_record_table_load(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x412240. */
uint32_t lifted_f412240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x412390. */
uint32_t lifted_f412390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4123d0. */
uint32_t lifted_actor_storage_style(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
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

/* Original 0x4126f0. */
uint32_t lifted_object_flag(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x414a90. */
uint32_t lifted_anchor_offsets_update(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x414b10. */
uint32_t lifted_anchor_offsets_update_414b10(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415180. */
uint32_t lifted_text_table_refresh(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415330. */
uint32_t lifted_f415330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415350. */
uint32_t lifted_f415350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4153e0. */
uint32_t lifted_table_pair_select(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415470. */
uint32_t lifted_f415470(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415530. */
uint32_t lifted_global_reset_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415550. */
uint32_t lifted_session_latch_release(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415b10. */
uint32_t lifted_global_clear_tables(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415b30. */
uint32_t lifted_global_set_cell(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415b40. */
uint32_t lifted_global_set_cell_415b40(const VertrixCalls *calls,
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

/* Original 0x415c00. */
uint32_t lifted_table_all_filled(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415c30. */
uint32_t lifted_table_all_filled_415c30(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415d60. */
uint32_t lifted_global_cell(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415d90. */
uint32_t lifted_global_set_cell_415d90(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415e10. */
uint32_t lifted_clear_each_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415e40. */
uint32_t lifted_table_find_matching(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415e80. */
uint32_t lifted_table_find_equal(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415eb0. */
uint32_t lifted_table_value_matching(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415ed0. */
uint32_t lifted_table_value_equal(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415ef0. */
uint32_t lifted_f415ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415f10. */
uint32_t lifted_f415f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415f30. */
uint32_t lifted_f415f30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415f50. */
uint32_t lifted_f415f50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415f70. */
uint32_t lifted_f415f70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415f90. */
uint32_t lifted_f415f90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415fb0. */
uint32_t lifted_f415fb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415fc0. */
uint32_t lifted_f415fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415fd0. */
uint32_t lifted_f415fd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415fe0. */
uint32_t lifted_f415fe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416970. */
uint32_t lifted_f416970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416b30. */
uint32_t lifted_f416b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416b50. */
uint32_t lifted_f416b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416b70. */
uint32_t lifted_f416b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416b90. */
uint32_t lifted_f416b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416bb0. */
uint32_t lifted_f416bb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416bd0. */
uint32_t lifted_f416bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416bf0. */
uint32_t lifted_f416bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416c10. */
uint32_t lifted_point_list_add(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417030. */
uint32_t lifted_f417030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4170f0. */
uint32_t lifted_f4170f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417130. */
uint32_t lifted_f417130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4171e0. */
uint32_t lifted_f4171e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417220. */
uint32_t lifted_f417220(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417260. */
uint32_t lifted_f417260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417290. */
uint32_t lifted_f417290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4172c0. */
uint32_t lifted_f4172c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417350. */
uint32_t lifted_f417350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4173d0. */
uint32_t lifted_f4173d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417460. */
uint32_t lifted_f417460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4174f0. */
uint32_t lifted_sfx_allocate_channel_p1(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417550. */
uint32_t lifted_sfx_allocate_channel_p2(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4175b0. */
uint32_t lifted_f4175b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417620. */
uint32_t lifted_f417620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417790. */
uint32_t lifted_score_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417840. */
uint32_t lifted_table_last_change(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417880. */
uint32_t lifted_f417880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417890. */
uint32_t lifted_f417890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4178a0. */
uint32_t lifted_f4178a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4178b0. */
uint32_t lifted_f4178b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4178c0. */
uint32_t lifted_f4178c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4178d0. */
uint32_t lifted_f4178d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417930. */
uint32_t lifted_table_byte_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417970. */
uint32_t lifted_table_pair_link(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4179d0. */
uint32_t lifted_quad_average(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417c80. */
uint32_t lifted_f417c80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417cf0. */
uint32_t lifted_table_grid_value(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417d10. */
uint32_t lifted_f417d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417d40. */
uint32_t lifted_f417d40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417d70. */
uint32_t lifted_f417d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417da0. */
uint32_t lifted_table_groups_used(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417df0. */
uint32_t lifted_table_row_used(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417e20. */
uint32_t lifted_table_bonus(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417e60. */
uint32_t lifted_table_random_empty(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417ed0. */
uint32_t lifted_table_random_empty_417ed0(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417f40. */
uint32_t lifted_matcher_reset(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417fc0. */
uint32_t lifted_table_column_count(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418000. */
uint32_t lifted_table_column_nth(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418050. */
uint32_t lifted_table_column_open(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4180a0. */
uint32_t lifted_table_column_open_nth(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418100. */
uint32_t lifted_f418100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418110. */
uint32_t lifted_f418110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418130. */
uint32_t lifted_f418130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418150. */
uint32_t lifted_compare_unsigned(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4182c0. */
uint32_t lifted_f4182c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4182f0. */
uint32_t lifted_resource_entry_call(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418550. */
uint32_t lifted_resource_entry_call_418550(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418570. */
uint32_t lifted_resource_entry_call_418570(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418760. */
uint32_t lifted_rtl_construct_derived_stream(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418820. */
uint32_t lifted_object_set_period(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418830. */
uint32_t lifted_actor_clock_to_period(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418840. */
uint32_t lifted_object_set_counter(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418850. */
uint32_t lifted_object_invoke_callback(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418870. */
uint32_t lifted_object_clear_counter(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418970. */
uint32_t lifted_f418970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418ae0. */
uint32_t lifted_f418ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418ce0. */
uint32_t lifted_f418ce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4192a0. */
uint32_t lifted_f4192a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4193b0. */
uint32_t lifted_f4193b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x419490. */
uint32_t lifted_guarded_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4194b0. */
uint32_t lifted_guarded_call_4194b0(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x419ef0. */
uint32_t lifted_f419ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x419f60. */
uint32_t lifted_f419f60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a010. */
uint32_t lifted_f41a010(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a240. */
uint32_t lifted_f41a240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a2b0. */
uint32_t lifted_f41a2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a2f0. */
uint32_t lifted_surface_blit_progress(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a4e0. */
uint32_t lifted_f41a4e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a520. */
uint32_t lifted_f41a520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a680. */
uint32_t lifted_f41a680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a6c0. */
uint32_t lifted_f41a6c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a700. */
uint32_t lifted_f41a700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a800. */
uint32_t lifted_f41a800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a930. */
uint32_t lifted_global_clear(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a940. */
uint32_t lifted_f41a940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a960. */
uint32_t lifted_f41a960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a9a0. */
uint32_t lifted_f41a9a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41aa20. */
uint32_t lifted_f41aa20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41aaa0. */
uint32_t lifted_f41aaa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41aaf0. */
uint32_t lifted_f41aaf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ab00. */
uint32_t lifted_f41ab00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ab30. */
uint32_t lifted_f41ab30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ab60. */
uint32_t lifted_f41ab60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ab90. */
uint32_t lifted_surface_blit_region(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41abe0. */
uint32_t lifted_f41abe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ac00. */
uint32_t lifted_f41ac00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ac20. */
uint32_t lifted_f41ac20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ac40. */
uint32_t lifted_f41ac40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ac70. */
uint32_t lifted_surface_clear_second(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ac80. */
uint32_t lifted_f41ac80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41aca0. */
uint32_t lifted_f41aca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41b5e0. */
uint32_t lifted_f41b5e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41b680. */
uint32_t lifted_f41b680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c020. */
uint32_t lifted_f41c020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c080. */
uint32_t lifted_f41c080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c0c0. */
uint32_t lifted_f41c0c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c0f0. */
uint32_t lifted_f41c0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c160. */
uint32_t lifted_f41c160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c1d0. */
uint32_t lifted_f41c1d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c240. */
uint32_t lifted_f41c240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c2b0. */
uint32_t lifted_f41c2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c390. */
uint32_t lifted_f41c390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c400. */
uint32_t lifted_f41c400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c6d0. */
uint32_t lifted_f41c6d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c740. */
uint32_t lifted_f41c740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c9e0. */
uint32_t lifted_f41c9e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41cbb0. */
uint32_t lifted_f41cbb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d410. */
uint32_t lifted_f41d410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d470. */
uint32_t lifted_f41d470(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d510. */
uint32_t lifted_f41d510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d5b0. */
uint32_t lifted_gate_dispatch_call(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d640. */
uint32_t lifted_f41d640(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d670. */
uint32_t lifted_frame_counter_update(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41dd60. */
uint32_t lifted_f41dd60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ddf0. */
uint32_t lifted_f41ddf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41dec0. */
uint32_t lifted_f41dec0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41df00. */
uint32_t lifted_f41df00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ede0. */
uint32_t lifted_f41ede0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41efe0. */
uint32_t lifted_f41efe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41f460. */
uint32_t lifted_f41f460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41f910. */
uint32_t lifted_f41f910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41fc70. */
uint32_t lifted_f41fc70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x421e80. */
uint32_t lifted_f421e80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x423d70. */
uint32_t lifted_f423d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424160. */
uint32_t lifted_f424160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424180. */
uint32_t lifted_f424180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4241d0. */
uint32_t lifted_f4241d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4241e0. */
uint32_t lifted_f4241e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4241f0. */
uint32_t lifted_f4241f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424200. */
uint32_t lifted_f424200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424760. */
uint32_t lifted_object_center_titled(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424790. */
uint32_t lifted_f424790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424890. */
uint32_t lifted_f424890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425260. */
uint32_t lifted_f425260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4253b0. */
uint32_t lifted_f4253b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4259d0. */
uint32_t lifted_f4259d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425a50. */
uint32_t lifted_f425a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425ae0. */
uint32_t lifted_f425ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425d30. */
uint32_t lifted_object_set_table(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425de0. */
uint32_t lifted_object_clear_slots(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425e00. */
uint32_t lifted_table_used_count(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425e20. */
uint32_t lifted_player_piece_initialize(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425ef0. */
uint32_t lifted_piece_init_from_kind(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425f40. */
uint32_t lifted_f425f40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4261b0. */
uint32_t lifted_ai_row_reach(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x427380. */
uint32_t lifted_ai_bomb_search(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x427c10. */
uint32_t lifted_ai_features(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x427e10. */
uint32_t lifted_ai_mode_flags(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x428110. */
uint32_t lifted_ai_compare_boards(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x428e70. */
uint32_t lifted_ai_choice_scores(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429000. */
uint32_t lifted_ai_find_best_slot(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4290a0. */
uint32_t lifted_ai_choose_piece_rotation(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4290c0. */
uint32_t lifted_settings_defaults(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429350. */
uint32_t lifted_object_destroy_c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4293e0. */
uint32_t lifted_saved_block_load(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429460. */
uint32_t lifted_f429460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429600. */
uint32_t lifted_f429600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429660. */
uint32_t lifted_object_address_plus_4(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429670. */
uint32_t lifted_marker_actor_construct(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429880. */
uint32_t lifted_piece_actor_construct_slots(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429d50. */
uint32_t lifted_choice_grid_apply(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429df0. */
uint32_t lifted_choice_grid_load_values(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429e80. */
uint32_t lifted_choice_grid_store_values(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429ee0. */
uint32_t lifted_choice_grid_pick_rows(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429fe0. */
uint32_t lifted_choice_grid_pick_cell(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a080. */
uint32_t lifted_choice_grid_pick_column(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a140. */
uint32_t lifted_choice_grid_mark(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a170. */
uint32_t lifted_choice_grid_cell_bytes(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a190. */
uint32_t lifted_choice_grid_available(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a1b0. */
uint32_t lifted_choice_grid_any_marked(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a310. */
uint32_t lifted_f42a310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a480. */
uint32_t lifted_piece_release_children(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a4a0. */
uint32_t lifted_f42a4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a540. */
uint32_t lifted_f42a540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a800. */
uint32_t lifted_piece_children_place(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a8b0. */
uint32_t lifted_f42a8b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a8e0. */
uint32_t lifted_f42a8e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a940. */
uint32_t lifted_piece_clear_offset_x(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a950. */
uint32_t lifted_piece_clear_offset_y(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a960. */
uint32_t lifted_f42a960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a970. */
uint32_t lifted_f42a970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a980. */
uint32_t lifted_piece_child_kinds(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a9d0. */
uint32_t lifted_f42a9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42aa20. */
uint32_t lifted_f42aa20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42aab0. */
uint32_t lifted_piece_actor_parent_construct(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42acf0. */
uint32_t lifted_piece_actor_construct_placed(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42af30. */
uint32_t lifted_piece_actor_layout(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42af80. */
uint32_t lifted_piece_actor_cycle(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b000. */
uint32_t lifted_player_preview_motion_start(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b050. */
uint32_t lifted_player_preview_below_limit(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b070. */
uint32_t lifted_player_preview_frame(const VertrixCalls *calls,
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

/* Original 0x42b150. */
uint32_t lifted_ui_player_preview_parent_construct(const VertrixCalls *calls,
                                                   const VertrixFactoryServices *services,
                                                   const VertrixGlobals *globals,
                                                   const LiftEntry *entry);

/* Original 0x42b290. */
uint32_t lifted_f42b290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b370. */
uint32_t lifted_ui_player_previews_construct(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b5c0. */
uint32_t lifted_piece_actor_construct_empty(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b6b0. */
uint32_t lifted_f42b6b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b920. */
uint32_t lifted_piece_set_variant(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b950. */
uint32_t lifted_piece_snap_to_left(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b990. */
uint32_t lifted_piece_snap_to_origin(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b9f0. */
uint32_t lifted_piece_arm_once(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ba40. */
uint32_t lifted_object_y_above_limit(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ba70. */
uint32_t lifted_f42ba70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42bab0. */
uint32_t lifted_f42bab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42bb00. */
uint32_t lifted_block_construct(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42bbd0. */
uint32_t lifted_block_create(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42e870. */
uint32_t lifted_board_construct(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42eb60. */
uint32_t lifted_board_release_active(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42eba0. */
uint32_t lifted_board_release_piece_children(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ebc0. */
uint32_t lifted_board_clear_collection(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ebe0. */
uint32_t lifted_board_clear_collection_42ebe0(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x42ec00. */
uint32_t lifted_board_clear_collection_42ec00(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x42ec20. */
uint32_t lifted_board_clear_collection_42ec20(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x42ec40. */
uint32_t lifted_board_clear_collection_42ec40(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x42ec60. */
uint32_t lifted_board_clear_collection_42ec60(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x42ec80. */
uint32_t lifted_board_collection_all_handler(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42eca0. */
uint32_t lifted_board_collection_all_handler_42eca0(const VertrixCalls *calls,
                                                    const VertrixFactoryServices *services,
                                                    const VertrixGlobals *globals,
                                                    const LiftEntry *entry);

/* Original 0x42ecc0. */
uint32_t lifted_board_collection_all_handler_42ecc0(const VertrixCalls *calls,
                                                    const VertrixFactoryServices *services,
                                                    const VertrixGlobals *globals,
                                                    const LiftEntry *entry);

/* Original 0x42ed40. */
uint32_t lifted_board_piece_all_handler(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ed70. */
uint32_t lifted_board_piece_all_handler_42ed70(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x42eda0. */
uint32_t lifted_board_collection_set_handler(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42edf0. */
uint32_t lifted_board_piece_all_handler_42edf0(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

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
uint32_t lifted_player_fill_bytes(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef80. */
uint32_t lifted_player_fill_bytes_42ef80(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f210. */
uint32_t lifted_board_mark_columns(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f280. */
uint32_t lifted_board_piece_store_negated(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f2b0. */
uint32_t lifted_board_piece_store_negated_always(const VertrixCalls *calls,
                                                 const VertrixFactoryServices *services,
                                                 const VertrixGlobals *globals,
                                                 const LiftEntry *entry);

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
uint32_t lifted_player_fill_bytes_42f7d0(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f7f0. */
uint32_t lifted_player_fill_bytes_42f7f0(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f810. */
uint32_t lifted_player_fill_bytes_42f810(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f830. */
uint32_t lifted_player_fill_bytes_42f830(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f850. */
uint32_t lifted_f42f850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f860. */
uint32_t lifted_f42f860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f870. */
uint32_t lifted_f42f870(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f880. */
uint32_t lifted_f42f880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f890. */
uint32_t lifted_f42f890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f8a0. */
uint32_t lifted_f42f8a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f8b0. */
uint32_t lifted_f42f8b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f8e0. */
uint32_t lifted_f42f8e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
#endif
