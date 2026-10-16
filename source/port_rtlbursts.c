#include "port_rtlbursts.h"

/* Marked board cells bursting outwards. */

/* The signed quotient of `value` by `divisor` as idiv leaves it after cdq (value kept when the
 * divisor is 0). */
static uint32_t quotient(uint32_t value, uint32_t divisor)
{
    LiftFlags flags = {0};
    uint32_t eax = value;
    uint32_t edx = (uint32_t)((int32_t)value >> 31);
    lift_idiv1(32, divisor, &eax, &edx, &flags);
    return eax;
}

/* The centre of a piece across (+0xe) or down (+0x16) plus 12. */
static int32_t piece_centre(Port *port, uint32_t piece, uint32_t field)
{
    return (int32_t)(int16_t)port_u16(port, piece, field) + 0xc;
}

/* Original 0x4375f0: the marked cells of the board eax (0x436030 counts them, 0x4360b0 picks each)
 * burst outwards: their centre and greatest distance (across plus down) from it found; each piece
 * moved to its waiting slot (+0x87c), stepped by 0x44dcf0 (0x4ac8f0) with +0x4e 100, shown
 * (0x4ac7b0 with 2), +0x93 1, started (0x4ac510, 0x4ac380 with the centre down); its speeds
 * +0x12/+0x1a set to 5 along its greater way from the centre (signed by its side) and in
 * proportion along the other, shown with twice the distance over itself (at least 1), +0x64 and
 * +0x52 three times it over itself, +0x48 a hundred times, +0x58 0. eax 1, or 0 with none marked;
 * edx kept. */
uint32_t vertrix_port_board_burst_marked_4375f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x4c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t count;
    uint32_t index;
    uint32_t across = 0;
    uint32_t down = 0;
    int32_t farthest = 0;
    uint32_t twice;
    uint32_t piece;
    LiftFlags flags = {0};
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    count = port_call_with(&port, 0x436030, board, entry->edx, entry->ebx, entry->ecx, board,
                           entry->edi, ebp);
    port_set32(&port, ebp, -0x20u, count);
    if (count == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    for (index = 0; index < count && !port.env.failed; index++)
    {
        port_call_with(&port, 0x4360b0, board, index, ebp - 0x48, ebp - 0x44, board, index, ebp);
        piece = port_u32(
            &port, board + port_u32(&port, ebp, -0x48u) * 0x34 + port_u32(&port, ebp, -0x44u) * 4,
            0x220);
        across += (uint32_t)piece_centre(&port, piece, 0xe);
        down += (uint32_t)piece_centre(&port, piece, 0x16);
    }
    {
        uint32_t eax = across;
        uint32_t edx = 0;
        lift_div1(32, count, &eax, &edx, &flags);
        across = eax;
        eax = down;
        edx = 0;
        lift_div1(32, count, &eax, &edx, &flags);
        down = eax;
    }
    port_set32(&port, ebp, -0x1cu, across);
    port_set32(&port, ebp, -0x2cu, down);
    for (index = 0; index < count && !port.env.failed; index++)
    {
        int32_t distance;
        int32_t way;
        port_call_with(&port, 0x4360b0, board, index, ebp - 0x40, ebp - 0x3c, board, index, ebp);
        piece = port_u32(
            &port, board + port_u32(&port, ebp, -0x40u) * 0x34 + port_u32(&port, ebp, -0x3cu) * 4,
            0x220);
        way = piece_centre(&port, piece, 0xe) - (int32_t)across;
        distance = way < 0 ? -way : way;
        way = piece_centre(&port, piece, 0x16) - (int32_t)down;
        distance += way < 0 ? -way : way;
        if (distance > farthest)
        {
            farthest = distance;
        }
    }
    port_set32(&port, ebp, -0x18u, (uint32_t)farthest);
    twice = quotient((uint32_t)farthest * 2, (uint32_t)farthest);
    port_set32(&port, ebp, -0x28u, twice);
    for (index = 0; index < count && !port.env.failed; index++)
    {
        uint32_t slot;
        uint32_t edi = index == 0 ? count : index;
        int32_t x;
        int32_t y;
        uint32_t shown;
        uint32_t steps;
        port_set32(&port, ebp, -0x30u, index);
        port_call_with(&port, 0x4360b0, board, index, ebp - 0x38, ebp - 0x34, board, edi, ebp);
        slot = board + port_u32(&port, ebp, -0x38u) * 0x34 + port_u32(&port, ebp, -0x34u) * 4;
        piece = port_u32(&port, slot, 0x220);
        port_set32(&port, slot, 0x87c, piece);
        port_set32(&port, slot, 0x220, 0);
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebp - 0x38, piece, board, edi, ebp)
        CALL(0x4ac8f0, piece, 0x44dcf0);
        port_set8(&port, piece, 0x4e, 0x64);
        CALL(0x4ac7b0, piece, 2);
        port_set8(&port, piece, 0x93, 1);
        CALL(0x4ac510, piece, vertrix_lift_edx);
        CALL(0x4ac380, piece, down);
#undef CALL
        x = piece_centre(&port, piece, 0xe) - (int32_t)across;
        y = piece_centre(&port, piece, 0x16) - (int32_t)vertrix_lift_edx;
        if (x < y)
        {
            port_set16(&port, piece, 0x12, 5);
            if (x < 0)
            {
                port_set16(&port, piece, 0x12, 0u - port_u16(&port, piece, 0x12));
            }
            if (x == 0)
            {
                port_set16(&port, piece, 0x1a, 0);
            }
            else
            {
                port_set16(&port, piece, 0x1a,
                           quotient((uint32_t)((int32_t)(int16_t)port_u16(&port, piece, 0x12) * y),
                                    (uint32_t)x));
            }
        }
        else
        {
            port_set16(&port, piece, 0x1a, 5);
            if (y < 0)
            {
                port_set16(&port, piece, 0x1a, 0u - port_u16(&port, piece, 0x1a));
            }
            if (y == 0)
            {
                port_set16(&port, piece, 0x12, 0);
            }
            else
            {
                port_set16(&port, piece, 0x12,
                           quotient((uint32_t)((int32_t)(int16_t)port_u16(&port, piece, 0x1a) * x),
                                    (uint32_t)y));
            }
        }
        port_set32(&port, ebp, -0x24u, (uint32_t)farthest);
        shown = twice == 0 ? 1 : twice;
        port_call_with(&port, 0x4ac7b0, piece, shown, shown, piece, board, edi, ebp);
        steps = quotient((uint32_t)farthest * 3, (uint32_t)farthest);
        port_set32(&port, piece, 0x64, steps);
        port_set32(&port, piece, 0x58, 0);
        port_set16(&port, piece, 0x48, quotient((uint32_t)farthest * 100, (uint32_t)farthest));
        port_set8(&port, piece, 0x52, steps);
    }
    port_set32(&port, ebp, -0x30u, count);
    return port_return(&port, 1, entry->edx);
}
