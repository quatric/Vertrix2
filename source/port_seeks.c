#include "port_seeks.h"

/* The runtime's file seek and the window control's construction. */

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

/* The seek's end: the stream's lock released (the hook 0x507ca4) and the result. */
static uint32_t seek_end(Port *port, uint32_t stream, uint32_t result, uint32_t ebx,
                         uint32_t offset, uint32_t edi, uint32_t ebp)
{
    port_call_with(port, port_u32(port, 0, 0x507ca4), port_u32(port, stream, 0x10),
                   vertrix_lift_edx, ebx, stream, offset, edi, ebp);
    return port_return(port, result, vertrix_lift_edx);
}

/* The seek of the handle to `to` (0x4e0150): 0, or -1 when it fails. */
static uint32_t seek_handle(Port *port, uint32_t stream, uint32_t to, uint32_t ebx, uint32_t offset,
                            uint32_t edi, uint32_t ebp)
{
    return port_call_with(port, 0x4e0150, port_u32(port, stream, 0x10), to, ebx, stream, offset,
                          edi, ebp) == 0xffffffffu;
}

/* Original 0x4ebce8: the stream eax's seek to edx from ebx (0 the start, 1 the current place, 2
 * the end) under its lock (the hooks 0x507ca0 and 0x507ca4): a stream in use (+0xc bits 1 and 2)
 * is flushed when written (+0xd bit 4, 0x4e3ce0; a failure gives -1, with the error 9 for a
 * negative start), a current place counted back by the buffered +4, the buffer +8's start taken
 * and bits 2 and 4 cleared; an idle stream is first moved within its buffer when it can be
 * (0x4ebc90; the handle's place 0x4ec380 less the buffered count for the start), else the handle
 * is seeked (0x4e0150) and the buffer refilled (0x4ebcd0); the end clears bit 4 and the buffer.
 * 0, or -1. */
uint32_t vertrix_port_rtl_file_seek_4ebce8(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->eax;
    uint32_t offset = entry->edx;
    uint32_t whence = entry->ebx;
    uint32_t ebp = entry->ebp;
    uint32_t edi = entry->edi;
    uint32_t flags;
    uint32_t place;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, port_u32(&port, 0, 0x507ca0), port_u32(&port, stream, 0x10), offset,
                   whence, stream, offset, edi, ebp);
    flags = port_u8(&port, stream, 0xc);
    if ((flags & 6) != 0)
    {
        if ((port_u8(&port, stream, 0xd) & 0x10) != 0)
        {
            if (port_call_with(&port, 0x4e3ce0, stream, vertrix_lift_edx, whence, stream, offset,
                               edi, ebp) != 0)
            {
                if (whence == 0 && (int32_t)offset < 0)
                {
                    port_call_with(&port, 0x4dae70, 9, vertrix_lift_edx, whence, stream, offset,
                                   edi, ebp);
                }
                return seek_end(&port, stream, 0xffffffffu, whence, offset, edi, ebp);
            }
        }
        else
        {
            if (whence == 1)
            {
                offset -= port_u32(&port, stream, 4);
            }
            port_set32(&port, stream, 4, 0);
            port_set32(&port, stream, 0, port_u32(&port, port_u32(&port, stream, 8), 8));
        }
        port_set8(&port, stream, 0xc, port_u8(&port, stream, 0xc) & 0xeb);
        if (seek_handle(&port, stream, offset, whence, offset, edi, ebp))
        {
            return seek_end(&port, stream, 0xffffffffu, whence, offset, edi, ebp);
        }
        return seek_end(&port, stream, 0, whence, offset, edi, ebp);
    }
    if (whence == 2)
    {
        port_set8(&port, stream, 0xc, flags & 0xef);
        port_set32(&port, stream, 0, port_u32(&port, port_u32(&port, stream, 8), 8));
        port_set32(&port, stream, 4, 0);
        if (seek_handle(&port, stream, offset, whence, offset, edi, ebp))
        {
            return seek_end(&port, stream, 0xffffffffu, whence, offset, edi, ebp);
        }
        return seek_end(&port, stream, 0, whence, offset, edi, ebp);
    }
    if (whence > 1)
    {
        port_call_with(&port, 0x4dae70, 9, vertrix_lift_edx, whence, stream, offset, edi, ebp);
        return seek_end(&port, stream, 0xffffffffu, whence, offset, edi, ebp);
    }
    if (whence == 1)
    {
        edi = port_u32(&port, stream, 4);
        place = offset;
    }
    else
    {
        place = port_call_with(&port, 0x4ec380, port_u32(&port, stream, 0x10), vertrix_lift_edx,
                               whence, stream, offset, edi, ebp);
        edi = offset - (place - port_u32(&port, stream, 4));
        place = edi;
    }
    if (port_call_with(&port, 0x4ebc90, place, stream, whence, stream, offset, edi, ebp) == 0)
    {
        return seek_end(&port, stream, 0, whence, offset, edi, ebp);
    }
    if (seek_handle(&port, stream, whence == 1 ? offset - edi : offset, whence, offset, edi, ebp))
    {
        return seek_end(&port, stream, 0xffffffffu, whence, offset, edi, ebp);
    }
    port_call_with(&port, 0x4ebcd0, stream, vertrix_lift_edx, whence, stream, offset, edi, ebp);
    return seek_end(&port, stream, 0, whence, offset, edi, ebp);
}

/* Original 0x4d3e20: the window control eax's construction: under a guard record (0x5197e0) the
 * base (0x4cf320 with 10), its +0x6c list (0x4d8340) and +0xac text (0x4ca070) are made; the
 * methods 0x5198f4, +0x40 and +0x88 -1, +0x3c 1, the other fields cleared, the rectangle +0x58
 * emptied (SetRectEmpty 0x4f1ac0) and the control registered (0x4d4040). The control. */
uint32_t vertrix_port_window_control_construct_4d3e20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    static const uint32_t cleared[] = {0x9c, 0x44, 0x48, 0x8c, 0x90, 0x94,
                                       0x98, 0xa0, 0xa4, 0x68, 0xa8, 0xb8};
    static const uint32_t cleared_after[] = {0x50, 0x4c, 0x54, 0xb0, 0xb4};
    Port port;
    uint32_t record = entry->esp - BELOW;
    uint32_t control = entry->eax;
    uint32_t eax;
    uint32_t args[1];
    unsigned index;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, record, 0, port.env.chain);
    port_set32(&port, record, 4, 0x4ec1ec);
    port_set32(&port, record, 8, 0x5197e0);
    port_set32(&port, record, 0xc, 0);
    port_set8(&port, record, 0x18, 0);
    port_set32(&port, record, 0x14, control);
    eax = port_call_with(&port, 0x4cf320, control, 0xa, control, entry->ecx, entry->esi, entry->edi,
                         entry->ebp);
    port_set32(&port, record, 0xc, 1);
    eax = port_call_with(&port, 0x4d8340, eax + 0x6c, vertrix_lift_edx, control, entry->ecx,
                         entry->esi, entry->edi, entry->ebp);
    port_set32(&port, record, 0xc, 2);
    eax = port_call_with(&port, 0x4ca070, eax + 0x40, vertrix_lift_edx, control, entry->ecx,
                         entry->esi, entry->edi, entry->ebp);
    control = eax - 0xac;
    port_set32(&port, record, 0xc, 3);
    port_set32(&port, control, 0, 0x5198f4);
    port_set32(&port, control, 0x40, 0xffffffffu);
    port_set32(&port, control, 0x3c, 1);
    for (index = 0; index < sizeof cleared / sizeof cleared[0]; ++index)
    {
        port_set32(&port, control, cleared[index], 0);
    }
    args[0] = control + 0x58;
    call_frame(&port, 0x4f1ac0, control + 0x58, vertrix_lift_edx, control, entry->ecx, entry->esi,
               entry->edi, entry->ebp, args, 1);
    for (index = 0; index < sizeof cleared_after / sizeof cleared_after[0]; ++index)
    {
        port_set32(&port, control, cleared_after[index], 0);
    }
    port_set32(&port, control, 0x88, 0xffffffffu);
    port_call_with(&port, 0x4d4040, control, vertrix_lift_edx, control, entry->ecx, entry->esi,
                   entry->edi, entry->ebp);
    return port_return(&port, control, entry->edx);
}
