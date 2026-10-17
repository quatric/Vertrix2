#include "rtlaibombsearches.h"

/* The computer player's bomb search: for each reachable column, drops a piece holding a bomb in
 * all three rotations onto a copy of its board and keeps the placement whose blast is best
 * (ai_player.c has the same search in plain C, vertrix_ai_bomb_search). */

enum
{
    /* The routine's frame under its return slot: the locals its callees reach by address. */
    BELOW = 0x98,
    CELLS = 0x94,
    REACH = 0x50,
    COUNT = 0x44,
    STONES = 0x40,

    ARGUMENT_ROTATION = 4,
    ARGUMENT_COLUMN = 8,
    ARGUMENT_START = 0x10,
    ARGUMENT_ROW = 0x14,
    ARGUMENT_LEVEL = 0x18,
    ARGUMENT_PATTERN = 0x1c,
    ARGUMENT_MODE = 0x20,
    ARGUMENTS = 8,
    PAIR_LEVEL = 1,
    STONE_LEVEL = 2,
    /* Mode 0x23: the fewest cells in the blast wins. */
    FEWEST_MODE = 0x23,
    FEWEST_START = 10000,

    PLAYER_BOARD = 0x184,
    COLUMNS = 5,
    ROWS_PER_COLUMN = 13,
    BOARD_CELLS = COLUMNS * ROWS_PER_COLUMN,
    EMPTY_CELL = 0xff,
    BOMB_CELL = 6,
    ROTATIONS = 3,
    /* For the vertical patterns: a centre column higher than eight cells, with no bomb in it. */
    HEIGHT_COLUMN = 2,
    HEIGHT_LIMIT = 8,

    ROW_REACH = 0x4261b0,
    BLAST_TALLY = 0x434300,
    BLAST_COUNT = 0x4344e0
};

/* Original 0x427380 (eax = the player, edx, ebx and ecx = the piece's three colours, top first;
 * stack: where the rotation and column go, an unused dword, the start column, the row, the AI
 * level, the bomb pattern (its low byte, signed) and the mode). Returns 1 with the column and
 * rotation, or 0 (outputs untouched) for a level of 1 or less or a piece without a bomb. The
 * original copies the board before testing the mode, and does not check 0x4261b0's result. */
uint32_t vertrix_port_ai_bomb_search_427380(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    Port port;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    const uint32_t frame = entry->esp - 4;
    const uint32_t cells = frame - CELLS;
    const uint32_t reach = frame - REACH;
    const uint32_t count = frame - COUNT;
    const uint32_t stones = frame - STONES;
    const uint32_t player = entry->eax;
    const uint32_t board = player + PLAYER_BOARD;
    /* The piece's colours from the bottom cell up, for each rotation. */
    const uint32_t a = entry->edx & 0xff;
    const uint32_t b = entry->ebx & 0xff;
    const uint32_t c = entry->ecx & 0xff;
    const uint32_t colours[ROTATIONS][3] = {{c, b, a}, {a, c, b}, {b, a, c}};
    const uint32_t level = port_u32(&port, entry->esp, ARGUMENT_LEVEL);

    if (level <= PAIR_LEVEL ||
        (entry->edx != BOMB_CELL && entry->ebx != BOMB_CELL && entry->ecx != BOMB_CELL))
    {
        return port_return(&port, 0, 0);
    }
    port_copy(&port, cells, board, BOARD_CELLS);
    const int fewest = port_u32(&port, entry->esp, ARGUMENT_MODE) == FEWEST_MODE;
    const uint32_t pattern =
        (uint32_t)(int32_t)(int8_t)port_u8(&port, entry->esp, ARGUMENT_PATTERN);
    if (!fewest && (pattern & 0xff) >= 2 && (pattern & 0xff) <= 3)
    {
        const uint32_t centre = cells + HEIGHT_COLUMN * ROWS_PER_COLUMN;
        int32_t top = ROWS_PER_COLUMN - 1;
        int bomb = 0;
        if (port_u8(&port, centre, (uint32_t)top) != EMPTY_CELL)
        {
            do
            {
                if (port_u8(&port, centre, (uint32_t)top) == BOMB_CELL)
                {
                    bomb = 1;
                }
                top--;
            } while (top >= 0 && port_u8(&port, centre, (uint32_t)top) != EMPTY_CELL);
        }
        if (!bomb && top > -1 && ROWS_PER_COLUMN - 1 - top > HEIGHT_LIMIT)
        {
            port_set32(&port, port_u32(&port, entry->esp, ARGUMENT_COLUMN), 0, HEIGHT_COLUMN);
            port_set32(&port, port_u32(&port, entry->esp, ARGUMENT_ROTATION), 0, 0);
            return port_return(&port, 1, 0);
        }
    }

    const uint32_t row = port_u32(&port, entry->esp, ARGUMENT_ROW);
    port_call_stack(&port, ROW_REACH, player, cells, reach,
                    port_u32(&port, entry->esp, ARGUMENT_START), &row, 1);
    int32_t best = fewest ? FEWEST_START : 0;
    uint32_t best_column = 0;
    uint32_t best_rotation = 0;
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
            int better;
            if (fewest)
            {
                /* The cells inside the blast: the fewest wins. */
                port_call(&port, BLAST_COUNT, cells, count, pattern, 0);
                const int32_t value = (int32_t)port_u32(&port, count, 0);
                better = value < best;
                best = better ? value : best;
            }
            else
            {
                /* The blasted cells, plus twice the blasted stones from level 3. */
                port_call(&port, BLAST_TALLY, cells, count, stones, pattern);
                int32_t value = (int32_t)port_u32(&port, stones, 0);
                if (level > STONE_LEVEL)
                {
                    value = (int32_t)port_u32(&port, count, 0) * 2 +
                            (int32_t)port_u32(&port, stones, 0);
                }
                better = value > best;
                best = better ? value : best;
            }
            if (better)
            {
                best_column = x;
                best_rotation = rotation;
            }
        }
    }
    port_set32(&port, port_u32(&port, entry->esp, ARGUMENT_COLUMN), 0, best_column);
    port_set32(&port, port_u32(&port, entry->esp, ARGUMENT_ROTATION), 0, best_rotation);
    return port_return(&port, 1, 0);
}
