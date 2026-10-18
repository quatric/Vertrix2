#include "rtlreads.h"

/* Text to double conversion, pending error fetches and decoder scanline reads. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4ed79f: the text eax (end into edx) parsed by 0x4ed60b into an extended value in the
 * frame and narrowed to a double (eax low, edx high): too large gives the infinity 0x51ab90 (its
 * negation by 0x4dae4a for a negative value) with the range error 0x4dae94, otherwise 0x4e543c
 * narrows it and an underflow to zero (or a denormal, or the type 3) also reports the range
 * error; 0 when nothing parses. */
uint32_t vertrix_port_rtl_text_to_double_4ed79f(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t kind;
    uint32_t eax;
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ebx);
    kind = port_call_with(&port, 0x4ed60b, entry->eax, ebp - 0x28, entry->edx, entry->ecx,
                          entry->esi, entry->edi, ebp);
    edx = vertrix_lift_edx;
    if (kind == 0)
    {
        port_set32(&port, ebp, -0x14, 0);
        port_set32(&port, ebp, -0x10, 0);
        return port_return(&port, 0, 0);
    }
    eax = port_u16(&port, ebp, -0x20) & 0x7fff;
    if ((int32_t)eax >= 0x43ff)
    {
        port_call_with(&port, 0x4dae94, eax, edx, kind, entry->ecx, entry->esi, entry->edi, ebp);
        if ((port_u8(&port, ebp, -0x1f) & 0x80) != 0)
        {
            eax = port_call_with(&port, 0x4dae4a, port_u32(&port, 0, 0x51ab90),
                                 port_u32(&port, 0, 0x51ab94), kind, entry->ecx, entry->esi,
                                 entry->edi, ebp);
            port_set32(&port, ebp, -0x14, eax);
            port_set32(&port, ebp, -0x10, vertrix_lift_edx);
        }
        else
        {
            port_set32(&port, ebp, -0x14, port_u32(&port, 0, 0x51ab90));
            port_set32(&port, ebp, -0x10, port_u32(&port, 0, 0x51ab94));
        }
        return port_return(&port, port_u32(&port, ebp, -0x14), port_u32(&port, ebp, -0x10));
    }
    if ((int32_t)eax < 0x3bcd)
    {
        if ((int32_t)eax < -0x34)
        {
            port_call_with(&port, 0x4dae94, eax, edx, 0, entry->ecx, entry->esi, entry->edi, ebp);
            port_set32(&port, ebp, -0x14, 0);
            port_set32(&port, ebp, -0x10, 0);
            return port_return(&port, 0, 0);
        }
        eax = port_call_with(&port, 0x4e543c, ebp - 0x28, ebp - 0x14, kind, entry->ecx, entry->esi,
                             entry->edi, ebp);
        edx = vertrix_lift_edx;
        port_set32(&port, ebp, -0xc, port_u32(&port, ebp, -0x14));
        eax = port_u32(&port, ebp, -0x10);
        port_set32(&port, ebp, -8, eax);
        if (eax != 0 && (port_u16(&port, ebp, -6) & 0x7ff0) != 0)
        {
            return port_return(&port, port_u32(&port, ebp, -0x14), port_u32(&port, ebp, -0x10));
        }
    }
    else
    {
        eax = port_call_with(&port, 0x4e543c, ebp - 0x28, ebp - 0x14, kind, entry->ecx, entry->esi,
                             entry->edi, ebp);
        edx = vertrix_lift_edx;
        if (kind != 3)
        {
            port_set32(&port, ebp, -0x1c, port_u32(&port, ebp, -0x14));
            eax = port_u32(&port, ebp, -0x10);
            port_set32(&port, ebp, -0x18, eax);
            if ((port_u16(&port, ebp, -0x16) & 0x7ff0) != 0)
            {
                return port_return(&port, port_u32(&port, ebp, -0x14), port_u32(&port, ebp, -0x10));
            }
        }
    }
    port_call_with(&port, 0x4dae94, eax, edx, kind, entry->ecx, entry->esi, entry->edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x14), port_u32(&port, ebp, -0x10));
}

/* Original 0x4ed984: the pending error: a stored one (0x509718) is taken and cleared; with an
 * error hook (0x507d30) it answers (after 0x507cfc); otherwise, under the runtime lock hooks
 * (0x507ca0, 0x507ca4), this thread's record (0x4e89e8) is read by 0x4ed880 with its last error
 * (0x4f1b8c into the frame) saved and restored (0x4f1c8c). edx kept. */
uint32_t vertrix_port_rtl_pending_error_4ed984(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x14;
    uint32_t eax;
    uint32_t error;
    uint32_t record;
    uint32_t args[2];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp - 4, 0, entry->ebx);
    port_set32(&port, entry->esp - 8, 0, entry->ecx);
    port_set32(&port, entry->esp - 0xc, 0, entry->edx);
    port_set32(&port, entry->esp - 0x10, 0, entry->esi);
    eax = port_u32(&port, 0, 0x509718);
    if (eax != 0)
    {
        port_set32(&port, 0, 0x509718, 0);
        return port_return(&port, eax, entry->edx);
    }
    if (port_u32(&port, 0, 0x507d30) != 0)
    {
        eax = port_call_with(&port, port_u32(&port, 0, 0x507cfc), 0, entry->edx, entry->ebx,
                             entry->ecx, entry->esi, entry->edi, entry->ebp);
        error = port_call_with(&port, port_u32(&port, 0, 0x507d30), eax, vertrix_lift_edx,
                               entry->ebx, entry->ecx, entry->esi, entry->edi, entry->ebp);
        return port_return(&port, error, entry->edx);
    }
    eax = port_call_with(&port, port_u32(&port, 0, 0x507ca0), 0, entry->edx, entry->ebx, entry->ecx,
                         entry->esi, entry->edi, entry->ebp);
    record = port_call_with(&port, 0x4e89e8, eax, vertrix_lift_edx, entry->ebx, entry->ecx,
                            entry->esi, entry->edi, entry->ebp);
    args[0] = record;
    args[1] = esp;
    eax = call_frame(&port, 0x4f1b8c, esp, vertrix_lift_edx, record, entry->ecx, entry->esi,
                     entry->edi, entry->ebp, args, 2);
    args[0] = record;
    args[1] = 0;
    call_frame(&port, 0x4f1c8c, eax, vertrix_lift_edx, record, entry->ecx, entry->esi, entry->edi,
               entry->ebp, args, 2);
    error = port_call_with(&port, 0x4ed880, record, vertrix_lift_edx, record, entry->ecx,
                           entry->esi, entry->edi, entry->ebp);
    args[0] = record;
    args[1] = port_u32(&port, esp, 0);
    call_frame(&port, 0x4f1c8c, error, vertrix_lift_edx, record, args[1], error, entry->edi,
               entry->ebp, args, 2);
    port_call_with(&port, port_u32(&port, 0, 0x507ca4), 0, vertrix_lift_edx, record, args[1], error,
                   entry->edi, entry->ebp);
    return port_return(&port, error, entry->edx);
}

/* Original 0x4b99b0: scanlines read from the decoder eax (in state 0xcd, else the error 0x14 with
 * the state): past its last row (+0x8c against +0x74) the warning 0x7b (method +4 of -1) and 0;
 * otherwise its progress monitor (+8) told the row and the count, and the main controller
 * (+0x1a8) method +4 reads into the count in the frame, added to the row. eax the rows read. */
uint32_t vertrix_port_jpeg_read_scanlines_4b99b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t cinfo = entry->eax;
    uint32_t ecx = entry->ebx;
    uint32_t ebx = entry->ebx;
    uint32_t edx = entry->edx;
    uint32_t error;
    uint32_t progress;
    uint32_t main;
    uint32_t rows;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ecx);
    port_set32(&port, ebp, -8, entry->esi);
    port_set32(&port, ebp, -0xc, entry->edi);
    if (port_u32(&port, cinfo, 0x14) != 0xcd)
    {
        error = port_u32(&port, cinfo, 0);
        port_set32(&port, error, 0x14, 0x14);
        ebx = port_u32(&port, cinfo, 0);
        port_set32(&port, ebx, 0x18, port_u32(&port, cinfo, 0x14));
        ebx = port_u32(&port, cinfo, 0);
        port_call_with(&port, port_u32(&port, ebx, 0), cinfo, edx, ebx, ecx, cinfo, entry->edi,
                       ebp);
        edx = vertrix_lift_edx;
    }
    if (port_u32(&port, cinfo, 0x8c) >= port_u32(&port, cinfo, 0x74))
    {
        port_set32(&port, port_u32(&port, cinfo, 0), 0x14, 0x7b);
        ecx = port_u32(&port, cinfo, 0);
        port_call_with(&port, port_u32(&port, ecx, 4), cinfo, 0xffffffffu, ebx, ecx, cinfo,
                       entry->edi, ebp);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    progress = port_u32(&port, cinfo, 8);
    if (progress != 0)
    {
        port_set32(&port, progress, 4, port_u32(&port, cinfo, 0x8c));
        port_set32(&port, port_u32(&port, cinfo, 8), 8, port_u32(&port, cinfo, 0x74));
        ebx = port_u32(&port, cinfo, 8);
        port_call_with(&port, port_u32(&port, ebx, 0), cinfo, edx, ebx, ecx, cinfo, entry->edi,
                       ebp);
        edx = vertrix_lift_edx;
    }
    port_set32(&port, ebp, -0x10, 0);
    main = port_u32(&port, cinfo, 0x1a8);
    port_call_with(&port, port_u32(&port, main, 4), cinfo, edx, ebp - 0x10, ecx, cinfo, main, ebp);
    rows = port_u32(&port, ebp, -0x10);
    port_set32(&port, cinfo, 0x8c, port_u32(&port, cinfo, 0x8c) + rows);
    return port_return(&port, port_u32(&port, ebp, -0x10), vertrix_lift_edx);
}
