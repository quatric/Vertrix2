#include "port_rtlgrids.h"

/* Control colour messages, brush set-up and board column settling. */

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

/* Original 0x4d73b0: the colour message edx for the window eax from the control ebx (kind ecx):
 * the control's own answer (0x4d1e50 into the frame) when it has one, else 0x4d2540 with the
 * message's +4, the control's handle +0x1c (0 without one), ecx and this thread's hook record's
 * (0x4dc030 of 0x5c5c28) +4 and +8, answering the record's +4, or 0x4cf850 when it declines. */
uint32_t vertrix_port_rtl_control_colour_4d73b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 0xc;
    uint32_t self = entry->eax;
    uint32_t message = entry->edx;
    uint32_t control = entry->ebx;
    uint32_t record;
    uint32_t eax;
    uint32_t args[5];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp - 4, 0, entry->esi);
    port_set32(&port, entry->esp - 8, 0, entry->edi);
    port_set32(&port, ebp, 0, entry->ebp);
    eax =
        port_call_with(&port, 0x4d1e50, control, ebp - 8, control, entry->ecx, self, message, ebp);
    if (eax != 0)
    {
        return port_return(&port, port_u32(&port, ebp, -8), vertrix_lift_edx);
    }
    record = port_call_with(&port, 0x4dc030, 0x5c5c28, 0x4ccc40, control, entry->ecx, self, message,
                            ebp);
    port_set32(&port, ebp, -4, record);
    eax = control != 0 ? port_u32(&port, control, 0x1c) : 0;
    args[0] = port_u32(&port, message, 4);
    args[1] = eax;
    args[2] = entry->ecx;
    args[3] = port_u32(&port, record, 4);
    args[4] = port_u32(&port, record, 8);
    eax = call_frame(&port, 0x4d2540, eax, vertrix_lift_edx, control, entry->ecx, self, message,
                     ebp, args, 5);
    if (eax == 0)
    {
        eax = port_call_with(&port, 0x4cf850, self, vertrix_lift_edx, control, entry->ecx, self,
                             message, ebp);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    return port_return(&port, port_u32(&port, port_u32(&port, ebp, -4), 4), vertrix_lift_edx);
}

/* Original 0x4d2540 (ret 0x14): the colour message kind (third argument, 2..4 or 6) for the device
 * context (first) of a control (second; kind 2 only for a list box, 0x4dc290 of 2) with a brush
 * (fourth): its colour (0x4f180c into the frame) set as the text colour (0x4f1880) and the
 * background (fifth, the stock 8 by 0x4f19e0 when -1) set by 0x4f18a8. eax 1, or 0 when not. */
uint32_t vertrix_port_rtl_control_brush_4d2540(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint8_t stack[BELOW + 8 + 20];
    uint32_t esp = entry->esp - 0xc;
    uint32_t context;
    uint32_t kind;
    uint32_t background;
    uint32_t eax;
    uint32_t edx = entry->edx;
    uint32_t args[3];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 5);
    context = port_u32(&port, entry->esp, 4);
    kind = port_u32(&port, entry->esp, 0xc);
    if (context == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    if (port_u32(&port, entry->esp, 0x10) == 0 || kind == 1 || kind == 0 || kind == 5)
    {
        return port_return(&port, 0, entry->edx);
    }
    if (kind == 2)
    {
        args[0] = port_u32(&port, entry->esp, 8);
        args[1] = 2;
        eax = call_frame(&port, 0x4dc290, 2, entry->edx, entry->ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp, args, 2);
        edx = vertrix_lift_edx;
        if (eax == 0)
        {
            return port_return(&port, 0, edx);
        }
    }
    args[0] = port_u32(&port, entry->esp, 0x10);
    args[1] = 0xc;
    args[2] = esp;
    eax = call_frame(&port, 0x4f180c, esp, edx, entry->ebx, entry->ecx, entry->esi, entry->edi,
                     entry->ebp, args, 3);
    args[0] = context;
    args[1] = port_u32(&port, esp, 4);
    eax = call_frame(&port, 0x4f1880, eax, vertrix_lift_edx, entry->ebx, entry->ecx, entry->esi,
                     entry->edi, entry->ebp, args, 2);
    background = port_u32(&port, entry->esp, 0x14);
    if (background == 0xffffffffu)
    {
        args[0] = 8;
        background = call_frame(&port, 0x4f19e0, eax, vertrix_lift_edx, entry->ebx, entry->ecx,
                                entry->esi, entry->edi, entry->ebp, args, 1);
        eax = background;
        port_set32(&port, entry->esp, 0x14, background);
    }
    args[0] = context;
    args[1] = background;
    call_frame(&port, 0x4f18a8, eax, vertrix_lift_edx, entry->ebx, entry->ecx, entry->esi,
               entry->edi, entry->ebp, args, 2);
    return port_return(&port, 1, vertrix_lift_edx);
}

/* Original 0x432980: the board eax (five columns of thirteen bytes) settled when 0x4328e0 marks
 * cells in the frame (a dword a cell): from the bottom, each marked cell's piece (1) drops past
 * the empty cells (0xff) below it, leaving its place empty. edx kept. */
uint32_t vertrix_port_board_settle_432980(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x128
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t marks = ebp - 0x128;
    uint32_t eax;
    uint32_t column;
    uint32_t offset;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ebx);
    port_set32(&port, ebp, -8, entry->ecx);
    port_set32(&port, ebp, -0xc, entry->edx);
    port_set32(&port, ebp, -0x10, entry->esi);
    port_set32(&port, ebp, -0x14, entry->edi);
    eax = port_call_with(&port, 0x4328e0, board, marks, entry->ebx, board, entry->esi, entry->edi,
                         ebp);
    if (eax == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    column = board;
    offset = 0;
    port_set32(&port, ebp, -0x20, column);
    port_set32(&port, ebp, -0x24, offset);
    do
    {
        int32_t row;
        uint32_t cell = column + 0xb;
        uint32_t edi = offset + 0x2c;
        eax = column;
        port_set32(&port, ebp, -0x1c, column);
        port_set32(&port, ebp, -0x18, column);
        for (row = 0xb; row >= 0 && !port.env.failed; row--, edi -= 4, cell--)
        {
            if (port_u32(&port, marks, edi) != 1)
            {
                continue;
            }
            eax = (uint32_t)row + 1;
            if ((int32_t)eax < 0xd)
            {
                uint32_t place = column + eax;
                while (port_u8(&port, place, 0) == 0xff && !port.env.failed)
                {
                    eax++;
                    place++;
                    if ((int32_t)eax >= 0xd)
                    {
                        break;
                    }
                }
            }
            eax = eax - 1 + column;
            port_set8(&port, eax, 0, port_u8(&port, cell, 0));
            port_set8(&port, cell, 0, 0xff);
        }
        offset += 0x34;
        column += 0xd;
        port_set32(&port, ebp, -0x24, offset);
        port_set32(&port, ebp, -0x20, column);
    } while (offset != 0x104 && !port.env.failed);
    return port_return(&port, eax, entry->edx);
}
