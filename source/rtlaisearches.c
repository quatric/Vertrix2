#include "rtlaisearches.h"

/* The computer player's figure search: for each reachable column, drops the falling piece in all
 * three rotations onto a copy of its board and keeps the best scoring one (ai_player.c has the
 * same search in plain C, vertrix_ai_search_native). */

enum
{
    /* The routine's frame under its return slot: the locals its callees reach by address. */
    BELOW = 0x194,
    MATCHES = 0x190,
    CELLS = 0x8c,
    BEST = 0x40,
    KIND = 0x48,
    REACH = 0x38,
    SCORE = 0x10,

    ARGUMENT_ROTATION = 4,
    ARGUMENT_COLUMN = 8,
    ARGUMENT_LEVEL = 0xc,
    ARGUMENT_ROW = 0x10,
    ARGUMENT_START = 0x14,
    ARGUMENT_SKILL = 0x18,
    MIN_SKILL = 2,

    PLAYER_BOARD = 0x184,
    COLUMNS = 5,
    ROWS_PER_COLUMN = 13,
    BOARD_CELLS = COLUMNS * ROWS_PER_COLUMN,
    EMPTY_CELL = 0xff,
    ROTATIONS = 3,

    MEMSET = 0x4eb5c0,
    ROW_REACH = 0x4261b0,
    FIGURE_MATCHES = 0x434ee0
};

/* Original 0x4270a0 (eax = the player, edx, ebx and ecx = the piece's three colours, top first;
 * stack: where the rotation and column go, the match level (a byte), the row, the start column and
 * the skill). Returns 1 with the best column and its rotation, or 0 when the skill is 2 or less or
 * no drop matches. The original does not check 0x4261b0's result. */
uint32_t vertrix_port_ai_search_4270a0(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8 + 4 * 6];
    Port port;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 6);
    const uint32_t frame = entry->esp - 4;
    const uint32_t cells = frame - CELLS;
    const uint32_t best = frame - BEST;
    const uint32_t kind = frame - KIND;
    const uint32_t reach = frame - REACH;
    const uint32_t score = frame - SCORE;
    const uint32_t player = entry->eax;
    const uint32_t board = player + PLAYER_BOARD;
    /* The piece's colours from the bottom cell up, for each rotation. */
    const uint32_t a = entry->edx & 0xff;
    const uint32_t b = entry->ebx & 0xff;
    const uint32_t c = entry->ecx & 0xff;
    const uint32_t colours[ROTATIONS][3] = {{c, b, a}, {a, c, b}, {b, a, c}};
    const uint32_t level = port_u8(&port, entry->esp, ARGUMENT_LEVEL);

    if (port_u32(&port, entry->esp, ARGUMENT_SKILL) <= MIN_SKILL)
    {
        return port_return(&port, 0, 0);
    }
    port_call(&port, MEMSET, best, 0, COLUMNS, 0);
    port_call(&port, MEMSET, kind, 0, COLUMNS, 0);
    port_copy(&port, cells, board, BOARD_CELLS);
    const uint32_t start = port_u32(&port, entry->esp, ARGUMENT_START);
    port_call_stack(&port, ROW_REACH, player, cells, reach,
                    port_u32(&port, entry->esp, ARGUMENT_ROW), &start, 1);

    int failed = 1;
    for (uint32_t x = 0; x < COLUMNS && !port.env.failed; x++)
    {
        if (port_u8(&port, reach, x) == 0)
        {
            continue;
        }
        port_copy(&port, cells, board, BOARD_CELLS);
        const uint32_t base = cells + x * ROWS_PER_COLUMN;
        int32_t cell = ROWS_PER_COLUMN - 1;
        while (cell >= 0 && port_u8(&port, base, (uint32_t)cell) != EMPTY_CELL && !port.env.failed)
        {
            cell--;
        }
        if (cell < 0)
        {
            continue;
        }
        for (uint32_t rotation = 0; rotation < ROTATIONS && !port.env.failed; rotation++)
        {
            for (int32_t piece = 0; piece < 3 && piece <= cell; piece++)
            {
                port_set8(&port, base, (uint32_t)(cell - piece), colours[rotation][piece]);
            }
            port_set16(&port, score, 0, 0);
            const uint32_t argument = score;
            if (port_call_stack(&port, FIGURE_MATCHES, cells, frame - MATCHES, level, 0, &argument,
                                1) == 1)
            {
                failed = 0;
                if ((int32_t)port_u16(&port, score, 0) > (int32_t)port_u8(&port, best, x))
                {
                    port_set8(&port, best, x, port_u8(&port, score, 0));
                    port_set8(&port, kind, x, rotation);
                }
            }
        }
    }
    if (failed)
    {
        return port_return(&port, 0, 0);
    }
    uint32_t column = 0;
    for (uint32_t x = 1; x < COLUMNS; x++)
    {
        if (port_u8(&port, best, x) > port_u8(&port, best, column))
        {
            column = x;
        }
    }
    port_set32(&port, port_u32(&port, entry->esp, ARGUMENT_COLUMN), 0, column);
    port_set32(&port, port_u32(&port, entry->esp, ARGUMENT_ROTATION), 0,
               port_u8(&port, kind, column));
    return port_return(&port, 1, 0);
}
