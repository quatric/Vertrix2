#include "board_cell_replace.h"
#include "actor_storage.h"

enum
{
    FORWARD_FRAME_SHIFT = 4
};

enum
{
    BYTE_WIDTH = 1,
    DWORD_WIDTH = 4,
    LOCAL_FIRST = 0x18,
    LOCAL_SECOND = 0x14
};

typedef struct Cell
{
    uint32_t column;
    uint32_t row;
    size_t block_offset;
} Cell;

static int cell_mark(void *storage, size_t size, const Cell *cell, uint32_t *block)
{
    size_t marker =
        VERTRIX_REPLACE_MARKERS + (size_t)VERTRIX_REPLACE_MARKER_COLUMN * cell->column + cell->row;
    size_t companion = VERTRIX_REPLACE_COMPANION +
                       (size_t)VERTRIX_REPLACE_COLUMN_STRIDE * cell->column + 4 * (size_t)cell->row;
    return vertrix_actor_storage_write(storage, size, marker, BYTE_WIDTH, 2) &&
           vertrix_actor_storage_read(storage, size, cell->block_offset, DWORD_WIDTH, block) &&
           vertrix_actor_storage_write(storage, size, companion, DWORD_WIDTH, *block) &&
           vertrix_actor_storage_write(storage, size, cell->block_offset, DWORD_WIDTH, 0);
}

static int16_t low_half(uint32_t value)
{
    return (int16_t)(uint16_t)value;
}

static uint32_t replace_tail(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             uint32_t board, void *storage, size_t size, uint32_t arg,
                             const Cell *cell, uint32_t block, int random_roles)
{
    void *block_storage;
    size_t block_size;
    void *new_storage;
    size_t new_size;
    uint32_t old_ebx =
        random_roles ? (uint32_t)(VERTRIX_REPLACE_COLUMN_STRIDE * cell->column) : block;
    uint32_t old_ecx = random_roles ? block : board + VERTRIX_REPLACE_COLUMN_STRIDE * cell->column;
    uint32_t held;
    uint32_t speed;
    uint32_t replacement;
    uint32_t edx;
    if (!services->resolve(block, &block_storage, &block_size, services->context))
    {
        return 0;
    }
    vertrix_call(calls, 0x4ac8f0, block, VERTRIX_REPLACE_HANDLER_44D480, old_ebx, old_ecx, 0);
    if (!vertrix_actor_storage_write(block_storage, block_size, 0x4e, BYTE_WIDTH, 0x64))
    {
        return 0;
    }
    vertrix_call(calls, 0x4ac7b0, block, 3, old_ebx, old_ecx, 0);
    if (!vertrix_actor_storage_write(block_storage, block_size, 0x44, BYTE_WIDTH, 0x10))
    {
        return 0;
    }
    replacement = vertrix_call(calls, 0x430800, board, arg, old_ebx, old_ecx, 0);
    if (!vertrix_actor_storage_write(storage, size, cell->block_offset, DWORD_WIDTH, replacement) ||
        !vertrix_actor_storage_read(block_storage, block_size, 0xd0, DWORD_WIDTH, &held) ||
        !services->resolve(replacement, &new_storage, &new_size, services->context))
    {
        return 0;
    }
    uint32_t new_ebx = random_roles ? replacement : block;
    uint32_t new_ecx = random_roles ? block : replacement;
    vertrix_call(calls, 0x4ac490, replacement, held, new_ebx, new_ecx, 0);
    vertrix_call(calls, 0x4ac7b0, replacement, 3, new_ebx, new_ecx, 0);
    if (!vertrix_actor_storage_read(block_storage, block_size, 0xb8, DWORD_WIDTH, &speed))
    {
        return 0;
    }
    edx = speed;
    vertrix_call(calls, 0x4ac710, replacement, edx, new_ebx, new_ecx, 0);
    vertrix_call(calls, 0x4ac510, replacement, edx, new_ebx, new_ecx, 0);
    vertrix_call(calls, 0x4ac380, replacement, edx, new_ebx, new_ecx, 0);
    vertrix_call(calls, 0x4ac510, block, edx, new_ebx, new_ecx, 0);
    edx = VERTRIX_REPLACE_HANDLER_44D5F0;
    vertrix_call(calls, 0x4ac380, block, edx, new_ebx, new_ecx, 0);
    vertrix_call(calls, 0x4ac8f0, replacement, edx, new_ebx, new_ecx, 0);
    if (!vertrix_actor_storage_write(new_storage, new_size, 0x44, BYTE_WIDTH, 0))
    {
        return 0;
    }
    vertrix_call(calls, 0x430440, board, (uint32_t)(int32_t)low_half(cell->column),
                 (uint32_t)(int32_t)low_half(cell->row), new_ecx, 0);
    return 1;
}

static void fill_cell(Cell *cell, uint32_t column, uint32_t row)
{
    cell->column = column;
    cell->row = row;
    cell->block_offset =
        VERTRIX_REPLACE_BLOCKS + (size_t)VERTRIX_REPLACE_COLUMN_STRIDE * column + 4 * (size_t)row;
}

uint32_t vertrix_board_replace_cell(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t board,
                                    void *storage, size_t size, uint32_t arg, uint32_t frame,
                                    uint32_t ebx, uint32_t ecx)
{
    Cell cell;
    uint32_t column;
    uint32_t row;
    uint32_t block;
    if (vertrix_call(calls, 0x436030, board, arg, ebx, ecx, 0) == 0)
    {
        return 0;
    }
    vertrix_call_out(calls, 0x435fe0, board, 0, frame - LOCAL_FIRST, frame - LOCAL_SECOND, &column,
                     &row);
    fill_cell(&cell, column, row);
    if (!cell_mark(storage, size, &cell, &block))
    {
        return 0;
    }
    return replace_tail(calls, services, board, storage, size, arg, &cell, block, 0);
}

uint32_t vertrix_board_replace_random_cell(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services, uint32_t board,
                                           void *storage, size_t size, uint32_t arg, uint32_t frame,
                                           uint32_t ebx, uint32_t ecx)
{
    Cell cell;
    uint32_t column;
    uint32_t row;
    uint32_t block;
    uint32_t verdict = vertrix_call(calls, 0x436030, board, arg, ebx, ecx, 0);
    uint32_t draw;
    if (verdict == 0)
    {
        return 0;
    }
    draw = vertrix_call(calls, 0x4826c0, 0x598d30, verdict & 0xffff, ebx, frame - LOCAL_SECOND, 0);
    vertrix_call_out(calls, 0x4360b0, board, draw & 0xffff, frame - LOCAL_FIRST,
                     frame - LOCAL_SECOND, &column, &row);
    fill_cell(&cell, column, row);
    if (!cell_mark(storage, size, &cell, &block))
    {
        return 0;
    }
    return replace_tail(calls, services, board, storage, size, arg, &cell, block, 1);
}

uint32_t vertrix_board_burst_occupied(const VertrixCalls *calls, uint32_t first,
                                      const void *first_storage, size_t first_size, uint32_t second,
                                      const void *second_storage, size_t second_size)
{
    uint32_t result = first;
    for (uint32_t column = 0; column < VERTRIX_REPLACE_COLUMNS; ++column)
    {
        for (uint32_t row = 0; row < VERTRIX_REPLACE_ROWS; ++row)
        {
            size_t offset = VERTRIX_REPLACE_BLOCKS +
                            (size_t)VERTRIX_REPLACE_COLUMN_STRIDE * column + 4 * (size_t)row;
            uint32_t in_second;
            uint32_t in_first;
            if (!vertrix_actor_storage_read(second_storage, second_size, offset, DWORD_WIDTH,
                                            &in_second) ||
                !vertrix_actor_storage_read(first_storage, first_size, offset, DWORD_WIDTH,
                                            &in_first))
            {
                return 0;
            }
            if (in_second != 0)
            {
                result = vertrix_call(calls, 0x430660, first, (uint32_t)(int32_t)low_half(column),
                                      (uint32_t)(int32_t)low_half(row), row, 0);
            }
            if (in_first != 0)
            {
                result = vertrix_call(calls, 0x430660, second, (uint32_t)(int32_t)low_half(column),
                                      (uint32_t)(int32_t)low_half(row), row, 0);
            }
        }
    }
    return result;
}

uint32_t vertrix_board_view_setup(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, const void *storage, size_t size, uint32_t frame)
{
    uint32_t board;
    uint32_t handler;
    void *board_storage;
    size_t board_size;
    uint32_t stack[11];
    if (!vertrix_actor_storage_read(storage, size, 0x15c, DWORD_WIDTH, &board))
    {
        return 0;
    }
    stack[0] = object + 0x4cc;
    stack[1] = object + 0x194;
    stack[2] = object + 0x198;
    stack[3] = 0;
    stack[4] = frame - LOCAL_SECOND;
    stack[5] = board + 0xb80;
    stack[6] = board + 0xc0;
    stack[7] = 0;
    stack[8] = 0;
    stack[9] = board + 0xb84;
    stack[10] = board + 0xb88;
    vertrix_calln(calls, 0x482110, object + 0x19c, object + 0x4c4, object + 0x4c5, 0, stack, 11,
                  &handler);
    vertrix_call(calls, 0x4ac8f0, object, handler, object + 0x4c5, 0, 0);
    if (!vertrix_actor_storage_read(storage, size, 0x15c, DWORD_WIDTH, &board) ||
        !services->resolve(board, &board_storage, &board_size, services->context) ||
        !vertrix_actor_storage_write(board_storage, board_size, 0xb90, DWORD_WIDTH, 1))
    {
        return 0;
    }
    vertrix_call(calls, 0x4726d0, board, handler, object + 0x4c5, 0, 0);
    return vertrix_call(calls, 0x43ad50, object, handler, object + 0x4c5, 0, 0);
}

uint32_t vertrix_board_view_setup_forward(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services, uint32_t object,
                                          const void *storage, size_t size, uint32_t frame)
{
    return vertrix_board_view_setup(calls, services, object, storage, size,
                                    frame - FORWARD_FRAME_SHIFT);
}
