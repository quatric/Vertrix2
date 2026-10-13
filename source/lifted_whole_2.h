#ifndef VERTRIX_LIFTED_WHOLE_2_H
#define VERTRIX_LIFTED_WHOLE_2_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_PIECE_CHILD_UPDATE_44C2B0_STACK = 104,
    LIFTED_PIECE_CHILD_UPDATE_44C310_STACK = 104,
    LIFTED_PIECE_CHILD_UPDATE_44C370_STACK = 104,
    LIFTED_F44C3D0_STACK = 68,
    LIFTED_F44C3E0_STACK = 108,
    LIFTED_F44C450_STACK = 108,
    LIFTED_F44C4C0_STACK = 108,
    LIFTED_F44C530_STACK = 108,
    LIFTED_F44C5A0_STACK = 104,
    LIFTED_F44C610_STACK = 104,
    LIFTED_F44C680_STACK = 104,
    LIFTED_F44C6E0_STACK = 104,
    LIFTED_F44C780_STACK = 108,
    LIFTED_F44C7F0_STACK = 108,
    LIFTED_BLOCK_UPDATE_STACK = 76,
    LIFTED_BLOCK_MOTION_UPDATE_STACK = 108,
    LIFTED_F44C8E0_STACK = 108,
    LIFTED_F44C940_STACK = 76,
    LIFTED_BLOCK_FADE_UPDATE_STACK = 108,
    LIFTED_BLOCK_PULSE_UPDATE_STACK = 108,
    LIFTED_F44CA40_STACK = 108,
    LIFTED_F44CAB0_STACK = 120,
    LIFTED_F44CB50_STACK = 120,
    LIFTED_BLOCK_BYTE_PULSE_UPDATE_STACK = 108,
    LIFTED_BLOCK_BYTE_PULSE_UPDATE_44CC60_STACK = 108,
    LIFTED_F44CCD0_STACK = 152,
    LIFTED_BLOCK_SCALE_UPDATE_STACK = 108,
    LIFTED_BLOCK_RETURN_UPDATE_STACK = 108,
    LIFTED_F44CF70_STACK = 108,
    LIFTED_F44CFD0_STACK = 108,
    LIFTED_F44D030_STACK = 152,
    LIFTED_F44D1E0_STACK = 108,
    LIFTED_F44D250_STACK = 108,
    LIFTED_F44D2C0_STACK = 108,
    LIFTED_F44D330_STACK = 108,
    LIFTED_F44D3A0_STACK = 108,
    LIFTED_BLOCK_BYTE_PULSE_UPDATE_44D410_STACK = 108,
    LIFTED_F44D480_STACK = 108,
    LIFTED_F44D4F0_STACK = 108,
    LIFTED_F44D560_STACK = 120,
    LIFTED_F44D5F0_STACK = 108,
    LIFTED_F44D660_STACK = 108,
    LIFTED_F44D6D0_STACK = 120,
    LIFTED_BLOCK_BYTE_PULSE_UPDATE_44D760_STACK = 108,
    LIFTED_F44D7D0_STACK = 108,
    LIFTED_F44D840_STACK = 108,
    LIFTED_BLOCK_MODE_PULSE_UPDATE_STACK = 116,
    LIFTED_F44D940_STACK = 116,
    LIFTED_F44D9D0_STACK = 120,
    LIFTED_BLOCK_HALF_PULSE_UPDATE_STACK = 120,
    LIFTED_F44DB10_STACK = 120,
    LIFTED_F44DBB0_STACK = 124,
    LIFTED_F44DC80_STACK = 108,
    LIFTED_F44DCF0_STACK = 128,
    LIFTED_BLOCK_ORBIT_UPDATE_STACK = 184,
    LIFTED_F44DFB0_STACK = 188,
    LIFTED_F44E120_STACK = 152,
    LIFTED_BLOCK_SLIDE_UPDATE_STACK = 120,
    LIFTED_F44E2D0_STACK = 120,
    LIFTED_BLOCK_COLLAPSE_UPDATE_STACK = 120,
    LIFTED_F44E410_STACK = 116,
    LIFTED_BLOCK_VISIBILITY_UPDATE_STACK = 108,
    LIFTED_F44E510_STACK = 108,
    LIFTED_BLOCK_SWELL_UPDATE_STACK = 108,
    LIFTED_F44E600_STACK = 108,
    LIFTED_F44E670_STACK = 108,
    LIFTED_BLOCK_ACCELERATE_UPDATE_STACK = 124,
    LIFTED_BLOCK_MODE_AMOUNT_UPDATE_STACK = 108,
    LIFTED_F44E800_STACK = 120,
    LIFTED_BLOCK_PERIOD_UPDATE_STACK = 116,
    LIFTED_F44E920_STACK = 136,
    LIFTED_F44E9F0_STACK = 140,
    LIFTED_F44EAF0_STACK = 136,
    LIFTED_BLOCK_TRAVEL_UPDATE_STACK = 108,
    LIFTED_F44EC40_STACK = 120,
    LIFTED_BLOCK_SPIN_UPDATE_STACK = 168,
    LIFTED_F44EE20_STACK = 168,
    LIFTED_F44F040_STACK = 108,
    LIFTED_F44F0B0_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F180_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F1E0_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F240_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F2B0_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F320_STACK = 108,
    LIFTED_BLOCK_CYCLE_UPDATE_STACK = 104,
    LIFTED_F44F3E0_STACK = 104,
    LIFTED_F44F430_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F4A0_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F500_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F560_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F5D0_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F630_STACK = 108,
    LIFTED_BLOCK_EFFECT_UPDATE_44F690_STACK = 108,
    LIFTED_F44F700_STACK = 108,
    LIFTED_F44F770_STACK = 108,
    LIFTED_F44F7E0_STACK = 120,
    LIFTED_F44F880_STACK = 120,
    LIFTED_F44F920_STACK = 108,
    LIFTED_F44F990_STACK = 108,
    LIFTED_F44FA00_STACK = 108,
    LIFTED_NUMBER_PLAYER_UPDATE_STACK = 80,
    LIFTED_F44FAA0_STACK = 84,
    LIFTED_NUMBER_TRANSITION_UPDATE_STACK = 100,
    LIFTED_NUMBER_TRANSITION_UPDATE_44FB40_STACK = 104,
    LIFTED_NUMBER_TRANSITION_UPDATE_44FBB0_STACK = 96,
    LIFTED_F44FC00_STACK = 80,
    LIFTED_F44FC30_STACK = 84,
    LIFTED_NUMBER_TRANSITION_CONFIGURED_STACK = 104,
    LIFTED_NUMBER_TRANSITION_CONFIGURED_44FCF0_STACK = 104,
    LIFTED_NUMBER_TRANSITION_CONFIGURED_44FD60_STACK = 96,
    LIFTED_NUMBER_TRANSITION_CONFIGURED_44FDB0_STACK = 108,
    LIFTED_NUMBER_TRANSITION_CONFIGURED_44FE30_STACK = 96,
    LIFTED_PLAYER_INDICATOR_UPDATE_STACK = 84,
    LIFTED_PLAYER_INDICATOR_UPDATE_44FED0_STACK = 96,
    LIFTED_PLAYER_INDICATOR_UPDATE_44FF30_STACK = 88,
    LIFTED_PLAYER_INDICATOR_UPDATE_44FF60_STACK = 80,
    LIFTED_UI_INDICATOR_STORAGE_UPDATE_STACK = 88,
    LIFTED_UI_INDICATOR_STORAGE_UPDATE_44FFF0_STACK = 96,
    LIFTED_UI_INDICATOR_STORAGE_UPDATE_450040_STACK = 92,
    LIFTED_UI_INDICATOR_STORAGE_UPDATE_4500B0_STACK = 100,
    LIFTED_UI_INDICATOR_STORAGE_UPDATE_450100_STACK = 80,
    LIFTED_UI_BORDER_STORAGE_UPDATE_STACK = 92,
    LIFTED_UI_BORDER_STORAGE_UPDATE_4501A0_STACK = 96,
    LIFTED_UI_BORDER_STORAGE_UPDATE_450200_STACK = 96,
    LIFTED_UI_BORDER_STORAGE_UPDATE_450270_STACK = 108,
    LIFTED_UI_BORDER_STORAGE_UPDATE_450300_STACK = 80,
    LIFTED_BLOCK_FINISH_EFFECT_UPDATE_STACK = 108,
    LIFTED_BLOCK_FINISH_EFFECT_UPDATE_4503B0_STACK = 124,
    LIFTED_BLOCK_FINISH_EFFECT_UPDATE_450450_STACK = 120,
    LIFTED_BLOCK_FINISH_EFFECT_UPDATE_4504E0_STACK = 104,
    LIFTED_BLOCK_FINISH_EFFECT_UPDATE_450550_STACK = 108,
    LIFTED_BLOCK_FINISH_EFFECT_UPDATE_4505C0_STACK = 108,
    LIFTED_BLOCK_FINISH_EFFECT_UPDATE_450630_STACK = 104,
    LIFTED_BLOCK_FINISH_EFFECT_UPDATE_4506A0_STACK = 108,
    LIFTED_BLOCK_ANIMATION_UPDATE_STACK = 76,
    LIFTED_BLOCK_ANIMATION_UPDATE_450730_STACK = 76,
    LIFTED_PLAYER_COUNTDOWN_UPDATE_STACK = 96,
    LIFTED_PLAYER_COUNTDOWN_UPDATE_4507E0_STACK = 88,
    LIFTED_PLAYER_COUNTDOWN_UPDATE_450830_STACK = 88,
    LIFTED_UI_COMPANION_STORAGE_UPDATE_STACK = 88,
    LIFTED_UI_COMPANION_STORAGE_UPDATE_4508C0_STACK = 104,
    LIFTED_UI_COMPANION_STORAGE_UPDATE_450920_STACK = 84,
    LIFTED_UI_COMPANION_STORAGE_UPDATE_450960_STACK = 96,
    LIFTED_UI_COMPANION_STORAGE_UPDATE_4509A0_STACK = 88,
    LIFTED_UI_COMPANION_STORAGE_UPDATE_4509D0_STACK = 80,
    LIFTED_LINKED_ALTERNATING_UPDATE_STACK = 104,
    LIFTED_LINKED_ALTERNATING_UPDATE_450AA0_STACK = 116,
    LIFTED_LINKED_ALTERNATING_UPDATE_450B30_STACK = 96,
    LIFTED_LINKED_ALTERNATING_UPDATE_450B90_STACK = 96,
    LIFTED_LINKED_ALTERNATING_UPDATE_450BF0_STACK = 100,
    LIFTED_LINKED_ALTERNATING_UPDATE_450C70_STACK = 100,
    LIFTED_F450CD0_STACK = 104,
    LIFTED_F450D40_STACK = 104,
    LIFTED_F450DF0_STACK = 92,
    LIFTED_F450E70_STACK = 148,
    LIFTED_F450F60_STACK = 72,
    LIFTED_F450FF0_STACK = 304,
    LIFTED_F4513D0_STACK = 72,
    LIFTED_F4513F0_STACK = 116,
    LIFTED_STATE_STEPS_451490_STACK = 120,
    LIFTED_STATE_GATE_451520_STACK = 100,
    LIFTED_STATE_DRAIN_451580_STACK = 124,
    LIFTED_STATE_CHECK_451630_STACK = 100,
    LIFTED_STATE_START_451690_STACK = 116,
    LIFTED_STATE_STEPS_451730_STACK = 116,
    LIFTED_OBJECT_POST_LOCK_STACK = 188,
    LIFTED_OBJECT_POST_LOCK_TWIN_STACK = 184,
    LIFTED_PLAYER_START_BONUS_STACK = 88,
    LIFTED_F451AA0_STACK = 164,
    LIFTED_F451C00_STACK = 108,
    LIFTED_F451C80_STACK = 164,
    LIFTED_STATE_CHOICE_CHECK_STACK = 92,
    LIFTED_STATE_CHOICE_APPLY_STACK = 144,
    LIFTED_F451F10_STACK = 92,
    LIFTED_STATE_CHOICE_TAKE_STACK = 172,
    LIFTED_F452050_STACK = 72,
    LIFTED_F452070_STACK = 88,
    LIFTED_F4520B0_STACK = 88,
    LIFTED_F4520F0_STACK = 112,
    LIFTED_STATE_MATCH_452160_STACK = 136,
    LIFTED_OBJECT_ARM_HOLD_STACK = 96,
    LIFTED_OBJECT_ENTER_ATTACK_STACK = 108,
    LIFTED_F452370_STACK = 88,
    LIFTED_F4523D0_STACK = 88,
    LIFTED_STATE_ATTACK_452440_STACK = 136,
    LIFTED_F4526E0_STACK = 116,
    LIFTED_STATE_ADVANCE_452770_STACK = 120,
    LIFTED_EFFECT_NEGATED_GATE_STACK = 100,
    LIFTED_EFFECT_VALUE_GATE_STACK = 104,
    LIFTED_EFFECT_PROGRESS_GATE_STACK = 112,
    LIFTED_EFFECT_ARM_HANDLER_STACK = 80,
    LIFTED_EFFECT_ARMED_HANDLER_STACK = 128,
    LIFTED_EFFECT_ARM_HANDLER_452B00_STACK = 80,
    LIFTED_EFFECT_ARMED_HANDLER_452B20_STACK = 116,
    LIFTED_EFFECT_ARM_HANDLER_452BB0_STACK = 80,
    LIFTED_EFFECT_ARMED_HANDLER_452BD0_STACK = 116,
    LIFTED_EFFECT_ARM_HANDLER_452C60_STACK = 80,
    LIFTED_EFFECT_ARMED_HANDLER_452C80_STACK = 116,
    LIFTED_EFFECT_PROGRESS_UPDATE_GATE_STACK = 104,
    LIFTED_EFFECT_PROGRESS_COMPARE_STACK = 128,
    LIFTED_EFFECT_BOARD_MATCH_STACK = 192,
    LIFTED_F452FC0_STACK = 104,
    LIFTED_EFFECT_CONVERT_BLOCKS_STACK = 160,
    LIFTED_F453280_STACK = 116,
    LIFTED_STATE_COMBINE_453320_STACK = 120,
    LIFTED_STATE_PAIR_4533B0_STACK = 128,
    LIFTED_EFFECT_STONE_ARM_STACK = 112,
    LIFTED_EFFECT_STONE_APPLY_STACK = 112,
    LIFTED_EFFECT_STONE_CLEAR_STACK = 100,
    LIFTED_EFFECT_STATE_GATE_STACK = 100,
    LIFTED_EFFECT_STATE_GATE_453620_STACK = 100,
    LIFTED_EFFECT_STATE_GATE_453670_STACK = 100,
    LIFTED_EFFECT_STATE_GATE_4536C0_STACK = 96,
    LIFTED_EFFECT_STATE_GATE_453710_STACK = 96,
    LIFTED_EFFECT_STATE_GATE_453760_STACK = 96,
    LIFTED_EFFECT_STATE_GATE_4537B0_STACK = 100,
    LIFTED_EFFECT_STATE_GATE_453800_STACK = 100,
    LIFTED_EFFECT_STATE_GATE_453850_STACK = 100,
    LIFTED_EFFECT_STATE_GATE_4538A0_STACK = 100,
    LIFTED_EFFECT_STATE_GATE_4538F0_STACK = 100,
    LIFTED_EFFECT_STATE_GATE_453940_STACK = 100,
    LIFTED_EFFECT_STATE_GATE_453990_STACK = 100,
    LIFTED_EFFECT_STATE_GATE_4539E0_STACK = 100,
    LIFTED_EFFECT_STATE_GATE_453A30_STACK = 96,
    LIFTED_EFFECT_STATE_GATE_453A80_STACK = 100,
    LIFTED_EFFECT_FORCED_CHOICE_STACK = 132,
    LIFTED_EFFECT_PAIR_SOUND_STACK = 112,
    LIFTED_EFFECT_COPY_SPEED_STACK = 108,
    LIFTED_EFFECT_SLIDE_START_STACK = 120,
    LIFTED_F453D50_STACK = 172,
    LIFTED_STATE_ASK_453EF0_STACK = 92,
    LIFTED_EFFECT_ATTACK_STACK = 108,
    LIFTED_EFFECT_SLIDE_START_453FD0_STACK = 120,
    LIFTED_F454090_STACK = 156,
    LIFTED_STATE_ASK_454200_STACK = 92,
    LIFTED_EFFECT_ATTACK_454250_STACK = 108,
    LIFTED_EFFECT_SLIDE_START_4542E0_STACK = 120,
    LIFTED_F4543A0_STACK = 156,
    LIFTED_STATE_ASK_454510_STACK = 92,
    LIFTED_EFFECT_ATTACK_454560_STACK = 120,
    LIFTED_F454600_STACK = 100,
    LIFTED_STATE_CYCLE_4546A0_STACK = 128,
    LIFTED_STATE_ASK_454760_STACK = 92,
    LIFTED_EFFECT_ATTACK_4547B0_STACK = 104,
    LIFTED_F454830_STACK = 132,
    LIFTED_F4548E0_STACK = 116,
    LIFTED_F454970_STACK = 100,
    LIFTED_EFFECT_ATTACK_4549D0_STACK = 104,
    LIFTED_F454A50_STACK = 132,
    LIFTED_STATE_DRAIN_454B20_STACK = 120,
    LIFTED_STATE_DONE_454BD0_STACK = 100,
    LIFTED_EFFECT_ATTACK_454C30_STACK = 104,
    LIFTED_F454CB0_STACK = 132,
    LIFTED_STATE_DRAIN_454D80_STACK = 120,
    LIFTED_STATE_DONE_454E30_STACK = 100,
    LIFTED_EFFECT_ATTACK_454E90_STACK = 104,
    LIFTED_F454F00_STACK = 132,
    LIFTED_STATE_DONE_454FC0_STACK = 100,
    LIFTED_EFFECT_ATTACK_455020_STACK = 104,
    LIFTED_F4550A0_STACK = 196,
    LIFTED_STATE_DONE_4552B0_STACK = 100,
    LIFTED_STATE_GUARD_455320_STACK = 100,
    LIFTED_STATE_GUARD_4553A0_STACK = 132,
    LIFTED_EFFECT_CHECK_BIND_STACK = 112,
    LIFTED_EFFECT_FIELD_BIND_STACK = 104,
    LIFTED_F455580_STACK = 108,
    LIFTED_EFFECT_CHECK_BIND_455600_STACK = 112,
    LIFTED_EFFECT_CHECK_BIND_455670_STACK = 116,
    LIFTED_F455700_STACK = 108,
    LIFTED_EFFECT_CHECK_BIND_455790_STACK = 124,
    LIFTED_F455830_STACK = 128,
    LIFTED_EFFECT_CHECK_BIND_4558E0_STACK = 116,
    LIFTED_F455970_STACK = 108,
    LIFTED_EFFECT_CHECK_BIND_455A00_STACK = 116,
    LIFTED_F455A90_STACK = 112,
    LIFTED_EFFECT_ATTACK_455B20_STACK = 104,
    LIFTED_F455B90_STACK = 124,
    LIFTED_STATE_DONE_455C30_STACK = 100,
    LIFTED_EFFECT_ATTACK_455CA0_STACK = 104,
    LIFTED_F455D10_STACK = 124,
    LIFTED_STATE_REPLACE_455DB0_STACK = 96,
    LIFTED_STATE_ASK_455E00_STACK = 92,
    LIFTED_EFFECT_SLIDE_BEGIN_STACK = 128,
    LIFTED_EFFECT_SLIDE_WAIT_STACK = 108,
    LIFTED_EFFECT_SLIDE_ADVANCE_STACK = 132,
    LIFTED_EFFECT_SLIDE_END_STACK = 104,
    LIFTED_F4560C0_STACK = 136,
    LIFTED_F456170_STACK = 144,
    LIFTED_F456290_STACK = 96,
    LIFTED_F456300_STACK = 124,
    LIFTED_F456390_STACK = 140,
    LIFTED_F456490_STACK = 96,
    LIFTED_F4564E0_STACK = 124,
    LIFTED_F456570_STACK = 140,
    LIFTED_F4566D0_STACK = 124,
    LIFTED_F456760_STACK = 140,
    LIFTED_F4568C0_STACK = 84,
    LIFTED_F456900_STACK = 120,
    LIFTED_F456980_STACK = 112,
    LIFTED_F456A00_STACK = 112,
    LIFTED_F456A80_STACK = 120,
    LIFTED_F456B00_STACK = 120,
    LIFTED_F456B80_STACK = 112,
    LIFTED_F456BF0_STACK = 100,
    LIFTED_F456CA0_STACK = 72,
    LIFTED_F456CD0_STACK = 108,
    LIFTED_F456D80_STACK = 96,
    LIFTED_F456DE0_STACK = 96,
    LIFTED_F456E40_STACK = 96,
    LIFTED_F456F10_STACK = 108,
    LIFTED_F456FA0_STACK = 96,
    LIFTED_F457000_STACK = 100,
    LIFTED_F457060_STACK = 96,
    LIFTED_F4570B0_STACK = 124,
    LIFTED_F457170_STACK = 92,
    LIFTED_F4571F0_STACK = 124,
    LIFTED_F4572B0_STACK = 92,
    LIFTED_F457670_STACK = 100,
    LIFTED_F4576D0_STACK = 100,
    LIFTED_F457730_STACK = 76,
    LIFTED_F457770_STACK = 96,
    LIFTED_OBJECT_FLIP_SIDE_STACK = 108,
    LIFTED_UI_CENTER_ON_ANCHOR_STACK = 92,
    LIFTED_F4578F0_STACK = 128,
    LIFTED_F457A00_STACK = 140,
    LIFTED_F457B70_STACK = 116,
    LIFTED_F457C10_STACK = 128,
    LIFTED_F457D10_STACK = 136,
    LIFTED_F457E40_STACK = 124,
    LIFTED_F457F40_STACK = 148,
    LIFTED_F4580B0_STACK = 96,
    LIFTED_F458100_STACK = 96,
    LIFTED_F458150_STACK = 124,
    LIFTED_F458260_STACK = 108,
    LIFTED_F4582D0_STACK = 108,
    LIFTED_F458330_STACK = 92,
    LIFTED_F4583C0_STACK = 96,
    LIFTED_F458410_STACK = 80,
    LIFTED_F458450_STACK = 96,
    LIFTED_F458490_STACK = 92,
    LIFTED_F4584F0_STACK = 108,
    LIFTED_F458560_STACK = 108,
    LIFTED_F4585C0_STACK = 144,
    LIFTED_F458710_STACK = 112,
    LIFTED_F4587A0_STACK = 136,
    LIFTED_F458880_STACK = 160,
    LIFTED_F4589E0_STACK = 100,
    LIFTED_F458A70_STACK = 140,
    LIFTED_F458C20_STACK = 144,
    LIFTED_F458D40_STACK = 124,
    LIFTED_F458E30_STACK = 140,
    LIFTED_F458F00_STACK = 116,
    LIFTED_F458FD0_STACK = 140,
    LIFTED_F4590A0_STACK = 92,
    LIFTED_F459100_STACK = 144,
    LIFTED_F459200_STACK = 84,
    LIFTED_F459290_STACK = 140,
    LIFTED_F4593B0_STACK = 136,
    LIFTED_F4594A0_STACK = 140,
    LIFTED_F4597E0_STACK = 112,
    LIFTED_F459860_STACK = 92,
    LIFTED_F4598A0_STACK = 104,
    LIFTED_F459900_STACK = 96,
    LIFTED_F459950_STACK = 96,
    LIFTED_F4599E0_STACK = 96,
    LIFTED_F459A30_STACK = 112,
    LIFTED_F459AB0_STACK = 96,
    LIFTED_F459B00_STACK = 96,
    LIFTED_F459B60_STACK = 112,
    LIFTED_TITLE_LETTER_COUNT_CALL_STACK = 168,
    LIFTED_TITLE_LETTER_RESTART_CALL_STACK = 144,
    LIFTED_TITLE_LETTER_LAUNCH_CALL_STACK = 124,
    LIFTED_TITLE_LETTER_FLY_OUT_CALL_STACK = 140,
    LIFTED_TITLE_LETTER_FIGHT_COUNT_CALL_STACK = 144,
    LIFTED_TITLE_LETTER_FIGHT_SETTLE_CALL_STACK = 104,
    LIFTED_TITLE_LETTER_FIGHT_RESTART_CALL_STACK = 124,
    LIFTED_TITLE_LETTER_FIGHT_FLY_CALL_STACK = 140,
    LIFTED_TITLE_LETTER_WAVE_COUNT_CALL_STACK = 136,
    LIFTED_TITLE_LETTER_WAVE_CALL_STACK = 132,
    LIFTED_TITLE_LETTER_WAVE_CALL_45A830_STACK = 132,
    LIFTED_TITLE_LETTER_WAVE_FLY_CALL_STACK = 140,
    LIFTED_F45AA20_STACK = 104,
    LIFTED_F45AA70_STACK = 88,
    LIFTED_F45AAB0_STACK = 156,
    LIFTED_F45ABD0_STACK = 148,
    LIFTED_F45AC70_STACK = 132,
    LIFTED_F45AD20_STACK = 140,
    LIFTED_F45AEA0_STACK = 124,
    LIFTED_F45AF40_STACK = 128,
    LIFTED_F45B0B0_STACK = 92,
    LIFTED_F45B0F0_STACK = 92,
    LIFTED_F45B130_STACK = 84,
    LIFTED_F45B150_STACK = 92,
    LIFTED_F45B190_STACK = 168,
    LIFTED_F45B410_STACK = 132,
    LIFTED_F45B4C0_STACK = 136,
    LIFTED_F45B590_STACK = 104,
    LIFTED_F45B5F0_STACK = 152,
    LIFTED_F45B710_STACK = 108,
    LIFTED_F45B790_STACK = 108,
    LIFTED_F45B7F0_STACK = 108,
    LIFTED_F45B860_STACK = 108,
    LIFTED_F45B8D0_STACK = 108,
    LIFTED_F45B950_STACK = 108,
    LIFTED_EFFECT_ATTACK_45B9C0_STACK = 104,
    LIFTED_F45BA30_STACK = 120,
    LIFTED_F45BAD0_STACK = 120
};

/* Original 0x44c2b0. */
uint32_t lifted_piece_child_update_44c2b0(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c310. */
uint32_t lifted_piece_child_update_44c310(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c370. */
uint32_t lifted_piece_child_update_44c370(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c3d0. */
uint32_t lifted_f44c3d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c3e0. */
uint32_t lifted_f44c3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c450. */
uint32_t lifted_f44c450(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c4c0. */
uint32_t lifted_f44c4c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c530. */
uint32_t lifted_f44c530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c5a0. */
uint32_t lifted_f44c5a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c610. */
uint32_t lifted_f44c610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c680. */
uint32_t lifted_f44c680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c6e0. */
uint32_t lifted_f44c6e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c780. */
uint32_t lifted_f44c780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c7f0. */
uint32_t lifted_f44c7f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c860. */
uint32_t lifted_block_update(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c880. */
uint32_t lifted_block_motion_update(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c8e0. */
uint32_t lifted_f44c8e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c940. */
uint32_t lifted_f44c940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c960. */
uint32_t lifted_block_fade_update(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44c9d0. */
uint32_t lifted_block_pulse_update(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ca40. */
uint32_t lifted_f44ca40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44cab0. */
uint32_t lifted_f44cab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44cb50. */
uint32_t lifted_f44cb50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44cbf0. */
uint32_t lifted_block_byte_pulse_update(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44cc60. */
uint32_t lifted_block_byte_pulse_update_44cc60(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x44ccd0. */
uint32_t lifted_f44ccd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ce80. */
uint32_t lifted_block_scale_update(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44cf00. */
uint32_t lifted_block_return_update(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44cf70. */
uint32_t lifted_f44cf70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44cfd0. */
uint32_t lifted_f44cfd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d030. */
uint32_t lifted_f44d030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d1e0. */
uint32_t lifted_f44d1e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d250. */
uint32_t lifted_f44d250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d2c0. */
uint32_t lifted_f44d2c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d330. */
uint32_t lifted_f44d330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d3a0. */
uint32_t lifted_f44d3a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d410. */
uint32_t lifted_block_byte_pulse_update_44d410(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x44d480. */
uint32_t lifted_f44d480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d4f0. */
uint32_t lifted_f44d4f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d560. */
uint32_t lifted_f44d560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d5f0. */
uint32_t lifted_f44d5f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d660. */
uint32_t lifted_f44d660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d6d0. */
uint32_t lifted_f44d6d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d760. */
uint32_t lifted_block_byte_pulse_update_44d760(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x44d7d0. */
uint32_t lifted_f44d7d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d840. */
uint32_t lifted_f44d840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d8b0. */
uint32_t lifted_block_mode_pulse_update(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d940. */
uint32_t lifted_f44d940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44d9d0. */
uint32_t lifted_f44d9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44da70. */
uint32_t lifted_block_half_pulse_update(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44db10. */
uint32_t lifted_f44db10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44dbb0. */
uint32_t lifted_f44dbb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44dc80. */
uint32_t lifted_f44dc80(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x44e250. */
uint32_t lifted_block_slide_update(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e2d0. */
uint32_t lifted_f44e2d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e380. */
uint32_t lifted_block_collapse_update(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e410. */
uint32_t lifted_f44e410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e4a0. */
uint32_t lifted_block_visibility_update(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e510. */
uint32_t lifted_f44e510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e590. */
uint32_t lifted_block_swell_update(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e600. */
uint32_t lifted_f44e600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e670. */
uint32_t lifted_f44e670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e6e0. */
uint32_t lifted_block_accelerate_update(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e790. */
uint32_t lifted_block_mode_amount_update(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e800. */
uint32_t lifted_f44e800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44e890. */
uint32_t lifted_block_period_update(const VertrixCalls *calls,
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

/* Original 0x44ebe0. */
uint32_t lifted_block_travel_update(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ec40. */
uint32_t lifted_f44ec40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ece0. */
uint32_t lifted_block_spin_update(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44ee20. */
uint32_t lifted_f44ee20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f040. */
uint32_t lifted_f44f040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f0b0. */
uint32_t lifted_f44f0b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f120. */
uint32_t lifted_block_effect_update(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f180. */
uint32_t lifted_block_effect_update_44f180(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f1e0. */
uint32_t lifted_block_effect_update_44f1e0(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f240. */
uint32_t lifted_block_effect_update_44f240(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f2b0. */
uint32_t lifted_block_effect_update_44f2b0(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f320. */
uint32_t lifted_block_effect_update_44f320(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f390. */
uint32_t lifted_block_cycle_update(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f3e0. */
uint32_t lifted_f44f3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f430. */
uint32_t lifted_f44f430(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f4a0. */
uint32_t lifted_block_effect_update_44f4a0(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f500. */
uint32_t lifted_block_effect_update_44f500(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f560. */
uint32_t lifted_block_effect_update_44f560(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f5d0. */
uint32_t lifted_block_effect_update_44f5d0(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f630. */
uint32_t lifted_block_effect_update_44f630(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f690. */
uint32_t lifted_block_effect_update_44f690(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f700. */
uint32_t lifted_f44f700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f770. */
uint32_t lifted_f44f770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f7e0. */
uint32_t lifted_f44f7e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f880. */
uint32_t lifted_f44f880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f920. */
uint32_t lifted_f44f920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44f990. */
uint32_t lifted_f44f990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fa00. */
uint32_t lifted_f44fa00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fa70. */
uint32_t lifted_number_player_update(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44faa0. */
uint32_t lifted_f44faa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fad0. */
uint32_t lifted_number_transition_update(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fb40. */
uint32_t lifted_number_transition_update_44fb40(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x44fbb0. */
uint32_t lifted_number_transition_update_44fbb0(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x44fc00. */
uint32_t lifted_f44fc00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fc30. */
uint32_t lifted_f44fc30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fc60. */
uint32_t lifted_number_transition_configured(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fcf0. */
uint32_t lifted_number_transition_configured_44fcf0(const VertrixCalls *calls,
                                                    const VertrixFactoryServices *services,
                                                    const VertrixGlobals *globals,
                                                    const LiftEntry *entry);

/* Original 0x44fd60. */
uint32_t lifted_number_transition_configured_44fd60(const VertrixCalls *calls,
                                                    const VertrixFactoryServices *services,
                                                    const VertrixGlobals *globals,
                                                    const LiftEntry *entry);

/* Original 0x44fdb0. */
uint32_t lifted_number_transition_configured_44fdb0(const VertrixCalls *calls,
                                                    const VertrixFactoryServices *services,
                                                    const VertrixGlobals *globals,
                                                    const LiftEntry *entry);

/* Original 0x44fe30. */
uint32_t lifted_number_transition_configured_44fe30(const VertrixCalls *calls,
                                                    const VertrixFactoryServices *services,
                                                    const VertrixGlobals *globals,
                                                    const LiftEntry *entry);

/* Original 0x44fe80. */
uint32_t lifted_player_indicator_update(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fed0. */
uint32_t lifted_player_indicator_update_44fed0(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x44ff30. */
uint32_t lifted_player_indicator_update_44ff30(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x44ff60. */
uint32_t lifted_player_indicator_update_44ff60(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x44ff90. */
uint32_t lifted_ui_indicator_storage_update(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x44fff0. */
uint32_t lifted_ui_indicator_storage_update_44fff0(const VertrixCalls *calls,
                                                   const VertrixFactoryServices *services,
                                                   const VertrixGlobals *globals,
                                                   const LiftEntry *entry);

/* Original 0x450040. */
uint32_t lifted_ui_indicator_storage_update_450040(const VertrixCalls *calls,
                                                   const VertrixFactoryServices *services,
                                                   const VertrixGlobals *globals,
                                                   const LiftEntry *entry);

/* Original 0x4500b0. */
uint32_t lifted_ui_indicator_storage_update_4500b0(const VertrixCalls *calls,
                                                   const VertrixFactoryServices *services,
                                                   const VertrixGlobals *globals,
                                                   const LiftEntry *entry);

/* Original 0x450100. */
uint32_t lifted_ui_indicator_storage_update_450100(const VertrixCalls *calls,
                                                   const VertrixFactoryServices *services,
                                                   const VertrixGlobals *globals,
                                                   const LiftEntry *entry);

/* Original 0x450130. */
uint32_t lifted_ui_border_storage_update(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4501a0. */
uint32_t lifted_ui_border_storage_update_4501a0(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x450200. */
uint32_t lifted_ui_border_storage_update_450200(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x450270. */
uint32_t lifted_ui_border_storage_update_450270(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x450300. */
uint32_t lifted_ui_border_storage_update_450300(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x450330. */
uint32_t lifted_block_finish_effect_update(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4503b0. */
uint32_t lifted_block_finish_effect_update_4503b0(const VertrixCalls *calls,
                                                  const VertrixFactoryServices *services,
                                                  const VertrixGlobals *globals,
                                                  const LiftEntry *entry);

/* Original 0x450450. */
uint32_t lifted_block_finish_effect_update_450450(const VertrixCalls *calls,
                                                  const VertrixFactoryServices *services,
                                                  const VertrixGlobals *globals,
                                                  const LiftEntry *entry);

/* Original 0x4504e0. */
uint32_t lifted_block_finish_effect_update_4504e0(const VertrixCalls *calls,
                                                  const VertrixFactoryServices *services,
                                                  const VertrixGlobals *globals,
                                                  const LiftEntry *entry);

/* Original 0x450550. */
uint32_t lifted_block_finish_effect_update_450550(const VertrixCalls *calls,
                                                  const VertrixFactoryServices *services,
                                                  const VertrixGlobals *globals,
                                                  const LiftEntry *entry);

/* Original 0x4505c0. */
uint32_t lifted_block_finish_effect_update_4505c0(const VertrixCalls *calls,
                                                  const VertrixFactoryServices *services,
                                                  const VertrixGlobals *globals,
                                                  const LiftEntry *entry);

/* Original 0x450630. */
uint32_t lifted_block_finish_effect_update_450630(const VertrixCalls *calls,
                                                  const VertrixFactoryServices *services,
                                                  const VertrixGlobals *globals,
                                                  const LiftEntry *entry);

/* Original 0x4506a0. */
uint32_t lifted_block_finish_effect_update_4506a0(const VertrixCalls *calls,
                                                  const VertrixFactoryServices *services,
                                                  const VertrixGlobals *globals,
                                                  const LiftEntry *entry);

/* Original 0x450710. */
uint32_t lifted_block_animation_update(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450730. */
uint32_t lifted_block_animation_update_450730(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x450750. */
uint32_t lifted_player_countdown_update(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4507e0. */
uint32_t lifted_player_countdown_update_4507e0(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x450830. */
uint32_t lifted_player_countdown_update_450830(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry);

/* Original 0x450860. */
uint32_t lifted_ui_companion_storage_update(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4508c0. */
uint32_t lifted_ui_companion_storage_update_4508c0(const VertrixCalls *calls,
                                                   const VertrixFactoryServices *services,
                                                   const VertrixGlobals *globals,
                                                   const LiftEntry *entry);

/* Original 0x450920. */
uint32_t lifted_ui_companion_storage_update_450920(const VertrixCalls *calls,
                                                   const VertrixFactoryServices *services,
                                                   const VertrixGlobals *globals,
                                                   const LiftEntry *entry);

/* Original 0x450960. */
uint32_t lifted_ui_companion_storage_update_450960(const VertrixCalls *calls,
                                                   const VertrixFactoryServices *services,
                                                   const VertrixGlobals *globals,
                                                   const LiftEntry *entry);

/* Original 0x4509a0. */
uint32_t lifted_ui_companion_storage_update_4509a0(const VertrixCalls *calls,
                                                   const VertrixFactoryServices *services,
                                                   const VertrixGlobals *globals,
                                                   const LiftEntry *entry);

/* Original 0x4509d0. */
uint32_t lifted_ui_companion_storage_update_4509d0(const VertrixCalls *calls,
                                                   const VertrixFactoryServices *services,
                                                   const VertrixGlobals *globals,
                                                   const LiftEntry *entry);

/* Original 0x450a10. */
uint32_t lifted_linked_alternating_update(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450aa0. */
uint32_t lifted_linked_alternating_update_450aa0(const VertrixCalls *calls,
                                                 const VertrixFactoryServices *services,
                                                 const VertrixGlobals *globals,
                                                 const LiftEntry *entry);

/* Original 0x450b30. */
uint32_t lifted_linked_alternating_update_450b30(const VertrixCalls *calls,
                                                 const VertrixFactoryServices *services,
                                                 const VertrixGlobals *globals,
                                                 const LiftEntry *entry);

/* Original 0x450b90. */
uint32_t lifted_linked_alternating_update_450b90(const VertrixCalls *calls,
                                                 const VertrixFactoryServices *services,
                                                 const VertrixGlobals *globals,
                                                 const LiftEntry *entry);

/* Original 0x450bf0. */
uint32_t lifted_linked_alternating_update_450bf0(const VertrixCalls *calls,
                                                 const VertrixFactoryServices *services,
                                                 const VertrixGlobals *globals,
                                                 const LiftEntry *entry);

/* Original 0x450c70. */
uint32_t lifted_linked_alternating_update_450c70(const VertrixCalls *calls,
                                                 const VertrixFactoryServices *services,
                                                 const VertrixGlobals *globals,
                                                 const LiftEntry *entry);

/* Original 0x450cd0. */
uint32_t lifted_f450cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450d40. */
uint32_t lifted_f450d40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450df0. */
uint32_t lifted_f450df0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450e70. */
uint32_t lifted_f450e70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450f60. */
uint32_t lifted_f450f60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450ff0. */
uint32_t lifted_f450ff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4513d0. */
uint32_t lifted_f4513d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4513f0. */
uint32_t lifted_f4513f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451490. */
uint32_t lifted_state_steps_451490(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451520. */
uint32_t lifted_state_gate_451520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451580. */
uint32_t lifted_state_drain_451580(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451630. */
uint32_t lifted_state_check_451630(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451690. */
uint32_t lifted_state_start_451690(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451730. */
uint32_t lifted_state_steps_451730(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4517c0. */
uint32_t lifted_object_post_lock(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451920. */
uint32_t lifted_object_post_lock_twin(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451a60. */
uint32_t lifted_player_start_bonus(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451aa0. */
uint32_t lifted_f451aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451c00. */
uint32_t lifted_f451c00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451c80. */
uint32_t lifted_f451c80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451dd0. */
uint32_t lifted_state_choice_check(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451e20. */
uint32_t lifted_state_choice_apply(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451f10. */
uint32_t lifted_f451f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x451f50. */
uint32_t lifted_state_choice_take(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452050. */
uint32_t lifted_f452050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452070. */
uint32_t lifted_f452070(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4520b0. */
uint32_t lifted_f4520b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4520f0. */
uint32_t lifted_f4520f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452160. */
uint32_t lifted_state_match_452160(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452250. */
uint32_t lifted_object_arm_hold(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4522c0. */
uint32_t lifted_object_enter_attack(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452370. */
uint32_t lifted_f452370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4523d0. */
uint32_t lifted_f4523d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452440. */
uint32_t lifted_state_attack_452440(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4526e0. */
uint32_t lifted_f4526e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452770. */
uint32_t lifted_state_advance_452770(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452830. */
uint32_t lifted_effect_negated_gate(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452880. */
uint32_t lifted_effect_value_gate(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4528e0. */
uint32_t lifted_effect_progress_gate(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452a30. */
uint32_t lifted_effect_arm_handler(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452a50. */
uint32_t lifted_effect_armed_handler(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452b00. */
uint32_t lifted_effect_arm_handler_452b00(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452b20. */
uint32_t lifted_effect_armed_handler_452b20(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452bb0. */
uint32_t lifted_effect_arm_handler_452bb0(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452bd0. */
uint32_t lifted_effect_armed_handler_452bd0(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452c60. */
uint32_t lifted_effect_arm_handler_452c60(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452c80. */
uint32_t lifted_effect_armed_handler_452c80(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452d10. */
uint32_t lifted_effect_progress_update_gate(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452d70. */
uint32_t lifted_effect_progress_compare(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452e00. */
uint32_t lifted_effect_board_match(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452fc0. */
uint32_t lifted_f452fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453150. */
uint32_t lifted_effect_convert_blocks(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453280. */
uint32_t lifted_f453280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453320. */
uint32_t lifted_state_combine_453320(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4533b0. */
uint32_t lifted_state_pair_4533b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453460. */
uint32_t lifted_effect_stone_arm(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4534e0. */
uint32_t lifted_effect_stone_apply(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453570. */
uint32_t lifted_effect_stone_clear(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4535d0. */
uint32_t lifted_effect_state_gate(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453620. */
uint32_t lifted_effect_state_gate_453620(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453670. */
uint32_t lifted_effect_state_gate_453670(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4536c0. */
uint32_t lifted_effect_state_gate_4536c0(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453710. */
uint32_t lifted_effect_state_gate_453710(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453760. */
uint32_t lifted_effect_state_gate_453760(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4537b0. */
uint32_t lifted_effect_state_gate_4537b0(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453800. */
uint32_t lifted_effect_state_gate_453800(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453850. */
uint32_t lifted_effect_state_gate_453850(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4538a0. */
uint32_t lifted_effect_state_gate_4538a0(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4538f0. */
uint32_t lifted_effect_state_gate_4538f0(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453940. */
uint32_t lifted_effect_state_gate_453940(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453990. */
uint32_t lifted_effect_state_gate_453990(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4539e0. */
uint32_t lifted_effect_state_gate_4539e0(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453a30. */
uint32_t lifted_effect_state_gate_453a30(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453a80. */
uint32_t lifted_effect_state_gate_453a80(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453ad0. */
uint32_t lifted_effect_forced_choice(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453b90. */
uint32_t lifted_effect_pair_sound(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453c00. */
uint32_t lifted_effect_copy_speed(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453c90. */
uint32_t lifted_effect_slide_start(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453d50. */
uint32_t lifted_f453d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453ef0. */
uint32_t lifted_state_ask_453ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453f40. */
uint32_t lifted_effect_attack(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453fd0. */
uint32_t lifted_effect_slide_start_453fd0(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454090. */
uint32_t lifted_f454090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454200. */
uint32_t lifted_state_ask_454200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454250. */
uint32_t lifted_effect_attack_454250(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4542e0. */
uint32_t lifted_effect_slide_start_4542e0(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4543a0. */
uint32_t lifted_f4543a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454510. */
uint32_t lifted_state_ask_454510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454560. */
uint32_t lifted_effect_attack_454560(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454600. */
uint32_t lifted_f454600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4546a0. */
uint32_t lifted_state_cycle_4546a0(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454760. */
uint32_t lifted_state_ask_454760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4547b0. */
uint32_t lifted_effect_attack_4547b0(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454830. */
uint32_t lifted_f454830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4548e0. */
uint32_t lifted_f4548e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454970. */
uint32_t lifted_f454970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4549d0. */
uint32_t lifted_effect_attack_4549d0(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454a50. */
uint32_t lifted_f454a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454b20. */
uint32_t lifted_state_drain_454b20(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454bd0. */
uint32_t lifted_state_done_454bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454c30. */
uint32_t lifted_effect_attack_454c30(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454cb0. */
uint32_t lifted_f454cb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454d80. */
uint32_t lifted_state_drain_454d80(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454e30. */
uint32_t lifted_state_done_454e30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454e90. */
uint32_t lifted_effect_attack_454e90(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454f00. */
uint32_t lifted_f454f00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454fc0. */
uint32_t lifted_state_done_454fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455020. */
uint32_t lifted_effect_attack_455020(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4550a0. */
uint32_t lifted_f4550a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4552b0. */
uint32_t lifted_state_done_4552b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455320. */
uint32_t lifted_state_guard_455320(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4553a0. */
uint32_t lifted_state_guard_4553a0(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4554a0. */
uint32_t lifted_effect_check_bind(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455510. */
uint32_t lifted_effect_field_bind(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455580. */
uint32_t lifted_f455580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455600. */
uint32_t lifted_effect_check_bind_455600(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455670. */
uint32_t lifted_effect_check_bind_455670(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455700. */
uint32_t lifted_f455700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455790. */
uint32_t lifted_effect_check_bind_455790(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455830. */
uint32_t lifted_f455830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4558e0. */
uint32_t lifted_effect_check_bind_4558e0(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455970. */
uint32_t lifted_f455970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455a00. */
uint32_t lifted_effect_check_bind_455a00(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455a90. */
uint32_t lifted_f455a90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455b20. */
uint32_t lifted_effect_attack_455b20(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455b90. */
uint32_t lifted_f455b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455c30. */
uint32_t lifted_state_done_455c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455ca0. */
uint32_t lifted_effect_attack_455ca0(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455d10. */
uint32_t lifted_f455d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455db0. */
uint32_t lifted_state_replace_455db0(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455e00. */
uint32_t lifted_state_ask_455e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455e50. */
uint32_t lifted_effect_slide_begin(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455f10. */
uint32_t lifted_effect_slide_wait(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455f80. */
uint32_t lifted_effect_slide_advance(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456060. */
uint32_t lifted_effect_slide_end(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4560c0. */
uint32_t lifted_f4560c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456170. */
uint32_t lifted_f456170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456290. */
uint32_t lifted_f456290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456300. */
uint32_t lifted_f456300(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456390. */
uint32_t lifted_f456390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456490. */
uint32_t lifted_f456490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4564e0. */
uint32_t lifted_f4564e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456570. */
uint32_t lifted_f456570(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4566d0. */
uint32_t lifted_f4566d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456760. */
uint32_t lifted_f456760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4568c0. */
uint32_t lifted_f4568c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456900. */
uint32_t lifted_f456900(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456980. */
uint32_t lifted_f456980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456a00. */
uint32_t lifted_f456a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456a80. */
uint32_t lifted_f456a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456b00. */
uint32_t lifted_f456b00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456b80. */
uint32_t lifted_f456b80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456bf0. */
uint32_t lifted_f456bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456ca0. */
uint32_t lifted_f456ca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456cd0. */
uint32_t lifted_f456cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456d80. */
uint32_t lifted_f456d80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456de0. */
uint32_t lifted_f456de0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456e40. */
uint32_t lifted_f456e40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456f10. */
uint32_t lifted_f456f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456fa0. */
uint32_t lifted_f456fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457000. */
uint32_t lifted_f457000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457060. */
uint32_t lifted_f457060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4570b0. */
uint32_t lifted_f4570b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457170. */
uint32_t lifted_f457170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4571f0. */
uint32_t lifted_f4571f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4572b0. */
uint32_t lifted_f4572b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457670. */
uint32_t lifted_f457670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4576d0. */
uint32_t lifted_f4576d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457730. */
uint32_t lifted_f457730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457770. */
uint32_t lifted_f457770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457810. */
uint32_t lifted_object_flip_side(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x457b70. */
uint32_t lifted_f457b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4580b0. */
uint32_t lifted_f4580b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458100. */
uint32_t lifted_f458100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458150. */
uint32_t lifted_f458150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458260. */
uint32_t lifted_f458260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4582d0. */
uint32_t lifted_f4582d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458330. */
uint32_t lifted_f458330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4583c0. */
uint32_t lifted_f4583c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458410. */
uint32_t lifted_f458410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458450. */
uint32_t lifted_f458450(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458490. */
uint32_t lifted_f458490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4584f0. */
uint32_t lifted_f4584f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458560. */
uint32_t lifted_f458560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4585c0. */
uint32_t lifted_f4585c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458710. */
uint32_t lifted_f458710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4587a0. */
uint32_t lifted_f4587a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458880. */
uint32_t lifted_f458880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4589e0. */
uint32_t lifted_f4589e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x458e30. */
uint32_t lifted_f458e30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458f00. */
uint32_t lifted_f458f00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458fd0. */
uint32_t lifted_f458fd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4590a0. */
uint32_t lifted_f4590a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459100. */
uint32_t lifted_f459100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459200. */
uint32_t lifted_f459200(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4597e0. */
uint32_t lifted_f4597e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459860. */
uint32_t lifted_f459860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4598a0. */
uint32_t lifted_f4598a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459900. */
uint32_t lifted_f459900(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459950. */
uint32_t lifted_f459950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4599e0. */
uint32_t lifted_f4599e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459a30. */
uint32_t lifted_f459a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459ab0. */
uint32_t lifted_f459ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459b00. */
uint32_t lifted_f459b00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459b60. */
uint32_t lifted_f459b60(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x45a1c0. */
uint32_t lifted_title_letter_fly_out_call(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a290. */
uint32_t lifted_title_letter_fight_count_call(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals,
                                              const LiftEntry *entry);

/* Original 0x45a3e0. */
uint32_t lifted_title_letter_fight_settle_call(const VertrixCalls *calls,
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

/* Original 0x45aa20. */
uint32_t lifted_f45aa20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45aa70. */
uint32_t lifted_f45aa70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45aab0. */
uint32_t lifted_f45aab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45abd0. */
uint32_t lifted_f45abd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ac70. */
uint32_t lifted_f45ac70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ad20. */
uint32_t lifted_f45ad20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45aea0. */
uint32_t lifted_f45aea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45af40. */
uint32_t lifted_f45af40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b0b0. */
uint32_t lifted_f45b0b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b0f0. */
uint32_t lifted_f45b0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b130. */
uint32_t lifted_f45b130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b150. */
uint32_t lifted_f45b150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b190. */
uint32_t lifted_f45b190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b410. */
uint32_t lifted_f45b410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b4c0. */
uint32_t lifted_f45b4c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b590. */
uint32_t lifted_f45b590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b5f0. */
uint32_t lifted_f45b5f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b710. */
uint32_t lifted_f45b710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b790. */
uint32_t lifted_f45b790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b7f0. */
uint32_t lifted_f45b7f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b860. */
uint32_t lifted_f45b860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b8d0. */
uint32_t lifted_f45b8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b950. */
uint32_t lifted_f45b950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45b9c0. */
uint32_t lifted_effect_attack_45b9c0(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ba30. */
uint32_t lifted_f45ba30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bad0. */
uint32_t lifted_f45bad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
