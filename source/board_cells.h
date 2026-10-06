#ifndef VERTRIX_BOARD_CELLS_H
#define VERTRIX_BOARD_CELLS_H
#include "scene.h"
#include <stddef.h>
/* Board marking and column fall routines over the scene storage. Slot handles are only tested
 * for zero; board_value is the original board byte at +0x58. */

/* Original0x42f210: fill the column array at +0x9a1 with the negated board value and fill the
 * 13 cells of cell_b for every column whose slot at +0x988 holds a handle. */
void vertrix_board_mark_columns(VertrixScene *scene, uint8_t board_value);

/* Original0x42f440: fill rows[0] with the board value and, for every row whose slot at +0x9e8
 * holds a handle, store it in that row of all five columns of cell_a. */
void vertrix_board_mark_rows_first(VertrixScene *scene, uint8_t board_value);

/* Original0x42f4b0: as 0x42f440 with rows[2] and the slots at +0xa2c. */
void vertrix_board_mark_rows_second(VertrixScene *scene, uint8_t board_value);

/* Supplied boundary for the virtual destructor (vtable slot 0) the original calls with flag 2. */
typedef void (*VertrixBoardDestroy)(uint32_t object, uint32_t flag, void *context);

/* Original0x42f760: for each of the five columns of the grid at +0x220, destroy and clear the
 * bottom slot when it holds an object, then move every slot down one row and empty the top slot.
 * Columns are processed in order, so destruction events precede later columns. */
void vertrix_board_drop_columns(VertrixScene *scene, VertrixBoardDestroy destroy, void *context);

/* Supplied boundary resolving an object handle to its storage. Returns zero when unknown. */
typedef int (*VertrixObjectStorage)(uint32_t handle, void **storage, size_t *size, void *context);

/* Destroy (flag 2) and clear one slot when it holds an object; the shared body of the release
 * routines below. */
void vertrix_board_release_slot(uint32_t *slot, VertrixBoardDestroy destroy, void *context);

/* Original0x42eb60: destroy the active piece (virtual destructor, flag 2) and clear its slot. */
void vertrix_board_release_active(VertrixScene *scene, VertrixBoardDestroy destroy, void *context);

/* Original0x430150: the same for the extra object at +0xce0. */
void vertrix_board_release_extra(VertrixScene *scene, VertrixBoardDestroy destroy, void *context);

/* Original0x42ee20: when a piece is active, for each of its three child handles at piece +0x15c
 * that is set: period 5 steps, byte +0x4e = 0x64, counter cleared and handler 0x44c960.
 * Returns zero for unresolvable objects, preserving everything already changed. */
int vertrix_board_ready_previews(const VertrixScene *scene, VertrixObjectStorage resolve,
                                 void *context);

/* Original0x42ee80: for every set slot of the grid at +0x220, in column order, set its period
 * to steps*12 and clear its counter. Returns zero for an unresolvable object. */
int vertrix_board_restart_slots(const VertrixScene *scene, uint32_t steps,
                                VertrixObjectStorage resolve, void *context);

/* Original0x4300b0 (lower = 0) and 0x430100 (lower = 1): position the extra object. Its word
 * +0x18 becomes board_y + 0x108 (or +0x138), word +0x1a becomes table_word (the entry of the
 * word table at 0x4f7d08 selected by the dword at 0x532bbc, read at the boundary) and its
 * handler becomes 0x44c880 (or 0x44c8e0). Short extra storage is preserved. */
int vertrix_board_place_extra(void *extra, size_t size, uint16_t board_y, uint16_t table_word,
                              int lower);
/* Original0x432200: destroy and clear every slot of the grid at +0x220 whose object has type
 * byte +0x15d equal to 2, in column order. Returns zero for an unresolvable object. */
int vertrix_board_purge_type_two(VertrixScene *scene, VertrixObjectStorage resolve,
                                 VertrixBoardDestroy destroy, void *context);

/* Original0x432280 / 0x4322f0 / 0x4334b0: report whether any object of the grid at +0x220
 * (type byte +0x15d equal to 1, then byte +0x15c equal to 6) or of the collection at +0x324
 * (type byte +0x15d equal to 1) matches. Scans stop at the first match. Returns -1 for an
 * unresolvable object reached before a match. */
int vertrix_board_has_type_one(const VertrixScene *scene, VertrixObjectStorage resolve,
                               void *context);
int vertrix_board_has_kind_six(const VertrixScene *scene, VertrixObjectStorage resolve,
                               void *context);
int vertrix_board_has_type_one_extra(const VertrixScene *scene, VertrixObjectStorage resolve,
                                     void *context);

/* Original0x432ba0: swap grid_a[col_a][row_a] with grid_b[col_b][row_b] in 13-entry columns.
 * Columns must be 0..4 and rows 0..12; other values return zero without swapping. */
int vertrix_board_swap_slots(uint32_t *grid_a, uint32_t col_a, uint32_t row_a, uint32_t *grid_b,
                             uint32_t col_b, uint32_t row_b);
/* Original0x42ff10: give an actor the board's clip rectangle. Actor byte +0x8e becomes 3 and its
 * limit words +0xa8, +0xaa, +0xac, +0xae become x, x + 0x77, y and y + 0x137, where x and y are the
 * signed words at board +0x0e and +0x16. Short or null storage is preserved and returns zero. */
int vertrix_board_set_actor_clip(const void *board, size_t board_size, void *actor,
                                 size_t actor_size);
#endif
