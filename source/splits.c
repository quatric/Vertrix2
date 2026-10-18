#include "splits.h"

/* The board's split of its marked pieces. */

/* The speed of a piece across `distance` (its absolute value as a word, by 100 over 60). */
static uint32_t split_speed(uint32_t distance)
{
    uint32_t sign = (uint32_t)((int32_t)distance >> 31);
    uint32_t span = (distance ^ sign) - sign;
    return (uint32_t)((int32_t)(int16_t)span * 0x64) / 0x3c;
}

/* Original 0x437d70: the split of the board eax's marked pieces (0x436030 counts them, 0x4360b0
 * finds each one's row and column): each piece moves from the cells (+0x220) to the leaving
 * cells (+0x87c) and flies left (the state 0x44e250, 0x4ac8f0; speed 2, 0x4ac7b0; +0x4e 0x64,
 * +0x93 1, 0x4ac510, 0x4ac380, +0x4f 0x32, +0x50 0x14) to the board's +0xe less 0x18 and a height
 * drawn below 3 plus 1 (0x4826c0 of 0x598d30), its pace +0x4a its distance by 100 over 60 and
 * +0x4c 10; a new piece of its kind (+0x15c, 0x430800) takes its cell, its place, step (+0xd0,
 * 0x4ac490) and frame (+0xb8, 0x4ac710), and flies likewise right to the board's +0xe plus
 * 0x7d. 1, or 0 with none marked; the registers but eax kept. */
uint32_t vertrix_port_board_split_marked_437d70(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t count;
    uint32_t index;
    uint32_t slot;
    uint32_t piece;
    uint32_t fresh;
    uint32_t height;
    uint32_t ebx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    count = port_call_with(&port, 0x436030, board, entry->edx, entry->ebx, entry->ecx, board,
                           entry->edi, ebp);
    port_set32(&port, ebp, -0x18u, count);
    if (count == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    for (index = 0; index < count; ++index)
    {
        ebx = ebp - 0x20;
        port_call_with(&port, 0x4360b0, board, index, ebx, ebp - 0x1c, board, index, ebp);
        slot = board + port_u32(&port, ebp, -0x20u) * 0x34 + port_u32(&port, ebp, -0x1cu) * 4;
        piece = port_u32(&port, slot, 0x220);
        port_set32(&port, slot, 0x87c, piece);
        port_set32(&port, slot, 0x220, 0);
        port_call_with(&port, 0x4ac8f0, piece, 0x44e250, ebx, piece, board, index, ebp);
        port_set8(&port, piece, 0x4e, 0x64);
        port_call_with(&port, 0x4ac7b0, piece, 2, ebx, piece, board, index, ebp);
        port_set8(&port, piece, 0x93, 1);
        port_call_with(&port, 0x4ac510, piece, vertrix_lift_edx, ebx, piece, board, index, ebp);
        port_call_with(&port, 0x4ac380, piece, vertrix_lift_edx, ebx, piece, board, index, ebp);
        port_set8(&port, piece, 0x4e, 0x64);
        port_set8(&port, piece, 0x4f, 0x32);
        port_set16(&port, piece, 0x50, 0x14);
        ebx = ((ebx & 0xffff0000u) | port_u16(&port, board, 0xe)) - 0x18;
        port_set16(&port, piece, 0x10, ebx);
        height = port_call_with(&port, 0x4826c0, 0x598d30, 3, ebx, piece, board, index, ebp);
        port_set16(&port, piece, 0x12, height + 1);
        port_set16(&port, piece, 0x4a,
                   split_speed((uint32_t)((int32_t)port_u32(&port, piece, 0xe) >> 16) -
                               (uint32_t)((int32_t)port_u32(&port, piece, 0xc) >> 16)));
        port_set16(&port, piece, 0x4c, 0xa);
        fresh = port_call_with(&port, 0x430800, board,
                               (uint32_t)(int32_t)(int8_t)port_u8(&port, piece, 0x15c), 0x3c, piece,
                               board, index, ebp);
        slot = board + port_u32(&port, ebp, -0x20u) * 0x34;
        port_set32(&port, ebp, -0x24u, slot);
        port_set32(&port, slot + port_u32(&port, ebp, -0x1cu) * 4, 0x220, fresh);
        port_set16(&port, fresh, 0xe, port_u16(&port, piece, 0xe));
        port_set16(&port, fresh, 0x16, port_u16(&port, piece, 0x16));
        port_call_with(&port, 0x4ac490, fresh, port_u32(&port, piece, 0xd0), fresh, piece, board,
                       index, ebp);
        port_call_with(&port, 0x4ac7b0, fresh, 2, fresh, piece, board, index, ebp);
        port_set8(&port, fresh, 0x93, 1);
        port_call_with(&port, 0x4ac710, fresh, port_u32(&port, piece, 0xb8), fresh, piece, board,
                       index, ebp);
        port_call_with(&port, 0x4ac8f0, fresh, 0x44e250, fresh, piece, board, index, ebp);
        port_call_with(&port, 0x4ac510, fresh, vertrix_lift_edx, fresh, piece, board, index, ebp);
        port_call_with(&port, 0x4ac380, fresh, vertrix_lift_edx, fresh, piece, board, index, ebp);
        port_set8(&port, fresh, 0x4e, 0x64);
        port_set8(&port, fresh, 0x4f, 0x32);
        port_set16(&port, fresh, 0x50, 0x14);
        port_set16(&port, fresh, 0x10, port_u16(&port, board, 0xe) + 0x7d);
        port_set16(&port, fresh, 0x12, port_u16(&port, piece, 0x12));
        port_set16(&port, fresh, 0x4c, 0xa);
        port_set16(&port, fresh, 0x4a,
                   split_speed((uint32_t)((int32_t)port_u32(&port, fresh, 0xe) >> 16) -
                               (uint32_t)((int32_t)port_u32(&port, piece, 0xc) >> 16)));
    }
    return port_return(&port, 1, entry->edx);
}
