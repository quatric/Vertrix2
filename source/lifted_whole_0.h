#ifndef VERTRIX_LIFTED_WHOLE_0_H
#define VERTRIX_LIFTED_WHOLE_0_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_MIXER_OUTPUT_STACK = 92,
    LIFTED_F406170_STACK = 852,
    LIFTED_F407020_STACK = 184,
    LIFTED_F407830_STACK = 392,
    LIFTED_F4083A0_STACK = 212,
    LIFTED_F40AED0_STACK = 92,
    LIFTED_CURVE_TABLE_BUILD_STACK = 120,
    LIFTED_MIXER_VIBRATO_STACK = 80,
    LIFTED_MIXER_VOLUME_SLIDE_STACK = 76,
    LIFTED_OBJECT_FREE_TREE_STACK = 116,
    LIFTED_OBJECT_ATTACH_ITEM_STACK = 100,
    LIFTED_F411280_STACK = 80,
    LIFTED_F412240_STACK = 136,
    LIFTED_F415580_STACK = 976,
    LIFTED_TABLE_ALL_FILLED_415C30_STACK = 72,
    LIFTED_TABLE_FIND_MATCHING_STACK = 88,
    LIFTED_NOTICE_CALL_FULL_STACK = 164,
    LIFTED_F416140_STACK = 244,
    LIFTED_F4163B0_STACK = 176,
    LIFTED_F416500_STACK = 372,
    LIFTED_F416990_STACK = 180,
    LIFTED_OBJECT_LOAD_SCRIPT_STACK = 148,
    LIFTED_POINT_LIST_ADD_STACK = 76,
    LIFTED_F417690_STACK = 364,
    LIFTED_TABLE_RANDOM_EMPTY_STACK = 164,
    LIFTED_TABLE_RANDOM_EMPTY_417ED0_STACK = 164,
    LIFTED_CLOCK_TEXT_STACK = 212,
    LIFTED_RTL_CONSTRUCT_DERIVED_STREAM_STACK = 68,
    LIFTED_F418AF0_STACK = 488,
    LIFTED_F418D50_STACK = 896,
    LIFTED_F4192A0_STACK = 172,
    LIFTED_F4193B0_STACK = 168,
    LIFTED_F41A080_STACK = 300,
    LIFTED_F41A320_STACK = 692,
    LIFTED_F41A540_STACK = 680,
    LIFTED_F41ACC0_STACK = 1048,
    LIFTED_F41C9E0_STACK = 176,
    LIFTED_F41DF30_STACK = 1088,
    LIFTED_F41E310_STACK = 808,
    LIFTED_F41E5E0_STACK = 724,
    LIFTED_F41EDE0_STACK = 204,
    LIFTED_F41F080_STACK = 484,
    LIFTED_F41F500_STACK = 476,
    LIFTED_F41FC70_STACK = 156,
    LIFTED_F41FD20_STACK = 180,
    LIFTED_F420040_STACK = 516,
    LIFTED_F420E10_STACK = 420,
    LIFTED_F421AC0_STACK = 436,
    LIFTED_F421BE0_STACK = 524,
    LIFTED_F423DC0_STACK = 632,
    LIFTED_F423EA0_STACK = 640,
    LIFTED_F424180_STACK = 104,
    LIFTED_F424230_STACK = 436,
    LIFTED_F424790_STACK = 160,
    LIFTED_F424890_STACK = 160,
    LIFTED_F425260_STACK = 184,
    LIFTED_F4253B0_STACK = 164,
    LIFTED_F425AE0_STACK = 196,
    LIFTED_PIECE_INIT_FROM_KIND_STACK = 68,
    LIFTED_OBJECT_COMPARE_REGIONS_STACK = 280,
    LIFTED_AI_FEATURES_STACK = 76,
    LIFTED_AI_COMPARE_BOARDS_STACK = 184,
    LIFTED_AI_RECORD_SCORE_STACK = 136,
    LIFTED_AI_FIND_BEST_SLOT_STACK = 104,
    LIFTED_SETTINGS_DEFAULTS_STACK = 116,
    LIFTED_F429460_STACK = 148,
    LIFTED_SLOT_OBJECTS_MAKE_STACK = 168,
    LIFTED_CHOICE_GRID_PICK_ROWS_STACK = 112,
    LIFTED_CHOICE_GRID_PICK_CELL_STACK = 112,
    LIFTED_CHOICE_GRID_PICK_COLUMN_STACK = 100,
    LIFTED_CHOICE_GRID_AVAILABLE_STACK = 64,
    LIFTED_F42A310_STACK = 144,
    LIFTED_F42A540_STACK = 276,
    LIFTED_PIECE_ACTOR_CONSTRUCT_PLACED_STACK = 180,
    LIFTED_F42B290_STACK = 96,
    LIFTED_UI_PLAYER_PREVIEWS_CONSTRUCT_STACK = 232,
    LIFTED_F42B6B0_STACK = 176,
    LIFTED_BLOCK_CREATE_FULL_STACK = 128,
    LIFTED_BOARD_CONSTRUCT_STACK = 200
};

/* Original 0x401010. */
uint32_t lifted_mixer_output(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x406170. */
uint32_t lifted_f406170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x407020. */
uint32_t lifted_f407020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x407830. */
uint32_t lifted_f407830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4083a0. */
uint32_t lifted_f4083a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40aed0. */
uint32_t lifted_f40aed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ba00. */
uint32_t lifted_curve_table_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40d090. */
uint32_t lifted_mixer_vibrato(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40d250. */
uint32_t lifted_mixer_volume_slide(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ef90. */
uint32_t lifted_object_free_tree(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40f910. */
uint32_t lifted_object_attach_item(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x411280. */
uint32_t lifted_f411280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x412240. */
uint32_t lifted_f412240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415580. */
uint32_t lifted_f415580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415c30. */
uint32_t lifted_table_all_filled_415c30(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415e40. */
uint32_t lifted_table_find_matching(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416010. */
uint32_t lifted_notice_call_full(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416140. */
uint32_t lifted_f416140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4163b0. */
uint32_t lifted_f4163b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416500. */
uint32_t lifted_f416500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416990. */
uint32_t lifted_f416990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416a80. */
uint32_t lifted_object_load_script(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416c10. */
uint32_t lifted_point_list_add(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417690. */
uint32_t lifted_f417690(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417e60. */
uint32_t lifted_table_random_empty(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x417ed0. */
uint32_t lifted_table_random_empty_417ed0(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418170. */
uint32_t lifted_clock_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418760. */
uint32_t lifted_rtl_construct_derived_stream(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418af0. */
uint32_t lifted_f418af0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x418d50. */
uint32_t lifted_f418d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4192a0. */
uint32_t lifted_f4192a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4193b0. */
uint32_t lifted_f4193b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a080. */
uint32_t lifted_f41a080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a320. */
uint32_t lifted_f41a320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a540. */
uint32_t lifted_f41a540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41acc0. */
uint32_t lifted_f41acc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41c9e0. */
uint32_t lifted_f41c9e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41df30. */
uint32_t lifted_f41df30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41e310. */
uint32_t lifted_f41e310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41e5e0. */
uint32_t lifted_f41e5e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41ede0. */
uint32_t lifted_f41ede0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41f080. */
uint32_t lifted_f41f080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41f500. */
uint32_t lifted_f41f500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41fc70. */
uint32_t lifted_f41fc70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41fd20. */
uint32_t lifted_f41fd20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x420040. */
uint32_t lifted_f420040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x420e10. */
uint32_t lifted_f420e10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x421ac0. */
uint32_t lifted_f421ac0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x421be0. */
uint32_t lifted_f421be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x423dc0. */
uint32_t lifted_f423dc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x423ea0. */
uint32_t lifted_f423ea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424180. */
uint32_t lifted_f424180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x424230. */
uint32_t lifted_f424230(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x425ae0. */
uint32_t lifted_f425ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425ef0. */
uint32_t lifted_piece_init_from_kind(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x427ae0. */
uint32_t lifted_object_compare_regions(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x427c10. */
uint32_t lifted_ai_features(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x428110. */
uint32_t lifted_ai_compare_boards(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x428610. */
uint32_t lifted_ai_record_score(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429000. */
uint32_t lifted_ai_find_best_slot(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4290c0. */
uint32_t lifted_settings_defaults(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429460. */
uint32_t lifted_f429460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429bf0. */
uint32_t lifted_slot_objects_make(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429ee0. */
uint32_t lifted_choice_grid_pick_rows(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429fe0. */
uint32_t lifted_choice_grid_pick_cell(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a080. */
uint32_t lifted_choice_grid_pick_column(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a190. */
uint32_t lifted_choice_grid_available(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a310. */
uint32_t lifted_f42a310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a540. */
uint32_t lifted_f42a540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42acf0. */
uint32_t lifted_piece_actor_construct_placed(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b290. */
uint32_t lifted_f42b290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b370. */
uint32_t lifted_ui_player_previews_construct(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b6b0. */
uint32_t lifted_f42b6b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42bbd0. */
uint32_t lifted_block_create_full(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42e870. */
uint32_t lifted_board_construct(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

#endif
