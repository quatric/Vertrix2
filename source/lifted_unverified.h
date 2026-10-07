#ifndef VERTRIX_LIFTED_UNVERIFIED_H
#define VERTRIX_LIFTED_UNVERIFIED_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F418270_STACK = 100,
    LIFTED_F41A040_STACK = 84,
    LIFTED_F42A200_STACK = 120,
    LIFTED_PLAYER_MODE_IN_GROUP_A_STACK = 64,
    LIFTED_PLAYER_MODE_IN_GROUP_B_STACK = 64,
    LIFTED_FONT_MEASURE_STACK = 264,
    LIFTED_TEXT_LAYOUT_STACK = 72,
    LIFTED_OBJECT_CORNER_CALL_STACK = 164,
    LIFTED_F45DCA0_STACK = 660,
    LIFTED_F4726D0_STACK = 428,
    LIFTED_F47C520_STACK = 240,
    LIFTED_F485550_STACK = 292,
    LIFTED_F486DA0_STACK = 84,
    LIFTED_F4873D0_STACK = 420,
    LIFTED_ARRAY_LIST_BUILD_STACK = 128,
    LIFTED_FIND_SUCCEEDED_STACK = 368,
    LIFTED_F4AA660_STACK = 92,
    LIFTED_F4AA950_STACK = 88,
    LIFTED_F4AABE0_STACK = 92,
    LIFTED_ACTOR_GATE_STACK = 128,
    LIFTED_ACTOR_CHAIN_PAINT_STACK = 76,
    LIFTED_F4B17E0_STACK = 108,
    LIFTED_F4B6240_STACK = 84,
    LIFTED_OBJECT_CONSTRUCT_LABELED_BOX_STACK = 136,
    LIFTED_OBJECT_LABEL_TEXT_STACK = 128,
    LIFTED_F4B68A0_STACK = 136,
    LIFTED_F4CA5A0_STACK = 96,
    LIFTED_F4CCF3B_STACK = 120,
    LIFTED_F4CDBE0_STACK = 192,
    LIFTED_F4CDFB0_STACK = 80,
    LIFTED_F4CE740_STACK = 220,
    LIFTED_F4D7C40_STACK = 564,
    LIFTED_F4D9060_STACK = 448,
    LIFTED_RTL_STATIC_INIT_CALL_STACK = 72,
    LIFTED_RTL_JUMP_CAPTURE_STACK = 72,
    LIFTED_F4DBB30_STACK = 192,
    LIFTED_F4DBD20_STACK = 192,
    LIFTED_F4DF320_STACK = 248,
    LIFTED_F4DFAC0_STACK = 92,
    LIFTED_F4DFB24_STACK = 168
};

/* Original 0x418270. */
uint32_t lifted_f418270(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a040. */
uint32_t lifted_f41a040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a200. */
uint32_t lifted_f42a200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d3b0. */
uint32_t lifted_player_mode_in_group_a(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d3d0. */
uint32_t lifted_player_mode_in_group_b(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x440610. */
uint32_t lifted_font_measure(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x440990. */
uint32_t lifted_text_layout(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x440ca0. */
uint32_t lifted_object_corner_call(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45dca0. */
uint32_t lifted_f45dca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4726d0. */
uint32_t lifted_f4726d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47c520. */
uint32_t lifted_f47c520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x485550. */
uint32_t lifted_f485550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x486da0. */
uint32_t lifted_f486da0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4873d0. */
uint32_t lifted_f4873d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4875a0. */
uint32_t lifted_array_list_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4895e0. */
uint32_t lifted_find_succeeded(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aa660. */
uint32_t lifted_f4aa660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aa950. */
uint32_t lifted_f4aa950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4aabe0. */
uint32_t lifted_f4aabe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ae3e0. */
uint32_t lifted_actor_gate(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4af8c0. */
uint32_t lifted_actor_chain_paint(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b17e0. */
uint32_t lifted_f4b17e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6240. */
uint32_t lifted_f4b6240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6350. */
uint32_t lifted_object_construct_labeled_box(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b65d0. */
uint32_t lifted_object_label_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b68a0. */
uint32_t lifted_f4b68a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ca5a0. */
uint32_t lifted_f4ca5a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccf3b. */
uint32_t lifted_f4ccf3b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cdbe0. */
uint32_t lifted_f4cdbe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cdfb0. */
uint32_t lifted_f4cdfb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce740. */
uint32_t lifted_f4ce740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d7c40. */
uint32_t lifted_f4d7c40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9060. */
uint32_t lifted_f4d9060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9510. */
uint32_t lifted_rtl_static_init_call(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d9f06. */
uint32_t lifted_rtl_jump_capture(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dbb30. */
uint32_t lifted_f4dbb30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dbd20. */
uint32_t lifted_f4dbd20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df320. */
uint32_t lifted_f4df320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dfac0. */
uint32_t lifted_f4dfac0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dfb24. */
uint32_t lifted_f4dfb24(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
