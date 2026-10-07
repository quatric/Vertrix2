#ifndef VERTRIX_LIFTED_WHOLE_2_H
#define VERTRIX_LIFTED_WHOLE_2_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F45C760_STACK = 88,
    LIFTED_F45C7E0_STACK = 84,
    LIFTED_F45C830_STACK = 120,
    LIFTED_F45C8B0_STACK = 72,
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
    LIFTED_F45E810_STACK = 68,
    LIFTED_F45E820_STACK = 68,
    LIFTED_F45E830_STACK = 76,
    LIFTED_F45E8D0_STACK = 72,
    LIFTED_F45E8F0_STACK = 76,
    LIFTED_F45E910_STACK = 84,
    LIFTED_F45E950_STACK = 76,
    LIFTED_F45E990_STACK = 84,
    LIFTED_F45EA60_STACK = 72,
    LIFTED_F45EA80_STACK = 80,
    LIFTED_F45EAC0_STACK = 348,
    LIFTED_F45EC00_STACK = 120,
    LIFTED_F45ECD0_STACK = 88,
    LIFTED_F45ED10_STACK = 92,
    LIFTED_F45ED40_STACK = 72,
    LIFTED_F45EE30_STACK = 128,
    LIFTED_F45F0A0_STACK = 84,
    LIFTED_F45F1F0_STACK = 108,
    LIFTED_F45F590_STACK = 84,
    LIFTED_F45F770_STACK = 276,
    LIFTED_F45FA70_STACK = 84,
    LIFTED_F45FAB0_STACK = 92,
    LIFTED_F45FE10_STACK = 140,
    LIFTED_F45FEE0_STACK = 140,
    LIFTED_F4601C0_STACK = 172,
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
    LIFTED_F46C500_STACK = 152,
    LIFTED_F46C9D0_STACK = 2064,
    LIFTED_F46E8B0_STACK = 180,
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
    LIFTED_F472620_STACK = 136,
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
    LIFTED_F475510_STACK = 112,
    LIFTED_F475700_STACK = 136,
    LIFTED_F475790_STACK = 64,
    LIFTED_F475A20_STACK = 96,
    LIFTED_F475A80_STACK = 96,
    LIFTED_F475AB0_STACK = 80,
    LIFTED_F475AD0_STACK = 68,
    LIFTED_F475B20_STACK = 104,
    LIFTED_F475BE0_STACK = 92,
    LIFTED_F475CD0_STACK = 84,
    LIFTED_F475D20_STACK = 88,
    LIFTED_F475D70_STACK = 68,
    LIFTED_F475D90_STACK = 68,
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
    LIFTED_F476320_STACK = 80,
    LIFTED_F476400_STACK = 80,
    LIFTED_F476440_STACK = 80,
    LIFTED_F476480_STACK = 72,
    LIFTED_F4764A0_STACK = 76,
    LIFTED_F4764D0_STACK = 76,
    LIFTED_F476500_STACK = 76,
    LIFTED_F476590_STACK = 80,
    LIFTED_F4765B0_STACK = 120,
    LIFTED_F4766F0_STACK = 76,
    LIFTED_F476720_STACK = 96,
    LIFTED_F476810_STACK = 108,
    LIFTED_F476A00_STACK = 72,
    LIFTED_F476D70_STACK = 236,
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
    LIFTED_F477C90_STACK = 136,
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
    LIFTED_F478D10_STACK = 100,
    LIFTED_F478D80_STACK = 76,
    LIFTED_F478DA0_STACK = 72,
    LIFTED_F478EB0_STACK = 68,
    LIFTED_F478F10_STACK = 72,
    LIFTED_F479A40_STACK = 72,
    LIFTED_F479D70_STACK = 80,
    LIFTED_F479DF0_STACK = 108,
    LIFTED_F47CD60_STACK = 88,
    LIFTED_F47E780_STACK = 92,
    LIFTED_F47EB60_STACK = 96,
    LIFTED_F47F190_STACK = 68,
    LIFTED_F47F260_STACK = 68,
    LIFTED_F47F750_STACK = 80,
    LIFTED_F47F770_STACK = 76,
    LIFTED_F47F9B0_STACK = 84,
    LIFTED_F47F9E0_STACK = 88,
    LIFTED_F47FA20_STACK = 76,
    LIFTED_F47FCE0_STACK = 68,
    LIFTED_F480890_STACK = 80,
    LIFTED_F480B20_STACK = 96,
    LIFTED_F481B30_STACK = 136,
    LIFTED_F481BC0_STACK = 76,
    LIFTED_F481F30_STACK = 128,
    LIFTED_F481FB0_STACK = 156,
    LIFTED_F482060_STACK = 72,
    LIFTED_F4823B0_STACK = 104,
    LIFTED_F482540_STACK = 68,
    LIFTED_F4826C0_STACK = 84,
    LIFTED_F482720_STACK = 76,
    LIFTED_F482740_STACK = 68,
    LIFTED_F482750_STACK = 72,
    LIFTED_F482770_STACK = 72,
    LIFTED_F4827C0_STACK = 100,
    LIFTED_F482860_STACK = 80,
    LIFTED_F4828A0_STACK = 84,
    LIFTED_F4828F0_STACK = 80,
    LIFTED_F482930_STACK = 100,
    LIFTED_F482A40_STACK = 68,
    LIFTED_F482A60_STACK = 76,
    LIFTED_F482B30_STACK = 68,
    LIFTED_F482B40_STACK = 84,
    LIFTED_F482BB0_STACK = 76,
    LIFTED_F483060_STACK = 88,
    LIFTED_F4830F0_STACK = 76,
    LIFTED_F483750_STACK = 76,
    LIFTED_F4844B0_STACK = 100,
    LIFTED_F484530_STACK = 72,
    LIFTED_F484550_STACK = 116,
    LIFTED_F4845D0_STACK = 68,
    LIFTED_F484A60_STACK = 68,
    LIFTED_F4856A0_STACK = 88,
    LIFTED_F487280_STACK = 76,
    LIFTED_F4872B0_STACK = 68,
    LIFTED_F4872C0_STACK = 80,
    LIFTED_F487640_STACK = 72,
    LIFTED_F487710_STACK = 80,
    LIFTED_F487790_STACK = 92,
    LIFTED_F4877D0_STACK = 72,
    LIFTED_F487870_STACK = 68,
    LIFTED_F487920_STACK = 68,
    LIFTED_F4879F0_STACK = 80,
    LIFTED_F487A10_STACK = 72,
    LIFTED_F487B00_STACK = 68,
    LIFTED_F487FD0_STACK = 92,
    LIFTED_F488050_STACK = 88,
    LIFTED_F488560_STACK = 88,
    LIFTED_F4885C0_STACK = 84,
    LIFTED_F4886F0_STACK = 76,
    LIFTED_F488940_STACK = 68,
    LIFTED_F488960_STACK = 84,
    LIFTED_F488B90_STACK = 160,
    LIFTED_F489B20_STACK = 76,
    LIFTED_F489F90_STACK = 68,
    LIFTED_F489FA0_STACK = 160,
    LIFTED_F48A2D0_STACK = 68,
    LIFTED_F48A2F0_STACK = 68,
    LIFTED_F48A300_STACK = 72,
    LIFTED_F48A310_STACK = 104,
    LIFTED_F48A380_STACK = 88,
    LIFTED_F48A420_STACK = 100,
    LIFTED_F48A670_STACK = 140,
    LIFTED_F48A8A0_STACK = 72,
    LIFTED_F48A910_STACK = 68,
    LIFTED_F48AA90_STACK = 72,
    LIFTED_F48AAD0_STACK = 72,
    LIFTED_F48AAF0_STACK = 68,
    LIFTED_F48B770_STACK = 88,
    LIFTED_F48B7E0_STACK = 292,
    LIFTED_F48BDF0_STACK = 128,
    LIFTED_F48C260_STACK = 76,
    LIFTED_F48C280_STACK = 76,
    LIFTED_F48C2B0_STACK = 76,
    LIFTED_F48C2E0_STACK = 76,
    LIFTED_F48C310_STACK = 76,
    LIFTED_F48C330_STACK = 76,
    LIFTED_F48C390_STACK = 80,
    LIFTED_F48C3B0_STACK = 80,
    LIFTED_F48C3D0_STACK = 100,
    LIFTED_F48C460_STACK = 80,
    LIFTED_F48C480_STACK = 76,
    LIFTED_F48C610_STACK = 76,
    LIFTED_F48C9B0_STACK = 72,
    LIFTED_F48C9D0_STACK = 72,
    LIFTED_F48C9F0_STACK = 80,
    LIFTED_F48CC30_STACK = 740,
    LIFTED_F48D330_STACK = 72,
    LIFTED_F48D500_STACK = 72,
    LIFTED_F48D520_STACK = 68,
    LIFTED_F48D530_STACK = 172,
    LIFTED_F48D600_STACK = 80,
    LIFTED_F48D620_STACK = 72,
    LIFTED_F48D6B0_STACK = 68,
    LIFTED_F4AC130_STACK = 136,
    LIFTED_F4AC250_STACK = 104,
    LIFTED_F4AC2B0_STACK = 104,
    LIFTED_F4AC370_STACK = 68,
    LIFTED_F4AC390_STACK = 68,
    LIFTED_F4AC3B0_STACK = 72,
    LIFTED_F4AC420_STACK = 80,
    LIFTED_F4AC470_STACK = 68,
    LIFTED_F4AC4A0_STACK = 80,
    LIFTED_F4AC500_STACK = 68,
    LIFTED_F4AC520_STACK = 68,
    LIFTED_F4AC540_STACK = 72,
    LIFTED_F4AC560_STACK = 84,
    LIFTED_F4AC590_STACK = 68,
    LIFTED_F4AC5B0_STACK = 80,
    LIFTED_F4AC600_STACK = 68,
    LIFTED_F4AC620_STACK = 68,
    LIFTED_F4AC640_STACK = 72,
    LIFTED_F4AC6B0_STACK = 80,
    LIFTED_F4AC720_STACK = 72,
    LIFTED_F4AC760_STACK = 72,
    LIFTED_F4AC780_STACK = 72,
    LIFTED_F4AC7B0_STACK = 68,
    LIFTED_F4AC7E0_STACK = 84,
    LIFTED_F4AC810_STACK = 84,
    LIFTED_F4AC840_STACK = 68,
    LIFTED_F4AC8A0_STACK = 76,
    LIFTED_F4AC8D0_STACK = 76,
    LIFTED_F4AC920_STACK = 68,
    LIFTED_F4AC940_STACK = 68,
    LIFTED_F4AC980_STACK = 64,
    LIFTED_F4ACA00_STACK = 92,
    LIFTED_F4ACA60_STACK = 80,
    LIFTED_F4ACAB0_STACK = 80,
    LIFTED_F4ACB00_STACK = 80,
    LIFTED_F4ACC10_STACK = 80,
    LIFTED_F4ACC70_STACK = 76,
    LIFTED_F4ACE40_STACK = 84,
    LIFTED_F4AD530_STACK = 80,
    LIFTED_F4AD580_STACK = 80,
    LIFTED_F4AD5E0_STACK = 80,
    LIFTED_F4AD630_STACK = 80,
    LIFTED_F4AD6E0_STACK = 76,
    LIFTED_F4AD720_STACK = 84,
    LIFTED_F4AD750_STACK = 76,
    LIFTED_F4AD790_STACK = 76,
    LIFTED_F4ADE60_STACK = 80,
    LIFTED_F4ADF20_STACK = 64,
    LIFTED_F4ADFE0_STACK = 68,
    LIFTED_F4AE010_STACK = 120,
    LIFTED_F4AE110_STACK = 64,
    LIFTED_F4AE140_STACK = 68,
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
    LIFTED_F4B5420_STACK = 156
};

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

/* Original 0x45e810. */
uint32_t lifted_f45e810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e820. */
uint32_t lifted_f45e820(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e830. */
uint32_t lifted_f45e830(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x45fe10. */
uint32_t lifted_f45fe10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45fee0. */
uint32_t lifted_f45fee0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4601c0. */
uint32_t lifted_f4601c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x46c500. */
uint32_t lifted_f46c500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46c9d0. */
uint32_t lifted_f46c9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46e8b0. */
uint32_t lifted_f46e8b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x472620. */
uint32_t lifted_f472620(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x475510. */
uint32_t lifted_f475510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475700. */
uint32_t lifted_f475700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475790. */
uint32_t lifted_f475790(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x475be0. */
uint32_t lifted_f475be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x476a00. */
uint32_t lifted_f476a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476d70. */
uint32_t lifted_f476d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x477c90. */
uint32_t lifted_f477c90(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x478f10. */
uint32_t lifted_f478f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479a40. */
uint32_t lifted_f479a40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479d70. */
uint32_t lifted_f479d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479df0. */
uint32_t lifted_f479df0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47cd60. */
uint32_t lifted_f47cd60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e780. */
uint32_t lifted_f47e780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47eb60. */
uint32_t lifted_f47eb60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f190. */
uint32_t lifted_f47f190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f260. */
uint32_t lifted_f47f260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f750. */
uint32_t lifted_f47f750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f770. */
uint32_t lifted_f47f770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f9b0. */
uint32_t lifted_f47f9b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f9e0. */
uint32_t lifted_f47f9e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47fa20. */
uint32_t lifted_f47fa20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47fce0. */
uint32_t lifted_f47fce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480890. */
uint32_t lifted_f480890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480b20. */
uint32_t lifted_f480b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481b30. */
uint32_t lifted_f481b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481bc0. */
uint32_t lifted_f481bc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481f30. */
uint32_t lifted_f481f30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481fb0. */
uint32_t lifted_f481fb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482060. */
uint32_t lifted_f482060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4823b0. */
uint32_t lifted_f4823b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482540. */
uint32_t lifted_f482540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4826c0. */
uint32_t lifted_f4826c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482720. */
uint32_t lifted_f482720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482740. */
uint32_t lifted_f482740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482750. */
uint32_t lifted_f482750(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x482a40. */
uint32_t lifted_f482a40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482a60. */
uint32_t lifted_f482a60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482b30. */
uint32_t lifted_f482b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482b40. */
uint32_t lifted_f482b40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482bb0. */
uint32_t lifted_f482bb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x483060. */
uint32_t lifted_f483060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4830f0. */
uint32_t lifted_f4830f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x483750. */
uint32_t lifted_f483750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4844b0. */
uint32_t lifted_f4844b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484530. */
uint32_t lifted_f484530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484550. */
uint32_t lifted_f484550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4845d0. */
uint32_t lifted_f4845d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484a60. */
uint32_t lifted_f484a60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4856a0. */
uint32_t lifted_f4856a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487280. */
uint32_t lifted_f487280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4872b0. */
uint32_t lifted_f4872b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4872c0. */
uint32_t lifted_f4872c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487640. */
uint32_t lifted_f487640(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487710. */
uint32_t lifted_f487710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487790. */
uint32_t lifted_f487790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4877d0. */
uint32_t lifted_f4877d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487870. */
uint32_t lifted_f487870(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487920. */
uint32_t lifted_f487920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4879f0. */
uint32_t lifted_f4879f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487a10. */
uint32_t lifted_f487a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487b00. */
uint32_t lifted_f487b00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487fd0. */
uint32_t lifted_f487fd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488050. */
uint32_t lifted_f488050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488560. */
uint32_t lifted_f488560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4885c0. */
uint32_t lifted_f4885c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4886f0. */
uint32_t lifted_f4886f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488940. */
uint32_t lifted_f488940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488960. */
uint32_t lifted_f488960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488b90. */
uint32_t lifted_f488b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489b20. */
uint32_t lifted_f489b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489f90. */
uint32_t lifted_f489f90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489fa0. */
uint32_t lifted_f489fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a2d0. */
uint32_t lifted_f48a2d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a2f0. */
uint32_t lifted_f48a2f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a300. */
uint32_t lifted_f48a300(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a310. */
uint32_t lifted_f48a310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a380. */
uint32_t lifted_f48a380(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a420. */
uint32_t lifted_f48a420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a670. */
uint32_t lifted_f48a670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a8a0. */
uint32_t lifted_f48a8a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a910. */
uint32_t lifted_f48a910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48aa90. */
uint32_t lifted_f48aa90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48aad0. */
uint32_t lifted_f48aad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48aaf0. */
uint32_t lifted_f48aaf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48b770. */
uint32_t lifted_f48b770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48b7e0. */
uint32_t lifted_f48b7e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48bdf0. */
uint32_t lifted_f48bdf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c260. */
uint32_t lifted_f48c260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c280. */
uint32_t lifted_f48c280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c2b0. */
uint32_t lifted_f48c2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c2e0. */
uint32_t lifted_f48c2e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c310. */
uint32_t lifted_f48c310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c330. */
uint32_t lifted_f48c330(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x48c9b0. */
uint32_t lifted_f48c9b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c9d0. */
uint32_t lifted_f48c9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c9f0. */
uint32_t lifted_f48c9f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48cc30. */
uint32_t lifted_f48cc30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d330. */
uint32_t lifted_f48d330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d500. */
uint32_t lifted_f48d500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d520. */
uint32_t lifted_f48d520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d530. */
uint32_t lifted_f48d530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d600. */
uint32_t lifted_f48d600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d620. */
uint32_t lifted_f48d620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d6b0. */
uint32_t lifted_f48d6b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac130. */
uint32_t lifted_f4ac130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac250. */
uint32_t lifted_f4ac250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac2b0. */
uint32_t lifted_f4ac2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac370. */
uint32_t lifted_f4ac370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac390. */
uint32_t lifted_f4ac390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac3b0. */
uint32_t lifted_f4ac3b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac420. */
uint32_t lifted_f4ac420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac470. */
uint32_t lifted_f4ac470(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac4a0. */
uint32_t lifted_f4ac4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac500. */
uint32_t lifted_f4ac500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac520. */
uint32_t lifted_f4ac520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac540. */
uint32_t lifted_f4ac540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac560. */
uint32_t lifted_f4ac560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac590. */
uint32_t lifted_f4ac590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac5b0. */
uint32_t lifted_f4ac5b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac600. */
uint32_t lifted_f4ac600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac620. */
uint32_t lifted_f4ac620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac640. */
uint32_t lifted_f4ac640(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac6b0. */
uint32_t lifted_f4ac6b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac720. */
uint32_t lifted_f4ac720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac760. */
uint32_t lifted_f4ac760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac780. */
uint32_t lifted_f4ac780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac7b0. */
uint32_t lifted_f4ac7b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ac8a0. */
uint32_t lifted_f4ac8a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac8d0. */
uint32_t lifted_f4ac8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac920. */
uint32_t lifted_f4ac920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac940. */
uint32_t lifted_f4ac940(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ace40. */
uint32_t lifted_f4ace40(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ade60. */
uint32_t lifted_f4ade60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4adf20. */
uint32_t lifted_f4adf20(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
#endif
