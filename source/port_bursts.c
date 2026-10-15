#include "port_bursts.h"

/* The board's bursts of pieces. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* Original 0x4302a0: the match burst of the board eax at the cell edx, ebx (scaled by 0x18):
 * one draw (0x4826c0 of 0x598d30) below 0x168 gives the first angle and one below 2, plus 3,
 * the speed; eight pieces (0x15c bytes, 0x4ca000, 0x4abd70) are made (0x4adf20 with five zeros)
 * at the board's +0xe and +0x16 plus the cell plus 0xc, stepped (0x4ac470 1), timed (0x4ac7b0
 * 1, 0x4ac840 2), given the image 0x54651c (0x4ac8d0), a frame drawn below 0x20 (0x4ac710), the
 * angle (0x4ac8a0, +0x94 1) and +0x24 the remainder below 0x168 of the edx it leaves, +0x95 4,
 * +0x48 0, +0x4e 0x32, +0x93 1, +0x28 the speed, placed (0x4ad510), +0x30 0x64, +0x32 1, the
 * state 0x444700 (0x4ac8f0), and added to the list +0xcec (0x4b5e70); each angle 0x2d past the
 * last. The last add's result. */
uint32_t vertrix_port_match_burst_4302a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t across = entry->edx * 0x18;
    uint32_t down = entry->ebx * 0x18;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t list = board + 0xcec;
    uint32_t angle;
    uint32_t speed;
    uint32_t count;
    uint32_t piece;
    uint32_t frame;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t eax = 0;
    int32_t rest;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x1cu, board);
    angle = port_call_with(&port, 0x4826c0, 0x598d30, 0x168, down, across, entry->esi, entry->edi,
                           ebp) &
            0xffff;
    speed = port_call_with(&port, 0x4826c0, 0x598d30, 2, down, across, entry->esi, angle, ebp) + 3;
    port_set32(&port, ebp, -0x18u, speed);
    port_set32(&port, ebp, -0x20u, 0);
    port_set32(&port, ebp, -0x10u, across);
    port_set32(&port, ebp, -0x14u, down);
    port_set32(&port, ebp, -0x24u, list);
    edx = 0;
    ebx = down;
    ecx = across;
    esi = entry->esi;
    for (count = 0; count < 8; ++count)
    {
        piece = port_call_with(&port, 0x4ca000, 0x15c, edx, ebx, ecx, esi, angle, ebp);
        if (piece != 0)
        {
            piece =
                port_call_with(&port, 0x4abd70, piece, vertrix_lift_edx, ebx, ecx, esi, angle, ebp);
        }
        call_frame(&port, 0x4adf20, piece, 0, 0, 0, piece, angle, ebp, zeros, 5);
        port_set16(&port, piece, 0xe, port_u16(&port, board, 0xe) + across + 0xc);
        port_set16(&port, piece, 0x16, port_u16(&port, board, 0x16) + down + 0xc);
        port_call_with(&port, 0x4ac470, piece, 1, down, 0, piece, angle, ebp);
        port_call_with(&port, 0x4ac7b0, piece, 1, down, 0, piece, angle, ebp);
        port_call_with(&port, 0x4ac840, piece, 2, down, 0, piece, angle, ebp);
        port_call_with(&port, 0x4ac8d0, piece, 0x54651c, down, 0, piece, angle, ebp);
        frame =
            port_call_with(&port, 0x4826c0, 0x598d30, 0x20, down, 0, piece, angle, ebp) & 0xffff;
        port_call_with(&port, 0x4ac710, piece, frame, down, 0x168, piece, angle, ebp);
        port_set8(&port, piece, 0x94, 1);
        port_call_with(&port, 0x4ac8a0, piece, angle & 0xffff, down, 0x168, piece, angle, ebp);
        rest = (int32_t)vertrix_lift_edx % 0x168;
        port_set8(&port, piece, 0x95, 4);
        port_set16(&port, piece, 0x48, 0);
        port_set8(&port, piece, 0x4e, 0x32);
        ebx = (uint32_t)((int32_t)port_u32(&port, piece, 0xc) >> 16);
        port_set8(&port, piece, 0x93, 1);
        ecx = (uint32_t)((int32_t)port_u32(&port, piece, 0x14) >> 16);
        port_set16(&port, piece, 0x24, (uint32_t)rest);
        port_set16(&port, piece, 0x28, speed);
        angle += 0x2d;
        port_call_with(&port, 0x4ad510, piece, 0, ebx, ecx, piece, angle, ebp);
        port_set16(&port, piece, 0x30, 0x64);
        port_set16(&port, piece, 0x32, 1);
        port_call_with(&port, 0x4ac8f0, piece, 0x444700, ebx, count, piece, angle, ebp);
        ecx = count + 1;
        eax = port_call_with(&port, 0x4b5e70, list, piece, ebx, ecx, piece, angle, ebp);
        edx = vertrix_lift_edx;
        port_set32(&port, ebp, -0x20u, ecx);
        esi = piece;
    }
    return port_return(&port, eax, edx);
}

/* Original 0x430440: the rings of the board eax at the cell edx, ebx (scaled by 0x18): three
 * rings, each from an angle drawn (0x4826c0 of 0x598d30) below 0x168, of 0x12 pieces (0x15c
 * bytes, 0x4ca000, 0x4abd70) 0x14 apart, made (0x4adf20 with five zeros) at the board's +0xe and
 * +0x16 plus the cell plus 0xc, stepped (0x4ac470 4), timed (0x4ac7b0 1), given the image
 * 0x54651c with a frame drawn below 0x20 on the first and third ring, else 0x546500 at frame 0
 * (0x4ac8d0, 0x4ac710), the angle (0x4ac8a0, +0x94 1) and +0x24 the remainder below 0x168 of the
 * edx it leaves, +0x95 4, +0x48 0, +0x4e 0x32, +0x93 1, +0x44 3, +0x70 0x96, +0x30 0xc and +0x32
 * 5 less 4 and 1 a ring, +0x28 0, placed (0x4ad510 with +0x70), the state 0x444970 (0x4ac8f0)
 * and added to the list +0xcec (0x4b5e70). 0, edx the angle past the last. */
uint32_t vertrix_port_board_rings_430440(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x40
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t across = entry->edx * 0x18;
    uint32_t down = entry->ebx * 0x18;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t list = board + 0xcec;
    uint32_t ring;
    uint32_t odd = 1;
    uint32_t span = 5;
    uint32_t reach = 0xc;
    uint32_t angle;
    uint32_t count;
    uint32_t piece;
    uint32_t frame;
    uint32_t edx;
    uint32_t ebx = down;
    uint32_t ecx = 1;
    uint32_t esi = 0;
    uint32_t edi = entry->edi;
    int32_t rest;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x34u, board);
    port_set32(&port, ebp, -0x2cu, 0);
    port_set32(&port, ebp, -0x3cu, list);
    port_set32(&port, ebp, -0x20u, span);
    port_set32(&port, ebp, -0x28u, odd);
    port_set32(&port, ebp, -0x10u, across);
    port_set32(&port, ebp, -0x14u, down);
    port_set32(&port, ebp, -0x24u, reach);
    edx = 0;
    for (ring = 0; ring < 3; ++ring)
    {
        angle = port_call_with(&port, 0x4826c0, 0x598d30, 0x168, ebx, ecx, esi, edi, ebp) & 0xffff;
        edx = vertrix_lift_edx;
        port_set32(&port, ebp, -0x38u, angle);
        port_set32(&port, ebp, -0x18u, reach);
        port_set32(&port, ebp, -0x30u, 0);
        port_set32(&port, ebp, -0x1cu, span);
        edi = 0;
        for (count = 0; count < 0x12; ++count)
        {
            piece = port_call_with(&port, 0x4ca000, 0x15c, edx, ebx, ecx, esi, edi, ebp);
            if (piece != 0)
            {
                piece = port_call_with(&port, 0x4abd70, piece, vertrix_lift_edx, ebx, ecx, esi, edi,
                                       ebp);
            }
            call_frame(&port, 0x4adf20, piece, 0, 0, 0, esi, piece, ebp, zeros, 5);
            port_set16(&port, piece, 0xe, port_u16(&port, board, 0xe) + across + 0xc);
            port_set16(&port, piece, 0x16, port_u16(&port, board, 0x16) + down + 0xc);
            port_call_with(&port, 0x4ac470, piece, 4, down, 0, esi, piece, ebp);
            port_call_with(&port, 0x4ac7b0, piece, 1, down, 0, esi, piece, ebp);
            if (odd == 1)
            {
                frame =
                    port_call_with(&port, 0x4826c0, 0x598d30, 0x20, down, 0, piece, piece, ebp) &
                    0xffff;
                port_call_with(&port, 0x4ac8d0, piece, 0x54651c, down, frame + 1, piece, piece,
                               ebp);
                port_call_with(&port, 0x4ac710, piece, frame, down, frame + 1, piece, piece, ebp);
            }
            else
            {
                port_call_with(&port, 0x4ac8d0, piece, 0x546500, down, 0, piece, piece, ebp);
                port_call_with(&port, 0x4ac710, piece, 0, down, 0, piece, piece, ebp);
            }
            port_set8(&port, piece, 0x94, 1);
            port_call_with(&port, 0x4ac8a0, piece, port_u16(&port, ebp, -0x38u), down, 0x168, piece,
                           piece, ebp);
            rest = (int32_t)vertrix_lift_edx % 0x168;
            port_set8(&port, piece, 0x95, 4);
            port_set16(&port, piece, 0x48, 0);
            port_set8(&port, piece, 0x4e, 0x32);
            port_set8(&port, piece, 0x93, 1);
            port_set8(&port, piece, 0x44, 3);
            ebx = (uint32_t)((int32_t)port_u32(&port, piece, 0xc) >> 16);
            port_set32(&port, piece, 0x70, 0x96);
            ecx = (uint32_t)((int32_t)port_u32(&port, piece, 0x14) >> 16);
            port_set16(&port, piece, 0x24, (uint32_t)rest);
            edx = (uint32_t)((int32_t)port_u32(&port, piece, 0x6e) >> 16);
            port_set16(&port, piece, 0x30, reach);
            port_set16(&port, piece, 0x32, span);
            port_set16(&port, piece, 0x28, 0);
            port_call_with(&port, 0x4ad510, piece, edx, ebx, ecx, piece, piece, ebp);
            port_call_with(&port, 0x4ac8f0, piece, 0x444970, ebx, ecx, piece, piece, ebp);
            port_call_with(&port, 0x4b5e70, list, piece, ebx, count, piece, piece, ebp);
            ecx = count + 1;
            edx = port_u32(&port, ebp, -0x38u) + 0x14;
            port_set32(&port, ebp, -0x30u, ecx);
            port_set32(&port, ebp, -0x38u, edx);
            esi = piece;
            edi = piece;
        }
        odd = 1 - odd;
        --span;
        edi = ring + 1;
        reach -= 4;
        esi = reach;
        ecx = span;
        port_set32(&port, ebp, -0x28u, odd);
        port_set32(&port, ebp, -0x20u, span);
        port_set32(&port, ebp, -0x2cu, edi);
        port_set32(&port, ebp, -0x24u, reach);
    }
    return port_return(&port, odd, edx);
}

/* Original 0x430660: the burst of the board eax at the cell edx, ebx (scaled by 0x18): one draw
 * (0x4826c0 of 0x598d30) below 0x168 gives the first angle and one below 9, plus 2, the speed;
 * ten pieces (0x15c bytes, 0x4ca000, 0x4abd70) are made (0x4adf20 with five zeros) at the
 * board's +0xe and +0x16 plus the cell plus 0xc, stepped (0x4ac470 4), timed (0x4ac7b0 1), given
 * the image 0x54651c (0x4ac8d0) at a frame drawn below 0x20 (0x4ac710), the angle (0x4ac8a0,
 * +0x94 1) and +0x24 the remainder below 0x168 of the edx it leaves, +0x95 4, +0x48 0, +0x4e
 * 0x32, +0x93 1, +0x44 3, +0x70 0x96, +0x30 0xc, +0x32 1, +0x28 the speed, placed (0x4ad510 with
 * +0x70), the state 0x444a80 (0x4ac8f0), and added to the list +0xcec (0x4b5e70); each angle
 * 0x24 past the last. The last add's result. */
uint32_t vertrix_port_board_burst_430660(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t across = entry->edx * 0x18;
    uint32_t down = entry->ebx * 0x18;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t list = board + 0xcec;
    uint32_t angle;
    uint32_t speed;
    uint32_t count;
    uint32_t piece;
    uint32_t frame;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t eax = 0;
    int32_t rest;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x24u, board);
    angle = port_call_with(&port, 0x4826c0, 0x598d30, 0x168, entry->ebx, entry->edx, entry->esi,
                           entry->edi, ebp) &
            0xffff;
    speed = (port_call_with(&port, 0x4826c0, 0x598d30, 9, entry->ebx, entry->edx, entry->esi, angle,
                            ebp) &
             0xffff) +
            2;
    port_set32(&port, ebp, -0x18u, speed);
    port_set32(&port, ebp, -0x20u, 0);
    port_set32(&port, ebp, -0x1cu, list);
    port_set32(&port, ebp, -0x14u, across);
    port_set32(&port, ebp, -0x10u, down);
    edx = 0;
    ebx = down;
    ecx = across;
    esi = entry->esi;
    for (count = 0; count < 0xa; ++count)
    {
        piece = port_call_with(&port, 0x4ca000, 0x15c, edx, ebx, ecx, esi, angle, ebp);
        if (piece != 0)
        {
            piece =
                port_call_with(&port, 0x4abd70, piece, vertrix_lift_edx, ebx, ecx, esi, angle, ebp);
        }
        call_frame(&port, 0x4adf20, piece, 0, 0, 0, piece, angle, ebp, zeros, 5);
        port_set16(&port, piece, 0xe, port_u16(&port, board, 0xe) + across + 0xc);
        port_set16(&port, piece, 0x16, port_u16(&port, board, 0x16) + down + 0xc);
        port_call_with(&port, 0x4ac470, piece, 4, down, 0, piece, angle, ebp);
        port_call_with(&port, 0x4ac7b0, piece, 1, down, 0, piece, angle, ebp);
        frame =
            port_call_with(&port, 0x4826c0, 0x598d30, 0x20, down, 0, piece, angle, ebp) & 0xffff;
        port_call_with(&port, 0x4ac8d0, piece, 0x54651c, down, frame, piece, angle, ebp);
        port_call_with(&port, 0x4ac710, piece, frame, down, frame, piece, angle, ebp);
        port_set8(&port, piece, 0x94, 1);
        port_call_with(&port, 0x4ac8a0, piece, angle & 0xffff, down, 0x168, piece, angle, ebp);
        rest = (int32_t)vertrix_lift_edx % 0x168;
        port_set8(&port, piece, 0x95, 4);
        port_set16(&port, piece, 0x48, 0);
        port_set8(&port, piece, 0x4e, 0x32);
        port_set8(&port, piece, 0x93, 1);
        port_set8(&port, piece, 0x44, 3);
        port_set32(&port, piece, 0x70, 0x96);
        port_set16(&port, piece, 0x30, 0xc);
        ebx = (uint32_t)((int32_t)port_u32(&port, piece, 0xc) >> 16);
        port_set16(&port, piece, 0x32, 1);
        ecx = (uint32_t)((int32_t)port_u32(&port, piece, 0x14) >> 16);
        port_set16(&port, piece, 0x24, (uint32_t)rest);
        edx = (uint32_t)((int32_t)port_u32(&port, piece, 0x6e) >> 16);
        port_set16(&port, piece, 0x28, speed);
        angle += 0x24;
        port_call_with(&port, 0x4ad510, piece, edx, ebx, ecx, piece, angle, ebp);
        port_call_with(&port, 0x4ac8f0, piece, 0x444a80, ebx, count, piece, angle, ebp);
        ecx = count + 1;
        eax = port_call_with(&port, 0x4b5e70, list, piece, ebx, ecx, piece, angle, ebp);
        edx = vertrix_lift_edx;
        port_set32(&port, ebp, -0x20u, ecx);
        esi = piece;
    }
    return port_return(&port, eax, edx);
}
