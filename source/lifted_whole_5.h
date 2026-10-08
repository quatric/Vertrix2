#ifndef VERTRIX_LIFTED_WHOLE_5_H
#define VERTRIX_LIFTED_WHOLE_5_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_RETURN_CONSTANT_FFFF_STACK = 64,
    LIFTED_F4D28C0_STACK = 128,
    LIFTED_F4D2910_STACK = 136,
    LIFTED_F4D2A00_STACK = 252,
    LIFTED_F4D2BB0_STACK = 104,
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
    LIFTED_F4D30F0_STACK = 104,
    LIFTED_RTL_CLASS_CHAIN_CONTAINS_STACK = 68,
    LIFTED_F4D3E20_STACK = 136,
    LIFTED_OBJECT_DESTROY_F_STACK = 152,
    LIFTED_F4D4040_STACK = 84,
    LIFTED_RTL_RECORD_FORWARD_STACK = 84,
    LIFTED_F4D4080_STACK = 92,
    LIFTED_F4D41A0_STACK = 76,
    LIFTED_F4D41C0_STACK = 80,
    LIFTED_F4D4270_STACK = 84,
    LIFTED_F4D42A0_STACK = 84,
    LIFTED_F4D4300_STACK = 64,
    LIFTED_RTL_ANCESTOR_SEARCH_STACK = 76,
    LIFTED_F4D4570_STACK = 172,
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
    LIFTED_F4D59F0_STACK = 88,
    LIFTED_F4D5A70_STACK = 88,
    LIFTED_F4D5BF8_STACK = 92,
    LIFTED_F4D5C70_STACK = 92,
    LIFTED_F4D6080_STACK = 100,
    LIFTED_F4D62E0_STACK = 76,
    LIFTED_F4D6380_STACK = 84,
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
    LIFTED_RETURN_CONSTANT_4D5330_STACK = 64,
    LIFTED_RTL_TEST_AND_SET_STACK = 80,
    LIFTED_RTL_PARSE_INTEGER_STACK = 76,
    LIFTED_F4D6768_STACK = 68,
    LIFTED_RTL_INTEGER_TO_DOUBLE_STACK = 68,
    LIFTED_F4D67A8_STACK = 72,
    LIFTED_RTL_MODE_CALL_STACK = 72,
    LIFTED_RTL_FLOAT_TO_INTEGER_STACK = 64,
    LIFTED_F4D6A30_STACK = 80,
    LIFTED_F4D6F10_STACK = 108,
    LIFTED_F4D6F50_STACK = 112,
    LIFTED_F4D70E0_STACK = 92,
    LIFTED_F4D7140_STACK = 128,
    LIFTED_F4D73C0_STACK = 80,
    LIFTED_F4D7400_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D73B0_STACK = 64,
    LIFTED_F4D7440_STACK = 64,
    LIFTED_F4D7450_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D73C0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D7400_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D25E0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D7140_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D7110_STACK = 64,
    LIFTED_F4D74A6_STACK = 68,
    LIFTED_F4D7510_STACK = 112,
    LIFTED_F4D75A0_STACK = 112,
    LIFTED_F4D7630_STACK = 144,
    LIFTED_F4D7AA0_STACK = 104,
    LIFTED_F4D7C00_STACK = 88,
    LIFTED_F4D7D70_STACK = 120,
    LIFTED_F4D7E50_STACK = 1748,
    LIFTED_RTL_SIGN_COMPARE_STACK = 64,
    LIFTED_F4D80D5_STACK = 84,
    LIFTED_F4D8198_STACK = 80,
    LIFTED_RTL_SINGLE_DIVIDE_SOFTWARE_FULL_STACK = 88,
    LIFTED_RTL_CONSTRUCT_CHUNK_LIST_STACK = 104,
    LIFTED_F4D83C0_STACK = 72,
    LIFTED_F4D83F0_STACK = 136,
    LIFTED_NODE_POOL_TAKE_PAIR_STACK = 92,
    LIFTED_F4D84F0_STACK = 72,
    LIFTED_F4D8510_STACK = 80,
    LIFTED_F4D8540_STACK = 80,
    LIFTED_RTL_WIDE_LENGTH_STACK = 72,
    LIFTED_F4D85A0_STACK = 72,
    LIFTED_F4D85F0_STACK = 68,
    LIFTED_F4D85FC_STACK = 72,
    LIFTED_F4D8650_STACK = 104,
    LIFTED_F4D86D0_STACK = 136,
    LIFTED_F4D8770_STACK = 112,
    LIFTED_F4D8950_STACK = 80,
    LIFTED_F4D8B30_STACK = 84,
    LIFTED_OBJECT_DESTROY_G_STACK = 136,
    LIFTED_NODE_POOL_TAKE_INITIALISED_STACK = 104,
    LIFTED_F4D9280_STACK = 104,
    LIFTED_F4D92F0_STACK = 104,
    LIFTED_F4D9350_STACK = 76,
    LIFTED_F4D93F0_STACK = 96,
    LIFTED_F4D9430_STACK = 88,
    LIFTED_RTL_FORWARD_PAIR_STACK = 88,
    LIFTED_F4D9AE0_STACK = 64,
    LIFTED_RTL_ZERO_CALL3_STACK = 100,
    LIFTED_F4DA71B_STACK = 100,
    LIFTED_RTL_COPY_TERMINATED_STACK = 84,
    LIFTED_F4DABB0_STACK = 64,
    LIFTED_F4DACA0_STACK = 72,
    LIFTED_RTL_NEGATE_DOUBLE_STACK = 64,
    LIFTED_F4DAE70_STACK = 72,
    LIFTED_F4DAEB8_STACK = 72,
    LIFTED_F4DB131_STACK = 88,
    LIFTED_F4DB6A4_STACK = 88,
    LIFTED_F4DB980_STACK = 100,
    LIFTED_F4DBA10_STACK = 72,
    LIFTED_F4DBA20_STACK = 76,
    LIFTED_F4DBA80_STACK = 84,
    LIFTED_F4DBAA0_STACK = 72,
    LIFTED_F4DBAC0_STACK = 88,
    LIFTED_F4DBC60_STACK = 104,
    LIFTED_F4DBCD0_STACK = 100,
    LIFTED_F4DC000_STACK = 72,
    LIFTED_F4DC190_STACK = 72,
    LIFTED_F4DC1C0_STACK = 72,
    LIFTED_F4DC290_STACK = 116,
    LIFTED_F4DC400_STACK = 76,
    LIFTED_F4DC420_STACK = 156,
    LIFTED_F4DC4B0_STACK = 96,
    LIFTED_F4DC6C0_STACK = 732,
    LIFTED_F4DCC70_STACK = 192,
    LIFTED_F4DD0C0_STACK = 180,
    LIFTED_F4DD160_STACK = 68,
    LIFTED_RTL_RECORD_SET_ARGUMENT_STACK = 68,
    LIFTED_F4DD180_STACK = 68,
    LIFTED_RTL_CONSTRUCT_LIST_STACK = 104,
    LIFTED_F4DD3E0_STACK = 92,
    LIFTED_F4DD460_STACK = 88,
    LIFTED_F4DD4A0_STACK = 152,
    LIFTED_F4DDBE0_STACK = 92,
    LIFTED_RTL_RELEASE_LIST_HEAD_STACK = 84,
    LIFTED_F4DDC90_STACK = 84,
    LIFTED_F4DE5C0_STACK = 80,
    LIFTED_F4DE600_STACK = 80,
    LIFTED_F4DE630_STACK = 140,
    LIFTED_F4DE810_STACK = 252,
    LIFTED_F4DE900_STACK = 148,
    LIFTED_F4DEA40_STACK = 72,
    LIFTED_F4DEA78_STACK = 68,
    LIFTED_RTL_RECORD_INCREMENT_STACK = 68,
    LIFTED_F4DEC70_STACK = 104,
    LIFTED_RTL_CONSTRUCT_EVENT_TABLE_STACK = 124,
    LIFTED_RTL_SEGMENT_DISPATCH_STACK = 84,
    LIFTED_RTL_CONSTRUCT_TABLE_STACK = 104,
    LIFTED_F4DEF50_STACK = 84,
    LIFTED_F4DEF90_STACK = 76,
    LIFTED_F4DEFD0_STACK = 136,
    LIFTED_F4DF0D0_STACK = 72,
    LIFTED_F4DF1C0_STACK = 76,
    LIFTED_FORMAT_SPEC_STACK = 80,
    LIFTED_RTL_PARSE_FORMAT_FLAGS_STACK = 72,
    LIFTED_F4DFA74_STACK = 68,
    LIFTED_RTL_DISTRIBUTE_SLACK_STACK = 88,
    LIFTED_F4E012C_STACK = 76,
    LIFTED_F4E0150_STACK = 116,
    LIFTED_F4E01D0_STACK = 80,
    LIFTED_F4E0228_STACK = 68,
    LIFTED_F4E0250_STACK = 76,
    LIFTED_F4E03FC_STACK = 76,
    LIFTED_F4E0430_STACK = 120,
    LIFTED_F4E0508_STACK = 156,
    LIFTED_F4E0738_STACK = 116,
    LIFTED_F4E081C_STACK = 84,
    LIFTED_F4E0884_STACK = 80,
    LIFTED_F4E0960_STACK = 64,
    LIFTED_F4E0994_STACK = 68,
    LIFTED_F4E09F0_STACK = 68,
    LIFTED_F4E0A30_STACK = 104,
    LIFTED_F4E0A95_STACK = 64,
    LIFTED_F4E0AE5_STACK = 104,
    LIFTED_F4E0B9E_STACK = 84,
    LIFTED_F4E0BED_STACK = 72,
    LIFTED_F4E0BF8_STACK = 76,
    LIFTED_F4E0EAF_STACK = 64,
    LIFTED_F4E0EC7_STACK = 152,
    LIFTED_F4E0FC0_STACK = 120,
    LIFTED_F4E104E_STACK = 84,
    LIFTED_F4E1054_STACK = 68,
    LIFTED_F4E105A_STACK = 64,
    LIFTED_F4E11B0_STACK = 92,
    LIFTED_F4E1210_STACK = 72,
    LIFTED_F4E1260_STACK = 84,
    LIFTED_F4E1290_STACK = 84,
    LIFTED_F4E14A3_STACK = 72,
    LIFTED_F4E14B0_STACK = 68,
    LIFTED_F4E14B7_STACK = 68,
    LIFTED_F4E14F0_STACK = 80,
    LIFTED_F4E1520_STACK = 108,
    LIFTED_F4E1590_STACK = 80,
    LIFTED_F4E15B0_STACK = 68,
    LIFTED_F4E15C0_STACK = 68,
    LIFTED_F4E1620_STACK = 88,
    LIFTED_F4E1700_STACK = 120,
    LIFTED_F4E1982_STACK = 100,
    LIFTED_F4E1990_STACK = 92,
    LIFTED_F4E19F0_STACK = 104,
    LIFTED_F4E1BF0_STACK = 96,
    LIFTED_F4E2371_STACK = 68,
    LIFTED_F4E237D_STACK = 68,
    LIFTED_F4E2389_STACK = 76,
    LIFTED_F4E2400_STACK = 72,
    LIFTED_F4E2420_STACK = 72,
    LIFTED_F4E2434_STACK = 104,
    LIFTED_F4E26E0_STACK = 128,
    LIFTED_F4E28E0_STACK = 128,
    LIFTED_F4E2A30_STACK = 108,
    LIFTED_F4E2AD0_STACK = 108,
    LIFTED_F4E2B60_STACK = 124,
    LIFTED_F4E2C40_STACK = 92,
    LIFTED_F4E2CC0_STACK = 84,
    LIFTED_F4E2D40_STACK = 84,
    LIFTED_F4E2D60_STACK = 120,
    LIFTED_F4E2F10_STACK = 148,
    LIFTED_F4E3060_STACK = 116,
    LIFTED_F4E3420_STACK = 96,
    LIFTED_F4E34C0_STACK = 68,
    LIFTED_F4E3530_STACK = 116,
    LIFTED_F4E3681_STACK = 76,
    LIFTED_F4E3694_STACK = 64,
    LIFTED_F4E36C4_STACK = 68,
    LIFTED_F4E36D2_STACK = 68,
    LIFTED_F4E36E4_STACK = 76,
    LIFTED_F4E370F_STACK = 72,
    LIFTED_F4E371E_STACK = 76,
    LIFTED_F4E373E_STACK = 76,
    LIFTED_F4E3743_STACK = 76,
    LIFTED_F4E37FE_STACK = 68,
    LIFTED_F4E3814_STACK = 64,
    LIFTED_F4E3846_STACK = 96,
    LIFTED_F4E38FF_STACK = 84,
    LIFTED_F4E39A0_STACK = 80,
    LIFTED_F4E39D0_STACK = 80,
    LIFTED_F4E39F0_STACK = 88,
    LIFTED_F4E3A50_STACK = 68,
    LIFTED_F4E3A90_STACK = 68,
    LIFTED_F4E3BF0_STACK = 176,
    LIFTED_F4E3CE0_STACK = 112,
    LIFTED_F4E3F28_STACK = 88,
    LIFTED_F4E4024_STACK = 84,
    LIFTED_F4E4080_STACK = 100,
    LIFTED_F4E4110_STACK = 160,
    LIFTED_F4E43C4_STACK = 80,
    LIFTED_F4E44C8_STACK = 92,
    LIFTED_F4E47A8_STACK = 80,
    LIFTED_F4E4FD0_STACK = 68,
    LIFTED_F4E4FF8_STACK = 76,
    LIFTED_F4E5024_STACK = 96,
    LIFTED_F4E506C_STACK = 84,
    LIFTED_F4E5177_STACK = 64,
    LIFTED_F4E5271_STACK = 88,
    LIFTED_F4E532C_STACK = 76,
    LIFTED_F4E53B4_STACK = 84,
    LIFTED_F4E543C_STACK = 92,
    LIFTED_F4E5678_STACK = 88,
    LIFTED_F4E56A8_STACK = 104,
    LIFTED_F4E5700_STACK = 64,
    LIFTED_F4E571C_STACK = 88,
    LIFTED_F4E5738_STACK = 88,
    LIFTED_F4E5750_STACK = 76,
    LIFTED_F4E5774_STACK = 88,
    LIFTED_F4E5788_STACK = 88,
    LIFTED_F4E579C_STACK = 88,
    LIFTED_F4E5808_STACK = 88,
    LIFTED_F4E5810_STACK = 88,
    LIFTED_F4E5838_STACK = 108,
    LIFTED_F4E587C_STACK = 80,
    LIFTED_F4E58B8_STACK = 84,
    LIFTED_F4E5918_STACK = 100,
    LIFTED_F4E596C_STACK = 116,
    LIFTED_F4E59F4_STACK = 108,
    LIFTED_F4E5BEC_STACK = 72,
    LIFTED_F4E5CD1_STACK = 104,
    LIFTED_F4E5FE4_STACK = 88,
    LIFTED_F4E628C_STACK = 80,
    LIFTED_F4E6320_STACK = 120,
    LIFTED_F4E636C_STACK = 72,
    LIFTED_F4E64A0_STACK = 120,
    LIFTED_F4E6510_STACK = 160,
    LIFTED_F4E6600_STACK = 88,
    LIFTED_F4E66A0_STACK = 100,
    LIFTED_F4E66DC_STACK = 76,
    LIFTED_F4E6734_STACK = 384,
    LIFTED_F4E6B2C_STACK = 76,
    LIFTED_F4E6BFF_STACK = 72,
    LIFTED_F4E6C1D_STACK = 72,
    LIFTED_F4E6C98_STACK = 80,
    LIFTED_F4E6CD4_STACK = 68,
    LIFTED_F4E6CF2_STACK = 64,
    LIFTED_F4E6F30_STACK = 64,
    LIFTED_F4E70D0_STACK = 72,
    LIFTED_F4E7120_STACK = 68,
    LIFTED_F4E7140_STACK = 72,
    LIFTED_F4E7280_STACK = 68,
    LIFTED_F4E7540_STACK = 104,
    LIFTED_F4E7660_STACK = 112,
    LIFTED_F4E7850_STACK = 108,
    LIFTED_F4E7A00_STACK = 84,
    LIFTED_F4E7B18_STACK = 76,
    LIFTED_F4E7B50_STACK = 68,
    LIFTED_F4E7B90_STACK = 76,
    LIFTED_F4E7BF0_STACK = 80,
    LIFTED_F4E7C30_STACK = 104,
    LIFTED_F4E7E44_STACK = 76,
    LIFTED_F4E7EB0_STACK = 88,
    LIFTED_F4E7EF4_STACK = 76,
    LIFTED_F4E7F0C_STACK = 64,
    LIFTED_F4E8230_STACK = 116,
    LIFTED_F4E82D0_STACK = 72,
    LIFTED_F4E82F0_STACK = 64,
    LIFTED_F4E8310_STACK = 68,
    LIFTED_F4E8330_STACK = 104,
    LIFTED_F4E8400_STACK = 92,
    LIFTED_F4E8574_STACK = 92,
    LIFTED_F4E85C0_STACK = 76,
    LIFTED_F4E8620_STACK = 84,
    LIFTED_F4E8650_STACK = 84,
    LIFTED_F4E8660_STACK = 92,
    LIFTED_F4E869C_STACK = 100,
    LIFTED_F4E86FC_STACK = 76,
    LIFTED_F4E8730_STACK = 72,
    LIFTED_F4E8790_STACK = 68,
    LIFTED_F4E88BF_STACK = 76,
    LIFTED_F4E8950_STACK = 64,
    LIFTED_F4E8978_STACK = 144,
    LIFTED_F4E89E8_STACK = 68,
    LIFTED_F4E89F4_STACK = 68,
    LIFTED_F4E8A58_STACK = 72,
    LIFTED_F4E8A7C_STACK = 72,
    LIFTED_F4E8AA0_STACK = 76
};

/* Original 0x4d25e0. */
uint32_t lifted_return_constant_ffff(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d28c0. */
uint32_t lifted_f4d28c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2910. */
uint32_t lifted_f4d2910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2a00. */
uint32_t lifted_f4d2a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2bb0. */
uint32_t lifted_f4d2bb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d30f0. */
uint32_t lifted_f4d30f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d4080. */
uint32_t lifted_f4d4080(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d4570. */
uint32_t lifted_f4d4570(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d59f0. */
uint32_t lifted_f4d59f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5a70. */
uint32_t lifted_f4d5a70(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d6380. */
uint32_t lifted_f4d6380(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d66cd. */
uint32_t lifted_rtl_test_and_set(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6710. */
uint32_t lifted_rtl_parse_integer(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6768. */
uint32_t lifted_f4d6768(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6775. */
uint32_t lifted_rtl_integer_to_double(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d67a8. */
uint32_t lifted_f4d67a8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d67b2. */
uint32_t lifted_rtl_mode_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d67f0. */
uint32_t lifted_rtl_float_to_integer(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6a30. */
uint32_t lifted_f4d6a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6f10. */
uint32_t lifted_f4d6f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6f50. */
uint32_t lifted_f4d6f50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d70e0. */
uint32_t lifted_f4d70e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7140. */
uint32_t lifted_f4d7140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d73c0. */
uint32_t lifted_f4d73c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7400. */
uint32_t lifted_f4d7400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7430. */
uint32_t lifted_return_constant_4d73b0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7440. */
uint32_t lifted_f4d7440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7450. */
uint32_t lifted_f4d7450(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7460. */
uint32_t lifted_return_constant_4d73c0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7470. */
uint32_t lifted_return_constant_4d7400(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7480. */
uint32_t lifted_return_constant_4d25e0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7490. */
uint32_t lifted_return_constant_4d7140(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d74a0. */
uint32_t lifted_return_constant_4d7110(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d74a6. */
uint32_t lifted_f4d74a6(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7510. */
uint32_t lifted_f4d7510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d75a0. */
uint32_t lifted_f4d75a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7630. */
uint32_t lifted_f4d7630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7aa0. */
uint32_t lifted_f4d7aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7c00. */
uint32_t lifted_f4d7c00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7d70. */
uint32_t lifted_f4d7d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7e50. */
uint32_t lifted_f4d7e50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8082. */
uint32_t lifted_rtl_sign_compare(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d80d5. */
uint32_t lifted_f4d80d5(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8198. */
uint32_t lifted_f4d8198(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8227. */
uint32_t lifted_rtl_single_divide_software_full(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x4d8340. */
uint32_t lifted_rtl_construct_chunk_list(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d83c0. */
uint32_t lifted_f4d83c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d83f0. */
uint32_t lifted_f4d83f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8490. */
uint32_t lifted_node_pool_take_pair(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d84f0. */
uint32_t lifted_f4d84f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8510. */
uint32_t lifted_f4d8510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8540. */
uint32_t lifted_f4d8540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8580. */
uint32_t lifted_rtl_wide_length(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d85a0. */
uint32_t lifted_f4d85a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d85f0. */
uint32_t lifted_f4d85f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d85fc. */
uint32_t lifted_f4d85fc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8650. */
uint32_t lifted_f4d8650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d86d0. */
uint32_t lifted_f4d86d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8770. */
uint32_t lifted_f4d8770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8950. */
uint32_t lifted_f4d8950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8b30. */
uint32_t lifted_f4d8b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8b80. */
uint32_t lifted_object_destroy_g(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8c20. */
uint32_t lifted_node_pool_take_initialised(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9280. */
uint32_t lifted_f4d9280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d92f0. */
uint32_t lifted_f4d92f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9350. */
uint32_t lifted_f4d9350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d93f0. */
uint32_t lifted_f4d93f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9430. */
uint32_t lifted_f4d9430(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9930. */
uint32_t lifted_rtl_forward_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9ae0. */
uint32_t lifted_f4d9ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4da66e. */
uint32_t lifted_rtl_zero_call3(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4da71b. */
uint32_t lifted_f4da71b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4daab0. */
uint32_t lifted_rtl_copy_terminated(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dabb0. */
uint32_t lifted_f4dabb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4daca0. */
uint32_t lifted_f4daca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dae4a. */
uint32_t lifted_rtl_negate_double(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dae70. */
uint32_t lifted_f4dae70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4daeb8. */
uint32_t lifted_f4daeb8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db131. */
uint32_t lifted_f4db131(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db6a4. */
uint32_t lifted_f4db6a4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db980. */
uint32_t lifted_f4db980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dba10. */
uint32_t lifted_f4dba10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dba20. */
uint32_t lifted_f4dba20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dba80. */
uint32_t lifted_f4dba80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dbaa0. */
uint32_t lifted_f4dbaa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dbac0. */
uint32_t lifted_f4dbac0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dbc60. */
uint32_t lifted_f4dbc60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dbcd0. */
uint32_t lifted_f4dbcd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc000. */
uint32_t lifted_f4dc000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc190. */
uint32_t lifted_f4dc190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc1c0. */
uint32_t lifted_f4dc1c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc290. */
uint32_t lifted_f4dc290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc400. */
uint32_t lifted_f4dc400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc420. */
uint32_t lifted_f4dc420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc4b0. */
uint32_t lifted_f4dc4b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc6c0. */
uint32_t lifted_f4dc6c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dcc70. */
uint32_t lifted_f4dcc70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd0c0. */
uint32_t lifted_f4dd0c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd160. */
uint32_t lifted_f4dd160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd170. */
uint32_t lifted_rtl_record_set_argument(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd180. */
uint32_t lifted_f4dd180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd360. */
uint32_t lifted_rtl_construct_list(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd3e0. */
uint32_t lifted_f4dd3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd460. */
uint32_t lifted_f4dd460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd4a0. */
uint32_t lifted_f4dd4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ddbe0. */
uint32_t lifted_f4ddbe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ddc60. */
uint32_t lifted_rtl_release_list_head(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ddc90. */
uint32_t lifted_f4ddc90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4de5c0. */
uint32_t lifted_f4de5c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4de600. */
uint32_t lifted_f4de600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4de630. */
uint32_t lifted_f4de630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4de810. */
uint32_t lifted_f4de810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4de900. */
uint32_t lifted_f4de900(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dea40. */
uint32_t lifted_f4dea40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dea78. */
uint32_t lifted_f4dea78(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dec60. */
uint32_t lifted_rtl_record_increment(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dec70. */
uint32_t lifted_f4dec70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4decd0. */
uint32_t lifted_rtl_construct_event_table(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dee73. */
uint32_t lifted_rtl_segment_dispatch(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4deec0. */
uint32_t lifted_rtl_construct_table(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4def50. */
uint32_t lifted_f4def50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4def90. */
uint32_t lifted_f4def90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4defd0. */
uint32_t lifted_f4defd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df0d0. */
uint32_t lifted_f4df0d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df1c0. */
uint32_t lifted_f4df1c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df6c8. */
uint32_t lifted_format_spec(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df81c. */
uint32_t lifted_rtl_parse_format_flags(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dfa74. */
uint32_t lifted_f4dfa74(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dfa7c. */
uint32_t lifted_rtl_distribute_slack(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e012c. */
uint32_t lifted_f4e012c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0150. */
uint32_t lifted_f4e0150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e01d0. */
uint32_t lifted_f4e01d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0228. */
uint32_t lifted_f4e0228(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0250. */
uint32_t lifted_f4e0250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e03fc. */
uint32_t lifted_f4e03fc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0430. */
uint32_t lifted_f4e0430(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0508. */
uint32_t lifted_f4e0508(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0738. */
uint32_t lifted_f4e0738(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e081c. */
uint32_t lifted_f4e081c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0884. */
uint32_t lifted_f4e0884(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0960. */
uint32_t lifted_f4e0960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0994. */
uint32_t lifted_f4e0994(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e09f0. */
uint32_t lifted_f4e09f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0a30. */
uint32_t lifted_f4e0a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0a95. */
uint32_t lifted_f4e0a95(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0ae5. */
uint32_t lifted_f4e0ae5(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0b9e. */
uint32_t lifted_f4e0b9e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0bed. */
uint32_t lifted_f4e0bed(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0bf8. */
uint32_t lifted_f4e0bf8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0eaf. */
uint32_t lifted_f4e0eaf(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0ec7. */
uint32_t lifted_f4e0ec7(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0fc0. */
uint32_t lifted_f4e0fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e104e. */
uint32_t lifted_f4e104e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1054. */
uint32_t lifted_f4e1054(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e105a. */
uint32_t lifted_f4e105a(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e11b0. */
uint32_t lifted_f4e11b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1210. */
uint32_t lifted_f4e1210(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1260. */
uint32_t lifted_f4e1260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1290. */
uint32_t lifted_f4e1290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e14a3. */
uint32_t lifted_f4e14a3(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e14b0. */
uint32_t lifted_f4e14b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e14b7. */
uint32_t lifted_f4e14b7(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e14f0. */
uint32_t lifted_f4e14f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1520. */
uint32_t lifted_f4e1520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1590. */
uint32_t lifted_f4e1590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e15b0. */
uint32_t lifted_f4e15b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e15c0. */
uint32_t lifted_f4e15c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1620. */
uint32_t lifted_f4e1620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1700. */
uint32_t lifted_f4e1700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1982. */
uint32_t lifted_f4e1982(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1990. */
uint32_t lifted_f4e1990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e19f0. */
uint32_t lifted_f4e19f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1bf0. */
uint32_t lifted_f4e1bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2371. */
uint32_t lifted_f4e2371(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e237d. */
uint32_t lifted_f4e237d(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2389. */
uint32_t lifted_f4e2389(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2400. */
uint32_t lifted_f4e2400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2420. */
uint32_t lifted_f4e2420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2434. */
uint32_t lifted_f4e2434(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e26e0. */
uint32_t lifted_f4e26e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e28e0. */
uint32_t lifted_f4e28e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2a30. */
uint32_t lifted_f4e2a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2ad0. */
uint32_t lifted_f4e2ad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2b60. */
uint32_t lifted_f4e2b60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2c40. */
uint32_t lifted_f4e2c40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2cc0. */
uint32_t lifted_f4e2cc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2d40. */
uint32_t lifted_f4e2d40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2d60. */
uint32_t lifted_f4e2d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2f10. */
uint32_t lifted_f4e2f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3060. */
uint32_t lifted_f4e3060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3420. */
uint32_t lifted_f4e3420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e34c0. */
uint32_t lifted_f4e34c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3530. */
uint32_t lifted_f4e3530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3681. */
uint32_t lifted_f4e3681(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3694. */
uint32_t lifted_f4e3694(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e36c4. */
uint32_t lifted_f4e36c4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e36d2. */
uint32_t lifted_f4e36d2(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e36e4. */
uint32_t lifted_f4e36e4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e370f. */
uint32_t lifted_f4e370f(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e371e. */
uint32_t lifted_f4e371e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e373e. */
uint32_t lifted_f4e373e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3743. */
uint32_t lifted_f4e3743(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e37fe. */
uint32_t lifted_f4e37fe(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3814. */
uint32_t lifted_f4e3814(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3846. */
uint32_t lifted_f4e3846(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e38ff. */
uint32_t lifted_f4e38ff(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e39a0. */
uint32_t lifted_f4e39a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e39d0. */
uint32_t lifted_f4e39d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e39f0. */
uint32_t lifted_f4e39f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3a50. */
uint32_t lifted_f4e3a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3a90. */
uint32_t lifted_f4e3a90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3bf0. */
uint32_t lifted_f4e3bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3ce0. */
uint32_t lifted_f4e3ce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3f28. */
uint32_t lifted_f4e3f28(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e4024. */
uint32_t lifted_f4e4024(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e4080. */
uint32_t lifted_f4e4080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e4110. */
uint32_t lifted_f4e4110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e43c4. */
uint32_t lifted_f4e43c4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e44c8. */
uint32_t lifted_f4e44c8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e47a8. */
uint32_t lifted_f4e47a8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e4fd0. */
uint32_t lifted_f4e4fd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e4ff8. */
uint32_t lifted_f4e4ff8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5024. */
uint32_t lifted_f4e5024(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e506c. */
uint32_t lifted_f4e506c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5177. */
uint32_t lifted_f4e5177(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5271. */
uint32_t lifted_f4e5271(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e532c. */
uint32_t lifted_f4e532c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e53b4. */
uint32_t lifted_f4e53b4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e543c. */
uint32_t lifted_f4e543c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5678. */
uint32_t lifted_f4e5678(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e56a8. */
uint32_t lifted_f4e56a8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5700. */
uint32_t lifted_f4e5700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e571c. */
uint32_t lifted_f4e571c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5738. */
uint32_t lifted_f4e5738(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5750. */
uint32_t lifted_f4e5750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5774. */
uint32_t lifted_f4e5774(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5788. */
uint32_t lifted_f4e5788(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e579c. */
uint32_t lifted_f4e579c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5808. */
uint32_t lifted_f4e5808(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5810. */
uint32_t lifted_f4e5810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5838. */
uint32_t lifted_f4e5838(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e587c. */
uint32_t lifted_f4e587c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e58b8. */
uint32_t lifted_f4e58b8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5918. */
uint32_t lifted_f4e5918(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e596c. */
uint32_t lifted_f4e596c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e59f4. */
uint32_t lifted_f4e59f4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5bec. */
uint32_t lifted_f4e5bec(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5cd1. */
uint32_t lifted_f4e5cd1(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5fe4. */
uint32_t lifted_f4e5fe4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e628c. */
uint32_t lifted_f4e628c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6320. */
uint32_t lifted_f4e6320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e636c. */
uint32_t lifted_f4e636c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e64a0. */
uint32_t lifted_f4e64a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6510. */
uint32_t lifted_f4e6510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6600. */
uint32_t lifted_f4e6600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e66a0. */
uint32_t lifted_f4e66a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e66dc. */
uint32_t lifted_f4e66dc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6734. */
uint32_t lifted_f4e6734(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6b2c. */
uint32_t lifted_f4e6b2c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6bff. */
uint32_t lifted_f4e6bff(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6c1d. */
uint32_t lifted_f4e6c1d(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6c98. */
uint32_t lifted_f4e6c98(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6cd4. */
uint32_t lifted_f4e6cd4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6cf2. */
uint32_t lifted_f4e6cf2(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6f30. */
uint32_t lifted_f4e6f30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e70d0. */
uint32_t lifted_f4e70d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7120. */
uint32_t lifted_f4e7120(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7140. */
uint32_t lifted_f4e7140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7280. */
uint32_t lifted_f4e7280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7540. */
uint32_t lifted_f4e7540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7660. */
uint32_t lifted_f4e7660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7850. */
uint32_t lifted_f4e7850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7a00. */
uint32_t lifted_f4e7a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7b18. */
uint32_t lifted_f4e7b18(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7b50. */
uint32_t lifted_f4e7b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7b90. */
uint32_t lifted_f4e7b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7bf0. */
uint32_t lifted_f4e7bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7c30. */
uint32_t lifted_f4e7c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7e44. */
uint32_t lifted_f4e7e44(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7eb0. */
uint32_t lifted_f4e7eb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7ef4. */
uint32_t lifted_f4e7ef4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7f0c. */
uint32_t lifted_f4e7f0c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8230. */
uint32_t lifted_f4e8230(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e82d0. */
uint32_t lifted_f4e82d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e82f0. */
uint32_t lifted_f4e82f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8310. */
uint32_t lifted_f4e8310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8330. */
uint32_t lifted_f4e8330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8400. */
uint32_t lifted_f4e8400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8574. */
uint32_t lifted_f4e8574(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e85c0. */
uint32_t lifted_f4e85c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8620. */
uint32_t lifted_f4e8620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8650. */
uint32_t lifted_f4e8650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8660. */
uint32_t lifted_f4e8660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e869c. */
uint32_t lifted_f4e869c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e86fc. */
uint32_t lifted_f4e86fc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8730. */
uint32_t lifted_f4e8730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8790. */
uint32_t lifted_f4e8790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e88bf. */
uint32_t lifted_f4e88bf(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8950. */
uint32_t lifted_f4e8950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8978. */
uint32_t lifted_f4e8978(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e89e8. */
uint32_t lifted_f4e89e8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e89f4. */
uint32_t lifted_f4e89f4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8a58. */
uint32_t lifted_f4e8a58(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8a7c. */
uint32_t lifted_f4e8a7c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8aa0. */
uint32_t lifted_f4e8aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
