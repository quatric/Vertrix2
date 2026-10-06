#include "player_actions.h"
#include "actor_storage.h"
#include "event_stack.h"
#include "object_access.h"

enum
{
    PLAYER_BOARD = 0x15c,
    PLAYER_STACK = 0x19c,
    PLAYER_STACK_SIZE = 0x20c,
    PLAYER_HANDLER = 0x154,
    PLAYER_D0C = 0x194,
    PLAYER_D10 = 0x198,
    PLAYER_B00 = 0x4c4,
    PLAYER_B01 = 0x4c5,
    PLAYER_D04 = 0x4c8,
    PLAYER_B08 = 0x4cc,
    PLAYER_B14 = 0x4cd,
    PLAYER_LEVEL = 0x17c,
    BOARD_D18 = 0xb80,
    BOARD_D1C = 0xc0,
    BOARD_W20 = 0x12,
    BOARD_W22 = 0x1a,
    BOARD_D24 = 0xb84,
    BOARD_D28 = 0xb88,
    LEVEL_DRAW_LIMIT = 10,
    PLAYER_OPPONENT = 0x3b0,
    STATE_IDLE = 1,
    STATE_BUSY = 4,
    STATE_DONE = 5,
    FLAG_OPPONENT = 1,
    HANDLER_452070 = 0x452070,
    HANDLER_452370 = 0x452370,
    HANDLER_4520B0 = 0x4520b0,
    HANDLER_4523D0 = 0x4523d0,
    HANDLER_4523B0 = 0x4523b0,
    PLAYER_TABLE_INDEX = 0x488,
    SELECTOR_TABLE = 0x4f8d38,
    VALUE_TABLE = 0x4f8d84,
    ROW_STRIDE = 40,
    LEVEL_STRIDE = 240,
    LOW_WORD = 0xffff
};

typedef struct
{
    size_t offset;
    unsigned width;
} Field;

/* Player fields in record order: b00, b01, d04, b08, d0c, d10, b14, d2c. */
static const Field player_fields[8] = {{PLAYER_B00, 1}, {PLAYER_B01, 1},    {PLAYER_D04, 4},
                                       {PLAYER_B08, 1}, {PLAYER_D0C, 4},    {PLAYER_D10, 4},
                                       {PLAYER_B14, 1}, {PLAYER_HANDLER, 4}};

/* Board fields in record order: d18, d1c, w20, w22, d24, d28. */
static const Field board_fields[6] = {{BOARD_D18, 4}, {BOARD_D1C, 4}, {BOARD_W20, 2},
                                      {BOARD_W22, 2}, {BOARD_D24, 4}, {BOARD_D28, 4}};

int vertrix_player_push_event(void *player, size_t size, VertrixObjectStorage resolve,
                              void *context)
{
    uint32_t board, from_player[8], from_board[6];
    if (!player || size < PLAYER_STACK + PLAYER_STACK_SIZE ||
        !vertrix_actor_storage_read(player, size, PLAYER_BOARD, 4, &board))
    {
        return 0;
    }
    for (int i = 0; i < 8; ++i)
    {
        if (!vertrix_actor_storage_read(player, size, player_fields[i].offset,
                                        player_fields[i].width, &from_player[i]))
        {
            return 0;
        }
    }
    for (int i = 0; i < 6; ++i)
    {
        if (!vertrix_object_read(board, resolve, context, board_fields[i].offset,
                                 board_fields[i].width, &from_board[i]))
        {
            return 0;
        }
    }
    VertrixEventRecord record = {.b00 = (uint8_t)from_player[0],
                                 .b01 = (uint8_t)from_player[1],
                                 .d04 = from_player[2],
                                 .b08 = (uint8_t)from_player[3],
                                 .d0c = from_player[4],
                                 .d10 = from_player[5],
                                 .b14 = (uint8_t)from_player[6],
                                 .d2c = from_player[7],
                                 .d18 = from_board[0],
                                 .d1c = from_board[1],
                                 .w20 = (uint16_t)from_board[2],
                                 .w22 = (uint16_t)from_board[3],
                                 .d24 = from_board[4],
                                 .d28 = from_board[5]};
    vertrix_event_stack_push((uint8_t *)player + PLAYER_STACK, size - PLAYER_STACK, &record);
    return 1;
}

int vertrix_player_randomize_level(void *player, size_t size, VertrixSpawnDraw draw,
                                   void *draw_context, VertrixLevelNotify notify,
                                   void *notify_context)
{
    uint32_t current, level;
    if (!vertrix_actor_storage_read(player, size, PLAYER_LEVEL, 4, &current))
    {
        return -1;
    }
    do
    {
        level = draw(LEVEL_DRAW_LIMIT, draw_context);
    } while (level == current);
    return vertrix_player_set_level(player, size, (int32_t)level, notify, notify_context);
}

static int read_opponent(const void *player, size_t size, uint32_t *opponent)
{
    return vertrix_actor_storage_read(player, size, PLAYER_OPPONENT, 4, opponent);
}

static int enter_state(void *player, size_t size, uint32_t state, uint32_t handler)
{
    return vertrix_actor_storage_write(player, size, PLAYER_B08, 1, state) &&
           vertrix_actor_storage_write(player, size, PLAYER_HANDLER, 4, handler);
}

int vertrix_player_enter_452070(void *player, size_t size, VertrixObjectStorage resolve,
                                void *context, uint32_t *changed)
{
    uint32_t opponent, flag, state;
    *changed = 0;
    if (!read_opponent(player, size, &opponent) ||
        !vertrix_object_read(opponent, resolve, context, PLAYER_B00, 1, &flag))
    {
        return 0;
    }
    if (flag == FLAG_OPPONENT)
    {
        return 1;
    }
    if (!vertrix_object_read(opponent, resolve, context, PLAYER_B08, 1, &state))
    {
        return 0;
    }
    if (state != STATE_IDLE && state != STATE_BUSY)
    {
        return 1;
    }
    if (!vertrix_player_push_event(player, size, resolve, context) ||
        !enter_state(player, size, STATE_DONE, HANDLER_452070))
    {
        return 0;
    }
    *changed = 1;
    return 1;
}

int vertrix_player_enter_452370(void *player, size_t size, VertrixObjectStorage resolve,
                                void *context)
{
    return vertrix_player_push_event(player, size, resolve, context) &&
           enter_state(player, size, STATE_DONE, HANDLER_452370);
}

int vertrix_player_enter_4520b0(void *player, size_t size, VertrixObjectStorage resolve,
                                void *context, uint32_t *changed)
{
    uint32_t opponent, state;
    *changed = 0;
    if (!read_opponent(player, size, &opponent) ||
        !vertrix_object_read(opponent, resolve, context, PLAYER_B08, 1, &state))
    {
        return 0;
    }
    if (state != STATE_IDLE)
    {
        return 1;
    }
    if (!vertrix_player_push_event(player, size, resolve, context) ||
        !enter_state(player, size, STATE_DONE, HANDLER_4520B0))
    {
        return 0;
    }
    *changed = 1;
    return 1;
}

int vertrix_player_enter_4523d0(void *player, size_t size, VertrixObjectStorage resolve,
                                void *context)
{
    uint32_t opponent;
    void *storage;
    size_t opponent_size;
    if (!enter_state(player, size, STATE_BUSY, HANDLER_4523D0) ||
        !read_opponent(player, size, &opponent) ||
        !resolve(opponent, &storage, &opponent_size, context) ||
        !vertrix_player_push_event(storage, opponent_size, resolve, context) ||
        !enter_state(storage, opponent_size, STATE_BUSY, HANDLER_4523B0))
    {
        return 0;
    }
    return 1;
}

int vertrix_player_draw_table_value(const void *player, size_t size, uint32_t low_row,
                                    uint32_t width_row, uint32_t level, VertrixMemoryRead read,
                                    void *read_context, VertrixSpawnDraw draw, void *draw_context,
                                    VertrixPlayerDrawGlobals *globals, uint32_t *result)
{
    uint32_t index, selector, low, width;
    uint32_t base = VALUE_TABLE + LEVEL_STRIDE * level;
    if (!vertrix_actor_storage_read(player, size, PLAYER_TABLE_INDEX, 4, &index) ||
        !read(SELECTOR_TABLE + 4 * index, 4, &selector, read_context) ||
        !read(base + ROW_STRIDE * low_row + 4 * selector, 4, &low, read_context) ||
        !read(base + ROW_STRIDE * width_row + 4 * selector, 4, &width, read_context))
    {
        return 0;
    }
    globals->selector = selector;
    globals->low = low;
    globals->width = width;
    *result =
        (low & LOW_WORD) + ((width & LOW_WORD) != 0 ? draw((uint16_t)width, draw_context) : 0);
    return 1;
}
