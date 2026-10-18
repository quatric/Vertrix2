#include "rtlsurfaceboundses.h"

enum
{
    SURFACE_WIDTH = 4,
    SURFACE_HEIGHT = 8,
    ARGUMENT_HEIGHT_OUT = 4,
    ARGUMENTS = 1,

    PIXEL_SET = 0x478f10
};

/* Original 0x4792d0 (eax = a surface, edx, ebx and ecx = where the left, top and width go, the
 * stack argument where the height goes; ret 4): the box around the pixels 0x478f10 reports set,
 * scanning each column top to bottom with word counters while they stay at or below the last
 * column and row. The box's edges are words, compared signed: the left and top start at the last
 * column and row, the right and bottom at 0. When the left is still the last column the box is the
 * whole surface (0, 0, the width, the height). Returns 0 when the stored box (read back) is the
 * whole surface and 1 otherwise; no caller reads edx. */
uint32_t vertrix_port_surface_bounds_4792d0(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 4 * ARGUMENTS];
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, ARGUMENTS);
    const uint32_t surface = entry->eax;
    const uint32_t left_out = entry->edx;
    const uint32_t top_out = entry->ebx;
    const uint32_t width_out = entry->ecx;
    const uint32_t height_out = port_u32(&port, entry->esp, ARGUMENT_HEIGHT_OUT);
    const int32_t last_column = (int32_t)(port_u32(&port, surface, SURFACE_WIDTH) - 1);
    const int32_t last_row = (int32_t)(port_u32(&port, surface, SURFACE_HEIGHT) - 1);
    int16_t left = (int16_t)last_column;
    int16_t top = (int16_t)last_row;
    int16_t right = 0;
    int16_t bottom = 0;
    for (uint16_t x = 0; (int32_t)x <= last_column && !port.env.failed; x++)
    {
        for (uint16_t y = 0; (int32_t)y <= last_row && !port.env.failed; y++)
        {
            if (port_call(&port, PIXEL_SET, surface, x, y, 0) == 0)
            {
                continue;
            }
            if (x < left)
            {
                left = (int16_t)x;
            }
            if (x > right)
            {
                right = (int16_t)x;
            }
            if (y < top)
            {
                top = (int16_t)y;
            }
            if (y > bottom)
            {
                bottom = (int16_t)y;
            }
        }
    }
    if (left == last_column)
    {
        port_set32(&port, left_out, 0, 0);
        port_set32(&port, top_out, 0, 0);
        port_set32(&port, width_out, 0, (uint32_t)last_column + 1);
        port_set32(&port, height_out, 0, (uint32_t)last_row + 1);
    }
    else
    {
        port_set32(&port, left_out, 0, (uint32_t)(int32_t)left);
        port_set32(&port, top_out, 0, (uint32_t)(int32_t)top);
        port_set32(&port, width_out, 0, (uint32_t)(right - left + 1));
        port_set32(&port, height_out, 0, (uint32_t)(bottom - top + 1));
    }
    const int whole = port_u32(&port, left_out, 0) == 0 && port_u32(&port, top_out, 0) == 0 &&
                      port_u32(&port, width_out, 0) == port_u32(&port, surface, SURFACE_WIDTH) &&
                      port_u32(&port, height_out, 0) == port_u32(&port, surface, SURFACE_HEIGHT);
    return port_return(&port, whole ? 0 : 1, 0);
}
