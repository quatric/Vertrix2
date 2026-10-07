#ifndef VERTRIX_LIFTED_WHOLE_2_H
#define VERTRIX_LIFTED_WHOLE_2_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4505C0_STACK = 108,
    LIFTED_F450630_STACK = 104,
    LIFTED_F4506A0_STACK = 108,
    LIFTED_F450710_STACK = 76,
    LIFTED_F450730_STACK = 76,
    LIFTED_F450750_STACK = 96,
    LIFTED_F4507E0_STACK = 88,
    LIFTED_F450830_STACK = 88,
    LIFTED_F450860_STACK = 88,
    LIFTED_F4508C0_STACK = 104,
    LIFTED_F450920_STACK = 84,
    LIFTED_F450960_STACK = 96,
    LIFTED_F4509A0_STACK = 88,
    LIFTED_F4509D0_STACK = 80,
    LIFTED_F450A10_STACK = 104,
    LIFTED_F450AA0_STACK = 116,
    LIFTED_F450B30_STACK = 96,
    LIFTED_F450B90_STACK = 96,
    LIFTED_F450BF0_STACK = 100,
    LIFTED_F450C70_STACK = 100,
    LIFTED_F450CD0_STACK = 104,
    LIFTED_F450D40_STACK = 104,
    LIFTED_F450DF0_STACK = 92,
    LIFTED_F450E70_STACK = 148,
    LIFTED_F450F60_STACK = 72,
    LIFTED_OBJECT_START_HOLD_STACK = 84,
    LIFTED_F4513D0_STACK = 72,
    LIFTED_F4513F0_STACK = 116,
    LIFTED_STATE_STEPS_451490_STACK = 120,
    LIFTED_STATE_GATE_451520_STACK = 100,
    LIFTED_STATE_DRAIN_451580_STACK = 124,
    LIFTED_STATE_CHECK_451630_STACK = 100,
    LIFTED_STATE_START_451690_STACK = 116,
    LIFTED_F451730_STACK = 116,
    LIFTED_PLAYER_START_BONUS_STACK = 88,
    LIFTED_F451AA0_STACK = 164,
    LIFTED_F451C00_STACK = 108,
    LIFTED_STATE_CHOICE_CHECK_STACK = 92,
    LIFTED_STATE_CHOICE_APPLY_STACK = 144,
    LIFTED_F451F10_STACK = 92,
    LIFTED_F452050_STACK = 72,
    LIFTED_F452070_STACK = 88,
    LIFTED_F4520B0_STACK = 88,
    LIFTED_F4520F0_STACK = 112,
    LIFTED_STATE_MATCH_452160_STACK = 136,
    LIFTED_OBJECT_ARM_HOLD_STACK = 96,
    LIFTED_OBJECT_ENTER_ATTACK_STACK = 108,
    LIFTED_F452370_STACK = 88,
    LIFTED_F4523B0_STACK = 64,
    LIFTED_F4523D0_STACK = 88,
    LIFTED_STATE_ATTACK_452440_STACK = 136,
    LIFTED_F4526E0_STACK = 116,
    LIFTED_STATE_ADVANCE_452770_STACK = 120,
    LIFTED_EFFECT_NEGATED_GATE_STACK = 100,
    LIFTED_EFFECT_VALUE_GATE_STACK = 104,
    LIFTED_EFFECT_PROGRESS_GATE_STACK = 112,
    LIFTED_EFFECT_ARM_HANDLER_STACK = 80,
    LIFTED_F452A50_STACK = 128,
    LIFTED_F452B00_STACK = 80,
    LIFTED_F452B20_STACK = 116,
    LIFTED_F452BB0_STACK = 80,
    LIFTED_F452BD0_STACK = 116,
    LIFTED_F452C60_STACK = 80,
    LIFTED_F452C80_STACK = 116,
    LIFTED_EFFECT_PROGRESS_UPDATE_GATE_STACK = 104,
    LIFTED_EFFECT_PROGRESS_COMPARE_STACK = 128,
    LIFTED_EFFECT_BOARD_MATCH_STACK = 192,
    LIFTED_F452FC0_STACK = 104,
    LIFTED_F453280_STACK = 116,
    LIFTED_STATE_COMBINE_453320_STACK = 120,
    LIFTED_STATE_PAIR_4533B0_STACK = 128,
    LIFTED_EFFECT_STONE_ARM_STACK = 112,
    LIFTED_EFFECT_STONE_APPLY_STACK = 112,
    LIFTED_EFFECT_STONE_CLEAR_STACK = 100,
    LIFTED_F4535D0_STACK = 100,
    LIFTED_F453620_STACK = 100,
    LIFTED_F453670_STACK = 100,
    LIFTED_F4536C0_STACK = 96,
    LIFTED_F453710_STACK = 96,
    LIFTED_F453760_STACK = 96,
    LIFTED_F4537B0_STACK = 100,
    LIFTED_F453800_STACK = 100,
    LIFTED_F453850_STACK = 100,
    LIFTED_F4538A0_STACK = 100,
    LIFTED_F4538F0_STACK = 100,
    LIFTED_F453940_STACK = 100,
    LIFTED_F453990_STACK = 100,
    LIFTED_F4539E0_STACK = 100,
    LIFTED_F453A30_STACK = 96,
    LIFTED_F453A80_STACK = 100,
    LIFTED_EFFECT_PAIR_SOUND_STACK = 112,
    LIFTED_EFFECT_COPY_SPEED_STACK = 108,
    LIFTED_F453C90_STACK = 120,
    LIFTED_F453D50_STACK = 172,
    LIFTED_STATE_ASK_453EF0_STACK = 92,
    LIFTED_F453F40_STACK = 108,
    LIFTED_F453FD0_STACK = 120,
    LIFTED_F454090_STACK = 156,
    LIFTED_STATE_ASK_454200_STACK = 92,
    LIFTED_F454250_STACK = 108,
    LIFTED_F4542E0_STACK = 120,
    LIFTED_F4543A0_STACK = 156,
    LIFTED_STATE_ASK_454510_STACK = 92,
    LIFTED_F454560_STACK = 120,
    LIFTED_F454600_STACK = 100,
    LIFTED_STATE_CYCLE_4546A0_STACK = 128,
    LIFTED_F454760_STACK = 92,
    LIFTED_F4547B0_STACK = 104,
    LIFTED_F454830_STACK = 132,
    LIFTED_F4548E0_STACK = 116,
    LIFTED_F454970_STACK = 100,
    LIFTED_F4549D0_STACK = 104,
    LIFTED_F454A50_STACK = 132,
    LIFTED_STATE_DRAIN_454B20_STACK = 120,
    LIFTED_STATE_DONE_454BD0_STACK = 100,
    LIFTED_F454C30_STACK = 104,
    LIFTED_F454CB0_STACK = 132,
    LIFTED_STATE_DRAIN_454D80_STACK = 120,
    LIFTED_F454E30_STACK = 100,
    LIFTED_F454E90_STACK = 104,
    LIFTED_F454F00_STACK = 132,
    LIFTED_STATE_DONE_454FC0_STACK = 100,
    LIFTED_F455020_STACK = 104,
    LIFTED_STATE_DONE_4552B0_STACK = 100,
    LIFTED_STATE_GUARD_455320_STACK = 100,
    LIFTED_STATE_GUARD_4553A0_STACK = 132,
    LIFTED_F4554A0_STACK = 112,
    LIFTED_EFFECT_FIELD_BIND_STACK = 104,
    LIFTED_F455580_STACK = 108,
    LIFTED_F455600_STACK = 112,
    LIFTED_F455670_STACK = 116,
    LIFTED_F455700_STACK = 108,
    LIFTED_F455790_STACK = 124,
    LIFTED_F455830_STACK = 128,
    LIFTED_F4558E0_STACK = 116,
    LIFTED_F455970_STACK = 108,
    LIFTED_F455A00_STACK = 116,
    LIFTED_F455A90_STACK = 112,
    LIFTED_F455B20_STACK = 104,
    LIFTED_F455B90_STACK = 124,
    LIFTED_STATE_DONE_455C30_STACK = 100,
    LIFTED_F455CA0_STACK = 104,
    LIFTED_F455D10_STACK = 124,
    LIFTED_STATE_REPLACE_455DB0_STACK = 96,
    LIFTED_F455E00_STACK = 92,
    LIFTED_EFFECT_SLIDE_BEGIN_STACK = 128,
    LIFTED_EFFECT_SLIDE_WAIT_STACK = 108,
    LIFTED_EFFECT_SLIDE_ADVANCE_STACK = 132,
    LIFTED_EFFECT_SLIDE_END_STACK = 104,
    LIFTED_F4560C0_STACK = 136,
    LIFTED_F456290_STACK = 96,
    LIFTED_F456300_STACK = 124,
    LIFTED_F456490_STACK = 96,
    LIFTED_F4564E0_STACK = 124,
    LIFTED_F4566D0_STACK = 124,
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
    LIFTED_F456EA0_STACK = 104,
    LIFTED_F456F10_STACK = 108,
    LIFTED_F456FA0_STACK = 96,
    LIFTED_F457000_STACK = 100,
    LIFTED_F457060_STACK = 96,
    LIFTED_F4570B0_STACK = 124,
    LIFTED_F457170_STACK = 92,
    LIFTED_F4571F0_STACK = 124,
    LIFTED_F4572B0_STACK = 92,
    LIFTED_F457330_STACK = 132,
    LIFTED_F457420_STACK = 92,
    LIFTED_F457460_STACK = 92,
    LIFTED_F4574A0_STACK = 112,
    LIFTED_F457550_STACK = 104,
    LIFTED_F4575B0_STACK = 132,
    LIFTED_F457670_STACK = 100,
    LIFTED_F4576D0_STACK = 100,
    LIFTED_F457730_STACK = 76,
    LIFTED_F457770_STACK = 96,
    LIFTED_OBJECT_FLIP_SIDE_STACK = 108,
    LIFTED_F4578F0_STACK = 128,
    LIFTED_F457B70_STACK = 116,
    LIFTED_F457C10_STACK = 128,
    LIFTED_F457E40_STACK = 124,
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
    LIFTED_F458710_STACK = 112,
    LIFTED_F4587A0_STACK = 136,
    LIFTED_F4589E0_STACK = 100,
    LIFTED_F458D40_STACK = 124,
    LIFTED_F458F00_STACK = 116,
    LIFTED_F4590A0_STACK = 92,
    LIFTED_F459200_STACK = 84,
    LIFTED_F459760_STACK = 96,
    LIFTED_F4597A0_STACK = 96,
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
    LIFTED_F459E00_STACK = 144,
    LIFTED_TITLE_LETTER_LAUNCH_STACK = 124,
    LIFTED_F45A3E0_STACK = 104,
    LIFTED_F45A440_STACK = 124,
    LIFTED_F45A750_STACK = 132,
    LIFTED_F45A830_STACK = 132,
    LIFTED_F45AA20_STACK = 104,
    LIFTED_F45AA70_STACK = 88,
    LIFTED_F45AAB0_STACK = 156,
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
    LIFTED_F45B9C0_STACK = 104,
    LIFTED_F45BA30_STACK = 120,
    LIFTED_F45BAD0_STACK = 120,
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
    LIFTED_F45C3C0_STACK = 120,
    LIFTED_F45C480_STACK = 124,
    LIFTED_F45C540_STACK = 124,
    LIFTED_F45C6E0_STACK = 88,
    LIFTED_F45C760_STACK = 88,
    LIFTED_F45C7E0_STACK = 84,
    LIFTED_F45C830_STACK = 120,
    LIFTED_F45C8B0_STACK = 72,
    LIFTED_F45C8E0_STACK = 100,
    LIFTED_F45C940_STACK = 100,
    LIFTED_F45CC40_STACK = 140,
    LIFTED_F45CD00_STACK = 140,
    LIFTED_ACTOR_REFRESH_IF_ACTIVE_STACK = 68,
    LIFTED_F45CDD0_STACK = 100,
    LIFTED_F45CE50_STACK = 104,
    LIFTED_F45CEB0_STACK = 108,
    LIFTED_F45CF30_STACK = 92,
    LIFTED_F45CF70_STACK = 116,
    LIFTED_F45D0C0_STACK = 92,
    LIFTED_F45D100_STACK = 92,
    LIFTED_F45D140_STACK = 84,
    LIFTED_F45D160_STACK = 92,
    LIFTED_F45D1A0_STACK = 168,
    LIFTED_F45D420_STACK = 132,
    LIFTED_F45D690_STACK = 132,
    LIFTED_F45D740_STACK = 108,
    LIFTED_F45D7B0_STACK = 108,
    LIFTED_OBJECT_STEP_TOGGLE_STACK = 96,
    LIFTED_TABLE_RELEASE_EVERYTHING_STACK = 212,
    LIFTED_F45E3C0_STACK = 120,
    LIFTED_F45E400_STACK = 120,
    LIFTED_TABLE_BUILD_PAIR_STACK = 128,
    LIFTED_F45E490_STACK = 116,
    LIFTED_F45E530_STACK = 96,
    LIFTED_RESOURCE_ROWS_BUILD_STACK = 124,
    LIFTED_TABLE_BUILD_BY_FLAG_STACK = 116,
    LIFTED_F45E670_STACK = 72,
    LIFTED_RESOURCE_ONE_FRAME_STACK = 72,
    LIFTED_RESOURCE_COLUMN_BUILD_STACK = 104,
    LIFTED_F45E720_STACK = 72,
    LIFTED_TABLE_RELEASE_ONE_STACK = 68,
    LIFTED_TABLE_FILL_SLOT_STACK = 136,
    LIFTED_F45E7B0_STACK = 128,
    LIFTED_F45E810_STACK = 68,
    LIFTED_F45E820_STACK = 68,
    LIFTED_TABLE_RELEASE_RUN_STACK = 76,
    LIFTED_TABLE_FILL_INDEXED_STACK = 136,
    LIFTED_INDEXED_RESOURCE_CALL_STACK = 72,
    LIFTED_F45E8F0_STACK = 76,
    LIFTED_F45E910_STACK = 84,
    LIFTED_GRID_ARRAY_CALL_STACK = 76,
    LIFTED_GRID_CELL_CALL_STACK = 84,
    LIFTED_F45E9E0_STACK = 136,
    LIFTED_F45EA60_STACK = 72,
    LIFTED_F45EA80_STACK = 80,
    LIFTED_F45EAC0_STACK = 348,
    LIFTED_F45EC00_STACK = 120,
    LIFTED_RESOURCE_GRID_FINISH_STACK = 104,
    LIFTED_RESOURCE_PAIR_CALL_STACK = 88,
    LIFTED_RESOURCE_SINGLE_FINISH_STACK = 92,
    LIFTED_F45ED40_STACK = 72,
    LIFTED_F45ED60_STACK = 112,
    LIFTED_RESOURCE_CELL_ROWS_STACK = 128,
    LIFTED_F45EF40_STACK = 132,
    LIFTED_RESOURCE_PAIRED_FINISH_STACK = 212,
    LIFTED_SEVEN_STEPS_STACK = 84,
    LIFTED_F45F0C0_STACK = 120,
    LIFTED_RESOURCE_INDEXED_FINISH_STACK = 124,
    LIFTED_TABLE_IDENTITY_CELLS_STACK = 64,
    LIFTED_RESOURCE_STRIDE_FINISH_STACK = 108,
    LIFTED_RESOURCE_FLAGGED_FINISH_STACK = 112,
    LIFTED_F45F3F0_STACK = 144,
    LIFTED_STRING_APPEND_STACK = 84,
    LIFTED_F45F590_STACK = 84,
    LIFTED_F45F770_STACK = 276,
    LIFTED_UI_PANELS_SLOT1_STACK = 84,
    LIFTED_UI_PANELS_SLOT2_STACK = 92,
    LIFTED_LABEL_FRAME_STACK = 228,
    LIFTED_F45FC80_STACK = 232,
    LIFTED_LABEL_BOX_STACK = 140,
    LIFTED_F45FEE0_STACK = 140,
    LIFTED_F4601C0_STACK = 172,
    LIFTED_F460840_STACK = 252,
    LIFTED_F460A40_STACK = 112,
    LIFTED_F460AD0_STACK = 112,
    LIFTED_F460B60_STACK = 156,
    LIFTED_F460DF0_STACK = 160,
    LIFTED_F460ED0_STACK = 160,
    LIFTED_F460FA0_STACK = 180,
    LIFTED_F461090_STACK = 176,
    LIFTED_F4657F0_STACK = 292,
    LIFTED_MARKER_SPAWN_STACK = 124,
    LIFTED_F466D60_STACK = 2768,
    LIFTED_F46A410_STACK = 644,
    LIFTED_HUD_BUILD_STACK = 1096,
    LIFTED_F46C500_STACK = 152,
    LIFTED_F46C9D0_STACK = 2064,
    LIFTED_MARQUEE_BUILD_STACK = 180,
    LIFTED_F470960_STACK = 240,
    LIFTED_ROW_LABEL_STACK = 240,
    LIFTED_PANEL_GROUP_STACK = 368,
    LIFTED_PANEL_SPAWN_STACK = 168,
    LIFTED_UI_ACTOR_PLACE_STACK = 92,
    LIFTED_UI_COMPANION_SPAWN_STACK = 112,
    LIFTED_SLIDE_PAIR_STACK = 228,
    LIFTED_DELAY_ACTOR_SPAWN_STACK = 128,
    LIFTED_F4713C0_STACK = 64,
    LIFTED_UI_SLIDE_FROM_BELOW_STACK = 68,
    LIFTED_UI_SLIDE_SIDEWAYS_STACK = 64,
    LIFTED_F4718A0_STACK = 128,
    LIFTED_F471920_STACK = 84,
    LIFTED_F471940_STACK = 84,
    LIFTED_F471960_STACK = 84,
    LIFTED_F471980_STACK = 84,
    LIFTED_UI_SLIDE_FROM_ABOVE_STACK = 68,
    LIFTED_F4719E0_STACK = 68,
    LIFTED_F4719F0_STACK = 72,
    LIFTED_F471A20_STACK = 72,
    LIFTED_F471A40_STACK = 72,
    LIFTED_F471A50_STACK = 72,
    LIFTED_F471A60_STACK = 68,
    LIFTED_LIST_CLEAR_CALL_STACK = 68,
    LIFTED_F471A80_STACK = 68,
    LIFTED_F471A90_STACK = 68,
    LIFTED_F471AA0_STACK = 72,
    LIFTED_F471AB0_STACK = 72,
    LIFTED_F471AD0_STACK = 72,
    LIFTED_F471AE0_STACK = 72,
    LIFTED_F471AF0_STACK = 68,
    LIFTED_F471B00_STACK = 68,
    LIFTED_F471B10_STACK = 68,
    LIFTED_F471B20_STACK = 72,
    LIFTED_F471B30_STACK = 72,
    LIFTED_F471B50_STACK = 72,
    LIFTED_F471B60_STACK = 72,
    LIFTED_F471B70_STACK = 68,
    LIFTED_F471B80_STACK = 68,
    LIFTED_F471B90_STACK = 68,
    LIFTED_F471BA0_STACK = 72,
    LIFTED_ACTORS_HANDLER_FROM_EC_STACK = 80,
    LIFTED_ACTORS_HANDLER_FROM_EC_UNLINKED_STACK = 88,
    LIFTED_ACTOR_LIST_IDLE_EXCEPT_STACK = 88,
    LIFTED_ACTOR_LIST_ALL_IDLE_STACK = 80,
    LIFTED_F471CD0_STACK = 80,
    LIFTED_F471D10_STACK = 80,
    LIFTED_F471D50_STACK = 80,
    LIFTED_F471D90_STACK = 80,
    LIFTED_F471DD0_STACK = 80
};

/* Original 0x4505c0. */
uint32_t lifted_f4505c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450630. */
uint32_t lifted_f450630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4506a0. */
uint32_t lifted_f4506a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450710. */
uint32_t lifted_f450710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450730. */
uint32_t lifted_f450730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450750. */
uint32_t lifted_f450750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4507e0. */
uint32_t lifted_f4507e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450830. */
uint32_t lifted_f450830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450860. */
uint32_t lifted_f450860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4508c0. */
uint32_t lifted_f4508c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450920. */
uint32_t lifted_f450920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450960. */
uint32_t lifted_f450960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4509a0. */
uint32_t lifted_f4509a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4509d0. */
uint32_t lifted_f4509d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450a10. */
uint32_t lifted_f450a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450aa0. */
uint32_t lifted_f450aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450b30. */
uint32_t lifted_f450b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450b90. */
uint32_t lifted_f450b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450bf0. */
uint32_t lifted_f450bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x450c70. */
uint32_t lifted_f450c70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

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

/* Original 0x450f80. */
uint32_t lifted_object_start_hold(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f451730(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4523b0. */
uint32_t lifted_f4523b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f452a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452b00. */
uint32_t lifted_f452b00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452b20. */
uint32_t lifted_f452b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452bb0. */
uint32_t lifted_f452bb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452bd0. */
uint32_t lifted_f452bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452c60. */
uint32_t lifted_f452c60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x452c80. */
uint32_t lifted_f452c80(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4535d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453620. */
uint32_t lifted_f453620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453670. */
uint32_t lifted_f453670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4536c0. */
uint32_t lifted_f4536c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453710. */
uint32_t lifted_f453710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453760. */
uint32_t lifted_f453760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4537b0. */
uint32_t lifted_f4537b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453800. */
uint32_t lifted_f453800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453850. */
uint32_t lifted_f453850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4538a0. */
uint32_t lifted_f4538a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4538f0. */
uint32_t lifted_f4538f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453940. */
uint32_t lifted_f453940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453990. */
uint32_t lifted_f453990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4539e0. */
uint32_t lifted_f4539e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453a30. */
uint32_t lifted_f453a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453a80. */
uint32_t lifted_f453a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453b90. */
uint32_t lifted_effect_pair_sound(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453c00. */
uint32_t lifted_effect_copy_speed(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453c90. */
uint32_t lifted_f453c90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453d50. */
uint32_t lifted_f453d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453ef0. */
uint32_t lifted_state_ask_453ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453f40. */
uint32_t lifted_f453f40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x453fd0. */
uint32_t lifted_f453fd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454090. */
uint32_t lifted_f454090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454200. */
uint32_t lifted_state_ask_454200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454250. */
uint32_t lifted_f454250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4542e0. */
uint32_t lifted_f4542e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4543a0. */
uint32_t lifted_f4543a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454510. */
uint32_t lifted_state_ask_454510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454560. */
uint32_t lifted_f454560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454600. */
uint32_t lifted_f454600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4546a0. */
uint32_t lifted_state_cycle_4546a0(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454760. */
uint32_t lifted_f454760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4547b0. */
uint32_t lifted_f4547b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4549d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f454c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454cb0. */
uint32_t lifted_f454cb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454d80. */
uint32_t lifted_state_drain_454d80(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454e30. */
uint32_t lifted_f454e30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454e90. */
uint32_t lifted_f454e90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454f00. */
uint32_t lifted_f454f00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x454fc0. */
uint32_t lifted_state_done_454fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455020. */
uint32_t lifted_f455020(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f4554a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455510. */
uint32_t lifted_effect_field_bind(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455580. */
uint32_t lifted_f455580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455600. */
uint32_t lifted_f455600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455670. */
uint32_t lifted_f455670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455700. */
uint32_t lifted_f455700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455790. */
uint32_t lifted_f455790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455830. */
uint32_t lifted_f455830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4558e0. */
uint32_t lifted_f4558e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455970. */
uint32_t lifted_f455970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455a00. */
uint32_t lifted_f455a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455a90. */
uint32_t lifted_f455a90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455b20. */
uint32_t lifted_f455b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455b90. */
uint32_t lifted_f455b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455c30. */
uint32_t lifted_state_done_455c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455ca0. */
uint32_t lifted_f455ca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455d10. */
uint32_t lifted_f455d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455db0. */
uint32_t lifted_state_replace_455db0(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x455e00. */
uint32_t lifted_f455e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x456290. */
uint32_t lifted_f456290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456300. */
uint32_t lifted_f456300(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x456490. */
uint32_t lifted_f456490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4564e0. */
uint32_t lifted_f4564e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4566d0. */
uint32_t lifted_f4566d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x456ea0. */
uint32_t lifted_f456ea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x457330. */
uint32_t lifted_f457330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457420. */
uint32_t lifted_f457420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457460. */
uint32_t lifted_f457460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4574a0. */
uint32_t lifted_f4574a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457550. */
uint32_t lifted_f457550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4575b0. */
uint32_t lifted_f4575b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4578f0. */
uint32_t lifted_f4578f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457b70. */
uint32_t lifted_f457b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457c10. */
uint32_t lifted_f457c10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x457e40. */
uint32_t lifted_f457e40(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x458710. */
uint32_t lifted_f458710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4587a0. */
uint32_t lifted_f4587a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4589e0. */
uint32_t lifted_f4589e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458d40. */
uint32_t lifted_f458d40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x458f00. */
uint32_t lifted_f458f00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4590a0. */
uint32_t lifted_f4590a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459200. */
uint32_t lifted_f459200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459760. */
uint32_t lifted_f459760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4597a0. */
uint32_t lifted_f4597a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x459e00. */
uint32_t lifted_f459e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a0c0. */
uint32_t lifted_title_letter_launch(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a3e0. */
uint32_t lifted_f45a3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a440. */
uint32_t lifted_f45a440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a750. */
uint32_t lifted_f45a750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45a830. */
uint32_t lifted_f45a830(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f45b9c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ba30. */
uint32_t lifted_f45ba30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45bad0. */
uint32_t lifted_f45bad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

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

/* Original 0x45c3c0. */
uint32_t lifted_f45c3c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c480. */
uint32_t lifted_f45c480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c540. */
uint32_t lifted_f45c540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c6e0. */
uint32_t lifted_f45c6e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c760. */
uint32_t lifted_f45c760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c7e0. */
uint32_t lifted_f45c7e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c830. */
uint32_t lifted_f45c830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c8b0. */
uint32_t lifted_f45c8b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c8e0. */
uint32_t lifted_f45c8e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45c940. */
uint32_t lifted_f45c940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45cc40. */
uint32_t lifted_f45cc40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45cd00. */
uint32_t lifted_f45cd00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45cdc0. */
uint32_t lifted_actor_refresh_if_active(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45cdd0. */
uint32_t lifted_f45cdd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ce50. */
uint32_t lifted_f45ce50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ceb0. */
uint32_t lifted_f45ceb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45cf30. */
uint32_t lifted_f45cf30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45cf70. */
uint32_t lifted_f45cf70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d0c0. */
uint32_t lifted_f45d0c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d100. */
uint32_t lifted_f45d100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d140. */
uint32_t lifted_f45d140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d160. */
uint32_t lifted_f45d160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d1a0. */
uint32_t lifted_f45d1a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45d420. */
uint32_t lifted_f45d420(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x45e260. */
uint32_t lifted_table_release_everything(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e3c0. */
uint32_t lifted_f45e3c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e400. */
uint32_t lifted_f45e400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e440. */
uint32_t lifted_table_build_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e490. */
uint32_t lifted_f45e490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e530. */
uint32_t lifted_f45e530(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
uint32_t lifted_f45e670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e690. */
uint32_t lifted_resource_one_frame(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e6b0. */
uint32_t lifted_resource_column_build(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e720. */
uint32_t lifted_f45e720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e740. */
uint32_t lifted_table_release_one(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e750. */
uint32_t lifted_table_fill_slot(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e7b0. */
uint32_t lifted_f45e7b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e810. */
uint32_t lifted_f45e810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e820. */
uint32_t lifted_f45e820(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e830. */
uint32_t lifted_table_release_run(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e850. */
uint32_t lifted_table_fill_indexed(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e8d0. */
uint32_t lifted_indexed_resource_call(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e8f0. */
uint32_t lifted_f45e8f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e910. */
uint32_t lifted_f45e910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e950. */
uint32_t lifted_grid_array_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e990. */
uint32_t lifted_grid_cell_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45e9e0. */
uint32_t lifted_f45e9e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ea60. */
uint32_t lifted_f45ea60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ea80. */
uint32_t lifted_f45ea80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45eac0. */
uint32_t lifted_f45eac0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ec00. */
uint32_t lifted_f45ec00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ec50. */
uint32_t lifted_resource_grid_finish(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ecd0. */
uint32_t lifted_resource_pair_call(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ed10. */
uint32_t lifted_resource_single_finish(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ed40. */
uint32_t lifted_f45ed40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ed60. */
uint32_t lifted_f45ed60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ee30. */
uint32_t lifted_resource_cell_rows(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ef40. */
uint32_t lifted_f45ef40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f020. */
uint32_t lifted_resource_paired_finish(const VertrixCalls *calls,
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
uint32_t lifted_table_identity_cells(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f1f0. */
uint32_t lifted_resource_stride_finish(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f250. */
uint32_t lifted_resource_flagged_finish(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f3f0. */
uint32_t lifted_f45f3f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f540. */
uint32_t lifted_string_append(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f590. */
uint32_t lifted_f45f590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45f770. */
uint32_t lifted_f45f770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45fa70. */
uint32_t lifted_ui_panels_slot1(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45fab0. */
uint32_t lifted_ui_panels_slot2(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4657f0. */
uint32_t lifted_f4657f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x465a70. */
uint32_t lifted_marker_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x466d60. */
uint32_t lifted_f466d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46a410. */
uint32_t lifted_f46a410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46b810. */
uint32_t lifted_hud_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46c500. */
uint32_t lifted_f46c500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46c9d0. */
uint32_t lifted_f46c9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x46e8b0. */
uint32_t lifted_marquee_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x471020. */
uint32_t lifted_panel_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4710d0. */
uint32_t lifted_ui_actor_place(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471100. */
uint32_t lifted_ui_companion_spawn(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4711a0. */
uint32_t lifted_slide_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471340. */
uint32_t lifted_delay_actor_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4713c0. */
uint32_t lifted_f4713c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4717f0. */
uint32_t lifted_ui_slide_from_below(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471820. */
uint32_t lifted_ui_slide_sideways(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x4719e0. */
uint32_t lifted_f4719e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4719f0. */
uint32_t lifted_f4719f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471a20. */
uint32_t lifted_f471a20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471a40. */
uint32_t lifted_f471a40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471a50. */
uint32_t lifted_f471a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471a60. */
uint32_t lifted_f471a60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471a70. */
uint32_t lifted_list_clear_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471a80. */
uint32_t lifted_f471a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471a90. */
uint32_t lifted_f471a90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471aa0. */
uint32_t lifted_f471aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471ab0. */
uint32_t lifted_f471ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471ad0. */
uint32_t lifted_f471ad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471ae0. */
uint32_t lifted_f471ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471af0. */
uint32_t lifted_f471af0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b00. */
uint32_t lifted_f471b00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b10. */
uint32_t lifted_f471b10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b20. */
uint32_t lifted_f471b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b30. */
uint32_t lifted_f471b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b50. */
uint32_t lifted_f471b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b60. */
uint32_t lifted_f471b60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b70. */
uint32_t lifted_f471b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b80. */
uint32_t lifted_f471b80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471b90. */
uint32_t lifted_f471b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471ba0. */
uint32_t lifted_f471ba0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471bb0. */
uint32_t lifted_actors_handler_from_ec(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471bf0. */
uint32_t lifted_actors_handler_from_ec_unlinked(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x471c40. */
uint32_t lifted_actor_list_idle_except(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471c90. */
uint32_t lifted_actor_list_all_idle(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471cd0. */
uint32_t lifted_f471cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471d10. */
uint32_t lifted_f471d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471d50. */
uint32_t lifted_f471d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471d90. */
uint32_t lifted_f471d90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x471dd0. */
uint32_t lifted_f471dd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
