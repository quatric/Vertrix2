#include "rtlbits.h"

/* Odd runtime library pieces: window defaults, blank skips and mantissa normalisation. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4d6300: 1 when the window eax has its +0x98 set, else its method +0xa4 with the
 * application's (0x4ce220) +0x3c, +0x40 and +0x44 (as 0x4cf850); edx kept. */
uint32_t vertrix_port_rtl_window_default_4d6300(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t application;
    uint32_t methods;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, self, 0x98) != 0)
    {
        return port_return(&port, 1, entry->edx);
    }
    application = port_call_with(&port, 0x4ce220, self, entry->edx, entry->ebx, entry->ecx, self,
                                 entry->edi, entry->ebp);
    methods = port_u32(&port, self, 0);
    eax = port_call_with(&port, port_u32(&port, methods, 0xa4), self,
                         port_u32(&port, application, 0x3c), port_u32(&port, application, 0x40),
                         port_u32(&port, application, 0x44), self, methods, entry->ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x480940: the object edx's method +0x7c of it and 0x598628; when it answers, 0x486e20
 * and 0x485700 (0x50f6ed, 1) report the object eax to 0x5b9c50 (0), else 1. */
uint32_t vertrix_port_object_check_report_480940(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t other = entry->edx;
    uint32_t methods;
    uint32_t result;
    uint32_t args[2];
    port_open(&port, calls, services, globals, entry);
    methods = port_u32(&port, other, 0);
    args[0] = other;
    args[1] = port_u32(&port, 0, 0x598628);
    result = call_frame(&port, port_u32(&port, methods, 0x7c), methods, other, self, args[1],
                        entry->esi, entry->edi, entry->ebp, args, 2);
    if (result == 0)
    {
        return port_return(&port, 1, vertrix_lift_edx);
    }
    port_call_with(&port, 0x486e20, 0x5b9c50, self, self, result, entry->esi, entry->edi,
                   entry->ebp);
    port_call_with(&port, 0x485700, 0x5b9c50, 1, 0x50f6ed, result, entry->esi, entry->edi,
                   entry->ebp);
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x4e44c8: characters read from the stream eax (0x4e4100, the stream then in edx) while
 * blank (bit 1 of 0x507d58 one past the byte, through the frame), the last pushed back (0x4e4108)
 * unless the stream's +0x10 has bit 1; eax the blanks skipped, edx kept. */
uint32_t vertrix_port_rtl_skip_blanks_4e44c8(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x14;
    uint32_t edx = entry->eax;
    uint32_t ebx = 0;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x10, entry->ebx);
    port_set32(&port, esp, 0xc, entry->ecx);
    port_set32(&port, esp, 8, entry->edx);
    port_set32(&port, esp, 4, entry->esi);
    for (;;)
    {
        eax = port_call_with(&port, 0x4e4100, edx, edx, ebx, ecx, esi, entry->edi, entry->ebp);
        edx = vertrix_lift_edx;
        port_set32(&port, esp, 0, eax);
        ecx = (ecx & 0xffffff00u) | ((port_u8(&port, esp, 0) + 1) & 0xff);
        esi = ecx & 0xff;
        if ((port_u8(&port, esi, 0x507d58) & 2) == 0 || port.env.failed)
        {
            break;
        }
        ebx++;
    }
    if ((port_u8(&port, edx, 0x10) & 2) == 0)
    {
        port_call_with(&port, 0x4e4108, eax, edx, ebx, ecx, esi, entry->edi, entry->ebp);
    }
    return port_return(&port, ebx, port_u32(&port, esp, 8));
}

/* Original 0x4ee3d2: the mantissa edx:eax:ebp shifted left (whole dwords first, edi the exponent
 * following) until its top bit is set, then rounded to edx:eax (a carry out renormalised). Zero
 * stays. */
uint32_t vertrix_port_rtl_normalise_4ee3d2(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t low = entry->ebp;
    unsigned round;
    port_open(&port, calls, services, globals, entry);
    if ((eax | edx | low) == 0)
    {
        return port_return(&port, eax, edx);
    }
    for (round = 0; round < 2; round++)
    {
        if (edx == 0)
        {
            edx = eax;
            eax = low;
            low = 0;
        }
    }
    while ((edx & 0x80000000u) == 0)
    {
        edx = (edx << 1) | (eax >> 31);
        eax = (eax << 1) | (low >> 31);
        low <<= 1;
    }
    if ((low & 0x80000000u) != 0)
    {
        eax++;
        if (eax == 0)
        {
            edx++;
            if (edx == 0)
            {
                edx = 0x80000000u;
            }
        }
    }
    return port_return(&port, eax, edx);
}

/* Original 0x4e8660: under the heap lock (0x507cb8, 0x507cc0) each heap of the chain 0x50aefc
 * (next +8) whose rover +0x24 points at its own end (+0 less 0x2c) is shrunk by 0x4e86fc; eax 0,
 * edx kept. */
uint32_t vertrix_port_rtl_heap_trim_4e8660(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    port_open(&port, calls, services, globals, entry);
    eax = port_call_with(&port, port_u32(&port, 0, 0x507cb8), entry->eax, entry->edx, ebx, ecx, esi,
                         entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    eax = port_u32(&port, 0, 0x50aefc);
    while (eax != 0 && !port.env.failed)
    {
        ebx = port_u32(&port, eax, 0) - 0x2c;
        ecx = port_u32(&port, eax, 0x24);
        esi = port_u32(&port, ecx, 0);
        edx = port_u32(&port, eax, 8);
        if (ebx == esi)
        {
            port_call_with(&port, 0x4e86fc, eax, edx, ebx, ecx, esi, entry->edi, entry->ebp);
            edx = vertrix_lift_edx;
        }
        eax = edx;
    }
    port_call_with(&port, port_u32(&port, 0, 0x507cc0), eax, edx, ebx, ecx, esi, entry->edi,
                   entry->ebp);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x4ea0d0: the path eax made to exist: while 0x4e7b50 refuses it, its parent (0x4e3a50
 * into the frame, 0x4eab80, 0x4e7120) is cut at its lead byte length (0x4e6f30, the byte from that
 * call's edx), handed to 0x4e8790 and the next part taken (0x4e3a90). eax the path, edx kept. */
uint32_t vertrix_port_rtl_path_make_4ea0d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x10;
    uint32_t path = entry->eax;
    uint32_t ebx = path;
    uint32_t edx = entry->edx;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0xc, entry->ebx);
    port_set32(&port, esp, 8, entry->ecx);
    port_set32(&port, esp, 4, entry->edx);
    for (;;)
    {
        eax = port_call_with(&port, 0x4e7b50, ebx, edx, ebx, path, entry->esi, entry->edi,
                             entry->ebp);
        edx = vertrix_lift_edx;
        if (eax != 0 || port.env.failed)
        {
            break;
        }
        eax = port_call_with(&port, 0x4e3a50, ebx, esp, ebx, path, entry->esi, entry->edi,
                             entry->ebp);
        eax = port_call_with(&port, 0x4eab80, eax, vertrix_lift_edx, ebx, path, entry->esi,
                             entry->edi, entry->ebp);
        port_call_with(&port, 0x4e7120, eax, vertrix_lift_edx, ebx, path, entry->esi, entry->edi,
                       entry->ebp);
        eax = port_call_with(&port, 0x4e6f30, esp, vertrix_lift_edx & 0xffffff00u, ebx, path,
                             entry->esi, entry->edi, entry->ebp);
        port_set8(&port, esp + eax, 0, vertrix_lift_edx);
        port_call_with(&port, 0x4e8790, ebx, esp, ebx, path, entry->esi, entry->edi, entry->ebp);
        ebx = port_call_with(&port, 0x4e3a90, ebx, vertrix_lift_edx, ebx, path, entry->esi,
                             entry->edi, entry->ebp);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, path, port_u32(&port, esp, 4));
}

/* Original 0x488050: 1 when the object eax's position (0x487fd0, not -1) survives a seek there and
 * back (0x488040 then 0x489b20 giving the same), else 0. */
uint32_t vertrix_port_stream_seek_check_488050(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t eax;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    eax = port_call_with(&port, 0x487fd0, self, entry->edx, entry->ebx, self, entry->esi,
                         entry->edi, entry->ebp);
    if (eax == 0xffffffffu)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    target =
        port_call_with(&port, 0x488040, self, eax, entry->ebx, self, 0, entry->edi, entry->ebp);
    eax = port_call_with(&port, 0x489b20, self, target, target, self, 0, entry->edi, entry->ebp);
    return port_return(&port, eax == target ? 1 : 0, vertrix_lift_edx);
}
