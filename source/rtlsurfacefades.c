#include "rtlsurfacefades.h"

/* A surface region faded towards its blur. */

enum
{
    FORM_DWORD,
    FORM_565,
    FORM_555
};

/* The pixel at address as 0xRRGGBB (16-bit forms widened by eight bits a channel). */
static uint32_t pixel(Port *port, uint32_t address, int form)
{
    uint32_t word;
    if (form == FORM_DWORD)
    {
        return port_u32(port, address, 0) & 0xffffff;
    }
    word = port_u16(port, address, 0);
    if (form == FORM_565)
    {
        return (((word & 0xf800) << 5) | ((word & 0x7e0) << 2) | (word & 0x1f)) << 3;
    }
    return (((word & 0x7c00) << 6) | ((word & 0x3e0) << 3) | (word & 0x1f)) << 3;
}

/* The channel sums divided by the count (a zero count, with nothing summed, leaves 0). */
static uint32_t average(uint32_t sum, uint32_t count)
{
    return count != 0 ? sum / count : sum;
}

/* The neighbour at address added to the three channel sums. */
static void add_pixel(Port *port, uint32_t address, int form, uint32_t *sum, uint32_t *count)
{
    uint32_t value = pixel(port, address, form);
    sum[0] += (value >> 16) & 0xff;
    sum[1] += (value >> 8) & 0xff;
    sum[2] += value & 0xff;
    (*count)++;
}

/* Original 0x47a040 (two stack arguments, popped: the height and the level 0..100): the ecx by
 * height region at edx, ebx of the surface eax (not 8-bit) faded: copied into a new surface of its
 * depth and format (0x478d10, 0x47ce10), then each pixel set to the level's table 0x558cf0 + level
 * * 256 (at 0x55f1f0) of itself plus the table of 100 - level (at 0x55f1f4) of the average of its
 * up to four neighbours in the copy, a channel at a time (OR-ed together), for 32-bit and 16-bit
 * 5-6-5 (format 0x558a79 2) or 5-5-5 surfaces; the copy freed (0x478d80, whose eax and edx are
 * returned). */
uint32_t vertrix_port_surface_fade_47a040(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xbc
    };
    Port port;
    uint8_t stack[BELOW + 8 + 2 * 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t source = entry->eax;
    uint32_t x = entry->edx;
    uint32_t y = entry->ebx;
    uint32_t width = entry->ecx;
    uint32_t height;
    uint32_t level;
    uint32_t depth;
    uint32_t format;
    uint32_t pitch;
    uint32_t copy;
    uint32_t mix;
    uint32_t rest;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t size;
    uint32_t form;
    uint32_t start;
    uint32_t row;
    uint32_t column;
    uint32_t copy_row;
    uint32_t target;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    height = port_u32(&port, ebp, 8);
    level = port_u32(&port, ebp, 0xc);
    depth = port_u8(&port, source, 0xc);
    format = port_u8(&port, source, 0xd);
    port_set8(&port, 0, 0x558a79, format);
    pitch = port_u32(&port, source, 4);
    if (depth == 1)
    {
        return port_return(&port, (pitch & 0xffff00ffu) | 0x100, entry->edx);
    }
    copy = port_call_with(&port, 0x478d10, width, height, depth, width, source, entry->edi, ebp);
    port_set8(&port, copy, 0xd, port_u8(&port, 0, 0x558a79));
    {
        uint32_t args[4] = {x, y, width, height};
        port_call_registers(&port, 0x47ce10, copy, source, 0, 0, source, copy, ebp, args, 4);
    }
    mix = 0x558cf0 + (level << 8);
    rest = 0x558cf0 + ((0x64 - level) << 8);
    edx = pitch * y;
    ebx = height - 1;
    ecx = ((width - 1) & 0xffffff00u) | depth;
    if (depth != 4 && depth != 2)
    {
        return port_return(&port,
                           port_call_with(&port, 0x478d80, copy, edx, ebx, ecx, source, copy, ebp),
                           vertrix_lift_edx);
    }
    port_set32(&port, 0, 0x55f1f0, mix);
    port_set32(&port, 0, 0x55f1f4, rest);
    size = depth;
    form = depth == 4 ? FORM_DWORD : port_u8(&port, 0, 0x558a79) == 2 ? FORM_565 : FORM_555;
    start = port_u32(&port, source, 0) + edx * size + x * size;
    copy_row = port_u32(&port, copy, 0);
    target = start;
    for (row = 0; row < height && !port.env.failed; row++)
    {
        uint32_t walk = copy_row;
        uint32_t out = target;
        for (column = 0; column < width && !port.env.failed; column++)
        {
            uint32_t sum[3] = {0, 0, 0};
            uint32_t count = 0;
            uint32_t centre;
            uint32_t blur;
            uint32_t red;
            uint32_t green;
            uint32_t blue;
            uint32_t value;
            if (row > 0)
            {
                add_pixel(&port, walk - width * size, form, sum, &count);
            }
            if (row < height - 1)
            {
                add_pixel(&port, walk + width * size, form, sum, &count);
            }
            if (column > 0)
            {
                add_pixel(&port, walk - size, form, sum, &count);
            }
            if (column < width - 1)
            {
                add_pixel(&port, walk + size, form, sum, &count);
            }
            blur = (average(sum[0], count) << 16) | (average(sum[1], count) << 8) |
                   average(sum[2], count);
            centre = pixel(&port, walk, form);
            red = port_u8(&port, mix, (centre >> 16) & 0xff) +
                  port_u8(&port, rest, (blur >> 16) & 0xff);
            green = port_u8(&port, mix, (centre >> 8) & 0xff) +
                    port_u8(&port, rest, ((blur & 0xffff) >> 8) & 0xff);
            blue = port_u8(&port, mix, centre & 0xff) + port_u8(&port, rest, blur & 0xff);
            value = (red << 16) | (green << 8) | blue;
            if (form == FORM_DWORD)
            {
                port_set32(&port, out, 0, value);
            }
            else if (form == FORM_565)
            {
                port_set16(&port, out, 0,
                           (((value & 0xf80000) >> 5) | ((value & 0xfc00) >> 2) | (value & 0xf8)) >>
                               3);
            }
            else
            {
                port_set16(&port, out, 0,
                           (((value & 0xf80000) >> 6) | ((value & 0xf800) >> 3) | (value & 0xf8)) >>
                               3);
            }
            out += size;
            walk += size;
        }
        copy_row += width * size;
        target += pitch * size;
    }
    /* The registers the original leaves for 0x478d80 on each way out. */
    if (form == FORM_DWORD)
    {
        edx = height != 0 ? width : start;
        ebx = height != 0 ? target : height - 1;
        ecx = height != 0 ? copy_row : ecx;
    }
    else if (form == FORM_565)
    {
        edx = height != 0 && width != 0 ? copy_row : 0;
        ebx = height != 0 ? target : height - 1;
        ecx = height != 0 ? copy_row : 0;
    }
    else
    {
        edx = height != 0 ? copy_row : (start & 0xffffff00u) | port_u8(&port, 0, 0x558a79);
        ebx = height != 0 ? height : height - 1;
        ecx = height != 0 ? target : ecx;
    }
    return port_return(&port,
                       port_call_with(&port, 0x478d80, copy, edx, ebx, ecx, source, copy, ebp),
                       vertrix_lift_edx);
}
