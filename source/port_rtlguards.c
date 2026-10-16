#include "port_rtlguards.h"

/* Guarded buffer advances, item broadcasts, window message routes and object teardown. */

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

/* Original 0x4b50d0: under a guard frame (0x4ec1ec, 0x5180b0), when the reader eax's position
 * +0x190 is short of its end +0x18c, 0x4b4fb0 moves it on by edx (to the end when fewer are
 * left). eax 1 when it moved, else 0. */
uint32_t vertrix_port_reader_advance_4b50d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t reader = entry->eax;
    uint32_t count = entry->edx;
    uint32_t place;
    uint32_t end;
    uint32_t edx;
    uint32_t moved = 0;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ebx);
    port_set32(&port, ebp, -8, entry->ecx);
    port_set32(&port, ebp, -0xc, entry->esi);
    port_set32(&port, ebp, -0x10, entry->edi);
    port_set32(&port, ebp, -0x20, port.env.chain);
    port.env.chain = ebp - 0x20;
    port_set32(&port, ebp, -0x1c, 0x4ec1ec);
    port_set32(&port, ebp, -0x18, 0x5180b0);
    port_set32(&port, ebp, -0x14, 0);
    edx = port_u32(&port, reader, 0x190);
    end = port_u32(&port, reader, 0x18c);
    if (edx < end)
    {
        place = end - edx > count ? edx + count : end;
        moved = 1;
        port_call_with(&port, 0x4b4fb0, reader, place, 1, reader, count, 0, ebp);
        edx = vertrix_lift_edx;
    }
    port.env.chain = port_u32(&port, ebp, -0x20);
    return port_return(&port, moved, edx);
}

/* Original 0x42b290: each of the three items of eax at +0x15c, then of the three at +0x168, given
 * edx by its class (+0x158) method +8. eax and edx as the last step leaves them. */
uint32_t vertrix_port_items_broadcast_both_42b290(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t self = entry->eax;
    uint32_t value = entry->edx;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t esi = entry->esi;
    uint32_t slot;
    uint32_t item;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ebx);
    port_set32(&port, ebp, -8, entry->ecx);
    port_set32(&port, ebp, -0xc, entry->esi);
    port_set32(&port, ebp, -0x10, entry->edi);
    port_set32(&port, ebp, -0x14, self);
    for (slot = self; slot != self + 0xc && !port.env.failed; slot += 4)
    {
        edx = port_u32(&port, slot, 0x15c);
        if (edx != 0)
        {
            esi = port_u32(&port, edx, 0x158);
            eax = port_call_with(&port, port_u32(&port, esi, 8), edx, value, value, slot, esi,
                                 self + 0xc, ebp);
            edx = vertrix_lift_edx;
        }
    }
    for (slot = self; slot != self + 0xc && !port.env.failed; slot += 4)
    {
        item = port_u32(&port, slot, 0x168);
        if (item != 0)
        {
            esi = port_u32(&port, item, 0x158);
            eax = port_call_with(&port, port_u32(&port, esi, 8), item, value, value, slot, esi,
                                 self + 0xc, ebp);
            edx = vertrix_lift_edx;
        }
    }
    return port_return(&port, eax, edx);
}

/* Original 0x4cff20 (ret 0xc): a command (first argument, not negative) matching the application's
 * (0x4ce220) pending +0x24 against the third argument's +0xc ends it: its handle +0x2c freed
 * (0x4f1b08) and cleared, 0x4cfd20 told and +0x24 cleared (eax 0); otherwise 0x4f18ec of that
 * handle with the three arguments. */
uint32_t vertrix_port_rtl_command_finish_4cff20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8 + 12];
    uint32_t third;
    uint32_t application;
    uint32_t edx;
    uint32_t eax;
    uint32_t args[4];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set32(&port, entry->esp - 4, 0, entry->ebx);
    port_set32(&port, entry->esp - 8, 0, entry->esi);
    third = port_u32(&port, entry->esp, 0xc);
    application = port_call_with(&port, 0x4ce220, entry->eax, entry->edx, entry->ebx, entry->ecx,
                                 third, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    if ((int32_t)port_u32(&port, entry->esp, 4) >= 0)
    {
        edx = port_u32(&port, application, 0x24);
        if (edx == port_u32(&port, third, 0xc))
        {
            args[0] = port_u32(&port, application, 0x2c);
            eax = call_frame(&port, 0x4f1b08, application, edx, application, entry->ecx, third,
                             entry->edi, entry->ebp, args, 1);
            port_set32(&port, application, 0x2c, 0);
            args[0] = port_u32(&port, third, 0xc);
            call_frame(&port, 0x4cfd20, eax, vertrix_lift_edx, application, entry->ecx, third,
                       entry->edi, entry->ebp, args, 1);
            port_set32(&port, application, 0x24, 0);
            return port_return(&port, 0, vertrix_lift_edx);
        }
    }
    args[0] = port_u32(&port, application, 0x2c);
    args[1] = port_u32(&port, entry->esp, 4);
    args[2] = port_u32(&port, entry->esp, 8);
    args[3] = third;
    eax = call_frame(&port, 0x4f18ec, application, edx, application, entry->ecx, third, entry->edi,
                     entry->ebp, args, 4);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4dd4a0: the object eax torn down by the flags dl: bit 2 hands it to 0x4ccb9f (class
 * 0x519780) and 0x4ca040; otherwise, under a guard frame, it takes the class 0x51b5d4, its handle
 * (0x4dd460, when +4 is set) is closed (0x4f17dc), it takes the class 0x517454 and bit 1 frees it
 * (0x4ca050). eax the object. */
uint32_t vertrix_port_rtl_handle_destroy_4dd4a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x3c;
    uint32_t self = entry->eax;
    uint32_t flags = entry->edx;
    uint32_t eax;
    uint32_t edx = entry->edx;
    uint32_t args[1];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp - 4, 0, entry->ebx);
    port_set32(&port, entry->esp - 8, 0, entry->ecx);
    port_set32(&port, esp, 0x30, flags);
    if ((flags & 4) != 0)
    {
        port_set32(&port, esp, 0x20, 1);
        port_set32(&port, esp, 0, self);
        eax = port_call_with(&port, 0x4ccb9f, self, 0x519780, self, entry->ecx, entry->esi,
                             entry->edi, entry->ebp);
        port_set32(&port, esp, 0x20, 0);
        port_call_with(&port, 0x4ca040, eax, vertrix_lift_edx, self, entry->ecx, entry->esi,
                       entry->edi, entry->ebp);
        return port_return(&port, self, vertrix_lift_edx);
    }
    port_set32(&port, self, 0, 0x51b5d4);
    port_set32(&port, esp, 0x24, self);
    port_set8(&port, esp, 0x28, flags);
    port_set32(&port, esp, 0x14, port.env.chain);
    port.env.chain = esp + 0x14;
    port_set32(&port, esp, 0x18, 0x4ec1ec);
    port_set32(&port, esp, 0x1c, 0x51afe8);
    port_set32(&port, esp, 0x20, 3);
    eax = (self & 0xffffff00u) | (flags & 0xff);
    if (port_u32(&port, self, 4) != 0)
    {
        eax = port_call_with(&port, 0x4dd460, self, edx, self, entry->ecx, entry->esi, entry->edi,
                             entry->ebp);
        args[0] = eax;
        call_frame(&port, 0x4f17dc, eax, vertrix_lift_edx, self, entry->ecx, entry->esi, entry->edi,
                   entry->ebp, args, 1);
        edx = vertrix_lift_edx;
    }
    port_set32(&port, esp, 0x20, 0);
    port_set32(&port, self, 0, 0x517454);
    if ((flags & 2) != 0)
    {
        port_call_with(&port, 0x4ca050, self, edx, self, entry->ecx, entry->esi, entry->edi,
                       entry->ebp);
        edx = vertrix_lift_edx;
    }
    port.env.chain = port_u32(&port, esp, 0x14);
    return port_return(&port, self, edx);
}

/* Unless eax's +0x274 is 0xff, from the row 0x42a200 gives (its edx) each set item of its table
 * (+0x15c, four a row, rows 0x10 apart up to 0x70) handed edx by its class (+0x158) method. */
static uint32_t table_items_call(PORT_SIGNATURE, uint32_t method)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t self = entry->eax;
    uint32_t value = entry->edx;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t row;
    uint32_t base;
    uint32_t ecx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ebx);
    port_set32(&port, ebp, -8, entry->ecx);
    port_set32(&port, ebp, -0xc, entry->esi);
    port_set32(&port, ebp, -0x10, entry->edi);
    port_set32(&port, ebp, -0x18, self);
    if (port_u8(&port, self, 0x274) == 0xff)
    {
        return port_return(&port, eax, edx);
    }
    eax = port_call_with(&port, 0x42a200, self, 0, value, entry->ecx, entry->esi, entry->edi, ebp);
    row = vertrix_lift_edx;
    port_set32(&port, ebp, -0x14, row);
    do
    {
        base = self + row;
        for (ecx = 0; ecx != 0x10 && !port.env.failed; ecx += 4)
        {
            eax = base + ecx;
            edx = port_u32(&port, eax, 0x15c);
            if (edx != 0)
            {
                uint32_t methods = port_u32(&port, edx, 0x158);
                eax = port_call_with(&port, port_u32(&port, methods, method), edx, value, value,
                                     ecx, methods, base, ebp);
                edx = vertrix_lift_edx;
            }
        }
        row = port_u32(&port, ebp, -0x14) + 0x10;
        port_set32(&port, ebp, -0x14, row);
    } while (row != 0x70 && !port.env.failed);
    return port_return(&port, eax, edx);
}

/* Original 0x429a10: the table items' method +8 with edx. */
uint32_t vertrix_port_table_items_set_429a10(PORT_SIGNATURE)
{
    return table_items_call(calls, services, globals, entry, 8);
}

/* Original 0x429af0: the table items' method +0x10 with edx. */
uint32_t vertrix_port_table_items_apply_429af0(PORT_SIGNATURE)
{
    return table_items_call(calls, services, globals, entry, 0x10);
}
