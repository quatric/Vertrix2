#ifndef VERTRIX_LIFTED_WHOLE_0_H
#define VERTRIX_LIFTED_WHOLE_0_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_MIXER_OUTPUT_STACK = 92,
    LIFTED_F401054_STACK = 92,
    LIFTED_F404480_STACK = 80,
    LIFTED_F404580_STACK = 64,
    LIFTED_F404610_STACK = 76,
    LIFTED_F404680_STACK = 76,
    LIFTED_F405E00_STACK = 100,
    LIFTED_F405EA0_STACK = 88,
    LIFTED_F405EE0_STACK = 80,
    LIFTED_F405F30_STACK = 88,
    LIFTED_F405F70_STACK = 108,
    LIFTED_F406170_STACK = 852,
    LIFTED_F407020_STACK = 184,
    LIFTED_BITS_HEADER_STACK = 176,
    LIFTED_BITS_FILL_STACK = 128,
    LIFTED_F407720_STACK = 100,
    LIFTED_F407830_STACK = 392,
    LIFTED_F4083A0_STACK = 212,
    LIFTED_F4088E0_STACK = 1176,
    LIFTED_WINDOW_TABLES_STACK = 208,
    LIFTED_F40A800_STACK = 88,
    LIFTED_F40A860_STACK = 76,
    LIFTED_F40A890_STACK = 72,
    LIFTED_F40A8F0_STACK = 88,
    LIFTED_F40A950_STACK = 92,
    LIFTED_F40A9D0_STACK = 124,
    LIFTED_F40AAE0_STACK = 76,
    LIFTED_F40AB10_STACK = 68,
    LIFTED_F40AB60_STACK = 84,
    LIFTED_F40ABA0_STACK = 84,
    LIFTED_F40AC00_STACK = 68,
    LIFTED_F40AC10_STACK = 68,
    LIFTED_F40AC20_STACK = 68,
    LIFTED_F40AC30_STACK = 68,
    LIFTED_F40AC50_STACK = 84,
    LIFTED_F40ACA0_STACK = 84,
    LIFTED_F40ACD0_STACK = 68,
    LIFTED_F40AD50_STACK = 68,
    LIFTED_F40ADB0_STACK = 68,
    LIFTED_F40ADC0_STACK = 68,
    LIFTED_F40ADD0_STACK = 68,
    LIFTED_F40ADE0_STACK = 68,
    LIFTED_F40ADF0_STACK = 68,
    LIFTED_F40AE00_STACK = 68,
    LIFTED_F40AE10_STACK = 68,
    LIFTED_F40AE60_STACK = 68,
    LIFTED_MODULE_RESET_CALLS_STACK = 84,
    LIFTED_F40AED0_STACK = 92,
    LIFTED_F40AF30_STACK = 132,
    LIFTED_F40AF90_STACK = 96,
    LIFTED_F40B040_STACK = 116,
    LIFTED_F40B080_STACK = 88,
    LIFTED_F40B620_STACK = 116,
    LIFTED_F40B660_STACK = 88,
    LIFTED_CURVE_TABLE_BUILD_STACK = 120,
    LIFTED_F40C1C0_STACK = 72,
    LIFTED_GLOBAL_DISCARD_CALL_STACK = 68,
    LIFTED_F40C1F0_STACK = 76,
    LIFTED_F40C210_STACK = 68,
    LIFTED_F40C220_STACK = 88,
    LIFTED_F40C260_STACK = 88,
    LIFTED_F40C2A0_STACK = 88,
    LIFTED_F40C2E0_STACK = 88,
    LIFTED_F40C320_STACK = 88,
    LIFTED_F40C360_STACK = 88,
    LIFTED_F40C430_STACK = 100,
    LIFTED_MIXER_CHANNEL_STACK = 116,
    LIFTED_MIXER_PITCH_STACK = 80,
    LIFTED_MIXER_NOTE_PERIOD_STACK = 72,
    LIFTED_MIXER_PORTAMENTO_STACK = 88,
    LIFTED_MIXER_VIBRATO_STACK = 80,
    LIFTED_MIXER_VOLUME_SLIDE_STACK = 76,
    LIFTED_MIXER_VOLUME_COLUMN_STACK = 92,
    LIFTED_MIXER_TRIGGER_RESET_STACK = 76,
    LIFTED_F40E030_STACK = 88,
    LIFTED_MIXER_SELECT_SAMPLE_STACK = 80,
    LIFTED_MIXER_NOTE_RELEASE_STACK = 68,
    LIFTED_F40E670_STACK = 76,
    LIFTED_MIXER_ROW_STACK = 92,
    LIFTED_F40E8A0_STACK = 104,
    LIFTED_FLAGGED_TABLE_CALL_STACK = 92,
    LIFTED_F40EDE0_STACK = 80,
    LIFTED_F40EE30_STACK = 68,
    LIFTED_F40EE60_STACK = 72,
    LIFTED_F40EEA0_STACK = 68,
    LIFTED_F40EF00_STACK = 68,
    LIFTED_F40EF40_STACK = 68,
    LIFTED_OBJECT_FREE_TREE_STACK = 116,
    LIFTED_F40F170_STACK = 72,
    LIFTED_OBJECT_ATTACH_ITEM_STACK = 100,
    LIFTED_F40F9E0_STACK = 308,
    LIFTED_F410150_STACK = 72,
    LIFTED_F4108A0_STACK = 416,
    LIFTED_F411280_STACK = 80,
    LIFTED_F4112D0_STACK = 468,
    LIFTED_F411C70_STACK = 164,
    LIFTED_F4120A0_STACK = 72,
    LIFTED_RECORD_TABLE_LOAD_STACK = 100,
    LIFTED_F412240_STACK = 136,
    LIFTED_F412390_STACK = 88,
    LIFTED_F4123D0_STACK = 68,
    LIFTED_F412430_STACK = 68,
    LIFTED_F412510_STACK = 68,
    LIFTED_F4125E0_STACK = 68,
    LIFTED_F412690_STACK = 80,
    LIFTED_F4126F0_STACK = 64,
    LIFTED_F414A90_STACK = 92,
    LIFTED_F414B10_STACK = 92,
    LIFTED_TEXT_TABLE_REFRESH_STACK = 148,
    LIFTED_F415330_STACK = 80,
    LIFTED_F415350_STACK = 72,
    LIFTED_F4153E0_STACK = 68,
    LIFTED_F415470_STACK = 76,
    LIFTED_F415530_STACK = 68,
    LIFTED_F415550_STACK = 68,
    LIFTED_F415B10_STACK = 68,
    LIFTED_F415B30_STACK = 64,
    LIFTED_F415B40_STACK = 64,
    LIFTED_F415B50_STACK = 68,
    LIFTED_F415B90_STACK = 72,
    LIFTED_F415BD0_STACK = 68,
    LIFTED_F415C00_STACK = 72,
    LIFTED_F415C30_STACK = 72,
    LIFTED_F415D60_STACK = 64,
    LIFTED_F415D90_STACK = 64,
    LIFTED_CLEAR_EACH_CALL_STACK = 76,
    LIFTED_F415E40_STACK = 88,
    LIFTED_F415E80_STACK = 72,
    LIFTED_F415EB0_STACK = 72,
    LIFTED_F415ED0_STACK = 72,
    LIFTED_F415EF0_STACK = 80,
    LIFTED_F415F10_STACK = 80,
    LIFTED_F415F30_STACK = 80,
    LIFTED_F415F50_STACK = 80,
    LIFTED_F415F70_STACK = 80,
    LIFTED_F415F90_STACK = 80,
    LIFTED_F415FB0_STACK = 72,
    LIFTED_F415FC0_STACK = 72,
    LIFTED_F415FD0_STACK = 72,
    LIFTED_F415FE0_STACK = 72,
    LIFTED_F416970_STACK = 72,
    LIFTED_F416B30_STACK = 80,
    LIFTED_F416B50_STACK = 80,
    LIFTED_F416B70_STACK = 80,
    LIFTED_F416B90_STACK = 80,
    LIFTED_F416BB0_STACK = 80,
    LIFTED_F416BD0_STACK = 80,
    LIFTED_F416BF0_STACK = 80,
    LIFTED_POINT_LIST_ADD_STACK = 76,
    LIFTED_F417030_STACK = 80,
    LIFTED_F4170F0_STACK = 80,
    LIFTED_F417130_STACK = 80,
    LIFTED_F4171E0_STACK = 84,
    LIFTED_F417220_STACK = 84,
    LIFTED_F417260_STACK = 80,
    LIFTED_F417290_STACK = 80,
    LIFTED_F4172C0_STACK = 120,
    LIFTED_F417350_STACK = 104,
    LIFTED_F4173D0_STACK = 120,
    LIFTED_F417460_STACK = 104,
    LIFTED_SFX_ALLOCATE_CHANNEL_P1_STACK = 84,
    LIFTED_SFX_ALLOCATE_CHANNEL_P2_STACK = 84,
    LIFTED_F4175B0_STACK = 84,
    LIFTED_F417620_STACK = 84,
    LIFTED_F417790_STACK = 80,
    LIFTED_F417840_STACK = 76,
    LIFTED_F417880_STACK = 72,
    LIFTED_F417890_STACK = 72,
    LIFTED_F4178A0_STACK = 72,
    LIFTED_F4178B0_STACK = 72,
    LIFTED_F4178C0_STACK = 72,
    LIFTED_F4178D0_STACK = 72,
    LIFTED_F417930_STACK = 68,
    LIFTED_F417970_STACK = 72,
    LIFTED_QUAD_AVERAGE_STACK = 112,
    LIFTED_F417C80_STACK = 84,
    LIFTED_F417CF0_STACK = 68,
    LIFTED_F417D10_STACK = 68,
    LIFTED_F417D40_STACK = 68,
    LIFTED_F417D70_STACK = 68,
    LIFTED_F417DA0_STACK = 88,
    LIFTED_F417DF0_STACK = 76,
    LIFTED_F417E20_STACK = 68,
    LIFTED_F417E60_STACK = 164,
    LIFTED_F417ED0_STACK = 164,
    LIFTED_MATCHER_RESET_STACK = 68,
    LIFTED_F417FC0_STACK = 84,
    LIFTED_F418000_STACK = 80,
    LIFTED_F418050_STACK = 88,
    LIFTED_F4180A0_STACK = 84,
    LIFTED_F418100_STACK = 68,
    LIFTED_F418110_STACK = 84,
    LIFTED_F418130_STACK = 84,
    LIFTED_F418150_STACK = 64,
    LIFTED_F4182C0_STACK = 92,
    LIFTED_RESOURCE_ENTRY_CALL_STACK = 72,
    LIFTED_F418550_STACK = 72,
    LIFTED_F418570_STACK = 72,
    LIFTED_RTL_CONSTRUCT_DERIVED_STREAM_STACK = 68,
    LIFTED_F418820_STACK = 64,
    LIFTED_F418830_STACK = 68,
    LIFTED_F418840_STACK = 64,
    LIFTED_F418850_STACK = 72,
    LIFTED_F418870_STACK = 64,
    LIFTED_F418970_STACK = 120,
    LIFTED_F418AE0_STACK = 76,
    LIFTED_F418CE0_STACK = 100,
    LIFTED_F4192A0_STACK = 172,
    LIFTED_F4193B0_STACK = 168,
    LIFTED_GUARDED_CALL_STACK = 68,
    LIFTED_F4194B0_STACK = 68,
    LIFTED_F419EF0_STACK = 116,
    LIFTED_F419F60_STACK = 68,
    LIFTED_F41A010_STACK = 104,
    LIFTED_F41A240_STACK = 104,
    LIFTED_F41A2B0_STACK = 92,
    LIFTED_F41A2F0_STACK = 92,
    LIFTED_F41A4E0_STACK = 96,
    LIFTED_F41A520_STACK = 76,
    LIFTED_F41A680_STACK = 96,
    LIFTED_F41A6C0_STACK = 96,
    LIFTED_F41A700_STACK = 128,
    LIFTED_F41A800_STACK = 148,
    LIFTED_F41A930_STACK = 68,
    LIFTED_F41A940_STACK = 72,
    LIFTED_F41A960_STACK = 104,
    LIFTED_F41A9A0_STACK = 100,
    LIFTED_F41AA20_STACK = 104,
    LIFTED_F41AAA0_STACK = 104,
    LIFTED_F41AAF0_STACK = 68,
    LIFTED_F41AB00_STACK = 76,
    LIFTED_F41AB30_STACK = 76,
    LIFTED_F41AB60_STACK = 76,
    LIFTED_F41AB90_STACK = 96,
    LIFTED_F41ABE0_STACK = 76,
    LIFTED_F41AC00_STACK = 76,
    LIFTED_F41AC20_STACK = 76,
    LIFTED_F41AC40_STACK = 80,
    LIFTED_SURFACE_CLEAR_SECOND_STACK = 72,
    LIFTED_F41AC80_STACK = 84,
    LIFTED_F41ACA0_STACK = 80,
    LIFTED_F41B5E0_STACK = 124,
    LIFTED_F41B680_STACK = 120,
    LIFTED_F41C020_STACK = 124,
    LIFTED_F41C080_STACK = 96,
    LIFTED_F41C0C0_STACK = 84,
    LIFTED_F41C0F0_STACK = 120,
    LIFTED_F41C160_STACK = 120,
    LIFTED_F41C1D0_STACK = 120,
    LIFTED_F41C240_STACK = 120,
    LIFTED_F41C2B0_STACK = 120,
    LIFTED_F41C390_STACK = 116,
    LIFTED_F41C400_STACK = 68,
    LIFTED_F41C6D0_STACK = 120,
    LIFTED_F41C740_STACK = 120,
    LIFTED_F41C9E0_STACK = 176,
    LIFTED_F41CBB0_STACK = 136,
    LIFTED_F41D410_STACK = 108,
    LIFTED_F41D470_STACK = 156,
    LIFTED_F41D510_STACK = 152,
    LIFTED_GATE_DISPATCH_CALL_STACK = 120,
    LIFTED_F41D640_STACK = 72,
    LIFTED_F41D670_STACK = 72,
    LIFTED_F41DD60_STACK = 120,
    LIFTED_F41DDF0_STACK = 120,
    LIFTED_F41DEC0_STACK = 96,
    LIFTED_F41DF00_STACK = 96,
    LIFTED_F41EDE0_STACK = 204,
    LIFTED_F41EFE0_STACK = 152,
    LIFTED_F41F460_STACK = 156,
    LIFTED_F41F910_STACK = 156,
    LIFTED_F41FC70_STACK = 156,
    LIFTED_F421E80_STACK = 144,
    LIFTED_F423D70_STACK = 92,
    LIFTED_F424160_STACK = 68,
    LIFTED_F424180_STACK = 104,
    LIFTED_F4241D0_STACK = 64,
    LIFTED_F4241E0_STACK = 64,
    LIFTED_F4241F0_STACK = 64,
    LIFTED_F424200_STACK = 64,
    LIFTED_OBJECT_CENTER_TITLED_STACK = 84,
    LIFTED_F424790_STACK = 160,
    LIFTED_F424890_STACK = 160,
    LIFTED_F425260_STACK = 184,
    LIFTED_F4253B0_STACK = 164,
    LIFTED_F4259D0_STACK = 144,
    LIFTED_F425A50_STACK = 144,
    LIFTED_F425AE0_STACK = 196,
    LIFTED_OBJECT_SET_TABLE_STACK = 72,
    LIFTED_F425DE0_STACK = 68,
    LIFTED_TABLE_USED_COUNT_STACK = 72,
    LIFTED_F425E20_STACK = 68,
    LIFTED_F425EF0_STACK = 68,
    LIFTED_F425F40_STACK = 64,
    LIFTED_F4261B0_STACK = 84,
    LIFTED_AI_BOMB_SEARCH_STACK = 268,
    LIFTED_F427C10_STACK = 76,
    LIFTED_F427E10_STACK = 76,
    LIFTED_F428110_STACK = 184,
    LIFTED_F428E70_STACK = 112,
    LIFTED_AI_FIND_BEST_SLOT_STACK = 104,
    LIFTED_AI_CHOOSE_PIECE_ROTATION_STACK = 76,
    LIFTED_SETTINGS_DEFAULTS_STACK = 116,
    LIFTED_F429350_STACK = 136,
    LIFTED_SAVED_BLOCK_LOAD_STACK = 96,
    LIFTED_F429460_STACK = 148,
    LIFTED_F429600_STACK = 88,
    LIFTED_F429660_STACK = 64,
    LIFTED_F429670_STACK = 68,
    LIFTED_PIECE_ACTOR_CONSTRUCT_SLOTS_STACK = 96,
    LIFTED_F429D50_STACK = 100,
    LIFTED_F429DF0_STACK = 96,
    LIFTED_F429E80_STACK = 92,
    LIFTED_F429EE0_STACK = 112,
    LIFTED_CHOICE_GRID_PICK_CELL_STACK = 112,
    LIFTED_F42A080_STACK = 100,
    LIFTED_F42A140_STACK = 64,
    LIFTED_F42A170_STACK = 64,
    LIFTED_F42A190_STACK = 64,
    LIFTED_F42A1B0_STACK = 84,
    LIFTED_F42A310_STACK = 144,
    LIFTED_F42A480_STACK = 72,
    LIFTED_F42A4A0_STACK = 72,
    LIFTED_F42A540_STACK = 276,
    LIFTED_F42A800_STACK = 88,
    LIFTED_F42A8B0_STACK = 72,
    LIFTED_F42A8E0_STACK = 84,
    LIFTED_F42A940_STACK = 64,
    LIFTED_F42A950_STACK = 64,
    LIFTED_F42A960_STACK = 64,
    LIFTED_F42A970_STACK = 64,
    LIFTED_F42A980_STACK = 72,
    LIFTED_F42A9D0_STACK = 80,
    LIFTED_F42AA20_STACK = 80,
    LIFTED_PIECE_ACTOR_PARENT_CONSTRUCT_STACK = 76,
    LIFTED_F42ACF0_STACK = 180,
    LIFTED_F42AF30_STACK = 80,
    LIFTED_PIECE_ACTOR_CYCLE_STACK = 88,
    LIFTED_F42B000_STACK = 80,
    LIFTED_F42B050_STACK = 68,
    LIFTED_F42B070_STACK = 68,
    LIFTED_F42B0F0_STACK = 72,
    LIFTED_F42B110_STACK = 64,
    LIFTED_F42B150_STACK = 76,
    LIFTED_F42B290_STACK = 96,
    LIFTED_F42B370_STACK = 232,
    LIFTED_F42B5C0_STACK = 68,
    LIFTED_F42B6B0_STACK = 176,
    LIFTED_F42B920_STACK = 72,
    LIFTED_F42B950_STACK = 80,
    LIFTED_F42B990_STACK = 84,
    LIFTED_F42B9F0_STACK = 80,
    LIFTED_F42BA40_STACK = 68,
    LIFTED_F42BA70_STACK = 72,
    LIFTED_F42BAB0_STACK = 64,
    LIFTED_F42BB00_STACK = 68,
    LIFTED_F42BBD0_STACK = 128,
    LIFTED_BOARD_CONSTRUCT_STACK = 200,
    LIFTED_F42EB60_STACK = 80,
    LIFTED_F42EBA0_STACK = 72,
    LIFTED_F42EBC0_STACK = 72,
    LIFTED_F42EBE0_STACK = 72,
    LIFTED_F42EC00_STACK = 72,
    LIFTED_F42EC20_STACK = 72,
    LIFTED_F42EC40_STACK = 72,
    LIFTED_F42EC60_STACK = 72,
    LIFTED_F42EC80_STACK = 72,
    LIFTED_F42ECA0_STACK = 72,
    LIFTED_F42ECC0_STACK = 72,
    LIFTED_F42ED40_STACK = 76,
    LIFTED_F42ED70_STACK = 76,
    LIFTED_F42EDA0_STACK = 72,
    LIFTED_F42EDF0_STACK = 76,
    LIFTED_F42EE20_STACK = 92,
    LIFTED_F42EE80_STACK = 100,
    LIFTED_F42EEE0_STACK = 72,
    LIFTED_F42EF00_STACK = 72,
    LIFTED_F42EF10_STACK = 72,
    LIFTED_F42EF20_STACK = 72,
    LIFTED_F42EF30_STACK = 72,
    LIFTED_F42EF40_STACK = 72,
    LIFTED_F42EF50_STACK = 72,
    LIFTED_F42EF60_STACK = 68,
    LIFTED_F42EF80_STACK = 68,
    LIFTED_F42F210_STACK = 96,
    LIFTED_F42F280_STACK = 76,
    LIFTED_F42F2B0_STACK = 72,
    LIFTED_F42F2E0_STACK = 84,
    LIFTED_F42F310_STACK = 100,
    LIFTED_F42F3D0_STACK = 76,
    LIFTED_F42F410_STACK = 72,
    LIFTED_F42F440_STACK = 100,
    LIFTED_F42F4B0_STACK = 100,
    LIFTED_F42F520_STACK = 76,
    LIFTED_F42F550_STACK = 76,
    LIFTED_F42F580_STACK = 96,
    LIFTED_F42F620_STACK = 104,
    LIFTED_F42F6E0_STACK = 76,
    LIFTED_F42F720_STACK = 76,
    LIFTED_F42F760_STACK = 88,
    LIFTED_F42F7D0_STACK = 68,
    LIFTED_F42F7F0_STACK = 68,
    LIFTED_F42F810_STACK = 68,
    LIFTED_F42F830_STACK = 68,
    LIFTED_F42F850_STACK = 72,
    LIFTED_F42F860_STACK = 72,
    LIFTED_F42F870_STACK = 72,
    LIFTED_F42F880_STACK = 72,
    LIFTED_F42F890_STACK = 64,
    LIFTED_F42F8A0_STACK = 64,
    LIFTED_F42F8B0_STACK = 80,
    LIFTED_F42F8E0_STACK = 80,
    LIFTED_BOARD_CLIP_STACK = 76,
    LIFTED_F42FF50_STACK = 164,
    LIFTED_F430090_STACK = 68,
    LIFTED_F4300B0_STACK = 76,
    LIFTED_F430100_STACK = 76,
    LIFTED_F430150_STACK = 80,
    LIFTED_ACTOR_SPAWN_MATCH_EFFECT_STACK = 152,
    LIFTED_ACTOR_SPAWN_MATCH_BURST_STACK = 184
};

/* Original 0x401010. */
uint32_t lifted_mixer_output(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x401054. */
uint32_t lifted_f401054(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x404480. */
uint32_t lifted_f404480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x404580. */
uint32_t lifted_f404580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x404610. */
uint32_t lifted_f404610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x404680. */
uint32_t lifted_f404680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x405e00. */
uint32_t lifted_f405e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x405ea0. */
uint32_t lifted_f405ea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x405ee0. */
uint32_t lifted_f405ee0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x405f30. */
uint32_t lifted_f405f30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x405f70. */
uint32_t lifted_f405f70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x406170. */
uint32_t lifted_f406170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x407020. */
uint32_t lifted_f407020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x407280. */
uint32_t lifted_bits_header(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4074a0. */
uint32_t lifted_bits_fill(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x407720. */
uint32_t lifted_f407720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x407830. */
uint32_t lifted_f407830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4083a0. */
uint32_t lifted_f4083a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4088e0. */
uint32_t lifted_f4088e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a590. */
uint32_t lifted_window_tables(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a800. */
uint32_t lifted_f40a800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a860. */
uint32_t lifted_f40a860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a890. */
uint32_t lifted_f40a890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a8f0. */
uint32_t lifted_f40a8f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a950. */
uint32_t lifted_f40a950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40a9d0. */
uint32_t lifted_f40a9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40aae0. */
uint32_t lifted_f40aae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ab10. */
uint32_t lifted_f40ab10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ab60. */
uint32_t lifted_f40ab60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40aba0. */
uint32_t lifted_f40aba0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ac00. */
uint32_t lifted_f40ac00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ac10. */
uint32_t lifted_f40ac10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ac20. */
uint32_t lifted_f40ac20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ac30. */
uint32_t lifted_f40ac30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ac50. */
uint32_t lifted_f40ac50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40aca0. */
uint32_t lifted_f40aca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40acd0. */
uint32_t lifted_f40acd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ad50. */
uint32_t lifted_f40ad50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40adb0. */
uint32_t lifted_f40adb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40adc0. */
uint32_t lifted_f40adc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40add0. */
uint32_t lifted_f40add0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ade0. */
uint32_t lifted_f40ade0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40adf0. */
uint32_t lifted_f40adf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ae00. */
uint32_t lifted_f40ae00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ae10. */
uint32_t lifted_f40ae10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ae60. */
uint32_t lifted_f40ae60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ae80. */
uint32_t lifted_module_reset_calls(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40aed0. */
uint32_t lifted_f40aed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40af30. */
uint32_t lifted_f40af30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40af90. */
uint32_t lifted_f40af90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40b040. */
uint32_t lifted_f40b040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40b080. */
uint32_t lifted_f40b080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40b620. */
uint32_t lifted_f40b620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40b660. */
uint32_t lifted_f40b660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ba00. */
uint32_t lifted_curve_table_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c1c0. */
uint32_t lifted_f40c1c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c1e0. */
uint32_t lifted_global_discard_call(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c1f0. */
uint32_t lifted_f40c1f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c210. */
uint32_t lifted_f40c210(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c220. */
uint32_t lifted_f40c220(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c260. */
uint32_t lifted_f40c260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c2a0. */
uint32_t lifted_f40c2a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c2e0. */
uint32_t lifted_f40c2e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c320. */
uint32_t lifted_f40c320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c360. */
uint32_t lifted_f40c360(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c430. */
uint32_t lifted_f40c430(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40c460. */
uint32_t lifted_mixer_channel(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ce20. */
uint32_t lifted_mixer_pitch(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ce80. */
uint32_t lifted_mixer_note_period(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40cff0. */
uint32_t lifted_mixer_portamento(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40d090. */
uint32_t lifted_mixer_vibrato(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40d250. */
uint32_t lifted_mixer_volume_slide(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40dc80. */
uint32_t lifted_mixer_volume_column(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40df20. */
uint32_t lifted_mixer_trigger_reset(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e030. */
uint32_t lifted_f40e030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e580. */
uint32_t lifted_mixer_select_sample(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e640. */
uint32_t lifted_mixer_note_release(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e670. */
uint32_t lifted_f40e670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e770. */
uint32_t lifted_mixer_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40e8a0. */
uint32_t lifted_f40e8a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ed70. */
uint32_t lifted_flagged_table_call(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ede0. */
uint32_t lifted_f40ede0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ee30. */
uint32_t lifted_f40ee30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ee60. */
uint32_t lifted_f40ee60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40eea0. */
uint32_t lifted_f40eea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ef00. */
uint32_t lifted_f40ef00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ef40. */
uint32_t lifted_f40ef40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ef90. */
uint32_t lifted_object_free_tree(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40f170. */
uint32_t lifted_f40f170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40f910. */
uint32_t lifted_object_attach_item(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40f9e0. */
uint32_t lifted_f40f9e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x410150. */
uint32_t lifted_f410150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4108a0. */
uint32_t lifted_f4108a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x411280. */
uint32_t lifted_f411280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4112d0. */
uint32_t lifted_f4112d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x411c70. */
uint32_t lifted_f411c70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4120a0. */
uint32_t lifted_f4120a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4121e0. */
uint32_t lifted_record_table_load(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x412240. */
uint32_t lifted_f412240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x412390. */
uint32_t lifted_f412390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4123d0. */
uint32_t lifted_f4123d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x412430. */
uint32_t lifted_f412430(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x412510. */
uint32_t lifted_f412510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4125e0. */
uint32_t lifted_f4125e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x412690. */
uint32_t lifted_f412690(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4126f0. */
uint32_t lifted_f4126f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x414a90. */
uint32_t lifted_f414a90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x414b10. */
uint32_t lifted_f414b10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415180. */
uint32_t lifted_text_table_refresh(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415330. */
uint32_t lifted_f415330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415350. */
uint32_t lifted_f415350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4153e0. */
uint32_t lifted_f4153e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415470. */
uint32_t lifted_f415470(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415530. */
uint32_t lifted_f415530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415550. */
uint32_t lifted_f415550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415b10. */
uint32_t lifted_f415b10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415b30. */
uint32_t lifted_f415b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415b40. */
uint32_t lifted_f415b40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415b50. */
uint32_t lifted_f415b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415b90. */
uint32_t lifted_f415b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415bd0. */
uint32_t lifted_f415bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415c00. */
uint32_t lifted_f415c00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415c30. */
uint32_t lifted_f415c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415d60. */
uint32_t lifted_f415d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415d90. */
uint32_t lifted_f415d90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415e10. */
uint32_t lifted_clear_each_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415e40. */
uint32_t lifted_f415e40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415e80. */
uint32_t lifted_f415e80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415eb0. */
uint32_t lifted_f415eb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415ed0. */
uint32_t lifted_f415ed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415ef0. */
uint32_t lifted_f415ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415f10. */
uint32_t lifted_f415f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415f30. */
uint32_t lifted_f415f30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415f50. */
uint32_t lifted_f415f50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415f70. */
uint32_t lifted_f415f70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415f90. */
uint32_t lifted_f415f90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415fb0. */
uint32_t lifted_f415fb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415fc0. */
uint32_t lifted_f415fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415fd0. */
uint32_t lifted_f415fd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415fe0. */
uint32_t lifted_f415fe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416970. */
uint32_t lifted_f416970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416b30. */
uint32_t lifted_f416b30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416b50. */
uint32_t lifted_f416b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416b70. */
uint32_t lifted_f416b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416b90. */
uint32_t lifted_f416b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416bb0. */
uint32_t lifted_f416bb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416bd0. */
uint32_t lifted_f416bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416bf0. */
uint32_t lifted_f416bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416c10. */
uint32_t lifted_point_list_add(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417030. */
uint32_t lifted_f417030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4170f0. */
uint32_t lifted_f4170f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417130. */
uint32_t lifted_f417130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4171e0. */
uint32_t lifted_f4171e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417220. */
uint32_t lifted_f417220(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417260. */
uint32_t lifted_f417260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417290. */
uint32_t lifted_f417290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4172c0. */
uint32_t lifted_f4172c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417350. */
uint32_t lifted_f417350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4173d0. */
uint32_t lifted_f4173d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417460. */
uint32_t lifted_f417460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4174f0. */
uint32_t lifted_sfx_allocate_channel_p1(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417550. */
uint32_t lifted_sfx_allocate_channel_p2(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4175b0. */
uint32_t lifted_f4175b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417620. */
uint32_t lifted_f417620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417790. */
uint32_t lifted_f417790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417840. */
uint32_t lifted_f417840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417880. */
uint32_t lifted_f417880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417890. */
uint32_t lifted_f417890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4178a0. */
uint32_t lifted_f4178a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4178b0. */
uint32_t lifted_f4178b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4178c0. */
uint32_t lifted_f4178c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4178d0. */
uint32_t lifted_f4178d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417930. */
uint32_t lifted_f417930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417970. */
uint32_t lifted_f417970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4179d0. */
uint32_t lifted_quad_average(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417c80. */
uint32_t lifted_f417c80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417cf0. */
uint32_t lifted_f417cf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417d10. */
uint32_t lifted_f417d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417d40. */
uint32_t lifted_f417d40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417d70. */
uint32_t lifted_f417d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417da0. */
uint32_t lifted_f417da0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417df0. */
uint32_t lifted_f417df0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417e20. */
uint32_t lifted_f417e20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417e60. */
uint32_t lifted_f417e60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417ed0. */
uint32_t lifted_f417ed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417f40. */
uint32_t lifted_matcher_reset(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417fc0. */
uint32_t lifted_f417fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418000. */
uint32_t lifted_f418000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418050. */
uint32_t lifted_f418050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4180a0. */
uint32_t lifted_f4180a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418100. */
uint32_t lifted_f418100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418110. */
uint32_t lifted_f418110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418130. */
uint32_t lifted_f418130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418150. */
uint32_t lifted_f418150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4182c0. */
uint32_t lifted_f4182c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4182f0. */
uint32_t lifted_resource_entry_call(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418550. */
uint32_t lifted_f418550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418570. */
uint32_t lifted_f418570(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418760. */
uint32_t lifted_rtl_construct_derived_stream(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418820. */
uint32_t lifted_f418820(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418830. */
uint32_t lifted_f418830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418840. */
uint32_t lifted_f418840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418850. */
uint32_t lifted_f418850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418870. */
uint32_t lifted_f418870(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418970. */
uint32_t lifted_f418970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418ae0. */
uint32_t lifted_f418ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418ce0. */
uint32_t lifted_f418ce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4192a0. */
uint32_t lifted_f4192a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4193b0. */
uint32_t lifted_f4193b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x419490. */
uint32_t lifted_guarded_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4194b0. */
uint32_t lifted_f4194b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x419ef0. */
uint32_t lifted_f419ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x419f60. */
uint32_t lifted_f419f60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a010. */
uint32_t lifted_f41a010(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a240. */
uint32_t lifted_f41a240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a2b0. */
uint32_t lifted_f41a2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a2f0. */
uint32_t lifted_f41a2f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a4e0. */
uint32_t lifted_f41a4e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a520. */
uint32_t lifted_f41a520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a680. */
uint32_t lifted_f41a680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a6c0. */
uint32_t lifted_f41a6c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a700. */
uint32_t lifted_f41a700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a800. */
uint32_t lifted_f41a800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a930. */
uint32_t lifted_f41a930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a940. */
uint32_t lifted_f41a940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a960. */
uint32_t lifted_f41a960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a9a0. */
uint32_t lifted_f41a9a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41aa20. */
uint32_t lifted_f41aa20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41aaa0. */
uint32_t lifted_f41aaa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41aaf0. */
uint32_t lifted_f41aaf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ab00. */
uint32_t lifted_f41ab00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ab30. */
uint32_t lifted_f41ab30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ab60. */
uint32_t lifted_f41ab60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ab90. */
uint32_t lifted_f41ab90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41abe0. */
uint32_t lifted_f41abe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ac00. */
uint32_t lifted_f41ac00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ac20. */
uint32_t lifted_f41ac20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ac40. */
uint32_t lifted_f41ac40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ac70. */
uint32_t lifted_surface_clear_second(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ac80. */
uint32_t lifted_f41ac80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41aca0. */
uint32_t lifted_f41aca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41b5e0. */
uint32_t lifted_f41b5e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41b680. */
uint32_t lifted_f41b680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c020. */
uint32_t lifted_f41c020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c080. */
uint32_t lifted_f41c080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c0c0. */
uint32_t lifted_f41c0c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c0f0. */
uint32_t lifted_f41c0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c160. */
uint32_t lifted_f41c160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c1d0. */
uint32_t lifted_f41c1d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c240. */
uint32_t lifted_f41c240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c2b0. */
uint32_t lifted_f41c2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c390. */
uint32_t lifted_f41c390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c400. */
uint32_t lifted_f41c400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c6d0. */
uint32_t lifted_f41c6d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c740. */
uint32_t lifted_f41c740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c9e0. */
uint32_t lifted_f41c9e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41cbb0. */
uint32_t lifted_f41cbb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d410. */
uint32_t lifted_f41d410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d470. */
uint32_t lifted_f41d470(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d510. */
uint32_t lifted_f41d510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d5b0. */
uint32_t lifted_gate_dispatch_call(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d640. */
uint32_t lifted_f41d640(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41d670. */
uint32_t lifted_f41d670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41dd60. */
uint32_t lifted_f41dd60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ddf0. */
uint32_t lifted_f41ddf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41dec0. */
uint32_t lifted_f41dec0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41df00. */
uint32_t lifted_f41df00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ede0. */
uint32_t lifted_f41ede0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41efe0. */
uint32_t lifted_f41efe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41f460. */
uint32_t lifted_f41f460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41f910. */
uint32_t lifted_f41f910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41fc70. */
uint32_t lifted_f41fc70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x421e80. */
uint32_t lifted_f421e80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x423d70. */
uint32_t lifted_f423d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424160. */
uint32_t lifted_f424160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424180. */
uint32_t lifted_f424180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4241d0. */
uint32_t lifted_f4241d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4241e0. */
uint32_t lifted_f4241e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4241f0. */
uint32_t lifted_f4241f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424200. */
uint32_t lifted_f424200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424760. */
uint32_t lifted_object_center_titled(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424790. */
uint32_t lifted_f424790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424890. */
uint32_t lifted_f424890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425260. */
uint32_t lifted_f425260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4253b0. */
uint32_t lifted_f4253b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4259d0. */
uint32_t lifted_f4259d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425a50. */
uint32_t lifted_f425a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425ae0. */
uint32_t lifted_f425ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425d30. */
uint32_t lifted_object_set_table(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425de0. */
uint32_t lifted_f425de0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425e00. */
uint32_t lifted_table_used_count(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425e20. */
uint32_t lifted_f425e20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425ef0. */
uint32_t lifted_f425ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425f40. */
uint32_t lifted_f425f40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4261b0. */
uint32_t lifted_f4261b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x427380. */
uint32_t lifted_ai_bomb_search(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x427c10. */
uint32_t lifted_f427c10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x427e10. */
uint32_t lifted_f427e10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x428110. */
uint32_t lifted_f428110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x428e70. */
uint32_t lifted_f428e70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429000. */
uint32_t lifted_ai_find_best_slot(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4290a0. */
uint32_t lifted_ai_choose_piece_rotation(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4290c0. */
uint32_t lifted_settings_defaults(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429350. */
uint32_t lifted_f429350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4293e0. */
uint32_t lifted_saved_block_load(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429460. */
uint32_t lifted_f429460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429600. */
uint32_t lifted_f429600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429660. */
uint32_t lifted_f429660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429670. */
uint32_t lifted_f429670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429880. */
uint32_t lifted_piece_actor_construct_slots(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429d50. */
uint32_t lifted_f429d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429df0. */
uint32_t lifted_f429df0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429e80. */
uint32_t lifted_f429e80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429ee0. */
uint32_t lifted_f429ee0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429fe0. */
uint32_t lifted_choice_grid_pick_cell(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a080. */
uint32_t lifted_f42a080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a140. */
uint32_t lifted_f42a140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a170. */
uint32_t lifted_f42a170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a190. */
uint32_t lifted_f42a190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a1b0. */
uint32_t lifted_f42a1b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a310. */
uint32_t lifted_f42a310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a480. */
uint32_t lifted_f42a480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a4a0. */
uint32_t lifted_f42a4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a540. */
uint32_t lifted_f42a540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a800. */
uint32_t lifted_f42a800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a8b0. */
uint32_t lifted_f42a8b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a8e0. */
uint32_t lifted_f42a8e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a940. */
uint32_t lifted_f42a940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a950. */
uint32_t lifted_f42a950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a960. */
uint32_t lifted_f42a960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a970. */
uint32_t lifted_f42a970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a980. */
uint32_t lifted_f42a980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a9d0. */
uint32_t lifted_f42a9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42aa20. */
uint32_t lifted_f42aa20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42aab0. */
uint32_t lifted_piece_actor_parent_construct(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42acf0. */
uint32_t lifted_f42acf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42af30. */
uint32_t lifted_f42af30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42af80. */
uint32_t lifted_piece_actor_cycle(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b000. */
uint32_t lifted_f42b000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b050. */
uint32_t lifted_f42b050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b070. */
uint32_t lifted_f42b070(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b0f0. */
uint32_t lifted_f42b0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b110. */
uint32_t lifted_f42b110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b150. */
uint32_t lifted_f42b150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b290. */
uint32_t lifted_f42b290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b370. */
uint32_t lifted_f42b370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b5c0. */
uint32_t lifted_f42b5c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b6b0. */
uint32_t lifted_f42b6b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b920. */
uint32_t lifted_f42b920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b950. */
uint32_t lifted_f42b950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b990. */
uint32_t lifted_f42b990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b9f0. */
uint32_t lifted_f42b9f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ba40. */
uint32_t lifted_f42ba40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ba70. */
uint32_t lifted_f42ba70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42bab0. */
uint32_t lifted_f42bab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42bb00. */
uint32_t lifted_f42bb00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42bbd0. */
uint32_t lifted_f42bbd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42e870. */
uint32_t lifted_board_construct(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42eb60. */
uint32_t lifted_f42eb60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42eba0. */
uint32_t lifted_f42eba0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ebc0. */
uint32_t lifted_f42ebc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ebe0. */
uint32_t lifted_f42ebe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ec00. */
uint32_t lifted_f42ec00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ec20. */
uint32_t lifted_f42ec20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ec40. */
uint32_t lifted_f42ec40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ec60. */
uint32_t lifted_f42ec60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ec80. */
uint32_t lifted_f42ec80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42eca0. */
uint32_t lifted_f42eca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ecc0. */
uint32_t lifted_f42ecc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ed40. */
uint32_t lifted_f42ed40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ed70. */
uint32_t lifted_f42ed70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42eda0. */
uint32_t lifted_f42eda0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42edf0. */
uint32_t lifted_f42edf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ee20. */
uint32_t lifted_f42ee20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ee80. */
uint32_t lifted_f42ee80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42eee0. */
uint32_t lifted_f42eee0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef00. */
uint32_t lifted_f42ef00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef10. */
uint32_t lifted_f42ef10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef20. */
uint32_t lifted_f42ef20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef30. */
uint32_t lifted_f42ef30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef40. */
uint32_t lifted_f42ef40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef50. */
uint32_t lifted_f42ef50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef60. */
uint32_t lifted_f42ef60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ef80. */
uint32_t lifted_f42ef80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f210. */
uint32_t lifted_f42f210(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f280. */
uint32_t lifted_f42f280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f2b0. */
uint32_t lifted_f42f2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f2e0. */
uint32_t lifted_f42f2e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f310. */
uint32_t lifted_f42f310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f3d0. */
uint32_t lifted_f42f3d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f410. */
uint32_t lifted_f42f410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f440. */
uint32_t lifted_f42f440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f4b0. */
uint32_t lifted_f42f4b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f520. */
uint32_t lifted_f42f520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f550. */
uint32_t lifted_f42f550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f580. */
uint32_t lifted_f42f580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f620. */
uint32_t lifted_f42f620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f6e0. */
uint32_t lifted_f42f6e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f720. */
uint32_t lifted_f42f720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f760. */
uint32_t lifted_f42f760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f7d0. */
uint32_t lifted_f42f7d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f7f0. */
uint32_t lifted_f42f7f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f810. */
uint32_t lifted_f42f810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f830. */
uint32_t lifted_f42f830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f850. */
uint32_t lifted_f42f850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f860. */
uint32_t lifted_f42f860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f870. */
uint32_t lifted_f42f870(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f880. */
uint32_t lifted_f42f880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f890. */
uint32_t lifted_f42f890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f8a0. */
uint32_t lifted_f42f8a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f8b0. */
uint32_t lifted_f42f8b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42f8e0. */
uint32_t lifted_f42f8e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ff10. */
uint32_t lifted_board_clip(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ff50. */
uint32_t lifted_f42ff50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430090. */
uint32_t lifted_f430090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4300b0. */
uint32_t lifted_f4300b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430100. */
uint32_t lifted_f430100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430150. */
uint32_t lifted_f430150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x430190. */
uint32_t lifted_actor_spawn_match_effect(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4302a0. */
uint32_t lifted_actor_spawn_match_burst(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
