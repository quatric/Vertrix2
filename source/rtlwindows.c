#include "rtlwindows.h"

/* Window class checks and message routing. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4dc290 (ret 8): 1 when the window (first argument) has the style low bits of the
 * second (0x4f19f0 of -16) and its class name (0x4f1968, ten bytes into the frame) is 0x505af0
 * (0x4f1d18), else 0. */
uint32_t vertrix_port_rtl_window_class_check_4dc290(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint8_t stack[BELOW + 8 + 8];
    uint32_t esp = entry->esp - 0xc;
    uint32_t window;
    uint32_t args[3];
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    window = port_u32(&port, entry->esp, 4);
    if (window == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    args[0] = window;
    args[1] = 0xfffffff0u;
    eax = call_frame(&port, 0x4f19f0, entry->eax, entry->edx, entry->ebx, entry->ecx, entry->esi,
                     entry->edi, entry->ebp, args, 2);
    if ((eax & 0xf) != port_u32(&port, entry->esp, 8))
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    args[0] = window;
    args[1] = esp;
    args[2] = 0xa;
    call_frame(&port, 0x4f1968, esp, vertrix_lift_edx, entry->ebx, entry->ecx, entry->esi,
               entry->edi, entry->ebp, args, 3);
    args[0] = esp;
    args[1] = 0x505af0;
    eax = call_frame(&port, 0x4f1d18, esp, vertrix_lift_edx, entry->ebx, entry->ecx, entry->esi,
                     entry->edi, entry->ebp, args, 2);
    return port_return(&port, eax == 0 ? 1 : 0, vertrix_lift_edx);
}

/* Original 0x4d5c70: when the active form (0x4cbe80, its method +0x78) is eax, the message edx's
 * handler (+0x24's method +4) gets the message and whether eax's +0x50 is set; otherwise the
 * message's +0x18 is set. */
uint32_t vertrix_port_rtl_form_route_4d5c70(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t message = entry->edx;
    uint32_t eax;
    uint32_t handler;
    port_open(&port, calls, services, globals, entry);
    eax = port_call_with(&port, 0x4cbe80, self, message, message, entry->ecx, self, entry->edi,
                         entry->ebp);
    if (eax != 0)
    {
        eax = port_call_with(&port, 0x4cbe80, eax, vertrix_lift_edx, message, entry->ecx, self,
                             entry->edi, entry->ebp);
        eax = port_call_with(&port, port_u32(&port, port_u32(&port, eax, 0), 0x78), eax,
                             port_u32(&port, eax, 0), message, entry->ecx, self, entry->edi,
                             entry->ebp);
    }
    if (eax != self)
    {
        port_set32(&port, message, 0x18, 1);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    handler = port_u32(&port, message, 0x24);
    eax = port_call_with(&port, port_u32(&port, handler, 4), message,
                         port_u32(&port, self, 0x50) != 0 ? 1 : 0, message, handler, self,
                         entry->edi, entry->ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4d05e0: the message ebx for eax: a notification (kind 1) goes to the window of its
 * +0x14 (0x4e1230, its method +0x14 with the message); otherwise 0x4d1e80 of +0x14 answers; what
 * is left goes to 0x4cf850. */
uint32_t vertrix_port_rtl_message_route_4d05e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t message = entry->ebx;
    uint32_t eax;
    uint32_t args[2];
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, message, 0) == 1)
    {
        args[0] = port_u32(&port, message, 0x14);
        eax = call_frame(&port, 0x4e1230, self, entry->edx, message, entry->ecx, self, entry->edi,
                         entry->ebp, args, 1);
        if (eax != 0)
        {
            uint32_t methods = port_u32(&port, eax, 0);
            eax = port_call_with(&port, port_u32(&port, methods, 0x14), eax, message, message,
                                 entry->ecx, methods, entry->edi, entry->ebp);
            return port_return(&port, eax, vertrix_lift_edx);
        }
    }
    else
    {
        args[0] = port_u32(&port, message, 0x14);
        args[1] = 0;
        eax = call_frame(&port, 0x4d1e80, self, entry->edx, message, entry->ecx, self, entry->edi,
                         entry->ebp, args, 2);
        if (eax != 0)
        {
            return port_return(&port, eax, vertrix_lift_edx);
        }
    }
    eax = port_call_with(&port, 0x4cf850, self, vertrix_lift_edx, message, entry->ecx, self,
                         entry->edi, entry->ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}
