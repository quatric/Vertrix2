#ifndef VERTRIX_LIFTED_WHOLE_6_H
#define VERTRIX_LIFTED_WHOLE_6_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4E66DC_STACK = 76,
    LIFTED_F4E6734_STACK = 384,
    LIFTED_F4E6B2C_STACK = 76,
    LIFTED_F4E6BFF_STACK = 72,
    LIFTED_F4E6C1D_STACK = 72,
    LIFTED_F4E6C98_STACK = 80,
    LIFTED_F4E6CD4_STACK = 68,
    LIFTED_F4E6CF2_STACK = 64,
    LIFTED_F4E6F30_STACK = 64,
    LIFTED_F4E70D0_STACK = 72,
    LIFTED_F4E7120_STACK = 68,
    LIFTED_F4E7140_STACK = 72,
    LIFTED_F4E7280_STACK = 68,
    LIFTED_F4E7540_STACK = 104,
    LIFTED_F4E7660_STACK = 112,
    LIFTED_F4E7850_STACK = 108,
    LIFTED_F4E7A00_STACK = 84,
    LIFTED_F4E7B18_STACK = 76,
    LIFTED_F4E7B50_STACK = 68,
    LIFTED_F4E7B90_STACK = 76,
    LIFTED_F4E7BF0_STACK = 80,
    LIFTED_F4E7C30_STACK = 104,
    LIFTED_F4E7E44_STACK = 76,
    LIFTED_F4E7EB0_STACK = 88,
    LIFTED_F4E7EF4_STACK = 76,
    LIFTED_F4E7F0C_STACK = 64,
    LIFTED_F4E8230_STACK = 116,
    LIFTED_F4E82D0_STACK = 72,
    LIFTED_F4E82F0_STACK = 64,
    LIFTED_F4E8310_STACK = 68,
    LIFTED_F4E8330_STACK = 104,
    LIFTED_F4E8400_STACK = 92,
    LIFTED_F4E8574_STACK = 92,
    LIFTED_F4E85C0_STACK = 76,
    LIFTED_F4E8620_STACK = 84,
    LIFTED_F4E8650_STACK = 84,
    LIFTED_F4E8660_STACK = 92,
    LIFTED_F4E869C_STACK = 100,
    LIFTED_F4E86FC_STACK = 76,
    LIFTED_F4E8730_STACK = 72,
    LIFTED_F4E8790_STACK = 68,
    LIFTED_F4E88BF_STACK = 76,
    LIFTED_F4E8950_STACK = 64,
    LIFTED_F4E8978_STACK = 144,
    LIFTED_F4E89E8_STACK = 68,
    LIFTED_F4E89F4_STACK = 68,
    LIFTED_F4E8A58_STACK = 72,
    LIFTED_F4E8A7C_STACK = 72,
    LIFTED_F4E8AA0_STACK = 76,
    LIFTED_F4E8ABC_STACK = 80,
    LIFTED_F4E8B24_STACK = 76,
    LIFTED_F4E8CC8_STACK = 104,
    LIFTED_F4E8D80_STACK = 84,
    LIFTED_F4E8DCB_STACK = 112,
    LIFTED_F4E8E69_STACK = 80,
    LIFTED_F4E8EA0_STACK = 80,
    LIFTED_F4E8FA7_STACK = 84,
    LIFTED_F4E8FF0_STACK = 80,
    LIFTED_F4E9020_STACK = 72,
    LIFTED_F4E9060_STACK = 76,
    LIFTED_F4E9194_STACK = 84,
    LIFTED_F4E91E0_STACK = 140,
    LIFTED_F4E949C_STACK = 80,
    LIFTED_F4E9670_STACK = 72,
    LIFTED_F4E9980_STACK = 80,
    LIFTED_F4E9C94_STACK = 76,
    LIFTED_F4E9CA8_STACK = 72,
    LIFTED_F4E9D10_STACK = 76,
    LIFTED_F4E9F00_STACK = 84,
    LIFTED_F4EA13C_STACK = 68,
    LIFTED_F4EA144_STACK = 68,
    LIFTED_F4EA190_STACK = 92,
    LIFTED_F4EA2A8_STACK = 72,
    LIFTED_F4EA310_STACK = 64,
    LIFTED_F4EA350_STACK = 108,
    LIFTED_F4EA410_STACK = 88,
    LIFTED_F4EA450_STACK = 84,
    LIFTED_F4EA540_STACK = 104,
    LIFTED_F4EA6A0_STACK = 72,
    LIFTED_F4EA6B0_STACK = 72,
    LIFTED_F4EA8CC_STACK = 132,
    LIFTED_F4EAA7C_STACK = 100,
    LIFTED_F4EADA0_STACK = 96,
    LIFTED_F4EAFB8_STACK = 124,
    LIFTED_F4EB140_STACK = 100,
    LIFTED_F4EB250_STACK = 72,
    LIFTED_F4EB270_STACK = 76,
    LIFTED_F4EB2A0_STACK = 160,
    LIFTED_F4EB3A0_STACK = 100,
    LIFTED_F4EB400_STACK = 64,
    LIFTED_F4EB4D4_STACK = 84,
    LIFTED_F4EB526_STACK = 68,
    LIFTED_F4EB57C_STACK = 68,
    LIFTED_RTL_SINGLE_NEGATE_STACK = 64,
    LIFTED_F4EB5C0_STACK = 76,
    LIFTED_F4EB606_STACK = 68,
    LIFTED_F4EB860_STACK = 72,
    LIFTED_F4EB892_STACK = 68,
    LIFTED_F4EB910_STACK = 92,
    LIFTED_F4EBA4C_STACK = 120,
    LIFTED_F4EBB34_STACK = 100,
    LIFTED_F4EBB78_STACK = 72,
    LIFTED_F4EBB84_STACK = 100,
    LIFTED_F4EBC90_STACK = 80,
    LIFTED_F4EBCD0_STACK = 68,
    LIFTED_F4EBCE8_STACK = 144,
    LIFTED_F4EBE60_STACK = 96,
    LIFTED_F4EBEC0_STACK = 140,
    LIFTED_F4EC0E0_STACK = 120,
    LIFTED_F4EC160_STACK = 76,
    LIFTED_F4EC1A0_STACK = 116,
    LIFTED_F4EC1D0_STACK = 72,
    LIFTED_F4EC1EC_STACK = 80,
    LIFTED_F4EC2D0_STACK = 72,
    LIFTED_F4EC307_STACK = 68,
    LIFTED_F4EC380_STACK = 112,
    LIFTED_F4EC3E0_STACK = 132,
    LIFTED_F4EC548_STACK = 80,
    LIFTED_F4EC578_STACK = 96,
    LIFTED_F4EC640_STACK = 64,
    LIFTED_F4EC650_STACK = 96,
    LIFTED_F4EC850_STACK = 100,
    LIFTED_F4EC8F0_STACK = 84,
    LIFTED_F4EC910_STACK = 72,
    LIFTED_F4EC940_STACK = 88,
    LIFTED_F4ECA85_STACK = 72,
    LIFTED_F4ECAA0_STACK = 80,
    LIFTED_F4ECAD0_STACK = 124,
    LIFTED_F4ECB50_STACK = 72,
    LIFTED_F4ECBA9_STACK = 100,
    LIFTED_F4ECC03_STACK = 108,
    LIFTED_F4ECC60_STACK = 84,
    LIFTED_F4ECF60_STACK = 64,
    LIFTED_F4EDA00_STACK = 128,
    LIFTED_F4EDB48_STACK = 80,
    LIFTED_F4EDD24_STACK = 80,
    LIFTED_F4EDF7F_STACK = 68,
    LIFTED_F4EE025_STACK = 72,
    LIFTED_F4EE094_STACK = 76,
    LIFTED_F4EE0DC_STACK = 80,
    LIFTED_F4EE160_STACK = 80,
    LIFTED_F4EE370_STACK = 92,
    LIFTED_F4EE3D2_STACK = 64,
    LIFTED_F4EE670_STACK = 88,
    LIFTED_F4EE730_STACK = 88,
    LIFTED_RETURN_CONSTANT_4EE730_STACK = 64,
    LIFTED_RETURN_CONSTANT_4EE750_STACK = 64,
    LIFTED_RETURN_CONSTANT_4EE6A0_STACK = 64,
    LIFTED_F4EE840_STACK = 104,
    LIFTED_F4EE8D0_STACK = 84,
    LIFTED_F4EE980_STACK = 136,
    LIFTED_F4EEA20_STACK = 104,
    LIFTED_F4EEA90_STACK = 84,
    LIFTED_F4EEB00_STACK = 76,
    LIFTED_F4EEB20_STACK = 76
};

/* Original 0x4e66dc. */
uint32_t lifted_f4e66dc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6734. */
uint32_t lifted_f4e6734(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6b2c. */
uint32_t lifted_f4e6b2c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6bff. */
uint32_t lifted_f4e6bff(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6c1d. */
uint32_t lifted_f4e6c1d(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6c98. */
uint32_t lifted_f4e6c98(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6cd4. */
uint32_t lifted_f4e6cd4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6cf2. */
uint32_t lifted_f4e6cf2(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6f30. */
uint32_t lifted_f4e6f30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e70d0. */
uint32_t lifted_f4e70d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7120. */
uint32_t lifted_f4e7120(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7140. */
uint32_t lifted_f4e7140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7280. */
uint32_t lifted_f4e7280(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e7a00. */
uint32_t lifted_f4e7a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7b18. */
uint32_t lifted_f4e7b18(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7b50. */
uint32_t lifted_f4e7b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7b90. */
uint32_t lifted_f4e7b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e7eb0. */
uint32_t lifted_f4e7eb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7ef4. */
uint32_t lifted_f4e7ef4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7f0c. */
uint32_t lifted_f4e7f0c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8230. */
uint32_t lifted_f4e8230(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e82d0. */
uint32_t lifted_f4e82d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e82f0. */
uint32_t lifted_f4e82f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8310. */
uint32_t lifted_f4e8310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8330. */
uint32_t lifted_f4e8330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8400. */
uint32_t lifted_f4e8400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8574. */
uint32_t lifted_f4e8574(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e85c0. */
uint32_t lifted_f4e85c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8620. */
uint32_t lifted_f4e8620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8650. */
uint32_t lifted_f4e8650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8660. */
uint32_t lifted_f4e8660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e869c. */
uint32_t lifted_f4e869c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e86fc. */
uint32_t lifted_f4e86fc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8730. */
uint32_t lifted_f4e8730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8790. */
uint32_t lifted_f4e8790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e88bf. */
uint32_t lifted_f4e88bf(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8950. */
uint32_t lifted_f4e8950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8978. */
uint32_t lifted_f4e8978(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e89e8. */
uint32_t lifted_f4e89e8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e89f4. */
uint32_t lifted_f4e89f4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8a58. */
uint32_t lifted_f4e8a58(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8a7c. */
uint32_t lifted_f4e8a7c(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e8cc8. */
uint32_t lifted_f4e8cc8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8d80. */
uint32_t lifted_f4e8d80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8dcb. */
uint32_t lifted_f4e8dcb(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8e69. */
uint32_t lifted_f4e8e69(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8ea0. */
uint32_t lifted_f4e8ea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8fa7. */
uint32_t lifted_f4e8fa7(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e9194. */
uint32_t lifted_f4e9194(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e91e0. */
uint32_t lifted_f4e91e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e949c. */
uint32_t lifted_f4e949c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9670. */
uint32_t lifted_f4e9670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9980. */
uint32_t lifted_f4e9980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9c94. */
uint32_t lifted_f4e9c94(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9ca8. */
uint32_t lifted_f4e9ca8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9d10. */
uint32_t lifted_f4e9d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9f00. */
uint32_t lifted_f4e9f00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea13c. */
uint32_t lifted_f4ea13c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea144. */
uint32_t lifted_f4ea144(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea190. */
uint32_t lifted_f4ea190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea2a8. */
uint32_t lifted_f4ea2a8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea310. */
uint32_t lifted_f4ea310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea350. */
uint32_t lifted_f4ea350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea410. */
uint32_t lifted_f4ea410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea450. */
uint32_t lifted_f4ea450(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea540. */
uint32_t lifted_f4ea540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea6a0. */
uint32_t lifted_f4ea6a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea6b0. */
uint32_t lifted_f4ea6b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea8cc. */
uint32_t lifted_f4ea8cc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eaa7c. */
uint32_t lifted_f4eaa7c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eada0. */
uint32_t lifted_f4eada0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eafb8. */
uint32_t lifted_f4eafb8(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4eb2a0. */
uint32_t lifted_f4eb2a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb3a0. */
uint32_t lifted_f4eb3a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb400. */
uint32_t lifted_f4eb400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb4d4. */
uint32_t lifted_f4eb4d4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb526. */
uint32_t lifted_f4eb526(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb57c. */
uint32_t lifted_f4eb57c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb5b4. */
uint32_t lifted_rtl_single_negate(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb5c0. */
uint32_t lifted_f4eb5c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb606. */
uint32_t lifted_f4eb606(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb860. */
uint32_t lifted_f4eb860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb892. */
uint32_t lifted_f4eb892(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb910. */
uint32_t lifted_f4eb910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eba4c. */
uint32_t lifted_f4eba4c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ebb34. */
uint32_t lifted_f4ebb34(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ebb78. */
uint32_t lifted_f4ebb78(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ebb84. */
uint32_t lifted_f4ebb84(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ebc90. */
uint32_t lifted_f4ebc90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ebcd0. */
uint32_t lifted_f4ebcd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ebce8. */
uint32_t lifted_f4ebce8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ebe60. */
uint32_t lifted_f4ebe60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ebec0. */
uint32_t lifted_f4ebec0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec0e0. */
uint32_t lifted_f4ec0e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec160. */
uint32_t lifted_f4ec160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec1a0. */
uint32_t lifted_f4ec1a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec1d0. */
uint32_t lifted_f4ec1d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec1ec. */
uint32_t lifted_f4ec1ec(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec2d0. */
uint32_t lifted_f4ec2d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec307. */
uint32_t lifted_f4ec307(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ec640. */
uint32_t lifted_f4ec640(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec650. */
uint32_t lifted_f4ec650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec850. */
uint32_t lifted_f4ec850(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4eca85. */
uint32_t lifted_f4eca85(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ecba9. */
uint32_t lifted_f4ecba9(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ecc03. */
uint32_t lifted_f4ecc03(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ecc60. */
uint32_t lifted_f4ecc60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ecf60. */
uint32_t lifted_f4ecf60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eda00. */
uint32_t lifted_f4eda00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4edb48. */
uint32_t lifted_f4edb48(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4edd24. */
uint32_t lifted_f4edd24(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4edf7f. */
uint32_t lifted_f4edf7f(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee025. */
uint32_t lifted_f4ee025(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee094. */
uint32_t lifted_f4ee094(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee0dc. */
uint32_t lifted_f4ee0dc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee160. */
uint32_t lifted_f4ee160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee370. */
uint32_t lifted_f4ee370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee3d2. */
uint32_t lifted_f4ee3d2(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee670. */
uint32_t lifted_f4ee670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee730. */
uint32_t lifted_f4ee730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee7f0. */
uint32_t lifted_return_constant_4ee730(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee800. */
uint32_t lifted_return_constant_4ee750(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ee810. */
uint32_t lifted_return_constant_4ee6a0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
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

/* Original 0x4eea90. */
uint32_t lifted_f4eea90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eeb00. */
uint32_t lifted_f4eeb00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eeb20. */
uint32_t lifted_f4eeb20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
