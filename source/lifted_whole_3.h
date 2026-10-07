#ifndef VERTRIX_LIFTED_WHOLE_3_H
#define VERTRIX_LIFTED_WHOLE_3_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4AE150_STACK = 76,
    LIFTED_F4AE1F0_STACK = 68,
    LIFTED_F4AE250_STACK = 80,
    LIFTED_F4AF2A0_STACK = 80,
    LIFTED_F4AF370_STACK = 72,
    LIFTED_F4AF530_STACK = 68,
    LIFTED_F4B0B70_STACK = 136,
    LIFTED_F4B17B0_STACK = 76,
    LIFTED_F4B1FA0_STACK = 232,
    LIFTED_F4B2300_STACK = 72,
    LIFTED_F4B3100_STACK = 68,
    LIFTED_F4B3340_STACK = 80,
    LIFTED_F4B34D0_STACK = 68,
    LIFTED_F4B3500_STACK = 156,
    LIFTED_F4B3A00_STACK = 212,
    LIFTED_F4B3CE0_STACK = 112,
    LIFTED_F4B3D60_STACK = 112,
    LIFTED_F4B3FB0_STACK = 68,
    LIFTED_F4B4270_STACK = 80,
    LIFTED_F4B4510_STACK = 68,
    LIFTED_F4B45F0_STACK = 72,
    LIFTED_F4B4600_STACK = 68,
    LIFTED_F4B4610_STACK = 68,
    LIFTED_F4B4620_STACK = 68,
    LIFTED_F4B46E0_STACK = 72,
    LIFTED_F4B4780_STACK = 72,
    LIFTED_F4B4CB0_STACK = 68,
    LIFTED_F4B4CF0_STACK = 252,
    LIFTED_F4B5050_STACK = 112,
    LIFTED_F4B50D0_STACK = 112,
    LIFTED_F4B5150_STACK = 128,
    LIFTED_F4B5400_STACK = 68,
    LIFTED_F4B5420_STACK = 156,
    LIFTED_F4B54D0_STACK = 68,
    LIFTED_F4B5500_STACK = 84,
    LIFTED_F4B5550_STACK = 68,
    LIFTED_F4B5580_STACK = 136,
    LIFTED_F4B5C60_STACK = 68,
    LIFTED_F4B5D40_STACK = 84,
    LIFTED_F4B5DB0_STACK = 68,
    LIFTED_F4B5DC0_STACK = 168,
    LIFTED_F4B5E70_STACK = 80,
    LIFTED_F4B6460_STACK = 160,
    LIFTED_F4B6560_STACK = 68,
    LIFTED_F4B6690_STACK = 64,
    LIFTED_F4B66C0_STACK = 72,
    LIFTED_F4B6700_STACK = 84,
    LIFTED_F4B6800_STACK = 140,
    LIFTED_F4B6890_STACK = 68,
    LIFTED_F4B69F0_STACK = 76,
    LIFTED_F4B6A10_STACK = 68,
    LIFTED_F4B6EA0_STACK = 68,
    LIFTED_F4B6F70_STACK = 80,
    LIFTED_F4B7600_STACK = 68,
    LIFTED_F4B76D0_STACK = 92,
    LIFTED_F4B78D0_STACK = 68,
    LIFTED_F4B78E0_STACK = 172,
    LIFTED_F4B79A0_STACK = 80,
    LIFTED_F4B7A80_STACK = 72,
    LIFTED_F4B8170_STACK = 80,
    LIFTED_F4B9050_STACK = 120,
    LIFTED_F4B9310_STACK = 68,
    LIFTED_F4B9330_STACK = 92,
    LIFTED_F4B98B0_STACK = 116,
    LIFTED_F4B9CB0_STACK = 84,
    LIFTED_F4B9CF0_STACK = 96,
    LIFTED_F4B9D70_STACK = 76,
    LIFTED_F4B9DD0_STACK = 68,
    LIFTED_F4B9DE0_STACK = 116,
    LIFTED_F4B9F70_STACK = 184,
    LIFTED_F4C07D0_STACK = 88,
    LIFTED_F4C0990_STACK = 68,
    LIFTED_F4C0B51_STACK = 96,
    LIFTED_F4C1D20_STACK = 68,
    LIFTED_F4C3220_STACK = 100,
    LIFTED_F4C33A0_STACK = 128,
    LIFTED_F4C35F0_STACK = 72,
    LIFTED_F4C3E40_STACK = 84,
    LIFTED_F4C3F80_STACK = 68,
    LIFTED_F4C5A00_STACK = 92,
    LIFTED_F4C5BB0_STACK = 68,
    LIFTED_F4C5BC0_STACK = 68,
    LIFTED_F4C5BD0_STACK = 68,
    LIFTED_F4C5BE0_STACK = 68,
    LIFTED_F4C9820_STACK = 68,
    LIFTED_F4C9840_STACK = 72,
    LIFTED_F4C98F0_STACK = 72,
    LIFTED_F4C9DAF_STACK = 76,
    LIFTED_F4C9DD6_STACK = 76,
    LIFTED_F4C9E00_STACK = 76,
    LIFTED_F4C9FE0_STACK = 76,
    LIFTED_F4CA070_STACK = 80,
    LIFTED_F4CA1A0_STACK = 88,
    LIFTED_F4CA1E0_STACK = 76,
    LIFTED_F4CA3A0_STACK = 92,
    LIFTED_F4CA3F0_STACK = 88,
    LIFTED_F4CAFD0_STACK = 92,
    LIFTED_F4CB460_STACK = 104,
    LIFTED_F4CB950_STACK = 80,
    LIFTED_F4CB970_STACK = 80,
    LIFTED_F4CBA60_STACK = 76,
    LIFTED_F4CBA70_STACK = 68,
    LIFTED_F4CBE80_STACK = 68,
    LIFTED_F4CBF10_STACK = 112,
    LIFTED_F4CC760_STACK = 72,
    LIFTED_F4CC780_STACK = 72,
    LIFTED_F4CC990_STACK = 80,
    LIFTED_F4CCAD0_STACK = 72,
    LIFTED_F4CCAF0_STACK = 80,
    LIFTED_F4CCB9F_STACK = 80,
    LIFTED_F4CCC60_STACK = 92,
    LIFTED_F4CCCC0_STACK = 88,
    LIFTED_F4CCCF0_STACK = 88,
    LIFTED_F4CCD20_STACK = 92,
    LIFTED_F4CCD50_STACK = 84,
    LIFTED_F4CCDD0_STACK = 84,
    LIFTED_F4CCE00_STACK = 84,
    LIFTED_F4CCE30_STACK = 84,
    LIFTED_F4CCE60_STACK = 92,
    LIFTED_F4CD090_STACK = 72,
    LIFTED_F4CD520_STACK = 92,
    LIFTED_F4CD836_STACK = 76,
    LIFTED_F4CD847_STACK = 84,
    LIFTED_F4CDA40_STACK = 92,
    LIFTED_F4CDA90_STACK = 88,
    LIFTED_F4CDAF0_STACK = 116,
    LIFTED_F4CDB70_STACK = 112,
    LIFTED_F4CDFE0_STACK = 88,
    LIFTED_F4CE080_STACK = 76,
    LIFTED_F4CE810_STACK = 76,
    LIFTED_F4CE9FD_STACK = 72,
    LIFTED_F4CF320_STACK = 120,
    LIFTED_F4CF3A0_STACK = 120,
    LIFTED_F4CF480_STACK = 88,
    LIFTED_F4CF5D0_STACK = 112,
    LIFTED_F4CF850_STACK = 92,
    LIFTED_F4CF880_STACK = 92,
    LIFTED_F4CF8E0_STACK = 80,
    LIFTED_F4CF940_STACK = 84,
    LIFTED_F4CF980_STACK = 84,
    LIFTED_F4CF9D0_STACK = 96,
    LIFTED_F4CFC90_STACK = 120,
    LIFTED_F4D16B0_STACK = 68,
    LIFTED_F4D1900_STACK = 92,
    LIFTED_F4D1930_STACK = 88,
    LIFTED_F4D2020_STACK = 132,
    LIFTED_F4D2170_STACK = 88,
    LIFTED_F4D21A0_STACK = 80,
    LIFTED_F4D21D0_STACK = 144,
    LIFTED_F4D2260_STACK = 104,
    LIFTED_F4D22B0_STACK = 128,
    LIFTED_F4D2390_STACK = 124,
    LIFTED_F4D2420_STACK = 76,
    LIFTED_F4D2440_STACK = 76,
    LIFTED_F4D3010_STACK = 76,
    LIFTED_F4D3020_STACK = 72,
    LIFTED_F4D30F0_STACK = 104,
    LIFTED_F4D3120_STACK = 68,
    LIFTED_F4D3F70_STACK = 152,
    LIFTED_F4D4040_STACK = 84,
    LIFTED_F4D4060_STACK = 84,
    LIFTED_F4D41A0_STACK = 76,
    LIFTED_F4D41C0_STACK = 80,
    LIFTED_F4D42A0_STACK = 84,
    LIFTED_F4D4390_STACK = 76,
    LIFTED_F4D4E60_STACK = 104,
    LIFTED_F4D4FD0_STACK = 88,
    LIFTED_F4D5010_STACK = 120,
    LIFTED_F4D5150_STACK = 84,
    LIFTED_F4D5180_STACK = 100,
    LIFTED_F4D51C0_STACK = 412,
    LIFTED_F4D54C0_STACK = 260,
    LIFTED_F4D58E0_STACK = 80,
    LIFTED_F4D5A70_STACK = 88,
    LIFTED_F4D62E0_STACK = 76,
    LIFTED_F4D63B0_STACK = 76,
    LIFTED_F4D63D0_STACK = 76,
    LIFTED_F4D66CD_STACK = 80,
    LIFTED_F4D6710_STACK = 76,
    LIFTED_F4D6768_STACK = 68,
    LIFTED_F4D6775_STACK = 68,
    LIFTED_F4D67A8_STACK = 72,
    LIFTED_F4D67B2_STACK = 72,
    LIFTED_F4D6A30_STACK = 80,
    LIFTED_F4D6F10_STACK = 108,
    LIFTED_F4D73C0_STACK = 80,
    LIFTED_F4D74A6_STACK = 68,
    LIFTED_F4D82C6_STACK = 68,
    LIFTED_F4D8340_STACK = 104,
    LIFTED_F4D83C0_STACK = 72,
    LIFTED_F4D83F0_STACK = 136,
    LIFTED_F4D8490_STACK = 92,
    LIFTED_F4D8540_STACK = 80,
    LIFTED_F4D8580_STACK = 72,
    LIFTED_F4D85FC_STACK = 72,
    LIFTED_F4D8620_STACK = 72,
    LIFTED_F4D8650_STACK = 104,
    LIFTED_F4D86D0_STACK = 136,
    LIFTED_F4D8770_STACK = 112,
    LIFTED_F4D8950_STACK = 80,
    LIFTED_F4D8AB0_STACK = 104,
    LIFTED_F4D8B80_STACK = 136,
    LIFTED_F4D8C20_STACK = 104,
    LIFTED_F4D9280_STACK = 104,
    LIFTED_F4D92F0_STACK = 104,
    LIFTED_F4D9350_STACK = 76,
    LIFTED_F4D9930_STACK = 88,
    LIFTED_F4D9AE0_STACK = 64,
    LIFTED_F4DA66E_STACK = 100,
    LIFTED_F4DA71B_STACK = 100,
    LIFTED_F4DACA0_STACK = 72,
    LIFTED_F4DAD2E_STACK = 72,
    LIFTED_F4DB6D9_STACK = 96,
    LIFTED_F4DB980_STACK = 100,
    LIFTED_F4DC000_STACK = 72,
    LIFTED_F4DC160_STACK = 72,
    LIFTED_F4DC190_STACK = 72,
    LIFTED_F4DC1C0_STACK = 72,
    LIFTED_F4DD160_STACK = 68,
    LIFTED_F4DD170_STACK = 68,
    LIFTED_F4DD180_STACK = 68,
    LIFTED_F4DD360_STACK = 104,
    LIFTED_F4DD3E0_STACK = 92,
    LIFTED_F4DD440_STACK = 72,
    LIFTED_F4DD460_STACK = 88,
    LIFTED_F4DDBE0_STACK = 92,
    LIFTED_F4DDC40_STACK = 72,
    LIFTED_F4DDC60_STACK = 84,
    LIFTED_F4DEC60_STACK = 68,
    LIFTED_F4DEEC0_STACK = 104,
    LIFTED_F4DEF50_STACK = 84,
    LIFTED_F4DEF90_STACK = 76,
    LIFTED_F4DEFD0_STACK = 136,
    LIFTED_F4DF070_STACK = 92,
    LIFTED_F4DFA7C_STACK = 88,
    LIFTED_F4E0150_STACK = 116,
    LIFTED_F4E01D0_STACK = 80,
    LIFTED_F4E0250_STACK = 76,
    LIFTED_F4E081C_STACK = 84,
    LIFTED_F4E0B9E_STACK = 84,
    LIFTED_F4E0BED_STACK = 72,
    LIFTED_F4E0BF8_STACK = 76,
    LIFTED_F4E0FC0_STACK = 120,
    LIFTED_F4E104E_STACK = 84,
    LIFTED_F4E1054_STACK = 68,
    LIFTED_F4E11B0_STACK = 92,
    LIFTED_F4E1210_STACK = 72,
    LIFTED_F4E1260_STACK = 84,
    LIFTED_F4E14F0_STACK = 80,
    LIFTED_F4E15B0_STACK = 68,
    LIFTED_F4E15C0_STACK = 68,
    LIFTED_F4E2371_STACK = 68,
    LIFTED_F4E237D_STACK = 68,
    LIFTED_F4E2389_STACK = 76,
    LIFTED_F4E2420_STACK = 72,
    LIFTED_F4E2CC0_STACK = 84,
    LIFTED_F4E2D40_STACK = 84,
    LIFTED_F4E2F10_STACK = 148,
    LIFTED_F4E3681_STACK = 76,
    LIFTED_F4E36C4_STACK = 68,
    LIFTED_F4E36D2_STACK = 68,
    LIFTED_F4E36E4_STACK = 76,
    LIFTED_F4E370F_STACK = 72,
    LIFTED_F4E371E_STACK = 76,
    LIFTED_F4E373E_STACK = 76,
    LIFTED_F4E3743_STACK = 76,
    LIFTED_F4E37FE_STACK = 68,
    LIFTED_F4E39A0_STACK = 80,
    LIFTED_F4E39D0_STACK = 80,
    LIFTED_F4E39F0_STACK = 88,
    LIFTED_F4E3A50_STACK = 68,
    LIFTED_F4E3A90_STACK = 68,
    LIFTED_F4E3BF0_STACK = 176,
    LIFTED_F4E4024_STACK = 84,
    LIFTED_F4E44C8_STACK = 92,
    LIFTED_F4E4FD0_STACK = 68,
    LIFTED_F4E4FF8_STACK = 76,
    LIFTED_F4E5271_STACK = 88,
    LIFTED_F4E532C_STACK = 76,
    LIFTED_F4E571C_STACK = 88,
    LIFTED_F4E5738_STACK = 88,
    LIFTED_F4E5750_STACK = 76,
    LIFTED_F4E5774_STACK = 88,
    LIFTED_F4E5788_STACK = 88,
    LIFTED_F4E579C_STACK = 88,
    LIFTED_F4E5808_STACK = 88,
    LIFTED_F4E5810_STACK = 88,
    LIFTED_F4E587C_STACK = 80,
    LIFTED_F4E58B8_STACK = 84,
    LIFTED_F4E5CD1_STACK = 104,
    LIFTED_F4E636C_STACK = 72,
    LIFTED_F4E6600_STACK = 88,
    LIFTED_F4E6CD4_STACK = 68,
    LIFTED_F4E70D0_STACK = 72,
    LIFTED_F4E7140_STACK = 72,
    LIFTED_F4E7540_STACK = 104,
    LIFTED_F4E7660_STACK = 112,
    LIFTED_F4E7850_STACK = 108,
    LIFTED_F4E7B50_STACK = 68,
    LIFTED_F4E7BF0_STACK = 80,
    LIFTED_F4E7C30_STACK = 104,
    LIFTED_F4E7E44_STACK = 76,
    LIFTED_F4E7EF4_STACK = 76,
    LIFTED_F4E82D0_STACK = 72,
    LIFTED_F4E8310_STACK = 68,
    LIFTED_F4E8650_STACK = 84,
    LIFTED_F4E86FC_STACK = 76,
    LIFTED_F4E89E8_STACK = 68,
    LIFTED_F4E89F4_STACK = 68,
    LIFTED_F4E8AA0_STACK = 76,
    LIFTED_F4E8ABC_STACK = 80,
    LIFTED_F4E8B24_STACK = 76,
    LIFTED_F4E8D80_STACK = 84,
    LIFTED_F4E8FF0_STACK = 80,
    LIFTED_F4E9020_STACK = 72,
    LIFTED_F4E9060_STACK = 76,
    LIFTED_F4E91E0_STACK = 140,
    LIFTED_F4E9C94_STACK = 76,
    LIFTED_F4E9CA8_STACK = 72,
    LIFTED_F4EA2A8_STACK = 72,
    LIFTED_F4EA6A0_STACK = 72,
    LIFTED_F4EA6B0_STACK = 72,
    LIFTED_F4EAA7C_STACK = 100,
    LIFTED_F4EB140_STACK = 100,
    LIFTED_F4EB250_STACK = 72,
    LIFTED_F4EB270_STACK = 76,
    LIFTED_F4EB3A0_STACK = 100,
    LIFTED_F4EB526_STACK = 68,
    LIFTED_F4EB57C_STACK = 68,
    LIFTED_F4EB5C0_STACK = 76,
    LIFTED_F4EB606_STACK = 68,
    LIFTED_F4EBB78_STACK = 72,
    LIFTED_F4EBCD0_STACK = 68,
    LIFTED_F4EC160_STACK = 76,
    LIFTED_F4EC1D0_STACK = 72,
    LIFTED_F4EC2D0_STACK = 72,
    LIFTED_F4EC380_STACK = 112,
    LIFTED_F4EC3E0_STACK = 132,
    LIFTED_F4EC548_STACK = 80,
    LIFTED_F4EC578_STACK = 96,
    LIFTED_F4EC8F0_STACK = 84,
    LIFTED_F4EC910_STACK = 72,
    LIFTED_F4EC940_STACK = 88,
    LIFTED_F4ECAA0_STACK = 80,
    LIFTED_F4ECAD0_STACK = 124,
    LIFTED_F4ECB50_STACK = 72,
    LIFTED_F4ECC60_STACK = 84,
    LIFTED_F4EDF7F_STACK = 68,
    LIFTED_F4EE670_STACK = 88,
    LIFTED_F4EE840_STACK = 104,
    LIFTED_F4EE8D0_STACK = 84,
    LIFTED_F4EE980_STACK = 136,
    LIFTED_F4EEA20_STACK = 104
};

/* Original 0x4ae150. */
uint32_t lifted_f4ae150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ae1f0. */
uint32_t lifted_f4ae1f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ae250. */
uint32_t lifted_f4ae250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4af2a0. */
uint32_t lifted_f4af2a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4af370. */
uint32_t lifted_f4af370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4af530. */
uint32_t lifted_f4af530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b0b70. */
uint32_t lifted_f4b0b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b17b0. */
uint32_t lifted_f4b17b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b1fa0. */
uint32_t lifted_f4b1fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b2300. */
uint32_t lifted_f4b2300(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3100. */
uint32_t lifted_f4b3100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3340. */
uint32_t lifted_f4b3340(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4b4270. */
uint32_t lifted_f4b4270(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4510. */
uint32_t lifted_f4b4510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b45f0. */
uint32_t lifted_f4b45f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4600. */
uint32_t lifted_f4b4600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4610. */
uint32_t lifted_f4b4610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4620. */
uint32_t lifted_f4b4620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b46e0. */
uint32_t lifted_f4b46e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4780. */
uint32_t lifted_f4b4780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4cb0. */
uint32_t lifted_f4b4cb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4cf0. */
uint32_t lifted_f4b4cf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4b5400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5420. */
uint32_t lifted_f4b5420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b54d0. */
uint32_t lifted_f4b54d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5500. */
uint32_t lifted_f4b5500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5550. */
uint32_t lifted_f4b5550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5580. */
uint32_t lifted_f4b5580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5c60. */
uint32_t lifted_f4b5c60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5d40. */
uint32_t lifted_f4b5d40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5db0. */
uint32_t lifted_f4b5db0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5dc0. */
uint32_t lifted_f4b5dc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5e70. */
uint32_t lifted_f4b5e70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6460. */
uint32_t lifted_f4b6460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6560. */
uint32_t lifted_f4b6560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6690. */
uint32_t lifted_f4b6690(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b66c0. */
uint32_t lifted_f4b66c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6700. */
uint32_t lifted_f4b6700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6800. */
uint32_t lifted_f4b6800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6890. */
uint32_t lifted_f4b6890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b69f0. */
uint32_t lifted_f4b69f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6a10. */
uint32_t lifted_f4b6a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6ea0. */
uint32_t lifted_f4b6ea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6f70. */
uint32_t lifted_f4b6f70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7600. */
uint32_t lifted_f4b7600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b76d0. */
uint32_t lifted_f4b76d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b78d0. */
uint32_t lifted_f4b78d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b78e0. */
uint32_t lifted_f4b78e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b79a0. */
uint32_t lifted_f4b79a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7a80. */
uint32_t lifted_f4b7a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b8170. */
uint32_t lifted_f4b8170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9050. */
uint32_t lifted_f4b9050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9310. */
uint32_t lifted_f4b9310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9330. */
uint32_t lifted_f4b9330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b98b0. */
uint32_t lifted_f4b98b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9cb0. */
uint32_t lifted_f4b9cb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4b9f70. */
uint32_t lifted_f4b9f70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c07d0. */
uint32_t lifted_f4c07d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c0990. */
uint32_t lifted_f4c0990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c0b51. */
uint32_t lifted_f4c0b51(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c1d20. */
uint32_t lifted_f4c1d20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3220. */
uint32_t lifted_f4c3220(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c33a0. */
uint32_t lifted_f4c33a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c35f0. */
uint32_t lifted_f4c35f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3e40. */
uint32_t lifted_f4c3e40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3f80. */
uint32_t lifted_f4c3f80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5a00. */
uint32_t lifted_f4c5a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5bb0. */
uint32_t lifted_f4c5bb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5bc0. */
uint32_t lifted_f4c5bc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5bd0. */
uint32_t lifted_f4c5bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5be0. */
uint32_t lifted_f4c5be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9820. */
uint32_t lifted_f4c9820(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9840. */
uint32_t lifted_f4c9840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c98f0. */
uint32_t lifted_f4c98f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9daf. */
uint32_t lifted_f4c9daf(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ca070. */
uint32_t lifted_f4ca070(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca1a0. */
uint32_t lifted_f4ca1a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca1e0. */
uint32_t lifted_f4ca1e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca3a0. */
uint32_t lifted_f4ca3a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca3f0. */
uint32_t lifted_f4ca3f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cafd0. */
uint32_t lifted_f4cafd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb460. */
uint32_t lifted_f4cb460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb950. */
uint32_t lifted_f4cb950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb970. */
uint32_t lifted_f4cb970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cba60. */
uint32_t lifted_f4cba60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cba70. */
uint32_t lifted_f4cba70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cbe80. */
uint32_t lifted_f4cbe80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cbf10. */
uint32_t lifted_f4cbf10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc760. */
uint32_t lifted_f4cc760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc780. */
uint32_t lifted_f4cc780(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ccb9f. */
uint32_t lifted_f4ccb9f(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4cd090. */
uint32_t lifted_f4cd090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd520. */
uint32_t lifted_f4cd520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd836. */
uint32_t lifted_f4cd836(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd847. */
uint32_t lifted_f4cd847(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cda40. */
uint32_t lifted_f4cda40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cda90. */
uint32_t lifted_f4cda90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cdaf0. */
uint32_t lifted_f4cdaf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cdb70. */
uint32_t lifted_f4cdb70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cdfe0. */
uint32_t lifted_f4cdfe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce080. */
uint32_t lifted_f4ce080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce810. */
uint32_t lifted_f4ce810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce9fd. */
uint32_t lifted_f4ce9fd(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf320. */
uint32_t lifted_f4cf320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf3a0. */
uint32_t lifted_f4cf3a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf480. */
uint32_t lifted_f4cf480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf5d0. */
uint32_t lifted_f4cf5d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf850. */
uint32_t lifted_f4cf850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf880. */
uint32_t lifted_f4cf880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf8e0. */
uint32_t lifted_f4cf8e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf940. */
uint32_t lifted_f4cf940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf980. */
uint32_t lifted_f4cf980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf9d0. */
uint32_t lifted_f4cf9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cfc90. */
uint32_t lifted_f4cfc90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d16b0. */
uint32_t lifted_f4d16b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1900. */
uint32_t lifted_f4d1900(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1930. */
uint32_t lifted_f4d1930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2020. */
uint32_t lifted_f4d2020(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d2390. */
uint32_t lifted_f4d2390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2420. */
uint32_t lifted_f4d2420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2440. */
uint32_t lifted_f4d2440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d3010. */
uint32_t lifted_f4d3010(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d3020. */
uint32_t lifted_f4d3020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d30f0. */
uint32_t lifted_f4d30f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d3120. */
uint32_t lifted_f4d3120(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d3f70. */
uint32_t lifted_f4d3f70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4040. */
uint32_t lifted_f4d4040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4060. */
uint32_t lifted_f4d4060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d41a0. */
uint32_t lifted_f4d41a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d41c0. */
uint32_t lifted_f4d41c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d42a0. */
uint32_t lifted_f4d42a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4390. */
uint32_t lifted_f4d4390(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d54c0. */
uint32_t lifted_f4d54c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d58e0. */
uint32_t lifted_f4d58e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5a70. */
uint32_t lifted_f4d5a70(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d66cd. */
uint32_t lifted_f4d66cd(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6710. */
uint32_t lifted_f4d6710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6768. */
uint32_t lifted_f4d6768(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6775. */
uint32_t lifted_f4d6775(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d67a8. */
uint32_t lifted_f4d67a8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d67b2. */
uint32_t lifted_f4d67b2(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6a30. */
uint32_t lifted_f4d6a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6f10. */
uint32_t lifted_f4d6f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d73c0. */
uint32_t lifted_f4d73c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d74a6. */
uint32_t lifted_f4d74a6(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d82c6. */
uint32_t lifted_f4d82c6(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8340. */
uint32_t lifted_f4d8340(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d83c0. */
uint32_t lifted_f4d83c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d83f0. */
uint32_t lifted_f4d83f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8490. */
uint32_t lifted_f4d8490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8540. */
uint32_t lifted_f4d8540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8580. */
uint32_t lifted_f4d8580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d85fc. */
uint32_t lifted_f4d85fc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8620. */
uint32_t lifted_f4d8620(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d8ab0. */
uint32_t lifted_f4d8ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8b80. */
uint32_t lifted_f4d8b80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8c20. */
uint32_t lifted_f4d8c20(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d9930. */
uint32_t lifted_f4d9930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9ae0. */
uint32_t lifted_f4d9ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4da66e. */
uint32_t lifted_f4da66e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4da71b. */
uint32_t lifted_f4da71b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4daca0. */
uint32_t lifted_f4daca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dad2e. */
uint32_t lifted_f4dad2e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db6d9. */
uint32_t lifted_f4db6d9(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db980. */
uint32_t lifted_f4db980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc000. */
uint32_t lifted_f4dc000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc160. */
uint32_t lifted_f4dc160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc190. */
uint32_t lifted_f4dc190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc1c0. */
uint32_t lifted_f4dc1c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd160. */
uint32_t lifted_f4dd160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd170. */
uint32_t lifted_f4dd170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd180. */
uint32_t lifted_f4dd180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd360. */
uint32_t lifted_f4dd360(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd3e0. */
uint32_t lifted_f4dd3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd440. */
uint32_t lifted_f4dd440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd460. */
uint32_t lifted_f4dd460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ddbe0. */
uint32_t lifted_f4ddbe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ddc40. */
uint32_t lifted_f4ddc40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ddc60. */
uint32_t lifted_f4ddc60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dec60. */
uint32_t lifted_f4dec60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4deec0. */
uint32_t lifted_f4deec0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4df070. */
uint32_t lifted_f4df070(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dfa7c. */
uint32_t lifted_f4dfa7c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0150. */
uint32_t lifted_f4e0150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e01d0. */
uint32_t lifted_f4e01d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0250. */
uint32_t lifted_f4e0250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e081c. */
uint32_t lifted_f4e081c(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e0fc0. */
uint32_t lifted_f4e0fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e104e. */
uint32_t lifted_f4e104e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1054. */
uint32_t lifted_f4e1054(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e14f0. */
uint32_t lifted_f4e14f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e15b0. */
uint32_t lifted_f4e15b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e15c0. */
uint32_t lifted_f4e15c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e2420. */
uint32_t lifted_f4e2420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2cc0. */
uint32_t lifted_f4e2cc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2d40. */
uint32_t lifted_f4e2d40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2f10. */
uint32_t lifted_f4e2f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3681. */
uint32_t lifted_f4e3681(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e4024. */
uint32_t lifted_f4e4024(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e44c8. */
uint32_t lifted_f4e44c8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e4fd0. */
uint32_t lifted_f4e4fd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e4ff8. */
uint32_t lifted_f4e4ff8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5271. */
uint32_t lifted_f4e5271(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e532c. */
uint32_t lifted_f4e532c(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e587c. */
uint32_t lifted_f4e587c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e58b8. */
uint32_t lifted_f4e58b8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5cd1. */
uint32_t lifted_f4e5cd1(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e636c. */
uint32_t lifted_f4e636c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6600. */
uint32_t lifted_f4e6600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6cd4. */
uint32_t lifted_f4e6cd4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e70d0. */
uint32_t lifted_f4e70d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7140. */
uint32_t lifted_f4e7140(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e7b50. */
uint32_t lifted_f4e7b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e7ef4. */
uint32_t lifted_f4e7ef4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e82d0. */
uint32_t lifted_f4e82d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8310. */
uint32_t lifted_f4e8310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8650. */
uint32_t lifted_f4e8650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e86fc. */
uint32_t lifted_f4e86fc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e89e8. */
uint32_t lifted_f4e89e8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e89f4. */
uint32_t lifted_f4e89f4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8aa0. */
uint32_t lifted_f4e8aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8abc. */
uint32_t lifted_f4e8abc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8b24. */
uint32_t lifted_f4e8b24(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8d80. */
uint32_t lifted_f4e8d80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8ff0. */
uint32_t lifted_f4e8ff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9020. */
uint32_t lifted_f4e9020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9060. */
uint32_t lifted_f4e9060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e91e0. */
uint32_t lifted_f4e91e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9c94. */
uint32_t lifted_f4e9c94(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9ca8. */
uint32_t lifted_f4e9ca8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea2a8. */
uint32_t lifted_f4ea2a8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea6a0. */
uint32_t lifted_f4ea6a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea6b0. */
uint32_t lifted_f4ea6b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eaa7c. */
uint32_t lifted_f4eaa7c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb140. */
uint32_t lifted_f4eb140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb250. */
uint32_t lifted_f4eb250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb270. */
uint32_t lifted_f4eb270(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb3a0. */
uint32_t lifted_f4eb3a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb526. */
uint32_t lifted_f4eb526(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb57c. */
uint32_t lifted_f4eb57c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb5c0. */
uint32_t lifted_f4eb5c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb606. */
uint32_t lifted_f4eb606(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ebb78. */
uint32_t lifted_f4ebb78(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ebcd0. */
uint32_t lifted_f4ebcd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec160. */
uint32_t lifted_f4ec160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec1d0. */
uint32_t lifted_f4ec1d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec2d0. */
uint32_t lifted_f4ec2d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec380. */
uint32_t lifted_f4ec380(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec3e0. */
uint32_t lifted_f4ec3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec548. */
uint32_t lifted_f4ec548(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec578. */
uint32_t lifted_f4ec578(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec8f0. */
uint32_t lifted_f4ec8f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec910. */
uint32_t lifted_f4ec910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec940. */
uint32_t lifted_f4ec940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ecaa0. */
uint32_t lifted_f4ecaa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ecad0. */
uint32_t lifted_f4ecad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ecb50. */
uint32_t lifted_f4ecb50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ecc60. */
uint32_t lifted_f4ecc60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4edf7f. */
uint32_t lifted_f4edf7f(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee670. */
uint32_t lifted_f4ee670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee840. */
uint32_t lifted_f4ee840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee8d0. */
uint32_t lifted_f4ee8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee980. */
uint32_t lifted_f4ee980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eea20. */
uint32_t lifted_f4eea20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
