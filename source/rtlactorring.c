#include "rtlactorring.h"

/* A ring of eight sparks around a board cell, flying out at 45 degree steps from a random angle. */

enum
{
    SPARKS = 8,
    SPARK_BYTES = 0x15c,
    CELL_PIXELS = 0x18,
    HALF_CELL = 0xc,
    FULL_TURN = 360,
    STEP = 45,

    /* The board's origin and its list of effects. */
    BOARD_X = 0xe,
    BOARD_Y = 0x16,
    BOARD_EFFECTS = 0xcec,

    ACTOR_X_FIXED = 0xc,
    ACTOR_X = 0xe,
    ACTOR_Y_FIXED = 0x14,
    ACTOR_Y = 0x16,
    ACTOR_ANGLE = 0x24,
    ACTOR_TURN = 0x28,
    ACTOR_SPEED = 0x30,
    ACTOR_SPEED_STEP = 0x32,
    ACTOR_PALETTE_OFFSET = 0x48,
    ACTOR_LAYER = 0x4e,
    ACTOR_LIFE = 0x64,
    ACTOR_FLAG_93 = 0x93,
    ACTOR_FLAG_94 = 0x94,
    ACTOR_FLAG_95 = 0x95,

    /* The random table: the next word modulo a limit. */
    RANDOM = 0x598d30,
    RANDOM_NEXT = 0x4826c0,
    /* A spark is a single frame (one in 33) or a frame of the spark strip. */
    SPARK_IMAGE = 0x546500,
    SPARK_STRIP = 0x54651c,
    SPARK_UPDATE = 0x443550,

    GET_MEM = 0x4ca000,
    ACTOR_RESET = 0x4abd70,
    ACTOR_PLACE = 0x4adf20,
    ACTOR_SET_LIMIT = 0x4ac470,
    ACTOR_SET_RATE = 0x4ac7b0,
    ACTOR_SET_SECOND_LIMIT = 0x4ac840,
    ACTOR_ATTACH = 0x4ac8d0,
    ACTOR_SET_FRAME = 0x4ac710,
    ACTOR_BIND_FRAME = 0x4ac8a0,
    ACTOR_SET_ORIGIN = 0x4ad510,
    ACTOR_SET_UPDATE = 0x4ac8f0,
    LIST_APPEND = 0x4b5e70
};

static uint32_t random_below(Port *port, uint32_t limit)
{
    return port_call(port, RANDOM_NEXT, RANDOM, limit, 0, 0) & 0xffff;
}

/* Original 0x42bca0 (eax = board, edx = column, ebx = row): eight sparks (0x15c-byte actors) at
 * the cell's centre, 45 degrees apart from a random start: each is reset, placed, given its
 * counter limits and rate, the spark image or a random frame of the strip, its angle, a speed of
 * 80 to 99, the update 0x443550 and a 40-tick life, and joins the board's effects (+0xcec).
 * Returns what the last append returns, eax and edx (its callers read both). */
uint32_t vertrix_port_board_cell_spawn_actor_ring_42bca0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t board = entry->eax;
    const uint32_t x_offset = entry->edx * CELL_PIXELS;
    const uint32_t y_offset = entry->ebx * CELL_PIXELS;
    const uint32_t effects = board + BOARD_EFFECTS;
    uint32_t angle = random_below(&port, FULL_TURN);
    uint32_t result = 0;
    for (int i = 0; i < SPARKS && !port.env.failed; i++)
    {
        uint32_t spark = port_call(&port, GET_MEM, SPARK_BYTES, 0, 0, 0);
        if (spark != 0)
        {
            spark = port_call(&port, ACTOR_RESET, spark, 0, 0, 0);
        }
        const uint32_t nothing[5] = {0};
        port_call_stack(&port, ACTOR_PLACE, spark, 0, 0, 0, nothing, 5);
        port_set16(&port, spark, ACTOR_X, port_u16(&port, board, BOARD_X) + x_offset + HALF_CELL);
        port_set16(&port, spark, ACTOR_Y, port_u16(&port, board, BOARD_Y) + y_offset + HALF_CELL);
        port_call(&port, ACTOR_SET_LIMIT, spark, 4, 0, 0);
        port_call(&port, ACTOR_SET_RATE, spark, 1, 0, 0);
        port_call(&port, ACTOR_SET_SECOND_LIMIT, spark, 1, 0, 0);
        const uint32_t pick = random_below(&port, 0x21);
        port_call(&port, ACTOR_ATTACH, spark, pick == 0 ? SPARK_IMAGE : SPARK_STRIP, 0, 0);
        port_call(&port, ACTOR_SET_FRAME, spark, pick == 0 ? 0 : pick - 1, 0, 0);
        port_set8(&port, spark, ACTOR_FLAG_94, 1);
        port_call(&port, ACTOR_BIND_FRAME, spark, 0, 0, 0);
        port_set8(&port, spark, ACTOR_FLAG_95, 4);
        port_set16(&port, spark, ACTOR_PALETTE_OFFSET, 0);
        port_set8(&port, spark, ACTOR_LAYER, 0x32);
        port_set8(&port, spark, ACTOR_FLAG_93, 1);
        port_set16(&port, spark, ACTOR_ANGLE, (uint32_t)((int32_t)(angle & 0xffff) % FULL_TURN));
        port_set16(&port, spark, ACTOR_TURN, 0);
        /* Its origin: the integer parts of its 16.16 position. */
        const uint32_t x = (uint32_t)((int32_t)port_u32(&port, spark, ACTOR_X_FIXED) >> 16);
        const uint32_t y = (uint32_t)((int32_t)port_u32(&port, spark, ACTOR_Y_FIXED) >> 16);
        port_call(&port, ACTOR_SET_ORIGIN, spark, 0, x, y);
        port_set16(&port, spark, ACTOR_SPEED, random_below(&port, 0x14) + 0x50);
        port_set16(&port, spark, ACTOR_SPEED_STEP, 2);
        port_set32(&port, spark, ACTOR_LIFE, 0x28);
        angle += STEP;
        port_call(&port, ACTOR_SET_UPDATE, spark, SPARK_UPDATE, 0, 0);
        result = port_call(&port, LIST_APPEND, effects, spark, 0, 0);
    }
    return port_return(&port, result, vertrix_lift_edx);
}
