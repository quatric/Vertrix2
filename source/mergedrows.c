#include "mergedrows.h"

/* The image decoder's merged and fancy upsampling. */

/* One merged pixel: the luma at `luma` with the chroma terms through the range limit `limit` into
 * the three bytes at `out`; edx as the original leaves it. */
static uint32_t merged_pixel(Port *port, uint32_t luma, uint32_t limit, uint32_t out, uint32_t red,
                             uint32_t green, uint32_t blue)
{
    uint32_t y = port_u8(port, luma, 0);
    uint32_t last;
    port_set8(port, out, 0, port_u8(port, limit + red + y, 0));
    port_set8(port, out, 1, port_u8(port, limit + green + y, 0));
    last = port_u8(port, limit + y + blue, 0);
    port_set8(port, out, 2, last);
    return ((y + blue) & 0xffffff00u) | last;
}

/* Original 0x4c1e40: one row (group ebx of the planes edx into the row ecx) of the decoder eax's
 * 2:1 horizontal merged upsampling: each chroma pair (the upsampler +0x1c4's Cr red +0x10, Cb
 * blue +0x14, Cr +0x18 and Cb +0x1c green tables, the green term the high half) serves two lumas,
 * half the width +0x70 of them, and an odd last luma one more. Through the range limit +0x144;
 * eax is the output place, edx the decoder (the last pixel's on an odd width). */
uint32_t vertrix_port_merged_upsample_h2v1_4c1e40(PORT_SIGNATURE)
{
    Port port;
    uint32_t cinfo = entry->eax;
    uint32_t upsample;
    uint32_t red_table;
    uint32_t blue_table;
    uint32_t green_red;
    uint32_t green_blue;
    uint32_t offset = entry->ebx * 4;
    uint32_t luma;
    uint32_t cb_in;
    uint32_t cr_in;
    uint32_t out;
    uint32_t pairs;
    uint32_t limit;
    uint32_t cb;
    uint32_t cr;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    upsample = port_u32(&port, cinfo, 0x1c4);
    red_table = port_u32(&port, upsample, 0x10);
    blue_table = port_u32(&port, upsample, 0x14);
    green_red = port_u32(&port, upsample, 0x18);
    green_blue = port_u32(&port, upsample, 0x1c);
    luma = port_u32(&port, port_u32(&port, entry->edx, 0) + offset, 0);
    cb_in = port_u32(&port, port_u32(&port, entry->edx, 4) + offset, 0);
    cr_in = port_u32(&port, port_u32(&port, entry->edx, 8) + offset, 0);
    out = port_u32(&port, entry->ecx, 0);
    pairs = port_u32(&port, cinfo, 0x70) >> 1;
    limit = port_u32(&port, cinfo, 0x144);
    while (pairs != 0 && !port.env.failed)
    {
        cb = port_u8(&port, cb_in, 0);
        cr = port_u8(&port, cr_in, 0);
        cb_in++;
        cr_in++;
        red = port_u32(&port, red_table + cr * 4, 0);
        green = (uint32_t)((int32_t)(port_u32(&port, green_blue + cb * 4, 0) +
                                     port_u32(&port, green_red + cr * 4, 0)) >>
                           16);
        blue = port_u32(&port, blue_table + cb * 4, 0);
        merged_pixel(&port, luma, limit, out, red, green, blue);
        out += 3;
        merged_pixel(&port, luma + 1, limit, out, red, green, blue);
        out += 3;
        luma += 2;
        pairs--;
    }
    edx = cinfo;
    if (port_u8(&port, cinfo, 0x70) & 1)
    {
        cb = port_u8(&port, cb_in, 0);
        cr = port_u8(&port, cr_in, 0);
        red = port_u32(&port, red_table + cr * 4, 0);
        green = (uint32_t)((int32_t)(port_u32(&port, green_blue + cb * 4, 0) +
                                     port_u32(&port, green_red + cr * 4, 0)) >>
                           16);
        blue = port_u32(&port, blue_table + cb * 4, 0);
        edx = merged_pixel(&port, luma, limit, out, red, green, blue);
    }
    return port_return(&port, out, edx);
}

/* Original 0x4c3a30: 2:1 by 2:1 fancy upsampling of the component edx (its width +0x28) for the
 * decoder eax: each of its +0x138 row groups of ebx makes two rows of [ecx], each from the row and
 * its upper or lower neighbour weighted 3:1 down the column and 3:1 across, the end columns
 * copied. eax is the row count, edx the decoder (with no rows, the decoder and 0). */
uint32_t vertrix_port_fancy_upsample_h2v2_4c3a30(PORT_SIGNATURE)
{
    Port port;
    uint32_t cinfo = entry->eax;
    uint32_t component = entry->edx;
    uint32_t rows;
    uint32_t place = entry->ebx;
    uint32_t outrow = 0;
    uint32_t v;
    uint32_t near;
    uint32_t far;
    uint32_t out;
    uint32_t this_sum;
    uint32_t next_sum;
    uint32_t last_sum;
    uint32_t count;
    port_open(&port, calls, services, globals, entry);
    rows = port_u32(&port, entry->ecx, 0);
    if ((int32_t)port_u32(&port, cinfo, 0x138) <= 0)
    {
        return port_return(&port, cinfo, 0);
    }
    do
    {
        for (v = 0; v < 2; v++)
        {
            near = port_u32(&port, place, 0);
            far = port_u32(&port, place, v != 0 ? 4 : -4u);
            out = port_u32(&port, rows + outrow * 4, 0);
            outrow++;
            this_sum = port_u8(&port, near, 0) * 3 + port_u8(&port, far, 0);
            next_sum = port_u8(&port, near, 1) * 3 + port_u8(&port, far, 1);
            near += 2;
            far += 2;
            out += 2;
            port_set8(&port, out, -2u, (uint32_t)((int32_t)(this_sum * 4 + 8) >> 4));
            port_set8(&port, out, -1u, (uint32_t)((int32_t)(this_sum * 3 + next_sum + 7) >> 4));
            last_sum = this_sum;
            this_sum = next_sum;
            count = port_u32(&port, component, 0x28) - 2;
            while (count != 0 && !port.env.failed)
            {
                next_sum = port_u8(&port, near, 0) * 3 + port_u8(&port, far, 0);
                near++;
                far++;
                port_set8(&port, out, 0, (uint32_t)((int32_t)(last_sum + this_sum * 3 + 8) >> 4));
                port_set8(&port, out, 1, (uint32_t)((int32_t)(next_sum + this_sum * 3 + 7) >> 4));
                count--;
                last_sum = this_sum;
                this_sum = next_sum;
                out += 2;
            }
            port_set8(&port, out, 0, (uint32_t)((int32_t)(last_sum + this_sum * 3 + 8) >> 4));
            port_set8(&port, out, 1, (uint32_t)((int32_t)(this_sum * 4 + 7) >> 4));
        }
        place += 4;
    } while ((int32_t)outrow < (int32_t)port_u32(&port, cinfo, 0x138) && !port.env.failed);
    return port_return(&port, outrow, cinfo);
}
