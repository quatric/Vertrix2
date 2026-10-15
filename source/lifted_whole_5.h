#ifndef VERTRIX_LIFTED_WHOLE_5_H
#define VERTRIX_LIFTED_WHOLE_5_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4B7020_STACK = 100,
    LIFTED_WAVE_LOAD_STACK = 164,
    LIFTED_F4B826F_STACK = 436,
    LIFTED_F4B99B0_STACK = 100,
    LIFTED_F4B9CB0_STACK = 84,
    LIFTED_F4BB040_STACK = 128,
    LIFTED_F4BB3D0_STACK = 100,
    LIFTED_F4BB470_STACK = 88,
    LIFTED_F4BC6C0_STACK = 84,
    LIFTED_F4BCEA0_STACK = 144,
    LIFTED_F4BD210_STACK = 84,
    LIFTED_F4BD9E0_STACK = 212,
    LIFTED_F4BE0B0_STACK = 160,
    LIFTED_F4BEF10_STACK = 108,
    LIFTED_F4C0860_STACK = 112,
    LIFTED_F4C2000_STACK = 132,
    LIFTED_F4C31A0_STACK = 88,
    LIFTED_F4C3320_STACK = 104,
    LIFTED_F4C3780_STACK = 112,
    LIFTED_F4C3950_STACK = 92,
    LIFTED_F4C3BE0_STACK = 140,
    LIFTED_F4C3E60_STACK = 296,
    LIFTED_F4C4000_STACK = 408,
    LIFTED_F4C4730_STACK = 244,
    LIFTED_F4C5400_STACK = 120,
    LIFTED_F4C54D0_STACK = 120,
    LIFTED_F4C58E0_STACK = 116,
    LIFTED_F4C63A0_STACK = 108,
    LIFTED_F4C6460_STACK = 100,
    LIFTED_F4C6A20_STACK = 136,
    LIFTED_F4C70F0_STACK = 268,
    LIFTED_F4C8500_STACK = 2200,
    LIFTED_F4C8BE0_STACK = 120,
    LIFTED_F4C9550_STACK = 116,
    LIFTED_RTL_COPY_ROWS_STACK = 88,
    LIFTED_F4CA040_STACK = 92,
    LIFTED_F4CA050_STACK = 92,
    LIFTED_RTL_STRING_COPY_PAIR_STACK = 84,
    LIFTED_F4CB5A0_STACK = 196,
    LIFTED_RTL_RECORD_FIELD_STACK = 68,
    LIFTED_F4CC0D0_STACK = 148,
    LIFTED_F4CC450_STACK = 108,
    LIFTED_F4CC7A0_STACK = 92,
    LIFTED_RTL_BLOCK_CALL_STACK = 80,
    LIFTED_F4CCD80_STACK = 120,
    LIFTED_RTL_TERMINATE_CALL_STACK = 76,
    LIFTED_RTL_VARARG_CALL_STACK = 84,
    LIFTED_F4CD56C_STACK = 244,
    LIFTED_F4CD7DC_STACK = 84,
    LIFTED_RTL_LOCAL_CALL_STACK = 92,
    LIFTED_RTL_STRING_FILL_STACK = 88,
    LIFTED_F4CDBE0_STACK = 192,
    LIFTED_F4CDFB0_STACK = 80,
    LIFTED_F4CF4A0_STACK = 80,
    LIFTED_F4CF4D0_STACK = 132,
    LIFTED_F4CF800_STACK = 96,
    LIFTED_F4CF8D0_STACK = 112,
    LIFTED_F4CF910_STACK = 80,
    LIFTED_F4CF9D0_STACK = 96,
    LIFTED_F4CFA20_STACK = 408,
    LIFTED_F4CFC90_STACK = 120,
    LIFTED_F4CFF20_STACK = 112,
    LIFTED_F4D01A0_STACK = 152,
    LIFTED_F4D05E0_STACK = 100,
    LIFTED_F4D0620_STACK = 92,
    LIFTED_F4D0670_STACK = 80,
    LIFTED_F4D06A0_STACK = 80,
    LIFTED_F4D0740_STACK = 128,
    LIFTED_F4D1710_STACK = 160,
    LIFTED_F4D1840_STACK = 108,
    LIFTED_F4D1890_STACK = 124,
    LIFTED_F4D21D0_STACK = 144,
    LIFTED_F4D23F0_STACK = 92,
    LIFTED_F4D2460_STACK = 136,
    LIFTED_F4D2540_STACK = 136,
    LIFTED_F4D3040_STACK = 172,
    LIFTED_F4D4300_STACK = 64,
    LIFTED_RTL_ANCESTOR_SEARCH_STACK = 76,
    LIFTED_F4D4700_STACK = 196,
    LIFTED_F4D49A0_STACK = 104,
    LIFTED_F4D4E60_STACK = 104,
    LIFTED_F4D51C0_STACK = 412,
    LIFTED_F4D5390_STACK = 136,
    LIFTED_F4D5930_STACK = 152,
    LIFTED_F4D5AB0_STACK = 472,
    LIFTED_F4D5BF8_STACK = 92,
    LIFTED_F4D5C70_STACK = 92,
    LIFTED_F4D6080_STACK = 100
};

/* Original 0x4b7020. */
uint32_t lifted_f4b7020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7e80. */
uint32_t lifted_wave_load(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b826f. */
uint32_t lifted_f4b826f(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b99b0. */
uint32_t lifted_f4b99b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b9cb0. */
uint32_t lifted_f4b9cb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bb040. */
uint32_t lifted_f4bb040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bb3d0. */
uint32_t lifted_f4bb3d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bb470. */
uint32_t lifted_f4bb470(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bc6c0. */
uint32_t lifted_f4bc6c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bcea0. */
uint32_t lifted_f4bcea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bd210. */
uint32_t lifted_f4bd210(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bd9e0. */
uint32_t lifted_f4bd9e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4be0b0. */
uint32_t lifted_f4be0b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bef10. */
uint32_t lifted_f4bef10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c0860. */
uint32_t lifted_f4c0860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c2000. */
uint32_t lifted_f4c2000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c31a0. */
uint32_t lifted_f4c31a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3320. */
uint32_t lifted_f4c3320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3780. */
uint32_t lifted_f4c3780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3950. */
uint32_t lifted_f4c3950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3be0. */
uint32_t lifted_f4c3be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c3e60. */
uint32_t lifted_f4c3e60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c4000. */
uint32_t lifted_f4c4000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c4730. */
uint32_t lifted_f4c4730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5400. */
uint32_t lifted_f4c5400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c54d0. */
uint32_t lifted_f4c54d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c58e0. */
uint32_t lifted_f4c58e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c63a0. */
uint32_t lifted_f4c63a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c6460. */
uint32_t lifted_f4c6460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c6a20. */
uint32_t lifted_f4c6a20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c70f0. */
uint32_t lifted_f4c70f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c8500. */
uint32_t lifted_f4c8500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c8be0. */
uint32_t lifted_f4c8be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9550. */
uint32_t lifted_f4c9550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c9860. */
uint32_t lifted_rtl_copy_rows(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca040. */
uint32_t lifted_f4ca040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca050. */
uint32_t lifted_f4ca050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca240. */
uint32_t lifted_rtl_string_copy_pair(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb5a0. */
uint32_t lifted_f4cb5a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cbe80. */
uint32_t lifted_rtl_record_field(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc0d0. */
uint32_t lifted_f4cc0d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc450. */
uint32_t lifted_f4cc450(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cc7a0. */
uint32_t lifted_f4cc7a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccb9f. */
uint32_t lifted_rtl_block_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccd80. */
uint32_t lifted_f4ccd80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd0a4. */
uint32_t lifted_rtl_terminate_call(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd544. */
uint32_t lifted_rtl_vararg_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd56c. */
uint32_t lifted_f4cd56c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd7dc. */
uint32_t lifted_f4cd7dc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd9f0. */
uint32_t lifted_rtl_local_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cda90. */
uint32_t lifted_rtl_string_fill(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cdbe0. */
uint32_t lifted_f4cdbe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cdfb0. */
uint32_t lifted_f4cdfb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf4a0. */
uint32_t lifted_f4cf4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf4d0. */
uint32_t lifted_f4cf4d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf800. */
uint32_t lifted_f4cf800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf8d0. */
uint32_t lifted_f4cf8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf910. */
uint32_t lifted_f4cf910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf9d0. */
uint32_t lifted_f4cf9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cfa20. */
uint32_t lifted_f4cfa20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cfc90. */
uint32_t lifted_f4cfc90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cff20. */
uint32_t lifted_f4cff20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d01a0. */
uint32_t lifted_f4d01a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d05e0. */
uint32_t lifted_f4d05e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d0620. */
uint32_t lifted_f4d0620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d0670. */
uint32_t lifted_f4d0670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d06a0. */
uint32_t lifted_f4d06a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d0740. */
uint32_t lifted_f4d0740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1710. */
uint32_t lifted_f4d1710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1840. */
uint32_t lifted_f4d1840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d1890. */
uint32_t lifted_f4d1890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d21d0. */
uint32_t lifted_f4d21d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d23f0. */
uint32_t lifted_f4d23f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2460. */
uint32_t lifted_f4d2460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d2540. */
uint32_t lifted_f4d2540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d3040. */
uint32_t lifted_f4d3040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4300. */
uint32_t lifted_f4d4300(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4390. */
uint32_t lifted_rtl_ancestor_search(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4700. */
uint32_t lifted_f4d4700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d49a0. */
uint32_t lifted_f4d49a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4e60. */
uint32_t lifted_f4d4e60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d51c0. */
uint32_t lifted_f4d51c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5390. */
uint32_t lifted_f4d5390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5930. */
uint32_t lifted_f4d5930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5ab0. */
uint32_t lifted_f4d5ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5bf8. */
uint32_t lifted_f4d5bf8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5c70. */
uint32_t lifted_f4d5c70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6080. */
uint32_t lifted_f4d6080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
