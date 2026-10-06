#include "board_actions.h"
#include "actor_fields.h"
#include "actor_storage.h"
#include "board_markers.h"
#include "object_access.h"
#include <string.h>

enum
{
    COLUMNS = 5,
    ROWS = 13,
    CELL_COUNT = COLUMNS * ROWS,
    COLUMN_STRIDE = 0x34,
    GRID_BLOCKS = 0x220,
    GRID_COMPANIONS = 0x87c,
    MARKERS = 0xb94,
    BOARD_X = 0xe,
    BOARD_Y = 0x16,
    BOARD_PIECE = 0xa60,
    PIECE_X = 0xe,
    PIECE_Y = 0x16,
    PIECE_HEIGHT = 0x47,
    CELL_SIZE = 24,
    MARKER_PENDING = 1,
    MARKER_STARTED = 2,
    START_COMPANION_HANDLER = 0x44e790,
    START_BLOCK_HANDLER = 0x44e800,
    FLAG_BLOCK_HANDLER = 0x44d9d0,
    FLAG_COMPANION_HANDLER = 0x44dbb0,
    SLIDE_X_TARGET = 0x10,
    SLIDE_Y_TARGET = 0x18,
    SLIDE_X_SAVED = 8,
    SLIDE_Y_SAVED = 0xa,
    ACTOR_X = 0xe,
    ACTOR_Y = 0x16,
    SLIDE_DOWN_HANDLER = 0x44e920,
    SLIDE_UP_HANDLER = 0x44ebe0,
    SLIDE_STORAGE = 0x158,
    SLIDE_DOWN_BYTE_44 = 0x44,
    SLIDE_DOWN_BYTE_45 = 0x45,
    SLIDE_DOWN_WORD_46 = 0x46,
    SLIDE_DOWN_WORD_48 = 0x48,
    SLIDE_STEPS = 4,
    SLIDE_WORD_12 = 0x12,
    SLIDE_WORD_1A = 0x1a,
    SLIDE_UP_DWORD_58 = 0x58,
    SLIDE_UP_DWORD_5C = 0x5c,
    SLIDE_UP_DWORD_60 = 0x60,
    FLAG_93 = 0x93,
    POWER_4E = 0x4e,
    FLAG_95 = 0x95,
    STONE_KIND = 5,
    KIND_BYTE = 0x15c,
    STONE_OLD_HANDLER = 0x44cb50,
    STONE_NEW_HANDLER = 0x44cab0,
    STONE_STEPS = 5,
    STONE_OLD_POWER = 0x64,
    STONE_OLD_FLAG_95 = 3,
    STONE_NEW_WORD_48 = 0xc8,
    OBJECT_D0 = 0xd0,
    OBJECT_FRAME = 0xb8
};

static size_t cell_offset(size_t grid, uint32_t column, uint32_t row)
{
    return grid + COLUMN_STRIDE * (size_t)column + 4 * (size_t)row;
}

static int object_storage(const VertrixFactoryServices *services, uint32_t handle, void **storage,
                          size_t *size)
{
    return services->resolve(handle, storage, size, services->context);
}

/* Applies a handler to the object a grid cell holds. */
static int set_cell_handler(const void *board, size_t board_size, size_t grid, uint32_t column,
                            uint32_t row, uint32_t handler, const VertrixFactoryServices *services)
{
    uint32_t handle;
    void *storage;
    size_t size;
    return vertrix_actor_storage_read(board, board_size, cell_offset(grid, column, row), 4,
                                      &handle) &&
           object_storage(services, handle, &storage, &size) &&
           vertrix_actor_set_handler(storage, size, handler);
}

int vertrix_board_piece_hits_grid(const void *board, size_t board_size,
                                  const VertrixFactoryServices *services,
                                  const uint32_t other_grid[CELL_COUNT], uint32_t *hit)
{
    uint32_t piece, piece_x, piece_y, board_x, board_y;
    if (!vertrix_actor_storage_read(board, board_size, BOARD_PIECE, 4, &piece) ||
        !vertrix_object_read(piece, services->resolve, services->context, PIECE_X, 2, &piece_x) ||
        !vertrix_object_read(piece, services->resolve, services->context, PIECE_Y, 2, &piece_y) ||
        !vertrix_actor_storage_read(board, board_size, BOARD_X, 2, &board_x) ||
        !vertrix_actor_storage_read(board, board_size, BOARD_Y, 2, &board_y))
    {
        return 0;
    }
    int32_t column = ((int32_t)(int16_t)piece_x - (int16_t)board_x) / CELL_SIZE;
    int32_t top = ((int32_t)(int16_t)piece_y - (int16_t)board_y) / CELL_SIZE;
    int32_t bottom = ((int32_t)(int16_t)(piece_y + PIECE_HEIGHT) - (int16_t)board_y) / CELL_SIZE;
    *hit = 0;
    for (int32_t row = top; row <= bottom; ++row)
    {
        if (row < 0)
        {
            continue;
        }
        int64_t index = (int64_t)column * ROWS + row;
        if (index < 0 || index >= CELL_COUNT)
        {
            return 0;
        }
        if (other_grid[index] != 0)
        {
            *hit = 1;
            return 1;
        }
    }
    return 1;
}

int vertrix_board_start_marked(void *board, size_t board_size,
                               const VertrixFactoryServices *services)
{
    uint8_t *markers = (uint8_t *)board + MARKERS;
    if (!board || board_size < MARKERS + CELL_COUNT)
    {
        return 0;
    }
    uint32_t pending = vertrix_board_marker_count(markers, MARKER_PENDING);
    for (uint32_t done = 0; done < pending; ++done)
    {
        uint32_t column, row;
        if (!vertrix_board_marker_nth_by_row(markers, MARKER_PENDING, 0, &column, &row))
        {
            return 0;
        }
        markers[column * ROWS + row] = MARKER_STARTED;
        if (!set_cell_handler(board, board_size, GRID_COMPANIONS, column, row,
                              START_COMPANION_HANDLER, services) ||
            !set_cell_handler(board, board_size, GRID_BLOCKS, column, row, START_BLOCK_HANDLER,
                              services))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_board_flag_marked(const void *board, size_t board_size,
                              const VertrixFactoryServices *services)
{
    const uint8_t *markers = (const uint8_t *)board + MARKERS;
    if (!board || board_size < MARKERS + CELL_COUNT)
    {
        return 0;
    }
    uint32_t pending = vertrix_board_marker_count(markers, MARKER_PENDING);
    for (uint32_t n = 0; n < pending; ++n)
    {
        uint32_t column, row;
        if (!vertrix_board_marker_nth_by_row(markers, MARKER_PENDING, n, &column, &row) ||
            !set_cell_handler(board, board_size, GRID_BLOCKS, column, row, FLAG_BLOCK_HANDLER,
                              services) ||
            !set_cell_handler(board, board_size, GRID_COMPANIONS, column, row,
                              FLAG_COMPANION_HANDLER, services))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_actor_start_slide(const void *board, size_t board_size, void *actor, size_t actor_size,
                              int32_t cells_x, int32_t cells_y)
{
    uint8_t copy[SLIDE_STORAGE];
    uint32_t board_x, board_y, x, y;
    if (!actor || actor_size < sizeof(copy) ||
        !vertrix_actor_storage_read(board, board_size, BOARD_X, 2, &board_x) ||
        !vertrix_actor_storage_read(board, board_size, BOARD_Y, 2, &board_y))
    {
        return 0;
    }
    memcpy(copy, actor, sizeof(copy));
    uint16_t target_x = (uint16_t)(board_x + (uint32_t)cells_x * CELL_SIZE);
    uint16_t target_y = (uint16_t)(board_y + (uint32_t)cells_y * CELL_SIZE);
    vertrix_actor_storage_read(copy, sizeof(copy), ACTOR_X, 2, &x);
    vertrix_actor_storage_read(copy, sizeof(copy), ACTOR_Y, 2, &y);
    vertrix_actor_storage_write(copy, sizeof(copy), SLIDE_X_TARGET, 2, target_x);
    vertrix_actor_storage_write(copy, sizeof(copy), SLIDE_Y_TARGET, 2, target_y);
    vertrix_actor_storage_write(copy, sizeof(copy), SLIDE_X_SAVED, 2, x);
    vertrix_actor_storage_write(copy, sizeof(copy), SLIDE_Y_SAVED, 2, y);
    if ((int16_t)target_y > (int16_t)y)
    {
        vertrix_actor_set_handler(copy, sizeof(copy), SLIDE_DOWN_HANDLER);
        vertrix_actor_storage_write(copy, sizeof(copy), SLIDE_DOWN_BYTE_44, 1, 0x10);
        vertrix_actor_storage_write(copy, sizeof(copy), SLIDE_DOWN_BYTE_45, 1, 0xc);
        vertrix_actor_storage_write(copy, sizeof(copy), SLIDE_DOWN_WORD_46, 2, 1);
        vertrix_actor_storage_write(copy, sizeof(copy), SLIDE_DOWN_WORD_48, 2, 0xffec);
    }
    else if ((int16_t)target_y < (int16_t)y)
    {
        vertrix_actor_set_handler(copy, sizeof(copy), SLIDE_UP_HANDLER);
        vertrix_actor_storage_write(copy, sizeof(copy), SLIDE_UP_DWORD_58, 4, 0);
        vertrix_actor_storage_write(copy, sizeof(copy), SLIDE_UP_DWORD_5C, 4, SLIDE_STEPS);
        vertrix_actor_storage_write(copy, sizeof(copy), SLIDE_UP_DWORD_60, 4, 1);
        vertrix_actor_storage_write(copy, sizeof(copy), FLAG_93, 1, 1);
        vertrix_actor_storage_write(copy, sizeof(copy), POWER_4E, 1, 0x32);
        vertrix_actor_storage_write(copy, sizeof(copy), FLAG_95, 1, SLIDE_STEPS);
    }
    else
    {
        memcpy(actor, copy, sizeof(copy));
        return 1;
    }
    vertrix_actor_set_period_steps(copy, sizeof(copy), SLIDE_STEPS);
    vertrix_actor_clear_counter(copy, sizeof(copy));
    vertrix_actor_storage_write(copy, sizeof(copy), SLIDE_WORD_12, 2, SLIDE_STEPS);
    vertrix_actor_storage_write(copy, sizeof(copy), SLIDE_WORD_1A, 2, SLIDE_STEPS);
    memcpy(actor, copy, sizeof(copy));
    return 1;
}

int vertrix_board_make_stone(void *board, size_t board_size, int8_t column, int8_t row,
                             const VertrixFactoryServices *services)
{
    uint32_t companion, block, kind, stone, d0, frame;
    void *old_storage, *new_storage;
    size_t old_size, new_size;
    if (column < 0 || column >= COLUMNS || row < 0 || row >= ROWS)
    {
        return 0;
    }
    size_t blocks_at = cell_offset(GRID_BLOCKS, (uint32_t)column, (uint32_t)row);
    size_t companions_at = cell_offset(GRID_COMPANIONS, (uint32_t)column, (uint32_t)row);
    if (!vertrix_actor_storage_read(board, board_size, companions_at, 4, &companion) ||
        !vertrix_actor_storage_read(board, board_size, blocks_at, 4, &block))
    {
        return 0;
    }
    if (companion != 0 || block == 0)
    {
        return 0;
    }
    if (!object_storage(services, block, &old_storage, &old_size) ||
        !vertrix_actor_storage_read(old_storage, old_size, KIND_BYTE, 1, &kind))
    {
        return 0;
    }
    if (kind == STONE_KIND)
    {
        return 0;
    }
    vertrix_actor_storage_write(board, board_size, blocks_at, 4, companion);
    vertrix_actor_storage_write(board, board_size, companions_at, 4, block);
    if (!vertrix_actor_set_handler(old_storage, old_size, STONE_OLD_HANDLER) ||
        !vertrix_actor_storage_write(old_storage, old_size, POWER_4E, 1, STONE_OLD_POWER) ||
        !vertrix_actor_set_period_steps(old_storage, old_size, STONE_STEPS) ||
        !vertrix_actor_storage_write(old_storage, old_size, FLAG_95, 1, STONE_OLD_FLAG_95) ||
        !vertrix_actor_clear_counter(old_storage, old_size) ||
        !vertrix_actor_clear_cc(old_storage, old_size) ||
        !vertrix_block_spawn(board, board_size, STONE_KIND, services, &stone) ||
        !vertrix_actor_storage_write(board, board_size, blocks_at, 4, stone) ||
        !vertrix_actor_storage_read(old_storage, old_size, OBJECT_D0, 4, &d0) ||
        !object_storage(services, stone, &new_storage, &new_size) ||
        !vertrix_actor_set_d0(new_storage, new_size, d0) ||
        !vertrix_actor_set_period_steps(new_storage, new_size, STONE_STEPS) ||
        !vertrix_actor_storage_read(old_storage, old_size, OBJECT_FRAME, 4, &frame) ||
        !vertrix_actor_set_frame_index(new_storage, new_size, frame) ||
        !vertrix_actor_storage_write(new_storage, new_size, FLAG_95, 1, STONE_OLD_FLAG_95) ||
        !vertrix_actor_storage_write(new_storage, new_size, SLIDE_DOWN_WORD_48, 2,
                                     STONE_NEW_WORD_48) ||
        !vertrix_actor_clear_counter(new_storage, new_size) ||
        !vertrix_actor_clear_cc(new_storage, new_size) ||
        !vertrix_actor_set_handler(new_storage, new_size, STONE_NEW_HANDLER))
    {
        return 0;
    }
    return 1;
}
