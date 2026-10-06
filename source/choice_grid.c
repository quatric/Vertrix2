#include "choice_grid.h"
#include "actor_fields.h"
#include "object_access.h"

enum
{
    ENABLED = 1,
    PICK_FIRST_ROW = 1,
    PICK_END_ROW = 4,
    SHUFFLE_PASSES = 10,
    ENABLED_POWER = 0x64,
    FIELD_POWER = 0x4e,
    FIELD_FLAG = 0x93,
    FIELD_STATE = 0x15c,
    FIELD_MARK = 0x15d,
    CELL_HANDLER = 0x456ca0
};

static int cell_index(uint32_t row, uint32_t column)
{
    uint32_t index = row * VERTRIX_CHOICE_COLUMNS + column;
    if (index >= VERTRIX_CHOICE_CELLS)
    {
        return -1;
    }
    return (int)index;
}

static int set_cell_fields(uint32_t handle, uint32_t value, VertrixObjectStorage resolve,
                           void *context)
{
    int enabled = value == ENABLED;
    int ok =
        vertrix_object_write(handle, resolve, context, FIELD_POWER, 1, enabled ? ENABLED_POWER : 0);
    ok = ok && vertrix_object_write(handle, resolve, context, FIELD_FLAG, 1, enabled ? 0 : 1);
    return ok && vertrix_object_write(handle, resolve, context, FIELD_STATE, 1, enabled ? 0 : 1);
}

int vertrix_choice_grid_apply(const VertrixChoiceGrid *grid, VertrixObjectStorage resolve,
                              void *context)
{
    for (int i = 0; i < VERTRIX_CHOICE_CELLS; ++i)
    {
        void *storage;
        size_t size;
        if (grid->cells[i] == 0)
        {
            continue;
        }
        if (!set_cell_fields(grid->cells[i], grid->values[i], resolve, context) ||
            !vertrix_object_write(grid->cells[i], resolve, context, FIELD_MARK, 1, 0) ||
            !resolve(grid->cells[i], &storage, &size, context) ||
            !vertrix_actor_set_handler(storage, size, CELL_HANDLER))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_choice_grid_load_values(VertrixChoiceGrid *grid, const uint32_t *source,
                                    VertrixObjectStorage resolve, void *context)
{
    for (int i = 0; i < VERTRIX_CHOICE_CELLS; ++i)
    {
        grid->values[i] = source[i];
        if (grid->cells[i] == 0)
        {
            continue;
        }
        if (!vertrix_object_write(grid->cells[i], resolve, context, FIELD_STATE, 1,
                                  source[i] == ENABLED ? 0 : 1))
        {
            return 0;
        }
    }
    return 1;
}

void vertrix_choice_grid_store_values(const VertrixChoiceGrid *grid, uint32_t *destination,
                                      uint32_t start)
{
    for (int i = 0; i < VERTRIX_CHOICE_CELLS; ++i)
    {
        destination[start + (uint32_t)i] = grid->values[i];
    }
}

/* Ten passes swapping each list position with a drawn position (0x429f4f and 0x42a0be). */
static void shuffle(uint8_t *list, uint32_t count, VertrixChoiceDraw draw, void *context)
{
    for (int pass = 0; pass < SHUFFLE_PASSES; ++pass)
    {
        for (uint32_t i = 0; i < count; ++i)
        {
            uint32_t other = draw((uint16_t)count, context);
            uint8_t kept = list[other];
            list[other] = list[i];
            list[i] = kept;
        }
    }
}

int vertrix_choice_grid_pick_rows(const VertrixChoiceGrid *grid, uint8_t limit, uint32_t *rows,
                                  VertrixChoiceDraw draw, void *context)
{
    uint8_t list[VERTRIX_CHOICE_ROWS];
    uint32_t count = 0;
    for (int i = 0; i < VERTRIX_CHOICE_ROWS; ++i)
    {
        rows[i] = UINT32_MAX;
    }
    for (uint32_t row = 0; row < VERTRIX_CHOICE_ROWS; ++row)
    {
        uint32_t enabled = 0;
        for (uint32_t column = 0; column < VERTRIX_CHOICE_COLUMNS; ++column)
        {
            if (grid->values[row * VERTRIX_CHOICE_COLUMNS + column] == ENABLED)
            {
                enabled += ENABLED;
            }
        }
        if (enabled > 0)
        {
            list[count++] = (uint8_t)row;
        }
    }
    if (count == 0)
    {
        return 0;
    }
    if (count > 1)
    {
        shuffle(list, count, draw, context);
    }
    uint32_t taken = limit < count ? limit : count;
    for (uint32_t i = 0; i < taken; ++i)
    {
        rows[i] = list[i];
    }
    return 1;
}

int vertrix_choice_grid_pick_column(const VertrixChoiceGrid *grid, uint8_t row, uint8_t *column_out,
                                    VertrixChoiceDraw draw, void *context)
{
    uint8_t list[VERTRIX_CHOICE_COLUMNS];
    uint32_t count = 0;
    for (uint32_t column = 0; column < VERTRIX_CHOICE_COLUMNS; ++column)
    {
        if (grid->values[(uint32_t)row * VERTRIX_CHOICE_COLUMNS + column] == ENABLED)
        {
            list[count++] = (uint8_t)column;
        }
    }
    if (count == 0)
    {
        return 0;
    }
    shuffle(list, count, draw, context);
    *column_out = list[draw((uint16_t)count, context)];
    return 1;
}

int vertrix_choice_grid_pick_cell(const VertrixChoiceGrid *grid, uint8_t *row_out,
                                  uint8_t *column_out, VertrixChoiceDraw draw, void *context)
{
    uint8_t rows[VERTRIX_CHOICE_ROWS];
    uint32_t count = 0;
    for (uint32_t row = PICK_FIRST_ROW; row < PICK_END_ROW; ++row)
    {
        for (uint32_t column = 0; column < VERTRIX_CHOICE_COLUMNS; ++column)
        {
            if (grid->values[row * VERTRIX_CHOICE_COLUMNS + column] == ENABLED)
            {
                rows[count++] = (uint8_t)row;
                break;
            }
        }
    }
    if (count == 0)
    {
        return 0;
    }
    *row_out = rows[draw((uint16_t)count, context)];
    return vertrix_choice_grid_pick_column(grid, *row_out, column_out, draw, context);
}

int vertrix_choice_grid_mark(const VertrixChoiceGrid *grid, uint32_t row, uint32_t column,
                             VertrixObjectStorage resolve, void *context)
{
    int index = cell_index(row, column);
    uint32_t state;
    if (index < 0 || grid->cells[index] == 0 ||
        !vertrix_object_read(grid->cells[index], resolve, context, FIELD_STATE, 1, &state) ||
        state != 0)
    {
        return 0;
    }
    return vertrix_object_write(grid->cells[index], resolve, context, FIELD_MARK, 1, 1);
}

int vertrix_choice_grid_available(const VertrixChoiceGrid *grid, uint32_t row, uint32_t column,
                                  VertrixObjectStorage resolve, void *context)
{
    int index = cell_index(row, column);
    uint32_t state;
    if (index < 0 || grid->cells[index] == 0 ||
        !vertrix_object_read(grid->cells[index], resolve, context, FIELD_STATE, 1, &state))
    {
        return 0;
    }
    return state == 0;
}

int vertrix_choice_grid_any_marked(const VertrixChoiceGrid *grid, VertrixObjectStorage resolve,
                                   void *context)
{
    for (int i = 0; i < VERTRIX_CHOICE_CELLS; ++i)
    {
        uint32_t mark;
        if (grid->cells[i] != 0 &&
            vertrix_object_read(grid->cells[i], resolve, context, FIELD_MARK, 1, &mark) &&
            mark == 1)
        {
            return 1;
        }
    }
    return 0;
}

void vertrix_choice_grid_cell_bytes(const VertrixChoiceGrid *grid, uint32_t row, uint32_t column,
                                    uint8_t *first, uint8_t *second)
{
    int index = cell_index(row, column);
    if (index < 0)
    {
        return;
    }
    *first = grid->first_bytes[index];
    *second = grid->second_bytes[index];
}
