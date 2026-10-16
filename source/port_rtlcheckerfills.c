#include "port_rtlcheckerfills.h"

/* Checkered and solid rectangles. */

enum
{
    PHASE = 0x558b28,
    COLOUR = 0x558b40
};

/* A call (with count stack arguments, nearest first) that leaves its edx in *edx; the eax. */
static uint32_t fill_call(Port *port, uint32_t *edx, uint32_t target, uint32_t eax, uint32_t d,
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

/* The phase byte 0x558b28 flipped (1 less it), the old one returned. */
static uint32_t flip_phase(Port *port)
{
    uint32_t phase = port_u8(port, 0, PHASE);
    port_set8(port, 0, PHASE, 1 - phase);
    return phase;
}

/* A row of every other point from *at (the pointer kept at the global at) by the step: with the
 * phase 0 one point skipped and one fewer counted; *esi the count left. */
static void checker_row(Port *port, uint32_t at, uint32_t width, uint32_t step, uint32_t *esi,
                        uint32_t *edx)
{
    uint32_t point;
    *esi = width;
    if (port_u8(port, 0, PHASE) == 0)
    {
        port_set32(port, 0, at, port_u32(port, 0, at) + step / 2);
        *esi = width - 1;
    }
    while ((int32_t)*esi > 0 && !port->env.failed)
    {
        point = port_u32(port, 0, at) + step;
        *esi -= 2;
        if (step == 2)
        {
            *edx = (*edx & ~0xffu) | port_u8(port, 0, COLOUR);
            port_set8(port, point, -2u, *edx);
        }
        else
        {
            *edx = (*edx & ~0xffffu) | port_u16(port, 0, COLOUR);
            port_set16(port, point, -4u, *edx);
        }
        port_set32(port, 0, at, point);
    }
}

/* A row of every other dword point from *edi; with the phase 0 one point skipped. */
static void checker_row32(Port *port, uint32_t width, uint32_t *esi, uint32_t *edi)
{
    *esi = width;
    if (port_u8(port, 0, PHASE) == 0)
    {
        *edi += 4;
        *esi = width - 1;
    }
    while ((int32_t)*esi > 0 && !port->env.failed)
    {
        *edi += 8;
        *esi -= 2;
        port_set32(port, *edi, -8u, port_u32(port, 0, COLOUR));
    }
}

/* Original 0x47bd80 (three stack arguments, popped: the rows, the colour and the border): an
 * ecx-wide checkered rectangle of the surface eax from the point edx, ebx, every other point of
 * the colour (mapped by 0x479a40, kept at 0x558b40) by the phase 0x558b28 (1 at the start,
 * flipped each row), by the depth +0xc (kept at 0x558b3c) of 1, 2 or 4 bytes: from the points +0
 * by the pitch +4 in points, or for a surface with +0x10 from 0x478eb0 (kept at 0x558b44) by the
 * pitch +0x14 in bytes (kept at 0x558b24). The corners kept at 0x558b2c..0x558b38, the walks at
 * 0x558b08..0x558b1c, 0x558b18/0x558b20. A border other than 0xff000000 is drawn round it
 * (0x47c3b0, four lines). Other depths draw nothing. */
uint32_t vertrix_port_surface_checker_rect_47bd80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint8_t stack[BELOW + 8 + 3 * 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t surface = entry->eax;
    uint32_t x = entry->edx;
    uint32_t y = entry->ebx;
    uint32_t width = entry->ecx;
    uint32_t rows;
    uint32_t border;
    uint32_t depth;
    uint32_t pitch;
    uint32_t eax;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    esi = port_u32(&port, 0, 0x558b20);
    edi = port_u32(&port, 0, 0x558b18);
    rows = port_u32(&port, ebp, 8);
    border = port_u32(&port, ebp, 0x10);
    port_set8(&port, 0, 0x558b3c, port_u8(&port, surface, 0xc));
    eax = fill_call(&port, &edx, 0x479a40, surface, port_u32(&port, ebp, 0xc), y, rows, esi, edi,
                    ebp, NULL, 0);
    port_set32(&port, 0, COLOUR, eax);
    port_set32(&port, 0, 0x558b2c, x);
    port_set32(&port, 0, 0x558b34, y);
    port_set32(&port, 0, 0x558b30, x + width - 1);
    port_set32(&port, 0, 0x558b38, y + rows - 1);
    port_set32(&port, 0, 0x558b24, port_u32(&port, surface, 4));
    port_set8(&port, 0, PHASE, 1);
    depth = port_u8(&port, surface, 0xc);
    if (port_u32(&port, surface, 0x10) == 0)
    {
        pitch = port_u32(&port, 0, 0x558b24);
        eax = pitch * y;
        edx = surface;
        edi = port_u32(&port, 0, 0x558b18);
        esi = port_u32(&port, 0, 0x558b20);
        if (depth == 1)
        {
            edx = port_u32(&port, surface, 0) + eax + x;
            port_set32(&port, 0, 0x558b08, edx);
            port_set32(&port, 0, 0x558b0c, edx);
            for (; rows != 0 && !port.env.failed; rows--)
            {
                edx = port_u32(&port, 0, 0x558b0c) + port_u32(&port, 0, 0x558b24);
                port_set32(&port, 0, 0x558b0c, edx);
                checker_row(&port, 0x558b08, width, 2, &esi, &edx);
                edx = (edx & ~0xff00u) | (flip_phase(&port) << 8);
                port_set32(&port, 0, 0x558b08, port_u32(&port, 0, 0x558b0c));
            }
        }
        else if (depth == 2)
        {
            edx = port_u32(&port, surface, 0) + eax * 2 + x * 2;
            port_set32(&port, 0, 0x558b10, edx);
            port_set32(&port, 0, 0x558b14, edx);
            for (; rows != 0 && !port.env.failed; rows--)
            {
                port_set32(&port, 0, 0x558b14,
                           port_u32(&port, 0, 0x558b14) + port_u32(&port, 0, 0x558b24) * 2);
                edx = (edx & ~0xffu) | port_u8(&port, 0, PHASE);
                checker_row(&port, 0x558b10, width, 4, &esi, &edx);
                flip_phase(&port);
                port_set32(&port, 0, 0x558b10, port_u32(&port, 0, 0x558b14));
            }
        }
        else if (depth == 4)
        {
            edx = port_u32(&port, surface, 0);
            edi = (eax << 2) + edx + (x << 2);
            port_set32(&port, 0, 0x558b1c, edi);
            for (; rows != 0 && !port.env.failed; rows--)
            {
                edx = port_u32(&port, 0, 0x558b1c) + (port_u32(&port, 0, 0x558b24) << 2);
                port_set32(&port, 0, 0x558b1c, edx);
                checker_row32(&port, width, &esi, &edi);
                flip_phase(&port);
                edi = port_u32(&port, 0, 0x558b1c);
            }
        }
        else
        {
            return port_return(&port, eax, edx);
        }
    }
    else
    {
        uint32_t address;
        address = fill_call(&port, &edx, 0x478eb0, surface, x, y, rows, esi, edi, ebp, NULL, 0);
        port_set32(&port, 0, 0x558b24, port_u32(&port, surface, 0x14));
        edx = surface;
        port_set32(&port, 0, 0x558b44, address);
        edi = port_u32(&port, 0, 0x558b18);
        esi = port_u32(&port, 0, 0x558b20);
        if (depth == 1)
        {
            port_set32(&port, 0, 0x558b08, address);
            port_set32(&port, 0, 0x558b0c, address);
            for (; rows != 0 && !port.env.failed; rows--)
            {
                port_set32(&port, 0, 0x558b0c,
                           port_u32(&port, 0, 0x558b0c) + port_u32(&port, 0, 0x558b24));
                edx = (edx & ~0xffu) | port_u8(&port, 0, PHASE);
                checker_row(&port, 0x558b08, width, 2, &esi, &edx);
                flip_phase(&port);
                port_set32(&port, 0, 0x558b08, port_u32(&port, 0, 0x558b0c));
            }
        }
        else if (depth == 2)
        {
            port_set32(&port, 0, 0x558b10, address);
            port_set32(&port, 0, 0x558b14, address);
            for (; rows != 0 && !port.env.failed; rows--)
            {
                port_set32(&port, 0, 0x558b14,
                           port_u32(&port, 0, 0x558b14) + port_u32(&port, 0, 0x558b24));
                checker_row(&port, 0x558b10, width, 4, &esi, &edx);
                edx = (edx & ~0xff00u) | (flip_phase(&port) << 8);
                port_set32(&port, 0, 0x558b10, port_u32(&port, 0, 0x558b14));
            }
        }
        else if (depth == 4)
        {
            edi = address;
            port_set32(&port, 0, 0x558b1c, address);
            for (; rows != 0 && !port.env.failed; rows--)
            {
                port_set32(&port, 0, 0x558b1c,
                           port_u32(&port, 0, 0x558b1c) + port_u32(&port, 0, 0x558b24));
                edx = (edx & ~0xffu) | port_u8(&port, 0, PHASE);
                checker_row32(&port, width, &esi, &edi);
                flip_phase(&port);
                edi = port_u32(&port, 0, 0x558b1c);
            }
        }
        else
        {
            return port_return(&port, address, edx);
        }
    }
    port_set32(&port, 0, 0x558b20, esi);
    port_set32(&port, 0, 0x558b18, edi);
    if (border == 0xff000000u)
    {
        return port_return(&port, border, edx);
    }
    {
        uint32_t across = port_u32(&port, 0, 0x558b30) - port_u32(&port, 0, 0x558b2c) + 1;
        uint32_t down = port_u32(&port, 0, 0x558b38) - port_u32(&port, 0, 0x558b34) + 1;
        uint32_t line[2] = {1, border};
        uint32_t side[2] = {down, border};
        fill_call(&port, &edx, 0x47c3b0, surface, port_u32(&port, 0, 0x558b2c),
                  port_u32(&port, 0, 0x558b34), across, esi, edi, ebp, line, 2);
        fill_call(&port, &edx, 0x47c3b0, surface, port_u32(&port, 0, 0x558b2c),
                  port_u32(&port, 0, 0x558b38), across, esi, edi, ebp, line, 2);
        fill_call(&port, &edx, 0x47c3b0, surface, port_u32(&port, 0, 0x558b2c),
                  port_u32(&port, 0, 0x558b34), 1, esi, edi, ebp, side, 2);
        eax = fill_call(&port, &edx, 0x47c3b0, surface, port_u32(&port, 0, 0x558b30),
                        port_u32(&port, 0, 0x558b34), 1, esi, edi, ebp, side, 2);
    }
    return port_return(&port, eax, edx);
}

/* Original 0x47c250 (two stack arguments, popped: the rows and the colour): an ecx-wide solid
 * rectangle of the surface eax from the point edx, ebx in the colour, by the depth +0xc (kept at
 * 0x558b58) of 1, 2 or 4 bytes from the points +0 by the pitch +4 (kept at 0x558b54, the row
 * skip at 0x558b50); the walks left at 0x558b48, 0x558b4c, 0x558b5c and 0x558b60. */
uint32_t vertrix_port_surface_solid_rect_47c250(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint8_t stack[BELOW + 8 + 2 * 4];
    uint32_t surface = entry->eax;
    uint32_t x = entry->edx;
    uint32_t y = entry->ebx;
    uint32_t width = entry->ecx;
    uint32_t rows;
    uint32_t colour;
    uint32_t pitch;
    uint32_t skip;
    uint32_t depth;
    uint32_t eax = surface;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    port_set32(&port, entry->esp, -4u, entry->esi);
    port_set32(&port, entry->esp, -8u, entry->edi);
    port_set32(&port, entry->esp, -0xcu, entry->ebp);
    esi = port_u32(&port, 0, 0x558b4c);
    edi = port_u32(&port, 0, 0x558b60);
    ebp = port_u32(&port, 0, 0x558b48);
    rows = port_u32(&port, entry->esp, 4);
    colour = port_u32(&port, entry->esp, 8);
    depth = port_u8(&port, surface, 0xc);
    port_set8(&port, 0, 0x558b58, depth);
    pitch = port_u32(&port, surface, 4);
    port_set32(&port, 0, 0x558b54, pitch);
    skip = pitch - width;
    port_set32(&port, 0, 0x558b50, skip);
    if (depth == 2)
    {
        edi = pitch * y * 2 + port_u32(&port, surface, 0);
        eax = x * 2;
        edi += eax;
        for (; rows != 0 && !port.env.failed; rows--)
        {
            for (esi = width; esi != 0 && !port.env.failed; esi--)
            {
                edi += 2;
                port_set16(&port, edi, -2u, colour);
            }
            eax = port_u32(&port, 0, 0x558b50) * 2;
            edi += eax;
        }
    }
    else if (depth == 1)
    {
        eax = port_u32(&port, surface, 0) + pitch * y;
        ebp = x + eax;
        port_set8(&port, 0, 0x558b59, colour);
        for (; rows != 0 && !port.env.failed; rows--)
        {
            for (esi = width; esi != 0 && !port.env.failed; esi--)
            {
                ebp++;
                port_set8(&port, ebp, -1u, port_u8(&port, 0, 0x558b59));
            }
            eax = port_u32(&port, 0, 0x558b50);
            ebp += eax;
        }
    }
    else if (depth == 4)
    {
        eax = x << 2;
        port_set32(&port, 0, 0x558b5c, ((pitch * y) << 2) + port_u32(&port, surface, 0) + eax);
        for (; rows != 0 && !port.env.failed; rows--)
        {
            for (esi = width; esi != 0 && !port.env.failed; esi--)
            {
                eax = port_u32(&port, 0, 0x558b5c) + 4;
                port_set32(&port, eax, -4u, colour);
                port_set32(&port, 0, 0x558b5c, eax);
            }
            eax = port_u32(&port, 0, 0x558b50) << 2;
            port_set32(&port, 0, 0x558b5c, port_u32(&port, 0, 0x558b5c) + eax);
        }
    }
    port_set32(&port, 0, 0x558b48, ebp);
    port_set32(&port, 0, 0x558b60, edi);
    port_set32(&port, 0, 0x558b4c, esi);
    return port_return(&port, eax, colour);
}
