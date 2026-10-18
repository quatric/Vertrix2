#include "rtlslots.h"

/* Application slots, surface name lookups and window message dispatch. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* This thread's value for the slot key eax, made by the constructor edx and stored (0x4dbd20) when
 * it has none (the key allocated on first use by 0x4dbb30, the slot table at 0x5c77a8 made by
 * 0x4dbac0; the value looked up in the thread's array from TlsGetValue, slot 0x4f1cdc). */
static uint32_t thread_slot(PORT_SIGNATURE)
{
    enum
    {
        SLOTS = 0x5c77a8,
        SLOTS_STORAGE = 0x5c7770
    };
    Port port;
    uint32_t key = entry->eax;
    uint32_t make = entry->edx;
    uint32_t edx = entry->edx;
    uint32_t ecx = entry->ecx;
    uint32_t table;
    uint32_t index;
    uint32_t value = 0;
    uint32_t argument;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, key, 0) == 0)
    {
        if (port_u32(&port, 0, SLOTS) == 0)
        {
            port_set32(&port, 0, SLOTS, port_call(&port, 0x4dbac0, SLOTS_STORAGE, 1, key, ecx));
            edx = vertrix_lift_edx;
        }
        port_set32(&port, key, 0,
                   port_call(&port, 0x4dbb30, port_u32(&port, 0, SLOTS), edx, key, ecx));
        edx = vertrix_lift_edx;
    }
    table = port_u32(&port, 0, SLOTS);
    argument = port_u32(&port, table, 0);
    index = port_u32(&port, key, 0);
    /* The thread's slot array through TlsGetValue: its count at +8, the values at +0xc. */
    table = port_call_stack(&port, 0x4f1cdc, table, edx, key, ecx, &argument, 1);
    edx = vertrix_lift_edx;
    if (table != 0 && (int32_t)index < (int32_t)port_u32(&port, table, 8))
    {
        value = port_u32(&port, port_u32(&port, table, 0xc), index * 4);
    }
    if (value != 0)
    {
        return port_return(&port, value, edx);
    }
    value = port_call(&port, make, 0, edx, key, 0);
    port_call(&port, 0x4dbd20, port_u32(&port, 0, SLOTS), port_u32(&port, key, 0), value, value);
    return port_return(&port, value, vertrix_lift_edx);
}

/* Original 0x4ce220: this thread's application block (slot 0x5c5c60, made by 0x4ce7c0); the
 * original continues into 0x4dbf80. */
uint32_t vertrix_port_rtl_application_4ce220(PORT_SIGNATURE)
{
    LiftEntry moved = *entry;
    moved.eax = 0x5c5c60;
    moved.edx = 0x4ce7c0;
    return thread_slot(calls, services, globals, &moved);
}

/* Original 0x47f1b0: under a guard frame (0x4ec1ec, 0x5168c8) and the lock 0x558c9c, the text edx
 * cleared (0x4ca280 of 0x50ee80) and, when 0x47f190 finds the surface of eax by ebx, set to its
 * name (+0x4c, 0x47fc50 into the frame, 0x4ca370). eax the text. */
uint32_t vertrix_port_surface_name_47f1b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x124
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t self = entry->eax;
    uint32_t text = entry->edx;
    uint32_t surface;
    uint32_t ebx = entry->ebx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t args[1];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ecx);
    port_set32(&port, ebp, -8, entry->esi);
    port_set32(&port, ebp, -0xc, entry->edi);
    port_set32(&port, ebp, -0x20, port.env.chain);
    port.env.chain = ebp - 0x20;
    port_set32(&port, ebp, -0x1c, 0x4ec1ec);
    port_set32(&port, ebp, -0x18, 0x5168c8);
    port_set32(&port, ebp, -0x14, 0);
    args[0] = 0x558c9c;
    call_frame(&port, 0x4f1b48, 0, 0x4ec1ec, ebx, 0x5168c8, text, self, ebp, args, 1);
    surface = port_call_with(&port, 0x47f190, self, ebx, ebx, 0x5168c8, text, self, ebp);
    ecx = surface;
    eax = port_call_with(&port, 0x4ca280, text, 0x50ee80, ebx, ecx, text, self, ebp);
    if (surface != 0)
    {
        ebx = port_u32(&port, surface, 0x4c);
        ecx = 0xffffffffu;
        port_call_with(&port, 0x47fc50, self, ebp - 0x120, ebx, ecx, text, self, ebp);
        eax = port_call_with(&port, 0x4ca370, text, ebp - 0x120, ebx, ecx, text, self, ebp);
    }
    args[0] = 0x558c9c;
    call_frame(&port, 0x4f1c40, eax, vertrix_lift_edx, ebx, ecx, text, self, ebp, args, 1);
    port.env.chain = port_u32(&port, ebp, -0x20);
    return port_return(&port, text, vertrix_lift_edx);
}

/* Original 0x4d0740: the message ebx for the window eax: a notification (kind 1) finds the window
 * of its handle (the application's +0x58 when it is the application's +0x54 handle, else
 * 0x4f19b0 of eax's +0x1c; 0x4e1210), and that control by the message's +8 (0x4d06d0) gets its
 * method +0x18; any other kind finds its control (0x4d1a50 with +4 and 1), which may take it
 * (0x4d1e50 of 0). What is left goes to 0x4cf850. */
uint32_t vertrix_port_rtl_message_dispatch_4d0740(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t message = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t eax;
    uint32_t edx;
    uint32_t args[3];
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, message, 0) == 1)
    {
        eax = port_call_with(&port, 0x4ce220, self, entry->edx, message, ecx, self, entry->edi,
                             entry->ebp);
        edx = port_u32(&port, eax, 0x54);
        if (edx == port_u32(&port, self, 0x1c))
        {
            args[0] = port_u32(&port, eax, 0x58);
        }
        else
        {
            args[0] = port_u32(&port, self, 0x1c);
            eax = call_frame(&port, 0x4f19b0, eax, edx, message, ecx, self, entry->edi, entry->ebp,
                             args, 1);
            edx = vertrix_lift_edx;
            args[0] = eax;
        }
        eax = call_frame(&port, 0x4e1210, eax, edx, message, ecx, self, entry->edi, entry->ebp,
                         args, 1);
        eax = port_call_with(&port, 0x4d06d0, eax, port_u32(&port, message, 8), message, ecx, self,
                             entry->edi, entry->ebp);
        edx = vertrix_lift_edx;
        if (eax != 0)
        {
            ecx = port_u32(&port, eax, 0);
            port_call_with(&port, port_u32(&port, ecx, 0x18), eax, message, message, ecx, self,
                           entry->edi, entry->ebp);
            edx = vertrix_lift_edx;
        }
    }
    else
    {
        args[0] = port_u32(&port, self, 0x1c);
        args[1] = port_u32(&port, message, 4);
        args[2] = 1;
        eax = call_frame(&port, 0x4d1a50, args[1], entry->edx, message, ecx, self, entry->edi,
                         entry->ebp, args, 3);
        edx = vertrix_lift_edx;
        if (eax != 0)
        {
            eax =
                port_call_with(&port, 0x4d1e50, eax, 0, message, ecx, self, entry->edi, entry->ebp);
            edx = vertrix_lift_edx;
            if (eax != 0)
            {
                return port_return(&port, eax, edx);
            }
        }
    }
    eax = port_call_with(&port, 0x4cf850, self, edx, message, ecx, self, entry->edi, entry->ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}
