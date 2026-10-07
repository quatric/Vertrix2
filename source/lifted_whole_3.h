#ifndef VERTRIX_LIFTED_WHOLE_3_H
#define VERTRIX_LIFTED_WHOLE_3_H
#include <stdint.h>

#include "actor_build.h"

enum
{
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
    LIFTED_F472D50_STACK = 80,
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
    LIFTED_F473E60_STACK = 136,
    LIFTED_F474540_STACK = 72,
    LIFTED_F4754E0_STACK = 72,
    LIFTED_F475510_STACK = 112,
    LIFTED_F4756D0_STACK = 64,
    LIFTED_F475700_STACK = 136,
    LIFTED_F475790_STACK = 64,
    LIFTED_F4757B0_STACK = 64,
    LIFTED_F4757E0_STACK = 72,
    LIFTED_F475800_STACK = 64,
    LIFTED_F475810_STACK = 64,
    LIFTED_F475820_STACK = 64,
    LIFTED_F475830_STACK = 64,
    LIFTED_F4759D0_STACK = 64,
    LIFTED_F4759E0_STACK = 84,
    LIFTED_F475A20_STACK = 96,
    LIFTED_F475A80_STACK = 96,
    LIFTED_F475AB0_STACK = 80,
    LIFTED_F475AD0_STACK = 68,
    LIFTED_F475AF0_STACK = 64,
    LIFTED_F475B00_STACK = 64,
    LIFTED_F475B20_STACK = 104,
    LIFTED_F475B80_STACK = 104,
    LIFTED_F475BE0_STACK = 92,
    LIFTED_F475C30_STACK = 100,
    LIFTED_F475C80_STACK = 84,
    LIFTED_F475CD0_STACK = 84,
    LIFTED_F475D20_STACK = 88,
    LIFTED_F475D70_STACK = 68,
    LIFTED_F475D90_STACK = 68,
    LIFTED_F475DA0_STACK = 80,
    LIFTED_F475DD0_STACK = 64,
    LIFTED_F475DE0_STACK = 64,
    LIFTED_F475DF0_STACK = 68,
    LIFTED_F475E10_STACK = 72,
    LIFTED_F475E30_STACK = 64,
    LIFTED_F475E40_STACK = 64,
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
    LIFTED_F476650_STACK = 64,
    LIFTED_F4766F0_STACK = 76,
    LIFTED_F476720_STACK = 96,
    LIFTED_F476810_STACK = 108,
    LIFTED_F4768E0_STACK = 72,
    LIFTED_F476A00_STACK = 72,
    LIFTED_F476C80_STACK = 84,
    LIFTED_F476CC0_STACK = 104,
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
    LIFTED_F477240_STACK = 64,
    LIFTED_F4772F0_STACK = 72,
    LIFTED_F477320_STACK = 104,
    LIFTED_F477610_STACK = 96,
    LIFTED_F4777C0_STACK = 88,
    LIFTED_F477870_STACK = 64,
    LIFTED_F477910_STACK = 64,
    LIFTED_F477930_STACK = 64,
    LIFTED_F4779C0_STACK = 64,
    LIFTED_F477AF0_STACK = 72,
    LIFTED_F477C30_STACK = 108,
    LIFTED_F477D10_STACK = 104,
    LIFTED_F477D70_STACK = 104,
    LIFTED_F477E10_STACK = 64,
    LIFTED_F477E30_STACK = 84,
    LIFTED_F477ED0_STACK = 88,
    LIFTED_F477F10_STACK = 220,
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
    LIFTED_F478B70_STACK = 84,
    LIFTED_F478BD0_STACK = 72,
    LIFTED_F478C90_STACK = 92,
    LIFTED_F478CD0_STACK = 64,
    LIFTED_F478D10_STACK = 100,
    LIFTED_F478D80_STACK = 76,
    LIFTED_F478DA0_STACK = 72,
    LIFTED_F478EB0_STACK = 68,
    LIFTED_F478ED0_STACK = 72,
    LIFTED_F478F10_STACK = 72,
    LIFTED_F4792D0_STACK = 124,
    LIFTED_F4799F0_STACK = 76,
    LIFTED_F479A40_STACK = 72,
    LIFTED_F479B30_STACK = 64,
    LIFTED_F479B50_STACK = 112,
    LIFTED_F479D70_STACK = 80,
    LIFTED_F479DF0_STACK = 108,
    LIFTED_F47AB70_STACK = 100,
    LIFTED_F47BD80_STACK = 160,
    LIFTED_F47C250_STACK = 96,
    LIFTED_F47C3B0_STACK = 96,
    LIFTED_F47C930_STACK = 84,
    LIFTED_F47CB40_STACK = 88,
    LIFTED_F47CD60_STACK = 88,
    LIFTED_F47CE10_STACK = 104,
    LIFTED_F47E200_STACK = 92,
    LIFTED_F47E780_STACK = 92,
    LIFTED_F47E7D0_STACK = 160,
    LIFTED_F47E990_STACK = 64,
    LIFTED_F47E9A0_STACK = 64,
    LIFTED_F47E9B0_STACK = 132,
    LIFTED_F47EA20_STACK = 92,
    LIFTED_F47EAB0_STACK = 96,
    LIFTED_F47EB60_STACK = 96,
    LIFTED_F47ECF0_STACK = 64,
    LIFTED_F47ED10_STACK = 72,
    LIFTED_F47ED30_STACK = 72,
    LIFTED_F47ED60_STACK = 64,
    LIFTED_F47ED70_STACK = 64,
    LIFTED_F47ED80_STACK = 64,
    LIFTED_F47ED90_STACK = 64,
    LIFTED_F47EDA0_STACK = 772,
    LIFTED_F47F0F0_STACK = 112,
    LIFTED_F47F160_STACK = 68,
    LIFTED_F47F190_STACK = 68,
    LIFTED_F47F260_STACK = 68,
    LIFTED_F47F2F0_STACK = 96,
    LIFTED_F47F320_STACK = 84,
    LIFTED_F47F370_STACK = 92,
    LIFTED_F47F3D0_STACK = 100,
    LIFTED_F47F4B0_STACK = 252,
    LIFTED_F47F590_STACK = 116,
    LIFTED_F47F750_STACK = 80,
    LIFTED_F47F770_STACK = 76,
    LIFTED_F47F790_STACK = 656,
    LIFTED_F47F830_STACK = 656,
    LIFTED_F47F8E0_STACK = 64,
    LIFTED_F47F8F0_STACK = 64,
    LIFTED_F47F9B0_STACK = 84,
    LIFTED_F47F9E0_STACK = 88,
    LIFTED_F47FA20_STACK = 76,
    LIFTED_F47FA40_STACK = 116,
    LIFTED_F47FA90_STACK = 124,
    LIFTED_F47FC10_STACK = 100,
    LIFTED_F47FC50_STACK = 108,
    LIFTED_F47FCE0_STACK = 68,
    LIFTED_F47FE20_STACK = 96,
    LIFTED_F47FE50_STACK = 96,
    LIFTED_F47FE80_STACK = 96,
    LIFTED_F480030_STACK = 104,
    LIFTED_F480070_STACK = 64,
    LIFTED_F480890_STACK = 80,
    LIFTED_F4808F0_STACK = 104,
    LIFTED_F480940_STACK = 92,
    LIFTED_F480990_STACK = 100,
    LIFTED_F480B20_STACK = 96,
    LIFTED_F481420_STACK = 76,
    LIFTED_F481460_STACK = 72,
    LIFTED_F4817A0_STACK = 136,
    LIFTED_F481B20_STACK = 64,
    LIFTED_F481B30_STACK = 136,
    LIFTED_F481BC0_STACK = 76,
    LIFTED_F481D90_STACK = 80,
    LIFTED_F481E10_STACK = 116,
    LIFTED_F481F30_STACK = 128,
    LIFTED_F481FB0_STACK = 156,
    LIFTED_F482050_STACK = 64,
    LIFTED_F482060_STACK = 72,
    LIFTED_F482110_STACK = 76,
    LIFTED_F4823B0_STACK = 104,
    LIFTED_F482480_STACK = 64,
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
    LIFTED_F4829C0_STACK = 84,
    LIFTED_F482A40_STACK = 68,
    LIFTED_F482A60_STACK = 76,
    LIFTED_F482B30_STACK = 68,
    LIFTED_F482B40_STACK = 84,
    LIFTED_F482BB0_STACK = 76,
    LIFTED_F483060_STACK = 88,
    LIFTED_F4830F0_STACK = 76,
    LIFTED_F4831B0_STACK = 204,
    LIFTED_F483750_STACK = 76,
    LIFTED_F483CE0_STACK = 92,
    LIFTED_F484410_STACK = 64,
    LIFTED_F4844B0_STACK = 100,
    LIFTED_F484500_STACK = 80,
    LIFTED_F484530_STACK = 72,
    LIFTED_F484550_STACK = 116,
    LIFTED_F4845D0_STACK = 68,
    LIFTED_F4849E0_STACK = 68,
    LIFTED_F4849F0_STACK = 68,
    LIFTED_F484A60_STACK = 68,
    LIFTED_F484B30_STACK = 88,
    LIFTED_F4854A0_STACK = 120,
    LIFTED_F4856A0_STACK = 88,
    LIFTED_F485700_STACK = 476,
    LIFTED_F486D00_STACK = 132,
    LIFTED_F487020_STACK = 116,
    LIFTED_F487060_STACK = 88,
    LIFTED_F487280_STACK = 76,
    LIFTED_F4872B0_STACK = 68,
    LIFTED_F4872C0_STACK = 80,
    LIFTED_F4872F0_STACK = 64,
    LIFTED_F4874F0_STACK = 104,
    LIFTED_F487640_STACK = 72,
    LIFTED_F487660_STACK = 112,
    LIFTED_F4876C0_STACK = 84,
    LIFTED_F487710_STACK = 80,
    LIFTED_F487770_STACK = 72,
    LIFTED_F487790_STACK = 92,
    LIFTED_F4877D0_STACK = 72,
    LIFTED_F4877E0_STACK = 64,
    LIFTED_F4877F0_STACK = 76,
    LIFTED_F487850_STACK = 64,
    LIFTED_F487860_STACK = 64,
    LIFTED_F487870_STACK = 68,
    LIFTED_F487920_STACK = 68,
    LIFTED_F4879E0_STACK = 64,
    LIFTED_F4879F0_STACK = 80,
    LIFTED_F487A10_STACK = 72,
    LIFTED_F487A20_STACK = 68,
    LIFTED_F487B00_STACK = 68,
    LIFTED_F487FD0_STACK = 92,
    LIFTED_F488030_STACK = 64,
    LIFTED_F488040_STACK = 64,
    LIFTED_F488050_STACK = 88,
    LIFTED_F488510_STACK = 84,
    LIFTED_F488560_STACK = 88,
    LIFTED_F4885A0_STACK = 68,
    LIFTED_F4885C0_STACK = 84,
    LIFTED_F488620_STACK = 128,
    LIFTED_F4886F0_STACK = 76,
    LIFTED_F488850_STACK = 88,
    LIFTED_F4888C0_STACK = 100,
    LIFTED_F488940_STACK = 68,
    LIFTED_F488960_STACK = 84,
    LIFTED_F4889A0_STACK = 108,
    LIFTED_F488A20_STACK = 96,
    LIFTED_F488B90_STACK = 160,
    LIFTED_F489B20_STACK = 76,
    LIFTED_F489B40_STACK = 104,
    LIFTED_F489D00_STACK = 96,
    LIFTED_F489F90_STACK = 68,
    LIFTED_F489FA0_STACK = 160,
    LIFTED_F48A2D0_STACK = 68,
    LIFTED_F48A2E0_STACK = 64,
    LIFTED_F48A2F0_STACK = 68,
    LIFTED_F48A300_STACK = 72,
    LIFTED_F48A310_STACK = 104,
    LIFTED_F48A380_STACK = 88,
    LIFTED_F48A420_STACK = 100,
    LIFTED_F48A620_STACK = 80,
    LIFTED_F48A670_STACK = 140,
    LIFTED_F48A710_STACK = 192,
    LIFTED_F48A8A0_STACK = 72,
    LIFTED_F48A8C0_STACK = 88,
    LIFTED_F48A910_STACK = 68,
    LIFTED_F48AA70_STACK = 64,
    LIFTED_F48AA80_STACK = 64,
    LIFTED_F48AA90_STACK = 72,
    LIFTED_F48AAD0_STACK = 72,
    LIFTED_F48AAF0_STACK = 68,
    LIFTED_F48ABE0_STACK = 64,
    LIFTED_F48ABF0_STACK = 64,
    LIFTED_F48AC00_STACK = 64,
    LIFTED_F48B550_STACK = 140,
    LIFTED_F48B770_STACK = 88,
    LIFTED_F48B7E0_STACK = 292,
    LIFTED_F48BB80_STACK = 144,
    LIFTED_F48BCA0_STACK = 124,
    LIFTED_F48BDF0_STACK = 128,
    LIFTED_F48BE70_STACK = 124,
    LIFTED_F48C0F0_STACK = 140,
    LIFTED_F48C260_STACK = 76,
    LIFTED_F48C280_STACK = 76,
    LIFTED_F48C2B0_STACK = 76,
    LIFTED_F48C2E0_STACK = 76,
    LIFTED_F48C310_STACK = 76,
    LIFTED_F48C330_STACK = 76,
    LIFTED_F48C370_STACK = 64,
    LIFTED_F48C390_STACK = 80,
    LIFTED_F48C3B0_STACK = 80,
    LIFTED_F48C3D0_STACK = 100,
    LIFTED_F48C460_STACK = 80,
    LIFTED_F48C480_STACK = 76,
    LIFTED_F48C610_STACK = 76,
    LIFTED_F48C680_STACK = 96,
    LIFTED_F48C970_STACK = 120,
    LIFTED_F48C9B0_STACK = 72,
    LIFTED_F48C9D0_STACK = 72,
    LIFTED_F48C9F0_STACK = 80,
    LIFTED_F48D330_STACK = 72,
    LIFTED_F48D3E0_STACK = 68,
    LIFTED_F48D480_STACK = 64,
    LIFTED_F48D500_STACK = 72,
    LIFTED_F48D520_STACK = 68,
    LIFTED_F48D530_STACK = 172,
    LIFTED_F48D5F0_STACK = 64,
    LIFTED_F48D600_STACK = 80,
    LIFTED_F48D620_STACK = 72,
    LIFTED_F48D630_STACK = 68,
    LIFTED_F48D650_STACK = 100,
    LIFTED_F48D6B0_STACK = 68,
    LIFTED_F48D6C0_STACK = 100,
    LIFTED_F4ABD70_STACK = 64,
    LIFTED_F4AC130_STACK = 136,
    LIFTED_F4AC1C0_STACK = 68,
    LIFTED_F4AC1E0_STACK = 64,
    LIFTED_F4AC1F0_STACK = 104,
    LIFTED_F4AC250_STACK = 104,
    LIFTED_F4AC2B0_STACK = 104,
    LIFTED_F4AC310_STACK = 104,
    LIFTED_F4AC370_STACK = 68,
    LIFTED_F4AC380_STACK = 64,
    LIFTED_F4AC390_STACK = 68,
    LIFTED_F4AC3B0_STACK = 72,
    LIFTED_F4AC420_STACK = 80,
    LIFTED_F4AC470_STACK = 68,
    LIFTED_F4AC490_STACK = 64,
    LIFTED_F4AC4A0_STACK = 80,
    LIFTED_F4AC4E0_STACK = 64,
    LIFTED_F4AC4F0_STACK = 64,
    LIFTED_F4AC500_STACK = 68,
    LIFTED_F4AC510_STACK = 64,
    LIFTED_F4AC520_STACK = 68,
    LIFTED_F4AC540_STACK = 72,
    LIFTED_F4AC560_STACK = 84,
    LIFTED_F4AC590_STACK = 68,
    LIFTED_F4AC5B0_STACK = 80,
    LIFTED_F4AC600_STACK = 68,
    LIFTED_F4AC610_STACK = 64,
    LIFTED_F4AC620_STACK = 68,
    LIFTED_F4AC640_STACK = 72,
    LIFTED_F4AC6B0_STACK = 80,
    LIFTED_F4AC700_STACK = 64,
    LIFTED_F4AC710_STACK = 64,
    LIFTED_F4AC720_STACK = 72,
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
    LIFTED_F4AC8F0_STACK = 64
};

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

/* Original 0x472d50. */
uint32_t lifted_f472d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x473e60. */
uint32_t lifted_f473e60(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4756d0. */
uint32_t lifted_f4756d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475700. */
uint32_t lifted_f475700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475790. */
uint32_t lifted_f475790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4757b0. */
uint32_t lifted_f4757b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4757e0. */
uint32_t lifted_f4757e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475800. */
uint32_t lifted_f475800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475810. */
uint32_t lifted_f475810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475820. */
uint32_t lifted_f475820(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475830. */
uint32_t lifted_f475830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4759d0. */
uint32_t lifted_f4759d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4759e0. */
uint32_t lifted_f4759e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x475af0. */
uint32_t lifted_f475af0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475b00. */
uint32_t lifted_f475b00(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x475dd0. */
uint32_t lifted_f475dd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475de0. */
uint32_t lifted_f475de0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475df0. */
uint32_t lifted_f475df0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475e10. */
uint32_t lifted_f475e10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475e30. */
uint32_t lifted_f475e30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475e40. */
uint32_t lifted_f475e40(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x476650. */
uint32_t lifted_f476650(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x476c80. */
uint32_t lifted_f476c80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476cc0. */
uint32_t lifted_f476cc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x477240. */
uint32_t lifted_f477240(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4777c0. */
uint32_t lifted_f4777c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477870. */
uint32_t lifted_f477870(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477910. */
uint32_t lifted_f477910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477930. */
uint32_t lifted_f477930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4779c0. */
uint32_t lifted_f4779c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477af0. */
uint32_t lifted_f477af0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477c30. */
uint32_t lifted_f477c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477d10. */
uint32_t lifted_f477d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x477f10. */
uint32_t lifted_f477f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x478b70. */
uint32_t lifted_f478b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478bd0. */
uint32_t lifted_f478bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478c90. */
uint32_t lifted_f478c90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478cd0. */
uint32_t lifted_f478cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4799f0. */
uint32_t lifted_f4799f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479a40. */
uint32_t lifted_f479a40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479b30. */
uint32_t lifted_f479b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479b50. */
uint32_t lifted_f479b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479d70. */
uint32_t lifted_f479d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479df0. */
uint32_t lifted_f479df0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ab70. */
uint32_t lifted_f47ab70(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x47c930. */
uint32_t lifted_f47c930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47cb40. */
uint32_t lifted_f47cb40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47cd60. */
uint32_t lifted_f47cd60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ce10. */
uint32_t lifted_f47ce10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e200. */
uint32_t lifted_f47e200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e780. */
uint32_t lifted_f47e780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e7d0. */
uint32_t lifted_f47e7d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e990. */
uint32_t lifted_f47e990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e9a0. */
uint32_t lifted_f47e9a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e9b0. */
uint32_t lifted_f47e9b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ea20. */
uint32_t lifted_f47ea20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47eab0. */
uint32_t lifted_f47eab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47eb60. */
uint32_t lifted_f47eb60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ecf0. */
uint32_t lifted_f47ecf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed10. */
uint32_t lifted_f47ed10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed30. */
uint32_t lifted_f47ed30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed60. */
uint32_t lifted_f47ed60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed70. */
uint32_t lifted_f47ed70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed80. */
uint32_t lifted_f47ed80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed90. */
uint32_t lifted_f47ed90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47eda0. */
uint32_t lifted_f47eda0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f0f0. */
uint32_t lifted_f47f0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f160. */
uint32_t lifted_f47f160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f190. */
uint32_t lifted_f47f190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f260. */
uint32_t lifted_f47f260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f2f0. */
uint32_t lifted_f47f2f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f320. */
uint32_t lifted_f47f320(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f47f8e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f8f0. */
uint32_t lifted_f47f8f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x47fa40. */
uint32_t lifted_f47fa40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47fa90. */
uint32_t lifted_f47fa90(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f47fe20(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f480070(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480890. */
uint32_t lifted_f480890(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f481420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481460. */
uint32_t lifted_f481460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4817a0. */
uint32_t lifted_f4817a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481b20. */
uint32_t lifted_f481b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481b30. */
uint32_t lifted_f481b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481bc0. */
uint32_t lifted_f481bc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481d90. */
uint32_t lifted_f481d90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481e10. */
uint32_t lifted_f481e10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481f30. */
uint32_t lifted_f481f30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481fb0. */
uint32_t lifted_f481fb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482050. */
uint32_t lifted_f482050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482060. */
uint32_t lifted_f482060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482110. */
uint32_t lifted_f482110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4823b0. */
uint32_t lifted_f4823b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482480. */
uint32_t lifted_f482480(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4829c0. */
uint32_t lifted_f4829c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4831b0. */
uint32_t lifted_f4831b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x483750. */
uint32_t lifted_f483750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x483ce0. */
uint32_t lifted_f483ce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484410. */
uint32_t lifted_f484410(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f484550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4845d0. */
uint32_t lifted_f4845d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4849e0. */
uint32_t lifted_f4849e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4849f0. */
uint32_t lifted_f4849f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484a60. */
uint32_t lifted_f484a60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484b30. */
uint32_t lifted_f484b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4854a0. */
uint32_t lifted_f4854a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4856a0. */
uint32_t lifted_f4856a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f487280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4872b0. */
uint32_t lifted_f4872b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4872c0. */
uint32_t lifted_f4872c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4872f0. */
uint32_t lifted_f4872f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4874f0. */
uint32_t lifted_f4874f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487640. */
uint32_t lifted_f487640(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487660. */
uint32_t lifted_f487660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4876c0. */
uint32_t lifted_f4876c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487710. */
uint32_t lifted_f487710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487770. */
uint32_t lifted_f487770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487790. */
uint32_t lifted_f487790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4877d0. */
uint32_t lifted_f4877d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4877e0. */
uint32_t lifted_f4877e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4877f0. */
uint32_t lifted_f4877f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487850. */
uint32_t lifted_f487850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487860. */
uint32_t lifted_f487860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487870. */
uint32_t lifted_f487870(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487920. */
uint32_t lifted_f487920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4879e0. */
uint32_t lifted_f4879e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4879f0. */
uint32_t lifted_f4879f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487a10. */
uint32_t lifted_f487a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487a20. */
uint32_t lifted_f487a20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487b00. */
uint32_t lifted_f487b00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487fd0. */
uint32_t lifted_f487fd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488030. */
uint32_t lifted_f488030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488040. */
uint32_t lifted_f488040(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4885a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f488940(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f488b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489b20. */
uint32_t lifted_f489b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489b40. */
uint32_t lifted_f489b40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489d00. */
uint32_t lifted_f489d00(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x48a2e0. */
uint32_t lifted_f48a2e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x48a620. */
uint32_t lifted_f48a620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a670. */
uint32_t lifted_f48a670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a710. */
uint32_t lifted_f48a710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a8a0. */
uint32_t lifted_f48a8a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a8c0. */
uint32_t lifted_f48a8c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a910. */
uint32_t lifted_f48a910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48aa70. */
uint32_t lifted_f48aa70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48aa80. */
uint32_t lifted_f48aa80(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x48abe0. */
uint32_t lifted_f48abe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48abf0. */
uint32_t lifted_f48abf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x48c370. */
uint32_t lifted_f48c370(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f48c9b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c9d0. */
uint32_t lifted_f48c9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c9f0. */
uint32_t lifted_f48c9f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d330. */
uint32_t lifted_f48d330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d3e0. */
uint32_t lifted_f48d3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d480. */
uint32_t lifted_f48d480(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x48d5f0. */
uint32_t lifted_f48d5f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d600. */
uint32_t lifted_f48d600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d620. */
uint32_t lifted_f48d620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d630. */
uint32_t lifted_f48d630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d650. */
uint32_t lifted_f48d650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d6b0. */
uint32_t lifted_f48d6b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d6c0. */
uint32_t lifted_f48d6c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4abd70. */
uint32_t lifted_f4abd70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac130. */
uint32_t lifted_f4ac130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac1c0. */
uint32_t lifted_f4ac1c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac1e0. */
uint32_t lifted_f4ac1e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac1f0. */
uint32_t lifted_f4ac1f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac250. */
uint32_t lifted_f4ac250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac2b0. */
uint32_t lifted_f4ac2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac310. */
uint32_t lifted_f4ac310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac370. */
uint32_t lifted_f4ac370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac380. */
uint32_t lifted_f4ac380(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ac490. */
uint32_t lifted_f4ac490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac4a0. */
uint32_t lifted_f4ac4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac4e0. */
uint32_t lifted_f4ac4e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac4f0. */
uint32_t lifted_f4ac4f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac500. */
uint32_t lifted_f4ac500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac510. */
uint32_t lifted_f4ac510(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ac610. */
uint32_t lifted_f4ac610(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ac700. */
uint32_t lifted_f4ac700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac710. */
uint32_t lifted_f4ac710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac720. */
uint32_t lifted_f4ac720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

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
#endif
