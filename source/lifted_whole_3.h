#ifndef VERTRIX_LIFTED_WHOLE_3_H
#define VERTRIX_LIFTED_WHOLE_3_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F45BB80_STACK = 108,
    LIFTED_F45BC00_STACK = 108,
    LIFTED_F45BC80_STACK = 108,
    LIFTED_F45BEB0_STACK = 108,
    LIFTED_F45BFF0_STACK = 108,
    LIFTED_F45C060_STACK = 116,
    LIFTED_F45C600_STACK = 132,
    LIFTED_F45C9A0_STACK = 248,
    LIFTED_F45CC40_STACK = 140,
    LIFTED_F45CD00_STACK = 140,
    LIFTED_F45D1A0_STACK = 168,
    LIFTED_F45D690_STACK = 132,
    LIFTED_F45D740_STACK = 108,
    LIFTED_F45D7B0_STACK = 108,
    LIFTED_F45DCA0_STACK = 660,
    LIFTED_TABLE_RELEASE_EVERYTHING_STACK = 212,
    LIFTED_RESOURCE_ROWS_BUILD_STACK = 124,
    LIFTED_F45F0C0_STACK = 120,
    LIFTED_RESOURCE_INDEXED_FINISH_STACK = 124,
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
    LIFTED_UI_COMPANION_SPAWN_STACK = 112,
    LIFTED_F4718A0_STACK = 128,
    LIFTED_F472170_STACK = 128,
    LIFTED_F4723A0_STACK = 180,
    LIFTED_BANNER_ACTOR_SPAWN_STACK = 136,
    LIFTED_F4726D0_STACK = 428,
    LIFTED_OVERLAY_SPAWN_STACK = 132,
    LIFTED_ICONS_BUILD_STACK = 288,
    LIFTED_F473490_STACK = 140,
    LIFTED_PAIR_WORDS_STACK = 148,
    LIFTED_BITMAP_LOAD_STACK = 232,
    LIFTED_F473E60_STACK = 136,
    LIFTED_F473FC0_STACK = 308,
    LIFTED_F4741A0_STACK = 348,
    LIFTED_PALETTE_CHANNELS_STACK = 152,
    LIFTED_RELEASE_PAIR_STACK = 112,
    LIFTED_INPUT_QUEUE_ACKNOWLEDGE_FULL_STACK = 80,
    LIFTED_SOUND_CUE_BOTH_STACK = 96,
    LIFTED_SOUND_RELEASE_STREAM_STACK = 104,
    LIFTED_F477610_STACK = 96,
    LIFTED_FORMAT_DECIMAL_STACK = 100,
    LIFTED_CURSOR_CAPTURE_STACK = 108,
    LIFTED_OBJECT_CENTER_PLACE_STACK = 84,
    LIFTED_F478910_STACK = 180,
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
    LIFTED_F47E7D0_STACK = 160,
    LIFTED_F47E9B0_STACK = 132,
    LIFTED_DISPLAY_RELEASE_PAIR_STACK = 92,
    LIFTED_F47EAB0_STACK = 96,
    LIFTED_F47EB60_STACK = 96,
    LIFTED_F47EDA0_STACK = 772,
    LIFTED_F47EEB0_STACK = 180,
    LIFTED_F47F0F0_STACK = 112,
    LIFTED_OBJECT_PICK_ENTRY_STACK = 108,
    LIFTED_F47F4B0_STACK = 252,
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

/* Original 0x45beb0. */
uint32_t lifted_f45beb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bff0. */
uint32_t lifted_f45bff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c060. */
uint32_t lifted_f45c060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c600. */
uint32_t lifted_f45c600(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x45dca0. */
uint32_t lifted_f45dca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e260. */
uint32_t lifted_table_release_everything(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e590. */
uint32_t lifted_resource_rows_build(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f0c0. */
uint32_t lifted_f45f0c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f140. */
uint32_t lifted_resource_indexed_finish(const VertrixCalls *calls,
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

/* Original 0x471100. */
uint32_t lifted_ui_companion_spawn(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4718a0. */
uint32_t lifted_f4718a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472170. */
uint32_t lifted_f472170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4723a0. */
uint32_t lifted_f4723a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472620. */
uint32_t lifted_banner_actor_spawn(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4726d0. */
uint32_t lifted_f4726d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472c10. */
uint32_t lifted_overlay_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4731a0. */
uint32_t lifted_icons_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x473490. */
uint32_t lifted_f473490(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x474cd0. */
uint32_t lifted_palette_channels(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x475510. */
uint32_t lifted_release_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476320. */
uint32_t lifted_input_queue_acknowledge_full(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476720. */
uint32_t lifted_sound_cue_both(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x477c30. */
uint32_t lifted_cursor_capture(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x477e30. */
uint32_t lifted_object_center_place(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478910. */
uint32_t lifted_f478910(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x47e7d0. */
uint32_t lifted_f47e7d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x47eda0. */
uint32_t lifted_f47eda0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47eeb0. */
uint32_t lifted_f47eeb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f0f0. */
uint32_t lifted_f47f0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f280. */
uint32_t lifted_object_pick_entry(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f4b0. */
uint32_t lifted_f47f4b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f790. */
uint32_t lifted_f47f790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f830. */
uint32_t lifted_f47f830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
