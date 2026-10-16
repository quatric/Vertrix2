#include "port_rtlpumps.h"

/* The JPEG restart resynchronisation and the application's message pump. */

/* Original 0x4c0860: the JPEG decoder eax resynchronised to the restart marker edx (warning 0x79
 * through the error manager's +4 with -1): the marker +0x1a0 found is judged (warning 0x61 with
 * level 4 and the action): any marker below 0xc0 or the previous two restarts discards data and
 * reads the next marker (0x4bf770; 0 when suspended), a non-restart or one of the next two restarts
 * stays for later (1), the wanted one is taken (+0x1a0 cleared, 1). */
uint32_t vertrix_port_jpeg_resync_restart_4c0860(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t desired = entry->edx;
    uint32_t marker;
    uint32_t error;
    uint32_t action;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    marker = port_u32(&port, decoder, 0x1a0);
    port_set32(&port, port_u32(&port, decoder, 0), 0x14, 0x79);
    port_set32(&port, port_u32(&port, decoder, 0), 0x18, marker);
    port_set32(&port, port_u32(&port, decoder, 0), 0x1c, desired);
    error = port_u32(&port, decoder, 0);
    port_call_with(&port, port_u32(&port, error, 4), decoder, 0xffffffffu, decoder, desired, marker,
                   error, ebp);
    port_set32(&port, ebp, -0x1cu, ((desired - 2) & 7) + 0xd0);
    port_set32(&port, ebp, -0x20u, ((desired - 1) & 7) + 0xd0);
    port_set32(&port, ebp, -0x18u, ((desired + 2) & 7) + 0xd0);
    port_set32(&port, ebp, -0x14u, ((desired + 1) & 7) + 0xd0);
    while (!port.env.failed)
    {
        if ((int32_t)marker < 0xc0)
        {
            action = 2;
        }
        else if ((int32_t)marker < 0xd0 || (int32_t)marker > 0xd7)
        {
            action = 3;
        }
        else if (marker == port_u32(&port, ebp, -0x14u) || marker == port_u32(&port, ebp, -0x18u))
        {
            action = 3;
        }
        else if (marker == port_u32(&port, ebp, -0x20u) || marker == port_u32(&port, ebp, -0x1cu))
        {
            action = 2;
        }
        else
        {
            action = 1;
        }
        port_set32(&port, port_u32(&port, decoder, 0), 0x14, 0x61);
        port_set32(&port, port_u32(&port, decoder, 0), 0x18, marker);
        port_set32(&port, port_u32(&port, decoder, 0), 0x1c, action);
        error = port_u32(&port, decoder, 0);
        port_call_with(&port, port_u32(&port, error, 4), decoder, 4, decoder, action, marker, error,
                       ebp);
        if (action == 1)
        {
            port_set32(&port, decoder, 0x1a0, 0);
            return port_return(&port, 1, vertrix_lift_edx);
        }
        if (action == 3)
        {
            return port_return(&port, 1, vertrix_lift_edx);
        }
        eax = port_call_with(&port, 0x4bf770, decoder, vertrix_lift_edx, decoder, action, marker,
                             error, ebp);
        if (eax == 0)
        {
            return port_return(&port, 0, vertrix_lift_edx);
        }
        marker = port_u32(&port, decoder, 0x1a0);
    }
    return port_return(&port, 0, vertrix_lift_edx);
}

/* A call of the pump's: its eax, its edx kept in *edx. */
static uint32_t call_pump(Port *port, uint32_t *edx, uint32_t target, uint32_t eax, uint32_t d,
                          uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                          const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, d, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    *edx = vertrix_lift_edx;
    return result;
}

/* Original 0x4cc0d0: the message pump of the application eax (its message at +0x30): while a
 * message waits (import 0x4f1a5c with no filter and no removal) it is idle no more; while none
 * waits the idle method +0x64 runs with its count until it says done; then while the method +0x60
 * reports messages each is handled (+0x68) and the idle count restarted. The method +0x6c ends it.
 * edx kept. */
uint32_t vertrix_port_application_pump_4cc0d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t application = entry->eax;
    uint32_t message = entry->eax + 0x30;
    uint32_t idle = 1;
    uint32_t count = 0;
    uint32_t eax;
    uint32_t edx = entry->edx;
    uint32_t ecx = entry->ecx;
    uint32_t zero[5];
    int state = 1;
    port_open(&port, calls, services, globals, entry);
#define CALL(target, a, d, args, n)                                                                \
    (eax = call_pump(&port, &edx, target, a, d, application, ecx, count, idle, entry->ebp, args, n))
    zero[0] = message;
    zero[1] = zero[2] = zero[3] = zero[4] = 0;
    while (!port.env.failed)
    {
        if (state == 0)
        {
            if (idle == 0)
            {
                state = 2;
                continue;
            }
            state = 1;
        }
        if (state == 1)
        {
            if (CALL(0x4f1a5c, message, edx, zero, 5) != 0)
            {
                state = 2;
                continue;
            }
            ecx = port_u32(&port, application, 0);
            CALL(port_u32(&port, ecx, 0x64), application, count, NULL, 0);
            count++;
            if (eax != 0)
            {
                state = 0;
                continue;
            }
            idle = 0;
            state = 2;
        }
        edx = port_u32(&port, application, 0);
        if (CALL(port_u32(&port, edx, 0x60), application, edx, NULL, 0) == 0)
        {
            break;
        }
        ecx = port_u32(&port, application, 0);
        if (CALL(port_u32(&port, ecx, 0x68), application, message, NULL, 0) != 0)
        {
            idle = 1;
            count = 0;
        }
        if (CALL(0x4f1a5c, message, edx, zero, 5) != 0)
        {
            state = 2;
            continue;
        }
        state = 0;
    }
    edx = port_u32(&port, application, 0);
    CALL(port_u32(&port, edx, 0x6c), application, edx, NULL, 0);
#undef CALL
    return port_return(&port, eax, entry->edx);
}
