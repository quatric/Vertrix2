#include "rectfills.h"

/* The clipped rectangle fill. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x47c710: the rectangle bx, cx to the first and second stack words on the surface eax
 * in the colour of the seventh (none for 0xff000000; guarded 0x516858), clipped to the third to
 * sixth (left, top, right, bottom) and dropped when outside; its size goes to the words 0x558b8c
 * and 0x558b8e and, when both are above 0, a 32 bit pixel format at ebp-0x50 (0x481b20, 0x481bc0
 * of 0xff0000, 0xff00, 0xff and 0xff000000; released by 0x481b30) converts the colour with edx
 * (0x481e10) and the surface is filled (0x47c3b0). Returns the guard's link. ret 0x1c. */
uint32_t vertrix_port_surface_fill_clipped_47c710(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x54
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0x1c];
    uint32_t ebp = entry->esp - 4;
    uint32_t surface = entry->eax;
    uint32_t left = entry->ebx;
    uint32_t top = entry->ecx;
    uint32_t right;
    uint32_t bottom;
    uint32_t edx;
    uint32_t width;
    uint32_t height;
    uint32_t colour;
    uint32_t pushed[2];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 7);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x10u, surface);
    port_set32(&port, ebp, -0xcu, entry->edx);
    right = port_u32(&port, ebp, 8);
    bottom = port_u32(&port, ebp, 0xc);
    port_set32(&port, ebp, -0x24u, port.env.chain);
    port_set32(&port, ebp, -0x20u, 0x4ec1ec);
    port_set32(&port, ebp, -0x1cu, 0x516858);
    port_set32(&port, ebp, -0x18u, 0);
    if (port_u32(&port, ebp, 0x20) == 0xff000000u ||
        (int32_t)left > (int32_t)port_u32(&port, ebp, 0x18) ||
        (int32_t)right < (int32_t)port_u32(&port, ebp, 0x10) ||
        (int32_t)top > (int32_t)port_u32(&port, ebp, 0x1c) ||
        (int32_t)bottom < (int32_t)port_u32(&port, ebp, 0x14))
    {
        return port_return(&port, port_u32(&port, ebp, -0x24u), right);
    }
    if ((int32_t)top < (int32_t)port_u32(&port, ebp, 0x14))
    {
        top = port_u32(&port, ebp, 0x14);
    }
    if ((int32_t)left < (int32_t)port_u32(&port, ebp, 0x10))
    {
        left = port_u32(&port, ebp, 0x10);
    }
    if ((int32_t)bottom > (int32_t)port_u32(&port, ebp, 0x1c))
    {
        bottom = port_u32(&port, ebp, 0x1c);
    }
    if ((int32_t)right > (int32_t)port_u32(&port, ebp, 0x18))
    {
        right = port_u32(&port, ebp, 0x18);
    }
    edx = right - left + 1;
    port_set16(&port, 0, 0x558b8c, edx);
    port_set16(&port, 0, 0x558b8e, bottom - top + 1);
    width = (uint32_t)(int32_t)(int16_t)port_u16(&port, 0, 0x558b8c);
    height = (uint32_t)(int32_t)(int16_t)port_u16(&port, 0, 0x558b8e);
    if ((int32_t)width <= 0 || (int32_t)height <= 0)
    {
        return port_return(&port, port_u32(&port, ebp, -0x24u), edx);
    }
    port_call_with(&port, 0x481b20, ebp - 0x50, 0xff0000, 0xff00, 0xff, left, top, ebp);
    port_set32(&port, ebp, -0x18u, 1);
    pushed[0] = 0xff000000u;
    if (call_frame(&port, 0x481bc0, ebp - 0x50, 0xff0000, 0xff00, 0xff, left, top, ebp, pushed,
                   1) == 0)
    {
        port_call_with(&port, 0x481b30, ebp - 0x50, 0, 0xff00, 0xff, left, top, ebp);
        return port_return(&port, port_u32(&port, ebp, -0x24u), vertrix_lift_edx);
    }
    colour = port_call_with(&port, 0x481e10, ebp - 0x50, port_u32(&port, ebp, -0xcu),
                            port_u32(&port, ebp, 0x20), 0xff, left, top, ebp);
    pushed[0] = (uint32_t)(int32_t)(int16_t)port_u16(&port, 0, 0x558b8e);
    pushed[1] = colour;
    call_frame(&port, 0x47c3b0, surface, left, top,
               (uint32_t)(int32_t)(int16_t)port_u16(&port, 0, 0x558b8c), left, top, ebp, pushed, 2);
    port_set32(&port, ebp, -0x18u, 0);
    port_call_with(&port, 0x481b30, ebp - 0x50, 0, top, 0, left, top, ebp);
    port_set32(&port, ebp, -0x18u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x24u), vertrix_lift_edx);
}
