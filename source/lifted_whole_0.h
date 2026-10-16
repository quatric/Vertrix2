#ifndef VERTRIX_LIFTED_WHOLE_0_H
#define VERTRIX_LIFTED_WHOLE_0_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F406170_STACK = 852,
    LIFTED_F407020_STACK = 184,
    LIFTED_F407830_STACK = 392,
    LIFTED_F4083A0_STACK = 212,
    LIFTED_F40AED0_STACK = 92,
    LIFTED_CURVE_TABLE_BUILD_STACK = 120,
    LIFTED_OBJECT_FREE_TREE_STACK = 116,
    LIFTED_OBJECT_ATTACH_ITEM_STACK = 100,
    LIFTED_F415580_STACK = 976,
    LIFTED_F416140_STACK = 244,
    LIFTED_F416500_STACK = 372,
    LIFTED_POINT_LIST_ADD_STACK = 76,
    LIFTED_RTL_CONSTRUCT_DERIVED_STREAM_STACK = 68,
    LIFTED_F418AF0_STACK = 488,
    LIFTED_F418D50_STACK = 896,
    LIFTED_F4192A0_STACK = 172,
    LIFTED_F4193B0_STACK = 168,
    LIFTED_F41A320_STACK = 692,
    LIFTED_F41A540_STACK = 680,
    LIFTED_F41ACC0_STACK = 1048,
    LIFTED_F41DF30_STACK = 1088,
    LIFTED_F41E310_STACK = 808,
    LIFTED_F41E5E0_STACK = 724,
    LIFTED_F41F080_STACK = 484,
    LIFTED_F41F500_STACK = 476,
    LIFTED_F420040_STACK = 516,
    LIFTED_F420E10_STACK = 420,
    LIFTED_F421AC0_STACK = 436,
    LIFTED_F421BE0_STACK = 524,
    LIFTED_F423DC0_STACK = 632,
    LIFTED_F423EA0_STACK = 640,
    LIFTED_F424230_STACK = 436,
    LIFTED_PIECE_INIT_FROM_KIND_STACK = 68,
    LIFTED_OBJECT_COMPARE_REGIONS_STACK = 280,
    LIFTED_AI_COMPARE_BOARDS_STACK = 184,
    LIFTED_AI_RECORD_SCORE_STACK = 136,
    LIFTED_AI_FIND_BEST_SLOT_STACK = 104,
    LIFTED_SETTINGS_DEFAULTS_STACK = 116,
    LIFTED_CHOICE_GRID_PICK_CELL_STACK = 112,
    LIFTED_F42A540_STACK = 276,
    LIFTED_PIECE_ACTOR_CONSTRUCT_PLACED_STACK = 180
};

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

/* Original 0x40ef90. */
uint32_t lifted_object_free_tree(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40f910. */
uint32_t lifted_object_attach_item(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x415580. */
uint32_t lifted_f415580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416140. */
uint32_t lifted_f416140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416500. */
uint32_t lifted_f416500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x416c10. */
uint32_t lifted_point_list_add(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x41a320. */
uint32_t lifted_f41a320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41a540. */
uint32_t lifted_f41a540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41acc0. */
uint32_t lifted_f41acc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x41f080. */
uint32_t lifted_f41f080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41f500. */
uint32_t lifted_f41f500(const VertrixCalls *calls, const VertrixFactoryServices *services,
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

/* Original 0x424230. */
uint32_t lifted_f424230(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425ef0. */
uint32_t lifted_piece_init_from_kind(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x427ae0. */
uint32_t lifted_object_compare_regions(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
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

/* Original 0x429fe0. */
uint32_t lifted_choice_grid_pick_cell(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a540. */
uint32_t lifted_f42a540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42acf0. */
uint32_t lifted_piece_actor_construct_placed(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

#endif
