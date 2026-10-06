#ifndef VERTRIX_BOARD_MARKERS_H
#define VERTRIX_BOARD_MARKERS_H
#include "board_cells.h"
#include "random.h"
/* Block kind snapshot and marker grids. Both are 5 columns of 13 bytes at board +0x1de (kinds,
 * 0xff = empty, 5 = stone, 6 = bomb) and +0xb94 (markers). */
#define VERTRIX_MARKER_CELLS 65

/* Original0x4327e0: kinds[i] is 0xff for an empty slot, else the kind byte +0x15c of the slot's
 * object. Returns zero for an unresolvable object. */
int vertrix_board_snapshot_kinds(const uint32_t *slots, uint32_t count,
                                 VertrixObjectStorage resolve, void *context, uint8_t *kinds);

/* Original0x432840: clear 65 mask dwords. */
void vertrix_board_clear_mask(uint32_t mask[VERTRIX_MARKER_CELLS]);

/* Original0x435e80 after its snapshot: marker 1 where the kind is selectable for mode (all
 * non-empty kinds for mode 2; everything but stones for mode 1; ordinary kinds, excluding
 * stones and bombs, for mode 0; none for other modes), else 0. */
void vertrix_board_markers_for_mode(const uint8_t kinds[VERTRIX_MARKER_CELLS], uint32_t mode,
                                    uint8_t markers[VERTRIX_MARKER_CELLS]);

/* Original0x435f30 after its snapshot: clear the markers, then mark the first occupied cell of
 * every column when it is not a stone. */
void vertrix_board_markers_top(const uint8_t kinds[VERTRIX_MARKER_CELLS],
                               uint8_t markers[VERTRIX_MARKER_CELLS]);

/* Original0x436030 (kind 1) and 0x436070 (kind 2): number of markers equal to kind. */
uint32_t vertrix_board_marker_count(const uint8_t markers[VERTRIX_MARKER_CELLS], uint8_t kind);

/* Original0x435fe0 (column order, kind 1), 0x4360b0 (row order, kind 1) and 0x436100 (row order,
 * kind 2): column and row of the n-th marker equal to kind (n counted from zero). Returns 1 when
 * found, leaving the outputs untouched otherwise. */
int vertrix_board_marker_nth_by_column(const uint8_t markers[VERTRIX_MARKER_CELLS], uint8_t kind,
                                       uint32_t n, uint32_t *column, uint32_t *row);
int vertrix_board_marker_nth_by_row(const uint8_t markers[VERTRIX_MARKER_CELLS], uint8_t kind,
                                    uint32_t n, uint32_t *column, uint32_t *row);

/* Original0x436850 (stones excluded) and 0x4372c0 (stones included), after their snapshots:
 * marker 1 for every even cell index (column-major, 13 per column) holding a block, else 0. */
void vertrix_board_markers_checker(const uint8_t kinds[VERTRIX_MARKER_CELLS], int include_stones,
                                   uint8_t markers[VERTRIX_MARKER_CELLS]);

/* Original0x436fe0 and 0x437240 (identical), after their snapshots: marker 1 for stones. */
void vertrix_board_markers_stones(const uint8_t kinds[VERTRIX_MARKER_CELLS],
                                  uint8_t markers[VERTRIX_MARKER_CELLS]);

/* Original0x436a10 after its snapshot: marker 1 where the kind, as a signed byte, equals wanted.
 * Returns the number of markers set (the original stores it through its pointer). */
uint32_t vertrix_board_markers_kind(const uint8_t kinds[VERTRIX_MARKER_CELLS], uint32_t wanted,
                                    uint8_t markers[VERTRIX_MARKER_CELLS]);

/* Original0x436aa0 after its snapshot: stones and empty cells are never marked; bombs are marked
 * for mode 5; other kinds for modes 5 and 6. */
void vertrix_board_markers_for_power(const uint8_t kinds[VERTRIX_MARKER_CELLS], uint32_t mode,
                                     uint8_t markers[VERTRIX_MARKER_CELLS]);
/* Original0x438830 (kind 1) and 0x4388a0 (kind 2): searching one column from its bottom row up,
 * find the n-th (from zero) marker equal to kind. Returns 1 and stores the column and row, or 0
 * leaving the outputs untouched. */
int vertrix_board_marker_in_column(const uint8_t markers[VERTRIX_MARKER_CELLS], uint8_t kind,
                                   uint32_t column, uint32_t n, uint32_t *found_column,
                                   uint32_t *found_row);

/* Original0x438910: 0 without a snapshot when first >= second (signed). Otherwise snapshot the
 * kinds (as 0x4327e0 does into board +0x1de) and report 1 when any column's bottom cell holds a
 * block. Returns zero from the function itself for an unresolvable object. */
int vertrix_board_any_bottom(const uint32_t *slots, int32_t first, int32_t second,
                             VertrixObjectStorage resolve, void *context,
                             uint8_t kinds[VERTRIX_MARKER_CELLS], uint32_t *occupied);
/* Original0x438d50: like 0x438910 but reports 1 when any cell holds a block. */
int vertrix_board_any_block(const uint32_t *slots, int32_t first, int32_t second,
                            VertrixObjectStorage resolve, void *context,
                            uint8_t kinds[VERTRIX_MARKER_CELLS], uint32_t *occupied);
/* Original0x439370 after its snapshot: marker 1 where the kind, as a sign-extended byte (empty
 * cells are -1), equals wanted. */
void vertrix_board_markers_equal(const uint8_t kinds[VERTRIX_MARKER_CELLS], int32_t wanted,
                                 uint8_t markers[VERTRIX_MARKER_CELLS]);

/* Original0x4375a0: snapshot the kinds of the 65 slots (as 0x4327e0) and set marker 1 for every
 * cell whose kind is not empty, 0 otherwise. Returns zero for an unresolvable object. */
int vertrix_board_mark_filled(const uint32_t slots[VERTRIX_MARKER_CELLS],
                              VertrixObjectStorage resolve, void *context,
                              uint8_t kinds[VERTRIX_MARKER_CELLS],
                              uint8_t markers[VERTRIX_MARKER_CELLS]);

/* Original0x4383f0: snapshot the kinds (as 0x4327e0) and set marker 0 for empty cells, 1 for stones
 * (kind 5) and 2 for every other kind. Returns zero for an unresolvable object. */
int vertrix_board_mark_stones(const uint32_t slots[VERTRIX_MARKER_CELLS],
                              VertrixObjectStorage resolve, void *context,
                              uint8_t kinds[VERTRIX_MARKER_CELLS],
                              uint8_t markers[VERTRIX_MARKER_CELLS]);

/* Original0x437f60: as 0x4383f0 but bombs (kind 6) get marker 0 too: 0 for empty cells and bombs, 1
 * for stones (kind 5) and 2 for every other kind. */
int vertrix_board_mark_stones_not_bombs(const uint32_t slots[VERTRIX_MARKER_CELLS],
                                        VertrixObjectStorage resolve, void *context,
                                        uint8_t kinds[VERTRIX_MARKER_CELLS],
                                        uint8_t markers[VERTRIX_MARKER_CELLS]);

/* Original0x4328a0: snapshot the kinds (as 0x4327e0) and report whether any block would fall, using
 * the falling-mask test 0x4328e0. Returns zero for an unresolvable object. */
int vertrix_board_any_falling(const uint32_t slots[VERTRIX_MARKER_CELLS],
                              VertrixObjectStorage resolve, void *context,
                              uint8_t kinds[VERTRIX_MARKER_CELLS], uint32_t *falling);

/* Original0x432b10: snapshot the kinds as 0x4328a0 does and, when any block would fall, store the
 * board value in the cell array (65 bytes at board +0x19d) for every cell the falling mask flags.
 * Returns zero for an unresolvable object. */
int vertrix_board_mark_falling_cells(const uint32_t slots[VERTRIX_MARKER_CELLS],
                                     VertrixObjectStorage resolve, void *context,
                                     uint8_t kinds[VERTRIX_MARKER_CELLS], uint8_t board_value,
                                     uint8_t cells[VERTRIX_MARKER_CELLS]);

/* Original0x437b70: consume one draw below 48 per row (13 draws, all discarded)
 * and stamp dword +0x68 = 0x30 on every nonzero companion in the +0x87c grid
 * (rows of 4-byte handles, columns every 0x34 bytes up to +0x104). Returns
 * zero for short storage or an unresolvable companion. */
int vertrix_board_stamp_companions(void *board, size_t board_size, VertrixRandom *random,
                                   VertrixObjectStorage resolve, void *context);
#endif
