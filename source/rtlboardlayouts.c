#include "rtlboardlayouts.h"

enum
{
    /* The frame under the return slot: the width and height 0x4b14c0 measures. */
    BELOW = 0x9c,
    MEASURED_WIDTH = 0x9c,
    MEASURED_HEIGHT = 0x98,

    /* The board: its position, the cells' signed x and y nudges (5 columns of 13 rows), and its
     * actor tables. */
    BOARD_X = 0xe,
    BOARD_Y = 0x16,
    CELL_NUDGE_X = 0x15c,
    CELL_NUDGE_Y = 0x19d,
    COLUMNS = 5,
    ROWS = 13,
    CELL = 0x18,
    HALF_CELL = 0xc,
    CELL_ACTORS = 0x220,
    CELL_EXTRAS = 0x87c,
    COLUMN_STRIDE = 0x34,
    BOTTOM_ACTORS = 0x988,
    BOTTOM_NUDGE_X = 0x99c,
    BOTTOM_NUDGE_Y = 0x9a1,
    BOTTOM_Y = 0x138,
    LEFT_ACTORS = 0x9e8,
    LEFT_NUDGE_X = 0x9a6,
    LEFT_NUDGE_Y = 0x9b3,
    RIGHT_ACTORS = 0xa2c,
    RIGHT_NUDGE_X = 0x9c0,
    RIGHT_NUDGE_Y = 0x9cd,
    RIGHT_X = 0x78,
    QUARTERS = 0x324,
    QUARTER_COLUMN = 0xd0,
    QUARTER_ROW = 0x10,

    ACTOR_X = 0xe,
    ACTOR_Y = 0x16,
    ACTOR_KIND = 0x44,
    /* Actors of this kind keep their place uncentred. */
    KIND_FIXED = 0x10,

    MEASURE = 0x4b14c0
};

static uint32_t nudge(Port *port, uint32_t board, uint32_t table, uint32_t index)
{
    return (uint32_t)(int32_t)(int8_t)port_u8(port, board + index, table);
}

/* Moves the actor to (x, y) and, unless its kind is 0x10, centres it in a cell by its size
 * (0x4b14c0, with `edi` as the original leaves it; half of 0x18 less each, unsigned). */
static void place(Port *port, const LiftEntry *entry, uint32_t board, uint32_t actor, uint32_t x,
                  uint32_t y, uint32_t edi)
{
    port_set16(port, actor, ACTOR_X, x);
    port_set16(port, actor, ACTOR_Y, y);
    if (port_u8(port, actor, ACTOR_KIND) == KIND_FIXED)
    {
        return;
    }
    const uint32_t width = entry->esp - MEASURED_WIDTH;
    const uint32_t height = entry->esp - MEASURED_HEIGHT;
    port_call_with(port, MEASURE, actor, width, height, board, actor, edi, entry->ebp);
    port_set16(port, actor, ACTOR_X,
               (uint32_t)(int32_t)(int16_t)port_u16(port, actor, ACTOR_X) +
                   ((CELL - port_u32(port, width, 0)) >> 1));
    port_set16(port, actor, ACTOR_Y,
               (uint32_t)(int32_t)(int16_t)port_u16(port, actor, ACTOR_Y) +
                   ((CELL - port_u32(port, height, 0)) >> 1));
}

/* Original 0x430930 (eax = the board): lays out the board's actors. Each cell actor (+0x220, 5
 * columns of 13, 0x34 bytes a column) and cell extra (+0x87c) goes to the board's position plus
 * 0x18 per column and row plus the cell's nudges (+0x15c, +0x19d); the bottom actors (+0x988, one
 * per column) go 0x138 down with their nudges (+0x99c, +0x9a1), the left ones (+0x9e8, one per row)
 * a cell to the left (+0x9a6, +0x9b3) and the right ones (+0xa2c) 0x78 across (+0x9c0, +0x9cd);
 * each of these is centred in its cell. The four quarter actors of each cell (+0x324, 0xd0 a
 * column, 0x10 a row) go to the cell's corners, half a cell apart, uncentred. Returns 5, what the
 * original leaves in eax; no caller reads edx. */
uint32_t vertrix_port_board_layout_430930(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t board = entry->eax;
    const uint32_t tables[2] = {CELL_ACTORS, CELL_EXTRAS};
    for (unsigned t = 0; t < 2; t++)
    {
        for (uint32_t column = 0; column < COLUMNS && !port.env.failed; column++)
        {
            for (uint32_t row = 0; row < ROWS && !port.env.failed; row++)
            {
                const uint32_t actor =
                    port_u32(&port, board + column * COLUMN_STRIDE + row * 4, tables[t]);
                if (actor == 0)
                {
                    continue;
                }
                const uint32_t cell = column * ROWS + row;
                place(&port, entry, board, actor,
                      port_u16(&port, board, BOARD_X) + column * CELL +
                          nudge(&port, board, CELL_NUDGE_X, cell),
                      port_u16(&port, board, BOARD_Y) + row * CELL +
                          nudge(&port, board, CELL_NUDGE_Y, cell),
                      row);
            }
        }
    }
    for (uint32_t column = 0; column < COLUMNS && !port.env.failed; column++)
    {
        const uint32_t actor = port_u32(&port, board + column * 4, BOTTOM_ACTORS);
        if (actor != 0)
        {
            place(&port, entry, board, actor,
                  port_u16(&port, board, BOARD_X) + column * CELL +
                      nudge(&port, board, BOTTOM_NUDGE_X, column),
                  port_u16(&port, board, BOARD_Y) + BOTTOM_Y +
                      nudge(&port, board, BOTTOM_NUDGE_Y, column),
                  board + column * 4);
        }
    }
    for (uint32_t row = 0; row < ROWS && !port.env.failed; row++)
    {
        const uint32_t actor = port_u32(&port, board + row * 4, LEFT_ACTORS);
        if (actor != 0)
        {
            place(&port, entry, board, actor,
                  port_u16(&port, board, BOARD_X) - CELL + nudge(&port, board, LEFT_NUDGE_X, row),
                  port_u16(&port, board, BOARD_Y) + row * CELL +
                      nudge(&port, board, LEFT_NUDGE_Y, row),
                  row);
        }
    }
    for (uint32_t row = 0; row < ROWS && !port.env.failed; row++)
    {
        const uint32_t actor = port_u32(&port, board + row * 4, RIGHT_ACTORS);
        if (actor != 0)
        {
            place(&port, entry, board, actor,
                  port_u16(&port, board, BOARD_X) + RIGHT_X +
                      nudge(&port, board, RIGHT_NUDGE_X, row),
                  port_u16(&port, board, BOARD_Y) + row * CELL +
                      nudge(&port, board, RIGHT_NUDGE_Y, row),
                  row);
        }
    }
    for (uint32_t column = 0; column < COLUMNS && !port.env.failed; column++)
    {
        for (uint32_t row = 0; row < ROWS && !port.env.failed; row++)
        {
            const uint32_t slot = board + column * QUARTER_COLUMN + row * QUARTER_ROW;
            const uint32_t cell = column * ROWS + row;
            for (uint32_t quarter = 0; quarter < 4; quarter++)
            {
                const uint32_t actor = port_u32(&port, slot + quarter * 4, QUARTERS);
                if (actor != 0)
                {
                    port_set16(&port, actor, ACTOR_X,
                               port_u16(&port, board, BOARD_X) + column * CELL +
                                   nudge(&port, board, CELL_NUDGE_X, cell) +
                                   ((quarter & 1) ? HALF_CELL : 0));
                    port_set16(&port, actor, ACTOR_Y,
                               port_u16(&port, board, BOARD_Y) + row * CELL +
                                   nudge(&port, board, CELL_NUDGE_Y, cell) +
                                   ((quarter & 2) ? HALF_CELL : 0));
                }
            }
        }
    }
    return port_return(&port, COLUMNS, 0);
}
