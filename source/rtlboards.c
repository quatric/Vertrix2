#include "rtlboards.h"

/* JPEG block arrays, board drops, piece choices, and script loads. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4c54d0: as 0x4c5400 for a JPEG block array: its rows of +8 blocks (128 bytes each)
 * moved between memory and the backing store (write with ebx set, method +0x34, else read +0x30)
 * in steps of +0x14 rows clipped to +0x10, +0x1c and +4. */
uint32_t vertrix_port_jpeg_barray_io_4c54d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t array = entry->edx;
    uint32_t done = 0;
    uint32_t eax;
    uint32_t edx = entry->edx;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x18u, entry->eax);
    port_set32(&port, ebp, -0x24u, entry->ebx);
    eax = port_u32(&port, array, 8) << 7;
    port_set32(&port, ebp, -0x20u, eax);
    eax = port_u32(&port, array, 0x18) * port_u32(&port, ebp, -0x20u);
    port_set32(&port, ebp, -0x10u, eax);
    if ((int32_t)port_u32(&port, array, 0x10) <= 0)
    {
        return port_return(&port, eax, edx);
    }
    port_set32(&port, ebp, -0x1cu, array + 0x30);
    do
    {
        uint32_t ecx;
        uint32_t bytes;
        eax = port_u32(&port, array, 0x10) - done;
        ecx = port_u32(&port, array, 0x14);
        if ((int32_t)eax > (int32_t)ecx)
        {
            eax = ecx;
        }
        edx = port_u32(&port, array, 0x18) + done;
        ecx = port_u32(&port, array, 0x1c) - edx;
        if ((int32_t)eax >= (int32_t)ecx)
        {
            eax = ecx;
        }
        ecx = port_u32(&port, array, 4) - edx;
        edx = ecx;
        if ((int32_t)eax >= (int32_t)ecx)
        {
            eax = ecx;
        }
        if ((int32_t)eax <= 0)
        {
            break;
        }
        bytes = port_u32(&port, ebp, -0x20u) * eax;
        port_set32(&port, ebp, -0x14u, bytes);
        args[0] = bytes;
        call_frame(&port, port_u32(&port, array, port_u32(&port, ebp, -0x24u) != 0 ? 0x34 : 0x30),
                   port_u32(&port, ebp, -0x18u), port_u32(&port, ebp, -0x1cu),
                   port_u32(&port, port_u32(&port, array, 0), done * 4),
                   port_u32(&port, ebp, -0x10u), array, done, ebp, args, 1);
        port_set32(&port, ebp, -0x10u, port_u32(&port, ebp, -0x10u) + port_u32(&port, ebp, -0x14u));
        eax = port_u32(&port, array, 0x14);
        edx = port_u32(&port, array, 0x10);
        done += eax;
    } while ((int32_t)done < (int32_t)edx && !port.env.failed);
    return port_return(&port, eax, edx);
}

/* Original 0x432a30: the byte board +0x1de of eax rebuilt from +0x220 (0x4327e0, ebx 0x41) and,
 * when 0x4328e0 marks cells in the frame, each marked cell of the five columns (from row 11 up)
 * moved one row down (+0x1df), its place emptied (0xff) and reported to 0x432ba0 (ebx the row
 * below, the column and row as stack arguments). eax as the loops leave it, edx kept. */
uint32_t vertrix_port_board_drop_marked_432a30(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x134
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t bytes = board + 0x1de;
    uint32_t cells = board + 0x220;
    uint32_t marks = ebp - 0x130;
    uint32_t eax;
    uint32_t args[2];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_call_with(&port, 0x4327e0, cells, bytes, 0x41, cells, board, bytes, ebp);
    eax = port_call_with(&port, 0x4328e0, bytes, marks, 0x41, cells, board, bytes, ebp);
    if (eax == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_set32(&port, ebp, -0x24u, cells);
    port_set32(&port, ebp, -0x28u, board);
    port_set32(&port, ebp, -0x20u, 0);
    port_set32(&port, ebp, -0x2cu, 0);
    do
    {
        uint32_t below = 0xc;
        uint32_t place;
        port_set32(&port, ebp, -0x1cu, port_u32(&port, ebp, -0x2cu) + 0x2c);
        port_set32(&port, ebp, -0x18u, 0xb);
        place = port_u32(&port, ebp, -0x28u) + 0xb;
        do
        {
            uint32_t row;
            if (port_u32(&port, marks, port_u32(&port, ebp, -0x1cu)) == 1)
            {
                uint32_t column = port_u32(&port, ebp, -0x20u);
                row = port_u32(&port, ebp, -0x18u);
                port_set8(&port, place, 0x1df, port_u8(&port, place, 0x1de));
                port_set8(&port, place, 0x1de, 0xff);
                args[0] = column;
                args[1] = row;
                cells = port_u32(&port, ebp, -0x24u);
                call_frame(&port, 0x432ba0, cells, column, below, cells, place, below, ebp, args,
                           2);
            }
            eax = port_u32(&port, ebp, -0x1cu) - 4;
            row = port_u32(&port, ebp, -0x18u) - 1;
            below--;
            place--;
            port_set32(&port, ebp, -0x1cu, eax);
            port_set32(&port, ebp, -0x18u, row);
            if ((int32_t)row < 0)
            {
                break;
            }
        } while (!port.env.failed);
        port_set32(&port, ebp, -0x2cu, port_u32(&port, ebp, -0x2cu) + 0x34);
        port_set32(&port, ebp, -0x28u, port_u32(&port, ebp, -0x28u) + 0xd);
        port_set32(&port, ebp, -0x20u, port_u32(&port, ebp, -0x20u) + 1);
    } while ((int32_t)port_u32(&port, ebp, -0x20u) < 5 && !port.env.failed);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x43d180: the three kinds of the player eax's next piece (0x43d130 draws one into a
 * frame byte) stored at edx, ebx and ecx: for the mode +0x4c8 0x2e three different kinds; 0x2a
 * three alike (the third 5 in mode 0x2d); 0x29 the first two drawn and the third as the second;
 * else all three drawn. eax as the last byte load leaves it. */
uint32_t vertrix_port_piece_kinds_43d180(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t mode;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
#define DRAW(slot)                                                                                 \
    port_call_with(&port, 0x43d130, player, ebp - (slot), entry->ebx, entry->ecx, player,          \
                   entry->edx, ebp)
    mode = port_u32(&port, player, 0x4c8);
    if (mode == 0x2e)
    {
        DRAW(0xc);
        eax = DRAW(0x14);
        while (port_u8(&port, ebp, -0x14u) == port_u8(&port, ebp, -0xcu) && !port.env.failed)
        {
            eax = DRAW(0x14);
        }
        do
        {
            eax = DRAW(0x10);
        } while ((port_u8(&port, ebp, -0x10u) == port_u8(&port, ebp, -0xcu) ||
                  port_u8(&port, ebp, -0x10u) == port_u8(&port, ebp, -0x14u)) &&
                 !port.env.failed);
        edx = vertrix_lift_edx;
    }
    else
    {
        eax = DRAW(0xc);
        mode = port_u32(&port, player, 0x4c8);
        if (mode == 0x2a)
        {
            eax = (eax & 0xffffff00u) | port_u8(&port, ebp, -0xcu);
            port_set8(&port, ebp, -0x10u, eax);
            port_set8(&port, ebp, -0x14u, eax);
        }
        else
        {
            eax = DRAW(0x14);
            mode = port_u32(&port, player, 0x4c8);
            if (mode == 0x29)
            {
                eax = (eax & 0xffffff00u) | port_u8(&port, ebp, -0x14u);
                port_set8(&port, ebp, -0x10u, eax);
            }
            else
            {
                eax = DRAW(0x10);
            }
        }
        mode = port_u32(&port, player, 0x4c8);
        if (mode == 0x2d)
        {
            port_set8(&port, ebp, -0x10u, 5);
        }
        edx = mode;
    }
#undef DRAW
    port_set8(&port, entry->edx, 0, port_u8(&port, ebp, -0xcu));
    port_set8(&port, entry->ebx, 0, port_u8(&port, ebp, -0x14u));
    eax = (eax & 0xffffff00u) | port_u8(&port, ebp, -0x10u);
    port_set8(&port, entry->ecx, 0, eax);
    return port_return(&port, eax, edx);
}

/* Copies the text at `from` (two bytes a step, to its terminator) to `to`; the source position
 * after it. */
static uint32_t copy_text(Port *port, uint32_t to, uint32_t from)
{
    for (;;)
    {
        uint32_t c = port_u8(port, from, 0);
        port_set8(port, to, 0, c);
        if (c == 0 || port->env.failed)
        {
            return from;
        }
        c = port_u8(port, from, 1);
        from += 2;
        port_set8(port, to, 1, c);
        to += 2;
        if (c == 0)
        {
            return from;
        }
    }
}

/* Original 0x423dc0: the script object of the file eax (or 0x50de11) loaded (0x423d70) when it
 * exists (0x45f590), then given the file edx (or 0x50de12) when that exists and is of the kind
 * 0x50de4c (0x489b40, 0x4798b0); the object or 0. */
uint32_t vertrix_port_script_object_open_423dc0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x220
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t first = ebp - 0x218;
    uint32_t second = ebp - 0x114;
    uint32_t esi;
    uint32_t object;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x10u, 0);
    port_set32(&port, ebp, -0x21cu, first);
    esi = copy_text(&port, first, entry->eax != 0 ? entry->eax : 0x50de11);
    port_set32(&port, ebp, -0x21cu, second);
    esi = copy_text(&port, second, entry->edx != 0 ? entry->edx : 0x50de12);
    if (port_call_with(&port, 0x45f590, first, entry->edx, entry->ebx, 0, esi, second, ebp) != 1)
    {
        return port_return(&port, port_u32(&port, ebp, -0x10u), vertrix_lift_edx);
    }
    object =
        port_call_with(&port, 0x423d70, first, vertrix_lift_edx, entry->ebx, 0, esi, second, ebp);
    port_set32(&port, ebp, -0x10u, object);
    if (object == 0 || vertrix_lift_edx == 0)
    {
        return port_return(&port, port_u32(&port, ebp, -0x10u), vertrix_lift_edx);
    }
    if (port_call_with(&port, 0x45f590, second, vertrix_lift_edx, entry->ebx, object, esi, second,
                       ebp) != 1)
    {
        return port_return(&port, port_u32(&port, ebp, -0x10u), vertrix_lift_edx);
    }
    if (port_call_with(&port, 0x489b40, second, 0x50de4c, entry->ebx, object, esi, second, ebp) !=
        1)
    {
        return port_return(&port, port_u32(&port, ebp, -0x10u), vertrix_lift_edx);
    }
    port_call_with(&port, 0x4798b0, object, second, entry->ebx, object, esi, second, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x10u), vertrix_lift_edx);
}
