#include "slots.h"

/* The computer player's column scores and the board's slot objects. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x428e70: the seven column scores ebx (cleared, 0x4eb5c0) from the 7 by 4 marks ecx
 * and their scores edx (ret 4, the mode): a column without marks scores 0; with a mode over 2,
 * or a column not flagged in 0x4fb6c0, the best score of its first mark and the later ones
 * marked 1; else the mean of the scores marked 1 (summed in a byte). 1 when any marked 1 has a
 * score, else 0; edx is left at that mark (or past the last). */
uint32_t vertrix_port_ai_choice_scores_428e70(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t scores = entry->edx;
    uint32_t out = entry->ebx;
    uint32_t marks = entry->ecx;
    uint32_t mode;
    uint32_t column;
    uint32_t index;
    uint32_t first;
    uint32_t best;
    uint32_t value;
    uint32_t sum;
    uint32_t count;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    mode = port_u32(&port, ebp, 8);
    port_set32(&port, ebp, -0x24u, marks);
    port_call_with(&port, 0x4eb5c0, out, 0, 7, marks, scores, out, ebp);
    port_set32(&port, ebp, -0x14u, out);
    port_set32(&port, ebp, -0x20u, 0);
    port_set32(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x28u, 0);
    for (column = 0; column < 7; ++column)
    {
        for (first = 0; first < 4; ++first)
        {
            if (port_u32(&port, marks, (column * 4 + first) * 4) != 0)
            {
                break;
            }
        }
        if (first == 4)
        {
            port_set8(&port, out, column, 0);
        }
        else if (mode > 2 || port_u8(&port, 0, 0x4fb6c0 + column) == 0)
        {
            best = port_u8(&port, scores, column * 4 + first);
            for (index = first + 1; index < 4; ++index)
            {
                value = port_u8(&port, scores, column * 4 + index);
                if (port_u32(&port, marks, (column * 4 + index) * 4) == 1 &&
                    (int32_t)value > (int32_t)best)
                {
                    best = value;
                }
            }
            port_set8(&port, out, column, best);
        }
        else
        {
            sum = port_u8(&port, out, column);
            count = 0;
            for (index = 0; index < 4; ++index)
            {
                if (port_u32(&port, marks, (column * 4 + index) * 4) == 1)
                {
                    sum = (sum + port_u8(&port, scores, column * 4 + index)) & 0xff;
                    port_set8(&port, out, column, sum);
                    ++count;
                }
            }
            if (count != 0)
            {
                port_set8(
                    &port, out, column,
                    (uint32_t)((int32_t)(int8_t)port_u8(&port, out, column) / (int32_t)count));
            }
        }
        port_set32(&port, ebp, -0x20u, column + 1);
        port_set32(&port, ebp, -0x1cu, (column + 1) * 0x10);
        port_set32(&port, ebp, -0x28u, (column + 1) * 4);
        port_set32(&port, ebp, -0x14u, out + column + 1);
    }
    for (index = 0; index < 0x1c; ++index)
    {
        if (port_u32(&port, marks, index * 4) == 1 && port_u8(&port, scores, index) != 0)
        {
            return port_return(&port, 1, marks + index * 4);
        }
    }
    return port_return(&port, 0, marks + 0x70);
}

/* Original 0x429bf0: the board eax's 28 slot objects of the level dl (+0x274): each slot's two
 * bytes (0x4178d0 gives the kind, 0x417930 fills them) go to +0x23c and +0x258; a slot with a
 * kind has an object of 0x160 bytes (0x4ca000, 0x43a080) made (0x4adf20 with 0x544a88 and the
 * kind) with the board's +0x52, +0x94 and +0x95, shown (0x4ac8a0 of 0x16, 0x4ac7d0), +0x15c set,
 * the state 0x456ca0 (0x4ac8f0), +0x124 1, the owner +4 and its row at +0x64, and is kept at the
 * board's +0x15c (16 bytes a row). */
uint32_t vertrix_port_slot_objects_make_429bf0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t slot;
    uint32_t row;
    uint32_t column;
    uint32_t kind;
    uint32_t object;
    uint32_t eax = 0;
    uint32_t edx = entry->edx;
    uint32_t args[5];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set8(&port, board, 0x274, entry->edx);
    for (slot = 0; slot < 0x1c; ++slot)
    {
        port_set8(&port, ebp, -0x14u, slot);
        row = slot / 4;
        column = slot - row * 4;
        port_set32(&port, ebp, -0x28u, row);
        port_set32(&port, ebp, -0x30u, row * 4);
        port_set32(&port, ebp, -0x20u, column);
        kind = port_call_with(&port, 0x4178d0, port_u8(&port, board, 0x274), slot, ebp - 0x1c,
                              ebp - 0x18, slot, board, ebp);
        port_set32(&port, ebp, -0x2cu, kind);
        port_set32(&port, ebp, -0x24u, kind);
        eax = port_call_with(&port, 0x417930, port_u8(&port, board, 0x274), slot, ebp - 0x1c,
                             ebp - 0x18, slot, board, ebp);
        edx = vertrix_lift_edx;
        port_set8(&port, board + slot, 0x23c, port_u8(&port, ebp, -0x1cu));
        port_set8(&port, board + slot, 0x258, port_u8(&port, ebp, -0x18u));
        eax = (eax & 0xffffff00u) | port_u8(&port, ebp, -0x18u);
        if (kind == 0xffffffffu)
        {
            continue;
        }
        object =
            port_call_with(&port, 0x4ca000, 0x160, edx, column, board + slot, kind, board, ebp);
        if (object != 0)
        {
            object = port_call_with(&port, 0x43a080, object, vertrix_lift_edx, column, board + slot,
                                    kind, board, ebp);
        }
        args[0] = 0x544a88;
        args[1] = kind;
        args[2] = 0;
        args[3] = 0;
        args[4] = 0;
        call_frame(&port, 0x4adf20, object, 0, 0, 0, object, board, ebp, args, 5);
        port_set8(&port, object, 0x4e, 0);
        port_set8(&port, object, 0x93, 1);
        port_set8(&port, object, 0x52, port_u8(&port, board, 0x52));
        port_set8(&port, object, 0x94, port_u8(&port, board, 0x94));
        port_set8(&port, object, 0x95, port_u8(&port, board, 0x95));
        port_call_with(&port, 0x4ac8a0, object, 0x16, 0, 0, object, board, ebp);
        port_call_with(&port, 0x4ac7d0, object, vertrix_lift_edx, 0, 0, object, board, ebp);
        port_set8(&port, object, 0x15c, 1);
        port_set8(&port, object, 0x15d, 0);
        port_call_with(&port, 0x4ac8f0, object, 0x456ca0, 0, 0, object, board, ebp);
        edx = vertrix_lift_edx;
        port_set32(&port, object, 0x124, 1);
        port_set32(&port, object, 4, port_u32(&port, board, 4));
        port_set32(&port, object, 0x64, row);
        eax = board + row * 0x10;
        port_set32(&port, eax + column * 4, 0x15c, object);
    }
    port_set8(&port, ebp, -0x14u, slot);
    return port_return(&port, eax, edx);
}
