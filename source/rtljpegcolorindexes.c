#include "rtljpegcolorindexes.h"

/* libjpeg's create_colorindex (jquant1.c): the one-pass quantizer's colour index, a table per
 * output component mapping each sample value to its nearest colour's share of the colormap index,
 * padded on both sides for the ordered dither. */

enum
{
    CINFO_MEM = 4,
    CINFO_DITHER_MODE = 0x58,
    CINFO_OUT_COLOR_COMPONENTS = 0x78,
    CINFO_CQUANTIZE = 0x1cc,
    MEM_ALLOC_SARRAY = 8,
    JPOOL_IMAGE = 1,
    JDITHER_ORDERED = 1,
    MAXJSAMPLE = 255,
    PADDING = MAXJSAMPLE * 2,

    /* The quantizer: the colormap's size, the colour index rows, whether they are padded and the
     * values per component. */
    QUANTIZE_SV_ACTUAL = 0x14,
    QUANTIZE_COLORINDEX = 0x18,
    QUANTIZE_IS_PADDED = 0x1c,
    QUANTIZE_NCOLORS = 0x20,

    LARGEST_INPUT_VALUE = 0x4c5d60
};

/* largest_input_value (0x4c5d60): the largest sample value that maps to output value j of the
 * component (ebx = j, ecx = maxj; eax and edx hold cinfo and the component as the original
 * leaves them). */
static uint32_t largest_input_value(Port *port, uint32_t cinfo, uint32_t component, uint32_t j,
                                    uint32_t maxj)
{
    return port_call(port, LARGEST_INPUT_VALUE, cinfo, component, j, maxj);
}

/* Original 0x4c6020 (eax = cinfo): create_colorindex. With the ordered dither each row is padded
 * by 255 entries on both sides (is_padded set to the dither mode, 1; else 0). The rows come from
 * the image pool's alloc_sarray (mem method +8: 256 + padding wide, one per output component);
 * for each component the block size is the colormap size divided by the colours of this and every
 * earlier component (Ncolors), entry j holds val * block size (a byte) for the first output value
 * val whose largest input value (0x4c5d60) reaches j, and the padding copies the row's ends.
 * Returns the last component's Ncolors address plus 4 (cinfo when there is none). */
uint32_t vertrix_port_jpeg_create_colorindex_4c6020(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t cquantize = port_u32(&port, cinfo, CINFO_CQUANTIZE);
    const uint32_t dither = port_u32(&port, cinfo, CINFO_DITHER_MODE);
    uint32_t pad = 0;
    if (dither == JDITHER_ORDERED)
    {
        pad = PADDING;
        port_set32(&port, cquantize, QUANTIZE_IS_PADDED, dither);
    }
    else
    {
        port_set32(&port, cquantize, QUANTIZE_IS_PADDED, 0);
    }
    const uint32_t mem = port_u32(&port, cinfo, CINFO_MEM);
    port_set32(&port, cquantize, QUANTIZE_COLORINDEX,
               port_call(&port, port_u32(&port, mem, MEM_ALLOC_SARRAY), cinfo, JPOOL_IMAGE,
                         MAXJSAMPLE + 1 + pad, port_u32(&port, cinfo, CINFO_OUT_COLOR_COMPONENTS)));
    int32_t blksize = (int32_t)port_u32(&port, cquantize, QUANTIZE_SV_ACTUAL);
    uint32_t result = cinfo;
    for (uint32_t component = 0;
         (int32_t)component < (int32_t)port_u32(&port, cinfo, CINFO_OUT_COLOR_COMPONENTS) &&
         !port.env.failed;
         component++)
    {
        const int32_t colors =
            (int32_t)port_u32(&port, cquantize, QUANTIZE_NCOLORS + 4 * component);
        if (colors == 0 || (blksize == INT32_MIN && colors == -1))
        {
            /* The original's idiv faults here. */
            port.env.failed = 1;
            break;
        }
        blksize /= colors;
        const uint32_t row = port_u32(&port, cquantize, QUANTIZE_COLORINDEX) + 4 * component;
        if (pad != 0)
        {
            port_set32(&port, row, 0, port_u32(&port, row, 0) + MAXJSAMPLE);
        }
        const uint32_t index = port_u32(&port, row, 0);
        const uint32_t maxj = (uint32_t)colors - 1;
        uint32_t val = 0;
        int32_t k = (int32_t)largest_input_value(&port, cinfo, component, 0, maxj);
        uint32_t share = (val * (uint32_t)blksize) & 0xff;
        for (int32_t j = 0; j <= MAXJSAMPLE && !port.env.failed; j++)
        {
            while (j > k && !port.env.failed)
            {
                val++;
                share = (share + (uint32_t)blksize) & 0xff;
                k = (int32_t)largest_input_value(&port, cinfo, component, val, maxj);
            }
            port_set8(&port, index + (uint32_t)j, 0, share);
        }
        if (pad != 0)
        {
            for (uint32_t j = 1; j <= MAXJSAMPLE; j++)
            {
                port_set8(&port, index - j, 0, port_u8(&port, index, 0));
                port_set8(&port, index + MAXJSAMPLE + j, 0, port_u8(&port, index, MAXJSAMPLE));
            }
        }
        result = cquantize + 4 * component + 4;
    }
    return port_return(&port, result, entry->edx);
}
