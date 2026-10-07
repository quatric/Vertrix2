#ifndef VERTRIX_LIFTED_WHOLE_0_H
#define VERTRIX_LIFTED_WHOLE_0_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F401010_STACK = 92,
    LIFTED_F401054_STACK = 92,
    LIFTED_F404610_STACK = 76,
    LIFTED_F404680_STACK = 76,
    LIFTED_F405EA0_STACK = 88,
    LIFTED_F40A800_STACK = 88,
    LIFTED_F40A860_STACK = 76,
    LIFTED_F40A890_STACK = 72,
    LIFTED_F40A8F0_STACK = 88,
    LIFTED_F40A950_STACK = 92,
    LIFTED_F40A9D0_STACK = 124,
    LIFTED_F40AB10_STACK = 68,
    LIFTED_F40AD50_STACK = 68,
    LIFTED_F40AE80_STACK = 84,
    LIFTED_F40BA00_STACK = 120,
    LIFTED_F40C1C0_STACK = 72,
    LIFTED_F40C1E0_STACK = 68,
    LIFTED_F40C1F0_STACK = 76,
    LIFTED_F40C210_STACK = 68,
    LIFTED_F40C220_STACK = 88,
    LIFTED_F40C260_STACK = 88,
    LIFTED_F40C2A0_STACK = 88,
    LIFTED_F40C2E0_STACK = 88,
    LIFTED_F40C320_STACK = 88,
    LIFTED_F40C360_STACK = 88,
    LIFTED_F40C430_STACK = 100,
    LIFTED_F40CE20_STACK = 80,
    LIFTED_F40CE80_STACK = 72,
    LIFTED_F40CFF0_STACK = 88,
    LIFTED_F40D090_STACK = 80,
    LIFTED_F40D250_STACK = 76,
    LIFTED_F40DC80_STACK = 92,
    LIFTED_F40DF20_STACK = 76,
    LIFTED_F40E580_STACK = 80,
    LIFTED_F40E640_STACK = 68,
    LIFTED_F40E670_STACK = 76,
    LIFTED_F40E770_STACK = 92,
    LIFTED_F40ED70_STACK = 92,
    LIFTED_F40EDE0_STACK = 80,
    LIFTED_F40EE30_STACK = 68,
    LIFTED_F40EE60_STACK = 72,
    LIFTED_F40EEA0_STACK = 68,
    LIFTED_F40EF00_STACK = 68,
    LIFTED_F40EF40_STACK = 68,
    LIFTED_F40F170_STACK = 72,
    LIFTED_F40F9E0_STACK = 308,
    LIFTED_F410150_STACK = 72,
    LIFTED_F4108A0_STACK = 416,
    LIFTED_F4112D0_STACK = 468,
    LIFTED_F4121E0_STACK = 100,
    LIFTED_F412390_STACK = 88,
    LIFTED_F412430_STACK = 68,
    LIFTED_F412510_STACK = 68,
    LIFTED_F4125E0_STACK = 68,
    LIFTED_F414A90_STACK = 92,
    LIFTED_F414B10_STACK = 92,
    LIFTED_F415330_STACK = 80,
    LIFTED_F415350_STACK = 72,
    LIFTED_F4153E0_STACK = 68,
    LIFTED_F415530_STACK = 68,
    LIFTED_F415550_STACK = 68,
    LIFTED_F415B50_STACK = 68,
    LIFTED_F415B90_STACK = 72,
    LIFTED_F415BD0_STACK = 68,
    LIFTED_F415C00_STACK = 72,
    LIFTED_F415C30_STACK = 72,
    LIFTED_F415EF0_STACK = 80,
    LIFTED_F415F10_STACK = 80,
    LIFTED_F415F30_STACK = 80,
    LIFTED_F415F50_STACK = 80,
    LIFTED_F415F70_STACK = 80,
    LIFTED_F415F90_STACK = 80,
    LIFTED_F416970_STACK = 72,
    LIFTED_F416B30_STACK = 80,
    LIFTED_F416B50_STACK = 80,
    LIFTED_F416B70_STACK = 80,
    LIFTED_F416B90_STACK = 80,
    LIFTED_F416BB0_STACK = 80,
    LIFTED_F416BD0_STACK = 80,
    LIFTED_F416BF0_STACK = 80,
    LIFTED_F416C10_STACK = 76,
    LIFTED_F417030_STACK = 80,
    LIFTED_F4170F0_STACK = 80,
    LIFTED_F417130_STACK = 80,
    LIFTED_F4174F0_STACK = 84,
    LIFTED_F417550_STACK = 84,
    LIFTED_F4175B0_STACK = 84,
    LIFTED_F417620_STACK = 84,
    LIFTED_F417790_STACK = 80,
    LIFTED_F4178D0_STACK = 72,
    LIFTED_F417970_STACK = 72,
    LIFTED_F417E20_STACK = 68,
    LIFTED_F417F40_STACK = 68,
    LIFTED_F418100_STACK = 68,
    LIFTED_F4182F0_STACK = 72,
    LIFTED_F418550_STACK = 72,
    LIFTED_F418570_STACK = 72,
    LIFTED_F418760_STACK = 68,
    LIFTED_F418830_STACK = 68,
    LIFTED_F418970_STACK = 120,
    LIFTED_F418AE0_STACK = 76,
    LIFTED_F4192A0_STACK = 172,
    LIFTED_F419490_STACK = 68,
    LIFTED_F4194B0_STACK = 68,
    LIFTED_F419EF0_STACK = 116,
    LIFTED_F419F60_STACK = 68,
    LIFTED_F41A240_STACK = 104,
    LIFTED_F41A2B0_STACK = 92,
    LIFTED_F41A2F0_STACK = 92,
    LIFTED_F41A4E0_STACK = 96,
    LIFTED_F41A520_STACK = 76,
    LIFTED_F41A680_STACK = 96,
    LIFTED_F41A6C0_STACK = 96,
    LIFTED_F41A700_STACK = 128,
    LIFTED_F41A930_STACK = 68,
    LIFTED_F41A940_STACK = 72,
    LIFTED_F41A960_STACK = 104,
    LIFTED_F41A9A0_STACK = 100,
    LIFTED_F41AA20_STACK = 104,
    LIFTED_F41AAA0_STACK = 104,
    LIFTED_F41AAF0_STACK = 68,
    LIFTED_F41AB00_STACK = 76,
    LIFTED_F41AB30_STACK = 76,
    LIFTED_F41AB60_STACK = 76,
    LIFTED_F41AB90_STACK = 96,
    LIFTED_F41ABE0_STACK = 76,
    LIFTED_F41AC00_STACK = 76,
    LIFTED_F41AC20_STACK = 76,
    LIFTED_F41AC40_STACK = 80,
    LIFTED_F41AC70_STACK = 72,
    LIFTED_F41AC80_STACK = 84,
    LIFTED_F41ACA0_STACK = 80,
    LIFTED_F41B5E0_STACK = 124,
    LIFTED_F41B680_STACK = 120,
    LIFTED_F41C020_STACK = 124,
    LIFTED_F41C080_STACK = 96,
    LIFTED_F41C0C0_STACK = 84,
    LIFTED_F41C0F0_STACK = 120,
    LIFTED_F41C160_STACK = 120,
    LIFTED_F41C1D0_STACK = 120,
    LIFTED_F41C240_STACK = 120,
    LIFTED_F41C2B0_STACK = 120,
    LIFTED_F41C390_STACK = 116,
    LIFTED_F41C400_STACK = 68,
    LIFTED_F41C6D0_STACK = 120,
    LIFTED_F41C740_STACK = 120,
    LIFTED_F41C9E0_STACK = 176,
    LIFTED_F41CBB0_STACK = 136,
    LIFTED_F41D410_STACK = 108,
    LIFTED_F41D470_STACK = 156,
    LIFTED_F41D510_STACK = 152,
    LIFTED_F41D5B0_STACK = 120,
    LIFTED_F41D640_STACK = 72,
    LIFTED_F41D670_STACK = 72,
    LIFTED_F41DD60_STACK = 120,
    LIFTED_F41DDF0_STACK = 120,
    LIFTED_F41EDE0_STACK = 204,
    LIFTED_F41EFE0_STACK = 152,
    LIFTED_F41F460_STACK = 156,
    LIFTED_F41F910_STACK = 156,
    LIFTED_F41FC70_STACK = 156,
    LIFTED_F421E80_STACK = 144,
    LIFTED_F423D70_STACK = 92,
    LIFTED_F424160_STACK = 68,
    LIFTED_F424180_STACK = 104,
    LIFTED_F424760_STACK = 84,
    LIFTED_F425260_STACK = 184,
    LIFTED_F4253B0_STACK = 164,
    LIFTED_F4259D0_STACK = 144,
    LIFTED_F425A50_STACK = 144,
    LIFTED_F425AE0_STACK = 196,
    LIFTED_F425D30_STACK = 72,
    LIFTED_F425E00_STACK = 72,
    LIFTED_F425E20_STACK = 68,
    LIFTED_F425EF0_STACK = 68,
    LIFTED_F4290A0_STACK = 76,
    LIFTED_F429350_STACK = 136,
    LIFTED_F4293E0_STACK = 96,
    LIFTED_F429460_STACK = 148,
    LIFTED_F429670_STACK = 68,
    LIFTED_F429FE0_STACK = 112,
    LIFTED_F42A080_STACK = 100,
    LIFTED_F42A480_STACK = 72,
    LIFTED_F42A4A0_STACK = 72,
    LIFTED_F42A540_STACK = 276,
    LIFTED_F42A8B0_STACK = 72,
    LIFTED_F42A8E0_STACK = 84,
    LIFTED_F42B000_STACK = 80,
    LIFTED_F42B050_STACK = 68,
    LIFTED_F42B0F0_STACK = 72,
    LIFTED_F42B5C0_STACK = 68,
    LIFTED_F42B920_STACK = 72,
    LIFTED_F42B950_STACK = 80,
    LIFTED_F42B990_STACK = 84,
    LIFTED_F42B9F0_STACK = 80,
    LIFTED_F42BA40_STACK = 68,
    LIFTED_F42BA70_STACK = 72,
    LIFTED_F42BB00_STACK = 68,
    LIFTED_F42EBA0_STACK = 72,
    LIFTED_F42EBC0_STACK = 72,
    LIFTED_F42EBE0_STACK = 72,
    LIFTED_F42EC00_STACK = 72,
    LIFTED_F42EC20_STACK = 72,
    LIFTED_F42EC40_STACK = 72,
    LIFTED_F42EC60_STACK = 72,
    LIFTED_F42EC80_STACK = 72,
    LIFTED_F42ECA0_STACK = 72,
    LIFTED_F42ECC0_STACK = 72,
    LIFTED_F42ED40_STACK = 76,
    LIFTED_F42ED70_STACK = 76,
    LIFTED_F42EDA0_STACK = 72,
    LIFTED_F42EDF0_STACK = 76,
    LIFTED_F42EE80_STACK = 100,
    LIFTED_F42EEE0_STACK = 72,
    LIFTED_F42EF00_STACK = 72,
    LIFTED_F42EF10_STACK = 72,
    LIFTED_F42EF20_STACK = 72,
    LIFTED_F42EF30_STACK = 72,
    LIFTED_F42EF40_STACK = 72,
    LIFTED_F42EF50_STACK = 72,
    LIFTED_F42F280_STACK = 76,
    LIFTED_F42F2B0_STACK = 72,
    LIFTED_F42F3D0_STACK = 76,
    LIFTED_F42F410_STACK = 72,
    LIFTED_F42F520_STACK = 76,
    LIFTED_F42F550_STACK = 76,
    LIFTED_F42F6E0_STACK = 76,
    LIFTED_F42F720_STACK = 76,
    LIFTED_F42F850_STACK = 72,
    LIFTED_F42F860_STACK = 72,
    LIFTED_F42F870_STACK = 72,
    LIFTED_F42F880_STACK = 72,
    LIFTED_F42FF50_STACK = 164,
    LIFTED_F430090_STACK = 68,
    LIFTED_F4300B0_STACK = 76,
    LIFTED_F430100_STACK = 76,
    LIFTED_F430190_STACK = 152,
    LIFTED_F4302A0_STACK = 184,
    LIFTED_F430440_STACK = 204,
    LIFTED_F430660_STACK = 180,
    LIFTED_F430800_STACK = 96,
    LIFTED_F431100_STACK = 80,
    LIFTED_F431140_STACK = 80,
    LIFTED_F431180_STACK = 72,
    LIFTED_F4311A0_STACK = 72,
    LIFTED_F431390_STACK = 84,
    LIFTED_F4314A0_STACK = 160,
    LIFTED_F431780_STACK = 140,
    LIFTED_F431930_STACK = 140,
    LIFTED_F431B20_STACK = 104,
    LIFTED_F431D60_STACK = 72,
    LIFTED_F431FA0_STACK = 68,
    LIFTED_F432010_STACK = 68,
    LIFTED_F4320D0_STACK = 80,
    LIFTED_F432110_STACK = 80,
    LIFTED_F432160_STACK = 92,
    LIFTED_F4321B0_STACK = 84,
    LIFTED_F432820_STACK = 76,
    LIFTED_F433550_STACK = 116,
    LIFTED_F435FE0_STACK = 84,
    LIFTED_F436030_STACK = 88,
    LIFTED_F436070_STACK = 88,
    LIFTED_F4360B0_STACK = 84,
    LIFTED_F436100_STACK = 84,
    LIFTED_F438910_STACK = 76,
    LIFTED_F438D50_STACK = 92,
    LIFTED_F43A080_STACK = 68,
    LIFTED_F43A410_STACK = 112,
    LIFTED_F43A510_STACK = 68,
    LIFTED_F43A560_STACK = 72,
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
    LIFTED_F43B660_STACK = 80,
    LIFTED_F43B680_STACK = 80,
    LIFTED_F43B720_STACK = 100,
    LIFTED_F43B7C0_STACK = 88,
    LIFTED_F43B800_STACK = 68,
    LIFTED_F43B810_STACK = 76,
    LIFTED_F43B930_STACK = 88,
    LIFTED_F43B980_STACK = 84,
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
    LIFTED_F43D260_STACK = 88,
    LIFTED_F43D2B0_STACK = 80,
    LIFTED_F43D300_STACK = 68,
    LIFTED_F43D320_STACK = 72,
    LIFTED_F43D3F0_STACK = 68,
    LIFTED_F43D800_STACK = 80,
    LIFTED_F43E260_STACK = 84,
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
    LIFTED_F441120_STACK = 68,
    LIFTED_F441A80_STACK = 104,
    LIFTED_F441B30_STACK = 100,
    LIFTED_F442110_STACK = 72,
    LIFTED_F442B00_STACK = 76,
    LIFTED_F443260_STACK = 84,
    LIFTED_F443320_STACK = 112,
    LIFTED_F4433C0_STACK = 112,
    LIFTED_F443460_STACK = 124,
    LIFTED_F4434E0_STACK = 96,
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
    LIFTED_F445A00_STACK = 116,
    LIFTED_F445A90_STACK = 112,
    LIFTED_F445B10_STACK = 112,
    LIFTED_F446730_STACK = 108,
    LIFTED_F4467C0_STACK = 108,
    LIFTED_F4469C0_STACK = 124,
    LIFTED_F446A80_STACK = 104,
    LIFTED_F446D70_STACK = 124,
    LIFTED_F446EC0_STACK = 128,
    LIFTED_F447140_STACK = 124,
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
    LIFTED_F449360_STACK = 76
};

/* Original 0x401010. */
uint32_t lifted_f401010(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x401054. */
uint32_t lifted_f401054(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x404610. */
uint32_t lifted_f404610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x404680. */
uint32_t lifted_f404680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x405ea0. */
uint32_t lifted_f405ea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a800. */
uint32_t lifted_f40a800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a860. */
uint32_t lifted_f40a860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a890. */
uint32_t lifted_f40a890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a8f0. */
uint32_t lifted_f40a8f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a950. */
uint32_t lifted_f40a950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a9d0. */
uint32_t lifted_f40a9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ab10. */
uint32_t lifted_f40ab10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ad50. */
uint32_t lifted_f40ad50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ae80. */
uint32_t lifted_f40ae80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ba00. */
uint32_t lifted_f40ba00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c1c0. */
uint32_t lifted_f40c1c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c1e0. */
uint32_t lifted_f40c1e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c1f0. */
uint32_t lifted_f40c1f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c210. */
uint32_t lifted_f40c210(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c220. */
uint32_t lifted_f40c220(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c260. */
uint32_t lifted_f40c260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c2a0. */
uint32_t lifted_f40c2a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c2e0. */
uint32_t lifted_f40c2e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c320. */
uint32_t lifted_f40c320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c360. */
uint32_t lifted_f40c360(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c430. */
uint32_t lifted_f40c430(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ce20. */
uint32_t lifted_f40ce20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ce80. */
uint32_t lifted_f40ce80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40cff0. */
uint32_t lifted_f40cff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40d090. */
uint32_t lifted_f40d090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40d250. */
uint32_t lifted_f40d250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40dc80. */
uint32_t lifted_f40dc80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40df20. */
uint32_t lifted_f40df20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e580. */
uint32_t lifted_f40e580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e640. */
uint32_t lifted_f40e640(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e670. */
uint32_t lifted_f40e670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e770. */
uint32_t lifted_f40e770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ed70. */
uint32_t lifted_f40ed70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ede0. */
uint32_t lifted_f40ede0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ee30. */
uint32_t lifted_f40ee30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ee60. */
uint32_t lifted_f40ee60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40eea0. */
uint32_t lifted_f40eea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ef00. */
uint32_t lifted_f40ef00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ef40. */
uint32_t lifted_f40ef40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40f170. */
uint32_t lifted_f40f170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40f9e0. */
uint32_t lifted_f40f9e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x410150. */
uint32_t lifted_f410150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4108a0. */
uint32_t lifted_f4108a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4112d0. */
uint32_t lifted_f4112d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4121e0. */
uint32_t lifted_f4121e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x412390. */
uint32_t lifted_f412390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x412430. */
uint32_t lifted_f412430(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x412510. */
uint32_t lifted_f412510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4125e0. */
uint32_t lifted_f4125e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x414a90. */
uint32_t lifted_f414a90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x414b10. */
uint32_t lifted_f414b10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415330. */
uint32_t lifted_f415330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415350. */
uint32_t lifted_f415350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4153e0. */
uint32_t lifted_f4153e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415530. */
uint32_t lifted_f415530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415550. */
uint32_t lifted_f415550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415b50. */
uint32_t lifted_f415b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415b90. */
uint32_t lifted_f415b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415bd0. */
uint32_t lifted_f415bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415c00. */
uint32_t lifted_f415c00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415c30. */
uint32_t lifted_f415c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415ef0. */
uint32_t lifted_f415ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415f10. */
uint32_t lifted_f415f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415f30. */
uint32_t lifted_f415f30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415f50. */
uint32_t lifted_f415f50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415f70. */
uint32_t lifted_f415f70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415f90. */
uint32_t lifted_f415f90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416970. */
uint32_t lifted_f416970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416b30. */
uint32_t lifted_f416b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416b50. */
uint32_t lifted_f416b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416b70. */
uint32_t lifted_f416b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416b90. */
uint32_t lifted_f416b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416bb0. */
uint32_t lifted_f416bb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416bd0. */
uint32_t lifted_f416bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416bf0. */
uint32_t lifted_f416bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416c10. */
uint32_t lifted_f416c10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417030. */
uint32_t lifted_f417030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4170f0. */
uint32_t lifted_f4170f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417130. */
uint32_t lifted_f417130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4174f0. */
uint32_t lifted_f4174f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417550. */
uint32_t lifted_f417550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4175b0. */
uint32_t lifted_f4175b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417620. */
uint32_t lifted_f417620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417790. */
uint32_t lifted_f417790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4178d0. */
uint32_t lifted_f4178d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417970. */
uint32_t lifted_f417970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417e20. */
uint32_t lifted_f417e20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417f40. */
uint32_t lifted_f417f40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418100. */
uint32_t lifted_f418100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4182f0. */
uint32_t lifted_f4182f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418550. */
uint32_t lifted_f418550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418570. */
uint32_t lifted_f418570(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418760. */
uint32_t lifted_f418760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418830. */
uint32_t lifted_f418830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418970. */
uint32_t lifted_f418970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418ae0. */
uint32_t lifted_f418ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4192a0. */
uint32_t lifted_f4192a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x419490. */
uint32_t lifted_f419490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4194b0. */
uint32_t lifted_f4194b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x419ef0. */
uint32_t lifted_f419ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x419f60. */
uint32_t lifted_f419f60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a240. */
uint32_t lifted_f41a240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a2b0. */
uint32_t lifted_f41a2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a2f0. */
uint32_t lifted_f41a2f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a4e0. */
uint32_t lifted_f41a4e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a520. */
uint32_t lifted_f41a520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a680. */
uint32_t lifted_f41a680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a6c0. */
uint32_t lifted_f41a6c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a700. */
uint32_t lifted_f41a700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a930. */
uint32_t lifted_f41a930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a940. */
uint32_t lifted_f41a940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a960. */
uint32_t lifted_f41a960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a9a0. */
uint32_t lifted_f41a9a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41aa20. */
uint32_t lifted_f41aa20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41aaa0. */
uint32_t lifted_f41aaa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41aaf0. */
uint32_t lifted_f41aaf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ab00. */
uint32_t lifted_f41ab00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ab30. */
uint32_t lifted_f41ab30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ab60. */
uint32_t lifted_f41ab60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ab90. */
uint32_t lifted_f41ab90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41abe0. */
uint32_t lifted_f41abe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ac00. */
uint32_t lifted_f41ac00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ac20. */
uint32_t lifted_f41ac20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ac40. */
uint32_t lifted_f41ac40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ac70. */
uint32_t lifted_f41ac70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ac80. */
uint32_t lifted_f41ac80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41aca0. */
uint32_t lifted_f41aca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41b5e0. */
uint32_t lifted_f41b5e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41b680. */
uint32_t lifted_f41b680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c020. */
uint32_t lifted_f41c020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c080. */
uint32_t lifted_f41c080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c0c0. */
uint32_t lifted_f41c0c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c0f0. */
uint32_t lifted_f41c0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c160. */
uint32_t lifted_f41c160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c1d0. */
uint32_t lifted_f41c1d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c240. */
uint32_t lifted_f41c240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c2b0. */
uint32_t lifted_f41c2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c390. */
uint32_t lifted_f41c390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c400. */
uint32_t lifted_f41c400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c6d0. */
uint32_t lifted_f41c6d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c740. */
uint32_t lifted_f41c740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c9e0. */
uint32_t lifted_f41c9e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41cbb0. */
uint32_t lifted_f41cbb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d410. */
uint32_t lifted_f41d410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d470. */
uint32_t lifted_f41d470(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d510. */
uint32_t lifted_f41d510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d5b0. */
uint32_t lifted_f41d5b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d640. */
uint32_t lifted_f41d640(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d670. */
uint32_t lifted_f41d670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41dd60. */
uint32_t lifted_f41dd60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ddf0. */
uint32_t lifted_f41ddf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ede0. */
uint32_t lifted_f41ede0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41efe0. */
uint32_t lifted_f41efe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41f460. */
uint32_t lifted_f41f460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41f910. */
uint32_t lifted_f41f910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41fc70. */
uint32_t lifted_f41fc70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x421e80. */
uint32_t lifted_f421e80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x423d70. */
uint32_t lifted_f423d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424160. */
uint32_t lifted_f424160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424180. */
uint32_t lifted_f424180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424760. */
uint32_t lifted_f424760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425260. */
uint32_t lifted_f425260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4253b0. */
uint32_t lifted_f4253b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4259d0. */
uint32_t lifted_f4259d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425a50. */
uint32_t lifted_f425a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425ae0. */
uint32_t lifted_f425ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425d30. */
uint32_t lifted_f425d30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425e00. */
uint32_t lifted_f425e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425e20. */
uint32_t lifted_f425e20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425ef0. */
uint32_t lifted_f425ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4290a0. */
uint32_t lifted_f4290a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429350. */
uint32_t lifted_f429350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4293e0. */
uint32_t lifted_f4293e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429460. */
uint32_t lifted_f429460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429670. */
uint32_t lifted_f429670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429fe0. */
uint32_t lifted_f429fe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a080. */
uint32_t lifted_f42a080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a480. */
uint32_t lifted_f42a480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a4a0. */
uint32_t lifted_f42a4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a540. */
uint32_t lifted_f42a540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a8b0. */
uint32_t lifted_f42a8b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a8e0. */
uint32_t lifted_f42a8e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b000. */
uint32_t lifted_f42b000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b050. */
uint32_t lifted_f42b050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b0f0. */
uint32_t lifted_f42b0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b5c0. */
uint32_t lifted_f42b5c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b920. */
uint32_t lifted_f42b920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b950. */
uint32_t lifted_f42b950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b990. */
uint32_t lifted_f42b990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b9f0. */
uint32_t lifted_f42b9f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ba40. */
uint32_t lifted_f42ba40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ba70. */
uint32_t lifted_f42ba70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42bb00. */
uint32_t lifted_f42bb00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42eba0. */
uint32_t lifted_f42eba0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ebc0. */
uint32_t lifted_f42ebc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ebe0. */
uint32_t lifted_f42ebe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ec00. */
uint32_t lifted_f42ec00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ec20. */
uint32_t lifted_f42ec20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ec40. */
uint32_t lifted_f42ec40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ec60. */
uint32_t lifted_f42ec60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ec80. */
uint32_t lifted_f42ec80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42eca0. */
uint32_t lifted_f42eca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ecc0. */
uint32_t lifted_f42ecc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ed40. */
uint32_t lifted_f42ed40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ed70. */
uint32_t lifted_f42ed70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42eda0. */
uint32_t lifted_f42eda0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42edf0. */
uint32_t lifted_f42edf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ee80. */
uint32_t lifted_f42ee80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42eee0. */
uint32_t lifted_f42eee0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef00. */
uint32_t lifted_f42ef00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef10. */
uint32_t lifted_f42ef10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef20. */
uint32_t lifted_f42ef20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef30. */
uint32_t lifted_f42ef30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef40. */
uint32_t lifted_f42ef40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef50. */
uint32_t lifted_f42ef50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f280. */
uint32_t lifted_f42f280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f2b0. */
uint32_t lifted_f42f2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f3d0. */
uint32_t lifted_f42f3d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f410. */
uint32_t lifted_f42f410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f520. */
uint32_t lifted_f42f520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f550. */
uint32_t lifted_f42f550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f6e0. */
uint32_t lifted_f42f6e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f720. */
uint32_t lifted_f42f720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f850. */
uint32_t lifted_f42f850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f860. */
uint32_t lifted_f42f860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f870. */
uint32_t lifted_f42f870(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f880. */
uint32_t lifted_f42f880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ff50. */
uint32_t lifted_f42ff50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430090. */
uint32_t lifted_f430090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4300b0. */
uint32_t lifted_f4300b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430100. */
uint32_t lifted_f430100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430190. */
uint32_t lifted_f430190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4302a0. */
uint32_t lifted_f4302a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430440. */
uint32_t lifted_f430440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430660. */
uint32_t lifted_f430660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430800. */
uint32_t lifted_f430800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431100. */
uint32_t lifted_f431100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431140. */
uint32_t lifted_f431140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431180. */
uint32_t lifted_f431180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4311a0. */
uint32_t lifted_f4311a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431390. */
uint32_t lifted_f431390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4314a0. */
uint32_t lifted_f4314a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431780. */
uint32_t lifted_f431780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431930. */
uint32_t lifted_f431930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431b20. */
uint32_t lifted_f431b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431d60. */
uint32_t lifted_f431d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431fa0. */
uint32_t lifted_f431fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432010. */
uint32_t lifted_f432010(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4320d0. */
uint32_t lifted_f4320d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432110. */
uint32_t lifted_f432110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432160. */
uint32_t lifted_f432160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4321b0. */
uint32_t lifted_f4321b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432820. */
uint32_t lifted_f432820(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x433550. */
uint32_t lifted_f433550(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x438910. */
uint32_t lifted_f438910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438d50. */
uint32_t lifted_f438d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a080. */
uint32_t lifted_f43a080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a410. */
uint32_t lifted_f43a410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a510. */
uint32_t lifted_f43a510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a560. */
uint32_t lifted_f43a560(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x43b660. */
uint32_t lifted_f43b660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b680. */
uint32_t lifted_f43b680(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x43d3f0. */
uint32_t lifted_f43d3f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d800. */
uint32_t lifted_f43d800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e260. */
uint32_t lifted_f43e260(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x441120. */
uint32_t lifted_f441120(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x445a00. */
uint32_t lifted_f445a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445a90. */
uint32_t lifted_f445a90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445b10. */
uint32_t lifted_f445b10(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x446d70. */
uint32_t lifted_f446d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446ec0. */
uint32_t lifted_f446ec0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x447140. */
uint32_t lifted_f447140(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
#endif
