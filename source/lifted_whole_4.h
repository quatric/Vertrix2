#ifndef VERTRIX_LIFTED_WHOLE_4_H
#define VERTRIX_LIFTED_WHOLE_4_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4B9C20_STACK = 100,
    LIFTED_F4B9CB0_STACK = 84,
    LIFTED_F4B9CF0_STACK = 96,
    LIFTED_F4B9D70_STACK = 76,
    LIFTED_F4B9DD0_STACK = 68,
    LIFTED_F4B9DE0_STACK = 116,
    LIFTED_F4BA220_STACK = 184,
    LIFTED_F4BB3D0_STACK = 100,
    LIFTED_F4BB470_STACK = 88,
    LIFTED_F4BBA40_STACK = 128,
    LIFTED_F4BC050_STACK = 100,
    LIFTED_F4BC6C0_STACK = 84,
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
    LIFTED_F4C0990_STACK = 68,
    LIFTED_F4C09E0_STACK = 88,
    LIFTED_F4C0B51_STACK = 96,
    LIFTED_F4C14B7_STACK = 160,
    LIFTED_F4C1D20_STACK = 68,
    LIFTED_F4C1E40_STACK = 124,
    LIFTED_F4C2000_STACK = 132,
    LIFTED_F4C3220_STACK = 100,
    LIFTED_F4C3320_STACK = 104,
    LIFTED_F4C33A0_STACK = 128,
    LIFTED_F4C3540_STACK = 112,
    LIFTED_F4C35F0_STACK = 72,
    LIFTED_F4C3780_STACK = 112,
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
    LIFTED_F4C5BC0_STACK = 68,
    LIFTED_F4C5BD0_STACK = 68,
    LIFTED_F4C5BE0_STACK = 68,
    LIFTED_F4C5C00_STACK = 68,
    LIFTED_F4C6460_STACK = 100,
    LIFTED_F4C69C0_STACK = 100,
    LIFTED_F4C6A20_STACK = 136,
    LIFTED_F4C6C70_STACK = 72,
    LIFTED_F4C70F0_STACK = 268,
    LIFTED_F4C8BE0_STACK = 120,
    LIFTED_F4C9550_STACK = 116,
    LIFTED_F4C9820_STACK = 68,
    LIFTED_F4C9840_STACK = 72,
    LIFTED_F4C98F0_STACK = 72,
    LIFTED_F4C9DAF_STACK = 76,
    LIFTED_F4C9DD6_STACK = 76,
    LIFTED_F4C9E00_STACK = 76,
    LIFTED_F4C9FE0_STACK = 76,
    LIFTED_F4C9FF0_STACK = 92,
    LIFTED_F4CA000_STACK = 92,
    LIFTED_F4CA070_STACK = 80,
    LIFTED_F4CA0D0_STACK = 84,
    LIFTED_F4CA110_STACK = 92,
    LIFTED_F4CA150_STACK = 76,
    LIFTED_F4CA1A0_STACK = 88,
    LIFTED_F4CA1E0_STACK = 76,
    LIFTED_F4CA210_STACK = 84,
    LIFTED_F4CA240_STACK = 84,
    LIFTED_F4CA280_STACK = 104,
    LIFTED_F4CA310_STACK = 92,
    LIFTED_F4CA370_STACK = 88,
    LIFTED_F4CA3A0_STACK = 92,
    LIFTED_F4CA3F0_STACK = 88,
    LIFTED_F4CA430_STACK = 112,
    LIFTED_F4CA4A0_STACK = 120,
    LIFTED_F4CA520_STACK = 124,
    LIFTED_F4CA600_STACK = 88,
    LIFTED_F4CA650_STACK = 76,
    LIFTED_F4CA670_STACK = 96,
    LIFTED_F4CA710_STACK = 84,
    LIFTED_F4CA730_STACK = 108,
    LIFTED_F4CA770_STACK = 100,
    LIFTED_F4CA970_STACK = 128,
    LIFTED_F4CAFD0_STACK = 92,
    LIFTED_F4CB080_STACK = 100,
    LIFTED_F4CB460_STACK = 104,
    LIFTED_F4CB4F0_STACK = 140,
    LIFTED_F4CB5A0_STACK = 196,
    LIFTED_F4CB950_STACK = 80,
    LIFTED_F4CB970_STACK = 80,
    LIFTED_F4CBA60_STACK = 76,
    LIFTED_F4CBA70_STACK = 68,
    LIFTED_F4CBE80_STACK = 68,
    LIFTED_F4CBE90_STACK = 128,
    LIFTED_F4CBF10_STACK = 112,
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
    LIFTED_F4CCB9F_STACK = 80,
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
    LIFTED_F4CD0A4_STACK = 76,
    LIFTED_F4CD520_STACK = 92,
    LIFTED_F4CD836_STACK = 76,
    LIFTED_F4CD847_STACK = 84,
    LIFTED_F4CDA40_STACK = 92,
    LIFTED_F4CDA90_STACK = 88,
    LIFTED_F4CDAF0_STACK = 116,
    LIFTED_F4CDB70_STACK = 112,
    LIFTED_F4CDFE0_STACK = 88,
    LIFTED_F4CE080_STACK = 76,
    LIFTED_F4CE220_STACK = 104,
    LIFTED_F4CE810_STACK = 76,
    LIFTED_F4CE9C0_STACK = 88,
    LIFTED_F4CE9FD_STACK = 72,
    LIFTED_F4CF320_STACK = 120,
    LIFTED_F4CF3A0_STACK = 120,
    LIFTED_F4CF420_STACK = 124,
    LIFTED_F4CF480_STACK = 88,
    LIFTED_F4CF4A0_STACK = 80,
    LIFTED_F4CF5D0_STACK = 112,
    LIFTED_F4CF800_STACK = 96,
    LIFTED_F4CF850_STACK = 92,
    LIFTED_F4CF880_STACK = 92,
    LIFTED_F4CF8E0_STACK = 80,
    LIFTED_F4CF940_STACK = 84,
    LIFTED_F4CF980_STACK = 84,
    LIFTED_F4CF9D0_STACK = 96,
    LIFTED_F4CFC90_STACK = 120,
    LIFTED_F4CFE40_STACK = 164,
    LIFTED_F4CFF20_STACK = 112,
    LIFTED_F4CFF80_STACK = 104,
    LIFTED_F4CFFD0_STACK = 96,
    LIFTED_F4D01A0_STACK = 152,
    LIFTED_F4D04F0_STACK = 104,
    LIFTED_F4D05E0_STACK = 100,
    LIFTED_F4D0650_STACK = 88,
    LIFTED_F4D0740_STACK = 128,
    LIFTED_F4D0B30_STACK = 68,
    LIFTED_F4D16B0_STACK = 68,
    LIFTED_F4D1710_STACK = 160,
    LIFTED_F4D1840_STACK = 108,
    LIFTED_F4D1890_STACK = 124,
    LIFTED_F4D1900_STACK = 92,
    LIFTED_F4D1930_STACK = 88,
    LIFTED_F4D1980_STACK = 152,
    LIFTED_F4D1D20_STACK = 220,
    LIFTED_F4D1E00_STACK = 96,
    LIFTED_F4D1E50_STACK = 92,
    LIFTED_F4D2020_STACK = 132,
    LIFTED_F4D2170_STACK = 88,
    LIFTED_F4D21A0_STACK = 80,
    LIFTED_F4D21D0_STACK = 144,
    LIFTED_F4D2260_STACK = 104,
    LIFTED_F4D22B0_STACK = 128,
    LIFTED_F4D2310_STACK = 140,
    LIFTED_F4D2390_STACK = 124,
    LIFTED_F4D2420_STACK = 76,
    LIFTED_F4D2440_STACK = 76,
    LIFTED_F4D28C0_STACK = 128,
    LIFTED_F4D2910_STACK = 136,
    LIFTED_F4D2A00_STACK = 252,
    LIFTED_F4D2BB0_STACK = 104,
    LIFTED_F4D3010_STACK = 76,
    LIFTED_F4D3020_STACK = 72,
    LIFTED_F4D30F0_STACK = 104,
    LIFTED_F4D3120_STACK = 68,
    LIFTED_F4D3F70_STACK = 152,
    LIFTED_F4D4040_STACK = 84,
    LIFTED_F4D4060_STACK = 84,
    LIFTED_F4D4080_STACK = 92,
    LIFTED_F4D41A0_STACK = 76,
    LIFTED_F4D41C0_STACK = 80,
    LIFTED_F4D4270_STACK = 84,
    LIFTED_F4D42A0_STACK = 84,
    LIFTED_F4D4390_STACK = 76,
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
    LIFTED_F4D5390_STACK = 136,
    LIFTED_F4D54C0_STACK = 260,
    LIFTED_F4D5660_STACK = 140,
    LIFTED_F4D57A0_STACK = 88,
    LIFTED_F4D58E0_STACK = 80,
    LIFTED_F4D5910_STACK = 88,
    LIFTED_F4D59F0_STACK = 88,
    LIFTED_F4D5A70_STACK = 88,
    LIFTED_F4D5C70_STACK = 92,
    LIFTED_F4D6080_STACK = 100,
    LIFTED_F4D62E0_STACK = 76,
    LIFTED_F4D6380_STACK = 84,
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
    LIFTED_F4D6F50_STACK = 112,
    LIFTED_F4D70E0_STACK = 92,
    LIFTED_F4D7140_STACK = 128,
    LIFTED_F4D73C0_STACK = 80,
    LIFTED_F4D74A6_STACK = 68,
    LIFTED_F4D7510_STACK = 112,
    LIFTED_F4D75A0_STACK = 112,
    LIFTED_F4D7630_STACK = 144,
    LIFTED_F4D7AA0_STACK = 104,
    LIFTED_F4D7C00_STACK = 88,
    LIFTED_F4D7D70_STACK = 120,
    LIFTED_F4D7E50_STACK = 1748,
    LIFTED_F4D82C6_STACK = 68,
    LIFTED_F4D8340_STACK = 104,
    LIFTED_F4D83C0_STACK = 72,
    LIFTED_F4D83F0_STACK = 136,
    LIFTED_F4D8490_STACK = 92,
    LIFTED_F4D84F0_STACK = 72,
    LIFTED_F4D8510_STACK = 80,
    LIFTED_F4D8540_STACK = 80,
    LIFTED_F4D8580_STACK = 72,
    LIFTED_F4D85F0_STACK = 68,
    LIFTED_F4D85FC_STACK = 72,
    LIFTED_F4D8620_STACK = 72,
    LIFTED_F4D8650_STACK = 104,
    LIFTED_F4D86D0_STACK = 136,
    LIFTED_F4D8770_STACK = 112,
    LIFTED_F4D8950_STACK = 80,
    LIFTED_F4D8AB0_STACK = 104,
    LIFTED_F4D8B30_STACK = 84,
    LIFTED_F4D8B80_STACK = 136,
    LIFTED_F4D8C20_STACK = 104,
    LIFTED_F4D9280_STACK = 104,
    LIFTED_F4D92F0_STACK = 104,
    LIFTED_F4D9350_STACK = 76,
    LIFTED_F4D93F0_STACK = 96,
    LIFTED_F4D9430_STACK = 88,
    LIFTED_F4D9930_STACK = 88,
    LIFTED_F4D9AE0_STACK = 64,
    LIFTED_F4DA66E_STACK = 100,
    LIFTED_F4DA71B_STACK = 100,
    LIFTED_F4DAAB0_STACK = 84,
    LIFTED_F4DACA0_STACK = 72,
    LIFTED_F4DAD2E_STACK = 72,
    LIFTED_F4DAE70_STACK = 72,
    LIFTED_F4DAEB8_STACK = 72,
    LIFTED_F4DB1FD_STACK = 76,
    LIFTED_F4DB6A4_STACK = 88,
    LIFTED_F4DB6D9_STACK = 96,
    LIFTED_F4DB950_STACK = 92,
    LIFTED_F4DB980_STACK = 100,
    LIFTED_F4DBA10_STACK = 72,
    LIFTED_F4DBA20_STACK = 76,
    LIFTED_F4DBA80_STACK = 84,
    LIFTED_F4DBAA0_STACK = 72,
    LIFTED_F4DBAC0_STACK = 88,
    LIFTED_F4DBC60_STACK = 104,
    LIFTED_F4DBCD0_STACK = 100,
    LIFTED_F4DC000_STACK = 72,
    LIFTED_F4DC160_STACK = 72,
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
    LIFTED_F4DD170_STACK = 68,
    LIFTED_F4DD180_STACK = 68,
    LIFTED_F4DD360_STACK = 104,
    LIFTED_F4DD3E0_STACK = 92,
    LIFTED_F4DD440_STACK = 72,
    LIFTED_F4DD460_STACK = 88,
    LIFTED_F4DD4A0_STACK = 152,
    LIFTED_F4DDBE0_STACK = 92,
    LIFTED_F4DDC40_STACK = 72,
    LIFTED_F4DDC60_STACK = 84,
    LIFTED_F4DDC90_STACK = 84,
    LIFTED_F4DE5C0_STACK = 80,
    LIFTED_F4DE600_STACK = 80,
    LIFTED_F4DE630_STACK = 140,
    LIFTED_F4DE810_STACK = 252,
    LIFTED_F4DE900_STACK = 148,
    LIFTED_F4DEA40_STACK = 72,
    LIFTED_F4DEA78_STACK = 68,
    LIFTED_F4DEC60_STACK = 68,
    LIFTED_F4DEC70_STACK = 104,
    LIFTED_F4DEEC0_STACK = 104,
    LIFTED_F4DEF50_STACK = 84,
    LIFTED_F4DEF90_STACK = 76,
    LIFTED_F4DEFD0_STACK = 136,
    LIFTED_F4DF070_STACK = 92,
    LIFTED_F4DF0D0_STACK = 72,
    LIFTED_F4DF0F0_STACK = 76,
    LIFTED_F4DF1C0_STACK = 76,
    LIFTED_F4DF6C8_STACK = 80,
    LIFTED_F4DF81C_STACK = 72,
    LIFTED_F4DFA74_STACK = 68,
    LIFTED_F4DFA7C_STACK = 88,
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
    LIFTED_F4E09F0_STACK = 68,
    LIFTED_F4E0A30_STACK = 104,
    LIFTED_F4E0B9E_STACK = 84,
    LIFTED_F4E0BED_STACK = 72,
    LIFTED_F4E0BF8_STACK = 76,
    LIFTED_F4E0EC7_STACK = 152,
    LIFTED_F4E0FC0_STACK = 120,
    LIFTED_F4E104E_STACK = 84,
    LIFTED_F4E1054_STACK = 68,
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
    LIFTED_F4E36C4_STACK = 68,
    LIFTED_F4E36D2_STACK = 68,
    LIFTED_F4E36E4_STACK = 76,
    LIFTED_F4E370F_STACK = 72,
    LIFTED_F4E371E_STACK = 76,
    LIFTED_F4E373E_STACK = 76,
    LIFTED_F4E3743_STACK = 76,
    LIFTED_F4E37FE_STACK = 68,
    LIFTED_F4E38FF_STACK = 84,
    LIFTED_F4E39A0_STACK = 80,
    LIFTED_F4E39D0_STACK = 80,
    LIFTED_F4E39F0_STACK = 88,
    LIFTED_F4E3A50_STACK = 68
};

/* Original 0x4b9c20. */
uint32_t lifted_f4b9c20(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ba220. */
uint32_t lifted_f4ba220(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bb3d0. */
uint32_t lifted_f4bb3d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bb470. */
uint32_t lifted_f4bb470(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4c0990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c09e0. */
uint32_t lifted_f4c09e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c0b51. */
uint32_t lifted_f4c0b51(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c14b7. */
uint32_t lifted_f4c14b7(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4c3780. */
uint32_t lifted_f4c3780(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4c5bc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5bd0. */
uint32_t lifted_f4c5bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5be0. */
uint32_t lifted_f4c5be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5c00. */
uint32_t lifted_f4c5c00(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4c6c70. */
uint32_t lifted_f4c6c70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c70f0. */
uint32_t lifted_f4c70f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c8be0. */
uint32_t lifted_f4c8be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9550. */
uint32_t lifted_f4c9550(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4c9ff0. */
uint32_t lifted_f4c9ff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca000. */
uint32_t lifted_f4ca000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca070. */
uint32_t lifted_f4ca070(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4ca1a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca1e0. */
uint32_t lifted_f4ca1e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca210. */
uint32_t lifted_f4ca210(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca240. */
uint32_t lifted_f4ca240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca280. */
uint32_t lifted_f4ca280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca310. */
uint32_t lifted_f4ca310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca370. */
uint32_t lifted_f4ca370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca3a0. */
uint32_t lifted_f4ca3a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca3f0. */
uint32_t lifted_f4ca3f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca430. */
uint32_t lifted_f4ca430(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4ca670(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4cb460. */
uint32_t lifted_f4cb460(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4cba60. */
uint32_t lifted_f4cba60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cba70. */
uint32_t lifted_f4cba70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cbe80. */
uint32_t lifted_f4cbe80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cbe90. */
uint32_t lifted_f4cbe90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cbf10. */
uint32_t lifted_f4cbf10(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4ccb9f(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4cd0a4(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ce220. */
uint32_t lifted_f4ce220(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce810. */
uint32_t lifted_f4ce810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce9c0. */
uint32_t lifted_f4ce9c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d0b30. */
uint32_t lifted_f4d0b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d16b0. */
uint32_t lifted_f4d16b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d2310. */
uint32_t lifted_f4d2310(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d4390. */
uint32_t lifted_f4d4390(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4d8580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d85f0. */
uint32_t lifted_f4d85f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d8b30. */
uint32_t lifted_f4d8b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d93f0. */
uint32_t lifted_f4d93f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9430. */
uint32_t lifted_f4d9430(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4daab0. */
uint32_t lifted_f4daab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4daca0. */
uint32_t lifted_f4daca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dad2e. */
uint32_t lifted_f4dad2e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dae70. */
uint32_t lifted_f4dae70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4daeb8. */
uint32_t lifted_f4daeb8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db1fd. */
uint32_t lifted_f4db1fd(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db6a4. */
uint32_t lifted_f4db6a4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db6d9. */
uint32_t lifted_f4db6d9(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db950. */
uint32_t lifted_f4db950(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4dc160. */
uint32_t lifted_f4dc160(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4dd4a0. */
uint32_t lifted_f4dd4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4dec60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dec70. */
uint32_t lifted_f4dec70(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4df0d0. */
uint32_t lifted_f4df0d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df0f0. */
uint32_t lifted_f4df0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df1c0. */
uint32_t lifted_f4df1c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df6c8. */
uint32_t lifted_f4df6c8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df81c. */
uint32_t lifted_f4df81c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dfa74. */
uint32_t lifted_f4dfa74(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dfa7c. */
uint32_t lifted_f4dfa7c(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e09f0. */
uint32_t lifted_f4e09f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0a30. */
uint32_t lifted_f4e0a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
#endif
