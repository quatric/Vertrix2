#ifndef VERTRIX_LIFTED_WHOLE_8_H
#define VERTRIX_LIFTED_WHOLE_8_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_EVENT_PACK_STACK = 112,
    LIFTED_MODULE_LOAD_STACK = 252,
    LIFTED_F410270_STACK = 140,
    LIFTED_F413BD0_STACK = 1292,
    LIFTED_F41C7B0_STACK = 232,
    LIFTED_F41D0E0_STACK = 308,
    LIFTED_F41EAB0_STACK = 308,
    LIFTED_F420F10_STACK = 844,
    LIFTED_F4220D0_STACK = 292,
    LIFTED_F4223D0_STACK = 520,
    LIFTED_F422800_STACK = 520,
    LIFTED_F422C50_STACK = 292,
    LIFTED_F422F50_STACK = 360,
    LIFTED_F4237D0_STACK = 212,
    LIFTED_F424990_STACK = 532,
    LIFTED_F4288D0_STACK = 296,
    LIFTED_PLAYER_PREVIEW_FRAMES_STACK = 84,
    LIFTED_SCENE_LAYOUT_STACK = 284,
    LIFTED_BOARD_TILE_CELL_STACK = 72,
    LIFTED_F434300_STACK = 396,
    LIFTED_F4344E0_STACK = 396,
    LIFTED_LINE_PASS_STACK = 272,
    LIFTED_FIGURE_PASS_STACK = 208,
    LIFTED_BOARD_SWIRL_MARKED_STACK = 180,
    LIFTED_MODE_COLORS_STACK = 76,
    LIFTED_PATTERN_TABLES_STACK = 148,
    LIFTED_F442140_STACK = 108,
    LIFTED_F443DC0_STACK = 152,
    LIFTED_F444700_STACK = 132,
    LIFTED_F449090_STACK = 124,
    LIFTED_F472F80_STACK = 260,
    LIFTED_SURFACE_FILL_STACK = 96,
    LIFTED_F4798B0_STACK = 96,
    LIFTED_CIRCLE_POINTS_STACK = 92,
    LIFTED_F47AB70_STACK = 100,
    LIFTED_DISPLAY_READY_STACK = 64,
    LIFTED_F48B970_STACK = 168,
    LIFTED_F4B17E0_STACK = 108,
    LIFTED_F4B3140_STACK = 160,
    LIFTED_F4BB170_STACK = 112,
    LIFTED_F4BB270_STACK = 132,
    LIFTED_F4BB870_STACK = 116,
    LIFTED_F4BBC00_STACK = 1456,
    LIFTED_F4BBF30_STACK = 104,
    LIFTED_F4BC1E0_STACK = 220,
    LIFTED_F4BCBC0_STACK = 144,
    LIFTED_F4BDDE0_STACK = 160,
    LIFTED_F4BF6A0_STACK = 112,
    LIFTED_F4C14B7_STACK = 160,
    LIFTED_F4C17DA_STACK = 232,
    LIFTED_F4C1E10_STACK = 80,
    LIFTED_F4C23F0_STACK = 144,
    LIFTED_F4C2780_STACK = 176,
    LIFTED_F4C29C0_STACK = 172,
    LIFTED_F4C2C50_STACK = 128,
    LIFTED_F4C2D60_STACK = 468,
    LIFTED_F4C4F60_STACK = 108,
    LIFTED_F4C5030_STACK = 116,
    LIFTED_F4C55A0_STACK = 112,
    LIFTED_F4C5740_STACK = 112,
    LIFTED_F4C6640_STACK = 132,
    LIFTED_F4C6FF0_STACK = 88,
    LIFTED_F4C8CD0_STACK = 216,
    LIFTED_F4C90E0_STACK = 236,
    LIFTED_F4CCC40_STACK = 72,
    LIFTED_F4CE740_STACK = 220,
    LIFTED_F4CE760_STACK = 220,
    LIFTED_F4CE7E0_STACK = 76,
    LIFTED_F4D5360_STACK = 120,
    LIFTED_F4D6300_STACK = 92,
    LIFTED_F4D88A0_STACK = 108,
    LIFTED_F4DBB30_STACK = 192,
    LIFTED_F4DBD20_STACK = 192,
    LIFTED_F4DC030_STACK = 216,
    LIFTED_F4DF978_STACK = 88,
    LIFTED_F4E0328_STACK = 128,
    LIFTED_F4E08F0_STACK = 72,
    LIFTED_F4E0B7C_STACK = 104,
    LIFTED_F4E0C0C_STACK = 88,
    LIFTED_F4E1200_STACK = 112,
    LIFTED_F4E3698_STACK = 68,
    LIFTED_F4E3E00_STACK = 124,
    LIFTED_F4E5748_STACK = 96,
    LIFTED_F4E59C4_STACK = 84,
    LIFTED_F4E6C37_STACK = 132,
    LIFTED_F4E7D80_STACK = 112,
    LIFTED_F4E9A30_STACK = 80,
    LIFTED_F4ED880_STACK = 136,
    LIFTED_F4ED984_STACK = 144,
    LIFTED_F4EDC0E_STACK = 88,
    LIFTED_F4EDDC4_STACK = 104
};

/* Original 0x40f1a0. */
uint32_t lifted_event_pack(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40f360. */
uint32_t lifted_module_load(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x410270. */
uint32_t lifted_f410270(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x413bd0. */
uint32_t lifted_f413bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c7b0. */
uint32_t lifted_f41c7b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d0e0. */
uint32_t lifted_f41d0e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41eab0. */
uint32_t lifted_f41eab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x420f10. */
uint32_t lifted_f420f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4220d0. */
uint32_t lifted_f4220d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4223d0. */
uint32_t lifted_f4223d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x422800. */
uint32_t lifted_f422800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x422c50. */
uint32_t lifted_f422c50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x422f50. */
uint32_t lifted_f422f50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4237d0. */
uint32_t lifted_f4237d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424990. */
uint32_t lifted_f424990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4288d0. */
uint32_t lifted_f4288d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b090. */
uint32_t lifted_player_preview_frames(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430930. */
uint32_t lifted_scene_layout(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x433180. */
uint32_t lifted_board_tile_cell(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x434300. */
uint32_t lifted_f434300(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4344e0. */
uint32_t lifted_f4344e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4346b0. */
uint32_t lifted_line_pass(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x434ee0. */
uint32_t lifted_figure_pass(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4378c0. */
uint32_t lifted_board_swirl_marked(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43bd90. */
uint32_t lifted_mode_colors(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441f20. */
uint32_t lifted_pattern_tables(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x442140. */
uint32_t lifted_f442140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443dc0. */
uint32_t lifted_f443dc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444700. */
uint32_t lifted_f444700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x449090. */
uint32_t lifted_f449090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x472f80. */
uint32_t lifted_f472f80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x478f50. */
uint32_t lifted_surface_fill(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4798b0. */
uint32_t lifted_f4798b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x479e50. */
uint32_t lifted_circle_points(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47ab70. */
uint32_t lifted_f47ab70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f410. */
uint32_t lifted_display_ready(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48b970. */
uint32_t lifted_f48b970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b17e0. */
uint32_t lifted_f4b17e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b3140. */
uint32_t lifted_f4b3140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bb170. */
uint32_t lifted_f4bb170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bb270. */
uint32_t lifted_f4bb270(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bb870. */
uint32_t lifted_f4bb870(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bbc00. */
uint32_t lifted_f4bbc00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bbf30. */
uint32_t lifted_f4bbf30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bc1e0. */
uint32_t lifted_f4bc1e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bcbc0. */
uint32_t lifted_f4bcbc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bdde0. */
uint32_t lifted_f4bdde0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bf6a0. */
uint32_t lifted_f4bf6a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c14b7. */
uint32_t lifted_f4c14b7(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c17da. */
uint32_t lifted_f4c17da(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c1e10. */
uint32_t lifted_f4c1e10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c23f0. */
uint32_t lifted_f4c23f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c2780. */
uint32_t lifted_f4c2780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c29c0. */
uint32_t lifted_f4c29c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c2c50. */
uint32_t lifted_f4c2c50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c2d60. */
uint32_t lifted_f4c2d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c4f60. */
uint32_t lifted_f4c4f60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5030. */
uint32_t lifted_f4c5030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c55a0. */
uint32_t lifted_f4c55a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c5740. */
uint32_t lifted_f4c5740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c6640. */
uint32_t lifted_f4c6640(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c6ff0. */
uint32_t lifted_f4c6ff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c8cd0. */
uint32_t lifted_f4c8cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c90e0. */
uint32_t lifted_f4c90e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccc40. */
uint32_t lifted_f4ccc40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce740. */
uint32_t lifted_f4ce740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce760. */
uint32_t lifted_f4ce760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce7e0. */
uint32_t lifted_f4ce7e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5360. */
uint32_t lifted_f4d5360(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d6300. */
uint32_t lifted_f4d6300(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d88a0. */
uint32_t lifted_f4d88a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dbb30. */
uint32_t lifted_f4dbb30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dbd20. */
uint32_t lifted_f4dbd20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc030. */
uint32_t lifted_f4dc030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4df978. */
uint32_t lifted_f4df978(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0328. */
uint32_t lifted_f4e0328(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e08f0. */
uint32_t lifted_f4e08f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0b7c. */
uint32_t lifted_f4e0b7c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0c0c. */
uint32_t lifted_f4e0c0c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e1200. */
uint32_t lifted_f4e1200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3698. */
uint32_t lifted_f4e3698(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3e00. */
uint32_t lifted_f4e3e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5748. */
uint32_t lifted_f4e5748(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e59c4. */
uint32_t lifted_f4e59c4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6c37. */
uint32_t lifted_f4e6c37(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7d80. */
uint32_t lifted_f4e7d80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9a30. */
uint32_t lifted_f4e9a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ed880. */
uint32_t lifted_f4ed880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ed984. */
uint32_t lifted_f4ed984(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4edc0e. */
uint32_t lifted_f4edc0e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eddc4. */
uint32_t lifted_f4eddc4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
