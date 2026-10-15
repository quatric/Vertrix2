#include "port_namepairs.h"

/* The two player names of a session. */

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
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* Original 0x48c6c0 (guarded 0x5177c8): the session record (0x47f8f0's edx) names the players.
 * With its side +0x44 1 the names +0x3c and +0x40 go to 0x532c1c and 0x532c20 (0x4ca310), the
 * event 0x5bb498 is set (0x4f1c7c) when 0x532c20 is empty (0x4ccfe0 with 0x510c68), otherwise
 * reset (0x4f1ca0), and the event 0x5bb490 is set; on the other side the names are swapped and
 * 0x532c1c is tested (0x510c69). Both names are then cut to 14 and 3 (0x4cdb70 into the frame,
 * stored by 0x4ca310 and released by 0x4ca210). eax is the guard's link. */
uint32_t vertrix_port_session_names_48c6c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t guard = 0x5177c8;
    uint32_t object = entry->eax;
    uint32_t record;
    uint32_t first;
    uint32_t second;
    uint32_t side;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi = 0;
    uint32_t text;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x30, guard);
    port_call_with(&port, 0x47f8f0, object, object, guard, 0x4ec1ec, 0, entry->edi, ebp);
    record = vertrix_lift_edx;
    ecx = record + 0x40;
    side = port_u32(&port, record, 0x44);
    ebx = record + 0x3c;
    if (side == 1)
    {
        port_call_with(&port, 0x4ca310, 0x532c1c, ebx, ebx, ecx, 0, side, ebp);
        port_call_with(&port, 0x4ca310, 0x532c20, ecx, ebx, ecx, 0, side, ebp);
        eax = port_call_with(&port, 0x4ccfe0, port_u32(&port, 0, 0x532c20), 0x510c68, ebx, ecx, 0,
                             side, ebp);
        if (eax != 0)
        {
            ecx = port_u32(&port, 0, 0x5bb498);
            args[0] = ecx;
            eax =
                call_frame(&port, 0x4f1ca0, eax, vertrix_lift_edx, ebx, ecx, 0, side, ebp, args, 1);
        }
        else
        {
            ebx = port_u32(&port, 0, 0x5bb498);
            args[0] = ebx;
            eax =
                call_frame(&port, 0x4f1c7c, eax, vertrix_lift_edx, ebx, ecx, 0, side, ebp, args, 1);
        }
        esi = port_u32(&port, 0, 0x5bb490);
        args[0] = esi;
        call_frame(&port, 0x4f1c7c, eax, vertrix_lift_edx, ebx, ecx, esi, side, ebp, args, 1);
    }
    else
    {
        first = ecx;
        second = ebx;
        port_call_with(&port, 0x4ca310, 0x532c1c, first, ebx, ecx, 0, side, ebp);
        port_call_with(&port, 0x4ca310, 0x532c20, second, ebx, ecx, 0, side, ebp);
        eax = port_call_with(&port, 0x4ccfe0, port_u32(&port, 0, 0x532c1c), 0x510c69, ebx, ecx, 0,
                             side, ebp);
        if (eax == 0)
        {
            edx = port_u32(&port, 0, 0x5bb498);
            args[0] = edx;
            call_frame(&port, 0x4f1c7c, eax, edx, ebx, ecx, 0, side, ebp, args, 1);
        }
        else
        {
            eax = port_u32(&port, 0, 0x5bb498);
            args[0] = eax;
            call_frame(&port, 0x4f1ca0, eax, vertrix_lift_edx, ebx, ecx, 0, side, ebp, args, 1);
        }
    }
    text = port_call_with(&port, 0x4cdb70, 0x532c1c, ebp - 0x1c, 0xe, ecx, esi, 1, ebp);
    port_set32(&port, ebp, -0x24u, 1);
    port_call_with(&port, 0x4ca310, 0x532c1c, text, 0xe, ecx, esi, 1, ebp);
    port_set32(&port, ebp, -0x24u, 0);
    port_call_with(&port, 0x4ca210, ebp - 0x1c, 0, 0xe, ecx, esi, 1, ebp);
    port_set32(&port, ebp, -0x24u, 0);
    text = port_call_with(&port, 0x4cdb70, 0x532c20, ebp - 0x18, 0xe, 3, esi, 1, ebp);
    port_set32(&port, ebp, -0x24u, 3);
    port_call_with(&port, 0x4ca310, 0x532c20, text, 0, 3, esi, 1, ebp);
    port_set32(&port, ebp, -0x24u, 0);
    port_call_with(&port, 0x4ca210, ebp - 0x18, 0, 0, 3, esi, 1, ebp);
    port_set32(&port, ebp, -0x24u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x30u), entry->edx);
}
