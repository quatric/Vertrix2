#include "reaches.h"

/* The reach of the board's markers. */

/* Whether the reach from `from` falls short of the line's ends 0 and `last` on either side. */
static int reach_short(int32_t from, int32_t reach, int32_t last)
{
    int32_t edge = from - 1;
    int shorter = 0;
    while (edge >= 0 && edge > from - reach)
    {
        --edge;
    }
    if (edge != -1)
    {
        shorter = 1;
    }
    edge = from + 1;
    while (edge <= last && edge < reach + from)
    {
        ++edge;
    }
    if (edge != last + 1)
    {
        shorter = 1;
    }
    return shorter;
}

/* Original 0x433550: the reach of the markers of the board eax: its pick (+0x1de) taken from its
 * cells (0x4327e0 of +0x220, 0x41), the least reach from 1 up at which every marker (6) of the 5
 * by 13 pick reaches both ends of its column (the mode +0x839 1, 3 or 4) and of its row (2, 3 or
 * 4). The reach in al; the registers but eax kept. */
uint32_t vertrix_port_board_marker_reach_433550(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t reach = 0;
    uint32_t mode;
    int32_t row;
    int32_t column;
    int shorter;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, ebp, -0x18u, board);
    port_call_with(&port, 0x4327e0, board + 0x220, board + 0x1de, 0x41, entry->ecx & 0xffffff00u,
                   entry->esi, entry->edi, ebp);
    do
    {
        reach = (reach + 1) & 0xff;
        shorter = 0;
        for (row = 0; row < 5; ++row)
        {
            port_set32(&port, ebp, -0x28u, (uint32_t)row + 1);
            port_set32(&port, ebp, -0x24u, (uint32_t)row - 1);
            port_set32(&port, ebp, -0x20u, board + (uint32_t)row * 13);
            for (column = 0; column < 13; ++column)
            {
                if (port_u8(&port, board + (uint32_t)row * 13 + (uint32_t)column, 0x1de) != 6)
                {
                    continue;
                }
                mode = port_u8(&port, board, 0x839);
                if (mode == 1 || mode == 3 || mode == 4)
                {
                    shorter |= reach_short(row, (int32_t)reach, 4);
                }
                if (mode == 2 || mode == 3 || mode == 4)
                {
                    shorter |= reach_short(column, (int32_t)reach, 0xc);
                }
            }
            port_set32(&port, ebp, -0x20u, board + (uint32_t)row * 13 + 13);
            port_set32(&port, ebp, -0x1cu, board + (uint32_t)row * 13 + 13);
            port_set32(&port, ebp, -0x2cu, (uint32_t)row);
        }
    } while (shorter);
    return port_return(&port, reach, entry->edx);
}
