#include "board_piece.h"
#include "object_access.h"
#include <string.h>

enum
{
    BOARD_VALUE = 0x58,
    BOARD_X = 0xe,
    BOARD_Y = 0x16,
    BOARD_PIECE = 0xa60,
    BOARD_CELLS = 0x19d,
    BOARD_CELL_COUNT = 65,
    PIECE_X = 0xe,
    PIECE_Y = 0x16,
    PIECE_HEIGHT = 0x47,
    CHILD_KIND = 0x15c,
    PIECE_CHILDREN = 0x15c,
    PIECE_FLASH_FLAG = 0x17c,
    CHILD_COUNT = 3,
    CHILD_POWER = 0x4e,
    CHILD_STEP = 0x48,
    CHILD_FLAG_A = 0x93,
    CHILD_FLAG_B = 0x95,
    FLASH_POWER = 0x32,
    FLASH_STEP = 0x14,
    COLUMN_WIDTH = 24,
    LAST_COLUMN = 4
};

static int active_piece(const void *board, size_t board_size, uint32_t *piece)
{
    return vertrix_actor_storage_read(board, board_size, BOARD_PIECE, 4, piece);
}

int vertrix_board_has_piece(const void *board, size_t board_size, uint32_t *has_piece)
{
    uint32_t piece;
    if (!active_piece(board, board_size, &piece))
    {
        return 0;
    }
    *has_piece = piece != 0;
    return 1;
}

int vertrix_board_fill_cells(void *board, size_t board_size)
{
    uint32_t value;
    if (!vertrix_actor_storage_read(board, board_size, BOARD_VALUE, 1, &value) ||
        board_size < BOARD_CELLS + BOARD_CELL_COUNT)
    {
        return 0;
    }
    memset((uint8_t *)board + BOARD_CELLS, (int)value, BOARD_CELL_COUNT);
    return 1;
}

int vertrix_board_piece_child_kinds(const void *board, size_t board_size,
                                    VertrixObjectStorage resolve, void *context,
                                    uint8_t kinds[VERTRIX_PIECE_CHILD_COUNT])
{
    uint32_t piece;
    return active_piece(board, board_size, &piece) &&
           vertrix_piece_child_kinds(piece, resolve, context, kinds);
}

int vertrix_board_flash_children(const void *board, size_t board_size, VertrixObjectStorage resolve,
                                 void *context)
{
    uint32_t piece;
    if (!active_piece(board, board_size, &piece))
    {
        return 0;
    }
    for (int child = 0; child < CHILD_COUNT; ++child)
    {
        uint32_t handle;
        if (!vertrix_object_read(piece, resolve, context, PIECE_CHILDREN + 4 * child, 4, &handle) ||
            !vertrix_object_write(handle, resolve, context, CHILD_FLAG_A, 1, 1) ||
            !vertrix_object_write(handle, resolve, context, CHILD_FLAG_B, 1, 0) ||
            !vertrix_object_write(handle, resolve, context, CHILD_POWER, 1, FLASH_POWER) ||
            !vertrix_object_write(handle, resolve, context, CHILD_STEP, 2, FLASH_STEP))
        {
            return 0;
        }
    }
    return vertrix_object_write(piece, resolve, context, PIECE_FLASH_FLAG, 4, 1);
}

static int piece_cell(const void *board, size_t board_size, VertrixObjectStorage resolve,
                      void *context, uint32_t piece, int y_offset, int32_t *column, int32_t *row)
{
    uint32_t piece_x, piece_y, board_x, board_y;
    if (!vertrix_object_read(piece, resolve, context, PIECE_X, 2, &piece_x) ||
        !vertrix_object_read(piece, resolve, context, PIECE_Y, 2, &piece_y) ||
        !vertrix_actor_storage_read(board, board_size, BOARD_X, 2, &board_x) ||
        !vertrix_actor_storage_read(board, board_size, BOARD_Y, 2, &board_y))
    {
        return 0;
    }
    *column = ((int32_t)(int16_t)piece_x - (int16_t)board_x) / COLUMN_WIDTH;
    *row = ((int32_t)(int16_t)(piece_y + y_offset) - (int16_t)board_y) / COLUMN_WIDTH;
    return 1;
}

int vertrix_board_piece_column(const void *board, size_t board_size, VertrixObjectStorage resolve,
                               void *context, int32_t *column)
{
    uint32_t piece;
    int32_t row;
    return active_piece(board, board_size, &piece) &&
           piece_cell(board, board_size, resolve, context, piece, 0, column, &row);
}

int vertrix_board_piece_span(const void *board, size_t board_size, VertrixObjectStorage resolve,
                             void *context, int32_t *column, int32_t *top, int32_t *bottom)
{
    uint32_t piece;
    int32_t top_column, bottom_column;
    if (!active_piece(board, board_size, &piece) ||
        !piece_cell(board, board_size, resolve, context, piece, 0, &top_column, top) ||
        !piece_cell(board, board_size, resolve, context, piece, PIECE_HEIGHT, &bottom_column,
                    bottom))
    {
        return 0;
    }
    *column = bottom_column;
    return 1;
}

int vertrix_board_piece_child_kind(const void *board, size_t board_size,
                                   VertrixObjectStorage resolve, void *context, uint32_t index,
                                   int32_t *kind)
{
    uint32_t piece, child, value;
    if (!active_piece(board, board_size, &piece))
    {
        return 0;
    }
    if (piece == 0)
    {
        *kind = -1;
        return 1;
    }
    if (!vertrix_object_read(piece, resolve, context, PIECE_CHILDREN + 4 * index, 4, &child) ||
        !vertrix_object_read(child, resolve, context, CHILD_KIND, 1, &value))
    {
        return 0;
    }
    *kind = (int8_t)value;
    return 1;
}

int vertrix_board_piece_past_edge(const void *board, size_t board_size,
                                  VertrixObjectStorage resolve, void *context, int right,
                                  uint32_t *past)
{
    uint32_t piece, piece_x, board_x;
    if (!active_piece(board, board_size, &piece) ||
        !vertrix_object_read(piece, resolve, context, PIECE_X, 2, &piece_x) ||
        !vertrix_actor_storage_read(board, board_size, BOARD_X, 2, &board_x))
    {
        return 0;
    }
    int32_t column = ((int32_t)(int16_t)piece_x - (int16_t)board_x) / COLUMN_WIDTH;
    *past = right ? column > LAST_COLUMN : column <= 0;
    return 1;
}
