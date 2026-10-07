#ifndef VERTRIX_LIFTED_WHOLE_3_H
#define VERTRIX_LIFTED_WHOLE_3_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_SCENE_LOOKUP_PAIR_STACK = 92,
    LIFTED_OBJECT_FLIP_454_STACK = 72,
    LIFTED_OBJECT_FLIP_454_471E80_STACK = 72,
    LIFTED_OBJECT_SET_464_STACK = 64,
    LIFTED_OBJECT_GET_464_STACK = 64,
    LIFTED_OBJECT_GET_174_STACK = 64,
    LIFTED_OBJECT_GET_178_STACK = 64,
    LIFTED_F471EE0_STACK = 64,
    LIFTED_F472020_STACK = 128,
    LIFTED_F472090_STACK = 128,
    LIFTED_F472100_STACK = 128,
    LIFTED_F472170_STACK = 128,
    LIFTED_F4721E0_STACK = 128,
    LIFTED_F472250_STACK = 128,
    LIFTED_F4722C0_STACK = 128,
    LIFTED_F472330_STACK = 68,
    LIFTED_LIST_CLEAR_CALL_472350_STACK = 68,
    LIFTED_F472360_STACK = 80,
    LIFTED_F4723A0_STACK = 180,
    LIFTED_F472440_STACK = 72,
    LIFTED_F472460_STACK = 72,
    LIFTED_ACTOR_SPAWN_STACK = 128,
    LIFTED_F4724F0_STACK = 128,
    LIFTED_SPECIAL_ACTOR_SPAWN_STACK = 128,
    LIFTED_SCENE_CLEAR_MARKER_STACK = 72,
    LIFTED_BANNER_ACTOR_SPAWN_STACK = 136,
    LIFTED_F472AD0_STACK = 88,
    LIFTED_F472BD0_STACK = 84,
    LIFTED_OVERLAY_SPAWN_STACK = 132,
    LIFTED_SLOT_CREATE_CALL_STACK = 92,
    LIFTED_UI_PANEL_RELEASE_STACK = 80,
    LIFTED_F472DB0_STACK = 228,
    LIFTED_ICONS_BUILD_STACK = 288,
    LIFTED_F473490_STACK = 140,
    LIFTED_POINT_LIST_CONDITIONAL_STACK = 76,
    LIFTED_POINT_LIST_WHEN_ONE_STACK = 68,
    LIFTED_PAIR_WORDS_STACK = 148,
    LIFTED_PAIR_FLAGS_STACK = 144,
    LIFTED_F473960_STACK = 144,
    LIFTED_PAIR_SCAN_STACK = 144,
    LIFTED_RESOURCE_ENTRY_CALL_473CD0_STACK = 72,
    LIFTED_F473E60_STACK = 136,
    LIFTED_F474540_STACK = 72,
    LIFTED_PALETTE_TABLES_CYCLE_STACK = 72,
    LIFTED_RELEASE_PAIR_STACK = 112,
    LIFTED_SOUND_SIMPLE_CLEAR_STACK = 64,
    LIFTED_OBJECT_DESTROY_FLAGS_STACK = 136,
    LIFTED_SOUND_SIMPLE_SET_STACK = 64,
    LIFTED_FLAGS_CLEAR_STACK = 64,
    LIFTED_F4757E0_STACK = 72,
    LIFTED_FLAGS_GET_STACK = 64,
    LIFTED_FLAGS_DWORD_STACK = 64,
    LIFTED_FLAGS_DWORD_475820_STACK = 64,
    LIFTED_FLAGS_DWORD_475830_STACK = 64,
    LIFTED_F475840_STACK = 132,
    LIFTED_FLAGS_SET_STACK = 64,
    LIFTED_QUEUE_DRAIN_STACK = 84,
    LIFTED_OBJECT_LIST_INIT_STACK = 96,
    LIFTED_LIST_RESET_CALLS_STACK = 96,
    LIFTED_LIST_PUSH_CALL_STACK = 80,
    LIFTED_INPUT_REPEAT_START_STACK = 68,
    LIFTED_F475AF0_STACK = 64,
    LIFTED_FLAGS_IDLE_STACK = 64,
    LIFTED_F475B20_STACK = 104,
    LIFTED_F475B80_STACK = 104,
    LIFTED_F475BE0_STACK = 92,
    LIFTED_F475C30_STACK = 100,
    LIFTED_QUEUE_NEXT_STACK = 84,
    LIFTED_F475CD0_STACK = 84,
    LIFTED_F475D20_STACK = 88,
    LIFTED_F475D70_STACK = 68,
    LIFTED_OFFSET_CALL_STACK = 68,
    LIFTED_OBJECT_TRIPLE_STACK = 80,
    LIFTED_PROGRESS_SET_40_STACK = 64,
    LIFTED_F475DE0_STACK = 64,
    LIFTED_PROGRESS_DONE_STACK = 68,
    LIFTED_PROGRESS_QUOTIENT_STACK = 72,
    LIFTED_F475E30_STACK = 64,
    LIFTED_PROGRESS_SET_3C_STACK = 64,
    LIFTED_INPUT_REPEAT_TICK_STACK = 100,
    LIFTED_OBJECT_CONSTRUCT_F_STACK = 140,
    LIFTED_SLOT_CALL_STACK = 72,
    LIFTED_SLOT_TABLE_INIT_STACK = 76,
    LIFTED_INDEX_SWEEP_CALL_STACK = 80,
    LIFTED_INDEX_SWEEP_CALL_4760F0_STACK = 80,
    LIFTED_RECORD_CLEAR_FLAG_STACK = 72,
    LIFTED_RECORD_SET_FLAG_STACK = 72,
    LIFTED_F4761D0_STACK = 96,
    LIFTED_LIST_FIND_CALL_STACK = 80,
    LIFTED_F476280_STACK = 84,
    LIFTED_SLOT_SELECT_STACK = 80,
    LIFTED_F476320_STACK = 80,
    LIFTED_F476400_STACK = 80,
    LIFTED_F476440_STACK = 80,
    LIFTED_F476480_STACK = 72,
    LIFTED_SLOT_STORE_CALL_STACK = 76,
    LIFTED_F4764D0_STACK = 76,
    LIFTED_F476500_STACK = 76,
    LIFTED_SLOT_SEARCH_CALL_STACK = 84,
    LIFTED_TWO_CODES_CALL_STACK = 80,
    LIFTED_FIXED_CODES_CALL_STACK = 120,
    LIFTED_SOUND_KEY_IS_CONTROL_STACK = 64,
    LIFTED_SLOT_TABLE_RESET_STACK = 76,
    LIFTED_SOUND_CUE_BOTH_STACK = 96,
    LIFTED_RESOURCE_ENTRY_256_STACK = 108,
    LIFTED_SOUND_BANK_CLEAR_STACK = 72,
    LIFTED_SOUND_OPEN_KEYS_STACK = 72,
    LIFTED_SOUND_CHECK_PRIMARY_STACK = 84,
    LIFTED_SOUND_RELEASE_PRIMARY_STACK = 104,
    LIFTED_F476D20_STACK = 68,
    LIFTED_SOUND_CUE_OFFSET_STACK = 84,
    LIFTED_F476FE0_STACK = 84,
    LIFTED_SOUND_CUE_KEY_STACK = 84,
    LIFTED_F477040_STACK = 84,
    LIFTED_F477070_STACK = 84,
    LIFTED_F4770A0_STACK = 84,
    LIFTED_F4770D0_STACK = 84,
    LIFTED_F477100_STACK = 84,
    LIFTED_F477130_STACK = 84,
    LIFTED_F477160_STACK = 84,
    LIFTED_STREAM_INIT_STACK = 64,
    LIFTED_F4772F0_STACK = 72,
    LIFTED_F477320_STACK = 104,
    LIFTED_F477610_STACK = 96,
    LIFTED_FORMAT_DECIMAL_STACK = 100,
    LIFTED_TEXT_APPEND_CALL_STACK = 88,
    LIFTED_STREAM_SET_CLASS_STACK = 64,
    LIFTED_F477910_STACK = 64,
    LIFTED_F477930_STACK = 64,
    LIFTED_SOUND_SLIDER_CLEAR_STACK = 64,
    LIFTED_F477AF0_STACK = 72,
    LIFTED_CURSOR_CAPTURE_STACK = 108,
    LIFTED_F477D10_STACK = 104,
    LIFTED_OBJECT_CENTER_SETUP_STACK = 104,
    LIFTED_RECT_SET_STACK = 64,
    LIFTED_OBJECT_CENTER_PLACE_STACK = 84,
    LIFTED_OBJECT_RESET_CENTER_STACK = 88,
    LIFTED_F477F10_STACK = 220,
    LIFTED_RECT_COMMIT_STACK = 68,
    LIFTED_OBJECT_CLAMP_POSITION_STACK = 80,
    LIFTED_SOUND_CUE_POSITION_STACK = 88,
    LIFTED_F478520_STACK = 88,
    LIFTED_F478570_STACK = 92,
    LIFTED_F4785C0_STACK = 92,
    LIFTED_F478610_STACK = 92,
    LIFTED_F478660_STACK = 92,
    LIFTED_F4786B0_STACK = 92,
    LIFTED_F478700_STACK = 92,
    LIFTED_F478750_STACK = 92,
    LIFTED_F4787A0_STACK = 92,
    LIFTED_FLAGGED_CALL_STACK = 76,
    LIFTED_OBJECT_FILL_RAMP_STACK = 84,
    LIFTED_WHEN_FLAG_CALL_STACK = 72,
    LIFTED_LITERAL_COPY_CALL_STACK = 92,
    LIFTED_EVENT_KEY_INDEX_STACK = 64,
    LIFTED_F478D10_STACK = 100,
    LIFTED_F478D80_STACK = 76,
    LIFTED_EVENT_SCALE_FIELDS_STACK = 72,
    LIFTED_SURFACE_OFFSET_STACK = 68,
    LIFTED_F478ED0_STACK = 72,
    LIFTED_SURFACE_READ_STACK = 72,
    LIFTED_SURFACE_BOUNDS_STACK = 124,
    LIFTED_IMAGE_COLOR_KEY_STACK = 76,
    LIFTED_PIXEL_PACK_STACK = 72,
    LIFTED_SURFACE_CELL_ADDRESS_STACK = 64,
    LIFTED_SURFACE_FLIP_VERTICAL_STACK = 112,
    LIFTED_SURFACE_COPY_PIXEL_STACK = 80,
    LIFTED_NEIGHBOUR_CALLS_STACK = 108,
    LIFTED_F47BD80_STACK = 160,
    LIFTED_F47C250_STACK = 96,
    LIFTED_F47C3B0_STACK = 96,
    LIFTED_F47C710_STACK = 188,
    LIFTED_SURFACE_BLEND_STACK = 84,
    LIFTED_SURFACE_BLEND_MASKED_STACK = 88,
    LIFTED_SURFACE_DECIMATE_STACK = 88,
    LIFTED_SURFACE_BLIT_STACK = 104,
    LIFTED_SURFACE_BLIT_KEYED_STACK = 92,
    LIFTED_F47E780_STACK = 92,
    LIFTED_F47E7D0_STACK = 160,
    LIFTED_DWORD_SET_STACK = 64,
    LIFTED_OBJECT_DWORD_STACK = 64,
    LIFTED_F47E9B0_STACK = 132,
    LIFTED_DISPLAY_RELEASE_PAIR_STACK = 92,
    LIFTED_F47EAB0_STACK = 96,
    LIFTED_F47EB60_STACK = 96,
    LIFTED_OBJECT_ARM_30_STACK = 64,
    LIFTED_F47ED10_STACK = 72,
    LIFTED_F47ED30_STACK = 72,
    LIFTED_OBJECT_SET_DWORD_STACK = 64,
    LIFTED_OBJECT_SET_DWORD_47ED70_STACK = 64,
    LIFTED_OBJECT_SET_DWORD_47ED80_STACK = 64,
    LIFTED_OBJECT_SET_DWORD_47ED90_STACK = 64,
    LIFTED_F47EDA0_STACK = 772,
    LIFTED_F47EEB0_STACK = 180,
    LIFTED_F47F0F0_STACK = 112,
    LIFTED_DISPLAY_CHAIN_COUNT_STACK = 68,
    LIFTED_OBJECT_CHAIN_AT_STACK = 68,
    LIFTED_OBJECT_CHAIN_MEMBER_STACK = 68,
    LIFTED_F47F2F0_STACK = 96,
    LIFTED_DISPLAY_CHAIN_FIND_STACK = 84,
    LIFTED_F47F370_STACK = 92,
    LIFTED_F47F3D0_STACK = 100,
    LIFTED_F47F4B0_STACK = 252,
    LIFTED_F47F590_STACK = 116,
    LIFTED_F47F750_STACK = 80,
    LIFTED_F47F770_STACK = 76,
    LIFTED_F47F790_STACK = 656,
    LIFTED_F47F830_STACK = 656,
    LIFTED_OBJECT_SET_18_STACK = 64,
    LIFTED_F47F8F0_STACK = 64,
    LIFTED_CHECKED_CALLS_STACK = 84,
    LIFTED_F47F9E0_STACK = 88,
    LIFTED_F47FA20_STACK = 76,
    LIFTED_F47FA40_STACK = 116,
    LIFTED_F47FA90_STACK = 124,
    LIFTED_OBJECT_SET_TEXT_STACK = 96,
    LIFTED_F47FC10_STACK = 100,
    LIFTED_F47FC50_STACK = 108,
    LIFTED_F47FCE0_STACK = 68,
    LIFTED_DISPLAY_NOTIFY_STACK = 96,
    LIFTED_F47FE50_STACK = 96,
    LIFTED_F47FE80_STACK = 96,
    LIFTED_F480030_STACK = 104,
    LIFTED_OBJECT_DWORD_480070_STACK = 64,
    LIFTED_PALETTE_EXPAND_VGA_STACK = 80,
    LIFTED_F4808F0_STACK = 104,
    LIFTED_F480940_STACK = 92,
    LIFTED_F480990_STACK = 100,
    LIFTED_F480B20_STACK = 96,
    LIFTED_RLE_ENCODED_LENGTH_STACK = 76,
    LIFTED_F481460_STACK = 72,
    LIFTED_F4817A0_STACK = 136,
    LIFTED_OBJECT_SET_DWORD_481B20_STACK = 64,
    LIFTED_F481B30_STACK = 136,
    LIFTED_F481BC0_STACK = 76,
    LIFTED_PIXEL_CONVERT_STACK = 80,
    LIFTED_F481E10_STACK = 116,
    LIFTED_OBJECT_CREATE_WITH_CLASS_STACK = 128,
    LIFTED_OBJECT_DESTROY_B_STACK = 156,
    LIFTED_OBJECT_CLEAR_208_STACK = 64,
    LIFTED_EVENT_STACK_PUSH_STACK = 72,
    LIFTED_EVENT_STACK_POP_STACK = 76,
    LIFTED_F4823B0_STACK = 104,
    LIFTED_RANDOM_OBJECT_CONSTRUCT_STACK = 64,
    LIFTED_OBJECT_RESTART_RANGE_STACK = 68,
    LIFTED_F4826C0_STACK = 84,
    LIFTED_OBJECT_ALLOC_PAIR_STACK = 76,
    LIFTED_FORWARD_FIRST_DWORD_STACK = 68,
    LIFTED_RANDOM_INCLUSIVE_STACK = 72,
    LIFTED_F482770_STACK = 72,
    LIFTED_F4827C0_STACK = 100,
    LIFTED_F482860_STACK = 80,
    LIFTED_F4828A0_STACK = 84,
    LIFTED_F4828F0_STACK = 80,
    LIFTED_F482930_STACK = 100,
    LIFTED_F4829C0_STACK = 84,
    LIFTED_TABLE_ENTRY_CALL_STACK = 68,
    LIFTED_F482A60_STACK = 76,
    LIFTED_CALL_UNLESS_ZERO_STACK = 68,
    LIFTED_F482B40_STACK = 84,
    LIFTED_FLAG_PAIR_CALL_STACK = 76,
    LIFTED_F483060_STACK = 88,
    LIFTED_F4830F0_STACK = 76,
    LIFTED_F4831B0_STACK = 204,
    LIFTED_F483CE0_STACK = 92,
    LIFTED_OBJECT_SET_DWORD_484410_STACK = 64,
    LIFTED_F4844B0_STACK = 100,
    LIFTED_F484500_STACK = 80,
    LIFTED_F484530_STACK = 72,
    LIFTED_ROTATION_TABLES_LOAD_STACK = 116,
    LIFTED_ANGLE_FROM_RATIO_STACK = 68,
    LIFTED_FIXED_MULTIPLY_STACK = 68,
    LIFTED_FIXED_DIVIDE_STACK = 68,
    LIFTED_OBJECT_TABLE_516D34_STACK = 68,
    LIFTED_F484B30_STACK = 88,
    LIFTED_F4854A0_STACK = 120,
    LIFTED_SURFACE_PAIR_MAKE_STACK = 88,
    LIFTED_F485700_STACK = 476,
    LIFTED_F486D00_STACK = 132,
    LIFTED_F487020_STACK = 116,
    LIFTED_F487060_STACK = 88,
    LIFTED_OBJECT_RECORD_NEW_STACK = 76,
    LIFTED_FORWARD_CALL_STACK = 68,
    LIFTED_OBJECT_SURFACE_FORMAT_STACK = 80,
    LIFTED_F4872F0_STACK = 64,
    LIFTED_ARRAY_LIST_RELEASE_STACK = 104,
    LIFTED_LIST_NODE_ALLOC_STACK = 72,
    LIFTED_ARRAY_LIST_MAKE_STACK = 112,
    LIFTED_ARRAY_LIST_EACH_STACK = 84,
    LIFTED_OBJECT_ALLOC_ARRAYS_STACK = 80,
    LIFTED_F487750_STACK = 68,
    LIFTED_RESOURCE_TABLE_ENTRY_STACK = 72,
    LIFTED_F487790_STACK = 92,
    LIFTED_F4877D0_STACK = 72,
    LIFTED_OBJECT_DWORD_4877E0_STACK = 64,
    LIFTED_FRAME_RESOURCE_GET_STACK = 76,
    LIFTED_F487850_STACK = 64,
    LIFTED_F487860_STACK = 64,
    LIFTED_TABLE_OBJECT_CONSTRUCT_STACK = 68,
    LIFTED_F487920_STACK = 68,
    LIFTED_LIST_EMPTY_STACK = 64,
    LIFTED_F4879F0_STACK = 80,
    LIFTED_FORWARD_REGISTERS_487A10_STACK = 72,
    LIFTED_LIST_ITEM_STACK = 68,
    LIFTED_OBJECT_CONSTRUCT_G_STACK = 68,
    LIFTED_LIST_FIND_NAME_STACK = 92,
    LIFTED_TABLE_ITEM_STACK = 64,
    LIFTED_TABLE_ITEM_488040_STACK = 64,
    LIFTED_F488050_STACK = 88,
    LIFTED_F488510_STACK = 84,
    LIFTED_F488560_STACK = 88,
    LIFTED_PATH_LAST_SEPARATOR_STACK = 68,
    LIFTED_F4885C0_STACK = 84,
    LIFTED_F488620_STACK = 128,
    LIFTED_F4886F0_STACK = 76,
    LIFTED_F488850_STACK = 88,
    LIFTED_F4888C0_STACK = 100,
    LIFTED_PATH_IS_NETWORK_STACK = 68,
    LIFTED_F488960_STACK = 84,
    LIFTED_F4889A0_STACK = 108,
    LIFTED_F488A20_STACK = 96,
    LIFTED_OBJECT_DESTROY_E_STACK = 160,
    LIFTED_F489B20_STACK = 76,
    LIFTED_F489B40_STACK = 104,
    LIFTED_RTL_TEXT_EQUAL_STACK = 96,
    LIFTED_OBJECT_TABLE_517644_STACK = 68,
    LIFTED_F489FA0_STACK = 160,
    LIFTED_F48A2D0_STACK = 68,
    LIFTED_OBJECT_DWORD_48A2E0_STACK = 64,
    LIFTED_FORWARD_A2F0_STACK = 68,
    LIFTED_LIST_TEXT_LOOKUP_SLOT_STACK = 72,
    LIFTED_STREAM_SKIP_BLANK_STACK = 104,
    LIFTED_STREAM_SKIP_LINE_STACK = 88,
    LIFTED_STREAM_NEXT_DIRECTIVE_STACK = 100,
    LIFTED_OBJECT_UNKNOWN_INIT_STACK = 80,
    LIFTED_OBJECT_DESTROY_H_STACK = 140,
    LIFTED_F48A710_STACK = 192,
    LIFTED_RANGE_START_STACK = 72,
    LIFTED_OBJECT_UNKNOWN_RESET_STACK = 88,
    LIFTED_RANGE_DONE_STACK = 68,
    LIFTED_RANGE_BLOCK_SECOND_STACK = 64,
    LIFTED_OBJECT_DWORD_48AA80_STACK = 64,
    LIFTED_STREAM_SKIP_STACK = 72,
    LIFTED_RANGE_SPAN_STACK = 72,
    LIFTED_RANGE_SEEK_STACK = 68,
    LIFTED_OBJECT_SET_PAIR_STACK = 64,
    LIFTED_OBJECT_SET_INDEXED_WORD_STACK = 64,
    LIFTED_F48AC00_STACK = 64,
    LIFTED_F48B550_STACK = 140,
    LIFTED_F48B770_STACK = 88,
    LIFTED_F48B7E0_STACK = 292,
    LIFTED_F48BB80_STACK = 144,
    LIFTED_F48BCA0_STACK = 124,
    LIFTED_F48BDF0_STACK = 128,
    LIFTED_F48BE70_STACK = 124,
    LIFTED_F48C0F0_STACK = 140,
    LIFTED_OBJECT_NOTIFY_FIELD_STACK = 76,
    LIFTED_OBJECT_NOTIFY_GLOBAL_STACK = 76,
    LIFTED_OBJECT_NOTIFY_CHOICE_STACK = 76,
    LIFTED_OBJECT_NOTIFY_BYTE_STACK = 76,
    LIFTED_F48C310_STACK = 76,
    LIFTED_F48C330_STACK = 76,
    LIFTED_COPY_DWORD_STACK = 64,
    LIFTED_F48C390_STACK = 80,
    LIFTED_F48C3B0_STACK = 80,
    LIFTED_F48C3D0_STACK = 100,
    LIFTED_F48C460_STACK = 80,
    LIFTED_F48C480_STACK = 76,
    LIFTED_F48C610_STACK = 76,
    LIFTED_F48C680_STACK = 96,
    LIFTED_F48C970_STACK = 120,
    LIFTED_OBJECT_DELEGATE_STACK = 72,
    LIFTED_F48C9D0_STACK = 72,
    LIFTED_F48C9F0_STACK = 80,
    LIFTED_OBJECT_CLEAR_WITH_TABLE_STACK = 72,
    LIFTED_RECORD_COPY_STACK = 68,
    LIFTED_OBJECT_CLEAR_BLOCK_STACK = 64,
    LIFTED_OBJECT_CLEAR_WITH_ONES_STACK = 72,
    LIFTED_F48D520_STACK = 68,
    LIFTED_F48D530_STACK = 172,
    LIFTED_LIST_EMPTY_48D5F0_STACK = 64,
    LIFTED_F48D600_STACK = 80,
    LIFTED_FORWARD_REGISTERS_48D620_STACK = 72,
    LIFTED_LIST_ITEM_48D630_STACK = 68,
    LIFTED_F48D650_STACK = 100,
    LIFTED_FORWARD_CALL_48D6B0_STACK = 68,
    LIFTED_F48D6C0_STACK = 100,
    LIFTED_SURFACE_MASK32_STACK = 96,
    LIFTED_ACTOR_STORAGE_CONSTRUCT_STACK = 64,
    LIFTED_ACTOR_BASE_DESTROY_FULL_STACK = 136,
    LIFTED_F4AC1C0_STACK = 68,
    LIFTED_F4AC1E0_STACK = 64,
    LIFTED_ANIMATION_TICK_STACK = 104,
    LIFTED_ANIMATION_TICK_4AC250_STACK = 104,
    LIFTED_ANIMATION_TICK_4AC2B0_STACK = 104,
    LIFTED_ANIMATION_TICK_4AC310_STACK = 104,
    LIFTED_ACTOR_ADD_CC_STACK = 68,
    LIFTED_ACTOR_CLEAR_CC_STACK = 64,
    LIFTED_ACTOR_CC_REACHED_STACK = 68,
    LIFTED_ACTOR_STEP_QUOTIENT_STACK = 72,
    LIFTED_ACTOR_CONSUME_PROGRESS_STACK = 80,
    LIFTED_ACTOR_SET_D0_STEPS_STACK = 68,
    LIFTED_ACTOR_SET_D0_STACK = 64,
    LIFTED_ACTOR_REFRESH_COUNT_STACK = 80,
    LIFTED_ACTOR_SET_114_STACK = 64,
    LIFTED_ACTOR_SET_11C_STACK = 64,
    LIFTED_ACTOR_ADD_ELAPSED_STACK = 68,
    LIFTED_ACTOR_CLEAR_COUNTER_STACK = 64,
    LIFTED_ACTOR_CLOCK_REACHED_STACK = 68,
    LIFTED_ACTOR_COUNTER_QUOTIENT_STACK = 72,
    LIFTED_OBJECT_SCALE_CALL_STACK = 84,
    LIFTED_F4AC590_STACK = 68,
    LIFTED_ACTOR_COUNTER_WRAP_STACK = 80,
    LIFTED_ACTOR_ADD_ELAPSED_4AC600_STACK = 68,
    LIFTED_F4AC610_STACK = 64,
    LIFTED_ACTOR_COUNTER_PAIR_REACHED_STACK = 68,
    LIFTED_ACTOR_PROGRESS_QUOTIENT_STACK = 72,
    LIFTED_ACTOR_PROGRESS_WRAP_STACK = 80,
    LIFTED_ACTOR_RESET_FRAME_COUNTER_STACK = 64,
    LIFTED_ACTOR_SET_FRAME_INDEX_STACK = 64
};

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

/* Original 0x471ea0. */
uint32_t lifted_object_set_464(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f471ee0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472020. */
uint32_t lifted_f472020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472090. */
uint32_t lifted_f472090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472100. */
uint32_t lifted_f472100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472170. */
uint32_t lifted_f472170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4721e0. */
uint32_t lifted_f4721e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472250. */
uint32_t lifted_f472250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4722c0. */
uint32_t lifted_f4722c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472330. */
uint32_t lifted_f472330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472350. */
uint32_t lifted_list_clear_call_472350(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472360. */
uint32_t lifted_f472360(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4723a0. */
uint32_t lifted_f4723a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472440. */
uint32_t lifted_f472440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472460. */
uint32_t lifted_f472460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472470. */
uint32_t lifted_actor_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4724f0. */
uint32_t lifted_f4724f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472570. */
uint32_t lifted_special_actor_spawn(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4725f0. */
uint32_t lifted_scene_clear_marker(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472620. */
uint32_t lifted_banner_actor_spawn(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472ad0. */
uint32_t lifted_f472ad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472bd0. */
uint32_t lifted_f472bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472c10. */
uint32_t lifted_overlay_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472d00. */
uint32_t lifted_slot_create_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472d50. */
uint32_t lifted_ui_panel_release(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472db0. */
uint32_t lifted_f472db0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4731a0. */
uint32_t lifted_icons_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473490. */
uint32_t lifted_f473490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4735e0. */
uint32_t lifted_point_list_conditional(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473610. */
uint32_t lifted_point_list_when_one(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473630. */
uint32_t lifted_pair_words(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4737d0. */
uint32_t lifted_pair_flags(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473960. */
uint32_t lifted_f473960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473af0. */
uint32_t lifted_pair_scan(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473cd0. */
uint32_t lifted_resource_entry_call_473cd0(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473e60. */
uint32_t lifted_f473e60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x474540. */
uint32_t lifted_f474540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4754e0. */
uint32_t lifted_palette_tables_cycle(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475510. */
uint32_t lifted_release_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4756d0. */
uint32_t lifted_sound_simple_clear(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475700. */
uint32_t lifted_object_destroy_flags(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475790. */
uint32_t lifted_sound_simple_set(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4757b0. */
uint32_t lifted_flags_clear(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4757e0. */
uint32_t lifted_f4757e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475800. */
uint32_t lifted_flags_get(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475810. */
uint32_t lifted_flags_dword(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475820. */
uint32_t lifted_flags_dword_475820(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475830. */
uint32_t lifted_flags_dword_475830(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475840. */
uint32_t lifted_f475840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4759d0. */
uint32_t lifted_flags_set(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4759e0. */
uint32_t lifted_queue_drain(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475a20. */
uint32_t lifted_object_list_init(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475a80. */
uint32_t lifted_list_reset_calls(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475ab0. */
uint32_t lifted_list_push_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475ad0. */
uint32_t lifted_input_repeat_start(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475af0. */
uint32_t lifted_f475af0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475b00. */
uint32_t lifted_flags_idle(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475b20. */
uint32_t lifted_f475b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475b80. */
uint32_t lifted_f475b80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475be0. */
uint32_t lifted_f475be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475c30. */
uint32_t lifted_f475c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475c80. */
uint32_t lifted_queue_next(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475cd0. */
uint32_t lifted_f475cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475d20. */
uint32_t lifted_f475d20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475d70. */
uint32_t lifted_f475d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475d90. */
uint32_t lifted_offset_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475da0. */
uint32_t lifted_object_triple(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475dd0. */
uint32_t lifted_progress_set_40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475de0. */
uint32_t lifted_f475de0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475df0. */
uint32_t lifted_progress_done(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475e10. */
uint32_t lifted_progress_quotient(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475e30. */
uint32_t lifted_f475e30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475e40. */
uint32_t lifted_progress_set_3c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475e50. */
uint32_t lifted_input_repeat_tick(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475ec0. */
uint32_t lifted_object_construct_f(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476010. */
uint32_t lifted_slot_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476090. */
uint32_t lifted_slot_table_init(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4760c0. */
uint32_t lifted_index_sweep_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4760f0. */
uint32_t lifted_index_sweep_call_4760f0(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476120. */
uint32_t lifted_record_clear_flag(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476140. */
uint32_t lifted_record_set_flag(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4761d0. */
uint32_t lifted_f4761d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476260. */
uint32_t lifted_list_find_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476280. */
uint32_t lifted_f476280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4762e0. */
uint32_t lifted_slot_select(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476320. */
uint32_t lifted_f476320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476400. */
uint32_t lifted_f476400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476440. */
uint32_t lifted_f476440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476480. */
uint32_t lifted_f476480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4764a0. */
uint32_t lifted_slot_store_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4764d0. */
uint32_t lifted_f4764d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476500. */
uint32_t lifted_f476500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476530. */
uint32_t lifted_slot_search_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476590. */
uint32_t lifted_two_codes_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4765b0. */
uint32_t lifted_fixed_codes_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476650. */
uint32_t lifted_sound_key_is_control(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4766f0. */
uint32_t lifted_slot_table_reset(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476720. */
uint32_t lifted_sound_cue_both(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476810. */
uint32_t lifted_resource_entry_256(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4768e0. */
uint32_t lifted_sound_bank_clear(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476a00. */
uint32_t lifted_sound_open_keys(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476c80. */
uint32_t lifted_sound_check_primary(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476cc0. */
uint32_t lifted_sound_release_primary(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476d20. */
uint32_t lifted_f476d20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476fb0. */
uint32_t lifted_sound_cue_offset(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476fe0. */
uint32_t lifted_f476fe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477010. */
uint32_t lifted_sound_cue_key(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477040. */
uint32_t lifted_f477040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477070. */
uint32_t lifted_f477070(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4770a0. */
uint32_t lifted_f4770a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4770d0. */
uint32_t lifted_f4770d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477100. */
uint32_t lifted_f477100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477130. */
uint32_t lifted_f477130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477160. */
uint32_t lifted_f477160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477240. */
uint32_t lifted_stream_init(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4772f0. */
uint32_t lifted_f4772f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477320. */
uint32_t lifted_f477320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477610. */
uint32_t lifted_f477610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4776a0. */
uint32_t lifted_format_decimal(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4777c0. */
uint32_t lifted_text_append_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477870. */
uint32_t lifted_stream_set_class(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477910. */
uint32_t lifted_f477910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477930. */
uint32_t lifted_f477930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4779c0. */
uint32_t lifted_sound_slider_clear(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477af0. */
uint32_t lifted_f477af0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477c30. */
uint32_t lifted_cursor_capture(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477d10. */
uint32_t lifted_f477d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477d70. */
uint32_t lifted_object_center_setup(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477e10. */
uint32_t lifted_rect_set(const VertrixCalls *calls, const VertrixFactoryServices *services,
                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477e30. */
uint32_t lifted_object_center_place(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477ed0. */
uint32_t lifted_object_reset_center(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477f10. */
uint32_t lifted_f477f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478460. */
uint32_t lifted_rect_commit(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478480. */
uint32_t lifted_object_clamp_position(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4784d0. */
uint32_t lifted_sound_cue_position(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478520. */
uint32_t lifted_f478520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478570. */
uint32_t lifted_f478570(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4785c0. */
uint32_t lifted_f4785c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478610. */
uint32_t lifted_f478610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478660. */
uint32_t lifted_f478660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4786b0. */
uint32_t lifted_f4786b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478700. */
uint32_t lifted_f478700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478750. */
uint32_t lifted_f478750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4787a0. */
uint32_t lifted_f4787a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478b40. */
uint32_t lifted_flagged_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478b70. */
uint32_t lifted_object_fill_ramp(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478bd0. */
uint32_t lifted_when_flag_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478c90. */
uint32_t lifted_literal_copy_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478cd0. */
uint32_t lifted_event_key_index(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478d10. */
uint32_t lifted_f478d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478d80. */
uint32_t lifted_f478d80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478da0. */
uint32_t lifted_event_scale_fields(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478eb0. */
uint32_t lifted_surface_offset(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478ed0. */
uint32_t lifted_f478ed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478f10. */
uint32_t lifted_surface_read(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4792d0. */
uint32_t lifted_surface_bounds(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4799f0. */
uint32_t lifted_image_color_key(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479a40. */
uint32_t lifted_pixel_pack(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479b30. */
uint32_t lifted_surface_cell_address(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479b50. */
uint32_t lifted_surface_flip_vertical(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479d70. */
uint32_t lifted_surface_copy_pixel(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479df0. */
uint32_t lifted_neighbour_calls(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47bd80. */
uint32_t lifted_f47bd80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47c250. */
uint32_t lifted_f47c250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47c3b0. */
uint32_t lifted_f47c3b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47c710. */
uint32_t lifted_f47c710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47c930. */
uint32_t lifted_surface_blend(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47cb40. */
uint32_t lifted_surface_blend_masked(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47cd60. */
uint32_t lifted_surface_decimate(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ce10. */
uint32_t lifted_surface_blit(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e200. */
uint32_t lifted_surface_blit_keyed(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e780. */
uint32_t lifted_f47e780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e7d0. */
uint32_t lifted_f47e7d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e990. */
uint32_t lifted_dword_set(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e9a0. */
uint32_t lifted_object_dword(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e9b0. */
uint32_t lifted_f47e9b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ea20. */
uint32_t lifted_display_release_pair(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47eab0. */
uint32_t lifted_f47eab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47eb60. */
uint32_t lifted_f47eb60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ecf0. */
uint32_t lifted_object_arm_30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed10. */
uint32_t lifted_f47ed10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed30. */
uint32_t lifted_f47ed30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed60. */
uint32_t lifted_object_set_dword(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed70. */
uint32_t lifted_object_set_dword_47ed70(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed80. */
uint32_t lifted_object_set_dword_47ed80(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed90. */
uint32_t lifted_object_set_dword_47ed90(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47eda0. */
uint32_t lifted_f47eda0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47eeb0. */
uint32_t lifted_f47eeb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f0f0. */
uint32_t lifted_f47f0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f160. */
uint32_t lifted_display_chain_count(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f190. */
uint32_t lifted_object_chain_at(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f260. */
uint32_t lifted_object_chain_member(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f2f0. */
uint32_t lifted_f47f2f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f320. */
uint32_t lifted_display_chain_find(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f370. */
uint32_t lifted_f47f370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f3d0. */
uint32_t lifted_f47f3d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f4b0. */
uint32_t lifted_f47f4b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f590. */
uint32_t lifted_f47f590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f750. */
uint32_t lifted_f47f750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f770. */
uint32_t lifted_f47f770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f790. */
uint32_t lifted_f47f790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f830. */
uint32_t lifted_f47f830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f8e0. */
uint32_t lifted_object_set_18(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f8f0. */
uint32_t lifted_f47f8f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f9b0. */
uint32_t lifted_checked_calls(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f9e0. */
uint32_t lifted_f47f9e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47fa20. */
uint32_t lifted_f47fa20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47fa40. */
uint32_t lifted_f47fa40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47fa90. */
uint32_t lifted_f47fa90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47faf0. */
uint32_t lifted_object_set_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47fc10. */
uint32_t lifted_f47fc10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47fc50. */
uint32_t lifted_f47fc50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47fce0. */
uint32_t lifted_f47fce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47fe20. */
uint32_t lifted_display_notify(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47fe50. */
uint32_t lifted_f47fe50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47fe80. */
uint32_t lifted_f47fe80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480030. */
uint32_t lifted_f480030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480070. */
uint32_t lifted_object_dword_480070(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480890. */
uint32_t lifted_palette_expand_vga(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4808f0. */
uint32_t lifted_f4808f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480940. */
uint32_t lifted_f480940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480990. */
uint32_t lifted_f480990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480b20. */
uint32_t lifted_f480b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481420. */
uint32_t lifted_rle_encoded_length(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481460. */
uint32_t lifted_f481460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4817a0. */
uint32_t lifted_f4817a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481b20. */
uint32_t lifted_object_set_dword_481b20(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481b30. */
uint32_t lifted_f481b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481bc0. */
uint32_t lifted_f481bc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481d90. */
uint32_t lifted_pixel_convert(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481e10. */
uint32_t lifted_f481e10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481f30. */
uint32_t lifted_object_create_with_class(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481fb0. */
uint32_t lifted_object_destroy_b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482050. */
uint32_t lifted_object_clear_208(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482060. */
uint32_t lifted_event_stack_push(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482110. */
uint32_t lifted_event_stack_pop(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4823b0. */
uint32_t lifted_f4823b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482480. */
uint32_t lifted_random_object_construct(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482540. */
uint32_t lifted_object_restart_range(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4826c0. */
uint32_t lifted_f4826c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482720. */
uint32_t lifted_object_alloc_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482740. */
uint32_t lifted_forward_first_dword(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482750. */
uint32_t lifted_random_inclusive(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482770. */
uint32_t lifted_f482770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4827c0. */
uint32_t lifted_f4827c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482860. */
uint32_t lifted_f482860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4828a0. */
uint32_t lifted_f4828a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4828f0. */
uint32_t lifted_f4828f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482930. */
uint32_t lifted_f482930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4829c0. */
uint32_t lifted_f4829c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482a40. */
uint32_t lifted_table_entry_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482a60. */
uint32_t lifted_f482a60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482b30. */
uint32_t lifted_call_unless_zero(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482b40. */
uint32_t lifted_f482b40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482bb0. */
uint32_t lifted_flag_pair_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x483060. */
uint32_t lifted_f483060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4830f0. */
uint32_t lifted_f4830f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4831b0. */
uint32_t lifted_f4831b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x483ce0. */
uint32_t lifted_f483ce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484410. */
uint32_t lifted_object_set_dword_484410(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4844b0. */
uint32_t lifted_f4844b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484500. */
uint32_t lifted_f484500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484530. */
uint32_t lifted_f484530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484550. */
uint32_t lifted_rotation_tables_load(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4845d0. */
uint32_t lifted_angle_from_ratio(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4849e0. */
uint32_t lifted_fixed_multiply(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4849f0. */
uint32_t lifted_fixed_divide(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484a60. */
uint32_t lifted_object_table_516d34(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484b30. */
uint32_t lifted_f484b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4854a0. */
uint32_t lifted_f4854a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4856a0. */
uint32_t lifted_surface_pair_make(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x485700. */
uint32_t lifted_f485700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x486d00. */
uint32_t lifted_f486d00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487020. */
uint32_t lifted_f487020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487060. */
uint32_t lifted_f487060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487280. */
uint32_t lifted_object_record_new(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4872b0. */
uint32_t lifted_forward_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4872c0. */
uint32_t lifted_object_surface_format(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4872f0. */
uint32_t lifted_f4872f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4874f0. */
uint32_t lifted_array_list_release(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487640. */
uint32_t lifted_list_node_alloc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487660. */
uint32_t lifted_array_list_make(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4876c0. */
uint32_t lifted_array_list_each(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487710. */
uint32_t lifted_object_alloc_arrays(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487750. */
uint32_t lifted_f487750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487770. */
uint32_t lifted_resource_table_entry(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487790. */
uint32_t lifted_f487790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4877d0. */
uint32_t lifted_f4877d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4877e0. */
uint32_t lifted_object_dword_4877e0(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4877f0. */
uint32_t lifted_frame_resource_get(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487850. */
uint32_t lifted_f487850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487860. */
uint32_t lifted_f487860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487870. */
uint32_t lifted_table_object_construct(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487920. */
uint32_t lifted_f487920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4879e0. */
uint32_t lifted_list_empty(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4879f0. */
uint32_t lifted_f4879f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487a10. */
uint32_t lifted_forward_registers_487a10(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487a20. */
uint32_t lifted_list_item(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487b00. */
uint32_t lifted_object_construct_g(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487fd0. */
uint32_t lifted_list_find_name(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488030. */
uint32_t lifted_table_item(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488040. */
uint32_t lifted_table_item_488040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488050. */
uint32_t lifted_f488050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488510. */
uint32_t lifted_f488510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488560. */
uint32_t lifted_f488560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4885a0. */
uint32_t lifted_path_last_separator(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4885c0. */
uint32_t lifted_f4885c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488620. */
uint32_t lifted_f488620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4886f0. */
uint32_t lifted_f4886f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488850. */
uint32_t lifted_f488850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4888c0. */
uint32_t lifted_f4888c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488940. */
uint32_t lifted_path_is_network(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488960. */
uint32_t lifted_f488960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4889a0. */
uint32_t lifted_f4889a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488a20. */
uint32_t lifted_f488a20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488b90. */
uint32_t lifted_object_destroy_e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489b20. */
uint32_t lifted_f489b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489b40. */
uint32_t lifted_f489b40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489d00. */
uint32_t lifted_rtl_text_equal(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489f90. */
uint32_t lifted_object_table_517644(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489fa0. */
uint32_t lifted_f489fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a2d0. */
uint32_t lifted_f48a2d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a2e0. */
uint32_t lifted_object_dword_48a2e0(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a2f0. */
uint32_t lifted_forward_a2f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a300. */
uint32_t lifted_list_text_lookup_slot(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a310. */
uint32_t lifted_stream_skip_blank(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a380. */
uint32_t lifted_stream_skip_line(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a420. */
uint32_t lifted_stream_next_directive(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a620. */
uint32_t lifted_object_unknown_init(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a670. */
uint32_t lifted_object_destroy_h(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a710. */
uint32_t lifted_f48a710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a8a0. */
uint32_t lifted_range_start(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a8c0. */
uint32_t lifted_object_unknown_reset(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a910. */
uint32_t lifted_range_done(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48aa70. */
uint32_t lifted_range_block_second(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48aa80. */
uint32_t lifted_object_dword_48aa80(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48aa90. */
uint32_t lifted_stream_skip(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48aad0. */
uint32_t lifted_range_span(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48aaf0. */
uint32_t lifted_range_seek(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48abe0. */
uint32_t lifted_object_set_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48abf0. */
uint32_t lifted_object_set_indexed_word(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48ac00. */
uint32_t lifted_f48ac00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48b550. */
uint32_t lifted_f48b550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48b770. */
uint32_t lifted_f48b770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48b7e0. */
uint32_t lifted_f48b7e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48bb80. */
uint32_t lifted_f48bb80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48bca0. */
uint32_t lifted_f48bca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48bdf0. */
uint32_t lifted_f48bdf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48be70. */
uint32_t lifted_f48be70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c0f0. */
uint32_t lifted_f48c0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c260. */
uint32_t lifted_object_notify_field(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c280. */
uint32_t lifted_object_notify_global(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c2b0. */
uint32_t lifted_object_notify_choice(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c2e0. */
uint32_t lifted_object_notify_byte(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c310. */
uint32_t lifted_f48c310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c330. */
uint32_t lifted_f48c330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c370. */
uint32_t lifted_copy_dword(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c390. */
uint32_t lifted_f48c390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c3b0. */
uint32_t lifted_f48c3b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c3d0. */
uint32_t lifted_f48c3d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c460. */
uint32_t lifted_f48c460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c480. */
uint32_t lifted_f48c480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c610. */
uint32_t lifted_f48c610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c680. */
uint32_t lifted_f48c680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c970. */
uint32_t lifted_f48c970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c9b0. */
uint32_t lifted_object_delegate(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c9d0. */
uint32_t lifted_f48c9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c9f0. */
uint32_t lifted_f48c9f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d330. */
uint32_t lifted_object_clear_with_table(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d3e0. */
uint32_t lifted_record_copy(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d480. */
uint32_t lifted_object_clear_block(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d500. */
uint32_t lifted_object_clear_with_ones(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d520. */
uint32_t lifted_f48d520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d530. */
uint32_t lifted_f48d530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d5f0. */
uint32_t lifted_list_empty_48d5f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d600. */
uint32_t lifted_f48d600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d620. */
uint32_t lifted_forward_registers_48d620(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d630. */
uint32_t lifted_list_item_48d630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d650. */
uint32_t lifted_f48d650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d6b0. */
uint32_t lifted_forward_call_48d6b0(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d6c0. */
uint32_t lifted_f48d6c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ab200. */
uint32_t lifted_surface_mask32(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4abd70. */
uint32_t lifted_actor_storage_construct(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac130. */
uint32_t lifted_actor_base_destroy_full(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac1c0. */
uint32_t lifted_f4ac1c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac1e0. */
uint32_t lifted_f4ac1e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac1f0. */
uint32_t lifted_animation_tick(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac250. */
uint32_t lifted_animation_tick_4ac250(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac2b0. */
uint32_t lifted_animation_tick_4ac2b0(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac310. */
uint32_t lifted_animation_tick_4ac310(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac370. */
uint32_t lifted_actor_add_cc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac380. */
uint32_t lifted_actor_clear_cc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac390. */
uint32_t lifted_actor_cc_reached(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac3b0. */
uint32_t lifted_actor_step_quotient(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac420. */
uint32_t lifted_actor_consume_progress(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac470. */
uint32_t lifted_actor_set_d0_steps(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac490. */
uint32_t lifted_actor_set_d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac4a0. */
uint32_t lifted_actor_refresh_count(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac4e0. */
uint32_t lifted_actor_set_114(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac4f0. */
uint32_t lifted_actor_set_11c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac500. */
uint32_t lifted_actor_add_elapsed(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac510. */
uint32_t lifted_actor_clear_counter(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac520. */
uint32_t lifted_actor_clock_reached(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac540. */
uint32_t lifted_actor_counter_quotient(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac560. */
uint32_t lifted_object_scale_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac590. */
uint32_t lifted_f4ac590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac5b0. */
uint32_t lifted_actor_counter_wrap(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac600. */
uint32_t lifted_actor_add_elapsed_4ac600(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac610. */
uint32_t lifted_f4ac610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac620. */
uint32_t lifted_actor_counter_pair_reached(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac640. */
uint32_t lifted_actor_progress_quotient(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac6b0. */
uint32_t lifted_actor_progress_wrap(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac700. */
uint32_t lifted_actor_reset_frame_counter(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac710. */
uint32_t lifted_actor_set_frame_index(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);
#endif
