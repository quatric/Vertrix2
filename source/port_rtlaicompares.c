#include "port_rtlaicompares.h"

/* The computer player's comparison of two boards. */

/* A count graded 1 to 4 by the bounds (0 below the first). */
static uint32_t grade(int32_t count, int32_t first, int32_t second, int32_t third, int32_t fourth)
{
    if (count < first)
    {
        return 0;
    }
    if (count < second)
    {
        return 1;
    }
    if (count < third)
    {
        return 2;
    }
    if (count < fourth)
    {
        return 3;
    }
    return 4;
}

/* A count of tall rows graded: none 0, under 3 1, under 5 2, 5 3; more keeps the grade. */
static uint32_t grade_tall(int32_t count, uint32_t grade)
{
    if (count == 0)
    {
        return 0;
    }
    if (count < 3)
    {
        return 1;
    }
    if (count < 5)
    {
        return 2;
    }
    if (count == 5)
    {
        return 3;
    }
    return grade;
}

/* The grade of the board, its rival's, and the lead (0 without one) at out, out + 5, out + 10. */
static void put_grades(Port *port, uint32_t out, uint32_t eax, uint32_t edx)
{
    port_set8(port, out, 0, eax);
    port_set8(port, out, 5, edx);
    port_set8(port, out, 0xa, (int32_t)eax > (int32_t)edx ? (eax - edx) & 0xff : 0);
}

/* The rows of the board (5 of 13 bytes, 0xff empty) whose first column is filled, counted from
 * the middle out: rows 1, 0 above and 3, 4 below; the first filled each side scores its
 * distance. */
static uint32_t edge_score(Port *port, uint32_t board)
{
    uint32_t score = 0;
    int32_t row;
    for (row = 1; row >= 0; row--)
    {
        if (port_u8(port, board + (uint32_t)row * 0xd, 0) != 0xff)
        {
            score += (uint32_t)row + 1;
            break;
        }
    }
    for (row = 3; row < 5; row++)
    {
        if (port_u8(port, board + (uint32_t)row * 0xd, 0) != 0xff)
        {
            score += 5 - (uint32_t)row;
            break;
        }
    }
    return score;
}

/* Original 0x428110: the boards edx (own) and ebx (rival) of the player eax compared into the
 * grades at ecx, each with the rival's and the lead: +0 the filled cells (13, 20, 26, 39), +2 the
 * rows over 6 tall (any filled first column 4), +3 the cells of kind 5 (7, 15, 20), +4 the cells
 * of kind 6 (1, 2, 3, else 4) against the rival's kind 5; +0x10/+0x11 4 with the middle row's
 * first cell filled on each board, +0x12 4 with the rival's row 1 (row 3 for a player with
 * +0x17c) first cell filled. eax the grades, edx the rival's kind 5 grade. */
uint32_t vertrix_port_ai_compare_boards_428110(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x78
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t own = entry->edx;
    uint32_t rival = entry->ebx;
    uint32_t out = entry->ecx;
    int32_t own_filled = 0;
    int32_t rival_filled = 0;
    int32_t own_fives = 0;
    int32_t rival_fives = 0;
    int32_t own_sixes = 0;
    int32_t own_tall = 0;
    int32_t rival_tall = 0;
    uint32_t own_edges;
    uint32_t rival_edges;
    uint32_t eax;
    uint32_t edx;
    uint32_t row;
    uint32_t column;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->esi);
    port_set32(&port, entry->esp, -8u, entry->edi);
    port_set32(&port, entry->esp, -0xcu, entry->ebp);
    for (row = 0; row < 5; row++)
    {
        int32_t own_height = 13;
        int32_t rival_height = 13;
        for (column = 0; column < 13 && port_u8(&port, own + row * 0xd + column, 0) == 0xff;
             column++)
        {
            own_height--;
        }
        for (column = 0; column < 13 && port_u8(&port, rival + row * 0xd + column, 0) == 0xff;
             column++)
        {
            rival_height--;
        }
        if (own_height > 6)
        {
            own_tall++;
        }
        if (rival_height > 6)
        {
            rival_tall++;
        }
    }
    for (row = 0; row < 5; row++)
    {
        for (column = 0; column < 13; column++)
        {
            uint32_t mine = port_u8(&port, own + row * 0xd + column, 0);
            uint32_t theirs = port_u8(&port, rival + row * 0xd + column, 0);
            if (mine != 0xff)
            {
                own_filled++;
            }
            if (theirs != 0xff)
            {
                rival_filled++;
            }
            if (mine == 5)
            {
                own_fives++;
            }
            else if (mine == 6)
            {
                own_sixes++;
            }
            if (theirs == 5)
            {
                rival_fives++;
            }
        }
    }
    own_edges = edge_score(&port, own);
    rival_edges = edge_score(&port, rival);
    eax = grade(own_filled, 0xd, 0x14, 0x1a, 0x27);
    edx = grade(rival_filled, 0xd, 0x14, 0x1a, 0x27);
    put_grades(&port, out, eax, edx);
    eax = own_edges != 0 ? 4 : grade_tall(own_tall, eax);
    edx = rival_edges != 0 ? 4 : grade_tall(rival_tall, edx);
    put_grades(&port, out + 2, eax, edx);
    eax = own_fives == 0 ? 0 : grade(own_fives, 1, 7, 0xf, 0x14);
    edx = rival_fives == 0 ? 0 : grade(rival_fives, 1, 7, 0xf, 0x14);
    put_grades(&port, out + 3, eax, edx);
    eax = own_sixes;
    if (eax != 0 && eax != 1 && eax != 2 && eax != 3)
    {
        eax = 4;
    }
    put_grades(&port, out + 4, eax, edx);
    port_set8(&port, out, 0x10, port_u8(&port, own, 0x1a) != 0xff ? 4 : 0);
    port_set8(&port, out, 0x11, port_u8(&port, rival, 0x1a) != 0xff ? 4 : 0);
    if (port_u8(&port, entry->eax, 0x17c) == 0)
    {
        port_set8(&port, out, 0x12, port_u8(&port, rival, 0xd) != 0xff ? 4 : 0);
    }
    else
    {
        port_set8(&port, out, 0x12, port_u8(&port, rival, 0x27) != 0xff ? 4 : 0);
    }
    return port_return(&port, out, edx);
}
