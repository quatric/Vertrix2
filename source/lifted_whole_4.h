#ifndef VERTRIX_LIFTED_WHOLE_4_H
#define VERTRIX_LIFTED_WHOLE_4_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_OBJECT_SET_TEXT_STACK = 96,
    LIFTED_F480D60_STACK = 280,
    LIFTED_RLE_DECODE_BITMAP_STACK = 108,
    LIFTED_F485700_STACK = 476,
    LIFTED_F487BE0_STACK = 176,
    LIFTED_PATH_LAST_SEPARATOR_STACK = 68,
    LIFTED_RTL_WRITE_TEXT_CALL_STACK = 100,
    LIFTED_F489A10_STACK = 216,
    LIFTED_F48AC50_STACK = 408,
    LIFTED_F48AD00_STACK = 464,
    LIFTED_F48AE00_STACK = 932,
    LIFTED_F48BE70_STACK = 124,
    LIFTED_F48C4A0_STACK = 184,
    LIFTED_F48C860_STACK = 2528,
    LIFTED_F48CC30_STACK = 740,
    LIFTED_F4B0B70_STACK = 136,
    LIFTED_F4B2A00_STACK = 340,
    LIFTED_F4B2D90_STACK = 300,
    LIFTED_F4B4CF0_STACK = 252,
    LIFTED_F4B58A0_STACK = 196
};

/* Original 0x47faf0. */
uint32_t lifted_object_set_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480d60. */
uint32_t lifted_f480d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x481580. */
uint32_t lifted_rle_decode_bitmap(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x485700. */
uint32_t lifted_f485700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487be0. */
uint32_t lifted_f487be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4885a0. */
uint32_t lifted_path_last_separator(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489470. */
uint32_t lifted_rtl_write_text_call(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489a10. */
uint32_t lifted_f489a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x48be70. */
uint32_t lifted_f48be70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c4a0. */
uint32_t lifted_f48c4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c860. */
uint32_t lifted_f48c860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48cc30. */
uint32_t lifted_f48cc30(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4b4cf0. */
uint32_t lifted_f4b4cf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b58a0. */
uint32_t lifted_f4b58a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
