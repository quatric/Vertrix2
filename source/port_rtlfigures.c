#include "port_rtlfigures.h"

/* The figure pass: same-kind shapes found on the board's 5 by 13 grid. */

enum
{
    ROWS = 5,
    COLUMNS = 13,
    MARKS = 0x5408a0,
    NEIGHBOURHOODS = 0x5408e8
};

typedef struct
{
    int8_t column;
    int8_t row;
} Offset;

typedef struct
{
    uint16_t weight;
    uint8_t count;
    Offset cells[7];
} Figure;

/* The shapes in the order the original tries them: their weights and cells (column, row). */
static const Figure FIGURES[] = {
    {7, 7, {{0, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {0, -2}, {0, 2}}},
    {6, 5, {{0, 0}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}}},
    {5, 5, {{0, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}}},
    {4, 5, {{0, 0}, {-2, -2}, {-1, -1}, {1, -1}, {2, -2}}},
    {4, 5, {{0, 0}, {-2, 2}, {-1, 1}, {1, 1}, {2, 2}}},
    {4, 5, {{0, 0}, {1, -1}, {1, 1}, {2, -2}, {2, 2}}},
    {4, 5, {{0, 0}, {-2, -2}, {-2, 2}, {-1, -1}, {-1, 1}}},
    {3, 5, {{0, 0}, {0, -2}, {0, -1}, {0, 1}, {0, 2}}},
    {2, 4, {{0, 0}, {-1, -1}, {-2, 0}, {-1, 1}}},
};

/* The neighbourhood record of the cell: 25 flags, (column + 2) * 5 + row + 2, of same-kind cells
 * within two. */
static uint32_t neighbourhood(int row, int column)
{
    return NEIGHBOURHOODS + row * 0x145 + column * 0x19;
}

static uint32_t flag_index(int column, int row)
{
    return (column + 2) * 5 + row + 2;
}

/* Whether the neighbour (a signed byte) is the cell's kind (unsigned): never for kinds of 0x80 up.
 */
static int same_kind(uint32_t kind, uint32_t neighbour)
{
    return (int32_t)(int8_t)neighbour == (int32_t)kind;
}

/* The figure tried at the cell: all its flags set (and for the last its left neighbour not), its
 * cells marked; scored (and found) when none was marked before. */
static void try_figure(Port *port, const Figure *figure, int last, int row, int column,
                       uint32_t score, uint32_t found)
{
    uint32_t record = neighbourhood(row, column);
    int32_t flags = 0;
    int32_t marked = 0;
    unsigned i;
    if (last && port_u8(port, record, flag_index(-1, 0)) != 0)
    {
        return;
    }
    for (i = 0; i < figure->count; i++)
    {
        flags += (int8_t)port_u8(port, record,
                                 flag_index(figure->cells[i].column, figure->cells[i].row));
    }
    if (flags != figure->count)
    {
        return;
    }
    for (i = 0; i < figure->count; i++)
    {
        marked += (int8_t)port_u8(
            port, MARKS, (row + figure->cells[i].row) * COLUMNS + column + figure->cells[i].column);
    }
    for (i = 0; i < figure->count; i++)
    {
        port_set8(port, MARKS,
                  (row + figure->cells[i].row) * COLUMNS + column + figure->cells[i].column, 1);
    }
    if (marked == 0)
    {
        port_set32(port, found, 0, 1);
        port_set16(port, port_u32(port, score, 0), 0,
                   port_u16(port, port_u32(port, score, 0), 0) + figure->weight);
    }
}

/* Original 0x434ee0 (one stack argument, popped: the score word's address): the board's grid eax
 * (5 rows of 13 kinds) searched for figures. The marks 0x5408a0 cleared (0x4eb5c0) and each cell's
 * neighbourhood record cleared (0x4eb5c0) and, for a kind not 0xff, 5 or 6, its flags set for the
 * same kind within two rows and columns. Then nine figures tried at every cell in turn (an X of
 * seven 7, a plus 6, an X 5, four V shapes 4, a column of five 3 and an arrow 2), each found one
 * marked and, when it overlaps no earlier one, its weight added to the score. With ecx 1 the marked
 * cells set 1 in the table edx (13 dwords a row) and turned to kind 7. eax whether one was scored,
 * edx 13. */
uint32_t vertrix_port_figure_pass_434ee0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x88
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t grid = entry->eax;
    uint32_t found = ebp - 0x7c;
    uint32_t score = ebp + 8;
    int row;
    int column;
    unsigned figure;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x84u, entry->edx);
    port_set32(&port, ebp, -0x80u, entry->ecx);
    port_set32(&port, found, 0, 0);
    port_call_with(&port, 0x4eb5c0, MARKS, 0, 0x41, entry->ecx, entry->esi, grid, ebp);
    for (row = 0; row < ROWS && !port.env.failed; row++)
    {
        for (column = 0; column < COLUMNS && !port.env.failed; column++)
        {
            uint32_t record = neighbourhood(row, column);
            uint32_t kind;
            int across;
            int down;
            port_call_with(&port, 0x4eb5c0, record, 0, 0x19, record, column, grid, ebp);
            kind = port_u8(&port, grid, row * COLUMNS + column);
            if (kind == 0xff || kind == 5 || kind == 6)
            {
                continue;
            }
            port_set8(&port, record, flag_index(0, 0), 1);
            for (across = -2; across <= 2; across++)
            {
                if (column + across < 0 || column + across >= COLUMNS)
                {
                    continue;
                }
                for (down = -2; down <= 2; down++)
                {
                    if (row + down < 0 || row + down >= ROWS)
                    {
                        continue;
                    }
                    if (same_kind(kind,
                                  port_u8(&port, grid, (row + down) * COLUMNS + column + across)))
                    {
                        port_set8(&port, record, flag_index(across, down), 1);
                    }
                }
            }
        }
    }
    for (figure = 0; figure < sizeof FIGURES / sizeof FIGURES[0]; figure++)
    {
        for (row = 0; row < ROWS && !port.env.failed; row++)
        {
            for (column = 0; column < COLUMNS && !port.env.failed; column++)
            {
                try_figure(&port, &FIGURES[figure], figure == 8, row, column, score, found);
            }
        }
    }
    if (entry->ecx == 1)
    {
        for (row = 0; row < ROWS && !port.env.failed; row++)
        {
            for (column = 0; column < COLUMNS && !port.env.failed; column++)
            {
                if (port_u8(&port, MARKS, row * COLUMNS + column) == 1)
                {
                    port_set32(&port, entry->edx + row * 0x34, column * 4, 1);
                    port_set8(&port, grid, row * COLUMNS + column, 7);
                }
            }
        }
    }
    return port_return(&port, port_u32(&port, found, 0), 0xd);
}
