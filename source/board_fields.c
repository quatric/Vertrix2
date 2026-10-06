#include "board_fields.h"
#include "actor_fields.h"

enum
{
    BOARD_ACTIVE = 0xa60,
    BOARD_EXTRA = 0xce0,
    BOARD_A68 = 0xa68,
    BOARD_COUNTER = 0x838,
    BOARD_COUNTER_VALUE = 0x839,
    BOARD_Y = 0x16,
    PIECE_Y = 0x16,
    PIECE_TOP_MARGIN = 0x48,
    EXTRA_IDLE_HANDLER = 0x44c860
};

static int resolved_object(const void *board, size_t board_size, uint32_t pointer_offset,
                           VertrixObjectStorage resolve, void *context, void **storage,
                           size_t *size)
{
    uint32_t handle;
    return vertrix_actor_storage_read(board, board_size, pointer_offset, 4, &handle) &&
           resolve(handle, storage, size, context);
}

int vertrix_board_object_field(const void *board, size_t board_size, uint32_t pointer_offset,
                               uint32_t field_offset, VertrixObjectStorage resolve, void *context,
                               uint32_t *value)
{
    void *storage;
    size_t size;
    return resolved_object(board, board_size, pointer_offset, resolve, context, &storage, &size) &&
           vertrix_actor_storage_read(storage, size, field_offset, 4, value);
}

int vertrix_board_set_a68(void *board, size_t board_size, uint32_t value)
{
    return vertrix_actor_storage_write(board, board_size, BOARD_A68, 4, value);
}

int vertrix_board_reset_counter(void *board, size_t board_size, uint8_t value)
{
    uint8_t copy[BOARD_COUNTER_VALUE + 1];
    if (!board || board_size < sizeof(copy))
    {
        return 0;
    }
    return vertrix_actor_storage_write(board, board_size, BOARD_COUNTER, 1, 0) &&
           vertrix_actor_storage_write(board, board_size, BOARD_COUNTER_VALUE, 1, value);
}

int vertrix_board_bump_counter(void *board, size_t board_size)
{
    uint32_t counter;
    return vertrix_actor_storage_read(board, board_size, BOARD_COUNTER, 1, &counter) &&
           vertrix_actor_storage_write(board, board_size, BOARD_COUNTER, 1, counter + 1);
}

int vertrix_board_piece_below_top(const void *board, size_t board_size,
                                  VertrixObjectStorage resolve, void *context, uint32_t *below)
{
    void *piece;
    size_t piece_size;
    uint32_t board_y, piece_y;
    if (!resolved_object(board, board_size, BOARD_ACTIVE, resolve, context, &piece, &piece_size) ||
        !vertrix_actor_storage_read(board, board_size, BOARD_Y, 2, &board_y) ||
        !vertrix_actor_storage_read(piece, piece_size, PIECE_Y, 2, &piece_y))
    {
        return 0;
    }
    *below = (int16_t)piece_y > (int16_t)board_y - PIECE_TOP_MARGIN;
    return 1;
}

int vertrix_board_extra_is_idle(const void *board, size_t board_size, VertrixObjectStorage resolve,
                                void *context, uint32_t *idle)
{
    void *extra;
    size_t extra_size;
    uint32_t handler;
    if (!resolved_object(board, board_size, BOARD_EXTRA, resolve, context, &extra, &extra_size) ||
        !vertrix_actor_get_handler(extra, extra_size, &handler))
    {
        return 0;
    }
    *idle = handler == EXTRA_IDLE_HANDLER;
    return 1;
}
