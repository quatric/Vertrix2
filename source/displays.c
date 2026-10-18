#include "displays.h"

/* The application's display start. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* The failure's three message boxes (MessageBoxA 0x4f1a4c) of the texts given the temporary at
 * `text` (0x4ca280, 0x4ca370), the application eax stopped (0x418870), the players released
 * (0x411f50 on 0x5327f0) and the temporary too (0x4ca210). */
static void display_failure(Port *port, uint32_t app, uint32_t text, const uint32_t *lines,
                            uint32_t stage, uint32_t ebx, uint32_t ecx, uint32_t edi, uint32_t ebp)
{
    uint32_t args[4] = {0, 0, 0, 0};
    uint32_t eax;
    port_call_with(port, 0x4ca280, text, lines[0], ebx, ecx, app, edi, ebp);
    port_set32(port, ebp, -0x24u, stage);
    args[1] = port_u32(port, text, 0);
    call_frame(port, 0x4f1a4c, args[1], vertrix_lift_edx, ebx, ecx, app, stage, ebp, args, 4);
    eax = port_call_with(port, 0x4ca370, text, lines[1], ebx, ecx, app, stage, ebp);
    args[1] = port_u32(port, text, 0);
    call_frame(port, 0x4f1a4c, eax, args[1], ebx, ecx, app, stage, ebp, args, 4);
    eax = port_call_with(port, 0x4ca370, text, lines[2], ebx, ecx, app, stage, ebp);
    args[1] = port_u32(port, text, 0);
    call_frame(port, 0x4f1a4c, eax, vertrix_lift_edx, ebx, args[1], app, stage, ebp, args, 4);
    port_call_with(port, 0x418870, app, vertrix_lift_edx, 0, args[1], app, stage, ebp);
    port_call_with(port, 0x411f50, 0x5327f0, 0, 0, args[1], app, stage, ebp);
    port_set32(port, ebp, -0x24u, 0);
    port_call_with(port, 0x4ca210, text, vertrix_lift_edx, 0, args[1], app, stage, ebp);
    port_set32(port, ebp, -0x24u, 0);
}

/* Original 0x41a080: the application eax's display: under a guard record (0x513fc4) it is
 * prepared (0x4189f0); without DirectDraw (0x484b30) the messages 0x50d9f1, 0x50da58 and
 * 0x50dab9 are shown and it stops; else the mode 0x532b4c is tried (0x418ce0) down the list
 * 0x4f8128 of three, and with none left the messages 0x50dafb, 0x50db62 and 0x50dbc3 are shown
 * and it stops; a mode that starts gives the state 0x41a540 (0x418840). The guard record's
 * chain. */
uint32_t vertrix_port_display_start_41a080(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    static const uint32_t missing[3] = {0x50d9f1, 0x50da58, 0x50dab9};
    static const uint32_t unusable[3] = {0x50dafb, 0x50db62, 0x50dbc3};
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t app = entry->eax;
    uint32_t ebx = 0;
    uint32_t ecx = 0x513fc4;
    uint32_t mode;
    uint32_t index;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x30u, port.env.chain);
    port_set32(&port, ebp, -0x2cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x28u, 0x513fc4);
    port_set32(&port, ebp, -0x24u, 0);
    eax = port_call_with(&port, 0x4189f0, app, 0x4ec1ec, 0, ecx, app, entry->edi, ebp);
    if (port_call_with(&port, 0x484b30, eax, vertrix_lift_edx, 0, ecx, app, entry->edi, ebp) == 0)
    {
        display_failure(&port, app, ebp - 0x1c, missing, 1, 0, ecx, entry->edi, ebp);
        return port_return(&port, port_u32(&port, ebp, -0x30u), entry->edx);
    }
    for (;;)
    {
        if (port_call_with(&port, 0x418ce0, app, port_u8(&port, 0, 0x532b4c), ebx, ecx, app,
                           entry->edi, ebp) != 0)
        {
            port_call_with(&port, 0x418840, app, 0x41a540, ebx, ecx, app, entry->edi, ebp);
            return port_return(&port, port_u32(&port, ebp, -0x30u), entry->edx);
        }
        ebx = 0;
        for (index = 0; index < 3; ++index)
        {
            ecx = port_u32(&port, 0, 0x4f8128 + index * 4);
            if (ecx == port_u32(&port, 0, 0x532b4c))
            {
                ebx = index;
            }
        }
        --ebx;
        if ((int32_t)ebx < 0)
        {
            break;
        }
        mode = port_u32(&port, 0, 0x4f8128 + ebx * 4);
        port_set32(&port, 0, 0x532b4c, mode);
    }
    display_failure(&port, app, ebp - 0x18, unusable, 3, ebx, ecx, entry->edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x30u), entry->edx);
}
