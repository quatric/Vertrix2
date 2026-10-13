#ifndef VERTRIX_LIFTED_WHOLE_5_H
#define VERTRIX_LIFTED_WHOLE_5_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4B7020_STACK = 100,
    LIFTED_F4B7C90_STACK = 96,
    LIFTED_F4B7DB0_STACK = 84,
    LIFTED_WAVE_LOAD_STACK = 164,
    LIFTED_TWO_STEP_CALL_STACK = 80,
    LIFTED_F4B8187_STACK = 428,
    LIFTED_F4B826F_STACK = 436,
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
    LIFTED_RETURN_UNCHANGED_4B9CE0_STACK = 64,
    LIFTED_F4B9CF0_STACK = 96,
    LIFTED_F4B9D70_STACK = 76,
    LIFTED_F4B9DD0_STACK = 68,
    LIFTED_F4B9DE0_STACK = 116,
    LIFTED_RETURN_ZERO_STACK = 64,
    LIFTED_F4BA220_STACK = 184,
    LIFTED_F4BB040_STACK = 128,
    LIFTED_RETURN_UNCHANGED_4BB260_STACK = 64,
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
    LIFTED_F4C3E60_STACK = 296,
    LIFTED_F4C3EA0_STACK = 76,
    LIFTED_F4C3ED0_STACK = 140,
    LIFTED_F4C3F80_STACK = 68,
    LIFTED_OBJECT_INIT_4C3FA0_STACK = 64,
    LIFTED_F4C4000_STACK = 408,
    LIFTED_F4C4730_STACK = 244,
    LIFTED_F4C4B00_STACK = 156,
    LIFTED_F4C4CC0_STACK = 68,
    LIFTED_F4C4D00_STACK = 72,
    LIFTED_F4C5120_STACK = 88,
    LIFTED_F4C5190_STACK = 88,
    LIFTED_F4C5200_STACK = 124,
    LIFTED_F4C5400_STACK = 120,
    LIFTED_F4C54D0_STACK = 120,
    LIFTED_F4C58E0_STACK = 116,
    LIFTED_F4C5A00_STACK = 92,
    LIFTED_F4C5A40_STACK = 128,
    LIFTED_F4C5BB0_STACK = 68,
    LIFTED_EDX_TO_EAX_CALL_STACK = 68,
    LIFTED_EDX_TO_EAX_CALL_4C5BE0_STACK = 68,
    LIFTED_RETURN_EBX_STACK = 64,
    LIFTED_F4C5C00_STACK = 68,
    LIFTED_RETURN_ZERO_4C5C10_STACK = 64,
    LIFTED_RETURN_UNCHANGED_4C5C20_STACK = 64,
    LIFTED_F4C63A0_STACK = 108,
    LIFTED_F4C6460_STACK = 100,
    LIFTED_F4C69C0_STACK = 100,
    LIFTED_F4C6A20_STACK = 136,
    LIFTED_RETURN_UNCHANGED_4C6A80_STACK = 64,
    LIFTED_F4C6C70_STACK = 72,
    LIFTED_F4C70F0_STACK = 268,
    LIFTED_F4C8500_STACK = 2200,
    LIFTED_F4C8BE0_STACK = 120,
    LIFTED_F4C9030_STACK = 100,
    LIFTED_RETURN_UNCHANGED_4C93C0_STACK = 64,
    LIFTED_F4C9550_STACK = 116,
    LIFTED_F4C9690_STACK = 64,
    LIFTED_F4C9820_STACK = 68,
    LIFTED_ROUND_UP_STACK = 72,
    LIFTED_RTL_COPY_ROWS_STACK = 88,
    LIFTED_RTL_ZERO_CALL_STACK = 72,
    LIFTED_F4C9FE0_STACK = 76,
    LIFTED_F4CA040_STACK = 92,
    LIFTED_F4CA050_STACK = 92,
    LIFTED_RTL_STRING_COPY_PAIR_STACK = 84,
    LIFTED_RTL_WIDE_ASSIGN_STACK = 92,
    LIFTED_RTL_STRING_CONCAT_STACK = 112,
    LIFTED_F4CA4A0_STACK = 120,
    LIFTED_F4CA650_STACK = 76,
    LIFTED_RTL_STRING_SET_LENGTH_STACK = 76,
    LIFTED_F4CA730_STACK = 108,
    LIFTED_F4CA770_STACK = 100,
    LIFTED_RETURN_CONSTANT_4CC7A0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4CCAF0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4CCB40_STACK = 64,
    LIFTED_F4CB4F0_STACK = 140,
    LIFTED_F4CB5A0_STACK = 196,
    LIFTED_F4CBA60_STACK = 76,
    LIFTED_RTL_RECORD_CLEAR_STACK = 68,
    LIFTED_F4CBC90_STACK = 124,
    LIFTED_RTL_RECORD_FIELD_STACK = 68,
    LIFTED_F4CBFE0_STACK = 152,
    LIFTED_F4CC0D0_STACK = 148,
    LIFTED_F4CC200_STACK = 224,
    LIFTED_F4CC420_STACK = 80,
    LIFTED_F4CC450_STACK = 108,
    LIFTED_F4CC760_STACK = 72,
    LIFTED_F4CC780_STACK = 72,
    LIFTED_F4CC7A0_STACK = 92,
    LIFTED_F4CCAD0_STACK = 72,
    LIFTED_F4CCAF0_STACK = 80,
    LIFTED_F4CCB40_STACK = 88,
    LIFTED_RTL_BLOCK_CALL_STACK = 80,
    LIFTED_F4CCCC0_STACK = 88,
    LIFTED_F4CCD80_STACK = 120,
    LIFTED_F4CCE00_STACK = 84,
    LIFTED_F4CCE30_STACK = 84,
    LIFTED_F4CCE60_STACK = 92,
    LIFTED_F4CCE90_STACK = 100,
    LIFTED_RTL_LINK_OWNER_STACK = 84,
    LIFTED_RTL_TERMINATE_CALL_STACK = 76,
    LIFTED_RTL_VARARG_CALL_STACK = 84,
    LIFTED_F4CD56C_STACK = 244,
    LIFTED_F4CD7DC_STACK = 84,
    LIFTED_F4CD836_STACK = 76,
    LIFTED_F4CD847_STACK = 84,
    LIFTED_RTL_LOCAL_CALL_STACK = 92,
    LIFTED_RTL_LOCAL_CHAIN_CALL_STACK = 96,
    LIFTED_RTL_STRING_FILL_STACK = 88,
    LIFTED_F4CDAD0_STACK = 80,
    LIFTED_F4CDB70_STACK = 112,
    LIFTED_F4CDBE0_STACK = 192,
    LIFTED_F4CDFB0_STACK = 80,
    LIFTED_F4CE080_STACK = 76,
    LIFTED_RTL_CONSTRUCT_BUFFER_STREAM_STACK = 120,
    LIFTED_F4CF4A0_STACK = 80,
    LIFTED_F4CF4D0_STACK = 132,
    LIFTED_F4CF5D0_STACK = 112,
    LIFTED_F4CF800_STACK = 96,
    LIFTED_F4CF850_STACK = 92,
    LIFTED_F4CF880_STACK = 92,
    LIFTED_F4CF8D0_STACK = 112,
    LIFTED_RTL_TRIPLE_CALL_STACK = 80,
    LIFTED_F4CF910_STACK = 80,
    LIFTED_F4CF940_STACK = 84,
    LIFTED_RTL_RELEASE_STRING_MEMBER_STACK = 84,
    LIFTED_F4CF9D0_STACK = 96,
    LIFTED_F4CFA20_STACK = 408,
    LIFTED_F4CFC90_STACK = 120,
    LIFTED_F4CFE40_STACK = 164,
    LIFTED_F4CFF20_STACK = 112,
    LIFTED_F4D01A0_STACK = 152,
    LIFTED_F4D0410_STACK = 108,
    LIFTED_F4D04D0_STACK = 92,
    LIFTED_F4D04F0_STACK = 104,
    LIFTED_F4D05E0_STACK = 100,
    LIFTED_F4D0620_STACK = 92,
    LIFTED_F4D0650_STACK = 88,
    LIFTED_F4D0670_STACK = 80,
    LIFTED_F4D06A0_STACK = 80,
    LIFTED_F4D0740_STACK = 128,
    LIFTED_RTL_RECORD_MARK_STACK = 68,
    LIFTED_F4D1710_STACK = 160,
    LIFTED_F4D1840_STACK = 108,
    LIFTED_F4D1890_STACK = 124,
    LIFTED_F4D1900_STACK = 92,
    LIFTED_F4D1930_STACK = 88,
    LIFTED_F4D1E50_STACK = 92,
    LIFTED_F4D1E80_STACK = 212,
    LIFTED_F4D2170_STACK = 88,
    LIFTED_F4D21A0_STACK = 80,
    LIFTED_F4D21D0_STACK = 144,
    LIFTED_F4D2260_STACK = 104,
    LIFTED_F4D22B0_STACK = 128,
    LIFTED_F4D2310_STACK = 140,
    LIFTED_RTL_SCOPE_REFRESH_STACK = 124,
    LIFTED_F4D23F0_STACK = 92,
    LIFTED_F4D2420_STACK = 76,
    LIFTED_F4D2440_STACK = 76,
    LIFTED_F4D2460_STACK = 136,
    LIFTED_F4D24A0_STACK = 80,
    LIFTED_F4D2540_STACK = 136,
    LIFTED_RETURN_CONSTANT_FFFF_STACK = 64,
    LIFTED_OBJECT_STATUS_ACTIVE_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D09B0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D05E0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D0740_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D24A0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D0620_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D2460_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D2420_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D2440_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D0650_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D0670_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D06A0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D02A0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D2170_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D21D0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D2260_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D22B0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D2310_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D21A0_STACK = 64,
    LIFTED_RTL_SCOPE_REFRESH_ADDRESS_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D23F0_STACK = 64,
    LIFTED_F4D3010_STACK = 76,
    LIFTED_RTL_SWAPPED_CALL_STACK = 72,
    LIFTED_F4D3040_STACK = 172,
    LIFTED_RTL_CLASS_CHAIN_CONTAINS_STACK = 68,
    LIFTED_F4D3E20_STACK = 136,
    LIFTED_OBJECT_DESTROY_F_STACK = 152,
    LIFTED_F4D4040_STACK = 84,
    LIFTED_RTL_RECORD_FORWARD_STACK = 84,
    LIFTED_F4D41A0_STACK = 76,
    LIFTED_F4D41C0_STACK = 80,
    LIFTED_F4D4270_STACK = 84,
    LIFTED_F4D42A0_STACK = 84,
    LIFTED_F4D4300_STACK = 64,
    LIFTED_RTL_ANCESTOR_SEARCH_STACK = 76,
    LIFTED_F4D4630_STACK = 160,
    LIFTED_F4D4700_STACK = 196,
    LIFTED_F4D4990_STACK = 72,
    LIFTED_F4D49A0_STACK = 104,
    LIFTED_F4D4D10_STACK = 128,
    LIFTED_F4D4E00_STACK = 92,
    LIFTED_F4D4E30_STACK = 92,
    LIFTED_F4D4E60_STACK = 104,
    LIFTED_F4D4FD0_STACK = 88,
    LIFTED_F4D5010_STACK = 120,
    LIFTED_F4D5150_STACK = 84,
    LIFTED_F4D5180_STACK = 100,
    LIFTED_F4D51C0_STACK = 412,
    LIFTED_F4D5330_STACK = 88,
    LIFTED_OBJECT_DWORD_4D5350_STACK = 64,
    LIFTED_F4D5390_STACK = 136,
    LIFTED_F4D54C0_STACK = 260,
    LIFTED_F4D5660_STACK = 140,
    LIFTED_F4D57A0_STACK = 88,
    LIFTED_F4D58E0_STACK = 80,
    LIFTED_F4D5910_STACK = 88,
    LIFTED_F4D5930_STACK = 152,
    LIFTED_F4D59F0_STACK = 88,
    LIFTED_F4D5A70_STACK = 88,
    LIFTED_F4D5AB0_STACK = 472,
    LIFTED_F4D5BF8_STACK = 92,
    LIFTED_F4D5C70_STACK = 92,
    LIFTED_F4D6080_STACK = 100,
    LIFTED_F4D62E0_STACK = 76,
    LIFTED_F4D63B0_STACK = 76,
    LIFTED_F4D63D0_STACK = 76,
    LIFTED_RETURN_CONSTANT_4D54C0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D5660_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D57A0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D57C0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D6080_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D58E0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D4E00_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D4E30_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D5360_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D4990_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D4D10_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D4C00_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D62E0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D6300_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D4EE0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D4FD0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D5010_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D50D0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D5150_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D5180_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D4270_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D4630_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D41C0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D41A0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D42A0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D4300_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D4E60_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D5A30_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D5A70_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D5BF8_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D5C70_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D5AB0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D51C0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D5280_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D5330_STACK = 64
};

/* Original 0x4b7020. */
uint32_t lifted_f4b7020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7c90. */
uint32_t lifted_f4b7c90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7db0. */
uint32_t lifted_f4b7db0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7e80. */
uint32_t lifted_wave_load(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b8170. */
uint32_t lifted_two_step_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b8187. */
uint32_t lifted_f4b8187(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b826f. */
uint32_t lifted_f4b826f(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_return_unchanged_4b9ce0(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
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
uint32_t lifted_return_zero(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ba220. */
uint32_t lifted_f4ba220(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bb040. */
uint32_t lifted_f4bb040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bb260. */
uint32_t lifted_return_unchanged_4bb260(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
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

/* Original 0x4c3e60. */
uint32_t lifted_f4c3e60(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4c3fa0. */
uint32_t lifted_object_init_4c3fa0(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c4000. */
uint32_t lifted_f4c4000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c4730. */
uint32_t lifted_f4c4730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c4b00. */
uint32_t lifted_f4c4b00(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4c5a40. */
uint32_t lifted_f4c5a40(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_return_zero_4c5c10(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5c20. */
uint32_t lifted_return_unchanged_4c5c20(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
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
uint32_t lifted_return_unchanged_4c6a80(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c6c70. */
uint32_t lifted_f4c6c70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c70f0. */
uint32_t lifted_f4c70f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c8500. */
uint32_t lifted_f4c8500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c8be0. */
uint32_t lifted_f4c8be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9030. */
uint32_t lifted_f4c9030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c93c0. */
uint32_t lifted_return_unchanged_4c93c0(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
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

/* Original 0x4c9fe0. */
uint32_t lifted_f4c9fe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca040. */
uint32_t lifted_f4ca040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca050. */
uint32_t lifted_f4ca050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca240. */
uint32_t lifted_rtl_string_copy_pair(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca3a0. */
uint32_t lifted_rtl_wide_assign(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca430. */
uint32_t lifted_rtl_string_concat(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca4a0. */
uint32_t lifted_f4ca4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca650. */
uint32_t lifted_f4ca650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca6f0. */
uint32_t lifted_rtl_string_set_length(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca730. */
uint32_t lifted_f4ca730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca770. */
uint32_t lifted_f4ca770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb390. */
uint32_t lifted_return_constant_4cc7a0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb3a0. */
uint32_t lifted_return_constant_4ccaf0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb3b0. */
uint32_t lifted_return_constant_4ccb40(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb4f0. */
uint32_t lifted_f4cb4f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb5a0. */
uint32_t lifted_f4cb5a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cba60. */
uint32_t lifted_f4cba60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cba70. */
uint32_t lifted_rtl_record_clear(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cbc90. */
uint32_t lifted_f4cbc90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cbe80. */
uint32_t lifted_rtl_record_field(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cbfe0. */
uint32_t lifted_f4cbfe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4cc760. */
uint32_t lifted_f4cc760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc780. */
uint32_t lifted_f4cc780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc7a0. */
uint32_t lifted_f4cc7a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4cccc0. */
uint32_t lifted_f4cccc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccd80. */
uint32_t lifted_f4ccd80(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4cce90. */
uint32_t lifted_f4cce90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccee0. */
uint32_t lifted_rtl_link_owner(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd0a4. */
uint32_t lifted_rtl_terminate_call(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd544. */
uint32_t lifted_rtl_vararg_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd56c. */
uint32_t lifted_f4cd56c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd7dc. */
uint32_t lifted_f4cd7dc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd836. */
uint32_t lifted_f4cd836(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd847. */
uint32_t lifted_f4cd847(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd9f0. */
uint32_t lifted_rtl_local_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cda12. */
uint32_t lifted_rtl_local_chain_call(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cda90. */
uint32_t lifted_rtl_string_fill(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cdad0. */
uint32_t lifted_f4cdad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cdb70. */
uint32_t lifted_f4cdb70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cdbe0. */
uint32_t lifted_f4cdbe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cdfb0. */
uint32_t lifted_f4cdfb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce080. */
uint32_t lifted_f4ce080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf320. */
uint32_t lifted_rtl_construct_buffer_stream(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf4a0. */
uint32_t lifted_f4cf4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf4d0. */
uint32_t lifted_f4cf4d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4cf8d0. */
uint32_t lifted_f4cf8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf8e0. */
uint32_t lifted_rtl_triple_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf910. */
uint32_t lifted_f4cf910(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4cfa20. */
uint32_t lifted_f4cfa20(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d01a0. */
uint32_t lifted_f4d01a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d0410. */
uint32_t lifted_f4d0410(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d0620. */
uint32_t lifted_f4d0620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d0650. */
uint32_t lifted_f4d0650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d0670. */
uint32_t lifted_f4d0670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d06a0. */
uint32_t lifted_f4d06a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d1e50. */
uint32_t lifted_f4d1e50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1e80. */
uint32_t lifted_f4d1e80(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d23f0. */
uint32_t lifted_f4d23f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2420. */
uint32_t lifted_f4d2420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2440. */
uint32_t lifted_f4d2440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2460. */
uint32_t lifted_f4d2460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d24a0. */
uint32_t lifted_f4d24a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2540. */
uint32_t lifted_f4d2540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d25e0. */
uint32_t lifted_return_constant_ffff(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2d70. */
uint32_t lifted_object_status_active(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2ea0. */
uint32_t lifted_return_constant_4d09b0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2eb0. */
uint32_t lifted_return_constant_4d05e0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2ec0. */
uint32_t lifted_return_constant_4d0740(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2ed0. */
uint32_t lifted_return_constant_4d24a0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2ee0. */
uint32_t lifted_return_constant_4d0620(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2ef0. */
uint32_t lifted_return_constant_4d2460(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2f00. */
uint32_t lifted_return_constant_4d2420(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2f10. */
uint32_t lifted_return_constant_4d2440(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2f20. */
uint32_t lifted_return_constant_4d0650(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2f30. */
uint32_t lifted_return_constant_4d0670(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2f40. */
uint32_t lifted_return_constant_4d06a0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2f50. */
uint32_t lifted_return_constant_4d02a0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2f60. */
uint32_t lifted_return_constant_4d2170(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2f70. */
uint32_t lifted_return_constant_4d21d0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2f80. */
uint32_t lifted_return_constant_4d2260(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2f90. */
uint32_t lifted_return_constant_4d22b0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2fa0. */
uint32_t lifted_return_constant_4d2310(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2fb0. */
uint32_t lifted_return_constant_4d21a0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2fc0. */
uint32_t lifted_rtl_scope_refresh_address(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2fd0. */
uint32_t lifted_return_constant_4d23f0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d3010. */
uint32_t lifted_f4d3010(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d3020. */
uint32_t lifted_rtl_swapped_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d3040. */
uint32_t lifted_f4d3040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d3120. */
uint32_t lifted_rtl_class_chain_contains(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d3e20. */
uint32_t lifted_f4d3e20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d3f70. */
uint32_t lifted_object_destroy_f(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4040. */
uint32_t lifted_f4d4040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4060. */
uint32_t lifted_rtl_record_forward(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d41a0. */
uint32_t lifted_f4d41a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d41c0. */
uint32_t lifted_f4d41c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4270. */
uint32_t lifted_f4d4270(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d42a0. */
uint32_t lifted_f4d42a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4300. */
uint32_t lifted_f4d4300(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4390. */
uint32_t lifted_rtl_ancestor_search(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4630. */
uint32_t lifted_f4d4630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4700. */
uint32_t lifted_f4d4700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4990. */
uint32_t lifted_f4d4990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d49a0. */
uint32_t lifted_f4d49a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4d10. */
uint32_t lifted_f4d4d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4e00. */
uint32_t lifted_f4d4e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4e30. */
uint32_t lifted_f4d4e30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4e60. */
uint32_t lifted_f4d4e60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4fd0. */
uint32_t lifted_f4d4fd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5010. */
uint32_t lifted_f4d5010(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5150. */
uint32_t lifted_f4d5150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5180. */
uint32_t lifted_f4d5180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d51c0. */
uint32_t lifted_f4d51c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5330. */
uint32_t lifted_f4d5330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5350. */
uint32_t lifted_object_dword_4d5350(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5390. */
uint32_t lifted_f4d5390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d54c0. */
uint32_t lifted_f4d54c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5660. */
uint32_t lifted_f4d5660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d57a0. */
uint32_t lifted_f4d57a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d58e0. */
uint32_t lifted_f4d58e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5910. */
uint32_t lifted_f4d5910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5930. */
uint32_t lifted_f4d5930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d59f0. */
uint32_t lifted_f4d59f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5a70. */
uint32_t lifted_f4d5a70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5ab0. */
uint32_t lifted_f4d5ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5bf8. */
uint32_t lifted_f4d5bf8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5c70. */
uint32_t lifted_f4d5c70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6080. */
uint32_t lifted_f4d6080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d62e0. */
uint32_t lifted_f4d62e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d63b0. */
uint32_t lifted_f4d63b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d63d0. */
uint32_t lifted_f4d63d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6490. */
uint32_t lifted_return_constant_4d54c0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d64a0. */
uint32_t lifted_return_constant_4d5660(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d64b0. */
uint32_t lifted_return_constant_4d57a0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d64c0. */
uint32_t lifted_return_constant_4d57c0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d64d0. */
uint32_t lifted_return_constant_4d6080(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d64e0. */
uint32_t lifted_return_constant_4d58e0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d64f0. */
uint32_t lifted_return_constant_4d4e00(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6500. */
uint32_t lifted_return_constant_4d4e30(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6510. */
uint32_t lifted_return_constant_4d5360(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6520. */
uint32_t lifted_return_constant_4d4990(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6530. */
uint32_t lifted_return_constant_4d4d10(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6540. */
uint32_t lifted_return_constant_4d4c00(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6550. */
uint32_t lifted_return_constant_4d62e0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6560. */
uint32_t lifted_return_constant_4d6300(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6570. */
uint32_t lifted_return_constant_4d4ee0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6580. */
uint32_t lifted_return_constant_4d4fd0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6590. */
uint32_t lifted_return_constant_4d5010(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d65a0. */
uint32_t lifted_return_constant_4d50d0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d65b0. */
uint32_t lifted_return_constant_4d5150(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d65c0. */
uint32_t lifted_return_constant_4d5180(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d65d0. */
uint32_t lifted_return_constant_4d4270(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d65e0. */
uint32_t lifted_return_constant_4d4630(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d65f0. */
uint32_t lifted_return_constant_4d41c0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6600. */
uint32_t lifted_return_constant_4d41a0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6610. */
uint32_t lifted_return_constant_4d42a0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6620. */
uint32_t lifted_return_constant_4d4300(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6630. */
uint32_t lifted_return_constant_4d4e60(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6640. */
uint32_t lifted_return_constant_4d5a30(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6650. */
uint32_t lifted_return_constant_4d5a70(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6660. */
uint32_t lifted_return_constant_4d5bf8(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6670. */
uint32_t lifted_return_constant_4d5c70(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6680. */
uint32_t lifted_return_constant_4d5ab0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6690. */
uint32_t lifted_return_constant_4d51c0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d66a0. */
uint32_t lifted_return_constant_4d5280(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d66b0. */
uint32_t lifted_return_constant_4d5330(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);
#endif
