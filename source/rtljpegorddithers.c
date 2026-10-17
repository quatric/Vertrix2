#include "rtljpegorddithers.h"

/* libjpeg's quantize3_ord_dither (jquant1.c): maps three-component rows to colormap indexes,
 * adding the ordered dither matrix row by row. */

enum
{
    CINFO_OUTPUT_WIDTH = 0x70,
    CINFO_CQUANTIZE = 0x1cc,
    /* my_cquantizer: the colour index tables, the dither row and the three dither matrices
     * (16x16 ints). */
    CQUANTIZE_COLORINDEX = 0x18,
    CQUANTIZE_ROW_INDEX = 0x30,
    CQUANTIZE_DITHER = 0x34,
    ODITH_MASK = 0xf,
    DITHER_ROW_BYTES = 0x40
};

/* Original 0x4c6640 (eax = cinfo, edx = input_buf, ebx = output_buf, ecx = num_rows). Reached
 * through a method pointer, so its registers on return are compared: eax is the next dither row
 * and edx the quantizer, or the output width and 0 when there are no rows. */
uint32_t vertrix_port_jpeg_quantize3_ord_dither_4c6640(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t input_buf = entry->edx;
    const uint32_t output_buf = entry->ebx;
    const int32_t num_rows = (int32_t)entry->ecx;
    const uint32_t cquantize = port_u32(&port, cinfo, CINFO_CQUANTIZE);
    const uint32_t colorindex = port_u32(&port, cquantize, CQUANTIZE_COLORINDEX);
    const uint32_t width = port_u32(&port, cinfo, CINFO_OUTPUT_WIDTH);
    uint32_t colorindex_of[3];
    for (unsigned ci = 0; ci < 3; ci++)
    {
        colorindex_of[ci] = port_u32(&port, colorindex, ci * 4);
    }

    if (num_rows <= 0)
    {
        return port_return(&port, width, 0);
    }
    uint32_t row_index = 0;
    for (int32_t row = 0; row < num_rows && !port.env.failed; row++)
    {
        row_index = port_u32(&port, cquantize, CQUANTIZE_ROW_INDEX);
        uint32_t dither[3];
        for (unsigned ci = 0; ci < 3; ci++)
        {
            dither[ci] = port_u32(&port, cquantize, CQUANTIZE_DITHER + ci * 4) +
                         row_index * DITHER_ROW_BYTES;
        }
        uint32_t input = port_u32(&port, input_buf, row * 4);
        uint32_t output = port_u32(&port, output_buf, row * 4);
        uint32_t col_index = 0;
        for (uint32_t col = width; col != 0 && !port.env.failed; col--)
        {
            uint32_t pixcode = 0;
            for (unsigned ci = 0; ci < 3; ci++)
            {
                const uint32_t value =
                    port_u8(&port, input, ci) + port_u32(&port, dither[ci], col_index * 4);
                pixcode += port_u8(&port, colorindex_of[ci], value);
            }
            port_set8(&port, output, 0, pixcode & 0xff);
            input += 3;
            output++;
            col_index = (col_index + 1) & ODITH_MASK;
        }
        row_index = (row_index + 1) & ODITH_MASK;
        port_set32(&port, cquantize, CQUANTIZE_ROW_INDEX, row_index);
    }
    return port_return(&port, row_index, cquantize);
}
