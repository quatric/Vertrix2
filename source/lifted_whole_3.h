#ifndef VERTRIX_LIFTED_WHOLE_3_H
#define VERTRIX_LIFTED_WHOLE_3_H
#include <stdint.h>

#include "actor_build.h"

enum
{
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
    LIFTED_F4772F0_STACK = 72,
    LIFTED_F477320_STACK = 104,
    LIFTED_F477610_STACK = 96,
    LIFTED_F4777C0_STACK = 88,
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
    LIFTED_F478D10_STACK = 100,
    LIFTED_F478D80_STACK = 76,
    LIFTED_F478DA0_STACK = 72,
    LIFTED_F478EB0_STACK = 68,
    LIFTED_F478ED0_STACK = 72,
    LIFTED_F478F10_STACK = 72,
    LIFTED_F4792D0_STACK = 124,
    LIFTED_F4799F0_STACK = 76,
    LIFTED_F479A40_STACK = 72,
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
    LIFTED_F47E9B0_STACK = 132,
    LIFTED_F47EA20_STACK = 92,
    LIFTED_F47EAB0_STACK = 96,
    LIFTED_F47EB60_STACK = 96,
    LIFTED_F47ED10_STACK = 72,
    LIFTED_F47ED30_STACK = 72,
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
    LIFTED_F480890_STACK = 80,
    LIFTED_F4808F0_STACK = 104,
    LIFTED_F480940_STACK = 92,
    LIFTED_F480990_STACK = 100,
    LIFTED_F480B20_STACK = 96,
    LIFTED_F481420_STACK = 76,
    LIFTED_F481460_STACK = 72,
    LIFTED_F4817A0_STACK = 136,
    LIFTED_F481B30_STACK = 136,
    LIFTED_F481BC0_STACK = 76,
    LIFTED_F481D90_STACK = 80,
    LIFTED_F481E10_STACK = 116,
    LIFTED_F481F30_STACK = 128,
    LIFTED_F481FB0_STACK = 156,
    LIFTED_F482060_STACK = 72,
    LIFTED_F482110_STACK = 76,
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
    LIFTED_F4874F0_STACK = 104,
    LIFTED_F487640_STACK = 72,
    LIFTED_F487660_STACK = 112,
    LIFTED_F4876C0_STACK = 84,
    LIFTED_F487710_STACK = 80,
    LIFTED_F487770_STACK = 72,
    LIFTED_F487790_STACK = 92,
    LIFTED_F4877D0_STACK = 72,
    LIFTED_F4877F0_STACK = 76,
    LIFTED_F487870_STACK = 68,
    LIFTED_F487920_STACK = 68,
    LIFTED_F4879F0_STACK = 80,
    LIFTED_F487A10_STACK = 72,
    LIFTED_F487A20_STACK = 68,
    LIFTED_F487B00_STACK = 68,
    LIFTED_F487FD0_STACK = 92,
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
    LIFTED_F48AA90_STACK = 72,
    LIFTED_F48AAD0_STACK = 72,
    LIFTED_F48AAF0_STACK = 68,
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
    LIFTED_F48D500_STACK = 72,
    LIFTED_F48D520_STACK = 68,
    LIFTED_F48D530_STACK = 172,
    LIFTED_F48D600_STACK = 80,
    LIFTED_F48D620_STACK = 72,
    LIFTED_F48D630_STACK = 68,
    LIFTED_F48D650_STACK = 100,
    LIFTED_F48D6B0_STACK = 68,
    LIFTED_F48D6C0_STACK = 100,
    LIFTED_F4AC130_STACK = 136,
    LIFTED_F4AC1C0_STACK = 68,
    LIFTED_F4AC1F0_STACK = 104,
    LIFTED_F4AC250_STACK = 104,
    LIFTED_F4AC2B0_STACK = 104,
    LIFTED_F4AC310_STACK = 104,
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
    LIFTED_F4AF560_STACK = 244,
    LIFTED_F4B0B70_STACK = 136,
    LIFTED_F4B14C0_STACK = 96,
    LIFTED_F4B15E0_STACK = 96,
    LIFTED_F4B17B0_STACK = 76,
    LIFTED_F4B17E0_STACK = 108,
    LIFTED_F4B1FA0_STACK = 232,
    LIFTED_F4B2290_STACK = 68,
    LIFTED_F4B22C0_STACK = 80,
    LIFTED_F4B2300_STACK = 72,
    LIFTED_F4B2340_STACK = 76,
    LIFTED_F4B2380_STACK = 80,
    LIFTED_F4B23C0_STACK = 76,
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
    LIFTED_F4B6FA0_STACK = 68,
    LIFTED_F4B7020_STACK = 100,
    LIFTED_F4B7600_STACK = 68,
    LIFTED_F4B76D0_STACK = 92,
    LIFTED_F4B78D0_STACK = 68,
    LIFTED_F4B78E0_STACK = 172,
    LIFTED_F4B79A0_STACK = 80,
    LIFTED_F4B79C0_STACK = 72,
    LIFTED_F4B7A80_STACK = 72,
    LIFTED_F4B7B00_STACK = 100
};

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

/* Original 0x47ed10. */
uint32_t lifted_f47ed10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed30. */
uint32_t lifted_f47ed30(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x482060. */
uint32_t lifted_f482060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482110. */
uint32_t lifted_f482110(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4877f0. */
uint32_t lifted_f4877f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x487a20. */
uint32_t lifted_f487a20(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x48aa90. */
uint32_t lifted_f48aa90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48aad0. */
uint32_t lifted_f48aad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48aaf0. */
uint32_t lifted_f48aaf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ac130. */
uint32_t lifted_f4ac130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac1c0. */
uint32_t lifted_f4ac1c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4b17e0. */
uint32_t lifted_f4b17e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
#endif
