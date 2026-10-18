#include "rtlrecords.h"

/* The runtime library's record clears and reads. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4cba70: the record eax takes the methods 0x518d14 (+0x24) and clears +0x18..+0x20,
 * copied into +0..+0x14 (+0x10 cleared). eax and edx kept. */
uint32_t vertrix_port_rtl_record_clear_4cba70(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, record, 0x24, 0x518d14);
    port_set32(&port, record, 0x1c, 0);
    port_set32(&port, record, 0x20, 0);
    port_set32(&port, record, 0x18, 0);
    value = port_u32(&port, record, 0x1c);
    port_set32(&port, record, 4, value);
    port_set32(&port, record, 0, value);
    value = port_u32(&port, record, 0x20);
    port_set32(&port, record, 0xc, value);
    port_set32(&port, record, 8, value);
    value = port_u32(&port, record, 0x18);
    port_set32(&port, record, 0x10, 0);
    port_set32(&port, record, 0x14, value);
    return port_return(&port, record, entry->edx);
}

/* Original 0x4cbc90: the record eax (its key +0, none when 0 or a low word 0xffff, giving 1) is
 * read by the object edx's method +0x14 (with -1 and a zero argument), its flag +0x14 cleared
 * first. With ebx set and the flag still clear, the method runs again (0, into a frame dword
 * cleared first) and the record's handler +0x24 takes the result. eax is the first read's. */
uint32_t vertrix_port_rtl_record_read_4cbc90(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t esp = entry->esp - 0x28;
    uint32_t record = entry->eax;
    uint32_t object = entry->edx;
    uint32_t methods;
    uint32_t first;
    uint32_t eax;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x10, entry->ebx);
    if (port_u32(&port, record, 0) == 0 || port_u16(&port, record, 0) == 0xffff)
    {
        return port_return(&port, 1, entry->edx);
    }
    port_set32(&port, record, 0x14, 0);
    methods = port_u32(&port, object, 0);
    args[0] = 0;
    first = call_frame(&port, port_u32(&port, methods, 0x14), object, port_u32(&port, record, 0),
                       0xffffffffu, record, record, object, methods, args, 1);
    port_set32(&port, esp, 0x14, first);
    if (port_u32(&port, esp, 0x10) != 0 && port_u32(&port, record, 0x14) == 0)
    {
        port_set32(&port, esp, 0, 0);
        methods = port_u32(&port, object, 0);
        args[0] = esp;
        eax = call_frame(&port, port_u32(&port, methods, 0x14), object, port_u32(&port, record, 0),
                         0, record, record, object, methods, args, 1);
        object = port_u32(&port, record, 0x24);
        port_call_with(&port, port_u32(&port, object, 0), record, eax, 0, record, record, object,
                       methods);
    }
    return port_return(&port, port_u32(&port, esp, 0x14), vertrix_lift_edx);
}

/* The window `owner` (its handle +0x1c) shown again: message 0x363 posted (0x4cf650 with 1, 0)
 * and sent (0x4d1ae0 with 1, 0, 1, 1). */
static uint32_t window_repost(Port *port, uint32_t owner, uint32_t eax, uint32_t ebx, uint32_t ecx,
                              uint32_t esi, uint32_t edi, uint32_t ebp)
{
    uint32_t args[6];
    args[0] = owner;
    args[1] = port_u32(port, owner, 0x1c);
    args[2] = 0x363;
    args[3] = 1;
    args[4] = 0;
    eax = call_frame(port, 0x4cf650, eax, vertrix_lift_edx, ebx, ecx, esi, edi, ebp, args, 5);
    args[0] = port_u32(port, owner, 0x1c);
    args[1] = 0x363;
    args[2] = 1;
    args[3] = 0;
    args[4] = 1;
    args[5] = 1;
    return call_frame(port, 0x4d1ae0, eax, vertrix_lift_edx, ebx, ecx, esi, edi, ebp, args, 6);
}

/* Original 0x4cc200: with edx above 0 the record 0x4ce780 gives, when its +0x10 is clear, is
 * counted up and left (0x4dec60, 0x4dec70). Otherwise the window +0x1c of eax, when visible
 * (0x4f1a28), takes message 0x363, then every other window of the 0x4ce780 list (+8, next +0x54)
 * with a handle: one without a saved state +0x88 saves it (0x4ccdd0 with 0), a visible one or one
 * with a state not below 0 takes message 0x363, a state above 0 is restored (0x4ccdd0) and the
 * state becomes -1. eax is 1 when edx is negative. */
uint32_t vertrix_port_rtl_windows_refresh_4cc200(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t edi = entry->edx;
    uint32_t ebp = entry->ebp;
    uint32_t eax = self;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edx = entry->edx;
    uint32_t args[1];
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)edi > 0)
    {
        eax = port_call_with(&port, 0x4ce780, eax, entry->edx, ebx, ecx, esi, edi, ebp);
        if (port_u32(&port, eax, 0x10) == 0)
        {
            eax = port_call_with(&port, 0x4dec60, eax, vertrix_lift_edx, ebx, ecx, esi, edi, ebp);
            port_call_with(&port, 0x4dec70, eax, vertrix_lift_edx, ebx, ecx, esi, edi, ebp);
        }
        return port_return(&port, 0, vertrix_lift_edx);
    }
    esi = port_u32(&port, self, 0x1c);
    if (esi != 0 && port_u32(&port, esi, 0x1c) != 0)
    {
        args[0] = port_u32(&port, esi, 0x1c);
        eax = call_frame(&port, 0x4f1a28, eax, edx, ebx, ecx, esi, edi, ebp, args, 1);
        edx = vertrix_lift_edx;
        if (eax != 0)
        {
            eax = window_repost(&port, esi, eax, ebx, ecx, esi, edi, ebp);
            edx = vertrix_lift_edx;
        }
    }
    eax = port_call_with(&port, 0x4ce780, eax, edx, ebx, ecx, esi, edi, ebp);
    eax = port_u32(&port, eax, 8);
    for (ebx = eax; ebx != 0 && !port.env.failed; ebx = port_u32(&port, ebx, 0x54))
    {
        if (port_u32(&port, ebx, 0x1c) == 0 || ebx == esi)
        {
            continue;
        }
        if (port_u32(&port, ebx, 0x88) == 0)
        {
            eax = port_call_with(&port, 0x4ccdd0, ebx, 0, ebx, ecx, esi, edi, ebp);
        }
        args[0] = port_u32(&port, ebx, 0x1c);
        eax = call_frame(&port, 0x4f1a28, eax, vertrix_lift_edx, ebx, ecx, esi, edi, ebp, args, 1);
        if (eax != 0 || (int32_t)port_u32(&port, ebx, 0x88) >= 0)
        {
            eax = window_repost(&port, ebx, eax, ebx, ecx, esi, edi, ebp);
        }
        if ((int32_t)port_u32(&port, ebx, 0x88) > 0)
        {
            eax = port_call_with(&port, 0x4ccdd0, ebx, port_u32(&port, ebx, 0x88), ebx, ecx, esi,
                                 edi, ebp);
        }
        port_set32(&port, ebx, 0x88, 0xffffffffu);
    }
    return port_return(&port, (int32_t)edi < 0, vertrix_lift_edx);
}
