#include "netaddresses.h"

/* The network address report. */

/* The guard record (0x4ec1ec, `guard`) of a frame routine at `record`. */
static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x48ca20 (guarded 0x5177e4): with the address object edx, whose kind (method +0x2c
 * into the frame) is the 16 bytes 0x51698c, the line 0x510dd7 (0x4ca370 into the frame text) is
 * replaced by the port (method +0x40 of 0x510ded and 0x510df7, sized 4, formatted 0x510e01 by
 * 0x4cdfb0) and logged (0x4ca090, 0x4b76d0 on 0x532c24); then the line 0x510e0f is replaced by
 * the address (method +0x40 of 0x510e27 for the size, a buffer twice that from 0x4c9ff0, 0x510e39
 * into it, converted by 0x47fc50 of eax into a second buffer, formatted 0x510e4b) and logged; the
 * buffers are freed (0x4ca040) and the text released (0x4ca210). eax is the guard's link, edx the
 * release's. */
uint32_t vertrix_port_address_report_48ca20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x58
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t guard = 0x5177e4;
    uint32_t object = entry->edx;
    uint32_t methods;
    uint32_t eax;
    uint32_t ebx = object;
    uint32_t ecx = guard;
    uint32_t esi = 0;
    uint32_t edi = entry->edi;
    uint32_t buffer;
    uint32_t text;
    uint32_t args[5];
    unsigned n;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, entry->eax);
    guard_record(&port, ebp - 0x54, guard);
    port_set32(&port, ebp, -0x30u, 0);
    port_set32(&port, ebp, -0x2cu, 0);
    port_call_with(&port, 0x4ca070, ebp - 0x28, 1, ebx, ecx, esi, edi, ebp);
    port_set32(&port, ebp, -0x48u, vertrix_lift_edx);
    if (object == 0)
    {
        goto release;
    }
    methods = port_u32(&port, object, 0);
    args[0] = object;
    args[1] = ebp - 0x40;
    edi = 0x51698c;
    esi = ebp - 0x40;
    call_frame(&port, port_u32(&port, methods, 0x2c), methods, ebp - 0x40, ebx, ecx, esi, edi, ebp,
               args, 2);
    eax = 0;
    for (n = 0; n < 0x10;)
    {
        uint8_t a = port_u8(&port, esi, n);
        uint8_t b = port_u8(&port, edi, n);
        n++;
        if (a != b)
        {
            eax = a < b ? 0xffffffffu : 1;
            break;
        }
    }
    ecx = 0x10 - n;
    esi += n;
    edi += n;
    if (eax != 0)
    {
        goto release;
    }
    esi = 2;
    port_set32(&port, ebp, -0x30u, 0);
    port_set32(&port, ebp, -0x24u, esi);
    port_call_with(&port, 0x4ca370, ebp - 0x28, 0x510dd7, ebx, ecx, esi, edi, ebp);
    methods = port_u32(&port, object, 0);
    ecx = 0;
    args[0] = object;
    args[1] = 0x510ded;
    args[2] = 0;
    args[3] = ebp - 0x30;
    args[4] = ebp - 0x24;
    eax = call_frame(&port, port_u32(&port, methods, 0x40), ebp - 0x30, methods, ebx, ecx, esi, edi,
                     ebp, args, 5);
    if (eax == 0x80158100u && port_u32(&port, ebp, -0x30u) == 4)
    {
        methods = port_u32(&port, object, 0);
        args[0] = object;
        args[1] = 0x510df7;
        args[2] = ebp - 0x2c;
        args[3] = ebp - 0x30;
        args[4] = ebp - 0x24;
        eax = call_frame(&port, port_u32(&port, methods, 0x40), ebp - 0x2c, methods, ebx, ecx, esi,
                         edi, ebp, args, 5);
        if ((int32_t)eax >= 0)
        {
            args[0] = ebp - 0x28;
            args[1] = 0x510e01;
            args[2] = port_u32(&port, ebp, -0x2cu);
            call_frame(&port, 0x4cdfb0, ebp - 0x28, vertrix_lift_edx, ebx, ecx, esi, edi, ebp, args,
                       3);
        }
    }
    text = port_call_with(&port, 0x4ca090, ebp - 0x20, ebp - 0x28, ebx, ecx, esi, edi, ebp);
    port_set32(&port, ebp, -0x48u, 2);
    ecx = 1;
    edi = 0;
    port_call_with(&port, 0x4b76d0, 0x532c24, text, ebx, ecx, esi, edi, ebp);
    port_set32(&port, ebp, -0x48u, ecx);
    port_call_with(&port, 0x4ca210, ebp - 0x20, 0, ebx, ecx, esi, edi, ebp);
    port_set32(&port, ebp, -0x48u, ecx);
    port_set32(&port, ebp, -0x30u, edi);
    port_set32(&port, ebp, -0x24u, ecx);
    port_call_with(&port, 0x4ca370, ebp - 0x28, 0x510e0f, ebx, ecx, esi, edi, ebp);
    methods = port_u32(&port, object, 0);
    args[0] = object;
    args[1] = 0x510e27;
    args[2] = edi;
    args[3] = ebp - 0x30;
    args[4] = ebp - 0x24;
    eax = call_frame(&port, port_u32(&port, methods, 0x40), ebp - 0x30, methods, ebx, ecx, esi, edi,
                     ebp, args, 5);
    if (eax == 0x80158100u)
    {
        edi = port_call_with(&port, 0x4c9ff0, port_u32(&port, ebp, -0x30u) * 2, vertrix_lift_edx,
                             ebx, ecx, esi, edi, ebp);
        port_set32(&port, ebp, -0x14u, edi);
        methods = port_u32(&port, object, 0);
        args[0] = object;
        args[1] = 0x510e39;
        args[2] = edi;
        args[3] = ebp - 0x30;
        args[4] = ebp - 0x24;
        eax = call_frame(&port, port_u32(&port, methods, 0x40), ebp - 0x30, methods, ebx, ecx, esi,
                         edi, ebp, args, 5);
        if ((int32_t)eax >= 0)
        {
            esi = port_call_with(&port, 0x4c9ff0, port_u32(&port, ebp, -0x30u), vertrix_lift_edx,
                                 ebx, ecx, esi, edi, ebp);
            ebx = edi;
            ecx = port_u32(&port, ebp, -0x30u);
            port_call_with(&port, 0x47fc50, port_u32(&port, ebp, -0x18u), esi, ebx, ecx, esi, edi,
                           ebp);
            args[0] = ebp - 0x28;
            args[1] = 0x510e4b;
            args[2] = esi;
            call_frame(&port, 0x4cdfb0, ebp - 0x28, vertrix_lift_edx, ebx, ecx, esi, edi, ebp, args,
                       3);
            if (esi != 0)
            {
                port_call_with(&port, 0x4ca040, esi, vertrix_lift_edx, ebx, ecx, esi, edi, ebp);
            }
        }
        buffer = port_u32(&port, ebp, -0x14u);
        if (buffer != 0)
        {
            port_call_with(&port, 0x4ca040, buffer, buffer, ebx, ecx, esi, edi, ebp);
        }
    }
    ecx = 4;
    ebx = 1;
    text = port_call_with(&port, 0x4ca090, ebp - 0x1c, ebp - 0x28, ebx, ecx, esi, edi, ebp);
    port_set32(&port, ebp, -0x48u, ecx);
    port_call_with(&port, 0x4b76d0, 0x532c24, text, ebx, ecx, esi, edi, ebp);
    port_set32(&port, ebp, -0x48u, ebx);
    port_call_with(&port, 0x4ca210, ebp - 0x1c, 0, ebx, ecx, esi, edi, ebp);
    port_set32(&port, ebp, -0x48u, ebx);
release:
    edi = 0;
    port_set32(&port, ebp, -0x48u, edi);
    port_call_with(&port, 0x4ca210, ebp - 0x28, 0, ebx, ecx, esi, edi, ebp);
    port_set32(&port, ebp, -0x48u, edi);
    return port_return(&port, port_u32(&port, ebp, -0x54u), vertrix_lift_edx);
}
