#ifndef VERTRIX_LIFTED_WHOLE_2_H
#define VERTRIX_LIFTED_WHOLE_2_H
#include <stdint.h>

#include "actor_build.h"

enum
{
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
    LIFTED_F457330_STACK = 132,
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
    LIFTED_F45AD20_STACK = 140,
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
    LIFTED_F45C6E0_STACK = 88,
    LIFTED_F45C760_STACK = 88,
    LIFTED_F45C7E0_STACK = 84,
    LIFTED_F45C830_STACK = 120,
    LIFTED_F45C8B0_STACK = 72,
    LIFTED_F45C8E0_STACK = 100,
    LIFTED_F45C940_STACK = 100,
    LIFTED_F45CC40_STACK = 140,
    LIFTED_F45CD00_STACK = 140,
    LIFTED_F45CDC0_STACK = 68,
    LIFTED_F45CDD0_STACK = 100,
    LIFTED_F45CE50_STACK = 104,
    LIFTED_F45CEB0_STACK = 108,
    LIFTED_F45CF30_STACK = 92,
    LIFTED_F45CF70_STACK = 116,
    LIFTED_F45D0C0_STACK = 92,
    LIFTED_F45D100_STACK = 92,
    LIFTED_F45D140_STACK = 84,
    LIFTED_F45D160_STACK = 92,
    LIFTED_F45D1A0_STACK = 168,
    LIFTED_F45D420_STACK = 132,
    LIFTED_F45D690_STACK = 132,
    LIFTED_F45D740_STACK = 108,
    LIFTED_F45D7B0_STACK = 108,
    LIFTED_F45D820_STACK = 96,
    LIFTED_F45E260_STACK = 212,
    LIFTED_F45E3C0_STACK = 120,
    LIFTED_F45E400_STACK = 120,
    LIFTED_F45E440_STACK = 128,
    LIFTED_F45E490_STACK = 116,
    LIFTED_F45E530_STACK = 96,
    LIFTED_F45E590_STACK = 124,
    LIFTED_F45E630_STACK = 116,
    LIFTED_F45E670_STACK = 72,
    LIFTED_F45E690_STACK = 72,
    LIFTED_F45E6B0_STACK = 104,
    LIFTED_F45E720_STACK = 72,
    LIFTED_F45E740_STACK = 68,
    LIFTED_F45E750_STACK = 136,
    LIFTED_F45E7B0_STACK = 128,
    LIFTED_F45E810_STACK = 68,
    LIFTED_F45E820_STACK = 68,
    LIFTED_F45E830_STACK = 76,
    LIFTED_F45E850_STACK = 136,
    LIFTED_F45E8D0_STACK = 72,
    LIFTED_F45E8F0_STACK = 76,
    LIFTED_F45E910_STACK = 84,
    LIFTED_F45E950_STACK = 76,
    LIFTED_F45E990_STACK = 84,
    LIFTED_F45E9E0_STACK = 136,
    LIFTED_F45EA60_STACK = 72,
    LIFTED_F45EA80_STACK = 80,
    LIFTED_F45EAC0_STACK = 348,
    LIFTED_F45EC00_STACK = 120,
    LIFTED_F45ECD0_STACK = 88,
    LIFTED_F45ED10_STACK = 92,
    LIFTED_F45ED40_STACK = 72,
    LIFTED_F45EE30_STACK = 128,
    LIFTED_F45F0A0_STACK = 84,
    LIFTED_F45F0C0_STACK = 120,
    LIFTED_F45F140_STACK = 124,
    LIFTED_F45F1F0_STACK = 108,
    LIFTED_F45F590_STACK = 84,
    LIFTED_F45F770_STACK = 276,
    LIFTED_F45FA70_STACK = 84,
    LIFTED_F45FAB0_STACK = 92,
    LIFTED_F45FB00_STACK = 228,
    LIFTED_F45FC80_STACK = 232,
    LIFTED_F45FE10_STACK = 140,
    LIFTED_F45FEE0_STACK = 140,
    LIFTED_F4601C0_STACK = 172,
    LIFTED_F460840_STACK = 252,
    LIFTED_F460A40_STACK = 112,
    LIFTED_F460AD0_STACK = 112,
    LIFTED_F460B60_STACK = 156,
    LIFTED_F460DF0_STACK = 160,
    LIFTED_F460ED0_STACK = 160,
    LIFTED_F460FA0_STACK = 180,
    LIFTED_F461090_STACK = 176,
    LIFTED_F4657F0_STACK = 292,
    LIFTED_F465A70_STACK = 124,
    LIFTED_F466D60_STACK = 2768,
    LIFTED_F46B810_STACK = 1096,
    LIFTED_F46C500_STACK = 152,
    LIFTED_F46C9D0_STACK = 2064,
    LIFTED_F46E8B0_STACK = 180,
    LIFTED_F470960_STACK = 240,
    LIFTED_F470B20_STACK = 240,
    LIFTED_F470D20_STACK = 368,
    LIFTED_F4710D0_STACK = 92,
    LIFTED_F471100_STACK = 112,
    LIFTED_F4711A0_STACK = 228,
    LIFTED_F471340_STACK = 128,
    LIFTED_F4717F0_STACK = 68,
    LIFTED_F471820_STACK = 64,
    LIFTED_F4718A0_STACK = 128,
    LIFTED_F471920_STACK = 84,
    LIFTED_F471940_STACK = 84,
    LIFTED_F471960_STACK = 84,
    LIFTED_F471980_STACK = 84,
    LIFTED_F4719A0_STACK = 68,
    LIFTED_F4719E0_STACK = 68,
    LIFTED_F4719F0_STACK = 72,
    LIFTED_F471A20_STACK = 72,
    LIFTED_F471A40_STACK = 72,
    LIFTED_F471A50_STACK = 72,
    LIFTED_F471A60_STACK = 68,
    LIFTED_F471A70_STACK = 68,
    LIFTED_F471A80_STACK = 68,
    LIFTED_F471A90_STACK = 68,
    LIFTED_F471AA0_STACK = 72,
    LIFTED_F471AB0_STACK = 72,
    LIFTED_F471AD0_STACK = 72,
    LIFTED_F471AE0_STACK = 72,
    LIFTED_F471AF0_STACK = 68,
    LIFTED_F471B00_STACK = 68,
    LIFTED_F471B10_STACK = 68,
    LIFTED_F471B20_STACK = 72,
    LIFTED_F471B30_STACK = 72,
    LIFTED_F471B50_STACK = 72,
    LIFTED_F471B60_STACK = 72,
    LIFTED_F471B70_STACK = 68,
    LIFTED_F471B80_STACK = 68,
    LIFTED_F471B90_STACK = 68,
    LIFTED_F471BA0_STACK = 72,
    LIFTED_F471BB0_STACK = 80,
    LIFTED_F471BF0_STACK = 88,
    LIFTED_F471C40_STACK = 88,
    LIFTED_F471C90_STACK = 80,
    LIFTED_F471CD0_STACK = 80,
    LIFTED_F471D10_STACK = 80,
    LIFTED_F471D50_STACK = 80,
    LIFTED_F471D90_STACK = 80,
    LIFTED_F471DD0_STACK = 80,
    LIFTED_F471E10_STACK = 92,
    LIFTED_F471E60_STACK = 72,
    LIFTED_F471E80_STACK = 72,
    LIFTED_F472020_STACK = 128,
    LIFTED_F472090_STACK = 128,
    LIFTED_F472100_STACK = 128,
    LIFTED_F472170_STACK = 128,
    LIFTED_F4721E0_STACK = 128,
    LIFTED_F472250_STACK = 128,
    LIFTED_F4722C0_STACK = 128,
    LIFTED_F472330_STACK = 68,
    LIFTED_F472350_STACK = 68,
    LIFTED_F472360_STACK = 80,
    LIFTED_F4723A0_STACK = 180,
    LIFTED_F472440_STACK = 72,
    LIFTED_F472460_STACK = 72,
    LIFTED_F472470_STACK = 128,
    LIFTED_F4724F0_STACK = 128,
    LIFTED_F472570_STACK = 128,
    LIFTED_F4725F0_STACK = 72,
    LIFTED_F472620_STACK = 136,
    LIFTED_F472AD0_STACK = 88,
    LIFTED_F472BD0_STACK = 84,
    LIFTED_F472C10_STACK = 132,
    LIFTED_F472D00_STACK = 92,
    LIFTED_F472DB0_STACK = 228,
    LIFTED_F4731A0_STACK = 288,
    LIFTED_F473490_STACK = 140,
    LIFTED_F4735E0_STACK = 76,
    LIFTED_F473610_STACK = 68,
    LIFTED_F473630_STACK = 148,
    LIFTED_F4737D0_STACK = 144,
    LIFTED_F473960_STACK = 144,
    LIFTED_F473AF0_STACK = 144,
    LIFTED_F473CD0_STACK = 72,
    LIFTED_F474540_STACK = 72,
    LIFTED_F4754E0_STACK = 72,
    LIFTED_F475510_STACK = 112,
    LIFTED_F475700_STACK = 136,
    LIFTED_F475790_STACK = 64,
    LIFTED_F4757E0_STACK = 72,
    LIFTED_F475A20_STACK = 96,
    LIFTED_F475A80_STACK = 96,
    LIFTED_F475AB0_STACK = 80,
    LIFTED_F475AD0_STACK = 68,
    LIFTED_F475B20_STACK = 104,
    LIFTED_F475B80_STACK = 104,
    LIFTED_F475BE0_STACK = 92,
    LIFTED_F475C80_STACK = 84,
    LIFTED_F475CD0_STACK = 84,
    LIFTED_F475D20_STACK = 88,
    LIFTED_F475D70_STACK = 68,
    LIFTED_F475D90_STACK = 68,
    LIFTED_F475DA0_STACK = 80,
    LIFTED_F475DF0_STACK = 68,
    LIFTED_F475E10_STACK = 72,
    LIFTED_F475E50_STACK = 100,
    LIFTED_F476010_STACK = 72,
    LIFTED_F476090_STACK = 76,
    LIFTED_F4760C0_STACK = 80,
    LIFTED_F4760F0_STACK = 80,
    LIFTED_F476120_STACK = 72,
    LIFTED_F476140_STACK = 72,
    LIFTED_F4761D0_STACK = 96,
    LIFTED_F476260_STACK = 80,
    LIFTED_F476280_STACK = 84,
    LIFTED_F4762E0_STACK = 80,
    LIFTED_F476320_STACK = 80,
    LIFTED_F476400_STACK = 80,
    LIFTED_F476440_STACK = 80,
    LIFTED_F476480_STACK = 72,
    LIFTED_F4764A0_STACK = 76,
    LIFTED_F4764D0_STACK = 76,
    LIFTED_F476500_STACK = 76,
    LIFTED_F476530_STACK = 84,
    LIFTED_F476590_STACK = 80,
    LIFTED_F4765B0_STACK = 120,
    LIFTED_F4766F0_STACK = 76,
    LIFTED_F476720_STACK = 96,
    LIFTED_F476810_STACK = 108,
    LIFTED_F4768E0_STACK = 72,
    LIFTED_F476A00_STACK = 72,
    LIFTED_F476D20_STACK = 68,
    LIFTED_F476FB0_STACK = 84,
    LIFTED_F476FE0_STACK = 84,
    LIFTED_F477010_STACK = 84,
    LIFTED_F477040_STACK = 84,
    LIFTED_F477070_STACK = 84,
    LIFTED_F4770A0_STACK = 84,
    LIFTED_F4770D0_STACK = 84,
    LIFTED_F477100_STACK = 84,
    LIFTED_F477130_STACK = 84,
    LIFTED_F477160_STACK = 84,
    LIFTED_F4772F0_STACK = 72,
    LIFTED_F477610_STACK = 96,
    LIFTED_F477AF0_STACK = 72,
    LIFTED_F477C30_STACK = 108,
    LIFTED_F477D70_STACK = 104,
    LIFTED_F477E10_STACK = 64,
    LIFTED_F477E30_STACK = 84,
    LIFTED_F477ED0_STACK = 88,
    LIFTED_F478460_STACK = 68,
    LIFTED_F478480_STACK = 80,
    LIFTED_F4784D0_STACK = 88,
    LIFTED_F478520_STACK = 88,
    LIFTED_F478570_STACK = 92,
    LIFTED_F4785C0_STACK = 92,
    LIFTED_F478610_STACK = 92,
    LIFTED_F478660_STACK = 92,
    LIFTED_F4786B0_STACK = 92,
    LIFTED_F478700_STACK = 92,
    LIFTED_F478750_STACK = 92,
    LIFTED_F4787A0_STACK = 92,
    LIFTED_F478B40_STACK = 76,
    LIFTED_F478BD0_STACK = 72,
    LIFTED_F478C90_STACK = 92,
    LIFTED_F478D10_STACK = 100,
    LIFTED_F478D80_STACK = 76,
    LIFTED_F478DA0_STACK = 72,
    LIFTED_F478EB0_STACK = 68,
    LIFTED_F478ED0_STACK = 72,
    LIFTED_F478F10_STACK = 72,
    LIFTED_F4792D0_STACK = 124
};

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

/* Original 0x457330. */
uint32_t lifted_f457330(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x45ad20. */
uint32_t lifted_f45ad20(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x45c760. */
uint32_t lifted_f45c760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c7e0. */
uint32_t lifted_f45c7e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c830. */
uint32_t lifted_f45c830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c8b0. */
uint32_t lifted_f45c8b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c8e0. */
uint32_t lifted_f45c8e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c940. */
uint32_t lifted_f45c940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45cc40. */
uint32_t lifted_f45cc40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45cd00. */
uint32_t lifted_f45cd00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45cdc0. */
uint32_t lifted_f45cdc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45cdd0. */
uint32_t lifted_f45cdd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ce50. */
uint32_t lifted_f45ce50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ceb0. */
uint32_t lifted_f45ceb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45cf30. */
uint32_t lifted_f45cf30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45cf70. */
uint32_t lifted_f45cf70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d0c0. */
uint32_t lifted_f45d0c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d100. */
uint32_t lifted_f45d100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d140. */
uint32_t lifted_f45d140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d160. */
uint32_t lifted_f45d160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d1a0. */
uint32_t lifted_f45d1a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d420. */
uint32_t lifted_f45d420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d690. */
uint32_t lifted_f45d690(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d740. */
uint32_t lifted_f45d740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d7b0. */
uint32_t lifted_f45d7b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d820. */
uint32_t lifted_f45d820(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e260. */
uint32_t lifted_f45e260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e3c0. */
uint32_t lifted_f45e3c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e400. */
uint32_t lifted_f45e400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e440. */
uint32_t lifted_f45e440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e490. */
uint32_t lifted_f45e490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e530. */
uint32_t lifted_f45e530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e590. */
uint32_t lifted_f45e590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e630. */
uint32_t lifted_f45e630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e670. */
uint32_t lifted_f45e670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e690. */
uint32_t lifted_f45e690(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e6b0. */
uint32_t lifted_f45e6b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e720. */
uint32_t lifted_f45e720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e740. */
uint32_t lifted_f45e740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e750. */
uint32_t lifted_f45e750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e7b0. */
uint32_t lifted_f45e7b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e810. */
uint32_t lifted_f45e810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e820. */
uint32_t lifted_f45e820(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e830. */
uint32_t lifted_f45e830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e850. */
uint32_t lifted_f45e850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e8d0. */
uint32_t lifted_f45e8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e8f0. */
uint32_t lifted_f45e8f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e910. */
uint32_t lifted_f45e910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e950. */
uint32_t lifted_f45e950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e990. */
uint32_t lifted_f45e990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e9e0. */
uint32_t lifted_f45e9e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ea60. */
uint32_t lifted_f45ea60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ea80. */
uint32_t lifted_f45ea80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45eac0. */
uint32_t lifted_f45eac0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ec00. */
uint32_t lifted_f45ec00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ecd0. */
uint32_t lifted_f45ecd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ed10. */
uint32_t lifted_f45ed10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ed40. */
uint32_t lifted_f45ed40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ee30. */
uint32_t lifted_f45ee30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f0a0. */
uint32_t lifted_f45f0a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f0c0. */
uint32_t lifted_f45f0c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f140. */
uint32_t lifted_f45f140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f1f0. */
uint32_t lifted_f45f1f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f590. */
uint32_t lifted_f45f590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f770. */
uint32_t lifted_f45f770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45fa70. */
uint32_t lifted_f45fa70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45fab0. */
uint32_t lifted_f45fab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45fb00. */
uint32_t lifted_f45fb00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45fc80. */
uint32_t lifted_f45fc80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45fe10. */
uint32_t lifted_f45fe10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45fee0. */
uint32_t lifted_f45fee0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4601c0. */
uint32_t lifted_f4601c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460840. */
uint32_t lifted_f460840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460a40. */
uint32_t lifted_f460a40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460ad0. */
uint32_t lifted_f460ad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460b60. */
uint32_t lifted_f460b60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460df0. */
uint32_t lifted_f460df0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460ed0. */
uint32_t lifted_f460ed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460fa0. */
uint32_t lifted_f460fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x461090. */
uint32_t lifted_f461090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4657f0. */
uint32_t lifted_f4657f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x465a70. */
uint32_t lifted_f465a70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x466d60. */
uint32_t lifted_f466d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46b810. */
uint32_t lifted_f46b810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46c500. */
uint32_t lifted_f46c500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46c9d0. */
uint32_t lifted_f46c9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46e8b0. */
uint32_t lifted_f46e8b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x470960. */
uint32_t lifted_f470960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x470b20. */
uint32_t lifted_f470b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x470d20. */
uint32_t lifted_f470d20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4710d0. */
uint32_t lifted_f4710d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471100. */
uint32_t lifted_f471100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4711a0. */
uint32_t lifted_f4711a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471340. */
uint32_t lifted_f471340(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4717f0. */
uint32_t lifted_f4717f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471820. */
uint32_t lifted_f471820(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4718a0. */
uint32_t lifted_f4718a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471920. */
uint32_t lifted_f471920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471940. */
uint32_t lifted_f471940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471960. */
uint32_t lifted_f471960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471980. */
uint32_t lifted_f471980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4719a0. */
uint32_t lifted_f4719a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4719e0. */
uint32_t lifted_f4719e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4719f0. */
uint32_t lifted_f4719f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471a20. */
uint32_t lifted_f471a20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471a40. */
uint32_t lifted_f471a40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471a50. */
uint32_t lifted_f471a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471a60. */
uint32_t lifted_f471a60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471a70. */
uint32_t lifted_f471a70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471a80. */
uint32_t lifted_f471a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471a90. */
uint32_t lifted_f471a90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471aa0. */
uint32_t lifted_f471aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x471b00. */
uint32_t lifted_f471b00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b10. */
uint32_t lifted_f471b10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b20. */
uint32_t lifted_f471b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x471b80. */
uint32_t lifted_f471b80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b90. */
uint32_t lifted_f471b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471ba0. */
uint32_t lifted_f471ba0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471bb0. */
uint32_t lifted_f471bb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471bf0. */
uint32_t lifted_f471bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471c40. */
uint32_t lifted_f471c40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471c90. */
uint32_t lifted_f471c90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471cd0. */
uint32_t lifted_f471cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471d10. */
uint32_t lifted_f471d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471d50. */
uint32_t lifted_f471d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471d90. */
uint32_t lifted_f471d90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471dd0. */
uint32_t lifted_f471dd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471e10. */
uint32_t lifted_f471e10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471e60. */
uint32_t lifted_f471e60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471e80. */
uint32_t lifted_f471e80(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f472350(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f472470(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4724f0. */
uint32_t lifted_f4724f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472570. */
uint32_t lifted_f472570(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4725f0. */
uint32_t lifted_f4725f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472620. */
uint32_t lifted_f472620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472ad0. */
uint32_t lifted_f472ad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472bd0. */
uint32_t lifted_f472bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472c10. */
uint32_t lifted_f472c10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472d00. */
uint32_t lifted_f472d00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472db0. */
uint32_t lifted_f472db0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4731a0. */
uint32_t lifted_f4731a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473490. */
uint32_t lifted_f473490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4735e0. */
uint32_t lifted_f4735e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473610. */
uint32_t lifted_f473610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473630. */
uint32_t lifted_f473630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4737d0. */
uint32_t lifted_f4737d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473960. */
uint32_t lifted_f473960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473af0. */
uint32_t lifted_f473af0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473cd0. */
uint32_t lifted_f473cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x474540. */
uint32_t lifted_f474540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4754e0. */
uint32_t lifted_f4754e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475510. */
uint32_t lifted_f475510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475700. */
uint32_t lifted_f475700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475790. */
uint32_t lifted_f475790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4757e0. */
uint32_t lifted_f4757e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475a20. */
uint32_t lifted_f475a20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475a80. */
uint32_t lifted_f475a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475ab0. */
uint32_t lifted_f475ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475ad0. */
uint32_t lifted_f475ad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x475c80. */
uint32_t lifted_f475c80(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f475d90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475da0. */
uint32_t lifted_f475da0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475df0. */
uint32_t lifted_f475df0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475e10. */
uint32_t lifted_f475e10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475e50. */
uint32_t lifted_f475e50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476010. */
uint32_t lifted_f476010(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476090. */
uint32_t lifted_f476090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4760c0. */
uint32_t lifted_f4760c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4760f0. */
uint32_t lifted_f4760f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476120. */
uint32_t lifted_f476120(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476140. */
uint32_t lifted_f476140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4761d0. */
uint32_t lifted_f4761d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476260. */
uint32_t lifted_f476260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476280. */
uint32_t lifted_f476280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4762e0. */
uint32_t lifted_f4762e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4764a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4764d0. */
uint32_t lifted_f4764d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476500. */
uint32_t lifted_f476500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476530. */
uint32_t lifted_f476530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476590. */
uint32_t lifted_f476590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4765b0. */
uint32_t lifted_f4765b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4766f0. */
uint32_t lifted_f4766f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476720. */
uint32_t lifted_f476720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476810. */
uint32_t lifted_f476810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4768e0. */
uint32_t lifted_f4768e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476a00. */
uint32_t lifted_f476a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476d20. */
uint32_t lifted_f476d20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476fb0. */
uint32_t lifted_f476fb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476fe0. */
uint32_t lifted_f476fe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477010. */
uint32_t lifted_f477010(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4772f0. */
uint32_t lifted_f4772f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477610. */
uint32_t lifted_f477610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477af0. */
uint32_t lifted_f477af0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477c30. */
uint32_t lifted_f477c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477d70. */
uint32_t lifted_f477d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477e10. */
uint32_t lifted_f477e10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477e30. */
uint32_t lifted_f477e30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477ed0. */
uint32_t lifted_f477ed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478460. */
uint32_t lifted_f478460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478480. */
uint32_t lifted_f478480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4784d0. */
uint32_t lifted_f4784d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f478b40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478bd0. */
uint32_t lifted_f478bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478c90. */
uint32_t lifted_f478c90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478d10. */
uint32_t lifted_f478d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478d80. */
uint32_t lifted_f478d80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478da0. */
uint32_t lifted_f478da0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478eb0. */
uint32_t lifted_f478eb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478ed0. */
uint32_t lifted_f478ed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478f10. */
uint32_t lifted_f478f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4792d0. */
uint32_t lifted_f4792d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
