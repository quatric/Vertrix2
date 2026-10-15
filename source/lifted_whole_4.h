#ifndef VERTRIX_LIFTED_WHOLE_4_H
#define VERTRIX_LIFTED_WHOLE_4_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F47FA40_STACK = 116,
    LIFTED_F47FA90_STACK = 124,
    LIFTED_OBJECT_SET_TEXT_STACK = 96,
    LIFTED_F47FC10_STACK = 100,
    LIFTED_F47FE80_STACK = 96,
    LIFTED_F480940_STACK = 92,
    LIFTED_F480D60_STACK = 280,
    LIFTED_RLE_DECODE_STACK = 112,
    LIFTED_RLE_DECODE_BITMAP_STACK = 108,
    LIFTED_OBJECT_CREATE_WITH_CLASS_STACK = 128,
    LIFTED_EVENT_STACK_POP_STACK = 76,
    LIFTED_F4831B0_STACK = 204,
    LIFTED_F484530_STACK = 72,
    LIFTED_F485700_STACK = 476,
    LIFTED_F4871D0_STACK = 232,
    LIFTED_F487BE0_STACK = 176,
    LIFTED_F488050_STACK = 88,
    LIFTED_PATH_LAST_SEPARATOR_STACK = 68,
    LIFTED_PATH_IS_NETWORK_STACK = 68,
    LIFTED_F489170_STACK = 204,
    LIFTED_F489230_STACK = 208,
    LIFTED_RTL_WRITE_TEXT_CALL_STACK = 100,
    LIFTED_FIND_ATTRIBUTE_FLAG_STACK = 368,
    LIFTED_F489A10_STACK = 216,
    LIFTED_F48A100_STACK = 212,
    LIFTED_F48A710_STACK = 192,
    LIFTED_F48AC50_STACK = 408,
    LIFTED_F48AD00_STACK = 464,
    LIFTED_F48AE00_STACK = 932,
    LIFTED_F48B7E0_STACK = 292,
    LIFTED_F48BCA0_STACK = 124,
    LIFTED_F48BE70_STACK = 124,
    LIFTED_F48C0F0_STACK = 140,
    LIFTED_F48C4A0_STACK = 184,
    LIFTED_F48C6C0_STACK = 208,
    LIFTED_F48C860_STACK = 2528,
    LIFTED_F48C970_STACK = 120,
    LIFTED_F48CA20_STACK = 356,
    LIFTED_F48CC30_STACK = 740,
    LIFTED_F4ACD30_STACK = 80,
    LIFTED_ACTOR_TURN_TOWARD_STACK = 84,
    LIFTED_F4B0B70_STACK = 136,
    LIFTED_F4B2A00_STACK = 340,
    LIFTED_F4B2D90_STACK = 300,
    LIFTED_OBJECT_SET_PAIR_4B35B0_STACK = 64,
    LIFTED_F4B3A00_STACK = 212,
    LIFTED_F4B3FB0_STACK = 68,
    LIFTED_F4B4CF0_STACK = 252,
    LIFTED_F4B50D0_STACK = 112,
    LIFTED_F4B5700_STACK = 208,
    LIFTED_F4B58A0_STACK = 196
};

/* Original 0x47fa40. */
uint32_t lifted_f47fa40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47fa90. */
uint32_t lifted_f47fa90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47faf0. */
uint32_t lifted_object_set_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47fc10. */
uint32_t lifted_f47fc10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47fe80. */
uint32_t lifted_f47fe80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480940. */
uint32_t lifted_f480940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480d60. */
uint32_t lifted_f480d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481480. */
uint32_t lifted_rle_decode(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481580. */
uint32_t lifted_rle_decode_bitmap(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481f30. */
uint32_t lifted_object_create_with_class(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482110. */
uint32_t lifted_event_stack_pop(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4831b0. */
uint32_t lifted_f4831b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x484530. */
uint32_t lifted_f484530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x485700. */
uint32_t lifted_f485700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4871d0. */
uint32_t lifted_f4871d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487be0. */
uint32_t lifted_f487be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488050. */
uint32_t lifted_f488050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4885a0. */
uint32_t lifted_path_last_separator(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488940. */
uint32_t lifted_path_is_network(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489170. */
uint32_t lifted_f489170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489230. */
uint32_t lifted_f489230(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489470. */
uint32_t lifted_rtl_write_text_call(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4895b0. */
uint32_t lifted_find_attribute_flag(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489a10. */
uint32_t lifted_f489a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a100. */
uint32_t lifted_f48a100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48a710. */
uint32_t lifted_f48a710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48ac50. */
uint32_t lifted_f48ac50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48ad00. */
uint32_t lifted_f48ad00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48ae00. */
uint32_t lifted_f48ae00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48b7e0. */
uint32_t lifted_f48b7e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48bca0. */
uint32_t lifted_f48bca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48be70. */
uint32_t lifted_f48be70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c0f0. */
uint32_t lifted_f48c0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c4a0. */
uint32_t lifted_f48c4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c6c0. */
uint32_t lifted_f48c6c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c860. */
uint32_t lifted_f48c860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c970. */
uint32_t lifted_f48c970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48ca20. */
uint32_t lifted_f48ca20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48cc30. */
uint32_t lifted_f48cc30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4acd30. */
uint32_t lifted_f4acd30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ace40. */
uint32_t lifted_actor_turn_toward(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b0b70. */
uint32_t lifted_f4b0b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b2a00. */
uint32_t lifted_f4b2a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b2d90. */
uint32_t lifted_f4b2d90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b35b0. */
uint32_t lifted_object_set_pair_4b35b0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3a00. */
uint32_t lifted_f4b3a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3fb0. */
uint32_t lifted_f4b3fb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4cf0. */
uint32_t lifted_f4b4cf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b50d0. */
uint32_t lifted_f4b50d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5700. */
uint32_t lifted_f4b5700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b58a0. */
uint32_t lifted_f4b58a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
