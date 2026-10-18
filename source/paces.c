#include "paces.h"

/* The motion of the board's pieces. */

/* The piece's pace (+0x4c), +0x48 cleared, its way (+0x4a) and its state (0x4ac8f0). */
static uint32_t motion_state(Port *port, uint32_t piece, uint32_t pace, uint32_t way,
                             uint32_t state, uint32_t ebx, uint32_t esi, uint32_t edi, uint32_t ebp)
{
    port_set16(port, piece, 0x4c, pace);
    port_set16(port, piece, 0x48, 0);
    port_set16(port, piece, 0x4a, way);
    port_call_with(port, 0x4ac8f0, piece, state, ebx, piece, esi, edi, ebp);
    return vertrix_lift_edx;
}

/* Original 0x438960: the motion dl of the board eax's pieces (+0x220, 5 by 13), column by
 * column, each slowed (0x4ac7b0 4, 0x4ac510) and, turn about (the first right), given: 0 the
 * state 0x44f120 right or 0x44f180 left (pace 10, way 0x64 or -0x64); 1 the state 0x44f240 left
 * (pace 8); 2 +0x80 and +0x84 cleared, +0x88 a draw (0x4826c0 of 0x598d30) plus 2, +0x8c 1 and
 * the state 0x44f390, or 0x44f3e0 when a draw below 2 is not 0; 3 and 4 +0x94 0, +0x52 0 or 1
 * and the states 0x44f4a0 and 0x44f500 (3) or 0x44f5d0 and 0x44f630 (4) as for 0. 13; ebx, ecx,
 * esi and edi kept. */
uint32_t vertrix_port_board_set_motion_438960(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t motion = entry->edx & 0xff;
    uint32_t ebx = (entry->ebx & 0xffffff00u) | motion;
    uint32_t turn = 0;
    uint32_t column;
    uint32_t row;
    uint32_t slot;
    uint32_t piece;
    uint32_t edx = entry->edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x20u, board);
    port_set32(&port, ebp, -0x24u, board);
    for (column = 0; column < 13; ++column)
    {
        port_set32(&port, ebp, -0x14u, column);
        port_set32(&port, ebp, -0x18u, 0x104 + column * 4);
        port_set32(&port, ebp, -0x1cu, board + 0x104 + column * 4);
        edx = 0x104 + column * 4;
        for (row = 0; row < 5; ++row)
        {
            slot = board + column * 4 + row * 0x34;
            piece = port_u32(&port, slot, 0x220);
            if (piece != 0 && motion <= 4)
            {
                port_call_with(&port, 0x4ac7b0, piece, 4, ebx, piece, turn, slot, ebp);
                if (motion == 2)
                {
                    port_call_with(&port, 0x4ac510, piece, 5, ebx, piece, turn, slot, ebp);
                }
                else
                {
                    port_call_with(&port, 0x4ac510, piece, vertrix_lift_edx, ebx, piece, turn, slot,
                                   ebp);
                }
                if (motion == 0)
                {
                    edx = motion_state(&port, piece, 0xa, turn == 0 ? 0x64 : 0xff9c,
                                       turn == 0 ? 0x44f120 : 0x44f180, ebx, turn, slot, ebp);
                }
                else if (motion == 1)
                {
                    edx = motion_state(&port, piece, 8, 0xff9c, 0x44f240, ebx, turn, slot, ebp);
                }
                else if (motion == 2)
                {
                    port_set32(&port, piece, 0x80, 0);
                    port_set32(&port, piece, 0x84, 0);
                    port_set32(&port, piece, 0x88,
                               (port_call_with(&port, 0x4826c0, 0x598d30, vertrix_lift_edx, ebx,
                                               piece, turn, slot, ebp) &
                                0xffff) +
                                   2);
                    port_set8(&port, piece, 0x8c, 1);
                    port_call_with(
                        &port, 0x4ac8f0, piece,
                        (port_call_with(&port, 0x4826c0, 0x598d30, 2, ebx, piece, turn, slot, ebp) &
                         0xffff) == 0
                            ? 0x44f390
                            : 0x44f3e0,
                        ebx, piece, turn, slot, ebp);
                    edx = vertrix_lift_edx;
                }
                else
                {
                    port_set8(&port, piece, 0x94, 0);
                    port_set8(&port, piece, 0x52, motion == 4);
                    if (turn == 0)
                    {
                        edx = motion_state(&port, piece, 0xa, 0x64,
                                           motion == 3 ? 0x44f4a0 : 0x44f5d0, ebx, turn, slot, ebp);
                    }
                    else
                    {
                        edx = motion_state(&port, piece, 0xa, 0xff9c,
                                           motion == 3 ? 0x44f500 : 0x44f630, ebx, turn, slot, ebp);
                    }
                }
            }
            turn = 1 - turn;
        }
    }
    port_set32(&port, ebp, -0x14u, 13);
    port_set32(&port, ebp, -0x18u, 0x138);
    return port_return(&port, 13, edx);
}
