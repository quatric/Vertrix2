#ifndef VERTRIX_LIFTED_WHOLE_1_H
#define VERTRIX_LIFTED_WHOLE_1_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_BOARD_RINGS_STACK = 204,
    LIFTED_BOARD_BURST_STACK = 180,
    LIFTED_BOARD_PIECE_COLUMN_STACK = 96,
    LIFTED_F4314A0_STACK = 160,
    LIFTED_BOARD_DEAL_FIRST_ROW_STACK = 140,
    LIFTED_BOARD_DEAL_SECOND_ROW_STACK = 140,
    LIFTED_BOARD_PIECE_SPAN_STACK = 104,
    LIFTED_F431D90_STACK = 184,
    LIFTED_BOARD_PIECE_PAST_EDGE_STACK = 100,
    LIFTED_BOARD_PIECE_PAST_EDGE_432080_STACK = 100,
    LIFTED_BOARD_ANY_FALLING_STACK = 348,
    LIFTED_F432980_STACK = 368,
    LIFTED_F432A30_STACK = 392,
    LIFTED_BOARD_SWAP_SLOTS_STACK = 72,
    LIFTED_BOARD_MARKER_REACH_STACK = 116,
    LIFTED_F433840_STACK = 272,
    LIFTED_F433E20_STACK = 216,
    LIFTED_BOARD_SWAP_MARKED_STACK = 220,
    LIFTED_BOARD_REPLACE_RANDOM_CELL_STACK = 152,
    LIFTED_BOARD_REPLACE_CELL_STACK = 148,
    LIFTED_BOARD_SCATTER_MARKED_STACK = 168,
    LIFTED_BOARD_SPLIT_MARKED_STACK = 160,
    LIFTED_BOARD_COLLAPSE_MARKED_STACK = 168,
    LIFTED_BOARD_SET_MOTION_STACK = 156,
    LIFTED_F438EF0_STACK = 180,
    LIFTED_F439510_STACK = 180,
    LIFTED_BOARD_CLEAR_MARKED_EXTRA_STACK = 112,
    LIFTED_F43A6F0_STACK = 168,
    LIFTED_F43AD70_STACK = 328,
    LIFTED_F43B260_STACK = 172,
    LIFTED_F43C140_STACK = 84,
    LIFTED_PIECE_STACK = 116,
    LIFTED_F43D370_STACK = 80,
    LIFTED_SLOT_OBJECT_CONSTRUCT_STACK = 136,
    LIFTED_PARTICLE_EMIT_STACK = 156,
    LIFTED_SPAWN_SPREAD_FULL_STACK = 108,
    LIFTED_BOARD_PARTICLES_SETUP_STACK = 264,
    LIFTED_F43F200_STACK = 752,
    LIFTED_FONT_MAPS_INITIALIZE_STACK = 520,
    LIFTED_F440490_STACK = 136,
    LIFTED_F440D50_STACK = 244,
    LIFTED_F440FC0_STACK = 176,
    LIFTED_FORWARD_4EA190_STACK = 68,
    LIFTED_F441600_STACK = 496,
    LIFTED_F441B70_STACK = 408,
    LIFTED_F4429A0_STACK = 92,
    LIFTED_F443550_STACK = 132,
    LIFTED_F443890_STACK = 148,
    LIFTED_F443AB0_STACK = 96,
    LIFTED_F444020_STACK = 160,
    LIFTED_F4443D0_STACK = 112,
    LIFTED_F444970_STACK = 124,
    LIFTED_F444A80_STACK = 128,
    LIFTED_F444C80_STACK = 184,
    LIFTED_F444E00_STACK = 248,
    LIFTED_F4451D0_STACK = 184,
    LIFTED_F445350_STACK = 272,
    LIFTED_F445B90_STACK = 180,
    LIFTED_F446850_STACK = 172,
    LIFTED_F4473B0_STACK = 176,
    LIFTED_F448810_STACK = 176,
    LIFTED_F44A720_STACK = 200,
    LIFTED_F44BC50_STACK = 236,
    LIFTED_F44BF70_STACK = 264
};

/* Original 0x430440. */
uint32_t lifted_board_rings(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430660. */
uint32_t lifted_board_burst(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431340. */
uint32_t lifted_board_piece_column(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4314a0. */
uint32_t lifted_f4314a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431780. */
uint32_t lifted_board_deal_first_row(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431930. */
uint32_t lifted_board_deal_second_row(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431b20. */
uint32_t lifted_board_piece_span(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x431d90. */
uint32_t lifted_f431d90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432040. */
uint32_t lifted_board_piece_past_edge(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432080. */
uint32_t lifted_board_piece_past_edge_432080(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4328a0. */
uint32_t lifted_board_any_falling(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432980. */
uint32_t lifted_f432980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432a30. */
uint32_t lifted_f432a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432ba0. */
uint32_t lifted_board_swap_slots(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x433550. */
uint32_t lifted_board_marker_reach(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x433840. */
uint32_t lifted_f433840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x433e20. */
uint32_t lifted_f433e20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436150. */
uint32_t lifted_board_swap_marked(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436440. */
uint32_t lifted_board_replace_random_cell(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4365c0. */
uint32_t lifted_board_replace_cell(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x437be0. */
uint32_t lifted_board_scatter_marked(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x437d70. */
uint32_t lifted_board_split_marked(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438540. */
uint32_t lifted_board_collapse_marked(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438960. */
uint32_t lifted_board_set_motion(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x438ef0. */
uint32_t lifted_f438ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x439510. */
uint32_t lifted_f439510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4398c0. */
uint32_t lifted_board_clear_marked_extra(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a6f0. */
uint32_t lifted_f43a6f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43ad70. */
uint32_t lifted_f43ad70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43b260. */
uint32_t lifted_f43b260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43c140. */
uint32_t lifted_f43c140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d180. */
uint32_t lifted_piece(const VertrixCalls *calls, const VertrixFactoryServices *services,
                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d370. */
uint32_t lifted_f43d370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d6a0. */
uint32_t lifted_slot_object_construct(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43dc80. */
uint32_t lifted_particle_emit(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43dea0. */
uint32_t lifted_spawn_spread_full(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43e4d0. */
uint32_t lifted_board_particles_setup(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43f200. */
uint32_t lifted_f43f200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43fc50. */
uint32_t lifted_font_maps_initialize(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x440490. */
uint32_t lifted_f440490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x440d50. */
uint32_t lifted_f440d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x440fc0. */
uint32_t lifted_f440fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441120. */
uint32_t lifted_forward_4ea190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441600. */
uint32_t lifted_f441600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441b70. */
uint32_t lifted_f441b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4429a0. */
uint32_t lifted_f4429a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443550. */
uint32_t lifted_f443550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443890. */
uint32_t lifted_f443890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443ab0. */
uint32_t lifted_f443ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444020. */
uint32_t lifted_f444020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4443d0. */
uint32_t lifted_f4443d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444970. */
uint32_t lifted_f444970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444a80. */
uint32_t lifted_f444a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444c80. */
uint32_t lifted_f444c80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444e00. */
uint32_t lifted_f444e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4451d0. */
uint32_t lifted_f4451d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445350. */
uint32_t lifted_f445350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445b90. */
uint32_t lifted_f445b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x446850. */
uint32_t lifted_f446850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4473b0. */
uint32_t lifted_f4473b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x448810. */
uint32_t lifted_f448810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44a720. */
uint32_t lifted_f44a720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44bc50. */
uint32_t lifted_f44bc50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44bf70. */
uint32_t lifted_f44bf70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
