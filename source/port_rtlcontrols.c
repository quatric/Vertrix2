#include "port_rtlcontrols.h"

/* Control message forwarding and form visibility. */

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

/* Original 0x4d1710: the message edx (its low word the command) of the control eax from the
 * window ebx. Without a window a command is sent to the control's method +0x14 with the record
 * 0x4d16b0 fills in the frame, and when that record's result is set sent again plain; nothing
 * without a command. A window of the current control's (0x4ce220 +0xbc against the control's
 * +0x1c) or one 0x4d1e80 handles gives 1; otherwise the command is sent plain. */
uint32_t vertrix_port_control_command_4d1710(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
    };
    Port port;
    uint32_t esp = entry->esp - BELOW;
    uint32_t control = entry->eax;
    uint32_t window = entry->ebx;
    uint32_t command = entry->edx & 0xffff;
    uint32_t high = (entry->edx >> 16) & 0xffff;
    uint32_t zero[1] = {0};
    uint32_t eax;
    uint32_t ebx = high;
    uint32_t vtable;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ecx);
    port_set32(&port, entry->esp, -8u, entry->esi);
    port_set32(&port, entry->esp, -0xcu, entry->edi);
    port_set32(&port, entry->esp, -0x10u, entry->ebp);
    if (window == 0)
    {
        if (command == 0)
        {
            return port_return(&port, 0, entry->edx);
        }
        call_frame(&port, 0x4d16b0, esp, entry->edx, 0xffffffffu, esp, control, command, 0, NULL,
                   0);
        port_set32(&port, esp, 0, command);
        vtable = port_u32(&port, control, 0);
        eax = call_frame(&port, port_u32(&port, vtable, 0x14), control, command, 0xffffffffu, esp,
                         control, command, vtable, zero, 1);
        if (port_u32(&port, esp, 0x28) == 0)
        {
            return port_return(&port, 1, vertrix_lift_edx);
        }
        ebx = 0;
    }
    else
    {
        uint32_t args[2] = {window, 0};
        eax = call_frame(&port, 0x4ce220, high, entry->edx, high, entry->ecx, control, command,
                         window, NULL, 0);
        eax = port_u32(&port, eax, 0xbc);
        if (eax == port_u32(&port, control, 0x1c))
        {
            return port_return(&port, 1, vertrix_lift_edx);
        }
        eax = call_frame(&port, 0x4d1e80, eax, vertrix_lift_edx, high, entry->ecx, control, command,
                         window, args, 2);
        if (eax != 0)
        {
            return port_return(&port, 1, vertrix_lift_edx);
        }
        if (command == 0)
        {
            return port_return(&port, eax, vertrix_lift_edx);
        }
    }
    vtable = port_u32(&port, control, 0);
    eax = call_frame(&port, port_u32(&port, vtable, 0x14), control, command, ebx, 0, control,
                     command, vtable, zero, 1);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4d5390: the control edx shown (ebx set) or hidden in its form (0x4d63b0), ecx when it
 * is the form's own: a form's control goes through its method +0xc8 and the form's flags +0xb8 get
 * 0xc; any other is repositioned (0x4ccd80 with show 0x57 or hide 0x97) and put through +0xc8,
 * the form told +0xcc (0) unless it is shown and still visible (0x4d63d0). For a visible control
 * the form's active state +0x88 follows: the window +0x70's method +0xe4 (else whether it is
 * shown) decides between 8 or 0 by the form's +0xcc or 0x4ccdd0. */
uint32_t vertrix_port_form_control_show_4d5390(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint32_t esp = entry->esp - BELOW;
    uint32_t control = entry->edx;
    uint32_t shown = entry->ebx;
    uint32_t form;
    uint32_t eax;
    uint32_t ecx;
    uint32_t ebx;
    uint32_t vtable;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->esi);
    port_set32(&port, entry->esp, -8u, entry->edi);
    port_set32(&port, entry->esp, -0xcu, entry->ebp);
    port_set32(&port, esp, 0, entry->ecx);
    form = call_frame(&port, 0x4d63b0, control, entry->edx, entry->ebx, entry->ecx, entry->esi,
                      control, shown, NULL, 0);
    ebx = 0;
    if (port_u32(&port, esp, 0) != 0)
    {
        ebx = port_u32(&port, vertrix_lift_edx, 0);
        call_frame(&port, port_u32(&port, ebx, 0xc8), control, shown, ebx, form, form, control,
                   shown, NULL, 0);
        port_set8(&port, form, 0xb8, port_u8(&port, form, 0xb8) | 0xc);
    }
    else
    {
        uint32_t args[3] = {0, 0, (entry->ebx != 0 ? 0x40 : 0x80) | 0x17};
        int skip;
        call_frame(&port, 0x4ccd80, control, 0, 0, 0, form, control, shown, args, 3);
        vtable = port_u32(&port, control, 0);
        call_frame(&port, port_u32(&port, vtable, 0xc8), control, shown, 0, vtable, form, control,
                   shown, NULL, 0);
        skip = 0;
        if (shown == 0)
        {
            skip = call_frame(&port, 0x4d63d0, control, vertrix_lift_edx, 0, vtable, form, control,
                              shown, NULL, 0) != 0;
        }
        if (!skip)
        {
            vtable = port_u32(&port, form, 0);
            call_frame(&port, port_u32(&port, vtable, 0xcc), form, 0, 0, vtable, form, control,
                       shown, NULL, 0);
        }
    }
    eax = call_frame(&port, 0x4d63d0, control, vertrix_lift_edx, ebx, form, form, control, shown,
                     NULL, 0);
    if (eax == 0)
    {
        return port_return(&port, eax, vertrix_lift_edx);
    }
    if (port_u32(&port, control, 0x70) != 0)
    {
        uint32_t window = port_u32(&port, control, 0x70);
        vtable = port_u32(&port, window, 0);
        eax = call_frame(&port, port_u32(&port, vtable, 0xe4), window, vertrix_lift_edx, ebx,
                         vtable, form, control, shown, NULL, 0);
    }
    else
    {
        eax = shown != 0 ? 1 : 0;
    }
    ecx = eax;
    if (eax == 1 && shown != 0)
    {
        port_set32(&port, form, 0x88, 0xffffffffu);
        if (port_u32(&port, esp, 0) != 0)
        {
            port_set32(&port, form, 0x88, 8);
            vtable = port_u32(&port, form, 0);
            eax = call_frame(&port, port_u32(&port, vtable, 0xcc), form, 0, ebx, vtable, form,
                             control, shown, NULL, 0);
            return port_return(&port, eax, vertrix_lift_edx);
        }
        eax = call_frame(&port, 0x4ccdd0, form, 8, ebx, ecx, form, control, shown, NULL, 0);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    if (ecx == 0)
    {
        port_set32(&port, form, 0x88, 0xffffffffu);
        if (port_u32(&port, esp, 0) != 0)
        {
            port_set32(&port, form, 0x88, 0);
            return port_return(&port, 0, vertrix_lift_edx);
        }
        eax = call_frame(&port, 0x4ccdd0, form, 0, ebx, 0, form, control, shown, NULL, 0);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    if (port_u32(&port, esp, 0) == 0)
    {
        vtable = port_u32(&port, form, 0);
        eax = call_frame(&port, port_u32(&port, vtable, 0xcc), form, 0, ebx, vtable, form, control,
                         shown, NULL, 0);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4dbb30: a free slot of the handle table eax taken under its lock +0x20 (imports
 * 0x4f1b48/0x4f1c40): the hint +0xc when free, else the first free from 1; with none the table
 * +0x14 (8 bytes a slot, +8 slots) grows by 32 in global memory (0x4f1c0c, or 0x4f1c20, 0x4f1c2c
 * and 0x4f1c28; out of memory relocks it, unlocks the table and raises 0x4d9510), the new slots
 * cleared (0x4eb5c0). The slot is marked used, the hint set past it and the high mark +0x10 kept.
 * eax the slot. edx kept. */
uint32_t vertrix_port_handle_table_take_4dbb30(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t esp = entry->esp - BELOW;
    uint32_t table = entry->eax;
    uint32_t lock = entry->eax + 0x20;
    uint32_t capacity;
    uint32_t slot;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t ebp = entry->ebp;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->ecx);
    port_set32(&port, entry->esp, -0xcu, entry->edx);
    port_set32(&port, entry->esp, -0x10u, entry->esi);
    port_set32(&port, entry->esp, -0x14u, entry->edi);
    port_set32(&port, entry->esp, -0x18u, entry->ebp);
    {
        uint32_t args[1] = {lock};
        call_frame(&port, 0x4f1b48, lock, entry->edx, ebx, ecx, entry->esi, table, ebp, args, 1);
    }
    capacity = port_u32(&port, table, 8);
    edx = capacity;
    slot = port_u32(&port, table, 0xc);
    if (!((int32_t)slot < (int32_t)capacity &&
          (port_u8(&port, port_u32(&port, table, 0x14) + slot * 8, 0) & 1) == 0))
    {
        slot = 1;
        if ((int32_t)capacity > 1)
        {
            eax = port_u32(&port, table, 0x14) + 8;
            while ((port_u8(&port, eax, 0) & 1) != 0 && !port.env.failed)
            {
                slot++;
                eax += 8;
                if ((int32_t)slot >= (int32_t)capacity)
                {
                    break;
                }
            }
        }
        if ((int32_t)slot >= (int32_t)capacity)
        {
            uint32_t memory;
            ebp = port_u32(&port, table, 8) + 0x20;
            port_set32(&port, esp, 0, ebp * 8);
            eax = ebp * 8;
            if (port_u32(&port, table, 0x14) == 0)
            {
                uint32_t args[2] = {0x2002, ebp * 8};
                eax = call_frame(&port, 0x4f1c0c, ebp * 8, capacity, ebx, ecx, slot, table, ebp,
                                 args, 2);
            }
            else
            {
                uint32_t args[3] = {port_u32(&port, table, 0x14), 0, 0};
                ebx =
                    call_frame(&port, 0x4f1c20, eax, capacity, ebx, ecx, slot, table, ebp, args, 1);
                args[0] = ebx;
                eax = call_frame(&port, 0x4f1c2c, ebx, vertrix_lift_edx, ebx, ecx, slot, table, ebp,
                                 args, 1);
                args[0] = ebx;
                args[1] = port_u32(&port, esp, 0);
                args[2] = 0x2002;
                eax = call_frame(&port, 0x4f1c28, eax, vertrix_lift_edx, ebx, ecx, slot, table, ebp,
                                 args, 3);
            }
            ebx = eax;
            if (ebx == 0)
            {
                uint32_t args[1] = {port_u32(&port, table, 0x14)};
                eax = call_frame(&port, 0x4f1c20, eax, vertrix_lift_edx, ebx, ecx, slot, table, ebp,
                                 args, 1);
                args[0] = eax;
                call_frame(&port, 0x4f1c24, eax, vertrix_lift_edx, ebx, ecx, slot, table, ebp, args,
                           1);
                args[0] = lock;
                eax = call_frame(&port, 0x4f1c40, lock, vertrix_lift_edx, ebx, ecx, slot, table,
                                 ebp, args, 1);
                eax = call_frame(&port, 0x4d9510, eax, vertrix_lift_edx, ebx, ecx, slot, table, ebp,
                                 NULL, 0);
            }
            {
                uint32_t args[1] = {ebx};
                memory = call_frame(&port, 0x4f1c24, eax, vertrix_lift_edx, ebx, ecx, slot, table,
                                    ebp, args, 1);
            }
            ecx = memory;
            call_frame(&port, 0x4eb5c0, port_u32(&port, table, 8) * 8 + memory, 0,
                       (ebp - port_u32(&port, table, 8)) * 8, memory, slot, table, ebp, NULL, 0);
            edx = vertrix_lift_edx;
            ebx = (ebp - port_u32(&port, table, 8)) * 8;
            port_set32(&port, table, 8, ebp);
            port_set32(&port, table, 0x14, memory);
        }
    }
    if ((int32_t)slot >= (int32_t)port_u32(&port, table, 0x10))
    {
        port_set32(&port, table, 0x10, slot + 1);
    }
    eax = port_u32(&port, table, 0x14);
    port_set8(&port, eax + slot * 8, 0, port_u8(&port, eax + slot * 8, 0) | 1);
    port_set32(&port, table, 0xc, slot + 1);
    {
        uint32_t args[1] = {lock};
        call_frame(&port, 0x4f1c40, slot + 1, edx, ebx, ecx, slot, lock, ebp, args, 1);
    }
    return port_return(&port, slot, entry->edx);
}
