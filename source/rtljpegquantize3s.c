#include "rtljpegquantize3s.h"

/* libjpeg's color_quantize3 (jquant1.c): three-component pixels to colormap indexes, no dither. */

enum
{
    CINFO_OUTPUT_WIDTH = 0x70,
    CINFO_CQUANTIZE = 0x1cc,
    /* The quantizer's colorindex: one table per component, each sample's share of the index. */
    CQUANTIZE_COLORINDEX = 0x18
};

/* Original 0x4c6460 (eax = cinfo, edx = input rows, ebx = output rows, ecx = row count): every
 * pixel's index is colorindex[0][r] + colorindex[1][g] + colorindex[2][b] (a byte). The method's
 * callers see eax and edx as the original leaves them: the output rows past the last row and the
 * row count, or with no rows the output width and the input rows. */
uint32_t vertrix_port_jpeg_color_quantize3_4c6460(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t input = entry->edx;
    const uint32_t output = entry->ebx;
    const int32_t rows = (int32_t)entry->ecx;
    const uint32_t colorindex =
        port_u32(&port, port_u32(&port, cinfo, CINFO_CQUANTIZE), CQUANTIZE_COLORINDEX);
    const uint32_t red = port_u32(&port, colorindex, 0);
    const uint32_t green = port_u32(&port, colorindex, 4);
    const uint32_t blue = port_u32(&port, colorindex, 8);
    const uint32_t width = port_u32(&port, cinfo, CINFO_OUTPUT_WIDTH);
    if (rows <= 0)
    {
        return port_return(&port, width, input);
    }
    for (int32_t row = 0; row < rows && !port.env.failed; row++)
    {
        uint32_t in = port_u32(&port, input + row * 4, 0);
        uint32_t out = port_u32(&port, output + row * 4, 0);
        for (uint32_t column = width; column > 0 && !port.env.failed; column--)
        {
            const uint32_t index = port_u8(&port, red + port_u8(&port, in, 0), 0) +
                                   port_u8(&port, green + port_u8(&port, in, 1), 0) +
                                   port_u8(&port, blue + port_u8(&port, in, 2), 0);
            port_set8(&port, out, 0, index);
            in += 3;
            out++;
        }
    }
    return port_return(&port, output + (uint32_t)rows * 4, (uint32_t)rows);
}
