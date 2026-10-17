#include "rtljpegmergedupsamples.h"

/* libjpeg's h2v2_merged_upsample (jdmerge.c): makes two RGB output rows from two luma rows and
 * one row of each chroma component, sharing each chroma pair between four pixels. */

enum
{
    CINFO_OUTPUT_WIDTH = 0x70,
    CINFO_SAMPLE_RANGE_LIMIT = 0x144,
    CINFO_UPSAMPLE = 0x1c4,
    /* my_upsampler: the colour conversion tables. */
    UPSAMPLE_CR_R = 0x10,
    UPSAMPLE_CB_B = 0x14,
    UPSAMPLE_CR_G = 0x18,
    UPSAMPLE_CB_G = 0x1c,
    SCALEBITS = 16
};

typedef struct Chroma
{
    uint32_t red;
    uint32_t green;
    uint32_t blue;
} Chroma;

static uint32_t table(Port *port, uint32_t upsample, uint32_t which, uint32_t index)
{
    return port_u32(port, port_u32(port, upsample, which), index * 4);
}

static Chroma chroma(Port *port, uint32_t upsample, uint32_t cb, uint32_t cr)
{
    Chroma c;
    c.red = table(port, upsample, UPSAMPLE_CR_R, cr);
    c.green = (uint32_t)((int32_t)(table(port, upsample, UPSAMPLE_CB_G, cb) +
                                   table(port, upsample, UPSAMPLE_CR_G, cr)) >>
                         SCALEBITS);
    c.blue = table(port, upsample, UPSAMPLE_CB_B, cb);
    return c;
}

/* Writes one pixel for luma y. Returns the last index into the range table, which the original
 * leaves in eax. */
static uint32_t put_pixel(Port *port, uint32_t range_limit, uint32_t out, uint32_t y,
                          const Chroma *c)
{
    port_set8(port, out, 0, port_u8(port, range_limit, y + c->red));
    port_set8(port, out, 1, port_u8(port, range_limit, y + c->green));
    port_set8(port, out, 2, port_u8(port, range_limit, y + c->blue));
    return y + c->blue;
}

/* Original 0x4c2000 (eax = cinfo, edx = input_buf, ebx = in_row_group_ctr, ecx = output_buf).
 * Reached through a method pointer, so its registers on return are compared: edx is the range
 * table; eax is cinfo, or for an odd width the last range index with the byte read over its low
 * byte. */
uint32_t vertrix_port_jpeg_h2v2_merged_upsample_4c2000(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t input_buf = entry->edx;
    const uint32_t group = entry->ebx;
    const uint32_t output_buf = entry->ecx;
    const uint32_t upsample = port_u32(&port, cinfo, CINFO_UPSAMPLE);

    const uint32_t luma = port_u32(&port, input_buf, 0);
    uint32_t inptr00 = port_u32(&port, luma, group * 8);
    uint32_t inptr01 = port_u32(&port, luma, group * 8 + 4);
    uint32_t inptr1 = port_u32(&port, port_u32(&port, input_buf, 4), group * 4);
    uint32_t inptr2 = port_u32(&port, port_u32(&port, input_buf, 8), group * 4);
    const uint32_t range_limit = port_u32(&port, cinfo, CINFO_SAMPLE_RANGE_LIMIT);
    uint32_t outptr0 = port_u32(&port, output_buf, 0);
    uint32_t outptr1 = port_u32(&port, output_buf, 4);

    for (uint32_t col = port_u32(&port, cinfo, CINFO_OUTPUT_WIDTH) >> 1;
         col != 0 && !port.env.failed; col--)
    {
        const Chroma c =
            chroma(&port, upsample, port_u8(&port, inptr1, 0), port_u8(&port, inptr2, 0));
        inptr1++;
        inptr2++;
        put_pixel(&port, range_limit, outptr0, port_u8(&port, inptr00, 0), &c);
        put_pixel(&port, range_limit, outptr0 + 3, port_u8(&port, inptr00, 1), &c);
        put_pixel(&port, range_limit, outptr1, port_u8(&port, inptr01, 0), &c);
        put_pixel(&port, range_limit, outptr1 + 3, port_u8(&port, inptr01, 1), &c);
        inptr00 += 2;
        inptr01 += 2;
        outptr0 += 6;
        outptr1 += 6;
    }

    if ((port_u8(&port, cinfo, CINFO_OUTPUT_WIDTH) & 1) == 0)
    {
        return port_return(&port, cinfo, range_limit);
    }
    const Chroma c = chroma(&port, upsample, port_u8(&port, inptr1, 0), port_u8(&port, inptr2, 0));
    put_pixel(&port, range_limit, outptr0, port_u8(&port, inptr00, 0), &c);
    const uint32_t index = put_pixel(&port, range_limit, outptr1, port_u8(&port, inptr01, 0), &c);
    return port_return(&port, (index & ~0xffu) | port_u8(&port, range_limit, index), range_limit);
}
