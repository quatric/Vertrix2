#ifndef VERTRIX_CHOICE_GRID_H
#define VERTRIX_CHOICE_GRID_H
#include "board_cells.h"
/* Choice grid: seven rows of four cells at object +0x15c (object handles), a parallel table of
 * dword values at +0x1cc (1 marks an enabled cell) and two byte tables at +0x23c and +0x258.
 * Cells are indexed row * 4 + column. */
#define VERTRIX_CHOICE_ROWS 7
#define VERTRIX_CHOICE_COLUMNS 4
#define VERTRIX_CHOICE_CELLS 28

typedef struct
{
    uint32_t cells[VERTRIX_CHOICE_CELLS];
    uint32_t values[VERTRIX_CHOICE_CELLS];
    uint8_t first_bytes[VERTRIX_CHOICE_CELLS];
    uint8_t second_bytes[VERTRIX_CHOICE_CELLS];
} VertrixChoiceGrid;

/* Supplied boundary for the original random draw 0x4826c0 (a value below divisor). */
typedef uint16_t (*VertrixChoiceDraw)(uint16_t divisor, void *context);

/* Original0x429d50: for every cell holding an object, set its fields from the cell value: value 1
 * gives byte +0x4e = 0x64, +0x93 = 0, +0x15c = 0; any other value gives 0, 1, 1. Then clear
 * +0x15d and set handler 0x456ca0. Returns zero for an unresolvable object. */
int vertrix_choice_grid_apply(const VertrixChoiceGrid *grid, VertrixObjectStorage resolve,
                              void *context);

/* Original0x429df0: copy 28 values from source, and for every cell holding an object set its byte
 * +0x15c to 0 for value 1, else 1. Returns zero for an unresolvable object. */
int vertrix_choice_grid_load_values(VertrixChoiceGrid *grid, const uint32_t *source,
                                    VertrixObjectStorage resolve, void *context);

/* Original0x429e80: store the 28 values at destination[start .. start + 27]. */
void vertrix_choice_grid_store_values(const VertrixChoiceGrid *grid, uint32_t *destination,
                                      uint32_t start);

/* Original0x429ee0: set 7 outputs to 0xffffffff, list the rows with a value 1, shuffle the list
 * with ten passes of draws and copy the first min(count, limit) rows to the outputs. Returns zero
 * when no row qualifies. */
int vertrix_choice_grid_pick_rows(const VertrixChoiceGrid *grid, uint8_t limit, uint32_t *rows,
                                  VertrixChoiceDraw draw, void *context);

/* Original0x42a080: the same shuffle over the columns of one row holding value 1, then one more
 * draw selects the column stored in column_out. Returns zero when the row has none. */
int vertrix_choice_grid_pick_column(const VertrixChoiceGrid *grid, uint8_t row, uint8_t *column_out,
                                    VertrixChoiceDraw draw, void *context);

/* Original0x429fe0: list the rows 1 to 3 that hold a value 1, draw one of them into row_out and
 * then pick a column of that row as vertrix_choice_grid_pick_column does. Returns zero, leaving
 * row_out untouched, when no row qualifies. */
int vertrix_choice_grid_pick_cell(const VertrixChoiceGrid *grid, uint8_t *row_out,
                                  uint8_t *column_out, VertrixChoiceDraw draw, void *context);

/* Original0x42a140: when the cell holds an object whose byte +0x15c is zero, set its byte +0x15d
 * to 1 and return 1; otherwise 0. */
int vertrix_choice_grid_mark(const VertrixChoiceGrid *grid, uint32_t row, uint32_t column,
                             VertrixObjectStorage resolve, void *context);

/* Original0x42a190: 1 when the cell holds an object whose byte +0x15c is zero, else 0. */
int vertrix_choice_grid_available(const VertrixChoiceGrid *grid, uint32_t row, uint32_t column,
                                  VertrixObjectStorage resolve, void *context);

/* Original0x42a1b0: 1 when any cell holds an object whose byte +0x15d is 1, else 0. */
int vertrix_choice_grid_any_marked(const VertrixChoiceGrid *grid, VertrixObjectStorage resolve,
                                   void *context);

/* Original0x42a170: read both table bytes of one cell. */
void vertrix_choice_grid_cell_bytes(const VertrixChoiceGrid *grid, uint32_t row, uint32_t column,
                                    uint8_t *first, uint8_t *second);
#endif
