#include "board_cells.h"
#include "actor_fields.h"
#include <string.h>

enum
{
    COLUMNS = 5,
    ROWS = 13,
    DESTROY_FLAG = 2,
    PREVIEW_CHILDREN = 3,
    PREVIEW_CHILD_HANDLES = 0x15c,
    PREVIEW_STEPS = 5,
    PREVIEW_HANDLER = 0x44c960,
    ACTOR_POWER = 0x4e,
    FIRST_GRID_SLOTS = 65,
    SECOND_GRID_FIRST = 161,
    SECOND_GRID_SLOTS = 260,
    TYPE_BYTE = 0x15d,
    KIND_BYTE = 0x15c,
    TYPE_PURGED = 2,
    TYPE_SEEKED = 1,
    KIND_SEEKED = 6,
    BOARD_X = 0xe,
    BOARD_Y = 0x16,
    CLIP_KIND = 0x8e,
    CLIP_KIND_ACTOR = 3,
    CLIP_LEFT = 0xa8,
    CLIP_RIGHT = 0xaa,
    CLIP_TOP = 0xac,
    CLIP_BOTTOM = 0xae,
    CLIP_WIDTH = 0x77,
    CLIP_HEIGHT = 0x137,
    EXTRA_Y = 0x18,
    EXTRA_TABLE_WORD = 0x1a,
    EXTRA_UPPER_OFFSET = 0x108,
    EXTRA_LOWER_OFFSET = 0x138,
    EXTRA_UPPER_HANDLER = 0x44c880,
    EXTRA_LOWER_HANDLER = 0x44c8e0,
    POWER_NO_FLAG = 0x64,
    /* Offsets into scene.slots of the collections at +0x988, +0x9e8 and +0xa2c. */
    COLUMN_FLAG_SLOTS = 130,
    ROW_FLAG_SLOTS_FIRST = 135,
    ROW_FLAG_SLOTS_SECOND = 148
};

void vertrix_board_mark_columns(VertrixScene *scene, uint8_t board_value)
{
    uint8_t mark = (uint8_t)-board_value;
    memset(scene->columns_b, mark, sizeof scene->columns_b);
    for (int column = 0; column < COLUMNS; ++column)
    {
        if (scene->slots[COLUMN_FLAG_SLOTS + column] != 0)
        {
            memset(&scene->cell_b[column * ROWS], mark, ROWS);
        }
    }
}

static void mark_rows(VertrixScene *scene, uint8_t row_values[ROWS], int flag_slots,
                      uint8_t board_value)
{
    memset(row_values, board_value, ROWS);
    for (int row = 0; row < ROWS; ++row)
    {
        if (scene->slots[flag_slots + row] == 0)
        {
            continue;
        }
        for (int column = 0; column < COLUMNS; ++column)
        {
            scene->cell_a[column * ROWS + row] = board_value;
        }
    }
}

void vertrix_board_mark_rows_first(VertrixScene *scene, uint8_t board_value)
{
    mark_rows(scene, scene->rows[0], ROW_FLAG_SLOTS_FIRST, board_value);
}

void vertrix_board_mark_rows_second(VertrixScene *scene, uint8_t board_value)
{
    mark_rows(scene, scene->rows[2], ROW_FLAG_SLOTS_SECOND, board_value);
}

void vertrix_board_drop_columns(VertrixScene *scene, VertrixBoardDestroy destroy, void *context)
{
    for (int column = 0; column < COLUMNS; ++column)
    {
        uint32_t *slots = &scene->slots[column * ROWS];
        if (slots[ROWS - 1] != 0)
        {
            destroy(slots[ROWS - 1], DESTROY_FLAG, context);
            slots[ROWS - 1] = 0;
        }
        for (int row = ROWS - 2; row >= 0; --row)
        {
            slots[row + 1] = slots[row];
        }
        slots[0] = 0;
    }
}

void vertrix_board_release_slot(uint32_t *slot, VertrixBoardDestroy destroy, void *context)
{
    if (*slot != 0)
    {
        destroy(*slot, DESTROY_FLAG, context);
        *slot = 0;
    }
}

void vertrix_board_release_active(VertrixScene *scene, VertrixBoardDestroy destroy, void *context)
{
    vertrix_board_release_slot(&scene->active, destroy, context);
}

void vertrix_board_release_extra(VertrixScene *scene, VertrixBoardDestroy destroy, void *context)
{
    vertrix_board_release_slot(&scene->extra, destroy, context);
}

int vertrix_board_ready_previews(const VertrixScene *scene, VertrixObjectStorage resolve,
                                 void *context)
{
    if (scene->active == 0)
    {
        return 1;
    }
    for (int child = 0; child < PREVIEW_CHILDREN; ++child)
    {
        void *piece;
        size_t piece_size;
        uint32_t handle;
        if (!resolve(scene->active, &piece, &piece_size, context) ||
            !vertrix_actor_storage_read(piece, piece_size, PREVIEW_CHILD_HANDLES + 4 * child, 4,
                                        &handle))
        {
            return 0;
        }
        if (handle == 0)
        {
            continue;
        }
        void *storage;
        size_t size;
        if (!resolve(handle, &storage, &size, context) ||
            !vertrix_actor_set_period_steps(storage, size, PREVIEW_STEPS) ||
            !vertrix_actor_storage_write(storage, size, ACTOR_POWER, 1, POWER_NO_FLAG) ||
            !vertrix_actor_clear_counter(storage, size) ||
            !vertrix_actor_set_handler(storage, size, PREVIEW_HANDLER))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_board_restart_slots(const VertrixScene *scene, uint32_t steps,
                                VertrixObjectStorage resolve, void *context)
{
    for (int slot = 0; slot < COLUMNS * ROWS; ++slot)
    {
        if (scene->slots[slot] == 0)
        {
            continue;
        }
        void *storage;
        size_t size;
        if (!resolve(scene->slots[slot], &storage, &size, context) ||
            !vertrix_actor_set_period_steps(storage, size, steps) ||
            !vertrix_actor_clear_counter(storage, size))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_board_place_extra(void *extra, size_t size, uint16_t board_y, uint16_t table_word,
                              int lower)
{
    uint32_t offset = lower ? EXTRA_LOWER_OFFSET : EXTRA_UPPER_OFFSET;
    uint32_t handler = lower ? EXTRA_LOWER_HANDLER : EXTRA_UPPER_HANDLER;
    uint8_t copy[0x158];
    if (!extra || size < sizeof(copy))
    {
        return 0;
    }
    memcpy(copy, extra, sizeof(copy));
    if (!vertrix_actor_storage_write(copy, sizeof(copy), EXTRA_Y, 2, board_y + offset) ||
        !vertrix_actor_storage_write(copy, sizeof(copy), EXTRA_TABLE_WORD, 2, table_word) ||
        !vertrix_actor_set_handler(copy, sizeof(copy), handler))
    {
        return 0;
    }
    memcpy(extra, copy, sizeof(copy));
    return 1;
}

/* Reads one byte of an object; returns 0 when the object cannot be resolved. */
static int object_byte(uint32_t handle, size_t offset, VertrixObjectStorage resolve, void *context,
                       uint32_t *value)
{
    void *storage;
    size_t size;
    return resolve(handle, &storage, &size, context) &&
           vertrix_actor_storage_read(storage, size, offset, 1, value);
}

int vertrix_board_purge_type_two(VertrixScene *scene, VertrixObjectStorage resolve,
                                 VertrixBoardDestroy destroy, void *context)
{
    for (int slot = 0; slot < FIRST_GRID_SLOTS; ++slot)
    {
        uint32_t type;
        if (scene->slots[slot] == 0)
        {
            continue;
        }
        if (!object_byte(scene->slots[slot], TYPE_BYTE, resolve, context, &type))
        {
            return 0;
        }
        if (type == TYPE_PURGED)
        {
            vertrix_board_release_slot(&scene->slots[slot], destroy, context);
        }
    }
    return 1;
}

static int has_byte(const VertrixScene *scene, int first, int count, size_t offset, uint32_t wanted,
                    VertrixObjectStorage resolve, void *context)
{
    for (int slot = first; slot < first + count; ++slot)
    {
        uint32_t value;
        if (scene->slots[slot] == 0)
        {
            continue;
        }
        if (!object_byte(scene->slots[slot], offset, resolve, context, &value))
        {
            return -1;
        }
        if (value == wanted)
        {
            return 1;
        }
    }
    return 0;
}

int vertrix_board_has_type_one(const VertrixScene *scene, VertrixObjectStorage resolve,
                               void *context)
{
    return has_byte(scene, 0, FIRST_GRID_SLOTS, TYPE_BYTE, TYPE_SEEKED, resolve, context);
}

int vertrix_board_has_kind_six(const VertrixScene *scene, VertrixObjectStorage resolve,
                               void *context)
{
    return has_byte(scene, 0, FIRST_GRID_SLOTS, KIND_BYTE, KIND_SEEKED, resolve, context);
}

int vertrix_board_has_type_one_extra(const VertrixScene *scene, VertrixObjectStorage resolve,
                                     void *context)
{
    return has_byte(scene, SECOND_GRID_FIRST, SECOND_GRID_SLOTS, TYPE_BYTE, TYPE_SEEKED, resolve,
                    context);
}

int vertrix_board_swap_slots(uint32_t *grid_a, uint32_t col_a, uint32_t row_a, uint32_t *grid_b,
                             uint32_t col_b, uint32_t row_b)
{
    if (!grid_a || !grid_b || col_a >= COLUMNS || col_b >= COLUMNS || row_a >= ROWS ||
        row_b >= ROWS)
    {
        return 0;
    }
    uint32_t *a = &grid_a[col_a * ROWS + row_a];
    uint32_t *b = &grid_b[col_b * ROWS + row_b];
    uint32_t held = *b;
    *b = *a;
    *a = held;
    return 1;
}

int vertrix_board_set_actor_clip(const void *board, size_t board_size, void *actor,
                                 size_t actor_size)
{
    uint32_t x, y;
    uint8_t copy[VERTRIX_ACTOR_BASE_SIZE];
    if (!actor || actor_size < sizeof(copy) ||
        !vertrix_actor_storage_read(board, board_size, BOARD_X, 2, &x) ||
        !vertrix_actor_storage_read(board, board_size, BOARD_Y, 2, &y))
    {
        return 0;
    }
    memcpy(copy, actor, sizeof(copy));
    int32_t left = (int16_t)x;
    int32_t top = (int16_t)y;
    if (!vertrix_actor_storage_write(copy, sizeof(copy), CLIP_KIND, 1, CLIP_KIND_ACTOR) ||
        !vertrix_actor_storage_write(copy, sizeof(copy), CLIP_LEFT, 2, (uint32_t)left) ||
        !vertrix_actor_storage_write(copy, sizeof(copy), CLIP_RIGHT, 2,
                                     (uint32_t)(left + CLIP_WIDTH)) ||
        !vertrix_actor_storage_write(copy, sizeof(copy), CLIP_TOP, 2, (uint32_t)top) ||
        !vertrix_actor_storage_write(copy, sizeof(copy), CLIP_BOTTOM, 2,
                                     (uint32_t)(top + CLIP_HEIGHT)))
    {
        return 0;
    }
    memcpy(actor, copy, sizeof(copy));
    return 1;
}
