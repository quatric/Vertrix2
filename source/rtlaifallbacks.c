#include "rtlaifallbacks.h"

/* The computer player's fallback when no figure move is found: picks the lowest reachable column
 * (the outer columns first, a tie settled by the last pick or a coin), then a rotation from a pair
 * in the piece or from the colours beside the landing cell, else a random one (ai_player.c has the
 * same search in plain C, vertrix_ai_fallback). */

enum
{
    /* The routine's frame under its return slot: the arrays its callees fill or that it indexes
     * with the column it stored, at the original's offsets. */
    BELOW = 0x9c,
    HEIGHTS = 0x44,
    UNUSED_A = 0x54,
    UNUSED_B = 0x4c,
    REACH = 0x3c,
    CELLS = 0x98,

    ARGUMENT_ROTATION = 4,
    ARGUMENT_COLUMN = 8,
    ARGUMENT_START = 0x10,
    ARGUMENT_ROW = 0x14,
    ARGUMENT_LEVEL = 0x18,
    ARGUMENTS = 6,

    PLAYER_PREVIOUS = 0x180,
    PLAYER_BOARD = 0x184,
    COLUMNS = 5,
    ROWS_PER_COLUMN = 13,
    BOARD_CELLS = COLUMNS * ROWS_PER_COLUMN,
    EMPTY_CELL = 0xff,
    ABSENT = 0xfe,
    FULL_HEIGHT = 13,
    CENTRE = 2,
    CENTRE_MIN_EMPTY = 3,
    LAST_ROW = 12,

    PAIR_LEVEL = 1,
    NEIGHBOUR_LEVEL = 2,
    EXTRA_LEVEL = 4,

    RANDOM_STATE = 0x598d48,
    FILL = 0x4eb5c0,
    ROW_REACH = 0x4261b0,
    RANDOM_BELOW = 0x4826c0
};

/* The cells beside the landing row r: the left column's rows r-3 .. r+1, then the right
 * column's. */
enum
{
    L3,
    L2,
    L1,
    L0,
    LP,
    R3,
    R2,
    R1,
    R0,
    RP,
    NEIGHBOURS
};

/* One test: when the condition cell holds a colour (a signed byte above -1) and the empty cell is
 * empty, the value cell, sign-extended, is compared with the piece's three colours in order, and
 * the first equal one gives its rotation. */
typedef struct
{
    uint8_t condition;
    uint8_t empty;
    uint8_t value;
    uint8_t rotations[3];
} NeighbourTest;

/* Original 0x4263cb..0x4264e4: the tests at levels above 2. The sixth compares the right column's
 * landing cell without checking that it holds a colour. */
static const NeighbourTest TESTS[] = {{L2, R2, L2, {0, 1, 2}}, {R2, L2, R2, {0, 1, 2}},
                                      {L1, R1, L1, {2, 0, 1}}, {R1, L1, R1, {2, 0, 1}},
                                      {L0, R0, L0, {1, 2, 0}}, {R1, L1, R0, {1, 2, 0}}};

/* Original 0x426519..0x4267a3: the tests at level 4 only. */
static const NeighbourTest EXTRA_TESTS[] = {
    {L3, R1, L3, {0, 1, 2}}, {R1, L3, R1, {0, 1, 2}}, {L2, R0, L2, {2, 0, 1}},
    {R0, L2, R0, {2, 0, 1}}, {L1, RP, L1, {1, 2, 0}}, {RP, L1, RP, {1, 2, 0}},
    {R3, L1, R3, {0, 1, 2}}, {L1, R3, L1, {0, 1, 2}}, {R2, L0, R2, {2, 0, 1}},
    {L0, R2, L0, {2, 0, 1}}, {R1, LP, R1, {1, 2, 0}}, {LP, R1, LP, {1, 2, 0}}};

static uint32_t sign_extend(uint8_t value)
{
    return (uint32_t)(int32_t)(int8_t)value;
}

/* The rotation the first passing test gives, or -1. */
static uint32_t neighbour_rotation(const NeighbourTest *tests, size_t count,
                                   const uint8_t cells[NEIGHBOURS], const uint32_t piece[3])
{
    for (size_t t = 0; t < count; t++)
    {
        const NeighbourTest *test = &tests[t];
        if ((int8_t)cells[test->condition] <= -1 || cells[test->empty] != EMPTY_CELL)
        {
            continue;
        }
        for (unsigned i = 0; i < 3; i++)
        {
            if (sign_extend(cells[test->value]) == piece[i])
            {
                return test->rotations[i];
            }
        }
    }
    return 0xffffffffu;
}

/* Original 0x4267d1..0x426850: the column for a board with at least one viable column. The lowest
 * reachable height wins (heights of the full and unreachable columns are 13); among the columns
 * at that height the outer pairs (0 and 4, then 1 and 3) are tried first, a tie going to the
 * previous pick (+0x180) or by random(2), and the centre last. */
static uint32_t pick_column(Port *port, uint32_t player, uint32_t heights, uint32_t reach)
{
    uint32_t best = 0;
    uint32_t low;
    uint32_t fallback;
    while (best < COLUMNS && port_u8(port, heights, best) == FULL_HEIGHT)
    {
        best++;
    }
    if (best == COLUMNS)
    {
        fallback = CENTRE;
        low = LAST_ROW;
    }
    else
    {
        fallback = best;
        low = port_u8(port, heights, best);
        for (uint32_t x = best + 1; x < COLUMNS; x++)
        {
            if (port_u8(port, reach, x) != 0 && port_u8(port, heights, x) < low)
            {
                fallback = x;
                low = port_u8(port, heights, x);
            }
        }
    }
    uint32_t pick = 0xffffffffu;
    uint32_t left = 0;
    uint32_t right = COLUMNS - 1;
    do
    {
        if (port_u8(port, heights, left) == low)
        {
            pick = left;
        }
        if (port_u8(port, heights, right) == low)
        {
            if (pick == 0xffffffffu)
            {
                pick = right;
            }
            else
            {
                const uint32_t previous = port_u32(port, player, PLAYER_PREVIOUS);
                if (right == previous)
                {
                    pick = previous;
                }
                else if (left != previous &&
                         (port_call(port, RANDOM_BELOW, RANDOM_STATE, 2, 0, 0) & 0xffff) == 1)
                {
                    pick = right;
                }
            }
        }
        right--;
        left++;
    } while (pick == 0xffffffffu && left < 2);
    if (pick == 0xffffffffu && fallback == CENTRE)
    {
        pick = CENTRE;
    }
    return pick;
}

/* Original 0x426240 (eax = the player, edx, ebx and ecx = the piece's three colours; stack: where
 * the rotation and the column go, an unused dword, the start column, the row and the AI level;
 * ret 0x18). Stores the column in +0x180 and the column output (2 when no column is viable: the
 * centre counts as full with three or fewer empty cells), then returns the rotation it also
 * stores: the colour that a pair shares at levels above 1, the neighbour tests at levels above 2
 * when the landing row is above 2, else random(3). The original ignores 0x4261b0's result, reads
 * the column back through its output, and takes the right column's cell under the landing row as
 * absent always. */
uint32_t vertrix_port_ai_fallback_426240(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    Port port;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    const uint32_t frame = entry->esp - 4;
    const uint32_t heights = frame - HEIGHTS;
    const uint32_t reach = frame - REACH;
    const uint32_t cells = frame - CELLS;
    const uint32_t player = entry->eax;
    const uint32_t piece[3] = {entry->edx, entry->ebx, entry->ecx};
    const uint32_t column_out = port_u32(&port, entry->esp, ARGUMENT_COLUMN);
    const uint32_t level = port_u32(&port, entry->esp, ARGUMENT_LEVEL);
    uint32_t rotation = 0xffffffffu;

    port_call(&port, FILL, heights, 0, COLUMNS, 0);
    port_call(&port, FILL, frame - UNUSED_A, 0, COLUMNS, 0);
    port_call(&port, FILL, frame - UNUSED_B, 0, COLUMNS, 0);
    port_copy(&port, cells, player + PLAYER_BOARD, BOARD_CELLS);
    const uint32_t row = port_u32(&port, entry->esp, ARGUMENT_ROW);
    port_call_stack(&port, ROW_REACH, 0, cells, reach, port_u32(&port, entry->esp, ARGUMENT_START),
                    &row, 1);

    uint32_t viable = 0;
    for (uint32_t x = 0; x < COLUMNS && !port.env.failed; x++)
    {
        port_set8(&port, heights, x, FULL_HEIGHT);
        if (port_u8(&port, reach, x) == 0)
        {
            continue;
        }
        const uint32_t column = cells + x * ROWS_PER_COLUMN;
        for (uint32_t y = 0; y < ROWS_PER_COLUMN && port_u8(&port, column, y) == EMPTY_CELL; y++)
        {
            port_set8(&port, heights, x, port_u8(&port, heights, x) - 1);
        }
        const int32_t empty = FULL_HEIGHT - (int32_t)port_u8(&port, heights, x);
        if (x == CENTRE && empty <= CENTRE_MIN_EMPTY)
        {
            port_set8(&port, heights, x, FULL_HEIGHT);
        }
        else if (port_u8(&port, heights, x) != FULL_HEIGHT)
        {
            viable++;
        }
    }
    if (viable == 0)
    {
        port_set32(&port, column_out, 0, CENTRE);
    }
    else
    {
        const uint32_t pick = pick_column(&port, player, heights, reach);
        port_set32(&port, player, PLAYER_PREVIOUS, pick);
        port_set32(&port, column_out, 0, pick);
    }

    if (level > PAIR_LEVEL)
    {
        if (piece[0] == piece[1])
        {
            rotation = 0;
        }
        else if (piece[1] == piece[2])
        {
            rotation = 1;
        }
        else if (piece[2] == piece[0])
        {
            rotation = 2;
        }
    }
    if (rotation == 0xffffffffu && level > NEIGHBOUR_LEVEL)
    {
        const uint32_t chosen = port_u32(&port, column_out, 0);
        const int32_t r = LAST_ROW - (int32_t)port_u8(&port, heights, chosen);
        if (r > NEIGHBOUR_LEVEL)
        {
            uint8_t near[NEIGHBOURS];
            for (unsigned i = 0; i < NEIGHBOURS; i++)
            {
                near[i] = ABSENT;
            }
            if (chosen != 0)
            {
                const uint32_t landing = (chosen - 1) * ROWS_PER_COLUMN + (uint32_t)r;
                if (r > 3)
                {
                    near[L3] = (uint8_t)port_u8(&port, cells, landing - 3);
                }
                near[L2] = (uint8_t)port_u8(&port, cells, landing - 2);
                near[L1] = (uint8_t)port_u8(&port, cells, landing - 1);
                near[L0] = (uint8_t)port_u8(&port, cells, landing);
                if (r < LAST_ROW)
                {
                    near[LP] = (uint8_t)port_u8(&port, cells, landing + 1);
                }
            }
            if (chosen != COLUMNS - 1)
            {
                const uint32_t landing = (chosen + 1) * ROWS_PER_COLUMN + (uint32_t)r;
                if (r > 3)
                {
                    near[R3] = (uint8_t)port_u8(&port, cells, landing - 3);
                }
                near[R2] = (uint8_t)port_u8(&port, cells, landing - 2);
                near[R1] = (uint8_t)port_u8(&port, cells, landing - 1);
                near[R0] = (uint8_t)port_u8(&port, cells, landing);
                if (r > LAST_ROW)
                {
                    near[RP] = (uint8_t)port_u8(&port, cells, landing + 1);
                }
            }
            rotation = neighbour_rotation(TESTS, sizeof TESTS / sizeof TESTS[0], near, piece);
            if (rotation == 0xffffffffu && level == EXTRA_LEVEL)
            {
                rotation = neighbour_rotation(
                    EXTRA_TESTS, sizeof EXTRA_TESTS / sizeof EXTRA_TESTS[0], near, piece);
            }
        }
    }
    if (rotation == 0xffffffffu)
    {
        rotation = port_call(&port, RANDOM_BELOW, RANDOM_STATE, 3, 0, 0) & 0xffff;
    }
    port_set32(&port, port_u32(&port, entry->esp, ARGUMENT_ROTATION), 0, rotation);
    return port_return(&port, rotation, 0);
}
