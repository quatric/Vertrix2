#ifndef VERTRIX_LIFTED_WHOLE_3_H
#define VERTRIX_LIFTED_WHOLE_3_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F45BB80_STACK = 108,
    LIFTED_F45BC00_STACK = 108,
    LIFTED_F45BC80_STACK = 108,
    LIFTED_F45BD00_STACK = 108,
    LIFTED_F45BD60_STACK = 108,
    LIFTED_F45BDD0_STACK = 108,
    LIFTED_F45BE40_STACK = 108,
    LIFTED_F45BEB0_STACK = 108,
    LIFTED_F45BF20_STACK = 108,
    LIFTED_F45BF80_STACK = 108,
    LIFTED_F45BFF0_STACK = 108,
    LIFTED_F45C060_STACK = 116,
    LIFTED_F45C0E0_STACK = 108,
    LIFTED_F45C150_STACK = 108,
    LIFTED_F45C1B0_STACK = 108,
    LIFTED_F45C210_STACK = 96,
    LIFTED_F45C250_STACK = 88,
    LIFTED_F45C2B0_STACK = 76,
    LIFTED_F45C600_STACK = 132,
    LIFTED_F45C6E0_STACK = 88,
    LIFTED_F45C8E0_STACK = 100,
    LIFTED_F45C940_STACK = 100,
    LIFTED_F45C9A0_STACK = 248,
    LIFTED_F45CC40_STACK = 140,
    LIFTED_F45CD00_STACK = 140,
    LIFTED_F45D1A0_STACK = 168,
    LIFTED_F45D690_STACK = 132,
    LIFTED_F45D740_STACK = 108,
    LIFTED_F45D7B0_STACK = 108,
    LIFTED_OBJECT_STEP_TOGGLE_STACK = 96,
    LIFTED_F45DCA0_STACK = 660,
    LIFTED_TABLE_RELEASE_EVERYTHING_STACK = 212,
    LIFTED_TABLE_BUILD_PAIR_STACK = 128,
    LIFTED_RESOURCE_ROWS_BUILD_STACK = 124,
    LIFTED_TABLE_BUILD_BY_FLAG_STACK = 116,
    LIFTED_TABLE_RELEASE_BY_FLAG_STACK = 72,
    LIFTED_TABLE_RELEASE_ONE_STACK = 68,
    LIFTED_TABLE_RELEASE_ONE_45E810_STACK = 68,
    LIFTED_TABLE_RELEASE_ONE_45E820_STACK = 68,
    LIFTED_TABLE_RELEASE_RUN_STACK = 76,
    LIFTED_TABLE_RELEASE_RUN_45E8F0_STACK = 76,
    LIFTED_TABLE_RELEASE_ROWS_STACK = 84,
    LIFTED_TABLE_RELEASE_PAIR_STACK = 80,
    LIFTED_RESOURCE_PAIR_CALL_STACK = 88,
    LIFTED_SEVEN_STEPS_STACK = 84,
    LIFTED_F45F0C0_STACK = 120,
    LIFTED_RESOURCE_INDEXED_FINISH_STACK = 124,
    LIFTED_TABLE_IDENTITY_CELLS_FULL_STACK = 64,
    LIFTED_RESOURCE_FLAGGED_FINISH_STACK = 112,
    LIFTED_F45F3F0_STACK = 144,
    LIFTED_F45F770_STACK = 276,
    LIFTED_LABEL_FRAME_STACK = 228,
    LIFTED_F45FC80_STACK = 232,
    LIFTED_LABEL_BOX_STACK = 140,
    LIFTED_F45FEE0_STACK = 140,
    LIFTED_F4601C0_STACK = 172,
    LIFTED_F4602A0_STACK = 232,
    LIFTED_F460440_STACK = 244,
    LIFTED_F460630_STACK = 260,
    LIFTED_F460840_STACK = 252,
    LIFTED_F460A40_STACK = 112,
    LIFTED_F460AD0_STACK = 112,
    LIFTED_F460B60_STACK = 156,
    LIFTED_F460C50_STACK = 252,
    LIFTED_F460DF0_STACK = 160,
    LIFTED_F460ED0_STACK = 160,
    LIFTED_F460FA0_STACK = 180,
    LIFTED_F461090_STACK = 176,
    LIFTED_F461180_STACK = 288,
    LIFTED_F461360_STACK = 220,
    LIFTED_F4614C0_STACK = 220,
    LIFTED_F461930_STACK = 1096,
    LIFTED_F4627A0_STACK = 1572,
    LIFTED_F4633B0_STACK = 3240,
    LIFTED_F4651B0_STACK = 708,
    LIFTED_F4657F0_STACK = 292,
    LIFTED_MARKER_SPAWN_STACK = 124,
    LIFTED_F466D60_STACK = 2768,
    LIFTED_F469480_STACK = 984,
    LIFTED_F46A410_STACK = 644,
    LIFTED_F46A9C0_STACK = 1164,
    LIFTED_HUD_BUILD_STACK = 1096,
    LIFTED_F46C9D0_STACK = 2064,
    LIFTED_MARQUEE_BUILD_STACK = 180,
    LIFTED_LETTER_MENU_STACK = 480,
    LIFTED_LETTER_GRID_STACK = 244,
    LIFTED_F46F440_STACK = 1140,
    LIFTED_F470960_STACK = 240,
    LIFTED_ROW_LABEL_STACK = 240,
    LIFTED_PANEL_GROUP_STACK = 368,
    LIFTED_UI_ACTOR_PLACE_STACK = 92,
    LIFTED_UI_COMPANION_SPAWN_STACK = 112,
    LIFTED_F4718A0_STACK = 128,
    LIFTED_F471920_STACK = 84,
    LIFTED_F471940_STACK = 84,
    LIFTED_F471960_STACK = 84,
    LIFTED_F471980_STACK = 84,
    LIFTED_UI_SLIDE_FROM_ABOVE_STACK = 68,
    LIFTED_F471A90_STACK = 68,
    LIFTED_F471B10_STACK = 68,
    LIFTED_LIST_CLEAR_CALL_471B80_STACK = 68,
    LIFTED_F471B90_STACK = 68,
    LIFTED_F471BA0_STACK = 72,
    LIFTED_ACTORS_HANDLER_FROM_EC_UNLINKED_STACK = 88,
    LIFTED_ACTOR_LIST_ALL_IDLE_471CD0_STACK = 80,
    LIFTED_ACTOR_LIST_ALL_IDLE_471D10_STACK = 80,
    LIFTED_OBJECT_SET_464_STACK = 64,
    LIFTED_F472020_STACK = 128,
    LIFTED_F472090_STACK = 128,
    LIFTED_F472170_STACK = 128,
    LIFTED_F4721E0_STACK = 128,
    LIFTED_F472250_STACK = 128,
    LIFTED_F4722C0_STACK = 128,
    LIFTED_F4723A0_STACK = 180,
    LIFTED_F472440_STACK = 72,
    LIFTED_F472460_STACK = 72,
    LIFTED_ACTOR_SPAWN_STACK = 128,
    LIFTED_SPECIAL_ACTOR_SPAWN_STACK = 128,
    LIFTED_SCENE_CLEAR_MARKER_STACK = 72,
    LIFTED_BANNER_ACTOR_SPAWN_STACK = 136,
    LIFTED_F4726D0_STACK = 428,
    LIFTED_F472BD0_STACK = 84,
    LIFTED_OVERLAY_SPAWN_STACK = 132,
    LIFTED_SLOT_CREATE_CALL_STACK = 92,
    LIFTED_UI_PANEL_RELEASE_FULL_STACK = 80,
    LIFTED_F472D90_STACK = 72,
    LIFTED_ICONS_BUILD_STACK = 288,
    LIFTED_F473490_STACK = 140,
    LIFTED_POINT_LIST_CONDITIONAL_STACK = 76,
    LIFTED_PAIR_WORDS_STACK = 148,
    LIFTED_BITMAP_LOAD_STACK = 232,
    LIFTED_F473E60_STACK = 136,
    LIFTED_F473FC0_STACK = 308,
    LIFTED_F4741A0_STACK = 348,
    LIFTED_F474490_STACK = 404,
    LIFTED_F474540_STACK = 72,
    LIFTED_PALETTE_CHANNELS_STACK = 152,
    LIFTED_PALETTE_TABLES_CYCLE_STACK = 72,
    LIFTED_RELEASE_PAIR_STACK = 112,
    LIFTED_OBJECT_DESTROY_FLAGS_STACK = 136,
    LIFTED_F475B20_STACK = 104,
    LIFTED_F475B80_STACK = 104,
    LIFTED_F475BE0_STACK = 92,
    LIFTED_QUEUE_NEXT_STACK = 84,
    LIFTED_PROGRESS_SET_40_STACK = 64,
    LIFTED_INPUT_REPEAT_COUNTER_CLEAR_FULL_STACK = 64,
    LIFTED_PROGRESS_DONE_STACK = 68,
    LIFTED_PROGRESS_QUOTIENT_STACK = 72,
    LIFTED_INPUT_REPEAT_COUNTER_ADVANCE_FULL_STACK = 64,
    LIFTED_PROGRESS_SET_3C_STACK = 64,
    LIFTED_OBJECT_CONSTRUCT_F_STACK = 140,
    LIFTED_SLOT_CALL_STACK = 72,
    LIFTED_F4761D0_STACK = 96,
    LIFTED_LIST_FIND_CALL_STACK = 80,
    LIFTED_SLOT_SELECT_STACK = 80,
    LIFTED_INPUT_QUEUE_ACKNOWLEDGE_FULL_STACK = 80,
    LIFTED_F476440_STACK = 80,
    LIFTED_F4764D0_STACK = 76,
    LIFTED_F476500_STACK = 76,
    LIFTED_SLOT_SEARCH_CALL_STACK = 84,
    LIFTED_SOUND_KEY_IS_CONTROL_STACK = 64,
    LIFTED_SOUND_CUE_BOTH_STACK = 96,
    LIFTED_RESOURCE_ENTRY_256_STACK = 108,
    LIFTED_SOUND_CHECK_PRIMARY_STACK = 84,
    LIFTED_SOUND_RELEASE_PRIMARY_STACK = 104,
    LIFTED_SOUND_CUE_OFFSET_STACK = 84,
    LIFTED_SOUND_CUE_OFFSET_476FE0_STACK = 84,
    LIFTED_SOUND_CUE_KEY_STACK = 84,
    LIFTED_SOUND_CUE_KEY_477040_STACK = 84,
    LIFTED_SOUND_CUE_KEY_477070_STACK = 84,
    LIFTED_SOUND_CUE_KEY_4770A0_STACK = 84,
    LIFTED_SOUND_CUE_KEY_4770D0_STACK = 84,
    LIFTED_SOUND_CUE_KEY_477100_STACK = 84,
    LIFTED_SOUND_CUE_KEY_477130_STACK = 84,
    LIFTED_SOUND_CUE_KEY_477160_STACK = 84,
    LIFTED_SOUND_RELEASE_STREAM_STACK = 104,
    LIFTED_F477610_STACK = 96,
    LIFTED_FORMAT_DECIMAL_STACK = 100,
    LIFTED_TEXT_APPEND_CALL_STACK = 88,
    LIFTED_CURSOR_CAPTURE_STACK = 108,
    LIFTED_CURSOR_RELEASE_STACK = 136,
    LIFTED_SOUND_RELEASE_LOOPED_STACK = 104,
    LIFTED_OBJECT_CENTER_PLACE_STACK = 84,
    LIFTED_OBJECT_RESET_CENTER_STACK = 88,
    LIFTED_SOUND_CUE_POSITION_478570_STACK = 92,
    LIFTED_SOUND_CUE_POSITION_4785C0_STACK = 92,
    LIFTED_SOUND_CUE_POSITION_478610_STACK = 92,
    LIFTED_SOUND_CUE_POSITION_478660_STACK = 92,
    LIFTED_SOUND_CUE_POSITION_4786B0_STACK = 92,
    LIFTED_SOUND_CUE_POSITION_478700_STACK = 92,
    LIFTED_SOUND_CUE_POSITION_478750_STACK = 92,
    LIFTED_SOUND_CUE_POSITION_4787A0_STACK = 92,
    LIFTED_F478860_STACK = 140,
    LIFTED_F478910_STACK = 180,
    LIFTED_WHEN_FLAG_CALL_STACK = 72,
    LIFTED_OFFSET_PAIR_CALL_STACK = 92,
    LIFTED_OFFSET_PAIR_CLAMP_CALL_STACK = 92,
    LIFTED_LITERAL_COPY_CALL_STACK = 92,
    LIFTED_OBJECT_DESCRIBE_STACK = 136,
    LIFTED_SURFACE_CELL_ADDRESS_STACK = 64,
    LIFTED_SURFACE_FLIP_VERTICAL_STACK = 112,
    LIFTED_F47BD80_STACK = 160,
    LIFTED_F47C3B0_STACK = 96,
    LIFTED_F47C710_STACK = 188,
    LIFTED_SURFACE_BLEND_STACK = 84,
    LIFTED_SURFACE_BLEND_MASKED_STACK = 88,
    LIFTED_SURFACE_DECIMATE_STACK = 88,
    LIFTED_SURFACE_BLIT_STACK = 104,
    LIFTED_SURFACE_BLIT_KEYED_STACK = 92,
    LIFTED_F47E360_STACK = 216,
    LIFTED_F47E680_STACK = 188,
    LIFTED_F47E780_STACK = 92,
    LIFTED_F47E7D0_STACK = 160,
    LIFTED_DWORD_SET_STACK = 64,
    LIFTED_OBJECT_DWORD_STACK = 64,
    LIFTED_F47E9B0_STACK = 132,
    LIFTED_DISPLAY_RELEASE_PAIR_STACK = 92,
    LIFTED_F47EAB0_STACK = 96,
    LIFTED_F47EB60_STACK = 96,
    LIFTED_OBJECT_ARM_30_STACK = 64,
    LIFTED_F47ED10_STACK = 72,
    LIFTED_F47ED30_STACK = 72,
    LIFTED_OBJECT_SET_DWORD_STACK = 64,
    LIFTED_OBJECT_SET_DWORD_47ED70_STACK = 64,
    LIFTED_OBJECT_SET_DWORD_47ED80_STACK = 64,
    LIFTED_OBJECT_SET_DWORD_47ED90_STACK = 64,
    LIFTED_F47EDA0_STACK = 772,
    LIFTED_F47EEB0_STACK = 180,
    LIFTED_F47F0F0_STACK = 112,
    LIFTED_DISPLAY_CHAIN_COUNT_STACK = 68,
    LIFTED_OBJECT_CHAIN_AT_STACK = 68,
    LIFTED_OBJECT_CHAIN_MEMBER_STACK = 68,
    LIFTED_OBJECT_PICK_ENTRY_STACK = 108,
    LIFTED_F47F2F0_STACK = 96,
    LIFTED_DISPLAY_CHAIN_FIND_STACK = 84,
    LIFTED_F47F370_STACK = 92,
    LIFTED_F47F3D0_STACK = 100,
    LIFTED_F47F4B0_STACK = 252,
    LIFTED_F47F750_STACK = 80,
    LIFTED_F47F770_STACK = 76,
    LIFTED_F47F790_STACK = 656,
    LIFTED_F47F830_STACK = 656
};

/* Original 0x45bb80. */
uint32_t lifted_f45bb80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bc00. */
uint32_t lifted_f45bc00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bc80. */
uint32_t lifted_f45bc80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bd00. */
uint32_t lifted_f45bd00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bd60. */
uint32_t lifted_f45bd60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bdd0. */
uint32_t lifted_f45bdd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45be40. */
uint32_t lifted_f45be40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45beb0. */
uint32_t lifted_f45beb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bf20. */
uint32_t lifted_f45bf20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bf80. */
uint32_t lifted_f45bf80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bff0. */
uint32_t lifted_f45bff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c060. */
uint32_t lifted_f45c060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c0e0. */
uint32_t lifted_f45c0e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c150. */
uint32_t lifted_f45c150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c1b0. */
uint32_t lifted_f45c1b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c210. */
uint32_t lifted_f45c210(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c250. */
uint32_t lifted_f45c250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c2b0. */
uint32_t lifted_f45c2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c600. */
uint32_t lifted_f45c600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c6e0. */
uint32_t lifted_f45c6e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c8e0. */
uint32_t lifted_f45c8e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c940. */
uint32_t lifted_f45c940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c9a0. */
uint32_t lifted_f45c9a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45cc40. */
uint32_t lifted_f45cc40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45cd00. */
uint32_t lifted_f45cd00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d1a0. */
uint32_t lifted_f45d1a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d690. */
uint32_t lifted_f45d690(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d740. */
uint32_t lifted_f45d740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d7b0. */
uint32_t lifted_f45d7b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d820. */
uint32_t lifted_object_step_toggle(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45dca0. */
uint32_t lifted_f45dca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e260. */
uint32_t lifted_table_release_everything(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e440. */
uint32_t lifted_table_build_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e590. */
uint32_t lifted_resource_rows_build(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e630. */
uint32_t lifted_table_build_by_flag(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e670. */
uint32_t lifted_table_release_by_flag(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e740. */
uint32_t lifted_table_release_one(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e810. */
uint32_t lifted_table_release_one_45e810(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e820. */
uint32_t lifted_table_release_one_45e820(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e830. */
uint32_t lifted_table_release_run(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e8f0. */
uint32_t lifted_table_release_run_45e8f0(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e910. */
uint32_t lifted_table_release_rows(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ea80. */
uint32_t lifted_table_release_pair(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ecd0. */
uint32_t lifted_resource_pair_call(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f0a0. */
uint32_t lifted_seven_steps(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f0c0. */
uint32_t lifted_f45f0c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f140. */
uint32_t lifted_resource_indexed_finish(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f1e0. */
uint32_t lifted_table_identity_cells_full(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f250. */
uint32_t lifted_resource_flagged_finish(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f3f0. */
uint32_t lifted_f45f3f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f770. */
uint32_t lifted_f45f770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45fb00. */
uint32_t lifted_label_frame(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45fc80. */
uint32_t lifted_f45fc80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45fe10. */
uint32_t lifted_label_box(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45fee0. */
uint32_t lifted_f45fee0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4601c0. */
uint32_t lifted_f4601c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4602a0. */
uint32_t lifted_f4602a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460440. */
uint32_t lifted_f460440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460630. */
uint32_t lifted_f460630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460840. */
uint32_t lifted_f460840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460a40. */
uint32_t lifted_f460a40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460ad0. */
uint32_t lifted_f460ad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460b60. */
uint32_t lifted_f460b60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460c50. */
uint32_t lifted_f460c50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460df0. */
uint32_t lifted_f460df0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460ed0. */
uint32_t lifted_f460ed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x460fa0. */
uint32_t lifted_f460fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x461090. */
uint32_t lifted_f461090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x461180. */
uint32_t lifted_f461180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x461360. */
uint32_t lifted_f461360(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4614c0. */
uint32_t lifted_f4614c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x461930. */
uint32_t lifted_f461930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4627a0. */
uint32_t lifted_f4627a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4633b0. */
uint32_t lifted_f4633b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4651b0. */
uint32_t lifted_f4651b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4657f0. */
uint32_t lifted_f4657f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x465a70. */
uint32_t lifted_marker_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x466d60. */
uint32_t lifted_f466d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x469480. */
uint32_t lifted_f469480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46a410. */
uint32_t lifted_f46a410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46a9c0. */
uint32_t lifted_f46a9c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46b810. */
uint32_t lifted_hud_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46c9d0. */
uint32_t lifted_f46c9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46e8b0. */
uint32_t lifted_marquee_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46ea30. */
uint32_t lifted_letter_menu(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46eda0. */
uint32_t lifted_letter_grid(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46f440. */
uint32_t lifted_f46f440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x470960. */
uint32_t lifted_f470960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x470b20. */
uint32_t lifted_row_label(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x470d20. */
uint32_t lifted_panel_group(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4710d0. */
uint32_t lifted_ui_actor_place(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471100. */
uint32_t lifted_ui_companion_spawn(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4718a0. */
uint32_t lifted_f4718a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471920. */
uint32_t lifted_f471920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471940. */
uint32_t lifted_f471940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471960. */
uint32_t lifted_f471960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471980. */
uint32_t lifted_f471980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4719a0. */
uint32_t lifted_ui_slide_from_above(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471a90. */
uint32_t lifted_f471a90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b10. */
uint32_t lifted_f471b10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b80. */
uint32_t lifted_list_clear_call_471b80(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b90. */
uint32_t lifted_f471b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471ba0. */
uint32_t lifted_f471ba0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471bf0. */
uint32_t lifted_actors_handler_from_ec_unlinked(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x471cd0. */
uint32_t lifted_actor_list_all_idle_471cd0(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471d10. */
uint32_t lifted_actor_list_all_idle_471d10(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471ea0. */
uint32_t lifted_object_set_464(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472020. */
uint32_t lifted_f472020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472090. */
uint32_t lifted_f472090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472170. */
uint32_t lifted_f472170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4721e0. */
uint32_t lifted_f4721e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472250. */
uint32_t lifted_f472250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4722c0. */
uint32_t lifted_f4722c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4723a0. */
uint32_t lifted_f4723a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472440. */
uint32_t lifted_f472440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472460. */
uint32_t lifted_f472460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472470. */
uint32_t lifted_actor_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472570. */
uint32_t lifted_special_actor_spawn(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4725f0. */
uint32_t lifted_scene_clear_marker(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472620. */
uint32_t lifted_banner_actor_spawn(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4726d0. */
uint32_t lifted_f4726d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472bd0. */
uint32_t lifted_f472bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472c10. */
uint32_t lifted_overlay_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472d00. */
uint32_t lifted_slot_create_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472d50. */
uint32_t lifted_ui_panel_release_full(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472d90. */
uint32_t lifted_f472d90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4731a0. */
uint32_t lifted_icons_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473490. */
uint32_t lifted_f473490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4735e0. */
uint32_t lifted_point_list_conditional(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473630. */
uint32_t lifted_pair_words(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473cf0. */
uint32_t lifted_bitmap_load(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473e60. */
uint32_t lifted_f473e60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473fc0. */
uint32_t lifted_f473fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4741a0. */
uint32_t lifted_f4741a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x474490. */
uint32_t lifted_f474490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x474540. */
uint32_t lifted_f474540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x474cd0. */
uint32_t lifted_palette_channels(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4754e0. */
uint32_t lifted_palette_tables_cycle(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475510. */
uint32_t lifted_release_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475700. */
uint32_t lifted_object_destroy_flags(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475b20. */
uint32_t lifted_f475b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475b80. */
uint32_t lifted_f475b80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475be0. */
uint32_t lifted_f475be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475c80. */
uint32_t lifted_queue_next(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475dd0. */
uint32_t lifted_progress_set_40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475de0. */
uint32_t lifted_input_repeat_counter_clear_full(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x475df0. */
uint32_t lifted_progress_done(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475e10. */
uint32_t lifted_progress_quotient(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475e30. */
uint32_t lifted_input_repeat_counter_advance_full(const VertrixCalls *calls,
                                                  const VertrixFactoryServices *services,
                                                  const VertrixGlobals *globals,
                                                  const LiftEntry *entry);

/* Original 0x475e40. */
uint32_t lifted_progress_set_3c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475ec0. */
uint32_t lifted_object_construct_f(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476010. */
uint32_t lifted_slot_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4761d0. */
uint32_t lifted_f4761d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476260. */
uint32_t lifted_list_find_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4762e0. */
uint32_t lifted_slot_select(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476320. */
uint32_t lifted_input_queue_acknowledge_full(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476440. */
uint32_t lifted_f476440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4764d0. */
uint32_t lifted_f4764d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476500. */
uint32_t lifted_f476500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476530. */
uint32_t lifted_slot_search_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476650. */
uint32_t lifted_sound_key_is_control(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476720. */
uint32_t lifted_sound_cue_both(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476810. */
uint32_t lifted_resource_entry_256(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476c80. */
uint32_t lifted_sound_check_primary(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476cc0. */
uint32_t lifted_sound_release_primary(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476fb0. */
uint32_t lifted_sound_cue_offset(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476fe0. */
uint32_t lifted_sound_cue_offset_476fe0(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477010. */
uint32_t lifted_sound_cue_key(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477040. */
uint32_t lifted_sound_cue_key_477040(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477070. */
uint32_t lifted_sound_cue_key_477070(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4770a0. */
uint32_t lifted_sound_cue_key_4770a0(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4770d0. */
uint32_t lifted_sound_cue_key_4770d0(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477100. */
uint32_t lifted_sound_cue_key_477100(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477130. */
uint32_t lifted_sound_cue_key_477130(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477160. */
uint32_t lifted_sound_cue_key_477160(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477320. */
uint32_t lifted_sound_release_stream(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477610. */
uint32_t lifted_f477610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4776a0. */
uint32_t lifted_format_decimal(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4777c0. */
uint32_t lifted_text_append_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477c30. */
uint32_t lifted_cursor_capture(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477c90. */
uint32_t lifted_cursor_release(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477d10. */
uint32_t lifted_sound_release_looped(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477e30. */
uint32_t lifted_object_center_place(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477ed0. */
uint32_t lifted_object_reset_center(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478570. */
uint32_t lifted_sound_cue_position_478570(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4785c0. */
uint32_t lifted_sound_cue_position_4785c0(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478610. */
uint32_t lifted_sound_cue_position_478610(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478660. */
uint32_t lifted_sound_cue_position_478660(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4786b0. */
uint32_t lifted_sound_cue_position_4786b0(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478700. */
uint32_t lifted_sound_cue_position_478700(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478750. */
uint32_t lifted_sound_cue_position_478750(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4787a0. */
uint32_t lifted_sound_cue_position_4787a0(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478860. */
uint32_t lifted_f478860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478910. */
uint32_t lifted_f478910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478bd0. */
uint32_t lifted_when_flag_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478bf0. */
uint32_t lifted_offset_pair_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478c40. */
uint32_t lifted_offset_pair_clamp_call(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478c90. */
uint32_t lifted_literal_copy_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478dd0. */
uint32_t lifted_object_describe(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479b30. */
uint32_t lifted_surface_cell_address(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479b50. */
uint32_t lifted_surface_flip_vertical(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47bd80. */
uint32_t lifted_f47bd80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47c3b0. */
uint32_t lifted_f47c3b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47c710. */
uint32_t lifted_f47c710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47c930. */
uint32_t lifted_surface_blend(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47cb40. */
uint32_t lifted_surface_blend_masked(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47cd60. */
uint32_t lifted_surface_decimate(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ce10. */
uint32_t lifted_surface_blit(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e200. */
uint32_t lifted_surface_blit_keyed(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e360. */
uint32_t lifted_f47e360(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e680. */
uint32_t lifted_f47e680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e780. */
uint32_t lifted_f47e780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e7d0. */
uint32_t lifted_f47e7d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e990. */
uint32_t lifted_dword_set(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e9a0. */
uint32_t lifted_object_dword(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47e9b0. */
uint32_t lifted_f47e9b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ea20. */
uint32_t lifted_display_release_pair(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47eab0. */
uint32_t lifted_f47eab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47eb60. */
uint32_t lifted_f47eb60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ecf0. */
uint32_t lifted_object_arm_30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed10. */
uint32_t lifted_f47ed10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed30. */
uint32_t lifted_f47ed30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed60. */
uint32_t lifted_object_set_dword(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed70. */
uint32_t lifted_object_set_dword_47ed70(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed80. */
uint32_t lifted_object_set_dword_47ed80(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ed90. */
uint32_t lifted_object_set_dword_47ed90(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47eda0. */
uint32_t lifted_f47eda0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47eeb0. */
uint32_t lifted_f47eeb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f0f0. */
uint32_t lifted_f47f0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f160. */
uint32_t lifted_display_chain_count(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f190. */
uint32_t lifted_object_chain_at(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f260. */
uint32_t lifted_object_chain_member(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f280. */
uint32_t lifted_object_pick_entry(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f2f0. */
uint32_t lifted_f47f2f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f320. */
uint32_t lifted_display_chain_find(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f370. */
uint32_t lifted_f47f370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f3d0. */
uint32_t lifted_f47f3d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f4b0. */
uint32_t lifted_f47f4b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f750. */
uint32_t lifted_f47f750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f770. */
uint32_t lifted_f47f770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f790. */
uint32_t lifted_f47f790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f830. */
uint32_t lifted_f47f830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
