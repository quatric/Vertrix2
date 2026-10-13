#ifndef VERTRIX_LIFTED_WHOLE_4_H
#define VERTRIX_LIFTED_WHOLE_4_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_OBJECT_WRITE_18_STACK = 64,
    LIFTED_RETURN_UNCHANGED_47F8F0_STACK = 64,
    LIFTED_CHECKED_CALLS_STACK = 84,
    LIFTED_F47F9E0_STACK = 88,
    LIFTED_F47FA20_STACK = 76,
    LIFTED_F47FA40_STACK = 116,
    LIFTED_F47FA90_STACK = 124,
    LIFTED_OBJECT_SET_TEXT_STACK = 96,
    LIFTED_F47FC10_STACK = 100,
    LIFTED_F47FC50_STACK = 108,
    LIFTED_F47FCE0_STACK = 68,
    LIFTED_DISPLAY_NOTIFY_STACK = 96,
    LIFTED_F47FE50_STACK = 96,
    LIFTED_F47FE80_STACK = 96,
    LIFTED_F480030_STACK = 104,
    LIFTED_PALETTE_EXPAND_VGA_STACK = 80,
    LIFTED_F4808F0_STACK = 104,
    LIFTED_F480940_STACK = 92,
    LIFTED_F480D60_STACK = 280,
    LIFTED_RLE_DECODE_STACK = 112,
    LIFTED_RLE_DECODE_BITMAP_STACK = 108,
    LIFTED_OBJECT_CREATE_WITH_CLASS_STACK = 128,
    LIFTED_OBJECT_DESTROY_B_STACK = 156,
    LIFTED_OBJECT_CLEAR_208_STACK = 64,
    LIFTED_EVENT_STACK_PUSH_STACK = 72,
    LIFTED_EVENT_STACK_POP_STACK = 76,
    LIFTED_F4823B0_STACK = 104,
    LIFTED_FORWARD_FIRST_DWORD_STACK = 68,
    LIFTED_F482770_STACK = 72,
    LIFTED_F4828A0_STACK = 84,
    LIFTED_F4829C0_STACK = 84,
    LIFTED_CALL_UNLESS_ZERO_STACK = 68,
    LIFTED_F4831B0_STACK = 204,
    LIFTED_F4844B0_STACK = 100,
    LIFTED_F484500_STACK = 80,
    LIFTED_F484530_STACK = 72,
    LIFTED_F4848F0_STACK = 672,
    LIFTED_F485700_STACK = 476,
    LIFTED_F486ED0_STACK = 292,
    LIFTED_F487060_STACK = 88,
    LIFTED_F487080_STACK = 232,
    LIFTED_F487130_STACK = 256,
    LIFTED_F4871D0_STACK = 232,
    LIFTED_FORWARD_CALL_STACK = 68,
    LIFTED_ARRAY_LIST_RELEASE_STACK = 104,
    LIFTED_TABLE_OBJECT_CONSTRUCT_STACK = 68,
    LIFTED_F487920_STACK = 68,
    LIFTED_LIST_EMPTY_STACK = 64,
    LIFTED_OBJECT_RELEASE_CALL_STACK = 80,
    LIFTED_FORWARD_REGISTERS_487A10_STACK = 72,
    LIFTED_LIST_ITEM_STACK = 68,
    LIFTED_OBJECT_CONSTRUCT_G_STACK = 68,
    LIFTED_F487BE0_STACK = 176,
    LIFTED_LIST_FIND_NAME_STACK = 92,
    LIFTED_TABLE_ITEM_STACK = 64,
    LIFTED_TABLE_ITEM_488040_STACK = 64,
    LIFTED_F488050_STACK = 88,
    LIFTED_PATH_LAST_SEPARATOR_STACK = 68,
    LIFTED_PATH_IS_NETWORK_STACK = 68,
    LIFTED_F489170_STACK = 204,
    LIFTED_F489230_STACK = 208,
    LIFTED_F4893C0_STACK = 136,
    LIFTED_RTL_WRITE_TEXT_CALL_STACK = 100,
    LIFTED_FIND_ATTRIBUTE_FLAG_STACK = 368,
    LIFTED_F489A10_STACK = 216,
    LIFTED_F489B20_STACK = 76,
    LIFTED_F489FA0_STACK = 160,
    LIFTED_F48A100_STACK = 212,
    LIFTED_F48A710_STACK = 192,
    LIFTED_F48AC50_STACK = 408,
    LIFTED_F48AD00_STACK = 464,
    LIFTED_F48AE00_STACK = 932,
    LIFTED_F48B550_STACK = 140,
    LIFTED_F48B770_STACK = 88,
    LIFTED_F48B7E0_STACK = 292,
    LIFTED_F48BCA0_STACK = 124,
    LIFTED_F48BE70_STACK = 124,
    LIFTED_F48C0F0_STACK = 140,
    LIFTED_OBJECT_NOTIFY_CHOICE_STACK = 76,
    LIFTED_OBJECT_NOTIFY_BYTE_STACK = 76,
    LIFTED_OBJECT_NOTIFY_FIELD_48C310_STACK = 76,
    LIFTED_F48C390_STACK = 80,
    LIFTED_F48C3B0_STACK = 80,
    LIFTED_F48C3D0_STACK = 100,
    LIFTED_F48C460_STACK = 80,
    LIFTED_F48C480_STACK = 76,
    LIFTED_F48C4A0_STACK = 184,
    LIFTED_F48C610_STACK = 76,
    LIFTED_F48C680_STACK = 96,
    LIFTED_F48C6C0_STACK = 208,
    LIFTED_F48C860_STACK = 2528,
    LIFTED_F48C970_STACK = 120,
    LIFTED_OBJECT_DELEGATE_STACK = 72,
    LIFTED_F48C9D0_STACK = 72,
    LIFTED_F48CA20_STACK = 356,
    LIFTED_F48CC30_STACK = 740,
    LIFTED_RECORD_COPY_STACK = 68,
    LIFTED_F48D530_STACK = 172,
    LIFTED_LIST_EMPTY_48D5F0_STACK = 64,
    LIFTED_OBJECT_RELEASE_CALL_48D600_STACK = 80,
    LIFTED_FORWARD_REGISTERS_48D620_STACK = 72,
    LIFTED_LIST_ITEM_48D630_STACK = 68,
    LIFTED_F48D650_STACK = 100,
    LIFTED_FORWARD_CALL_48D6B0_STACK = 68,
    LIFTED_F48D6C0_STACK = 100,
    LIFTED_F4AC1C0_STACK = 68,
    LIFTED_F4AC1E0_STACK = 64,
    LIFTED_ANIMATION_TICK_4AC310_STACK = 104,
    LIFTED_F4AC590_STACK = 68,
    LIFTED_F4AC610_STACK = 64,
    LIFTED_ACTOR_RANDOMIZE_PERIOD_STACK = 84,
    LIFTED_ACTOR_RANDOMIZE_D0_STACK = 84,
    LIFTED_ACTOR_GET_B4_FULL_STACK = 64,
    LIFTED_STEP_TOWARD_STACK = 64,
    LIFTED_DWORD_TRANSITION_STACK = 76,
    LIFTED_F4ACCC0_STACK = 80,
    LIFTED_F4ACD30_STACK = 80,
    LIFTED_ACTOR_TURN_TOWARD_STACK = 84,
    LIFTED_ACTOR_SPIN_STACK = 80,
    LIFTED_ACTOR_POLAR_OFFSET_SECOND_STACK = 80,
    LIFTED_ACTOR_ORBIT_POINT_STACK = 92,
    LIFTED_F4AD2C0_STACK = 100,
    LIFTED_ACTOR_CHAIN_ORBIT_POINT_STACK = 108,
    LIFTED_ACTOR_SET_WORDS_2A_FULL_STACK = 64,
    LIFTED_BYTE_TRANSITION_4AD580_STACK = 80,
    LIFTED_WORD_TRANSITION_4AD5E0_STACK = 80,
    LIFTED_WORD_TRANSITION_4AD630_STACK = 80,
    LIFTED_OBJECT_STEP_DWORD_STACK = 76,
    LIFTED_ACTOR_DWORD_TRANSITION_4AD790_STACK = 76,
    LIFTED_F4ADFA0_STACK = 64,
    LIFTED_F4B0B70_STACK = 136,
    LIFTED_OBJECT_RELEASE_SLOTS_FULL_STACK = 80,
    LIFTED_F4B2300_STACK = 72,
    LIFTED_F4B2340_STACK = 76,
    LIFTED_F4B2A00_STACK = 340,
    LIFTED_F4B2D90_STACK = 300,
    LIFTED_F4B34D0_STACK = 68,
    LIFTED_F4B3500_STACK = 156,
    LIFTED_OBJECT_SET_PAIR_4B35B0_STACK = 64,
    LIFTED_F4B3A00_STACK = 212,
    LIFTED_OBJECT_SET_PAIR_4B3C30_STACK = 64,
    LIFTED_OBJECT_LABEL_FORMAT_ALTERNATE_STACK = 140,
    LIFTED_F4B3CE0_STACK = 112,
    LIFTED_F4B3D60_STACK = 112,
    LIFTED_F4B3FB0_STACK = 68,
    LIFTED_OBJECT_CONTAINS_POINT_STACK = 80,
    LIFTED_OBJECT_DWORD_4B4500_STACK = 64,
    LIFTED_OBJECT_SET_MODE_STACK = 68,
    LIFTED_OBJECT_CURSOR_ROW_STACK = 72,
    LIFTED_OBJECT_STEP_TEXT_LENGTH_STACK = 68,
    LIFTED_OBJECT_STEP_TEXT_LENGTH_4B4610_STACK = 68,
    LIFTED_OBJECT_STEP_TEXT_LENGTH_4B4620_STACK = 68,
    LIFTED_OBJECT_TEXT_LENGTH_RESET_STACK = 80,
    LIFTED_OBJECT_CURSOR_AT_END_STACK = 76,
    LIFTED_OBJECT_CURSOR_CLAMP_STACK = 80,
    LIFTED_OBJECT_TEXT_ROW_STACK = 72,
    LIFTED_OBJECT_TEXT_NEAREST_STACK = 96,
    LIFTED_OBJECT_TEXT_SEEK_STACK = 72,
    LIFTED_OBJECT_PARENT_APPEND_STACK = 72,
    LIFTED_OBJECT_PARENT_GLYPH_STACK = 68,
    LIFTED_OBJECT_PARENT_APPEND_4B4CD0_STACK = 72,
    LIFTED_F4B4CF0_STACK = 252,
    LIFTED_OBJECT_SET_PAIR_4B4FA0_STACK = 64,
    LIFTED_OBJECT_LABEL_FORMAT_STACK = 140,
    LIFTED_F4B5050_STACK = 112,
    LIFTED_F4B50D0_STACK = 112,
    LIFTED_F4B5580_STACK = 136,
    LIFTED_F4B5630_STACK = 160,
    LIFTED_F4B5700_STACK = 208,
    LIFTED_F4B58A0_STACK = 196,
    LIFTED_OBJECT_START_5182C4_STACK = 68,
    LIFTED_OBJECT_SLOT_PRESENT_UNOWNED_STACK = 84,
    LIFTED_OBJECT_RELEASE_ITEMS_STACK = 88,
    LIFTED_TIMER_RESET_STACK = 64,
    LIFTED_OBJECT_SET_WORD_STACK = 64,
    LIFTED_OBJECT_SET_WORD_4B6550_STACK = 64,
    LIFTED_OBJECT_WORD_STACK = 64,
    LIFTED_OBJECT_WORD_4B65A0_STACK = 64,
    LIFTED_OBJECT_SET_DWORD_4B65B0_STACK = 64,
    LIFTED_OBJECT_SET_FOUR_WORDS_STACK = 64,
    LIFTED_OBJECT_CONTAINS_STACK = 72,
    LIFTED_OBJECT_SLOT_PRESENT_4B6700_STACK = 84,
    LIFTED_OBJECT_TEXT_VALUE_STACK = 140,
    LIFTED_OBJECT_GLYPH_PRESENT_STACK = 68,
    LIFTED_OBJECT_RELEASE_CALL_4B6F70_STACK = 80
};

/* Original 0x47f8e0. */
uint32_t lifted_object_write_18(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f8f0. */
uint32_t lifted_return_unchanged_47f8f0(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f9b0. */
uint32_t lifted_checked_calls(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x47faf0. */
uint32_t lifted_object_set_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_display_notify(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_palette_expand_vga(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4808f0. */
uint32_t lifted_f4808f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x481fb0. */
uint32_t lifted_object_destroy_b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482050. */
uint32_t lifted_object_clear_208(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482060. */
uint32_t lifted_event_stack_push(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482110. */
uint32_t lifted_event_stack_pop(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4823b0. */
uint32_t lifted_f4823b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482740. */
uint32_t lifted_forward_first_dword(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482770. */
uint32_t lifted_f482770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4828a0. */
uint32_t lifted_f4828a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4829c0. */
uint32_t lifted_f4829c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482b30. */
uint32_t lifted_call_unless_zero(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4831b0. */
uint32_t lifted_f4831b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4848f0. */
uint32_t lifted_f4848f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x485700. */
uint32_t lifted_f485700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x486ed0. */
uint32_t lifted_f486ed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487060. */
uint32_t lifted_f487060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487080. */
uint32_t lifted_f487080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487130. */
uint32_t lifted_f487130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4871d0. */
uint32_t lifted_f4871d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4872b0. */
uint32_t lifted_forward_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4874f0. */
uint32_t lifted_array_list_release(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487870. */
uint32_t lifted_table_object_construct(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487920. */
uint32_t lifted_f487920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4879e0. */
uint32_t lifted_list_empty(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4879f0. */
uint32_t lifted_object_release_call(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487a10. */
uint32_t lifted_forward_registers_487a10(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487a20. */
uint32_t lifted_list_item(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487b00. */
uint32_t lifted_object_construct_g(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487be0. */
uint32_t lifted_f487be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487fd0. */
uint32_t lifted_list_find_name(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488030. */
uint32_t lifted_table_item(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488040. */
uint32_t lifted_table_item_488040(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4893c0. */
uint32_t lifted_f4893c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x489b20. */
uint32_t lifted_f489b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489fa0. */
uint32_t lifted_f489fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x48b550. */
uint32_t lifted_f48b550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48b770. */
uint32_t lifted_f48b770(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x48c2b0. */
uint32_t lifted_object_notify_choice(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c2e0. */
uint32_t lifted_object_notify_byte(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c310. */
uint32_t lifted_object_notify_field_48c310(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
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

/* Original 0x48c4a0. */
uint32_t lifted_f48c4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c610. */
uint32_t lifted_f48c610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c680. */
uint32_t lifted_f48c680(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x48c9b0. */
uint32_t lifted_object_delegate(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48c9d0. */
uint32_t lifted_f48c9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48ca20. */
uint32_t lifted_f48ca20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48cc30. */
uint32_t lifted_f48cc30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d3e0. */
uint32_t lifted_record_copy(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d530. */
uint32_t lifted_f48d530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d5f0. */
uint32_t lifted_list_empty_48d5f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d600. */
uint32_t lifted_object_release_call_48d600(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d620. */
uint32_t lifted_forward_registers_48d620(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d630. */
uint32_t lifted_list_item_48d630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d650. */
uint32_t lifted_f48d650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d6b0. */
uint32_t lifted_forward_call_48d6b0(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48d6c0. */
uint32_t lifted_f48d6c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac1c0. */
uint32_t lifted_f4ac1c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac1e0. */
uint32_t lifted_f4ac1e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac310. */
uint32_t lifted_animation_tick_4ac310(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac590. */
uint32_t lifted_f4ac590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac610. */
uint32_t lifted_f4ac610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac7e0. */
uint32_t lifted_actor_randomize_period(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac810. */
uint32_t lifted_actor_randomize_d0(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac960. */
uint32_t lifted_actor_get_b4_full(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ac980. */
uint32_t lifted_step_toward(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4acc70. */
uint32_t lifted_dword_transition(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4accc0. */
uint32_t lifted_f4accc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4acd30. */
uint32_t lifted_f4acd30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ace40. */
uint32_t lifted_actor_turn_toward(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad110. */
uint32_t lifted_actor_spin(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad210. */
uint32_t lifted_actor_polar_offset_second(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad260. */
uint32_t lifted_actor_orbit_point(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad2c0. */
uint32_t lifted_f4ad2c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad440. */
uint32_t lifted_actor_chain_orbit_point(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad510. */
uint32_t lifted_actor_set_words_2a_full(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad580. */
uint32_t lifted_byte_transition_4ad580(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad5e0. */
uint32_t lifted_word_transition_4ad5e0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad630. */
uint32_t lifted_word_transition_4ad630(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad750. */
uint32_t lifted_object_step_dword(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ad790. */
uint32_t lifted_actor_dword_transition_4ad790(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x4adfa0. */
uint32_t lifted_f4adfa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b0b70. */
uint32_t lifted_f4b0b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b22c0. */
uint32_t lifted_object_release_slots_full(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b2300. */
uint32_t lifted_f4b2300(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b2340. */
uint32_t lifted_f4b2340(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b2a00. */
uint32_t lifted_f4b2a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b2d90. */
uint32_t lifted_f4b2d90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b34d0. */
uint32_t lifted_f4b34d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3500. */
uint32_t lifted_f4b3500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b35b0. */
uint32_t lifted_object_set_pair_4b35b0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3a00. */
uint32_t lifted_f4b3a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3c30. */
uint32_t lifted_object_set_pair_4b3c30(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3c40. */
uint32_t lifted_object_label_format_alternate(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

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
uint32_t lifted_object_contains_point(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4500. */
uint32_t lifted_object_dword_4b4500(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4510. */
uint32_t lifted_object_set_mode(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b45f0. */
uint32_t lifted_object_cursor_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4600. */
uint32_t lifted_object_step_text_length(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4610. */
uint32_t lifted_object_step_text_length_4b4610(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x4b4620. */
uint32_t lifted_object_step_text_length_4b4620(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x4b4630. */
uint32_t lifted_object_text_length_reset(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4660. */
uint32_t lifted_object_cursor_at_end(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4690. */
uint32_t lifted_object_cursor_clamp(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b46e0. */
uint32_t lifted_object_text_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4700. */
uint32_t lifted_object_text_nearest(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4780. */
uint32_t lifted_object_text_seek(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4c90. */
uint32_t lifted_object_parent_append(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4cb0. */
uint32_t lifted_object_parent_glyph(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4cd0. */
uint32_t lifted_object_parent_append_4b4cd0(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4cf0. */
uint32_t lifted_f4b4cf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4fa0. */
uint32_t lifted_object_set_pair_4b4fa0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4fb0. */
uint32_t lifted_object_label_format(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5050. */
uint32_t lifted_f4b5050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b50d0. */
uint32_t lifted_f4b50d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5580. */
uint32_t lifted_f4b5580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5630. */
uint32_t lifted_f4b5630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5700. */
uint32_t lifted_f4b5700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b58a0. */
uint32_t lifted_f4b58a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5c60. */
uint32_t lifted_object_start_5182c4(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5d40. */
uint32_t lifted_object_slot_present_unowned(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6020. */
uint32_t lifted_object_release_items(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6530. */
uint32_t lifted_timer_reset(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6540. */
uint32_t lifted_object_set_word(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6550. */
uint32_t lifted_object_set_word_4b6550(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6590. */
uint32_t lifted_object_word(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b65a0. */
uint32_t lifted_object_word_4b65a0(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b65b0. */
uint32_t lifted_object_set_dword_4b65b0(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6690. */
uint32_t lifted_object_set_four_words(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b66c0. */
uint32_t lifted_object_contains(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6700. */
uint32_t lifted_object_slot_present_4b6700(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6930. */
uint32_t lifted_object_text_value(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6a10. */
uint32_t lifted_object_glyph_present(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6f70. */
uint32_t lifted_object_release_call_4b6f70(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);
#endif
