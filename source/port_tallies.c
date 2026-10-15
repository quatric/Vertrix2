#include "port_tallies.h"

/* The board's fullest row mark, its kind pick, the marked cells' step, and an object's
 * teardown. */

/* The frame's saved words as the original pushes them: ebp at the frame base, then `count`
 * registers below it. The random picks below read past their lists into them. */
static void saved_registers(Port *port, const LiftEntry *entry, uint32_t ebp, unsigned count,
                            const uint32_t *registers)
{
    unsigned index;
    port_set32(port, ebp, 0, entry->ebp);
    for (index = 0; index < count; ++index)
    {
        port_set32(port, ebp, -4u * (index + 1), registers[index]);
    }
}

static uint32_t sign8(uint32_t value)
{
    return (uint32_t)(int32_t)(int8_t)value;
}

/* Original 0x438dd0: the board eax's cells (13 a row from +0x1de, 0xff empty; set up by 0x4327e0
 * from +0x220) counted by row into the frame; with any filled, one of the fullest rows is picked
 * (0x4826c0 on 0x598d30, an index past the list reading the frame's saved words) and its
 * filled cells are marked 1 at +0xb94, all others 0. */
uint32_t vertrix_port_board_mark_fullest_row_438dd0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x54
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t most = 0;
    uint32_t row;
    uint32_t cell;
    uint32_t count;
    uint32_t found;
    uint32_t pick;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    saved_registers(&port, entry, ebp, 5,
                    (const uint32_t[]){entry->ebx, entry->ecx, entry->edx, entry->esi, entry->edi});
    port_set32(&port, ebp, -0x28u, board);
    port_call_with(&port, 0x4327e0, board + 0x220, board + 0x1de, 0x41, entry->ecx, entry->esi, 0,
                   ebp);
    for (row = 0; row < 5; ++row)
    {
        count = 0;
        for (cell = 0; cell < 0xd; ++cell)
        {
            if (port_u8(&port, board + row * 0xd + cell, 0x1de) != 0xff)
            {
                ++count;
            }
        }
        port_set32(&port, ebp, -0x50u + row * 4, count);
        if (count > most)
        {
            most = count;
        }
    }
    port_set32(&port, ebp, -0x1cu, 0x14);
    port_set32(&port, ebp, -0x18u, board + 0x4e);
    if (most == 0)
    {
        return port_return(&port, board + 0x4e, entry->edx);
    }
    found = 0;
    for (row = 0; row < 5; ++row)
    {
        if (port_u32(&port, ebp, -0x50u + row * 4) == most)
        {
            port_set32(&port, ebp, -0x3cu + found * 4, row);
            ++found;
        }
    }
    pick = port_call_with(&port, 0x4826c0, 0x598d30, found & 0xffff, 0xff, 0x14, found * 4, most,
                          ebp) &
           0xffff;
    pick = port_u32(&port, ebp, -0x3cu + pick * 4);
    for (row = 0; row < 5; ++row)
    {
        for (cell = 0; cell < 0xd; ++cell)
        {
            uint32_t at = board + row * 0xd + cell;
            port_set8(&port, at, 0xb94, port_u8(&port, at, 0x1de) != 0xff && row == pick ? 1 : 0);
        }
        port_set32(&port, ebp, -0x20u, board + row * 0xd + 0x1a);
        port_set32(&port, ebp, -0x24u, board + row * 0xd + 0xd);
    }
    return port_return(&port, board + 0x41, entry->edx);
}

/* Original 0x439260: the board eax's kinds (0 to 4 at the cells +0x1de, set up by 0x4327e0 from
 * +0x220) counted; those present are shuffled (0x4826c0 on 0x598d30) when more than one, at most 3
 * counted into ebx's word, and the five list words copied to edx. 5. */
uint32_t vertrix_port_board_pick_kinds_439260(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x44
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t list = entry->edx;
    uint32_t row;
    uint32_t cell;
    uint32_t kind;
    uint32_t found;
    uint32_t index;
    uint32_t pick;
    uint32_t held;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    saved_registers(&port, entry, ebp, 3, (const uint32_t[]){entry->ecx, entry->esi, entry->edi});
    port_set32(&port, ebp, -0x10u, board);
    port_set32(&port, ebp, -0x18u, list);
    port_set32(&port, ebp, -0x14u, entry->ebx);
    port_call_with(&port, 0x4327e0, board + 0x220, board + 0x1de, 0x41, entry->ecx, entry->esi,
                   entry->edi, ebp);
    for (kind = 0; kind < 5; ++kind)
    {
        port_set32(&port, ebp, -0x2cu + kind * 4, 0);
    }
    for (row = 0; row < 5; ++row)
    {
        for (cell = 0; cell < 0xd; ++cell)
        {
            kind = sign8(port_u8(&port, board + row * 0xd + cell, 0x1de));
            if ((int32_t)kind >= 0 && (int32_t)kind < 5)
            {
                port_set32(&port, ebp, -0x2cu + kind * 4,
                           port_u32(&port, ebp, -0x2cu + kind * 4) + 1);
            }
        }
    }
    found = 0;
    for (kind = 0; kind < 5; ++kind)
    {
        if ((int32_t)port_u32(&port, ebp, -0x2cu + kind * 4) > 0)
        {
            port_set32(&port, ebp, -0x40u + found * 4, kind);
            ++found;
        }
    }
    if (found > 1)
    {
        for (index = 0; index < found; ++index)
        {
            held = port_u32(&port, ebp, -0x40u + index * 4);
            pick = port_call_with(&port, 0x4826c0, 0x598d30, found & 0xffff, index * 4, found,
                                  index, held, ebp) &
                   0xffff;
            port_set32(&port, ebp, -0x40u + index * 4, port_u32(&port, ebp, -0x40u + pick * 4));
            port_set32(&port, ebp, -0x40u + pick * 4, held);
        }
    }
    if (found > 3)
    {
        found = 3;
    }
    port_set32(&port, entry->ebx, 0, found);
    for (index = 0; index < 5; ++index)
    {
        port_set32(&port, list, index * 4, port_u32(&port, ebp, -0x40u + index * 4));
    }
    return port_return(&port, 5, list + 0x14);
}

/* Original 0x4393f0: the board eax's marked step ecx (a count word) of ebx: a count at the end is
 * 1; otherwise, after 0x439370, each cell marked 1 at +0xb94 is handed on (0x439510 with its
 * piece +0x220) or, on the last step, finished (0x439690); the result goes to +0xbdc and the
 * cell is marked 2, and 0 is given. The count goes up. */
uint32_t vertrix_port_board_marked_step_4393f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t limit = entry->ebx;
    uint32_t counter = entry->ecx;
    uint32_t result = 1;
    uint32_t row;
    uint32_t column;
    uint32_t ecx = 1;
    uint32_t done;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, limit);
    port_set32(&port, ebp, -0x30u, counter);
    port_set32(&port, ebp, -0x1cu, 1);
    if (port_u32(&port, counter, 0) >= limit)
    {
        return port_return(&port, 1, entry->edx);
    }
    port_set32(&port, ebp, -0x20u, board);
    port_set32(&port, ebp, -0x24u, board);
    port_call_with(&port, 0x439370, board, entry->edx, port_u32(&port, counter, 0), 1, 0, board,
                   ebp);
    for (row = 0; row < 5; ++row)
    {
        port_set32(&port, ebp, -0x2cu, row);
        for (column = 0; column < 0xd; ++column)
        {
            uint32_t at = board + row * 0xd + column;
            uint32_t slot = board + row * 0x34 + column * 4;
            port_set32(&port, ebp, -0x14u, at);
            port_set32(&port, ebp, -0xcu, slot);
            port_set32(&port, ebp, -0x28u, at);
            port_set32(&port, ebp, -0x10u, slot);
            if (port_u8(&port, at, 0xb94) == 1)
            {
                result = 0;
                port_set32(&port, ebp, -0x1cu, 0);
                if (port_u32(&port, counter, 0) + 1 != limit)
                {
                    done = port_call_with(&port, 0x439510, board, row, column,
                                          port_u32(&port, slot, 0x220), column, board, ebp);
                }
                else
                {
                    done = port_call_with(&port, 0x439690, board, row, column, ecx, column, board,
                                          ebp);
                }
                port_set32(&port, slot, 0xbdc, done);
                port_set8(&port, at, 0xb94, 2);
            }
            ecx = at + 1;
        }
        port_set32(&port, ebp, -0x20u, board + (row + 1) * 0xd);
        port_set32(&port, ebp, -0x24u, board + (row + 1) * 0x34);
        port_set32(&port, ebp, -0x2cu, row + 1);
    }
    port_set32(&port, counter, 0, port_u32(&port, counter, 0) + 1);
    return port_return(&port, result, board + 0x104);
}

/* Original 0x43a970: the object eax's teardown by the flags edx: with bit 4 the class is freed
 * (0x4ccb9f with 0x514ce0, 0x4ca040); otherwise under a guard record (0x514c1c, step 4) its
 * methods become 0x514cb4, the children +0x4e8, +0x15c, +0x450 (method +0x158), +0x468 (method
 * +4 of +0) and +0x46c (method +0x1c) are told 2, the list +0x19c cleared (0x481fb0), the base
 * torn down (0x4ac130 with 1) and with bit 2 freed (0x4ca050). The object. */
uint32_t vertrix_port_object_teardown_43a970(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x48
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t flags = entry->edx;
    uint32_t record = ebp - 0x30;
    uint32_t esi = 0x514c1c;
    uint32_t child;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    if ((flags & 4) != 0)
    {
        port_set32(&port, ebp, -0x44u, object);
        port_set32(&port, ebp, -0x24u, 1);
        result = port_call_with(&port, 0x4ccb9f, object, 0x514ce0, flags, object, entry->esi,
                                entry->edi, ebp);
        port_set32(&port, ebp, -0x24u, 0);
        port_call_with(&port, 0x4ca040, result, 0, flags, object, entry->esi, entry->edi, ebp);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, 0x158, 0x514cb4);
    port_set32(&port, ebp, -0x1cu, object);
    port_set8(&port, ebp, -0x18u, flags);
    port_set32(&port, record, 0, port.env.chain);
    port_set32(&port, record, 4, 0x4ec1ec);
    port_set32(&port, record, 8, 0x514c1c);
    port_set32(&port, record, 0xc, 4);
    child = port_u32(&port, object, 0x4e8);
    if (child != 0)
    {
        esi = port_u32(&port, child, 0x158);
        port_call_with(&port, port_u32(&port, esi, 0), child, 2, flags, object, esi, 4, ebp);
    }
    child = port_u32(&port, object, 0x15c);
    if (child != 0)
    {
        esi = port_u32(&port, child, 0x158);
        port_call_with(&port, port_u32(&port, esi, 0), child, 2, flags, object, esi, 4, ebp);
    }
    child = port_u32(&port, object, 0x450);
    if (child != 0)
    {
        esi = port_u32(&port, child, 0x158);
        port_call_with(&port, port_u32(&port, esi, 0), child, 2, flags, object, esi, 4, ebp);
    }
    child = port_u32(&port, object, 0x468);
    if (child != 0)
    {
        esi = port_u32(&port, child, 0);
        port_call_with(&port, port_u32(&port, esi, 4), child, 2, flags, object, esi, 4, ebp);
    }
    child = port_u32(&port, object, 0x46c);
    if (child != 0)
    {
        esi = port_u32(&port, child, 0x1c);
        port_call_with(&port, port_u32(&port, esi, 0), child, 2, flags, object, esi, 4, ebp);
    }
    port_set32(&port, ebp, -0x24u, 3);
    result = port_call_with(&port, 0x481fb0, object + 0x19c, 0, flags, object, 0, 4, ebp);
    port_set32(&port, ebp, -0x24u, 0);
    result = port_call_with(&port, 0x4ac130, result - 0x19c, 1, flags, object, 0, 4, ebp);
    port_set32(&port, ebp, -0x24u, 0);
    if ((flags & 2) != 0)
    {
        port_call_with(&port, 0x4ca050, result, vertrix_lift_edx, flags, result, 0, 4, ebp);
    }
    return port_return(&port, result, vertrix_lift_edx);
}
