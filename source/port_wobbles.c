#include "port_wobbles.h"

/* The pieces' wobble. */

/* The wobbling piece eax (+0x95 1, 0x4ac1f0) when due (0x4ac500, 0x4ac520)
 * takes its stride (0x4ac540, 0x4ac5b0), whether it is done (0x4acc10) and its size (0x4b14c0
 * into the width and height): placed at its +8, +0xa plus the room left of 0x18 (whole for the
 * phase +0x24 0, 1 and 2 across, 1, 5 and 6 down, 7 both; half for 3 across, 1 and 5 down; none
 * otherwise, the phases past 7 placing it at its esi, edi), lit +0x4e at 50 parts of 16 of
 * +0x44 plus 0x32; when 0x4ad750 lets it the phase steps by the stride, below 8. Done, it takes
 * the state `state` (+0x4e cleared first with `dark`). Turned (0x4ac8a0) in the end; the
 * registers but eax kept. */
static uint32_t wobble_step(PORT_SIGNATURE, uint32_t state, int dark)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t piece = entry->eax;
    uint32_t stride;
    uint32_t done;
    uint32_t across;
    uint32_t down;
    uint32_t half;
    uint32_t phase;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set8(&port, piece, 0x95, 1);
    port_call_with(&port, 0x4ac1f0, piece, entry->edx, ebx, piece, esi, edi, ebp);
    port_call_with(&port, 0x4ac500, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
    if (port_call_with(&port, 0x4ac520, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp) != 1)
    {
        eax = port_call_with(&port, 0x4ac8a0, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
        return port_return(&port, eax, entry->edx);
    }
    stride = port_call_with(&port, 0x4ac540, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
    port_set32(&port, ebp, -0x18u, stride);
    port_call_with(&port, 0x4ac5b0, piece, stride, ebx, piece, esi, edi, ebp);
    ebx = ebp - 0x20;
    done = port_call_with(&port, 0x4acc10, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
    port_set32(&port, ebp, -0x1cu, done);
    port_set32(&port, ebp, -0x28u, 0);
    port_set32(&port, ebp, -0x20u, 0);
    port_call_with(&port, 0x4b14c0, piece, ebp - 0x28, ebx, piece, esi, edi, ebp);
    ebx = port_u32(&port, ebp, -0x20u);
    down = 0x18 - ebx;
    across = 0x18 - port_u32(&port, ebp, -0x28u);
    phase = port_u16(&port, piece, 0x24);
    if (phase == 0)
    {
        esi = across;
        edi = down;
    }
    else
    {
        half = down >> 1;
        port_set32(&port, ebp, -0x24u, half);
        ebx = (half & 0xffff0000u) | phase;
        if (phase == 1)
        {
            edi = half;
            esi = across;
        }
        else if (phase == 2)
        {
            esi = across;
            edi = 0;
        }
        else if (phase == 3)
        {
            esi = across >> 1;
            edi = 0;
        }
        else if (phase == 4)
        {
            esi = 0;
            edi = 0;
        }
        else if (phase == 5)
        {
            edi = half;
            esi = 0;
        }
        else if (phase == 6)
        {
            edi = down;
            esi = 0;
        }
        else if (phase == 7)
        {
            esi = across >> 1;
            edi = down;
        }
    }
    port_set16(&port, piece, 0xe, port_u16(&port, piece, 8) + esi);
    port_set16(&port, piece, 0x16, port_u16(&port, piece, 0xa) + edi);
    port_set8(&port, piece, 0x4e, ((port_u8(&port, piece, 0x44) * 50) >> 4) + 0x32);
    if (port_call_with(&port, 0x4ad750, piece, stride, ebx, piece, esi, edi, ebp) == 0)
    {
        port_set16(&port, piece, 0x24, port_u16(&port, piece, 0x24) + port_u32(&port, ebp, -0x18u));
        edx = (uint32_t)((int32_t)(int16_t)port_u16(&port, piece, 0x24) % 8);
        port_set16(&port, piece, 0x24, edx);
        ebx = 8;
    }
    else
    {
        edx = vertrix_lift_edx;
    }
    if (port_u32(&port, ebp, -0x1cu) == 0)
    {
        if (dark)
        {
            port_set8(&port, piece, 0x4e, 0);
        }
        port_call_with(&port, 0x4ac8f0, piece, state, ebx, piece, esi, edi, ebp);
        edx = vertrix_lift_edx;
    }
    eax = port_call_with(&port, 0x4ac8a0, piece, edx, ebx, piece, esi, edi, ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x44ccd0: the wobble ending in the state 0x44ce80. */
uint32_t vertrix_port_piece_wobble_44ccd0(PORT_SIGNATURE)
{
    return wobble_step(calls, services, globals, entry, 0x44ce80, 0);
}

/* Original 0x44d030: the wobble ending dark (+0x4e 0) in the state 0x44c860. */
uint32_t vertrix_port_piece_wobble_dark_44d030(PORT_SIGNATURE)
{
    return wobble_step(calls, services, globals, entry, 0x44c860, 1);
}
