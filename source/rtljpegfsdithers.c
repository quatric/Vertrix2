#include "rtljpegfsdithers.h"

/* libjpeg's pass2_fs_dither (jquant2.c): the two-pass quantizer's mapping of pixel rows with
 * Floyd-Steinberg dithering, the errors limited and kept as 16-bit values. */

enum
{
    CINFO_OUTPUT_WIDTH = 0x70,
    CINFO_COLORMAP = 0x88,
    CINFO_SAMPLE_RANGE_LIMIT = 0x144,
    CINFO_CQUANTIZE = 0x1cc,

    /* The quantizer: the histogram, the error rows, whether this row runs right to left and the
     * error limiting table. */
    QUANTIZE_HISTOGRAM = 0x18,
    QUANTIZE_FSERRORS = 0x20,
    QUANTIZE_ON_ODD_ROW = 0x24,
    QUANTIZE_ERROR_LIMITER = 0x28,

    C0_SHIFT = 3,
    C1_SHIFT = 2,
    C2_SHIFT = 3,
    HIST_C2_ELEMS = 32,
    CELL_SIZE = 2,
    ERROR_SIZE = 2,
    COMPONENTS = 3,

    FILL_INVERSE_CMAP = 0x4c8500
};

/* RIGHT_SHIFT of a signed 32-bit value. */
static uint32_t shift_right(uint32_t value, unsigned count)
{
    return (uint32_t)((int32_t)value >> count);
}

/* One component's error spread: the error stored at the current column (the previous column's
 * error below plus 3 x), the next error below (the earlier one plus 5 x) and the error carried
 * right (7 x). */
typedef struct
{
    uint32_t cur;
    uint32_t belowerr;
    uint32_t bpreverr;
} Spread;

static uint32_t spread(Spread *component)
{
    const uint32_t bnexterr = component->cur;
    const uint32_t delta = component->cur * 2;
    component->cur += delta;
    const uint32_t stored = component->bpreverr + component->cur;
    component->cur += delta;
    component->bpreverr = component->belowerr + component->cur;
    component->belowerr = bnexterr;
    component->cur += delta;
    return stored;
}

/* Original 0x4c8cd0 (eax = cinfo, edx = the input rows, ebx = the output rows, ecx = the row
 * count): pass2_fs_dither. Rows alternate direction (on_odd_row: right to left from the row's end,
 * the errors from the error row's far end). Each pixel adds its component's carried error and the
 * error row's (+8, >> 4), limits it (error_limiter), clamps through the range limit table, looks
 * up its histogram cell (filled by 0x4c8500 when 0), stores the colour and spreads the remaining
 * error. The error row ends with the last errors carried. Returns edx = the row count (0 when
 * there are none) and eax as the original leaves it. */
uint32_t vertrix_port_jpeg_pass2_fs_dither_4c8cd0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t input_buf = entry->edx;
    const uint32_t output_buf = entry->ebx;
    const uint32_t num_rows = entry->ecx;
    const uint32_t cquantize = port_u32(&port, cinfo, CINFO_CQUANTIZE);
    const uint32_t histogram = port_u32(&port, cquantize, QUANTIZE_HISTOGRAM);
    const uint32_t width = port_u32(&port, cinfo, CINFO_OUTPUT_WIDTH);
    const uint32_t range_limit = port_u32(&port, cinfo, CINFO_SAMPLE_RANGE_LIMIT);
    const uint32_t error_limit = port_u32(&port, cquantize, QUANTIZE_ERROR_LIMITER);
    const uint32_t colormap = port_u32(&port, cinfo, CINFO_COLORMAP);
    const uint32_t colormap0 = port_u32(&port, colormap, 0);
    const uint32_t colormap1 = port_u32(&port, colormap, 4);
    const uint32_t colormap2 = port_u32(&port, colormap, 8);
    if ((int32_t)num_rows <= 0)
    {
        return port_return(&port, colormap2, 0);
    }
    uint32_t last = 0;
    for (uint32_t row = 0; (int32_t)row < (int32_t)num_rows && !port.env.failed; row++)
    {
        uint32_t inptr = port_u32(&port, input_buf, 4 * row);
        uint32_t outptr = port_u32(&port, output_buf, 4 * row);
        uint32_t dir;
        uint32_t dir3;
        uint32_t errorptr;
        if (port_u32(&port, cquantize, QUANTIZE_ON_ODD_ROW) != 0)
        {
            inptr += (width - 1) * COMPONENTS;
            outptr += width - 1;
            dir = 0xffffffffu;
            dir3 = 0u - COMPONENTS;
            errorptr = port_u32(&port, cquantize, QUANTIZE_FSERRORS) +
                       (width + 1) * COMPONENTS * ERROR_SIZE;
            port_set32(&port, cquantize, QUANTIZE_ON_ODD_ROW, 0);
        }
        else
        {
            dir = 1;
            dir3 = COMPONENTS;
            errorptr = port_u32(&port, cquantize, QUANTIZE_FSERRORS);
            port_set32(&port, cquantize, QUANTIZE_ON_ODD_ROW, 1);
        }
        Spread spreads[COMPONENTS] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        for (uint32_t col = width; col > 0 && !port.env.failed; col--)
        {
            uint32_t cur[COMPONENTS];
            for (unsigned c = 0; c < COMPONENTS; c++)
            {
                const uint32_t error = (uint32_t)(int32_t)(int16_t)port_u16(
                    &port, errorptr + dir3 * ERROR_SIZE, ERROR_SIZE * c);
                cur[c] = shift_right(spreads[c].cur + error + 8, 4);
                cur[c] = port_u32(&port, error_limit, 4 * cur[c]);
                cur[c] += port_u8(&port, inptr, c);
                cur[c] = port_u8(&port, range_limit, cur[c]);
            }
            const uint32_t cell = port_u32(&port, histogram, 4 * (cur[0] >> C0_SHIFT)) +
                                  (cur[1] >> C1_SHIFT) * HIST_C2_ELEMS * CELL_SIZE +
                                  (cur[2] >> C2_SHIFT) * CELL_SIZE;
            if (port_u16(&port, cell, 0) == 0)
            {
                port_call(&port, FILL_INVERSE_CMAP, cinfo, cur[0] >> C0_SHIFT, cur[1] >> C1_SHIFT,
                          cur[2] >> C2_SHIFT);
            }
            const uint32_t pixcode = port_u16(&port, cell, 0) - 1;
            port_set8(&port, outptr, 0, pixcode);
            spreads[0].cur = cur[0] - port_u8(&port, colormap0, pixcode);
            spreads[1].cur = cur[1] - port_u8(&port, colormap1, pixcode);
            spreads[2].cur = cur[2] - port_u8(&port, colormap2, pixcode);
            for (unsigned c = 0; c < COMPONENTS; c++)
            {
                port_set16(&port, errorptr, ERROR_SIZE * c, spread(&spreads[c]));
            }
            inptr += dir3;
            outptr += dir;
            errorptr += dir3 * ERROR_SIZE;
        }
        for (unsigned c = 0; c < COMPONENTS; c++)
        {
            port_set16(&port, errorptr, ERROR_SIZE * c, spreads[c].bpreverr);
        }
        last = spreads[2].bpreverr;
    }
    return port_return(&port, last, num_rows);
}
