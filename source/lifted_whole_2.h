#ifndef VERTRIX_LIFTED_WHOLE_2_H
#define VERTRIX_LIFTED_WHOLE_2_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F44DBB0_STACK = 124,
    LIFTED_BLOCK_ORBIT_UPDATE_STACK = 184,
    LIFTED_F44DFB0_STACK = 188,
    LIFTED_F44E920_STACK = 136,
    LIFTED_F44E9F0_STACK = 140,
    LIFTED_F44EAF0_STACK = 136,
    LIFTED_F450E70_STACK = 148,
    LIFTED_F450FF0_STACK = 304,
    LIFTED_STATE_DRAIN_451580_STACK = 124,
    LIFTED_OBJECT_POST_LOCK_STACK = 188,
    LIFTED_F452370_STACK = 88,
    LIFTED_EFFECT_BOARD_MATCH_STACK = 192,
    LIFTED_F453D50_STACK = 172,
    LIFTED_EFFECT_ATTACK_454E90_STACK = 104,
    LIFTED_F4550A0_STACK = 196,
    LIFTED_EFFECT_ATTACK_455B20_STACK = 104,
    LIFTED_EFFECT_ATTACK_455CA0_STACK = 104,
    LIFTED_F4570B0_STACK = 124,
    LIFTED_F4571F0_STACK = 124,
    LIFTED_UI_CENTER_ON_ANCHOR_STACK = 92,
    LIFTED_F457A00_STACK = 140,
    LIFTED_F457F40_STACK = 148,
    LIFTED_F4585C0_STACK = 144,
    LIFTED_F458A70_STACK = 140,
    LIFTED_F4594A0_STACK = 140,
    LIFTED_TITLE_LETTER_COUNT_CALL_STACK = 168,
    LIFTED_TITLE_LETTER_FIGHT_COUNT_CALL_STACK = 144,
    LIFTED_TITLE_LETTER_FIGHT_FLY_CALL_STACK = 140,
    LIFTED_TITLE_LETTER_WAVE_COUNT_CALL_STACK = 136,
    LIFTED_TITLE_LETTER_WAVE_FLY_CALL_STACK = 140,
    LIFTED_F45AC70_STACK = 132,
    LIFTED_F45AD20_STACK = 140,
    LIFTED_F45B190_STACK = 168,
    LIFTED_EFFECT_ATTACK_45B9C0_STACK = 104
};

/* Original 0x44dbb0. */
uint32_t lifted_f44dbb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44de20. */
uint32_t lifted_block_orbit_update(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44dfb0. */
uint32_t lifted_f44dfb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e920. */
uint32_t lifted_f44e920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e9f0. */
uint32_t lifted_f44e9f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44eaf0. */
uint32_t lifted_f44eaf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450e70. */
uint32_t lifted_f450e70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450ff0. */
uint32_t lifted_f450ff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451580. */
uint32_t lifted_state_drain_451580(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4517c0. */
uint32_t lifted_object_post_lock(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452370. */
uint32_t lifted_f452370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452e00. */
uint32_t lifted_effect_board_match(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453d50. */
uint32_t lifted_f453d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454e90. */
uint32_t lifted_effect_attack_454e90(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4550a0. */
uint32_t lifted_f4550a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455b20. */
uint32_t lifted_effect_attack_455b20(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455ca0. */
uint32_t lifted_effect_attack_455ca0(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4570b0. */
uint32_t lifted_f4570b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4571f0. */
uint32_t lifted_f4571f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457890. */
uint32_t lifted_ui_center_on_anchor(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457a00. */
uint32_t lifted_f457a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457f40. */
uint32_t lifted_f457f40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4585c0. */
uint32_t lifted_f4585c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458a70. */
uint32_t lifted_f458a70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4594a0. */
uint32_t lifted_f4594a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459be0. */
uint32_t lifted_title_letter_count_call(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a290. */
uint32_t lifted_title_letter_fight_count_call(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x45a4f0. */
uint32_t lifted_title_letter_fight_fly_call(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a620. */
uint32_t lifted_title_letter_wave_count_call(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a910. */
uint32_t lifted_title_letter_wave_fly_call(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ac70. */
uint32_t lifted_f45ac70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ad20. */
uint32_t lifted_f45ad20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b190. */
uint32_t lifted_f45b190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b9c0. */
uint32_t lifted_effect_attack_45b9c0(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

#endif
