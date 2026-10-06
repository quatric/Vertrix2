#ifndef VERTRIX_TABLE_QUERIES_H
#define VERTRIX_TABLE_QUERIES_H
#include <stddef.h>
#include <stdint.h>
/* Small queries over the game's static and session tables. Table contents are supplied by the
 * caller as the original table bytes; the original reads them from fixed global addresses. */

enum
{
    VERTRIX_NO_MATCH = -1,
    VERTRIX_PAIR_ROW_SIZE = 28,
    VERTRIX_GRID_ROW_SIZE = 22,
    VERTRIX_SLOT_COLUMNS = 19,
    VERTRIX_FLAG_ROW_SIZE = 13,
    VERTRIX_LEVEL_STEPS = 96,
    VERTRIX_FILLED_SLOTS = 19,
    VERTRIX_BONUS_CAP = 99999999
};

/* Original0x417930: the entries at row * 28 + column of two byte tables (0x4f9320, 0x4f9538).
 * Row and column are bytes. */
void vertrix_table_byte_pair(const uint8_t *first, const uint8_t *second, uint8_t row,
                             uint8_t column, uint8_t *first_out, uint8_t *second_out);

/* Original0x417cf0, 0x417d10, 0x417d40 and 0x417d70: dword at row * 22 + column of the table at
 * 0x533e1c. The last three add the dword at 0x4f8ce0, 0x4f8ce4 and 0x4f8ce8 to row * 22 and
 * pass it as the column; callers supply that value. */
uint32_t vertrix_table_grid_value(const uint32_t *grid, uint32_t row, uint32_t column);

/* Original0x417df0: 1 when any of the 13 bytes of the row (table 0x4f9ad8) is nonzero. */
uint32_t vertrix_table_row_used(const uint8_t *flags, uint32_t row);

/* Original0x417e20: threshold bonus. The step count is zero when value is not below limit
 * (dword 0x532b34), else limit - value; multiplied by the dword 0x4f80d8[level] (level is the
 * dword 0x532bbc), added to base, increased by half (rounded down) and capped at 99999999. All
 * arithmetic is 32-bit. */
uint32_t vertrix_table_bonus(uint32_t base, uint32_t value, uint32_t limit,
                             const uint32_t *multipliers, uint32_t level);

/* Original0x417fc0: number of the first count[column] rows whose dword in the column equals
 * value. The grid (0x534c18) has 19 dwords per row; counts are at 0x534f10. */
uint32_t vertrix_table_column_count(const uint32_t *grid, const uint32_t *counts, uint32_t column,
                                    uint32_t value);

/* Original0x418000: row index of the n-th (from zero) of those matching rows, or 0. */
uint32_t vertrix_table_column_nth(const uint32_t *grid, const uint32_t *counts, uint32_t column,
                                  uint32_t value, uint32_t n);

/* Original0x417840: with n at most 254 (larger values never terminate in the original), the
 * result is 1 plus the highest index in 1..n whose dword differs from the one before it in the
 * table at 0x533290, or 1 plus zero when none does. Returned as a byte. */
uint8_t vertrix_table_last_change(const uint32_t *table, uint32_t n);

/* Original0x40f170: 1 plus the first of the 96 words (table 0x4f74d4) not above value; zero for
 * a zero value or when none qualifies. */
uint32_t vertrix_table_level_for(const uint16_t *steps, uint32_t value);

/* Original0x415c00 (table 0x5344a4) and 0x415c30 (0x5344f0): 1 when all 19 dwords are nonzero. */
uint32_t vertrix_table_all_filled(const uint32_t *slots);

/* Supplied boundary for the comparison 0x4ccfe0; zero means equal. */
typedef int (*VertrixCompare)(uint32_t item, uint32_t key, void *context);

/* Original0x415e40: index of the last item for which compare(item, key) is zero, or -1. Every
 * item is compared, in order. */
int32_t vertrix_table_find_matching(const uint32_t *items, uint32_t count, uint32_t key,
                                    VertrixCompare compare, void *context);

/* Original0x415e80: index of the last item equal to key, or -1. */
int32_t vertrix_table_find_equal(const uint32_t *items, uint32_t count, uint32_t key);

/* Original0x415eb0: values[index] for the index found by vertrix_table_find_matching, or 0. */
uint32_t vertrix_table_value_matching(const uint32_t *items, const uint32_t *values, uint32_t count,
                                      uint32_t key, VertrixCompare compare, void *context);

/* Original0x415ed0: values[index] for the index found by vertrix_table_find_equal, or 0. */
uint32_t vertrix_table_value_equal(const uint32_t *items, const uint32_t *values, uint32_t count,
                                   uint32_t key);

enum
{
    VERTRIX_PAIR_TABLE_ROW = 20,
    VERTRIX_PAIR_MODE_LAST = 5,
    VERTRIX_LINK_ROW_SIZE = 8,
    VERTRIX_GROUP_ROW_SIZE = 30,
    VERTRIX_GROUP_SIZE = 5,
    VERTRIX_GROUPS = 6,
    VERTRIX_OPEN_SLOTS = VERTRIX_FILLED_SLOTS
};

/* Original0x4153e0: copy a pair of dwords of the 14 row, 20 column table at 0x5336ac. The
 * pair is rows 2m and 2m+1 of the column for modes m below 5, rows 10 and 11 for mode 6 and rows
 * 12 and 13 for mode 5. Returns 0 and leaves the outputs for other modes. */
int vertrix_table_pair_select(const uint32_t *table, uint32_t column, uint32_t mode,
                              uint32_t *first, uint32_t *second);

/* Original0x417970: with the byte tables of 0x417930, 0xffffffff when either entry at
 * row * 28 + column is zero, else the byte of the table at 0x4f90f7 indexed first * 8 + second. */
uint32_t vertrix_table_pair_link(const uint8_t *first, const uint8_t *second, const uint8_t *links,
                                 uint8_t row, uint8_t column);

/* Original0x417da0: of the six groups of five bytes in the row (30 bytes, table 0x4f9800), the
 * number holding any nonzero byte. */
uint32_t vertrix_table_groups_used(const uint8_t *flags, uint32_t row);

/* Supplied boundary for the shared draw 0x4826c0: a value below limit (only the low 16 bits are
 * used). */
typedef uint32_t (*VertrixDraw)(uint32_t limit, void *context);

/* Original0x417e60 (table 0x5344a4) and 0x417ed0 (0x5344f0): draw one of the indices of the
 * zero dwords of the 19, or 0 without drawing when none is zero. The original reads stale stack
 * data for a draw at or above the number of zero dwords; that case returns 0 here. */
uint32_t vertrix_table_random_empty(const uint32_t *slots, VertrixDraw draw, void *context);

/* Original0x418050: number of the first count[column] rows whose dword in the column is 0, 3, 4
 * or 5. */
uint32_t vertrix_table_column_open(const uint32_t *grid, const uint32_t *counts, uint32_t column);

/* Original0x4180a0: row index of the n-th (from zero) such row, or 0. */
uint32_t vertrix_table_column_open_nth(const uint32_t *grid, const uint32_t *counts,
                                       uint32_t column, uint32_t n);
#endif
