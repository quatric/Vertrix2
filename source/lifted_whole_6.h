#ifndef VERTRIX_LIFTED_WHOLE_6_H
#define VERTRIX_LIFTED_WHOLE_6_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4D6A30_STACK = 80,
    LIFTED_F4D7140_STACK = 128,
    LIFTED_F4D73B0_STACK = 120,
    LIFTED_RTL_SIGN_COMPARE_STACK = 64,
    LIFTED_F4D80D5_STACK = 84,
    LIFTED_F4D8198_STACK = 80,
    LIFTED_RTL_SINGLE_DIVIDE_SOFTWARE_FULL_STACK = 88,
    LIFTED_F4D83F0_STACK = 136,
    LIFTED_F4D85C0_STACK = 80,
    LIFTED_F4D8950_STACK = 80,
    LIFTED_OBJECT_DESTROY_G_STACK = 136,
    LIFTED_NODE_POOL_TAKE_INITIALISED_STACK = 104,
    LIFTED_RTL_STATIC_INIT_CALL_STACK = 72,
    LIFTED_F4D9530_STACK = 72,
    LIFTED_F4D9AE0_STACK = 64,
    LIFTED_RTL_ZERO_CALL3_STACK = 100,
    LIFTED_EXCEPTION_CHAIN_STEP_STACK = 128,
    LIFTED_F4DA71B_STACK = 100,
    LIFTED_RTL_STACK_PAIR_CALL_STACK = 80,
    LIFTED_F4DAC10_STACK = 80,
    LIFTED_F4DACD0_STACK = 96,
    LIFTED_F4DACF8_STACK = 80,
    LIFTED_F4DAD38_STACK = 116,
    LIFTED_F4DB131_STACK = 88,
    LIFTED_F4DB950_STACK = 92,
    LIFTED_F4DB980_STACK = 100,
    LIFTED_F4DB9FC_STACK = 100,
    LIFTED_F4DC290_STACK = 116,
    LIFTED_F4DC2F0_STACK = 184,
    LIFTED_F4DC4B0_STACK = 96,
    LIFTED_F4DD430_STACK = 112,
    LIFTED_F4DD4A0_STACK = 152,
    LIFTED_F4DDC30_STACK = 112,
    LIFTED_RTL_RELEASE_LIST_HEAD_STACK = 84,
    LIFTED_F4DDE50_STACK = 72,
    LIFTED_RTL_SEGMENT_DISPATCH_STACK = 84,
    LIFTED_F4DEFD0_STACK = 136,
    LIFTED_RTL_TABLE_LOOKUP_VALUE_STACK = 76,
    LIFTED_F4E0430_STACK = 120,
    LIFTED_F4E0508_STACK = 156,
    LIFTED_F4E08A0_STACK = 72,
    LIFTED_F4E0AE5_STACK = 104,
    LIFTED_F4E0B9E_STACK = 84,
    LIFTED_F4E0EC7_STACK = 152,
    LIFTED_F4E0F8B_STACK = 76,
    LIFTED_F4E105A_STACK = 64,
    LIFTED_F4E1230_STACK = 80,
    LIFTED_F4E1590_STACK = 80,
    LIFTED_F4E2371_STACK = 68,
    LIFTED_F4E237D_STACK = 68,
    LIFTED_F4E2389_STACK = 76,
    LIFTED_F4E2434_STACK = 104,
    LIFTED_F4E373E_STACK = 76,
    LIFTED_F4E3CE0_STACK = 112,
    LIFTED_F4E4110_STACK = 160,
    LIFTED_F4E43C4_STACK = 80,
    LIFTED_F4E44C8_STACK = 92,
    LIFTED_F4E506C_STACK = 84,
    LIFTED_F4E543C_STACK = 92,
    LIFTED_F4E571C_STACK = 88,
    LIFTED_F4E5738_STACK = 88,
    LIFTED_F4E5774_STACK = 88,
    LIFTED_F4E5788_STACK = 88,
    LIFTED_F4E5808_STACK = 88,
    LIFTED_F4E5BEC_STACK = 72,
    LIFTED_F4E628C_STACK = 80,
    LIFTED_F4E62E0_STACK = 108,
    LIFTED_F4E6734_STACK = 384,
    LIFTED_F4E6918_STACK = 116,
    LIFTED_F4E6B2C_STACK = 76,
    LIFTED_F4E6C98_STACK = 80,
    LIFTED_F4E6F60_STACK = 140,
    LIFTED_F4E7C30_STACK = 104,
    LIFTED_F4E7FC4_STACK = 400,
    LIFTED_F4E81D0_STACK = 108,
    LIFTED_F4E8330_STACK = 104,
    LIFTED_F4E8650_STACK = 84,
    LIFTED_F4E8660_STACK = 92,
    LIFTED_F4E88BF_STACK = 76,
    LIFTED_F4E8CC8_STACK = 104,
    LIFTED_F4E8FA7_STACK = 84,
    LIFTED_F4E909C_STACK = 128,
    LIFTED_F4E949C_STACK = 80,
    LIFTED_F4E97B4_STACK = 116,
    LIFTED_F4E9D10_STACK = 76,
    LIFTED_F4E9F00_STACK = 84,
    LIFTED_F4E9F10_STACK = 144,
    LIFTED_F4EA0D0_STACK = 108,
    LIFTED_F4EA190_STACK = 92,
    LIFTED_F4EA350_STACK = 108,
    LIFTED_F4EA470_STACK = 128,
    LIFTED_F4EA540_STACK = 104,
    LIFTED_F4EA6B0_STACK = 72,
    LIFTED_F4EAB80_STACK = 108,
    LIFTED_F4EB250_STACK = 72,
    LIFTED_F4EB4D4_STACK = 84,
    LIFTED_F4EB910_STACK = 92,
    LIFTED_F4EBA4C_STACK = 120,
    LIFTED_F4EBB34_STACK = 100,
    LIFTED_F4EBB78_STACK = 72
};

/* Original 0x4d6a30. */
uint32_t lifted_f4d6a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7140. */
uint32_t lifted_f4d7140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d73b0. */
uint32_t lifted_f4d73b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4d85c0. */
uint32_t lifted_f4d85c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8950. */
uint32_t lifted_f4d8950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8b80. */
uint32_t lifted_object_destroy_g(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8c20. */
uint32_t lifted_node_pool_take_initialised(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9510. */
uint32_t lifted_rtl_static_init_call(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9530. */
uint32_t lifted_f4d9530(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4dacd0. */
uint32_t lifted_f4dacd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dacf8. */
uint32_t lifted_f4dacf8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dad38. */
uint32_t lifted_f4dad38(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4dc290. */
uint32_t lifted_f4dc290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc2f0. */
uint32_t lifted_f4dc2f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc4b0. */
uint32_t lifted_f4dc4b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd430. */
uint32_t lifted_f4dd430(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd4a0. */
uint32_t lifted_f4dd4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4dee73. */
uint32_t lifted_rtl_segment_dispatch(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4defd0. */
uint32_t lifted_f4defd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df140. */
uint32_t lifted_rtl_table_lookup_value(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0430. */
uint32_t lifted_f4e0430(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0508. */
uint32_t lifted_f4e0508(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e08a0. */
uint32_t lifted_f4e08a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0ae5. */
uint32_t lifted_f4e0ae5(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0b9e. */
uint32_t lifted_f4e0b9e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0ec7. */
uint32_t lifted_f4e0ec7(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0f8b. */
uint32_t lifted_f4e0f8b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e105a. */
uint32_t lifted_f4e105a(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1230. */
uint32_t lifted_f4e1230(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e2434. */
uint32_t lifted_f4e2434(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e373e. */
uint32_t lifted_f4e373e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3ce0. */
uint32_t lifted_f4e3ce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e506c. */
uint32_t lifted_f4e506c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e543c. */
uint32_t lifted_f4e543c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e571c. */
uint32_t lifted_f4e571c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5738. */
uint32_t lifted_f4e5738(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e5bec. */
uint32_t lifted_f4e5bec(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e628c. */
uint32_t lifted_f4e628c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e62e0. */
uint32_t lifted_f4e62e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4e6c98. */
uint32_t lifted_f4e6c98(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6f60. */
uint32_t lifted_f4e6f60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7c30. */
uint32_t lifted_f4e7c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7fc4. */
uint32_t lifted_f4e7fc4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e81d0. */
uint32_t lifted_f4e81d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8330. */
uint32_t lifted_f4e8330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8650. */
uint32_t lifted_f4e8650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8660. */
uint32_t lifted_f4e8660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e88bf. */
uint32_t lifted_f4e88bf(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8cc8. */
uint32_t lifted_f4e8cc8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8fa7. */
uint32_t lifted_f4e8fa7(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e909c. */
uint32_t lifted_f4e909c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e949c. */
uint32_t lifted_f4e949c(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4ea350. */
uint32_t lifted_f4ea350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea470. */
uint32_t lifted_f4ea470(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea540. */
uint32_t lifted_f4ea540(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
