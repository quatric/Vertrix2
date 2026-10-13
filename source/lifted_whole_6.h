#ifndef VERTRIX_LIFTED_WHOLE_6_H
#define VERTRIX_LIFTED_WHOLE_6_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_RTL_INTEGER_TO_DOUBLE_STACK = 68,
    LIFTED_F4D6A30_STACK = 80,
    LIFTED_F4D70E0_STACK = 92,
    LIFTED_F4D7140_STACK = 128,
    LIFTED_F4D73B0_STACK = 120,
    LIFTED_F4D73C0_STACK = 80,
    LIFTED_F4D7400_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D73B0_STACK = 64,
    LIFTED_F4D7440_STACK = 64,
    LIFTED_F4D7450_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D73C0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D7400_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D25E0_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D7140_STACK = 64,
    LIFTED_RETURN_CONSTANT_4D7110_STACK = 64,
    LIFTED_RTL_SIGN_COMPARE_STACK = 64,
    LIFTED_F4D80D5_STACK = 84,
    LIFTED_F4D8198_STACK = 80,
    LIFTED_RTL_SINGLE_DIVIDE_SOFTWARE_FULL_STACK = 88,
    LIFTED_F4D83F0_STACK = 136,
    LIFTED_RTL_WIDE_LENGTH_STACK = 72,
    LIFTED_F4D85A0_STACK = 72,
    LIFTED_F4D85C0_STACK = 80,
    LIFTED_F4D8950_STACK = 80,
    LIFTED_F4D8B30_STACK = 84,
    LIFTED_OBJECT_DESTROY_G_STACK = 136,
    LIFTED_NODE_POOL_TAKE_INITIALISED_STACK = 104,
    LIFTED_F4D9350_STACK = 76,
    LIFTED_RTL_STATIC_INIT_CALL_STACK = 72,
    LIFTED_F4D9530_STACK = 72,
    LIFTED_RTL_FORWARD_PAIR_STACK = 88,
    LIFTED_F4D9AE0_STACK = 64,
    LIFTED_RTL_ZERO_CALL3_STACK = 100,
    LIFTED_EXCEPTION_CHAIN_STEP_STACK = 128,
    LIFTED_F4DA71B_STACK = 100,
    LIFTED_RTL_STACK_PAIR_CALL_STACK = 80,
    LIFTED_F4DAC10_STACK = 80,
    LIFTED_F4DACA0_STACK = 72,
    LIFTED_F4DACD0_STACK = 96,
    LIFTED_F4DACF8_STACK = 80,
    LIFTED_RTL_EBX_FROM_EDX_CALL_STACK = 72,
    LIFTED_F4DAD38_STACK = 116,
    LIFTED_RTL_NEGATE_DOUBLE_STACK = 64,
    LIFTED_F4DAE70_STACK = 72,
    LIFTED_F4DAEB8_STACK = 72,
    LIFTED_F4DB131_STACK = 88,
    LIFTED_F4DB950_STACK = 92,
    LIFTED_F4DB980_STACK = 100,
    LIFTED_F4DB9FC_STACK = 100,
    LIFTED_F4DBA20_STACK = 76,
    LIFTED_F4DBC60_STACK = 104,
    LIFTED_F4DC000_STACK = 72,
    LIFTED_F4DC190_STACK = 72,
    LIFTED_F4DC290_STACK = 116,
    LIFTED_F4DC2F0_STACK = 184,
    LIFTED_F4DC420_STACK = 156,
    LIFTED_F4DC4B0_STACK = 96,
    LIFTED_RTL_RECORD_SET_ARGUMENT_STACK = 68,
    LIFTED_RTL_CONSTRUCT_LIST_STACK = 104,
    LIFTED_F4DD3E0_STACK = 92,
    LIFTED_F4DD430_STACK = 112,
    LIFTED_F4DD460_STACK = 88,
    LIFTED_F4DD4A0_STACK = 152,
    LIFTED_F4DDBE0_STACK = 92,
    LIFTED_F4DDC30_STACK = 112,
    LIFTED_RTL_RELEASE_LIST_HEAD_STACK = 84,
    LIFTED_F4DDE50_STACK = 72,
    LIFTED_F4DE600_STACK = 80,
    LIFTED_F4DE630_STACK = 140,
    LIFTED_F4DE810_STACK = 252,
    LIFTED_RTL_RECORD_INCREMENT_STACK = 68,
    LIFTED_F4DEC70_STACK = 104,
    LIFTED_RTL_CONSTRUCT_EVENT_TABLE_STACK = 124,
    LIFTED_F4DED70_STACK = 104,
    LIFTED_RTL_SEGMENT_DISPATCH_STACK = 84,
    LIFTED_F4DEF50_STACK = 84,
    LIFTED_F4DEF90_STACK = 76,
    LIFTED_F4DEFD0_STACK = 136,
    LIFTED_F4DF0D0_STACK = 72,
    LIFTED_F4DF0F0_STACK = 76,
    LIFTED_RTL_TABLE_LOOKUP_VALUE_STACK = 76,
    LIFTED_F4DF1C0_STACK = 76,
    LIFTED_F4DFA74_STACK = 68,
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
    LIFTED_F4E08A0_STACK = 72,
    LIFTED_F4E0960_STACK = 64,
    LIFTED_F4E0994_STACK = 68,
    LIFTED_F4E09F0_STACK = 68,
    LIFTED_F4E0A30_STACK = 104,
    LIFTED_F4E0A95_STACK = 64,
    LIFTED_F4E0AE5_STACK = 104,
    LIFTED_F4E0B9E_STACK = 84,
    LIFTED_F4E0BED_STACK = 72,
    LIFTED_F4E0BF8_STACK = 76,
    LIFTED_F4E0EAF_STACK = 64,
    LIFTED_F4E0EC7_STACK = 152,
    LIFTED_F4E0F8B_STACK = 76,
    LIFTED_F4E0FC0_STACK = 120,
    LIFTED_F4E105A_STACK = 64,
    LIFTED_F4E11B0_STACK = 92,
    LIFTED_F4E1210_STACK = 72,
    LIFTED_F4E1230_STACK = 80,
    LIFTED_F4E14A3_STACK = 72,
    LIFTED_F4E1590_STACK = 80,
    LIFTED_F4E2371_STACK = 68,
    LIFTED_F4E237D_STACK = 68,
    LIFTED_F4E2389_STACK = 76,
    LIFTED_F4E2420_STACK = 72,
    LIFTED_F4E2434_STACK = 104,
    LIFTED_F4E36C4_STACK = 68,
    LIFTED_F4E36D2_STACK = 68,
    LIFTED_F4E36E4_STACK = 76,
    LIFTED_F4E373E_STACK = 76,
    LIFTED_F4E3743_STACK = 76,
    LIFTED_F4E37FE_STACK = 68,
    LIFTED_F4E38FF_STACK = 84,
    LIFTED_F4E3BF0_STACK = 176,
    LIFTED_F4E3CE0_STACK = 112,
    LIFTED_F4E3F28_STACK = 88,
    LIFTED_F4E4080_STACK = 100,
    LIFTED_F4E4110_STACK = 160,
    LIFTED_F4E43C4_STACK = 80,
    LIFTED_F4E44C8_STACK = 92,
    LIFTED_F4E5024_STACK = 96,
    LIFTED_F4E506C_STACK = 84,
    LIFTED_F4E543C_STACK = 92,
    LIFTED_F4E5678_STACK = 88,
    LIFTED_F4E56A8_STACK = 104,
    LIFTED_F4E5700_STACK = 64,
    LIFTED_F4E571C_STACK = 88,
    LIFTED_F4E5738_STACK = 88,
    LIFTED_F4E5750_STACK = 76,
    LIFTED_F4E5774_STACK = 88,
    LIFTED_F4E5788_STACK = 88,
    LIFTED_F4E5808_STACK = 88,
    LIFTED_F4E5918_STACK = 100,
    LIFTED_F4E596C_STACK = 116,
    LIFTED_F4E5BEC_STACK = 72,
    LIFTED_F4E628C_STACK = 80,
    LIFTED_F4E62E0_STACK = 108,
    LIFTED_F4E6320_STACK = 120,
    LIFTED_F4E636C_STACK = 72,
    LIFTED_F4E64A0_STACK = 120,
    LIFTED_F4E6510_STACK = 160,
    LIFTED_F4E6600_STACK = 88,
    LIFTED_F4E6630_STACK = 124,
    LIFTED_F4E66A0_STACK = 100,
    LIFTED_F4E66DC_STACK = 76,
    LIFTED_F4E6734_STACK = 384,
    LIFTED_F4E6918_STACK = 116,
    LIFTED_F4E6B2C_STACK = 76,
    LIFTED_F4E6BFF_STACK = 72,
    LIFTED_F4E6C1D_STACK = 72,
    LIFTED_F4E6C98_STACK = 80,
    LIFTED_F4E6CD4_STACK = 68,
    LIFTED_F4E6CF2_STACK = 64,
    LIFTED_F4E6F60_STACK = 140,
    LIFTED_F4E70D0_STACK = 72,
    LIFTED_F4E7140_STACK = 72,
    LIFTED_F4E7280_STACK = 68,
    LIFTED_F4E7540_STACK = 104,
    LIFTED_F4E7BF0_STACK = 80,
    LIFTED_F4E7C30_STACK = 104,
    LIFTED_F4E7E44_STACK = 76,
    LIFTED_F4E7EB0_STACK = 88,
    LIFTED_F4E7EF4_STACK = 76,
    LIFTED_F4E7F0C_STACK = 64,
    LIFTED_F4E7FC4_STACK = 400,
    LIFTED_F4E81D0_STACK = 108,
    LIFTED_F4E82F0_STACK = 64,
    LIFTED_F4E8310_STACK = 68,
    LIFTED_F4E8330_STACK = 104,
    LIFTED_F4E8400_STACK = 92,
    LIFTED_F4E8574_STACK = 92,
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
    LIFTED_F4E8FA7_STACK = 84,
    LIFTED_F4E9020_STACK = 72,
    LIFTED_F4E909C_STACK = 128,
    LIFTED_F4E949C_STACK = 80,
    LIFTED_F4E9670_STACK = 72,
    LIFTED_F4E97B4_STACK = 116,
    LIFTED_F4E9D10_STACK = 76,
    LIFTED_F4E9F00_STACK = 84,
    LIFTED_F4E9F10_STACK = 144,
    LIFTED_F4EA0D0_STACK = 108,
    LIFTED_F4EA190_STACK = 92,
    LIFTED_F4EA2A8_STACK = 72,
    LIFTED_F4EA310_STACK = 64,
    LIFTED_F4EA350_STACK = 108,
    LIFTED_F4EA470_STACK = 128,
    LIFTED_F4EA540_STACK = 104,
    LIFTED_F4EA6A0_STACK = 72,
    LIFTED_F4EA6B0_STACK = 72,
    LIFTED_F4EAB80_STACK = 108,
    LIFTED_F4EB250_STACK = 72,
    LIFTED_F4EB4D4_STACK = 84,
    LIFTED_F4EB910_STACK = 92,
    LIFTED_F4EBA4C_STACK = 120,
    LIFTED_F4EBB34_STACK = 100,
    LIFTED_F4EBB78_STACK = 72
};

/* Original 0x4d6775. */
uint32_t lifted_rtl_integer_to_double(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6a30. */
uint32_t lifted_f4d6a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d70e0. */
uint32_t lifted_f4d70e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7140. */
uint32_t lifted_f4d7140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d73b0. */
uint32_t lifted_f4d73b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d73c0. */
uint32_t lifted_f4d73c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7400. */
uint32_t lifted_f4d7400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7430. */
uint32_t lifted_return_constant_4d73b0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7440. */
uint32_t lifted_f4d7440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7450. */
uint32_t lifted_f4d7450(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7460. */
uint32_t lifted_return_constant_4d73c0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7470. */
uint32_t lifted_return_constant_4d7400(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7480. */
uint32_t lifted_return_constant_4d25e0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7490. */
uint32_t lifted_return_constant_4d7140(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d74a0. */
uint32_t lifted_return_constant_4d7110(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8082. */
uint32_t lifted_rtl_sign_compare(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d80d5. */
uint32_t lifted_f4d80d5(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8198. */
uint32_t lifted_f4d8198(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8227. */
uint32_t lifted_rtl_single_divide_software_full(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x4d83f0. */
uint32_t lifted_f4d83f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8580. */
uint32_t lifted_rtl_wide_length(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d85a0. */
uint32_t lifted_f4d85a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d85c0. */
uint32_t lifted_f4d85c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8950. */
uint32_t lifted_f4d8950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8b30. */
uint32_t lifted_f4d8b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8b80. */
uint32_t lifted_object_destroy_g(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8c20. */
uint32_t lifted_node_pool_take_initialised(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9350. */
uint32_t lifted_f4d9350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9510. */
uint32_t lifted_rtl_static_init_call(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9530. */
uint32_t lifted_f4d9530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9930. */
uint32_t lifted_rtl_forward_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9ae0. */
uint32_t lifted_f4d9ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4da66e. */
uint32_t lifted_rtl_zero_call3(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4da6b6. */
uint32_t lifted_exception_chain_step(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4da71b. */
uint32_t lifted_f4da71b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dabe0. */
uint32_t lifted_rtl_stack_pair_call(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dac10. */
uint32_t lifted_f4dac10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4daca0. */
uint32_t lifted_f4daca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dacd0. */
uint32_t lifted_f4dacd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dacf8. */
uint32_t lifted_f4dacf8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dad2e. */
uint32_t lifted_rtl_ebx_from_edx_call(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dad38. */
uint32_t lifted_f4dad38(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dae4a. */
uint32_t lifted_rtl_negate_double(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dae70. */
uint32_t lifted_f4dae70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4daeb8. */
uint32_t lifted_f4daeb8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db131. */
uint32_t lifted_f4db131(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db950. */
uint32_t lifted_f4db950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db980. */
uint32_t lifted_f4db980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db9fc. */
uint32_t lifted_f4db9fc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dba20. */
uint32_t lifted_f4dba20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dbc60. */
uint32_t lifted_f4dbc60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc000. */
uint32_t lifted_f4dc000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc190. */
uint32_t lifted_f4dc190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc290. */
uint32_t lifted_f4dc290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc2f0. */
uint32_t lifted_f4dc2f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc420. */
uint32_t lifted_f4dc420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc4b0. */
uint32_t lifted_f4dc4b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd170. */
uint32_t lifted_rtl_record_set_argument(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd360. */
uint32_t lifted_rtl_construct_list(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd3e0. */
uint32_t lifted_f4dd3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd430. */
uint32_t lifted_f4dd430(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ddc30. */
uint32_t lifted_f4ddc30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ddc60. */
uint32_t lifted_rtl_release_list_head(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dde50. */
uint32_t lifted_f4dde50(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4dec60. */
uint32_t lifted_rtl_record_increment(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dec70. */
uint32_t lifted_f4dec70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4decd0. */
uint32_t lifted_rtl_construct_event_table(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ded70. */
uint32_t lifted_f4ded70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dee73. */
uint32_t lifted_rtl_segment_dispatch(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
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

/* Original 0x4df0d0. */
uint32_t lifted_f4df0d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df0f0. */
uint32_t lifted_f4df0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df140. */
uint32_t lifted_rtl_table_lookup_value(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df1c0. */
uint32_t lifted_f4df1c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dfa74. */
uint32_t lifted_f4dfa74(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e08a0. */
uint32_t lifted_f4e08a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0960. */
uint32_t lifted_f4e0960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0994. */
uint32_t lifted_f4e0994(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e09f0. */
uint32_t lifted_f4e09f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0a30. */
uint32_t lifted_f4e0a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0a95. */
uint32_t lifted_f4e0a95(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0ae5. */
uint32_t lifted_f4e0ae5(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e0eaf. */
uint32_t lifted_f4e0eaf(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0ec7. */
uint32_t lifted_f4e0ec7(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0f8b. */
uint32_t lifted_f4e0f8b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0fc0. */
uint32_t lifted_f4e0fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e105a. */
uint32_t lifted_f4e105a(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e11b0. */
uint32_t lifted_f4e11b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1210. */
uint32_t lifted_f4e1210(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1230. */
uint32_t lifted_f4e1230(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e14a3. */
uint32_t lifted_f4e14a3(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1590. */
uint32_t lifted_f4e1590(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e2420. */
uint32_t lifted_f4e2420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e2434. */
uint32_t lifted_f4e2434(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e3bf0. */
uint32_t lifted_f4e3bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3ce0. */
uint32_t lifted_f4e3ce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3f28. */
uint32_t lifted_f4e3f28(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e4080. */
uint32_t lifted_f4e4080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e4110. */
uint32_t lifted_f4e4110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e43c4. */
uint32_t lifted_f4e43c4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e44c8. */
uint32_t lifted_f4e44c8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5024. */
uint32_t lifted_f4e5024(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e506c. */
uint32_t lifted_f4e506c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e543c. */
uint32_t lifted_f4e543c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5678. */
uint32_t lifted_f4e5678(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e56a8. */
uint32_t lifted_f4e56a8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5700. */
uint32_t lifted_f4e5700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e571c. */
uint32_t lifted_f4e571c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5738. */
uint32_t lifted_f4e5738(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5750. */
uint32_t lifted_f4e5750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5774. */
uint32_t lifted_f4e5774(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5788. */
uint32_t lifted_f4e5788(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5808. */
uint32_t lifted_f4e5808(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5918. */
uint32_t lifted_f4e5918(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e596c. */
uint32_t lifted_f4e596c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5bec. */
uint32_t lifted_f4e5bec(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e628c. */
uint32_t lifted_f4e628c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e62e0. */
uint32_t lifted_f4e62e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6320. */
uint32_t lifted_f4e6320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e636c. */
uint32_t lifted_f4e636c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e64a0. */
uint32_t lifted_f4e64a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6510. */
uint32_t lifted_f4e6510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6600. */
uint32_t lifted_f4e6600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6630. */
uint32_t lifted_f4e6630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e66a0. */
uint32_t lifted_f4e66a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e66dc. */
uint32_t lifted_f4e66dc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6734. */
uint32_t lifted_f4e6734(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6918. */
uint32_t lifted_f4e6918(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e6f60. */
uint32_t lifted_f4e6f60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e70d0. */
uint32_t lifted_f4e70d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e7fc4. */
uint32_t lifted_f4e7fc4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e81d0. */
uint32_t lifted_f4e81d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e8fa7. */
uint32_t lifted_f4e8fa7(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9020. */
uint32_t lifted_f4e9020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e909c. */
uint32_t lifted_f4e909c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e949c. */
uint32_t lifted_f4e949c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9670. */
uint32_t lifted_f4e9670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e97b4. */
uint32_t lifted_f4e97b4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9d10. */
uint32_t lifted_f4e9d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9f00. */
uint32_t lifted_f4e9f00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9f10. */
uint32_t lifted_f4e9f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea0d0. */
uint32_t lifted_f4ea0d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ea470. */
uint32_t lifted_f4ea470(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4eab80. */
uint32_t lifted_f4eab80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb250. */
uint32_t lifted_f4eb250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eb4d4. */
uint32_t lifted_f4eb4d4(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

#endif
