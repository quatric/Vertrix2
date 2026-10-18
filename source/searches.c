#include "searches.h"

/* The computer player's move search and move features. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* The board's pick of 0x41 bytes at +0x1de copied to the search eax's +0x184; esi past it. */
static uint32_t copy_pick(Port *port, uint32_t search, uint32_t board)
{
    uint32_t index;
    for (index = 0; index < 0x41; ++index)
    {
        port_set8(port, search + 0x184, index, port_u8(port, board + 0x1de, index));
    }
    return board + 0x1de + 0x41;
}

/* Original 0x425f60: the search eax for the player edx (ret 4) with the board +0x15c holding a
 * piece (+0xa60): its cells are counted (0x431b20 into ebp-0x28, ebp-0x24 and ebp-0x20; none ends
 * with 0) and marked (0x432820), and the searches tried in turn until one finds a move, each after
 * the board's pick is copied to +0x184 and given the search's +0x16c and +0x168, the player's
 * level +0x4dc, the counts and +0x160: the bomb search 0x427380 (with the player's bombs +0x4cd
 * and +0x4c8, when it has bombs), the plain 0x4270a0, the chain 0x4269e0 and the fallback
 * 0x426240. The move found, or the board without a piece. */
uint32_t vertrix_port_ai_move_search_425f60(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t search = entry->eax;
    uint32_t player = entry->edx;
    uint32_t board;
    uint32_t esi;
    uint32_t result;
    uint32_t args[8];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, -0xcu, search);
    port_set32(&port, ebp, -0x10u, player);
    port_set32(&port, ebp, -0x18u, entry->ebx);
    port_set32(&port, ebp, -0x14u, entry->ecx);
    port_set32(&port, ebp, -0x28u, 0);
    port_set32(&port, ebp, -0x24u, 0);
    port_set32(&port, ebp, -0x20u, 0);
    board = port_u32(&port, player, 0x15c);
    port_set32(&port, ebp, -0x1cu, board);
    if (port_u32(&port, board, 0xa60) == 0)
    {
        return port_return(&port, board, player);
    }
    if (port_call_with(&port, 0x431b20, board, ebp - 0x28, ebp - 0x24, ebp - 0x20, 0,
                       port_u32(&port, board, 0xa60), ebp) == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_call_with(&port, 0x432820, board, vertrix_lift_edx, ebp - 0x24, ebp - 0x20, 0,
                   port_u32(&port, board, 0xa60), ebp);
    args[0] = search + 0x16c;
    args[1] = search + 0x168;
    args[2] = port_u8(&port, player, 0x4dc);
    args[3] = port_u32(&port, ebp, -0x28u);
    args[4] = port_u32(&port, ebp, -0x20u);
    args[5] = port_u32(&port, search, 0x160);
    if (port_u8(&port, player, 0x4cd) != 0)
    {
        esi = copy_pick(&port, search, board);
        args[2] = port_u8(&port, player, 0x4dc);
        args[3] = port_u32(&port, ebp, -0x28u);
        args[4] = port_u32(&port, ebp, -0x20u);
        args[5] = port_u32(&port, search, 0x160);
        args[6] = (uint32_t)(int32_t)(int8_t)port_u8(&port, player, 0x4cd);
        args[7] = port_u32(&port, player, 0x4c8);
        result = call_frame(&port, 0x427380, search, entry->ebx, entry->ecx,
                            port_u32(&port, ebp, 8), esi, search + 0x184, ebp, args, 8);
        if (result != 0)
        {
            return port_return(&port, result, vertrix_lift_edx);
        }
    }
    copy_pick(&port, search, board);
    args[2] = port_u8(&port, player, 0x4dc);
    args[3] = port_u32(&port, ebp, -0x28u);
    args[4] = port_u32(&port, ebp, -0x20u);
    args[5] = port_u32(&port, search, 0x160);
    result = call_frame(&port, 0x4270a0, search, entry->ebx, entry->ecx, port_u32(&port, ebp, 8),
                        args[5], args[4], ebp, args, 6);
    if (result != 0)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    esi = copy_pick(&port, search, board);
    args[2] = port_u8(&port, player, 0x4dc);
    args[3] = port_u32(&port, ebp, -0x28u);
    args[4] = port_u32(&port, ebp, -0x20u);
    args[5] = port_u32(&port, search, 0x160);
    result = call_frame(&port, 0x4269e0, search, entry->ebx, entry->ecx, port_u32(&port, ebp, 8),
                        esi, search + 0x184, ebp, args, 6);
    if (result != 0)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    copy_pick(&port, search, board);
    args[2] = port_u8(&port, player, 0x4dc);
    args[3] = port_u32(&port, ebp, -0x28u);
    args[4] = port_u32(&port, ebp, -0x20u);
    args[5] = port_u32(&port, search, 0x160);
    result = call_frame(&port, 0x426240, search, entry->ebx, entry->ecx, port_u32(&port, ebp, 8),
                        args[5], args[4], ebp, args, 6);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x427c10: the move features (ret 0x14) of the row edx against the target row arg 3,
 * the kind ebx and the columns ecx and arg 0 at the widths arg 1 and arg 2, into the bytes of
 * arg 4: +1 the rows below the target (0 beneath it or both 9, else 1 to 4), +6 the kind (0 for
 * 9 or below 4, 1 for 4, 2 for 5, 4 for 8, else 3), +0xb the height over the kind (0 to 4 by 0,
 * 2, 4 and 6), +0xf the reach right and +0x26 the reach left (0 none, else by 12, 24 and 36
 * units between the column ends). The last feature, edx as the original leaves it. */
uint32_t vertrix_port_ai_features_427c10(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0x14];
    uint32_t ebp = entry->esp - 4;
    uint32_t row = entry->edx;
    uint32_t kind = entry->ebx;
    uint32_t column = entry->ecx;
    uint32_t other;
    uint32_t left;
    uint32_t right;
    uint32_t target;
    uint32_t out;
    uint32_t value;
    uint32_t edx;
    int32_t near;
    int32_t far;
    int32_t height;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 5);
    other = port_u32(&port, ebp, 8);
    left = port_u32(&port, ebp, 0xc);
    right = port_u32(&port, ebp, 0x10);
    target = port_u32(&port, ebp, 0x14);
    out = port_u32(&port, ebp, 0x18);
    if (row < target || (row == 9 && target == 9))
    {
        value = 0;
    }
    else if (row == target)
    {
        value = 1;
    }
    else if (target == row + 1)
    {
        value = 2;
    }
    else if (target == row + 2)
    {
        value = 3;
    }
    else
    {
        value = 4;
    }
    port_set8(&port, out, 1, value);
    if (kind == 9 || kind < 4)
    {
        value = 0;
    }
    else if (kind == 8)
    {
        value = 4;
    }
    else if (kind == 5)
    {
        value = 2;
    }
    else if (kind == 4)
    {
        value = 1;
    }
    else
    {
        value = 3;
    }
    edx = row - kind;
    port_set8(&port, out, 6, value);
    height = (int32_t)edx;
    value = height <= 0 ? 0 : height > 6 ? 4 : height > 4 ? 3 : height > 2 ? 2 : 1;
    port_set8(&port, out, 0xb, value);
    if (column < other)
    {
        near = (int32_t)(left + column * 12);
        far = (int32_t)(right + other * 12);
        edx = (uint32_t)near;
        if (far > near + 0xc)
        {
            value = 1;
        }
        else if (far > near + 0x18)
        {
            value = 2;
        }
        else
        {
            edx = (uint32_t)(near + 0x24);
            value = far > near + 0x24 ? 3 : 4;
        }
    }
    else
    {
        value = 0;
    }
    port_set8(&port, out, 0xf, value);
    if (other >= column)
    {
        value = 0;
    }
    else
    {
        near = (int32_t)(left + column * 12);
        far = (int32_t)(right + other * 12);
        edx = (uint32_t)far;
        if (near > far + 0xc)
        {
            value = 1;
        }
        else if (near > far + 0x18)
        {
            value = 2;
        }
        else
        {
            edx = (uint32_t)(far + 0x24);
            value = near > far + 0x24 ? 3 : 4;
        }
    }
    port_set8(&port, out, 0x26, value);
    return port_return(&port, value, edx);
}
