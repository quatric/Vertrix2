#ifndef VERTRIX_LIFTED_WHOLE_1_H
#define VERTRIX_LIFTED_WHOLE_1_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4314A0_STACK = 160,
    LIFTED_F432A30_STACK = 392,
    LIFTED_BOARD_SWAP_SLOTS_STACK = 72,
    LIFTED_F433840_STACK = 272,
    LIFTED_F433E20_STACK = 216,
    LIFTED_BOARD_SWAP_MARKED_STACK = 220,
    LIFTED_BOARD_COLLAPSE_MARKED_STACK = 168,
    LIFTED_BOARD_CLEAR_MARKED_EXTRA_STACK = 112,
    LIFTED_F43A6F0_STACK = 168,
    LIFTED_F43AD70_STACK = 328,
    LIFTED_F43C140_STACK = 84,
    LIFTED_PIECE_STACK = 116,
    LIFTED_BOARD_PARTICLES_SETUP_STACK = 264,
    LIFTED_F43F200_STACK = 752,
    LIFTED_FONT_MAPS_INITIALIZE_STACK = 520,
    LIFTED_F440490_STACK = 136,
    LIFTED_F440D50_STACK = 244,
    LIFTED_F440FC0_STACK = 176,
    LIFTED_F441600_STACK = 496,
    LIFTED_F441B70_STACK = 408,
    LIFTED_F443550_STACK = 132,
    LIFTED_F444020_STACK = 160,
    LIFTED_F4443D0_STACK = 112,
    LIFTED_F444A80_STACK = 128,
    LIFTED_F444E00_STACK = 248,
    LIFTED_F445350_STACK = 272,
    LIFTED_F445B90_STACK = 180,
    LIFTED_F44A720_STACK = 200,
    LIFTED_F44BC50_STACK = 236
};

/* Original 0x4314a0. */
uint32_t lifted_f4314a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432a30. */
uint32_t lifted_f432a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432ba0. */
uint32_t lifted_board_swap_slots(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x438540. */
uint32_t lifted_board_collapse_marked(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
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

/* Original 0x43c140. */
uint32_t lifted_f43c140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d180. */
uint32_t lifted_piece(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x441600. */
uint32_t lifted_f441600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x441b70. */
uint32_t lifted_f441b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x443550. */
uint32_t lifted_f443550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444020. */
uint32_t lifted_f444020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4443d0. */
uint32_t lifted_f4443d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444a80. */
uint32_t lifted_f444a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x444e00. */
uint32_t lifted_f444e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445350. */
uint32_t lifted_f445350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x445b90. */
uint32_t lifted_f445b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44a720. */
uint32_t lifted_f44a720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44bc50. */
uint32_t lifted_f44bc50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
