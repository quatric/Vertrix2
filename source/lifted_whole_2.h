#ifndef VERTRIX_LIFTED_WHOLE_2_H
#define VERTRIX_LIFTED_WHOLE_2_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F44CCD0_STACK = 152,
    LIFTED_F44D030_STACK = 152,
    LIFTED_F44DBB0_STACK = 124,
    LIFTED_F44DCF0_STACK = 128,
    LIFTED_BLOCK_ORBIT_UPDATE_STACK = 184,
    LIFTED_F44DFB0_STACK = 188,
    LIFTED_F44E120_STACK = 152,
    LIFTED_F44E2D0_STACK = 120,
    LIFTED_BLOCK_ACCELERATE_UPDATE_STACK = 124,
    LIFTED_F44E920_STACK = 136,
    LIFTED_F44E9F0_STACK = 140,
    LIFTED_F44EAF0_STACK = 136,
    LIFTED_BLOCK_SPIN_UPDATE_STACK = 168,
    LIFTED_F44EE20_STACK = 168,
    LIFTED_F450D40_STACK = 104,
    LIFTED_F450E70_STACK = 148,
    LIFTED_F450FF0_STACK = 304,
    LIFTED_STATE_DRAIN_451580_STACK = 124,
    LIFTED_OBJECT_POST_LOCK_STACK = 188,
    LIFTED_OBJECT_POST_LOCK_TWIN_STACK = 184,
    LIFTED_F451AA0_STACK = 164,
    LIFTED_F451C80_STACK = 164,
    LIFTED_STATE_CHOICE_APPLY_STACK = 144,
    LIFTED_STATE_CHOICE_TAKE_STACK = 172,
    LIFTED_STATE_MATCH_452160_STACK = 136,
    LIFTED_OBJECT_ENTER_ATTACK_STACK = 108,
    LIFTED_F452370_STACK = 88,
    LIFTED_STATE_ATTACK_452440_STACK = 136,
    LIFTED_STATE_ADVANCE_452770_STACK = 120,
    LIFTED_EFFECT_ARMED_HANDLER_STACK = 128,
    LIFTED_EFFECT_BOARD_MATCH_STACK = 192,
    LIFTED_EFFECT_CONVERT_BLOCKS_STACK = 160,
    LIFTED_STATE_PAIR_4533B0_STACK = 128,
    LIFTED_EFFECT_FORCED_CHOICE_STACK = 132,
    LIFTED_EFFECT_SLIDE_START_STACK = 120,
    LIFTED_F453D50_STACK = 172,
    LIFTED_EFFECT_SLIDE_START_453FD0_STACK = 120,
    LIFTED_F454090_STACK = 156,
    LIFTED_EFFECT_SLIDE_START_4542E0_STACK = 120,
    LIFTED_F4543A0_STACK = 156,
    LIFTED_STATE_CYCLE_4546A0_STACK = 128,
    LIFTED_F454830_STACK = 132,
    LIFTED_F454A50_STACK = 132,
    LIFTED_STATE_DRAIN_454B20_STACK = 120,
    LIFTED_F454CB0_STACK = 132,
    LIFTED_STATE_DRAIN_454D80_STACK = 120,
    LIFTED_EFFECT_ATTACK_454E90_STACK = 104,
    LIFTED_F454F00_STACK = 132,
    LIFTED_F4550A0_STACK = 196,
    LIFTED_STATE_GUARD_4553A0_STACK = 132,
    LIFTED_F455830_STACK = 128,
    LIFTED_EFFECT_ATTACK_455B20_STACK = 104,
    LIFTED_EFFECT_ATTACK_455CA0_STACK = 104,
    LIFTED_EFFECT_SLIDE_BEGIN_STACK = 128,
    LIFTED_EFFECT_SLIDE_ADVANCE_STACK = 132,
    LIFTED_F4560C0_STACK = 136,
    LIFTED_F456170_STACK = 144,
    LIFTED_F456BF0_STACK = 100,
    LIFTED_F456CD0_STACK = 108,
    LIFTED_F4570B0_STACK = 124,
    LIFTED_F4571F0_STACK = 124,
    LIFTED_UI_CENTER_ON_ANCHOR_STACK = 92,
    LIFTED_F4578F0_STACK = 128,
    LIFTED_F457A00_STACK = 140,
    LIFTED_F457C10_STACK = 128,
    LIFTED_F457D10_STACK = 136,
    LIFTED_F457E40_STACK = 124,
    LIFTED_F457F40_STACK = 148,
    LIFTED_F458150_STACK = 124,
    LIFTED_F4585C0_STACK = 144,
    LIFTED_F4587A0_STACK = 136,
    LIFTED_F458880_STACK = 160,
    LIFTED_F458A70_STACK = 140,
    LIFTED_F458C20_STACK = 144,
    LIFTED_F458D40_STACK = 124,
    LIFTED_F458F00_STACK = 116,
    LIFTED_F459100_STACK = 144,
    LIFTED_F459290_STACK = 140,
    LIFTED_F4593B0_STACK = 136,
    LIFTED_F4594A0_STACK = 140,
    LIFTED_TITLE_LETTER_COUNT_CALL_STACK = 168,
    LIFTED_TITLE_LETTER_RESTART_CALL_STACK = 144,
    LIFTED_TITLE_LETTER_LAUNCH_CALL_STACK = 124,
    LIFTED_TITLE_LETTER_FIGHT_COUNT_CALL_STACK = 144,
    LIFTED_TITLE_LETTER_FIGHT_RESTART_CALL_STACK = 124,
    LIFTED_TITLE_LETTER_FIGHT_FLY_CALL_STACK = 140,
    LIFTED_TITLE_LETTER_WAVE_COUNT_CALL_STACK = 136,
    LIFTED_TITLE_LETTER_WAVE_CALL_STACK = 132,
    LIFTED_TITLE_LETTER_WAVE_CALL_45A830_STACK = 132,
    LIFTED_TITLE_LETTER_WAVE_FLY_CALL_STACK = 140,
    LIFTED_F45AAB0_STACK = 156,
    LIFTED_F45AC70_STACK = 132,
    LIFTED_F45AD20_STACK = 140,
    LIFTED_F45B190_STACK = 168,
    LIFTED_F45B4C0_STACK = 136,
    LIFTED_F45B5F0_STACK = 152,
    LIFTED_EFFECT_ATTACK_45B9C0_STACK = 104,
    LIFTED_F45BAD0_STACK = 120
};

/* Original 0x44ccd0. */
uint32_t lifted_f44ccd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d030. */
uint32_t lifted_f44d030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44dbb0. */
uint32_t lifted_f44dbb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44dcf0. */
uint32_t lifted_f44dcf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44de20. */
uint32_t lifted_block_orbit_update(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44dfb0. */
uint32_t lifted_f44dfb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e120. */
uint32_t lifted_f44e120(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e2d0. */
uint32_t lifted_f44e2d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e6e0. */
uint32_t lifted_block_accelerate_update(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
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

/* Original 0x44ece0. */
uint32_t lifted_block_spin_update(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ee20. */
uint32_t lifted_f44ee20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450d40. */
uint32_t lifted_f450d40(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x451920. */
uint32_t lifted_object_post_lock_twin(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451aa0. */
uint32_t lifted_f451aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451c80. */
uint32_t lifted_f451c80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451e20. */
uint32_t lifted_state_choice_apply(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451f50. */
uint32_t lifted_state_choice_take(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452160. */
uint32_t lifted_state_match_452160(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4522c0. */
uint32_t lifted_object_enter_attack(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452370. */
uint32_t lifted_f452370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452440. */
uint32_t lifted_state_attack_452440(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452770. */
uint32_t lifted_state_advance_452770(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452a50. */
uint32_t lifted_effect_armed_handler(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452e00. */
uint32_t lifted_effect_board_match(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453150. */
uint32_t lifted_effect_convert_blocks(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4533b0. */
uint32_t lifted_state_pair_4533b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453ad0. */
uint32_t lifted_effect_forced_choice(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453c90. */
uint32_t lifted_effect_slide_start(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453d50. */
uint32_t lifted_f453d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453fd0. */
uint32_t lifted_effect_slide_start_453fd0(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454090. */
uint32_t lifted_f454090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4542e0. */
uint32_t lifted_effect_slide_start_4542e0(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4543a0. */
uint32_t lifted_f4543a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4546a0. */
uint32_t lifted_state_cycle_4546a0(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454830. */
uint32_t lifted_f454830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454a50. */
uint32_t lifted_f454a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454b20. */
uint32_t lifted_state_drain_454b20(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454cb0. */
uint32_t lifted_f454cb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454d80. */
uint32_t lifted_state_drain_454d80(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454e90. */
uint32_t lifted_effect_attack_454e90(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454f00. */
uint32_t lifted_f454f00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4550a0. */
uint32_t lifted_f4550a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4553a0. */
uint32_t lifted_state_guard_4553a0(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455830. */
uint32_t lifted_f455830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455b20. */
uint32_t lifted_effect_attack_455b20(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455ca0. */
uint32_t lifted_effect_attack_455ca0(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455e50. */
uint32_t lifted_effect_slide_begin(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455f80. */
uint32_t lifted_effect_slide_advance(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4560c0. */
uint32_t lifted_f4560c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456170. */
uint32_t lifted_f456170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456bf0. */
uint32_t lifted_f456bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456cd0. */
uint32_t lifted_f456cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4578f0. */
uint32_t lifted_f4578f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457a00. */
uint32_t lifted_f457a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457c10. */
uint32_t lifted_f457c10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457d10. */
uint32_t lifted_f457d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457e40. */
uint32_t lifted_f457e40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457f40. */
uint32_t lifted_f457f40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458150. */
uint32_t lifted_f458150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4585c0. */
uint32_t lifted_f4585c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4587a0. */
uint32_t lifted_f4587a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458880. */
uint32_t lifted_f458880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458a70. */
uint32_t lifted_f458a70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458c20. */
uint32_t lifted_f458c20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458d40. */
uint32_t lifted_f458d40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458f00. */
uint32_t lifted_f458f00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459100. */
uint32_t lifted_f459100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459290. */
uint32_t lifted_f459290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4593b0. */
uint32_t lifted_f4593b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4594a0. */
uint32_t lifted_f4594a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459be0. */
uint32_t lifted_title_letter_count_call(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459e00. */
uint32_t lifted_title_letter_restart_call(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a0c0. */
uint32_t lifted_title_letter_launch_call(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a290. */
uint32_t lifted_title_letter_fight_count_call(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x45a440. */
uint32_t lifted_title_letter_fight_restart_call(const VertrixCalls *calls,
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

/* Original 0x45a750. */
uint32_t lifted_title_letter_wave_call(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a830. */
uint32_t lifted_title_letter_wave_call_45a830(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x45a910. */
uint32_t lifted_title_letter_wave_fly_call(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45aab0. */
uint32_t lifted_f45aab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x45b4c0. */
uint32_t lifted_f45b4c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b5f0. */
uint32_t lifted_f45b5f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b9c0. */
uint32_t lifted_effect_attack_45b9c0(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bad0. */
uint32_t lifted_f45bad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
