#include "drops.h"

/* The board's falling column. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x431d90: the falling column (ret 4) of the board eax with the kinds dl, bl and cl
 * for the player arg 0: the column +0xa68 becomes 2 when its top cell (+0x220, 0x34 a column)
 * is taken; the column (0x188 bytes, 0x4ca000, 0x42a310) at +0xa60 is made (0x42a540 with the
 * board's +0xc and +0x14, 0x18 a column past +0xe, 0x48 above +0x16, then 0, 1 and 2), given the
 * level 0x532bbc's speed 0x4f7d50 of the player (0x4ac7d0), +0x1a from 0x4f7dc8 and the size
 * 0x190 (0x4ac860); +0xb90 1; each of its three pieces (+0x15c) is made (0x4adf20 with the state
 * 0x44c860), given its kind's step (0x415470, 0x4ac490), a speed drawn (0x4826c0 of 0x598d30)
 * below 10 plus 1 (0x4ac7b0), the image 0x544ac0 of 0x1c a kind (0x4ac8d0) and the kind at
 * +0x15c. +0xbd8 is set with the column 2 and +0x288 taken; the column +0xa68 becomes 2. */
uint32_t vertrix_port_board_column_drop_431d90(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t kinds[3];
    uint32_t args[5];
    uint32_t column;
    uint32_t player;
    uint32_t level;
    uint32_t piece;
    uint32_t part;
    uint32_t index;
    uint32_t across;
    uint32_t down;
    uint32_t ecx = entry->ecx;
    uint32_t kind;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x24u, board);
    port_set8(&port, ebp, -0xcu, entry->edx);
    port_set8(&port, ebp, -0x14u, entry->ebx);
    port_set8(&port, ebp, -0x10u, entry->ecx);
    kinds[0] = (uint32_t)(int32_t)(int8_t)entry->edx;
    kinds[1] = (uint32_t)(int32_t)(int8_t)entry->ebx;
    kinds[2] = (uint32_t)(int32_t)(int8_t)entry->ecx;
    column = port_u32(&port, board, 0xa68);
    if (column != 2)
    {
        ecx = board;
        if (port_u32(&port, board + column * 0x34, 0x220) != 0)
        {
            port_set32(&port, board, 0xa68, 2);
        }
    }
    piece = port_call_with(&port, 0x4ca000, 0x188, column, entry->ebx, ecx, entry->esi, entry->edi,
                           ebp);
    if (piece != 0)
    {
        piece = port_call_with(&port, 0x42a310, piece, vertrix_lift_edx, entry->ebx, ecx,
                               entry->esi, entry->edi, ebp);
    }
    port_set32(&port, board, 0xa60, piece);
    args[0] = (uint32_t)(int32_t)(int16_t)(port_u16(&port, board, 0x16) - 0x48);
    args[1] = 0;
    args[2] = 1;
    args[3] = 2;
    across = port_u16(&port, board, 0xa68) * 0x18 + port_u16(&port, board, 0xe);
    down = (uint32_t)((int32_t)port_u32(&port, board, 0x14) >> 16);
    call_frame(&port, 0x42a540, piece, (uint32_t)((int32_t)port_u32(&port, board, 0xc) >> 16), down,
               (uint32_t)(int32_t)(int16_t)across, piece, entry->edi, ebp, args, 4);
    ecx = (uint32_t)(int32_t)(int16_t)across;
    player = port_u32(&port, ebp, 8) * 4;
    level = port_u32(&port, 0, 0x532bbc);
    port_call_with(&port, 0x4ac7d0, piece, port_u32(&port, 0, player + level * 40 + 0x4f7d50),
                   player, ecx, piece, entry->edi, ebp);
    level = port_u32(&port, 0, 0x532bbc);
    port_set16(&port, piece, 0x1a, port_u16(&port, 0, player + level * 40 + 0x4f7dc8));
    port_call_with(&port, 0x4ac860, piece, 0x190, player, ecx, piece, entry->edi, ebp);
    port_set32(&port, ebp, -0x20u, piece);
    port_set32(&port, board, 0xb90, 1);
    for (index = 0; index < 3; ++index)
    {
        kind = kinds[index];
        port_set32(&port, ebp, -0x18u, kind);
        port_set32(&port, ebp, -0x1cu, piece + index * 4);
        part = port_u32(&port, piece + index * 4, 0x15c);
        args[0] = 0;
        args[1] = 0;
        args[2] = 0;
        args[3] = 0x44c860;
        args[4] = 0;
        down = (uint32_t)((int32_t)port_u32(&port, board, 0x14) >> 16);
        call_frame(&port, 0x4adf20, part, (uint32_t)((int32_t)port_u32(&port, board, 0xc) >> 16),
                   down, 0, part, index, ebp, args, 5);
        port_call_with(
            &port, 0x4ac490, part,
            port_call_with(&port, 0x415470, kind, vertrix_lift_edx, down, 0, part, index, ebp),
            down, 0, part, index, ebp);
        port_call_with(
            &port, 0x4ac7b0, part,
            (port_call_with(&port, 0x4826c0, 0x598d30, 0xa, down, 0, part, index, ebp) & 0xffff) +
                1,
            down, 0, part, index, ebp);
        port_call_with(&port, 0x4ac8d0, part, kind * 0x1c + 0x544ac0, down, 0, part, index + 1,
                       ebp);
        port_set8(&port, part, 0x15c, kind);
    }
    port_set32(&port, ebp, -0x1cu, piece + 0xc);
    if (port_u32(&port, board, 0xa68) == 2 && port_u32(&port, board, 0x288) != 0)
    {
        port_set32(&port, board, 0xbd8, 1);
    }
    port_set32(&port, board, 0xa68, 2);
    return port_return(&port, board, piece + 0xc);
}
