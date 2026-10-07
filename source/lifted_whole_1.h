#ifndef VERTRIX_LIFTED_WHOLE_1_H
#define VERTRIX_LIFTED_WHOLE_1_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4334B0_STACK = 104,
    LIFTED_F433550_STACK = 116,
    LIFTED_F433750_STACK = 116,
    LIFTED_F433840_STACK = 272,
    LIFTED_F433E20_STACK = 216,
    LIFTED_F435E80_STACK = 100,
    LIFTED_F435F30_STACK = 100,
    LIFTED_F435FE0_STACK = 84,
    LIFTED_F436030_STACK = 88,
    LIFTED_F436070_STACK = 88,
    LIFTED_F4360B0_STACK = 84,
    LIFTED_F436100_STACK = 84,
    LIFTED_F436850_STACK = 104,
    LIFTED_F4368E0_STACK = 140,
    LIFTED_F436A10_STACK = 104,
    LIFTED_F436AA0_STACK = 100,
    LIFTED_F436FE0_STACK = 100,
    LIFTED_F437240_STACK = 100,
    LIFTED_F4372C0_STACK = 104,
    LIFTED_F4375A0_STACK = 88,
    LIFTED_F437B70_STACK = 96,
    LIFTED_F437F60_STACK = 100,
    LIFTED_F4383F0_STACK = 100,
    LIFTED_F438470_STACK = 92,
    LIFTED_F4387B0_STACK = 96,
    LIFTED_F438830_STACK = 80,
    LIFTED_F4388A0_STACK = 80,
    LIFTED_F438910_STACK = 76,
    LIFTED_F438960_STACK = 156,
    LIFTED_F438B90_STACK = 116,
    LIFTED_F438C60_STACK = 96,
    LIFTED_F438D50_STACK = 92,
    LIFTED_F438DD0_STACK = 156,
    LIFTED_F438EF0_STACK = 180,
    LIFTED_F439140_STACK = 76,
    LIFTED_F439190_STACK = 120,
    LIFTED_F439370_STACK = 92,
    LIFTED_F439510_STACK = 180,
    LIFTED_F4398C0_STACK = 112,
    LIFTED_F43A080_STACK = 68,
    LIFTED_F43A160_STACK = 80,
    LIFTED_F43A410_STACK = 112,
    LIFTED_F43A510_STACK = 68,
    LIFTED_F43A520_STACK = 84,
    LIFTED_F43A560_STACK = 72,
    LIFTED_F43A5B0_STACK = 72,
    LIFTED_F43A5F0_STACK = 112,
    LIFTED_F43AAB0_STACK = 68,
    LIFTED_F43AB30_STACK = 80,
    LIFTED_F43AB60_STACK = 76,
    LIFTED_F43AB80_STACK = 76,
    LIFTED_F43ABD0_STACK = 72,
    LIFTED_F43AC00_STACK = 104,
    LIFTED_F43ACD0_STACK = 96,
    LIFTED_F43B1A0_STACK = 80,
    LIFTED_F43B260_STACK = 172,
    LIFTED_F43B430_STACK = 160,
    LIFTED_F43B590_STACK = 80,
    LIFTED_F43B5B0_STACK = 80,
    LIFTED_F43B660_STACK = 80,
    LIFTED_F43B680_STACK = 80,
    LIFTED_F43B6A0_STACK = 76,
    LIFTED_F43B720_STACK = 100,
    LIFTED_F43B7C0_STACK = 88,
    LIFTED_F43B800_STACK = 68,
    LIFTED_F43B810_STACK = 76,
    LIFTED_F43B930_STACK = 88,
    LIFTED_F43B980_STACK = 84,
    LIFTED_F43B9C0_STACK = 96,
    LIFTED_F43BA90_STACK = 72,
    LIFTED_F43BAF0_STACK = 68,
    LIFTED_F43BB00_STACK = 92,
    LIFTED_F43BB40_STACK = 68,
    LIFTED_F43BB60_STACK = 132,
    LIFTED_F43BC90_STACK = 84,
    LIFTED_F43BCE0_STACK = 80,
    LIFTED_F43BD00_STACK = 84,
    LIFTED_F43BD80_STACK = 68,
    LIFTED_F43C0E0_STACK = 80,
    LIFTED_F43C110_STACK = 80,
    LIFTED_F43C140_STACK = 84,
    LIFTED_F43CCB0_STACK = 80,
    LIFTED_F43CCF0_STACK = 88,
    LIFTED_F43CD30_STACK = 80,
    LIFTED_F43CD60_STACK = 84,
    LIFTED_F43CDA0_STACK = 84,
    LIFTED_F43CE00_STACK = 88,
    LIFTED_F43CE30_STACK = 84,
    LIFTED_F43CE70_STACK = 84,
    LIFTED_F43CEB0_STACK = 84,
    LIFTED_F43CEF0_STACK = 84,
    LIFTED_F43CF30_STACK = 88,
    LIFTED_F43CF70_STACK = 88,
    LIFTED_F43CFB0_STACK = 84,
    LIFTED_F43CFF0_STACK = 88,
    LIFTED_F43D030_STACK = 88,
    LIFTED_F43D070_STACK = 88,
    LIFTED_F43D0B0_STACK = 88,
    LIFTED_F43D0F0_STACK = 88,
    LIFTED_F43D130_STACK = 76,
    LIFTED_F43D260_STACK = 88,
    LIFTED_F43D2B0_STACK = 80,
    LIFTED_F43D300_STACK = 68,
    LIFTED_F43D320_STACK = 72,
    LIFTED_F43D330_STACK = 80,
    LIFTED_F43D370_STACK = 80,
    LIFTED_F43D3F0_STACK = 68,
    LIFTED_F43D800_STACK = 80,
    LIFTED_F43DC80_STACK = 156,
    LIFTED_F43DEA0_STACK = 108,
    LIFTED_F43DFF0_STACK = 184,
    LIFTED_F43E260_STACK = 84,
    LIFTED_F43E4D0_STACK = 264,
    LIFTED_F43E740_STACK = 96,
    LIFTED_F43E840_STACK = 100,
    LIFTED_F43E920_STACK = 136,
    LIFTED_F43F3F0_STACK = 80,
    LIFTED_F43F420_STACK = 72,
    LIFTED_F43F460_STACK = 68,
    LIFTED_F43F480_STACK = 124,
    LIFTED_F43F550_STACK = 124,
    LIFTED_F43F630_STACK = 124,
    LIFTED_F43F710_STACK = 124,
    LIFTED_F43F7F0_STACK = 124,
    LIFTED_F43F8D0_STACK = 124,
    LIFTED_F43F9B0_STACK = 124,
    LIFTED_F43FA90_STACK = 124,
    LIFTED_F43FB70_STACK = 124,
    LIFTED_F43FC50_STACK = 520,
    LIFTED_F440490_STACK = 136,
    LIFTED_F440A20_STACK = 224,
    LIFTED_F440D50_STACK = 244,
    LIFTED_F441120_STACK = 68,
    LIFTED_F441530_STACK = 88,
    LIFTED_F441A80_STACK = 104,
    LIFTED_F441B30_STACK = 100,
    LIFTED_F442110_STACK = 72,
    LIFTED_F4429A0_STACK = 92,
    LIFTED_F442B00_STACK = 76,
    LIFTED_F443260_STACK = 84,
    LIFTED_F443320_STACK = 112,
    LIFTED_F4433C0_STACK = 112,
    LIFTED_F443460_STACK = 124,
    LIFTED_F4434E0_STACK = 96,
    LIFTED_F443550_STACK = 132,
    LIFTED_F443890_STACK = 148,
    LIFTED_F443AB0_STACK = 96,
    LIFTED_F443D50_STACK = 96,
    LIFTED_F444020_STACK = 160,
    LIFTED_F444290_STACK = 132,
    LIFTED_F4443D0_STACK = 112,
    LIFTED_F444550_STACK = 132,
    LIFTED_F444A30_STACK = 96,
    LIFTED_F445090_STACK = 136,
    LIFTED_F445130_STACK = 136,
    LIFTED_F445630_STACK = 136,
    LIFTED_F4456D0_STACK = 136,
    LIFTED_F445890_STACK = 104,
    LIFTED_F445A00_STACK = 116,
    LIFTED_F445A90_STACK = 112,
    LIFTED_F445B10_STACK = 112,
    LIFTED_F445D10_STACK = 104,
    LIFTED_F445E90_STACK = 104,
    LIFTED_F446730_STACK = 108,
    LIFTED_F4467C0_STACK = 108,
    LIFTED_F4469C0_STACK = 124,
    LIFTED_F446A80_STACK = 104,
    LIFTED_F446B10_STACK = 128,
    LIFTED_F446D70_STACK = 124,
    LIFTED_F446EC0_STACK = 128,
    LIFTED_F447140_STACK = 124,
    LIFTED_F447290_STACK = 128,
    LIFTED_F447560_STACK = 104,
    LIFTED_F447600_STACK = 140,
    LIFTED_F4476B0_STACK = 88,
    LIFTED_F447740_STACK = 96,
    LIFTED_F447830_STACK = 104,
    LIFTED_F4478F0_STACK = 144,
    LIFTED_F4479F0_STACK = 96,
    LIFTED_F447A50_STACK = 96,
    LIFTED_F447AA0_STACK = 96,
    LIFTED_F447BC0_STACK = 132,
    LIFTED_F447E80_STACK = 136,
    LIFTED_F447F40_STACK = 104,
    LIFTED_F448140_STACK = 80,
    LIFTED_F448160_STACK = 68,
    LIFTED_F448180_STACK = 112,
    LIFTED_F448610_STACK = 100,
    LIFTED_F448690_STACK = 68,
    LIFTED_F4486D0_STACK = 68,
    LIFTED_F4486F0_STACK = 84,
    LIFTED_F448740_STACK = 84,
    LIFTED_F448790_STACK = 120,
    LIFTED_F448810_STACK = 176,
    LIFTED_F448C20_STACK = 116,
    LIFTED_F448CA0_STACK = 116,
    LIFTED_F448D30_STACK = 144,
    LIFTED_F448E00_STACK = 144,
    LIFTED_F448ED0_STACK = 144,
    LIFTED_F448FB0_STACK = 144,
    LIFTED_F4492F0_STACK = 100,
    LIFTED_F449360_STACK = 76,
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
    LIFTED_F44A720_STACK = 200,
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
    LIFTED_F451490_STACK = 120,
    LIFTED_F451520_STACK = 100,
    LIFTED_F451580_STACK = 124,
    LIFTED_F451630_STACK = 100,
    LIFTED_F451690_STACK = 116,
    LIFTED_F451730_STACK = 116,
    LIFTED_F451A60_STACK = 88,
    LIFTED_F451AA0_STACK = 164,
    LIFTED_F451C00_STACK = 108,
    LIFTED_F451DD0_STACK = 92,
    LIFTED_F451E20_STACK = 144,
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
    LIFTED_F452770_STACK = 120,
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
    LIFTED_F452C80_STACK = 116
};

/* Original 0x4334b0. */
uint32_t lifted_f4334b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x433550. */
uint32_t lifted_f433550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x433750. */
uint32_t lifted_f433750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x433840. */
uint32_t lifted_f433840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x433e20. */
uint32_t lifted_f433e20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x435e80. */
uint32_t lifted_f435e80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x435f30. */
uint32_t lifted_f435f30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x435fe0. */
uint32_t lifted_f435fe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436030. */
uint32_t lifted_f436030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436070. */
uint32_t lifted_f436070(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4360b0. */
uint32_t lifted_f4360b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436100. */
uint32_t lifted_f436100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436850. */
uint32_t lifted_f436850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4368e0. */
uint32_t lifted_f4368e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436a10. */
uint32_t lifted_f436a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436aa0. */
uint32_t lifted_f436aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436fe0. */
uint32_t lifted_f436fe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x437240. */
uint32_t lifted_f437240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4372c0. */
uint32_t lifted_f4372c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4375a0. */
uint32_t lifted_f4375a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x437b70. */
uint32_t lifted_f437b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x437f60. */
uint32_t lifted_f437f60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4383f0. */
uint32_t lifted_f4383f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438470. */
uint32_t lifted_f438470(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4387b0. */
uint32_t lifted_f4387b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438830. */
uint32_t lifted_f438830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4388a0. */
uint32_t lifted_f4388a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438910. */
uint32_t lifted_f438910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438960. */
uint32_t lifted_f438960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438b90. */
uint32_t lifted_f438b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438c60. */
uint32_t lifted_f438c60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438d50. */
uint32_t lifted_f438d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438dd0. */
uint32_t lifted_f438dd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438ef0. */
uint32_t lifted_f438ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x439140. */
uint32_t lifted_f439140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x439190. */
uint32_t lifted_f439190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x439370. */
uint32_t lifted_f439370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x439510. */
uint32_t lifted_f439510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4398c0. */
uint32_t lifted_f4398c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a080. */
uint32_t lifted_f43a080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a160. */
uint32_t lifted_f43a160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a410. */
uint32_t lifted_f43a410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a510. */
uint32_t lifted_f43a510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a520. */
uint32_t lifted_f43a520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a560. */
uint32_t lifted_f43a560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a5b0. */
uint32_t lifted_f43a5b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a5f0. */
uint32_t lifted_f43a5f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43aab0. */
uint32_t lifted_f43aab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ab30. */
uint32_t lifted_f43ab30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ab60. */
uint32_t lifted_f43ab60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ab80. */
uint32_t lifted_f43ab80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43abd0. */
uint32_t lifted_f43abd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ac00. */
uint32_t lifted_f43ac00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43acd0. */
uint32_t lifted_f43acd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b1a0. */
uint32_t lifted_f43b1a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b260. */
uint32_t lifted_f43b260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b430. */
uint32_t lifted_f43b430(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b590. */
uint32_t lifted_f43b590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b5b0. */
uint32_t lifted_f43b5b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b660. */
uint32_t lifted_f43b660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b680. */
uint32_t lifted_f43b680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b6a0. */
uint32_t lifted_f43b6a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b720. */
uint32_t lifted_f43b720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b7c0. */
uint32_t lifted_f43b7c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b800. */
uint32_t lifted_f43b800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b810. */
uint32_t lifted_f43b810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b930. */
uint32_t lifted_f43b930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b980. */
uint32_t lifted_f43b980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b9c0. */
uint32_t lifted_f43b9c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ba90. */
uint32_t lifted_f43ba90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43baf0. */
uint32_t lifted_f43baf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bb00. */
uint32_t lifted_f43bb00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bb40. */
uint32_t lifted_f43bb40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bb60. */
uint32_t lifted_f43bb60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bc90. */
uint32_t lifted_f43bc90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bce0. */
uint32_t lifted_f43bce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bd00. */
uint32_t lifted_f43bd00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bd80. */
uint32_t lifted_f43bd80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43c0e0. */
uint32_t lifted_f43c0e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43c110. */
uint32_t lifted_f43c110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43c140. */
uint32_t lifted_f43c140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ccb0. */
uint32_t lifted_f43ccb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ccf0. */
uint32_t lifted_f43ccf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cd30. */
uint32_t lifted_f43cd30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cd60. */
uint32_t lifted_f43cd60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cda0. */
uint32_t lifted_f43cda0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ce00. */
uint32_t lifted_f43ce00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ce30. */
uint32_t lifted_f43ce30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ce70. */
uint32_t lifted_f43ce70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ceb0. */
uint32_t lifted_f43ceb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cef0. */
uint32_t lifted_f43cef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cf30. */
uint32_t lifted_f43cf30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cf70. */
uint32_t lifted_f43cf70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cfb0. */
uint32_t lifted_f43cfb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43cff0. */
uint32_t lifted_f43cff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d030. */
uint32_t lifted_f43d030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d070. */
uint32_t lifted_f43d070(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d0b0. */
uint32_t lifted_f43d0b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d0f0. */
uint32_t lifted_f43d0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d130. */
uint32_t lifted_f43d130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d260. */
uint32_t lifted_f43d260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d2b0. */
uint32_t lifted_f43d2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d300. */
uint32_t lifted_f43d300(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d320. */
uint32_t lifted_f43d320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d330. */
uint32_t lifted_f43d330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d370. */
uint32_t lifted_f43d370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d3f0. */
uint32_t lifted_f43d3f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d800. */
uint32_t lifted_f43d800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43dc80. */
uint32_t lifted_f43dc80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43dea0. */
uint32_t lifted_f43dea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43dff0. */
uint32_t lifted_f43dff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e260. */
uint32_t lifted_f43e260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e4d0. */
uint32_t lifted_f43e4d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e740. */
uint32_t lifted_f43e740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e840. */
uint32_t lifted_f43e840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e920. */
uint32_t lifted_f43e920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f3f0. */
uint32_t lifted_f43f3f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f420. */
uint32_t lifted_f43f420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f460. */
uint32_t lifted_f43f460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f480. */
uint32_t lifted_f43f480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f550. */
uint32_t lifted_f43f550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f630. */
uint32_t lifted_f43f630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f710. */
uint32_t lifted_f43f710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f7f0. */
uint32_t lifted_f43f7f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f8d0. */
uint32_t lifted_f43f8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f9b0. */
uint32_t lifted_f43f9b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43fa90. */
uint32_t lifted_f43fa90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43fb70. */
uint32_t lifted_f43fb70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43fc50. */
uint32_t lifted_f43fc50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x440490. */
uint32_t lifted_f440490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x440a20. */
uint32_t lifted_f440a20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x440d50. */
uint32_t lifted_f440d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441120. */
uint32_t lifted_f441120(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441530. */
uint32_t lifted_f441530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441a80. */
uint32_t lifted_f441a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441b30. */
uint32_t lifted_f441b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x442110. */
uint32_t lifted_f442110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4429a0. */
uint32_t lifted_f4429a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x442b00. */
uint32_t lifted_f442b00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443260. */
uint32_t lifted_f443260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443320. */
uint32_t lifted_f443320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4433c0. */
uint32_t lifted_f4433c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443460. */
uint32_t lifted_f443460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4434e0. */
uint32_t lifted_f4434e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443550. */
uint32_t lifted_f443550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443890. */
uint32_t lifted_f443890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443ab0. */
uint32_t lifted_f443ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443d50. */
uint32_t lifted_f443d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444020. */
uint32_t lifted_f444020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444290. */
uint32_t lifted_f444290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4443d0. */
uint32_t lifted_f4443d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444550. */
uint32_t lifted_f444550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444a30. */
uint32_t lifted_f444a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445090. */
uint32_t lifted_f445090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445130. */
uint32_t lifted_f445130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445630. */
uint32_t lifted_f445630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4456d0. */
uint32_t lifted_f4456d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445890. */
uint32_t lifted_f445890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445a00. */
uint32_t lifted_f445a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445a90. */
uint32_t lifted_f445a90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445b10. */
uint32_t lifted_f445b10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445d10. */
uint32_t lifted_f445d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445e90. */
uint32_t lifted_f445e90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446730. */
uint32_t lifted_f446730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4467c0. */
uint32_t lifted_f4467c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4469c0. */
uint32_t lifted_f4469c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446a80. */
uint32_t lifted_f446a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446b10. */
uint32_t lifted_f446b10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446d70. */
uint32_t lifted_f446d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446ec0. */
uint32_t lifted_f446ec0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447140. */
uint32_t lifted_f447140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447290. */
uint32_t lifted_f447290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447560. */
uint32_t lifted_f447560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447600. */
uint32_t lifted_f447600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4476b0. */
uint32_t lifted_f4476b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447740. */
uint32_t lifted_f447740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447830. */
uint32_t lifted_f447830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4478f0. */
uint32_t lifted_f4478f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4479f0. */
uint32_t lifted_f4479f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447a50. */
uint32_t lifted_f447a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447aa0. */
uint32_t lifted_f447aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447bc0. */
uint32_t lifted_f447bc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447e80. */
uint32_t lifted_f447e80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447f40. */
uint32_t lifted_f447f40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448140. */
uint32_t lifted_f448140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448160. */
uint32_t lifted_f448160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448180. */
uint32_t lifted_f448180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448610. */
uint32_t lifted_f448610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448690. */
uint32_t lifted_f448690(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4486d0. */
uint32_t lifted_f4486d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4486f0. */
uint32_t lifted_f4486f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448740. */
uint32_t lifted_f448740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448790. */
uint32_t lifted_f448790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448810. */
uint32_t lifted_f448810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448c20. */
uint32_t lifted_f448c20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448ca0. */
uint32_t lifted_f448ca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448d30. */
uint32_t lifted_f448d30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448e00. */
uint32_t lifted_f448e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448ed0. */
uint32_t lifted_f448ed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448fb0. */
uint32_t lifted_f448fb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4492f0. */
uint32_t lifted_f4492f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449360. */
uint32_t lifted_f449360(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

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

/* Original 0x44a720. */
uint32_t lifted_f44a720(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x451490. */
uint32_t lifted_f451490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451520. */
uint32_t lifted_f451520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451580. */
uint32_t lifted_f451580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451630. */
uint32_t lifted_f451630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451690. */
uint32_t lifted_f451690(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451730. */
uint32_t lifted_f451730(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x451e20. */
uint32_t lifted_f451e20(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x452770. */
uint32_t lifted_f452770(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
#endif
