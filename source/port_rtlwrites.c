#include "port_rtlwrites.h"

/* Window placement queries and stream text writes. */

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

/* Original 0x4d5360: the window eax's state: through its client (+0x98) when it has one (its
 * control's +0x38 method +0xb0, or the control of 0x4f1aa8 of its handle +0x1c by 0x4cf8e0; the
 * original continues into 0x4cce60), else its method +0xa4 with the application's (0x4ce220) +0x3c,
 * +0x40 and +0x44 (into 0x4cf850). edx kept. */
uint32_t vertrix_port_rtl_window_state_4d5360(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t client;
    uint32_t eax;
    uint32_t args[1];
    port_open(&port, calls, services, globals, entry);
    client = port_u32(&port, self, 0x98);
    if (client == 0)
    {
        uint32_t application = port_call_with(&port, 0x4ce220, self, entry->edx, entry->ebx,
                                              entry->ecx, self, entry->edi, entry->ebp);
        uint32_t methods = port_u32(&port, self, 0);
        eax = port_call_with(&port, port_u32(&port, methods, 0xa4), self,
                             port_u32(&port, application, 0x3c), port_u32(&port, application, 0x40),
                             port_u32(&port, application, 0x44), self, methods, entry->ebp);
        return port_return(&port, eax, entry->edx);
    }
    if (port_u32(&port, client, 0x38) == 0)
    {
        args[0] = port_u32(&port, client, 0x1c);
        eax = call_frame(&port, 0x4f1aa8, client, entry->edx, entry->ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp, args, 1);
        args[0] = eax;
        eax = call_frame(&port, 0x4cf8e0, eax, vertrix_lift_edx, entry->ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp, args, 1);
        return port_return(&port, eax, entry->edx);
    }
    {
        uint32_t control = port_u32(&port, client, 0x38);
        uint32_t methods = port_u32(&port, control, 0);
        eax = port_call_with(&port, port_u32(&port, methods, 0xb0), control, methods, entry->ebx,
                             entry->ecx, entry->esi, entry->edi, entry->ebp);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4e8330: the text eax written to the stream edx (0x4e3e00 a character) under its lock
 * (+0x10, the hooks 0x507ca0 and 0x507ca4), set up first by 0x4e3b60 when it has no buffer; an
 * unbuffered stream (flag 4 of +0xd) is buffered for the write and flushed after (0x4e3ce0). eax
 * the count written, or -1. */
uint32_t vertrix_port_rtl_stream_write_text_4e8330(PORT_SIGNATURE)
{
    Port port;
    uint32_t text = entry->eax;
    uint32_t stream = entry->edx;
    uint32_t place = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t edi = 0;
    uint32_t esi = 0;
    uint32_t flags;
    port_open(&port, calls, services, globals, entry);
    eax = port_call_with(&port, port_u32(&port, 0, 0x507ca0), port_u32(&port, stream, 0x10), stream,
                         text, stream, entry->esi, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    eax = port_u32(&port, edx, 8);
    if (port_u32(&port, eax, 8) == 0)
    {
        eax = port_call_with(&port, 0x4e3b60, stream, edx, text, stream, entry->esi, entry->edi,
                             entry->ebp);
        edx = vertrix_lift_edx;
    }
    flags = port_u8(&port, stream, 0xd);
    eax = (eax & 0xffff00ffu) | (flags << 8);
    if ((flags & 4) != 0)
    {
        uint32_t low = flags & 0xf9;
        port_set8(&port, stream, 0xd, low);
        edx = (edx & 0xffff0000u) | ((low | 2) << 8) | low;
        edi = 1;
        port_set8(&port, stream, 0xd, low | 2);
    }
    for (;;)
    {
        eax = port_u8(&port, place, 0);
        if (eax == 0 || port.env.failed)
        {
            break;
        }
        edx = stream;
        place++;
        eax = port_call_with(&port, 0x4e3e00, eax, stream, place, stream, esi, edi, text);
        edx = vertrix_lift_edx;
        if (eax == 0xffffffffu)
        {
            esi = eax;
            break;
        }
    }
    if (edi != 0)
    {
        uint32_t low = port_u8(&port, stream, 0xd) & 0xf9;
        port_set8(&port, stream, 0xd, low);
        eax = (eax & 0xffff0000u) | ((low | 4) << 8) | low;
        port_set8(&port, stream, 0xd, low | 4);
        if (esi == 0)
        {
            esi = port_call_with(&port, 0x4e3ce0, stream, edx, place, stream, esi, edi, text);
            edx = vertrix_lift_edx;
        }
    }
    if (esi == 0)
    {
        esi = place - text;
    }
    port_call_with(&port, port_u32(&port, 0, 0x507ca4), port_u32(&port, stream, 0x10), edx, place,
                   stream, esi, edi, text);
    return port_return(&port, esi, vertrix_lift_edx);
}
