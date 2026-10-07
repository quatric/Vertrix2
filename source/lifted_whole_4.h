#ifndef VERTRIX_LIFTED_WHOLE_4_H
#define VERTRIX_LIFTED_WHOLE_4_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_ACTOR_RESET_FRAME_COUNTER_STACK = 64,
    LIFTED_ACTOR_SET_FRAME_INDEX_STACK = 64,
    LIFTED_BLOCK_RESOURCE_LAST_STACK = 72,
    LIFTED_ACTOR_NEXT_FRAME_COUNTER_STACK = 64,
    LIFTED_ACTOR_PREVIOUS_FRAME_COUNTER_STACK = 64,
    LIFTED_ACTOR_FRAME_IS_COUNT_STACK = 72,
    LIFTED_ACTOR_FRAME_IS_LAST_STACK = 72,
    LIFTED_ACTOR_FRAME_COUNTER_IS_ZERO_STACK = 64,
    LIFTED_ACTOR_SET_PERIOD_STEPS_STACK = 68,
    LIFTED_ACTOR_SET_PERIOD_STACK = 64,
    LIFTED_ACTOR_RANDOMIZE_PERIOD_STACK = 84,
    LIFTED_ACTOR_RANDOMIZE_D0_STACK = 84,
    LIFTED_ACTOR_SET_E0_STACK = 64,
    LIFTED_ACTOR_LOOKUP_IMAGE_STACK = 76,
    LIFTED_ACTOR_ATTACH_RESOURCE_STACK = 76,
    LIFTED_ACTOR_SET_HANDLER_STACK = 64,
    LIFTED_ACTOR_GET_HANDLER_STACK = 64,
    LIFTED_ACTOR_SET_EC_STACK = 64,
    LIFTED_ACTOR_HANDLER_FROM_EC_STACK = 68,
    LIFTED_ACTOR_SET_F0_STACK = 64,
    LIFTED_ACTOR_HANDLER_FROM_F0_STACK = 68,
    LIFTED_ACTOR_SET_B4_STACK = 64,
    LIFTED_ACTOR_GET_B4_STACK = 64,
    LIFTED_STEP_TOWARD_STACK = 64,
    LIFTED_WORD_TRANSITION_STACK = 80,
    LIFTED_WORD_TRANSITION_4ACAB0_STACK = 80,
    LIFTED_ACTOR_STEP_WORD_STACK = 80,
    LIFTED_BYTE_TRANSITION_STACK = 80,
    LIFTED_DWORD_TRANSITION_STACK = 76,
    LIFTED_F4ACCC0_STACK = 80,
    LIFTED_F4ACD30_STACK = 80,
    LIFTED_ACTOR_TURN_TOWARD_STACK = 84,
    LIFTED_ROTATION_ADVANCE_STACK = 80,
    LIFTED_ACTOR_SPIN_STACK = 80,
    LIFTED_ACTOR_POLAR_OFFSET_STACK = 80,
    LIFTED_ACTOR_POLAR_OFFSET_SECOND_STACK = 80,
    LIFTED_ACTOR_ORBIT_POINT_STACK = 92,
    LIFTED_F4AD2C0_STACK = 100,
    LIFTED_ACTOR_CHAIN_ORBIT_POINT_STACK = 108,
    LIFTED_ACTOR_SET_WORDS_2A_STACK = 64,
    LIFTED_WORD_TRANSITION_4AD530_STACK = 80,
    LIFTED_BYTE_TRANSITION_4AD580_STACK = 80,
    LIFTED_WORD_TRANSITION_4AD5E0_STACK = 80,
    LIFTED_WORD_TRANSITION_4AD630_STACK = 80,
    LIFTED_ACTOR_DWORD_TRANSITION_STACK = 76,
    LIFTED_OBJECT_STEP_DWORD_STACK = 76,
    LIFTED_ACTOR_DWORD_TRANSITION_4AD790_STACK = 76,
    LIFTED_F4AD870_STACK = 92,
    LIFTED_F4ADE20_STACK = 80,
    LIFTED_ACTOR_CHAIN_WALK_STACK = 80,
    LIFTED_ACTOR_INITIALIZE_STACK = 64,
    LIFTED_F4ADF70_STACK = 64,
    LIFTED_F4ADFA0_STACK = 64,
    LIFTED_ACTOR_REFRESH_VALUE_FULL_STACK = 64,
    LIFTED_ACTOR_REFRESH_ARM_FULL_STACK = 68,
    LIFTED_ACTOR_DRAW_SLOT_FULL_STACK = 120,
    LIFTED_F4AE110_STACK = 64,
    LIFTED_ACTOR_CHAIN_WALK_4AE140_STACK = 68,
    LIFTED_F4AE150_STACK = 76,
    LIFTED_F4AE1F0_STACK = 68,
    LIFTED_RENDER_PREPARE_STACK = 80,
    LIFTED_RENDER_RULE_STACK = 80,
    LIFTED_RENDER_FLAGS_STACK = 72,
    LIFTED_F4B0B70_STACK = 136,
    LIFTED_RESOURCE_MEASURE_STACK = 96,
    LIFTED_F4B17B0_STACK = 76,
    LIFTED_F4B1FA0_STACK = 232,
    LIFTED_OBJECT_ZERO_DWORDS_STACK = 68,
    LIFTED_OBJECT_RELEASE_SLOTS_FULL_STACK = 80,
    LIFTED_F4B2300_STACK = 72,
    LIFTED_F4B2340_STACK = 76,
    LIFTED_F4B2380_STACK = 80,
    LIFTED_F4B23C0_STACK = 76,
    LIFTED_F4B3100_STACK = 68,
    LIFTED_F4B3340_STACK = 80,
    LIFTED_RETURN_UNCHANGED_4B3360_STACK = 64,
    LIFTED_F4B34D0_STACK = 68,
    LIFTED_F4B3500_STACK = 156,
    LIFTED_F4B3A00_STACK = 212,
    LIFTED_F4B3CE0_STACK = 112,
    LIFTED_F4B3D60_STACK = 112,
    LIFTED_F4B3FB0_STACK = 68,
    LIFTED_OBJECT_DWORD_4B4500_STACK = 64,
    LIFTED_OBJECT_CURSOR_ROW_STACK = 72,
    LIFTED_OBJECT_TEXT_ROW_STACK = 72,
    LIFTED_OBJECT_TEXT_NEAREST_STACK = 96,
    LIFTED_OBJECT_TEXT_SEEK_STACK = 72,
    LIFTED_F4B4CF0_STACK = 252,
    LIFTED_OBJECT_SET_PAIR_4B4FA0_STACK = 64,
    LIFTED_F4B5050_STACK = 112,
    LIFTED_F4B50D0_STACK = 112,
    LIFTED_F4B5150_STACK = 128,
    LIFTED_ACTOR_CONSTRUCT_518174_STACK = 68,
    LIFTED_OBJECT_DESTROY_CALL_STACK = 156,
    LIFTED_ACTOR_SET_BOX_STACK = 68,
    LIFTED_OBJECT_SLOT_PRESENT_STACK = 84,
    LIFTED_F4B5550_STACK = 68,
    LIFTED_F4B5560_STACK = 76,
    LIFTED_F4B5580_STACK = 136,
    LIFTED_F4B5630_STACK = 160,
    LIFTED_F4B5700_STACK = 208,
    LIFTED_F4B58A0_STACK = 196,
    LIFTED_OBJECT_START_5182C4_STACK = 68,
    LIFTED_OBJECT_SLOT_PRESENT_UNOWNED_STACK = 84,
    LIFTED_F4B5DB0_STACK = 68,
    LIFTED_OBJECT_DESTROY_A_STACK = 168,
    LIFTED_OWNED_OBJECT_LIST_APPEND_STACK = 80,
    LIFTED_OBJECT_LIST_FIND_STACK = 72,
    LIFTED_F4B5FC0_STACK = 100,
    LIFTED_OBJECT_RELEASE_ITEMS_STACK = 88,
    LIFTED_F4B6070_STACK = 96,
    LIFTED_F4B60C0_STACK = 100,
    LIFTED_F4B6120_STACK = 96,
    LIFTED_F4B6170_STACK = 96,
    LIFTED_F4B61C0_STACK = 88,
    LIFTED_OBJECT_LIST_UPDATE_STACK = 88,
    LIFTED_OBJECT_DESTROY_D_STACK = 160,
    LIFTED_TIMER_RESET_STACK = 64,
    LIFTED_OBJECT_SET_WORD_STACK = 64,
    LIFTED_OBJECT_SET_WORD_4B6550_STACK = 64,
    LIFTED_TIMER_RUNNING_STACK = 68,
    LIFTED_OBJECT_WORD_STACK = 64,
    LIFTED_OBJECT_WORD_4B65A0_STACK = 64,
    LIFTED_OBJECT_SET_DWORD_4B65B0_STACK = 64,
    LIFTED_OBJECT_SET_FOUR_WORDS_STACK = 64,
    LIFTED_OBJECT_CONTAINS_STACK = 72,
    LIFTED_OBJECT_SLOT_PRESENT_4B6700_STACK = 84,
    LIFTED_F4B6800_STACK = 140,
    LIFTED_FORWARD_REGISTERS_4B6890_STACK = 68,
    LIFTED_F4B6EA0_STACK = 68,
    LIFTED_F4B7020_STACK = 100,
    LIFTED_F4B7600_STACK = 68,
    LIFTED_OBJECT_TABLE_NEW_4B78D0_STACK = 68,
    LIFTED_F4B78E0_STACK = 172,
    LIFTED_F4B7B00_STACK = 100,
    LIFTED_F4B7B80_STACK = 104,
    LIFTED_F4B7C90_STACK = 96,
    LIFTED_TIME_SAMPLE_STACK = 76,
    LIFTED_F4B7D70_STACK = 76,
    LIFTED_F4B7DB0_STACK = 84,
    LIFTED_TWO_STEP_CALL_STACK = 80,
    LIFTED_F4B826F_STACK = 436,
    LIFTED_RECORD_PREFIX_SUM_STACK = 108,
    LIFTED_F4B9050_STACK = 120,
    LIFTED_F4B9170_STACK = 80,
    LIFTED_F4B91B0_STACK = 76,
    LIFTED_F4B91E0_STACK = 80,
    LIFTED_F4B9200_STACK = 80,
    LIFTED_F4B9220_STACK = 100,
    LIFTED_F4B9310_STACK = 68,
    LIFTED_F4B9330_STACK = 92,
    LIFTED_F4B9540_STACK = 88,
    LIFTED_F4B95E0_STACK = 100,
    LIFTED_F4B97C0_STACK = 108,
    LIFTED_F4B98B0_STACK = 116,
    LIFTED_F4B99B0_STACK = 100,
    LIFTED_F4B9C10_STACK = 64,
    LIFTED_F4B9C20_STACK = 100,
    LIFTED_F4B9CB0_STACK = 84,
    LIFTED_F4B9CE0_STACK = 64,
    LIFTED_F4B9CF0_STACK = 96,
    LIFTED_F4B9D70_STACK = 76,
    LIFTED_F4B9DD0_STACK = 68,
    LIFTED_F4B9DE0_STACK = 116,
    LIFTED_F4BA210_STACK = 64,
    LIFTED_F4BA220_STACK = 184,
    LIFTED_F4BB260_STACK = 64,
    LIFTED_F4BB3D0_STACK = 100,
    LIFTED_F4BB470_STACK = 88,
    LIFTED_F4BB510_STACK = 136,
    LIFTED_F4BB6C0_STACK = 104,
    LIFTED_F4BB9B0_STACK = 108,
    LIFTED_F4BBA40_STACK = 128,
    LIFTED_F4BC050_STACK = 100,
    LIFTED_F4BC6C0_STACK = 84,
    LIFTED_F4BCE90_STACK = 64,
    LIFTED_F4BCEA0_STACK = 144,
    LIFTED_F4BD1C0_STACK = 80,
    LIFTED_F4BD210_STACK = 84,
    LIFTED_F4BD750_STACK = 144,
    LIFTED_F4BD9E0_STACK = 212,
    LIFTED_F4BE0B0_STACK = 160,
    LIFTED_F4BEF10_STACK = 108,
    LIFTED_F4BF190_STACK = 84,
    LIFTED_F4C07D0_STACK = 88,
    LIFTED_F4C0860_STACK = 112,
    LIFTED_OBJECT_RELEASE_LINKS_STACK = 68,
    LIFTED_F4C09E0_STACK = 88,
    LIFTED_F4C1D20_STACK = 68,
    LIFTED_F4C1E40_STACK = 124,
    LIFTED_F4C2000_STACK = 132,
    LIFTED_F4C31A0_STACK = 88,
    LIFTED_F4C3220_STACK = 100,
    LIFTED_F4C3320_STACK = 104,
    LIFTED_F4C33A0_STACK = 128,
    LIFTED_F4C3540_STACK = 112,
    LIFTED_F4C35F0_STACK = 72,
    LIFTED_F4C3760_STACK = 64,
    LIFTED_F4C3770_STACK = 64,
    LIFTED_F4C3780_STACK = 112,
    LIFTED_F4C3850_STACK = 80,
    LIFTED_F4C38B0_STACK = 104,
    LIFTED_F4C3950_STACK = 92,
    LIFTED_F4C3BE0_STACK = 140,
    LIFTED_F4C3E40_STACK = 84,
    LIFTED_F4C3EA0_STACK = 76,
    LIFTED_F4C3ED0_STACK = 140,
    LIFTED_F4C3F80_STACK = 68,
    LIFTED_F4C4CC0_STACK = 68,
    LIFTED_F4C4D00_STACK = 72,
    LIFTED_F4C5120_STACK = 88,
    LIFTED_F4C5190_STACK = 88,
    LIFTED_F4C5200_STACK = 124,
    LIFTED_F4C5400_STACK = 120,
    LIFTED_F4C54D0_STACK = 120,
    LIFTED_F4C58E0_STACK = 116,
    LIFTED_F4C5A00_STACK = 92,
    LIFTED_F4C5BB0_STACK = 68,
    LIFTED_EDX_TO_EAX_CALL_STACK = 68,
    LIFTED_EDX_TO_EAX_CALL_4C5BE0_STACK = 68,
    LIFTED_RETURN_EBX_STACK = 64,
    LIFTED_F4C5C00_STACK = 68,
    LIFTED_RETURN_ZERO_STACK = 64,
    LIFTED_F4C5C20_STACK = 64,
    LIFTED_F4C63A0_STACK = 108,
    LIFTED_F4C6460_STACK = 100,
    LIFTED_F4C69C0_STACK = 100,
    LIFTED_F4C6A20_STACK = 136,
    LIFTED_F4C6A80_STACK = 64,
    LIFTED_F4C6C70_STACK = 72,
    LIFTED_F4C70F0_STACK = 268,
    LIFTED_F4C8BE0_STACK = 120,
    LIFTED_F4C9030_STACK = 100,
    LIFTED_F4C93C0_STACK = 64,
    LIFTED_F4C9550_STACK = 116,
    LIFTED_F4C9690_STACK = 64,
    LIFTED_F4C9820_STACK = 68,
    LIFTED_ROUND_UP_STACK = 72,
    LIFTED_RTL_COPY_ROWS_STACK = 88,
    LIFTED_RTL_ZERO_CALL_STACK = 72,
    LIFTED_RTL_FLAGGED_CALL_STACK = 76,
    LIFTED_F4C9DD6_STACK = 76,
    LIFTED_F4C9E00_STACK = 76,
    LIFTED_F4C9FE0_STACK = 76,
    LIFTED_F4C9FF0_STACK = 92,
    LIFTED_F4CA000_STACK = 92,
    LIFTED_F4CA040_STACK = 92,
    LIFTED_F4CA050_STACK = 92,
    LIFTED_F4CA060_STACK = 64,
    LIFTED_F4CA070_STACK = 80,
    LIFTED_F4CA090_STACK = 92,
    LIFTED_F4CA0D0_STACK = 84,
    LIFTED_F4CA110_STACK = 92,
    LIFTED_F4CA150_STACK = 76,
    LIFTED_RTL_STRING_MAKE_UNIQUE_STACK = 88,
    LIFTED_F4CA1E0_STACK = 76,
    LIFTED_F4CA210_STACK = 84,
    LIFTED_F4CA2E0_STACK = 84,
    LIFTED_F4CA370_STACK = 88,
    LIFTED_RTL_WIDE_ASSIGN_STACK = 92,
    LIFTED_RTL_STRING_APPEND_PAIR_STACK = 88,
    LIFTED_F4CA4A0_STACK = 120,
    LIFTED_F4CA520_STACK = 124,
    LIFTED_F4CA600_STACK = 88,
    LIFTED_F4CA650_STACK = 76,
    LIFTED_RTL_STRING_UNIQUE_SIZE_STACK = 96,
    LIFTED_F4CA6C0_STACK = 84,
    LIFTED_RTL_STRING_SET_LENGTH_STACK = 76,
    LIFTED_F4CA710_STACK = 84,
    LIFTED_F4CA730_STACK = 108,
    LIFTED_F4CA770_STACK = 100,
    LIFTED_F4CA970_STACK = 128,
    LIFTED_F4CAFD0_STACK = 92,
    LIFTED_F4CB080_STACK = 100,
    LIFTED_F4CB390_STACK = 64,
    LIFTED_F4CB3A0_STACK = 64,
    LIFTED_F4CB3B0_STACK = 64,
    LIFTED_RTL_STREAM_INIT_STACK = 104,
    LIFTED_F4CB4F0_STACK = 140,
    LIFTED_F4CB5A0_STACK = 196,
    LIFTED_F4CB950_STACK = 80,
    LIFTED_F4CB970_STACK = 80,
    LIFTED_RTL_RECORD_CLEAR_STACK = 68,
    LIFTED_RTL_RECORD_FIELD_STACK = 68,
    LIFTED_F4CBE90_STACK = 128,
    LIFTED_RTL_STREAM_INIT_DERIVED_STACK = 112,
    LIFTED_F4CBF90_STACK = 84,
    LIFTED_F4CC0D0_STACK = 148,
    LIFTED_F4CC200_STACK = 224,
    LIFTED_F4CC420_STACK = 80,
    LIFTED_F4CC450_STACK = 108,
    LIFTED_F4CC4A0_STACK = 88,
    LIFTED_F4CC760_STACK = 72,
    LIFTED_F4CC780_STACK = 72,
    LIFTED_F4CC7A0_STACK = 92,
    LIFTED_F4CC7C0_STACK = 108,
    LIFTED_F4CC870_STACK = 92,
    LIFTED_F4CC990_STACK = 80,
    LIFTED_F4CCAD0_STACK = 72,
    LIFTED_F4CCAF0_STACK = 80,
    LIFTED_F4CCB40_STACK = 88,
    LIFTED_RTL_BLOCK_CALL_STACK = 80,
    LIFTED_F4CCBC0_STACK = 136,
    LIFTED_F4CCC60_STACK = 92,
    LIFTED_F4CCCC0_STACK = 88,
    LIFTED_F4CCCF0_STACK = 88,
    LIFTED_F4CCD20_STACK = 92,
    LIFTED_F4CCD50_STACK = 84,
    LIFTED_F4CCD80_STACK = 120,
    LIFTED_F4CCDD0_STACK = 84,
    LIFTED_F4CCE00_STACK = 84,
    LIFTED_F4CCE30_STACK = 84,
    LIFTED_F4CCE60_STACK = 92,
    LIFTED_F4CCFE0_STACK = 72,
    LIFTED_F4CD090_STACK = 72,
    LIFTED_RTL_TERMINATE_CALL_STACK = 76,
    LIFTED_F4CD7DC_STACK = 84,
    LIFTED_F4CD847_STACK = 84,
    LIFTED_F4CDA40_STACK = 92,
    LIFTED_F4CE080_STACK = 76,
    LIFTED_F4CE230_STACK = 68,
    LIFTED_F4CE810_STACK = 76,
    LIFTED_F4CE9C0_STACK = 88,
    LIFTED_RTL_RELEASE_INNER_STACK = 72,
    LIFTED_RTL_CONSTRUCT_BUFFER_STREAM_STACK = 120,
    LIFTED_F4CF420_STACK = 124,
    LIFTED_F4CF480_STACK = 88,
    LIFTED_F4CF4A0_STACK = 80,
    LIFTED_F4CF5D0_STACK = 112,
    LIFTED_F4CF800_STACK = 96,
    LIFTED_F4CF850_STACK = 92,
    LIFTED_F4CF880_STACK = 92,
    LIFTED_RTL_TRIPLE_CALL_STACK = 80,
    LIFTED_F4CF940_STACK = 84,
    LIFTED_RTL_RELEASE_STRING_MEMBER_STACK = 84,
    LIFTED_F4CF9D0_STACK = 96,
    LIFTED_F4CFC90_STACK = 120,
    LIFTED_F4CFE40_STACK = 164,
    LIFTED_F4CFF20_STACK = 112,
    LIFTED_F4CFF80_STACK = 104,
    LIFTED_F4CFFD0_STACK = 96,
    LIFTED_F4D01A0_STACK = 152,
    LIFTED_F4D04D0_STACK = 92,
    LIFTED_F4D04F0_STACK = 104,
    LIFTED_F4D05E0_STACK = 100,
    LIFTED_F4D0650_STACK = 88,
    LIFTED_F4D0740_STACK = 128,
    LIFTED_RTL_RECORD_MARK_STACK = 68,
    LIFTED_F4D1710_STACK = 160,
    LIFTED_F4D1840_STACK = 108,
    LIFTED_F4D1890_STACK = 124,
    LIFTED_F4D1900_STACK = 92,
    LIFTED_F4D1930_STACK = 88,
    LIFTED_F4D1980_STACK = 152,
    LIFTED_F4D1D20_STACK = 220,
    LIFTED_F4D1E00_STACK = 96,
    LIFTED_F4D1E50_STACK = 92,
    LIFTED_F4D2170_STACK = 88,
    LIFTED_F4D21A0_STACK = 80,
    LIFTED_F4D21D0_STACK = 144,
    LIFTED_F4D2260_STACK = 104,
    LIFTED_F4D22B0_STACK = 128,
    LIFTED_F4D2310_STACK = 140,
    LIFTED_RTL_SCOPE_REFRESH_STACK = 124,
    LIFTED_F4D2420_STACK = 76,
    LIFTED_F4D2440_STACK = 76
};

/* Original 0x4ac700. */
uint32_t lifted_actor_reset_frame_counter(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac710. */
uint32_t lifted_actor_set_frame_index(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac720. */
uint32_t lifted_block_resource_last(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac740. */
uint32_t lifted_actor_next_frame_counter(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac750. */
uint32_t lifted_actor_previous_frame_counter(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac760. */
uint32_t lifted_actor_frame_is_count(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac780. */
uint32_t lifted_actor_frame_is_last(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac7a0. */
uint32_t lifted_actor_frame_counter_is_zero(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac7b0. */
uint32_t lifted_actor_set_period_steps(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac7d0. */
uint32_t lifted_actor_set_period(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac7e0. */
uint32_t lifted_actor_randomize_period(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac810. */
uint32_t lifted_actor_randomize_d0(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac860. */
uint32_t lifted_actor_set_e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac8a0. */
uint32_t lifted_actor_lookup_image(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac8d0. */
uint32_t lifted_actor_attach_resource(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac8f0. */
uint32_t lifted_actor_set_handler(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac900. */
uint32_t lifted_actor_get_handler(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac910. */
uint32_t lifted_actor_set_ec(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac920. */
uint32_t lifted_actor_handler_from_ec(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac930. */
uint32_t lifted_actor_set_f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac940. */
uint32_t lifted_actor_handler_from_f0(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac950. */
uint32_t lifted_actor_set_b4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac960. */
uint32_t lifted_actor_get_b4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac980. */
uint32_t lifted_step_toward(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aca60. */
uint32_t lifted_word_transition(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4acab0. */
uint32_t lifted_word_transition_4acab0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4acb00. */
uint32_t lifted_actor_step_word(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4acc10. */
uint32_t lifted_byte_transition(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4acc70. */
uint32_t lifted_dword_transition(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4accc0. */
uint32_t lifted_f4accc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4acd30. */
uint32_t lifted_f4acd30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ace40. */
uint32_t lifted_actor_turn_toward(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad060. */
uint32_t lifted_rotation_advance(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad110. */
uint32_t lifted_actor_spin(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad1c0. */
uint32_t lifted_actor_polar_offset(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad210. */
uint32_t lifted_actor_polar_offset_second(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad260. */
uint32_t lifted_actor_orbit_point(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad2c0. */
uint32_t lifted_f4ad2c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad440. */
uint32_t lifted_actor_chain_orbit_point(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad510. */
uint32_t lifted_actor_set_words_2a(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad530. */
uint32_t lifted_word_transition_4ad530(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad580. */
uint32_t lifted_byte_transition_4ad580(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad5e0. */
uint32_t lifted_word_transition_4ad5e0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad630. */
uint32_t lifted_word_transition_4ad630(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad6e0. */
uint32_t lifted_actor_dword_transition(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad750. */
uint32_t lifted_object_step_dword(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad790. */
uint32_t lifted_actor_dword_transition_4ad790(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x4ad870. */
uint32_t lifted_f4ad870(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ade20. */
uint32_t lifted_f4ade20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ade60. */
uint32_t lifted_actor_chain_walk(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4adf20. */
uint32_t lifted_actor_initialize(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4adf70. */
uint32_t lifted_f4adf70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4adfa0. */
uint32_t lifted_f4adfa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4adfb0. */
uint32_t lifted_actor_refresh_value_full(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4adfe0. */
uint32_t lifted_actor_refresh_arm_full(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ae010. */
uint32_t lifted_actor_draw_slot_full(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ae110. */
uint32_t lifted_f4ae110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ae140. */
uint32_t lifted_actor_chain_walk_4ae140(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ae150. */
uint32_t lifted_f4ae150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ae1f0. */
uint32_t lifted_f4ae1f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ae250. */
uint32_t lifted_render_prepare(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4af2a0. */
uint32_t lifted_render_rule(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4af370. */
uint32_t lifted_render_flags(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b0b70. */
uint32_t lifted_f4b0b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b14c0. */
uint32_t lifted_resource_measure(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b17b0. */
uint32_t lifted_f4b17b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b1fa0. */
uint32_t lifted_f4b1fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b2290. */
uint32_t lifted_object_zero_dwords(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b22c0. */
uint32_t lifted_object_release_slots_full(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b2300. */
uint32_t lifted_f4b2300(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b2340. */
uint32_t lifted_f4b2340(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b2380. */
uint32_t lifted_f4b2380(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b23c0. */
uint32_t lifted_f4b23c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3100. */
uint32_t lifted_f4b3100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3340. */
uint32_t lifted_f4b3340(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3360. */
uint32_t lifted_return_unchanged_4b3360(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b34d0. */
uint32_t lifted_f4b34d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3500. */
uint32_t lifted_f4b3500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3a00. */
uint32_t lifted_f4b3a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3ce0. */
uint32_t lifted_f4b3ce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3d60. */
uint32_t lifted_f4b3d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3fb0. */
uint32_t lifted_f4b3fb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4500. */
uint32_t lifted_object_dword_4b4500(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b45f0. */
uint32_t lifted_object_cursor_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b46e0. */
uint32_t lifted_object_text_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4700. */
uint32_t lifted_object_text_nearest(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4780. */
uint32_t lifted_object_text_seek(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4cf0. */
uint32_t lifted_f4b4cf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4fa0. */
uint32_t lifted_object_set_pair_4b4fa0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5050. */
uint32_t lifted_f4b5050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b50d0. */
uint32_t lifted_f4b50d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5150. */
uint32_t lifted_f4b5150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5400. */
uint32_t lifted_actor_construct_518174(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5420. */
uint32_t lifted_object_destroy_call(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b54d0. */
uint32_t lifted_actor_set_box(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5500. */
uint32_t lifted_object_slot_present(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5550. */
uint32_t lifted_f4b5550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5560. */
uint32_t lifted_f4b5560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5580. */
uint32_t lifted_f4b5580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5630. */
uint32_t lifted_f4b5630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5700. */
uint32_t lifted_f4b5700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b58a0. */
uint32_t lifted_f4b58a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5c60. */
uint32_t lifted_object_start_5182c4(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5d40. */
uint32_t lifted_object_slot_present_unowned(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5db0. */
uint32_t lifted_f4b5db0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5dc0. */
uint32_t lifted_object_destroy_a(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5e70. */
uint32_t lifted_owned_object_list_append(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5eb0. */
uint32_t lifted_object_list_find(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5fc0. */
uint32_t lifted_f4b5fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6020. */
uint32_t lifted_object_release_items(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6070. */
uint32_t lifted_f4b6070(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b60c0. */
uint32_t lifted_f4b60c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6120. */
uint32_t lifted_f4b6120(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6170. */
uint32_t lifted_f4b6170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b61c0. */
uint32_t lifted_f4b61c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6200. */
uint32_t lifted_object_list_update(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6460. */
uint32_t lifted_object_destroy_d(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6530. */
uint32_t lifted_timer_reset(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6540. */
uint32_t lifted_object_set_word(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6550. */
uint32_t lifted_object_set_word_4b6550(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6560. */
uint32_t lifted_timer_running(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6590. */
uint32_t lifted_object_word(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b65a0. */
uint32_t lifted_object_word_4b65a0(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b65b0. */
uint32_t lifted_object_set_dword_4b65b0(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6690. */
uint32_t lifted_object_set_four_words(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b66c0. */
uint32_t lifted_object_contains(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6700. */
uint32_t lifted_object_slot_present_4b6700(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6800. */
uint32_t lifted_f4b6800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6890. */
uint32_t lifted_forward_registers_4b6890(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6ea0. */
uint32_t lifted_f4b6ea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7020. */
uint32_t lifted_f4b7020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7600. */
uint32_t lifted_f4b7600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b78d0. */
uint32_t lifted_object_table_new_4b78d0(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b78e0. */
uint32_t lifted_f4b78e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7b00. */
uint32_t lifted_f4b7b00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7b80. */
uint32_t lifted_f4b7b80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7c90. */
uint32_t lifted_f4b7c90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7cd0. */
uint32_t lifted_time_sample(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7d70. */
uint32_t lifted_f4b7d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7db0. */
uint32_t lifted_f4b7db0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b8170. */
uint32_t lifted_two_step_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b826f. */
uint32_t lifted_f4b826f(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b8fbc. */
uint32_t lifted_record_prefix_sum(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9050. */
uint32_t lifted_f4b9050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9170. */
uint32_t lifted_f4b9170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b91b0. */
uint32_t lifted_f4b91b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b91e0. */
uint32_t lifted_f4b91e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9200. */
uint32_t lifted_f4b9200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9220. */
uint32_t lifted_f4b9220(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9310. */
uint32_t lifted_f4b9310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9330. */
uint32_t lifted_f4b9330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9540. */
uint32_t lifted_f4b9540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b95e0. */
uint32_t lifted_f4b95e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b97c0. */
uint32_t lifted_f4b97c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b98b0. */
uint32_t lifted_f4b98b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b99b0. */
uint32_t lifted_f4b99b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9c10. */
uint32_t lifted_f4b9c10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9c20. */
uint32_t lifted_f4b9c20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9cb0. */
uint32_t lifted_f4b9cb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9ce0. */
uint32_t lifted_f4b9ce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9cf0. */
uint32_t lifted_f4b9cf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9d70. */
uint32_t lifted_f4b9d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9dd0. */
uint32_t lifted_f4b9dd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9de0. */
uint32_t lifted_f4b9de0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ba210. */
uint32_t lifted_f4ba210(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ba220. */
uint32_t lifted_f4ba220(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bb260. */
uint32_t lifted_f4bb260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bb3d0. */
uint32_t lifted_f4bb3d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bb470. */
uint32_t lifted_f4bb470(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bb510. */
uint32_t lifted_f4bb510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bb6c0. */
uint32_t lifted_f4bb6c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bb9b0. */
uint32_t lifted_f4bb9b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bba40. */
uint32_t lifted_f4bba40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bc050. */
uint32_t lifted_f4bc050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bc6c0. */
uint32_t lifted_f4bc6c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bce90. */
uint32_t lifted_f4bce90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bcea0. */
uint32_t lifted_f4bcea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bd1c0. */
uint32_t lifted_f4bd1c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bd210. */
uint32_t lifted_f4bd210(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bd750. */
uint32_t lifted_f4bd750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bd9e0. */
uint32_t lifted_f4bd9e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4be0b0. */
uint32_t lifted_f4be0b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bef10. */
uint32_t lifted_f4bef10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bf190. */
uint32_t lifted_f4bf190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c07d0. */
uint32_t lifted_f4c07d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c0860. */
uint32_t lifted_f4c0860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c0990. */
uint32_t lifted_object_release_links(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c09e0. */
uint32_t lifted_f4c09e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c1d20. */
uint32_t lifted_f4c1d20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c1e40. */
uint32_t lifted_f4c1e40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c2000. */
uint32_t lifted_f4c2000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c31a0. */
uint32_t lifted_f4c31a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3220. */
uint32_t lifted_f4c3220(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3320. */
uint32_t lifted_f4c3320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c33a0. */
uint32_t lifted_f4c33a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3540. */
uint32_t lifted_f4c3540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c35f0. */
uint32_t lifted_f4c35f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3760. */
uint32_t lifted_f4c3760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3770. */
uint32_t lifted_f4c3770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3780. */
uint32_t lifted_f4c3780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3850. */
uint32_t lifted_f4c3850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c38b0. */
uint32_t lifted_f4c38b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3950. */
uint32_t lifted_f4c3950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3be0. */
uint32_t lifted_f4c3be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3e40. */
uint32_t lifted_f4c3e40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3ea0. */
uint32_t lifted_f4c3ea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3ed0. */
uint32_t lifted_f4c3ed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3f80. */
uint32_t lifted_f4c3f80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c4cc0. */
uint32_t lifted_f4c4cc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c4d00. */
uint32_t lifted_f4c4d00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5120. */
uint32_t lifted_f4c5120(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5190. */
uint32_t lifted_f4c5190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5200. */
uint32_t lifted_f4c5200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5400. */
uint32_t lifted_f4c5400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c54d0. */
uint32_t lifted_f4c54d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c58e0. */
uint32_t lifted_f4c58e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5a00. */
uint32_t lifted_f4c5a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5bb0. */
uint32_t lifted_f4c5bb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5bc0. */
uint32_t lifted_edx_to_eax_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5be0. */
uint32_t lifted_edx_to_eax_call_4c5be0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5bf0. */
uint32_t lifted_return_ebx(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5c00. */
uint32_t lifted_f4c5c00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5c10. */
uint32_t lifted_return_zero(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5c20. */
uint32_t lifted_f4c5c20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c63a0. */
uint32_t lifted_f4c63a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c6460. */
uint32_t lifted_f4c6460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c69c0. */
uint32_t lifted_f4c69c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c6a20. */
uint32_t lifted_f4c6a20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c6a80. */
uint32_t lifted_f4c6a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c6c70. */
uint32_t lifted_f4c6c70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c70f0. */
uint32_t lifted_f4c70f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c8be0. */
uint32_t lifted_f4c8be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9030. */
uint32_t lifted_f4c9030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c93c0. */
uint32_t lifted_f4c93c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9550. */
uint32_t lifted_f4c9550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9690. */
uint32_t lifted_f4c9690(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9820. */
uint32_t lifted_f4c9820(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9840. */
uint32_t lifted_round_up(const VertrixCalls *calls, const VertrixFactoryServices *services,
                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9860. */
uint32_t lifted_rtl_copy_rows(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c98f0. */
uint32_t lifted_rtl_zero_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9daf. */
uint32_t lifted_rtl_flagged_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9dd6. */
uint32_t lifted_f4c9dd6(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9e00. */
uint32_t lifted_f4c9e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9fe0. */
uint32_t lifted_f4c9fe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9ff0. */
uint32_t lifted_f4c9ff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca000. */
uint32_t lifted_f4ca000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca040. */
uint32_t lifted_f4ca040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca050. */
uint32_t lifted_f4ca050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca060. */
uint32_t lifted_f4ca060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca070. */
uint32_t lifted_f4ca070(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca090. */
uint32_t lifted_f4ca090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca0d0. */
uint32_t lifted_f4ca0d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca110. */
uint32_t lifted_f4ca110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca150. */
uint32_t lifted_f4ca150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca1a0. */
uint32_t lifted_rtl_string_make_unique(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca1e0. */
uint32_t lifted_f4ca1e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca210. */
uint32_t lifted_f4ca210(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca2e0. */
uint32_t lifted_f4ca2e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca370. */
uint32_t lifted_f4ca370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca3a0. */
uint32_t lifted_rtl_wide_assign(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca3f0. */
uint32_t lifted_rtl_string_append_pair(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca4a0. */
uint32_t lifted_f4ca4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca520. */
uint32_t lifted_f4ca520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca600. */
uint32_t lifted_f4ca600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca650. */
uint32_t lifted_f4ca650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca670. */
uint32_t lifted_rtl_string_unique_size(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca6c0. */
uint32_t lifted_f4ca6c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca6f0. */
uint32_t lifted_rtl_string_set_length(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca710. */
uint32_t lifted_f4ca710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca730. */
uint32_t lifted_f4ca730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca770. */
uint32_t lifted_f4ca770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca970. */
uint32_t lifted_f4ca970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cafd0. */
uint32_t lifted_f4cafd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb080. */
uint32_t lifted_f4cb080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb390. */
uint32_t lifted_f4cb390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb3a0. */
uint32_t lifted_f4cb3a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb3b0. */
uint32_t lifted_f4cb3b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb460. */
uint32_t lifted_rtl_stream_init(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb4f0. */
uint32_t lifted_f4cb4f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb5a0. */
uint32_t lifted_f4cb5a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb950. */
uint32_t lifted_f4cb950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb970. */
uint32_t lifted_f4cb970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cba70. */
uint32_t lifted_rtl_record_clear(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cbe80. */
uint32_t lifted_rtl_record_field(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cbe90. */
uint32_t lifted_f4cbe90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cbf10. */
uint32_t lifted_rtl_stream_init_derived(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cbf90. */
uint32_t lifted_f4cbf90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc0d0. */
uint32_t lifted_f4cc0d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc200. */
uint32_t lifted_f4cc200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc420. */
uint32_t lifted_f4cc420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc450. */
uint32_t lifted_f4cc450(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc4a0. */
uint32_t lifted_f4cc4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc760. */
uint32_t lifted_f4cc760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc780. */
uint32_t lifted_f4cc780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc7a0. */
uint32_t lifted_f4cc7a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc7c0. */
uint32_t lifted_f4cc7c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc870. */
uint32_t lifted_f4cc870(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc990. */
uint32_t lifted_f4cc990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccad0. */
uint32_t lifted_f4ccad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccaf0. */
uint32_t lifted_f4ccaf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccb40. */
uint32_t lifted_f4ccb40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccb9f. */
uint32_t lifted_rtl_block_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccbc0. */
uint32_t lifted_f4ccbc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccc60. */
uint32_t lifted_f4ccc60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cccc0. */
uint32_t lifted_f4cccc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cccf0. */
uint32_t lifted_f4cccf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccd20. */
uint32_t lifted_f4ccd20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccd50. */
uint32_t lifted_f4ccd50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccd80. */
uint32_t lifted_f4ccd80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccdd0. */
uint32_t lifted_f4ccdd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cce00. */
uint32_t lifted_f4cce00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cce30. */
uint32_t lifted_f4cce30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cce60. */
uint32_t lifted_f4cce60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccfe0. */
uint32_t lifted_f4ccfe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd090. */
uint32_t lifted_f4cd090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd0a4. */
uint32_t lifted_rtl_terminate_call(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd7dc. */
uint32_t lifted_f4cd7dc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd847. */
uint32_t lifted_f4cd847(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cda40. */
uint32_t lifted_f4cda40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce080. */
uint32_t lifted_f4ce080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce230. */
uint32_t lifted_f4ce230(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce810. */
uint32_t lifted_f4ce810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce9c0. */
uint32_t lifted_f4ce9c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce9fd. */
uint32_t lifted_rtl_release_inner(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf320. */
uint32_t lifted_rtl_construct_buffer_stream(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf420. */
uint32_t lifted_f4cf420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf480. */
uint32_t lifted_f4cf480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf4a0. */
uint32_t lifted_f4cf4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf5d0. */
uint32_t lifted_f4cf5d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf800. */
uint32_t lifted_f4cf800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf850. */
uint32_t lifted_f4cf850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf880. */
uint32_t lifted_f4cf880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf8e0. */
uint32_t lifted_rtl_triple_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf940. */
uint32_t lifted_f4cf940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf980. */
uint32_t lifted_rtl_release_string_member(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf9d0. */
uint32_t lifted_f4cf9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cfc90. */
uint32_t lifted_f4cfc90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cfe40. */
uint32_t lifted_f4cfe40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cff20. */
uint32_t lifted_f4cff20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cff80. */
uint32_t lifted_f4cff80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cffd0. */
uint32_t lifted_f4cffd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d01a0. */
uint32_t lifted_f4d01a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d04d0. */
uint32_t lifted_f4d04d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d04f0. */
uint32_t lifted_f4d04f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d05e0. */
uint32_t lifted_f4d05e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d0650. */
uint32_t lifted_f4d0650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d0740. */
uint32_t lifted_f4d0740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d16b0. */
uint32_t lifted_rtl_record_mark(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1710. */
uint32_t lifted_f4d1710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1840. */
uint32_t lifted_f4d1840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1890. */
uint32_t lifted_f4d1890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1900. */
uint32_t lifted_f4d1900(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1930. */
uint32_t lifted_f4d1930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1980. */
uint32_t lifted_f4d1980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1d20. */
uint32_t lifted_f4d1d20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1e00. */
uint32_t lifted_f4d1e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1e50. */
uint32_t lifted_f4d1e50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2170. */
uint32_t lifted_f4d2170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d21a0. */
uint32_t lifted_f4d21a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d21d0. */
uint32_t lifted_f4d21d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2260. */
uint32_t lifted_f4d2260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d22b0. */
uint32_t lifted_f4d22b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2310. */
uint32_t lifted_f4d2310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2390. */
uint32_t lifted_rtl_scope_refresh(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2420. */
uint32_t lifted_f4d2420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2440. */
uint32_t lifted_f4d2440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
