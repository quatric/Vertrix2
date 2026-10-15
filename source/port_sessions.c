#include "port_sessions.h"

/* The session's options message. */

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

/* Original 0x48c0f0: the session eax's options edx: its +0x2c and +0x20 held to 255, the eight
 * flag bytes +0 to +7 packed as the bits 3, 2, 1, 0, 7, 6, 5 and 4; a message of 0x38 bytes
 * (0x4ca000, 0x48d330, 0x48d3e0) queued at +0x214 (0x48d600) under the lock 0x5328f0
 * (0x4f1b48, 0x4f1c40); the two counts and the flags at +0x1e8 to +0x1ea are sent from +0x1e7
 * (4 bytes) by 0x48c9b0 when ebx is 1, else by 0x48c9d0. */
uint32_t vertrix_port_session_options_48c0f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t session = entry->eax;
    uint32_t options = entry->edx;
    uint32_t first;
    uint32_t second;
    uint32_t flags;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t message;
    uint32_t eax;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    first = port_u32(&port, options, 0x2c);
    second = port_u32(&port, options, 0x20);
    port_set16(&port, ebp, -0x1cu, first >= 0xff ? 0xff : first);
    port_set16(&port, ebp, -0x20u, second >= 0xff ? 0xff : second);
    port_set8(&port, ebp, -0x14u, port_u8(&port, options, 4));
    port_set8(&port, ebp, -0x10u, port_u8(&port, options, 5));
    flags = (port_u8(&port, options, 0) << 3 | port_u8(&port, options, 1) << 2 |
             port_u8(&port, options, 2) << 1 | port_u8(&port, options, 3) |
             port_u8(&port, options, 4) << 7 | port_u8(&port, options, 5) << 6 |
             port_u8(&port, options, 6) << 5 | port_u8(&port, options, 7) << 4) &
            0xff;
    ebx = (second & 0xffff0000u) | port_u8(&port, options, 7) << 8 | flags;
    ecx = (first & 0xffff0000u) | port_u8(&port, options, 3) << 8 | port_u8(&port, options, 6);
    port_set32(&port, options, 0x2c, port_u16(&port, ebp, -0x1cu));
    port_set32(&port, options, 0x20, port_u16(&port, ebp, -0x20u));
    port_set8(&port, ebp, -0x18u, flags);
    message = port_call_with(&port, 0x4ca000, 0x38, options, ebx, ecx, session, entry->ebx, ebp);
    if (message != 0)
    {
        message = port_call_with(&port, 0x48d330, message, vertrix_lift_edx, ebx, ecx, session,
                                 entry->ebx, ebp);
    }
    eax = port_call_with(&port, 0x48d3e0, message, vertrix_lift_edx, message, ecx, session,
                         entry->ebx, ebp);
    args[0] = 0x5328f0;
    call_frame(&port, 0x4f1b48, eax, vertrix_lift_edx, message, ecx, session, entry->ebx, ebp, args,
               1);
    eax = port_call_with(&port, 0x48d600, session + 0x214, message, message, ecx, session,
                         entry->ebx, ebp);
    call_frame(&port, 0x4f1c40, eax, vertrix_lift_edx, message, ecx, session, entry->ebx, ebp, args,
               1);
    port_set8(&port, session, 0x1e8, port_u8(&port, ebp, -0x1cu));
    port_set8(&port, session, 0x1e9, port_u8(&port, ebp, -0x20u));
    port_set8(&port, session, 0x1ea, flags);
    eax = port_call_with(&port, entry->ebx == 1 ? 0x48c9b0 : 0x48c9d0, session, session + 0x1e7, 4,
                         ecx, session, entry->ebx, ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}
