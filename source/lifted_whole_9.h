#ifndef VERTRIX_LIFTED_WHOLE_9_H
#define VERTRIX_LIFTED_WHOLE_9_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F41D6D0_STACK = 392,
    LIFTED_F423BC0_STACK = 220,
    LIFTED_BOARDS_CONVERT_COUNTS_STACK = 208,
    LIFTED_BOARDS_CONVERT_RANDOM_STACK = 220,
    LIFTED_F4375F0_STACK = 176,
    LIFTED_BOARD_SPIN_MARKED_STACK = 256,
    LIFTED_F45FFB0_STACK = 248,
    LIFTED_STRING_TABLE_ASSIGN_STACK = 112,
    LIFTED_F47F1B0_STACK = 392,
    LIFTED_F480080_STACK = 84,
    LIFTED_OBJECT_KIND_TEXT_STACK = 172,
    LIFTED_PATH_SPLIT_A_STACK = 108,
    LIFTED_STRING_APPEND_CALLS_STACK = 84,
    LIFTED_TEXT_WRAP_STACK = 216,
    LIFTED_F4B42E0_STACK = 184,
    LIFTED_OBJECT_TEXT_INSERT_STACK = 236,
    LIFTED_OBJECT_TEXT_REMOVE_STACK = 216,
    LIFTED_OBJECT_TEXT_REBUILD_STACK = 216,
    LIFTED_F4B6A30_STACK = 136,
    LIFTED_F4BD950_STACK = 112,
    LIFTED_F4C6020_STACK = 148,
    LIFTED_F4C6C80_STACK = 200,
    LIFTED_F4CE220_STACK = 104,
    LIFTED_F4CF560_STACK = 112,
    LIFTED_F4DABD0_STACK = 116,
    LIFTED_RTL_READ_INTO_STACK = 384,
    LIFTED_F4E87C1_STACK = 124,
    LIFTED_F4EC68C_STACK = 96
};

/* Original 0x41d6d0. */
uint32_t lifted_f41d6d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x423bc0. */
uint32_t lifted_f423bc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436b40. */
uint32_t lifted_boards_convert_counts(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436d80. */
uint32_t lifted_boards_convert_random(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4375f0. */
uint32_t lifted_f4375f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x437fe0. */
uint32_t lifted_board_spin_marked(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x45ffb0. */
uint32_t lifted_f45ffb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x476160. */
uint32_t lifted_string_table_assign(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x47f1b0. */
uint32_t lifted_f47f1b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480080. */
uint32_t lifted_f480080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488d80. */
uint32_t lifted_object_kind_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4896f0. */
uint32_t lifted_path_split_a(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489760. */
uint32_t lifted_string_append_calls(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b25b0. */
uint32_t lifted_text_wrap(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b42e0. */
uint32_t lifted_f4b42e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4790. */
uint32_t lifted_object_text_insert(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4950. */
uint32_t lifted_object_text_remove(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4af0. */
uint32_t lifted_object_text_rebuild(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6a30. */
uint32_t lifted_f4b6a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bd950. */
uint32_t lifted_f4bd950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c6020. */
uint32_t lifted_f4c6020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c6c80. */
uint32_t lifted_f4c6c80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce220. */
uint32_t lifted_f4ce220(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cf560. */
uint32_t lifted_f4cf560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dabd0. */
uint32_t lifted_f4dabd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db8c0. */
uint32_t lifted_rtl_read_into(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e87c1. */
uint32_t lifted_f4e87c1(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec68c. */
uint32_t lifted_f4ec68c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
