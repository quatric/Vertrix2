#ifndef VERTRIX_LIFTED_WHOLE_4_H
#define VERTRIX_LIFTED_WHOLE_4_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4AC740_STACK = 64,
    LIFTED_F4AC750_STACK = 64,
    LIFTED_F4AC760_STACK = 72,
    LIFTED_F4AC780_STACK = 72,
    LIFTED_F4AC7A0_STACK = 64,
    LIFTED_F4AC7B0_STACK = 68,
    LIFTED_F4AC7D0_STACK = 64,
    LIFTED_F4AC7E0_STACK = 84,
    LIFTED_F4AC810_STACK = 84,
    LIFTED_F4AC840_STACK = 68,
    LIFTED_F4AC860_STACK = 64,
    LIFTED_F4AC8A0_STACK = 76,
    LIFTED_F4AC8D0_STACK = 76,
    LIFTED_F4AC8F0_STACK = 64,
    LIFTED_F4AC900_STACK = 64,
    LIFTED_F4AC910_STACK = 64,
    LIFTED_F4AC920_STACK = 68,
    LIFTED_F4AC930_STACK = 64,
    LIFTED_F4AC940_STACK = 68,
    LIFTED_F4AC950_STACK = 64,
    LIFTED_F4AC960_STACK = 64,
    LIFTED_F4AC980_STACK = 64,
    LIFTED_F4ACA00_STACK = 92,
    LIFTED_F4ACA60_STACK = 80,
    LIFTED_F4ACAB0_STACK = 80,
    LIFTED_F4ACB00_STACK = 80,
    LIFTED_F4ACC10_STACK = 80,
    LIFTED_F4ACC70_STACK = 76,
    LIFTED_F4ACCC0_STACK = 80,
    LIFTED_F4ACD30_STACK = 80,
    LIFTED_F4ACE40_STACK = 84,
    LIFTED_F4AD060_STACK = 80,
    LIFTED_F4AD110_STACK = 80,
    LIFTED_F4AD1C0_STACK = 80,
    LIFTED_F4AD210_STACK = 80,
    LIFTED_F4AD260_STACK = 92,
    LIFTED_F4AD2C0_STACK = 100,
    LIFTED_F4AD3C0_STACK = 100,
    LIFTED_F4AD440_STACK = 108,
    LIFTED_F4AD510_STACK = 64,
    LIFTED_F4AD520_STACK = 64,
    LIFTED_F4AD530_STACK = 80,
    LIFTED_F4AD580_STACK = 80,
    LIFTED_F4AD5E0_STACK = 80,
    LIFTED_F4AD630_STACK = 80,
    LIFTED_F4AD6E0_STACK = 76,
    LIFTED_F4AD720_STACK = 84,
    LIFTED_F4AD750_STACK = 76,
    LIFTED_F4AD790_STACK = 76,
    LIFTED_F4AD870_STACK = 92,
    LIFTED_F4ADE20_STACK = 80,
    LIFTED_F4ADE60_STACK = 80,
    LIFTED_F4ADF20_STACK = 64,
    LIFTED_F4ADF70_STACK = 64,
    LIFTED_F4ADFA0_STACK = 64,
    LIFTED_F4ADFB0_STACK = 64,
    LIFTED_F4ADFE0_STACK = 68,
    LIFTED_F4AE010_STACK = 120,
    LIFTED_F4AE110_STACK = 64,
    LIFTED_F4AE140_STACK = 68,
    LIFTED_F4AE150_STACK = 76,
    LIFTED_F4AE1F0_STACK = 68,
    LIFTED_F4AE250_STACK = 80,
    LIFTED_F4AF2A0_STACK = 80,
    LIFTED_F4AF2E0_STACK = 64,
    LIFTED_F4AF340_STACK = 64,
    LIFTED_F4AF370_STACK = 72,
    LIFTED_F4AF530_STACK = 68,
    LIFTED_F4AF560_STACK = 244,
    LIFTED_F4B0B70_STACK = 136,
    LIFTED_F4B14C0_STACK = 96,
    LIFTED_F4B15E0_STACK = 96,
    LIFTED_F4B17B0_STACK = 76,
    LIFTED_F4B1FA0_STACK = 232,
    LIFTED_F4B2290_STACK = 68,
    LIFTED_F4B22C0_STACK = 80,
    LIFTED_F4B2300_STACK = 72,
    LIFTED_F4B2340_STACK = 76,
    LIFTED_F4B2380_STACK = 80,
    LIFTED_F4B23C0_STACK = 76,
    LIFTED_F4B3100_STACK = 68,
    LIFTED_F4B3340_STACK = 80,
    LIFTED_F4B3360_STACK = 64,
    LIFTED_F4B34D0_STACK = 68,
    LIFTED_F4B3500_STACK = 156,
    LIFTED_F4B35B0_STACK = 64,
    LIFTED_F4B3A00_STACK = 212,
    LIFTED_F4B3C30_STACK = 64,
    LIFTED_F4B3CE0_STACK = 112,
    LIFTED_F4B3D60_STACK = 112,
    LIFTED_F4B3FB0_STACK = 68,
    LIFTED_F4B4270_STACK = 80,
    LIFTED_F4B4500_STACK = 64,
    LIFTED_F4B4510_STACK = 68,
    LIFTED_F4B45F0_STACK = 72,
    LIFTED_F4B4600_STACK = 68,
    LIFTED_F4B4610_STACK = 68,
    LIFTED_F4B4620_STACK = 68,
    LIFTED_F4B4630_STACK = 80,
    LIFTED_F4B4660_STACK = 76,
    LIFTED_F4B4690_STACK = 80,
    LIFTED_F4B46E0_STACK = 72,
    LIFTED_F4B4700_STACK = 96,
    LIFTED_F4B4780_STACK = 72,
    LIFTED_F4B4C90_STACK = 72,
    LIFTED_F4B4CB0_STACK = 68,
    LIFTED_F4B4CD0_STACK = 72,
    LIFTED_F4B4CF0_STACK = 252,
    LIFTED_F4B4FA0_STACK = 64,
    LIFTED_F4B5050_STACK = 112,
    LIFTED_F4B50D0_STACK = 112,
    LIFTED_F4B5150_STACK = 128,
    LIFTED_F4B5400_STACK = 68,
    LIFTED_F4B5420_STACK = 156,
    LIFTED_F4B54D0_STACK = 68,
    LIFTED_F4B5500_STACK = 84,
    LIFTED_F4B5550_STACK = 68,
    LIFTED_F4B5560_STACK = 76,
    LIFTED_F4B5580_STACK = 136,
    LIFTED_F4B5630_STACK = 160,
    LIFTED_F4B5C60_STACK = 68,
    LIFTED_F4B5D40_STACK = 84,
    LIFTED_F4B5DB0_STACK = 68,
    LIFTED_F4B5DC0_STACK = 168,
    LIFTED_F4B5E70_STACK = 80,
    LIFTED_F4B5EB0_STACK = 72,
    LIFTED_F4B5F50_STACK = 100,
    LIFTED_F4B5FC0_STACK = 100,
    LIFTED_F4B6020_STACK = 88,
    LIFTED_F4B6070_STACK = 96,
    LIFTED_F4B60C0_STACK = 100,
    LIFTED_F4B6120_STACK = 96,
    LIFTED_F4B6170_STACK = 96,
    LIFTED_F4B61C0_STACK = 88,
    LIFTED_F4B6200_STACK = 88,
    LIFTED_F4B6460_STACK = 160,
    LIFTED_F4B6530_STACK = 64,
    LIFTED_F4B6540_STACK = 64,
    LIFTED_F4B6550_STACK = 64,
    LIFTED_F4B6560_STACK = 68,
    LIFTED_F4B6590_STACK = 64,
    LIFTED_F4B65A0_STACK = 64,
    LIFTED_F4B65B0_STACK = 64,
    LIFTED_F4B6690_STACK = 64,
    LIFTED_F4B66C0_STACK = 72,
    LIFTED_F4B6700_STACK = 84,
    LIFTED_F4B6800_STACK = 140,
    LIFTED_F4B6890_STACK = 68,
    LIFTED_F4B69F0_STACK = 76,
    LIFTED_F4B6A10_STACK = 68,
    LIFTED_F4B6EA0_STACK = 68,
    LIFTED_F4B6F70_STACK = 80,
    LIFTED_F4B6FA0_STACK = 68,
    LIFTED_F4B7020_STACK = 100,
    LIFTED_F4B7600_STACK = 68,
    LIFTED_F4B76D0_STACK = 92,
    LIFTED_F4B78D0_STACK = 68,
    LIFTED_F4B78E0_STACK = 172,
    LIFTED_F4B79A0_STACK = 80,
    LIFTED_F4B79C0_STACK = 72,
    LIFTED_F4B7A80_STACK = 72,
    LIFTED_F4B7B00_STACK = 100,
    LIFTED_F4B7B80_STACK = 104,
    LIFTED_F4B7C90_STACK = 96,
    LIFTED_F4B7CD0_STACK = 76,
    LIFTED_F4B7D70_STACK = 76,
    LIFTED_F4B7DA0_STACK = 64,
    LIFTED_F4B7DB0_STACK = 84,
    LIFTED_F4B7E80_STACK = 164,
    LIFTED_F4B8170_STACK = 80,
    LIFTED_F4B826F_STACK = 436,
    LIFTED_F4B8FBC_STACK = 108,
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
    LIFTED_F4C0990_STACK = 68,
    LIFTED_F4C09E0_STACK = 88,
    LIFTED_F4C0B51_STACK = 96,
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
    LIFTED_F4C3FA0_STACK = 64,
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
    LIFTED_F4C5BF0_STACK = 64,
    LIFTED_F4C5C00_STACK = 68,
    LIFTED_F4C5C10_STACK = 64,
    LIFTED_F4C5C20_STACK = 64,
    LIFTED_F4C5D60_STACK = 64,
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
    LIFTED_F4C9840_STACK = 72,
    LIFTED_F4C9860_STACK = 88,
    LIFTED_F4C98F0_STACK = 72,
    LIFTED_F4C9DAF_STACK = 76,
    LIFTED_F4C9DD6_STACK = 76,
    LIFTED_F4C9E00_STACK = 76,
    LIFTED_F4C9FE0_STACK = 76,
    LIFTED_F4C9FF0_STACK = 92,
    LIFTED_F4CA000_STACK = 92,
    LIFTED_F4CA060_STACK = 64,
    LIFTED_F4CA070_STACK = 80,
    LIFTED_F4CA090_STACK = 92,
    LIFTED_F4CA0D0_STACK = 84,
    LIFTED_F4CA110_STACK = 92,
    LIFTED_F4CA150_STACK = 76,
    LIFTED_F4CA1A0_STACK = 88,
    LIFTED_F4CA1E0_STACK = 76,
    LIFTED_F4CA210_STACK = 84,
    LIFTED_F4CA240_STACK = 84,
    LIFTED_F4CA280_STACK = 104,
    LIFTED_F4CA2E0_STACK = 84,
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
    LIFTED_F4CA6C0_STACK = 84,
    LIFTED_F4CA6F0_STACK = 76,
    LIFTED_F4CA710_STACK = 84,
    LIFTED_F4CA730_STACK = 108,
    LIFTED_F4CA770_STACK = 100,
    LIFTED_F4CA970_STACK = 128,
    LIFTED_F4CAFD0_STACK = 92,
    LIFTED_F4CB080_STACK = 100,
    LIFTED_F4CB390_STACK = 64,
    LIFTED_F4CB3A0_STACK = 64,
    LIFTED_F4CB3B0_STACK = 64,
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
    LIFTED_F4CCEE0_STACK = 84,
    LIFTED_F4CCFE0_STACK = 72,
    LIFTED_F4CD090_STACK = 72,
    LIFTED_F4CD0A4_STACK = 76,
    LIFTED_F4CD520_STACK = 92,
    LIFTED_F4CD7DC_STACK = 84,
    LIFTED_F4CD836_STACK = 76,
    LIFTED_F4CD847_STACK = 84,
    LIFTED_F4CDA40_STACK = 92,
    LIFTED_F4CDA90_STACK = 88,
    LIFTED_F4CDAF0_STACK = 116,
    LIFTED_F4CDB70_STACK = 112,
    LIFTED_F4CDFE0_STACK = 88,
    LIFTED_F4CE080_STACK = 76,
    LIFTED_F4CE230_STACK = 68,
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
    LIFTED_F4CFA10_STACK = 64,
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
    LIFTED_F4D25E0_STACK = 64,
    LIFTED_F4D2700_STACK = 64,
    LIFTED_F4D28C0_STACK = 128,
    LIFTED_F4D2910_STACK = 136,
    LIFTED_F4D2A00_STACK = 252,
    LIFTED_F4D2BB0_STACK = 104,
    LIFTED_F4D2D70_STACK = 64
};

/* Original 0x4ac740. */
uint32_t lifted_f4ac740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac750. */
uint32_t lifted_f4ac750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac760. */
uint32_t lifted_f4ac760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac780. */
uint32_t lifted_f4ac780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac7a0. */
uint32_t lifted_f4ac7a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac7b0. */
uint32_t lifted_f4ac7b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac7d0. */
uint32_t lifted_f4ac7d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac7e0. */
uint32_t lifted_f4ac7e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac810. */
uint32_t lifted_f4ac810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac840. */
uint32_t lifted_f4ac840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac860. */
uint32_t lifted_f4ac860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac8a0. */
uint32_t lifted_f4ac8a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac8d0. */
uint32_t lifted_f4ac8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac8f0. */
uint32_t lifted_f4ac8f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac900. */
uint32_t lifted_f4ac900(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac910. */
uint32_t lifted_f4ac910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac920. */
uint32_t lifted_f4ac920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac930. */
uint32_t lifted_f4ac930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac940. */
uint32_t lifted_f4ac940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac950. */
uint32_t lifted_f4ac950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac960. */
uint32_t lifted_f4ac960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac980. */
uint32_t lifted_f4ac980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aca00. */
uint32_t lifted_f4aca00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aca60. */
uint32_t lifted_f4aca60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4acab0. */
uint32_t lifted_f4acab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4acb00. */
uint32_t lifted_f4acb00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4acc10. */
uint32_t lifted_f4acc10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4acc70. */
uint32_t lifted_f4acc70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4accc0. */
uint32_t lifted_f4accc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4acd30. */
uint32_t lifted_f4acd30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ace40. */
uint32_t lifted_f4ace40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad060. */
uint32_t lifted_f4ad060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad110. */
uint32_t lifted_f4ad110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad1c0. */
uint32_t lifted_f4ad1c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad210. */
uint32_t lifted_f4ad210(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad260. */
uint32_t lifted_f4ad260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad2c0. */
uint32_t lifted_f4ad2c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad3c0. */
uint32_t lifted_f4ad3c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad440. */
uint32_t lifted_f4ad440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad510. */
uint32_t lifted_f4ad510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad520. */
uint32_t lifted_f4ad520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad530. */
uint32_t lifted_f4ad530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad580. */
uint32_t lifted_f4ad580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad5e0. */
uint32_t lifted_f4ad5e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad630. */
uint32_t lifted_f4ad630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad6e0. */
uint32_t lifted_f4ad6e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad720. */
uint32_t lifted_f4ad720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad750. */
uint32_t lifted_f4ad750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad790. */
uint32_t lifted_f4ad790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad870. */
uint32_t lifted_f4ad870(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ade20. */
uint32_t lifted_f4ade20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ade60. */
uint32_t lifted_f4ade60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4adf20. */
uint32_t lifted_f4adf20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4adf70. */
uint32_t lifted_f4adf70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4adfa0. */
uint32_t lifted_f4adfa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4adfb0. */
uint32_t lifted_f4adfb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4adfe0. */
uint32_t lifted_f4adfe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ae010. */
uint32_t lifted_f4ae010(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ae110. */
uint32_t lifted_f4ae110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ae140. */
uint32_t lifted_f4ae140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

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

/* Original 0x4af2e0. */
uint32_t lifted_f4af2e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4af340. */
uint32_t lifted_f4af340(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4af370. */
uint32_t lifted_f4af370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4af530. */
uint32_t lifted_f4af530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4af560. */
uint32_t lifted_f4af560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b0b70. */
uint32_t lifted_f4b0b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b14c0. */
uint32_t lifted_f4b14c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b15e0. */
uint32_t lifted_f4b15e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b17b0. */
uint32_t lifted_f4b17b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b1fa0. */
uint32_t lifted_f4b1fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b2290. */
uint32_t lifted_f4b2290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b22c0. */
uint32_t lifted_f4b22c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4b3360(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b34d0. */
uint32_t lifted_f4b34d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3500. */
uint32_t lifted_f4b3500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b35b0. */
uint32_t lifted_f4b35b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3a00. */
uint32_t lifted_f4b3a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3c30. */
uint32_t lifted_f4b3c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4b4500. */
uint32_t lifted_f4b4500(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4b4630. */
uint32_t lifted_f4b4630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4660. */
uint32_t lifted_f4b4660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4690. */
uint32_t lifted_f4b4690(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b46e0. */
uint32_t lifted_f4b46e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4700. */
uint32_t lifted_f4b4700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4780. */
uint32_t lifted_f4b4780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4c90. */
uint32_t lifted_f4b4c90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4cb0. */
uint32_t lifted_f4b4cb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4cd0. */
uint32_t lifted_f4b4cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4cf0. */
uint32_t lifted_f4b4cf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4fa0. */
uint32_t lifted_f4b4fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4b5560. */
uint32_t lifted_f4b5560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5580. */
uint32_t lifted_f4b5580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5630. */
uint32_t lifted_f4b5630(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4b5eb0. */
uint32_t lifted_f4b5eb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5f50. */
uint32_t lifted_f4b5f50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5fc0. */
uint32_t lifted_f4b5fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6020. */
uint32_t lifted_f4b6020(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4b6200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6460. */
uint32_t lifted_f4b6460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6530. */
uint32_t lifted_f4b6530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6540. */
uint32_t lifted_f4b6540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6550. */
uint32_t lifted_f4b6550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6560. */
uint32_t lifted_f4b6560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6590. */
uint32_t lifted_f4b6590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b65a0. */
uint32_t lifted_f4b65a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b65b0. */
uint32_t lifted_f4b65b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4b6fa0. */
uint32_t lifted_f4b6fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7020. */
uint32_t lifted_f4b7020(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4b79c0. */
uint32_t lifted_f4b79c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7a80. */
uint32_t lifted_f4b7a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4b7cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7d70. */
uint32_t lifted_f4b7d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7da0. */
uint32_t lifted_f4b7da0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7db0. */
uint32_t lifted_f4b7db0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7e80. */
uint32_t lifted_f4b7e80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b8170. */
uint32_t lifted_f4b8170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b826f. */
uint32_t lifted_f4b826f(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b8fbc. */
uint32_t lifted_f4b8fbc(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4c0990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c09e0. */
uint32_t lifted_f4c09e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c0b51. */
uint32_t lifted_f4c0b51(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4c3fa0. */
uint32_t lifted_f4c3fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4c5bf0. */
uint32_t lifted_f4c5bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5c00. */
uint32_t lifted_f4c5c00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5c10. */
uint32_t lifted_f4c5c10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5c20. */
uint32_t lifted_f4c5c20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5d60. */
uint32_t lifted_f4c5d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4c9840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9860. */
uint32_t lifted_f4c9860(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ca2e0. */
uint32_t lifted_f4ca2e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ca6c0. */
uint32_t lifted_f4ca6c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca6f0. */
uint32_t lifted_f4ca6f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ccee0. */
uint32_t lifted_f4ccee0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4cd7dc. */
uint32_t lifted_f4cd7dc(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4cfa10. */
uint32_t lifted_f4cfa10(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d25e0. */
uint32_t lifted_f4d25e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2700. */
uint32_t lifted_f4d2700(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4d2d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
