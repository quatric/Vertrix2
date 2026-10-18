#include "glows.h"

/* The glow of a surface's shape spread by a kernel. */

/* Original 0x4831b0: the surface eax (pixels +0, width +4, height +8, place +0xc, +0x10) spread
 * by the kernel surface edx (pixels, width, height): a new surface (0x483060 at the place less
 * half the kernel, the size plus the kernel's halves twice, with 0, 0, 1 and 4) counts at each
 * pixel the kernel's pixels with alpha laid over each pixel of the source with alpha; each count
 * becomes an opaque grey (0xff at most; none stays 0) and, unless ebx is set, the glow under the
 * source's shape loses its alpha (the source's own place). Returns the new surface; edx is the
 * glow's end (a grey pass over it) for ebx set, else the source's height. */
uint32_t vertrix_port_surface_glow_4831b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t source = entry->eax;
    uint32_t kernel = entry->edx;
    uint32_t kernel_width;
    uint32_t kernel_height;
    uint32_t half_width;
    uint32_t half_height;
    uint32_t width;
    uint32_t height;
    uint32_t glow_width;
    uint32_t glow_height;
    uint32_t glow;
    uint32_t args[8];
    uint32_t from;
    uint32_t row;
    uint32_t row_at;
    uint32_t x;
    uint32_t to;
    uint32_t taps;
    uint32_t k;
    uint32_t at;
    uint32_t end;
    uint32_t value;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    kernel_width = port_u32(&port, kernel, 4);
    kernel_height = port_u32(&port, kernel, 8);
    half_width = kernel_width >> 1;
    half_height = kernel_height >> 1;
    width = port_u32(&port, source, 4);
    height = port_u32(&port, source, 8);
    glow_width = width + half_width * 2;
    glow_height = height + half_height * 2;
    args[0] = 0;
    args[1] = 0;
    args[2] = glow_width;
    args[3] = glow_height;
    args[4] = 0;
    args[5] = 0;
    args[6] = 1;
    args[7] = 4;
    glow = port_call_registers(&port, 0x483060, glow_width, glow_height,
                               port_u32(&port, source, 0xc) + half_width,
                               port_u32(&port, source, 0x10) + half_height, half_width, entry->edi,
                               entry->esp - 4, args, 8);
    from = port_u32(&port, source, 0);
    if (height != 0)
    {
        row = 0;
        row_at = 0;
        do
        {
            if (width != 0)
            {
                x = 0;
                do
                {
                    if ((port_u32(&port, from, 0) >> 24) != 0)
                    {
                        to = port_u32(&port, glow, 0) + x * 4 + row_at;
                        taps = port_u32(&port, kernel, 0);
                        if (kernel_height != 0)
                        {
                            k = 0;
                            do
                            {
                                if (kernel_width != 0)
                                {
                                    at = to;
                                    end = kernel_width * 4 + to;
                                    do
                                    {
                                        if ((port_u32(&port, taps, 0) >> 24) != 0)
                                        {
                                            port_set32(&port, at, 0, port_u32(&port, at, 0) + 1);
                                        }
                                        at += 4;
                                        taps += 4;
                                    } while (at < end && !port.env.failed);
                                }
                                k++;
                                to += glow_width * 4;
                            } while (k < kernel_height && !port.env.failed);
                        }
                    }
                    from += 4;
                    x++;
                } while (x < width && !port.env.failed);
            }
            row_at += glow_width * 4;
            row++;
        } while (row < height && !port.env.failed);
    }
    edx = port_u32(&port, glow, 0);
    if (glow_height != 0)
    {
        row = 0;
        do
        {
            if (glow_width != 0)
            {
                x = 0;
                do
                {
                    value = port_u32(&port, edx, 0);
                    if (value != 0)
                    {
                        if (value > 0xff)
                        {
                            value = 0xff;
                        }
                        port_set32(&port, edx, 0,
                                   value | ((value << 8) | (value << 16)) | 0xff000000u);
                    }
                    x++;
                    edx += 4;
                } while (x < glow_width && !port.env.failed);
            }
            row++;
        } while (row < glow_height && !port.env.failed);
    }
    if (entry->ebx != 0)
    {
        return port_return(&port, glow, edx);
    }
    to = (half_height * glow_width << 2) + (half_width << 2) + port_u32(&port, glow, 0);
    from = port_u32(&port, source, 0);
    if (height != 0)
    {
        row = 0;
        do
        {
            if (width != 0)
            {
                at = to;
                end = width * 4 + to;
                do
                {
                    if ((port_u32(&port, from, 0) >> 24) != 0)
                    {
                        port_set32(&port, at, 0, port_u32(&port, at, 0) & 0xffffffu);
                    }
                    at += 4;
                    from += 4;
                } while (at < end && !port.env.failed);
            }
            row++;
            to += glow_width * 4;
        } while (row < height && !port.env.failed);
    }
    return port_return(&port, glow, height);
}
