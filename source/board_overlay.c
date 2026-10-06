#include "board_overlay.h"
#include "actor_fields.h"
#include "actor_style_storage.h"

enum
{
    PLAYER_MODE = 0,
    PLAYER_BOARD = 0x15c,
    MODE_FIRST = 1,
    MODE_SECOND = 2,
    BLOCK_SIZE = 0x160,
    BOARD_ORIGIN_X = 0xc,
    BOARD_ORIGIN_Y = 0x14,
    BOARD_X_WORD = 0xe,
    BOARD_Y_WORD = 0x16,
    BOARD_OVERLAY = 0xce0,
    BOARD_STYLES = 0xce4,
    ACTOR_CLASS = 0,
    ACTOR_X_WORD = 0xe,
    ACTOR_Y_WORD = 0x16,
    ACTOR_BOX_LEFT = 0xa8,
    ACTOR_BOX_TOP = 0xaa,
    ACTOR_BOX_RIGHT = 0xac,
    ACTOR_BOX_BOTTOM = 0xae,
    ACTOR_MODE = 0x8e,
    ACTOR_MODE_VALUE = 3,
    BOX_WIDTH = 0x77,
    BOX_HEIGHT = 0x137,
    BELOW_BOARD = 0x138,
    STYLE_RECORD_SIZE = 12,
    FIRST_RESOURCE = 0x544d44,
    SECOND_RESOURCE = 0x544d60,
    FIRST_CLASS = 0x15,
    SECOND_CLASS = 0x16
};

static int read_record(VertrixMemoryRead read, void *context, uint32_t address,
                       uint8_t record[STYLE_RECORD_SIZE])
{
    for (uint32_t i = 0; i < STYLE_RECORD_SIZE; ++i)
    {
        uint32_t value;
        if (!read(address + i, 1, &value, context))
        {
            return 0;
        }
        record[i] = (uint8_t)value;
    }
    return 1;
}

int vertrix_board_create_overlay(void *board, size_t board_size, uint32_t variant, uint32_t d0,
                                 uint32_t steps, const VertrixFactoryServices *services,
                                 VertrixMemoryRead read, void *read_context)
{
    void *storage;
    size_t size;
    uint32_t origin_x, origin_y, board_x, board_y, styles, handle;
    uint8_t record[STYLE_RECORD_SIZE];
    if (!vertrix_actor_storage_read(board, board_size, BOARD_ORIGIN_X, 4, &origin_x) ||
        !vertrix_actor_storage_read(board, board_size, BOARD_ORIGIN_Y, 4, &origin_y) ||
        !vertrix_actor_storage_read(board, board_size, BOARD_X_WORD, 2, &board_x) ||
        !vertrix_actor_storage_read(board, board_size, BOARD_Y_WORD, 2, &board_y) ||
        !vertrix_actor_storage_read(board, board_size, BOARD_STYLES, 4, &styles) ||
        !read_record(read, read_context, styles, record))
    {
        return 0;
    }
    handle = services->allocate(BLOCK_SIZE, services->context);
    uint32_t left = (uint32_t)((int32_t)origin_x >> 16);
    uint32_t top = (uint32_t)((int32_t)origin_y >> 16);
    if (handle == 0 || !services->resolve(handle, &storage, &size, services->context) ||
        !vertrix_actor_storage_construct(storage, size) ||
        !vertrix_actor_initialize(storage, size, 0, 0, 0, 0, 0, 0, 0) ||
        !vertrix_actor_set_d0(storage, size, d0) ||
        !vertrix_actor_set_period_steps(storage, size, steps) ||
        !vertrix_actor_attach_resource(storage, size,
                                       variant == 0 ? FIRST_RESOURCE : SECOND_RESOURCE) ||
        !vertrix_actor_storage_write(storage, size, ACTOR_CLASS, 4,
                                     variant == 0 ? FIRST_CLASS : SECOND_CLASS) ||
        !vertrix_actor_storage_write(storage, size, ACTOR_BOX_LEFT, 2, left) ||
        !vertrix_actor_storage_write(storage, size, ACTOR_BOX_TOP, 2, left + BOX_WIDTH) ||
        !vertrix_actor_storage_write(storage, size, ACTOR_BOX_RIGHT, 2, top) ||
        !vertrix_actor_storage_write(storage, size, ACTOR_BOX_BOTTOM, 2, top + BOX_HEIGHT) ||
        !vertrix_actor_storage_write(storage, size, ACTOR_MODE, 1, ACTOR_MODE_VALUE) ||
        !vertrix_actor_set_frame_index(storage, size, 0) ||
        !vertrix_actor_storage_write(storage, size, ACTOR_X_WORD, 2, board_x) ||
        !vertrix_actor_storage_write(storage, size, ACTOR_Y_WORD, 2, board_y + BELOW_BOARD) ||
        !vertrix_actor_storage_style(storage, size, record) ||
        !vertrix_actor_storage_write(board, board_size, BOARD_OVERLAY, 4, handle))
    {
        return 0;
    }
    return 1;
}

int vertrix_player_create_overlay(const void *player, size_t player_size, uint32_t fallback_variant,
                                  uint32_t d0, uint32_t steps,
                                  const VertrixFactoryServices *services, VertrixMemoryRead read,
                                  void *read_context)
{
    uint32_t mode, board_handle;
    void *board;
    size_t board_size;
    uint32_t variant = fallback_variant;
    if (!vertrix_actor_storage_read(player, player_size, PLAYER_MODE, 4, &mode) ||
        !vertrix_actor_storage_read(player, player_size, PLAYER_BOARD, 4, &board_handle) ||
        !services->resolve(board_handle, &board, &board_size, services->context))
    {
        return 0;
    }
    if (mode == MODE_FIRST)
    {
        variant = 0;
    }
    else if (mode == MODE_SECOND)
    {
        variant = 1;
    }
    return vertrix_board_create_overlay(board, board_size, variant, d0, steps, services, read,
                                        read_context);
}
