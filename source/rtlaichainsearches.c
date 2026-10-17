#include "rtlaichainsearches.h"

/* The computer player's chain search: drops the piece in all three rotations into each reachable
 * column of a copy of its board and scores the runs it makes; from level 3 the best rotation is
 * replayed and the runs that follow the collapse are scored too (ai_player.c has the same search
 * in plain C, vertrix_ai_chain_search). */

enum
{
    /* The routine's frame under its return slot: its callees reach every local by address. */
    BELOW = 0x1b8,
    MASK = 0x1b4,
    CELLS = 0xb0,
    SECOND = 0x6c,
    THIRD = 0x64,
    BEST = 0x5c,
    REACH = 0x54,
    KIND = 0x4c,
    COUNT = 0x10,

    ARGUMENT_ROTATION = 4,
    ARGUMENT_COLUMN = 8,
    ARGUMENT_THRESHOLD = 0xc,
    ARGUMENT_START = 0x10,
    ARGUMENT_ROW = 0x14,
    ARGUMENT_LEVEL = 0x18,
    ARGUMENTS = 6,
    PAIR_LEVEL = 1,
    MIN_LEVEL = 2,
    EXTRA_LEVEL = 4,

    PLAYER_BOARD = 0x184,
    COLUMNS = 5,
    ROWS_PER_COLUMN = 13,
    BOARD_CELLS = COLUMNS * ROWS_PER_COLUMN,
    EMPTY_CELL = 0xff,
    ROTATIONS = 3,
    /* The columns tried from the outside in when no follow-up decides, and the fallback. */
    OUTER_PAIRS = 2,
    CENTER = 2,

    MEMSET = 0x4eb5c0,
    ROW_REACH = 0x4261b0,
    CLEAR_MASK = 0x432840,
    COLLAPSE = 0x432980,
    LINE_MATCHES = 0x4346b0
};

typedef struct
{
    Port *port;
    uint32_t cells;
    uint32_t mask;
    uint32_t count;
    uint32_t threshold;
} Search;

/* The line pass (0x4346b0): marks the runs in the mask. Returns 1 when it found any. */
static int lines(Search *search)
{
    return port_call(search->port, LINE_MATCHES, search->cells, search->mask, search->threshold,
                     search->count) == 1;
}

static void clear_mask(Search *search)
{
    port_call(search->port, CLEAR_MASK, search->mask, 0, 0, 0);
}

/* The marked cells (the mask holds a dword per cell). */
static uint32_t mask_sum(Search *search)
{
    uint32_t sum = 0;
    for (uint32_t i = 0; i < BOARD_CELLS; i++)
    {
        sum += port_u32(search->port, search->mask, i * 4);
    }
    return sum;
}

/* Empties the marked cells and lets the board fall (0x432980). */
static void remove_and_collapse(Search *search)
{
    for (uint32_t i = 0; i < BOARD_CELLS && !search->port->env.failed; i++)
    {
        if (port_u32(search->port, search->mask, i * 4) == 1)
        {
            port_set8(search->port, search->cells, i, EMPTY_CELL);
        }
    }
    port_call(search->port, COLLAPSE, search->cells, 0, 0, 0);
}

/* Original 0x4269e0 (eax = the player, edx, ebx and ecx = the piece's three colours, top first;
 * stack: where the rotation and column go, the run threshold (a byte), the start column, the row
 * and the level). Returns 1 with the column and its rotation, or 0 when no rotation makes a run.
 * The column is the best scoring one when no follow-up runs were found, else the outer column (or
 * the centre) whose rotation made runs: the follow-up scores pick nothing. At level 4 the chain is
 * followed without clearing the mask between rounds. The original does not check 0x4261b0's
 * result. */
uint32_t vertrix_port_ai_chain_search_4269e0(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    Port port;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    const uint32_t frame = entry->esp - 4;
    const uint32_t best = frame - BEST;
    const uint32_t kind = frame - KIND;
    const uint32_t second = frame - SECOND;
    const uint32_t third = frame - THIRD;
    const uint32_t reach = frame - REACH;
    const uint32_t player = entry->eax;
    const uint32_t board = player + PLAYER_BOARD;
    /* The piece's colours from the bottom cell up, for each rotation. */
    const uint32_t a = entry->edx & 0xff;
    const uint32_t b = entry->ebx & 0xff;
    const uint32_t c = entry->ecx & 0xff;
    const uint32_t colours[ROTATIONS][3] = {{c, b, a}, {a, c, b}, {b, a, c}};
    const uint32_t level = port_u32(&port, entry->esp, ARGUMENT_LEVEL);
    Search search = {&port, frame - CELLS, frame - MASK, frame - COUNT,
                     port_u8(&port, entry->esp, ARGUMENT_THRESHOLD)};

    int none = 1;
    port_set32(&port, search.count, 0, 0);
    port_call(&port, MEMSET, best, 0, COLUMNS, 0);
    port_call(&port, MEMSET, kind, 0, COLUMNS, 0);
    port_call(&port, MEMSET, second, 0, COLUMNS, 0);
    port_call(&port, MEMSET, third, 0, COLUMNS, 0);
    port_copy(&port, search.cells, board, BOARD_CELLS);
    const uint32_t row = port_u32(&port, entry->esp, ARGUMENT_ROW);
    port_call_stack(&port, ROW_REACH, player, search.cells, reach,
                    port_u32(&port, entry->esp, ARGUMENT_START), &row, 1);

    for (uint32_t x = 0; x < COLUMNS && !port.env.failed; x++)
    {
        if (port_u8(&port, reach, x) == 0)
        {
            continue;
        }
        port_copy(&port, search.cells, board, BOARD_CELLS);
        const uint32_t base = search.cells + x * ROWS_PER_COLUMN;
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
            clear_mask(&search);
            if (lines(&search))
            {
                const uint32_t sum = mask_sum(&search);
                if ((int32_t)sum > (int32_t)port_u8(&port, best, x))
                {
                    port_set8(&port, best, x, sum);
                    none = 0;
                    port_set8(&port, kind, x, rotation);
                }
            }
        }
        if (port_u8(&port, best, x) == 0 || level <= MIN_LEVEL)
        {
            continue;
        }

        /* Replay the best rotation, remove its runs and score what follows. */
        port_copy(&port, search.cells, board, BOARD_CELLS);
        const uint32_t chosen = port_u8(&port, kind, x);
        const uint32_t *order = colours[chosen == 0 ? 0 : chosen == 1 ? 1 : 2];
        for (int32_t piece = 0; piece < 3 && piece <= cell; piece++)
        {
            port_set8(&port, base, (uint32_t)(cell - piece), order[piece]);
        }
        clear_mask(&search);
        lines(&search);
        remove_and_collapse(&search);
        clear_mask(&search);
        if (!lines(&search))
        {
            continue;
        }
        port_set8(&port, second, x, mask_sum(&search));
        if (level != EXTRA_LEVEL)
        {
            continue;
        }
        remove_and_collapse(&search);
        clear_mask(&search);
        while (lines(&search) && !port.env.failed)
        {
            port_set8(&port, third, x, port_u8(&port, third, x) + mask_sum(&search));
            remove_and_collapse(&search);
        }
    }
    if (none)
    {
        return port_return(&port, 0, 0);
    }

    /* The follow-up scores (the original computes them and never uses the column they pick). */
    int32_t pick = -1;
    int32_t score = -1;
    if (level == EXTRA_LEVEL)
    {
        for (uint32_t x = 0; x < COLUMNS; x++)
        {
            const int32_t total = (int32_t)(port_u8(&port, third, x) + port_u8(&port, second, x) +
                                            port_u8(&port, best, x));
            if (port_u8(&port, third, x) != 0 && total > score)
            {
                score = total;
                pick = (int32_t)x;
            }
        }
    }
    if (pick == -1 && level > MIN_LEVEL)
    {
        for (uint32_t x = 0; x < COLUMNS; x++)
        {
            const int32_t total = (int32_t)(port_u8(&port, second, x) + port_u8(&port, best, x));
            if (port_u8(&port, second, x) != 0 && total > score)
            {
                score = total;
                pick = (int32_t)x;
            }
        }
    }

    int32_t column = -1;
    if (pick == -1 && level > PAIR_LEVEL)
    {
        /* The best scoring column, the first of equals. */
        column = 0;
        for (uint32_t x = 1; x < COLUMNS; x++)
        {
            if (port_u8(&port, best, x) > port_u8(&port, best, (uint32_t)column))
            {
                column = (int32_t)x;
            }
        }
    }
    else
    {
        for (uint32_t left = 0, right = COLUMNS - 1; column == -1 && left < OUTER_PAIRS;
             left++, right--)
        {
            if (port_u8(&port, best, left) != 0)
            {
                column = (int32_t)left;
            }
            else if (port_u8(&port, best, right) != 0)
            {
                column = (int32_t)right;
            }
        }
        if (column == -1)
        {
            column = CENTER;
        }
    }
    port_set32(&port, port_u32(&port, entry->esp, ARGUMENT_COLUMN), 0, (uint32_t)column);
    port_set32(&port, port_u32(&port, entry->esp, ARGUMENT_ROTATION), 0,
               port_u8(&port, kind, (uint32_t)column));
    return port_return(&port, 1, 0);
}
