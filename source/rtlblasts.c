#include "rtlblasts.h"

/* A board's bombs set off. */

/* A call that leaves its edx in *edx; the eax. */
static uint32_t blast_call(Port *port, uint32_t *edx, uint32_t target, uint32_t eax, uint32_t d,
                           uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp)
{
    uint32_t result;
    result = port_call_registers(port, target, eax, d, ebx, ecx, esi, edi, ebp, NULL, 0);
    *edx = vertrix_lift_edx;
    return result;
}

static void mark(Port *port, int32_t row, int32_t column)
{
    port_set8(port, 0, 0x540858 + (uint32_t)(row * 13 + column), 1);
}

/* The column of the row marked from column - 1 leftwards, then from column + 1 rightwards, each
 * while within reach and the board; true when one side stopped short of the edge. */
static int mark_across(Port *port, int32_t row, int32_t column, int32_t reach)
{
    int short_of = 0;
    int32_t at = column - 1;
    while (at >= 0 && at > column - reach)
    {
        mark(port, row, at);
        at--;
    }
    if (at != -1)
    {
        short_of = 1;
    }
    at = column + 1;
    while (at <= 12 && at < column + reach)
    {
        mark(port, row, at);
        at++;
    }
    if (at != 13)
    {
        short_of = 1;
    }
    return short_of;
}

/* Original 0x433e20: the bombs (+0x1de cells of kind 6) of the board eax set off. Its rows
 * (0x4327e0 of +0x220 and +0x1de, 0x41) settled, the marks 0x540858 (5 by 13) cleared; each bomb
 * marks its cell and by the board's kind +0x839 its reach +0x838: 1, 3 and 4 up and down the
 * column, 2, 3 and 4 along the row, 4 also along the rows above and below; a reach stopped short
 * of the edge is noted. The parts +0x734 (5 by 13 by 4) emptied (0xff), each marked cell blown
 * (0x433180 with the row and column), the board redrawn (0x42eee0) and a piece made (0x430850)
 * for every part now filled, kept at +0x324 (by 0xd0, 0x10 and 4) with +0x48 0, +0x93 1 and +0x4e
 * 60. eax 1 with a reach noted short, else 0; edx kept. */
uint32_t vertrix_port_board_bombs_433e20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x88
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t piece;
    uint32_t part;
    int32_t row;
    int32_t column;
    int32_t reach;
    int32_t at;
    int short_of = 0;
    unsigned kind;
    unsigned sub;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    blast_call(&port, &edx, 0x4327e0, board + 0x220, board + 0x1de, 0x41, 0, board, entry->edi,
               ebp);
    for (row = 0; row < 5; row++)
    {
        for (column = 0; column < 13; column++)
        {
            port_set8(&port, 0, 0x540858 + (uint32_t)(row * 13 + column), 0);
        }
    }
    for (row = 0; row < 5 && !port.env.failed; row++)
    {
        for (column = 0; column < 13 && !port.env.failed; column++)
        {
            if (port_u8(&port, board + (uint32_t)(row * 13 + column), 0x1de) != 6)
            {
                continue;
            }
            mark(&port, row, column);
            kind = port_u8(&port, board, 0x839);
            if (kind == 1 || kind == 3 || kind == 4)
            {
                reach = (int32_t)port_u8(&port, board, 0x838);
                at = row - 1;
                while (at >= 0 && at > row - reach)
                {
                    mark(&port, at, column);
                    at--;
                }
                if (at != -1)
                {
                    short_of = 1;
                }
                at = row + 1;
                while (at <= 4 && at < row + (int32_t)port_u8(&port, board, 0x838))
                {
                    mark(&port, at, column);
                    at++;
                }
                if (at != 5)
                {
                    short_of = 1;
                }
            }
            kind = port_u8(&port, board, 0x839);
            if (kind == 2 || kind == 3 || kind == 4)
            {
                if (mark_across(&port, row, column, (int32_t)port_u8(&port, board, 0x838)))
                {
                    short_of = 1;
                }
            }
            if (port_u8(&port, board, 0x839) != 4)
            {
                continue;
            }
            if (row > 0 &&
                mark_across(&port, row - 1, column, (int32_t)port_u8(&port, board, 0x838)))
            {
                short_of = 1;
            }
            if (row < 4 &&
                mark_across(&port, row + 1, column, (int32_t)port_u8(&port, board, 0x838)))
            {
                short_of = 1;
            }
        }
    }
    for (part = 0; part < 0x104; part++)
    {
        port_set8(&port, board + part, 0x734, 0xff);
    }
    edx = 0;
    for (row = 0; row < 5 && !port.env.failed; row++)
    {
        for (column = 0; column < 13 && !port.env.failed; column++)
        {
            if (port_u8(&port, 0, 0x540858 + (uint32_t)(row * 13 + column)) != 0)
            {
                blast_call(&port, &edx, 0x433180, board, (uint32_t)row, (uint32_t)column, 0x540858,
                           board, (uint32_t)(row * 13 + column), ebp);
            }
        }
    }
    blast_call(&port, &edx, 0x42eee0, board, edx, 5, 65, board, 65, ebp);
    for (row = 0; row < 5 && !port.env.failed; row++)
    {
        for (column = 0; column < 13 && !port.env.failed; column++)
        {
            uint32_t cell = board + (uint32_t)row * 0x34 + (uint32_t)column * 4;
            ebx = board + (uint32_t)row * 0xd0 + (uint32_t)column * 0x10;
            for (sub = 0; sub < 4 && !port.env.failed; sub++, ebx += 4)
            {
                uint32_t value = port_u8(&port, cell + sub, 0x734);
                if (value == 0xff)
                {
                    continue;
                }
                piece = blast_call(&port, &edx, 0x430850, board, (uint32_t)(int32_t)(int8_t)value,
                                   ebx, sub, board, cell, ebp);
                port_set16(&port, piece, 0x48, 0);
                port_set8(&port, piece, 0x93, 1);
                port_set8(&port, piece, 0x4e, 0x3c);
                port_set32(&port, ebx, 0x324, piece);
            }
        }
    }
    return port_return(&port, short_of ? 1u : 0u, entry->edx);
}

static uint32_t extend8(uint32_t value)
{
    return (uint32_t)(int32_t)(int8_t)(value & 0xffu);
}

/* The tracked registers of 0x433840 and its flag of a reach stopped short. */
typedef struct
{
    Port *port;
    uint32_t board;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edi;
    uint32_t ebp;
    int short_of;
} Reach;

/* A reach stopped short at the row edx and column ebx reported (0x433750). */
static void report(Reach *r)
{
    r->short_of = 1;
    r->eax = blast_call(r->port, &r->edx, 0x433750, r->board, r->edx, r->ebx, r->ecx, r->board,
                        r->edi, r->ebp);
}

/* The row (13 cells from base) marked in 0x540810 from column - 1 leftwards and from column + 1
 * rightwards while within reach; a side stopped short of the edge reported with the row byte. */
static void reach_across(Reach *r, uint32_t base, uint32_t column, uint32_t row_byte)
{
    Port *port = r->port;
    r->eax = column - 1;
    if ((int32_t)r->eax >= 0)
    {
        r->ecx = base + r->eax;
        do
        {
            r->edx = port_u8(port, r->board, 0x838);
            r->ebx = column - r->edx;
            if ((int32_t)r->eax <= (int32_t)r->ebx)
            {
                break;
            }
            r->ecx--;
            r->edx = (r->edx & ~0xffu) | 1;
            r->eax--;
            port_set8(port, r->ecx, 0x540811, 1);
        } while ((int32_t)r->eax >= 0);
    }
    if (r->eax != 0xffffffffu)
    {
        r->edx = (r->edx & ~0xff00u) | 0x100;
        r->ebx = extend8(r->eax);
        r->edx = extend8(row_byte);
        report(r);
    }
    r->eax = column + 1;
    if ((int32_t)r->eax <= 0xc)
    {
        r->ecx = base + r->eax;
        do
        {
            r->ebx = column;
            r->edx = port_u8(port, r->board, 0x838) + r->ebx;
            if ((int32_t)r->eax >= (int32_t)r->edx)
            {
                break;
            }
            r->ecx++;
            r->ebx = (r->ebx & ~0xffu) | 1;
            r->eax++;
            port_set8(port, r->ecx, 0x54080f, 1);
        } while ((int32_t)r->eax <= 0xc);
    }
    if (r->eax != 0xd)
    {
        r->ebx = (r->ebx & ~0xff00u) | 0x100;
        r->edx = extend8(row_byte);
        r->ebx = extend8(r->eax);
        report(r);
    }
}

/* The bomb at the row and column of 0x433840 set off (see there). */
static void reach_bomb(Reach *r, uint32_t row, uint32_t column)
{
    Port *port = r->port;
    uint32_t kind;
    port_set8(port, 0, 0x540810 + r->edi, 1);
    if (port_u8(port, r->board, 0x838) == 0)
    {
        r->ebx = extend8(column);
        r->edx = extend8(row);
        r->eax = blast_call(port, &r->edx, 0x433750, r->board, r->edx, r->ebx, r->ecx, r->board,
                            r->edi, r->ebp);
    }
    kind = port_u8(port, r->board, 0x839);
    r->eax = (r->eax & ~0xffu) | kind;
    if (kind == 1 || kind == 3 || kind == 4)
    {
        r->eax = row - 1;
        if ((int32_t)r->eax >= 0)
        {
            r->ecx = (row - 1) * 0xd + column;
            do
            {
                r->edx = port_u8(port, r->board, 0x838);
                r->ebx = row - r->edx;
                if ((int32_t)r->eax <= (int32_t)r->ebx)
                {
                    break;
                }
                r->ecx -= 0xd;
                r->edx = (r->edx & ~0xff00u) | 0x100;
                r->eax--;
                port_set8(port, r->ecx, 0x54081d, 1);
            } while ((int32_t)r->eax >= 0);
        }
        if (r->eax != 0xffffffffu)
        {
            r->ebx = (r->ebx & ~0xffu) | 1;
            r->edx = extend8(r->eax);
            r->ebx = extend8(column);
            report(r);
        }
        r->eax = row + 1;
        if ((int32_t)r->eax <= 4)
        {
            r->ecx = (row + 1) * 0xd + column;
            do
            {
                r->ebx = row;
                r->edx = port_u8(port, r->board, 0x838) + r->ebx;
                if ((int32_t)r->eax >= (int32_t)r->edx)
                {
                    break;
                }
                r->ecx += 0xd;
                r->ebx = (r->ebx & ~0xff00u) | 0x100;
                r->eax++;
                port_set8(port, r->ecx, 0x540803, 1);
            } while ((int32_t)r->eax <= 4);
        }
        if (r->eax != 5)
        {
            r->ecx = (r->ecx & ~0xffu) | 1;
            r->ebx = extend8(column);
            r->edx = extend8(r->eax);
            report(r);
        }
    }
    kind = port_u8(port, r->board, 0x839);
    r->ecx = (r->ecx & ~0xff00u) | (kind << 8);
    if (kind == 2 || kind == 3 || kind == 4)
    {
        reach_across(r, row * 0xd, column, row);
    }
    if (port_u8(port, r->board, 0x839) != 4)
    {
        return;
    }
    if ((int32_t)row > 0)
    {
        reach_across(r, (row - 1) * 0xd, column, row - 1);
    }
    if ((int32_t)row < 4)
    {
        reach_across(r, (row + 1) * 0xd, column, row + 1);
    }
}

/* Original 0x433840: 0x433e20 with the marks at 0x540810, each bomb's reach reported (0x433750
 * with its row and column) when the board has none (+0x838 0) and where a reach stops short of
 * the edge. eax 1 with a reach stopped short, else 0; edx kept. */
uint32_t vertrix_port_board_bombs_reported_433840(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x9c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    Reach r;
    uint32_t row;
    uint32_t column;
    uint32_t part;
    uint32_t piece;
    unsigned sub;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    r.port = &port;
    r.board = entry->eax;
    r.ebp = entry->esp - 4;
    r.short_of = 0;
    port_set32(&port, r.ebp, 0, entry->ebp);
    port_set32(&port, r.ebp, -4u, entry->ebx);
    port_set32(&port, r.ebp, -8u, entry->ecx);
    port_set32(&port, r.ebp, -0xcu, entry->edx);
    port_set32(&port, r.ebp, -0x10u, entry->esi);
    port_set32(&port, r.ebp, -0x14u, entry->edi);
    blast_call(&port, &r.edx, 0x4327e0, r.board + 0x220, r.board + 0x1de, 0x41, 0, r.board,
               entry->edi, r.ebp);
    for (part = 0; part < 0x41; part++)
    {
        port_set8(&port, 0, 0x540810 + part, 0);
    }
    for (row = 0; row < 5 && !port.env.failed; row++)
    {
        r.ecx = row - 1;
        for (column = 0; column < 13 && !port.env.failed; column++)
        {
            r.edi = row * 0xd + column;
            if (port_u8(&port, r.board + r.edi, 0x1de) == 6)
            {
                reach_bomb(&r, row, column);
            }
        }
    }
    for (part = 0; part < 0x104; part++)
    {
        port_set8(&port, r.board + part, 0x734, 0xff);
    }
    r.edx = 0;
    for (row = 0; row < 5 && !port.env.failed; row++)
    {
        for (column = 0; column < 13 && !port.env.failed; column++)
        {
            if (port_u8(&port, 0, 0x540810 + row * 13 + column) != 0)
            {
                blast_call(&port, &r.edx, 0x433180, r.board, row, column, 0x540810, r.board,
                           row * 13 + column, r.ebp);
            }
        }
    }
    blast_call(&port, &r.edx, 0x42eee0, r.board, r.edx, 5, 65, r.board, 65, r.ebp);
    for (row = 0; row < 5 && !port.env.failed; row++)
    {
        for (column = 0; column < 13 && !port.env.failed; column++)
        {
            uint32_t cell = r.board + row * 0x34 + column * 4;
            uint32_t ebx = r.board + row * 0xd0 + column * 0x10;
            for (sub = 0; sub < 4 && !port.env.failed; sub++, ebx += 4)
            {
                uint32_t value = port_u8(&port, cell + sub, 0x734);
                if (value == 0xff)
                {
                    continue;
                }
                piece = blast_call(&port, &r.edx, 0x430850, r.board, extend8(value), ebx, sub,
                                   r.board, cell, r.ebp);
                port_set16(&port, piece, 0x48, 0);
                port_set8(&port, piece, 0x93, 1);
                port_set8(&port, piece, 0x4e, 0x3c);
                port_set32(&port, ebx, 0x324, piece);
            }
        }
    }
    return port_return(&port, r.short_of ? 1u : 0u, entry->edx);
}
