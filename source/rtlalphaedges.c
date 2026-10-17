#include "rtlalphaedges.h"

/* Smooths a 32-bit image: each pixel is mixed with the average colour of its neighbours above,
 * below, left and right, by a percentage, through the two multiplication tables of 0x558cf0. */

enum
{
    IMAGE_PIXELS = 0,
    IMAGE_WIDTH = 4,
    IMAGE_HEIGHT = 8,
    IMAGE_ALPHA_EDGES = 0x26,
    IMAGE_BYTES_PER_PIXEL = 0x27,
    /* The only depth it works on. */
    PIXEL_BYTES = 4,
    OPAQUE = 0xff000000u,

    /* 101 rows of 256 bytes, row p holding v * p / 100; the two in use. */
    PERCENT_TABLES = 0x558cf0,
    OWN_TABLE = 0x55f1f0,
    AVERAGE_TABLE = 0x55f1f4,

    CALLOC = 0x4ec160,
    FREE = 0x4ea190
};

typedef struct
{
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    uint32_t count;
} Sum;

static void add(Sum *sum, uint32_t pixel)
{
    sum->red += (pixel >> 16) & 0xff;
    sum->green += (pixel >> 8) & 0xff;
    sum->blue += pixel & 0xff;
    sum->count++;
}

/* div with the dividend kept when the divisor is 0, as the lifted runtime does (a one-pixel image
 * without alpha edges). */
static uint32_t divide(uint32_t value, uint32_t by)
{
    return by != 0 ? value / by : value;
}

static uint32_t average(const Sum *sum)
{
    return divide(sum->red, sum->count) << 16 | divide(sum->green, sum->count) << 8 |
           divide(sum->blue, sum->count);
}

/* The pixel's own channels by the own table plus the average's by the other, opaque. */
static uint32_t mix(Port *port, uint32_t pixel, uint32_t mean)
{
    const uint32_t own = port_u32(port, OWN_TABLE, 0);
    const uint32_t other = port_u32(port, AVERAGE_TABLE, 0);
    uint32_t result = OPAQUE;
    for (unsigned shift = 16;; shift -= 8)
    {
        result |= (port_u8(port, own, (pixel >> shift) & 0xff) +
                   port_u8(port, other, (mean >> shift) & 0xff))
                  << shift;
        if (shift == 0)
        {
            return result;
        }
    }
}

/* Original 0x483790 (eax = the image, edx = the percentage of each pixel's own colour). Only for 4
 * bytes per pixel: works from a copy (calloc, freed after). With alpha edges set only opaque
 * neighbours count, and a transparent pixel with opaque neighbours takes their average scaled by
 * the rest of the percentage, staying transparent; otherwise every neighbour counts and every
 * pixel becomes opaque. */
uint32_t vertrix_port_image_alpha_edge_smooth_483790(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t image = entry->eax;
    const uint32_t percent = entry->edx;
    const uint32_t rest = 100 - percent;
    const uint32_t width = port_u32(&port, image, IMAGE_WIDTH);
    const uint32_t height = port_u32(&port, image, IMAGE_HEIGHT);
    const uint32_t depth = port_u8(&port, image, IMAGE_BYTES_PER_PIXEL);
    if (depth != PIXEL_BYTES)
    {
        return port_return(&port, 0, 0);
    }
    port_set32(&port, OWN_TABLE, 0, PERCENT_TABLES + (percent << 8));
    port_set32(&port, AVERAGE_TABLE, 0, PERCENT_TABLES + (rest << 8));
    const uint32_t pixels = port_u32(&port, image, IMAGE_PIXELS);
    const uint32_t bytes = depth * (width * height);
    const uint32_t copy = port_call(&port, CALLOC, bytes, 1, 0, 0);
    port_copy(&port, copy, port_u32(&port, image, IMAGE_PIXELS), bytes);
    const uint32_t stride = width * PIXEL_BYTES;
    const int alpha_edges = port_u8(&port, image, IMAGE_ALPHA_EDGES) == 1;

    for (uint32_t y = 0; y < height && !port.env.failed; y++)
    {
        for (uint32_t x = 0; x < width && !port.env.failed; x++)
        {
            const uint32_t from = copy + y * stride + x * PIXEL_BYTES;
            const uint32_t to = pixels + y * stride + x * PIXEL_BYTES;
            const uint32_t neighbours[4][2] = {{y > 0, from - stride},
                                               {y < height - 1, from + stride},
                                               {x > 0, from - PIXEL_BYTES},
                                               {x < width - 1, from + PIXEL_BYTES}};
            Sum sum = {0, 0, 0, 0};
            for (unsigned i = 0; i < 4; i++)
            {
                if (!neighbours[i][0])
                {
                    continue;
                }
                const uint32_t pixel = port_u32(&port, neighbours[i][1], 0);
                if (!alpha_edges || pixel >> 24 != 0)
                {
                    add(&sum, pixel);
                }
            }
            if (sum.count == 0)
            {
                continue;
            }
            const uint32_t pixel = port_u32(&port, from, 0);
            if (alpha_edges && pixel >> 24 == 0)
            {
                port_set32(&port, to, 0,
                           (sum.red / sum.count * rest / 100) << 16 |
                               (sum.green / sum.count * rest / 100) << 8 |
                               sum.blue / sum.count * rest / 100);
                continue;
            }
            port_set32(&port, to, 0, mix(&port, pixel, average(&sum)));
        }
    }
    port_call(&port, FREE, copy, 0, 0, 0);
    return port_return(&port, 0, 0);
}
