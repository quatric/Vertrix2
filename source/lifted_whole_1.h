#ifndef VERTRIX_LIFTED_WHOLE_1_H
#define VERTRIX_LIFTED_WHOLE_1_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F449390_STACK = 88,
    LIFTED_F4493D0_STACK = 108,
    LIFTED_F449460_STACK = 92,
    LIFTED_F4494C0_STACK = 92,
    LIFTED_F449710_STACK = 112,
    LIFTED_F449870_STACK = 96,
    LIFTED_F449A50_STACK = 92,
    LIFTED_F449E10_STACK = 96,
    LIFTED_F449FF0_STACK = 92,
    LIFTED_F44A340_STACK = 92,
    LIFTED_F44A520_STACK = 92,
    LIFTED_F44A570_STACK = 88,
    LIFTED_F44A5C0_STACK = 88,
    LIFTED_F44A610_STACK = 112,
    LIFTED_F44A6D0_STACK = 96,
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
    LIFTED_F44C2A0_STACK = 68,
    LIFTED_F44C2B0_STACK = 104,
    LIFTED_F44C310_STACK = 104,
    LIFTED_F44C370_STACK = 104,
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
    LIFTED_F44C860_STACK = 76,
    LIFTED_F44C880_STACK = 108,
    LIFTED_F44C8E0_STACK = 108,
    LIFTED_F44C940_STACK = 76,
    LIFTED_F44C960_STACK = 108,
    LIFTED_F44C9D0_STACK = 108,
    LIFTED_F44CA40_STACK = 108,
    LIFTED_F44CAB0_STACK = 120,
    LIFTED_F44CB50_STACK = 120,
    LIFTED_F44CBF0_STACK = 108,
    LIFTED_F44CC60_STACK = 108,
    LIFTED_F44CE80_STACK = 108,
    LIFTED_F44CF00_STACK = 108,
    LIFTED_F44CF70_STACK = 108,
    LIFTED_F44CFD0_STACK = 108,
    LIFTED_F44D1E0_STACK = 108,
    LIFTED_F44D250_STACK = 108,
    LIFTED_F44D2C0_STACK = 108,
    LIFTED_F44D330_STACK = 108,
    LIFTED_F44D3A0_STACK = 108,
    LIFTED_F44D410_STACK = 108,
    LIFTED_F44D480_STACK = 108,
    LIFTED_F44D4F0_STACK = 108,
    LIFTED_F44D560_STACK = 120,
    LIFTED_F44D5F0_STACK = 108,
    LIFTED_F44D660_STACK = 108,
    LIFTED_F44D6D0_STACK = 120,
    LIFTED_F44D760_STACK = 108,
    LIFTED_F44D7D0_STACK = 108,
    LIFTED_F44D840_STACK = 108,
    LIFTED_F44D8B0_STACK = 116,
    LIFTED_F44D940_STACK = 116,
    LIFTED_F44D9D0_STACK = 120,
    LIFTED_F44DA70_STACK = 120,
    LIFTED_F44DB10_STACK = 120,
    LIFTED_F44DBB0_STACK = 124,
    LIFTED_F44DC80_STACK = 108,
    LIFTED_F44DCF0_STACK = 128,
    LIFTED_F44E250_STACK = 120,
    LIFTED_F44E2D0_STACK = 120,
    LIFTED_F44E380_STACK = 120,
    LIFTED_F44E410_STACK = 116,
    LIFTED_F44E4A0_STACK = 108,
    LIFTED_F44E510_STACK = 108,
    LIFTED_F44E590_STACK = 108,
    LIFTED_F44E600_STACK = 108,
    LIFTED_F44E670_STACK = 108,
    LIFTED_F44E6E0_STACK = 124,
    LIFTED_F44E790_STACK = 108,
    LIFTED_F44E800_STACK = 120,
    LIFTED_F44E890_STACK = 116,
    LIFTED_F44EBE0_STACK = 108,
    LIFTED_F44EC40_STACK = 120,
    LIFTED_F44F040_STACK = 108,
    LIFTED_F44F0B0_STACK = 108,
    LIFTED_F44F120_STACK = 108,
    LIFTED_F44F180_STACK = 108,
    LIFTED_F44F1E0_STACK = 108,
    LIFTED_F44F240_STACK = 108,
    LIFTED_F44F2B0_STACK = 108,
    LIFTED_F44F320_STACK = 108,
    LIFTED_F44F390_STACK = 104,
    LIFTED_F44F3E0_STACK = 104,
    LIFTED_F44F430_STACK = 108,
    LIFTED_F44F4A0_STACK = 108,
    LIFTED_F44F500_STACK = 108,
    LIFTED_F44F560_STACK = 108,
    LIFTED_F44F5D0_STACK = 108,
    LIFTED_F44F630_STACK = 108,
    LIFTED_F44F690_STACK = 108,
    LIFTED_F44F700_STACK = 108,
    LIFTED_F44F770_STACK = 108,
    LIFTED_F44F7E0_STACK = 120,
    LIFTED_F44F880_STACK = 120,
    LIFTED_F44F920_STACK = 108,
    LIFTED_F44F990_STACK = 108,
    LIFTED_F44FA00_STACK = 108,
    LIFTED_F44FA70_STACK = 80,
    LIFTED_F44FAA0_STACK = 84,
    LIFTED_F44FAD0_STACK = 100,
    LIFTED_F44FB40_STACK = 104,
    LIFTED_F44FBB0_STACK = 96,
    LIFTED_F44FC00_STACK = 80,
    LIFTED_F44FC30_STACK = 84,
    LIFTED_F44FC60_STACK = 104,
    LIFTED_F44FCF0_STACK = 104,
    LIFTED_F44FD60_STACK = 96,
    LIFTED_F44FDB0_STACK = 108,
    LIFTED_F44FE30_STACK = 96,
    LIFTED_F44FE80_STACK = 84,
    LIFTED_F44FED0_STACK = 96,
    LIFTED_F44FF30_STACK = 88,
    LIFTED_F44FF60_STACK = 80,
    LIFTED_F44FF90_STACK = 88,
    LIFTED_F44FFF0_STACK = 96,
    LIFTED_F450040_STACK = 92,
    LIFTED_F4500B0_STACK = 100,
    LIFTED_F450100_STACK = 80,
    LIFTED_F450130_STACK = 92,
    LIFTED_F4501A0_STACK = 96,
    LIFTED_F450200_STACK = 96,
    LIFTED_F450270_STACK = 108,
    LIFTED_F450300_STACK = 80,
    LIFTED_F450330_STACK = 108,
    LIFTED_F4503B0_STACK = 124,
    LIFTED_F450450_STACK = 120,
    LIFTED_F4504E0_STACK = 104,
    LIFTED_F450550_STACK = 108,
    LIFTED_F4505C0_STACK = 108,
    LIFTED_F450630_STACK = 104,
    LIFTED_F4506A0_STACK = 108,
    LIFTED_F450710_STACK = 76,
    LIFTED_F450730_STACK = 76,
    LIFTED_F450750_STACK = 96,
    LIFTED_F4507E0_STACK = 88,
    LIFTED_F450830_STACK = 88,
    LIFTED_F450860_STACK = 88,
    LIFTED_F4508C0_STACK = 104,
    LIFTED_F450920_STACK = 84,
    LIFTED_F450960_STACK = 96,
    LIFTED_F4509A0_STACK = 88,
    LIFTED_F4509D0_STACK = 80,
    LIFTED_F450A10_STACK = 104,
    LIFTED_F450AA0_STACK = 116,
    LIFTED_F450B30_STACK = 96,
    LIFTED_F450B90_STACK = 96,
    LIFTED_F450BF0_STACK = 100,
    LIFTED_F450C70_STACK = 100,
    LIFTED_F450CD0_STACK = 104,
    LIFTED_F450D40_STACK = 104,
    LIFTED_F450DF0_STACK = 92,
    LIFTED_F450E70_STACK = 148,
    LIFTED_F450F60_STACK = 72,
    LIFTED_F450F80_STACK = 84,
    LIFTED_F4513D0_STACK = 72,
    LIFTED_F4513F0_STACK = 116,
    LIFTED_F451520_STACK = 100,
    LIFTED_F451630_STACK = 100,
    LIFTED_F451690_STACK = 116,
    LIFTED_F451A60_STACK = 88,
    LIFTED_F451AA0_STACK = 164,
    LIFTED_F451C00_STACK = 108,
    LIFTED_F451DD0_STACK = 92,
    LIFTED_F451F10_STACK = 92,
    LIFTED_F452050_STACK = 72,
    LIFTED_F452070_STACK = 88,
    LIFTED_F4520B0_STACK = 88,
    LIFTED_F4520F0_STACK = 112,
    LIFTED_F452160_STACK = 136,
    LIFTED_F452250_STACK = 96,
    LIFTED_F4522C0_STACK = 108,
    LIFTED_F452370_STACK = 88,
    LIFTED_F4523D0_STACK = 88,
    LIFTED_F452440_STACK = 136,
    LIFTED_F4526E0_STACK = 116,
    LIFTED_F452830_STACK = 100,
    LIFTED_F452880_STACK = 104,
    LIFTED_F4528E0_STACK = 112,
    LIFTED_F452A30_STACK = 80,
    LIFTED_F452A50_STACK = 128,
    LIFTED_F452B00_STACK = 80,
    LIFTED_F452B20_STACK = 116,
    LIFTED_F452BB0_STACK = 80,
    LIFTED_F452BD0_STACK = 116,
    LIFTED_F452C60_STACK = 80,
    LIFTED_F452C80_STACK = 116,
    LIFTED_F452D10_STACK = 104,
    LIFTED_F452D70_STACK = 128,
    LIFTED_F452E00_STACK = 192,
    LIFTED_F452FC0_STACK = 104,
    LIFTED_F453280_STACK = 116,
    LIFTED_F453320_STACK = 120,
    LIFTED_F4533B0_STACK = 128,
    LIFTED_F453460_STACK = 112,
    LIFTED_F4534E0_STACK = 112,
    LIFTED_F453570_STACK = 100,
    LIFTED_F4535D0_STACK = 100,
    LIFTED_F453620_STACK = 100,
    LIFTED_F453670_STACK = 100,
    LIFTED_F4536C0_STACK = 96,
    LIFTED_F453710_STACK = 96,
    LIFTED_F453760_STACK = 96,
    LIFTED_F4537B0_STACK = 100,
    LIFTED_F453800_STACK = 100,
    LIFTED_F453850_STACK = 100,
    LIFTED_F4538A0_STACK = 100,
    LIFTED_F4538F0_STACK = 100,
    LIFTED_F453940_STACK = 100,
    LIFTED_F453990_STACK = 100,
    LIFTED_F4539E0_STACK = 100,
    LIFTED_F453A30_STACK = 96,
    LIFTED_F453A80_STACK = 100,
    LIFTED_F453B90_STACK = 112,
    LIFTED_F453C00_STACK = 108,
    LIFTED_F453C90_STACK = 120,
    LIFTED_F453D50_STACK = 172,
    LIFTED_F453EF0_STACK = 92,
    LIFTED_F453F40_STACK = 108,
    LIFTED_F453FD0_STACK = 120,
    LIFTED_F454090_STACK = 156,
    LIFTED_F454200_STACK = 92,
    LIFTED_F454250_STACK = 108,
    LIFTED_F4542E0_STACK = 120,
    LIFTED_F4543A0_STACK = 156,
    LIFTED_F454510_STACK = 92,
    LIFTED_F454560_STACK = 120,
    LIFTED_F4546A0_STACK = 128,
    LIFTED_F454760_STACK = 92,
    LIFTED_F4547B0_STACK = 104,
    LIFTED_F454830_STACK = 132,
    LIFTED_F4548E0_STACK = 116,
    LIFTED_F454970_STACK = 100,
    LIFTED_F4549D0_STACK = 104,
    LIFTED_F454A50_STACK = 132,
    LIFTED_F454B20_STACK = 120,
    LIFTED_F454BD0_STACK = 100,
    LIFTED_F454C30_STACK = 104,
    LIFTED_F454CB0_STACK = 132,
    LIFTED_F454D80_STACK = 120,
    LIFTED_F454E30_STACK = 100,
    LIFTED_F454E90_STACK = 104,
    LIFTED_F454F00_STACK = 132,
    LIFTED_F454FC0_STACK = 100,
    LIFTED_F455020_STACK = 104,
    LIFTED_F4552B0_STACK = 100,
    LIFTED_F455320_STACK = 100,
    LIFTED_F4553A0_STACK = 132,
    LIFTED_F4554A0_STACK = 112,
    LIFTED_F455510_STACK = 104,
    LIFTED_F455580_STACK = 108,
    LIFTED_F455600_STACK = 112,
    LIFTED_F455670_STACK = 116,
    LIFTED_F455700_STACK = 108,
    LIFTED_F455790_STACK = 124,
    LIFTED_F455830_STACK = 128,
    LIFTED_F4558E0_STACK = 116,
    LIFTED_F455970_STACK = 108,
    LIFTED_F455A00_STACK = 116,
    LIFTED_F455A90_STACK = 112,
    LIFTED_F455B20_STACK = 104,
    LIFTED_F455B90_STACK = 124,
    LIFTED_F455C30_STACK = 100,
    LIFTED_F455CA0_STACK = 104,
    LIFTED_F455D10_STACK = 124,
    LIFTED_F455DB0_STACK = 96,
    LIFTED_F455E00_STACK = 92,
    LIFTED_F455E50_STACK = 128,
    LIFTED_F455F10_STACK = 108,
    LIFTED_F455F80_STACK = 132,
    LIFTED_F456060_STACK = 104,
    LIFTED_F4560C0_STACK = 136,
    LIFTED_F456290_STACK = 96,
    LIFTED_F456300_STACK = 124,
    LIFTED_F456490_STACK = 96,
    LIFTED_F4564E0_STACK = 124,
    LIFTED_F4566D0_STACK = 124,
    LIFTED_F4568C0_STACK = 84,
    LIFTED_F456900_STACK = 120,
    LIFTED_F456980_STACK = 112,
    LIFTED_F456A00_STACK = 112,
    LIFTED_F456A80_STACK = 120,
    LIFTED_F456B00_STACK = 120,
    LIFTED_F456B80_STACK = 112,
    LIFTED_F456BF0_STACK = 100,
    LIFTED_F456CA0_STACK = 72,
    LIFTED_F456CD0_STACK = 108,
    LIFTED_F456D80_STACK = 96,
    LIFTED_F456DE0_STACK = 96,
    LIFTED_F456E40_STACK = 96,
    LIFTED_F456EA0_STACK = 104,
    LIFTED_F456F10_STACK = 108,
    LIFTED_F456FA0_STACK = 96,
    LIFTED_F457000_STACK = 100,
    LIFTED_F457060_STACK = 96,
    LIFTED_F457170_STACK = 92,
    LIFTED_F4571F0_STACK = 124,
    LIFTED_F4572B0_STACK = 92,
    LIFTED_F457420_STACK = 92,
    LIFTED_F457460_STACK = 92,
    LIFTED_F4574A0_STACK = 112,
    LIFTED_F457550_STACK = 104,
    LIFTED_F4575B0_STACK = 132,
    LIFTED_F457670_STACK = 100,
    LIFTED_F4576D0_STACK = 100,
    LIFTED_F457730_STACK = 76,
    LIFTED_F457770_STACK = 96,
    LIFTED_F457810_STACK = 108,
    LIFTED_F4578F0_STACK = 128,
    LIFTED_F457B70_STACK = 116,
    LIFTED_F457C10_STACK = 128,
    LIFTED_F457E40_STACK = 124,
    LIFTED_F4580B0_STACK = 96,
    LIFTED_F458100_STACK = 96,
    LIFTED_F458150_STACK = 124,
    LIFTED_F458260_STACK = 108,
    LIFTED_F4582D0_STACK = 108,
    LIFTED_F458330_STACK = 92,
    LIFTED_F4583C0_STACK = 96,
    LIFTED_F458410_STACK = 80,
    LIFTED_F458450_STACK = 96,
    LIFTED_F458490_STACK = 92,
    LIFTED_F4584F0_STACK = 108,
    LIFTED_F458560_STACK = 108,
    LIFTED_F458710_STACK = 112,
    LIFTED_F4587A0_STACK = 136,
    LIFTED_F4589E0_STACK = 100,
    LIFTED_F458D40_STACK = 124,
    LIFTED_F458F00_STACK = 116,
    LIFTED_F4590A0_STACK = 92,
    LIFTED_F459200_STACK = 84,
    LIFTED_F459760_STACK = 96,
    LIFTED_F4597A0_STACK = 96,
    LIFTED_F4597E0_STACK = 112,
    LIFTED_F459860_STACK = 92,
    LIFTED_F4598A0_STACK = 104,
    LIFTED_F459900_STACK = 96,
    LIFTED_F459950_STACK = 96,
    LIFTED_F4599E0_STACK = 96,
    LIFTED_F459A30_STACK = 112,
    LIFTED_F459AB0_STACK = 96,
    LIFTED_F459B00_STACK = 96,
    LIFTED_F459B60_STACK = 112,
    LIFTED_F459E00_STACK = 144,
    LIFTED_F45A0C0_STACK = 124,
    LIFTED_F45A3E0_STACK = 104,
    LIFTED_F45A440_STACK = 124,
    LIFTED_F45A750_STACK = 132,
    LIFTED_F45A830_STACK = 132,
    LIFTED_F45AA20_STACK = 104,
    LIFTED_F45AA70_STACK = 88,
    LIFTED_F45AAB0_STACK = 156,
    LIFTED_F45AC70_STACK = 132,
    LIFTED_F45AEA0_STACK = 124,
    LIFTED_F45AF40_STACK = 128,
    LIFTED_F45B0B0_STACK = 92,
    LIFTED_F45B0F0_STACK = 92,
    LIFTED_F45B130_STACK = 84,
    LIFTED_F45B150_STACK = 92,
    LIFTED_F45B190_STACK = 168,
    LIFTED_F45B410_STACK = 132,
    LIFTED_F45B4C0_STACK = 136,
    LIFTED_F45B590_STACK = 104,
    LIFTED_F45B5F0_STACK = 152,
    LIFTED_F45B710_STACK = 108,
    LIFTED_F45B790_STACK = 108,
    LIFTED_F45B7F0_STACK = 108,
    LIFTED_F45B860_STACK = 108,
    LIFTED_F45B8D0_STACK = 108,
    LIFTED_F45B950_STACK = 108,
    LIFTED_F45B9C0_STACK = 104,
    LIFTED_F45BA30_STACK = 120,
    LIFTED_F45BAD0_STACK = 120,
    LIFTED_F45BB80_STACK = 108,
    LIFTED_F45BC00_STACK = 108,
    LIFTED_F45BC80_STACK = 108,
    LIFTED_F45BD00_STACK = 108,
    LIFTED_F45BD60_STACK = 108,
    LIFTED_F45BDD0_STACK = 108,
    LIFTED_F45BE40_STACK = 108,
    LIFTED_F45BEB0_STACK = 108,
    LIFTED_F45BF20_STACK = 108,
    LIFTED_F45BF80_STACK = 108,
    LIFTED_F45BFF0_STACK = 108,
    LIFTED_F45C060_STACK = 116,
    LIFTED_F45C0E0_STACK = 108,
    LIFTED_F45C150_STACK = 108,
    LIFTED_F45C1B0_STACK = 108,
    LIFTED_F45C210_STACK = 96,
    LIFTED_F45C250_STACK = 88,
    LIFTED_F45C2B0_STACK = 76,
    LIFTED_F45C3C0_STACK = 120,
    LIFTED_F45C480_STACK = 124,
    LIFTED_F45C540_STACK = 124,
    LIFTED_F45C6E0_STACK = 88
};

/* Original 0x449390. */
uint32_t lifted_f449390(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x449710. */
uint32_t lifted_f449710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449870. */
uint32_t lifted_f449870(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449a50. */
uint32_t lifted_f449a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f44c2a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c2b0. */
uint32_t lifted_f44c2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c310. */
uint32_t lifted_f44c310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c370. */
uint32_t lifted_f44c370(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f44c860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c880. */
uint32_t lifted_f44c880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c8e0. */
uint32_t lifted_f44c8e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c940. */
uint32_t lifted_f44c940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c960. */
uint32_t lifted_f44c960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c9d0. */
uint32_t lifted_f44c9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f44cbf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44cc60. */
uint32_t lifted_f44cc60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ce80. */
uint32_t lifted_f44ce80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44cf00. */
uint32_t lifted_f44cf00(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f44d410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

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
uint32_t lifted_f44d760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d7d0. */
uint32_t lifted_f44d7d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d840. */
uint32_t lifted_f44d840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d8b0. */
uint32_t lifted_f44d8b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d940. */
uint32_t lifted_f44d940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d9d0. */
uint32_t lifted_f44d9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44da70. */
uint32_t lifted_f44da70(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f44e250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e2d0. */
uint32_t lifted_f44e2d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e380. */
uint32_t lifted_f44e380(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e410. */
uint32_t lifted_f44e410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e4a0. */
uint32_t lifted_f44e4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e510. */
uint32_t lifted_f44e510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e590. */
uint32_t lifted_f44e590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e600. */
uint32_t lifted_f44e600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e670. */
uint32_t lifted_f44e670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e6e0. */
uint32_t lifted_f44e6e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e790. */
uint32_t lifted_f44e790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e800. */
uint32_t lifted_f44e800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e890. */
uint32_t lifted_f44e890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ebe0. */
uint32_t lifted_f44ebe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f44f120(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f180. */
uint32_t lifted_f44f180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f1e0. */
uint32_t lifted_f44f1e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f240. */
uint32_t lifted_f44f240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f2b0. */
uint32_t lifted_f44f2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f320. */
uint32_t lifted_f44f320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f390. */
uint32_t lifted_f44f390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f3e0. */
uint32_t lifted_f44f3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f430. */
uint32_t lifted_f44f430(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f4a0. */
uint32_t lifted_f44f4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f500. */
uint32_t lifted_f44f500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f560. */
uint32_t lifted_f44f560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f5d0. */
uint32_t lifted_f44f5d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f630. */
uint32_t lifted_f44f630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f690. */
uint32_t lifted_f44f690(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f44fa70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44faa0. */
uint32_t lifted_f44faa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fad0. */
uint32_t lifted_f44fad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fb40. */
uint32_t lifted_f44fb40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fbb0. */
uint32_t lifted_f44fbb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fc00. */
uint32_t lifted_f44fc00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fc30. */
uint32_t lifted_f44fc30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fc60. */
uint32_t lifted_f44fc60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fcf0. */
uint32_t lifted_f44fcf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fd60. */
uint32_t lifted_f44fd60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fdb0. */
uint32_t lifted_f44fdb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fe30. */
uint32_t lifted_f44fe30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fe80. */
uint32_t lifted_f44fe80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fed0. */
uint32_t lifted_f44fed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ff30. */
uint32_t lifted_f44ff30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ff60. */
uint32_t lifted_f44ff60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ff90. */
uint32_t lifted_f44ff90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fff0. */
uint32_t lifted_f44fff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450040. */
uint32_t lifted_f450040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4500b0. */
uint32_t lifted_f4500b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450100. */
uint32_t lifted_f450100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450130. */
uint32_t lifted_f450130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4501a0. */
uint32_t lifted_f4501a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450200. */
uint32_t lifted_f450200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450270. */
uint32_t lifted_f450270(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450300. */
uint32_t lifted_f450300(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450330. */
uint32_t lifted_f450330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4503b0. */
uint32_t lifted_f4503b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450450. */
uint32_t lifted_f450450(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4504e0. */
uint32_t lifted_f4504e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450550. */
uint32_t lifted_f450550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4505c0. */
uint32_t lifted_f4505c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450630. */
uint32_t lifted_f450630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4506a0. */
uint32_t lifted_f4506a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450710. */
uint32_t lifted_f450710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450730. */
uint32_t lifted_f450730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450750. */
uint32_t lifted_f450750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4507e0. */
uint32_t lifted_f4507e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450830. */
uint32_t lifted_f450830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450860. */
uint32_t lifted_f450860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4508c0. */
uint32_t lifted_f4508c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450920. */
uint32_t lifted_f450920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450960. */
uint32_t lifted_f450960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4509a0. */
uint32_t lifted_f4509a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4509d0. */
uint32_t lifted_f4509d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450a10. */
uint32_t lifted_f450a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450aa0. */
uint32_t lifted_f450aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450b30. */
uint32_t lifted_f450b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450b90. */
uint32_t lifted_f450b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450bf0. */
uint32_t lifted_f450bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450c70. */
uint32_t lifted_f450c70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450cd0. */
uint32_t lifted_f450cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450d40. */
uint32_t lifted_f450d40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450df0. */
uint32_t lifted_f450df0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450e70. */
uint32_t lifted_f450e70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450f60. */
uint32_t lifted_f450f60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450f80. */
uint32_t lifted_f450f80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4513d0. */
uint32_t lifted_f4513d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4513f0. */
uint32_t lifted_f4513f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451520. */
uint32_t lifted_f451520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451630. */
uint32_t lifted_f451630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451690. */
uint32_t lifted_f451690(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451a60. */
uint32_t lifted_f451a60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451aa0. */
uint32_t lifted_f451aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451c00. */
uint32_t lifted_f451c00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451dd0. */
uint32_t lifted_f451dd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451f10. */
uint32_t lifted_f451f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452050. */
uint32_t lifted_f452050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452070. */
uint32_t lifted_f452070(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4520b0. */
uint32_t lifted_f4520b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4520f0. */
uint32_t lifted_f4520f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452160. */
uint32_t lifted_f452160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452250. */
uint32_t lifted_f452250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4522c0. */
uint32_t lifted_f4522c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452370. */
uint32_t lifted_f452370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4523d0. */
uint32_t lifted_f4523d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452440. */
uint32_t lifted_f452440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4526e0. */
uint32_t lifted_f4526e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452830. */
uint32_t lifted_f452830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452880. */
uint32_t lifted_f452880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4528e0. */
uint32_t lifted_f4528e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452a30. */
uint32_t lifted_f452a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452a50. */
uint32_t lifted_f452a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452b00. */
uint32_t lifted_f452b00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452b20. */
uint32_t lifted_f452b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452bb0. */
uint32_t lifted_f452bb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452bd0. */
uint32_t lifted_f452bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452c60. */
uint32_t lifted_f452c60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452c80. */
uint32_t lifted_f452c80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452d10. */
uint32_t lifted_f452d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452d70. */
uint32_t lifted_f452d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452e00. */
uint32_t lifted_f452e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452fc0. */
uint32_t lifted_f452fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453280. */
uint32_t lifted_f453280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453320. */
uint32_t lifted_f453320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4533b0. */
uint32_t lifted_f4533b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453460. */
uint32_t lifted_f453460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4534e0. */
uint32_t lifted_f4534e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453570. */
uint32_t lifted_f453570(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4535d0. */
uint32_t lifted_f4535d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453620. */
uint32_t lifted_f453620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453670. */
uint32_t lifted_f453670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4536c0. */
uint32_t lifted_f4536c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453710. */
uint32_t lifted_f453710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453760. */
uint32_t lifted_f453760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4537b0. */
uint32_t lifted_f4537b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453800. */
uint32_t lifted_f453800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453850. */
uint32_t lifted_f453850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4538a0. */
uint32_t lifted_f4538a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4538f0. */
uint32_t lifted_f4538f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453940. */
uint32_t lifted_f453940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453990. */
uint32_t lifted_f453990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4539e0. */
uint32_t lifted_f4539e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453a30. */
uint32_t lifted_f453a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453a80. */
uint32_t lifted_f453a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453b90. */
uint32_t lifted_f453b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453c00. */
uint32_t lifted_f453c00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453c90. */
uint32_t lifted_f453c90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453d50. */
uint32_t lifted_f453d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453ef0. */
uint32_t lifted_f453ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453f40. */
uint32_t lifted_f453f40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453fd0. */
uint32_t lifted_f453fd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454090. */
uint32_t lifted_f454090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454200. */
uint32_t lifted_f454200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454250. */
uint32_t lifted_f454250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4542e0. */
uint32_t lifted_f4542e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4543a0. */
uint32_t lifted_f4543a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454510. */
uint32_t lifted_f454510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454560. */
uint32_t lifted_f454560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4546a0. */
uint32_t lifted_f4546a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454760. */
uint32_t lifted_f454760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4547b0. */
uint32_t lifted_f4547b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454830. */
uint32_t lifted_f454830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4548e0. */
uint32_t lifted_f4548e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454970. */
uint32_t lifted_f454970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4549d0. */
uint32_t lifted_f4549d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454a50. */
uint32_t lifted_f454a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454b20. */
uint32_t lifted_f454b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454bd0. */
uint32_t lifted_f454bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454c30. */
uint32_t lifted_f454c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454cb0. */
uint32_t lifted_f454cb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454d80. */
uint32_t lifted_f454d80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454e30. */
uint32_t lifted_f454e30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454e90. */
uint32_t lifted_f454e90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454f00. */
uint32_t lifted_f454f00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454fc0. */
uint32_t lifted_f454fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455020. */
uint32_t lifted_f455020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4552b0. */
uint32_t lifted_f4552b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455320. */
uint32_t lifted_f455320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4553a0. */
uint32_t lifted_f4553a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4554a0. */
uint32_t lifted_f4554a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455510. */
uint32_t lifted_f455510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455580. */
uint32_t lifted_f455580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455600. */
uint32_t lifted_f455600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455670. */
uint32_t lifted_f455670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455700. */
uint32_t lifted_f455700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455790. */
uint32_t lifted_f455790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455830. */
uint32_t lifted_f455830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4558e0. */
uint32_t lifted_f4558e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455970. */
uint32_t lifted_f455970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455a00. */
uint32_t lifted_f455a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455a90. */
uint32_t lifted_f455a90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455b20. */
uint32_t lifted_f455b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455b90. */
uint32_t lifted_f455b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455c30. */
uint32_t lifted_f455c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455ca0. */
uint32_t lifted_f455ca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455d10. */
uint32_t lifted_f455d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455db0. */
uint32_t lifted_f455db0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455e00. */
uint32_t lifted_f455e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455e50. */
uint32_t lifted_f455e50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455f10. */
uint32_t lifted_f455f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455f80. */
uint32_t lifted_f455f80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456060. */
uint32_t lifted_f456060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4560c0. */
uint32_t lifted_f4560c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456290. */
uint32_t lifted_f456290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456300. */
uint32_t lifted_f456300(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456490. */
uint32_t lifted_f456490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4564e0. */
uint32_t lifted_f4564e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4566d0. */
uint32_t lifted_f4566d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4568c0. */
uint32_t lifted_f4568c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456900. */
uint32_t lifted_f456900(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456980. */
uint32_t lifted_f456980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456a00. */
uint32_t lifted_f456a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456a80. */
uint32_t lifted_f456a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456b00. */
uint32_t lifted_f456b00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456b80. */
uint32_t lifted_f456b80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456bf0. */
uint32_t lifted_f456bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456ca0. */
uint32_t lifted_f456ca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456cd0. */
uint32_t lifted_f456cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456d80. */
uint32_t lifted_f456d80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456de0. */
uint32_t lifted_f456de0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456e40. */
uint32_t lifted_f456e40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456ea0. */
uint32_t lifted_f456ea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456f10. */
uint32_t lifted_f456f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456fa0. */
uint32_t lifted_f456fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457000. */
uint32_t lifted_f457000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457060. */
uint32_t lifted_f457060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457170. */
uint32_t lifted_f457170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4571f0. */
uint32_t lifted_f4571f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4572b0. */
uint32_t lifted_f4572b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457420. */
uint32_t lifted_f457420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457460. */
uint32_t lifted_f457460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4574a0. */
uint32_t lifted_f4574a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457550. */
uint32_t lifted_f457550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4575b0. */
uint32_t lifted_f4575b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457670. */
uint32_t lifted_f457670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4576d0. */
uint32_t lifted_f4576d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457730. */
uint32_t lifted_f457730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457770. */
uint32_t lifted_f457770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457810. */
uint32_t lifted_f457810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4578f0. */
uint32_t lifted_f4578f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457b70. */
uint32_t lifted_f457b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457c10. */
uint32_t lifted_f457c10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457e40. */
uint32_t lifted_f457e40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4580b0. */
uint32_t lifted_f4580b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458100. */
uint32_t lifted_f458100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458150. */
uint32_t lifted_f458150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458260. */
uint32_t lifted_f458260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4582d0. */
uint32_t lifted_f4582d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458330. */
uint32_t lifted_f458330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4583c0. */
uint32_t lifted_f4583c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458410. */
uint32_t lifted_f458410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458450. */
uint32_t lifted_f458450(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458490. */
uint32_t lifted_f458490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4584f0. */
uint32_t lifted_f4584f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458560. */
uint32_t lifted_f458560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458710. */
uint32_t lifted_f458710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4587a0. */
uint32_t lifted_f4587a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4589e0. */
uint32_t lifted_f4589e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458d40. */
uint32_t lifted_f458d40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458f00. */
uint32_t lifted_f458f00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4590a0. */
uint32_t lifted_f4590a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459200. */
uint32_t lifted_f459200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459760. */
uint32_t lifted_f459760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4597a0. */
uint32_t lifted_f4597a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4597e0. */
uint32_t lifted_f4597e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459860. */
uint32_t lifted_f459860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4598a0. */
uint32_t lifted_f4598a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459900. */
uint32_t lifted_f459900(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459950. */
uint32_t lifted_f459950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4599e0. */
uint32_t lifted_f4599e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459a30. */
uint32_t lifted_f459a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459ab0. */
uint32_t lifted_f459ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459b00. */
uint32_t lifted_f459b00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459b60. */
uint32_t lifted_f459b60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459e00. */
uint32_t lifted_f459e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a0c0. */
uint32_t lifted_f45a0c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a3e0. */
uint32_t lifted_f45a3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a440. */
uint32_t lifted_f45a440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a750. */
uint32_t lifted_f45a750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a830. */
uint32_t lifted_f45a830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45aa20. */
uint32_t lifted_f45aa20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45aa70. */
uint32_t lifted_f45aa70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45aab0. */
uint32_t lifted_f45aab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ac70. */
uint32_t lifted_f45ac70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45aea0. */
uint32_t lifted_f45aea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45af40. */
uint32_t lifted_f45af40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b0b0. */
uint32_t lifted_f45b0b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b0f0. */
uint32_t lifted_f45b0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b130. */
uint32_t lifted_f45b130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b150. */
uint32_t lifted_f45b150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b190. */
uint32_t lifted_f45b190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b410. */
uint32_t lifted_f45b410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b4c0. */
uint32_t lifted_f45b4c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b590. */
uint32_t lifted_f45b590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b5f0. */
uint32_t lifted_f45b5f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b710. */
uint32_t lifted_f45b710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b790. */
uint32_t lifted_f45b790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b7f0. */
uint32_t lifted_f45b7f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b860. */
uint32_t lifted_f45b860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b8d0. */
uint32_t lifted_f45b8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b950. */
uint32_t lifted_f45b950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b9c0. */
uint32_t lifted_f45b9c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ba30. */
uint32_t lifted_f45ba30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bad0. */
uint32_t lifted_f45bad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bb80. */
uint32_t lifted_f45bb80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bc00. */
uint32_t lifted_f45bc00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bc80. */
uint32_t lifted_f45bc80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bd00. */
uint32_t lifted_f45bd00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bd60. */
uint32_t lifted_f45bd60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bdd0. */
uint32_t lifted_f45bdd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45be40. */
uint32_t lifted_f45be40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45beb0. */
uint32_t lifted_f45beb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bf20. */
uint32_t lifted_f45bf20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bf80. */
uint32_t lifted_f45bf80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bff0. */
uint32_t lifted_f45bff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c060. */
uint32_t lifted_f45c060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c0e0. */
uint32_t lifted_f45c0e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c150. */
uint32_t lifted_f45c150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c1b0. */
uint32_t lifted_f45c1b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c210. */
uint32_t lifted_f45c210(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c250. */
uint32_t lifted_f45c250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c2b0. */
uint32_t lifted_f45c2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c3c0. */
uint32_t lifted_f45c3c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c480. */
uint32_t lifted_f45c480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c540. */
uint32_t lifted_f45c540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c6e0. */
uint32_t lifted_f45c6e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
